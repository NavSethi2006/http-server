#pragma once

#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <magic.h>
#include <assert.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "tcp.h"


void build_http_response(const char* file_name, const char* file_ext,char* response, size_t response_len);

void *http_connection(void*arg);