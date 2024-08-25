#include "../include/services/ProductosService.h"

ProductosService::ProductosService(DatabaseConnection& db) : dbConn(db) {}

std::vector<Producto> ProductosService::getAllProducts() {
    pqxx::work txn(*dbConn.getConnection());
    pqxx::result res = txn.exec("SELECT * FROM public.\"Productos\"");

    std::vector<Producto> productos;
    for (auto row : res) {
        Producto p = {
            row["id"].as<int>(),
            row["SKU"].as<std::string>(),
            row["nombre"].as<std::string>(),
            row["stock_minimo"].as<std::string>(),
            row["stock_actual"].as<std::string>(),
            row["id_tipo"].as<std::string>()
        };
        productos.push_back(p);
    }
    return productos;
}

Producto ProductosService::getProductById(int id) {
    pqxx::work txn(*dbConn.getConnection());
    pqxx::result res = txn.exec("SELECT * FROM public.\"Productos\" WHERE id = " + txn.quote(id));

    if (res.size() != 1) {
        throw std::runtime_error("Producto no encontrado");
    }

    auto row = res[0];
    Producto p = {
        row["id"].as<int>(),
        row["SKU"].as<std::string>(),
        row["nombre"].as<std::string>(),
        row["stock_minimo"].as<std::string>(),
        row["stock_actual"].as<std::string>(),
        row["id_tipo"].as<std::string>()
    };
    return p;
}

void ProductosService::createProduct(const Producto& producto) {
    pqxx::work txn(*dbConn.getConnection());
    std::string query = "INSERT INTO public.\"Productos\" (\"SKU\", \"nombre\", \"stock_minimo\", \"stock_actual\", \"id_tipo\") VALUES (" +
                        txn.quote(producto.sku) + ", " + txn.quote(producto.nombre) + ", " + txn.quote(producto.stock_minimo) + ", " + txn.quote(producto.stock_actual) + ", " + txn.quote(producto.id_tipo) + ")";
    txn.exec(query);
    txn.commit();
}

void ProductosService::deleteProductById(int id) {
    pqxx::work txn(*dbConn.getConnection());
    txn.exec("DELETE FROM public.\"Productos\" WHERE id = " + txn.quote(id));
    txn.commit();
}

void ProductosService::deleteProductBySKU(const std::string& sku) {
    pqxx::work txn(*dbConn.getConnection());
    txn.exec("DELETE FROM public.\"Productos\" WHERE \"SKU\" = " + txn.quote(sku));
    txn.commit();
}

std::vector<std::string> ProductosService::getColumns() {
    pqxx::work txn(*dbConn.getConnection());
    pqxx::result res = txn.exec("SELECT column_name FROM information_schema.columns WHERE table_name = 'Productos' AND table_schema = 'public'");

    std::vector<std::string> columns;
    for (auto row : res) {
        columns.push_back(row["column_name"].as<std::string>());
    }
    return columns;
}
