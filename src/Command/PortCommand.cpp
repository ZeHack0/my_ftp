/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** PortCommand
*/

#include "Command/PortCommand.hpp"
#include <sstream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>


namespace ftp {

    void PortCommand::execute(int fd, const std::string& args, Server& server) {
        Client& client = server.getClient(fd);

        if (!client.isAuthenticated()) {
            const std::string msg = "530 Not logged in.\r\n";
            write(fd, msg.c_str(), msg.length());
            return;
        }

        std::vector<std::string> tokens;
        std::stringstream ss(args);
        std::string item;
        while (std::getline(ss, item, ',')) tokens.push_back(item);

        if (tokens.size() != 6) {
            const std::string msg = "501 Syntax error in parameters.\r\n";
            write(fd, msg.c_str(), msg.length());
            return;
        }

        std::string ip = tokens[0] + "." + tokens[1] + "." + tokens[2] + "." + tokens[3];
        int port = std::stoi(tokens[4]) * 256 + std::stoi(tokens[5]);

        sockaddr_in dataAddr{};
        dataAddr.sin_family = AF_INET;
        dataAddr.sin_port = htons(port);
        inet_pton(AF_INET, ip.c_str(), &dataAddr.sin_addr);

        client.setDataAddr(dataAddr);
        client.setPassive(false);

        const std::string msg = "200 PORT command successful.\r\n";
        write(fd, msg.c_str(), msg.length());
    }
}