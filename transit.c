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
struct tr_service_info trcszl = {0};
struct tr_equipment_info trsbzl = {0};
const char *log_type[] = {
    "CONFIG",
    "WLRZ", "FJGJ", "JSTX", "XWRZ", "SJRZ",
    "PTNR", "SGJZ", "CSZL", "CSZT", "SBZL",
    "JSJZT", "SBGJ", "RZSJ", "SJTZ", "PNFJ"
};
FILE_LIST_T file_list_head;


/*
 * 宏定义
 */
#define APP                     "transit"
#define APP_PORT                6666
#define TIME_INTERVAL           60*5
#define MAX_LOG_TYPE_NUM        15
#define SAVE_FILE_DIR           "/tmp/"

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
 * 重命名文件
 */
void renameFile(char *dir, char *old, char *new)
{
    char fullpath_old[1024] = {0};
    char fullpath_new[1024] = {0};
    sprintf(fullpath_old, "%s%s", dir, old);
    sprintf(fullpath_new, "%s%s", dir, new);
    rename(old, new);
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
 * 读取 LOG/SBZL 配置
 */
void json_parser_sbzl(const char *filecfg)
{
}

/*
 * 读取 LOG/CSZL 配置
 * HOWTO use parson api, see: https://github.com/kgabis/parson
 */
void json_parser_cszl(const char *filecfg)
{
    char fullpath[256] = {0};
    JSON_Value *root_value;
    JSON_Array *objs;
    JSON_Object *obj;

    sprintf(fullpath, "%s/""%s", trapp.dir_for_jsons, filecfg);
    tr_log(LOG_INFO, "config file is: %s", fullpath);

    root_value = json_parse_file(fullpath);
    objs = json_value_get_array(root_value);
    obj = json_array_get_object(objs, 0);

    sprintf(trcszl.N01_service_code, "%.14s",
            json_object_get_string(obj, "SERVICE_CODE")?
            json_object_get_string(obj, "SERVICE_CODE"):
            "12345678901234");

    sprintf(trcszl.N31_xpoint, "%s",
            json_object_get_string(obj, "XPOINT")?
            json_object_get_string(obj, "XPOINT"):
            "0.0");

    sprintf(trcszl.N32_ypoint, "%s",
            json_object_get_string(obj, "YPOINT")?
            json_object_get_string(obj, "YPOINT"):
            "0.0");

    json_value_free(root_value);
}

/*
 * 读取 LOG/CONFIG 配置
 */
void json_parser_config(const char *filecfg)
{
    char fullpath[256] = {0};
    JSON_Value *root_value;
    JSON_Object *obj;

    sprintf(fullpath, "%s/""%s", trapp.dir_for_jsons, filecfg);
    tr_log(LOG_INFO, "config file is: %s", fullpath);

    root_value = json_parse_file(fullpath);
    obj = json_value_get_object(root_value);

    sprintf(trapp.cfg.dataAcqSysType, "%.3s",
            json_object_get_string(obj, "DateAcquisition")?
            json_object_get_string(obj, "DateAcquisition"):
            "000");
    sprintf(trapp.cfg.dataGenIden, "%.6s",
            json_object_get_string(obj, "DataGenerationIdentifier")?
            json_object_get_string(obj, "DataGenerationIdentifier"):
            "000000");
    sprintf(trapp.cfg.vendorOrgCode, "%.9s",
            json_object_get_string(obj, "VendorOrganizationCode")?
            json_object_get_string(obj, "VendorOrganizationCode"):
            "000000000");
    sprintf(trapp.cfg.company_id, "%s",
            json_object_get_string(obj, "COMPANY_ID")?
            json_object_get_string(obj, "COMPANY_ID"):
            "723005104");

    json_value_free(root_value);

}

/*
 * 文件命名
 * Example: 20150605093157706_123_440303_723005104_002.log
 */
void getUploadFilename(char *filename, char *dataAcqSysType,
                          char *dataGenIden, char *vendorOrgCode,
                          int logType, char *suffix)
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
            "_%03d.%s",
            timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
            timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, random,
            dataAcqSysType, dataGenIden, vendorOrgCode,
            logType, suffix);
}

/*
 * FTP上传文件
 */
void tr_ftp_upload(const char *orgName,
                   char *uploadName,
                   char *uploadDir,
                   const char *logType,
                   char *ftp_url,
                   char *usr_key)
{
    char fullpath[256] = {0};
    char dir[256] = {0};
    FTP_OPT ftp_option;
    time_t t;
    struct tm *timeinfo;

    t = time(NULL);
    timeinfo = localtime(&t);

    if (!uploadDIr) {
        sprintf(dir,
                "/%s/"
                "%d%02d%02d/"
                "%02d/%02d/",
                logType,
                timeinfo->tm_year + 1900,
                timeinfo->tm_mon + 1,
                timeinfo->tm_mday,
                timeinfo->tm_hour,
                timeinfo->tm_min);
    } else {
        sprintf(dir, "%s", uploadDir);
    }

    sprintf(fullpath, "%s/""%s", trapp.dir_for_jsons, orgName);

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
        sprintf(fullpath, "%s/""%s", trapp.dir_for_jsons, filename);
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
        sprintf(fullpath, "%s/""%s", trapp.dir_for_jsons, filename);
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

    sprintf(fullpath, "%s/""%s", trapp.dir_for_jsons, filename);
    if (stat(fullpath, &st) != 0) {
        return 1;
    }
    if (st.st_size)
        return 0;
    else
        return 1;
}

/*
 * 发送WLRZ日志, 以后会加入其他日志发送
 */
void upload_json_cb(evutil_socket_t fd, short event, void *arg)
{
    char uploadName[256] = {0};
    tr_log(LOG_INFO, "Report %s!", log_type[WLRZ]);

    if (isEmpty(log_type[WLRZ])) {
        tr_log(LOG_INFO, "%s is empty!", log_type[WLRZ]);
        return;
    } else {

        insert_file_buffer(log_type[WLRZ], "]");
        getUploadFilename(uploadName,
                             trapp.cfg.dataAcqSysType,
                             trapp.cfg.dataGenIden,
                             trapp.cfg.vendorOrgCode,
                             WLRZ, "log");
        tr_ftp_upload(log_type[WLRZ], uploadName, NULL, log_type[WLRZ],
                      trapp.ftp_url, trapp.usr_key);
        clear_file_buffer(log_type[WLRZ]);

        sprintf(uploadName + strlen(uploadName), "%s", ".ok");
        tr_ftp_upload(log_type[WLRZ], uploadName, NULL, log_type[WLRZ],
                      trapp.ftp_url, trapp.usr_key);
    }

    tr_log(LOG_INFO, "Report end", TIME_INTERVAL);
}

/*
 * 第一次启动系统发送某个日志，发送完不清空
 */
void init_send_json(int num)
{
    char uploadName[256] = {0};

    if (isEmpty(log_type[num])) {
        tr_log(LOG_INFO, "%s is empty!", log_type[num]);
        return;
    } else {
        tr_log(LOG_INFO, "report %s!", log_type[num]);

        getUploadFilename(uploadName,
                             trapp.cfg.dataAcqSysType,
                             trapp.cfg.dataGenIden,
                             trapp.cfg.vendorOrgCode,
                             num, "log");
        tr_ftp_upload(log_type[num], uploadName, NULL, log_type[num],
                      trapp.ftp_url, trapp.usr_key);

        sprintf(uploadName + strlen(uploadName), "%s", ".ok");
        tr_ftp_upload(log_type[num], uploadName, NULL, log_type[num],
                      trapp.ftp_url, trapp.usr_key);
    }

}

void parser_mdu_into_json(int *plus,
                          struct locator_mdu_payload_dw_audit *mdu,
                          char *json)
{
    *plus += sprintf(json + *plus, "%s", "{");

    *plus += sprintf(json + *plus,
                     "\"MAC\":\""MAC_FMT"\",", MAC_ARG(mdu->muMac));
    *plus += sprintf(json + *plus,
                     "\"TYPE\":%d,", 2);
    time_t t;
    t = time(NULL);
    *plus += sprintf(json + *plus,
                     "\"START_TIME\":%u,", t);
    *plus += sprintf(json + *plus,
                     "\"END_TIME\":%u,", 0);
    *plus += sprintf(json + *plus,
                     "\"POWER\":%hhd,", mdu->AbsRssi);
    *plus += sprintf(json + *plus,
                     "\"BSSID\":\""MAC_FMT"\",", MAC_ARG(mdu->bssid));
    *plus += sprintf(json + *plus,
                     "\"ESSID\":\"%s\",", mdu->ssid);
    *plus += sprintf(json + *plus,
                     "\"HISTORY_ESSID\":\"%s\",", "");
    *plus += sprintf(json + *plus,
                     "\"MODEL\":\"%s\",", "");
    *plus += sprintf(json + *plus,
                     "\"OS_VERSION\":\"%s\",", "");
    *plus += sprintf(json + *plus,
                     "\"IMEI\":\"%s\",", "");
    *plus += sprintf(json + *plus,
                     "\"IMSI\":\"%s\",", "");
    *plus += sprintf(json + *plus,
                     "\"STATION\":\"%s\",", "");
    *plus += sprintf(json + *plus,
                     "\"XPOINT\":\"%s\",", trcszl.N31_xpoint);
    *plus += sprintf(json + *plus,
                     "\"YPOINT\":\"%s\",", trcszl.N32_ypoint);
    *plus += sprintf(json + *plus,
                     "\"PHONE\":\"%s\",", "");
    *plus += sprintf(json + *plus,
                     "\"DEVMAC\":\""MAC_FMT"\",", MAC_ARG(mdu->apMac));
    *plus += sprintf(json + *plus,
                     "\"DEVICENUM\":\"%s"MAC_FMT_L"\",",
                     trapp.cfg.company_id, MAC_ARG(mdu->apMac));
    *plus += sprintf(json + *plus,
                     "\"SERVICECODE\":\"%s\",", trcszl.N01_service_code);
    *plus += sprintf(json + *plus,
                     "\"PROTOCOL_TYPE\":\"%s\",", "");
    *plus += sprintf(json + *plus,
                     "\"ACCOUNT\":\"%s\",", "");
    *plus += sprintf(json + *plus,
                     "\"FLAG\":\"%s\",", "");
    *plus += sprintf(json + *plus,
                     "\"URL\":\"%s\",", "");
    *plus += sprintf(json + *plus,
                     "\"COMPANY_ID\":\"%s\",", trapp.cfg.company_id);
    *plus += sprintf(json + *plus,
                     "\"AP_CHANNEL\":\"%hhu\",", mdu->channel);
    *plus += sprintf(json + *plus,
                     "\"AP_ENCRYTYPE\":\"%hhu\",",
                     mdu->encryptType?mdu->encryptType:99);
    *plus += sprintf(json + *plus,
                     "\"CONSULT_XPOINT\":\"%s\",", "");
    *plus += sprintf(json + *plus,
                     "\"CONSULT_YPOINT\":\"%s\"", "");

    *plus += sprintf(json + *plus, "%s", "}");
}

int parser_apmsg_to_json(unsigned char *msg, int msg_len, char *json)
{
    int plus = strlen(json);
    int header_size;
    int number_size;
    int value_size;
    int total_value_size;
    struct locator_mdu_payload_dw_audit *mdu;

    header_size = sizeof(struct locator_mdu_pdu_head_dw_audit);
    number_size = sizeof(struct locator_mdu_num_dw_audit);
    value_size = sizeof(struct locator_mdu_payload_dw_audit);

    struct locator_mdu_pdu_head_dw_audit *pdu_head = \
        (struct locator_mdu_pdu_head_dw_audit *)msg;
    struct locator_mdu_num_dw_audit *num_mdu = \
        (struct locator_mdu_num_dw_audit *)(msg + header_size);

    num_mdu->MDUNumber = ntohs(num_mdu->MDUNumber);
    total_value_size = value_size * (num_mdu->MDUNumber);

    pdu_head->header = ntohs(pdu_head->header);
    pdu_head->requestId = ntohs(pdu_head->requestId);
    pdu_head->dataLength = ntohl(pdu_head->dataLength);

    if (pdu_head->header != DW_AUDIT_HEADER) {
        tr_log(LOG_INFO, "Wrong header: %hu", pdu_head->header);
        return -1;
    }

    if ((msg_len - sizeof(struct locator_mdu_pdu_head_dw_audit)) != \
        pdu_head->dataLength) {
        tr_log(LOG_INFO, "Wrong msg! msg_len: %d, head_len: %d, data_len: %d",
               msg_len, sizeof(struct locator_mdu_pdu_head_dw_audit),
               pdu_head->dataLength);
        return -1;
    }

    if ((pdu_head->dataLength) != (number_size + \
                                   total_value_size)) {
        tr_log(LOG_INFO, "Wrong msg:%d %d %d %d value_size:%d number:%d",
               msg_len, pdu_head->dataLength, number_size,
               total_value_size, value_size, num_mdu->MDUNumber);
        return -1;
    }

    tr_log(LOG_INFO, "%s", json);
    if (plus >= value_size)
        plus += sprintf(json + plus, "%s", ",");

    int i = 0;
    for (i; i < num_mdu->MDUNumber; i++) {
        mdu = (struct locator_mdu_payload_dw_audit *)(msg +             \
                                                      header_size +     \
                                                      number_size +     \
                                                      i * value_size);
        mdu->header = ntohs(mdu->header);
        if (mdu->header != DW_AUDIT_HEADER)
            break;
        mdu->vendorId = ntohs(mdu->vendorId);
        mdu->timestamp = ntohl(mdu->timestamp);
        mdu->frameCtrl = ntohs(mdu->frameCtrl);
        mdu->seqCtrl = ntohs(mdu->seqCtrl);

        if (plus >= value_size)
            plus += sprintf(json + plus, "%s", ",\n");
        parser_mdu_into_json(&plus, mdu, json);
        trapp.count_wlrz ++;

        /* DROP other */
        if(trapp.count_wlrz >= 10000) {
            tr_log(LOG_INFO, "i:%d, count: %d, strlen: %d",
                   i, trapp.count_wlrz, strlen(json));
            return 0;
        }
    }

    return 0;
}

/*
 * Recv AP masg, use 64k buffer to avoid truncation
 */
void apmsg_recv_cb(evutil_socket_t fd, short what, void *arg)
{
    tr_log(LOG_INFO, "recv ap msg ... fd: %d", fd);

    int addr_len;
    int msg_len;
    char json[1024*64*8] = {0};
    unsigned char msg[1024*64];
    struct sockaddr_in addr;

    msg_len = recvfrom(fd, msg, sizeof(msg), 0,
                       (struct sockaddr *)&addr, &addr_len);
    if (msg_len < 0) {
        tr_log(LOG_ERR, "recv msg fail! errno: %d", errno);
        tr_log(LOG_ERR, "%s", strerror(errno));
        return;
    }
    //printHexBuffer(msg, msg_len);

     /* write to file */
    if (isEmpty(log_type[WLRZ])) {
        insert_file_buffer(log_type[WLRZ], "[");
    } else {
        insert_file_buffer(log_type[WLRZ], ",\n");
    }

   /* parse to json */
    if ( -1 == parser_apmsg_to_json(msg, msg_len, json)) {
        return;
    }

    insert_file_buffer(log_type[WLRZ], json);
    if (trapp.count_wlrz >=10000) {
        insert_file_buffer(log_type[WLRZ], "]");
        char newFileName[256] = {0};
        getUploadFilename(newFileName,
                             trapp.cfg.dataAcqSysType,
                             trapp.cfg.dataGenIden,
                             trapp.cfg.vendorOrgCode,
                             WLRZ, "log");
        renameFile(trapp.dir_for_jsons, log_type[WLRZ], newFileName);
        //upload_json_cb(-1, -1, NULL);
        trapp.count_wlrz = 0;
    }
}

void add_list_search_file(char *name,
                          char *filter,
                          struct list_head *head)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;
    if (!(entry = readdir(dir)))
        return;

    do {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            int len = snprintf(path,
                               sizeof(path)-1,
                               "%s/%s", name, entry->d_name);
            path[len] = 0;
            if (strcmp(entry->d_name, ".") == 0 ||
                strcmp(entry->d_name, "..") == 0)
                continue;
        } else {
            if (strstr(entry->d_name, filter))
                add_file_list(entry->d_name, head);
        }
    } while (entry = readdir(dir));
    closedir(dir);
}

int add_file_list(char *filename, struct list_head *head)
{
    FILE_LIST_T *node;
    node = (FILE_LIST_T*)malloc(sizeof(FILE_LIST_T));
    memset(node, 0, sizeof(FILE_LIST_T));
    node->localfilename = strdup(filename);
    list_add(&(node->stList), head);

    return 0;
}

int upload_file_list(char *uploaddir, struct list_head *head)
{
    struct list_head *pos, *q;
    FILE_LIST_T *tmp;
    char localFile[1024] = {0};
    char uploadFile[1024] = {0};
    char fullpathFile[1024] = {0};
    list_for_each_safe(pos, q, head) {
        tmp = list_entry(pos, FILE_LIST_T, stList);

        /* upload */
        sprintf(localFile, "%s", tmp->localfilename);
        sprintf(uploadFile, "%s", tmp->localfilename);
        tr_ftp_upload(localFile, uploadFile, uploadDir, WLRZ,
                      trapp.ftp_url, trapp.usr_key);
        clear_file_buffer(localFile);
        sprintf(uploadFile + strlen(uploadFile), "%s", ".ok");
        tr_ftp_upload(localFile, uploadFile, NULL, log_type[WLRZ],
                      trapp.ftp_url, trapp.usr_key);

        /* rm file */
        sprintf(fullpathFile, "%s""%s", trapp.dir_for_jsons, localFile);
        remove(fullpathFile);

        free(tmp->localfilename);
        list_del(pos);
        free(tmp);
    }

    return 0;
}

void getUploadDir(char *dir, char *logType)
{
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
}

void thread_call(char *uploadDir, struct list_head *head)
{
    add_list_search_file(trapp.dir_for_jsons, "001.log", head);
    upload_file_list(uploadDir, head);
}

/*
 * 这个线程为了ftp上报文件信息, ftp的异步太难了
 */
void *threadFunc(void *arg)
{
    struct timeval t;
    INIT_LIST_HEAD(&file_list_head.stList);
    char dir[1024] = {0};
    getUploadDir(dir, WLRZ);

    while (1) {
        t.tv_sec = TIME_INTERVAL;
        t.tv_usec = 0;
        select(0, NULL, NULL, NULL, &t);
        thread_call(dir, &file_list_head.stList);
    }
    return 0;
}

/*
 * 获取日志存放目录
 */
void init_json_dir()
{
    if (!trapp.dir_for_jsons)
        trapp.dir_for_jsons = SAVE_FILE_DIR;
    char command[512];
    sprintf(command, "mkdir -p %s", trapp.dir_for_jsons);
    system(command);
}

/*
 * 主函数
 */
int main(int argc, char **argv)
{
    int c;
    while ((c = getopt(argc, argv, "D:r:k:p:dx")) != -1) {
        switch(c) {
        case 'k':
            trapp.usr_key = optarg;
            printf("username and password: %s \n", trapp.usr_key);
            break;
        case 'r':
            trapp.ftp_url = optarg;
            printf("ftpserver url and port: %s \n", trapp.ftp_url);
            break;
        case 'x':
            printf("enable log\n");
            trapp.debug = 1;
            break;
        case 'D':
            trapp.dir_for_jsons = optarg;
            printf("read all files in this dir: %s\n", trapp.dir_for_jsons);
            break;
        case 'd':
            trapp.isdaemon = 1;
            break;
        default:
            printf("Usage: transit \n");
            printf("\t -r: ftpserver's ip or hostname, option: port\n");
            printf("\t -k: ftpserver's username and password\n");
            printf("\t     (default: anonymous:anonymous)\n");
            printf("\t -d: run in daemon\n");
            printf("\t -x: open log, see in /var/log/message, ");
            printf("depends on syslog.conf\n");
            printf("\t     (defalut: close)\n");
            printf("\t -D: all json fils keep in this dir, ");
            printf("include config file.\n");
            printf("\t     please see the sample in /appfs/etc/transit_dir/*\n");
            printf("\t     (defalut: /tmp/)\n");
            printf("\t     filename: CONFIG (!!this is config file)\n");
            printf("\t               WLRZ FJGJ JSTX XWRZ SJRZ\n");
            printf("\t               PTNR SGJZ CSZL CSZT SBZL\n");
            printf("\t               JSJZT SBGJ RZSJ SJTZ PNFJ\n");
            printf("Example:");
            printf("./transit -d -k username:password -r ip:port -D /tmp/");
            printf("\n");
            exit(1);
        }
    }

    if (trapp.isdaemon) {
        openlog(APP, LOG_PID, LOG_DAEMON);
        skeleton_daemon();
    }

    tr_log(LOG_INFO, "transt starting..\n");

    init_json_dir();
    tr_log(LOG_INFO, "json file is in %s\n", trapp.dir_for_jsons);

    json_parser_config(log_type[CONFIG]);
    json_parser_cszl(log_type[CSZL]);
    json_parser_sbzl(log_type[SBZL]);

    int i = 1;
    for (i; i <= 15; i ++) {
        init_send_json(i);
    }

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

    /* 创建线程 */
    pthread_t pth;
    pthread_create(&pth, NULL, threadFunc, NULL);

    /* Every 5 minutes */
    /* struct event *ev_timeout; */
    /* struct timeval tv; */
    /* ev_timeout = event_new(trapp.base, -1, EV_PERSIST | EV_TIMEOUT, */
    /*                        upload_json_cb, NULL); */
    /* evutil_timerclear(&tv); */
    /* tv.tv_sec = TIME_INTERVAL; */
    /* event_add(ev_timeout, &tv); */

    event_base_dispatch(trapp.base);

    return 0;
}
