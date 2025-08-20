#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Socket_TCP_UDP.hpp"
#include <iostream>
#include <string>

// Abstract Channel class
class Channel {
protected:
    Socket* channelSocket;  // Pointer to Socket

public:
    explicit Channel() : channelSocket(nullptr) {}
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void send(const std::string& message) = 0;
    virtual void receive() = 0;
    virtual ~Channel() {
        delete channelSocket;  // Clean up the socket object
    }
};

// ServerChannel implementation
class ServerChannel : public Channel {
public:
    explicit ServerChannel(SocketType socketType);
    void start() override;
    void stop() override;
    void send(const std::string& message) override;
    void receive() override;
};

// ClientChannel implementation
class ClientChannel : public Channel {
public:
    explicit ClientChannel(SocketType socketType);
    void start() override;
    void stop() override;
    void send(const std::string& message) override;
    void receive() override;
};

#endif // CHANNEL_HPP