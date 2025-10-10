#include <iostream>
#include "menu.h"
#include "UtilidadesCadena.h"
#include "OperacionesUsuario.h"
#include "Validaciones.h"  // Para validaciones de cédula, clave, saldo

using namespace std;

/**
 * @brief Maneja el flujo del menú de administrador con manejo básico de errores usando excepciones tipo C-string.
 */
void menuAdministrador(char**& usuarios, int& numUsuarios, char** admins, int numAdmins) {
    try {
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

        if (!valido) throw "Credenciales invalidas.";

        // Registro de nuevo usuario
        char cedula[50], clave[50], nombre[100], saldoStr[50];
        int saldoInicial = 0;

        cout << "\n=================================\n";
        cout << "    REGISTRAR NUEVO USUARIO\n";
        cout << "=================================\n";

        // ===== Validar CÉDULA =====
        do {
            cout << "Cedula del nuevo usuario: ";
            cin >> cedula;
            if (!validarCedula(cedula))
                cout << " Cedula invalida. Debe tener entre 6 y 10 digitos numericos y no empezar con 0.\n";
        } while (!validarCedula(cedula));

        // Verificar duplicado
        for (int i = 0; i < numUsuarios; i++) {
            char cedulaUsr[50], claveUsr[50];
            extraerCedulaYClave(usuarios[i], cedulaUsr, sizeof(cedulaUsr), claveUsr, sizeof(claveUsr));
            if (cadenasIguales(cedulaUsr, cedula)) throw "Ya existe un usuario con esa cedula.";
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
            if (!validarSaldo(saldoStr))
                cout << "Saldo invalido. Debe ser un numero entre 0 y 1,000,000.\n";
        } while (!validarSaldo(saldoStr));

        saldoInicial = atoi(saldoStr);

        // Crear línea "cedula,clave,nombre,saldo COP"
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

        // Expandir arreglo
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
    catch (const char* msg) {
        cerr << "\n[ERROR ADMINISTRADOR]: " << msg << "\n";
    }
}

/**
 * @brief Menú de usuario con manejo básico de errores mediante excepciones tipo C-string.
 */
void menuUsuario(char** usuarios, int numUsuarios) {
    try {
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
                if (!cadenasIguales(claveArchivo, claveIngresada))
                    throw "Clave incorrecta.";
                encontrado = true;

                bool continuar = true;
                while (continuar) {
                    int opcion;
                    cout << "\n=================================\n";
                    cout << "    OPERACIONES DISPONIBLES\n";
                    cout << "=================================\n";
                    cout << "1. Consultar saldo (Costo: 1000 COP)\n";
                    cout << "2. Retirar dinero (Costo: 1000 COP + monto)\n";
                    cout << "3. Volver al menu principal\n";
                    cout << "=================================\n";
                    cout << "Opcion: ";

                    if (!(cin >> opcion)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "\n Entrada invalida. Ingrese un numero.\n";
                        continue;
                    }

                    switch (opcion) {
                    case 1:
                        consultarSaldoUsuario(usuarios, numUsuarios, cedula);
                        break;
                    case 2: {
                        int monto;
                        cout << "\nMonto a retirar: ";
                        cin >> monto;
                        if (monto <= 0)
                            throw "El monto debe ser mayor a cero.";
                        modificarDineroUsuario(usuarios, numUsuarios, cedula, monto);
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
                break;
            }
        }
        if (!encontrado) throw "Cedula no encontrada en el sistema.";
    }
    catch (const char* msg) {
        cerr << "\n[ERROR USUARIO]: " << msg << "\n";
    }
}

/**
 * @brief Menú principal del sistema bancario, con manejo de errores básicos.
 */
void menuPrincipal(char**& usuarios, int& numUsuarios, char** admins, int numAdmins) {
    int opcion;
    do {
        try {
            cout << "\n===================================\n";
            cout << "||      SISTEMA BANCARIO         ||\n";
            cout << "===================================\n";
            cout << "|| 1. Administrador              ||\n";
            cout << "|| 2. Usuario                    ||\n";
            cout << "|| 3. Salir                      ||\n";
            cout << "===================================\n";
            cout << "Seleccione una opcion: ";

            if (!(cin >> opcion)) {
                cin.clear();
                cin.ignore(10000, '\n');
                throw "Entrada invalida. Debe ingresar un numero.";
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
                throw "Opcion invalida. Seleccione 1, 2 o 3.";
            }
        }
        catch (const char* msg) {
            cerr << "\n[ERROR MENU PRINCIPAL]: " << msg << "\n";
        }
    } while (opcion != 3);
}
