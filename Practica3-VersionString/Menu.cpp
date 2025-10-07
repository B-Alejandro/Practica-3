#include <iostream>
#include <stdexcept>
#include <cstdlib>  // stoi
#include "OperacionesUsuario.h"
#include "Validaciones.h"

using namespace std;

// ==========================================================
// Función auxiliar para extraer cédula y clave desde una línea
// ==========================================================
static void extraerCedulaYClave(const string& linea, string& cedula, string& clave) {
    size_t pos = linea.find(',');
    if (pos == string::npos) {
        cedula = "";
        clave = "";
        return;
    }
    cedula = linea.substr(0, pos);
    clave = linea.substr(pos + 1);
}

// ==========================================================
// MENÚ ADMINISTRADOR
// ==========================================================
void menuAdministrador(string*& usuarios, int& numUsuarios, string* admins, int numAdmins) {
    string cedulaAdmin, claveIngresada;
    cout << "\n=================================\n";
    cout << "    ACCESO ADMINISTRADOR\n";
    cout << "=================================\n";
    cout << "Cédula de administrador: ";
    cin >> cedulaAdmin;

    bool valido = false;

    for (int i = 0; i < numAdmins; i++) {
        string cedulaArchivo, claveArchivo;
        extraerCedulaYClave(admins[i], cedulaArchivo, claveArchivo);

        if (cedulaArchivo == cedulaAdmin) {
            cout << "Contraseña: ";
            cin >> claveIngresada;

            if (claveArchivo == claveIngresada)
                valido = true;
            break;
        }
    }

    if (!valido) {
        cout << "\n Credenciales inválidas.\n";
        return;
    }

    // REGISTRO DE NUEVO USUARIO
    string cedula, clave, nombre, saldoStr;
    int saldoInicial = 0;

    cout << "\n=================================\n";
    cout << "    REGISTRAR NUEVO USUARIO\n";
    cout << "=================================\n";

    // ===== Validar CÉDULA =====
    do {
        cout << "Cédula del nuevo usuario: ";
        cin >> cedula;
        if (!validarCedula(cedula.c_str())) {
            cout << " Cédula inválida. Debe tener entre 6 y 10 dígitos numéricos y no empezar con 0.\n";
        }
    } while (!validarCedula(cedula.c_str()));

    // Verificar que no exista ya esa cédula
    for (int i = 0; i < numUsuarios; i++) {
        string cedulaUsr, claveUsr;
        extraerCedulaYClave(usuarios[i], cedulaUsr, claveUsr);
        if (cedulaUsr == cedula) {
            cout << "\n Ya existe un usuario con esa cédula.\n";
            return;
        }
    }

    // ===== Validar CONTRASEÑA =====
    do {
        cout << "Clave: ";
        cin >> clave;
        if (!validarContrasena(clave.c_str())) {
            cout << " Contraseña inválida.\n"
                    "Debe tener entre 8 y 20 caracteres, incluir al menos:\n"
                    " - una mayúscula\n - un número\n - un carácter especial\n"
                    "y no contener espacios.\n";
        }
    } while (!validarContrasena(clave.c_str()));

    // ===== Nombre =====
    cout << "Nombre completo: ";
    cin.ignore();
    getline(cin, nombre);

    // ===== Validar SALDO =====
    do {
        cout << "Saldo inicial (0 - 1,000,000): ";
        cin >> saldoStr;
        if (!validarSaldo(saldoStr.c_str())) {
            cout << "Saldo inválido. Debe ser un número entre 0 y 1,000,000.\n";
        }
    } while (!validarSaldo(saldoStr.c_str()));

    saldoInicial = stoi(saldoStr);

    // Crear registro de usuario
    string nuevoUsuario = cedula + "," + clave + "," + nombre + "," + saldoStr + " COP";

    // Expandir arreglo dinámico
    string* nuevosUsuarios = new string[numUsuarios + 1];
    for (int i = 0; i < numUsuarios; i++) {
        nuevosUsuarios[i] = usuarios[i];
    }
    nuevosUsuarios[numUsuarios] = nuevoUsuario;

    delete[] usuarios;
    usuarios = nuevosUsuarios;
    numUsuarios++;

    cout << "\n Usuario agregado correctamente (en memoria).\n";
}

// ==========================================================
// MENÚ USUARIO
// ==========================================================
void menuUsuario(string* usuarios, int numUsuarios) {
    string cedula, claveIngresada;

    cout << "\n=================================\n";
    cout << "        MENÚ USUARIO\n";
    cout << "=================================\n";
    cout << "Cédula: ";
    cin >> cedula;
    cout << "Clave: ";
    cin >> claveIngresada;

    bool encontrado = false;

    for (int i = 0; i < numUsuarios; i++) {
        string cedulaArchivo, claveArchivo;
        extraerCedulaYClave(usuarios[i], cedulaArchivo, claveArchivo);

        if (cedulaArchivo == cedula) {
            if (claveArchivo == claveIngresada) {
                encontrado = true;
                bool continuar = true;

                while (continuar) {
                    int opcion;
                    cout << "\n=================================\n";
                    cout << "    OPERACIONES DISPONIBLES\n";
                    cout << "=================================\n";
                    cout << "1. Consultar saldo (Costo: 1000 COP)\n";
                    cout << "2. Retirar dinero (Costo: 1000 COP + monto)\n";
                    cout << "3. Volver al menú principal\n";
                    cout << "=================================\n";
                    cout << "Opción: ";

                    if (!(cin >> opcion)) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "\nEntrada inválida.\n";
                        continue;
                    }

                    switch (opcion) {
                    case 1:
                        consultarSaldoUsuario(usuarios[i], cedula);
                        break;

                    case 2: {
                        int monto;
                        cout << "\nMonto a retirar: ";
                        cin >> monto;

                        if (monto <= 0) {
                            cout << "\n El monto debe ser mayor a cero.\n";
                        } else {
                            modificarDineroUsuario(usuarios[i], cedula, monto);
                        }
                        break;
                    }

                    case 3:
                        cout << "\n Volviendo al menú principal...\n";
                        continuar = false;
                        break;

                    default:
                        cout << "\n Opción inválida.\n";
                    }
                }
            } else {
                cout << "\n Clave incorrecta.\n";
            }
            break;
        }
    }

    if (!encontrado) {
        cout << "\n Cédula no encontrada en el sistema.\n";
    }
}

// ==========================================================
// MENÚ PRINCIPAL
// ==========================================================
void menuPrincipal(string*& usuarios, int& numUsuarios, string* admins, int numAdmins) {
    int opcion;
    do {
        cout << "\n===================================\n";
        cout << "||      SISTEMA BANCARIO         ||\n";
        cout << "===================================\n";
        cout << "|| 1. Administrador              ||\n";
        cout << "|| 2. Usuario                    ||\n";
        cout << "|| 3. Salir                      ||\n";
        cout << "===================================\n";
        cout << "Seleccione una opción: ";

        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nEntrada inválida. Ingrese un número.\n";
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
            cout << "\n Opción inválida. Seleccione 1, 2 o 3.\n";
        }
    } while (opcion != 3);
}
