#ifndef CALCULUS_SERVICE_H
#define CALCULUS_SERVICE_H

#include <pqxx/pqxx>
#include "database/DatabaseConnection.h"
#include <vector>
#include <nlohmann/json.hpp>

class CalculusService {
public:
    explicit CalculusService(DatabaseConnection& db);

    float getTotalSales();
    int getTotalProducts();
    int getTotalClients();
    int getStockAlert();
    int getMaxPedidoId();
    int getTotalPedidos();
    float getAvgPrecioFinalPesos();
    float getAvgPrecioFinalUsd();
    
    struct MonthlySales {
        std::string month;
        double total_por_mes;
    };
    std::vector<MonthlySales> getMonthlySales();

    struct CategorySales{
        std::string category;
        int total;
    };
    std::vector<CategorySales> getCategorySales();

    struct PaymentMethodSales{
        std::string method;
        int total;
    };
    std::vector<PaymentMethodSales> getPaymentMethodSales();


private:
    DatabaseConnection& dbConn;
};

#endif // CALCULUS_SERVICE_H