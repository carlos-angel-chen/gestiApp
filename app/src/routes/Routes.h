#ifndef ROUTES_H
#define ROUTES_H

#include <pistache/http.h>
#include <pistache/router.h>
#include "database/DatabaseConnection.h"

// defino todas las rutas de la API REST
// y le paso la referencia a la conexión de la base de datos que será utilizada por los controladores para acceder a los datos
void setupRoutes(Pistache::Rest::Router& router, DatabaseConnection& dbConn);

// Declaración de la función handleOptions, que maneja solicitudes HTTP de tipo OPTIONS
// me sirve para verificar qué métodos y encabezados están permitidos 
void handleOptions(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);

#endif // ROUTES_H