#ifndef INSIDE_DBCONNECTOR_H
#define INSIDE_DBCONNECTOR_H

#include <string>
#include <memory>
#include <mariadb/conncpp.hpp>

class DBConnector {
public:
    explicit DBConnector();
    static std::unique_ptr<sql::Connection> generateDatabaseConnectionInstance();

private:
    static std::unique_ptr<sql::Connection>
    getConnection(
            const std::string& host,const std::string& user,
            const std::string& password,const std::string& database);
};

#endif