/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** WeaponComponent
*/

#ifndef WEAPONCOMPONENT_HPP_
#define WEAPONCOMPONENT_HPP_

class WeaponComponent {
    public:
        WeaponComponent(bool weapon) : _weapon(weapon) {};
        ~WeaponComponent() = default;
        bool _weapon;

    protected:
    private:
};

#endif /* !WEAPONCOMPONENT_HPP_ */
