#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <iostream>
using namespace std;

/**
 * @brief Verifica si una cédula es válida.
 *
 * Una cédula válida:
 *  - Contiene solo dígitos ('0'-'9')
 *  - Tiene entre 6 y 10 dígitos
 *  - No empieza con '0'
 *
 * @param cedula Cadena con la cédula a validar.
 * @return true si es válida, false en caso contrario.
 */
bool validarCedula(const char cedula[]);

/**
 * @brief Verifica si una contraseña cumple con los requisitos de seguridad.
 *
 * Requisitos:
 *  - Longitud entre 8 y 20 caracteres
 *  - Al menos una mayúscula, un número y un carácter especial
 *  - No contiene espacios
 *
 * @param password Cadena con la contraseña a validar.
 * @return true si cumple los criterios, false si no.
 */
bool validarContrasena(const char password[]);

/**
 * @brief Verifica si un saldo ingresado es válido.
 *
 * Un saldo válido:
 *  - Contiene solo dígitos
 *  - Está en el rango [0, 1,000,000]
 *
 * @param saldo Cadena con el saldo a validar.
 * @return true si es válido, false en caso contrario.
 */
bool validarSaldo(const char saldo[]);

#endif // VALIDACIONES_H
