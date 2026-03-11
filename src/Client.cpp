/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** Client
*/

#include "Client.hpp"
#include <cstring>

namespace ftp{

    Client::Client(int fd, const std::string& homePath)
    {
        _fd = fd;
        _currentPath = homePath;
        UserIsSet = false;
        _isLoggedIn = false;
        _dataFd = -1;
        _isPassive = false;
        memset(&_dataAddr, 0, sizeof(_dataAddr));
    }

    Client::~Client() = default;

}
