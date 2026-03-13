/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Main
*/

#include "Myftp.hpp"
#include "Server.hpp"
#include <iostream>

int main(int ac, char **av)
{
    if ((ac == 2 && std::string(av[1]) == "--help") ||
        (ac == 2 && std::string(av[1]) == "-h")) {
        help();
        return 0;
    }
    if (ac != 3)
        return std::cout << "Missing arguments" << std::endl, 84;

    try {
        ftp::Server server(av[1], av[2]);
        server.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}
