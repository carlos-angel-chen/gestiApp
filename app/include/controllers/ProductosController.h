#ifndef PRODUCTOS_CONTROLLER_H
#define PRODUCTOS_CONTROLLER_H

#include <pistache/http.h>
#include <pistache/router.h>
#include "database/DatabaseConnection.h"
#include "../services/ProductosService.h"

using namespace Pistache;

class ProductosController {
public:
    explicit ProductosController(DatabaseConnection& db);

    void getAllProducts(const Rest::Request& request, Http::ResponseWriter response);
    void getProductById(const Rest::Request& request, Http::ResponseWriter response);
    void getProductBySKU(const Rest::Request& request, Http::ResponseWriter response);
    void createProduct(const Rest::Request& request, Http::ResponseWriter response);
    void updateProduct(const Rest::Request& request, Http::ResponseWriter response);
    void deleteProductById(const Rest::Request& request, Http::ResponseWriter response);
    void getColumns(const Rest::Request& request, Http::ResponseWriter response);
    // void deleteProductBySKU(const Rest::Request& request, Http::ResponseWriter response);

private:
    DatabaseConnection& dbConn;
    ProductosService productService;
};

#endif // PRODUCTOS_CONTROLLER_H