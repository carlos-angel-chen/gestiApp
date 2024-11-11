#include "../include/models/Clientes.h"

Clientes::Clientes(
    int id,
    const std::string& razonSocial,
    const std::string& cuit,
    const std::string& tributacion,
    const std::string& telefono,
    const std::string& email,
    const std::string& nombre,
    const std::string& direccionFiscal,
    const std::string& direccionEntrega,
    const std::string& localidad,
    const std::string& cp,
    const std::string& whatsapp
) : id(id), 
    razonSocial(razonSocial), 
    cuit(cuit), 
    tributacion(tributacion), 
    telefono(telefono), 
    email(email), 
    nombre(nombre), 
    direccionFiscal(direccionFiscal), 
    direccionEntrega(direccionEntrega), 
    localidad(localidad), 
    cp(cp), 
    whatsapp(whatsapp) 
    {}

// Implementación de la función to_json
void to_json(nlohmann::json& j, const Clientes& c) {
    j = nlohmann::json{
        {"id", c.id},
        {"razon_social", c.razonSocial},
        {"cuit", c.cuit},
        {"tributacion", c.tributacion},
        {"telefono", c.telefono},
        {"email", c.email},
        {"nombre", c.nombre},
        {"direccion_fiscal", c.direccionFiscal},
        {"direccion_entrega", c.direccionEntrega},
        {"localidad", c.localidad},
        {"cp", c.cp},
        {"whatsapp", c.whatsapp}
    };
}

// Implementación de la función from_json (opcional si quieres convertir de JSON a Cliente)
void from_json(const nlohmann::json& j, Clientes& c) {
    j.at("id").get_to(c.id);
    j.at("razon_social").get_to(c.razonSocial);
    j.at("cuit").get_to(c.cuit);
    j.at("tributacion").get_to(c.tributacion);
    j.at("telefono").get_to(c.telefono);
    j.at("email").get_to(c.email);
    j.at("nombre").get_to(c.nombre);
    j.at("direccion_fiscal").get_to(c.direccionFiscal);
    j.at("direccion_entrega").get_to(c.direccionEntrega);
    j.at("localidad").get_to(c.localidad);
    j.at("cp").get_to(c.cp);
    j.at("whatsapp").get_to(c.whatsapp);
}