/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** TextureComponent
*/

#ifndef TEXTURECOMPONENT_HPP_
#define TEXTURECOMPONENT_HPP_

#include <iostream>

class TextureComponent {
    public:
        TextureComponent(std::string path) {
            _path = path;
        };
        TextureComponent(std::string path, bool shader = false) {
            _path = path, _shader = shader;
        };
        ~TextureComponent() = default;
        std::string _path;
        bool _shader;

    protected:
    private:
};

#endif /* !TEXTURECOMPONENT_HPP_ */
