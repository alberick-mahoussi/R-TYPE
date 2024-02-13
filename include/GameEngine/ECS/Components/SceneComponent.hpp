/*
** EPITECH PROJECT, 2023
** tek3
** File description:
** SceneComponent
*/

#ifndef SCENECOMPONENT_HPP_
#define SCENECOMPONENT_HPP_

#include <iostream>

class SceneComponent {
    public:
        SceneComponent(std::vector<std::string> sceneName) : _sceneName(sceneName) {};
        ~SceneComponent() = default;
        std::vector<std::string> _sceneName;

    protected:
    private:
};

#endif /* !SCENECOMPONENT_HPP_ */
