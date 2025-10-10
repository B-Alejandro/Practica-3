/**
 * @file main.cpp
 * @brief Archivo principal del sistema de cajero automático v2.0 sin std::exception.
 *
 * Maneja la carga segura, verificación, encriptación/desencriptación
 * y ejecución del menú principal usando manejo de errores manual con `throw` y `catch`.
 */

#include <iostream>
#include "Menu.h"
#include "Encriptacion.h"
#include "ManipulacionDeArchivos.h"

using namespace std;

/**
 * @brief Función principal del sistema de cajero automático.
 *
 * Carga y verifica archivos, encripta/desencripta datos,
 * inicia el menú principal y guarda cambios de manera segura.
 *
 * @return 0 si la ejecución fue exitosa, 1 si ocurrió un error.
 */
int main() {
    try {
        char rutaUsuarios[] = "../../Datos/usuarios.bin";   /**< Ruta de usuarios */
        char rutaAdmins[]   = "../../Datos/sudo.bin";       /**< Ruta de administradores */
        int numUsuarios = 0, numAdmins = 0;                 /**< Contadores de registros */
        const int SEMILLA = 4;                              /**< Semilla de encriptación */

        cout << "================================================\n";
        cout << "    SISTEMA DE CAJERO AUTOMATICO \n";
        cout << "         Carga Segura de Datos\n";
        cout << "================================================\n\n";

        cout << "[1/5] Cargando archivos del sistema...\n";
        char** usuarios = leerArchivoLineas(rutaUsuarios, numUsuarios);
        char** admins   = leerArchivoLineas(rutaAdmins, numAdmins);

        // Validación manual
        if (!usuarios || numUsuarios == 0)
            throw "Error: no se pudieron cargar los usuarios.";
        if (!admins || numAdmins == 0)
            throw "Error: no se pudieron cargar los administradores.";

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

            // Liberar memoria
            for (int i = 0; i < numUsuarios; i++) delete[] usuarios[i];
            delete[] usuarios;
            for (int i = 0; i < numAdmins; i++) delete[] admins[i];
            delete[] admins;

            // Recargar archivos
            usuarios = leerArchivoLineas(rutaUsuarios, numUsuarios);
            admins   = leerArchivoLineas(rutaAdmins, numAdmins);
            if (!usuarios || !admins)
                throw "Error al recargar los archivos encriptados.";
            cout << "Archivos recargados.\n\n";
        } else {
            cout << "Los archivos ya están encriptados.\n\n";
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
        cout << "\n\n\n\n\n\n\n\n\n\n";

        // Ejecución principal
        menuPrincipal(usuarios, numUsuarios, admins, numAdmins);

        cout << "\nGuardando cambios de forma segura...\n";
        encriptarArchivo(admins, numAdmins, SEMILLA);
        encriptarArchivo(usuarios, numUsuarios, SEMILLA);
        guardarArchivoLineas(rutaUsuarios, usuarios, numUsuarios);
        guardarArchivoLineas(rutaAdmins, admins, numAdmins);
        cout << "Datos guardados y encriptados correctamente.\n";

        // Liberar memoria
        for (int i = 0; i < numUsuarios; i++) delete[] usuarios[i];
        delete[] usuarios;
        for (int i = 0; i < numAdmins; i++) delete[] admins[i];
        delete[] admins;

        cout << "\n================================================\n";
        cout << "     Sesión finalizada correctamente\n";
        cout << "================================================\n";
        return 0;
    }

    // Captura de errores por texto
    catch (const char* msg) {
        cerr << "\n[Error] " << msg << "\n";
        return 1;
    }

    // Captura de errores tipo string
    catch (const string& msg) {
        cerr << "\n[Error] " << msg << "\n";
        return 1;
    }

    // Captura genérica
    catch (...) {
        cerr << "\n[Error desconocido] Ha ocurrido un problema inesperado.\n";
        return 1;
    }
}
