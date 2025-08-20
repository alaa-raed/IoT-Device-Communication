#include "../inc/Channel_C_S.hpp"
#include <iostream>

Channel* ChannelFactory::createChannel(ChannelType channelType, SocketType socketType) {
    switch (channelType) {
        case ChannelType::Server:
            return new ServerChannel(socketType);
        case ChannelType::Client:
            return new ClientChannel(socketType);
        default:
            std::cerr << "Invalid channel type provided.\n";
            return nullptr;
    }
}