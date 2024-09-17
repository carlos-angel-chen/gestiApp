#ifndef LOGITICA_SERVICE_H
#define LOGITICA_SERVICE_H

#include <pqxx/pqxx>
#include "../models/Logistica.h"
#include "database/DatabaseConnection.h"
#include <vector>

class LogisticaService {
public:
    explicit LogisticaService(DatabaseConnection& db);

    std::vector<Logistica> getAllLogisticas();
    std::vector<Logistica> getLogisticasByRazonSocial(const std::string& razonSocial);
    std::vector<Logistica> getLogisticasByNombre(const std::string& nombre);
    Logistica getLogisticaByCuit(const std::string& cuit);
    void createLogistica(const Logistica& logistica);
    Logistica updateLogisticaById(const Logistica& logistica);
    void deleteLogisticaById(int id);
    std::vector<std::string> getColumns();

private:
    DatabaseConnection& dbConn;
};

#endif // LOGITICA_SERVICE_H