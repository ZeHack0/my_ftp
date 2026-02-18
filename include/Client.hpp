/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** Client
*/

#pragma once

#include <iostream>
#include <arpa/inet.h>

namespace ftp {

    class Client {

        public:

            Client(int fd, const std::string& homePath);
            ~Client();

            int getFd() const { return _fd; }
            bool isAuthenticated() const { return _isLoggedIn; }
            void setAuthenticated(bool state) { _isLoggedIn = state; }

        private:
            int _fd;
            bool _isLoggedIn;
            int _dataFd;
            bool _isPassive;
            struct sockaddr_in _dataAddr;
            std::string _user;
            std::string _currentPath;
    };

}
