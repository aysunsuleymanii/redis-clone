//
// Created by Aysun Suleymanturk on 07/11/2026.
//


#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <iostream>
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

    std:: string line;

    while (true) {
        std:: cout << "> ";
        if (!std::getline(std::cin, line)) break;
        if (line == "quit") break;

        line += "\n";
        write(fd, line.data(), line.size());

        char buff[1024];
        ssize_t n = read(fd, buff, sizeof(buff));
        if (n <= 0) {
            std::cout << "Server closed the connection!" << std::endl;
            break;
        }
        std::cout << std::string(buff, n);
    }

    close(fd);

    return 0;
}