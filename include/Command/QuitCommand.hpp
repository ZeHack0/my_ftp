/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** QuitCommand
*/

#pragma once

#include "../ICommand.hpp"
#include "../Server.hpp"
#include <unistd.h>

namespace ftp {

    class QuitCommand: public ICommand {

        public:
            void execute(int fd, const std::string& args, Server& server) override {
                (void)args;
                const std::string msg = "221 Goodbye.\r\n";
                write(fd, msg.c_str(), msg.length());
                server.disconnectionClient(fd);
            }
    };

}
