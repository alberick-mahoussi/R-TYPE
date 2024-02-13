/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** GuiSystem
*/

#ifndef GUISYSTEM_HPP_
#define GUISYSTEM_HPP_

#include "GameEngine/ECS/Entity/Registry.hpp"

class GuiSystem : public System {
    public:
        GuiSystem(Registry &registry) : _registry(registry) {};
        ~GuiSystem();
        void callSystem() {
            auto const &GuiComp = _registry.get_components<GuiComponent>();
            auto const &ShootableComp = _registry.get_components<ShootableComponent>();
            auto &TextComp = _registry.get_components<TextComponent>();
            auto const &ScoreComp = _registry.get_components<ScoreComponent>();
            auto const &HealthComp = _registry.get_components<HealthComponent>();
            auto const &DamageComp = _registry.get_components<DamageComponent>();
            
            for (size_t i = 0; i < ShootableComp.size(); ++i) {
                auto const &Score = ScoreComp[i];
                auto const &Health = HealthComp[i];
                auto const &Damage = DamageComp[i];

                if (Score && Health && Damage) {

                    for (size_t i = 0; i < GuiComp.size(); ++i) {
                        auto const &Gui = GuiComp[i];
                        auto &Text = TextComp[i];
                        if (Text && Gui) {
                            if (Gui->_info == "Health") {
                                Text->_word = "Health: " + std::to_string(Health->_current_health);
                            } else if (Gui->_info == "Attack") {
                                Text->_word = "Attack: " + std::to_string(Damage->_damage);
                            } else if (Gui->_info == "Score") {
                                Text->_word = "Score: " + std::to_string(Score->_score);
                            }

                        }
                    }
                }
            }
        }

    protected:
    private:
        Registry &_registry;
};

#endif /* !GUISYSTEM_HPP_ */
