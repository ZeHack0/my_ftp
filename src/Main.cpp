/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Main
*/

#include "Myftp.hpp"
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
    std::cout << "./myftp <port>: " << av[1] << "    <path>: " << av[2] << std::endl;
}
