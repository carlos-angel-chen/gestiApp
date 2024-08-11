// src/main.cpp
#include "TodoController.hpp"
#include "AppComponent.hpp"

int main() {
    Pistache::Port port(9080);
    Pistache::Address addr(Pistache::Ipv4::any(), port);

    AppComponent components(addr);
    TodoController controller(components);

    controller.init();
    controller.start();

    // Esperar a que el servidor se detenga
    std::cout << "Server running on port " << port << std::endl;
    std::this_thread::sleep_for(std::chrono::hours(24));

    controller.shutdown();

    return 0;
}