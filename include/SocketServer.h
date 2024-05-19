#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H
#include<string>

class SocketServer {
public:
    explicit SocketServer(int port);
    void connect() const;

private:
    int port;
};

#endif //SOCKETSERVER_H