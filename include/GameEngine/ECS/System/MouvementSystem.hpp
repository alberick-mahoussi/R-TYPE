/*
** EPITECH PROJECT, 2023
** tek3
** File description:
** MouvementSystem
*/

#ifndef MOUVEMENTSYSTEM_HPP_
#define MOUVEMENTSYSTEM_HPP_

#include "GameEngine/ECS/Entity/Registry.hpp"

class MouvementSystem : public System {
    public:
        MouvementSystem(Registry &registry) : _registry(registry) {};
        ~MouvementSystem();
        void callSystem() {
            auto &positionComp = _registry.get_components<PositionComponent>();
            auto const &velocityComp = _registry.get_components<VelocityComponent>();
            // auto const &inputComp = _registry.get_components<InputComponent>();
            auto &entityCompo = _registry.get_components<DeadComponent>();
            auto &drawableComp = _registry.get_components<DrawableComponent>();
            auto &WeaponComp = _registry.get_components<WeaponComponent>();
            // int inputPlayer = std::any_cast<int>(_registry.indexedParams["input"]);
            auto &shootableComp = _registry.get_components<ShootableComponent>();
            std::any storedValue = _registry.indexedParams["entityMove"];
            entityMoveClass& _entitySend = std::any_cast<entityMoveClass&>(storedValue);
            for (size_t i = 1; i < positionComp.size(); ++i) {
                auto &position = positionComp[i];
                auto const &velocity = velocityComp[i];
                // auto const &input = inputComp[i];
                auto &entity = entityCompo[i];
                auto &shootable = shootableComp[i];
                auto &drawable = drawableComp[i];
                // if (entity && (entity->_alive == false && entity->_entityType == EntityType::WEAPON)) {
                //     switch (inputPlayer)
                //     {
                //     case Control::UP:
                //         position->_y = (position->_y - velocity->_y <= 50) ? 50 : position->_y - velocity->_y;
                //         break;
                //     case Control::DOWN:
                //         position->_y = (position->_y + velocity->_y >= 830) ? 830 : position->_y + velocity->_y;
                //         break;
                //     case Control::LEFT:
                //         position->_x = (position->_x - velocity->_x <= 162) ? 162 : position->_x - velocity->_x;
                //         break;
                //     case Control::RIGHT:
                //         position->_x = (position->_x + velocity->_x >= 1750) ? 1750 : position->_x + velocity->_x;
                //         break;
                //     }
                // }
                if (entity && (entity->_alive == false && entity->_entityType == EntityType::BULLET)) {
                    if (position->_x >= 2100 || position->_x <= -200) {
                        entity->_alive = true;
                        drawable->_draw = false;
                    } else {
                        position->_x += velocity->_x;
                        _entitySend._idEntity.push_back(i);
                        _entitySend._idPosX.push_back(position->_x);
                        _entitySend._idPosY.push_back(position->_y);
                    }
                }
                if (entity && (entity->_alive == false && entity->_entityType == EntityType::MOB)) {
                    if (position->_x <= -200) {
                        entity->_alive = true;
                        drawable->_draw = false;
                        shootable->_shoot = false;
                    } else {
                        position->_x += velocity->_x;
                        _entitySend._idEntity.push_back(i);
                        _entitySend._idPosX.push_back(position->_x);
                        _entitySend._idPosY.push_back(position->_y);
                    }
                }
            }
            _registry.indexedParams["entityMove"] = _entitySend;
        }

    protected:
    private:
        Registry &_registry;
};

#endif /* !MOUVEMENTSYSTEM_HPP_ */
