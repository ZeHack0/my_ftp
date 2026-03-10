/*
** EPITECH PROJECT, 2026
** my_ftp
** File description:
** HelpCommand
*/

#include "Command/HelpCommand.hpp"

#include <cstring>
#include <vector>

namespace ftp {

    void HelpCommand::execute(int fd, const std::string& args, Server& server) {
        (void)server;

        if (!args.empty()) {
            AccurateHelp(fd, args);
            return;
        }

        const std::string msg = "214 The following commands are recognized:\r\n"
                                "USER    PASS    CWD    CDUP\r\n"
                                "QUIT    DELE    PWD    PASV\r\n"
                                "PORT    HELP    NOOP   RETR\r\n"
                                "STOR    LIST\r\n";
        write(fd, msg.c_str(), msg.length());
    };

    void HelpCommand::AccurateHelp(int fd, const std::string& args) {

        std::vector<std::string> Commands = {"USER", "PASS", "CWD", "CDUP",
            "QUIT", "DELE", "PWD", "PASV", "PORT", "HELP", "NOOP",
            "RETR", "STOR", "LIST"};

        std::vector<std::string> DescriptionCommands = {
            "USER <SP> <username> <CRLF>    : Specify user for authentication\r\n",
            "PASS <SP> <password> <CRLF>    : Specify password for authentication\r\n",
            "CWD <SP> <pathname> <CRLF>    : Change working directory\r\n",
            "CDUP <CRLF>    : Change working directory to parent directory\r\n",
            "QUIT <CRLF>    : Disconnection\r\n",
            "DELE <SP> <pathname> <CRLF>    : Delete file on the server\r\n",
            "PWD <CRLF>    : Print working directory\r\n",
            "PASV <CRLF>    : Enable \"passive\" mode for data transfer\r\n",
            "PORT <SP> <host-port> <CRLF>   : Enable \"active\" mode for data transfer\r\n",
            "HELP [<SP> <string>] <CRLF>    : List available commands\r\n",
            "NOOP <CRLF>    : Do nothing\r\n",
            "RETR <SP> <pathname> <CRLF>    : Download file from server to client\r\n",
            "STOR <SP> <pathname> <CRLF>    : Upload file from client to server\r\n",
            "LIST [<SP> <pathname>] <CRLF>   : List files in the current working directory\r\n",
        };

        for (std::size_t i = 0; i < Commands.size(); i++) {
            if (std::strcmp(args.c_str(), Commands[i].c_str()) == 0) {
                write(fd, DescriptionCommands[i].c_str(), DescriptionCommands[i].length());
            }
        }
    }
}
