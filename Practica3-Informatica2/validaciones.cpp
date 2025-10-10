#include <iostream>
#include "Validaciones.h"
using namespace std;

// ================================
// Validar Cédula
// ================================

/**
 * @brief Valida si una cadena de caracteres cumple con los requisitos de un número de cédula.
 *
 * Los requisitos son:
 * - No puede ser un puntero nulo.
 * - Debe tener entre **6 y 10 dígitos**.
 * - Todos los caracteres deben ser numéricos.
 * - No puede comenzar con '0'.
 *
 * @param cedula La cadena que representa la cédula.
 * @return `true` si la cédula es válida, `false` en caso contrario.
 */
bool validarCedula(const char* cedula) {
    try {
        if (cedula == nullptr)
            throw "Puntero nulo recibido en validarCedula.";

        int longitud = 0;

        if (cedula[0] == '0')
            throw "La cédula no puede comenzar con 0.";

        while (cedula[longitud] != '\0') {
            char c = cedula[longitud];
            if (c < '0' || c > '9')
                throw "La cédula contiene caracteres no numéricos.";
            longitud++;
            if (longitud > 10)
                throw "La cédula excede los 10 dígitos permitidos.";
        }

        if (longitud < 6 || longitud > 10)
            throw "La cédula debe tener entre 6 y 10 dígitos.";

        return true;
    } catch (const char* msg) {
        cerr << "Error en validarCedula: " << msg << endl;
        return false;
    }
}

// ================================
// Validar Contraseña
// ================================

/**
 * @brief Valida si una cadena cumple con los requisitos de complejidad de una contraseña.
 *
 * Requisitos:
 * - Longitud entre **8 y 20**.
 * - Contiene mayúscula, minúscula, número y carácter especial.
 * - Sin espacios ni tabulaciones.
 * - Solo caracteres imprimibles ASCII.
 *
 * @param clave La cadena de la contraseña.
 * @return `true` si es válida, `false` si no lo es.
 */
bool validarContrasena(const char* clave) {
    try {
        if (clave == nullptr)
            throw "Puntero nulo recibido en validarContrasena.";

        int longitud = 0;
        bool tieneNumero = false;
        bool tieneMayuscula = false;
        bool tieneMinuscula = false;
        bool tieneEspecial = false;

        while (clave[longitud] != '\0') {
            unsigned char c = clave[longitud];

            if (c >= '0' && c <= '9') tieneNumero = true;
            else if (c >= 'A' && c <= 'Z') tieneMayuscula = true;
            else if (c >= 'a' && c <= 'z') tieneMinuscula = true;
            else if (c == ' ' || c == '\t')
                throw "La contraseña contiene espacios o tabulaciones.";
            else if (c >= 33 && c <= 126)
                tieneEspecial = true;
            else
                throw "La contraseña contiene caracteres no válidos.";

            longitud++;
        }

        if (longitud < 8 || longitud > 20)
            throw "La contraseña debe tener entre 8 y 20 caracteres.";

        if (!(tieneNumero && tieneMayuscula && tieneMinuscula && tieneEspecial))
            throw "La contraseña no cumple con los requisitos de complejidad.";

        return true;
    } catch (const char* msg) {
        cerr << "Error en validarContrasena: " << msg << endl;
        return false;
    }
}

// ================================
// Validar Saldo
// ================================

/**
 * @brief Valida si una cadena representa un saldo monetario válido.
 *
 * Requisitos:
 * - Solo números.
 * - No vacía.
 * - Valor entre 0 y 1,000,000.
 *
 * @param saldoStr La cadena del saldo.
 * @return `true` si es válido, `false` si no lo es.
 */
bool validarSaldo(const char* saldoStr) {
    try {
        if (saldoStr == nullptr)
            throw "Puntero nulo recibido en validarSaldo.";

        int i = 0;
        long saldo = 0;

        while (saldoStr[i] != '\0') {
            char c = saldoStr[i];
            if (c < '0' || c > '9')
                throw "El saldo contiene caracteres no numéricos.";

            saldo = saldo * 10 + (c - '0');
            if (saldo > 1000000)
                throw "El saldo excede el máximo permitido (1,000,000).";
            i++;
        }

        if (i == 0)
            throw "El saldo está vacío.";

        return (saldo >= 0 && saldo <= 1000000);
    } catch (const char* msg) {
        cerr << "Error en validarSaldo: " << msg << endl;
        return false;
    }
}
