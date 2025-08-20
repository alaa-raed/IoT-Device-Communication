#include "../inc/Socket.hpp"
#include <stdexcept>

// Static members initialization for UDPSocket
const char* UDPSocket::MULTICAST_ADDR = "239.0.0.1";
const int UDPSocket::MULTICAST_PORT = 8888;
const int UDPSocket::BUFFER_SIZE = 1024;

// Socket base class constructor and destructor
Socket::Socket(IsServer isServer) : isServer{isServer}, sockfd{-1} {}
Socket::~Socket() {}

// TCPSocket implementation
TCPSocket::TCPSocket(IsServer isServer) : Socket(isServer), clientSocket(-1) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        throw std::runtime_error("Failed to create TCP socket");
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(8080);
    address.sin_addr.s_addr = INADDR_ANY;
}

void TCPSocket::connect() {
    if (isServer == IsServer::server) {
        if (bind(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0) {
            throw std::runtime_error("Bind failed");
        }
        if (listen(sockfd, 3) < 0) {
            throw std::runtime_error("Listen failed");
        }
        std::cout << "TCP Server listening on port 8080...\n";

        socklen_t addrlen = sizeof(address);
        clientSocket = accept(sockfd, (struct sockaddr*)&address, &addrlen);
        if (clientSocket < 0) {
            throw std::runtime_error("Accept failed");
        }
        std::cout << "TCP Client connected\n";
    } else {
        address.sin_addr.s_addr = inet_addr("127.0.0.1");
        if (::connect(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0) {
            throw std::runtime_error("Connection failed");
        }
        std::cout << "TCP Connected to server\n";
    }
}

void TCPSocket::send(const std::string& message) {
    int targetSocket = (isServer == IsServer::server) ? clientSocket : sockfd;
    ssize_t bytesSent = ::send(targetSocket, message.c_str(), message.length(), 0);
    if (bytesSent < 0) {
        throw std::runtime_error("Send failed");
    }
    std::cout << "TCP Socket sent: " << message << "\n";
}

void TCPSocket::receive() {
    char buffer[1024] = {0};
    int targetSocket = (isServer == IsServer::server) ? clientSocket : sockfd;
    ssize_t bytesRead = recv(targetSocket, buffer, 1024 - 1, 0);
    if (bytesRead < 0) {
        throw std::runtime_error("Receive failed");
    }
    std::cout << "TCP Socket received: " << buffer << "\n";
}

void TCPSocket::shutdown() {
    if (clientSocket != -1) {
        close(clientSocket);
        clientSocket = -1;
    }
    if (sockfd != -1) {
        close(sockfd);
        sockfd = -1;
    }
    std::cout << "TCP Socket shut down.\n";
}

// UDPSocket implementation
UDPSocket::UDPSocket(IsServer isServer) : Socket(isServer), isConnected(false) {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        throw std::runtime_error("Failed to create UDP socket");
    }

    int reuse = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        close(sockfd);
        throw std::runtime_error("Failed to set SO_REUSEADDR");
    }

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(MULTICAST_PORT);

    setupMulticast();
}

void UDPSocket::connect() {
    try {
        if (isServer == IsServer::server) {
            setupServer();
        } else {
            setupClient();
        }
        isConnected = true;
        std::cout << "UDP Socket " 
                  << (isServer == IsServer::server ? "Server" : "Client") 
                  << " connected to multicast group\n";
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Connection failed: ") + e.what());
    }
}

void UDPSocket::send(const std::string& message) {
    if (!isConnected) {
        throw std::runtime_error("Socket not connected");
    }

    struct sockaddr_in multicastAddr;
    memset(&multicastAddr, 0, sizeof(multicastAddr));
    multicastAddr.sin_family = AF_INET;
    multicastAddr.sin_addr.s_addr = inet_addr(MULTICAST_ADDR);
    multicastAddr.sin_port = htons(MULTICAST_PORT);
    ssize_t bytesSent = sendto(sockfd, message.c_str(), message.length(), 0,
                             (struct sockaddr*)&multicastAddr, sizeof(multicastAddr));

    if (bytesSent < 0) {
        throw std::runtime_error("Failed to send message");
    }

    std::cout << "UDP Socket sent " << bytesSent << " bytes: " << message << "\n";
}

void UDPSocket::receive() {
    if (!isConnected) {
        throw std::runtime_error("Socket not connected");
    }

    char buffer[BUFFER_SIZE];
    struct sockaddr_in senderAddr;
    socklen_t senderLen = sizeof(senderAddr);

    ssize_t bytesRead = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0,
                               (struct sockaddr*)&senderAddr, &senderLen);

    if (bytesRead < 0) {
        throw std::runtime_error("Failed to receive message");
    }

    buffer[bytesRead] = '\0';
    std::cout << "UDP Socket received " << bytesRead << " bytes from "
              << inet_ntoa(senderAddr.sin_addr) << ":" << ntohs(senderAddr.sin_port)
              << ": " << buffer << "\n";
}

void UDPSocket::shutdown() {
    if (isConnected) {
        if (isServer != IsServer::server) {
            if (setsockopt(sockfd, IPPROTO_IP, IP_DROP_MEMBERSHIP, 
                         &mreq, sizeof(mreq)) < 0) {
                std::cerr << "Failed to leave multicast group\n";
            }
        }
        isConnected = false;
    }

    if (sockfd != -1) {
        close(sockfd);
        sockfd = -1;
    }
    std::cout << "UDP Socket shut down.\n";
}

UDPSocket::~UDPSocket() {
    shutdown();
    std::cout << "UDP Socket destroyed.\n";
}

void UDPSocket::setupMulticast() {
    int multicastTTL = 1;
    if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_TTL, 
                  &multicastTTL, sizeof(multicastTTL)) < 0) {
        close(sockfd);
        throw std::runtime_error("Failed to set multicast TTL");
    }
}

void UDPSocket::setupServer() {
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        throw std::runtime_error("Failed to bind server socket");
    }

    mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_ADDR);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);

    if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
        throw std::runtime_error("Failed to join multicast group");
    }
}

void UDPSocket::setupClient() {
    address.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        throw std::runtime_error("Failed to bind client socket");
    }

    mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_ADDR);
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);

    if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
        throw std::runtime_error("Failed to join multicast group");
    }
}