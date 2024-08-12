#include "Routes.h"
#include "../include/controllers/ProductosController.h"

void setupRoutes(Pistache::Rest::Router& router, DatabaseConnection& dbConn) {
    auto productosController = std::make_shared<ProductosController>(dbConn);

    using namespace Pistache::Rest;

    Routes::Get(router, "/productos", Routes::bind(&ProductosController::getAllProducts, productosController));
    Routes::Get(router, "/productos/:id", Routes::bind(&ProductosController::getProductoById, productosController));
    Routes::Post(router, "/productos", Routes::bind(&ProductosController::createProducto, productosController));
    Routes::Put(router, "/productos/:id", Routes::bind(&ProductosController::updateProducto, productosController));
    Routes::Delete(router, "/productos/:id", Routes::bind(&ProductosController::deleteProducto, productosController));
}