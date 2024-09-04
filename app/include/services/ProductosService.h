#ifndef PRODUCTOS_SERVICE_H
#define PRODUCTOS_SERVICE_H

#include <pqxx/pqxx>
#include <vector>
#include "../models/Productos.h"
#include "database/DatabaseConnection.h"

class ProductosService {
public:
    explicit ProductosService(DatabaseConnection& db);

    std::vector<Productos> getAllProducts();
    Productos getProductById(int id);
    std::vector<Productos> getProductBySKU(const std::string& sku);
    void createProduct(const Productos& productos);
    Productos updateProductById(const Productos& productos);
    void deleteProductById(int id);
    // void deleteProductBySKU(const std::string& sku);
    std::vector<std::string> getColumns();

private:
    DatabaseConnection& dbConn;
};

#endif // PRODUCTOS_SERVICE_H
