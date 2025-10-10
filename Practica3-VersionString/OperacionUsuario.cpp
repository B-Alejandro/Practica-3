#include <iostream>
#include <sstream>
#include "OperacionesUsuario.h"

using namespace std;

// ===========================================================
// === Función auxiliar: separa los campos de una línea CSV ===
// ===========================================================
/**
 * @brief Separa una línea de texto CSV en sus campos: cédula, clave, nombre y saldo.
 *
 * @param linea Línea con formato "cedula,clave,nombre,saldo COP".
 * @param cedula Variable de salida para la cédula.
 * @param clave Variable de salida para la clave.
 * @param nombre Variable de salida para el nombre.
 * @param saldoStr Variable de salida para el saldo en formato texto.
 * @return true si la línea se pudo descomponer correctamente, false si el formato es inválido.
 */
static bool descomponerLineaUsuario(
    const string& linea,
    string& cedula,
    string& clave,
    string& nombre,
    string& saldoStr)
{
    size_t p1 = linea.find(',');
    size_t p2 = linea.find(',', p1 + 1);
    size_t p3 = linea.find(',', p2 + 1);

    if (p1 == string::npos || p2 == string::npos || p3 == string::npos)
        return false;

    cedula = linea.substr(0, p1);
    clave = linea.substr(p1 + 1, p2 - p1 - 1);
    nombre = linea.substr(p2 + 1, p3 - p2 - 1);
    saldoStr = linea.substr(p3 + 1);

    return true;
}

// ===========================================================
// === CONSULTAR SALDO =======================================
// ===========================================================
/**
 * @brief Muestra el saldo de un usuario, cobra 1000 COP por la consulta y actualiza el registro.
 *
 * @param linea Línea de texto con la información del usuario.
 * @param cedulaBuscada Cédula del usuario que realiza la consulta.
 * @return true si se encontró y actualizó el usuario, false en caso contrario.
 */
bool consultarSaldoUsuario(string& linea, const string& cedulaBuscada) {
    try {
        string cedula, clave, nombre, saldoStr;

        if (!descomponerLineaUsuario(linea, cedula, clave, nombre, saldoStr))
            throw "Formato de registro inválido.";

        if (cedula != cedulaBuscada)
            return false;

        int saldoNum = 0;
        stringstream ss(saldoStr);
        ss >> saldoNum;

        cout << "\n---------------------------------\n";
        cout << "Usuario: " << nombre << endl;
        cout << "Saldo actual: " << saldoNum << " COP\n";
        cout << "Costo de la consulta: 1000 COP\n";

        saldoNum = max(0, saldoNum - 1000);

        cout << "Saldo después del cobro: " << saldoNum << " COP\n";
        cout << "---------------------------------\n";

        linea = cedula + "," + clave + "," + nombre + "," + to_string(saldoNum) + " COP";
        return true;
    }
    catch (const char* msg) {
        cerr << "Error en consultarSaldoUsuario(): " << msg << endl;
        return false;
    }
}

// ===========================================================
// === RETIRAR DINERO ========================================
// ===========================================================
/**
 * @brief Retira dinero del saldo de un usuario, cobrando 1000 COP por operación.
 *        Valida que el monto ingresado sea un número entero positivo.
 *
 * @param linea Línea de texto con la información del usuario.
 * @param cedulaBuscada Cédula del usuario que realiza el retiro.
 * @param montoRetiro Monto solicitado a retirar (ingresado por el usuario).
 * @return true si el retiro fue exitoso, false si hubo error o saldo insuficiente.
 * @throws const char* Si el formato del registro o el monto son inválidos.
 */
bool modificarDineroUsuario(string& linea, const string& cedulaBuscada, int montoRetiro) {
    try {
        string cedula, clave, nombre, saldoStr;

        if (!descomponerLineaUsuario(linea, cedula, clave, nombre, saldoStr))
            throw "Formato de registro inválido.";

        if (cedula != cedulaBuscada)
            return false;

        int saldoNum = 0;
        stringstream ss(saldoStr);
        ss >> saldoNum;

        // === Validar que el monto sea un número positivo ===
        if (cin.fail() || montoRetiro <= 0) {
            cin.clear();
            while (cin.get() != '\n' && !cin.eof());
            throw "El monto a retirar debe ser un número positivo.";
        }

        int costoOperacion = 1000;
        int total = montoRetiro + costoOperacion;

        if (saldoNum < total) {
            cout << "\n---------------------------------\n";
            cout << "Saldo insuficiente para retirar " << montoRetiro << " COP.\n";
            cout << "Saldo disponible: " << saldoNum << " COP\n";
            cout << "Costo total (retiro + operación): " << total << " COP\n";
            cout << "---------------------------------\n";
            return false;
        }

        saldoNum -= total;

        cout << "\n---------------------------------\n";
        cout << "Retiro exitoso.\n";
        cout << "Monto retirado: " << montoRetiro << " COP\n";
        cout << "Costo de operación: " << costoOperacion << " COP\n";
        cout << "Saldo restante: " << saldoNum << " COP\n";
        cout << "---------------------------------\n";

        linea = cedula + "," + clave + "," + nombre + "," + to_string(saldoNum) + " COP";
        return true;
    }
    catch (const char* msg) {
        cerr << "Error en modificarDineroUsuario(): " << msg << endl;
        return false;
    }
}
