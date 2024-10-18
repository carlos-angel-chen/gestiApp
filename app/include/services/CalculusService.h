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
    
    struct MonthlySales {
        std::string month;
        double total_por_mes;
    };
    
    std::vector<MonthlySales> getMonthlySales();

private:
    DatabaseConnection& dbConn;
};

#endif // CALCULUS_SERVICE_H