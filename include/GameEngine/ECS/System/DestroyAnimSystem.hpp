/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** DestroyAnimSystem
*/

#ifndef DESTROYANIMSYSTEM_HPP_
#define DESTROYANIMSYSTEM_HPP_

#include "GameEngine/ECS/Entity/Registry.hpp"

class DestroyAnimSystem : public System {
    public:
        DestroyAnimSystem(Registry &registry) : _registry(registry) {
            startTime = std::chrono::high_resolution_clock::now();
            currentTime = std::chrono::high_resolution_clock::now();
        };
        ~DestroyAnimSystem();
        void callSystem() {
            auto const &PositionComp = _registry.get_components<PositionComponent>();
            auto const &ScaleComp = _registry.get_components<ScaleComponent>();
            auto &DestroyedComp = _registry.get_components<DestroyedComponent>();
            auto &DeadComp = _registry.get_components<DeadComponent>();

            currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = currentTime - startTime;
            startTime = currentTime;

            for (size_t i = 0; i < DestroyedComp.size(); i++) {
                auto const &position = PositionComp[i];
                auto &mobs = DeadComp[i];
                auto &destroy = DestroyedComp[i];
                auto const &scale = ScaleComp[i];

                if (destroy && (destroy->_isDestroy == true)) {
                    if (destroy->_time == 0) {
                        _entityReusable = 0;
                        destroy->_isDestroy = false;
                        for (size_t i = 0; i < DeadComp.size(); ++i) {
                            if (mobs && (mobs->_alive == true && mobs->_entityType == EntityType::EXPLOSION)) {
                                _entityReusable = i;
                                break;
                            }
                        }
                        if (_entityReusable == 0) {

                            auto explosion = _registry.spawn_entity();
                            std::vector<std::string> scenes = {"Play"};
                            _registry.add_component<DrawableComponent>(explosion, DrawableComponent{true});
                            _registry.add_component<TextureComponent>(explosion, TextureComponent{EXPLOSION_1, false});
                            _registry.add_component<SceneComponent>(explosion, SceneComponent{scenes});
                            _registry.add_component<SpriteInitializedComponent>(explosion, SpriteInitializedComponent{false});
                            _registry.add_component<DestroyedComponent>(explosion, DestroyedComponent{true, 1});
                            _registry.add_component<PositionComponent>(explosion, PositionComponent{position->_x , position->_y , 196 / 6, 33});
                            _registry.add_component<AnimationComponent>(explosion, AnimationComponent{true, 0, 0.1f, 1, 6, 130, 0});
                            _registry.add_component<ScaleComponent>(explosion, ScaleComponent{3, 3});
                            _registry.add_component<DeadComponent>(explosion, DeadComponent{false, EntityType::EXPLOSION});
                        } else {
                            _registry.add_component<PositionComponent>(_entityReusable, PositionComponent{position->_x , position->_y , 196 / 6, 33});
                            _registry.add_component<DeadComponent>(_entityReusable, DeadComponent{false, EntityType::EXPLOSION});
                            _registry.add_component<DestroyedComponent>(_entityReusable, DestroyedComponent{true, 1});
                        }
                        _entityReusable = 0;
                    } else {
                        destroy->_time -= elapsed.count();
                        if (destroy->_time <= 0) {
                            mobs->_alive = true;
                        }
                    }
                }

            }
        }

    protected:
    private:
        std::chrono::high_resolution_clock::time_point startTime;
        std::chrono::high_resolution_clock::time_point currentTime;
        Registry &_registry;
        int _entityReusable = 0;
};

#endif /* !DESTROYANIMSYSTEM_HPP_ */
