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
    std::string tipo_producto;
    int stock_minimo;
    int stock_actual;
    float costo;
    float precio_venta;
    float precio_sin_iva;
    float precio_con_iva;
    float precio_minorista;
    float precio_mayorista;
    float precio_venta_minimo;

    // Defino construcctor por defecto de la clase
    // No hace ninguna inicializacion, solo crea un objeto "Productos" vacio
    Productos() = default;

    // Constructor parametrizado, permite inicializar un objeto "Productos" con valores específicos
    Productos(
        int id,
        const std::string& sku,
        const std::string& nombre,
        const std::string& tipo_producto,
        int stock_minimo,
        int stock_actual,
        float costo,
        float precio_venta,
        float precio_sin_iva,
        float precio_con_iva,
        float precio_minorista,
        float precio_mayorista,
        float precio_venta_minimo
    );

    // "friend" declara que las funciones son "amigas" de "Productos"
    // me permite accedor a los atributos privados o protegidos de la clase

    // Métodos adicionales si son necesarios (como validaciones o transformaciones)
    // Sobrecarga de la conversión a JSON
    friend void to_json(nlohmann::json& j, const Productos& p);
    friend void from_json(const nlohmann::json& j, Productos& p);
};

#endif // PRODUCTOS_H