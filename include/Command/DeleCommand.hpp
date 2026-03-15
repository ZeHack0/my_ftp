/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** DeleCommand
*/

#pragma once

#include "../ICommand.hpp"
#include "../Server.hpp"
#include <unistd.h>

namespace ftp {

    class DeleCommand: public ICommand {

        public:
            void execute(int fd, const std::string& args, Server& server) override
            {
                Client& client = server.getClient(fd);

                if (!client.isAuthenticated()) {
                    const std::string ErrorMsg = "530 Not logged in.\r\n";
                    write(fd, ErrorMsg.c_str(), ErrorMsg.length());
                    return;
                }

                if (args.empty()) {
                    const std::string errorMsg = "550 Permission denied.\r\n";
                    write(fd, errorMsg.c_str(), errorMsg.length());
                    return;
                }

                if (unlink(args.c_str()) == 0) {
                    const std::string successMsg = "250 Requested file action okay, completed.\r\n";
                    write(fd, successMsg.c_str(), successMsg.length());
                } else {
                    const std::string errorMsg = "550 Permission denied (file not found or access denied).\r\n";
                    write(fd, errorMsg.c_str(), errorMsg.length());
                }
            }
    };

}
