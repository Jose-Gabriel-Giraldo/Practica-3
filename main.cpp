#include <iostream>
#include "RLE.h"
#include "LZ78.h"
#include "Encriptacion.h"
#include "Archivo.h"
#include "utilidades.h"

using namespace std;


void mostrarMenu(int etapa) {
    cout << "\n=== Menu (etapa actual: " << etapa << "/4) ===\n";
    cout << "1. Comprimir\n";
    cout << "2. Encriptar\n";
    cout << "3. Desencriptar\n";
    cout << "4. Descomprimir\n";
    cout << "5. Verificar contra el original\n";
    cout << "6. Salir\n";
    cout << "Opcion: ";
}

int main() {
    char rutaArchivo[256];
    char* textoOriginal = nullptr; // copia del texto original, solo para comparar al final

    int metodoElegido = 0;
    int nGuardado = 0;
    unsigned char claveGuardada = 0;
    int etapa = 0; // 0=texto original, 1=comprimido, 2=encriptado, 3=desencriptado, 4=descomprimido

    cout << "=== Practica 3: Compresion + Encriptacion (un solo archivo) ===\n\n";

    try {
        cout << "Ruta del archivo de texto: ";
        cin >> rutaArchivo;

        unsigned char* bytes = nullptr;
        int longitud = 0;
        leerArchivo(rutaArchivo, bytes, longitud);

        textoOriginal = new char[longitud + 1];
        for (int i = 0; i < longitud; i++) {
            textoOriginal[i] = (char)bytes[i];
        }
        textoOriginal[longitud] = '\0';
        delete[] bytes;

        cout << "Archivo cargado: " << longitud << " caracteres\n";
    } catch (const char* mensaje) {
        cout << "Se detecto un error: " << mensaje << "\n";
        return 1;
    }

    bool salir = false;
    while (!salir) {
        mostrarMenu(etapa);
        int opcion;
        cin >> opcion;

        try {
            if (opcion == 1) {
                // ---------------- Comprimir ----------------
                // Usa el texto original guardado en memoria, y
                // sobreescribe el archivo con el resultado.
                if (etapa != 0) {
                    throw "El archivo ya no tiene el texto original en este momento";
                }

                cout << "Metodo (1=RLE, 2=LZ78): ";
                cin >> metodoElegido;
                if (metodoElegido != 1 && metodoElegido != 2) {
                    metodoElegido = 0;
                    throw "Metodo invalido";
                }

                unsigned char* datosComprimidos = nullptr;
                int cantidad = 0;

                if (metodoElegido == 1) {
                    char* comprimidoRLE = comprimirRLE(textoOriginal);
                    cantidad = longitudTexto(comprimidoRLE);
                    datosComprimidos = new unsigned char[cantidad];
                    for (int i = 0; i < cantidad; i++) {
                        datosComprimidos[i] = (unsigned char)comprimidoRLE[i];
                    }
                    delete[] comprimidoRLE;
                } else {
                    int* indices = nullptr;
                    char* caracteres = nullptr;
                    int cantidadPares = 0;
                    comprimirLZ78(textoOriginal, indices, caracteres, cantidadPares);
                    serializarLZ78(indices, caracteres, cantidadPares, datosComprimidos, cantidad);
                    delete[] indices;
                    delete[] caracteres;
                }

                escribirArchivo(rutaArchivo, datosComprimidos, cantidad);
                delete[] datosComprimidos;

                etapa = 1;
                cout << "Archivo sobreescrito con la version comprimida (" << cantidad << " bytes)\n";
                cout << "Abrelo para verlo si quieres.\n";

            } else if (opcion == 2) {
                // ---------------- Encriptar ----------------
                if (etapa != 1) {
                    throw "El archivo debe estar comprimido antes de encriptar";
                }

                cout << "Valor de rotacion n (0 < n < 8): ";
                cin >> nGuardado;
                int claveEntero;
                cout << "Clave de encriptacion (0-255): ";
                cin >> claveEntero;
                claveGuardada = (unsigned char)claveEntero;

                unsigned char* datos = nullptr;
                int cantidad = 0;
                leerArchivo(rutaArchivo, datos, cantidad);

                encriptar(datos, cantidad, nGuardado, claveGuardada);
                escribirArchivo(rutaArchivo, datos, cantidad);
                delete[] datos;

                etapa = 2;
                cout << "Archivo sobreescrito con la version encriptada.\n";
                cout << "Abrelo: ya no se ve como texto legible (eso es lo esperado).\n";

            } else if (opcion == 3) {
                // ---------------- Desencriptar ----------------
                if (etapa != 2) {
                    throw "El archivo debe estar encriptado antes de desencriptar";
                }

                unsigned char* datos = nullptr;
                int cantidad = 0;
                leerArchivo(rutaArchivo, datos, cantidad);

                desencriptar(datos, cantidad, nGuardado, claveGuardada);
                escribirArchivo(rutaArchivo, datos, cantidad);
                delete[] datos;

                etapa = 3;
                cout << "Archivo sobreescrito con la version desencriptada (vuelve a ser el comprimido legible).\n";

            } else if (opcion == 4) {
                // ---------------- Descomprimir ----------------
                if (etapa != 3) {
                    throw "El archivo debe estar desencriptado antes de descomprimir";
                }

                unsigned char* datos = nullptr;
                int cantidad = 0;
                leerArchivo(rutaArchivo, datos, cantidad);

                char* textoFinal = nullptr;

                if (metodoElegido == 1) {
                    char* comprimidoRecuperado = new char[cantidad + 1];
                    for (int i = 0; i < cantidad; i++) {
                        comprimidoRecuperado[i] = (char)datos[i];
                    }
                    comprimidoRecuperado[cantidad] = '\0';

                    textoFinal = descomprimirRLE(comprimidoRecuperado);
                    delete[] comprimidoRecuperado;
                } else {
                    int* indices2 = nullptr;
                    char* caracteres2 = nullptr;
                    int cantidadPares2 = 0;
                    deserializarLZ78(datos, cantidad, indices2, caracteres2, cantidadPares2);
                    textoFinal = descomprimirLZ78(indices2, caracteres2, cantidadPares2);
                    delete[] indices2;
                    delete[] caracteres2;
                }
                delete[] datos;

                escribirArchivo(rutaArchivo, (unsigned char*)textoFinal, longitudTexto(textoFinal));
                delete[] textoFinal;

                etapa = 4;
                cout << "Archivo sobreescrito con el texto final.\n";
                cout << "Abrelo: deberia verse igual al texto original.\n";

            } else if (opcion == 5) {
                // ---------------- Verificar ----------------
                if (etapa != 4) {
                    throw "Primero completa los pasos anteriores (falta descomprimir)";
                }

                unsigned char* bytes = nullptr;
                int longitud = 0;
                leerArchivo(rutaArchivo, bytes, longitud);

                char* textoActual = new char[longitud + 1];
                for (int i = 0; i < longitud; i++) {
                    textoActual[i] = (char)bytes[i];
                }
                textoActual[longitud] = '\0';
                delete[] bytes;

                cout << "El archivo coincide con el original: "
                     << (textosIguales(textoOriginal, textoActual) ? "OK" : "FALLO") << "\n";

                delete[] textoActual;

            } else if (opcion == 6) {
                salir = true;
            } else {
                cout << "Opcion invalida\n";
            }
        } catch (const char* mensaje) {
            cout << "Se detecto un error: " << mensaje << "\n";
        }
    }

    delete[] textoOriginal;

    return 0;
}
