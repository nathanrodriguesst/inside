#include <iostream>
#include <nlohmann/json.hpp>
#include <netinet/in.h>
#include <sys/socket.h>
#include "../../include/Scan.h"
#include "../include/SocketServer.h"

SocketServer::SocketServer(int port) : port(port) {}

void SocketServer::connect() const {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket == -1) {
        std::cerr << "Error connecting socket";
        return;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddress,
             sizeof(serverAddress)) < 0) {
        std::cerr << "Binding failed";
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
        std::string output = redirect(buffer);

        try {
            send(clientSocket, output.c_str(), output.length(), 0);
        } catch (const std::exception& e) {
            std::cout << "error sending data.";
            return;
        }
    }
}

std::string SocketServer::redirect(const char *buffer) {
    try {
        // Attempt to parse JSON
        std::cout << "Parsing JSON...\n";
        nlohmann::json socketData = nlohmann::json::parse(buffer);

        if (socketData.is_object()) {
            std::string action = socketData["action"];
            if (action == "nmap-scan") {
                std::cout << "Initializing nmap scan...\n";
                // Extract IP and args from JSON
                std::string ip = socketData["ip"];
                std::string args = socketData["args"];

                return Scan::prepareNmapScan(ip, args);

            } else if (action == "feroxbuster-scan") {
                std::cout << "Initializing feroxbuster scan...\n";
                std::string url = socketData["url"];
                std::string args = socketData["args"];

                std::cout << "ferox";
                return Scan::PrepareDirectoryBruteForce(url, args);
            }
        }
    } catch (const std::exception& e) {
        return "json error";
    }
    return "";
}