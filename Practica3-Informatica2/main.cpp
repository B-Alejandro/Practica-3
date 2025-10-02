#include <iostream>
#include "menu.h"
#include "sistema.h"
using namespace std;

// MAIN
int main() {
    char rutaUsuarios[] = "../../Datos/usuarios.txt";
    char rutaAdmins[] = "../../Datos/sudo.txt";

    int numUsuarios = 0, numAdmins = 0;
    char** usuarios = leerArchivoLineas(rutaUsuarios, numUsuarios);
    char** admins = leerArchivoLineas(rutaAdmins, numAdmins);

    if (usuarios == nullptr || numUsuarios == 0) {
        cerr << "No se pudieron cargar usuarios.\n";
        return 1;
    }
    if (admins == nullptr || numAdmins == 0) {
        cerr << "No se pudieron cargar administradores.\n";
        return 1;
    }

    menuPrincipal(usuarios, numUsuarios, admins, numAdmins);

    // Liberar memoria
    for (int i = 0; i < numUsuarios; i++) delete[] usuarios[i];
    delete[] usuarios;

    for (int i = 0; i < numAdmins; i++) delete[] admins[i];
    delete[] admins;

    return 0;
}
