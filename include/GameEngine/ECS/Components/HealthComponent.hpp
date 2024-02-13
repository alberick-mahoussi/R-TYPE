/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** HealthComponent
*/

#ifndef HEALTHCOMPONENT_HPP_
#define HEALTHCOMPONENT_HPP_

class HealthComponent {
    public:
        HealthComponent(int max_health, bool state) {
            _max_health = max_health;
            _current_health = max_health;
            _state = state;
        };
        ~HealthComponent() = default;
        int _max_health;
        int _current_health;
        bool _state;

    protected:
    private:
};

#endif /* !HEALTHCOMPONENT_HPP_ */
