#include "../include/models/MetodoPagos.h"


MetodoPagos::MetodoPagos(
    int id,
    const std::string& nombre
) : id(id), 
    nombre(nombre) 
    {}

// Implementación de la función to_json
void to_json(nlohmann::json& j, const MetodoPagos& mp) {
    j = nlohmann::json{
        {"id", mp.id},
        {"nombre", mp.nombre}
    };
}

// Implementación de la función from_json (opcional si quieres convertir de JSON a MetodoPagos)
void from_json(const nlohmann::json& j, MetodoPagos& mp) {
    j.at("id").get_to(mp.id);
    j.at("nombre").get_to(mp.nombre);
}