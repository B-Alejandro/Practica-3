#include <iostream>
using namespace std;

// ============================================================
//                 FUNCIONES BÁSICAS DE CADENAS
// ============================================================

/**
 * @brief Calcula la longitud de una cadena de caracteres.
 *
 * Recorre la cadena hasta encontrar el terminador nulo '\0'.
 *
 * @param cadena Puntero a la cadena de caracteres.
 * @return int Longitud de la cadena (sin contar el '\0').
 *
 * @throw const char* Si el puntero es nulo.
 *
 * @note Si ocurre un error, se imprime un mensaje y se devuelve 0.
 */
int longitud(const char* cadena) {
    try {
        if (cadena == nullptr)
            throw "Cadena nula en longitud().";

        int i = 0;
        while (cadena[i] != '\0') i++;
        return i;
    } catch (const char* msg) {
        cerr << "[Error] " << msg << endl;
        return 0;
    }
}

/**
 * @brief Copia el contenido de una cadena de origen a una cadena destino.
 *
 * @param destino Puntero al buffer donde se copiará el texto (salida).
 * @param origen Puntero a la cadena de origen (entrada).
 *
 * @throw const char* Si alguno de los punteros es nulo.
 *
 * @note Asegúrate de que el destino tenga suficiente espacio.
 */
void copiar(char* destino, const char* origen) {
    try {
        if (!destino || !origen)
            throw "Puntero nulo en copiar().";

        int i = 0;
        while (origen[i] != '\0') {
            destino[i] = origen[i];
            i++;
        }
        destino[i] = '\0';
    } catch (const char* msg) {
        cerr << "[Error] " << msg << endl;
    }
}

/**
 * @brief Copia un número específico de caracteres sin añadir terminador nulo.
 *
 * @param destino Puntero al buffer destino (salida).
 * @param origen Puntero a la cadena de origen (entrada).
 * @param len Número de caracteres a copiar.
 *
 * @throw const char* Si alguno de los punteros es nulo o si la longitud es negativa.
 */
void copiarN(char* destino, const char* origen, int len) {
    try {
        if (!destino || !origen)
            throw "Puntero nulo en copiarN().";
        if (len < 0)
            throw "Longitud negativa en copiarN().";

        for (int i = 0; i < len; i++)
            destino[i] = origen[i];
    } catch (const char* msg) {
        cerr << "[Error] " << msg << endl;
    }
}

// ============================================================
//                     MANEJO DE TEXTO
// ============================================================

/**
 * @brief Concatena una cadena al final de otra.
 *
 * @param destino Cadena destino donde se agregará el texto.
 * @param origen Cadena que se agregará al final.
 *
 * @throw const char* Si alguno de los punteros es nulo.
 *
 * @note No se valida el tamaño del buffer destino.
 */
void concatenar(char* destino, const char* origen) {
    try {
        if (!destino || !origen)
            throw "Puntero nulo en concatenar().";

        int i = 0;
        while (destino[i] != '\0') i++;
        int j = 0;
        while (origen[j] != '\0') {
            destino[i++] = origen[j++];
        }
        destino[i] = '\0';
    } catch (const char* msg) {
        cerr << "[Error] " << msg << endl;
    }
}

/**
 * @brief Separa una línea con formato "cedula,clave,nombre,dinero".
 *
 * Asigna memoria dinámica para cada campo. Si ocurre un error,
 * los punteros de salida quedan en `nullptr`.
 *
 * @param linea Cadena de texto a dividir (entrada).
 * @param cedula Referencia a puntero que recibirá la cédula.
 * @param clave Referencia a puntero que recibirá la clave.
 * @param nombre Referencia a puntero que recibirá el nombre.
 * @param dinero Referencia a puntero que recibirá el dinero.
 *
 * @throw const char* Si la línea es nula, vacía o tiene menos de 4 campos.
 *
 * @note El usuario debe liberar la memoria asignada con `delete[]`.
 */
void separarLinea(const char* linea, char*& cedula, char*& clave, char*& nombre, char*& dinero) {
    try {
        if (!linea)
            throw "Línea nula en separarLinea().";

        int len = longitud(linea);
        if (len == 0)
            throw "Línea vacía en separarLinea().";

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

        if (campo < 4)
            throw "Número de campos insuficiente en separarLinea().";

    } catch (const char* msg) {
        cerr << "[Error] " << msg << endl;
        cedula = clave = nombre = dinero = nullptr;
    }
}

/**
 * @brief Compara dos cadenas de texto.
 *
 * Devuelve `true` si son idénticas en contenido y longitud.
 *
 * @param a Primera cadena (entrada).
 * @param b Segunda cadena (entrada).
 * @return `true` si son iguales, `false` en caso contrario.
 *
 * @throw const char* Si alguno de los punteros es nulo.
 */
bool cadenasIguales(const char* a, const char* b) {
    try {
        if (!a || !b)
            throw "Puntero nulo en cadenasIguales().";

        int i = 0;
        while (a[i] != '\0' && b[i] != '\0') {
            if (a[i] != b[i]) return false;
            i++;
        }
        return a[i] == b[i];
    } catch (const char* msg) {
        cerr << "[Error] " << msg << endl;
        return false;
    }
}

/**
 * @brief Verifica si una cadena está compuesta solo por '0' y '1'.
 *
 * @param texto Cadena a verificar.
 * @return `true` si es binaria, `false` en caso contrario.
 *
 * @throw const char* Si el puntero es nulo o la cadena está vacía.
 */
bool esBinario(const char* texto) {
    try {
        if (!texto)
            throw "Cadena nula en esBinario().";
        if (texto[0] == '\0')
            throw "Cadena vacía en esBinario().";

        for (int i = 0; texto[i] != '\0'; i++) {
            if (texto[i] != '0' && texto[i] != '1')
                return false;
        }
        return true;
    } catch (const char* msg) {
        cerr << "[Error] " << msg << endl;
        return false;
    }
}
