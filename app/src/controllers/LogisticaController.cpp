#include "../include/controllers/LogisticaController.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

LogisticaController::LogisticaController(DatabaseConnection& db) : dbConn(db), logisticaService(db) {}

void LogisticaController::getAllLogisticas(const Rest::Request& request, Http::ResponseWriter response){
    try
    {
        auto logisticas = logisticaService.getAllLogisticas();
        json jsonResponse = json::array();
        for (const auto& logistica : logisticas)
        {
            jsonResponse.push_back(logistica);
        }
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    }
    catch(const std::exception& e)
    {
        json errorResponse = {{"error", "Error al obtener logistica"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}

void LogisticaController::getLogisticasByNombre(const Rest::Request& request, Http::ResponseWriter response){
    auto nombre = request.param(":nombre").as<std::string>();
    try
    {
        auto logisticas = logisticaService.getLogisticasByNombre(nombre);
        json jsonResponse = json::array();
        for (const auto& logistica : logisticas)
        {
            jsonResponse.push_back(logistica);
        }
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    }
    catch(const std::exception& e)
    {
        json errorResponse = {{"error", "Error al obtener logistica"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}

void LogisticaController::getLogisticasByRazonSocial(const Rest::Request& request, Http::ResponseWriter response){
    auto razonSocial = request.param(":razonSocial").as<std::string>();
    try
    {
        auto logisticas = logisticaService.getLogisticasByRazonSocial(razonSocial);
        json jsonResponse = json::array();
        for (const auto& logistica : logisticas)
        {
            jsonResponse.push_back(logistica);
        }
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    }
    catch(const std::exception& e)
    {
        json errorResponse = {{"error", "Error al obtener logistica"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}

void LogisticaController::getLogisticaByCuit(const Rest::Request& request, Http::ResponseWriter response){
    auto cuit = request.param(":cuit").as<std::string>();
    try
    {
        auto logistica = logisticaService.getLogisticaByCuit(cuit);
        json jsonResponse = logistica;
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    }
    catch(const std::exception& e)
    {
        json errorResponse = {{"error", "Error al obtener logistica"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}

void LogisticaController::createLogistica(const Rest::Request& request, Http::ResponseWriter response){
    try
    {
        auto jsonBody = json::parse(request.body());
        Logistica logistica = {
            0,
            jsonBody["razon_social"].get<std::string>(),
            jsonBody["CUIT"].get<std::string>(),
            jsonBody["direccion"].get<std::string>(),
            jsonBody["tipo"].get<std::string>(),
            jsonBody["nombre"].get<std::string>(),
            jsonBody["localidad"].get<std::string>(),
            jsonBody["telefono"].get<std::string>()
        };
        logisticaService.createLogistica(logistica);
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Created, "Logistica creada");
    }
    catch(const std::exception& e)
    {
        json errorResponse = {{"error", "Error al crear logistica"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}

void LogisticaController::updateLogisticaById(const Rest::Request& request, Http::ResponseWriter response){
    try
    {
        auto jsonBody = json::parse(request.body());
        Logistica logistica = {
            request.param(":id").as<int>(),
            jsonBody["razon_social"].get<std::string>(),
            jsonBody["CUIT"].get<std::string>(),
            jsonBody["direccion"].get<std::string>(),
            jsonBody["tipo"].get<std::string>(),
            jsonBody["nombre"].get<std::string>(),
            jsonBody["localidad"].get<std::string>(),
            jsonBody["telefono"].get<std::string>()
        };
        logisticaService.updateLogisticaById(logistica);
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, "Logistica actualizada");
    }
    catch(const std::exception& e)
    {
        json errorResponse = {{"error", "Error al actualizar logistica"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}

void LogisticaController::deleteLogisticaById(const Rest::Request& request, Http::ResponseWriter response){
    auto id = request.param(":id").as<int>();
    try
    {
        logisticaService.deleteLogisticaById(id);
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, "Logistica eliminada");
    }
    catch(const std::exception& e)
    {
        json errorResponse = {{"error", "Error al eliminar logistica"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}

void LogisticaController::getColumns(const Rest::Request& request, Http::ResponseWriter response){
    try
    {
        auto columns = logisticaService.getColumns();
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