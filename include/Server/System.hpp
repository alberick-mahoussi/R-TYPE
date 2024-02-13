/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** Système
*/

#ifndef SYST_ME_HPP_
    #define SYST_ME_HPP_
    #include "GameEngine/ECS/Entity/Registry.hpp"

class Room {
    public:
        Room(Registry &_registr) : _registry(_registr)
        {
            running = false;
            id_admin = -1;
            nb_players = 0;
            nb_player_ready = 0;
        }
        ~Room() {}
        void add_player(std::string name, udp::endpoint client_addresse)
        {
            if (nb_players == 0)
                id_admin = id;
            player_address.push_back(std::pair<int, udp::endpoint>(id, client_addresse));
            player_info.push_back(std::pair<int, std::string>(id, name));
            player_state.push_back(std::pair<int, bool>(id, false));
            id += 1;
            nb_players += 1;
        }
        void leave_room(udp::endpoint addres)
        {
            int i = -1;
            int j = -1;
            int u = -1;
            int id = - 1;
            for (size_t x = 0; x < player_address.size(); x++) {
                if (player_address[x].second == addres) {
                    i = x;
                    id = player_address[x].first;
                    break;
                }
            }
            if (i == -1)
                return;
            for (size_t x = 0; x < player_info.size(); x++) {
                if (player_info[x].first == id) {
                    j = x;
                    break;
                }
            }
            for (size_t x = 0; x < player_state.size(); x++) {
                if (player_state[x].first == id) {
                    u = x;
                    break;
                }
            }
            player_address.erase(player_address.begin() + i);
            player_info.erase(player_info.begin() + j);
            player_state.erase(player_state.begin() + u);
            nb_players -= 1;
        }
        void leave_room(int id)
        {
            int i = -1;
            int j = -1;
            int u = -1;
            for (size_t x = 0; x < player_address.size(); x++) {
                if (player_address[x].first == id) {
                    i = x;
                    break;
                }
            }
            if (i == -1)
                return;
            for (size_t x = 0; x < player_info.size(); x++) {
                if (player_info[x].first == id) {
                    j = x;
                    break;
                }
            }
            for (size_t x = 0; x < player_state.size(); x++) {
                if (player_state[x].first == id) {
                    u = x;
                    break;
                }
            }
            player_address.erase(player_address.begin() + i);
            player_info.erase(player_info.begin() + j);
            player_state.erase(player_state.begin() + u);
            nb_players -= 1;
        }
        void add_player_ready(udp::endpoint client_addresse)
        {
            int id;

            for (size_t i = 0; i < player_address.size(); i++) {
                if (player_address[i].second == client_addresse) {
                    id = player_address[i].first;
                    break;
                }
            }
            for (size_t x = 0; x < player_state.size(); x++) {
                if (player_state[x].first == id) {
                    player_state[x].second = true;
                    break;
                }
            }
            nb_player_ready += 1;
        }
        void add_player_ready(int id_players)
        {
            if (id_players > id)
                return;   
            for (size_t x = 0; x < player_state.size(); x++) {
                if (player_state[x].first == id_players) {
                    player_state[x].second = player_state[x].second == true ? false : true;
                    break;
                }
            }
            nb_player_ready += 1;
        }
        void AdminKillPlayer(udp::endpoint client_address, int player_kill);
        bool IsFull()
        {
            if (nb_players == MAX_PLAYER)
                return true;
            return false;
        }
        void SetState (bool state)
        {
            running = state;
        }
        void SetPlayerReady(int id)
        {
            for (size_t i = 0; i < player_state.size(); i++) {
                if (player_state[i].first == id)
                    player_state[i].second = true;
            }
        }
        void addMaxplayer(int nb)
        {
            MAX_PLAYER += nb;
        }
        void ReduxMaxplayer(int nb)
        {
            if (nb > MAX_PLAYER)
                return;
            MAX_PLAYER -= nb;
        }
        int getIDPlayer(udp::endpoint client_address)
        {
            int x = -1;
            for (size_t i = 0; i < player_address.size(); i++) {
                if (player_address[i].second == client_address) {
                    x = player_address[i].first;
                    break;
                }
            }
            return x;
        }
        int getIDPlayer(std::string name)
        {
            int x = -1;
            for (size_t i = 0; i < player_info.size(); i++) {
                if (player_info[i].second == name) {
                    x = player_info[i].first;
                    break;
                }
            }
            return x;
        }
        bool GetSateRoom() const
        {
            return running;
        }
        void AllPlayersReady()
        {
            if (nb_player_ready == MAX_PLAYER)
                running = true;
        }
        int GetPlayerRoom() const
        {
            return nb_players;
        }
        int GetRoomID() const
        {
            return room_id;
        }
        void AddMessage(int id, std::vector<uint8_t> msg)
        {
            request_player.push(std::pair<int, std::vector<uint8_t>>(id, msg));
        }
        void PopMessage()
        {
            request_player.pop();
        }
        std::pair<int, std::vector<uint8_t>>getMessageFront()
        {
            return request_player.front();
        }
        std::vector<std::pair<std::string, bool>> getplayerStatus()
        {
            int h = 0;
            std::string name;
            std::vector<std::pair<std::string, bool>> info;   
            for (size_t i = 0; i < player_info.size(); i++) {
                h = player_info[i].first;
                name = player_info[i].second;
                for (size_t b = 0; b < player_state.size(); b++) {
                    if (h == player_state[i].first) {
                        info.push_back({name, player_state[i].second});
                        break;
                    }
                }
            }
            return info;
        }
        std::vector<int> GetEntityPlayersID()
        {
            std::vector<int> players;
            for (size_t i = 0; i < player_address.size(); i++)
                players.push_back(player_address[i].first);
            return players;
        }
        std::vector<udp::endpoint> GetEntityPlayersIP()
        {
            std::vector<udp::endpoint> players;
            for (size_t i = 0; i < player_address.size(); i++)
                players.push_back(player_address[i].second);    
            return players;
        }
        void CheckRunning()
        {
            if (nb_player_ready == nb_players)
                running = true;
        }
        int GetAdminId()
        {
            return id_admin;
        }
        int GetMaxPlayer() const
        {
            return MAX_PLAYER;
        }
        int GetPlayers() const {
            return nb_players;
        }

    private:
        std::vector<std::pair<int, udp::endpoint>> player_address;
        std::vector<std::pair<int, std::string>> player_info;
        std::vector<std::pair<int, bool>> player_state; 
        std::queue<std::pair<int, std::vector<uint8_t>>>request_player;
        int room_id;
        int id = 50;
        bool running = false;
        int id_admin = -1;
        int nb_players = 0;
        int nb_player_ready = 0;
        int MAX_PLAYER = 4;
        Registry &_registry;
};
/*class Speed {
        public:
            Speed(float x, float y)
            {
                _x = x;
                _y = y;
            }
            ~Speed() {}

            float _x;
            float _y;
    };

    /// @brief stock index of the client in the network class
    typedef struct networkId_t
    {
        networkId_t(size_t _id) : id(_id) {}
        networkId_t() {}

        size_t id;
    } networkId; // struct for the network id

    typedef struct id_t {
        id_t (size_t _id) : id(_id) {}
        size_t id;
    } id;

    typedef struct Type_t {
        Type_t (int _type) : type(_type) {}
        int type;
    } Type;

    typedef struct Bonus_type_t {
        Bonus_type_t (int _type) : type(_type) {}
        int type;
    } Bonus_type;

    typedef struct Score_t {
        Score_t (int _value) : value(_value) {}
        int value;
    } Score;

    typedef struct Shoot_t {
        Shoot_t (bool _shoot) : shoot(_shoot) {}
        bool shoot;
    } Shoot;

    typedef struct Life_t {
        Life_t (int _life) : life(_life) {}
        int life;
    } Life;

    typedef struct Damage_t {
        Damage_t (int _value) : value(_value) {}
        int value;
    } Damage;

    typedef struct Name_t {
        Name_t (std::string _value) : value(_value) {}
        std::string value;
    } Name;
*/
    /*class room {
        public:
            room(id) {
                running = false;
            }
            ~room() {}

            void add_entity(Entity e)
            {
                _entities.push_back(e);
            }

            void add_player(Entity e)
            {
                _players.push_back(e);
            }
            std::vector<Entity> _entities;
            std::vector<Entity> _players;
            int running;
            int id_admin;
            int nb_players;
            int nb_ebale_game;
    };*/
#endif /* !SYST_ME_HPP_ */
