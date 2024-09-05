#ifndef CLIENTES_H
#define CLIENTES_H

#include <string>
/*
    id
    razon_social
    CUIT
    tributacion
    telefono
    email
*/

class Clientes {
public: 
    int id;
    std::string razonSocial;
    int cuit;
};

#endif // CLIENTES_H