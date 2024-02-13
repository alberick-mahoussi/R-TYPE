/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** ItemSystem
*/

#ifndef ITEMSYSTEM_HPP_
#define ITEMSYSTEM_HPP_

#include "GameEngine/ECS/Entity/Registry.hpp"

class ItemSystem : public System {
    public:
        ItemSystem(Registry &registry) : _registry(registry) {
            startTime = std::chrono::high_resolution_clock::now();
            currentTime = std::chrono::high_resolution_clock::now();
        };
        ~ItemSystem();
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
                if (std::any_cast<std::string>(_registry.indexedParams["exec"]) == "server") {
                    if (destroy && (destroy->_isDestroy == true)) {
                        if (destroy->_time <= 0) {
                            int r = std::rand() % 1;
                            if (r == 0) {
                                _entityReusable = 0;
                                for (size_t i = 0; i < DeadComp.size(); ++i) {
                                    if (mobs && (mobs->_alive == true && mobs->_entityType == EntityType::ITEM)) {
                                        _entityReusable = i;
                                        break;
                                    }
                                }
                                std::any storedValue = _registry.indexedParams["item"];
                                itemStruct& _itemSend = std::any_cast<itemStruct&>(storedValue);
                                if (_entityReusable == 0) {
                                    auto item = _registry.spawn_entity();
                                    std::vector<std::string> scenes = {"Play"};
                                    _registry.add_component<TeamComponent>(item, TeamComponent{TeamType::ENEMY});
                                    _registry.add_component<DrawableComponent>(item, DrawableComponent{true});
                                    _registry.add_component<TextureComponent>(item, TextureComponent{BONUS_1, false});
                                    _registry.add_component<SceneComponent>(item, SceneComponent{scenes});
                                    _registry.add_component<SpriteInitializedComponent>(item, SpriteInitializedComponent{false});
                                    _registry.add_component<PositionComponent>(item, PositionComponent{position->_x , position->_y , 144.0f / 6.0f, 18});
                                    _registry.add_component<AnimationComponent>(item, AnimationComponent{true, 0, 0.1f, 1, 6, 157, 35});
                                    _registry.add_component<ScaleComponent>(item, ScaleComponent{3, 3});
                                    _registry.add_component<DeadComponent>(item, DeadComponent{false, EntityType::ITEM});
                                    _registry.add_component<SoundComponent>(item, SoundComponent{{"", BONUS_SOUND}, 0});
                                    _registry.add_component<DestroyedComponent>(item, DestroyedComponent{false, 0});
                                    _registry.add_component<DamageComponent>(item, DamageComponent{0, static_cast<int>(item), 0});
                                    _registry.add_component<HealthComponent>(item, HealthComponent{0, false});
                                    _itemSend._id = item;
                                    _itemSend._x = position->_x;
                                    _itemSend._y = position->_y;
                                } else {
                                    _registry.add_component<PositionComponent>(_entityReusable, PositionComponent{position->_x , position->_y , 144.0f / 6.0f, 18});
                                    _registry.add_component<DeadComponent>(_entityReusable, DeadComponent{false, EntityType::ITEM});
                                    _itemSend._id = _entityReusable;
                                    _itemSend._x = position->_x;
                                    _itemSend._y = position->_y;
                                }
                                _entityReusable = 0;
                                _registry.indexedParams["item"] = _itemSend;
                            }
                            destroy->_isDestroy = false;
                        }
                    }
                } else if (std::any_cast<std::string>(_registry.indexedParams["exec"]) == "client") {
                    if (std::any_cast<itemStruct>(_registry.indexedParams["item"])._id != 0) {
                        int item = std::any_cast<itemStruct>(_registry.indexedParams["item"])._id;
                        double x = std::any_cast<itemStruct>(_registry.indexedParams["item"])._x;
                        double y = std::any_cast<itemStruct>(_registry.indexedParams["item"])._y;
                        std::cout << "item" << std::endl;
                        std::vector<std::string> scenes = {"Play"};
                        _registry.add_component<TeamComponent>(item, TeamComponent{TeamType::ENEMY});
                        _registry.add_component<DrawableComponent>(item, DrawableComponent{true});
                        _registry.add_component<TextureComponent>(item, TextureComponent{BONUS_1, false});
                        _registry.add_component<SceneComponent>(item, SceneComponent{scenes});
                        _registry.add_component<SpriteInitializedComponent>(item, SpriteInitializedComponent{false});
                        _registry.add_component<PositionComponent>(item, PositionComponent{x , y , 144.0f / 6.0f, 18});
                        _registry.add_component<AnimationComponent>(item, AnimationComponent{true, 0, 0.1f, 1, 6, 157, 35});
                        _registry.add_component<ScaleComponent>(item, ScaleComponent{3, 3});
                        _registry.add_component<DeadComponent>(item, DeadComponent{false, EntityType::ITEM});
                        _registry.add_component<SoundComponent>(item, SoundComponent{{"", BONUS_SOUND}, 0});
                        _registry.add_component<DestroyedComponent>(item, DestroyedComponent{false, 0});
                        _registry.add_component<DamageComponent>(item, DamageComponent{0, static_cast<int>(item), 0});
                        _registry.add_component<HealthComponent>(item, HealthComponent{0, false});
                    }
                }
            }
        }
    private:
        std::chrono::high_resolution_clock::time_point startTime;
        std::chrono::high_resolution_clock::time_point currentTime;
        Registry &_registry;
        int _entityReusable = 0;
};

#endif /* !ITEMSYSTEM_HPP_ */
