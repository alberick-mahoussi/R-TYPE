/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** TextBoxSystem
*/

#ifndef TEXTBOXSYSTEM_HPP_
#define TEXTBOXSYSTEM_HPP_

#include "GameEngine/ECS/Entity/Registry.hpp"

class TextBoxSystem : public System {
    public:
        TextBoxSystem(Registry &registry) : _registry(registry) {};
        ~TextBoxSystem();
        void callSystem() {
            auto const &TextBoxComp = _registry.get_components<TextBoxComponent>();
            auto &TextComp = _registry.get_components<TextComponent>();
            std::unordered_map<int, std::string> &storedMap = std::any_cast<std::unordered_map<int, std::string>&>(_registry.indexedParams["textBox"]);
            for (size_t i = 0; i < TextBoxComp.size(); i++) {
                auto &textBox = TextBoxComp[i];
                auto &text = TextComp[i];
                if (textBox) {
                    if (!storedMap[textBox->_id].empty()) {
                        text->_word = storedMap[textBox->_id];
                    } else {
                        text->_word = "..........";
                    }
                }
            }
        }

    protected:
    private:
        Registry &_registry;
};

#endif /* !TEXTBOXSYSTEM_HPP_ */
