#ifndef _AD_H
#define _AD_H

/* 0- TCP LOCAL,1-TCP INET, 2-UDP INET*/
#define TYPE_OF_SOCKET 2

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>

int create_tcp_local(void);
int create_tcp_inet (void);
int create_udp_inet (void);

#endif

