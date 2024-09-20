#ifndef PEDIDOS_H
#define PEDIDOS_H

#include <string>
#include <nlohmann/json.hpp>  // Asegúrate de incluir la biblioteca nlohmann::json

class Pedidos {
public:
    int id;
    std::string sku;
    std::string nombre;
    std::string tipo_producto;
    int cantidad;
    float costo;
    float precio_venta;
    float precio_sin_iva;
    float precio_con_iva;
    float precio_minorista;
    float precio_mayorista;
    float precio_venta_minimo;
    // float subtotal;

    Pedidos() = default;

    Pedidos(
        int id,
        const std::string& sku,
        const std::string& nombre,
        const std::string& tipo_producto,
        int cantidad,
        float costo,
        float precio_venta,
        float precio_sin_iva,
        float precio_con_iva,
        float precio_minorista,
        float precio_mayorista,
        float precio_venta_minimo
        // float subtotal
    );

    // Métodos adicionales si son necesarios (como validaciones o transformaciones)
    // Sobrecarga de la conversión a JSON
    friend void to_json(nlohmann::json& j, const Pedidos& p);
    friend void from_json(const nlohmann::json& j, Pedidos& p);
};

#endif // PEDIDOS_H