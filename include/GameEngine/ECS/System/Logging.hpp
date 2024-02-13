/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** Logging
*/

#ifndef LOGGING_HPP_
#define LOGGING_HPP_

#include "GameEngine/ECS/Entity/Registry.hpp"

class Logging : public System {
    public:
        Logging(Registry &registry) : _registry(registry) {};
        ~Logging() = default;
        void callSystem() override {
            auto const &positions = _registry.get_components<PositionComponent>();
            auto const &velocities = _registry.get_components<VelocityComponent>();
            for (size_t i = 0; i < positions.size(); ++i) {
                auto const &pos = positions[i];
                // auto const &vel = velocities[i];
                if (pos) {
                    std::cerr << i << ": Position = { " << pos.value()._x << ", " << pos.value()._y << " },\n";
                    //Velocity = { " << vel.value()._x << ", " << vel.value()._y << " }" << std::endl;
                }
            }
        }

    protected:
    private:
        Registry &_registry;
};

#endif /* !LOGGING_HPP_ */
