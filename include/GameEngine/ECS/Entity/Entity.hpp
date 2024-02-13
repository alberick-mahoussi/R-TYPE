/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <vector>
#include <stdexcept>
#include "GameEngine/ECS/Components/PositionComponent.hpp"
#include "GameEngine/ECS/Components/VelocityComponent.hpp"
#include "GameEngine/ECS/Components/DrawableComponent.hpp"
#include "GameEngine/ECS/Components/InputComponent.hpp"
#include "GameEngine/ECS/Components/TextComponent.hpp"
#include "GameEngine/ECS/Components/TextureComponent.hpp"
#include "GameEngine/ECS/Components/SceneComponent.hpp"
#include "GameEngine/ECS/Components/SpriteInitializedComponent.hpp"
#include "GameEngine/ECS/Components/AnimationComponent.hpp"
#include "GameEngine/ECS/Components/ScaleComponent.hpp"
#include "GameEngine/ECS/Components/ShootableComponent.hpp"
#include "GameEngine/ECS/Components/TeamComponent.hpp"
#include "GameEngine/ECS/Components/DeadComponent.hpp"
#include "GameEngine/ECS/Components/TextBoxComponent.hpp"
#include "GameEngine/ECS/Components/DamageComponent.hpp"
#include "GameEngine/ECS/Components/HealthComponent.hpp"
#include "GameEngine/ECS/Components/AIComponent.hpp"
#include "GameEngine/ECS/Components/CollisionComponent.hpp"
#include "GameEngine/ECS/Components/SoundComponent.hpp"
#include "GameEngine/ECS/Components/WeaponComponent.hpp"
#include "GameEngine/ECS/Components/ScoreComponent.hpp"
#include "GameEngine/ECS/Components/GuiComponent.hpp"
#include "GameEngine/ECS/Components/DropableComponent.hpp"
#include "GameEngine/ECS/Components/DestroyedComponent.hpp"

template <typename Component>

class sparse_array {
    public:
        using value_type = std::optional<Component>;
        using reference_type = value_type &;
        using const_reference_type = value_type const &;
        using container_t = std ::vector<value_type>;
        using size_type = typename container_t ::size_type;
        using iterator = typename container_t ::iterator;
        using const_iterator = typename container_t ::const_iterator;

    public:
        sparse_array() {};
        sparse_array(sparse_array const &) {};
        sparse_array(sparse_array &&) noexcept {};
        ~sparse_array() {};
        sparse_array &operator=(sparse_array const &);
        sparse_array &operator=(sparse_array &&) noexcept;
        reference_type operator[](size_t idx) {
            if (idx >= _data.size()) {
                throw std::out_of_range("Index out of range 1");
            }
            return _data[idx];
        };
        const_reference_type operator[](size_t idx) const {
            if (idx >= _data.size()) {
                throw std::out_of_range("Index out of range 2");
            }
            return _data[idx];
        };
        iterator begin() {
           return _data.begin();
        };
        const_iterator begin() const {
            return _data.begin();
        };
        const_iterator cbegin() const{
            return _data.cbegin();
        };
        iterator end() {
            return _data.end();
        };
        const_iterator end() const {
            return _data.end();
        };
        const_iterator cend() const {
            return _data.cend();
        };
        size_type size() const {
            return _data.size();
        };
        // template <typename... Args>
        // reference_type insert(Args&&... args) {
        //     _data.emplace_back(std::forward<Args>(args)...);
        //     return _data.back();
        // }
        reference_type insert(std::optional<Component> const &component) {
            _data.push_back(component);
            return _data[_data.size() - 1];
        };
        reference_type insert_at(size_type pos, Component const &component) {
            if (pos > _data.size()) {
                throw std::out_of_range("Index out of range 3");
            }
            _data.insert(_data.begin() + pos, component);
            return _data[pos];
        };
        reference_type insert_at(size_type pos, Component &&component) {
            if (pos > _data.size()) {
                throw std::out_of_range("Index out of range 4 ");
            }
            _data.insert(_data.begin() + pos, std::move(component));
            return _data[pos];
        };
        template <class... Params>
        reference_type emplace_at(size_type pos, Params &&... params) {
            if (pos > _data.size()) {
                throw std::out_of_range("Index out of range 5");
            }
            _data.emplace(_data.begin() + pos, std::forward<Params>(params)...);
            return _data[pos];
        };
        void erase(size_type pos) {
            if (pos >= _data.size()) {
                throw std::out_of_range("Index out of range 6");
            }
            _data.erase(_data.begin() + pos);
        };
        size_type get_index(value_type const &component) const {
            for (size_type i = 0; i < _data.size(); ++i) {
                if (&_data[i] == &component) {
                    return i;
                }
            }
            throw std::runtime_error("Component not found");
        };
        private :
        container_t _data;
};

#endif /* !ENTITY_HPP_ */
