#include <iostream>
#include "menu.h"
#include "Validaciones.h"  // <-- Importante: para usar las funciones de validación
using namespace std;

// ---- Funciones auxiliares ----
void extraerCedulaYClave(const char* linea, char* cedula, int maxCedula, char* clave, int maxClave) {
    int i = 0, j = 0;

    // Saltar espacios iniciales
    while (linea[i] != '\0' && (linea[i] == ' ' || linea[i] == '\t')) i++;

    // Copiar cédula hasta coma o CR/LF
    j = 0;
    while (linea[i] != '\0' && linea[i] != ',' && linea[i] != '\r' && linea[i] != '\n' && j < maxCedula - 1)
        cedula[j++] = linea[i++];
    cedula[j] = '\0';

    if (linea[i] == ',') i++; // saltar coma

    // Saltar espacios después de la coma
    while (linea[i] != '\0' && (linea[i] == ' ' || linea[i] == '\t')) i++;

    // Copiar clave hasta siguiente coma o CR/LF
    j = 0;
    while (linea[i] != '\0' && linea[i] != ',' && linea[i] != '\r' && linea[i] != '\n' && j < maxClave - 1)
        clave[j++] = linea[i++];
    clave[j] = '\0';
}

// ---- Menu administrador ----
void menuAdministrador(char**& usuarios, int& numUsuarios, char** admins, int numAdmins) {
    char cedulaAdmin[50], claveIngresada[50];
    cout << "\n=================================\n";
    cout << "    ACCESO ADMINISTRADOR\n";
    cout << "=================================\n";
    cout << "Cedula de administrador: ";
    cin >> cedulaAdmin;

    bool valido = false;
    for (int i = 0; i < numAdmins; i++) {
        char cedulaArchivo[50], claveArchivo[50];
        extraerCedulaYClave(admins[i], cedulaArchivo, sizeof(cedulaArchivo), claveArchivo, sizeof(claveArchivo));

        if (cadenasIguales(cedulaArchivo, cedulaAdmin)) {
            cout << "Contrasena: ";
            cin >> claveIngresada;

            if (cadenasIguales(claveArchivo, claveIngresada)) {
                valido = true;
            }
            break;
        }
    }

    if (!valido) {
        cout << "\n Credenciales invalidas.\n";
        return;
    }

    // Registro de usuario
    char cedula[50], clave[50], nombre[100], saldoStr[50];
    int saldoInicial;

    cout << "\n=================================\n";
    cout << "   REGISTRAR NUEVO USUARIO\n";
    cout << "=================================\n";

    // ===== Validar CÉDULA =====
    do {
        cout << "Cedula del nuevo usuario: ";
        cin >> cedula;
        if (!validarCedula(cedula)) {
            cout << " Cedula invalida. Debe tener entre 6 y 10 digitos numericos y no empezar con 0.\n";
        }
    } while (!validarCedula(cedula));

    // Verificar que no exista
    for (int i = 0; i < numUsuarios; i++) {
        char cedulaUsr[50], claveUsr[50];
        extraerCedulaYClave(usuarios[i], cedulaUsr, sizeof(cedulaUsr), claveUsr, sizeof(claveUsr));
        if (cadenasIguales(cedulaUsr, cedula)) {
            cout << "\n Ya existe un usuario con esa cedula.\n";
            return;
        }
    }

    // ===== Validar CONTRASEÑA =====
    do {
        cout << "Clave: ";
        cin >> clave;
        if (!validarContrasena(clave)) {
            cout << " Contrasena invalida.\n"
                    "Debe tener entre 8 y 20 caracteres, incluir al menos:\n"
                    " - una mayuscula\n - un numero\n - un caracter especial\n"
                    "y no contener espacios.\n";
        }
    } while (!validarContrasena(clave));

    // ===== Nombre =====
    cout << "Nombre completo: ";
    cin.ignore();
    cin.getline(nombre, 100);

    // ===== Validar SALDO =====
    do {
        cout << "Saldo inicial (0 - 1,000,000): ";
        cin >> saldoStr;
        if (!validarSaldo(saldoStr)) {
            cout << "Saldo invalido. Debe ser un numero entre 0 y 1,000,000.\n";
        }
    } while (!validarSaldo(saldoStr));

    saldoInicial = atoi(saldoStr);

    // Crear linea: "cedula,clave,nombre,saldo COP"
    char* nuevoUsuario = new char[300];
    nuevoUsuario[0] = '\0';
    concatenar(nuevoUsuario, cedula);
    concatenar(nuevoUsuario, ",");
    concatenar(nuevoUsuario, clave);
    concatenar(nuevoUsuario, ",");
    concatenar(nuevoUsuario, nombre);
    concatenar(nuevoUsuario, ",");
    concatenar(nuevoUsuario, saldoStr);
    concatenar(nuevoUsuario, " COP");

    // Crear nuevo arreglo mas grande
    char** nuevosUsuarios = new char*[numUsuarios + 1];
    for (int i = 0; i < numUsuarios; i++) {
        nuevosUsuarios[i] = usuarios[i];
    }
    nuevosUsuarios[numUsuarios] = nuevoUsuario;

    delete[] usuarios;
    usuarios = nuevosUsuarios;
    numUsuarios++;

    cout << "\n Usuario agregado correctamente (en memoria).\n";
}

// ---- Menu usuario ----
void menuUsuario(char** usuarios, int numUsuarios) {
    char cedula[50], claveIngresada[50];

    cout << "\n=================================\n";
    cout << "        MENU USUARIO\n";
    cout << "=================================\n";
    cout << "Cedula: ";
    cin >> cedula;

    cout << "Clave: ";
    cin >> claveIngresada;

    bool encontrado = false;
    for (int i = 0; i < numUsuarios; i++) {
        char cedulaArchivo[100], claveArchivo[100];
        extraerCedulaYClave(usuarios[i], cedulaArchivo, sizeof(cedulaArchivo), claveArchivo, sizeof(claveArchivo));

        if (cadenasIguales(cedulaArchivo, cedula)) {
            if (cadenasIguales(claveArchivo, claveIngresada)) {
                encontrado = true;

                bool continuar = true;
                while (continuar) {
                    int opcion;
                    cout << "\n=================================\n";
                    cout << "   OPERACIONES DISPONIBLES\n";
                    cout << "=================================\n";
                    cout << "1. Consultar saldo (Costo: 1000 COP)\n";
                    cout << "2. Retirar dinero (Costo: 1000 COP + monto)\n";
                    cout << "3. Volver al menu principal\n";
                    cout << "=================================\n";
                    cout << "Opcion: ";
                    cin >> opcion;

                    switch (opcion) {
                    case 1:
                        consultarSaldoUsuario(usuarios, numUsuarios, cedula);
                        break;

                    case 2: {
                        int monto;
                        cout << "\nMonto a retirar: ";
                        cin >> monto;

                        if (monto <= 0) {
                            cout << "\n El monto debe ser mayor a cero.\n";
                        } else {
                            modificarDineroUsuario(usuarios, numUsuarios, cedula, monto);
                        }
                        break;
                    }

                    case 3:
                        cout << "\n Volviendo al menu principal...\n";
                        continuar = false;
                        break;

                    default:
                        cout << "\n Opcion invalida.\n";
                    }
                }
            } else {
                cout << "\n Clave incorrecta.\n";
            }
            break;
        }
    }

    if (!encontrado) {
        cout << "\n Cedula no encontrada en el sistema.\n";
    }
}

// ---- Menu principal ----
void menuPrincipal(char**& usuarios, int& numUsuarios, char** admins, int numAdmins) {
    int opcion;
    do {
        cout << "\n===================================\n";
        cout << "||       SISTEMA BANCARIO        ||\n";
        cout << "===================================\n";
        cout << "|| 1. Administrador              ||\n";
        cout << "|| 2. Usuario                    ||\n";
        cout << "|| 3. Salir                      ||\n";
        cout << "===================================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n Entrada invalida. Ingrese un numero.\n";
            continue;
        }

        switch (opcion) {
        case 1:
            menuAdministrador(usuarios, numUsuarios, admins, numAdmins);
            break;
        case 2:
            menuUsuario(usuarios, numUsuarios);
            break;
        case 3:
            cout << "\n Gracias por usar el sistema. Hasta pronto!\n";
            break;
        default:
            cout << "\n Opcion invalida. Seleccione 1, 2 o 3.\n";
        }
    } while (opcion != 3);
}
