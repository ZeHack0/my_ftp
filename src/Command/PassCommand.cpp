/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** PassCommand
*/

#include "Command/PassCommand.hpp"
#include "Command/UserCommand.hpp"

namespace ftp {
    void PassCommand::execute(int fd, const std::string& args, Server& server){
        Client& client = server.getClient(fd);

        if (client.UserIsSet == false) {
            const std::string msg = "503 Bad sequence of commands.\r\n";
            write(fd, msg.c_str(), msg.length());
            return;
        }

        if (userExists(client.username, server) == false) {
            client.UserIsSet = false;
            const std::string msg = "530 Login incorrect.\r\n";
            write(fd, msg.c_str(), msg.length());
            return;
        }

        if (validPass(args, server) == true) {
            client.setAuthenticated(true);
            const std::string msg = "230 User logged in, proceed.\r\n";
            write(fd, msg.c_str(), msg.length());
            return;
        }

        client.UserIsSet = false;
        const std::string msg = "530 Login incorrect.\r\n";
        write(fd, msg.c_str(), msg.length());
    }

    bool PassCommand::userExists(const std::string& user, Server& server) {
        for (const auto& i : server._validUser){
            if (i._username == user)
                return true;
        }
        return false;
    }

    bool PassCommand::validPass(const std::string& password, Server& server) {
        for (const auto& i : server._validUser)
            if (i._password == password)
                return true;
        return false;
    }

}
