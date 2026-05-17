# Parqueadero
# Proyecto Parqueadero con Sockets

## Descripción

Este proyecto simula el ingreso y salida de vehículos en un parqueadero.

El sistema está dividido en:

- Cliente en C++
- Servidor en C++
- Librería dinámica DLL en C++
- Visualizador en Python

## Funcionamiento

El cliente genera placas de vehículos y las envía al servidor usando sockets TCP.

Cada mensaje tiene el formato:

PLACA|HORA|CELDA

Ejemplo:

ABC123|14:35:20|5

## Reglas del sistema

Si una placa no existe en el parqueadero, se registra como entrada.

Si una placa ya existe, se interpreta como salida y se libera la celda.

## Tecnologías usadas

- C++
- Winsock2
- Python
- Tkinter
- DLL en C++
- Git

## Estructura

cliente/
servidor/
dll/
visualizador/
docs/
data/

## Ejecución

Primero ejecutar el servidor.

Luego ejecutar el cliente.

Después abrir el visualizador en Python.

## Compilación

Servidor:

g++ servidor/server.cpp -o servidor/server.exe -lws2_32

Cliente:

g++ cliente/client.cpp -o cliente/client.exe -lws2_32

DLL:

g++ -shared dll/parqueadero_dll.cpp -o dll/parqueadero_dll.dll

Visualizador:

python visualizador/visualizador.py
