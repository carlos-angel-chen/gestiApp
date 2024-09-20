#include <iostream>
#include "../include/services/PedidosService.h"

PedidosService::PedidosService(DatabaseConnection& db) : dbConn(db) {}

std::vector<Pedidos> PedidosService::getAllPedidos(){
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        std::string query = R"(SELECT
                pedido.id,
                producto."SKU",
                producto.nombre AS nombre,
                tipo.nombre AS tipo_producto,
                pedido.cantidad,
                precio.costo,
                precio.precio_venta,
                precio.precio_sin_iva,
                precio.precio_con_iva,
                precio.precio_minorista,
                precio.precio_mayorista,
                precio.precio_venta_minimo,
                (pedido.cantidad * precio.precio_venta) AS subtotal
            FROM
                public."Pedidos" pedido
            LEFT JOIN
                public."Productos" producto
            ON
                producto.id = pedido.id_producto
            LEFT JOIN
                public."TipoProductos" tipo
            ON
                producto.id_tipo = tipo.id
            LEFT JOIN
                public."Precios" precio
            ON
                producto.id = precio.id_producto;)";

        pqxx::result res = txn.exec_params(query);

        std::vector<Pedidos> pedidos;
        for (auto row : res){
            Pedidos p = {
                row["id"].as<int>(),
                row["\"SKU\""].as<std::string>(),
                row["nombre"].as<std::string>(),
                row["tipo_producto"].as<std::string>(),
                row["cantidad"].as<int>(),
                row["costo"].as<float>(),
                row["precio_venta"].as<float>(),
                row["precio_sin_iva"].as<float>(),
                row["precio_con_iva"].as<float>(),
                row["precio_minorista"].as<float>(),
                row["precio_mayorista"].as<float>(),
                row["precio_venta_minimo"].as<float>()
                //row["subtotal"].as<float>()
            };
            pedidos.push_back(p);
        }
        return pedidos;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al obtener pedidos: " << e.what() << std::endl;
        throw;  // Lanza la excepción para que sea capturada por el controlador
    }
}

std::vector<Pedidos> PedidosService::getPedidoById(int id){
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        std::string query = R"(SELECT
                pedido.id,
                producto."SKU",
                producto.nombre AS nombre,
                tipo.nombre AS tipo_producto,
                pedido.cantidad,
                precio.costo,
                precio.precio_venta,
                precio.precio_sin_iva,
                precio.precio_con_iva,
                precio.precio_minorista,
                precio.precio_mayorista,
                precio.precio_venta_minimo,
                (pedido.cantidad * precio.precio_venta) AS subtotal
            FROM
                public."Pedidos" pedido
            LEFT JOIN
                public."Productos" producto
            ON
                producto.id = pedido.id_producto
            LEFT JOIN
                public."TipoProductos" tipo
            ON
                producto.id_tipo = tipo.id
            LEFT JOIN
                public."Precios" precio
            ON
                producto.id = precio.id_producto
            WHERE pedido.id = $1;)";

        pqxx::result res = txn.exec_params(query, id);

        std::vector<Pedidos> pedidos;
        for (auto row : res){
            Pedidos p = {
                row["id"].as<int>(),
                row["\"SKU\""].as<std::string>(),
                row["nombre"].as<std::string>(),
                row["tipo_producto"].as<std::string>(),
                row["cantidad"].as<int>(),
                row["costo"].as<float>(),
                row["precio_venta"].as<float>(),
                row["precio_sin_iva"].as<float>(),
                row["precio_con_iva"].as<float>(),
                row["precio_minorista"].as<float>(),
                row["precio_mayorista"].as<float>(),
                row["precio_venta_minimo"].as<float>()
                //row["subtotal"].as<float>()
            };
            pedidos.push_back(p);
        }
        return pedidos;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al obtener pedido: " << e.what() << std::endl;
        throw;  // Lanza la excepción para que sea capturada por el controlador
    }
}

std::vector<std::string> PedidosService::getColumns(){
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        std::string query = R"(SELECT 'id' AS column_name
            UNION
            SELECT '\"SKU\"' AS column_name
            UNION
            SELECT 'nombre' AS column_name
            UNION
            SELECT 'tipo_producto' AS column_name
            UNION
            SELECT 'cantidad' AS column_name
            UNION
            SELECT 'costo' AS column_name
            UNION
            SELECT 'precio_venta' AS column_name
            UNION
            SELECT 'precio_sin_iva' AS column_name
            UNION
            SELECT 'precio_con_iva' AS column_name
            UNION
            SELECT 'precio_minorista' AS column_name
            UNION
            SELECT 'precio_mayorista' AS column_name
            UNION
            SELECT 'precio_venta_minimo' AS column_name
            --UNION
            --SELECT 'subtotal' AS column_name
        )";
        pqxx::result res = txn.exec_params(query);

        std::vector<std::string> columns;
        for (auto row : res) {
            columns.push_back(row["column_name"].as<std::string>());
        }
        return columns;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al obtener pedidos: " << e.what() << std::endl;
        throw;  // Lanza la excepción para que sea capturada por el controlador
    }
}