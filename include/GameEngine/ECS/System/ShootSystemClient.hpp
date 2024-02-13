/*
** EPITECH PROJECT, 2023
** tek3
** File description:
** ShootSystem
*/

#ifndef SHOOTSYSTEMCLIENT_HPP_
#define SHOOTSYSTEMCLIENT_HPP_

#include "GameEngine/ECS/Entity/Registry.hpp"

class ShootSystemClient : public System {
    public:
        ShootSystemClient(Registry &registry) : _registry(registry) {};
        ~ShootSystemClient();
         void callSystem() {
            auto &positionComp = _registry.get_components<PositionComponent>();
            auto const &teamComp = _registry.get_components<TeamComponent>();
            auto const &shootableComp = _registry.get_components<ShootableComponent>();
            auto const &scaleComp = _registry.get_components<ScaleComponent>();
            auto const &animationComp = _registry.get_components<AnimationComponent>();
            auto const &bulletComp = _registry.get_components<DeadComponent>();
            auto &DamageComp = _registry.get_components<DamageComponent>();
            auto &SoundComp = _registry.get_components<SoundComponent>();
            int idBullet = std::any_cast<mobClass>(_registry.indexedParams["bullet"])._id;
            double x = std::any_cast<mobClass>(_registry.indexedParams["bullet"])._x;
            double y = std::any_cast<mobClass>(_registry.indexedParams["bullet"])._y;
            int type = std::any_cast<mobClass>(_registry.indexedParams["bullet"])._type;
            int idPlayer = std::any_cast<int>(_registry.indexedParams["playerController"]);

            std::any storedValue = _registry.indexedParams["bullet"];
            mobClass& _bulletSend = std::any_cast<mobClass&>(storedValue);

            if (idBullet > 0 && idPlayer > 0 && type > 0 && x > 0 && y > 0) {
                int playerId = idPlayer;
                auto &position = positionComp[idPlayer];
                auto &animation = animationComp[idPlayer];
                auto &scale = scaleComp[idPlayer];
                auto const &team = teamComp[idPlayer];
                auto const &shootable = shootableComp[idPlayer];
                auto &sound = SoundComp[idPlayer];
                std::vector<std::string> scenes = {"Play"};
                _registry.add_component<DrawableComponent>(idBullet, DrawableComponent{true});
                _registry.add_component<TextureComponent>(idBullet, TextureComponent{SHOOT, false});
                _registry.add_component<SceneComponent>(idBullet, SceneComponent{scenes});
                _registry.add_component<SpriteInitializedComponent>(idBullet, SpriteInitializedComponent{false});
                _registry.add_component<TeamComponent>(idBullet, TeamComponent{team->_team});
                _registry.add_component<DeadComponent>(idBullet, DeadComponent{false, EntityType::BULLET});
                switch (shootable->_type) {
                    case ShootType::BASIC:
                        _registry.add_component<PositionComponent>(idBullet, PositionComponent{position->_x + ((position->_wth * scale->_scaleX)) + 10, position->_y + ((position->_hgt) / 2), 29 / 2, 12});
                        _registry.add_component<AnimationComponent>(idBullet, AnimationComponent{true, 0, 0.1f, 1, 2, 288, 84});
                        _registry.add_component<ScaleComponent>(idBullet, ScaleComponent{3.5, 3.5});
                        _registry.add_component<VelocityComponent>(idBullet, VelocityComponent{10 , 0});
                        _registry.add_component<DamageComponent>(idBullet, DamageComponent{10 + DamageComp[playerId]->_bonus, playerId, 0});
                        _registry.add_component<DamageComponent>(playerId, DamageComponent{10 + DamageComp[playerId]->_bonus, playerId, DamageComp[playerId]->_bonus});
                        break;
                    case ShootType::BOMB:
                        _registry.add_component<PositionComponent>(idBullet, PositionComponent{position->_x + ((position->_wth * scale->_scaleX)) + 10, position->_y + ((position->_hgt) / 2), 33 / 2, 12});
                        _registry.add_component<AnimationComponent>(idBullet, AnimationComponent{true, 0, 0.1f, 1, 2, 232, 103});
                        _registry.add_component<ScaleComponent>(idBullet, ScaleComponent{4.5, 4.5});
                        _registry.add_component<VelocityComponent>(idBullet, VelocityComponent{5 , 0});
                        _registry.add_component<DamageComponent>(idBullet, DamageComponent{50 + DamageComp[playerId]->_bonus, playerId, 0});
                        _registry.add_component<DamageComponent>(playerId, DamageComponent{50 + DamageComp[playerId]->_bonus, playerId, DamageComp[playerId]->_bonus});
                        break;
                    default:
                        break;
                }
                _bulletSend._id = 0;
                _bulletSend._x = 0;
                _bulletSend._y = 0;
                _bulletSend._type = 0;
                _registry.indexedParams["bullet"] = _bulletSend;
            }
        }

    protected:
    private:
        Registry &_registry;
        int _entityReusable = 0;
};

#endif /* !SHOOTSYSTEM_HPP_ */
