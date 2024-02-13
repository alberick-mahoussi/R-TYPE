/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** CollisionComponent
*/

#ifndef COLLISIONCOMPONENT_HPP_
#define COLLISIONCOMPONENT_HPP_

class CollisionComponent {
    public:
        CollisionComponent(bool collision) : _collision(collision) {};
        ~CollisionComponent() = default;
        bool _collision;

    protected:
    private:
};

#endif /* !COLLISIONCOMPONENT_HPP_ */
