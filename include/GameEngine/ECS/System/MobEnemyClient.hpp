/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** MobEnemy
*/

#ifndef MOBENEMYCLIENT_HPP_
#define MOBENEMYCLIENT_HPP_

#include "GameEngine/ECS/Entity/Registry.hpp"

class MobEnemyClient : public System {
    public:
        MobEnemyClient(Registry &registry) : _registry(registry) {};
        ~MobEnemyClient();
        void callSystem() {
            Registry::entity_t mob = std::any_cast<mobClass>(_registry.indexedParams["mob"])._id;
            double x = std::any_cast<mobClass>(_registry.indexedParams["mob"])._x;
            double y = std::any_cast<mobClass>(_registry.indexedParams["mob"])._y;
            int type = std::any_cast<mobClass>(_registry.indexedParams["mob"])._type;
            if (type != 3 && x > 0 && y > 0) {
                std::vector<std::string> scenes = {"Play"};
                _registry.add_component<DrawableComponent>(mob, DrawableComponent{true});
                _registry.add_component<SceneComponent>(mob, SceneComponent{scenes});
                _registry.add_component<SpriteInitializedComponent>(mob, SpriteInitializedComponent{false});
                _registry.add_component<TeamComponent>(mob, TeamComponent{TeamType::ENEMY});
                _registry.add_component<DeadComponent>(mob, DeadComponent{false, EntityType::MOB});
                _registry.add_component<DamageComponent>(mob, DamageComponent{10, static_cast<int>(mob), 0});
                _registry.add_component<HealthComponent>(mob, HealthComponent{40, true});
                auto &positionComp = _registry.get_components<HealthComponent>();
                auto const &position = positionComp[int(mob)];
                _registry.add_component<DestroyedComponent>(mob, DestroyedComponent{false, 0});
                _registry.add_component<SoundComponent>(mob, SoundComponent{{"", EXPLOSION_SOUND, SHOOT_SOUND}, 0});

                switch (type) {
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
                std::any storedValue = _registry.indexedParams["mob"];
                mobClass& _mobSend = std::any_cast<mobClass&>(storedValue);
                _mobSend._x = 0;
                _mobSend._y  = 0;
                _mobSend._type = 3;
                _mobSend._id =  0;
                _registry.indexedParams["mob"] = _mobSend;
            }
        }

    protected:
    private:
        Registry &_registry;
        int _entityReusable = 0;
};

#endif /* !MOBENEMY_HPP_ */
