/**
 * @file main.cpp
 * @brief Archivo principal del sistema de cajero automático v2.0.
 *
 * Este archivo contiene la función main que gestiona la carga segura de datos,
 * verificación, encriptación y desencriptación de archivos de usuarios y administradores,
 * y la ejecución del menú principal del sistema.
 */

#include <iostream>
#include <string>
#include "Menu.h"
#include "Encriptacion.h"
#include "ManipulacionArchivos.h"

using namespace std;

/**
 * @brief Función principal de la aplicación.
 *
 * Ejecuta la secuencia principal para cargar archivos de usuarios y administradores,
 * verificar y gestionar encriptación y desencriptación, mostrar datos para depuración,
 * iniciar el sistema de cajero y guardar cambios de forma segura.
 *
 * @return Código de salida del programa. 0 para éxito, 1 para error.
 */
int main() {
    const string rutaUsuarios = "../../Datos/usuarios.bin";   /**< Ruta del archivo usuarios */
    const string rutaAdmins   = "../../Datos/sudo.bin";       /**< Ruta del archivo administradores */
    int numUsuarios = 0, numAdmins = 0;                       /**< Contadores de registros */
    const int SEMILLA = 4;                                    /**< Semilla para encriptación */

    cout << "================================================\n";
    cout << "    SISTEMA DE CAJERO AUTOMATICO \n";
    cout << "         Carga Segura de Datos\n";
    cout << "================================================\n\n";

    // [1] Cargar archivos
    cout << "[1/5] Cargando archivos del sistema...\n";
    string* usuarios = leerArchivoLineas(rutaUsuarios.c_str(), numUsuarios);
    string* admins   = leerArchivoLineas(rutaAdmins.c_str(), numAdmins);

    if (!usuarios || numUsuarios == 0) {
        cerr << "Error: No se pudieron cargar usuarios.\n";
        return 1;
    }
    if (!admins || numAdmins == 0) {
        cerr << "Error: No se pudieron cargar administradores.\n";
        return 1;
    }

    cout << "Archivos cargados correctamente.\n";
    cout << "  - Usuarios: " << numUsuarios << " registros\n";
    cout << "  - Admins:   " << numAdmins << " registros\n\n";

    // [2] Verificar si ya están encriptados
    cout << "[2/5] Verificando estado de encriptacion...\n";
    bool yaEncriptados = verificarEstadoEncriptacion(usuarios, admins);

    if (!yaEncriptados) {
        cout << "Archivos en texto plano → Encriptando con semilla " << SEMILLA << "...\n";
        encriptarArchivo(admins, numAdmins, SEMILLA);
        encriptarArchivo(usuarios, numUsuarios, SEMILLA);

        guardarArchivoLineas(rutaUsuarios.c_str(), usuarios, numUsuarios);
        guardarArchivoLineas(rutaAdmins.c_str(), admins, numAdmins);

        cout << "Archivos encriptados y guardados.\n\n";

        delete[] usuarios;
        delete[] admins;

        usuarios = leerArchivoLineas(rutaUsuarios.c_str(), numUsuarios);
        admins   = leerArchivoLineas(rutaAdmins.c_str(), numAdmins);

        cout << "Archivos recargados.\n\n";
    } else {
        cout << "Los archivos ya están encriptados.\n\n";
    }

    // [3] Desencriptar en memoria
    cout << "[" << (yaEncriptados ? "3" : "4") << "/5] Desencriptando datos en memoria...\n";
    desencriptarArchivo(admins, numAdmins, SEMILLA);
    desencriptarArchivo(usuarios, numUsuarios, SEMILLA);
    cout << "Datos desencriptados y listos para usar.\n\n";

    // Mostrar datos desencriptados (debug)
    cout << "--- DEPURACION: Usuarios desencriptados ---\n";
    mostrarLineas(usuarios, numUsuarios);
    cout << "--- DEPURACION: Administradores desencriptados ---\n";
    mostrarLineas(admins, numAdmins);

    // [4] Iniciar sistema
    cout << "[" << (yaEncriptados ? "4" : "5") << "/5] Iniciando sistema de cajero...\n";
    cout << "\n\n\n\n\n\n\n\n\n\n";

    menuPrincipal(usuarios, numUsuarios, admins, numAdmins);

    // [5] Guardar cambios
    cout << "\nGuardando cambios de forma segura...\n";
    encriptarArchivo(admins, numAdmins, SEMILLA);
    encriptarArchivo(usuarios, numUsuarios, SEMILLA);

    guardarArchivoLineas(rutaUsuarios.c_str(), usuarios, numUsuarios);
    guardarArchivoLineas(rutaAdmins.c_str(), admins, numAdmins);

    cout << "Datos guardados y encriptados correctamente.\n";

    delete[] usuarios;
    delete[] admins;

    cout << "\n================================================\n";
    cout << "     Sesión finalizada correctamente\n";
    cout << "================================================\n";
    return 0;
}
