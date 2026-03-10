/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** PwdCommand
*/

#pragma once

#include "../ICommand.hpp"
#include "../Server.hpp"
#include <unistd.h>

namespace ftp {

    class PwdCommand: public ICommand {

        public:
            void execute(int fd, const std::string& args, Server& server) override
            {
                (void)args;
                (void)server;
                const std::string msg = "PWD command in Progress.\r\n";
                write(fd, msg.c_str(), msg.length());
            }
    };

}
