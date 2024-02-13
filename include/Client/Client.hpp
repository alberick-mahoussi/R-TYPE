/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <iostream>
#include <unordered_set>
#include <any>
#include <optional>

#include "GameEngine/ECS/Entity/Registry.hpp"
#include "GameEngine/ECS/System/Logging.hpp"
#include "GameEngine/ECS/System/Render.hpp"
#include "GameEngine/ECS/System/Scene.hpp"
#include "GameEngine/ECS/System/MouvementSystem.hpp"
#include "GameEngine/ECS/System/ShootSystemClient.hpp"
#include "GameEngine/ECS/System/TextBoxSystem.hpp"
#include "GameEngine/ECS/System/MobEnemy.hpp"
#include "GameEngine/ECS/System/MobEnemyClient.hpp"
#include "GameEngine/ECS/System/GuiSystem.hpp"
#include "GameEngine/ECS/System/CollisionSystemClient.hpp"
#include "GameEngine/ECS/System/SoundSystem.hpp"
#include "GameEngine/ECS/System/DestroyAnimSystem.hpp"
#include "GameEngine/ECS/System/ItemSystem.hpp"
#include "GameEngine/ECS/System/GameOverSystem.hpp"
#include "GameEngine/ECS/System/WeaponSystem.hpp"
#include "GameEngine/ECS/System/EnemyShootSystem.hpp"
#include "GameEngine/ECS/System/EnemyShootSystemClient.hpp"
#include "../Network/network.hpp"
#include "../Network/Serialise.hpp"
#include "queue"

#include <SFML/Audio.hpp>
// #include <SFMLFFmpeg.hpp>

class Client {
    public:
      Client();
      ~Client();
      void launchGame();
      void initMenu();
      void initGame();
      void initSystem();
      void initWaitingRoom();
      void initLoggingScreen();
      // void gameOver();

      int _first = 0;
      bool isOpen = true;

    private:
      bool connected;
      Registry _registry;
      sf::Music _music;
};

#endif /* !CLIENT_HPP_ */
