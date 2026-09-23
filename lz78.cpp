#include <iostream>
#include "LZ78.h"
#include "utilidades.h"

using namespace std;

int buscarEntradaLZ78(int prefijoBuscado, char caracterBuscado, const int* prefijos,
                      const char* caracteres, int totalEntradas) {
    for (int k = 1; k <= totalEntradas; k++) {
        if (prefijos[k] == prefijoBuscado && caracteres[k] == caracterBuscado) {
            return k;
        }
    }
    return -1;
}

void comprimirLZ78(const char* texto, int*& indices, char*& caracteres, int& cantidadPares) {
    int longitud = longitudTexto(texto);

    if (longitud == 0) {
        throw "No se puede comprimir un texto vacio con LZ78";
    }

    int* prefijosDic = new int[longitud + 1];
    char* caracteresDic = new char[longitud + 1];
    prefijosDic[0] = -1;
    caracteresDic[0] = '\0';
    int totalEntradas = 0;

    indices = new int[longitud];
    caracteres = new char[longitud];
    cantidadPares = 0;

    int i = 0;
    while (i < longitud) {
        int indiceActual = 0;
        int extension = 0;

        while (i + extension < longitud) {
            int encontrada = buscarEntradaLZ78(indiceActual, texto[i + extension],
                                               prefijosDic, caracteresDic, totalEntradas);
            if (encontrada == -1) break;
            indiceActual = encontrada;
            extension++;
        }

        if (i + extension < longitud) {
            char nuevoCaracter = texto[i + extension];
            totalEntradas++;
            prefijosDic[totalEntradas] = indiceActual;
            caracteresDic[totalEntradas] = nuevoCaracter;

            indices[cantidadPares] = indiceActual;
            caracteres[cantidadPares] = nuevoCaracter;
            cantidadPares++;

            i += extension + 1;
        } else {
            indices[cantidadPares] = indiceActual;
            caracteres[cantidadPares] = '\0';
            cantidadPares++;
            i += extension;
        }
    }

    delete[] prefijosDic;
    delete[] caracteresDic;
}

int longitudFrase(int indice, const int* prefijos) {
    if (indice == 0) return 0;
    return 1 + longitudFrase(prefijos[indice], prefijos);
}

int escribirFrase(int indice, const int* prefijos, const char* caracteresDic, char* salida, int pos) {
    if (indice == 0) return pos;
    pos = escribirFrase(prefijos[indice], prefijos, caracteresDic, salida, pos);
    salida[pos] = caracteresDic[indice];
    pos++;
    return pos;
}

char* descomprimirLZ78(const int* indices, const char* caracteres, int cantidadPares) {
    if (cantidadPares <= 0) {
        throw "No hay datos para descomprimir con LZ78";
    }

    int* prefijosDic = new int[cantidadPares + 1];
    char* caracteresDic = new char[cantidadPares + 1];
    prefijosDic[0] = -1;
    caracteresDic[0] = '\0';
    int totalEntradas = 0;

    for (int k = 0; k < cantidadPares; k++) {
        if (indices[k] < 0 || indices[k] > totalEntradas) {
            delete[] prefijosDic;
            delete[] caracteresDic;
            throw "Datos LZ78 corruptos: indice de frase invalido";
        }
        if (caracteres[k] != '\0') {
            totalEntradas++;
            prefijosDic[totalEntradas] = indices[k];
            caracteresDic[totalEntradas] = caracteres[k];
        }
    }

    int tamanoSalida = 0;
    for (int k = 0; k < cantidadPares; k++) {
        tamanoSalida += longitudFrase(indices[k], prefijosDic);
        if (caracteres[k] != '\0') {
            tamanoSalida += 1;
        }
    }

    char* salida = new char[tamanoSalida + 1];
    int pos = 0;
    for (int k = 0; k < cantidadPares; k++) {
        pos = escribirFrase(indices[k], prefijosDic, caracteresDic, salida, pos);
        if (caracteres[k] != '\0') {
            salida[pos] = caracteres[k];
            pos++;
        }
    }
    salida[pos] = '\0';

    delete[] prefijosDic;
    delete[] caracteresDic;
    return salida;
}

void imprimirParesLZ78(const int* indices, const char* caracteres, int cantidadPares) {
    for (int k = 0; k < cantidadPares; k++) {
        cout << "(" << indices[k] << ", " << (caracteres[k] == '\0' ? '-' : caracteres[k]) << ") ";
    }
    cout << "\n";
}

void serializarLZ78(const int* indices, const char* caracteres, int cantidadPares,
                    unsigned char*& datos, int& cantidadBytes) {
    cantidadBytes = cantidadPares * 5; // 4 bytes del indice + 1 del caracter
    datos = new unsigned char[cantidadBytes];

    int pos = 0;
    for (int k = 0; k < cantidadPares; k++) {
        int valor = indices[k];
        datos[pos] = (unsigned char)((valor >> 24) & 0xFF); pos++;
        datos[pos] = (unsigned char)((valor >> 16) & 0xFF); pos++;
        datos[pos] = (unsigned char)((valor >> 8) & 0xFF); pos++;
        datos[pos] = (unsigned char)(valor & 0xFF); pos++;
        datos[pos] = (unsigned char)caracteres[k]; pos++;
    }
}

void deserializarLZ78(const unsigned char* datos, int cantidadBytes,
                      int*& indices, char*& caracteres, int& cantidadPares) {
    if (cantidadBytes % 5 != 0) {
        throw "Datos LZ78 corruptos: el tamano no es multiplo de 5";
    }
    cantidadPares = cantidadBytes / 5;
    indices = new int[cantidadPares];
    caracteres = new char[cantidadPares];

    int pos = 0;
    for (int k = 0; k < cantidadPares; k++) {
        int valor = 0;
        valor = (valor << 8) | datos[pos]; pos++;
        valor = (valor << 8) | datos[pos]; pos++;
        valor = (valor << 8) | datos[pos]; pos++;
        valor = (valor << 8) | datos[pos]; pos++;
        indices[k] = valor;
        caracteres[k] = (char)datos[pos]; pos++;
    }
}
