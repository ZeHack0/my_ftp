/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** CwdCommand
*/

#pragma once

#include "../ICommand.hpp"
#include "../Server.hpp"
#include <unistd.h>

namespace ftp {

    class CwdCommand: public ICommand {

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
                    const std::string errorMsg = "550 Failed to change directory.\r\n";
                    write(fd, errorMsg.c_str(), errorMsg.length());
                    return;
                }

                if (chdir(args.c_str()) == 0) {
                    std::string oldPath = client.getCurrentPath();

                    client.setOldPath(oldPath);
                    client.setCurrentPath(args);
                    const std::string successMsg = "250 Requested file action okay, completed.\r\n";
                    write(fd, successMsg.c_str(), successMsg.length());
                } else {
                    const std::string errorMsg = "550 Failed to change directory.\r\n";
                    write(fd, errorMsg.c_str(), errorMsg.length());
                }
            };
    };

}
