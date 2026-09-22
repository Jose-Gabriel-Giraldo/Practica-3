#ifndef RLE_H
#define RLE_H

int longitudTexto(const char* texto);
bool textosIguales(const char* a, const char* b);
bool esDigito(char c);

char* comprimirRLE(const char* texto);
char* descomprimirRLE(const char* comprimido);

#endif
