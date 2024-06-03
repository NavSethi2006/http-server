#include "http.h"


void *http_connection(void *arg) {
    int clientfd = *((int*)arg);
    char *buffer  = (char *) malloc(BUFFER_SIZE * sizeof(char));

    // recieve request data and store it into buffer

    ssize_t bytes_recived = recv(clientfd, buffer, BUFFER_SIZE, 0);
    if( bytes_recived > 0) {
        // check if request is GET

        regex_t regex;
        regcomp(&regex, "^GET /([^ ]*) HTTPS/1", REG_EXTENDED);
        regmatch_t regmatch[2];

        if(regexec(&regex, buffer, 2, regmatch, 0) == 0) {
            buffer[regmatch[1].rm_eo] = '\0';
            const char* url_encoded_file_name = buffer + regmatch[1].rm_eo;
            char* file_name = url_decode(url_encoded_file_name);

            char file_ext[32];
            strcpy(file_ext, get_file_extension(file_name));

            char* response = (char*) malloc(BUFFER_SIZE * 2 * sizeof(char));
            size_t response_length;
            build_http_response(file_name, file_ext, response, response_length);

            send(clientfd, response, response_length, 0);

            free(response);
            free(file_name);

        }
        regfree(&regex);
    }
    free(arg);
    free(buffer);
    return NULL;
}


void build_http_response(const char* file_name, const char* file_ext,char* response, size_t response_len ) {

    const char* mime_type = get_mime_type(file_ext);
    char* header = (char*) malloc(BUFFER_SIZE * sizeof(char));

    snprintf(header, BUFFER_SIZE, 
        "HTTP/1.1 404 NOT FOUND\r\n"
        "CONTENT-TYPE: text/plain\r\n"
        "\r\n",
        mime_type);

    int file_fd = open(file_name, O_RDONLY);

    if(file_fd == -1) {
        snprintf(response, BUFFER_SIZE, 
        "HTTP/1.1 404 NOT FOUND\r\n"
        "CONTENT-TYPE: text/plain\r\n"
        "\r\n"
        "Not found");
        response_len = strlen(response);
        return;
    }

    struct stat file_stat;
    fstat(file_fd, &file_stat);
    off_t file_size = file_stat.st_size;

    response_len = 0;
    memcpy(response, header, strlen(header));
    response_len = strlen(response);

    ssize_t bytes_read;
    while((bytes_read = recv(file_fd, response + response_len, BUFFER_SIZE-response_len,0)) > 0 ) {
        response_len += bytes_read;
    }

    free(header);
    close(file_fd);

}
