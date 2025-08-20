#include "../inc/Channel.hpp"

// ServerChannel implementation
ServerChannel::ServerChannel(SocketType socketType) {
    channelSocket = SocketFactory::createSocket(socketType, IsServer::server);
}

void ServerChannel::start() {
    std::cout << "ServerChannel started.\n";
    channelSocket->connect();
}

void ServerChannel::stop() {
    std::cout << "ServerChannel stopped.\n";
    channelSocket->shutdown();
}

void ServerChannel::send(const std::string& message) {
    channelSocket->send(message);
}

void ServerChannel::receive() {
    channelSocket->receive();
}

// ClientChannel implementation
ClientChannel::ClientChannel(SocketType socketType) {
    channelSocket = SocketFactory::createSocket(socketType, IsServer::client);
}

void ClientChannel::start() {
    std::cout << "ClientChannel started.\n";
    channelSocket->connect();
}

void ClientChannel::stop() {
    std::cout << "ClientChannel stopped.\n";
    channelSocket->shutdown();
}

void ClientChannel::send(const std::string& message) {
    channelSocket->send(message);
}

void ClientChannel::receive() {
    channelSocket->receive();
}