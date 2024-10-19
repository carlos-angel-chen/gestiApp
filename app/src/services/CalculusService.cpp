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

std::vector<CalculusService::CategorySales> CalculusService::getCategorySales(){
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        std::string query = R"(
            SELECT 
                tipo.nombre,
                COUNT(pedido.id) AS total
            FROM
                public."Productos" producto
            LEFT JOIN 
                public."Pedidos" pedido
            ON
                pedido.id_producto = producto.id
            LEFT JOIN
                public."TipoProductos" tipo
            ON
                producto.id_tipo = tipo.id
            GROUP BY tipo.nombre;
                    )";
        pqxx::result res = txn.exec(query);

        std::vector<CategorySales> categorySales;
        for (auto row : res){
            CategorySales cs;
            cs.category = row[0].as<std::string>();
            cs.total = row[1].as<int>();
            categorySales.push_back(cs);
        }
        txn.commit();
        return categorySales;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al obtener el total de productos por categoria: " << e.what() << std::endl;
        throw;
    }
}

std::vector<CalculusService::PaymentMethodSales> CalculusService::getPaymentMethodSales(){
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        std::string query = R"(
            SELECT
                metodo.nombre AS method,
                COUNT(venta.id) AS total
            FROM
                public."Ventas" venta
            LEFT JOIN
                public."MetodoPagos" metodo
            ON
                venta.id_metodo_pago = metodo.id
            GROUP BY metodo.nombre;
                    )";
        pqxx::result res = txn.exec(query);

        std::vector<PaymentMethodSales> paymentMethodSales;
        for (auto row : res){
            PaymentMethodSales pms;
            pms.method = row[0].as<std::string>();
            pms.total = row[1].as<int>();
            paymentMethodSales.push_back(pms);
        }
        txn.commit();
        return paymentMethodSales;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al obtener el total de ventas por método de pago: " << e.what() << std::endl;
        throw;
    }
}