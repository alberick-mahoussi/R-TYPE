/*
** EPITECH PROJECT, 2023
** tek3
** File description:
** ShootSystem
*/

#ifndef SHOOTSYSTEM_HPP_
#define SHOOTSYSTEM_HPP_

#include "GameEngine/ECS/Entity/Registry.hpp"

class ShootSystem : public System {
    public:
        ShootSystem(Registry &registry) : _registry(registry) {};
        ~ShootSystem();
        void callSystem() {
            auto &positionComp = _registry.get_components<PositionComponent>();
            auto const &teamComp = _registry.get_components<TeamComponent>();
            auto const &shootableComp = _registry.get_components<ShootableComponent>();
            auto const &scaleComp = _registry.get_components<ScaleComponent>();
            auto const &animationComp = _registry.get_components<AnimationComponent>();
            auto const &bulletComp = _registry.get_components<DeadComponent>();
            auto &DamageComp = _registry.get_components<DamageComponent>();
            auto &SoundComp = _registry.get_components<SoundComponent>();

            int shooter = 0;

            shooter = std::any_cast<int>(_registry.indexedParams["playerController"]);
            std::any storedValue = _registry.indexedParams["bullet"];
            mobClass& _bulletSend = std::any_cast<mobClass&>(storedValue);
            if (shooter > 0) {
                for (size_t i = 1; i < bulletComp.size(); ++i) {
                    auto const &bullet = bulletComp[i];
                    auto const &team = teamComp[i];
                    if (bullet && team && (bullet->_alive == true && bullet->_entityType == EntityType::BULLET && team->_team == TeamType::ALLY)) {
                        _entityReusable = i;
                        break;
                    }
                }
                int playerId = shooter;
                auto &position = positionComp[shooter];
                // auto &animation = animationComp[shooter];
                auto &scale = scaleComp[shooter];
                auto const &team = teamComp[shooter];
                auto const &shootable = shootableComp[shooter];
                // auto &sound = SoundComp[shooter];
                _bulletSend._type = shootable->_type;
                _bulletSend._x = position->_x;
                _bulletSend._y = position->_y;
                if (_entityReusable == 0) {
                    auto bullet = _registry.spawn_entity();
                    std::vector<std::string> scenes = {"Play"};
                    _registry.add_component<DrawableComponent>(bullet, DrawableComponent{true});
                    _registry.add_component<TextureComponent>(bullet, TextureComponent{SHOOT, false});
                    _registry.add_component<SceneComponent>(bullet, SceneComponent{scenes});
                    _registry.add_component<SpriteInitializedComponent>(bullet, SpriteInitializedComponent{false});
                    _registry.add_component<TeamComponent>(bullet, TeamComponent{TeamType::ALLY});
                    _registry.add_component<DeadComponent>(bullet, DeadComponent{false, EntityType::BULLET});
                    switch (shootable->_type) {
                        case ShootType::BASIC:
                            _registry.add_component<PositionComponent>(bullet, PositionComponent{position->_x + ((position->_wth * scale->_scaleX)) + 10, position->_y + ((position->_hgt) / 2), 29 / 2, 12});
                            _registry.add_component<AnimationComponent>(bullet, AnimationComponent{true, 0, 0.1f, 1, 2, 288, 84});
                            _registry.add_component<ScaleComponent>(bullet, ScaleComponent{3.5, 3.5});
                            _registry.add_component<VelocityComponent>(bullet, VelocityComponent{10 , 0});
                            _registry.add_component<DamageComponent>(bullet, DamageComponent{10 + DamageComp[playerId]->_bonus, playerId, 0});
                            _registry.add_component<DamageComponent>(playerId, DamageComponent{10 + DamageComp[playerId]->_bonus, playerId, DamageComp[playerId]->_bonus});
                            break;
                        case ShootType::BOMB:
                            _registry.add_component<PositionComponent>(bullet, PositionComponent{position->_x + ((position->_wth * scale->_scaleX)) + 10, position->_y + ((position->_hgt) / 2), 33 / 2, 12});
                            _registry.add_component<AnimationComponent>(bullet, AnimationComponent{true, 0, 0.1f, 1, 2, 232, 103});
                            _registry.add_component<ScaleComponent>(bullet, ScaleComponent{4.5, 4.5});
                            _registry.add_component<VelocityComponent>(bullet, VelocityComponent{5 , 0});
                            _registry.add_component<DamageComponent>(bullet, DamageComponent{50 + DamageComp[playerId]->_bonus, playerId, 0});
                            _registry.add_component<DamageComponent>(playerId, DamageComponent{50 + DamageComp[playerId]->_bonus, playerId, DamageComp[playerId]->_bonus});
                            break;
                        default:
                            break;
                    }
                    _bulletSend._id = bullet;
                } else {
                    switch (shootable->_type) {
                        case ShootType::BASIC:
                            _registry.add_component<PositionComponent>(_entityReusable, PositionComponent{position->_x + ((position->_wth * scale->_scaleX)) + 10, position->_y + ((position->_hgt) / 2), 29 / 2, 12});
                            _registry.add_component<AnimationComponent>(_entityReusable, AnimationComponent{true, 0, 0.1f, 1, 2, 288, 85});
                            _registry.add_component<ScaleComponent>(_entityReusable, ScaleComponent{3.5, 3.5});
                            _registry.add_component<VelocityComponent>(_entityReusable, VelocityComponent{10 , 0});
                            _registry.add_component<DamageComponent>(_entityReusable, DamageComponent{10 + DamageComp[playerId]->_bonus, playerId, 0});
                            _registry.add_component<DamageComponent>(playerId, DamageComponent{10 + DamageComp[playerId]->_bonus, playerId, DamageComp[playerId]->_bonus});
                            break;
                        case ShootType::BOMB:
                            _registry.add_component<PositionComponent>(_entityReusable, PositionComponent{position->_x + ((position->_wth * scale->_scaleX)) + 10, position->_y + ((position->_hgt) / 2), 33 / 2, 12 });
                            _registry.add_component<AnimationComponent>(_entityReusable, AnimationComponent{true, 0, 0.1f, 1, 2, 232, 103});
                            _registry.add_component<ScaleComponent>(_entityReusable, ScaleComponent{4.5, 4.5});
                            _registry.add_component<VelocityComponent>(_entityReusable, VelocityComponent{5 , 0});
                            _registry.add_component<DamageComponent>(_entityReusable, DamageComponent{50 + DamageComp[playerId]->_bonus, playerId, 0});
                            _registry.add_component<DamageComponent>(playerId, DamageComponent{50 + DamageComp[playerId]->_bonus, playerId, DamageComp[playerId]->_bonus});
                            break;
                        default:
                            break;
                    }
                    _registry.add_component<DeadComponent>(_entityReusable, DeadComponent{false, EntityType::BULLET});
                    _bulletSend._id = _entityReusable;
                }
                _entityReusable = 0;
                _registry.indexedParams["bullet"] = _bulletSend;
            }
        }

    protected:
    private:
        Registry &_registry;
        int _entityReusable = 0;
};

#endif /* !SHOOTSYSTEM_HPP_ */
