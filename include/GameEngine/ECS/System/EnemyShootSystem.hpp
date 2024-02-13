/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** EnemyShootSystem
*/

#ifndef ENEMYSHOOTSYSTEM_HPP_
#define ENEMYSHOOTSYSTEM_HPP_

#include "GameEngine/ECS/Entity/Registry.hpp"

class EnemyShootSystem : public System {
    public:
        EnemyShootSystem(Registry &registry) : _registry(registry) {};
        ~EnemyShootSystem();
        bool mob_info() {
            int r = std::rand() % 120;
            if (r == 0)
                return true;
            return false;
        }
        void callSystem() {
            auto &positionComp = _registry.get_components<PositionComponent>();
            auto const &teamComp = _registry.get_components<TeamComponent>();
            auto const &shootableComp = _registry.get_components<ShootableComponent>();
            auto const &scaleComp = _registry.get_components<ScaleComponent>();
            auto const &animationComp = _registry.get_components<AnimationComponent>();
            auto const &bulletComp = _registry.get_components<DeadComponent>();
            auto &DamageComp = _registry.get_components<DamageComponent>();
            auto &SoundComp = _registry.get_components<SoundComponent>();

            std::any storedValue = _registry.indexedParams["enemyShoot"];
            enemyShootClass& _bulletSend = std::any_cast<enemyShootClass&>(storedValue);

            if (std::any_cast<std::string>(_registry.indexedParams["exec"]) == "server") {
                    for (size_t i = 1; i < bulletComp.size(); ++i) {
                        auto const &bullet = bulletComp[i];
                        auto const &team = teamComp[i];
                        if (bullet && team && (bullet->_alive == true && (bullet->_entityType == EntityType::BULLET && team->_team == TeamType::ENEMY))) {
                            _entityReusable = i;
                            break;
                        }
                    }
                    for (size_t i = 0; i < shootableComp.size(); ++i) {
                        auto &position = positionComp[i];
                        auto &animation = animationComp[i];
                        auto const &bullet = bulletComp[i];
                        auto &scale = scaleComp[i];
                        auto const &team = teamComp[i];
                        auto const &shootable = shootableComp[i];
                        auto &sound = SoundComp[i];
                        if (shootable && bullet && team && (shootable->_shoot == true && (team->_team == TeamType::ENEMY && (bullet->_entityType == EntityType::MOB && bullet->_alive == false)))) {
                            if (mob_info() == true) {
                                if (_entityReusable == 0) {
                                    auto bullet = _registry.spawn_entity();
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
                                    _bulletSend._idBullet.push_back(bullet);
                                } else {
                                    switch (shootable->_type) {
                                        case ShootType::BASIC:
                                            _registry.add_component<PositionComponent>(_entityReusable, PositionComponent{position->_x, position->_y + ((position->_hgt * scale->_scaleY) / 2) - 10, 400 / 8, 8});
                                            _registry.add_component<AnimationComponent>(_entityReusable, AnimationComponent{true, 0, 0.1f, 1, 8, 0, 39});
                                            _registry.add_component<ScaleComponent>(_entityReusable, ScaleComponent{1, 3});
                                            _registry.add_component<VelocityComponent>(_entityReusable, VelocityComponent{-7.5 , 0});
                                            _registry.add_component<DamageComponent>(_entityReusable, DamageComponent{10 + DamageComp[shootable->_playerId]->_bonus, shootable->_playerId, 0});
                                            _registry.add_component<DamageComponent>(shootable->_playerId, DamageComponent{10 + DamageComp[shootable->_playerId]->_bonus, shootable->_playerId, DamageComp[shootable->_playerId]->_bonus});
                                            break;
                                        default:
                                            break;
                                    }
                                    _registry.add_component<DeadComponent>(_entityReusable, DeadComponent{false, EntityType::BULLET});
                                    _bulletSend._idBullet.push_back(_entityReusable);
                                }
                                _bulletSend._idPlayer.push_back(i);
                                _registry.indexedParams["enemyShoot"] = _bulletSend;
                            }
                        }
                    }
                _entityReusable = 0;
            }
        }
    protected:
    private:
        Registry &_registry;
        int _entityReusable = 0;
};

#endif /* !ENEMYSHOOTSYSTEM_HPP_ */
