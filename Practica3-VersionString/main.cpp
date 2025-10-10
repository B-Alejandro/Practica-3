/**
 * @file main.cpp
 * @brief Archivo principal del sistema de cajero automatico v2.0.
 *
 * Gestiona carga segura, verificacion, encriptacion/desencriptacion,
 * ejecucion del menu principal y guardado confiable de datos.
 */

#include <iostream>
#include <string>
#include "Menu.h"
#include "Encriptacion.h"
#include "ManipulacionArchivos.h"

using namespace std;

/**
 * @brief Funcion principal de la aplicacion.
 *
 * Ejecuta la secuencia principal de carga, encriptacion, desencriptacion,
 * menu principal y guardado seguro de datos.
 *
 * @return Codigo de salida del programa: 0 exito, 1 error controlado.
 */
int main() {
    const string rutaUsuarios = "../../Datos/usuarios.bin";
    const string rutaAdmins   = "../../Datos/sudo.bin";
    const int SEMILLA = 4;
    int numUsuarios = 0, numAdmins = 0;

    try {
        cout << "================================================\n";
        cout << "    SISTEMA DE CAJERO AUTOMATICO v2.0\n";
        cout << "================================================\n\n";

        // [1] Cargar archivos
        cout << "[1/5] Cargando archivos del sistema...\n";
        string* usuarios = leerArchivoLineas(rutaUsuarios.c_str(), numUsuarios);
        string* admins   = leerArchivoLineas(rutaAdmins.c_str(), numAdmins);

        if (!usuarios || numUsuarios == 0)
            throw "Error: No se pudieron cargar usuarios.";
        if (!admins || numAdmins == 0)
            throw "Error: No se pudieron cargar administradores.";

        cout << "Archivos cargados correctamente.\n";
        cout << "  - Usuarios: " << numUsuarios << " registros\n";
        cout << "  - Admins:   " << numAdmins << " registros\n\n";

        // [2] Verificar estado de encriptacion
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

            if (!usuarios || !admins)
                throw "Error al recargar los archivos encriptados.";

            cout << "Archivos recargados.\n\n";
        } else {
            cout << "Los archivos ya estan encriptados.\n\n";
        }

        // [3] Desencriptar en memoria
        cout << "[" << (yaEncriptados ? "3" : "4") << "/5] Desencriptando datos en memoria...\n";
        desencriptarArchivo(admins, numAdmins, SEMILLA);
        desencriptarArchivo(usuarios, numUsuarios, SEMILLA);
        cout << "Datos desencriptados y listos para usar.\n\n";

        // Mostrar datos desencriptados (modo debug)
        cout << "--- DEPURACION: Usuarios desencriptados ---\n";
        mostrarLineas(usuarios, numUsuarios);
        cout << "--- DEPURACION: Administradores desencriptados ---\n";
        mostrarLineas(admins, numAdmins);

        // [4] Iniciar sistema
        cout << "[" << (yaEncriptados ? "4" : "5") << "/5] Iniciando sistema de cajero...\n";
        cout << "\n\n\n\n\n\n\n\n\n\n";

        try {
            menuPrincipal(usuarios, numUsuarios, admins, numAdmins);
        } catch (const char* e) {
            cerr << "[Error en menuPrincipal] " << e << endl;
        }

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
        cout << "     Sesion finalizada correctamente\n";
        cout << "================================================\n";
        return 0;
    }
    catch (const char* e) {
        cerr << "[Error controlado] " << e << endl;
        return 1;
    }
    catch (...) {
        cerr << "[Error desconocido] Ocurrio un problema inesperado.\n";
        return 1;
    }
}
