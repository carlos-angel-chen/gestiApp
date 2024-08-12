#ifndef DATABASE_CONNECTION_H
#define DATABASE_CONNECTION_H

#include <pqxx/pqxx>  // Incluir la biblioteca pqxx
#include <string>

class DatabaseConnection {
private:
    std::string connectionString;
    pqxx::connection* conn;

public:
    DatabaseConnection(const std::string& connStr);
    ~DatabaseConnection();

    bool connect();
    void disconnect();
    bool isConnected() const;
    pqxx::connection* getConnection() const;
};

#endif // DATABASE_CONNECTION_H