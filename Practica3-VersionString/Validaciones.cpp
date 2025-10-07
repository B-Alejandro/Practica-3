#include <iostream>
#include <stdexcept>
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
 */
bool validarCedula(const string& cedula) {
    try {
        if (cedula.empty())
            throw invalid_argument("La cédula está vacía.");

        if (cedula.size() < 6 || cedula.size() > 10)
            throw length_error("La cédula debe tener entre 6 y 10 dígitos.");

        if (cedula[0] == '0')
            throw invalid_argument("La cédula no puede comenzar con 0.");

        for (char c : cedula) {
            if (c < '0' || c > '9')
                throw invalid_argument("La cédula contiene caracteres no numéricos.");
        }

        return true;
    } catch (const exception& e) {
        cerr << "Error en validarCedula: " << e.what() << endl;
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
 */
bool validarContrasena(const string& clave) {
    try {
        if (clave.empty())
            throw invalid_argument("La contraseña está vacía.");

        if (clave.size() < 8 || clave.size() > 20)
            throw length_error("La contraseña debe tener entre 8 y 20 caracteres.");

        bool tieneNumero = false;
        bool tieneMayuscula = false;
        bool tieneMinuscula = false;
        bool tieneEspecial = false;

        for (unsigned char c : clave) {
            if (c >= '0' && c <= '9') tieneNumero = true;
            else if (c >= 'A' && c <= 'Z') tieneMayuscula = true;
            else if (c >= 'a' && c <= 'z') tieneMinuscula = true;
            else if (c == ' ' || c == '\t')
                throw invalid_argument("La contraseña contiene espacios o tabulaciones.");
            else if (c >= 33 && c <= 126)
                tieneEspecial = true;
            else
                throw invalid_argument("La contraseña contiene caracteres no válidos.");
        }

        if (!(tieneNumero && tieneMayuscula && tieneMinuscula && tieneEspecial))
            throw invalid_argument("La contraseña no cumple con los requisitos de complejidad.");

        return true;
    } catch (const exception& e) {
        cerr << "Error en validarContrasena: " << e.what() << endl;
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
 */
bool validarSaldo(const string& saldoStr) {
    try {
        if (saldoStr.empty())
            throw length_error("El saldo está vacío.");

        long saldo = 0;

        for (char c : saldoStr) {
            if (c < '0' || c > '9')
                throw invalid_argument("El saldo contiene caracteres no numéricos.");

            saldo = saldo * 10 + (c - '0');
            if (saldo > 1000000)
                throw out_of_range("El saldo excede el máximo permitido (1,000,000).");
        }

        return (saldo >= 0 && saldo <= 1000000);
    } catch (const exception& e) {
        cerr << "Error en validarSaldo: " << e.what() << endl;
        return false;
    }
}
