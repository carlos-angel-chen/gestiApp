#include "../include/models/Ventas.h"

Ventas::Ventas(
    int id,
    int id_pedido,
    const std::string& fecha,
    int id_cliente,
    const std::string& nombre_cliente,
    int id_logistica,
    const std::string& logistica,
    int id_metodo_pago,
    const std::string& metodo_pago,
    float subtotal,
    float descuento,
    float precio_final_pesos,
    float precio_final_usd,
    const std::string& observaciones
) : id(id), 
    id_pedido(id_pedido), 
    fecha(fecha),
    id_cliente(id_cliente),
    nombre_cliente(nombre_cliente),
    id_logistica(id_logistica),
    logistica(logistica),
    id_metodo_pago(id_metodo_pago),
    metodo_pago(metodo_pago),
    subtotal(subtotal),
    descuento(descuento),
    precio_final_pesos(precio_final_pesos),
    precio_final_usd(precio_final_usd),
    observaciones(observaciones)
    {}

// Implementación de la función to_json
void to_json(nlohmann::json& j, const Ventas& p) {
    j = nlohmann::json{
        {"id", p.id},
        {"id_pedido", p.id_pedido},
        {"fecha", p.fecha},
        {"id_cliente", p.id_cliente},
        {"nombre_cliente", p.nombre_cliente},
        {"id_logistica", p.id_logistica},
        {"logistica", p.logistica},
        {"id_metodo_pago", p.id_metodo_pago},
        {"metodo_pago", p.metodo_pago},
        {"subtotal", p.subtotal},
        {"descuento", p.descuento},
        {"precio_final_pesos", p.precio_final_pesos},
        {"precio_final_usd", p.precio_final_usd},
        {"observaciones", p.observaciones}
    };
}

// Implementación de la función from_json (opcional si quieres convertir de JSON a Producto)
void from_json(const nlohmann::json& j, Ventas& v) {
    j.at("id").get_to(v.id);
    j.at("id_pedido").get_to(v.id_pedido);
    j.at("fecha").get_to(v.fecha);
    j.at("id_cliente").get_to(v.id_cliente);
    j.at("nombre_cliente").get_to(v.nombre_cliente);
    j.at("id_logistica").get_to(v.id_logistica);
    j.at("logistica").get_to(v.logistica);
    j.at("id_metodo_pago").get_to(v.id_metodo_pago);
    j.at("metodo_pago").get_to(v.metodo_pago);
    j.at("subtotal").get_to(v.subtotal);
    j.at("descuento").get_to(v.descuento);
    j.at("precio_final_pesos").get_to(v.precio_final_pesos);
    j.at("precio_final_usd").get_to(v.precio_final_usd);
    j.at("observaciones").get_to(v.observaciones);
}