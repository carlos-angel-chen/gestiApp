#ifndef METODO_PAGOS_H
#define METODO_PAGOS_H

#include <string>
#include <nlohmann/json.hpp>
#include <optional>

class MetodoPagos {
public:
    int id;
    std::string nombre;

    MetodoPagos() = default;

    MetodoPagos(
        int id,
        const std::string& nombre
    );

    // Métodos adicionales si son necesarios (como validaciones o transformaciones)
    // Sobrecarga de la conversión a JSON
    friend void to_json(nlohmann::json& j, const MetodoPagos& mp);
    friend void from_json(const nlohmann::json& j, MetodoPagos& mp);
};

#endif // METODO_PAGOS_H