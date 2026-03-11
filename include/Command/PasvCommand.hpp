/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** PasvCommand
*/

#pragma once

#include "../ICommand.hpp"
#include "../Server.hpp"
#include <unistd.h>

namespace ftp {

    class PasvCommand: public ICommand {

        public:
            void execute(int fd, const std::string& args, Server& server) override;
    };

}
