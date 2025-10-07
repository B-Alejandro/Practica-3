#include <iostream>
#include <sstream>
#include <stdexcept>
#include "OperacionesUsuario.h"

using namespace std;

// ===========================================================
// Función auxiliar: separa los campos de una línea CSV simple
// ===========================================================
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
// CONSULTAR SALDO
// ===========================================================
bool consultarSaldoUsuario(string& linea, const string& cedulaBuscada) {
    string cedula, clave, nombre, saldoStr;

    if (!descomponerLineaUsuario(linea, cedula, clave, nombre, saldoStr))
        return false;

    if (cedula != cedulaBuscada)
        return false;

    // Extraer el número del saldo (antes de " COP")
    int saldoNum = 0;
    {
        stringstream ss(saldoStr);
        ss >> saldoNum;
    }

    cout << "\n---------------------------------\n";
    cout << "Usuario: " << nombre << endl;
    cout << "Saldo actual: " << saldoNum << " COP\n";
    cout << "Costo de la consulta: 1000 COP\n";

    saldoNum -= 1000;
    if (saldoNum < 0) saldoNum = 0;

    cout << "Saldo después del cobro: " << saldoNum << " COP\n";
    cout << "---------------------------------\n";

    // Actualizar la línea con el nuevo saldo
    string nuevoSaldo = to_string(saldoNum) + " COP";
    linea = cedula + "," + clave + "," + nombre + "," + nuevoSaldo;

    return true;
}

// ===========================================================
// RETIRAR DINERO
// ===========================================================
bool modificarDineroUsuario(string& linea, const string& cedulaBuscada, int montoRetiro) {
    string cedula, clave, nombre, saldoStr;

    if (!descomponerLineaUsuario(linea, cedula, clave, nombre, saldoStr))
        return false;

    if (cedula != cedulaBuscada)
        return false;

    int saldoNum = 0;
    {
        stringstream ss(saldoStr);
        ss >> saldoNum;
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

    // Actualizar línea
    string nuevoSaldo = to_string(saldoNum) + " COP";
    linea = cedula + "," + clave + "," + nombre + "," + nuevoSaldo;

    return true;
}
