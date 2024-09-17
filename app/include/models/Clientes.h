#ifndef CLIENTES_H
#define CLIENTES_H

#include <string>
#include <nlohmann/json.hpp>  // Asegúrate de incluir la biblioteca nlohmann::json
#include <optional>

class Clientes {
public: 
    int id;
    std::string razonSocial;
    std::string cuit;
    std::string tributacion;
    std::string telefono;
    std::string email;
    std::string nombre;
    std::string direccionFiscal;
    std::string direccionEntrega;
    std::string localidad;
    std::string cp;
    std::string whatsapp;

    Clientes() = default;

    Clientes(
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
    );

    // Métodos adicionales si son necesarios (como validaciones o transformaciones)
    // Sobrecarga de la conversión a JSON
    friend void to_json(nlohmann::json& j, const Clientes& c);
    friend void from_json(const nlohmann::json& j, Clientes& c);
};

#endif // CLIENTES_H