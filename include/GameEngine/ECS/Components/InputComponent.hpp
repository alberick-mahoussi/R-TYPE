/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** InputComponent
*/

#ifndef INPUTCOMPONENT_HPP_
#define INPUTCOMPONENT_HPP_

class InputComponent {
    public:
        InputComponent(bool controllable) : _controllable(controllable) {};
        ~InputComponent() = default;
        bool _controllable;

    protected:
    private:
};

#endif /* !INPUTCOMPONENT_HPP_ */
