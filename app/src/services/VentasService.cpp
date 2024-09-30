#include <iostream>
#include "../include/services/VentasService.h"

VentasService::VentasService(DatabaseConnection& db) : dbConn(db) {}

std::vector<Ventas> VentasService::getAllVentas() {
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        std::string query = R"(
            SELECT 
                ventas.id,
                ventas.id_pedido,
                ventas.fecha,
                clientes.id AS id_cliente,
                clientes.nombre AS nombre_cliente,
                logistica.id AS id_logistica,
                logistica.razon_social AS logistica,
                metod_pago.id AS id_metodo_pago,
                metod_pago.nombre AS metodo_pago,
                ventas.subtotal,
                ventas.descuento,
                ventas.precio_final_pesos,
                ventas.precio_final_usd,
                ventas.observaciones
            FROM 
                public."Ventas" ventas
            LEFT JOIN
                public."Clientes" clientes
            ON
                ventas.id_cliente = clientes.id
            LEFT JOIN
                public."Logistica" logistica
            ON
                ventas.id_logistica = logistica.id
            LEFT JOIN
                public."MetodoPagos" metod_pago
            ON
                ventas.id_metodo_pago = metod_pago.id
        )";
        pqxx::result res = txn.exec_params(query);

        std::vector<Ventas> ventas;
        for(auto row : res){
            Ventas v = {
                row["id"].as<int>(),
                row["id_pedido"].as<int>(),
                row["fecha"].as<std::string>(),
                row["id_cliente"].as<int>(),
                row["nombre_cliente"].as<std::string>(),
                row["id_logistica"].as<int>(),
                row["logistica"].as<std::string>(),
                row["id_metodo_pago"].as<int>(),
                row["metodo_pago"].as<std::string>(),
                row["subtotal"].as<float>(),
                row["descuento"].as<float>(),
                row["precio_final_pesos"].as<float>(),
                row["precio_final_usd"].as<float>(),
                row["observaciones"].as<std::string>()
            };
            ventas.push_back(v);
        }
        return ventas;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al obtener ventas: " << e.what() << std::endl;
        throw;  // Lanza la excepción para que sea capturada por el controlador
    }
}

Ventas VentasService::getVentasById(int id) {
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        std::string query = R"(
            SELECT 
                ventas.id,
                ventas.id_pedido,
                ventas.fecha,
                clientes.id AS id_cliente,
                clientes.nombre AS nombre_cliente,
                logistica.id AS id_logistica,
                logistica.razon_social AS logistica,
                metod_pago.id AS id_metodo_pago,
                metod_pago.nombre AS metodo_pago,
                ventas.subtotal,
                ventas.descuento,
                ventas.precio_final_pesos,
                ventas.precio_final_usd,
                ventas.observaciones
            FROM 
                public."Ventas" ventas
            LEFT JOIN
                public."Clientes" clientes
            ON
                ventas.id_cliente = clientes.id
            LEFT JOIN
                public."Logistica" logistica
            ON
                ventas.id_logistica = logistica.id
            LEFT JOIN
                public."MetodoPagos" metod_pago
            ON
                ventas.id_metodo_pago = metod_pago.id
            WHERE ventas.id = $1;
        )";
        pqxx::result res = txn.exec_params(query, id);

        if (res.size() != 1) {
            throw std::runtime_error("Venta no encontrada");
        }

        auto row = res[0];
        Ventas v = {
            row["id"].as<int>(),
            row["id_pedido"].as<int>(),
            row["fecha"].as<std::string>(),
            row["id_cliente"].as<int>(),
            row["nombre_cliente"].as<std::string>(),
            row["id_logistica"].as<int>(),
            row["logistica"].as<std::string>(),
            row["id_metodo_pago"].as<int>(),
            row["metodo_pago"].as<std::string>(),
            row["subtotal"].as<float>(),
            row["descuento"].as<float>(),
            row["precio_final_pesos"].as<float>(),
            row["precio_final_usd"].as<float>(),
            row["observaciones"].as<std::string>()
        };

        txn.commit();
        return v;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al obtener venta: " << e.what() << std::endl;
        throw;  // Lanza la excepción para que sea capturada por el controlador
    }
}

void VentasService::createVentas(const Ventas& ventas){
    try
    {
        pqxx::work txn(*dbConn.getConnection());
        std::string queryVenta = R"(
            INSERT INTO public."Ventas" ("id_cliente", "id_pedido", "id_logistica", "fecha", "subtotal", "descuento", "precio_final_usd", "id_metodo_pago", "precio_final_pesos", "observaciones")
            VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10);
        )";
        txn.exec_params(queryVenta, 
                        ventas.id_cliente,
                        ventas.id_pedido,
                        ventas.id_logistica,
                        ventas.fecha,
                        ventas.subtotal,
                        ventas.descuento,
                        ventas.precio_final_usd,
                        ventas.id_metodo_pago,
                        ventas.precio_final_pesos,
                        ventas.observaciones);
        txn.commit();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error al crear venta: " << e.what() << std::endl;
        throw;  // Lanza la excepción para que sea capturada por el controlador
    }
}