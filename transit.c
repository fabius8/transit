/*
 * AP信息采集汇聚点
 *
 * Written by Fang Zheng <fangzheng@gbcom.com.cn>
 *
 * Copyright 2016, GBCOM, Inc. All Rights Reserved
 * See http://
 */

#include "transit.h"

/*
 * 全局变量
 */
struct tr_app trapp = {0};

/*
 * 宏定义
 */
#define APP                     "transit"
#define APP_PORT                6666
#define CREATE_DIR_TIME         5

/*
 * 日志
 */
int log_priority;
void tr_log(int level, const char *fmt, ...)
{
    if (!trapp.debug)
        return;

    va_list list;
    va_start(list, fmt);
    if (trapp.isdaemon)
        vsyslog(log_priority | level, fmt, list);
    else
        vprintf(fmt, list);
    va_end(list);
}

/*
 * ftp配置
 */
void ftp_opt_cfg(FTP_OPT *ftp_opt,
                 char *ftpserver,
                 char *usrPwd,
                 char *dir,
                 char *filename)
{
    if (!ftp_opt)
        return;
    sprintf(ftp_opt->url, "%s%s%s%s", "ftp://", ftpserver, dir, filename);
    tr_log(LOG_INFO, "url: %s\n", ftp_opt->url);

    if (!usrPwd)
        ftp_opt->user_key = "anonymous:anonymous";
    else
        ftp_opt->user_key = usrPwd;
    ftp_opt->file = filename;
}

void create_dir_cb(evutil_socket_t fd, short event, void *arg)
{
    FTP_OPT ftp_option;
    time_t t = time(NULL);
    char *filename = "";
    struct tm tm;

    t = time(NULL);
    tm = *localtime(&t);

    sprintf(trapp.current_dir, "/%d%02d%02d/%02d/%02d/",
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
            tm.tm_hour, tm.tm_min);
    ftp_opt_cfg(&ftp_option,
                trapp.ftp_url, trapp.usr_key, trapp.current_dir, filename);

    if (FTP_UPLOAD_SUCCESS == ftp_create_dirs(ftp_option))
        tr_log(LOG_INFO, "Upload success.\n");
    else
        tr_log(LOG_INFO, "Upload failed.\n");
}

void apmsg_recv_cb(evutil_socket_t fd, short what, void *arg)
{
    tr_log(LOG_INFO, "recv ap msg ...");
    struct sockaddr_in addr;
    int addr_len;
    int msg_len;
    unsigned char msg[1024];

    msg_len = recvfrom(fd, msg, sizeof(msg), 0,
                       (struct sockaddr *)&addr, &addr_len);
    printHexBuffer(msg, msg_len);

    /* parse to json */
    /* write to file */
}

/*
 * 主函数
 */
int main(int argc, char **argv)
{
    int c;
    while ((c = getopt(argc, argv, "h:u:dx")) != -1) {
        switch(c) {
        case 'u':
            trapp.usr_key = optarg;
            printf("user key: %s \n", trapp.usr_key);
            break;
        case 'h':
            trapp.ftp_url = optarg;
            printf("ftpserver: %s \n", trapp.ftp_url);
            break;
        case 'x':
            printf("enable log\n");
            trapp.debug = 1;
            break;
        case 'd':
            trapp.isdaemon = 1;
            break;
        default:
            printf("Usage: transit \n");
            printf("\t -h: ftpserver's ip or hostname\n");
            printf("\t -u: ftpserver's username and password, 'root:123456'\n");
            printf("\t -d: run in daemon\n");
            printf("\t -x: enable log\n");
            printf("example: ./transit -d -x -u aaa:123 -h 10.1.1.1\n");
            exit(1);
        }
    }

    if (trapp.isdaemon) {
        openlog(APP, LOG_PID, LOG_DAEMON);
        skeleton_daemon();
    }

    tr_log(LOG_INFO, "transt starting..\n");

    /* FTP_OPT ftp_option; */
    /* char *dir = "/a/b/"; */
    /* char *filename = "upload.txt"; */
    /* ftp_opt_cfg(&ftp_option, ftpserver, usrPwd, dir, "upload.txt"); */

    /* if(FTP_UPLOAD_SUCCESS == ftp_upload(ftp_option)) */
    /*     tr_log(LOG_INFO, "Upload success.\n"); */
    /* else */
    /*     tr_log(LOG_INFO, "Upload failed.\n"); */

    udpserver_init(&trapp.sock, APP_PORT);

    trapp.base = event_base_new();
    if(!trapp.base) {
        tr_log(LOG_ERR, "event_base_new Failed, Exiting");
        return -1;
    }

    /* event for recv AP msg  */
    trapp.ev_udp = event_new(trapp.base, trapp.sock, EV_PERSIST | EV_READ,
                             apmsg_recv_cb, NULL);
    event_add(trapp.ev_udp, NULL);

    /* ftp create dir in 5 minutes */
    struct event *ev_timeout;
    struct timeval tv;
    ev_timeout = event_new(trapp.base, -1, EV_PERSIST | EV_TIMEOUT,
                           create_dir_cb, NULL);
    evutil_timerclear(&tv);
    tv.tv_sec = CREATE_DIR_TIME;
    event_add(ev_timeout, &tv);

    event_base_dispatch(trapp.base);

    return 0;
}
