// src/Todo.hpp
#ifndef Todo_hpp
#define Todo_hpp

#include <string>

struct Todo {
    int id;
    std::string title;
    std::string description;
    bool completed;

    Todo(int id, const std::string& title, const std::string& description, bool completed)
        : id(id), title(title), description(description), completed(completed) {}
};

#endif /* Todo_hpp */