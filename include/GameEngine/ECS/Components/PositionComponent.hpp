/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** PositionComponent
*/

#ifndef POSITIONCOMPONENT_HPP_
#define POSITIONCOMPONENT_HPP_

class PositionComponent {
    public:
        PositionComponent() = default;
        PositionComponent(double x = 0, double y = 0, double wth = 0, double hgt = 0) : _x(x), _y(y), _wth(wth), _hgt(hgt) {};
        ~PositionComponent() = default;
        void setPos(float x, float y)
        {
            _x = x;
            _y = y;
        }
        void addPos(std::pair<float, float> pos)
        {
            _x += pos.first;
            _y += pos.second;
        }
        double _x;
        double _y;
        double _wth;
        double _hgt;

    protected:
    private:
};

#endif /* !POSITIONCOMPONENT_HPP_ */
