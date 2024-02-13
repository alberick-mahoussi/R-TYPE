/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** AIComponent
*/

#ifndef AICOMPONENT_HPP_
#define AICOMPONENT_HPP_

class AIComponent {
    public:
        AIComponent(bool serverControl) : _serverControl(serverControl){};
        ~AIComponent() = default;
        bool _serverControl;

    protected:
    private:
};

#endif /* !AICOMPONENT_HPP_ */
