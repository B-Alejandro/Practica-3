#ifndef OPERACIONES_USUARIO_H
#define OPERACIONES_USUARIO_H

/**
 * @brief Consulta el saldo de un usuario por su cédula.
 *
 * Descuenta automáticamente el costo de consulta (1000 COP) si hay fondos suficientes.
 *
 * @param lineas Arreglo de usuarios (cada línea contiene: cedula,clave,nombre,saldo).
 * @param numUsuarios Número de usuarios en el arreglo.
 * @param cedulaBuscada Cédula a buscar.
 * @return true si se encontró y actualizó el saldo, false si no existe.
 */
bool consultarSaldoUsuario(char** lineas, int numUsuarios, const char* cedulaBuscada);

/**
 * @brief Modifica el saldo de un usuario realizando un retiro.
 *
 * Aplica un costo fijo de transacción (1000 COP) y actualiza la línea del usuario.
 *
 * @param lineas Arreglo de usuarios.
 * @param numUsuarios Número de usuarios.
 * @param cedulaBuscada Cédula del usuario a modificar.
 * @param montoRetiro Monto que desea retirar.
 * @return true si el retiro fue exitoso, false en caso de fondos insuficientes o cédula inexistente.
 */
bool modificarDineroUsuario(char** lineas, int numUsuarios, const char* cedulaBuscada, int montoRetiro);

/**
 * @brief Extrae la cédula y la clave de una línea de texto con formato delimitado.
 *
 * Esta función asume que la cédula es el primer campo y la clave el segundo,
 * y ambos están separados por una coma. Ignora espacios y tabuladores
 * al inicio y alrededor de la coma.
 *
 * @param linea La línea de texto de donde se extraerán los datos.
 * @param cedula Puntero al buffer donde se almacenará la cédula extraída (salida).
 * @param maxCedula El tamaño máximo del buffer para la cédula.
 * @param clave Puntero al buffer donde se almacenará la clave extraída (salida).
 * @param maxClave El tamaño máximo del buffer para la clave.
 */
void extraerCedulaYClave(const char* linea, char* cedula, int maxCedula, char* clave, int maxClave);

#endif // OPERACIONES_USUARIO_H
