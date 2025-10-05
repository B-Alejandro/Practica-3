#ifndef SISTEMA_H
#define SISTEMA_H

// ======================================================
//  Archivo: Sistema.h
//  Descripción: Declaraciones de funciones para la
//  gestión de archivos del sistema de cajero.
// ======================================================

// ==================== GESTIÓN DE ARCHIVOS ====================

/**
 * @brief Lee un archivo y devuelve sus líneas como un arreglo dinámico de cadenas.
 *
 * Cada línea se guarda como un `char*` en un arreglo de punteros (`char**`).
 * Incluye validación de tamaño para evitar cargar archivos corruptos.
 *
 * @param rutaArchivo Ruta del archivo a leer (cadena tipo C).
 * @param numLineas Referencia donde se almacenará el número de líneas leídas.
 * @return char** Arreglo dinámico de líneas, o nullptr si ocurre un error.
 *
 * @note El usuario debe liberar la memoria de cada línea y del arreglo con delete[].
 */
char** leerArchivoLineas(const char* rutaArchivo, int& numLineas);

/**
 * @brief Guarda un arreglo de líneas en un archivo.
 *
 * Escribe todas las líneas del arreglo en el archivo especificado,
 * sobrescribiendo su contenido anterior.
 *
 * @param rutaArchivo Ruta del archivo donde guardar.
 * @param lineas Arreglo de cadenas a guardar.
 * @param numLineas Número de líneas en el arreglo.
 */
void guardarArchivoLineas(const char* rutaArchivo, char** lineas, int numLineas);

/**
 * @brief Guarda el arreglo de usuarios en un archivo de texto plano.
 *
 * IMPORTANTE: Este archivo NO debe estar encriptado.
 * Se guarda en formato: cedula,clave,nombre,saldo COP
 *
 * @param usuarios Arreglo de cadenas de usuarios.
 * @param numUsuarios Número de usuarios en el arreglo.
 * @param ruta Ruta del archivo donde guardar.
 *
 * @deprecated Use guardarArchivoLineas() en su lugar para mayor flexibilidad.
 */
void guardarUsuariosEnArchivo(char** usuarios, int numUsuarios, const char* ruta);

/**
 * @brief Muestra en consola el contenido de un arreglo de bytes.
 *
 * Recorre un arreglo de bytes y muestra los caracteres directamente.
 *
 * @param contenido Puntero al arreglo de bytes.
 * @param size Número de bytes en el arreglo.
 */
void mostrarContenido(unsigned char* contenido, int size);

/**
 * @brief Muestra en consola el contenido de un arreglo de líneas.
 *
 * Útil para depuración: muestra cada línea numerada del arreglo.
 *
 * @param lineas Arreglo de cadenas (char**).
 * @param numLineas Número de líneas en el arreglo.
 */
void mostrarLineas(char** lineas, int numLineas);

#endif // SISTEMA_H
