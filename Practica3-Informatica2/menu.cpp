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
    while (linea[i] != '\0' && linea[i] != ',' && linea[i] != '\r' && linea[i] != '\n' && j < maxClave - 1)
        clave[j++] = linea[i++];
    clave[j] = '\0';

    // Limpiar espacios al inicio y final
    trim(cedula);
    trim(clave);
}

// ---- Menú administrador ----
void menuAdministrador(char**& usuarios, int& numUsuarios, char** admins, int numAdmins) {
    char cedulaAdmin[50], claveIngresada[50];
    cout << "\n=================================\n";
    cout << "    ACCESO ADMINISTRADOR\n";
    cout << "=================================\n";
    cout << "Cédula de administrador: ";
    cin >> cedulaAdmin;
    trim(cedulaAdmin);

    bool valido = false;
    for (int i = 0; i < numAdmins; i++) {
        char cedulaArchivo[50], claveArchivo[50];
        extraerCedulaYClave(admins[i], cedulaArchivo, sizeof(cedulaArchivo), claveArchivo, sizeof(claveArchivo));

        if (cadenasIguales(cedulaArchivo, cedulaAdmin)) {
            cout << "Contraseña: ";
            cin >> claveIngresada;
            trim(claveIngresada);

            if (cadenasIguales(claveArchivo, claveIngresada)) {
                valido = true;
            }
            break;
        }
    }

    if (!valido) {
        cout << "\n Credenciales inválidas.\n";
        return;
    }

    // Registro de usuario
    char cedula[50], clave[50], nombre[100];
    int saldoInicial;

    cout << "\n=================================\n";
    cout << "   REGISTRAR NUEVO USUARIO\n";
    cout << "=================================\n";
    cout << "Cédula del nuevo usuario: ";
    cin >> cedula;
    trim(cedula);

    // Validar que no exista
    for (int i = 0; i < numUsuarios; i++) {
        char cedulaUsr[50], claveUsr[50];
        extraerCedulaYClave(usuarios[i], cedulaUsr, sizeof(cedulaUsr), claveUsr, sizeof(claveUsr));
        if (cadenasIguales(cedulaUsr, cedula)) {
            cout << "\n Ya existe un usuario con esa cédula.\n";
            return;
        }
    }

    cout << "Clave: ";
    cin >> clave;
    trim(clave);

    cout << "Nombre completo: ";
    cin.ignore();
    cin.getline(nombre, 100);

    cout << "Saldo inicial: ";
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

    // Crear nuevo arreglo más grande
    char** nuevosUsuarios = new char*[numUsuarios + 1];
    for (int i = 0; i < numUsuarios; i++) {
        nuevosUsuarios[i] = usuarios[i];
    }
    nuevosUsuarios[numUsuarios] = nuevoUsuario;

    delete[] usuarios;
    usuarios = nuevosUsuarios;
    numUsuarios++;

    // Guardar cambios en archivo
    guardarUsuariosEnArchivo(usuarios, numUsuarios, "../../Datos/usuarios.txt");
    cout << "\nUsuario agregado correctamente.\n";
}

// ---- Menú cliente ----
void menuUsuario(char** usuarios, int numUsuarios) {
    char cedula[50], claveIngresada[50];

    cout << "\n=================================\n";
    cout << "        MENÚ USUARIO\n";
    cout << "=================================\n";
    cout << "Cédula: ";
    cin >> cedula;
    trim(cedula);

    cout << "Clave: ";
    cin >> claveIngresada;
    trim(claveIngresada);

    // Buscar y validar usuario
    bool encontrado = false;
    for (int i = 0; i < numUsuarios; i++) {
        char cedulaArchivo[100], claveArchivo[100];
        extraerCedulaYClave(usuarios[i], cedulaArchivo, sizeof(cedulaArchivo), claveArchivo, sizeof(claveArchivo));

        if (cadenasIguales(cedulaArchivo, cedula)) {
            if (cadenasIguales(claveArchivo, claveIngresada)) {
                encontrado = true;

                // Mostrar submenú de operaciones
                bool continuar = true;
                while (continuar) {
                    int opcion;
                    cout << "\n=================================\n";
                    cout << "   OPERACIONES DISPONIBLES\n";
                    cout << "=================================\n";
                    cout << "1. Consultar saldo (Costo: 1000 COP)\n";
                    cout << "2. Retirar dinero (Costo: 1000 COP + monto)\n";
                    cout << "3. Volver al menú principal\n";
                    cout << "=================================\n";
                    cout << "Opción: ";
                    cin >> opcion;

                    switch (opcion) {
                    case 1:
                        // Consultar saldo
                        if (consultarSaldoUsuario(usuarios, numUsuarios, cedula)) {
                            guardarUsuariosEnArchivo(usuarios, numUsuarios, "../../Datos/usuarios.txt");
                        }
                        break;

                    case 2:
                        // Retirar dinero
                        {
                            int monto;
                            cout << "\nMonto a retirar: ";
                            cin >> monto;

                            if (monto <= 0) {
                                cout << "\n El monto debe ser mayor a cero.\n";
                            } else {
                                if (modificarDineroUsuario(usuarios, numUsuarios, cedula, monto)) {
                                    guardarUsuariosEnArchivo(usuarios, numUsuarios, "../../Datos/usuarios.txt");
                                }
                            }
                        }
                        break;

                    case 3:
                        cout << "\n👋 Volviendo al menú principal...\n";
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

// ---- Menú principal ----
void menuPrincipal(char**& usuarios, int& numUsuarios, char** admins, int numAdmins) {
    int opcion;
    do {
        cout << "\n#################################\n";
        cout << "#       SISTEMA BANCARIO        #\n";
        cout << "#################################\n";
        cout << "# 1. Administrador              #\n";
        cout << "# 2. Usuario                    #\n";
        cout << "# 3. Salir                      #\n";
        cout << "#################################\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        // Limpiar buffer de entrada en caso de entrada inválida
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n Entrada inválida. Ingrese un número.\n";
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
            cout << "\n👋 Gracias por usar el sistema. ¡Hasta pronto!\n";
            break;
        default:
            cout << "\n Opción inválida. Seleccione 1, 2 o 3.\n";
        }
    } while (opcion != 3);
}
