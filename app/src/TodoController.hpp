// src/TodoController.hpp
#ifndef TodoController_hpp
#define TodoController_hpp

#include <pistache/endpoint.h>
#include <pistache/router.h>
#include <pistache/http.h>
#include <pistache/net.h>
#include "TodoService.hpp"
#include "AppComponent.hpp"

using namespace Pistache;

class TodoController {
public:
    explicit TodoController(AppComponent& components)
        : httpEndpoint(components.getHttpEndpoint()), router(components.getRouter()) {}

    void init(size_t threads = 2) {
        auto opts = Http::Endpoint::options().threads(static_cast<int>(threads));
        httpEndpoint->init(opts);
        setupRoutes();
    }

    void start() {
        httpEndpoint->setHandler(router->handler());
        httpEndpoint->serve();
    }

    void shutdown() {
        httpEndpoint->shutdown();
    }

private:
    void setupRoutes() {
        using namespace Rest;
        Routes::Post(*router, "/delete/:id", Routes::bind(&TodoController::deleteTodoById, this));
    }

    void deleteTodoById(const Rest::Request& request, Http::ResponseWriter response) {
        auto id = request.param(":id").as<int>();
        if (todoService.deleteTodoById(id)) {
            response.send(Http::Code::Ok, "Todo deleted");
        } else {
            response.send(Http::Code::Not_Found, "Todo not found");
        }
    }

    std::shared_ptr<Http::Endpoint> httpEndpoint;
    std::shared_ptr<Rest::Router> router;
    TodoService todoService;
};

#endif /* TodoController_hpp */