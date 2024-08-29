#include "../include/models/Productos.h"

Productos::Productos(
    int id,
    const std::string& sku,
    const std::string& nombre,
    const std::optional<std::string> stock_minimo,
    const std::optional<std::string> stock_actual,
    const std::optional<std::string> id_tipo
) : id(id), 
    sku(sku), 
    nombre(nombre), 
    stock_minimo(stock_minimo), 
    stock_actual(stock_actual), 
    id_tipo(id_tipo) 
    {}

// Implementación de la función to_json
void to_json(nlohmann::json& j, const Productos& p) {
    j = nlohmann::json{
        {"id", p.id},
        {"\"SKU\"", p.sku},
        {"nombre", p.nombre}
    };

    // Solo incluye stock_minimo y stock_actual si tienen valor
    if (p.stock_minimo.has_value()) {
        j["stock_minimo"] = p.stock_minimo.value();
    } else {
        j["stock_minimo"] = nullptr;  // Puedes usar nullptr o simplemente omitir este campo
    }

    if (p.stock_actual.has_value()) {
        j["stock_actual"] = p.stock_actual.value();
    } else {
        j["stock_actual"] = nullptr;  // Puedes usar nullptr o simplemente omitir este campo
    }

    if (p.id_tipo.has_value()) {
        j["id_tipo"] = p.id_tipo.value();
    } else {
        j["id_tipo"] = nullptr;  // Puedes usar nullptr o simplemente omitir este campo
    }
}

// Implementación de la función from_json (opcional si quieres convertir de JSON a Producto)
void from_json(const nlohmann::json& j, Productos& p) {
    j.at("id").get_to(p.id);
    j.at("\"SKU\"").get_to(p.sku);
    j.at("nombre").get_to(p.nombre);
    j.at("stock_minimo").get_to(p.stock_minimo);
    j.at("stock_actual").get_to(p.stock_actual);
    j.at("id_tipo").get_to(p.id_tipo);
}