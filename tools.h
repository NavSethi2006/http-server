#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 


char *url_decode(const char *src);

const char *get_file_extension(const char* file_name);

const char *get_mime_type(const char* file_ext);
