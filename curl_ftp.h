#ifndef _CURL_FTP_H
#define _CURL_FTP_H

/* FTP OPERATION CODE */
typedef enum FTP_STATE {
    FTP_UPLOAD_SUCCESS,
    FTP_UPLOAD_FAILED,
    FTP_DOWNLOAD_SUCCESS,
    FTP_DOWNLOAD_FAILED,
}FTP_STATE;

typedef struct FTP_OPT {
    char url[512];              /* url of ftp */
    char *user_key;             /* username:password */
    char *file;                 /* filepath */
}FTP_OPT;

/* upload file to ftp server */
extern FTP_STATE ftp_upload(const FTP_OPT ftp_option);

/* download file from ftp server */
extern FTP_STATE ftp_download(const FTP_OPT ftp_option);

extern FTP_STATE ftp_create_dirs(const FTP_OPT ftp_option);

#endif
