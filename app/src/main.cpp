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

#include "database/DatabaseConnection.h"
#include <iostream>

int main() {
    // Definir la cadena de conexión a la base de datos
    std::string connectionString = "dbname=postgres user=postgres password=adminadmin hostaddr=127.0.0.1 port=5432";

    // Crear una instancia de la clase DatabaseConnection
    DatabaseConnection dbConn(connectionString);

    // Intentar conectarse a la base de datos
    if (!dbConn.connect()){
        std::cerr << "Error al conectar a la base de datos." << std::endl;
        return 1;
    }
    // Mientras necesites la conexion, sigue operando
    if (dbConn.isConnected()) {
        // Realizar opeaciones con l abase de datos aqui

        // Ejemplo
        try{
            pqxx::work txn(*dbConn.getConnection());
            pqxx::result res = txn.exec("SELECT * FROM public.\"Productos\"");
            for (auto row : res){
                std::cout << "Producto: " << row["id"].c_str() << " | " << row["\"SKU\""].c_str() << " | " << row["nombre"].c_str() << std::endl;
            }
            txn.commit();
        } catch(const std::exception &e){
            std::cerr << "Error al realizar la consulta: " << e.what() << std::endl;
        } 
    }

    dbConn.disconnect();
    return 0;
}
