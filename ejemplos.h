#ifndef EJEMPLOS_H
#define EJEMPLOS_H

// ---------------------------------------------------------
// Funciones propias para trabajar con texto (sin usar la
// libreria de C: strlen, strcmp, isdigit)
// ---------------------------------------------------------
int longitudTexto(const char* texto);
bool textosIguales(const char* a, const char* b);
bool esDigito(char c);

// ---------------------------------------------------------
// Ejemplo 2: Compresion y descompresion RLE
// ---------------------------------------------------------
char* comprimirRLE(const char* texto);
char* descomprimirRLE(const char* comprimido);

// ---------------------------------------------------------
// Ejemplo 3: Rotacion de bits sobre un byte
// ---------------------------------------------------------
unsigned char rotarIzquierda(unsigned char valor, int n);
unsigned char rotarDerecha(unsigned char valor, int n);
void imprimirBinario(unsigned char valor);

// ---------------------------------------------------------
// Ejemplo 4: Encriptacion/desencriptacion con XOR
// ---------------------------------------------------------
unsigned char aplicarXOR(unsigned char valor, unsigned char clave);

// ---------------------------------------------------------
// Ejemplo 5: Estructura basica de diccionario para LZ78
// ---------------------------------------------------------
void construirDiccionarioLZ78(const char* texto);

#endif
