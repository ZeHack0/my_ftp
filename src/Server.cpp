/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** Server
*/

#include "Server.hpp"

namespace ftp {

    Server::Server(const std::string& port, const std::string& path) {
        if (CheckPorIsValid(port) == false)
            throw std::runtime_error("Bad Port");
        _port = std::stoi(port);
        _path = path;
        init();
    }

    Server::~Server() = default;

    void Server::init() {
        _socket = socket(AF_INET, SOCK_STREAM, 0);
        if (_socket == -1) {
            perror("socket");
            throw std::runtime_error("Socket creation failed");
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
        pollfd server_pfd;
        server_pfd.fd = _socket;
        server_pfd.events = POLLIN;
        _poll_fds.push_back(server_pfd);

        std::cout << "Waiting for connections..." << std::endl;

        while (true) {
            if (poll(_poll_fds.data(), _poll_fds.size(), -1) == -1) {
                perror("poll");
                break;
            }

            for (size_t i = 0; i < _poll_fds.size(); i++) {
                if (_poll_fds[i].revents & POLLIN) {
                    if (_poll_fds[i].fd == _socket) {
                        std::cout << "handleNewConnection();" << std::endl;
                    } else {
                        std::cout << "handleClientActivity(_poll_fds[i].fd);" << std::endl;
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
}
