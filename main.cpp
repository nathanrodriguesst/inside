#include <iostream>
#include "include/nmap.h"
#include <nlohmann/json.hpp>
#include <netinet/in.h>
#include <sys/socket.h>

int main()
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(27908);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (struct sockaddr*)&serverAddress,
         sizeof(serverAddress));

    listen(serverSocket, 5);

    //listening loop
    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);

        char buffer[1024] = { 0 };
        recv(clientSocket, buffer, sizeof(buffer), 0);

        try {
            // Attempt to parse JSON
            std::cout << "parsing JSON...\n";
            nlohmann::json socketData = nlohmann::json::parse(buffer);

            if (socketData.is_object()) {
                std::string action = socketData["action"];
                if (action == "nmap-scan") {
                    std::cout << "nmap selected, initializing scan...\n";
                    // Extract IP and args from JSON
                    std::string ip = socketData["ip"];
                    std::string args = socketData["args"];

                    std::string output = nmapScan(ip, args);

                    send(clientSocket, output.c_str(), output.length(), 0);
                }
            } else {
                std::cout << "error";
                return -1;
            }
        } catch (const std::exception& e) {
            std::cout << "error";
        }
    }
}