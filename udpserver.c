#include "transit.h"

void ad_pkt_udp_init(int *sock, unsigned short *port)
{
    *sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(*sock < 0) {
        tr_log(LOG_ERR, "cannot open udp socket!");
        return;
    }
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(*port);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(*sock, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0) {
        tr_log(LOG_ERR, "cannot open udp socket!");
    }
}

