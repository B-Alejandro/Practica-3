#include <iostream>
#include <cstdlib>  // stoi
#include "OperacionesUsuario.h"
#include "Validaciones.h"

using namespace std;

// ==========================================================
// FUNCIÓN AUXILIAR
// ==========================================================

/**
 * @brief Extrae la cédula y la clave de una línea con formato CSV.
 *
 * Esta función recibe una cadena con formato `"cedula,clave,..."`
 * y separa los valores de cédula y clave, eliminando espacios
 * en blanco al inicio y al final. Valida que la línea contenga al menos
 * una coma y que ambos campos no estén vacíos.
 *
 * @param linea Línea de texto que contiene la cédula y la clave.
 * @param cedula Referencia donde se almacenará la cédula extraída.
 * @param clave Referencia donde se almacenará la clave extraída.
 * @throw const char* Si el formato de la línea es inválido o los campos están vacíos.
 */
void extraerCedulaYClave(const string& linea, string& cedula, string& clave) {
    string limpia = linea;
    size_t inicio = 0;
    while (inicio < limpia.size() && isspace(limpia[inicio]))
        inicio++;
    size_t fin = limpia.size();
    while (fin > inicio && isspace(limpia[fin - 1]))
        fin--;
    limpia = limpia.substr(inicio, fin - inicio);

    size_t pos1 = limpia.find(',');
    if (pos1 == string::npos)
        throw "Formato de línea inválido: falta la coma entre cédula y clave.";

    size_t pos2 = limpia.find(',', pos1 + 1);
    if (pos2 == string::npos)
        pos2 = limpia.size();

    string parteCedula = limpia.substr(0, pos1);
    string parteClave  = limpia.substr(pos1 + 1, pos2 - pos1 - 1);

    // Limpiar espacios
    inicio = 0;
    while (inicio < parteCedula.size() && isspace(parteCedula[inicio]))
        inicio++;
    fin = parteCedula.size();
    while (fin > inicio && isspace(parteCedula[fin - 1]))
        fin--;
    parteCedula = parteCedula.substr(inicio, fin - inicio);

    inicio = 0;
    while (inicio < parteClave.size() && isspace(parteClave[inicio]))
        inicio++;
    fin = parteClave.size();
    while (fin > inicio && isspace(parteClave[fin - 1]))
        fin--;
    parteClave = parteClave.substr(inicio, fin - inicio);

    if (parteCedula.empty() || parteClave.empty())
        throw "Línea incompleta: cédula o clave vacía.";

    cedula = parteCedula;
    clave  = parteClave;
}

// ==========================================================
// MENÚ ADMINISTRADOR
// ==========================================================

/**
 * @brief Muestra el menú de administrador y permite registrar nuevos usuarios.
 *
 * El administrador debe autenticarse con su cédula y contraseña antes de
 * poder registrar nuevos usuarios. Se validan la cédula, la contraseña,
 * el nombre y el saldo inicial del nuevo usuario.
 *
 * @param usuarios Referencia al arreglo dinámico de usuarios (se actualiza si se añade uno nuevo).
 * @param numUsuarios Referencia al número actual de usuarios.
 * @param admins Arreglo de cadenas con las credenciales de los administradores.
 * @param numAdmins Número total de administradores registrados.
 */
void menuAdministrador(string*& usuarios, int& numUsuarios, string* admins, int numAdmins) {
    try {
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

        if (!valido)
            throw "Credenciales inválidas.";

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

        for (int i = 0; i < numUsuarios; i++) {
            string cedulaUsr, claveUsr;
            extraerCedulaYClave(usuarios[i], cedulaUsr, claveUsr);
            if (cedulaUsr == cedula)
                throw "Ya existe un usuario con esa cédula.";
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
        if (saldoInicial < 0 || saldoInicial > 1000000)
            throw "Saldo fuera del rango permitido.";

        string nuevoUsuario = cedula + "," + clave + "," + nombre + "," + saldoStr + " COP";

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
    catch (const char* e) {
        cout << "\n[Error] " << e << "\n";
    }
}

// ==========================================================
// MENÚ USUARIO
// ==========================================================

/**
 * @brief Muestra el menú de usuario y permite realizar operaciones básicas.
 *
 * Un usuario puede consultar su saldo (con costo de 1000 COP)
 * o retirar dinero (con costo adicional del monto retirado).
 *
 * @param usuarios Arreglo de usuarios.
 * @param numUsuarios Número de usuarios registrados.
 */
void menuUsuario(string* usuarios, int numUsuarios) {
    try {
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
                            throw "Entrada inválida. Debe ingresar un número.";
                        }

                        switch (opcion) {
                        case 1:
                            consultarSaldoUsuario(usuarios[i], cedula);
                            break;

                        case 2: {
                            int monto;
                            cout << "\nMonto a retirar: ";
                            cin >> monto;

                            if (monto <= 0)
                                throw "El monto debe ser mayor a cero.";
                            else
                                modificarDineroUsuario(usuarios[i], cedula, monto);
                            break;
                        }

                        case 3:
                            cout << "\n Volviendo al menú principal...\n";
                            continuar = false;
                            break;

                        default:
                            throw "Opción inválida. Debe ser 1, 2 o 3.";
                        }
                    }
                } else {
                    throw "Clave incorrecta.";
                }
                break;
            }
        }

        if (!encontrado)
            throw "Cédula no encontrada en el sistema.";
    }
    catch (const char* e) {
        cout << "\n[Error] " << e << "\n";
    }
}

// ==========================================================
// MENÚ PRINCIPAL
// ==========================================================

/**
 * @brief Muestra el menú principal del sistema bancario.
 *
 * Permite elegir entre las opciones de acceso de administrador,
 * usuario o salir del sistema.
 *
 * @param usuarios Referencia al arreglo dinámico de usuarios.
 * @param numUsuarios Referencia al número de usuarios registrados.
 * @param admins Arreglo con los administradores.
 * @param numAdmins Cantidad de administradores.
 */
void menuPrincipal(string*& usuarios, int& numUsuarios, string* admins, int numAdmins) {
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
            cout << "Seleccione una opción: ";

            if (!(cin >> opcion)) {
                cin.clear();
                cin.ignore(10000, '\n');
                throw "Entrada inválida. Ingrese un número.";
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
                throw "Opción inválida. Seleccione 1, 2 o 3.";
            }
        }
        catch (const char* e) {
            cout << "\n[Error] " << e << "\n";
        }
    } while (opcion != 3);
}
