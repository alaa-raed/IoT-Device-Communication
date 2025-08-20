#include "../inc/Socket_TCP_UDP.hpp"
#include <iostream>

Socket* SocketFactory::createSocket(SocketType socketType, IsServer isServer) {
    switch (socketType) {
        case SocketType::TCP:
            return new TCPSocket(isServer);
        case SocketType::UDP_MULTICAST:
            return new UDPSocket(isServer);
        default:
            std::cerr << "Invalid socket type provided.\n";
            return nullptr;
    }
}