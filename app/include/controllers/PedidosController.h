#ifndef PEDIDO_CONTROLLER_H
#define PEDIDO_CONTROLLER_H

#include <pistache/http.h>
#include <pistache/router.h>
#include "database/DatabaseConnection.h"
#include "../services/PedidosService.h"

using namespace Pistache;

class PedidosController {
public:
    explicit PedidosController(DatabaseConnection& db);

    void getAllPedidos(const Rest::Request& request, Http::ResponseWriter response);
    void getPedidoById(const Rest::Request& request, Http::ResponseWriter response);
    void updatePedido(const Rest::Request& request, Http::ResponseWriter response);
    void deletePedidoById(const Rest::Request& request, Http::ResponseWriter response);
    void getColumns(const Rest::Request& request, Http::ResponseWriter response);
private:
    DatabaseConnection& dbConn;
    PedidosService pedidosService;
};

#endif // PEDIDO_CONTROLLER_H