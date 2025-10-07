#ifndef OPERACIONES_USUARIO_H
#define OPERACIONES_USUARIO_H

#include <string>
using namespace std;

/**
 * @brief Consulta el saldo de un usuario según su cédula.
 *
 * Muestra el saldo actual en consola y descuenta 1000 COP como costo de la operación.
 *
 * @param linea Línea de texto del usuario ("cedula,clave,nombre,saldo COP")
 * @param cedulaBuscada Cédula del usuario que desea consultar su saldo.
 * @return true si se encontró y actualizó correctamente, false en caso contrario.
 */
bool consultarSaldoUsuario(string& linea, const string& cedulaBuscada);

/**
 * @brief Retira dinero del saldo de un usuario, cobrando 1000 COP por la operación.
 *
 * @param linea Línea de texto del usuario ("cedula,clave,nombre,saldo COP")
 * @param cedulaBuscada Cédula del usuario que realiza el retiro.
 * @param montoRetiro Monto a retirar (debe ser positivo).
 * @return true si el retiro se realizó correctamente, false si hubo error o saldo insuficiente.
 */
bool modificarDineroUsuario(string& linea, const string& cedulaBuscada, int montoRetiro);

#endif
