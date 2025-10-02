#include <iostream>
#include "menu.h"
#include "sistema.h"
using namespace std;

// ---- Funciones auxiliares ----

// Elimina espacios, tabs, CR, LF al inicio y al final (in-place)
void trim(char* s) {
    if (!s) return;
    int len = 0;
    while (s[len] != '\0') len++;

    int start = 0;
    while (start < len && (s[start] == ' ' || s[start] == '\t' || s[start] == '\r' || s[start] == '\n'))
        start++;

    int end = len - 1;
    while (end >= start && (s[end] == ' ' || s[end] == '\t' || s[end] == '\r' || s[end] == '\n'))
        end--;

    int j = 0;
    for (int i = start; i <= end; ++i) s[j++] = s[i];
    s[j] = '\0';
}

// Extrae cédula y clave desde una línea con formato "cedula,clave,..."
void extraerCedulaYClave(const char* linea, char* cedula, int maxCedula, char* clave, int maxClave) {
    int i = 0, j = 0;

    // Saltar espacios iniciales
    while (linea[i] != '\0' && (linea[i] == ' ' || linea[i] == '\t')) i++;

    // Copiar cédula hasta la coma
    j = 0;
    while (linea[i] != '\0' && linea[i] != ',' && j < maxCedula - 1) cedula[j++] = linea[i++];
    cedula[j] = '\0';

    if (linea[i] == ',') i++; // saltar coma

    // Saltar espacios después de la coma
    while (linea[i] != '\0' && (linea[i] == ' ' || linea[i] == '\t')) i++;

    // Copiar clave hasta fin de línea o CR/LF
    j = 0;
    while (linea[i] != '\0' && linea[i] != '\r' && linea[i] != '\n' && j < maxClave - 1) clave[j++] = linea[i++];
    clave[j] = '\0';

    // Limpiar espacios al inicio y final
    trim(cedula);
    trim(clave);
}

// ---- Menú administrador ----
void menuAdministrador(char**& usuarios, int& numUsuarios, char** admins, int numAdmins) {
    char cedulaAdmin[50], claveIngresada[50];
    cout << "\n--- Acceso Administrador ---\n";
    cout << "Ingrese su cédula de administrador: ";
    cin >> cedulaAdmin;
    trim(cedulaAdmin);

    bool valido = false;
    for (int i = 0; i < numAdmins; i++) {
        char cedulaArchivo[50], claveArchivo[50];
        extraerCedulaYClave(admins[i], cedulaArchivo, sizeof(cedulaArchivo), claveArchivo, sizeof(claveArchivo));

        if (cadenasIguales(cedulaArchivo, cedulaAdmin)) {
            cout << "Ingrese su contraseña de administrador: ";
            cin >> claveIngresada;
            trim(claveIngresada);

            if (cadenasIguales(claveArchivo, claveIngresada)) {
                valido = true;
            }
            break;
        }
    }

    if (!valido) {
        cout << "Credenciales inválidas. Verifique cédula o clave.\n";
        return;
    }

    // Registro de usuario
    char cedula[50], clave[50], nombre[100];
    int saldoInicial;

    cout << "\n--- Registrar Nuevo Usuario ---\n";
    cout << "Ingrese la cédula del nuevo usuario: ";
    cin >> cedula;
    trim(cedula);

    // Validar que no exista
    for (int i = 0; i < numUsuarios; i++) {
        char cedulaUsr[50], claveUsr[50];
        extraerCedulaYClave(usuarios[i], cedulaUsr, sizeof(cedulaUsr), claveUsr, sizeof(claveUsr));
        if (cadenasIguales(cedulaUsr, cedula)) {
            cout << "Ya existe un usuario con esa cédula.\n";
            return;
        }
    }

    cout << "Ingrese la clave: ";
    cin >> clave;
    trim(clave);

    cout << "Ingrese el nombre completo: ";
    cin.ignore();              // limpia salto de línea pendiente
    cin.getline(nombre, 100);  // permite espacios

    cout << "Ingrese el saldo inicial: ";
    cin >> saldoInicial;

    // Crear línea: "cedula,clave,nombre,saldo COP"
    char* nuevoUsuario = new char[300];
    nuevoUsuario[0] = '\0';
    concatenar(nuevoUsuario, cedula);
    concatenar(nuevoUsuario, ",");
    concatenar(nuevoUsuario, clave);
    concatenar(nuevoUsuario, ",");
    concatenar(nuevoUsuario, nombre);
    concatenar(nuevoUsuario, ",");

    char saldoStr[50];
    sprintf(saldoStr, "%d", saldoInicial);
    concatenar(nuevoUsuario, saldoStr);
    concatenar(nuevoUsuario, " COP");

    usuarios[numUsuarios] = nuevoUsuario;
    numUsuarios++;

    // Guardar cambios en archivo
    guardarUsuariosEnArchivo(usuarios, numUsuarios, "../../Datos/usuarios.txt");
    cout << "Usuario agregado correctamente.\n";
}

// ---- Menú cliente ----
void menuUsuario(char** usuarios, int numUsuarios) {
    char cedula[50], claveIngresada[50];
    int monto;

    cout << "\n--- Menu Usuario ---\n";
    cout << "Ingrese su cédula: ";
    cin >> cedula;
    trim(cedula);

    cout << "Ingrese su clave: ";
    cin >> claveIngresada;
    trim(claveIngresada);

    bool valido = false;
    for (int i = 0; i < numUsuarios; i++) {
        char cedulaArchivo[100], claveArchivo[100];
        extraerCedulaYClave(usuarios[i], cedulaArchivo, sizeof(cedulaArchivo), claveArchivo, sizeof(claveArchivo));

        if (cadenasIguales(cedulaArchivo, cedula) && cadenasIguales(claveArchivo, claveIngresada)) {
            valido = true;
            cout << "Credenciales válidas. Ingrese monto a retirar: ";
            cin >> monto;
            modificarDineroUsuario(usuarios, numUsuarios, cedula, monto);
            guardarUsuariosEnArchivo(usuarios, numUsuarios, "../../Datos/usuarios.txt");
            break;
        }
    }
    if (!valido) {
        cout << "Credenciales inválidas. Verifique cédula o clave.\n";
    }
}

// ---- Menú principal ----
void menuPrincipal(char**& usuarios, int& numUsuarios, char** admins, int numAdmins) {
    int opcion;
    do {
        cout << "\n--- Menu Principal ---\n";
        cout << "1. Administrador\n";
        cout << "2. Usuario\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            menuAdministrador(usuarios, numUsuarios, admins, numAdmins);
            break;
        case 2:
            menuUsuario(usuarios, numUsuarios);
            break;
        case 3:
            cout << "Saliendo del sistema...\n";
            break;
        default:
            cout << "Opción inválida.\n";
        }
    } while (opcion != 3);
}
