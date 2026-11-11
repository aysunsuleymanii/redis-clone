//
// Created by Aysun Suleymanturk on 07/11/2026.
//



/*
 * 1. Create the socket
 * 2. Set the socket settings
 * 3. Bind the socket
 * 4. Wait for the connections
 * 5. Connect to the client socket
 * 6. Do something with socket data
 * 7. Close the socket
 * The server has a socket which listens incoming requests from the clients.
 * And for each client it creates a new socket with the accept() method.
 *
 *
 * const struct sockaddr *address: -> is the IP address and the port which we wait for requests.
 *
 *
 */

// which library is needed to create the socket?
#include <iostream>
#include <ostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

void do_something(int connfd) {
    char buf[1024];
    ssize_t n = read(connfd, buf, sizeof(buf));
    if (n > 0) {
        write(connfd, buf, n);
    }
}

int main() {
    // 1. create socket -> we can have many sockets open, this returns the index of the socket in file descriptor table.
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        std::cout << "socket creation failed" << std::endl;
    }

    // 2. write settings

    int opt = 1;
    // setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len);
    int res = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));


    // 3. bind -> means this socket should own this address

    sockaddr_in server_addr = {};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(1234);

    int bindingRes = bind(fd, (const sockaddr*)&server_addr, sizeof(server_addr));
    if (bindingRes != 0) {
        std::cout << "bind failed" << std::endl;
    }

    // 4. listen on connections
    int listenRes = listen(fd, SOMAXCONN);
    if (listenRes != 0) {
        std::cout << "listen failed" << std::endl;
    }

    // 5. loop: accept, handle, close

    while (true) {
        sockaddr_in client_addr{};
        socklen_t addrlen = sizeof(client_addr);
        int connfd = accept(fd, (sockaddr *)&client_addr, &addrlen);
        if (connfd < 0) {
            perror("accept()");
        }

        do_something(connfd);
        close(connfd);
    }



}