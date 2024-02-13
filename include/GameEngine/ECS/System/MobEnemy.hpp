/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** MobEnemy
*/

#ifndef MOBENEMY_HPP_
#define MOBENEMY_HPP_

#include "GameEngine/ECS/Entity/Registry.hpp"
#include <SFML/System/Vector3.hpp>

class MobEnemy : public System {
    public:
        MobEnemy(Registry &registry) : _registry(registry) {};
        ~MobEnemy();
        sf::Vector3f mob_info() {
            int r = std::rand() % 120;
            if (r == 0) {
                return sf::Vector3f {1920, float(std::rand() % (850)), float(std::rand() % (2))};
            } else
                return sf::Vector3f {0, 0, 3};
        }
        void callSystem() {
            sf::Vector3f data = mob_info();
            std::any storedValue = _registry.indexedParams["mob"];
            mobClass& _mobSend = std::any_cast<mobClass&>(storedValue);
            _mobSend._x = data.x;
            _mobSend._y  = data.y;
            _mobSend._type = data.z;
            _mobSend._id = int(0);
            _registry.indexedParams["mob"] = _mobSend;
        }
    protected:
    private:
        Registry &_registry;
        int _entityReusable = 0;
};

#endif /* !MOBENEMY_HPP_ */
