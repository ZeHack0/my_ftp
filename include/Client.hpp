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

            [[nodiscard]] int getFd() const { return _fd; }
            [[nodiscard]] bool isAuthenticated() const { return _isLoggedIn; }
            void setAuthenticated(bool state) { _isLoggedIn = state; }
            bool UserIsSet;
            std::string username;
            void setDataAddr(const sockaddr_in& addr) { _dataAddr = addr; }
            void setPassive(bool status) { _isPassive = status; }
            void setDataFd(int fd) { _dataFd = fd; }
            [[nodiscard]] int getDataFd() const { return _dataFd; }
            [[nodiscard]] bool isPassive() const { return _isPassive; }
            [[nodiscard]] sockaddr_in getDataAddr() const { return _dataAddr; }

        private:
            int _fd;
            bool _isLoggedIn;
            int _dataFd;
            bool _isPassive;
            sockaddr_in _dataAddr{};
            std::string _user;
            std::string _currentPath;
    };

}
