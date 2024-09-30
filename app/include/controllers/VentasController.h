#ifndef VENTAS_CONTROLLER_H
#define VENTAS_CONTROLLER_H

#include <pistache/http.h>
#include <pistache/router.h>
#include "database/DatabaseConnection.h"
#include "../services/VentasService.h"

using namespace Pistache;

class VentasController {
public:
    explicit VentasController(DatabaseConnection& db);

    void getAllVentas(const Rest::Request& request, Http::ResponseWriter response);
    void getVentaById(const Rest::Request& request, Http::ResponseWriter response);
    void createVenta(const Rest::Request& request, Http::ResponseWriter response);
    //void updateVentasById(const Rest::Request& request, Http::ResponseWriter response);
    //void deleteVentasById(const Rest::Request& request, Http::ResponseWriter response);
    //void getColumns(const Rest::Request& request, Http::ResponseWriter response);
private:
    DatabaseConnection& dbConn;
    VentasService ventasService;
};

#endif // VENTAS_CONTROLLER_H