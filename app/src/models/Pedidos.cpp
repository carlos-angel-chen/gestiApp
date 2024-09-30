#include "../include/models/Pedidos.h"

Pedidos::Pedidos(
    int id,
    int id_producto,
    const std::string& sku,
    const std::string& nombre,
    const std::string& tipo_producto,
    int cantidad,
    float costo,
    float precio_venta,
    float precio_sin_iva,
    float precio_con_iva,
    float precio_minorista,
    float precio_mayorista,
    float precio_venta_minimo
    // float subtotal
) : id(id), 
    id_producto(id_producto),
    sku(sku), 
    nombre(nombre),
    tipo_producto(tipo_producto),
    cantidad(cantidad),
    costo(costo),
    precio_venta(precio_venta),
    precio_sin_iva(precio_sin_iva),
    precio_con_iva(precio_con_iva),
    precio_minorista(precio_minorista),
    precio_mayorista(precio_mayorista),
    precio_venta_minimo(precio_venta_minimo)
    // subtotal(subtotal)
    {}

// Implementación de la función to_json
void to_json(nlohmann::json& j, const Pedidos& p) {
    j = nlohmann::json{
        {"id", p.id},
        {"id_producto", p.id_producto},
        {"\"SKU\"", p.sku},
        {"nombre", p.nombre},
        {"tipo_producto", p.tipo_producto},
        {"cantidad", p.cantidad},
        {"costo", p.costo},
        {"precio_venta", p.precio_venta},
        {"precio_sin_iva", p.precio_sin_iva},
        {"precio_con_iva", p.precio_con_iva},
        {"precio_minorista", p.precio_minorista},
        {"precio_mayorista", p.precio_mayorista},
        {"precio_venta_minimo", p.precio_venta_minimo}
        // {"subtotal", p.subtotal}
    };
}

// Implementación de la función from_json (opcional si quieres convertir de JSON a Producto)
void from_json(const nlohmann::json& j, Pedidos& p) {
    j.at("id").get_to(p.id);
    j.at("id_producto").get_to(p.id_producto);
    j.at("\"SKU\"").get_to(p.sku);
    j.at("nombre").get_to(p.nombre);
    j.at("tipo_producto").get_to(p.tipo_producto);
    j.at("cantidad").get_to(p.cantidad);
    j.at("costo").get_to(p.costo);
    j.at("precio_venta").get_to(p.precio_venta);
    j.at("precio_sin_iva").get_to(p.precio_sin_iva);
    j.at("precio_con_iva").get_to(p.precio_con_iva);
    j.at("precio_minorista").get_to(p.precio_minorista);
    j.at("precio_mayorista").get_to(p.precio_mayorista);
    j.at("precio_venta_minimo").get_to(p.precio_venta_minimo);
    // j.at("subtotal").get_to(p.subtotal);
}