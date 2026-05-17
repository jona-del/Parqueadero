#  Proyecto Parqueadero con Sockets, DLL y SWIG

Sistema distribuido para la gestión de un parqueadero utilizando:

- Cliente y servidor con sockets TCP
- Persistencia de datos en TXT
- DLL en C++
- Integración Python ↔ C++ mediante SWIG
- Interfaz gráfica con Tkinter
- Control de versiones con Git y GitHub

---

# Estructura del Proyecto

```text
cliente/        -> Cliente TCP
servidor/       -> Servidor principal
dll/            -> Librería dinámica en C++
visualizador/   -> Interfaz gráfica en Python
data/           -> Archivo de persistencia
