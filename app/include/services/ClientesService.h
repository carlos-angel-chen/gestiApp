#ifndef CLIENTES_SERVICE_H
#define CLIENTES_SERVICE_H

#include <pqxx/pqxx>
#include "../models/Clientes.h"
#include "database/DatabaseConnection.h"
#include <vector>

class ClientesService {
public:
    explicit ClientesService(DatabaseConnection& db);

    std::vector<Clientes> getAllClients();
    std::vector<Clientes> getClientsByNombre(const std::string& nombre);
    std::vector<Clientes> getClientsByRazonSocial(const std::string& razonSocial);
    std::vector<Clientes> getClientByCuit(const std::string& cuit);
    void createClient(const Clientes& clientes);
    Clientes updateClientById(const Clientes& clientes);
    void deleteClientById(int id);
    std::vector<std::string> getColumns();
    
private:
    DatabaseConnection& dbConn;
};

#endif // CLIENTES_SERVICE_H