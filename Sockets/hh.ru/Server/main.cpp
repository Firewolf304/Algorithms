#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <memory>
#include <cstring>
#include <fcntl.h>
#include <liburing/io_service.hpp>
#include <print>

std::shared_ptr<uio::io_service> service;
ssize_t port = 8080;
std::string ipAddr = "127.0.0.1";
int main(int args, char* argv[]) {
    if(args > 1) {
        port = std::atoi(argv[1]);
    }
    sockaddr_in servAddr{};
    fd_set readfds;
    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr  = inet_addr(ipAddr.c_str());
    servAddr.sin_port = htons(port);
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (fcntl(sock, F_SETFL, fcntl(sock, F_GETFL) | O_NONBLOCK) < 0) {
        throw std::runtime_error("Cant unlock socket");
    }
    if(bind(sock, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0)
    {
        throw std::runtime_error("Cant bind socket");
    }
    FD_ZERO(&readfds);
    FD_SET(sock, &readfds);
    listen(sock, 1000);
    std::print( "Server started\n");
    service = std::make_shared<uio::io_service>(10000);

    service->run([&](std::shared_ptr<uio::io_service> & service, int socket) noexcept -> uio::task<void> {
                     while (true) {
                         int clientfd = 0;
                         while ((clientfd = co_await service->accept(socket, nullptr, nullptr)) <= 0);
                         if(clientfd > socket) {
                             auto func_async = [&](int client) -> uio::task<void> {
                                 fcntl(client, F_SETFL, fcntl(client, F_GETFL) | O_NONBLOCK);
                                 std::vector<char> buf(2048);
                                 int i = co_await service->recv(client, buf.data(), 2048, MSG_NOSIGNAL);
                                 if (i <= 0) co_return ;
                                 std::string message (buf.data(), i);
                                 std::print("[{}] {}\n", std::chrono::system_clock::now(), message);
                             } (clientfd);
                         }
                         co_await service->shutdown(clientfd, SHUT_RDWR);
                         co_await service->close(clientfd);

                     }
                 }(service, std::move(sock))
    );
    return 0;
}
