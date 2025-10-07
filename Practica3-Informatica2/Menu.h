#ifndef MENU_H
#define MENU_H

#include "UtilidadesCadena.h"
#include "OperacionesUsuario.h"
#include "ManipulacionDeArchivos.h"

/**
 * @brief Elimina espacios, tabs, CR, LF al inicio y al final de una cadena (in-place).
 *
 * Modifica la cadena directamente, removiendo caracteres de espacio en blanco
 * al principio y al final.
 *
 * @param s Cadena a limpiar.
 */
void trim(char* s);

/**
 * @brief Extrae cedula y clave desde una linea con formato "cedula,clave,...".
 *
 * Parsea una linea CSV y extrae los dos primeros campos (cedula y clave),
 * aplicando trim automaticamente a ambos valores.
 *
 * @param linea Linea completa a procesar.
 * @param cedula Buffer donde se almacenara la cedula extraida.
 * @param maxCedula Tamanio maximo del buffer de cedula.
 * @param clave Buffer donde se almacenara la clave extraida.
 * @param maxClave Tamanio maximo del buffer de clave.
 */
void extraerCedulaYClave(const char* linea, char* cedula, int maxCedula, char* clave, int maxClave);

/**
 * @brief Menu de administrador para registrar nuevos usuarios.
 *
 * Solicita credenciales de administrador, las valida contra el arreglo de admins,
 * y si son correctas, permite agregar un nuevo usuario al sistema.
 * El nuevo usuario se agrega al arreglo dinamico y se guarda en el archivo.
 *
 * @param usuarios Arreglo de usuarios (se modifica por referencia si se anade un usuario).
 * @param numUsuarios Numero de usuarios (se incrementa si se anade uno nuevo).
 * @param admins Arreglo de administradores para validacion de acceso.
 * @param numAdmins Numero de administradores en el sistema.
 */
void menuAdministrador(char**& usuarios, int& numUsuarios, char** admins, int numAdmins);

/**
 * @brief Menu de usuario para consultas y retiros.
 *
 * Solicita cedula y clave del usuario, valida las credenciales y presenta
 * un submenu con operaciones disponibles:
 * - Consultar saldo (con costo de 1000 COP)
 * - Retirar dinero (con costo de transaccion de 1000 COP)
 * - Volver al menu principal
 *
 * @param usuarios Arreglo de usuarios.
 * @param numUsuarios Numero de usuarios en el sistema.
 */
void menuUsuario(char** usuarios, int numUsuarios);

/**
 * @brief Menu principal del sistema bancario.
 *
 * Presenta las opciones principales en un loop:
 * 1. Acceso como administrador
 * 2. Acceso como usuario
 * 3. Salir del sistema
 *
 * Incluye validacion de entrada y manejo de errores.
 *
 * @param usuarios Arreglo de usuarios (se puede modificar desde submenu de admin).
 * @param numUsuarios Numero de usuarios (se puede modificar desde submenu de admin).
 * @param admins Arreglo de administradores.
 * @param numAdmins Numero de administradores.
 */
void menuPrincipal(char**& usuarios, int& numUsuarios, char** admins, int numAdmins);

#endif // MENU_H
