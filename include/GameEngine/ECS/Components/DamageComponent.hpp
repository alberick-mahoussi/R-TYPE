/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** DamageComponent
*/

#ifndef DAMAGECOMPONENT_HPP_
#define DAMAGECOMPONENT_HPP_

class DamageComponent {
    public:
        DamageComponent(int damage, int playerId, int bonus) : _damage(damage), _playerId(playerId), _bonus(bonus) {};
        ~DamageComponent() = default;
        int _damage;
        int _bonus;
        int _playerId;

    protected:
    private:
};

#endif /* !DAMAGECOMPONENT_HPP_ */
