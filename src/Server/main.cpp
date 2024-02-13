/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** main
*/

#include <iostream>
#include "../../include/Network/packets.hpp"
#include "../../include/Server/Server.hpp"

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cerr << "Usage: ./server" << std::endl;
        return 84;
    }
    int port = atoi(av[1]);
    srand(time(NULL));
    try {
        Server server(port);
        server.Execute();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
