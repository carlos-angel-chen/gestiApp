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
                row["telefono"].as<std::string>(),
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
                row["telefono"].as<std::string>(),
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

std::vector<Clientes> ClientesService::getClientsByRazonSocial(const std::string& razonSocial) {
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT * FROM public.\"Clientes\" WHERE razon_social LIKE " + txn.quote("%" + razonSocial + "%")) ;

        std::vector<Clientes> clientes;
        for (auto row : res){
            Clientes c = {
                row["id"].as<int>(),
                row["razon_social"].as<std::string>(),
                row["\"CUIT\""].as<std::string>(),
                row["tributacion"].as<std::string>(),
                row["telefono"].as<std::string>(),
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

Clientes ClientesService::getClientByCuit(const std::string& cuit){
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT * FROM public.\"Clientes\" WHERE \"CUIT\" = " + txn.quote(cuit));

        if(res.size() != 1){
            throw std::runtime_error("Cliente no encontrado");
        }

        auto row = res[0];
        Clientes c = {
            row["id"].as<int>(),
            row["razon_social"].as<std::string>(),
            row["\"CUIT\""].as<std::string>(),
            row["tributacion"].as<std::string>(),
            row["telefono"].as<std::string>(),
            row["email"].as<std::string>(),
            row["nombre"].as<std::string>(),
            row["direccion_fiscal"].as<std::string>(),
            row["direccion_entrega"].as<std::string>(),
            row["localidad"].as<std::string>(),
            row["cp"].as<std::string>(),
            row["whatsapp"].as<std::string>()
        };

        txn.commit();
        return c;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al obtener clientes: " << e.what() << std::endl;
        throw;
    }
    
}

void ClientesService::createClient(const Clientes& cliente){
    try{
        pqxx::work txn(*dbConn.getConnection());

        std::string query = R"(INSERT INTO public."Clientes" 
            (razon_social, "CUIT", tributacion, telefono, email, nombre, "direccion_fiscal", "direccion_entrega", localidad, cp, whatsapp) 
            VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11))";

        // Ejecutar la consulta usando placeholders para evitar errores de formato
        txn.exec_params(query,
                        cliente.razonSocial,
                        cliente.cuit,
                        cliente.tributacion,
                        cliente.telefono,        // Asegúrate que este campo sea un número
                        cliente.email,
                        cliente.nombre,
                        cliente.direccionFiscal,
                        cliente.direccionEntrega,
                        cliente.localidad,
                        cliente.cp,
                        cliente.whatsapp);
        txn.commit();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al crear cliente: " << e.what() << std::endl;
        throw;
    }
}

Clientes ClientesService::updateClientById(const Clientes& cliente){
    try
    {
        pqxx::work txn(*dbConn.getConnection());

        std::string query = "UPDATE public.\"Clientes\" SET razon_social = " + txn.quote(cliente.razonSocial) + ", \"CUIT\" = " + txn.quote(cliente.cuit) + ", tributacion = " + txn.quote(cliente.tributacion) + ", telefono = " + txn.quote(cliente.telefono) + ", email = " + txn.quote(cliente.email) + ", nombre = " + txn.quote(cliente.nombre) + ", direccion_fiscal = " + txn.quote(cliente.direccionFiscal) + ", direccion_entrega = " + txn.quote(cliente.direccionEntrega) + ", localidad = " + txn.quote(cliente.localidad) + ", cp = " + txn.quote(cliente.cp) + ", whatsapp = " + txn.quote(cliente.whatsapp) + " WHERE id = " + txn.quote(cliente.id);

        txn.exec(query);
        txn.commit();
        return cliente;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al actualizar cliente: " << e.what() << std::endl;
        throw;
    }
}

void ClientesService::deleteClientById(int id){
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        std::string query = "DELETE FROM public.\"Clientes\" WHERE id = " + txn.quote(id);
        txn.exec(query);
        txn.commit();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al eliminar cliente: " << e.what() << std::endl;
        throw;
    }
}

std::vector<std::string> ClientesService::getColumns(){
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT column_name FROM information_schema.columns WHERE table_name = 'Clientes'");

        std::vector<std::string> columns;
        for(auto row : res){
            columns.push_back(row["column_name"].as<std::string>());
        }
        return columns;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al obtener columnas: " << e.what() << std::endl;
        throw;
    }
}