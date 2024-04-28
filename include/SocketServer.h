#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H
#include<string>

class SocketServer {
public:
    explicit SocketServer(int port);
    void connect() const;

private:
    int port;
    static std::string redirect(const char *buffer);
};

#endif //SOCKETSERVER_H