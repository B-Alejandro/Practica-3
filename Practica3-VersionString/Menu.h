#ifndef MENUS_BANCARIOS_H
#define MENUS_BANCARIOS_H

#include <string>

/**
 * @brief Muestra el menú principal del sistema bancario.
 */
void menuPrincipal(std::string*& usuarios, int& numUsuarios, std::string* admins, int numAdmins);

/**
 * @brief Menú del administrador (permite registrar nuevos usuarios).
 */
void menuAdministrador(std::string*& usuarios, int& numUsuarios, std::string* admins, int numAdmins);

/**
 * @brief Menú del usuario (consultar saldo, retirar dinero, etc.).
 */
void menuUsuario(std::string* usuarios, int numUsuarios);

#endif // MENUS_BANCARIOS_H
