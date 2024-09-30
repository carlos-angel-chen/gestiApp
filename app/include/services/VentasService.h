#ifndef VENTAS_SERVICE_H
#define VENTAS_SERVICE_H

#include <pqxx/pqxx>
#include <vector>
#include "../models/Ventas.h"
#include "database/DatabaseConnection.h"

class VentasService {
public:
    explicit VentasService(DatabaseConnection& db);

    std::vector<Ventas> getAllVentas();
    Ventas getVentasById(int id);
    //std::vector<Ventas> getVentasByPedido(int id_pedido);
    void createVentas(const Ventas& ventas);
    //Ventas updateVentasById(const Ventas& ventas);
    //void deleteVentasById(int id);
    //std::vector<std::string> getColumns();
private:
    DatabaseConnection& dbConn;
};

#endif // VENTAS_SERVICE_H