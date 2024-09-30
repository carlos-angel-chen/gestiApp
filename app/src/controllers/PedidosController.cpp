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

void PedidosController::getPedidoById(const Rest::Request& request, Http::ResponseWriter response){
    try
    {
        auto id = request.param(":id").as<int>();
        auto pedido = pedidosService.getPedidoById(id);
        json jsonResponse = json::array();
        for(const auto& p : pedido)
        {
            jsonResponse.push_back(p);
        }
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    }
    catch(const std::exception& e)
    {
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Not_Found, "Pedido no encontrado por ID");
    }    
}

void PedidosController::createPedido(const Rest::Request& request, Http::ResponseWriter response){
    try
    {
        auto jsonBody = json::parse(request.body());
        Pedidos pedido = {
            jsonBody["id"].get<int>(),
            jsonBody["id_producto"].get<int>(),
            jsonBody["SKU"].get<std::string>(),
            jsonBody["nombre"].get<std::string>(),
            jsonBody["tipo_producto"].get<std::string>(),
            jsonBody["cantidad"].get<int>(),
            jsonBody["costo"].get<float>(),
            jsonBody["precio_venta"].get<float>(),
            jsonBody["precio_sin_iva"].get<float>(),
            jsonBody["precio_con_iva"].get<float>(),
            jsonBody["precio_minorista"].get<float>(),
            jsonBody["precio_mayorista"].get<float>(),
            jsonBody["precio_venta_minimo"].get<float>()
        };
        pedidosService.createPedido(pedido);
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Created, "Pedido creado");
    }
    catch(const std::exception& e)
    {
        json errorResponse = {{"error", "Error al crear pedido"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }    
}

void PedidosController::getLastId(const Rest::Request& request, Http::ResponseWriter response){
    try
    {
        auto lastId = pedidosService.getLastId();
        json jsonResponse = lastId;
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    }
    catch(const std::exception& e)
    {
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, "Error al obtener último ID de la tabla Pedidos");
    }    
}

void PedidosController::getColumns(const Rest::Request& request, Http::ResponseWriter response){
    try
    {
        auto columns = pedidosService.getColumns();
        json jsonResponse = columns;
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    }
    catch(const std::exception& e)
    {
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, "Error al obtener columnas de la tabla Pedidos");
    }    
}