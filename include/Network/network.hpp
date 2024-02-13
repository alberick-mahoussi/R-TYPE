/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** network
*/

#ifndef NETWORK_HPP_
    #define NETWORK_HPP_
    #include <iostream>
    #include <vector>
    #include <cstdlib>
    #include <iostream>
    #include <iomanip>
    #include <thread>
    #include <string>
    #include <cstdio>
    #include <sstream>
    #include <stdbool.h>
    #include <ctime>
    #include <vector>
    #include <thread>
    #include <asio.hpp>
    #include "Serialise.hpp"
    #include "packets.hpp"

using asio::ip::udp;

enum info_type
{
    nonne = 1,
    newPlayer = 2,
    move = 3,
    createEnemy = 4,
    createMissile = 5,
    createOthers = 6,
    createBonus = 7,
    //getForce,
    updatePosition = 8,
    updateScore = 9,
    updateLife = 10,
    updateSpeed = 11,
    killEnemy = 12,
    killMissile = 13,
    killEntity = 14,
    leaveRoom = 15,
    gameStart = 16,
    addParallax = 17,
    gameOver = 18
};
///@brief network class of communication
class network
{
    private:
        asio::io_context & io_service; ///< IO context of the communication
        asio::ip::udp::socket _socket; ///< Socket that handle communication
        asio::ip::udp::endpoint _endpoint; ///< Endpoint from where the message will be received / sent

    public:
        /**
         * @brief Construct a new Udp Communication object
         * @param context IO Context of the communication
         * @param port Port where start the communication
         */
        network(asio::io_context &io_serv, int port) : io_service(io_serv),
        _socket(io_service, udp::endpoint(udp::v4(), port)) {};
        /**
         * @brief Construct a new Udp Communication object
         * @param context IO Context of the communication
         * @param port Port where start the communication
         * @param ip Ip address where connect the communication
         */
        network(asio::io_context &io_serv, int port, std::string const &ip) : io_service(io_serv),
        _socket(io_service, udp::endpoint(udp::v4(), 0)), _endpoint(asio::ip::address::from_string(ip), port) {
        };
        ///@brief Destroy the IUdpCommunication object
        ~network(){
            _socket.close();
        }
        /// @brief A method to send a message to the already known ip adress and port adress
        /// @param data The serialized message
        void send(std::vector<u_int8_t> const &data)
        {
            asio::error_code error;
            _socket.send_to(asio::buffer(data.data(), data.size()), _endpoint, 0, error);

            if (error) {
                std::cerr << "Erreur lors de l'envoi des données : " << error.message() << std::endl;
            } else {
                // std::cout << "package send" << std::endl;
            }
        }
        template <class T>
        void send(uint8_t id, const T &msg)
        {
            // std::cout << _socket.local_endpoint().address().to_string() << " " << _socket.local_endpoint().port() << std::endl;
            std::vector<u_int8_t> serializ_msg = Message_header::HeaderSerialize<T>(id, msg);
            asio::error_code error;
            _socket.send_to(asio::buffer(serializ_msg.data(), serializ_msg.size()), _endpoint, 0, error);

            if (error) {
                std::cerr << "Erreur lors de l'envoi des données : " << error.message() << std::endl;
            } else {
                std::cout << "Paquet envoyé avec succès" << std::endl;
            }
        }
        /**
         * @brief A method to send a message to an ip adress and port adress
         * @param data The serialized message
         * @param address The ip adress to send the message
         * @param port The port adress to send the message
         */
         void send(std::vector<u_int8_t> const &data, std::string const &address, int port)
        {
            asio::error_code error;
            setEndpoint(address, port);
            _socket.send_to(asio::buffer(data.data(), data.size()), _endpoint, 0, error);

            if (error) {
                std::cerr << "Erreur lors de l'envoi des données : " << error.message() << std::endl;
            } else {
                // std::cout << "package send" << std::endl;
            }
        }
        /**
         * @brief A method to send a message to specific endpoint
         * @param data The serialized message
         * @param ip client endpoint for send message
         */
        void send(std::vector<u_int8_t> const &data, udp::endpoint ip)
        {
            asio::error_code error;
            setEndpoint(ip);
            _socket.send_to(asio::buffer(data.data(), data.size()), _endpoint, 0, error);

            if (error) {
            std::cerr << "Erreur lors de l'envoi des données : " << error.message() << std::endl;
            } else {
            // std::cout << "package send" << std::endl;
            }
        }
        /**
         * @brief A method to send a message to an already known ip adress and port adress in an async way
         * @param data The serilized
         * @param callBack The function to call once the message is sent
         */
        void async_send(std::vector<u_int8_t> const &data, std::function<void(std::error_code const &, std::size_t)> callBack);
        /**
         * @brief A method to send a message to a ip adress and port adress in an async way
         * @param data The serialized message
         * @param callBack The function called once the message is sent
         * @param address The ip adress to send the message
         * @param port The port adress to send the message
         */
         void async_send(std::vector<u_int8_t> const &data, std::function<void(std::error_code const &, std::size_t)> callBack, asio::ip::address const &address, unsigned short const &port);
        /**
         * @brief A method to receive a message
         * @param data The buffer to fill when the message is received
         * @return std::pair<asio::ip::address, unsigned short> The ip adress and the port adress where the message came from
         */
         void receive(std::vector<u_int8_t> &data)
         {
            data.clear();
            data.resize(1024);
            _socket.receive_from(asio::buffer(data), _endpoint);
         }
        //@param callBack The function called once the message is received
        /**
         * @brief A method to receive a message in an async way
         * @param data The buffer to fill when the message is received
         */
        void async_receive(std::vector<u_int8_t> &data, std::function<void(std::error_code const &, std::size_t)> callBack)
        {
            int i;
            data.clear();
            data.resize(1024);
            _socket.async_receive_from(asio::buffer(data), _endpoint, callBack);
            /*[&](const asio::error_code& error, std::size_t bytes_received) {
                i = (int)Message_header::getId(data);
                std:: cout << i << std::endl;
                std::cout << serializable_system<msg_string>::deserialize(Message_header::extractMessageWithoutId(data)).data << std::endl;
                async_receive(data);
            });*/
        }
        /**
         * @brief Get the Enpoint Info object
         * @return std::pair<asio::ip::address, unsigned short> Pair with the ip address and the port of the endpoint
         */
         asio::ip::udp::endpoint  getEnpointInfo() const
         {
            return _endpoint;
         }
        /**
         * @brief Set the Enpoint Info object
         * @param endpointInfo Pair with the ip address and the port of the endpoint
         */
        void setEndpoint(asio::ip::udp::endpoint endpoint)
        {
            _endpoint.address(endpoint.address());
            _endpoint.port(endpoint.port());
        }
        /**
         * @brief Set the Enpoint data object
         * @param address Ip address of the endpoint
         * @param port Port of the endpoint
         */
        void setEndpoint(const std::string& address, int port)
        {
            asio::ip::udp::endpoint newEndpoint(asio::ip::address::from_string(address), port);
            _endpoint = newEndpoint;
        }
};

#endif /* !NETWORK_HPP_ */
