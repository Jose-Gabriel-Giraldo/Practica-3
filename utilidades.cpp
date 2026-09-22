#include "utilidades.h"

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

// Cuenta cuantos digitos tiene un numero (ej: 12 -> 2 digitos)
int contarDigitos(int n) {
    int digitos = 1;
    while (n >= 10) {
        n /= 10;
        digitos++;
    }
    return digitos;
}
