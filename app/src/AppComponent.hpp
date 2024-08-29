// AppComponent.hpp
#ifndef AppComponent_hpp
#define AppComponent_hpp

#include <pistache/endpoint.h>
#include <pistache/router.h>
#include <pistache/http.h>
#include <pistache/net.h>
#include <memory>

class AppComponent {
public:
    AppComponent(Pistache::Address addr)
        : httpEndpoint(std::make_shared<Pistache::Http::Endpoint>(addr)),
          router(std::make_shared<Pistache::Rest::Router>()) {}

    std::shared_ptr<Pistache::Http::Endpoint> getHttpEndpoint() {
        return httpEndpoint;
    }

    std::shared_ptr<Pistache::Rest::Router> getRouter() {
        return router;
    }

private:
    std::shared_ptr<Pistache::Http::Endpoint> httpEndpoint;
    std::shared_ptr<Pistache::Rest::Router> router;
};

#endif /* AppComponent_hpp */