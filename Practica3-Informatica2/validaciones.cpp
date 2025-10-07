#include <iostream>
#include <stdexcept> // Para std::invalid_argument, std::out_of_range, etc.
#include "validaciones.h"
using namespace std;

// ================================
// Validar Cédula
// ================================

/**
 * @brief Valida si una cadena de caracteres cumple con los requisitos de un número de cédula.
 *
 * Los requisitos son:
 * - No puede ser un puntero nulo.
 * - Debe tener entre **6 y 10 dígitos** (ambos inclusive).
 * - Todos los caracteres deben ser **numéricos** ('0'-'9').
 * - **No puede comenzar con '0'**.
 *
 * @param cedula La cadena de caracteres que representa la cédula.
 * @return `true` si la cédula es válida.
 * @return `false` si la cédula no cumple con algún requisito (muestra el error por `cerr`).
 * @exception std::invalid_argument Si el puntero es nulo, comienza con '0', o contiene caracteres no numéricos.
 * @exception std::out_of_range Si la longitud excede los 10 dígitos durante la iteración.
 * @exception std::length_error Si la longitud final no está entre 6 y 10.
 */
bool validarCedula(const char* cedula) {
    try {
        if (cedula == nullptr)
            throw invalid_argument("Puntero nulo recibido en validarCedula.");

        int longitud = 0;

        if (cedula[0] == '0')
            throw invalid_argument("La cédula no puede comenzar con 0.");

        while (cedula[longitud] != '\0') {
            char c = cedula[longitud];
            if (c < '0' || c > '9')
                throw invalid_argument("La cédula contiene caracteres no numéricos.");
            longitud++;
            if (longitud > 10)
                throw out_of_range("La cédula excede los 10 dígitos permitidos.");
        }

        if (longitud < 6 || longitud > 10)
            throw length_error("La cédula debe tener entre 6 y 10 dígitos.");

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
 * @brief Valida si una cadena de caracteres cumple con los requisitos de complejidad para una contraseña.
 *
 * Los requisitos son:
 * - No puede ser un puntero nulo.
 * - Debe tener entre **8 y 20 caracteres** de longitud.
 * - Debe contener al menos una **letra mayúscula**, una **letra minúscula**, un **número** y un **carácter especial** (cualquier imprimible que no sea letra/número/espacio).
 * - **No puede contener espacios** ni tabulaciones.
 * - Todos los caracteres deben ser imprimibles ASCII (rango 33-126).
 *
 * @param clave La cadena de caracteres que representa la contraseña.
 * @return `true` si la contraseña es válida.
 * @return `false` si la contraseña no cumple con algún requisito (muestra el error por `cerr`).
 * @exception std::invalid_argument Si el puntero es nulo, contiene espacios/tabulaciones, caracteres no válidos o no cumple con los requisitos de complejidad.
 * @exception std::length_error Si la longitud no está entre 8 y 20.
 */
bool validarContrasena(const char* clave) {
    try {
        if (clave == nullptr)
            throw invalid_argument("Puntero nulo recibido en validarContrasena.");

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
                throw invalid_argument("La contraseña contiene espacios o tabulaciones.");
            else if (c >= 33 && c <= 126) // Caracteres imprimibles ASCII (excluye espacio 32)
                tieneEspecial = true;
            else
                throw invalid_argument("La contraseña contiene caracteres no válidos.");

            longitud++;
        }

        if (longitud < 8 || longitud > 20)
            throw length_error("La contraseña debe tener entre 8 y 20 caracteres.");

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
 * @brief Valida si una cadena de caracteres representa un saldo monetario válido.
 *
 * Los requisitos son:
 * - No puede ser un puntero nulo.
 * - La cadena debe contener solo **caracteres numéricos** ('0'-'9').
 * - La cadena no puede estar vacía.
 * - El valor numérico del saldo **no puede exceder 1,000,000**.
 *
 * @param saldoStr La cadena de caracteres que representa el saldo.
 * @return `true` si el saldo es válido y está dentro del rango permitido ($0 - $1,000,000).
 * @return `false` si el saldo no cumple con algún requisito (muestra el error por `cerr`).
 * @exception std::invalid_argument Si el puntero es nulo o contiene caracteres no numéricos.
 * @exception std::out_of_range Si el valor numérico excede 1,000,000.
 * @exception std::length_error Si la cadena de saldo está vacía.
 */
bool validarSaldo(const char* saldoStr) {
    try {
        if (saldoStr == nullptr)
            throw invalid_argument("Puntero nulo recibido en validarSaldo.");

        int i = 0;
        long saldo = 0;

        while (saldoStr[i] != '\0') {
            char c = saldoStr[i];
            if (c < '0' || c > '9')
                throw invalid_argument("El saldo contiene caracteres no numéricos.");

            saldo = saldo * 10 + (c - '0');
            // Verificación temprana para el desbordamiento de rango
            if (saldo > 1000000)
                throw out_of_range("El saldo excede el máximo permitido (1,000,000).");
            i++;
        }

        if (i == 0)
            throw length_error("El saldo está vacío.");

        return (saldo >= 0 && saldo <= 1000000);
    } catch (const exception& e) {
        cerr << "Error en validarSaldo: " << e.what() << endl;
        return false;
    }
}
