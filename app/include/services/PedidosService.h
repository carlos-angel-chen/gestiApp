#ifndef PEDIDO_SERVICE_H
#define PEDIDO_SERVICE_H

#include <pqxx/pqxx>
#include <vector>
#include "../models/Pedidos.h"
#include "database/DatabaseConnection.h"

class PedidosService {
public:
    explicit PedidosService(DatabaseConnection& db);

    std::vector<Pedidos> getAllPedidos();
    std::vector<Pedidos> getPedidoById(int id);
    void createPedido(const Pedidos& pedidos);
    //Pedidos updatePedidoById(const Pedidos& pedidos);
    //void deletePedidoById(int id);
    int getLastId();
    std::vector<std::string> getColumns();
private:
    DatabaseConnection& dbConn;
};

#endif // PEDIDO_SERVICE_H