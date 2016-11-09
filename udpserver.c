#include "transit.h"

void printHexBuffer(void *buf, unsigned long len)
{
    unsigned long i;
    unsigned char *bytes = (unsigned char *)buf;
    unsigned char buffer[1024] = {0};
    unsigned char *tmp;
    tmp = buffer;
    if (NULL == buf || 0 == len)
    {
        return;
    }
    tr_log(LOG_INFO, "len = %d", len);

    for (i = 0; i < len; i ++)
    {
        sprintf(tmp, "%02x ", bytes[i]);
        tmp += 3;
        if((i + 1) % 8 == 0)
        {
            sprintf(tmp, "\n");
            tmp += 1;
        }
    }
    tr_log(LOG_INFO, "\n%s", buffer);
}


void udpserver_init(int *sock, unsigned short port)
{
    *sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(*sock < 0) {
        tr_log(LOG_ERR, "cannot open udp socket!");
        return;
    }
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(*sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0) {
        tr_log(LOG_ERR, "cannot open udp socket!");
    }
}

