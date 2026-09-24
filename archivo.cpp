#include <fstream>
#include "Archivo.h"

using namespace std;

void leerArchivo(const char* ruta, unsigned char*& datos, int& longitud) {
    ifstream archivo(ruta, ios::binary);
    if (!archivo.is_open()) {
        throw "No se pudo abrir el archivo de entrada";
    }

    archivo.seekg(0, ios::end);
    longitud = (int)archivo.tellg();
    archivo.seekg(0, ios::beg);

    datos = new unsigned char[longitud];
    archivo.read((char*)datos, longitud);
    archivo.close();
}

void escribirArchivo(const char* ruta, const unsigned char* datos, int longitud) {
    ofstream archivo(ruta, ios::binary);
    if (!archivo.is_open()) {
        throw "No se pudo crear el archivo de salida";
    }

    archivo.write((const char*)datos, longitud);
    archivo.close();
}
