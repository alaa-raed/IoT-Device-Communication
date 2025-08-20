#ifndef CHANNEL_FACTORY_HPP
#define CHANNEL_FACTORY_HPP

#include "Channel.hpp"

// Enum to specify the type of channel to create
enum class ChannelType {
    Server,
    Client
};

// Factory class to create channels based on the specified ChannelType
class ChannelFactory {
public:
    static Channel* createChannel(ChannelType channelType, SocketType socketType);
};

#endif // CHANNEL_FACTORY_HPP