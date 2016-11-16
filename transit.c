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
#define TIME_INTERVAL           10
#define MAX_LOG_TYPE_NUM        15
#define SAVE_FILE_DIR           "/tmp/"
#define create_file(x) clear_file_buffer(x)

const char *log_type[] = {
    "WLRZ", "FJGJ", "JSTX", "XWRZ", "SJRZ",
    "PTNR", "SGJZ", "CSZL", "CSZT", "SBZL",
    "JSJZT", "SBGJ", "RZSJ", "SJTZ", "PNFJ"
};

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
 * ftp参数配置
 */
void ftp_opt_cfg(FTP_OPT *ftp_opt,
                 char *ftpserver,
                 char *usrPwd,
                 char *dir,
                 char *uploadName,
                 char *orgName)
{
    if (!ftp_opt)
        return;
    sprintf(ftp_opt->url, "%s%s%s%s", "ftp://", ftpserver, dir, uploadName);
    tr_log(LOG_INFO, "url: %s\n", ftp_opt->url);

    if (!usrPwd)
        ftp_opt->user_key = "anonymous:anonymous";
    else
        ftp_opt->user_key = usrPwd;
    ftp_opt->file = orgName;
}

/*
 * 初始化读取配置
 */
void readcfg(char *filecfg)
{
    sprintf(trapp.cfg.dataAcqSysType, "%.3s", "123");
    sprintf(trapp.cfg.dataGenIden, "%.6s", "666666");
    sprintf(trapp.cfg.vendorOrgCode, "%.9s", "123456789");

    dictionary *dict = iniparser_load(filecfg);
    if (dict == NULL) {
        tr_log(LOG_ERR, "cannot parse file: %s\n", dict);
        return ;
    }

    iniparser_dump(dict, stderr);

    iniparser_freedict(dict);
}

/*
 * 文件命名
 * example: 20150605093157706_123_440303_723005104_002.log
 */
void createUploadFilename(char *filename, char *dataAcqSysType,
                          char *dataGenIden, char *vendorOrgCode,
                          char *logType, char *suffix)
{
    time_t t;
    struct tm *timeinfo;
    int random;

    if (!filename)
        return;

    t = time(NULL);
    timeinfo = localtime(&t);

    srand((unsigned)time(&t));
    random = rand() % 1000;
    sprintf(filename,
            "%d%02d%02d"
            "%02d%02d%02d%03d"
            "_%.3s_%.6s_%.9s"
            "_%.3s.%s",
            timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, random,
            dataAcqSysType, dataGenIden, vendorOrgCode,
            logType, suffix);
}

/*
 * FTP上传文件
 */
void tr_ftp_upload(const char *orgName, char *uploadName, const char *logType,
                   char *ftp_url, char *usr_key)
{
    char fullpath[256] = {0};
    char dir[256] = {0};
    FTP_OPT ftp_option;
    time_t t;
    struct tm *timeinfo;

    t = time(NULL);
    timeinfo = localtime(&t);

    sprintf(dir,
            "/%s/"
            "%d%02d%02d/"
            "%02d/%02d/",
            logType,
            timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
            timeinfo->tm_hour, timeinfo->tm_min);

    sprintf(fullpath, SAVE_FILE_DIR"%s", orgName);

    ftp_opt_cfg(&ftp_option, ftp_url, usr_key, dir, uploadName, fullpath);

    if (FTP_UPLOAD_SUCCESS == ftp_upload(ftp_option))
        tr_log(LOG_INFO, "Upload success.\n");
    else
        tr_log(LOG_INFO, "Upload failed.\n");
}

/*
 * 清空文件
 */
void clear_file_buffer(const char *filename)
{
    char fullpath[256] = {0};

    if (filename) {
        sprintf(fullpath, SAVE_FILE_DIR"%s", filename);
        fclose(fopen(fullpath, "w"));
    }
}

/*
 * 文件插入buffer
 */
void insert_file_buffer(const char *filename, char *buffer)
{
    char fullpath[256] = {0};
    FILE *fp;

    if (filename && buffer) {
        sprintf(fullpath, SAVE_FILE_DIR"%s", filename);
        fp = fopen(fullpath, "a+");
        fwrite(buffer, 1, strlen(buffer), fp);
        fclose(fp);
    }
}

/*
 * check file is empty or not
 */
int isEmpty(const char *filename)
{
    char fullpath[256] = {0};
    struct stat st;

    sprintf(fullpath, SAVE_FILE_DIR"%s", filename);
    if (stat(fullpath, &st) != 0) {
        return 1;
    }
    if (st.st_size)
        return 0;
    else
        return 1;
}

/*
 * substring to be replace
 */
void replace_str(char *str, char *sub, char *rep)
{
    char *p;

    if(!(p = strstr(str, sub)))
        return;

    sprintf(str + (p - str), "%s%s", rep, p + strlen(sub));
    return;
}

void timer_cb(evutil_socket_t fd, short event, void *arg)
{
    char uploadName[256] = {0};
    tr_log(LOG_INFO, "Time up! Wait next %d secs", TIME_INTERVAL);

    if (isEmpty(log_type[0])) {
        tr_log(LOG_INFO, "%s is empty!", log_type[0]);
        return;
    } else {
        tr_log(LOG_INFO, "report %s!", log_type[0]);

        insert_file_buffer(log_type[0], "]");
        createUploadFilename(uploadName,
                             trapp.cfg.dataAcqSysType,
                             trapp.cfg.dataGenIden,
                             trapp.cfg.vendorOrgCode,
                             "001", "log");
        tr_ftp_upload(log_type[0], uploadName, log_type[0],
                      trapp.ftp_url, trapp.usr_key);
        clear_file_buffer(log_type[0]);

        sprintf(uploadName + strlen(uploadName), "%s", ".ok");
        tr_ftp_upload(log_type[0], uploadName, log_type[0],
                      trapp.ftp_url, trapp.usr_key);
    }
}

void apmsg_recv_cb(evutil_socket_t fd, short what, void *arg)
{
    tr_log(LOG_INFO, "recv ap msg ... fd: %d", fd);
    struct sockaddr_in addr;
    int addr_len;
    int msg_len;
    unsigned char msg[4096];

    msg_len = recvfrom(fd, msg, sizeof(msg), 0,
                       (struct sockaddr *)&addr, &addr_len);
    if (msg_len < 0) {
        tr_log(LOG_ERR, "recv msg fail! errno: %d", errno);
        tr_log(LOG_ERR, "%s", strerror(errno));
        return;
    }
    printHexBuffer(msg, msg_len);

    /* parse to json */

    /* write to file */
    char *buf = "{\"test\":11,\"af\":22}";
    if (isEmpty(log_type[0])) {
        insert_file_buffer(log_type[0], "[");
    } else {
        insert_file_buffer(log_type[0], ",");
    }
    insert_file_buffer(log_type[0], buf);
}

/*
 * 主函数
 */
int main(int argc, char **argv)
{
    int c;
    while ((c = getopt(argc, argv, "f:r:k:dx")) != -1) {
        switch(c) {
        case 'k':
            trapp.usr_key = optarg;
            printf("user key: %s \n", trapp.usr_key);
            break;
        case 'f':
            trapp.filecfg = optarg;
            printf("filecfg: %s \n", trapp.filecfg);
            break;
        case 'r':
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
            printf("\t -r: ftpserver's ip or hostname\n");
            printf("\t -k: ftpserver's username and password, 'root:123456'\n");
            printf("\t -d: run in daemon\n");
            printf("\t -x: enable log\n");
            printf("example: ./transit -d -x -k aaa:123 -r 10.1.1.1\n");
            exit(1);
        }
    }

    if (trapp.isdaemon) {
        openlog(APP, LOG_PID, LOG_DAEMON);
        skeleton_daemon();
    }

    tr_log(LOG_INFO, "transt starting..\n");

    readcfg(trapp.filecfg);

    udpserver_init(&trapp.sock, APP_PORT);

    trapp.base = event_base_new();
    if(!trapp.base) {
        tr_log(LOG_ERR, "event_base_new Failed, Exiting");
        return -1;
    }

    /* recv AP msg  */
    trapp.ev_udp = event_new(trapp.base, trapp.sock, EV_PERSIST | EV_READ,
                             apmsg_recv_cb, NULL);
    event_add(trapp.ev_udp, NULL);

    /* Every 5 minutes */
    struct event *ev_timeout;
    struct timeval tv;
    ev_timeout = event_new(trapp.base, -1, EV_PERSIST | EV_TIMEOUT,
                           timer_cb, NULL);
    evutil_timerclear(&tv);
    tv.tv_sec = TIME_INTERVAL;
    event_add(ev_timeout, &tv);

    event_base_dispatch(trapp.base);

    return 0;
}
