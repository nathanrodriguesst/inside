#include <iostream>
#include "restAPI/RestfulServer.h"
#include <nlohmann/json.hpp>
#include "restAPI/Routes.h"

using json = nlohmann::json;
RestfulServer::RestfulServer(int port) : port(port) {}

void RestfulServer::start() const {
    httplib::Server svr;

    // Handle OPTIONS preflight request
    svr.Options(R"(/.*)", [](const httplib::Request &req, httplib::Response &res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        res.status = 204; // No content
    });

    Routes::setupRoutes(svr);

    std::cout << "Server Running on Port: " << port << std::endl;
    svr.listen("0.0.0.0", port);
}
