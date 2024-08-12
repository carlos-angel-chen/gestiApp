// // src/main.cpp
// #include "TodoController.hpp"
// #include "AppComponent.hpp"

// int main() {
//     Pistache::Port port(9080);
//     Pistache::Address addr(Pistache::Ipv4::any(), port);

//     AppComponent components(addr);
//     TodoController controller(components);

//     controller.init();
//     controller.start();

//     // Esperar a que el servidor se detenga
//     std::cout << "Server running on port " << port << std::endl;
//     std::this_thread::sleep_for(std::chrono::hours(24));

//     controller.shutdown();

//     return 0;
// }

#include <pistache/endpoint.h>
#include <pistache/router.h>
#include <pistache/http_headers.h>
#include "routes/Routes.h"
#include "database/DatabaseConnection.h"

using namespace Pistache;
using namespace Pistache::Rest;

// Función para manejar las solicitudes OPTIONS (CORS Preflight)
void handleOptions(const Rest::Request& request, Http::ResponseWriter response) {
    response.headers()
        .add<Http::Header::AccessControlAllowOrigin>("*")
        .add<Http::Header::AccessControlAllowMethods>("GET, POST, PUT, DELETE, OPTIONS")
        .add<Http::Header::AccessControlAllowHeaders>("Content-Type, Accept");
    response.send(Http::Code::Ok);
}

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

    // Manejar solicitudes OPTIONS para CORS
    Routes::Options(router, "/productos", Routes::bind(&handleOptions));

    setupRoutes(router, dbConn);

    // Iniciar el servidor con las rutas configuradas
    server.setHandler(router.handler());
    std::cout << "Servidor iniciado en http://localhost:" << port << std::endl;
    server.serve();

    // Desconectar la base de datos antes de salir
    dbConn.disconnect();

    return 0;
}
