#ifndef VENTAS_H
#define VENTAS_H

#include <string>
#include <nlohmann/json.hpp>  // Asegúrate de incluir la biblioteca nlohmann::json
#include <optional>

class Ventas {
public:
    int id;
    int id_pedido;
    std::string fecha;
    int id_cliente;
    std::string nombre_cliente;
    int id_logistica;
    std::string logistica;
    int id_metodo_pago;
    std::string metodo_pago;
    float subtotal;
    float descuento;
    float precio_final_pesos;
    float precio_final_usd;
    std::string observaciones;

    Ventas() = default;

    Ventas(
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
    );

    // Métodos adicionales si son necesarios (como validaciones o transformaciones)
    // Sobrecarga de la conversión a JSON
    friend void to_json(nlohmann::json& j, const Ventas& p);
    friend void from_json(const nlohmann::json& j, Ventas& p);
};

#endif // VENTAS_H