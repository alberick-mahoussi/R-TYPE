/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** WeaponSystem
*/

#ifndef WEAPONSYSTEM_HPP_
#define WEAPONSYSTEM_HPP_

#include "GameEngine/ECS/Entity/Registry.hpp"

class WeaponSystem : public System {
    public:
        WeaponSystem(Registry &registry) : _registry(registry) {};
        ~WeaponSystem();
        void callSystem() {
            auto const &InputComp = _registry.get_components<InputComponent>();
            auto const &PositionComp = _registry.get_components<PositionComponent>();
            auto const &ScoreComp = _registry.get_components<ScoreComponent>();
            auto const &DeadComp = _registry.get_components<DeadComponent>();
            auto &ShootableComp = _registry.get_components<ShootableComponent>();
            auto &WeaponComp = _registry.get_components<WeaponComponent>();
            auto &VelocityComp = _registry.get_components<VelocityComponent>();
            auto &ScaleComp = _registry.get_components<ScaleComponent>();

            for (size_t i = 0; i < InputComp.size(); ++i) {
                auto const &score = ScoreComp[i];
                auto const &input = InputComp[i];
                auto &position = PositionComp[i];
                auto const &dead = DeadComp[i];
                auto &shoot = ShootableComp[i];
                auto &_weapon = WeaponComp[i];
                auto &scale = ScaleComp[i];
                auto const &velocity = VelocityComp[i];
                if (std::any_cast<std::string>(_registry.indexedParams["exec"]) == "server") {
                    if (input && (input->_controllable == true)) {
                        if (score && _weapon && (score->_score >= 500 && _weapon->_weapon == false) ) {
                            _entityReusable = 0;
                            for (size_t i = 0; i < DeadComp.size(); ++i) {
                                if (dead && (dead->_alive == true && dead->_entityType == EntityType::WEAPON)) {
                                    _entityReusable = i;
                                    break;
                                }
                            }
                            std::any storedValue = _registry.indexedParams["weapon"];
                            weaponClass& _weaponSend = std::any_cast<weaponClass&>(storedValue);
                            if (_entityReusable == 0) {
                                auto weapon = _registry.spawn_entity();
                                std::vector<std::string> scenes = {"Play"};
                                _registry.add_component<DrawableComponent>(weapon, DrawableComponent{true});
                                _registry.add_component<TextureComponent>(weapon, TextureComponent{BONUS_1, false});
                                _registry.add_component<SceneComponent>(weapon, SceneComponent{scenes});
                                _registry.add_component<SpriteInitializedComponent>(weapon, SpriteInitializedComponent{false});
                                _registry.add_component<DestroyedComponent>(weapon, DestroyedComponent{false, 1});
                                _registry.add_component<PositionComponent>(weapon, PositionComponent{position->_x + (position->_wth * scale->_scaleX) - 20, position->_y, 180 / 6, 24});
                                _registry.add_component<AnimationComponent>(weapon, AnimationComponent{true, 0, 0.1f, 1, 6, 120, 68});
                                _registry.add_component<ScaleComponent>(weapon, ScaleComponent{3, 3});
                                _registry.add_component<VelocityComponent>(weapon, VelocityComponent{velocity->_x, velocity->_y});
                                _registry.add_component<DeadComponent>(weapon, DeadComponent{false, EntityType::WEAPON});
                                _registry.add_component<ShootableComponent>(shoot->_playerId, ShootableComponent{true, ShootType::BOMB, shoot->_playerId});
                                _weapon->_weapon = true;
                                _weaponSend._id = weapon;
                                _weaponSend._idPlayer = shoot->_playerId;
                            } else {
                                _registry.add_component<PositionComponent>(_entityReusable, PositionComponent{position->_x + (position->_wth * scale->_scaleX)  - 20, position->_y, 180 / 6, 24});
                                _registry.add_component<DeadComponent>(_entityReusable, DeadComponent{false, EntityType::WEAPON});
                                _registry.add_component<DestroyedComponent>(_entityReusable, DestroyedComponent{true, 1});
                                _registry.add_component<ShootableComponent>(shoot->_playerId, ShootableComponent{true, ShootType::BOMB, shoot->_playerId});
                                _weapon->_weapon = true;
                                _weaponSend._id = _entityReusable;
                                _weaponSend._idPlayer = shoot->_playerId;
                            }
                            _entityReusable = 0;
                            _registry.indexedParams["weapon"] = _weaponSend;
                        }
                    }
                } else if (std::any_cast<std::string>(_registry.indexedParams["exec"]) == "client") {
                    if (std::any_cast<weaponClass>(_registry.indexedParams["weapon"])._id != 0) {
                        int weapon = std::any_cast<weaponClass>(_registry.indexedParams["weapon"])._id;
                        int idPlayer = std::any_cast<weaponClass>(_registry.indexedParams["weapon"])._idPlayer;
                        auto &_weapon = WeaponComp[idPlayer];
                        auto const &_position = PositionComp[idPlayer];
                        auto const &velocity = VelocityComp[idPlayer];

                        std::vector<std::string> scenes = {"Play"};
                        _registry.add_component<DrawableComponent>(weapon, DrawableComponent{true});
                        _registry.add_component<TextureComponent>(weapon, TextureComponent{BONUS_1, false});
                        _registry.add_component<SceneComponent>(weapon, SceneComponent{scenes});
                        _registry.add_component<SpriteInitializedComponent>(weapon, SpriteInitializedComponent{false});
                        _registry.add_component<DestroyedComponent>(weapon, DestroyedComponent{false, 1});
                        _registry.add_component<PositionComponent>(weapon, PositionComponent{_position->_x + (_position->_wth * scale->_scaleX) - 20, _position->_y, 180 / 6, 24});
                        _registry.add_component<AnimationComponent>(weapon, AnimationComponent{true, 0, 0.1f, 1, 6, 120, 68});
                        _registry.add_component<ScaleComponent>(weapon, ScaleComponent{3, 3});
                        _registry.add_component<VelocityComponent>(weapon, VelocityComponent{velocity->_x, velocity->_y});
                        _registry.add_component<DeadComponent>(weapon, DeadComponent{false, EntityType::WEAPON});
                        _registry.add_component<ShootableComponent>(idPlayer, ShootableComponent{true, ShootType::BOMB, idPlayer});
                        _weapon->_weapon = true;
                    }
                }
            }
        }

    protected:
    private:
        Registry &_registry;
        int _entityReusable = 0;
};

#endif /* !WEAPONSYSTEM_HPP_ */
