// src/TodoService.hpp
#ifndef TodoService_hpp
#define TodoService_hpp

#include "Todo.hpp"
#include <vector>
#include <optional>
#include <algorithm>

class TodoService {
public:
    std::vector<Todo> getAllTodos() const {
        return todos;
    }

    std::optional<Todo> getTodoById(int id) const {
        auto it = std::find_if(todos.begin(), todos.end(), [id](const Todo& todo) {
            return todo.id == id;
        });
        if (it != todos.end()) {
            return *it;
        }
        return std::nullopt;
    }

    void addTodo(const Todo& todo) {
        todos.push_back(todo);
    }

    bool updateTodoById(int id, const Todo& updatedTodo) {
        auto it = std::find_if(todos.begin(), todos.end(), [id](const Todo& todo) {
            return todo.id == id;
        });
        if (it != todos.end()) {
            *it = updatedTodo;
            return true;
        }
        return false;
    }

    bool deleteTodoById(int id) {
        auto it = std::remove_if(todos.begin(), todos.end(), [id](const Todo& todo) {
            return todo.id == id;
        });
        if (it != todos.end()) {
            todos.erase(it, todos.end());
            return true;
        }
        return false;
    }

private:
    std::vector<Todo> todos;
};

#endif /* TodoService_hpp */