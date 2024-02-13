/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** Component
*/

#ifndef COMPONENT_HPP_
    #define COMPONENT_HPP_
    
class Component {
    public:
        Component();
        ~Component();

    protected:
    private:
};

struct PlayerID {
    int id;
    PlayerID(const int &player_id) : id(player_id) {}
};

#endif /* !COMPONENT_HPP_ */
