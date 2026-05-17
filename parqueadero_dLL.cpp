#include "parqueadero_dll.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

static string datos;

extern "C" __declspec(dllexport) const char* obtenerDatosParqueadero() {
    ifstream archivo("../data/parqueadero.txt");

    stringstream contenido;
    string linea;

    while (getline(archivo, linea)) {
        contenido << linea << "\n";
    }

    archivo.close();

    datos = contenido.str();

    return datos.c_str();
}
