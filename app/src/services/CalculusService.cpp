#include <iostream>
#include "../include/services/CalculusService.h"

CalculusService::CalculusService(DatabaseConnection& db) : dbConn(db) {}

float CalculusService::getTotalSales() {
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT SUM(precio_final_pesos) FROM public.\"Ventas\"");

        float total = 0;
        for (auto row : res){
            total = row[0].as<float>();
        }
       
        return total;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al obtener el total de ventas: " << e.what() << std::endl;
        throw;
    }
}

int CalculusService::getTotalProducts(){
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT COUNT(id) FROM public.\"Productos\"");

        int total = 0;
        for (auto row : res){
            total = row[0].as<int>();
        }
        
        return total;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al obtener el total de productos: " << e.what() << std::endl;
        throw;
    }
}

int CalculusService::getTotalClients(){
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT COUNT(id) FROM public.\"Clientes\"");

        int total = 0;
        for (auto row : res){
            total = row[0].as<int>();
        }
        
        return total;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al obtener el total de clientes: " << e.what() << std::endl;
        throw;
    }
}

int CalculusService::getStockAlert(){
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT COUNT(id) FROM public.\"Productos\" WHERE stock_actual < stock_minimo");

        int total = 0;
        for (auto row : res){
            total = row[0].as<int>();
        }
        
        return total;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al obtener el total de productos con stock bajo: " << e.what() << std::endl;
        throw;
    }
}