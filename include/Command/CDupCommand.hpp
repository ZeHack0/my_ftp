/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** CDupCommand
*/

#pragma once

#include "../ICommand.hpp"
#include "../Server.hpp"
#include <unistd.h>

namespace ftp {

    class CDupCommand: public ICommand {

        public:
            void execute(int fd, const std::string& args, Server& server) override
            {
                (void)server;
                const std::string msg = "CDUP command in Progress.\r\n";
                write(fd, msg.c_str(), msg.length());
                const std::string msg_args = args;
                write(fd, msg_args.c_str(), msg_args.length());
            }
    };

}
