/*#include <iostream>
#include "ejemplos.h"

using namespace std;

int longitudTexto(const char* texto) {
    int contador = 0;
    while (texto[contador] != '\0') {
        contador++;
    }
    return contador;
}

bool textosIguales(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return false;
        }
        i++;
    }
    return a[i] == b[i];
}

bool esDigito(char c) {
    return c >= '0' && c <= '9';
}

// Ejemplo 2: Compresion RLE

// Cuenta cuantos digitos tiene un numero (ej: 12 -> 2 digitos)
int contarDigitos(int n) {
    int digitos = 1;
    while (n >= 10) {
        n /= 10;
        digitos++;
    }
    return digitos;
}

char* comprimirRLE(const char* texto) {
    int longitud = longitudTexto(texto);

    int tamanoSalida = 0;
    int i = 0;
    while (i < longitud) {
        char actual = texto[i];
        int repeticiones = 1;
        while (i + repeticiones < longitud && texto[i + repeticiones] == actual) {
            repeticiones++;
        }
        tamanoSalida += contarDigitos(repeticiones) + 1;
        i += repeticiones;
    }

    char* salida = new char[tamanoSalida + 1];
    int pos = 0;
    i = 0;
    while (i < longitud) {
        char actual = texto[i];
        int repeticiones = 1;
        while (i + repeticiones < longitud && texto[i + repeticiones] == actual) {
            repeticiones++;
        }

        int digitos = contarDigitos(repeticiones);
        int numero = repeticiones;
        for (int d = digitos - 1; d >= 0; d--) {
            salida[pos + d] = (char)('0' + (numero % 10));
            numero /= 10;
        }
        pos += digitos;

        salida[pos] = actual;
        pos++;
        i += repeticiones;
    }
    salida[pos] = '\0';
    return salida;
}

char* descomprimirRLE(const char* comprimido) {
    int longitud = longitudTexto(comprimido);

    int tamanoSalida = 0;
    int i = 0;
    while (i < longitud) {
        int numero = 0;
        while (i < longitud && esDigito(comprimido[i])) {
            numero = numero * 10 + (comprimido[i] - '0');
            i++;
        }
        tamanoSalida += numero;
        i++;
    }

    char* salida = new char[tamanoSalida + 1];
    int pos = 0;
    i = 0;
    while (i < longitud) {
        int numero = 0;
        while (i < longitud && esDigito(comprimido[i])) {
            numero = numero * 10 + (comprimido[i] - '0');
            i++;
        }
        char caracter = comprimido[i];
        i++;
        for (int k = 0; k < numero; k++) {
            salida[pos] = caracter;
            pos++;
        }
    }
    salida[pos] = '\0';
    return salida;
}

// Ejemplo 3: Rotacion de bits

unsigned char rotarIzquierda(unsigned char valor, int n) {
    n = n % 8;
    return (unsigned char)((valor << n) | (valor >> (8 - n)));
}

unsigned char rotarDerecha(unsigned char valor, int n) {
    n = n % 8;
    return (unsigned char)((valor >> n) | (valor << (8 - n)));
}

void imprimirBinario(unsigned char valor) {
    for (int bit = 7; bit >= 0; bit--) {
        cout << ((valor >> bit) & 1);
    }
}

// Ejemplo 4: XOR

unsigned char aplicarXOR(unsigned char valor, unsigned char clave) {
    return valor ^ clave;
}

// Ejemplo 5: Diccionario basico para LZ78

void imprimirFraseDiccionario(int indice, const int* prefijos, const char* caracteres) {
    if (indice == 0) return;
    imprimirFraseDiccionario(prefijos[indice], prefijos, caracteres);
    cout << caracteres[indice];
}


int buscarEntrada(int prefijoBuscado, char caracterBuscado, const int* prefijos,
                  const char* caracteres, int totalEntradas) {
    for (int k = 1; k <= totalEntradas; k++) {
        if (prefijos[k] == prefijoBuscado && caracteres[k] == caracterBuscado) {
            return k;
        }
    }
    return -1;
}

void construirDiccionarioLZ78(const char* texto) {
    int longitud = longitudTexto(texto);

    int* prefijos = new int[longitud + 1];
    char* caracteres = new char[longitud + 1];
    prefijos[0] = -1;
    caracteres[0] = '\0';

    int totalEntradas = 0;
    int i = 0;
    int paso = 1;

    cout << "Paso | Par emitido | Nueva entrada\n";
    while (i < longitud) {
        int indiceActual = 0;
        int extension = 0;

        while (i + extension < longitud) {
            int encontrada = buscarEntrada(indiceActual, texto[i + extension],
                                           prefijos, caracteres, totalEntradas);
            if (encontrada == -1) break;
            indiceActual = encontrada;
            extension++;
        }

        if (i + extension < longitud) {
            char nuevoCaracter = texto[i + extension];
            totalEntradas++;
            prefijos[totalEntradas] = indiceActual;
            caracteres[totalEntradas] = nuevoCaracter;

            cout << paso << "    | (" << indiceActual << ", " << nuevoCaracter
                 << ")      | " << totalEntradas << " -> ";
            imprimirFraseDiccionario(totalEntradas, prefijos, caracteres);
            cout << "\n";

            i += extension + 1;
        } else {
            cout << paso << "    | (" << indiceActual << ")         | -\n";
            i += extension;
        }
        paso++;
    }

    delete[] prefijos;
    delete[] caracteres;
}*/
