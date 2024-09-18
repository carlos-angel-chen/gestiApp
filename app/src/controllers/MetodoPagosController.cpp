#include "../include/controllers/MetodoPagosController.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

MetodoPagosController::MetodoPagosController(DatabaseConnection& db) : dbConn(db), metodoPagosService(db) {}

void MetodoPagosController::getAllMetodoPagos(const Rest::Request& request, Http::ResponseWriter response) {
    try
    {
        auto metodoPagos = metodoPagosService.getAllMetodoPagos();
        json jsonResponse = json::array();
        for (const auto& metodoPago : metodoPagos)
        {
            jsonResponse.push_back(metodoPago);
        }
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    }
    catch(const std::exception& e)
    {
        json errorResponse = {{"error", "Error al obtener metodo de pago"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}

void MetodoPagosController::createMetodoPago(const Rest::Request& request, Http::ResponseWriter response){
    try
    {
        auto jsonBody = json::parse(request.body());
        MetodoPagos metodoPago = {
            0,
            jsonBody["nombre"].get<std::string>()
        };
        metodoPagosService.createMetodoPago(metodoPago);
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Created, "Metodo de pago creado");
    }
    catch(const std::exception& e)
    {
        json errorResponse = {{"error", "Error al crear metodo de pago"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }   
}

void MetodoPagosController::deleteMetodoPagoById(const Rest::Request& request, Http::ResponseWriter response){
    auto id = request.param(":id").as<int>();
    try
    {
        metodoPagosService.deleteMetodoPagoById(id);
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, "Metodo de pago eliminado");
    }
    catch(const std::exception& e)
    {
        json errorResponse = {{"error", "Error al eliminar metodo de pago"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}

void MetodoPagosController::updateMetodoPagoById(const Rest::Request& request, Http::ResponseWriter response){
    try
    {
        auto jsonBody = json::parse(request.body());
        MetodoPagos metodoPago = {
            request.param(":id").as<int>(),
            jsonBody["nombre"].get<std::string>()
        };
        metodoPagosService.updateMetodoPagoById(metodoPago);
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, "Metodo de pago actualizado");
    }
    catch(const std::exception& e)
    {
        json errorResponse = {{"error", "Error al actualizar metodo de pago"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}

void MetodoPagosController::getColumns(const Rest::Request& request, Http::ResponseWriter response){
    try
    {
        auto columns = metodoPagosService.getColumns();
        json jsonResponse = columns;
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    }
    catch(const std::exception& e)
    {
        json errorResponse = {{"error", "Error al obtener columnas"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}