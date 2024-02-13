/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** DestroyedComponent
*/

#ifndef DESTROYEDCOMPONENT_HPP_
#define DESTROYEDCOMPONENT_HPP_

class DestroyedComponent {
    public:
        DestroyedComponent(bool isDestroy, double time) : _isDestroy(isDestroy), _time(time) {};
        ~DestroyedComponent() = default;
        bool _isDestroy;
        double _time;

    protected:
    private:
};

#endif /* !DESTROYEDCOMPONENT_HPP_ */
