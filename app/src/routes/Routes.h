#ifndef ROUTES_H
#define ROUTES_H

#include <pistache/router.h>
#include "database/DatabaseConnection.h"

void setupRoutes(Pistache::Rest::Router& router, DatabaseConnection& dbConn);

#endif // ROUTES_H