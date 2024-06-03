#pragma once

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <assert.h>
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <regex.h>
#include "tools.h"

#define BUFFER_SIZE 1024

#define PORT 80

typedef struct tcp
{
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    int *clientfd;
    pthread_t server_thread;

    void (*customConnection)(void*);

} tcp;

tcp setup_tcp();

void run_tcp(tcp tcp_server, void(*sockfdd));