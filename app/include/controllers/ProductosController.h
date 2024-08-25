#ifndef PRODUCTOS_CONTROLLER_H
#define PRODUCTOS_CONTROLLER_H

#include <pistache/http.h>
#include <pistache/router.h>
#include "database/DatabaseConnection.h"

using namespace Pistache;

class ProductosController {
public:
    explicit ProductosController(DatabaseConnection& db);

    void getAllProducts(const Rest::Request& request, Http::ResponseWriter response);
    void getProductoById(const Rest::Request& request, Http::ResponseWriter response);
    void createProducto(const Rest::Request& request, Http::ResponseWriter response);
    void updateProducto(const Rest::Request& request, Http::ResponseWriter response);
    void deleteProductoById(const Rest::Request& request, Http::ResponseWriter response);
    void getColumns(const Rest::Request& request, Http::ResponseWriter response);
    void deleteProductoBySKU(const Rest::Request& request, Http::ResponseWriter response);

private:
    DatabaseConnection& dbConn;
};

#endif // PRODUCTOS_CONTROLLER_H