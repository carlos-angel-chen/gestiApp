#include "Routes.h"
#include "../include/controllers/ProductosController.h"
#include "../include/controllers/ClientesController.h"

void handleOptions(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    response.headers()
        .add<Pistache::Http::Header::AccessControlAllowOrigin>("*")
        .add<Pistache::Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
        .add<Pistache::Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
    
    response.send(Pistache::Http::Code::No_Content);
}

void setupRoutes(Pistache::Rest::Router& router, DatabaseConnection& dbConn) {
    auto productosController = std::make_shared<ProductosController>(dbConn);
    auto clientesController = std::make_shared<ClientesController>(dbConn);

    using namespace Pistache::Rest;

    // PRODUCTOS
    Routes::Get(router, "/productos", Routes::bind(&ProductosController::getAllProducts, productosController));
    Routes::Get(router, "/productos/:id", Routes::bind(&ProductosController::getProductById, productosController));
    Routes::Get(router, "/productos/:sku", Routes::bind(&ProductosController::getProductBySKU, productosController));
    Routes::Post(router, "/productos", Routes::bind(&ProductosController::createProduct, productosController));
    Routes::Put(router, "/productos/:id", Routes::bind(&ProductosController::updateProduct, productosController));
    Routes::Delete(router, "/productos/:id", Routes::bind(&ProductosController::deleteProductById, productosController));
    // Routes::Delete(router, "/productos/SKU/:sku", Routes::bind(&ProductosController::deleteProductBySKU, productosController));
    Routes::Get(router, "/productos/columns", Routes::bind(&ProductosController::getColumns, productosController));

    // Asegúrate de no duplicar las rutas OPTIONS
    Routes::Options(router, "/productos", Routes::bind(&handleOptions));
    Routes::Options(router, "/productos/:id", Routes::bind(&handleOptions));
    Routes::Options(router, "/productos/SKU/:sku", Routes::bind(&handleOptions));

    // CLIENTES
    Routes::Get(router, "/clientes", Routes::bind(&ClientesController::getAllClients, clientesController));
    Routes::Get(router, "/clientes/nombre/:nombre", Routes::bind(&ClientesController::getClientsByNombre, clientesController));
}
