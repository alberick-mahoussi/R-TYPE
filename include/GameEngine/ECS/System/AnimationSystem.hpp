/*
** EPITECH PROJECT, 2023
** tek3
** File description:
** AnimationSystem
*/

#ifndef ANIMATIONSYSTEM_HPP_
#define ANIMATIONSYSTEM_HPP_

#include "GameEngine/ECS/Entity/Registry.hpp"

class AnimationSystem : public System {
    public:
        AnimationSystem(Registry &registry) : _registry(registry) {};
        ~AnimationSystem();
        void callSystem() {
            // auto const &sceneComp = _registry.get_components<AnimationComponent>();
            // auto &drawableComp = _registry.get_components<DrawableComponent>();
            // for (size_t i = 0; i < sceneComp.size(); ++i) {
            //     auto const &scene = sceneComp[i];
            //     auto &drawable = drawableComp[i];
            // }
        }

    protected:
    private:
        Registry &_registry;
};

#endif /* !ANIMATIONSYSTEM_HPP_ */
