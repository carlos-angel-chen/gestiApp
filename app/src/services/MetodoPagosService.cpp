#include <iostream>
#include "../include/services/MetodoPagosService.h"

MetodoPagosService::MetodoPagosService(DatabaseConnection& db) : dbConn(db) {}

std::vector<MetodoPagos> MetodoPagosService::getAllMetodoPagos() {
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT * FROM public.\"MetodoPagos\"");

        std::vector<MetodoPagos> metodosPagos;
        for(auto row : res){
            MetodoPagos mp = {
                row["id"].as<int>(),
                row["nombre"].as<std::string>()
            };
            metodosPagos.push_back(mp);
        }
        return metodosPagos;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al obtener metodos de pago: " << e.what() << std::endl;
        throw;
    }
}

void MetodoPagosService::createMetodoPago(const MetodoPagos& metodoPago) {
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        std::string query = R"(INSERT INTO public."MetodoPagos" 
            (nombre) 
            VALUES ($1))";
        
        txn.exec_params(query, metodoPago.nombre);
        txn.commit();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al crear metodo de pago: " << e.what() << std::endl;
        throw;
    }
}

MetodoPagos MetodoPagosService::updateMetodoPagoById(const MetodoPagos& metodoPago) {
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        std::string query = R"(UPDATE public."MetodoPagos" 
            SET nombre = $1
            WHERE id = $2)";
        
        txn.exec_params(query, metodoPago.nombre, metodoPago.id);
        txn.commit();
        return metodoPago;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al actualizar metodo de pago: " << e.what() << std::endl;
        throw;
    }
}

void MetodoPagosService::deleteMetodoPagoById(int id) {
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        std::string query = R"(DELETE FROM public."MetodoPagos" WHERE id = $1)";
        
        txn.exec_params(query, id);
        txn.commit();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al eliminar metodo de pago: " << e.what() << std::endl;
        throw;
    }
}

std::vector<std::string> MetodoPagosService::getColumns(){
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT column_name FROM information_schema.columns WHERE table_name = 'MetodoPagos'");

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