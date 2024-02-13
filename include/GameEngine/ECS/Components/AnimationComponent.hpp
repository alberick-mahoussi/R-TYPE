/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** AnimationComponent
*/

#ifndef ANIMATIONCOMPONENT_HPP_
#define ANIMATIONCOMPONENT_HPP_

class AnimationComponent {
    public:
        AnimationComponent(bool animed, int currentFrame, double frameTime, int row, int column, int posX, int posY) : _animed(animed),
        _currentFrame(currentFrame), _frameTime(frameTime), _row(row), _column(column), _posX(posX), _posY(posY) {};
        ~AnimationComponent() = default;
        bool _animed;
        int _currentFrame;
        double _frameTime;
        int _column;
        int _row;
        int _posX;
        int _posY;

    protected:
    private:
};

#endif /* !ANIMATIONCOMPONENT_HPP_ */
