/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** HelpCommand
*/

#pragma once

#include "../ICommand.hpp"
#include "../Server.hpp"
#include <unistd.h>

namespace ftp {

    class HelpCommand: public ICommand {

        public:
            void execute(int fd, const std::string& args, Server& server) override;

        private:
            static void AccurateHelp(int fd, const std::string &arg);
    };

}
