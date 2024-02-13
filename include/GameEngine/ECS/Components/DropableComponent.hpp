/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** DropableComponent
*/

#ifndef DROPABLECOMPONENT_HPP_
#define DROPABLECOMPONENT_HPP_

class DropableComponent {
    public:
        DropableComponent(bool drop, double x, double y) : _drop(drop), _x(x), _y(y) {};
        ~DropableComponent() = default;
        bool _drop;
        double _x;
        double _y;

    protected:
    private:
};

#endif /* !DROPABLECOMPONENT_HPP_ */
