#ifndef _TRANSIT_H
#define _TRANSIT_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <syslog.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/socket.h>

#include "event.h"
#include "curl_ftp.h"
#include "parson/parson.h"

extern struct tr_app trapp;
extern const char *log_type[];
extern void skeleton_daemon();
extern void tr_log(int level, const char *fmt, ...);
extern void printHexBuffer(void *buf, unsigned long len);
extern void udpserver_init(int *sock, unsigned short port);

#define CONFIG 0
#define WLRZ   1
#define FJGJ   2
#define JSTX   3
#define XWRZ   4
#define SJRZ   5
#define PTNR   6
#define SGJZ   7
#define CSZL   8
#define CSZT   9
#define SBZL   10
#define JSJZT  11
#define SBGJ   12
#define RZSJ   13
#define SJTZ   14
#define PNFJ   15

#ifndef MAC_FMT
#define MAC_FMT "%02X-%02X-%02X-%02X-%02X-%02X"
#endif

#ifndef MAC_FMT_L
#define MAC_FMT_L "%02X%02X%02X%02X%02X%02X"
#endif


#ifndef MAC_ARG
#define MAC_ARG(x)                              \
        ((unsigned char*)(x))[0],               \
        ((unsigned char*)(x))[1],               \
        ((unsigned char*)(x))[2],               \
        ((unsigned char*)(x))[3],               \
        ((unsigned char*)(x))[4],               \
        ((unsigned char*)(x))[5]
#endif

struct tr_app {
    struct event_base *base;
    struct event *ev_udp;
    int sock;
    int debug;
    int isdaemon;
    int count_wlrz;
    char *dir_for_jsons;
    char *usr_key;
    char *ftp_url;
    struct {
        char dataAcqSysType[3];
        char dataGenIden[6];
        char vendorOrgCode[9];
        char company_id[32];
    } cfg;
};

#define DW_AUDIT_HEADER     (0x7C83)
#define DW_AUDIT_PDU_HEADER (0x7C83)


struct locator_mdu_pdu_head_dw_audit {
    unsigned short header;
    unsigned short requestId;
    unsigned char  code;
    unsigned char  subCode;
    unsigned char  reserved[2];
    unsigned int   dataLength;
}__attribute__((packed));

struct locator_mdu_num_dw_audit {
    unsigned short MDUNumber;
    unsigned char  reserved[2];
}__attribute__((packed));

struct locator_mdu_payload_dw_audit {
    unsigned short header;
    unsigned short requestId;
    unsigned char  code;
    unsigned char  subCode;
    unsigned int   dataLength;
    unsigned char  apMac[6];
    unsigned short vendorId;
    unsigned char  reserved1[2];
    unsigned char  bssid[6];
    unsigned char  radioType;
    unsigned char  channel;
    unsigned char  isAssoc;
    unsigned char  reserved2;
    unsigned int   timestamp;
    unsigned char  reserved3[2];
    unsigned char  muType;
    unsigned char  reserved4;
    char  AbsRssi;
    unsigned char  reserved5;
    unsigned char  noiseFloor;
    unsigned char  reserved6[3];
    unsigned char  dataRate;
    unsigned char  mpduFlags;
    unsigned char  muMac[6];
    unsigned short frameCtrl;
    unsigned short seqCtrl;
    unsigned char  reserved7[2];
    unsigned char  crc;
    unsigned char  encryptType;
    unsigned char  reserved8[2];
    unsigned char  ssid[33];
} __attribute__((packed));

struct tr_feature_collection {
    char N01_mac[17];
    char N02_type[4];
    char N03_start_time[20];
    char N04_end_time[20];
    char N05_power[8];
    char N06_bssid[17];
    char N07_essid[256];
    char N08_history_essid[1024];
    char N09_model[128];
    char N10_os_version[50];
    char N11_imei[20];
    char N12_imsi[20];
    char N13_station[20];
    char N14_xpoint[30];
    char N15_ypoint[30];
    char N16_phone[20];
    char N17_devmac[17];
    char N18_devicenum[21];
    char N19_servicecode[14];
    char N20_protocol_type[14];
    char N21_account[64];
    char N22_flag[2];
    char N23_url[1024];
    char N24_company[32];
    char N25_ap_channel[2];
    char N26_ap_encrytype[2];
    char N27_consult_xpoint[8];
    char N28_consult_ypoint[8];
} __attribute__((packed));

struct tr_service_info {
    char N01_service_code[14];
    char N02_service_name[256];
    char N03_address[256];
    char N04_zip[6];
    char N05_business_nature[1];
    char N06_principal[50];
    char N07_principal_tel[20];
    char N08_info_man[50];
    char N09_info_man_tel[20];
    char N10_info_man_email[50];
    char N11_producer_code[6];
    char N12_status[4];
    char N13_ending_number[4];
    char N14_server_number[4];
    char N15_exit_ip[128];
    char N16_auth_account[64];
    char N17_net_type[2];
    char N18_practitioner_number[3];
    char N19_net_monitor_department[20];
    char N20_net_monitor_man[50];
    char N21_net_monitor_man_tel[30];
    char N22_remark[256]; /*?*/
    char N23_service_type[4];
    char N24_province_code[6];
    char N25_city_code[6];
    char N26_area_code[6];
    char N27_city_type[6];
    char N28_police_code[8];
    char N29_mail_account[50];
    char N30_mobile_account[50];
    char N31_xpoint[20];
    char N32_ypoint[20];
    char N33_gis_xpoint[20];
    char N34_gis_ypoint[20];
    char N35_terminal_factory_orgcode[9];
    char N36_org_code[9];
    char N37_ip_type[2];
    char N38_band_width[11];
    char N39_net_lan[11];
    char N40_net_lan_term1nal[11];
    char N41_is_SAFE[2];
    char N42_wifi_terminal[11];
    char N43_principal_cert_type[7];
    char N44_principal_cert_code[50];
    char N45_person_name[50];
    char N46_person_tel[20];
    char N47_person_qq[20];
    char N48_infor_man_qq[20];
    char N49_start_time[5];
    char N50_end_time[5];
    char N51_create_time[20];
    char N52_cap_type[2];
} __attribute__((packed));

struct tr_equipment_info {
    char N01_equipment_num[21];
    char N02_equipment_name[128];
    char N03_mac[17];
    char N04_ip[11];
    char N05_security_factory_orgcode[9];
    char N06_vendor_name[255];
    char N07_verdor_num[255];
    char N08_service_code[6];
    char N09_province_code[6];
    char N10_city_code[6];
    char N11_area_code[6];
    char N12_install_date[16];
    char N13_install_point[255];
    char N14_equipment_type[2];
    char N15_longitude[10];
    char N16_latitude[10];
    char N17_subway_station[128];
    char N18_subway_line_info[256];
    char N19_subway_vehicle_info[256];
    char N20_subway_compartment_num[256];
    char N21_car_code[64];
    char N22_upload_time_interval[11];
    char N23_collection_radius[4];
    char N24_create_time[16];
    char N25_creater[50];
    char N26_last_connect_time[16];
    char N27_remark[255];
    char N28_wda_version[20];
    char N29_fireware_version[50];
} __attribute__((packed));

#endif
