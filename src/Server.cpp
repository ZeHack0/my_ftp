/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** Server
*/

#include "Server.hpp"
#include "Command/UserCommand.hpp"
#include "Command/PassCommand.hpp"
#include "Command/CwdCommand.hpp"
#include "Command/CDupCommand.hpp"
#include "Command/QuitCommand.hpp"
#include "Command/DeleCommand.hpp"
#include "Command/PwdCommand.hpp"
#include "Command/PasvCommand.hpp"
#include "Command/PortCommand.hpp"
#include "Command/HelpCommand.hpp"
#include "Command/NoopCommand.hpp"
#include "Command/REtrCommand.hpp"
#include "Command/STorCommand.hpp"
#include "Command/ListCommand.hpp"
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

        std::string Input(buffer);
        size_t last = Input.find_last_not_of("\r\n");

        if (last == std::string::npos)
            return;
        Input = Input.substr(0, last + 1);

        size_t Separator = Input.find(' ');
        std::string _commandName = Input.substr(0, Separator);
        std::string _args = (Separator == std::string::npos) ?
            "" : Input.substr(Separator + 1);

        if (_commandServer.count(_commandName))
            _commandServer[_commandName]->execute(fd, _args, *this);
        else {
            std::string msg = "500 Unknown command.\r\n";
            write(fd, msg.c_str(), msg.length());
        }
    }

    void Server::InitCommands() {
        _commandServer["USER"] = std::make_unique<UserCommand>();
        _commandServer["PASS"] = std::make_unique<PassCommand>();
        _commandServer["CWD"] = std::make_unique<CwdCommand>();
        _commandServer["CDUP"] = std::make_unique<CDupCommand>();
        _commandServer["QUIT"] = std::make_unique<QuitCommand>();
        _commandServer["DELE"] = std::make_unique<DeleCommand>();
        _commandServer["DWD"] = std::make_unique<PwdCommand>();
        _commandServer["PASV"] = std::make_unique<PasvCommand>();
        _commandServer["PORT"] = std::make_unique<PortCommand>();
        _commandServer["HELP"] = std::make_unique<HelpCommand>();
        _commandServer["NOOP"] = std::make_unique<NoopCommand>();
        _commandServer["RETR"] = std::make_unique<REtrCommand>();
        _commandServer["STOR"] = std::make_unique<STorCommand>();
        _commandServer["LIST"] = std::make_unique<ListCommand>();
    }
}
