/*
** EPITECH PROJECT, 2026
** nanotekspice
** File description:
** Help
*/

#include "Myftp.hpp"
#include <iostream>

void help()
{
    std::cout << "USAGE: ./myftp port path\n"
                 " port is the port number on which the server socket listens\n"
                 " path is the path to the home directory for the Anonymous user"
    << std::endl;
}
