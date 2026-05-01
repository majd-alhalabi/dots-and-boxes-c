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
#define BACKLOG 1

int start_server() {
    int server_fd;
    struct addrinfo hints, *res;
    int yes = 1;
    

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    

    int status = getaddrinfo(NULL, PORT, &hints, &res);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return -1;
    }
    

    server_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (server_fd < 0) {
        perror("socket failed");
        freeaddrinfo(res);
        return -1;
    }
    

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0) {
        perror("setsockopt failed");
        close(server_fd);
        freeaddrinfo(res);
        return -1;
    }
    

    if (bind(server_fd, res->ai_addr, res->ai_addrlen) < 0) {
        perror("bind failed");
        close(server_fd);
        freeaddrinfo(res);
        return -1;
    }
    
    freeaddrinfo(res);
    

    if (listen(server_fd, BACKLOG) < 0) {
        perror("listen failed");
        close(server_fd);
        return -1;
    }
    
    printf("Server listening on port %s...\n", PORT);
    
    return server_fd;
}

int accept_client(int server_fd) {
    int client_fd;
    struct sockaddr_storage their_addr;
    socklen_t addrlen = sizeof(their_addr);
    char client_ip[INET_ADDRSTRLEN];
    

    client_fd = accept(server_fd, (struct sockaddr*)&their_addr, &addrlen);
    if (client_fd < 0) {
        perror("accept failed");
        return -1;
    }
    

    struct sockaddr_in* addr_in = (struct sockaddr_in*)&their_addr;
    inet_ntop(AF_INET, &(addr_in->sin_addr), client_ip, INET_ADDRSTRLEN);
    printf("Client connected from %s\n", client_ip);
    
    return client_fd;
}

int send_move(int sock, Move move) {

    ssize_t bytes_written = write(sock, &move, sizeof(move));
    if (bytes_written < 0) {
        perror("write failed");
        return -1;
    }
    return bytes_written;
}

int receive_move(int sock, Move* move) {

    ssize_t bytes_read = read(sock, move, sizeof(*move));
    if (bytes_read < 0) {
        perror("read failed");
        return -1;
    }
    return bytes_read;
}

