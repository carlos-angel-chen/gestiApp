#include <iostream>
#include "../include/services/ClientesService.h"

ClientesService::ClientesService(DatabaseConnection& db) : dbConn(db) {}

std::vector<Clientes> ClientesService::getAllClients() {
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT * FROM public.\"Clientes\"");

        std::vector<Clientes> clientes;
        for (auto row : res){
            Clientes c = {
                row["id"].as<int>(),
                row["razon_social"].as<std::string>(),
                row["\"CUIT\""].as<std::string>(),
                row["tributacion"].as<std::string>(),
                row["telefono"].as<int>(),
                row["email"].as<std::string>(),
                row["nombre"].as<std::string>(),
                row["direccion_fiscal"].as<std::string>(),
                row["direccion_entrega"].as<std::string>(),
                row["localidad"].as<std::string>(),
                row["cp"].as<std::string>(),
                row["whatsapp"].as<std::string>()
            };
            clientes.push_back(c);
        }
        return clientes;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al obtener clientes: " << e.what() << std::endl;
        throw;
    }
}

std::vector<Clientes> ClientesService::getClientsByNombre(const std::string& nombre) {
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT * FROM public.\"Clientes\" WHERE nombre LIKE " + txn.quote("%" + nombre + "%")) ;

        std::vector<Clientes> clientes;
        for (auto row : res){
            Clientes c = {
                row["id"].as<int>(),
                row["razon_social"].as<std::string>(),
                row["\"CUIT\""].as<std::string>(),
                row["tributacion"].as<std::string>(),
                row["telefono"].as<int>(),
                row["email"].as<std::string>(),
                row["nombre"].as<std::string>(),
                row["direccion_fiscal"].as<std::string>(),
                row["direccion_entrega"].as<std::string>(),
                row["localidad"].as<std::string>(),
                row["cp"].as<std::string>(),
                row["whatsapp"].as<std::string>()
            };
            clientes.push_back(c);
        }
        return clientes;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al obtener clientes: " << e.what() << std::endl;
        throw;
    }
}
