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

    if(listen(sockfd, 5) < 0) perror("error whilst listening");


    return tcp_server;

}

void run_tcp(tcp tcp_server, void(*sockfdd) ) {
    
    tcp_server.clientfd = malloc(sizeof(int));

    client_len = sizeof(tcp_server.client_address);
    printf("waiting for client\n");
    while(1) {
        
        tcp_server.clientfd = ((int*)accept(sockfd, (struct sockaddr*)&tcp_server.client_address, &client_len));
        assert(client);

        pthread_t thread;
        pthread_create(&thread,  NULL,sockfdd, &client);

    }

        
}

