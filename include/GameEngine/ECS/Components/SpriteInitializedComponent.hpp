/*
** EPITECH PROJECT, 2023
** tek3
** File description:
** SpriteInitializedComponent
*/

#ifndef SPRITEINITIALIZEDCOMPONENT_HPP_
#define SPRITEINITIALIZEDCOMPONENT_HPP_

class SpriteInitializedComponent {
    public:
        SpriteInitializedComponent(bool initializedComponent = false) : _initializedComponent(initializedComponent) {};
        ~SpriteInitializedComponent() = default;
        void setInitialized() {
            _initializedComponent = true;
        }
        bool _initializedComponent;

    protected:
    private:
};

#endif /* !SPRITEINITIALIZEDCOMPONENT_HPP_ */
