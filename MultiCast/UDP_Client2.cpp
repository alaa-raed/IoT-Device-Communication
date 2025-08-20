#include "inc/Channel_C_S.hpp"
#include <iostream>
#include <chrono>
#include <string>
#include <bits/this_thread_sleep.h>

void displayClientHeader() {
    
    std::cout << "************UDP CLIENT 2************\n";
   
}

void runClientOperations(Channel* udpClientChannel) {
    std::string command;
    std::cout << "Type 'exit' to stop the client.\n";

    if (udpClientChannel) {
        udpClientChannel->start();
        std::cout << "Client channel is now active. Waiting for messages...\n";

        while (true) {
            // Receive messages from the server
            udpClientChannel->receive();

            // Check for user input to exit
            if (std::cin.peek() != '\n') { // Check for available input
                std::getline(std::cin, command);
                if (command == "exit") {
                    std::cout << "Exiting the client gracefully...\n";
                    break; // Break the loop if user types 'exit'
                }
            }

            // Optionally, add a small delay to reduce output flooding
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Sleep for a short period to reduce CPU usage
        }
        udpClientChannel->stop();
        std::cout << "Client channel stopped.\n";
        delete udpClientChannel; // Clean up the channel
    } else {
        std::cerr << "Failed to create UDP Client Channel.\n";
    }
}

int main() {
    displayClientHeader();

    Channel* udpClientChannel = ChannelFactory::createChannel(ChannelType::Client, SocketType::UDP_MULTICAST);
    
    runClientOperations(udpClientChannel);

    return 0;
}
