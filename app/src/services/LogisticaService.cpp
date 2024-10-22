#include <iostream>
#include "../include/services/LogisticaService.h"

LogisticaService::LogisticaService(DatabaseConnection& db) : dbConn(db) {}

std::vector<Logistica> LogisticaService::getAllLogisticas(){
    try{
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT * FROM public.\"Logistica\"");

        std::vector<Logistica> logisticas;
        for (auto row : res){
            Logistica l = {
                row["id"].as<int>(),
                row["razon_social"].as<std::string>(),
                row["cuit"].as<std::string>(),
                row["direccion"].as<std::string>(),
                row["tipo"].as<std::string>(),
                row["nombre"].as<std::string>(),
                row["localidad"].as<std::string>(),
                row["telefono"].as<std::string>()
            };
            logisticas.push_back(l);
        }
        return logisticas;
    }
    catch(const std::exception& e){
        std::cerr << "Error al obtener logistica: " << e.what() << std::endl;
        throw;
    }
}

std::vector<Logistica> LogisticaService::getLogisticasByRazonSocial(const std::string& razonSocial){
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT * FROM public.\"Logistica\" WHERE razon_social LIKE " + txn.quote("%" + razonSocial + "%")) ;

        std::vector<Logistica> logisticas;
        for(auto row : res){
            Logistica l = {
                row["id"].as<int>(),
                row["razon_social"].as<std::string>(),
                row["cuit"].as<std::string>(),
                row["direccion"].as<std::string>(),
                row["tipo"].as<std::string>(),
                row["nombre"].as<std::string>(),
                row["localidad"].as<std::string>(),
                row["telefono"].as<std::string>()
            };
            logisticas.push_back(l);
        }
        return logisticas;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al obtener logistica: " << e.what() << std::endl;
        throw;
    }
}

std::vector<Logistica> LogisticaService::getLogisticasByNombre(const std::string& nombre){
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT * FROM public.\"Logistica\" WHERE nombre LIKE " + txn.quote("%" + nombre + "%")) ;

        std::vector<Logistica> logisticas;
        for(auto row : res){
            Logistica l = {
                row["id"].as<int>(),
                row["razon_social"].as<std::string>(),
                row["cuit"].as<std::string>(),
                row["direccion"].as<std::string>(),
                row["tipo"].as<std::string>(),
                row["nombre"].as<std::string>(),
                row["localidad"].as<std::string>(),
                row["telefono"].as<std::string>()
            };
            logisticas.push_back(l);
        }
        return logisticas;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al obtener logistica: " << e.what() << std::endl;
        throw;
    }
}

Logistica LogisticaService::getLogisticaByCuit(const std::string& cuit){
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT * FROM public.\"Logistica\" WHERE cuit = " + txn.quote(cuit));

        if(res.size() != 1){
            throw std::runtime_error("Logistica no encontrada");
        }

        auto row = res[0];
        Logistica l = {
            row["id"].as<int>(),
            row["razon_social"].as<std::string>(),
            row["cuit"].as<std::string>(),
            row["direccion"].as<std::string>(),
            row["tipo"].as<std::string>(),
            row["nombre"].as<std::string>(),
            row["localidad"].as<std::string>(),
            row["telefono"].as<std::string>()
        };
        return l;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al obtener logistica: " << e.what() << std::endl;
        throw;
    }
}

void LogisticaService::createLogistica(const Logistica& logistica){
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        std::string query = R"(INSERT INTO public."Logistica"
            (razon_social, cuit, direccion, tipo, nombre, localidad, telefono)
            VALUES ($1, $2, $3, $4, $5, $6, $7))";

        txn.exec_params(query, 
                        logistica.razonSocial,
                        logistica.cuit,
                        logistica.direccion,
                        logistica.tipo,
                        logistica.nombre,
                        logistica.localidad,
                        logistica.telefono);
        txn.commit();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al crear logistica: " << e.what() << std::endl;
        throw;
    }
}

Logistica LogisticaService::updateLogisticaById(const Logistica& logistica){
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        std::string query = R"(UPDATE public."Logistica" SET
            razon_social = $1,
            cuit = $2,
            direccion = $3,
            tipo = $4,
            nombre = $5,
            localidad = $6,
            telefono = $7
            WHERE id = $8)";

        txn.exec_params(query, 
                        logistica.razonSocial,
                        logistica.cuit,
                        logistica.direccion,
                        logistica.tipo,
                        logistica.nombre,
                        logistica.localidad,
                        logistica.telefono,
                        logistica.id);
        txn.commit();
        return logistica;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al actualizar logistica: " << e.what() << std::endl;
        throw;
    }
}

void LogisticaService::deleteLogisticaById(int id){
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        std::string query = R"(DELETE FROM public."Logistica" WHERE id = $1)";
        txn.exec_params(query, id);
        txn.commit();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al eliminar logistica: " << e.what() << std::endl;
        throw;
    }
}

std::vector<std::string> LogisticaService::getColumns(){
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT column_name FROM information_schema.columns WHERE table_name = 'Logistica'");

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