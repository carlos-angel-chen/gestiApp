#include "../include/controllers/ClientesController.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

ClientesController::ClientesController(DatabaseConnection& db) : dbConn(db), clientesService(db) {}

void ClientesController::getAllClients(const Rest::Request& request, Http::ResponseWriter response) {
    try{
        auto clientes = clientesService.getAllClients();
        json jsonResponse = json::array();
        for (const auto& cliente : clientes){
            jsonResponse.push_back(cliente);
        }
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    } 
    catch( const std::exception& e){
        json errorResponse = {{"error", "Error al obtener clientes"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}

void ClientesController::getClientsByNombre(const Rest::Request& request, Http::ResponseWriter response) {
    auto nombre = request.param(":nombre").as<std::string>();
    try{
        auto clientes = clientesService.getClientsByNombre(nombre);
        json jsonResponse = json::array();
        for (const auto& cliente : clientes){
            jsonResponse.push_back(cliente);
        }
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    }
    catch(const std::exception& e){
        json errorResponse = {{"error", "Error al obtener clientes"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}