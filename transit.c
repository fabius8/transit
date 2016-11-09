/*
 * AP信息采集汇聚点
 *
 * Written by Fang Zheng <fangzheng@gbcom.com.cn>
 *
 * Copyright 2016, GBCOM, Inc. All Rights Reserved
 * See http://
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

#include "transit.h"

/*
 * 全局变量
 */
struct tr_app trapp = {0};

/*
 * 宏定义
 */
#define APP "transit"

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

/*
 * 主函数
 */
int main(int argc, char **argv)
{

    int c;
    while ((c = getopt(argc, argv, "h:u:d:x")) != -1) {
        switch(c) {
        case 'u':
            trapp.usr_key = optarg;
            printf("user key: %s \n", trapp.usr_key);
            break;
        case 'd':
            trapp.isdaemon = 1;
            skeleton_daemon();
            break;
        case 'h':
            trapp.ftp_url = optarg;
            printf("ftpserver: %s \n", trapp.ftp_url);
            break;
        case 'x':
            trapp.debug = 1;
            break;
        default:
            printf("Usage: transit \n");
            printf("\t -h: ftpserver's ip or hostname\n");
            printf("\t -u: ftpserver's user name and password, like 'root:123456'\n");
            printf("\t -d: run in daemon\n");
            printf("\t -x: enable log\n");
            exit(1);
        }
    }

    openlog(APP, LOG_PID, LOG_DAEMON);


    /* FTP_OPT ftp_option; */
    /* char *dir = "/a/b/"; */
    /* char *filename = "upload.txt"; */
    /* ftp_opt_cfg(&ftp_option, ftpserver, usrPwd, dir, "upload.txt"); */

    /* if(FTP_UPLOAD_SUCCESS == ftp_upload(ftp_option)) */
    /*     tr_log(LOG_INFO, "Upload success.\n"); */
    /* else */
    /*     tr_log(LOG_INFO, "Upload failed.\n"); */
    trapp.base = event_base_new();

    if(!trapp.base) {
        tr_log(LOG_INFO, "event_base_new Failed, Exiting");
        return -1;
    }


    event_base_dispatch(trapp.base);
    return 0;
}
