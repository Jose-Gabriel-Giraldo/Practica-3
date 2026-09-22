#include <iostream>
#include "RLE.h"
#include "utilidades.h"

using namespace std;

char* comprimirRLE(const char* texto) {
    int longitud = longitudTexto(texto);

    for (int i = 0; i < longitud; i++) {
        if (esDigito(texto[i])) {
            throw "No se puede comprimir: el texto contiene numeros y este formato no los soporta";
        }
    }

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
        int digitosLeidos = 0;
        while (i < longitud && esDigito(comprimido[i])) {
            numero = numero * 10 + (comprimido[i] - '0');
            i++;
            digitosLeidos++;
        }

        if (digitosLeidos == 0) {
            throw "Formato invalido: se esperaba un numero de repeticiones";
        }
        if (i >= longitud) {
            throw "Formato invalido: falta el caracter despues del numero";
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
