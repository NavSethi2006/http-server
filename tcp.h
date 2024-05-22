#pragma once

#include "stdio.h"
#include "arpa/inet.h"
#include "sys/socket.h"
#include "sys/types.h"
#include "assert.h"

#define PORT 443

typedef struct tcp
{
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

} tcp;

tcp setup_tcp();

void run_tcp(tcp tcp_server);