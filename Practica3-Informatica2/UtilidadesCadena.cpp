
#include <iostream>
using namespace std;

// ===================== FUNCIONES BÁSICAS =====================

/**
 * @brief Calcula la longitud de una cadena de caracteres.
 *
 * La longitud se determina contando el número de caracteres hasta
 * encontrar el terminador nulo ('\0').
 *
 * @param cadena La cadena de caracteres de entrada.
 * @return El número de caracteres en la cadena (excluyendo el '\0').
 */
int longitud(const char* cadena) {
    int i = 0;
    while (cadena[i] != '\0') i++;
    return i;
}

/**
 * @brief Copia el contenido de una cadena de origen a una cadena de destino.
 *
 * Se asume que el buffer de destino tiene suficiente espacio para alojar
 * la cadena de origen, incluido el terminador nulo.
 *
 * @param destino Puntero al buffer donde se copiará la cadena (salida).
 * @param origen Puntero a la cadena de caracteres a copiar (entrada).
 */
void copiar(char* destino, const char* origen) {
    int i = 0;
    while (origen[i] != '\0') {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

/**
 * @brief Copia un número específico de caracteres de una cadena de origen a una de destino.
 *
 * Esta función *no* agrega un terminador nulo ('\0') al destino,
 * por lo que el resultado puede no ser una cadena de C válida a menos que
 * `destino[len]` sea terminada manualmente.
 *
 * @param destino Puntero al buffer donde se copiarán los caracteres (salida).
 * @param origen Puntero a la cadena de caracteres de origen (entrada).
 * @param len El número de caracteres a copiar.
 */
void copiarN(char* destino, const char* origen, int len) {
    for (int i = 0; i < len; i++) destino[i] = origen[i];
}

// ===================== MANEJO DE TEXTO =====================

/**
 * @brief Concatena una cadena de origen al final de una cadena de destino.
 *
 * Se asume que el buffer de destino tiene suficiente espacio
 * para alojar la cadena ya existente más la cadena de origen.
 *
 * @param destino Puntero a la cadena que será extendida (entrada/salida).
 * @param origen Puntero a la cadena que se agregará al final (entrada).
 */
void concatenar(char* destino, const char* origen) {
    int i = 0;
    while (destino[i] != '\0') i++;
    int j = 0;
    while (origen[j] != '\0') {
        destino[i++] = origen[j++];
    }
    destino[i] = '\0';
}

/**
 * @brief Separa una línea de texto delimitada por comas en cuatro campos.
 *
 * Esta función espera que la línea contenga los campos: **cédula, clave, nombre, dinero**.
 * Asigna dinámicamente memoria para cada campo y los punteros de referencia
 * (cedula, clave, nombre, dinero) apuntarán a estas nuevas cadenas.
 * **Es responsabilidad del llamador liberar esta memoria con `delete[]`**.
 *
 * @param linea La cadena de entrada que contiene los campos separados por comas.
 * @param cedula Puntero a `char*` donde se almacenará la cédula (salida, memoria asignada dinámicamente).
 * @param clave Puntero a `char*` donde se almacenará la clave (salida, memoria asignada dinámicamente).
 * @param nombre Puntero a `char*` donde se almacenará el nombre (salida, memoria asignada dinámicamente).
 * @param dinero Puntero a `char*` donde se almacenará el dinero (salida, memoria asignada dinámicamente).
 */
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

/**
 * @brief Compara lexicográficamente dos cadenas de caracteres.
 *
 * La comparación se realiza caracter por caracter hasta que se encuentra
 * una diferencia o se alcanza el terminador nulo en ambas.
 *
 * @param a La primera cadena a comparar (entrada).
 * @param b La segunda cadena a comparar (entrada).
 * @return `true` si ambas cadenas son idénticas en contenido y longitud.
 * @return `false` en caso contrario.
 */
bool cadenasIguales(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

/**
 * @brief Verifica si una cadena de texto representa un número binario.
 *
 * Una cadena se considera binaria si está compuesta únicamente por los
 * caracteres '0' y '1'.
 *
 * @param texto La cadena de caracteres a verificar.
 * @return `true` si la cadena solo contiene '0' y '1'.
 * @return `false` si contiene cualquier otro caracter.
 */
bool esBinario(const char* texto) {
    for (int i = 0; texto[i] != '\0'; i++) {
        if (texto[i] != '0' && texto[i] != '1') return false;
    }
    return true;
}
