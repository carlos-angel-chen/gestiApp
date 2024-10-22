#ifndef CALCULUS_CONTROLLER_H
#define CALCULUS_CONTROLLER_H

#include <pistache/http.h>
#include <pistache/router.h>
#include "database/DatabaseConnection.h"
#include "../services/CalculusService.h"

using namespace Pistache;

class CalculusController {

public:
    explicit CalculusController(DatabaseConnection& db);

    void getTotalSales(const Rest::Request& request, Http::ResponseWriter response);
    void getTotalProducts(const Rest::Request& request, Http::ResponseWriter response);
    void getTotalClients(const Rest::Request& request, Http::ResponseWriter response);
    void getStockAlert(const Rest::Request& request, Http::ResponseWriter response);
    void getMonthlySales(const Rest::Request& request, Http::ResponseWriter response);
    void getCategorySales(const Rest::Request& request, Http::ResponseWriter response);
    void getPaymentMethodSales(const Rest::Request& request, Http::ResponseWriter response);
    void getMaxPedidoId(const Rest::Request& request, Http::ResponseWriter response);

private:
    DatabaseConnection& dbConn;
    CalculusService calculusService;
};

#endif // CALCULUS_CONTROLLER_H