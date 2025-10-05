#ifndef ENCRIPTACION_H
#define ENCRIPTACION_H
// ======================================================
//  Archivo: Encriptacion.h
//  Descripción: Declaraciones de funciones para el
//  sistema de encriptación y desencriptación de datos
//  de usuarios y administradores.
// ======================================================

#include <iostream>

// ==================== FUNCIONES AUXILIARES ====================

/**
 * @brief Calcula la longitud de una cadena terminada en '\0'.
 * @param texto Cadena a medir.
 * @return Número de caracteres antes del terminador.
 */
int longitud(const unsigned char* texto);

/**
 * @brief Copia manualmente len caracteres de origen a destino.
 * @param destino Buffer de destino.
 * @param origen Buffer de origen.
 * @param len Número de caracteres a copiar.
 */
void copiar(unsigned char* destino, const unsigned char* origen, int len);

// ==================== CONVERSIÓN BINARIO ↔ TEXTO ====================

/**
 * @brief Convierte texto ASCII a su representación binaria (8 bits por carácter).
 * @param text Texto ASCII de entrada.
 * @param size Número de caracteres en el texto.
 * @return Cadena binaria resultante (debe liberarse con delete[]).
 *
 * Ejemplo: "a" → "01100001"
 */
unsigned char* textoAbinario(unsigned char* text, int size);

/**
 * @brief Convierte una cadena binaria a texto ASCII.
 * @param texto Cadena de bits (debe tener longitud múltiplo de 8).
 * @param size Número total de bits en el arreglo.
 * @return Texto ASCII resultante (debe liberarse con delete[]).
 *
 * Ejemplo: "01100001" → "a"
 */
unsigned char* binarioAtexto(unsigned char* texto, int size);

// ==================== CAPA DE BITS ====================

/**
 * @brief Invierte todos los bits ('0' ↔ '1') de un bloque binario.
 * @param bloque Cadena binaria a invertir.
 * @param len Longitud del bloque.
 * @return Nuevo bloque binario invertido (debe liberarse con delete[]).
 */
unsigned char* invertirBits(const unsigned char* bloque, int len);

/**
 * @brief Invierte grupos de N bits dentro del bloque.
 * @param bloque Cadena binaria.
 * @param len Longitud del bloque.
 * @param n Tamaño de los grupos a invertir.
 * @return Nuevo bloque procesado (debe liberarse con delete[]).
 */
unsigned char* invertirCadaNBits(unsigned char* bloque, int len, int n);

/**
 * @brief Encripta una cadena binaria dividiéndola en bloques de longitud `semilla`.
 *
 * Algoritmo:
 * - Primer bloque: invierte todos los bits
 * - Bloques siguientes: según conteo de 1s y 0s del bloque anterior:
 *   * Igual cantidad → invertir todos
 *   * Más 0s que 1s → invertir cada 2 bits
 *   * Más 1s que 0s → invertir cada 3 bits
 *
 * @param binary Cadena binaria original.
 * @param size Número total de bits.
 * @param semilla Tamaño de los bloques.
 * @return Cadena binaria encriptada (debe liberarse con delete[]).
 */
unsigned char* encriptarBits(const unsigned char* binary, int size, int semilla);

/**
 * @brief Desencripta una cadena binaria usando las mismas reglas que encriptarBits.
 *
 * Nota: Este algoritmo es simétrico, por lo que aplicar la misma operación
 * dos veces devuelve el texto original.
 *
 * @param binary Cadena binaria cifrada.
 * @param size Longitud total en bits.
 * @param semilla Tamaño de bloque usado en el cifrado.
 * @return Cadena desencriptada (debe liberarse con delete[]).
 */
unsigned char* desencriptarBits(const unsigned char* binary, int size, int semilla);

// ==================== VERIFICACIÓN ====================

/**
 * @brief Determina si una cadena está compuesta únicamente por '0' y '1'.
 * @param texto Cadena a verificar.
 * @return true si es binaria, false si contiene otros caracteres.
 */
bool esBinario(const char* texto);

// ==================== FUNCIONES DE ALTO NIVEL ====================

/**
 * @brief Encripta un arreglo completo de líneas (texto → binario → encriptación).
 *
 * Proceso:
 * 1. Convierte cada línea de texto ASCII a binario
 * 2. Aplica el algoritmo de encriptación con la semilla especificada
 * 3. Reemplaza las líneas originales con las versiones encriptadas
 *
 * @param datos Arreglo de cadenas a encriptar (se modifica in-place).
 * @param numLineas Número de líneas en el arreglo.
 * @param semilla Semilla para el algoritmo de encriptación.
 *
 * Nota: Las líneas originales se liberan y reemplazan con nuevas cadenas.
 */
void encriptarArchivo(char** datos, int numLineas, int semilla);

/**
 * @brief Desencripta un arreglo completo de líneas (desencriptación → binario → texto).
 *
 * Proceso:
 * 1. Desencripta cada línea con la semilla especificada
 * 2. Convierte el binario resultante a texto ASCII
 * 3. Reemplaza las líneas encriptadas con las versiones en texto claro
 *
 * @param datos Arreglo de cadenas encriptadas (se modifica in-place).
 * @param numLineas Número de líneas en el arreglo.
 * @param semilla Semilla usada en la encriptación original.
 *
 * Nota: Las líneas encriptadas se liberan y reemplazan con texto legible.
 */
void desencriptarArchivo(char** datos, int numLineas, int semilla);

/**
 * @brief Verifica si los archivos de usuarios y administradores están encriptados.
 *
 * Comprueba si ambos arreglos contienen solo caracteres binarios ('0' y '1').
 *
 * @param usuarios Arreglo de cadenas de usuarios.
 * @param admins Arreglo de cadenas de administradores.
 * @return true si ambos están encriptados (en formato binario).
 * @return false si están en texto plano o hay inconsistencias.
 */
bool verificarEstadoEncriptacion(char** usuarios, char** admins);

// ==================== FUNCIONES LEGACY (DEPRECADAS) ====================
// Las siguientes funciones se mantienen por compatibilidad pero no se
// recomiendan para nuevos desarrollos. Use las funciones de alto nivel.

/**
 * @brief [DEPRECADA] Encripta líneas asumiendo que ya están en formato binario.
 * @param datos Arreglo de cadenas terminadas en nullptr.
 * @deprecated Use encriptarArchivo() que maneja la conversión completa.
 */
void encriptar(char** datos);

/**
 * @brief [DEPRECADA] Desencripta líneas dejándolas en formato binario.
 * @param datos Arreglo de cadenas terminadas en nullptr.
 * @deprecated Use desencriptarArchivo() que maneja la conversión completa.
 */
void desencriptar(char** datos);

/**
 * @brief [DEPRECADA] Verifica y encripta archivos si no lo están.
 * @deprecated Use verificarEstadoEncriptacion() y encriptarArchivo() separadamente.
 */
bool confirmarEncriptacion(const char* rutaAdmins,
                           const char* rutaUsuarios,
                           char** usuarios,
                           char** admins);

#endif // ENCRIPTACION_H
