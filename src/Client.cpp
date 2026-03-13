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
        UserIsSet = false;
        _isLoggedIn = false;
        _dataFd = -1;
        _isPassive = false;
        _ipAddress = -1;
        _portClient = -1;
        memset(&_dataAddr, 0, sizeof(_dataAddr));

        if (homePath == ".") {
            _currentPath = '/';
            _oldPath = '/';
        } else {
            _currentPath = homePath;
            _oldPath = homePath;
        }
    }

    Client::~Client() = default;

}
