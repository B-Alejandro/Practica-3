#include <iostream>
#include <fstream>
using namespace std;

// ---------------- FUNCIONES AUXILIARES ----------------
int longitud(const char* cadena) {
    int i = 0;
    while (cadena[i] != '\0') i++;
    return i;
}

void copiar(char* destino, const char* origen) {
    int i = 0;
    while (origen[i] != '\0') {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

void concatenar(char* destino, const char* origen) {
    int i = 0;
    while (destino[i] != '\0') i++;
    int j = 0;
    while (origen[j] != '\0') {
        destino[i++] = origen[j++];
    }
    destino[i] = '\0';
}

// Separar una línea en campos: cedula, clave, nombre, dinero
void separarLinea(const char* linea, char*& cedula, char*& clave, char*& nombre, char*& dinero) {
    int len = longitud(linea);
    int campo = 0;
    char buffer[200];
    int pos = 0;

    cedula = clave = nombre = dinero = nullptr;

    for (int i = 0; i <= len; i++) {
        if (linea[i] == ',' || linea[i] == '\0') {
            buffer[pos] = '\0';
            char* nuevo = new char[pos + 1];
            copiar(nuevo, buffer);

            if (campo == 0) cedula = nuevo;
            else if (campo == 1) clave = nuevo;
            else if (campo == 2) nombre = nuevo;
            else if (campo == 3) dinero = nuevo;

            campo++;
            pos = 0;
        } else {
            buffer[pos++] = linea[i];
        }
    }
}

bool cadenasIguales(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return false;
        }
        i++;
    }
    return a[i] == b[i];
}

// Consultar saldo de un usuario por cédula
bool consultarSaldoUsuario(char** lineas, int numUsuarios, const char* cedulaBuscada) {
    const int COSTO_CONSULTA = 1000;

    for (int i = 0; i < numUsuarios; i++) {
        // Comparar inicio de la línea con la cédula
        int j = 0;
        while (cedulaBuscada[j] != '\0' && lineas[i][j] == cedulaBuscada[j]) {
            j++;
        }
        if (cedulaBuscada[j] != '\0' || lineas[i][j] != ',') continue;

        // Separar campos
        char* cedula; char* clave; char* nombre; char* dinero;
        separarLinea(lineas[i], cedula, clave, nombre, dinero);

        // Convertir dinero a entero
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

        // Verificar si hay fondos para el costo de consulta
        if (saldo < COSTO_CONSULTA) {
            cout << "\n⚠️  ADVERTENCIA: Fondos insuficientes para cobrar la consulta." << endl;
            cout << "Saldo después de consulta: 0 COP" << endl;
            saldo = 0;
        } else {
            saldo -= COSTO_CONSULTA;
            cout << "Saldo después de consulta: " << saldo << " COP" << endl;
        }
        cout << "=================================\n\n";

        // Construir nuevo dinero
        char nuevoDinero[50];
        int idx = 0;
        int temp = saldo;
        char rev[20];
        int rpos = 0;
        if (temp == 0) rev[rpos++] = '0';
        while (temp > 0) {
            rev[rpos++] = (temp % 10) + '0';
            temp /= 10;
        }
        for (int t = rpos - 1; t >= 0; t--) {
            nuevoDinero[idx++] = rev[t];
        }
        nuevoDinero[idx++] = ' ';
        nuevoDinero[idx++] = 'C';
        nuevoDinero[idx++] = 'O';
        nuevoDinero[idx++] = 'P';
        nuevoDinero[idx] = '\0';

        // Reconstruir la línea
        delete[] lineas[i];
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

    cout << "❌ Cédula incorrecta: no existe en el sistema." << endl;
    return false;
}

// Modificar el dinero de un usuario por cédula (RETIRO)
bool modificarDineroUsuario(char** lineas, int numUsuarios, const char* cedulaBuscada, int montoRetiro) {
    const int COSTO_RETIRO = 1000;
    int montoTotal = montoRetiro + COSTO_RETIRO;

    for (int i = 0; i < numUsuarios; i++) {
        // Comparar inicio de la línea con la cédula
        int j = 0;
        while (cedulaBuscada[j] != '\0' && lineas[i][j] == cedulaBuscada[j]) {
            j++;
        }
        if (cedulaBuscada[j] != '\0' || lineas[i][j] != ',') continue;

        // Separar campos
        char* cedula; char* clave; char* nombre; char* dinero;
        separarLinea(lineas[i], cedula, clave, nombre, dinero);

        // Convertir dinero a entero
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

        // Validar fondos suficientes
        if (saldo < montoTotal) {
            cout << "\n❌ TRANSACCIÓN RECHAZADA" << endl;
            cout << "Fondos insuficientes para realizar el retiro." << endl;
            cout << "Se requieren " << montoTotal << " COP y solo tiene " << saldo << " COP." << endl;
            cout << "=================================\n\n";
            delete[] cedula; delete[] clave; delete[] nombre; delete[] dinero;
            return false;
        }

        saldo -= montoTotal;
        cout << "Nuevo saldo: " << saldo << " COP" << endl;
        cout << "✅ TRANSACCIÓN EXITOSA" << endl;
        cout << "=================================\n\n";

        // Construir nuevo dinero
        char nuevoDinero[50];
        int idx = 0;
        int temp = saldo;
        char rev[20];
        int rpos = 0;
        if (temp == 0) rev[rpos++] = '0';
        while (temp > 0) {
            rev[rpos++] = (temp % 10) + '0';
            temp /= 10;
        }
        for (int t = rpos - 1; t >= 0; t--) {
            nuevoDinero[idx++] = rev[t];
        }
        nuevoDinero[idx++] = ' ';
        nuevoDinero[idx++] = 'C';
        nuevoDinero[idx++] = 'O';
        nuevoDinero[idx++] = 'P';
        nuevoDinero[idx] = '\0';

        // Reconstruir la línea
        delete[] lineas[i];
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

    cout << "❌ Cédula incorrecta: no existe en el sistema." << endl;
    return false;
}
