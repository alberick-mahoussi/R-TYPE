/*
** EPITECH PROJECT, 2023
** tek3
** File description:
** ScaleComponent
*/

#ifndef SCALECOMPONENT_HPP_
#define SCALECOMPONENT_HPP_

class ScaleComponent {
    public:
        ScaleComponent(double scaleX, double scaleY) : _scaleX(scaleX), _scaleY(scaleY) {};
        ~ScaleComponent() = default;
        double _scaleX;
        double _scaleY;

    protected:
    private:
};

#endif /* !SCALECOMPONENT_HPP_ */
