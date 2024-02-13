/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** GuiComponent
*/

#ifndef GUICOMPONENT_HPP_
#define GUICOMPONENT_HPP_

#include <iostream>

class GuiComponent {
    public:
        GuiComponent(std::string info) : _info(info) {};
        ~GuiComponent() = default;
        std::string _info;

    protected:
    private:
};

#endif /* !GUICOMPONENT_HPP_ */
