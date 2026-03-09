/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** Server
*/

#include "Server.hpp"
#include "Command/QuitCommand.hpp"
#include <unistd.h>

namespace ftp {

    Server::Server(const std::string& port, const std::string& path) {
        if (CheckPorIsValid(port) == false)
            throw std::runtime_error("Bad Port");
        _port = std::stoi(port);
        _path = path;
        InitCommands();
        init();
    }

    Server::~Server() = default;

    void Server::init() {
        _socket = socket(AF_INET, SOCK_STREAM, 0);
        if (_socket == -1) {
            perror("socket");
            throw std::runtime_error("Socket creation failed");
        }

        int _opt = 1;
        if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &_opt, sizeof(_opt)) < 0) {
            perror("setsockopt");
            throw std::runtime_error("Set_Socket_Option failed");
        }

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(_port);

        if (bind(_socket, (sockaddr*)&addr, sizeof(addr)) < 0) {
            perror("bind");
            throw std::runtime_error("Bind failed");
        }

        if (listen(_socket, 3) < 0) {
            perror("listen");
            throw std::runtime_error("Listen failed");
        }
    }

    void Server::run() {
        pollfd server_pfd{};
        server_pfd.fd = _socket;
        server_pfd.events = POLLIN;
        _poll_fds.push_back(server_pfd);

        std::cout << "Waiting for connections..." << std::endl;

        while (true) {
            if (poll(_poll_fds.data(), _poll_fds.size(), -1) == -1) {
                perror("poll");
                break;
            }

            for (auto & _poll_fd : _poll_fds) {
                if (_poll_fd.revents & POLLIN) {
                    if (_poll_fd.fd == _socket) {
                        handleNewConnection();
                    } else {
                        handleClientActivity(_poll_fd.fd);
                    }
                }
            }
        }
    }

    bool Server::CheckPorIsValid(const std::string& port) {
        if (port.empty())
            return false;
        for (char c : port)
            if (!std::isdigit(static_cast<unsigned char>(c)))
                return false;
        return true;
    }

    void Server::handleNewConnection() {
        sockaddr_in _client_addr{};
        socklen_t _addr_size = sizeof(_client_addr);

        int _fd = accept(_socket, (sockaddr*)&_client_addr, &_addr_size);
        if (_fd == -1)
            return;

        pollfd client_pfd{};
        client_pfd.fd = _fd;
        client_pfd.events = POLLIN;
        _poll_fds.push_back(client_pfd);

        std::string welcome = "220 Server ready\r\n";
        write(_fd, welcome.c_str(), welcome.length());
    }

    void Server::disconnectionClient(int fd) {
        std::cout << "Client disconnected: " << fd << std::endl;

        close(fd);
        _clients.erase(fd);
        for (auto it = _poll_fds.begin(); it != _poll_fds.end(); ++it)
            if (it->fd == fd) {
                _poll_fds.erase(it);
                break;
            }
    }

    void Server::handleClientActivity(int fd)
    {
        char buffer[1024] = {0};
        std::size_t bytes = read(fd, buffer, sizeof(buffer) - 1);

        if (bytes <= 0) {
            this->disconnectionClient(fd);
            return;
        }

        std::string _Input(buffer);
        size_t last = _Input.find_last_not_of("\r\n");

        if (last == std::string::npos)
            return;
        _Input = _Input.substr(0, last + 1);

        size_t _Separator = _Input.find(' ');
        std::string _commandName = _Input.substr(0, _Separator);
        std::string _args = (_Separator == std::string::npos) ?
            "" : _Input.substr(_Separator + 1);

        if (_commandServer.count(_commandName))
            _commandServer[_commandName]->execute(fd, _args, *this);
        else {
            std::string msg = "500 Unknown command.\r\n";
            write(fd, msg.c_str(), msg.length());
        }
    }

    void Server::InitCommands() {
        _commandServer["QUIT"] = std::make_unique<QuitCommand>();
    }
}
