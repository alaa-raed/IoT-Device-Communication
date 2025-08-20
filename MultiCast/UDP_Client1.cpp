#include "inc/Channel_C_S.hpp"
#include <iostream>
#include <chrono>
#include <thread>

void displayClientHeader() {
    
    std::cout << "*************UDP CLIENT 1*************\n";
    
}

int main() {
    displayClientHeader();

    // Create a Client Channel with a UDP Socket
    Channel* udpClientChannel = ChannelFactory::createChannel(ChannelType::Client, SocketType::UDP_MULTICAST);
    
    if (udpClientChannel) {
        udpClientChannel->start();
        std::cout << "Client channel is now active. Waiting for messages...\n";

        // Continuous loop to receive messages
        while (true) {
            udpClientChannel->receive();

            // Optional: Add a small delay to reduce CPU usage
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Sleep for a short period
        }

        // Clean up (will never reach this line due to infinite loop)
        udpClientChannel->stop();
        std::cout << "Client channel stopped.\n";
        delete udpClientChannel; // Clean up the channel
    } else {
        std::cerr << "Failed to create UDP Client Channel.\n";
    }

    return 0;
}
