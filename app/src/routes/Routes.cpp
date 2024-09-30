#include "Routes.h"
#include "../include/controllers/ProductosController.h"
#include "../include/controllers/ClientesController.h"
#include "../include/controllers/LogisticaController.h"
#include "../include/controllers/MetodoPagosController.h"
#include "../include/controllers/PedidosController.h"
#include "../include/controllers/VentasController.h"

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
    auto logisticaController = std::make_shared<LogisticaController>(dbConn);
    auto metodoPagosController = std::make_shared<MetodoPagosController>(dbConn);
    auto pedidosController = std::make_shared<PedidosController>(dbConn);
    auto ventasController = std::make_shared<VentasController>(dbConn);

    using namespace Pistache::Rest;

    // PRODUCTOS
    Routes::Get(router, "/productos", Routes::bind(&ProductosController::getAllProducts, productosController));
    Routes::Get(router, "/productos/id/:id", Routes::bind(&ProductosController::getProductById, productosController));
    Routes::Get(router, "/productos/sku/:sku", Routes::bind(&ProductosController::getProductBySKU, productosController));
    Routes::Post(router, "/productos", Routes::bind(&ProductosController::createProduct, productosController));
    Routes::Put(router, "/productos/:id", Routes::bind(&ProductosController::updateProduct, productosController));
    Routes::Delete(router, "/productos/:id", Routes::bind(&ProductosController::deleteProductById, productosController));
    // Routes::Delete(router, "/productos/SKU/:sku", Routes::bind(&ProductosController::deleteProductBySKU, productosController));
    Routes::Get(router, "/productos/columns", Routes::bind(&ProductosController::getColumns, productosController));

    // Asegúrate de no duplicar las rutas OPTIONS
    Routes::Options(router, "/productos", Routes::bind(&handleOptions));
    Routes::Options(router, "/productos/:id", Routes::bind(&handleOptions));
    Routes::Options(router, "/productos/id/:id", Routes::bind(&handleOptions));
    Routes::Options(router, "/productos/sku/:sku", Routes::bind(&handleOptions));

    // CLIENTES
    Routes::Get(router, "/clientes", Routes::bind(&ClientesController::getAllClients, clientesController));
    Routes::Get(router, "/clientes/nombre/:nombre", Routes::bind(&ClientesController::getClientsByNombre, clientesController));
    Routes::Get(router, "/clientes/razon_social/:razonSocial", Routes::bind(&ClientesController::getClientsByRazonSocial, clientesController));
    Routes::Get(router, "/clientes/cuit/:cuit", Routes::bind(&ClientesController::getClientByCuit, clientesController));
    Routes::Post(router, "/clientes", Routes::bind(&ClientesController::createClient, clientesController));
    Routes::Put(router, "/clientes/:id", Routes::bind(&ClientesController::updateClientById, clientesController));
    Routes::Delete(router, "/clientes/:id", Routes::bind(&ClientesController::deleteClientById, clientesController));
    Routes::Get(router, "/clientes/columns", Routes::bind(&ClientesController::getColumns, clientesController));

    Routes::Options(router, "/clientes", Routes::bind(&handleOptions));
    Routes::Options(router, "/clientes/:id", Routes::bind(&handleOptions));

    // LOGISTICA
    Routes::Get(router, "/logistica", Routes::bind(&LogisticaController::getAllLogisticas, logisticaController));
    Routes::Get(router, "/logistica/nombre/:nombre", Routes::bind(&LogisticaController::getLogisticasByNombre, logisticaController));
    Routes::Get(router, "/logistica/razon_social/:razonSocial", Routes::bind(&LogisticaController::getLogisticasByRazonSocial, logisticaController));
    Routes::Get(router, "/logistica/cuit/:cuit", Routes::bind(&LogisticaController::getLogisticaByCuit, logisticaController));
    Routes::Post(router, "/logistica", Routes::bind(&LogisticaController::createLogistica, logisticaController));
    Routes::Put(router, "/logistica/:id", Routes::bind(&LogisticaController::updateLogisticaById, logisticaController));
    Routes::Delete(router, "/logistica/:id", Routes::bind(&LogisticaController::deleteLogisticaById, logisticaController));
    Routes::Get(router, "/logistica/columns", Routes::bind(&LogisticaController::getColumns, logisticaController));

    Routes::Options(router, "/logistica", Routes::bind(&handleOptions));
    Routes::Options(router, "/logistica/:id", Routes::bind(&handleOptions));

    // METODO PAGOS
    Routes::Get(router, "/metodo_pagos", Routes::bind(&MetodoPagosController::getAllMetodoPagos, metodoPagosController));
    Routes::Post(router, "/metodo_pagos", Routes::bind(&MetodoPagosController::createMetodoPago, metodoPagosController));
    Routes::Put(router, "/metodo_pagos/:id", Routes::bind(&MetodoPagosController::updateMetodoPagoById, metodoPagosController));
    Routes::Delete(router, "/metodo_pagos/:id", Routes::bind(&MetodoPagosController::deleteMetodoPagoById, metodoPagosController));
    Routes::Get(router, "/metodo_pagos/columns", Routes::bind(&MetodoPagosController::getColumns, metodoPagosController));
    
    Routes::Options(router, "/metodo_pagos", Routes::bind(&handleOptions));
    Routes::Options(router, "/metodo_pagos/:id", Routes::bind(&handleOptions));

    // PEDIDOS
    Routes::Get(router, "/pedidos", Routes::bind(&PedidosController::getAllPedidos, pedidosController));
    Routes::Get(router, "/pedidos/id/:id", Routes::bind(&PedidosController::getPedidoById, pedidosController));
    Routes::Get(router, "/pedidos/columns", Routes::bind(&PedidosController::getColumns, pedidosController));
    Routes::Get(router, "/pedidos/last_id", Routes::bind(&PedidosController::getLastId, pedidosController));
    Routes::Post(router, "/pedidos", Routes::bind(&PedidosController::createPedido, pedidosController));

    Routes::Options(router, "/pedidos", Routes::bind(&handleOptions));

    // VENTAS
    Routes::Get(router, "/ventas", Routes::bind(&VentasController::getAllVentas, ventasController));
    Routes::Get(router, "/ventas/id/:id", Routes::bind(&VentasController::getVentaById, ventasController));
    Routes::Post(router, "/ventas", Routes::bind(&VentasController::createVenta, ventasController));

    Routes::Options(router, "/ventas", Routes::bind(&handleOptions));
}
