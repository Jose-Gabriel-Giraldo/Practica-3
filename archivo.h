#ifndef ARCHIVO_H
#define ARCHIVO_H

void leerArchivo(const char* ruta, unsigned char*& datos, int& longitud);
void escribirArchivo(const char* ruta, const unsigned char* datos, int longitud);

#endif
