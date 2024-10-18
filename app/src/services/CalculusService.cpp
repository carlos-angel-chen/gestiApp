#include <iostream>
#include "../include/services/CalculusService.h"

CalculusService::CalculusService(DatabaseConnection& db) : dbConn(db) {}

float CalculusService::getTotalSales() {
    try   
    {
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT SUM(precio_final_pesos) FROM public.\"Ventas\"");

        float total = 0;
        if (!res.empty()) {
            total = res[0][0].as<float>(0);
        }
        txn.commit();
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
        if (!res.empty()) {
            total = res[0][0].as<int>(0);
        }
        txn.commit();
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
        if (!res.empty()) {
            total = res[0][0].as<int>(0);
        }
        txn.commit();
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
        if(!res.empty()){
            total = res[0][0].as<int>();
        }
        txn.commit();
        return total;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al obtener el total de productos con stock bajo: " << e.what() << std::endl;
        throw;
    }
}

std::vector<CalculusService::MonthlySales> CalculusService::getMonthlySales(){
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        std::string query = R"(
            SELECT 
                TO_CHAR(fecha, 'YYYY-MM') AS month,
                SUM(precio_final_pesos) AS total_por_mes
            FROM public."Ventas"
            GROUP BY TO_CHAR(fecha, 'YYYY-MM')
            ORDER BY month; -- Ordena por mes
        )";
        pqxx::result res = txn.exec(query);

        std::vector<MonthlySales> monthlySales;
        for (auto row : res){
            MonthlySales ms;
            ms.month = row[0].as<std::string>();
            ms.total_por_mes = row[1].as<double>();
            monthlySales.push_back(ms);
        }
        txn.commit();
        return monthlySales;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al obtener el total de ventas por mes: " << e.what() << std::endl;
        throw;
    }
}