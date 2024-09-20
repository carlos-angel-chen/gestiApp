#include "../include/controllers/PedidosController.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

PedidosController::PedidosController(DatabaseConnection& db) : dbConn(db), pedidosService(db) {}

void PedidosController::getAllPedidos(const Rest::Request& request, Http::ResponseWriter response){
    try
    {
        auto pedidos = pedidosService.getAllPedidos();
        json jsonResponse = json::array();
        for (const auto& pedido : pedidos)
        {
            jsonResponse.push_back(pedido);
        }

        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    }
    catch(const std::exception& e)
    {
        json errorResponse = {{"error", "Error al obtener pedidos"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");

        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}