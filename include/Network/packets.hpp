/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** message
*/

#ifndef MESSAGE_HPP_
    #define MESSAGE_HPP_
    #include <iostream>
    #include <string>
    #include <cstdint>
    #include <cstring>
    #include <iostream>
    /// Here we have all struct whom we use to communication Server-client
    /// @brief enum direction of player
    enum diretion {
        none = 0,
        up = 1,
        down = 2,
        left = 3,
        right = 4,
        space = 5,
    };
    /// @brief enum with information on updating entities
    /// @brief A packet to handle new connections to the game
    struct new_connection {
        new_connection() {};
        new_connection(int i) : id(i) {};
        uint16_t id;
    };
    /// @brief A packet to handle disconnection
    struct disconnection {
        disconnection() {};
        disconnection(int i) : disconnect(i) {};
        uint16_t disconnect; ///< Disconnection
    };
    /// @brief A packet to handle a new entity informations
    struct new_entity {
        uint16_t id; ///< id of new entity;
        float positionX; ///< x position of new entity;
        float positionY; ///< y position of new entity;
        uint16_t direction; ///< direction of new entity;
        std::size_t type; ///< type of entity;
        int clientId; ///< id of client
        int health; ///< health of new entity;
        int score; ///< score of new entity;
    };
    /// @brief A packet to tell the server that a client want to start the game in a certain lobby
    struct player_ready_to_game {
        player_ready_to_game() {}
        player_ready_to_game(int i) : id_player(i){}
        int id_player;
    };
    struct player_move {
        player_move() {}
        player_move(diretion dr) : diretion_player(dr){};
        uint16_t diretion_player;
    };
    struct player_shoot {
        player_shoot() {};
        player_shoot(int i) : player_id(i) {};
        int player_id;
    };
    struct update_player_position {
        update_player_position() {};
        update_player_position(int id_enti, int x, int y) : id_enitity(id_enti), pos_x(x), pos_y(y) {};

        uint16_t id_enitity;
        int pos_x;
        int pos_y;
    };
    struct inform_player_move {
        inform_player_move() {};
        inform_player_move(int id_enti, int dir) : id_enitity(id_enti), direction(dir) {};

        uint16_t id_enitity;
        uint16_t direction;
    };
    struct update_player_health {
        update_player_health() {};
        update_player_health(int id_enti, int health) : id_enitity(id_enti), health(health){};
        uint16_t id_enitity;
        int health;
    };
    /*struct player_in_room_id {
        player_in_room_id() {}
        player_in_room_id(int id_1, int id_2, int id_3, int id_4) : player_one(id_1),  player_two(id_2), player_three(id_3), player_four(id_4) {}
    uint16_t player_one;
    uint16_t player_two;
    uint16_t player_three;
    uint16_t player_four;
    };*/
    struct players_states {
        players_states() {
            for (int i = 0; i < 4; i++) {
                std::memset(names[i], 0, sizeof(names[i]));
            }
            memset(states_player, 0, sizeof(states_player));
        }
        char names[10][50];
        uint16_t states_player[10];
    };
    struct info_all_player {
        info_all_player(){};
        info_all_player(int id) : id_enitity((uint16_t)id) {
            memset(id_enitity_players, 0, sizeof(id_enitity_players));
        }
        uint16_t id_enitity;
        uint16_t id_enitity_players[10];
    };
    struct inform_player_shoot {
        inform_player_shoot() {};
        inform_player_shoot(int id) : id_enitity(id) {}
        uint16_t id_enitity;
    };
    struct new_ennemy {
        new_ennemy() {};
        new_ennemy(int x, int y, int type, int id) : pos_x(x), pos_y(y), type(type), id(id) {}
        int  pos_x;
        int pos_y;
        int type;
        int id;
    };
    struct new_item {
        new_item() {};
        new_item(int x, int y, int id) : pos_x(x), pos_y(y), id(id) {}
        int pos_x;
        int pos_y;
        int id;
    };
    struct new_allyBullet {
        new_allyBullet() {};
        new_allyBullet(int x, int y, int type, int id, int idPlayer) : pos_x(x), pos_y(y), type(type), id(id), idPlayer(idPlayer) {}
        int pos_x;
        int pos_y;
        int type;
        int id;
        int idPlayer;
    };
    struct new_ennemy_bullet {
        new_ennemy_bullet() {};
        new_ennemy_bullet(int idBullet, int idPlayer) : _idBullet(idBullet), _idPlayer(idPlayer) {}
        int _idBullet;
        int _idPlayer;
    };
    struct inform_player_disconnected {
        inform_player_disconnected() {};
        inform_player_disconnected(int id_enti) : id_enitity(id_enti){}

        uint16_t id_enitity;
    };
    struct msg_string {
        char data[256];
    };
    struct kill_player {
        uint16_t id_enitity;
    };

#endif /* !MESSAGE_HPP_ */
