/**
 * @file main.cpp
 * @brief Archivo principal del sistema de cajero automático v2.0.
 *
 * Este archivo contiene la función main que gestiona la carga segura de datos,
 * verificación, encriptación y desencriptación de archivos de usuarios y administradores,
 * y la ejecución del menú principal del sistema.
 */

#include <iostream>
#include "menu.h"
#include "Encriptacion.h"
#include "ManipulacionDeArchivos.h"

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
    char rutaUsuarios[] = "../../Datos/usuarios.bin";    /**< Ruta del archivo usuarios */
    char rutaAdmins[] = "../../Datos/sudo.bin";          /**< Ruta del archivo administradores */
    int numUsuarios = 0, numAdmins = 0;                   /**< Contadores de registros */
    const int SEMILLA = 4;                                 /**< Semilla para encriptación */

    cout << "================================================\n";
    cout << "    SISTEMA DE CAJERO AUTOMATICO \n";
    cout << "         Carga Segura de Datos\n";
    cout << "================================================\n\n";

    cout << "[1/5] Cargando archivos del sistema...\n";
    char** usuarios = leerArchivoLineas(rutaUsuarios, numUsuarios); /**< Carga usuarios */
    char** admins = leerArchivoLineas(rutaAdmins, numAdmins);       /**< Carga administradores */

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
    cout << "  - Admins: " << numAdmins << " registros\n\n";

    cout << "[2/5] Verificando estado de encriptacion...\n";
    bool yaEncriptados = verificarEstadoEncriptacion(usuarios, admins);

    if (!yaEncriptados) {
        cout << "Archivos en texto plano → Encriptando con semilla " << SEMILLA << "...\n";
        encriptarArchivo(admins, numAdmins, SEMILLA);
        encriptarArchivo(usuarios, numUsuarios, SEMILLA);
        guardarArchivoLineas(rutaUsuarios, usuarios, numUsuarios);
        guardarArchivoLineas(rutaAdmins, admins, numAdmins);
        cout << "Archivos encriptados y guardados.\n\n";

        for (int i = 0; i < numUsuarios; i++) delete[] usuarios[i];
        delete[] usuarios;
        for (int i = 0; i < numAdmins; i++) delete[] admins[i];
        delete[] admins;

        usuarios = leerArchivoLineas(rutaUsuarios, numUsuarios);
        admins = leerArchivoLineas(rutaAdmins, numAdmins);
        cout << "Archivos recargados.\n\n";
    } else {
        cout << "Los archivos ya estan encriptados.\n\n";
    }

    cout << "[" << (yaEncriptados ? "3" : "4") << "/5] Desencriptando datos en memoria...\n";
    desencriptarArchivo(admins, numAdmins, SEMILLA);
    desencriptarArchivo(usuarios, numUsuarios, SEMILLA);
    cout << "Datos desencriptados y listos para usar.\n\n";

    cout << "--- DEPURACION: Usuarios desencriptados ---\n";
    mostrarLineas(usuarios, numUsuarios);
    cout << "--- DEPURACION: Administradores desencriptados ---\n";
    mostrarLineas(admins, numAdmins);

    cout << "[" << (yaEncriptados ? "4" : "5") << "/5] Iniciando sistema de cajero...\n";
    cout<< "\n\n\n\n\n\n\n\n\n\n";
    menuPrincipal(usuarios, numUsuarios, admins, numAdmins);

    cout << "\nGuardando cambios de forma segura...\n";
    encriptarArchivo(admins, numAdmins, SEMILLA);
    encriptarArchivo(usuarios, numUsuarios, SEMILLA);
    guardarArchivoLineas(rutaUsuarios, usuarios, numUsuarios);
    guardarArchivoLineas(rutaAdmins, admins, numAdmins);
    cout << "Datos guardados y encriptados correctamente.\n";

    for (int i = 0; i < numUsuarios; i++) delete[] usuarios[i];
    delete[] usuarios;
    for (int i = 0; i < numAdmins; i++) delete[] admins[i];
    delete[] admins;

    cout << "\n================================================\n";
    cout << "     Sesion finalizada correctamente\n";
    cout << "================================================\n";
    return 0;
}
