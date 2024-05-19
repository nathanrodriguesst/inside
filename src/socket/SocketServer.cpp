#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include "../include/SocketServer.h"
#include "RedirectHub.h"

SocketServer::SocketServer(int port) : port(port) {}

void SocketServer::connect() const {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == -1) {
        std::cerr << "Error connecting to socket";
        return;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddress,
             sizeof(serverAddress)) < 0) {
        std::cerr << "Socket binding failed, port " << port << " may still be in use.";
        return;
    }

    listen(serverSocket, 5);

    //listening loop
    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        char buffer[1024] = { 0 };

        //receive client socket data
        recv(clientSocket, buffer, sizeof(buffer), 0);

        //read the json and redirect based on 'type' parameter
        std::string output = RedirectHub::redirect(buffer);

        try {
            send(clientSocket, output.c_str(), output.length(), 0);
        } catch (const std::exception& e) {
            std::cout << "Error sending data.";
            return;
        }
    }
}