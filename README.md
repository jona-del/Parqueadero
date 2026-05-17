#  Proyecto Parqueadero 

Sistema distribuido para la gestión de un parqueadero utilizando:

- Cliente y servidor con sockets TCP
- Persistencia de datos en TXT
- DLL en C++
- Integración Python ↔ C++ mediante SWIG
- Interfaz gráfica con Tkinter
- Control de versiones con Git y GitHub

EJECICION DEL PROYECTO
en la terminal se coloca
servidor/server.exe

LUEGO

cliente/client.exe

en esta parte se va actualizando en el data/parqueadero.txt

py visualizador/visualizador.py

y ahi aparece las placas de los carros con la interfaz de:

Vehículos estacionados
Hora de entrada
Celdas ocupadas
Celdas disponibles 

# Estructura del Proyecto

```text
cliente/        -> Cliente TCP
servidor/       -> Servidor principal
dll/            -> Librería dinámica en C++
visualizador/   -> Interfaz gráfica en Python
data/           -> Archivo de persistencia
