#ifndef UTILIDADES_CADENA_H
#define UTILIDADES_CADENA_H

#include <iostream>
using namespace std;

/**
 * @brief Calcula la longitud de una cadena terminada en '\0'.
 * @param cadena Cadena de caracteres.
 * @return Número de caracteres antes del terminador nulo.
 */
int longitud(const char* cadena);

/**
 * @brief Copia el contenido de la cadena origen en la destino.
 * @param destino Cadena destino (debe tener suficiente espacio).
 * @param origen Cadena origen.
 */
void copiar(char* destino, const char* origen);

/**
 * @brief Copia manualmente una cantidad fija de caracteres.
 * @param destino Cadena destino.
 * @param origen Cadena origen.
 * @param len Número de caracteres a copiar.
 */
void copiarN(char* destino, const char* origen, int len);

/**
 * @brief Concatena la cadena origen al final de la destino.
 */
void concatenar(char* destino, const char* origen);

/**
 * @brief Separa una línea CSV con formato "cedula,clave,nombre,dinero"
 * en cuatro cadenas independientes (asignadas dinámicamente).
 */
void separarLinea(const char* linea, char*& cedula, char*& clave, char*& nombre, char*& dinero);

/**
 * @brief Compara dos cadenas carácter por carácter.
 * @return true si son idénticas, false si difieren.
 */
bool cadenasIguales(const char* a, const char* b);

/**
 * @brief Verifica si una cadena contiene solo '0' y '1'.
 * @return true si es una cadena binaria, false de lo contrario.
 */
bool esBinario(const char* texto);

#endif // UTILIDADES_CADENA_H
