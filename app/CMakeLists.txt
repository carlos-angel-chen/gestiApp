cmake_minimum_required(VERSION 3.10)

project(app)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Incluir directorios para archivos de cabecera
include_directories(include)

# Añadir el código fuente (añade todos los archivos .cpp de tu proyecto)
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Incluir las dependencias de libpqxx
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBPQXX REQUIRED libpqxx)

# Incluir las dependencias de libpqxx
include_directories(${LIBPQXX_INCLUDE_DIRS})
link_directories(${LIBPQXX_LIBRARY_DIRS})

# Crear el ejecutable
add_executable(app ${SOURCES})

# Enlazar las bibliotecas de Pistache
target_link_libraries(app pistache ${LIBPQXX_LIBRARIES})



# Añadir los directorios de búsqueda para los encabezados y las bibliotecas de Pistache
# include_directories(/usr/local/include)
# link_directories(/usr/local/lib)

# Añadir los archivos fuente de tu proyecto
# set(SOURCES
#     src/main.cpp
#     src/AppComponent.hpp
#     src/Todo.hpp
#     src/TodoController.hpp
#     src/TodoService.hpp
# )
