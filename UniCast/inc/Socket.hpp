#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

enum class IsServer {
    server,
    client    
};

// Abstract Socket class
class Socket {
protected:
    IsServer isServer;
    int sockfd;
    struct sockaddr_in address;

public:
    explicit Socket(IsServer isServer);
    virtual void connect() = 0;
    virtual void send(const std::string& message) = 0;
    virtual void receive() = 0;
    virtual void shutdown() = 0;
    virtual ~Socket();
};

// TCP Socket implementation
class TCPSocket : public Socket {
private:
    int clientSocket; // Used only for server

public:
    explicit TCPSocket(IsServer isServer);
    void connect() override;
    void send(const std::string& message) override;
    void receive() override;
    void shutdown() override;
};

// UDP Socket implementation
class UDPSocket : public Socket {
private:
    static const char* MULTICAST_ADDR;
    static const int MULTICAST_PORT;
    static const int BUFFER_SIZE;
    struct ip_mreq mreq;
    bool isConnected;

public:
    explicit UDPSocket(IsServer isServer);
    void connect() override;
    void send(const std::string& message) override;
    void receive() override;
    void shutdown() override;
    ~UDPSocket() override;

private:
    void setupMulticast();
    void setupServer();
    void setupClient();
};

#endif // SOCKET_HPP