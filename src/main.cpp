#include "../include/socket/RestfullServer.h"

int main() {
    RestfullServer server(8080);
    server.start();
    return 0;
}