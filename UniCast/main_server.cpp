#include "inc/Channel_C_S.hpp"
#include <iostream>
#include <memory>  // For std::unique_ptr

void displayServerWelcomeMessage() {
    
    std::cout << "************SERVER INITIALIZED************\n";
    
}

void executeServerOperations(Channel* channel) {
    if (channel) {
        channel->start();
        std::cout << "Server is now active and ready to communicate.\n";
        channel->send("Greetings from the TCP Server Channel!");
        std::cout << "Message sent to client: [Greetings from the TCP Server Channel!]\n";
        channel->receive();
        channel->stop();
        std::cout << "Server operations completed. Shutting down...\n";
    } else {
        std::cerr << "Error: Unable to initiate channel operations.\n";
    }
}

int main() {
    displayServerWelcomeMessage();

    // Use a smart pointer to manage the Channel resource automatically
    std::unique_ptr<Channel> tcpServerChannel(ChannelFactory::createChannel(ChannelType::Server, SocketType::TCP));
    
    if (tcpServerChannel) {
        executeServerOperations(tcpServerChannel.get());
    } else {
        std::cerr << "Failed to create the TCP Server Channel. Exiting...\n";
    }

    return 0;
}
