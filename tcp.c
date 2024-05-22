#include "tcp.h"

int sockfd;
int client;
int client_len;
char response[1024];

tcp setup_tcp() {

    tcp tcp_server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd);

    tcp_server.server_address.sin_family = AF_INET;
    tcp_server.server_address.sin_port = htons(PORT);
    tcp_server.server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    int bindsock = bind(sockfd, (struct sockaddr*)&tcp_server.server_address, sizeof(sockfd));
    assert(bindsock);

    int listensock = listen(sockfd, 10);
    assert(listensock);

    return tcp_server;

}

void run_tcp(tcp tcp_server) {
    
    client = accept(sockfd, (struct sockaddr*)&tcp_server.client_address, &client_len);
    assert(client);
    while(1) {
        recv(sockfd, response, 1024, 0);
        send(sockfd, response, 1024, 0);
    }

        
}