#include <iostream>
#include "../include/services/ProductosService.h"

ProductosService::ProductosService(DatabaseConnection& db) : dbConn(db) {}

std::vector<Productos> ProductosService::getAllProducts() {
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT * FROM public.\"Productos\"");

        std::vector<Productos> productos;
        for (auto row : res) {
            Productos p = {
                row["id"].as<int>(),
                row["\"SKU\""].as<std::string>(),
                row["nombre"].as<std::string>(),
                !row["stock_minimo"].is_null() ? row["stock_minimo"].as<std::string>() : "", // Manejar valores NULL
                !row["stock_actual"].is_null() ? row["stock_actual"].as<std::string>() : "", // Manejar valores NULL
                !row["id_tipo"].is_null() ? row["id_tipo"].as<std::string>() : ""            // Manejar valores NULL
            };
            productos.push_back(p);
        }
        return productos;
    }
    catch (const std::exception& e) {
        std::cerr << "Error al obtener productos: " << e.what() << std::endl;
        throw;  // Lanza la excepción para que sea capturada por el controlador
    }    
}

Productos ProductosService::getProductById(int id) {
    try{
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT * FROM public.\"Productos\" WHERE id = " + txn.quote(id));

        if (res.size() != 1) {
            throw std::runtime_error("Producto no encontrado");
        }

        auto row = res[0];
        Productos p = {
            row["id"].as<int>(),
            row["\"SKU\""].as<std::string>(),
            row["nombre"].as<std::string>(),
            row["stock_minimo"].is_null() ? std::nullopt : std::optional<std::string>(row["stock_minimo"].as<std::string>()),
            row["stock_actual"].is_null() ? std::nullopt : std::optional<std::string>(row["stock_actual"].as<std::string>()),
            row["id_tipo"].is_null() ? std::nullopt : std::optional<std::string>(row["id_tipo"].as<std::string>())
        };
        return p;
    }
    catch (const std::exception& e) {
        std::cerr << "Error al obtener producto: " << e.what() << std::endl;
        throw;  // Lanza la excepción para que sea capturada por el controlador
    }
}
    

void ProductosService::createProduct(const Productos& productos) {
    try{
        pqxx::work txn(*dbConn.getConnection());

        // Inicia la consulta base con las columnas obligatorias
        std::string query = "INSERT INTO public.\"Productos\" (\"SKU\", \"nombre\", \"id_tipo\"";

        // Verifica si stock_minimo no es nulo, en ese caso agrega la columna a la consulta
        if (productos.stock_minimo.has_value() && productos.stock_minimo!="") {
            query += ", \"stock_minimo\"";
        }

        // Verifica si stock_actual no es nulo, en ese caso agrega la columna a la consulta
        if (productos.stock_actual.has_value() && productos.stock_actual!="") {
            query += ", \"stock_actual\"";
        }

        // Cierra la parte de las columnas
        query += ") VALUES (" + txn.quote(productos.sku) + ", " + txn.quote(productos.nombre) + ", " + txn.quote(productos.id_tipo);

        // Agrega los valores para stock_minimo y stock_actual si están presentes
        if (productos.stock_minimo.has_value() && productos.stock_minimo!="") {
            query += ", " + txn.quote(productos.stock_minimo.value());
        }

        if (productos.stock_actual.has_value() && productos.stock_actual!="") {
            query += ", " + txn.quote(productos.stock_actual.value());
        }

        // Cierra la consulta SQL
        query += ")";

        // Ejecuta la consulta y realiza el commit
        txn.exec(query);
        txn.commit();
    }
    catch(const std::exception& e) {
        std::cerr << "Error al crear producto: " << e.what() << std::endl;
        throw;  // Lanza la excepción para que sea capturada por el controlador
    }
}

Productos ProductosService::updateProductById(const Productos& productos){
    try{
        pqxx::work txn(*dbConn.getConnection());
        std::string query = "UPDATE public.\"Productos\" SET ";
        query += "\"SKU\" = " + txn.quote(productos.sku) + ", ";
        query += "\"nombre\" = " + txn.quote(productos.nombre) + ", ";
        query += "\"stock_minimo\" = " + txn.quote(productos.stock_minimo.value_or("")) + ", ";
        query += "\"stock_actual\" = " + txn.quote(productos.stock_actual.value_or("")) + ", ";
        query += "\"id_tipo\" = " + txn.quote(productos.id_tipo.value_or("")) + " ";
        query += "WHERE \"id\" = " + txn.quote(productos.id) + " RETURNING *";
        
        txn.exec(query);

        pqxx::result res = txn.exec("SELECT * FROM public.\"Productos\" WHERE id = " + txn.quote(productos.id));

        auto row = res[0];
        Productos p = {
            row["id"].as<int>(),
            row["\"SKU\""].as<std::string>(),
            row["nombre"].as<std::string>(),
            row["stock_minimo"].is_null() ? std::nullopt : std::optional<std::string>(row["stock_minimo"].as<std::string>()),
            row["stock_actual"].is_null() ? std::nullopt : std::optional<std::string>(row["stock_actual"].as<std::string>()),
            row["id_tipo"].is_null() ? std::nullopt : std::optional<std::string>(row["id_tipo"].as<std::string>())
        };

        txn.commit();
        return p;
    }
    catch (const std::exception& e) {
        std::cerr << "Error al actualizar producto: " << e.what() << std::endl;
        throw;  // Lanza la excepción para que sea capturada por el controlador
    }
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
    try{
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT column_name FROM information_schema.columns WHERE table_name = 'Productos' AND table_schema = 'public'");

        std::vector<std::string> columns;
        for (auto row : res) {
            columns.push_back(row["column_name"].as<std::string>());
        }
        return columns;
    }
    catch(const std::exception& e) {
        std::cerr << "Error al obtener columnas: " << e.what() << std::endl;
        throw;  // Lanza la excepción para que sea capturada por el controlador
    }
}
