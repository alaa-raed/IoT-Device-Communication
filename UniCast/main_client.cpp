#include "inc/Channel_C_S.hpp"
#include <iostream>
#include <memory>  // For std::unique_ptr
#include <unistd.h> // For sleep function

void displayClientWelcomeMessage() {
    std::cout << "************CLIENT INITIALIZED************\n";
    
}

void executeClientOperations(Channel* channel) {
    if (channel) {
        channel->start();
        std::cout << "Client channel is now active and listening for messages...\n";
        channel->receive();

        // Sleep for 2 seconds to simulate some processing time
        sleep(2); 
        
        std::cout << "Client is sending a message to the server...\n";
        channel->send("Hello from the TCP Client Channel!");
        std::cout << "Message sent to server: [Hello from the TCP Client Channel!]\n";
        
        channel->stop();
        std::cout << "Client operations completed. Shutting down...\n";
    } else {
        std::cerr << "Error: Unable to initiate client channel operations.\n";
    }
}

int main() {
    displayClientWelcomeMessage();

    // Use a smart pointer to manage the Channel resource automatically
    std::unique_ptr<Channel> tcpClientChannel(ChannelFactory::createChannel(ChannelType::Client, SocketType::TCP));

    if (tcpClientChannel) {
        executeClientOperations(tcpClientChannel.get());
    } else {
        std::cerr << "Failed to create the TCP Client Channel. Exiting...\n";
    }

    return 0;
}
