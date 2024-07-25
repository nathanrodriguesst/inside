#include "../include/restAPI/RestfulServer.h"

int main() {
    RestfulServer server(8080);
    server.start();
    return 0;
}