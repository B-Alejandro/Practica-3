#include <iostream>
#include <string>
#include "Validaciones.h"
using namespace std;

// ================================
// Validar Cédula
// ================================

/**
 * @brief Valida si una cadena cumple con los requisitos de un número de cédula.
 *
 * Requisitos:
 * - Longitud entre **6 y 10 dígitos**.
 * - Todos los caracteres deben ser numéricos.
 * - No puede comenzar con '0'.
 *
 * @param cedula Cadena que representa el número de cédula.
 * @return true si la cédula es válida, false en caso contrario.
 * @throws const char* Si la cédula está vacía, contiene letras o no cumple los requisitos.
 */
bool validarCedula(const string& cedula) {
    try {
        if (cedula.empty())
            throw "La cédula está vacía.";

        if (cedula.size() < 6 || cedula.size() > 10)
            throw "La cédula debe tener entre 6 y 10 dígitos.";

        if (cedula[0] == '0')
            throw "La cédula no puede comenzar con 0.";

        for (char c : cedula) {
            if (c < '0' || c > '9')
                throw "La cédula contiene caracteres no numéricos.";
        }

        return true;
    }
    catch (const char* msg) {
        cerr << "Error en validarCedula: " << msg << endl;
        return false;
    }
}

// ================================
// Validar Contraseña
// ================================

/**
 * @brief Valida si una cadena cumple con los requisitos de complejidad para una contraseña.
 *
 * Requisitos:
 * - Longitud entre **8 y 20 caracteres**.
 * - Debe contener al menos: una mayúscula, una minúscula, un número y un carácter especial.
 * - No puede contener espacios ni tabulaciones.
 * - Solo se permiten caracteres ASCII imprimibles (33–126).
 *
 * @param clave Cadena que representa la contraseña a validar.
 * @return true si la contraseña es válida, false en caso contrario.
 * @throws const char* Si la contraseña no cumple alguna de las condiciones anteriores.
 */
bool validarContrasena(const string& clave) {
    try {
        if (clave.empty())
            throw "La contraseña está vacía.";

        if (clave.size() < 8 || clave.size() > 20)
            throw "La contraseña debe tener entre 8 y 20 caracteres.";

        bool tieneNumero = false;
        bool tieneMayuscula = false;
        bool tieneMinuscula = false;
        bool tieneEspecial = false;

        for (unsigned char c : clave) {
            if (c >= '0' && c <= '9') tieneNumero = true;
            else if (c >= 'A' && c <= 'Z') tieneMayuscula = true;
            else if (c >= 'a' && c <= 'z') tieneMinuscula = true;
            else if (c == ' ' || c == '\t')
                throw "La contraseña contiene espacios o tabulaciones.";
            else if (c >= 33 && c <= 126)
                tieneEspecial = true;
            else
                throw "La contraseña contiene caracteres no válidos.";
        }

        if (!(tieneNumero && tieneMayuscula && tieneMinuscula && tieneEspecial))
            throw "La contraseña no cumple con los requisitos de complejidad.";

        return true;
    }
    catch (const char* msg) {
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
 * - Solo caracteres numéricos.
 * - No puede estar vacía.
 * - Valor numérico entre **0 y 1,000,000**.
 *
 * @param saldoStr Cadena que representa el saldo.
 * @return true si el saldo es válido, false en caso contrario.
 * @throws const char* Si el saldo está vacío, contiene letras o excede el máximo permitido.
 */
bool validarSaldo(const string& saldoStr) {
    try {
        if (saldoStr.empty())
            throw "El saldo está vacío.";

        long saldo = 0;

        for (char c : saldoStr) {
            if (c < '0' || c > '9')
                throw "El saldo contiene caracteres no numéricos.";

            saldo = saldo * 10 + (c - '0');
            if (saldo > 1000000)
                throw "El saldo excede el máximo permitido (1,000,000).";
        }

        return (saldo >= 0 && saldo <= 1000000);
    }
    catch (const char* msg) {
        cerr << "Error en validarSaldo: " << msg << endl;
        return false;
    }
}
