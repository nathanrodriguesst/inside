#ifndef SOCKET_SERVER_H
#define SOCKET_SERVER_H

#include "../vendor/http/httplib.h"

class RestfullServer {
public:
    explicit RestfullServer(int port);
    void start() const;

private:
    int port;
    void setupRoutes(httplib::Server &svr) const;
};

#endif // SOCKET_SERVER_H
