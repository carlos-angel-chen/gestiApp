#include "../include/models/Productos.h"

Productos::Productos(
    int id,
    const std::string& sku,
    const std::string& nombre,
    const std::string& tipo_producto,
    int stock_minimo,
    int stock_actual,
    float costo,
    float precio_venta,
    float precio_sin_iva,
    float precio_con_iva,
    float precio_minorista,
    float precio_mayorista,
    float precio_venta_minimo
) : id(id), 
    sku(sku), 
    nombre(nombre),
    tipo_producto(tipo_producto),
    stock_minimo(stock_minimo), 
    stock_actual(stock_actual), 
    costo(costo),
    precio_venta(precio_venta),
    precio_sin_iva(precio_sin_iva),
    precio_con_iva(precio_con_iva),
    precio_minorista(precio_minorista),
    precio_mayorista(precio_mayorista),
    precio_venta_minimo(precio_venta_minimo)
    {}

// Implementación de la función to_json
void to_json(nlohmann::json& j, const Productos& p) {
    j = nlohmann::json{
        {"id", p.id},
        {"\"SKU\"", p.sku},
        {"nombre", p.nombre},
        {"tipo_producto", p.tipo_producto},
        {"stock_minimo", p.stock_minimo},
        {"stock_actual", p.stock_actual},
        {"costo", p.costo},
        {"precio_venta", p.precio_venta},
        {"precio_sin_iva", p.precio_sin_iva},
        {"precio_con_iva", p.precio_con_iva},
        {"precio_minorista", p.precio_minorista},
        {"precio_mayorista", p.precio_mayorista},
        {"precio_venta_minimo", p.precio_venta_minimo}
    };
}

// Implementación de la función from_json (opcional si quieres convertir de JSON a Producto)
void from_json(const nlohmann::json& j, Productos& p) {
    j.at("id").get_to(p.id);
    j.at("\"SKU\"").get_to(p.sku);
    j.at("nombre").get_to(p.nombre);
    j.at("tipo_producto").get_to(p.tipo_producto);
    j.at("stock_minimo").get_to(p.stock_minimo);
    j.at("stock_actual").get_to(p.stock_actual);
    j.at("costo").get_to(p.costo);
    j.at("precio_venta").get_to(p.precio_venta);
    j.at("precio_sin_iva").get_to(p.precio_sin_iva);
    j.at("precio_con_iva").get_to(p.precio_con_iva);
    j.at("precio_minorista").get_to(p.precio_minorista);
    j.at("precio_mayorista").get_to(p.precio_mayorista);
    j.at("precio_venta_minimo").get_to(p.precio_venta_minimo);
}