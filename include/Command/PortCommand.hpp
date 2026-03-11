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
            void execute(int fd, const std::string& args, Server& server) override;
    };

}
