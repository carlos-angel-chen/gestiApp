#ifndef PRODUCTOS_SERVICE_H
#define PRODUCTOS_SERVICE_H

#include <pqxx/pqxx>
#include <vector>
#include "../models/Productos.h"
#include "database/DatabaseConnection.h"

class ProductosService {
public:
    // Constructor de la clase ProductosService, db es una referencia a DatabaseConnection
    // "explicit" Previene la conversión implícita de tipos, asegurando que el constructor solo pueda ser llamado con un DatabaseConnection
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
    // Proporciona acceso a la base de datos para realizar consultas SQL.
    // no se crea una nueva instancia, sino que se utiliza una existente, asi evito la sobrecarga de múltiples conexiones
    DatabaseConnection& dbConn;
};

#endif // PRODUCTOS_SERVICE_H
