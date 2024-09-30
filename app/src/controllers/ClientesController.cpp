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

void ClientesController::getClientsByRazonSocial(const Rest::Request& request, Http::ResponseWriter response) {
    auto razonSocial = request.param(":razonSocial").as<std::string>();
    try{
        auto clientes = clientesService.getClientsByRazonSocial(razonSocial);
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

void ClientesController::getClientByCuit(const Rest::Request& request, Http::ResponseWriter response) {
    auto cuit = request.param(":cuit").as<std::string>();
    try{
        auto clientes = clientesService.getClientByCuit(cuit);
        json jsonResponse = json::array();
        for (const auto& c : clientes){
            jsonResponse.push_back(c);
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

void ClientesController::createClient(const Rest::Request& request, Http::ResponseWriter response) {
    try{
        auto jsonBody = json::parse(request.body());
        Clientes cliente = {
            0,
            jsonBody["razon_social"].get<std::string>(),
            jsonBody["CUIT"].get<std::string>(),
            jsonBody["tributacion"].get<std::string>(),
            jsonBody["telefono"].get<std::string>(),
            jsonBody["email"].get<std::string>(),
            jsonBody["nombre"].get<std::string>(),
            jsonBody["direccion_fiscal"].get<std::string>(),
            jsonBody["direccion_entrega"].get<std::string>(),
            jsonBody["localidad"].get<std::string>(),
            jsonBody["cp"].get<std::string>(),
            jsonBody["whatsapp"].get<std::string>()
        };
        clientesService.createClient(cliente);
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Created, "Cliente creado");
    }
    catch(const std::exception& e){
        json errorResponse = {{"error", "Error al crear cliente"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}

void ClientesController::updateClientById(const Rest::Request& request, Http::ResponseWriter response){
    try
    {
        auto jsonBody = json::parse(request.body());
        Clientes cliente = {
            request.param(":id").as<int>(),
            jsonBody["razon_social"].get<std::string>(),
            jsonBody["CUIT"].get<std::string>(),
            jsonBody["tributacion"].get<std::string>(),
            jsonBody["telefono"].get<std::string>(),
            jsonBody["email"].get<std::string>(),
            jsonBody["nombre"].get<std::string>(),
            jsonBody["direccion_fiscal"].get<std::string>(),
            jsonBody["direccion_entrega"].get<std::string>(),
            jsonBody["localidad"].get<std::string>(),
            jsonBody["cp"].get<std::string>(),
            jsonBody["whatsapp"].get<std::string>()
        };
        auto clienteUpdated = clientesService.updateClientById(cliente);
        json jsonResponse = clienteUpdated;
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    }
    catch(const std::exception& e)
    {
        json errorResponse = {{"error", "Error al actualizar cliente"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }    
}

void ClientesController::deleteClientById(const Rest::Request& request, Http::ResponseWriter response){
    auto id = request.param(":id").as<int>();
    try
    {
        clientesService.deleteClientById(id);
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, "Cliente eliminado");
    }
    catch(const std::exception& e)
    {
        json errorResponse = {{"error", "Error al eliminar cliente"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}

void ClientesController::getColumns(const Rest::Request& request, Http::ResponseWriter response){
    try
    {
        auto columns = clientesService.getColumns();
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