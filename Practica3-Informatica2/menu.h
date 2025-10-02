#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
using namespace std;

/// @brief Longitud máxima de caracteres para almacenar un registro de usuario
const int MAX_LONG = 200;

/**
 * @brief Modifica el saldo de un usuario retirando un monto especificado.
 *
 * Busca la cédula en el arreglo de usuarios y, si existe suficiente saldo,
 * descuenta el monto solicitado.
 *
 * @param lineas Arreglo de usuarios en formato de texto
 * @param numUsuarios Cantidad de usuarios registrados
 * @param cedulaBuscada Cédula del usuario que realiza el retiro
 * @param montoRetiro Monto a retirar
 * @return true si la transacción fue exitosa
 * @return false si no se encontró el usuario o no había saldo suficiente
 */
bool modificarDineroUsuario(char** lineas, int numUsuarios, const char* cedulaBuscada, int montoRetiro);

/**
 * @brief Valida el acceso de un cliente por su cédula.
 *
 * Compara la cédula ingresada con las registradas en el sistema.
 *
 * @param cedula Cédula ingresada por el cliente
 * @return true si la cédula existe en el sistema
 * @return false en caso contrario
 */
bool validarCliente(const char cedula[]);

void menuAdministrador(char**& usuarios, int& numUsuarios, char** admins, int numAdmins);
void menuUsuario(char** usuarios, int numUsuarios);
void menuPrincipal(char**& usuarios, int& numUsuarios, char** admins, int numAdmins);
/**
 * @brief Registra un nuevo usuario en el sistema.
 *
 * Pide cédula, contraseña, nombre y saldo inicial, y los guarda en el arreglo de usuarios.
 *
 * @param usuarios Arreglo bidimensional donde se almacenan los usuarios
 * @param numUsuarios Cantidad actual de usuarios registrados (se actualiza al agregar uno nuevo)
 */
void registrarUsuario(char usuarios[][MAX_LONG], int& numUsuarios);

/**
 * @brief Copia una cadena en otra.
 *
 * Implementación propia de strcpy sin librerías externas.
 *
 * @param destino Arreglo donde se copiará la cadena
 * @param origen Cadena original a copiar
 */
void copiarCadena(char* destino, const char* origen);

/**
 * @brief Concatena una cadena al final de otra.
 *
 * Implementación propia de strcat sin librerías externas.
 *
 * @param destino Cadena base que recibirá la concatenación
 * @param origen Cadena que se añadirá al final de destino
 */

void concatenar(char* destino, const char* origen) ;

/**
 * @brief Compara dos cadenas de caracteres.
 *
 * Implementación propia de strcmp sin librerías externas.
 *
 * @param cad1 Primera cadena a comparar
 * @param cad2 Segunda cadena a comparar
 * @return true si ambas cadenas son iguales
 * @return false si son diferentes
 */
bool cadenasIguales(const char* cad1, const char* cad2);

#endif
