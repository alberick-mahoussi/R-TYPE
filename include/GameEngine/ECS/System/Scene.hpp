/*
** EPITECH PROJECT, 2023
** tek3
** File description:
** Scene
*/

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include "GameEngine/ECS/Entity/Registry.hpp"
#include "Network/network.hpp"
#include "Network/Serialise.hpp"
#include "queue"
#include <iostream>

class Scene : public System {
    public:
        Scene(Registry &registry) : _registry(registry) {};
        ~Scene();
        /// @brief function of sending first message to client to start game and load communication
        void init_communication();
        /// @brief function of sending packets to server with network tools
        void Receive_Data()
        {
            try {
            netwk->async_receive(buffer, std::bind(&Scene::HandleRequest, this, std::placeholders::_1, std::placeholders::_2));
            } catch (const std::exception &e) {
                std::cerr << "An exception occurred while receiving data: " << e.what() << std::endl;
            } catch (...) {
                std::cerr << "An unknown exception occurred while receiving data." << std::endl;
            }
        }
        void HandleRequest(asio::error_code const &error, std::size_t Bytes)
        {
            int protocole  = (int)Message_header::getId(buffer);
            // std:: cout << protocole << std::endl;
            if (protocole == 2) {
                update_player_position n = serializable_system<update_player_position>::deserialize(Message_header::extractMessageWithoutId(buffer));
                if (n.id_enitity != 0) {
                    auto &positionComp = _registry.get_components<PositionComponent>();
                    auto const &velocityComp = _registry.get_components<VelocityComponent>();
                    auto &position = positionComp[n.id_enitity];
                    position->_x = n.pos_x;
                    position->_y = n.pos_y;
                }
            } else if (protocole == 6) {
                players_states states = serializable_system<players_states>::deserialize(Message_header::extractMessageWithoutId(buffer));
                for (int i = 0; i < 4; i++) {
                std::cout << states.names[i] << std::endl;
                if (states.names[i][0] == 0)
                    _registry.add_component<TextComponent>(_registry._list.player[i], TextComponent{"Waiting...", "white", 40});
                else
                    _registry.add_component<TextComponent>(_registry._list.player[i], TextComponent{states.names[i], "white", 40});
                if (states.states_player[i] == 0)
                    _registry.add_component<TextComponent>(_registry._list.ready[i], TextComponent{"Not ready", "white", 40});
                else
                    _registry.add_component<TextComponent>(_registry._list.ready[i], TextComponent{"Ready", "white", 40});
                }
            } else if (protocole == 7) {
                std::vector<std::string> scenes = {"Play"};
                info_all_player con = serializable_system<info_all_player>::deserialize(Message_header::extractMessageWithoutId(buffer));
                std::cout << "id entity player " << con.id_enitity << std::endl;
                id_entity = con.id_enitity;
                for (int i = 0; i != 10; i++) {
                    if (con.id_enitity_players[i] != 0) {
                        _registry.add_component<PositionComponent>(con.id_enitity_players[i], PositionComponent{50, 50, 166 / 5, 86 / 5});
                        _registry.add_component<VelocityComponent>(con.id_enitity_players[i], VelocityComponent{50, 50});
                        _registry.add_component<DrawableComponent>(con.id_enitity_players[i], DrawableComponent{true});
                        _registry.add_component<SpriteInitializedComponent>(con.id_enitity_players[i], SpriteInitializedComponent{false});
                        _registry.add_component<TextureComponent>(con.id_enitity_players[i], TextureComponent{SPACESHIP, false});
                        _registry.add_component<SceneComponent>(con.id_enitity_players[i], SceneComponent{scenes});
                        _registry.add_component<ScaleComponent>(con.id_enitity_players[i], ScaleComponent{4, 4});
                        _registry.add_component<AnimationComponent>(con.id_enitity_players[i], AnimationComponent{true, 0, 0.1f, 5, 5, 0, 0});
                        _registry.add_component<TeamComponent>(con.id_enitity_players[i], TeamComponent{TeamType::ALLY});
                        _registry.add_component<HealthComponent>(con.id_enitity_players[i], HealthComponent{100, true});
                        _registry.add_component<DeadComponent>(con.id_enitity_players[i], DeadComponent{false, EntityType::PLAYER});
                        _registry.add_component<DamageComponent>(con.id_enitity_players[i], DamageComponent{10, static_cast<int>(con.id_enitity_players[i]), 0});
                        _registry.add_component<DestroyedComponent>(con.id_enitity_players[i], DestroyedComponent{false, 0});
                        _registry.add_component<SoundComponent>(con.id_enitity_players[i], SoundComponent{{"", SHOOT_SOUND, PLAYER_DEATH_SOUND}, 0});
                        _registry.add_component<WeaponComponent>(con.id_enitity_players[i], WeaponComponent{false});
                        _registry.add_component<ShootableComponent>(con.id_enitity_players[i], ShootableComponent{true, ShootType::BASIC, int(con.id_enitity_players[i])});
                    }
                }
                _registry.add_component<PositionComponent>(con.id_enitity, PositionComponent{50, 50, 166 / 5, 86 / 5});
                _registry.add_component<VelocityComponent>(con.id_enitity, VelocityComponent{50, 50});
                _registry.add_component<DrawableComponent>(con.id_enitity, DrawableComponent{true});
                _registry.add_component<SpriteInitializedComponent>(con.id_enitity, SpriteInitializedComponent{false});
                _registry.add_component<TextureComponent>(con.id_enitity, TextureComponent{SPACESHIP, false});
                _registry.add_component<SceneComponent>(con.id_enitity, SceneComponent{scenes});
                _registry.add_component<ScaleComponent>(con.id_enitity, ScaleComponent{4, 4});
                _registry.add_component<AnimationComponent>(con.id_enitity, AnimationComponent{true, 0, 0.1f, 5, 5, 0, 0});
                _registry.add_component<InputComponent>(con.id_enitity, InputComponent{true});
                _registry.add_component<ShootableComponent>(con.id_enitity, ShootableComponent{true, ShootType::BASIC, int(con.id_enitity)});
                _registry.add_component<TeamComponent>(con.id_enitity, TeamComponent{TeamType::ALLY});
                _registry.add_component<HealthComponent>(con.id_enitity, HealthComponent{100, true});
                _registry.add_component<DeadComponent>(con.id_enitity, DeadComponent{false, EntityType::PLAYER});
                _registry.add_component<ScoreComponent>(con.id_enitity, ScoreComponent{});
                _registry.add_component<DamageComponent>(con.id_enitity, DamageComponent{10, int(con.id_enitity), 0});
                _registry.add_component<DestroyedComponent>(con.id_enitity, DestroyedComponent{false, 0});
                _registry.add_component<SoundComponent>(con.id_enitity, SoundComponent{{"", SHOOT_SOUND, PLAYER_DEATH_SOUND}, 0});
                _registry.add_component<WeaponComponent>(con.id_enitity, WeaponComponent{false});
                // _registry.indexedParams["playerController"] = int(con.id_enitity);
                _registry.setScene("Play");
            } else if (protocole == 3) {
                new_allyBullet bullet = serializable_system<new_allyBullet>::deserialize(Message_header::extractMessageWithoutId(buffer));
                std::any storedValue = _registry.indexedParams["bullet"];
                mobClass& _bulletSend = std::any_cast<mobClass&>(storedValue);
                _bulletSend._x = bullet.pos_x;
                _bulletSend._y  = bullet.pos_y;
                _bulletSend._type = bullet.type;
                _bulletSend._id = bullet.id;
                _registry.indexedParams["bullet"] = _bulletSend;
                _registry.indexedParams["playerController"] = int(bullet.idPlayer);
                int mob = std::any_cast<mobClass>(_registry.indexedParams["bullet"])._id;
                double x = std::any_cast<mobClass>(_registry.indexedParams["bullet"])._x;
                double y = std::any_cast<mobClass>(_registry.indexedParams["bullet"])._y;
                int type = std::any_cast<mobClass>(_registry.indexedParams["bullet"])._type;
            } else if (protocole == 8) {
                new_ennemy enemy = serializable_system<new_ennemy>::deserialize(Message_header::extractMessageWithoutId(buffer));
                std::any storedValue = _registry.indexedParams["mob"];
                mobClass& _mobSend = std::any_cast<mobClass&>(storedValue);
                _mobSend._x = enemy.pos_x;
                _mobSend._y  = enemy.pos_y;
                _mobSend._type = enemy.type;
                _mobSend._id = enemy.id;
                _registry.indexedParams["mob"] = _mobSend;
            } else if (protocole == 9) {
                new_ennemy_bullet bullet = serializable_system<new_ennemy_bullet>::deserialize(Message_header::extractMessageWithoutId(buffer));
                std::any storedValue = _registry.indexedParams["enemyShoot"];
                enemyShootClass& _bulletSend = std::any_cast<enemyShootClass&>(storedValue);
                _bulletSend._bullet = bullet._idBullet;
                _bulletSend._player = bullet._idPlayer;
                _registry.indexedParams["enemyShoot"] = _bulletSend;
            } else if (protocole == 16) {
                update_player_health player_health = serializable_system<update_player_health>::deserialize(Message_header::extractMessageWithoutId(buffer));
                std::cout << player_health.id_enitity << " HEALTH: " << player_health.health << std::endl;
                auto &health = _registry.get_components<HealthComponent>();
                auto &new_player_health = health[player_health.id_enitity];
                new_player_health->_current_health = player_health.health;
            } else if (protocole == 18 || protocole == 21) {
                _registry.indexedParams["command"] = std::string("close");
            } else if (protocole == 22) {
                new_item item = serializable_system<new_item>::deserialize(Message_header::extractMessageWithoutId(buffer));
                std::any storedValue = _registry.indexedParams["item"];
                itemStruct& _itemSend = std::any_cast<itemStruct&>(storedValue);
                _itemSend._id = item.id;
                _itemSend._x = item.pos_x;
                _itemSend._y = item.pos_y;
                _registry.indexedParams["item"] = _itemSend;
            }
            packet_receive.push(buffer);
            Receive_Data();
        }
        /// @brief function of send packet to server with network tools
        void Send_Data()
        {
            try {
            while (!packet_sending.empty()) {
                std::vector<u_int8_t> msg = packet_sending.front();
                packet_sending.pop();
                netwk->send(msg);
            }
            } catch (const std::exception &e) {
                std::cerr << "An exception occurred while sending data: " << e.what() << std::endl;
            } catch (...) {
                std::cerr << "An unknown exception occurred while sending data." << std::endl;
            }
        }
        /// @brief function for run the context for asychrone process
        void run_context() {
        io_context.run();
        }
        /// @brief function for adding any struct to queue of msg to send server
        /// @param id(enum) type of message struct
        /// @param T struct message whom will sending
        template <class T>
        void add_sending(u_int8_t id, const T &msg)
        {
        packet_sending.push(Message_header::HeaderSerialize<T>(id, msg));
        }
        /// @brief set server information for connection;
        void SetServerInformation()
        {
        netwk->setEndpoint(ip, std::stoi(port));
        }
        /// @brief  Set info server and try to connect server
        void ConnectToServer()
        {
        SetServerInformation();
        New_player_message();
        }
        /// @brief Send message of connection to server
        void New_player_message()
        {
        msg_string new_player_message;
        strcpy(new_player_message.data, name.c_str());
        netwk->send(NEW_CONNECTION, new_player_message);
        }
        /// @brief  Send message of Deconnexion to server
        void Disconnect_server()
        {
        std::cout << "her disconnected\n";
        disconnection deconnect(0);
        netwk->send(DISCONNECTION, deconnect);
        }
        void Shoot()
        {
            player_shoot shoot(id);
            netwk->send(SHOOT_PLAYER, shoot);
        }
        void MoveUp()
        {
        player_move move(up);
        netwk->send(MOVE_PLAYER, move);
        }
        void MoveLeft()
        {
        player_move move(left);
        netwk->send(MOVE_PLAYER, move);
        }
        void MoverRight()
        {
        player_move move(right);
        netwk->send(MOVE_PLAYER, move);
        }
        void MoveDown()
        {
        player_move move(down);
        netwk->send(MOVE_PLAYER, move);
        }
        void Move_Shoot(int action)
        {
            switch (action) {
            case 1:
            MoveUp();
            break;
            case 2:
            MoveDown();
            break;
            case 3:
            MoveLeft();
            break;
            case 4:
            MoverRight();
            break;
            case 5:
            Shoot();
            break;
            }
        }
        void ReadyPlay()
        {
        player_ready_to_game player(0);
        netwk->send(READY_PLAYER, player);
        }
        void Killplayer(int id);
        void callSystem() {
            auto const &sceneComp = _registry.get_components<SceneComponent>();
            auto &drawableComp = _registry.get_components<DrawableComponent>();
            auto &bulletComp = _registry.get_components<DeadComponent>();

            if (_registry.getScene() == "WaitingScreen") {
                if (std::any_cast<std::string>(_registry.indexedParams["command"]) == "ready") {
                    ReadyPlay();
                    _registry.indexedParams["command"] = std::string("NONE");
                }
            }
            if (_registry.getScene() == "LoginScreen") {
                if (std::any_cast<std::string>(_registry.indexedParams["command"]) == "disconnect") {
                    Disconnect_server();
                    _registry.indexedParams["command"] = std::string("NONE");
                }
                if (std::any_cast<std::string>(_registry.indexedParams["command"]) == "connection") {
                    _registry.indexedParams["command"] = std::string("NONE");
                    _registry.setScene("WaitingScreen");
                    std::unordered_map<int, std::string> &storedMap = std::any_cast<std::unordered_map<int, std::string>&>(_registry.indexedParams["textBox"]);
                    int port = (storedMap[3].empty()) ? 8080 : stoi(storedMap[3]);
                    std::string ip = (storedMap[2].empty()) ? "127.0.0.1" : storedMap[2];
                    std::cout << ip << std::endl;
                    std::string input = (storedMap[1].empty()) ? "player" : storedMap[1];
                    netwk = std::make_shared<network>(io_context, port, ip);
                    Receive_Data();
                    if (!_thread.joinable())
                        _thread = std::thread(&Scene::run_context, this);
                    msg_string ms;
                    strcpy(ms.data, input.c_str());
                    netwk->send(NEW_CONNECTION, ms);
                    memset(ms.data, 0, sizeof(ms.data));
                }
            }
            if (_registry.getScene() == "Play") {
                if (std::any_cast<int>(_registry.indexedParams["input"]) != int(Control::NONE)) {
                    Move_Shoot(std::any_cast<int>(_registry.indexedParams["input"]));
                    _registry.indexedParams["input"] = int(Control::NONE);
                }
            }
            // if (_thread.joinable()) {
            //     try {
            //         io_context.stop();
            //         _thread.join();
            //     } catch (const std::exception &e) {
            //         std::cerr << "An exception occurred during IO context stop or thread join: " << e.what() << std::endl;
            //     } catch (...) {
            //         std::cerr << "An unknown exception occurred during IO context stop or thread join." << std::endl;
            //     }
            // }
            for (size_t i = 0; i < sceneComp.size(); ++i) {
                auto const &scene = sceneComp[i];
                auto &dead = bulletComp[i];
                auto &drawable = drawableComp[i];
                if (scene) {
                    for (int i = 0; i != scene->_sceneName.size(); i++) {
                        if ((_registry.getScene() == "Menu")) {
                            if (scene->_sceneName[i] == "Menu" && drawable->_draw == false) {
                                drawable->_draw = true;
                            }
                            if (scene->_sceneName[i] == "Menu" && drawable->_draw == true)
                                break;
                            if (drawable && (drawable->_draw == true && scene->_sceneName[i] != "Menu")) {
                                drawable->_draw = false;
                            }
                        } else if ((_registry.getScene() == "LoginScreen")) {

                            if (scene->_sceneName[i] == "LoginScreen" && drawable->_draw == false) {
                                drawable->_draw = true;
                            }
                            if (scene->_sceneName[i] == "LoginScreen" && drawable->_draw == true)
                                break;
                            if (drawable && (drawable->_draw == true && scene->_sceneName[i] != "LoginScreen")) {
                                drawable->_draw = false;
                            }
                        } else if ((_registry.getScene() == "WaitingScreen")) {
                            if (scene->_sceneName[i] == "WaitingScreen" && drawable->_draw == false) {
                                drawable->_draw = true;
                            }
                            if (scene->_sceneName[i] == "WaitingScreen" && drawable->_draw == true)
                                break;
                            if (drawable && (drawable->_draw == true && scene->_sceneName[i] != "WaitingScreen")) {
                                drawable->_draw = false;
                            }
                        } else if ((_registry.getScene() == "Play")) {
                            if (scene->_sceneName[i] == "Play" && drawable->_draw == false) {
                                drawable->_draw = true;
                                if (dead && (dead->_alive == true))
                                    drawable->_draw = false;
                            }
                            if (scene->_sceneName[i] == "Play" && drawable->_draw == true) {
                                if (dead && (dead->_alive == true))
                                    drawable->_draw = false;
                                break;
                            }
                            if (drawable && (scene->_sceneName[i] != "Play"))
                                drawable->_draw = false;
                        }
                    }
                }
            }
        }

    protected:
    private:
        std::shared_ptr<network> netwk;
        Registry &_registry;
        /// @brief  attribu for communication serer
        asio::io_context io_context;
        std::vector<uint8_t> buffer;
        std::queue<std::vector<uint8_t>> packet_receive;
        std::queue<std::vector<uint8_t>> packet_sending;
        int id_entity = 0;
        std::thread _thread;
        std::string ip;
        std::string port;
        std::string name;
        int id;
};

#endif /* !SCENE_HPP_ */
