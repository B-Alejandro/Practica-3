#include "utilidadesCadena.h"
#include <iostream>
#include <stdexcept>
using namespace std;

// ------------------------------------------
// Funciones auxiliares
// ------------------------------------------

/**
 * @brief Extrae la cédula y la clave de una línea de texto con formato delimitado.
 *
 * Esta función asume que la cédula es el primer campo y la clave el segundo,
 * y ambos están separados por una coma. Ignora espacios y tabuladores
 * al inicio y alrededor de la coma.
 *
 * @param linea La línea de texto de donde se extraerán los datos.
 * @param cedula Puntero al buffer donde se almacenará la cédula extraída (salida).
 * @param maxCedula El tamaño máximo del buffer para la cédula.
 * @param clave Puntero al buffer donde se almacenará la clave extraída (salida).
 * @param maxClave El tamaño máximo del buffer para la clave.
 */
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

// ==========================================
// CONSULTAR SALDO DE USUARIO
// ==========================================

/**
 * @brief Consulta el saldo de un usuario específico, lo muestra por consola y lo actualiza descontando el costo de la consulta.
 *
 * Itera sobre las líneas de usuarios, busca la cédula, extrae el saldo, lo muestra,
 * aplica el costo de la consulta (1000 COP) y actualiza la línea del usuario con
 * el nuevo saldo. Si el saldo es insuficiente, no se cobra la consulta.
 *
 * @param lineas Un arreglo de punteros a cadenas de caracteres, donde cada cadena
 * representa la información de un usuario (Cédula, Clave, Nombre, Dinero).
 * @param numUsuarios El número total de usuarios en el arreglo `lineas`.
 * @param cedulaBuscada La cédula del usuario cuyo saldo se desea consultar.
 * @return `true` si se encuentra el usuario, se consulta el saldo y se actualiza la línea.
 * @return `false` si no se encuentra la cédula o si ocurre un error (datos inválidos, error al separar línea).
 * @exception std::invalid_argument Si `lineas` es nulo, `numUsuarios` es $\le 0$ o `cedulaBuscada` es nulo.
 * @exception std::runtime_error Si el campo dinero no se puede separar correctamente.
 */
bool consultarSaldoUsuario(char** lineas, int numUsuarios, const char* cedulaBuscada) {
    const int COSTO_CONSULTA = 1000;

    try {
        if (!lineas || numUsuarios <= 0 || !cedulaBuscada)
            throw invalid_argument("Datos de entrada invalidos en consultarSaldoUsuario.");

        for (int i = 0; i < numUsuarios; i++) {
            int j = 0;
            // Compara la cédulaBuscada con el inicio de la línea (la cédula del usuario)
            while (cedulaBuscada[j] != '\0' && lineas[i][j] == cedulaBuscada[j]) j++;
            // Verifica que la cédula sea idéntica y que lo que siga en la línea sea la coma delimitadora
            if (cedulaBuscada[j] != '\0' || lineas[i][j] != ',') continue;

            char* cedula; char* clave; char* nombre; char* dinero;
            // Asume que separarLinea (definida en "utilidadesCadena.h") separa dinámicamente
            // la línea y asigna punteros a los campos.
            separarLinea(lineas[i], cedula, clave, nombre, dinero);

            if (!dinero) throw runtime_error("El campo dinero no se pudo separar correctamente.");

            int saldo = 0;
            int k = 0;
            // Convierte la cadena de dinero a entero (asume que los primeros caracteres son dígitos)
            while (dinero[k] >= '0' && dinero[k] <= '9') {
                saldo = saldo * 10 + (dinero[k] - '0');
                k++;
            }

            cout << "\n=================================\n";
            cout << "  CONSULTA DE SALDO\n";
            cout << "=================================\n";
            cout << "Usuario: " << nombre << endl;
            cout << "Cedula: " << cedula << endl;
            cout << "Saldo actual: " << saldo << " COP" << endl;
            cout << "Costo de consulta: " << COSTO_CONSULTA << " COP" << endl;

            if (saldo < COSTO_CONSULTA) {
                cout << "\nAdvertencia: Fondos insuficientes para cobrar la consulta.\n";
                saldo = 0;
            } else {
                saldo -= COSTO_CONSULTA;
            }

            cout << "Saldo despues de consulta: " << saldo << " COP\n";
            cout << "=================================\n\n";

            // Actualizar linea con el nuevo saldo
            delete[] lineas[i]; // Libera la línea antigua

            // Convierte el nuevo saldo a cadena para la actualización
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

            // Vuelve a construir la línea completa con el nuevo saldo
            // Se asume que longitud y concatenar están en "utilidadesCadena.h"
            int newLen = longitud(cedula) + longitud(clave) + longitud(nombre) + longitud(nuevoDinero) + 4; // +4 por las 3 comas y el '\0'
            lineas[i] = new char[newLen];
            lineas[i][0] = '\0';
            concatenar(lineas[i], cedula);
            concatenar(lineas[i], ",");
            concatenar(lineas[i], clave);
            concatenar(lineas[i], ",");
            concatenar(lineas[i], nombre);
            concatenar(lineas[i], ",");
            concatenar(lineas[i], nuevoDinero);

            // Libera los campos separados dinámicamente por separarLinea (asumiendo que usa new[])
            delete[] cedula; delete[] clave; delete[] nombre; delete[] dinero;
            return true;
        }

        cout << "Cedula incorrecta: no existe en el sistema.\n";
        return false;
    } catch (const exception& e) {
        cerr << "Error en consultarSaldoUsuario: " << e.what() << endl;
        return false;
    }
}

// ==========================================
// RETIRO DE DINERO
// ==========================================

/**
 * @brief Modifica el saldo de un usuario realizando un retiro, descontando el monto y el costo de la transacción.
 *
 * Itera sobre las líneas de usuarios, busca la cédula, verifica que haya fondos
 * suficientes (monto de retiro + costo de retiro), realiza el descuento y actualiza
 * la línea del usuario con el nuevo saldo.
 *
 * @param lineas Un arreglo de punteros a cadenas de caracteres, donde cada cadena
 * representa la información de un usuario (Cédula, Clave, Nombre, Dinero).
 * @param numUsuarios El número total de usuarios en el arreglo `lineas`.
 * @param cedulaBuscada La cédula del usuario al que se le modificará el saldo.
 * @param montoRetiro El monto de dinero que el usuario desea retirar.
 * @return `true` si se encuentra el usuario, hay fondos suficientes y se actualiza la línea.
 * @return `false` si no se encuentra la cédula, no hay fondos o si ocurre un error.
 * @exception std::invalid_argument Si `lineas` es nulo, `numUsuarios` es $\le 0$ o `cedulaBuscada` es nulo.
 * @exception std::runtime_error Si el campo dinero no se puede separar correctamente.
 */
bool modificarDineroUsuario(char** lineas, int numUsuarios, const char* cedulaBuscada, int montoRetiro) {
    const int COSTO_RETIRO = 1000;
    int montoTotal = montoRetiro + COSTO_RETIRO;

    try {
        if (!lineas || numUsuarios <= 0 || !cedulaBuscada)
            throw invalid_argument("Datos de entrada invalidos en modificarDineroUsuario.");

        for (int i = 0; i < numUsuarios; i++) {
            int j = 0;
            // Compara la cédulaBuscada con el inicio de la línea (la cédula del usuario)
            while (cedulaBuscada[j] != '\0' && lineas[i][j] == cedulaBuscada[j]) j++;
            // Verifica que la cédula sea idéntica y que lo que siga en la línea sea la coma delimitadora
            if (cedulaBuscada[j] != '\0' || lineas[i][j] != ',') continue;

            char* cedula; char* clave; char* nombre; char* dinero;
            // Asume que separarLinea (definida en "utilidadesCadena.h") separa dinámicamente
            // la línea y asigna punteros a los campos.
            separarLinea(lineas[i], cedula, clave, nombre, dinero);

            if (!dinero) throw runtime_error("El campo dinero no se pudo separar correctamente.");

            int saldo = 0;
            int k = 0;
            // Convierte la cadena de dinero a entero (asume que los primeros caracteres son dígitos)
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
            cout << "Costo de transaccion: " << COSTO_RETIRO << " COP" << endl;
            cout << "Total a descontar: " << montoTotal << " COP" << endl;

            if (saldo < montoTotal) {
                cout << "\nTransaccion rechazada.\n";
                cout << "Fondos insuficientes para realizar el retiro.\n";
                cout << "=================================\n\n";
                delete[] cedula; delete[] clave; delete[] nombre; delete[] dinero;
                return false;
            }

            saldo -= montoTotal;
            cout << "Nuevo saldo: " << saldo << " COP\n";
            cout << "Transaccion exitosa.\n";
            cout << "=================================\n\n";

            // Actualizar linea con el nuevo saldo
            delete[] lineas[i]; // Libera la línea antigua

            // Convierte el nuevo saldo a cadena para la actualización
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

            // Vuelve a construir la línea completa con el nuevo saldo
            // Se asume que longitud y concatenar están en "utilidadesCadena.h"
            int newLen = longitud(cedula) + longitud(clave) + longitud(nombre) + longitud(nuevoDinero) + 4; // +4 por las 3 comas y el '\0'
            lineas[i] = new char[newLen];
            lineas[i][0] = '\0';
            concatenar(lineas[i], cedula);
            concatenar(lineas[i], ",");
            concatenar(lineas[i], clave);
            concatenar(lineas[i], ",");
            concatenar(lineas[i], nombre);
            concatenar(lineas[i], ",");
            concatenar(lineas[i], nuevoDinero);

            // Libera los campos separados dinámicamente por separarLinea (asumiendo que usa new[])
            delete[] cedula; delete[] clave; delete[] nombre; delete[] dinero;
            return true;
        }

        cout << "Cedula incorrecta: no existe en el sistema.\n";
        return false;
    } catch (const exception& e) {
        cerr << "Error en modificarDineroUsuario: " << e.what() << endl;
        return false;
    }
}
