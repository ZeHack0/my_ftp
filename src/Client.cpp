/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** Client
*/

#include "Client.hpp"

namespace ftp{

    Client::Client(int fd, const std::string& homePath)
    {
        _fd = fd;
        _currentPath = homePath;
        UserIsSet = false;
        _isLoggedIn = false;
        (void)_dataFd;
        (void)_isPassive;
        (void)_dataAddr;
    }

    Client::~Client() = default;

}
