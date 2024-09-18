#ifndef METODO_PAGOS_CONTROLLER_H
#define METODO_PAGOS_CONTROLLER_H

#include <pistache/http.h>
#include <pistache/router.h>
#include "database/DatabaseConnection.h"
#include "../services/MetodoPagosService.h"

using namespace Pistache;

class MetodoPagosController {
public: 
    explicit MetodoPagosController(DatabaseConnection& db);

    void getAllMetodoPagos(const Rest::Request& request, Http::ResponseWriter response);
    void createMetodoPago(const Rest::Request& request, Http::ResponseWriter response);
    void deleteMetodoPagoById(const Rest::Request& request, Http::ResponseWriter response);
    void getColumns(const Rest::Request& request, Http::ResponseWriter response);
    void updateMetodoPagoById(const Rest::Request& request, Http::ResponseWriter response);
private:
    DatabaseConnection& dbConn;
    MetodoPagosService metodoPagosService;
};

#endif // METODO_PAGOS_CONTROLLER_H