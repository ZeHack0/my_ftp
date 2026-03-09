/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** ServerCommand
*/

#pragma once
#include <iostream>

namespace ftp {

    class Server;

    class ICommand {

        public:
            virtual ~ICommand() = default;
            virtual void execute(int fd, const std::string& args, Server& server) = 0;
    };

}
