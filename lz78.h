#ifndef LZ78_H
#define LZ78_H

void comprimirLZ78(const char* texto, int*& indices, char*& caracteres, int& cantidadPares);
char* descomprimirLZ78(const int* indices, const char* caracteres, int cantidadPares);
void imprimirParesLZ78(const int* indices, const char* caracteres, int cantidadPares);
void serializarLZ78(const int* indices, const char* caracteres, int cantidadPares,
                    unsigned char*& datos, int& cantidadBytes);
void deserializarLZ78(const unsigned char* datos, int cantidadBytes,
                      int*& indices, char*& caracteres, int& cantidadPares);

#endif
