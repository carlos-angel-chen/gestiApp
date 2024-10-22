#include "../include/controllers/ProductosController.h"
#include <nlohmann/json.hpp>

// Alias para facilitar el uso de json:
using json = nlohmann::json;


ProductosController::ProductosController(DatabaseConnection& db) : dbConn(db), productService(db) {}

void ProductosController::getAllProducts(const Rest::Request& request, Http::ResponseWriter response) {
    try {
        auto productos = productService.getAllProducts();
        json jsonResponse = json::array();
        for (const auto& producto : productos) {
            jsonResponse.push_back(producto);  // Usamos la función to_json
        }

        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    } catch (const std::exception& e) {
        // Encabezados CORS en caso de error también
        json errorResponse = {{"error", "Error al obtener productos"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");

        response.send(Http::Code::Internal_Server_Error, "Error al obtener productos");
    }
}

void ProductosController::getProductById(const Rest::Request& request, Http::ResponseWriter response) {
    auto id = request.param(":id").as<int>();
    try {
        auto producto = productService.getProductById(id);
        json jsonResponse = producto;
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    } catch (const std::exception& e) {
        // Encabezados CORS en caso de error también
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Not_Found, "Producto no encontrado por ID");
    }
}

void ProductosController::getProductBySKU(const Rest::Request& request, Http::ResponseWriter response){
    auto sku = request.param(":sku").as<std::string>();
    try{
        auto productos = productService.getProductBySKU(sku);
        json jsonResponse = json::array();
        for (const auto& producto : productos){
            jsonResponse.push_back(producto);
        }
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    }
    catch(const std::exception& e){
        // Encabezados CORS en caso de error también
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Not_Found, "Producto no encontrado por SKU");
    }
}

void ProductosController::createProduct(const Rest::Request& request, Http::ResponseWriter response) {
    try {
        auto jsonBody = json::parse(request.body());
        Productos producto = {
            0,
            jsonBody["sku"].get<std::string>(),
            jsonBody["nombre"].get<std::string>(),
            jsonBody["tipo_producto"].get<std::string>(),
            jsonBody["stock_minimo"].get<int>(),
            jsonBody["stock_actual"].get<int>(),
            jsonBody["costo"].get<float>(),
            jsonBody["precio_venta"].get<float>(),
            jsonBody["precio_sin_iva"].get<float>(),
            jsonBody["precio_con_iva"].get<float>(),
            jsonBody["precio_minorista"].get<float>(),
            jsonBody["precio_mayorista"].get<float>(),
            jsonBody["precio_venta_minimo"].get<float>()
        };

        productService.createProduct(producto);
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Created, "Producto creado");
    } catch (const std::exception& e) {
        // Encabezados CORS en caso de error también
        json errorResponse = {{"error", "Error al crear producto"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}

void ProductosController::updateProduct(const Rest::Request& request, Http::ResponseWriter response) {
    try {
        auto jsonBody = json::parse(request.body());
        Productos producto = {
            request.param(":id").as<int>(),
            jsonBody["sku"].get<std::string>(),
            jsonBody["nombre"].get<std::string>(),
            jsonBody["tipo_producto"].get<std::string>(),
            jsonBody["stock_minimo"].get<int>(),
            jsonBody["stock_actual"].get<int>(),
            jsonBody["costo"].get<float>(),
            jsonBody["precio_venta"].get<float>(),
            jsonBody["precio_sin_iva"].get<float>(),
            jsonBody["precio_con_iva"].get<float>(),
            jsonBody["precio_minorista"].get<float>(),
            jsonBody["precio_mayorista"].get<float>(),
            jsonBody["precio_venta_minimo"].get<float>()
        };

        auto productoUpdated = productService.updateProductById(producto);
        json jsonResponse = productoUpdated;
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    } catch (const std::exception& e) {
        // Encabezados CORS en caso de error también
        json errorResponse = {{"error", "Error al actualizar producto"}};
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, errorResponse.dump());
    }
}

void ProductosController::deleteProductById(const Rest::Request& request, Http::ResponseWriter response) {
    auto id = request.param(":id").as<int>();
    try {
        productService.deleteProductById(id);
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, "Producto eliminado");
    } catch (const std::exception& e) {
        // Encabezados CORS en caso de error también
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, "Error al eliminar producto");
    }
}

// void ProductosController::deleteProductBySKU(const Rest::Request& request, Http::ResponseWriter response) {
//     auto sku = request.param(":sku").as<std::string>();
//     try {
//         productService.deleteProductBySKU(sku);
//         response.headers()
//             .add<Http::Header::AccessControlAllowOrigin>("*")
//             .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
//             .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
//         response.send(Http::Code::Ok, "Producto eliminado");
//     } catch (const std::exception& e) {
//         // Encabezados CORS en caso de error también
//         response.headers()
//             .add<Http::Header::AccessControlAllowOrigin>("*")
//             .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
//             .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
//         response.send(Http::Code::Internal_Server_Error, "Error al eliminar producto");
//     }
// }

void ProductosController::getColumns(const Rest::Request& request, Http::ResponseWriter response) {
    try {
        auto columns = productService.getColumns();
        json jsonResponse = columns;
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Ok, jsonResponse.dump());
    } catch (const std::exception& e) {
        // Encabezados CORS en caso de error también
        response.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*")
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
        response.send(Http::Code::Internal_Server_Error, "Error al obtener columnas");
    }
}