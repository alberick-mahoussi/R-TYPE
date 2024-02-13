/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** VelocityComponent
*/

#ifndef VELOCITYCOMPONENT_HPP_
#define VELOCITYCOMPONENT_HPP_

class VelocityComponent {
    public:
    VelocityComponent() = default;
        VelocityComponent(double x = 0, double y = 0) : _x(x), _y(y) {};
        ~VelocityComponent() = default;
        void setVelocity(std::pair<float, float> velocity)
        {
            _x = velocity.first;
            _y = velocity.second;
        }
        void addVelocity(std::pair<float, float> velocity)
        {
            _x += velocity.first;
            _y += velocity.second;
        }
        double _x;
        double _y;

    protected:
    private:
};

#endif /* !VELOCITYCOMPONENT_HPP_ */
