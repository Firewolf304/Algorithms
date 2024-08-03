#include <iostream>
#include <liburing/io_service.hpp>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <print>
#include <format>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::print ("Using: {} <text> <port> <delay>\n", argv[0]);
        return 1;
    }

    std::string text{argv[1]};
    int port = atoi(argv[2]);
    int delay = atoi(argv[3]);
    std::string server_ip{"127.0.0.1"};

    while (1) {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1) {
            perror("Socket creation failed");
            return 1;
        }
        int optval = 1;
        socklen_t optlen = sizeof(optval);
        if (setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) == -1) {
            perror("setsockopt(SO_KEEPALIVE) failed");
            close(sock);
            return 1;
        }

        struct sockaddr_in server_address;
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(port);
        server_address.sin_addr.s_addr = inet_addr(server_ip.c_str());

        if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
            perror("Connection failed");
            close(sock);
            return 1;
        }

        if (send(sock, text.c_str(), text.size(), 0) == -1) {
            perror("Send failed");
        }

        close(sock);
        sleep(delay);
    }

    return 0;
}