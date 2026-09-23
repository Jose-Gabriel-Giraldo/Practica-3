#include "Encriptacion.h"

void validarRotacion(int n) {
    if (n <= 0 || n >= 8) {
        throw "El valor de rotacion n debe cumplir 0 < n < 8";
    }
}

unsigned char rotarIzquierda(unsigned char valor, int n) {
    return (unsigned char)((valor << n) | (valor >> (8 - n)));
}

unsigned char rotarDerecha(unsigned char valor, int n) {
    return (unsigned char)((valor >> n) | (valor << (8 - n)));
}

unsigned char aplicarXOR(unsigned char valor, unsigned char clave) {
    return valor ^ clave;
}

void encriptar(unsigned char* datos, int cantidad, int n, unsigned char clave) {
    validarRotacion(n);

    for (int i = 0; i < cantidad; i++) {
        datos[i] = rotarIzquierda(datos[i], n);
        datos[i] = aplicarXOR(datos[i], clave);
    }
}

void desencriptar(unsigned char* datos, int cantidad, int n, unsigned char clave) {
    validarRotacion(n);

    for (int i = 0; i < cantidad; i++) {
        datos[i] = aplicarXOR(datos[i], clave);
        datos[i] = rotarDerecha(datos[i], n);
    }
}
