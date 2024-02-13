/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** Registery
*/

#ifndef REGISTERY_HPP_
#define REGISTERY_HPP_

#include <iostream>
#include <unordered_map>
#include <typeindex>
#include <any>
#include <vector>
#include "GameEngine/ECS/Entity/Entity.hpp"
#include "GameEngine/GameVariable.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>
#include <queue>
#include <functional>

class mobClass {
  public:
    mobClass(int id, double x, double y, int type) : _id(id), _x(x), _y(y), _type(type) {};
    ~mobClass() = default;
    int _id = 0;
    double _x = 0;
    double _y = 0;
    int _type = 0;
};

class weaponClass {
  public:
    weaponClass(int id, int id_player) : _id(id), _idPlayer(id_player) {};
    ~weaponClass() = default;
    int _id;
    int _idPlayer;
};

class enemyShootClass {
  public:
    enemyShootClass(int bullet, int player) : _bullet(bullet), _player(player) {};
    ~enemyShootClass() = default;
    std::vector<int> _idBullet;
    int _bullet;
    std::vector<int> _idPlayer;
    int _player;
};

class entityMoveClass {
  public:
    // entityMoveClass(int entity, int pos_x, int pos_y) : _entity(entity), _posX(pos_x), _posY(pos_y) {};
    entityMoveClass() {};
    ~entityMoveClass() = default;
    std::vector<int> _idEntity;
    std::vector<int> _idPosX;
    std::vector<int> _idPosY;
    // int _entity;
    // int _posX;
    // int _posY;
};

struct playerList{
  std::vector<int> player;
  std::vector<int> ready;
};

class itemStruct {
  public:
    itemStruct(int id, double x, double y) : _id(id), _x(x), _y(y) {};
    ~itemStruct() = default;
    int _id;
    double _x;
    double _y;
};

class System {
    public:
        virtual void callSystem() {
            throw std::runtime_error("Error");
        };
};

class Registry {
    public:
        Registry() {
        register_component<PositionComponent>();
        register_component<VelocityComponent>();
        register_component<DrawableComponent>();
        register_component<InputComponent>();
        register_component<TextComponent>();
        register_component<TextureComponent>();
        register_component<SceneComponent>();
        register_component<SpriteInitializedComponent>();
        register_component<ScaleComponent>();
        register_component<AnimationComponent>();
        register_component<ShootableComponent>();
        register_component<TeamComponent>();
        register_component<DeadComponent>();
        register_component<TextBoxComponent>();
        register_component<DamageComponent>();
        register_component<HealthComponent>();
        register_component<AIComponent>();
        register_component<CollisionComponent>();
        register_component<SoundComponent>();
        register_component<WeaponComponent>();
        register_component<ScoreComponent>();
        register_component<GuiComponent>();
        register_component<DropableComponent>();
        register_component<DestroyedComponent>();

        paramsScene.push_back(std::string("Menu"));
        paramsScene.push_back(int(Control::NONE));
        paramsScene.push_back(std::unordered_map<int, std::string>());
        paramsScene.push_back(std::string("NONE"));
        paramsScene.push_back(int(Control::NONE));
        paramsScene.push_back(std::string("server"));
        paramsScene.push_back(itemStruct(0, 0, 0));
        paramsScene.push_back(mobClass(0, 0, 0, 0));
        paramsScene.push_back(weaponClass(0, 0));
        paramsScene.push_back(int(0));
        paramsScene.push_back(enemyShootClass(0, 0));
        paramsScene.push_back(entityMoveClass());
        paramsScene.push_back(mobClass(0, 0, 0, 0));

        indexedParams["scene"] = paramsScene[0];
        indexedParams["input"] = paramsScene[1];
        indexedParams["textBox"] = paramsScene[2];
        indexedParams["command"] = paramsScene[3];
        indexedParams["control"] = paramsScene[4];
        indexedParams["exec"] = paramsScene[5];
        indexedParams["item"] = paramsScene[6];
        indexedParams["mob"] = paramsScene[7];
        indexedParams["weapon"] = paramsScene[8];
        indexedParams["playerController"] = paramsScene[9];
        indexedParams["enemyShoot"] = paramsScene[10];
        indexedParams["entityMove"] = paramsScene[11];
        indexedParams["bullet"] = paramsScene[12];
        };
        ~Registry() = default;
        using entity_t = size_t;
        template <class Component>
        sparse_array<Component> &register_component() {
            std::type_index idx(typeid(Component));
            _components_arrays.insert(std::pair<std::type_index, std::any>(idx, sparse_array<Component>()));
            return std::any_cast<sparse_array<Component>&>(_components_arrays[idx]);
        }
        template <class Component>
        sparse_array<Component> & get_components() {
            std::type_index const idx(typeid(Component));
            return std::any_cast<sparse_array<Component>&>(_components_arrays[idx]);
        }
        template <typename Component, typename... Params>
        typename sparse_array<Component>::reference_type emplace_component(entity_t const &entity, Params &&...p)
        {
            auto &component_array = get_components<Component>();
            auto &new_component = component_array.emplace_at(entity, std::forward<Params>(p)...);
            return new_component;
        }
        template <class Component>
        void add_component(entity_t const & entity, Component component) {
            int x = 500;
            std::type_index const idx(typeid(Component));
            sparse_array<Component> & array = std::any_cast<sparse_array<Component>&>(_components_arrays[idx]);
            x = (entity >= x) ? x + 100 : x;
            for (size_t i = array.size(); i <= x; ++i) {
                array.insert(std::optional<Component>(std::nullopt));
            }
            array[entity].emplace(component);
        }
        template <class Component>
        void remove_component(entity_t const & from) {
            std::type_index const idx(typeid(Component));
            sparse_array<Component> & array = std::any_cast<sparse_array<Component>&>(_components_arrays[idx]);
            array.erase(from);
        }
        entity_t spawn_entity()
        {
            int id = entity_counter;
            entities.push_back(++entity_counter);
            return id;
        }
        entity_t entity_from_index(std::size_t idx)
        {
            if (idx < entities.size())
            {
                return entities[idx];
            }
            else
            {
                throw std::out_of_range("Entity index out of range 7");
            }
        }
        template <class Component>
        void kill_entity(entity_t const &e)
        {
            std::type_index const idx(typeid(Component));
            sparse_array<Component> & array = std::any_cast<sparse_array<Component>&>(_components_arrays[idx]);
            array.erase(e);
        }
        template <class SystemT>
        void register_system(SystemT *system, std::type_index const idx) {
            _systems.insert(std::pair<std::type_index, SystemT*>(idx, system));
            std::function<void (Registry &, std::vector<std::any>)> call_function = [](Registry & registry, std::vector<std::any> params) {
                return registry.call_system<SystemT>();
            };
            _call_functions.insert(std::pair<std::type_index, std::function<void (Registry &, std::vector<std::any>)>>(idx, call_function));
        }
        template <class SystemT>
        void call_system() {
            std::type_index const idx(typeid(SystemT));
            SystemT *sys = (SystemT*) _systems[idx];
            sys->callSystem();

        }
        // void call_system(std::type_index const tidx, std::vector<std::any> params) {
        //     std::function<void (Registry &, std::vector<std::any>)> & func = _call_functions[tidx];
        //     func(*this, params);
        // }

        // sf::RenderWindow &getDisplayWindow() {
        //   return _window;
        // }
        void add_system(System* system) {
            systems.push_back(system);
        }
        void remove_system(System* system) {
            auto it = std::find(systems.begin(), systems.end(), system);
            if (it != systems.end()) {
                systems.erase(it);
                delete system;
            }
        }
        std::string getScene() {
            return _scene;
        }
        void setScene(std::string scene) {
            _scene = scene;
        }
        std::unordered_map<std::type_index, System*> _systems;
        std::vector<System*> systems;
        Control _direction = Control::NONE;
        std::map<std::string, std::any> indexedParams;
        playerList _list;

    private:
        std::unordered_map<std::type_index, std::any> _components_arrays;
        std::unordered_map<std::type_index, std::function<void (Registry &, std::vector<std::any>)>> _call_functions;
        std::vector<entity_t> entities;
        entity_t entity_counter = 0;
        std::vector<std::function<void(Registry &, entity_t const &)>> erase_functions;
        std::string _scene = "Menu";
        std::vector<std::any> paramsScene;
};

#endif /* !REGISTERY_HPP_ */
