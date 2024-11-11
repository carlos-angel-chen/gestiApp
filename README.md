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
4. Instalo node.js y las bibliotecas que se van a utilizar para el Frontend
```
sudo apt-get install node.js
sudo apt install npm

nodejs -v
npm -v

#creo carpeta admin-dashboard
cd admin-dashboard
npm create vite@latest .

# elijo React
# elijo JavaScript

npm i

npm run dev
# chequeo que corre el servidor y luego mato la terminal

npm i react-router-dom lucide-react recharts@latest
npm i framer-motion
npm install -D tailwindcss postcss autoprefixer
npx tailwindcss init -p
```

Hasta aca es todo lo que se necesita para poder utilizarlo. Los siguientes pasos es para poder levantarlo localmente:

5. Clonamos este repo
```
git clone https://github.com/carlos-angel-chen/gestiApp.git
```
6. Compilamos el proyecto y levantamos el Backend
```
cd app/build/
cmake ..
make
./app
```
7. Abrimos otra terminal y levantamos el Frontend
```
cd admin-dashboard/
npm run dev
```
## Arquitectura principal
![Arquitectura](doc/arq.png)

### Base de datos
Se utilizo Postgresql como gestor de base de datos relacional. Para el diseño se utilizo [drawdb.app](https://drawdb.app). En la siguiente imagen se muestra las tablas que se crearon y sus relaciones:
![base de datos](doc/db_arq.png)

### Backend

### Frontend 