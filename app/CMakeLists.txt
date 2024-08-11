cmake_minimum_required(VERSION 3.10)

project(app)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Añadir los directorios de búsqueda para los encabezados y las bibliotecas de Pistache
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

# Añadir los archivos fuente de tu proyecto
set(SOURCES
    src/main.cpp
    src/AppComponent.hpp
    src/Todo.hpp
    src/TodoController.hpp
    src/TodoService.hpp
)

# Crear el ejecutable
add_executable(app ${SOURCES})

# Enlazar las bibliotecas de Pistache
target_link_libraries(app pistache)