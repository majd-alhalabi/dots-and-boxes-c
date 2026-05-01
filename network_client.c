#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include "network.h"

#define PORT "4444"

int connect_to_server(const char* ip) {
    int sockfd;
    struct addrinfo hints, *res;
    

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    
    int status = getaddrinfo(ip, PORT, &hints, &res);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return -1;
    }
    

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0) {
        perror("socket failed");
        freeaddrinfo(res);
        return -1;
    }
    

    if (connect(sockfd, res->ai_addr, res->ai_addrlen) < 0) {
        perror("connect failed");
        close(sockfd);
        freeaddrinfo(res);
        return -1;
    }
    
    freeaddrinfo(res);
    printf("Connected to server at %s:%s\n", ip, PORT);
    
    return sockfd;
}
