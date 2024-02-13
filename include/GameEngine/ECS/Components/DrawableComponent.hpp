/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** DrawableComponent
*/

#ifndef DRAWABLECOMPONENT_HPP_
#define DRAWABLECOMPONENT_HPP_

class DrawableComponent {
    public:
        DrawableComponent(bool draw) {
            _draw = draw;
        };
        ~DrawableComponent() = default;
        void setDraw() {
            _draw = _draw ? false : true;
        };
        bool _draw = false;

    protected:
    private:
};

#endif /* !DRAWABLECOMPONENT_HPP_ */
