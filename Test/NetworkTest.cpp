/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-1-rtype-alberick.mahoussi
** File description:
** NetworkTest
*/

#include <criterion/criterion.h>
#include "network.hpp"

Test(network, send_and_receive) {
    /// @brief Initialize asio::io_context and network object here
    asio::io_context io;
    network myNetwork(io, 12345);

    std::vector<u_int8_t> messageToSend = {1, 2, 3, 4, 5};

    myNetwork.send(messageToSend);

    std::vector<u_int8_t> receivedMessage;

    myNetwork.receive(receivedMessage);
    
    cr_assert_eq(messageToSend, receivedMessage, "Sent and received messages don't match");
}

Test(network, async_receive) {
    asio::io_context io;
    network myNetwork(io, 12345);

    std::vector<u_int8_t> messageToSend = {1, 2, 3, 4, 5};

    myNetwork.send(messageToSend);
    // Prepare a buffer to receive the message
    std::vector<u_int8_t> receivedMessage;

    // Receive the message asynchronously
    myNetwork.async_receive(receivedMessage, [&](const asio::error_code& error, std::size_t bytes_received) {
        cr_assert_not(error, "Error during async_receive: %s", error.message().c_str());
    });

}

/*int main(int argc, char *argv[]) {
    // Initialize the Criterion testing framework
    criterion_init(argc, argv);

    // Run the tests
    criterion_run_all();

    return 0;
}*/
