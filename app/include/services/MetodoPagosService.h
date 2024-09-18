#ifndef METODO_PAGOS_SERVICE_H
#define METODO_PAGOS_SERVICE_H

#include <pqxx/pqxx>
#include "../models/MetodoPagos.h"
#include "database/DatabaseConnection.h"
#include <vector>

class MetodoPagosService {
public:
    explicit MetodoPagosService(DatabaseConnection& db);

    std::vector<MetodoPagos> getAllMetodoPagos();
    void createMetodoPago(const MetodoPagos& metodoPago);
    void deleteMetodoPagoById(int id);
    std::vector<std::string> getColumns();
    MetodoPagos updateMetodoPagoById(const MetodoPagos& metodoPago);

private:
    DatabaseConnection& dbConn;
};

#endif // METODO_PAGOS_SERVICE_H