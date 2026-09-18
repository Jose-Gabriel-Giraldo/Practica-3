#include <iostream>
#include "ejemplos.h"

using namespace std;

int main() {
    cout << "=== Ejemplo 2: Compresion RLE ===\n";
    const char* textoRLE = "AAAABBBCC";
    char* comprimido = comprimirRLE(textoRLE);
    char* descomprimido = descomprimirRLE(comprimido);

    cout << "Texto original:   " << textoRLE << "\n";
    cout << "Texto comprimido: " << comprimido << "\n";
    cout << "Descomprimido:    " << descomprimido << "\n";
    cout << "Verificacion: " << (textosIguales(textoRLE, descomprimido) ? "OK" : "FALLO") << "\n\n";

    delete[] comprimido;
    delete[] descomprimido;

    cout << "=== Ejemplo 3: Rotacion de bits ===\n";
    unsigned char byteOriginal = 0b01000001; // letra 'A'
    int n = 3;
    unsigned char rotado = rotarIzquierda(byteOriginal, n);
    unsigned char recuperado = rotarDerecha(rotado, n);

    cout << "Byte original:        "; imprimirBinario(byteOriginal); cout << "\n";
    cout << "Rotado " << n << " bits izq:   "; imprimirBinario(rotado); cout << "\n";
    cout << "Rotado de vuelta der: "; imprimirBinario(recuperado); cout << "\n";
    cout << "Verificacion: " << (byteOriginal == recuperado ? "OK" : "FALLO") << "\n\n";

    cout << "=== Ejemplo 4: XOR para encriptar/desencriptar ===\n";
    unsigned char mensaje = 0b01000001; // letra 'A'
    unsigned char clave = 0b01011010;
    unsigned char encriptado = aplicarXOR(mensaje, clave);
    unsigned char desencriptado = aplicarXOR(encriptado, clave);

    cout << "Mensaje original: "; imprimirBinario(mensaje); cout << " ('A')\n";
    cout << "Clave K:          "; imprimirBinario(clave); cout << "\n";
    cout << "Encriptado:       "; imprimirBinario(encriptado); cout << "\n";
    cout << "Desencriptado:    "; imprimirBinario(desencriptado); cout << "\n";
    cout << "Verificacion: " << (mensaje == desencriptado ? "OK" : "FALLO") << "\n\n";

    cout << "=== Ejemplo 5: Estructura de diccionario LZ78 ===\n";
    const char* textoLZ78 = "ABAABABA";
    cout << "Texto: " << textoLZ78 << "\n";
    construirDiccionarioLZ78(textoLZ78);

    return 0;
}
