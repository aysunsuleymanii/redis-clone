//
// Created by Aysun Suleymanturk on 07/11/2026.
//

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

static void do_something(int connfd) {
    char buff[1024];

    while (true) {
        ssize_t n = read(connfd, buff, sizeof(buff));
        if (n == 0) break;
        if (n < 0) {
            std :: cout << "Reading failed" << std::endl;
        }

        std::string msg(buff, n);
        std::cout << "Client sent: " << msg << std::endl;
    }


    std::cout << "Client accepted" << std::endl;
}

int main() {
    // 1. create the socket
    int fd = socket(PF_INET, SOCK_STREAM, 0);

    // 2. set the options on the socket
    // setsockopt(int socket, int level, int option_name, const void *option_value, socklen_t option_len);

    int value = 1;
    int setSocketOptionsRes = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));


    // 3. Bind the address to the socket
    //  bind(int socket, const struct sockaddr *address, socklen_t address_len);

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(6379);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);


    int bindingRes = bind(fd, (struct sockaddr *) &addr, sizeof(addr));
    if (bindingRes < 0) {
        std::cout << "The binding of socket was not successful." << std::endl;
    }

    // 4. Connect the socket
    int listenRes = listen(fd, SOMAXCONN);
    if (listenRes < 0) {
        std::cout << "The server is listening!" << std::endl;
    }

    // 5. Wait for connections
    while (true) {
        struct sockaddr_in client_addr = {0};
        socklen_t client_len = sizeof(client_addr);
        int connfd = accept(fd, (struct sockaddr *)&client_addr, &client_len);
        if (connfd < 0) {
            std::cout << "The client cannot be accepted!" << std::endl;
        }
        do_something(connfd);
        close(connfd);
    }
}
