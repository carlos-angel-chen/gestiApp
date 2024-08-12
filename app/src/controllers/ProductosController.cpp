#include "../include/controllers/ProductosController.h"
#include <iostream>
#include <pqxx/pqxx>

ProductosController::ProductosController(DatabaseConnection& db) : dbConn(db) {}

void ProductosController::getAllProducts(const Rest::Request& request, Http::ResponseWriter response) {
    try{
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT * FROM public.\"Productos\"");

        std::string result = "[";
        bool first = true;
        for (auto row : res){
            if (!first) {
                result += ",";  // Agrega una coma entre objetos
            }
            first = false;
            result += "{ \"id\": " + std::string(row["id"].c_str()) + 
                      ", \"SKU\": \"" + std::string(row["\"SKU\""].c_str()) + 
                      "\", \"nombre\": \"" + std::string(row["nombre"].c_str()) + 
                      "\", \"stock_minimo\": \"" + std::string(row["stock_minimo"].c_str()) + 
                      "\", \"stock_actual\": \"" + std::string(row["stock_actual"].c_str()) + 
                      "\", \"id_tipo\": \"" + std::string(row["id_tipo"].c_str()) + 
                      "\" }";
        }
        result += "]";

        std::cout << result << std::endl;

        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");

        response.send(Http::Code::Ok, result);
    }catch(const std::exception &e){
        std::cerr << "Error al realizar la consulta: " << e.what() << std::endl;
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, "Error al obtener productos");
    }
}

void ProductosController::getProductoById(const Rest::Request& request, Http::ResponseWriter response) {
    auto id = request.param(":id").as<int>();
    try {
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT * FROM public.\"Productos\" WHERE id = " + txn.quote(id));

        if (res.size() == 1) {
            auto row = res[0];
            std::string result =    std::string("{\"id\": ") + row["id"].c_str() + 
                                    ", \"SKU\": \"" + row["\"SKU\""].c_str() + 
                                    "\", \"nombre\": \"" + row["nombre"].c_str() + 
                                    "\", \"stock_minimo\": \"" + row["stock_minimo"].c_str() +
                                    "\", \"stock_actual\": \"" + row["stock_actual"].c_str() +
                                    "\", \"id_tipo\": \"" + row["id_tipo"].c_str() +
                                    "\"}";

            response.headers()
                .add<Http::Header::AccessControlAllowOrigin>("*")
                .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
                .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
            response.send(Http::Code::Ok, result);
        } else {
            response.headers()
                .add<Http::Header::AccessControlAllowOrigin>("*")
                .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
                .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
            response.send(Http::Code::Not_Found, "Producto no encontrado");
        }
    } catch (const std::exception &e) {
        std::cerr << "Error al realizar la consulta: " << e.what() << std::endl;
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, "Error al obtener producto");
    }
}

void ProductosController::createProducto(const Rest::Request& request, Http::ResponseWriter response) {
    auto json = request.body();
    // Asume que el JSON tiene campos "SKU" y "nombre"
    // Parse JSON and insert into the database

    // Insertar la lógica de inserción aquí
    response.send(Http::Code::Created, "Producto creado");
}

void ProductosController::updateProducto(const Rest::Request& request, Http::ResponseWriter response) {
    auto id = request.param(":id").as<int>();
    auto json = request.body();
    // Asume que el JSON tiene campos "SKU" y "nombre"
    // Parse JSON and update the database entry

    // Insertar la lógica de actualización aquí
    response.send(Http::Code::Ok, "Producto actualizado");
}

void ProductosController::deleteProducto(const Rest::Request& request, Http::ResponseWriter response) {
    auto id = request.param(":id").as<int>();
    try {
        pqxx::work txn(*dbConn.getConnection());
        txn.exec("DELETE FROM public.\"Productos\" WHERE id = " + txn.quote(id));
        txn.commit();
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, "Producto eliminado");
    } catch (const std::exception &e) {
        std::cerr << "Error al realizar la consulta: " << e.what() << std::endl;
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, "Error al eliminar producto");
    }
}