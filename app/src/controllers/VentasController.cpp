#include "../include/controllers/VentasController.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

VentasController::VentasController(DatabaseConnection& db) : dbConn(db), ventasService(db) {}

void VentasController::getAllVentas(const Rest::Request& request, Http::ResponseWriter response){
    try
    {
        auto ventas = ventasService.getAllVentas();
        json jsonResponse = json::array();
        for (const auto& venta : ventas)
        {
            jsonResponse.push_back(venta);
        }

        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    }
    catch(const std::exception& e)
    {
        json errorResponse = {{"error", "Error al obtener ventas"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");

        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}

void VentasController::getVentaById(const Rest::Request& request, Http::ResponseWriter response){
    try
    {
        auto id = request.param(":id").as<int>();
        auto venta = ventasService.getVentasById(id);
        json jsonResponse = venta;
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
        response.send(Http::Code::Not_Found, "Venta no encontrada por ID");
    }    
}

void VentasController::createVenta(const Rest::Request& request, Http::ResponseWriter response){
    try
    {
        auto jsonBody = json::parse(request.body());
        Ventas venta = {
            0,
            jsonBody["id_pedido"].get<int>(),
            jsonBody["fecha"].get<std::string>(),
            jsonBody["id_cliente"].get<int>(),
            jsonBody["nombre_cliente"].get<std::string>(),
            jsonBody["id_logistica"].get<int>(),
            jsonBody["logistica"].get<std::string>(),
            jsonBody["id_metodo_pago"].get<int>(),
            jsonBody["metodo_pago"].get<std::string>(),
            jsonBody["subtotal"].get<float>(),
            jsonBody["descuento"].get<float>(),
            jsonBody["precio_final_pesos"].get<float>(),
            jsonBody["precio_final_usd"].get<float>(),
            jsonBody["observaciones"].get<std::string>()
        };
        ventasService.createVentas(venta);
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Created, "Venta creada");
    }
    catch(const std::exception& e)
    {
        json errorResponse = {{"error", "Error al crear venta"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}