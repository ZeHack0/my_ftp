/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** PortCommand
*/

#pragma once

#include "../ICommand.hpp"
#include "../Server.hpp"
#include <unistd.h>

namespace ftp {

    class PortCommand: public ICommand {

        public:
            void execute(int fd, const std::string& args, Server& server) override
            {
                Client& client = server.getClient(fd);

                if (!client.isAuthenticated()) {
                    const std::string ErrorMsg = "530 Not logged in.\r\n";
                    write(fd, ErrorMsg.c_str(), ErrorMsg.length());
                    return;
                }

                (void)args;

                const std::string msg = "PORT command in Progress.\r\n";
                write(fd, msg.c_str(), msg.length());
            }
    };

}
