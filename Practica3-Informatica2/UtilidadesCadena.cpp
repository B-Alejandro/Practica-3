#include "utilidadesCadena.h"
#include <iostream>
using namespace std;

// ===================== FUNCIONES BÁSICAS =====================

int longitud(const char* cadena) {
    int i = 0;
    while (cadena[i] != '\0') i++;
    return i;
}

void copiar(char* destino, const char* origen) {
    int i = 0;
    while (origen[i] != '\0') {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

void copiarN(char* destino, const char* origen, int len) {
    for (int i = 0; i < len; i++) destino[i] = origen[i];
}

// ===================== MANEJO DE TEXTO =====================

void concatenar(char* destino, const char* origen) {
    int i = 0;
    while (destino[i] != '\0') i++;
    int j = 0;
    while (origen[j] != '\0') {
        destino[i++] = origen[j++];
    }
    destino[i] = '\0';
}

void separarLinea(const char* linea, char*& cedula, char*& clave, char*& nombre, char*& dinero) {
    int len = longitud(linea);
    int campo = 0;
    char buffer[200];
    int pos = 0;

    cedula = clave = nombre = dinero = nullptr;

    for (int i = 0; i <= len; i++) {
        if (linea[i] == ',' || linea[i] == '\0') {
            buffer[pos] = '\0';
            char* nuevo = new char[pos + 1];
            copiar(nuevo, buffer);

            if (campo == 0) cedula = nuevo;
            else if (campo == 1) clave = nuevo;
            else if (campo == 2) nombre = nuevo;
            else if (campo == 3) dinero = nuevo;

            campo++;
            pos = 0;
        } else {
            buffer[pos++] = linea[i];
        }
    }
}

bool cadenasIguales(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

bool esBinario(const char* texto) {
    for (int i = 0; texto[i] != '\0'; i++) {
        if (texto[i] != '0' && texto[i] != '1') return false;
    }
    return true;
}
