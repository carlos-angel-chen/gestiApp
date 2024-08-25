#ifndef PRODUCTOS_SERVICE_H
#define PRODUCTOS_SERVICE_H

#include <pqxx/pqxx>
#include <vector>
#include <string>
#include "database/DatabaseConnection.h"

struct Producto {
    int id;
    std::string sku;
    std::string nombre;
    std::string stock_minimo;
    std::string stock_actual;
    std::string id_tipo;
};

class ProductosService {
public:
    explicit ProductosService(DatabaseConnection& db);

    std::vector<Producto> getAllProducts();
    Producto getProductById(int id);
    void createProduct(const Producto& producto);
    void deleteProductById(int id);
    void deleteProductBySKU(const std::string& sku);
    std::vector<std::string> getColumns();

private:
    DatabaseConnection& dbConn;
};

#endif // PRODUCTOS_SERVICE_H
