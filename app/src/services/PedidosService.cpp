#include <iostream>
#include "../include/services/PedidosService.h"

PedidosService::PedidosService(DatabaseConnection& db) : dbConn(db) {}

std::vector<Pedidos> PedidosService::getAllPedidos(){
    
}