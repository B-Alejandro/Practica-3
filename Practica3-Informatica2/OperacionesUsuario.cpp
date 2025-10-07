#include "operacionesUsuario.h"
#include "utilidadesCadena.h"
#include <iostream>
using namespace std;

bool consultarSaldoUsuario(char** lineas, int numUsuarios, const char* cedulaBuscada) {
    const int COSTO_CONSULTA = 1000;

    for (int i = 0; i < numUsuarios; i++) {
        int j = 0;
        while (cedulaBuscada[j] != '\0' && lineas[i][j] == cedulaBuscada[j]) j++;
        if (cedulaBuscada[j] != '\0' || lineas[i][j] != ',') continue;

        char* cedula; char* clave; char* nombre; char* dinero;
        separarLinea(lineas[i], cedula, clave, nombre, dinero);

        int saldo = 0;
        int k = 0;
        while (dinero[k] >= '0' && dinero[k] <= '9') {
            saldo = saldo * 10 + (dinero[k] - '0');
            k++;
        }

        cout << "\n=================================\n";
        cout << "  CONSULTA DE SALDO\n";
        cout << "=================================\n";
        cout << "Usuario: " << nombre << endl;
        cout << "Cédula: " << cedula << endl;
        cout << "Saldo actual: " << saldo << " COP" << endl;
        cout << "Costo de consulta: " << COSTO_CONSULTA << " COP" << endl;

        if (saldo < COSTO_CONSULTA) {
            cout << "\n⚠️  ADVERTENCIA: Fondos insuficientes para cobrar la consulta.\n";
            saldo = 0;
        } else {
            saldo -= COSTO_CONSULTA;
        }

        cout << "Saldo después de consulta: " << saldo << " COP\n";
        cout << "=================================\n\n";

        // Actualizar línea
        delete[] lineas[i];
        char nuevoDinero[50];
        int idx = 0;
        int temp = saldo;
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

    cout << "❌ Cédula incorrecta: no existe en el sistema.\n";
    return false;
}

bool modificarDineroUsuario(char** lineas, int numUsuarios, const char* cedulaBuscada, int montoRetiro) {
    const int COSTO_RETIRO = 1000;
    int montoTotal = montoRetiro + COSTO_RETIRO;

    for (int i = 0; i < numUsuarios; i++) {
        int j = 0;
        while (cedulaBuscada[j] != '\0' && lineas[i][j] == cedulaBuscada[j]) j++;
        if (cedulaBuscada[j] != '\0' || lineas[i][j] != ',') continue;

        char* cedula; char* clave; char* nombre; char* dinero;
        separarLinea(lineas[i], cedula, clave, nombre, dinero);

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
            cout << "\n❌ TRANSACCIÓN RECHAZADA\n";
            cout << "Fondos insuficientes para realizar el retiro.\n";
            cout << "=================================\n\n";
            delete[] cedula; delete[] clave; delete[] nombre; delete[] dinero;
            return false;
        }

        saldo -= montoTotal;
        cout << "Nuevo saldo: " << saldo << " COP\n";
        cout << "✅ TRANSACCIÓN EXITOSA\n";
        cout << "=================================\n\n";

        // Actualizar línea
        delete[] lineas[i];
        char nuevoDinero[50];
        int idx = 0;
        int temp = saldo;
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

    cout << "❌ Cédula incorrecta: no existe en el sistema.\n";
    return false;
}
