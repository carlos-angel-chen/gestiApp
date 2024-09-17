#ifndef LOGISTICA_H
#define LOGISTICA_H

#include <string>
#include <nlohmann/json.hpp>
#include <optional>

class Logistica {
public:
    int id;
    std::string razonSocial;
    std::string cuit;
    std::string direccion;
    std::string tipo;
    std::string nombre;
    std::string localidad;
    std::string telefono;

    Logistica() = default;

    Logistica(
        int id,
        const std::string& razonSocial,
        const std::string& cuit,
        const std::string& direccion,
        const std::string& tipo,
        const std::string& nombre,
        const std::string& localidad,
        const std::string& telefono
    );

    // Métodos adicionales si son necesarios (como validaciones o transformaciones)
    // Sobrecarga de la conversión a JSON
    friend void to_json(nlohmann::json& j, const Logistica& l);
    friend void from_json(const nlohmann::json& j, Logistica& l);
};

#endif // LOGISTICA_H