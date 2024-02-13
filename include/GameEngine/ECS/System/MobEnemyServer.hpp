/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** MobEnemyClient
*/

#ifndef MOBENEMYSERVER_HPP_
#define MOBENEMYSERVER_HPP_

#include "GameEngine/ECS/Entity/Registry.hpp"
#include <SFML/System/Vector3.hpp>

class MobEnemyServer : public System {
    public:
        MobEnemyServer(Registry &registry) : _registry(registry) {};
        ~MobEnemyServer();
        void callSystem() {
            auto const &mobsCompo = _registry.get_components<DeadComponent>();
            std::any storedValue = _registry.indexedParams["mob"];
            mobClass& _mobSend = std::any_cast<mobClass&>(storedValue);

            int mob = std::any_cast<mobClass>(_registry.indexedParams["mob"])._id;
            double x = std::any_cast<mobClass>(_registry.indexedParams["mob"])._x;
            double y = std::any_cast<mobClass>(_registry.indexedParams["mob"])._y;
            int type = std::any_cast<mobClass>(_registry.indexedParams["mob"])._type;
            
            if (type != 3) {
                for (size_t i = 0; i < mobsCompo.size(); ++i) {
                    auto const &mobs = mobsCompo[i];
                    if (mobs && (mobs->_alive == true && mobs->_entityType == EntityType::MOB)) {
                        _entityReusable = i;
                        break;
                    }
                }
                //x = data.x;
                //y  = data.y;
                //type = data.z;
                if (_entityReusable == 0) {
                    auto mob = _registry.spawn_entity();
                    std::vector<std::string> scenes = {"Play"};
                    _registry.add_component<DrawableComponent>(mob, DrawableComponent{true});
                    _registry.add_component<SceneComponent>(mob, SceneComponent{scenes});
                    _registry.add_component<SpriteInitializedComponent>(mob, SpriteInitializedComponent{false});
                    _registry.add_component<TeamComponent>(mob, TeamComponent{TeamType::ENEMY});
                    _registry.add_component<DeadComponent>(mob, DeadComponent{false, EntityType::MOB});
                    _registry.add_component<DamageComponent>(mob, DamageComponent{10, static_cast<int>(mob), 0});
                    _registry.add_component<HealthComponent>(mob, HealthComponent{40, true});
                    _registry.add_component<DestroyedComponent>(mob, DestroyedComponent{false, 0});
                    _registry.add_component<SoundComponent>(mob, SoundComponent{{"", EXPLOSION_SOUND, SHOOT_SOUND}, 0});
                    _mobSend._id = mob;

                    switch (int(type)) {
                        case 0:
                            _registry.add_component<TextureComponent>(mob, TextureComponent{ENEMY_1, false});
                            _registry.add_component<PositionComponent>(mob, PositionComponent{x, y, 266.5f / 8, 24});
                            _registry.add_component<HealthComponent>(mob, HealthComponent{40, true});
                            _registry.add_component<AnimationComponent>(mob, AnimationComponent{true, 0, 0.1f, 1, 8, 0, 6});
                            _registry.add_component<ScaleComponent>(mob, ScaleComponent{3, 3});
                            _registry.add_component<ShootableComponent>(mob, ShootableComponent{false, ShootType::NO_SHOOT, static_cast<int>(mob)});
                            _registry.add_component<VelocityComponent>(mob, VelocityComponent{-10 , 0});
                            break;
                        case 1:
                            _registry.add_component<TextureComponent>(mob, TextureComponent{ENEMY_2, false});
                            _registry.add_component<PositionComponent>(mob, PositionComponent{x, y, 264.0f / 8, 22});
                            _registry.add_component<HealthComponent>(mob, HealthComponent{100, true});
                            _registry.add_component<AnimationComponent>(mob, AnimationComponent{true, 0, 0.1f, 1, 8, 0, 6});
                            _registry.add_component<ScaleComponent>(mob, ScaleComponent{3, 3});
                            _registry.add_component<ShootableComponent>(mob, ShootableComponent{true, ShootType::BASIC, static_cast<int>(mob)});
                            _registry.add_component<VelocityComponent>(mob, VelocityComponent{-5 , 0});
                            break;
                        default:
                            break;
                    }
                } else if (type != 3) {
                    _mobSend._id = _entityReusable;
                    switch (int(type)) {
                        case 0:
                            _registry.add_component<TextureComponent>(_entityReusable, TextureComponent{ENEMY_1, false});
                            _registry.add_component<PositionComponent>(_entityReusable, PositionComponent{x, y, 266.5f / 8, 24});
                            _registry.add_component<AnimationComponent>(_entityReusable, AnimationComponent{true, 0, 0.1f, 1, 8, 0, 6});
                            _registry.add_component<HealthComponent>(_entityReusable, HealthComponent{40, true});
                            _registry.add_component<VelocityComponent>(_entityReusable, VelocityComponent{-10 , 0});
                            _registry.add_component<ShootableComponent>(_entityReusable, ShootableComponent{false, ShootType::NO_SHOOT, static_cast<int >(_entityReusable)});
                            _registry.add_component<ScaleComponent>(_entityReusable, ScaleComponent{3, 3});
                            break;
                        case 1:
                            _registry.add_component<TextureComponent>(_entityReusable, TextureComponent{ENEMY_2, false});
                            _registry.add_component<PositionComponent>(_entityReusable, PositionComponent{x, y, 264.0f / 8, 22});
                            _registry.add_component<HealthComponent>(_entityReusable, HealthComponent{100, true});
                            _registry.add_component<AnimationComponent>(_entityReusable, AnimationComponent{true, 0, 0.1f, 1, 8, 0, 6});
                            _registry.add_component<ScaleComponent>(_entityReusable, ScaleComponent{3, 3});
                            _registry.add_component<ShootableComponent>(_entityReusable, ShootableComponent{true, ShootType::BASIC, static_cast<int>(_entityReusable)});
                            _registry.add_component<VelocityComponent>(_entityReusable, VelocityComponent{-5 , 0});

                            break;
                        default:
                            break;
                    }
                    _registry.add_component<DeadComponent>(_entityReusable, DeadComponent{false, EntityType::MOB});
                }
                _entityReusable = 0;
                _registry.indexedParams["mob"] = _mobSend;
            }
        }

    protected:
    private:
        Registry &_registry;
        int _entityReusable = 0;
};

#endif /* !MOBENEMYCLIENT_HPP_ */
