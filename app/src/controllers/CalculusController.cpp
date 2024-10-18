#include "../include/controllers/CalculusController.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

CalculusController::CalculusController(DatabaseConnection& db) : dbConn(db), calculusService(db) {}

void CalculusController::getTotalSales(const Rest::Request& request, Http::ResponseWriter response) {
    try{
        auto total = calculusService.getTotalSales();
        json jsonResponse = {{"totalSales", total}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    } 
    catch( const std::exception& e){
        json errorResponse = {{"error", "Error al obtener el total de ventas"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}

void CalculusController::getTotalProducts(const Rest::Request& request, Http::ResponseWriter response) {
    try{
        auto total = calculusService.getTotalProducts();
        json jsonResponse = {{"totalProducts", total}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    } 
    catch( const std::exception& e){
        json errorResponse = {{"error", "Error al obtener el total de productos"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}

void CalculusController::getTotalClients(const Rest::Request& request, Http::ResponseWriter response) {
    try{
        auto total = calculusService.getTotalClients();
        json jsonResponse = {{"totalClients", total}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    } 
    catch( const std::exception& e){
        json errorResponse = {{"error", "Error al obtener el total de clientes"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}

void CalculusController::getStockAlert(const Rest::Request& request, Http::ResponseWriter response) {
    try{
        auto total = calculusService.getStockAlert();
        json jsonResponse = {{"stockAlert", total}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    } 
    catch( const std::exception& e){
        json errorResponse = {{"error", "Error al obtener el stock alert"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}

void CalculusController::getMonthlySales(const Rest::Request& request, Http::ResponseWriter response) {
    try{
        auto monthlySales = calculusService.getMonthlySales();
        json jsonResponse = json::array();
        for (const auto& ms : monthlySales){
            // Crear un objeto JSON directamente a partir de los campos de ms
            json saleData = {
                {"month", ms.month},  // Si tienes getters, usa ms.getMonth()
                {"total_por_mes", ms.total_por_mes}
            };
            jsonResponse.push_back(saleData); // Añadir el objeto JSON al array
        }
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    } 
    catch( const std::exception& e){
        json errorResponse = {{"error", "Error al obtener las ventas mensuales"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}