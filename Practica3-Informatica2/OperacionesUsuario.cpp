#include "UtilidadesCadena.h"
#include <iostream>
using namespace std;

// ==================================================
// FUNCIÓN AUXILIAR: Extraer cédula y clave de una línea
// ==================================================

/**
 * @brief Extrae los campos de cédula y clave de una línea de texto separada por comas.
 *
 * La línea debe tener el formato:
 * ```
 * cedula,clave
 * ```
 *
 * @param linea Cadena original que contiene los datos.
 * @param cedula Buffer donde se almacenará la cédula extraída.
 * @param maxCedula Tamaño máximo del buffer `cedula`.
 * @param clave Buffer donde se almacenará la clave extraída.
 * @param maxClave Tamaño máximo del buffer `clave`.
 */
void extraerCedulaYClave(const char* linea, char* cedula, int maxCedula, char* clave, int maxClave) {
    int i = 0, j = 0;

    // Extraer cédula hasta la coma o fin de línea
    while (linea[i] != '\0' && linea[i] != ',' && linea[i] != '\r' && linea[i] != '\n' && j < maxCedula - 1)
        cedula[j++] = linea[i++];
    cedula[j] = '\0';

    if (linea[i] == ',') i++;

    // Saltar espacios o tabulaciones
    while (linea[i] != '\0' && (linea[i] == ' ' || linea[i] == '\t')) i++;

    // Extraer clave
    j = 0;
    while (linea[i] != '\0' && linea[i] != ',' && linea[i] != '\r' && linea[i] != '\n' && j < maxClave - 1)
        clave[j++] = linea[i++];
    clave[j] = '\0';
}

// ==================================================
// CONSULTAR SALDO DE USUARIO
// ==================================================

/**
 * @brief Busca una cédula en la lista de usuarios y muestra su saldo.
 *
 * Si el usuario existe, cobra un costo fijo de consulta de 1000 COP y
 * actualiza el saldo en memoria. Si no existe, muestra un mensaje de error.
 *
 * @param lineas Arreglo de líneas con los datos de los usuarios.
 * @param numUsuarios Número total de usuarios en el arreglo.
 * @param cedulaBuscada Cédula del usuario a consultar.
 * @return `true` si se encontró y actualizó el saldo correctamente.
 * @return `false` si ocurrió un error o la cédula no existe.
 *
 * @throw const char* Si hay errores de punteros nulos o de separación de campos.
 */
bool consultarSaldoUsuario(char** lineas, int numUsuarios, const char* cedulaBuscada) {
    const int COSTO_CONSULTA = 1000;

    try {
        if (!lineas || numUsuarios <= 0 || !cedulaBuscada)
            throw "Datos de entrada inválidos en consultarSaldoUsuario.";

        for (int i = 0; i < numUsuarios; i++) {
            // Comparar cédula hasta la coma
            int j = 0;
            while (cedulaBuscada[j] != '\0' && lineas[i][j] == cedulaBuscada[j]) j++;
            if (cedulaBuscada[j] != '\0' || lineas[i][j] != ',') continue;

            // Separar los campos de la línea
            char* cedula; char* clave; char* nombre; char* dinero;
            separarLinea(lineas[i], cedula, clave, nombre, dinero);

            if (!dinero) throw "El campo dinero no se pudo separar correctamente.";

            // Convertir dinero a entero
            int saldo = 0;
            int k = 0;
            while (dinero[k] >= '0' && dinero[k] <= '9') {
                saldo = saldo * 10 + (dinero[k] - '0');
                k++;
            }

            // Mostrar información
            cout << "\n=================================\n";
            cout << "  CONSULTA DE SALDO\n";
            cout << "=================================\n";
            cout << "Usuario: " << nombre << endl;
            cout << "Cédula: " << cedula << endl;
            cout << "Saldo actual: " << saldo << " COP" << endl;
            cout << "Costo de consulta: " << COSTO_CONSULTA << " COP" << endl;

            if (saldo < COSTO_CONSULTA) {
                cout << "\nAdvertencia: Fondos insuficientes para cobrar la consulta.\n";
            } else {
                saldo -= COSTO_CONSULTA;
            }

            cout << "Saldo después de consulta: " << saldo << " COP\n";
            cout << "=================================\n\n";

            // Actualizar línea con nuevo saldo
            delete[] lineas[i];
            char nuevoDinero[50];
            int idx = 0, temp = saldo;
            char rev[20];
            int rpos = 0;
            if (temp == 0) rev[rpos++] = '0';
            while (temp > 0) rev[rpos++] = (temp % 10) + '0', temp /= 10;
            for (int t = rpos - 1; t >= 0; t--) nuevoDinero[idx++] = rev[t];
            nuevoDinero[idx++] = ' '; nuevoDinero[idx++] = 'C'; nuevoDinero[idx++] = 'O'; nuevoDinero[idx++] = 'P';
            nuevoDinero[idx] = '\0';

            int newLen = longitud(cedula) + longitud(clave) + longitud(nombre) + longitud(nuevoDinero) + 4;
            lineas[i] = new char[newLen];
            lineas[i][0] = '\0';
            concatenar(lineas[i], cedula);
            concatenar(lineas[i], ",");
            concatenar(lineas[i], clave);
            concatenar(lineas[i], ",");
            concatenar(lineas[i], nombre);
            concatenar(lineas[i], ",");
            concatenar(lineas[i], nuevoDinero);

            delete[] cedula; delete[] clave; delete[] nombre; delete[] dinero;
            return true;
        }

        cout << "Cédula incorrecta: no existe en el sistema.\n";
        return false;
    }
    catch (const char* mensaje) {
        cerr << "Error en consultarSaldoUsuario: " << mensaje << endl;
        return false;
    }
}

// ==================================================
// RETIRO DE DINERO
// ==================================================

/**
 * @brief Resta un monto del saldo del usuario, incluyendo el costo del retiro.
 *
 * Si el usuario no tiene fondos suficientes o no se encuentra, no se modifica el saldo.
 *
 * @param lineas Arreglo de líneas con datos de usuarios.
 * @param numUsuarios Número total de usuarios.
 * @param cedulaBuscada Cédula del usuario.
 * @param montoRetiro Monto solicitado para retirar.
 * @return `true` si el retiro se realizó exitosamente.
 * @return `false` si hubo un error o fondos insuficientes.
 *
 * @throw const char* Si hay datos de entrada inválidos o falla la separación de campos.
 */
bool modificarDineroUsuario(char** lineas, int numUsuarios, const char* cedulaBuscada, int montoRetiro) {
    const int COSTO_RETIRO = 1000;
    int montoTotal = montoRetiro + COSTO_RETIRO;

    try {
        if (!lineas || numUsuarios <= 0 || !cedulaBuscada)
            throw "Datos de entrada inválidos en modificarDineroUsuario.";

        for (int i = 0; i < numUsuarios; i++) {
            int j = 0;
            while (cedulaBuscada[j] != '\0' && lineas[i][j] == cedulaBuscada[j]) j++;
            if (cedulaBuscada[j] != '\0' || lineas[i][j] != ',') continue;

            char* cedula; char* clave; char* nombre; char* dinero;
            separarLinea(lineas[i], cedula, clave, nombre, dinero);
            if (!dinero) throw "El campo dinero no se pudo separar correctamente.";

            int saldo = 0;
            int k = 0;
            while (dinero[k] >= '0' && dinero[k] <= '9') {
                saldo = saldo * 10 + (dinero[k] - '0');
                k++;
            }

            cout << "\n=================================\n";
            cout << "  RETIRO DE DINERO\n";
            cout << "=================================\n";
            cout << "Usuario: " << nombre << endl;
            cout << "Saldo actual: " << saldo << " COP" << endl;
            cout << "Monto a retirar: " << montoRetiro << " COP" << endl;
            cout << "Costo de transacción: " << COSTO_RETIRO << " COP" << endl;
            cout << "Total a descontar: " << montoTotal << " COP" << endl;

            if (saldo < montoTotal) {
                cout << "\nTransacción rechazada.\n";
                cout << "Fondos insuficientes para realizar el retiro.\n";
                cout << "=================================\n\n";
                delete[] cedula; delete[] clave; delete[] nombre; delete[] dinero;
                return false;
            }

            saldo -= montoTotal;
            cout << "Nuevo saldo: " << saldo << " COP\n";
            cout << "Transacción exitosa.\n";
            cout << "=================================\n\n";

            // Actualizar saldo
            delete[] lineas[i];
            char nuevoDinero[50];
            int idx = 0, temp = saldo;
            char rev[20];
            int rpos = 0;
            if (temp == 0) rev[rpos++] = '0';
            while (temp > 0) rev[rpos++] = (temp % 10) + '0', temp /= 10;
            for (int t = rpos - 1; t >= 0; t--) nuevoDinero[idx++] = rev[t];
            nuevoDinero[idx++] = ' '; nuevoDinero[idx++] = 'C'; nuevoDinero[idx++] = 'O'; nuevoDinero[idx++] = 'P';
            nuevoDinero[idx] = '\0';

            int newLen = longitud(cedula) + longitud(clave) + longitud(nombre) + longitud(nuevoDinero) + 4;
            lineas[i] = new char[newLen];
            lineas[i][0] = '\0';
            concatenar(lineas[i], cedula);
            concatenar(lineas[i], ",");
            concatenar(lineas[i], clave);
            concatenar(lineas[i], ",");
            concatenar(lineas[i], nombre);
            concatenar(lineas[i], ",");
            concatenar(lineas[i], nuevoDinero);

            delete[] cedula; delete[] clave; delete[] nombre; delete[] dinero;
            return true;
        }

        cout << "Cédula incorrecta: no existe en el sistema.\n";
        return false;
    }
    catch (const char* mensaje) {
        cerr << "Error en modificarDineroUsuario: " << mensaje << endl;
        return false;
    }
}
