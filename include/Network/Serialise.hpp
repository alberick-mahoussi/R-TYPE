/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** Serialise
*/

#ifndef SERIALISE_HPP_
    #define SERIALISE_HPP_
    #include <iostream>
    #include <string>
    #include <vector>
    #include <iostream>
    #include <cstring>
    #include <cstdint>

/// @brief Enum representing Type of request sent from Network to Client
    enum PACKET_TYPE {
        NEW_CONNECTION,
        DISCONNECTION,
        MOVE_PLAYER,
        SHOOT_PLAYER,
        READY_PLAYER,
        KILL_ENTITY,
        NEW_CLIENT,
        START_GAME,
        NEW_ENEMY,
        NEW_ENEMY_BULLET,
        ENTITY_MOVE,
        UPDATE_POSITION,
        KILL_ENTITY_TYPE,
        NEW_CLIENT_RESPONSE,
        UPDATE_ENTITY_INFO,
        NUMBER_PLAYERS_IN_LOBBY,
        UPDATE_PLAYER_HEALTH,
        UPDATE_ENTITY_SCORE,
        END_GAME,
        NEW_LEVEL,
        NEW_CONNECTION_SINGLE,
        ROOM_FULL,
        NEW_ITEM,
    };

enum ENTITY_TYPE {
    BULLETT,
    ENEMY1,
    PARALLAX,
    ENEMY2,
    ENEMY3
};

template <class T>
struct serializable_system {
    /// @brief A method to serialize an object (the object passed as template argument) into a vector of uint8_t
    /// @param obj Object to serialize
    /// @return std::vector<uint8_t> Serialized object
    static std::vector<uint8_t> serialize(T const &obj) {
        std::vector<uint8_t> ret;
        ret.resize(sizeof(T));
        std::memcpy(ret.data(), std::addressof(obj), sizeof(T));
        return ret;
    }
    /**
     * @brief A method to unserialize a vector of uint8_t into an object (passed as template argument)
     * @param v Object to unserialize
     * @return T deserialize object
     */
    static T deserialize(std::vector<uint8_t> const &v) {
        T data;

        std::memcpy(&data, v.data(), sizeof(T));
        return data;
    }
};
    /// @brief Class to serialize and unserialize a packet (as a std::vector of uint8_ts) with an id representing the type of data
    struct Message_header {
        ///@brief A method to serialize an object (the object passed as template argument) into a vector of uint8_t with his type at front
        ///@tparam Seriazable Type of Structure to serialize
        ///@param id Type of structure represented with an enum
        ///@param obj Object to serialize
        ///@return std::vector<uint8_t> Serialized object
        template<class T>
        static std::vector<uint8_t> HeaderSerialize(uint8_t id, T const &obj)
        {
            std::vector<uint8_t> dat;
            dat.resize(sizeof(uint8_t));
            std::memcpy(dat.data(), &id, sizeof(uint8_t));
            std::vector<uint8_t> data = serializable_system<T>::serialize(obj);
            dat.insert(dat.end(), data.begin(), data.end());
            return dat;
        };
    /**
     * @brief Get the Id object from the uint8_ts
     * @param uint8_ts Unkwown type Serialized Object with an id representing his type at front
     * @return uint8_t Id representing the type of Object contained in uint8_ts
     */
    static uint8_t getId(std::vector<uint8_t> const &uint8_ts)
    {
        uint8_t id;
        std::memcpy(&id, uint8_ts.data(), sizeof(uint8_t));
        return id;
    };
    static std::vector<uint8_t> extractMessageWithoutId(std::vector<uint8_t> const &uint8_ts)
    {
        if (uint8_ts.size() <= sizeof(uint8_t)) {
            return std::vector<uint8_t>();
        }
        size_t remainingSize = uint8_ts.size() - sizeof(uint8_t);
        std::vector<uint8_t> message(uint8_ts.begin() + sizeof(uint8_t), uint8_ts.end());
        return message;
    }
};

#endif /* !SERIALISE_HPP_ */
