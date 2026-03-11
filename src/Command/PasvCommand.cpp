/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** PasvCommand
*/

#include "Command/PasvCommand.hpp"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

namespace ftp {

    void PasvCommand::execute(int fd, const std::string& args, Server& server) {
        Client& client = server.getClient(fd);
        (void)args;

        if (!client.isAuthenticated()) {
            const std::string ErrorMsg = "530 Not logged in.\r\n";
            write(fd, ErrorMsg.c_str(), ErrorMsg.length());
            return;
        }

        const int dataFd = socket(AF_INET, SOCK_STREAM, 0);

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = 0;

        if (bind(dataFd, (sockaddr *)&addr, sizeof(addr)) < 0) {
            perror("bind");
            throw std::runtime_error("Bind failed");
        }

        listen(dataFd, 1);

        socklen_t len = sizeof(addr);
        getsockname(dataFd, (sockaddr *)&addr, &len);

        const int port = ntohs(addr.sin_port);

        client.setDataFd(dataFd);
        client.setPassive(true);

        const std::string response = "227 Entering Passive Mode (127,0,0,1," +
                                   std::to_string(port / 256) + "," +
                                   std::to_string(port % 256) + ").\r\n";
        write(fd, response.c_str(), response.length());
    }
}
