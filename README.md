# gestiApp

La aplicacion de gestion de negocio, es un MVP.

Se realizo este proyecto como trabajo practico final de la materia 22.08 Algoritmos y Estructura de Datos - ITBA.

## Importante!
Esta aplicacion tiene un backend hecho en C++ utilizando el [Pistache REST Framework](https://pistacheio.github.io/pistache/). Por el momento solamente 
funciona en entorno Linux. En este proyecto se lo realizo utilizando Ubuntu 24.04.1 LTS.

## Como utilizarlo
Primero es necesario que estes utilizando una ditribucion de Linux. Luego es necesario que se instalen las bibliotecas y software necesarios. 
1. Instalar Postgresql 
```
sudo apt-get install postgresql

sudo apt install pgadmin4

sudo apt install pgadmin4-desktop
```
2. Instalar Pistache REST Framework. 
```
git clone https://github.com/pistacheio/pistache.git
cd pistache
meson setup build
meson install -C build
```
3. Biblioteca para establecer conexion entre Backend y Postgresql
```
sudo apt-get install libpqxx-dev libpq-dev
```

## Arquitectura principal
![Arquitectura](doc/arq.png)

### Base de datos
Se utilizo Postgresql como gestor de base de datos relacional. Para el diseño se utilizo [drawdb.app](https://drawdb.app). En la siguiente imagen se muestra las tablas que se crearon y sus relaciones:
![base de datos](doc/db_arq.png)

### Backend

### Frontend 