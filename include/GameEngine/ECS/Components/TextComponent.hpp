/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** TextComponent
*/

#ifndef TEXTCOMPONENT_HPP_
#define TEXTCOMPONENT_HPP_

#include <iostream>

class TextComponent {
    public:
        TextComponent(std::string word, std::string color, int size) : _word(word), _color(color), _size(size) {};
        ~TextComponent() = default;
        std::string _word;
        std::string _color;
        int _size;

    protected:
    private:
};

#endif /* !TEXTCOMPONENT_HPP_ */
