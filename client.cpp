//
// Created by Aysun Suleymanturk on 07/11/2026.
//


#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>


int main() {
    int fd = socket(PF_INET, SOCK_STREAM, 0);


    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(6379);                       // the server's port
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);     // 127.0.0.1, this machine

    int rc = connect(fd, (struct sockaddr *)&addr, sizeof(addr));

    char message[6] = "Hello";
    write(fd, message, strlen(message));

    close(fd);

    return 0;
}