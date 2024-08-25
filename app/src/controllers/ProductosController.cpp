#include "../include/controllers/ProductosController.h"
#include <iostream>
#include <pqxx/pqxx>
#include <nlohmann/json.hpp>

// Alias para facilitar el uso de json:
using json = nlohmann::json;


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
    try {
        auto json = nlohmann::json::parse(request.body());

        // SKU y nombre son obligatorios
        std::string sku = json["SKU"].get<std::string>();
        std::string nombre = json["nombre"].get<std::string>();
        std::string stock_minimo = json["stock_minimo"].get<std::string>();
        std::string stock_actual = json["stock_actual"].get<std::string>();
        std::string id_tipo = json["id_tipo"].get<std::string>();

        pqxx::work txn(*dbConn.getConnection());
        std::string query = "INSERT INTO public.\"Productos\" (\"SKU\", \"nombre\", \"stock_minimo\", \"stock_actual\", \"id_tipo\") VALUES (" +
                            txn.quote(sku) + ", " + txn.quote(nombre);  // Se asume que SKU y nombre son obligatorios
        
        if ((stock_minimo != "") && (stock_actual != "") && (id_tipo != "")) {
            query = "INSERT INTO public.\"Productos\" (\"SKU\", \"nombre\", \"stock_minimo\", \"stock_actual\", \"id_tipo\") VALUES (" +
                            txn.quote(sku) + ", " + txn.quote(nombre) + ", " + txn.quote(stock_minimo) + ", " + txn.quote(stock_actual) + ", " + txn.quote(id_tipo) + ")";
        }
        else if ((stock_minimo != "") && (stock_actual != "")){
            query = "INSERT INTO public.\"Productos\" (\"SKU\", \"nombre\", \"stock_minimo\", \"stock_actual\") VALUES (" +
                            txn.quote(sku) + ", " + txn.quote(nombre) + ", " + txn.quote(stock_minimo) + ", " + txn.quote(stock_actual) + ")";
        }
        else if ((stock_minimo != "") && (id_tipo != "")) {
            query = "INSERT INTO public.\"Productos\" (\"SKU\", \"nombre\", \"stock_minimo\", \"id_tipo\") VALUES (" +
                            txn.quote(sku) + ", " + txn.quote(nombre) + ", " + txn.quote(stock_minimo) + ", " + txn.quote(id_tipo) + ")";
        }
        else if ((stock_actual != "") && (id_tipo != "")) {
            query = "INSERT INTO public.\"Productos\" (\"SKU\", \"nombre\", \"stock_actual\", \"id_tipo\") VALUES (" +
                            txn.quote(sku) + ", " + txn.quote(nombre) + ", " + txn.quote(stock_actual) + ", " + txn.quote(id_tipo) + ")";
        }
        else if (stock_minimo != ""){
            query = "INSERT INTO public.\"Productos\" (\"SKU\", \"nombre\", \"stock_minimo\") VALUES (" +
                            txn.quote(sku) + ", " + txn.quote(nombre) + ", " + txn.quote(stock_minimo) + ")";
        }
        else if (stock_actual != ""){
            query = "INSERT INTO public.\"Productos\" (\"SKU\", \"nombre\", \"stock_actual\") VALUES (" +
                            txn.quote(sku) + ", " + txn.quote(nombre) + ", " + txn.quote(stock_actual) + ")";
        }
        else if (id_tipo != ""){
            query = "INSERT INTO public.\"Productos\" (\"SKU\", \"nombre\", \"id_tipo\") VALUES (" +
                            txn.quote(sku) + ", " + txn.quote(nombre) + ", " + txn.quote(id_tipo) + ")";
        }
        else {
            query = "INSERT INTO public.\"Productos\" (\"SKU\", \"nombre\") VALUES (" +
                            txn.quote(sku) + ", " + txn.quote(nombre) + ")";
        }
        
        txn.exec(query);
        txn.commit();

        response.send(Http::Code::Created, "Producto creado");
    } catch (const std::exception &e) {
        std::cerr << "Error al crear producto: " << e.what() << std::endl;
        response.send(Http::Code::Internal_Server_Error, "Error al crear producto");
    }
}

void ProductosController::updateProducto(const Rest::Request& request, Http::ResponseWriter response) {
    auto id = request.param(":id").as<int>();
    auto json = request.body();
    // Asume que el JSON tiene campos "SKU" y "nombre"
    // Parse JSON and update the database entry

    // Insertar la lógica de actualización aquí
    response.send(Http::Code::Ok, "Producto actualizado");
}

void ProductosController::deleteProductoById(const Rest::Request& request, Http::ResponseWriter response) {
    auto id = request.param(":id").as<int>();
    try {
        pqxx::work txn(*dbConn.getConnection());
        txn.exec("DELETE FROM public.\"Productos\" WHERE id = " + txn.quote(id));
        txn.commit();

        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")  // Permitir todas las fuentes
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")  // Métodos permitidos
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");

        response.send(Http::Code::Ok, "Producto eliminado");
    } catch (const std::exception &e) {
        std::cerr << "Error al realizar la consulta: " << e.what() << std::endl;

        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")  // Permitir todas las fuentes
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")  // Métodos permitidos
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");

        response.send(Http::Code::Internal_Server_Error, "Error al eliminar el producto");
    }
}

void ProductosController::deleteProductoBySKU(const Rest::Request& request, Http::ResponseWriter response) {
    auto sku = request.param(":sku").as<int>();
    try {
        pqxx::work txn(*dbConn.getConnection());
        txn.exec("DELETE FROM public.\"Productos\" WHERE \"SKU\" = " + txn.quote(sku));
        txn.commit();

        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")  // Permitir todas las fuentes
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")  // Métodos permitidos
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");

        response.send(Http::Code::Ok, "Producto eliminado");
    } catch (const std::exception &e) {
        std::cerr << "Error al realizar la consulta: " << e.what() << std::endl;

        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")  // Permitir todas las fuentes
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")  // Métodos permitidos
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");

        response.send(Http::Code::Internal_Server_Error, "Error al eliminar el producto");
    }
}

void ProductosController::getColumns(const Rest::Request& request, Http::ResponseWriter response) {
    try {
        pqxx::work txn(*dbConn.getConnection());
        pqxx::result res = txn.exec("SELECT column_name FROM information_schema.columns WHERE table_name = 'Productos' AND table_schema = 'public'");

        std::string result = "[";
        bool first = true;
        for (auto row : res) {
            if (!first) {
                result += ",";
            }
            first = false;
            result += "\"" + std::string(row["column_name"].c_str()) + "\"";
        }
        result += "]";

        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");

        response.send(Http::Code::Ok, result);
    } catch (const std::exception &e) {
        std::cerr << "Error al obtener columnas: " << e.what() << std::endl;
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, "Error al obtener columnas");
    }
}