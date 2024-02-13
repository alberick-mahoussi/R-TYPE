/*
** EPITECH PROJECT, 2023
** tek3
** File description:
** ShootableComponent
*/

#ifndef SHOOTABLECOMPONENT_HPP_
#define SHOOTABLECOMPONENT_HPP_

#include "GameEngine/GameVariable.hpp"

class ShootableComponent {
    public:
        ShootableComponent(bool shoot, ShootType type, int playerId) : _shoot(shoot), _type(type), _playerId(playerId) {};
        ~ShootableComponent() = default;
        bool _shoot;
        ShootType _type;
        int _playerId;

    protected:
    private:
};

#endif /* !SHOOTABLECOMPONENT_HPP_ */
