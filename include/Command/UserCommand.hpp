/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** UserCommand
*/

#pragma once

#include "../ICommand.hpp"
#include "../Server.hpp"
#include <unistd.h>

namespace ftp {

    class UserCommand: public ICommand {

        public:
            void execute(int fd, const std::string& args, Server& server) override {

                if (args.empty()) {
                    const std::string msg = "501 Syntax error in parameters or arguments.\r\n";
                    write(fd, msg.c_str(), msg.length());
                    return;
                }

                Client& client = server.getClient(fd);

                client.UserIsSet = true;
                client.username = args;
                const std::string msg = "331 Username ok, need password.\r\n";
                write(fd, msg.c_str(), msg.length());
            }
    };

}
