/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** GameOverSystem
*/

#ifndef GAMEOVERSYSTEM_HPP_
#define GAMEOVERSYSTEM_HPP_

#include "GameEngine/ECS/Entity/Registry.hpp"

class GameOverSystem : public System {
    public:
        GameOverSystem(Registry &registry) : _registry(registry) {};
        ~GameOverSystem();
        void callSystem() {
            auto const &ShootableComp = _registry.get_components<ShootableComponent>();
            auto const &HealthComp = _registry.get_components<HealthComponent>();
            auto &DeadComp = _registry.get_components<DeadComponent>();
            auto &drawableComp = _registry.get_components<DrawableComponent>();
            auto &teamComp = _registry.get_components<TeamComponent>();

            for (size_t i = 1; i < ShootableComp.size(); ++i) {
                auto const &health = HealthComp[i];
                auto &shoot = ShootableComp[i];
                auto const &team = teamComp[i];

                if (team && shoot && health && (shoot->_shoot == false && health->_current_health == 0 && team->_team != ENEMY)) {
                    for (size_t i = 0; i < DeadComp.size(); ++i) {
                        auto &dead = DeadComp[i];
                        if (dead && (dead->_alive == false)) {
                            dead->_alive = true;
                        }
                    }
                }
            }
        }

    protected:
    private:
        Registry &_registry;
};

#endif /* !GAMEOVERSYSTEM_HPP_ */
