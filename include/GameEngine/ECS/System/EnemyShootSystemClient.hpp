/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** EnemyShootSystemClient
*/

#ifndef ENEMYSHOOTSYSTEMCLIENT_HPP_
#define ENEMYSHOOTSYSTEMCLIENT_HPP_

#include "GameEngine/ECS/Entity/Registry.hpp"

class EnemyShootSystemClient : public System {
    public:
        EnemyShootSystemClient(Registry &registry) : _registry(registry) {};
        ~EnemyShootSystemClient();
        void callSystem() {
            auto &positionComp = _registry.get_components<PositionComponent>();
            auto const &shootableComp = _registry.get_components<ShootableComponent>();
            auto const &scaleComp = _registry.get_components<ScaleComponent>();
            auto &DamageComp = _registry.get_components<DamageComponent>();
            auto &SoundComp = _registry.get_components<SoundComponent>();

            Registry::entity_t bullet = std::any_cast<enemyShootClass>(_registry.indexedParams["enemyShoot"])._bullet;
            int i = std::any_cast<enemyShootClass>(_registry.indexedParams["enemyShoot"])._player;

            if (i > 50 && bullet > 49) {
                auto &scale = scaleComp[i];
                auto const &position = positionComp[i];
                auto const &shootable = shootableComp[i];
                auto &sound = SoundComp[i];
                sound->_index = 2;
                std::vector<std::string> scenes = {"Play"};
                _registry.add_component<DrawableComponent>(bullet, DrawableComponent{true});
                _registry.add_component<TextureComponent>(bullet, TextureComponent{SHOOT_2, false});
                _registry.add_component<SceneComponent>(bullet, SceneComponent{scenes});
                _registry.add_component<SpriteInitializedComponent>(bullet, SpriteInitializedComponent{false});
                _registry.add_component<TeamComponent>(bullet, TeamComponent{TeamType::ENEMY});
                _registry.add_component<DeadComponent>(bullet, DeadComponent{false, EntityType::BULLET});
                switch (shootable->_type) {
                    case ShootType::BASIC:
                        _registry.add_component<PositionComponent>(bullet, PositionComponent{position->_x, position->_y + ((position->_hgt * scale->_scaleY) / 2) - 10, 400 / 8, 8});
                        _registry.add_component<AnimationComponent>(bullet, AnimationComponent{true, 0, 0.1f, 1, 8, 0, 39});
                        _registry.add_component<ScaleComponent>(bullet, ScaleComponent{1, 3});
                        _registry.add_component<VelocityComponent>(bullet, VelocityComponent{-7.5 , 0});
                        _registry.add_component<DamageComponent>(bullet, DamageComponent{10 + DamageComp[shootable->_playerId]->_bonus, shootable->_playerId, 0});
                        _registry.add_component<DamageComponent>(shootable->_playerId, DamageComponent{10 + DamageComp[shootable->_playerId]->_bonus, shootable->_playerId, DamageComp[shootable->_playerId]->_bonus});
                        break;
                    default:
                        break;
                }
                std::any storedValue = _registry.indexedParams["enemyShoot"];
                enemyShootClass& _bulletSend = std::any_cast<enemyShootClass&>(storedValue);
                _bulletSend._bullet = 0;
                _bulletSend._player = 0;
                _registry.indexedParams["enemyShoot"] = _bulletSend;
            }
        }
    protected:
    private:
        Registry &_registry;
};

#endif /* !ENEMYSHOOTSYSTEMCLIENT_HPP_ */
