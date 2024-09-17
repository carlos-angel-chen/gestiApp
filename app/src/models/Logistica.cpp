#include "../include/models/Logistica.h"

Logistica::Logistica(
    int id,
    const std::string& razonSocial,
    const std::string& cuit,
    const std::string& direccion,
    const std::string& tipo,
    const std::string& nombre,
    const std::string& localidad,
    const std::string& telefono
) : id(id), 
    razonSocial(razonSocial), 
    cuit(cuit), 
    direccion(direccion), 
    tipo(tipo), 
    nombre(nombre), 
    localidad(localidad), 
    telefono(telefono) 
    {}

// Implementación de la función to_json
void to_json(nlohmann::json& j, const Logistica& l) {
    j = nlohmann::json{
        {"id", l.id},
        {"razon_social", l.razonSocial},
        {"\"CUIT\"", l.cuit},
        {"direccion", l.direccion},
        {"tipo", l.tipo},
        {"nombre", l.nombre},
        {"localidad", l.localidad},
        {"telefono", l.telefono}
    };
}

// Implementación de la función from_json (opcional si quieres convertir de JSON a Logistica)
void from_json(const nlohmann::json& j, Logistica& l) {
    j.at("id").get_to(l.id);
    j.at("razon_social").get_to(l.razonSocial);
    j.at("\"CUIT\"").get_to(l.cuit);
    j.at("direccion").get_to(l.direccion);
    j.at("tipo").get_to(l.tipo);
    j.at("nombre").get_to(l.nombre);
    j.at("localidad").get_to(l.localidad);
    j.at("telefono").get_to(l.telefono);
}