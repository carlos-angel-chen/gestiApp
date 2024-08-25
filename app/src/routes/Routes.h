#ifndef ROUTES_H
#define ROUTES_H

#include <pistache/http.h>
#include <pistache/router.h>
#include "database/DatabaseConnection.h"

void setupRoutes(Pistache::Rest::Router& router, DatabaseConnection& dbConn);

// Declaración de la función handleOptions
void handleOptions(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response);

#endif // ROUTES_H