/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** Server
*/

#pragma once

#include "Client.hpp"
#include <iostream>
#include <map>
#include <poll.h>
#include <vector>

namespace ftp {

    class Server {

        public:
            Server(const std::string& port, const std::string& path);
            ~Server();

            void run();

        private:
            int _socket;
            int _port;
            std::string _path;
            std::map<int, Client> _clients;
            std::vector<struct pollfd> _poll_fds;

            void init();
            void handleNewConnection();
            void handleClientActivity(int fd);
            bool CheckPorIsValid(const std::string &port);
    };

}
