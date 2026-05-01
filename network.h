#ifndef NETWORK_H
#define NETWORK_H

#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

typedef struct {
    int r1, c1, r2, c2;
} Move;

int start_server();
int accept_client(int server_fd);
int connect_to_server(const char* ip);
int send_move(int sock, Move move);
int receive_move(int sock, Move* move);

#endif
