/*
 EPITECH PROJECT, 2023
 B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
 File description:
 Clients
*/

#include "Client/Client.hpp"

Client::Client() : _registry()
{
   // if (!_music.openFromFile(MUSIC_GAME))
   //     std::cout << "Error: Could not display _music !" << std::endl;
    //_music.play();
    //_music.setLoop(true);
}

Client::~Client()
{
}

void Client::launchGame()
{
    while (std::any_cast<std::string>(_registry.indexedParams["command"]) != "close") {
        for (System* system : _registry.systems)
            system->callSystem();
    }
}

int main(void)
{
    try {
        Client client;
        client.initMenu();
        client.launchGame();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
