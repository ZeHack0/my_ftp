/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** PassCommand
*/

#pragma once

#include "../ICommand.hpp"
#include "../Server.hpp"

namespace ftp {

    class PassCommand: public ICommand {

        public:
            void execute(int fd, const std::string& args, Server& server) override;
        private:
            static bool userExists(const std::string& user, Server& server) ;
            static bool validPass(const std::string& password, Server& server);
    };

}
