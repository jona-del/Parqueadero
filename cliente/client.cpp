#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080

using namespace std;

string generarPlaca() {
    string placa = "";

    for (int i = 0; i < 3; i++) {
        placa += char('A' + rand() % 26);
    }

    for (int i = 0; i < 3; i++) {
        placa += char('0' + rand() % 10);
    }

    return placa;
}

string obtenerHora() {
    time_t ahora = time(0);
    tm* tiempo = localtime(&ahora);

    char buffer[80];
    strftime(buffer, 80, "%H:%M:%S", tiempo);

    return string(buffer);
}

int main() {
    srand(time(0));

    WSADATA wsaData;
    SOCKET sock = INVALID_SOCKET;
    struct sockaddr_in serv_addr;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cerr << "Error iniciando Winsock" << endl;
        return 1;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == INVALID_SOCKET) {
        cerr << "Error creando socket" << endl;
        WSACleanup();
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Para pruebas en el mismo PC:
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");


    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        cerr << "Error conectando con servidor" << endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    cout << "Cliente conectado al servidor." << endl;

    while (true) {
        string placa = generarPlaca();
        string hora = obtenerHora();

        string mensaje = placa + "|" + hora;

        send(sock, mensaje.c_str(), mensaje.length(), 0);

        cout << "Enviado: " << mensaje << endl;

        int espera = (rand() % 2 == 0) ? 2 : 5;
        this_thread::sleep_for(chrono::seconds(espera));
    }

    closesocket(sock);
    WSACleanup();

    return 0;
}