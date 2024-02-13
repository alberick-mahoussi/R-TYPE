/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** SoundComponent
*/

#ifndef SOUNDCOMPONENT_HPP_
#define SOUNDCOMPONENT_HPP_

#include <iostream>

class SoundComponent {
    public:
        SoundComponent(std::vector<std::string> path, int index) : _path(path), _index(index) {
            _path = path;
        };
        ~SoundComponent() {};
        std::vector<std::string> _path;
        int _index;

    protected:
    private:
};

#endif /* !SOUNDCOMPONENT_HPP_ */
