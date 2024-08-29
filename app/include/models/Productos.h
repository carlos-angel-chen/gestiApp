#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#include <string>
#include <nlohmann/json.hpp>  // Asegúrate de incluir la biblioteca nlohmann::json
#include <optional>

class Productos {
public:
    int id;
    std::string sku;
    std::string nombre;
    std::optional<std::string> stock_minimo;
    std::optional<std::string> stock_actual;
    std::optional<std::string> id_tipo;

    Productos() = default;

    Productos(
        int id,
        const std::string& sku,
        const std::string& nombre,
        std::optional<std::string> stock_minimo,
        std::optional<std::string> stock_actual,
        std::optional<std::string> id_tipo
    );

    // Métodos adicionales si son necesarios (como validaciones o transformaciones)
    // Sobrecarga de la conversión a JSON
    friend void to_json(nlohmann::json& j, const Productos& p);
    friend void from_json(const nlohmann::json& j, Productos& p);
};

#endif // PRODUCTOS_H