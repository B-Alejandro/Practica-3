#include <iostream>
#include "menu.h"
#include "Sistema.h"
#include "Encriptacion.h"
using namespace std;

int main() {
    char rutaUsuarios[] = "../../Datos/usuarios.bin";
    char rutaAdmins[] = "../../Datos/sudo.bin";
    int numUsuarios = 0, numAdmins = 0;
    const int SEMILLA = 4; // Semilla de encriptación

    cout << "================================================\n";
    cout << "    SISTEMA DE CAJERO AUTOMATICO v2.0\n";
    cout << "         Carga Segura de Datos\n";
    cout << "================================================\n\n";

    // ==================== CARGA DE ARCHIVOS ====================
    cout << "[1/5] Cargando archivos del sistema...\n";
    char** usuarios = leerArchivoLineas(rutaUsuarios, numUsuarios);
    char** admins = leerArchivoLineas(rutaAdmins, numAdmins);

    if (usuarios == nullptr || numUsuarios == 0) {
        cerr << "Error: No se pudieron cargar usuarios.\n";
        return 1;
    }
    if (admins == nullptr || numAdmins == 0) {
        cerr << "Error: No se pudieron cargar administradores.\n";
        return 1;
    }

    cout << "Archivos cargados correctamente.\n";
    cout << "  - Usuarios: " << numUsuarios << " registros\n";
    cout << "  - Admins: " << numAdmins << " registros\n\n";

    // ==================== VERIFICACIÓN DE ENCRIPTACIÓN ====================
    cout << "[2/5] Verificando estado de encriptacion...\n";
    bool yaEncriptados = verificarEstadoEncriptacion(usuarios, admins);

    if (!yaEncriptados) {
        // Archivos en texto plano → Encriptar
        cout << "Los archivos estan en texto plano.\n";
        cout << "Encriptando con semilla " << SEMILLA << "...\n";

        encriptarArchivo(admins, numAdmins, SEMILLA);
        encriptarArchivo(usuarios, numUsuarios, SEMILLA);

        // Guardar archivos encriptados
        guardarArchivoLineas(rutaUsuarios, usuarios, numUsuarios);
        guardarArchivoLineas(rutaAdmins, admins, numAdmins);

        cout << "Archivos encriptados y guardados.\n\n";

        // Recargar archivos encriptados
        cout << "[3/5] Recargando archivos encriptados...\n";
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

    // ==================== DESENCRIPTACIÓN EN MEMORIA ====================
    cout << "[" << (yaEncriptados ? "3" : "4") << "/5] Desencriptando datos en memoria...\n";
    desencriptarArchivo(admins, numAdmins, SEMILLA);
    desencriptarArchivo(usuarios, numUsuarios, SEMILLA);
    cout << "Datos desencriptados y listos para usar.\n\n";

    // Mostrar datos desencriptados para depuración
    cout << "--- DEPURACION: Usuarios desencriptados ---" << endl;
    mostrarLineas(usuarios, numUsuarios);

    cout << "--- DEPURACION: Administradores desencriptados ---" << endl;
    mostrarLineas(admins, numAdmins);

    // ==================== EJECUCIÓN DEL SISTEMA ====================
    cout << "[" << (yaEncriptados ? "4" : "5") << "/5] Iniciando sistema de cajero...\n";
    cout << "================================================\n\n";

    menuPrincipal(usuarios, numUsuarios, admins, numAdmins);

    // ==================== GUARDADO SEGURO ====================
    cout << "\n================================================\n";
    cout << "Guardando cambios de forma segura...\n";

    // Encriptar antes de guardar
    encriptarArchivo(admins, numAdmins, SEMILLA);
    encriptarArchivo(usuarios, numUsuarios, SEMILLA);

    // Guardar archivos encriptados
    guardarArchivoLineas(rutaUsuarios, usuarios, numUsuarios);
    guardarArchivoLineas(rutaAdmins, admins, numAdmins);

    cout << "Datos guardados y encriptados correctamente.\n";

    // ==================== LIBERACIÓN DE MEMORIA ====================
    for (int i = 0; i < numUsuarios; i++)
        delete[] usuarios[i];
    delete[] usuarios;

    for (int i = 0; i < numAdmins; i++)
        delete[] admins[i];
    delete[] admins;

    cout << "\n================================================\n";
    cout << "     Sesion finalizada correctamente\n";
    cout << "================================================\n";

    return 0;
}
