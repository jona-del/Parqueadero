#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <sstream>
#include <map>
#include <fstream>
#include <cstring>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080
#define TOTAL_CELDAS 20

using namespace std;

struct Vehiculo {
    string placa;
    string hora;
    int celda;
};

map<string, Vehiculo> parqueadero;

void guardarEstado() {
    ofstream archivo("./data/parqueadero.txt");

    for (auto const& item : parqueadero) {
        Vehiculo v = item.second;
        archivo << v.placa << "|" << v.hora << "|" << v.celda << endl;
    }

    archivo.close();
}

int obtenerCeldaLibre() {
    bool ocupadas[TOTAL_CELDAS + 1] = {false};

    for (auto const& item : parqueadero) {
        int celda = item.second.celda;

        if (celda >= 1 && celda <= TOTAL_CELDAS) {
            ocupadas[celda] = true;
        }
    }

    for (int i = 1; i <= TOTAL_CELDAS; i++) {
        if (!ocupadas[i]) {
            return i;
        }
    }

    return -1;
}

void procesarMensaje(string mensaje) {
    stringstream ss(mensaje);

    string placa;
    string hora;

    getline(ss, placa, '|');
    getline(ss, hora, '|');

    if (placa.empty() || hora.empty()) {
        cout << "Mensaje invalido recibido: " << mensaje << endl;
        return;
    }

    if (parqueadero.find(placa) == parqueadero.end()) {
        int celda = obtenerCeldaLibre();

        if (celda == -1) {
            cout << "PARQUEADERO LLENO -> No hay celdas disponibles." << endl;
            return;
        }

        Vehiculo nuevo;
        nuevo.placa = placa;
        nuevo.hora = hora;
        nuevo.celda = celda;

        parqueadero[placa] = nuevo;

        cout << "ENTRADA -> Placa: " << placa
             << " | Hora: " << hora
             << " | Celda asignada: " << celda << endl;
    } else {
        cout << "SALIDA -> Placa: " << placa
             << " | Celda liberada: " << parqueadero[placa].celda << endl;

        parqueadero.erase(placa);
    }

    guardarEstado();
}

int main() {
    WSADATA wsaData;
    SOCKET servidor_fd, nuevo_socket;
    struct sockaddr_in direccion;
    int addrlen = sizeof(direccion);
    char buffer[1024];

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "Error iniciando Winsock" << endl;
        return 1;
    }

    servidor_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (servidor_fd == INVALID_SOCKET) {
        cerr << "Error creando socket" << endl;
        WSACleanup();
        return 1;
    }

    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = INADDR_ANY;
    direccion.sin_port = htons(PORT);

    if (bind(servidor_fd, (struct sockaddr*)&direccion, sizeof(direccion)) == SOCKET_ERROR) {
        cerr << "Error en bind" << endl;
        closesocket(servidor_fd);
        WSACleanup();
        return 1;
    }

    if (listen(servidor_fd, 3) == SOCKET_ERROR) {
        cerr << "Error en listen" << endl;
        closesocket(servidor_fd);
        WSACleanup();
        return 1;
    }

    cout << "Servidor escuchando en puerto " << PORT << endl;

    nuevo_socket = accept(servidor_fd, (struct sockaddr*)&direccion, &addrlen);

    if (nuevo_socket == INVALID_SOCKET) {
        cerr << "Error aceptando conexion" << endl;
        closesocket(servidor_fd);
        WSACleanup();
        return 1;
    }

    cout << "Cliente conectado." << endl;

    while (true) {
        memset(buffer, 0, sizeof(buffer));

        int bytesRecibidos = recv(nuevo_socket, buffer, 1023, 0);

        if (bytesRecibidos <= 0) {
            cout << "Cliente desconectado." << endl;
            break;
        }

        buffer[bytesRecibidos] = '\0';

        string mensaje(buffer);
        procesarMensaje(mensaje);
    }

    closesocket(nuevo_socket);
    closesocket(servidor_fd);
    WSACleanup();

    return 0;
}