#ifndef CLIENTES_CONTROLLER_H
#define CLIENTES_CONTROLLER_H

#include <pistache/http.h>
#include <pistache/router.h>
#include "database/DatabaseConnection.h"
#include "../services/ClientesService.h"

using namespace Pistache;

class ClientesController {
public:
    explicit ClientesController(DatabaseConnection& db);

    void getAllClients(const Rest::Request& request, Http::ResponseWriter response);
    void getClientsByNombre(const Rest::Request& request, Http::ResponseWriter response);
    void getClientsByRazonSocial(const Rest::Request& request, Http::ResponseWriter response);
    void getClientByCuit(const Rest::Request& request, Http::ResponseWriter response);
    void createClient(const Rest::Request& request, Http::ResponseWriter response);
    void updateClientById(const Rest::Request& request, Http::ResponseWriter response);
    void deleteClientById(const Rest::Request& request, Http::ResponseWriter response);
    void getColumns(const Rest::Request& request, Http::ResponseWriter response);
private:
    DatabaseConnection& dbConn;
    ClientesService clientesService;
};

#endif // CLIENTES_CONTROLLER_H