/*
** EPITECH PROJECT, 2023
** tek3
** File description:
** DeadComponent
*/

#ifndef DEADCOMPONENT_HPP_
#define DEADCOMPONENT_HPP_

class DeadComponent {
    public:
        DeadComponent(bool alive, EntityType entityType) : _alive(alive), _entityType(entityType) {};
        ~DeadComponent() = default;
        bool _alive;
        EntityType _entityType;

    protected:
    private:
};

#endif /* !DEADCOMPONENT_HPP_ */
