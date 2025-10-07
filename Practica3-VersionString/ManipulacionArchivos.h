#ifndef MANIPULACION_ARCHIVOS_H
#define MANIPULACION_ARCHIVOS_H

#include <string>
using namespace std;

/**
 * @brief Lee un archivo y devuelve sus líneas como un arreglo dinámico de strings.
 *
 * Cada línea se guarda como un `std::string` dentro de un arreglo `string*`.
 * Incluye validación de tamaño para evitar cargar archivos corruptos.
 *
 * @param rutaArchivo Ruta del archivo a leer.
 * @param numLineas Referencia donde se almacenará el número de líneas leídas.
 * @return string* Arreglo dinámico de líneas, o nullptr si ocurre un error.
 * @throws runtime_error Si el archivo no se puede abrir o está corrupto.
 */
string* leerArchivoLineas(const string& rutaArchivo, int& numLineas);

/**
 * @brief Guarda un arreglo de strings en un archivo de texto.
 *
 * Sobrescribe el archivo si ya existe.
 *
 * @param rutaArchivo Ruta del archivo a escribir.
 * @param lineas Arreglo de cadenas a guardar.
 * @param numLineas Número de líneas a escribir.
 */
void guardarArchivoLineas(const string& rutaArchivo, string* lineas, int numLineas);

/**
 * @brief Muestra en consola el contenido de un arreglo de strings.
 *
 * @param lineas Arreglo de cadenas.
 * @param numLineas Número de líneas.
 */
void mostrarLineas(string* lineas, int numLineas);

/**
 * @brief Libera la memoria asignada a un arreglo dinámico de strings.
 *
 * @param lineas Referencia al puntero del arreglo para dejarlo en nullptr.
 */
void liberarLineas(string*& lineas);

#endif // MANIPULACION_ARCHIVOS_H
