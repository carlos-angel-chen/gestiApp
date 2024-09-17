#ifndef LOGISTICA_CONTROLLER_H
#define LOGISTICA_CONTROLLER_H

#include <pistache/http.h>
#include <pistache/router.h>
#include "database/DatabaseConnection.h"
#include "../services/LogisticaService.h"

using namespace Pistache;

class LogisticaController {
public:
    explicit LogisticaController(DatabaseConnection& db);

    void getAllLogisticas(const Rest::Request& request, Http::ResponseWriter response);
    void getLogisticasByRazonSocial(const Rest::Request& request, Http::ResponseWriter response);
    void getLogisticasByNombre(const Rest::Request& request, Http::ResponseWriter response);
    void getLogisticaByCuit(const Rest::Request& request, Http::ResponseWriter response);
    void createLogistica(const Rest::Request& request, Http::ResponseWriter response);
    void updateLogisticaById(const Rest::Request& request, Http::ResponseWriter response);
    void deleteLogisticaById(const Rest::Request& request, Http::ResponseWriter response);
    void getColumns(const Rest::Request& request, Http::ResponseWriter response);
private:
    DatabaseConnection& dbConn;
    LogisticaService logisticaService;
};

#endif // LOGISTICA_CONTROLLER_H