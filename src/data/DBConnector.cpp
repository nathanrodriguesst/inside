#include "data/DBConnector.h"
#include <iostream>
#include <mariadb/conncpp.hpp>

std::unique_ptr<sql::Connection> connection;

DBConnector::DBConnector() = default;

std::unique_ptr<sql::Connection> DBConnector::getConnection(const std::string& host, const std::string& user, const std::string& password, const std::string& database) {
    try {
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        std::unique_ptr<sql::Connection> conn(driver->connect("jdbc:mariadb://" + host + "/" + database, user, password));
        return conn;
    } catch (sql::SQLException& e) {
        std::cerr << "Error connecting to the database: " << e.what() << std::endl;
        return nullptr;
    }
}

std::unique_ptr<sql::Connection> DBConnector::generateDatabaseConnectionInstance() {
    std::string ip = "localhost";
    std::string user = "myazuk";
    std::string password = "123";
    std::string database = "inside";

    return getConnection(ip, user, password, database);
}
