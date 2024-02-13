/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** Server
*/

#ifndef SERVER_HPP_
    #define SERVER_HPP_
    #include <iostream>
    #include <queue>
    #include <unordered_set>
    #include <any>
    #include <optional>
    #include <map>
    #include "GameEngine/ECS/Entity/Registry.hpp"
    #include "GameEngine/ECS/System/Logging.hpp"
    #include "GameEngine/ECS/System/Render.hpp"
    #include "GameEngine/ECS/System/Scene.hpp"
    #include "GameEngine/ECS/System/MouvementSystem.hpp"
    #include "GameEngine/ECS/System/ShootSystem.hpp"
    #include "GameEngine/ECS/System/TextBoxSystem.hpp"
    #include "GameEngine/ECS/System/MobEnemy.hpp"
    #include "GameEngine/ECS/System/GuiSystem.hpp"
    #include "GameEngine/ECS/System/CollisionSystem.hpp"
    #include "GameEngine/ECS/System/SoundSystem.hpp"
    #include "GameEngine/ECS/System/DestroyAnimSystem.hpp"
    #include "GameEngine/ECS/System/ItemSystem.hpp"
    #include "GameEngine/ECS/System/GameOverSystem.hpp"
    #include "GameEngine/ECS/System/WeaponSystem.hpp"
    #include "GameEngine/ECS/System/EnemyShootSystem.hpp"
    #include "GameEngine/ECS/System/MobEnemyServer.hpp"
    #include "GameEngine/ECS/System/MobEnemy.hpp"
    #include "../Network/network.hpp"
    #include "System.hpp"
    #include "Component/Component.hpp"
    #include "../Network/Serialise.hpp"
    #include "../Network/packets.hpp"
    #include <mutex>

class Server {
     /// @brief Launch the server game
    public:
        /// @brief Create a new game server
        /// @param port Port where the server is located
        Server(int port);
        ~Server();
        void run_service()
        {
            io_context.run();
        }
        /// @brief Create the component necessary for the game
        void setComponent();
        /// @brief Creates a system to update Movement
        void setSystem();
        /// @brief execut requet client
        void Execute();
        /// @brief Manages the requests from the client
        void manageRequest();
         /**
         * @brief A method to handle the reception of a packet and dispatch it to the appropriate system
         * @param error In case of error, this is the error code
         * @param Bytes Number of bytes transferred
         */
        void HandleReceive(asio::error_code const &error, std::size_t Bytes);
        /// @brief  send the message of front to client with id specifer
        void SendData();
        /// @brief Handle the request from the client
        void HandleRequest();
        /// @brief Adds a player to the game
        void createPlayerSingle(std::string name);
        /// @brief Create an enemy
        /// @param t Enemy type
        /// @param x X Position
        /// @param y Y Position
        /// @param vx Velocity x
        /// @param vy Velocity y
        ///void createEnemy(int type, float x, float y, float vx, float vy, Entity room);
        /// @brief Kills a player (remove a life)
        /// @param client_index Client's id
        void kill_player_from_network(size_t client_index);
        /// @brief check if ip is for new_client in game
        /// @param address list of client addreess
        /// @param ip of potentiel new clien
        /// @return boolean false if client don'exist in base and true else
        bool check_New_client(std::vector<std::pair<udp::endpoint, int>> address, udp::endpoint ip);
        /**
        * @brief get ID player of client
        * @param ip of client
        * @param address list of ip know for client by server
        * @return int whom is id of cleint
        */
        int GetClientID(udp::endpoint ip);
        /**
        * @brief get ID entity player of client
        * @param ip of client
        * @param address list of ip know for client by server
        * @return int whom is id of cleint
        */
        /**
        * @brief get  Ip of player with ID
        * @param id_client id of player in network
        * @param address list of all client ip address
        * @return udp::endpoint address client
        */
        udp::endpoint GetClientEndpoint(int id_client);
        /// @brief send message to all client
        void MessageAllclient(std::vector<uint8_t> msg);
        /// @brief send message to all client with specifique endpoint
        /// @param player_address address of player
        void MessageAllclient(std::vector<uint8_t> msg, udp::endpoint ip);
        void MessageAllclient(std::vector<int> player_address, std::vector<uint8_t> msg);
        /// @brief send message to all client with specifique endpoint
        /// @param player_address address of player
        /// @param client_except who no get message;
        void MessageAllclient(std::vector<uint8_t> msg, std::vector<std::pair<udp::endpoint, int>> player_address, udp::endpoint client_except);
        void MessageAllclient(std::vector<int> player_address, std::vector<uint8_t> msg, int client_except);
        /// @brief deconnect client of game server
        /// @param client_id id of client want to be disconnected
        void deconnect_player(udp::endpoint ip);
        void InfoGameReady();
        void SendPlayerStartGame(std::pair<asio::ip::udp::endpoint, int> id, std::vector<std::pair<asio::ip::udp::endpoint, int>> player_ntwk_addres);
        void GameRoomLoop(std::shared_ptr<Room> room);
        void SendRoominfoPlayer();
        /// @brief Method to create new player entity
        /// @param player_id id of player on server system
        /// @param ip of client in network
        void CreatPlayerEntity(int player_id, udp::endpoint ip);
        void RunECSServer();
        void MovePlayer(Registry::entity_t &entity, uint16_t direction);
        void UpdatePlayer();
        /*void killPlayer(Entity play, Entity room);
        void killEntity_in_game(Entity play, Entity room);
        /// @brief Kill an enemy
        /// @param e id of enemy
        void killEnemy(size_t e, Entity room);
        /// @brief Shoot a projectile
        /// @param client_index Client's Id
        void Shoot(size_t client_index);
        /// @brief Creates a missile
        /// @param id Missile's data
        void createMissile(Msg_create_missile data);
        /// @brief Creates a bonus
        /// @param id Bonus's data
        void createBonus(int type, float x, float y, float vx, float vy, Entity room);
        /// @brief Update the position of an Entity
        /// @param data Entity's data
        void updatePosition(Msg_update data);
        void bonus_life_effect(Entity player, Entity bonus, Entity room);
        void bonus_kill_effect(Entity player, Entity bonus, Entity room);
        void bonus_speed_effect(Entity player, Entity bonus, Entity room);
        /// @brief Runs the game
        void run();
        /// @brief load enemy
        /// @param nb_player number of player
        /// @param type type of enemy
        /// @param velx velocity x
        /// @param vely velocity y
        void Load_enemy(int nb_player, int type, float velx, float vely, Entity room);
        /// @brief display enemy
        /// @param nb number of player
        void display_enemy(int nb, std::chrono::duration<double> elapsed, Entity room, int &ax);
        /// @brief random betwenn two numbers
        /// @param a min
        /// @param b max
        /// @return
        int Rand(int a, int b);
        /// @brief update player's score
        void updateScore(Msg_update_score score, Type t, Entity room);
        /// @brief update player's life
        /// @param life life's data
        void updateLife(Msg_update_life life, Entity room);
        /// @brief check collision between two entities
        /// @param p position of first entity
        /// @param b position of second entity
        /// @return True if collision, false otherwise
        //bool check_collision(auto &p, auto &b);
        /// @brief check collision between enemy and player
        void enemyCollision(Entity room);
        /// @brief check collision between player and player's missiles
        void playerCollision(Entity room);
        /// @brief check collision between player and bonuses
        void bonusCollision(Entity room);
        void createEnemyMissile(size_t j, float x, float y, int type, Entity room);
        void lunch_enemy_missile(std::chrono::duration<double> e, Entity room);
        void shootPlayer(Entity room);
        void EndGame(Entity room);
        template <typename T>
        void inform_all_room_clients(Entity room, T &msg, std::vector<size_t> ignore);
        Entity get_room_id();
        void manage_room(Entity room);*/
        void create_ennemy();
        void create_ennemy_bullet();
        void create_bullet();
        void move_ennemy_entity();
        void create_item();

    private:
        asio::io_context io_context;
        std::shared_ptr<network> netwk;
        Registry _regist;
        int nb_player = 0;
        int player_id = 50;
        int nb_player_ready = 0;
        std::vector<uint8_t> recv;
        std::thread request;
        std::thread _exec;
        bool run = false;
        std::vector<std::pair<udp::endpoint, int>> player_ntwk_address;
        std::thread ecs_thread;
        std::shared_ptr<Room> Rooms;
        std::queue<std::pair<udp::endpoint, std::vector<u_int8_t>>> recv_msg_client;
        std::queue<std::pair<udp::endpoint, std::vector<u_int8_t>>> send__msg_client;
        std::unordered_map<udp::endpoint, bool> player_status;
        std::unordered_map<udp::endpoint, std::string> player_name;
        std::unordered_map<udp::endpoint, Registry::entity_t> all_clients;
        std::mutex SendMutex;
        std::mutex RecvMutex;
        bool gamerun = false;
        asio::steady_timer timer;
};

#endif /* !SERVER_HPP_ */
