#include "../include/database/DatabaseConnection.h"
#include <iostream>

// Constructor de la clase DatabaseConnection: se encarga de
// inicializar los atributos del objeto cuando se crea una instancia 
// de DatabaseConnection
DatabaseConnection::DatabaseConnection(const std::string& connStr) : connectionString(connStr), conn(nullptr) {}

DatabaseConnection::~DatabaseConnection() {
    disconnect();
}

bool DatabaseConnection::connect() {
    try {
        // conn = new pqxx::connection(connectionString);
        conn = std::make_unique<pqxx::connection>(connectionString);
        if (conn->is_open()) {
            std::cout << "Connected to database: " << conn->dbname() << std::endl;
            return true;
        } else {
            std::cerr << "Failed to connect to database." << std::endl;
            return false;
        }
    } catch (const std::exception &e) {
        std::cerr << "Connection failed: " << e.what() << std::endl;
        return false;
    }
}

void DatabaseConnection::disconnect() {
    if (conn) {
        conn.reset();  // Esto libera la conexión automáticamente
        std::cout << "Disconnected from database." << std::endl;
    }
}

bool DatabaseConnection::isConnected() const {
    return conn && conn->is_open();
}

pqxx::connection* DatabaseConnection::getConnection() const {
    return conn.get();
}
