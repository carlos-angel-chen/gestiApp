#include <iostream>
#include "../include/services/ProductosService.h"

ProductosService::ProductosService(DatabaseConnection& db) : dbConn(db) {}

std::vector<Productos> ProductosService::getAllProducts() {
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        std::string query = R"(SELECT
                producto.id,
                producto.sku,
                producto.nombre,
                tipo.nombre AS tipo_producto,
                producto.stock_minimo,
                producto.stock_actual,
                precio.costo AS costo,
                precio.precio_venta,
                precio.precio_sin_iva,
                precio.precio_con_iva,
                precio.precio_minorista,
                precio.precio_mayorista,
                precio.precio_venta_minimo
            FROM
                public."Productos" producto
            LEFT JOIN
                public."Precios" precio
            ON
                producto.id = precio.id_producto
            LEFT JOIN
                public."TipoProductos" tipo
            ON
                producto.id_tipo = tipo.id
            ORDER BY producto.id ASC;
        )";
        pqxx::result res = txn.exec_params(query);

        std::vector<Productos> productos;
        for (auto row : res) {
            Productos p = {
                row["id"].as<int>(),
                row["sku"].as<std::string>(),
                row["nombre"].as<std::string>(),
                row["tipo_producto"].as<std::string>(),
                row["stock_minimo"].as<int>(),
                row["stock_actual"].as<int>(),
                row["costo"].as<float>(),
                row["precio_venta"].as<float>(),
                row["precio_sin_iva"].as<float>(),
                row["precio_con_iva"].as<float>(),
                row["precio_minorista"].as<float>(),
                row["precio_mayorista"].as<float>(),
                row["precio_venta_minimo"].as<float>()
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
        std::string query = R"(
            SELECT 
                producto.id, 
                producto.sku, 
                producto.nombre, 
                tipo.nombre AS tipo_producto, 
                producto.stock_minimo, 
                producto.stock_actual, 
                precio.costo AS costo, 
                precio.precio_venta, 
                precio.precio_sin_iva, 
                precio.precio_con_iva, 
                precio.precio_minorista, 
                precio.precio_mayorista, 
                precio.precio_venta_minimo
            FROM public."Productos" producto
            LEFT JOIN public."Precios" precio 
                ON producto.id = precio.id_producto
            LEFT JOIN public."TipoProductos" tipo 
                ON producto.id_tipo = tipo.id
            WHERE producto.id = $1;
        )";
        pqxx::result res = txn.exec_params(query, id);

        if (res.size() != 1) {
            throw std::runtime_error("Producto no encontrado");
        }

        auto row = res[0];
        Productos p = {
            row["id"].as<int>(),
            row["sku"].as<std::string>(),
            row["nombre"].as<std::string>(),
            row["tipo_producto"].as<std::string>(),
            row["stock_minimo"].as<int>(),
            row["stock_actual"].as<int>(),
            row["costo"].as<float>(),
            row["precio_venta"].as<float>(),
            row["precio_sin_iva"].as<float>(),
            row["precio_con_iva"].as<float>(),
            row["precio_minorista"].as<float>(),
            row["precio_mayorista"].as<float>(),
            row["precio_venta_minimo"].as<float>()
        };

        txn.commit();
        return p;
    }
    catch (const std::exception& e) {
        std::cerr << "Error al obtener producto: " << e.what() << std::endl;
        throw;  // Lanza la excepción para que sea capturada por el controlador
    }
}

std::vector<Productos> ProductosService::getProductBySKU(const std::string& sku){
    try{
        pqxx::work txn(*dbConn.getConnection());
        std::string searchPattern = "%" + sku + "%";
        std::string query = R"(SELECT
                producto.id,
                producto.sku,
                producto.nombre,
                tipo.nombre AS tipo_producto,
                producto.stock_minimo,
                producto.stock_actual,
                precio.costo AS costo,
                precio.precio_venta,
                precio.precio_sin_iva,
                precio.precio_con_iva,
                precio.precio_minorista,
                precio.precio_mayorista,
                precio.precio_venta_minimo
            FROM
                public."Productos" producto
            LEFT JOIN
                public."Precios" precio
            ON
                producto.id = precio.id_producto
            LEFT JOIN
                public."TipoProductos" tipo
            ON
                producto.id_tipo = tipo.id
            WHERE producto."SKU" LIKE $1;
        )";
        pqxx::result res = txn.exec_params(query, searchPattern);
        //pqxx::result res = txn.exec("SELECT * FROM public.\"Productos\" WHERE \"SKU\" = " + txn.quote(sku));
        
        std::vector<Productos> productos;
        for (auto row : res){
            Productos p = {
                row["id"].as<int>(),
                row["sku"].as<std::string>(),
                row["nombre"].as<std::string>(),
                row["tipo_producto"].as<std::string>(),
                row["stock_minimo"].as<int>(),
                row["stock_actual"].as<int>(),
                row["costo"].as<float>(),
                row["precio_venta"].as<float>(),
                row["precio_sin_iva"].as<float>(),
                row["precio_con_iva"].as<float>(),
                row["precio_minorista"].as<float>(),
                row["precio_mayorista"].as<float>(),
                row["precio_venta_minimo"].as<float>()
            };
            productos.push_back(p);
        }
        txn.commit();
        return productos;
    }
    catch(const std::exception& e){
        std::cerr << "Error al obtener producto: " << e.what() << std::endl;
        throw;  // Lanza la excepción para que sea capturada por el controlador
    }
}

void ProductosService::createProduct(const Productos& productos) {
    try{
        pqxx::work txn(*dbConn.getConnection());
        int id_tipo;
        if (productos.tipo_producto == "Insumos"){
            id_tipo = 1;
        }
        else {
            id_tipo = 2;
        }
        std::string queryProducto = R"(INSERT INTO public."Productos"
                ("sku", "nombre", "id_tipo", "stock_minimo", "stock_actual")
                VALUES
                ($1, $2, $3, $4, $5);)";
        txn.exec_params(queryProducto, productos.sku, productos.nombre, id_tipo, productos.stock_minimo, productos.stock_actual);

        std::string queryPrecio = R"(INSERT INTO public."Precios"
                ("id_producto", "costo", "precio_venta", "precio_sin_iva", "precio_con_iva", "precio_minorista", "precio_mayorista", "precio_venta_minimo")
            VALUES
                ((SELECT id FROM public."Productos" ORDER BY id DESC LIMIT 1), $1, $2, $3, $4, $5, $6, $7);)";
        txn.exec_params(queryPrecio, productos.costo, productos.precio_venta, productos.precio_sin_iva, productos.precio_con_iva, productos.precio_minorista, productos.precio_mayorista, productos.precio_venta_minimo);

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
        int id_tipo;
        if (productos.tipo_producto == "Insumos"){
            id_tipo = 1;
        }
        else {
            id_tipo = 2;
        }
        std::string queryProducto = R"(UPDATE public."Productos" SET
                "sku" = $1,
                "nombre" = $2,
                "id_tipo" = $3,
                "stock_minimo" = $4,
                "stock_actual" = $5
            WHERE id = $6;)";
        txn.exec_params(queryProducto, productos.sku, productos.nombre, id_tipo, productos.stock_minimo, productos.stock_actual, productos.id);

        std::string queryPrecio = R"(UPDATE public."Precios" SET
                "costo" = $1,
                "precio_venta" = $2,
                "precio_sin_iva" = $3,
                "precio_con_iva" = $4,
                "precio_minorista" = $5,
                "precio_mayorista" = $6,
                "precio_venta_minimo" = $7
            WHERE id_producto = $8;)";
        txn.exec_params(queryPrecio, productos.costo, productos.precio_venta, productos.precio_sin_iva, productos.precio_con_iva, productos.precio_minorista, productos.precio_mayorista, productos.precio_venta_minimo, productos.id);
        txn.commit();
        
        Productos p = getProductById(productos.id);
        return p;
    }
    catch (const std::exception& e) {
        std::cerr << "Error al actualizar producto: " << e.what() << std::endl;
        throw;  // Lanza la excepción para que sea capturada por el controlador
    }
}

void ProductosService::deleteProductById(int id) {
    try{
        pqxx::work txn(*dbConn.getConnection());
        txn.exec("DELETE FROM public.\"Precios\" WHERE id_producto = " + txn.quote(id));
        txn.exec("DELETE FROM public.\"Productos\" WHERE id = " + txn.quote(id));
        txn.commit();
    }
    catch(const std::exception& e) {
        std::cerr << "Error al eliminar producto: " << e.what() << std::endl;
        throw;  // Lanza la excepción para que sea capturada por el controlador
    }
}

// void ProductosService::deleteProductBySKU(const std::string& sku) {
//     pqxx::work txn(*dbConn.getConnection());
//     txn.exec("DELETE FROM public.\"Productos\" WHERE \"SKU\" = " + txn.quote(sku));
//     txn.commit();
// }

std::vector<std::string> ProductosService::getColumns() {
    try{
        pqxx::work txn(*dbConn.getConnection());
        std::string query = R"(SELECT 'id' AS column_name
            UNION ALL
            SELECT 'sku' AS column_name
            UNION ALL
            SELECT 'nombre' AS column_name
            UNION ALL
            SELECT 'tipo_producto' AS column_name
            UNION ALL
            SELECT 'stock_minimo' AS column_name
            UNION ALL
            SELECT 'stock_actual' AS column_name
            UNION ALL
            SELECT 'costo' AS column_name
            UNION ALL
            SELECT 'precio_venta' AS column_name
            UNION ALL
            SELECT 'precio_sin_iva' AS column_name
            UNION ALL
            SELECT 'precio_con_iva' AS column_name
            UNION ALL
            SELECT 'precio_minorista' AS column_name
            UNION ALL
            SELECT 'precio_mayorista' AS column_name
            UNION ALL
            SELECT 'precio_venta_minimo' AS column_name)";
        pqxx::result res = txn.exec(query);

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
