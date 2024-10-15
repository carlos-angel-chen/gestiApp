#ifndef CALCULUS_SERVICE_H
#define CALCULUS_SERVICE_H

#include <pqxx/pqxx>
#include "database/DatabaseConnection.h"
#include <vector>

class CalculusService {
public:
    explicit CalculusService(DatabaseConnection& db);

    float getTotalSales();
    int getTotalProducts();
    int getTotalClients();
    int getStockAlert();
    
private:
    DatabaseConnection& dbConn;
};

#endif // CALCULUS_SERVICE_H