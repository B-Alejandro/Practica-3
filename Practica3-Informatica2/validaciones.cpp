#include <iostream>
#include "validaciones.h"
using namespace std;

// ================================
// Validar Cédula
// ================================
bool validarCedula(const char* cedula) {
    if (cedula == nullptr) return false;

    int longitud = 0;

    // No puede empezar con '0'
    if (cedula[0] == '0') return false;

    while (cedula[longitud] != '\0') {
        char c = cedula[longitud];

        // Solo dígitos válidos
        if (c < '0' || c > '9') return false;

        longitud++;

        // Evitar cédulas absurdamente largas
        if (longitud > 10) return false;
    }

    // Debe tener entre 6 y 10 dígitos
    if (longitud < 6 || longitud > 10) return false;

    return true;
}

bool validarContrasena(const char* clave) {
    if (clave == nullptr) return false;

    int longitud = 0;
    bool tieneNumero = false;
    bool tieneMayuscula = false;
    bool tieneMinuscula = false;
    bool tieneEspecial = false;

    while (clave[longitud] != '\0') {
        unsigned char c = clave[longitud];

        if (c >= '0' && c <= '9') {
            tieneNumero = true;
        }
        else if (c >= 'A' && c <= 'Z') {
            tieneMayuscula = true;
        }
        else if (c >= 'a' && c <= 'z') {
            tieneMinuscula = true;
        }
        else if (c == ' ' || c == '\t') {
            // No se permiten espacios ni tabulaciones
            return false;
        }
        else if ((c >= 33 && c <= 126)) {
            // Cualquier símbolo imprimible estándar (sin espacios)
            tieneEspecial = true;
        }
        else {
            // Cualquier otro carácter extendido (ñ, tildes, etc.) es inválido
            return false;
        }

        longitud++;
    }

    // Debe tener al menos 8 caracteres
    if (longitud < 8) return false;

    // Debe cumplir todas las condiciones
    return (tieneNumero && tieneMayuscula && tieneMinuscula && tieneEspecial);
}

// ================================
// Validar Saldo
// ================================
bool validarSaldo(const char* saldoStr) {
    if (saldoStr == nullptr) return false;

    int i = 0;
    long saldo = 0;

    // Verificar que todos sean dígitos
    while (saldoStr[i] != '\0') {
        char c = saldoStr[i];
        if (c < '0' || c > '9') {
            return false;
        }

        saldo = saldo * 10 + (c - '0');
        if (saldo > 1000000) return false; // rango máximo
        i++;
    }

    // No debe estar vacío
    if (i == 0) return false;

    // Rango válido [0, 1000000]
    return (saldo >= 0 && saldo <= 1000000);
}
