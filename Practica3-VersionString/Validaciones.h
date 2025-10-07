#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>

/**
 * @brief Valida si una cadena cumple los requisitos de un número de cédula.
 * @param cedula Cadena con el número de cédula.
 * @return true si es válida, false en caso contrario.
 */
bool validarCedula(const std::string& cedula);

/**
 * @brief Valida si una cadena cumple los requisitos de una contraseña segura.
 * @param clave Cadena con la contraseña.
 * @return true si es válida, false en caso contrario.
 */
bool validarContrasena(const std::string& clave);

/**
 * @brief Valida si una cadena representa un saldo monetario válido.
 * @param saldoStr Cadena con el valor del saldo.
 * @return true si es válido, false en caso contrario.
 */
bool validarSaldo(const std::string& saldoStr);

#endif // VALIDACIONES_H
