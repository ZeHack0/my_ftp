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

namespace ftp {

    class Server {

        public:
            Server(int port, const std::string& path);
            ~Server();

            void run();

        private:
            int _master_socket;
            int _port;
            std::string _home_path;
            std::map<int, Client> _clients;
            std::vector<struct pollfd> _poll_fds;

            void init();
            void handleNewConnection();
            void handleClientActivity(int fd);
    };

}
