#include "inc/Channel_C_S.hpp"
#include <iostream>
#include <chrono>
#include <thread>

void displayServerHeader() {
    
    std::cout << "**********UDP SERVER**********\n";
    
}

int main() {
    displayServerHeader();

    // Create a Server Channel with a UDP Socket
    Channel* udpServerChannel = ChannelFactory::createChannel(ChannelType::Server, SocketType::UDP_MULTICAST);
    
    if (udpServerChannel) {
        udpServerChannel->start();
        std::cout << "Server channel is now active. Sending messages...\n";

        int messageCount = 1; // Initialize message counter
        while (messageCount <= 10) { // Send 10 messages
            udpServerChannel->send("Hello from the UDP Server Channel!");
            std::cout << "Message " << messageCount << " sent.\n";
            messageCount++; // Increment the counter
            std::this_thread::sleep_for(std::chrono::seconds(5)); // Sleep for 5 seconds
        }

        // Optional: Uncomment to receive messages if needed
        // udpServerChannel->receive(); 

        udpServerChannel->stop();
        std::cout << "Server channel stopped.\n";
        delete udpServerChannel; // Clean up the channel
    } else {
        std::cerr << "Failed to create UDP Server Channel.\n";
    }

    return 0;
}
