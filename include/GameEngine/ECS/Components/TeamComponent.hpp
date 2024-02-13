/*
** EPITECH PROJECT, 2023
** tek3
** File description:
** TeamComponent
*/

#ifndef TEAMCOMPONENT_HPP_
#define TEAMCOMPONENT_HPP_

#include "GameEngine/GameVariable.hpp"

class TeamComponent {
    public:
        TeamComponent(TeamType team) : _team(team) {};
        ~TeamComponent() = default;
        TeamType _team;

    protected:
    private:
};

#endif /* !TEAMCOMPONENT_HPP_ */
