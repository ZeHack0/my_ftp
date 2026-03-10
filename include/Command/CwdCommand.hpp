/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** CwdCommand
*/

#pragma once

#include "../ICommand.hpp"
#include "../Server.hpp"
#include <unistd.h>

namespace ftp {

    class CwdCommand: public ICommand {

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

                const std::string msg = "250 Requested file action okay, completed.\r\n";
                write(fd, msg.c_str(), msg.length());
            };
    };

}
