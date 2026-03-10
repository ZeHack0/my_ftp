/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** Server
*/

#pragma once

#include "Client.hpp"
#include "ICommand.hpp"
#include <iostream>
#include <map>
#include <poll.h>
#include <vector>
#include <memory>

namespace ftp {

    class Server {
        friend class PassCommand;

        struct FtpAccount {
            std::string _username;
            std::string _password;
        };

        public:
            Server(const std::string& port, const std::string& path);
            ~Server();

            void run();
            void disconnectionClient(int fd);
            Client& getClient(int fd);

        private:
            int _socket{};
            int _port;
            std::string _path;
            std::map<int, Client> _clients;
            std::vector<pollfd> _poll_fds;
            std::map<std::string, std::unique_ptr<ICommand>> _commandServer;

            void init();
            void handleNewConnection();
            void handleClientActivity(int fd);
            static bool CheckPorIsValid(const std::string &port);
            void InitCommands();
            std::vector<FtpAccount> _validUser;
    };

}
