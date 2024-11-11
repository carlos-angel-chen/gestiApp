#include <pistache/endpoint.h>
#include <pistache/router.h>
#include <pistache/http_headers.h>
#include "routes/Routes.h"
#include "database/DatabaseConnection.h"

using namespace Pistache;
using namespace Pistache::Rest;

int main() {
    // Configuración de la conexión a la base de datos
    std::string connectionString = "dbname=postgres user=postgres password=adminadmin hostaddr=127.0.0.1 port=5432";
    DatabaseConnection dbConn(connectionString);

    if (!dbConn.connect()) {
        std::cerr << "Error al conectar a la base de datos." << std::endl;
        return 1;  // Salir si la conexión falla
    }

    // Configurar el servidor Pistache
    Port port(9080);
    int thr = 2;  // Número de hilos (threads) para manejar solicitudes
    Address addr(Ipv4::any(), port);

    Http::Endpoint server(addr);
    auto opts = Http::Endpoint::options().threads(thr);
    server.init(opts);

    // Configurar las rutas
    Rest::Router router;

    setupRoutes(router, dbConn);

    // Iniciar el servidor con las rutas configuradas
    server.setHandler(router.handler());
    std::cout << "Servidor iniciado en http://localhost:" << port << std::endl;
    server.serve();

    // Desconectar la base de datos antes de salir
    dbConn.disconnect();

    return 0;
}
