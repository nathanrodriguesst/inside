#include "../include/SocketServer.h"

int main() {
    SocketServer socket(27908);
    socket.connect();
    return 0;
}