#ifndef ENCRIPTACION_H
#define ENCRIPTACION_H

// ===================== INVERSIÓN DE BITS =====================

/**
 * @brief Invierte todos los bits de un bloque ('0' ↔ '1').
 * @param bloque Cadena binaria a invertir.
 * @param len Longitud del bloque.
 * @return Nueva cadena con bits invertidos.
 */
unsigned char* invertirBits(const unsigned char* bloque, int len);

/**
 * @brief Invierte bloques de N bits dentro de la cadena.
 * @param bloque Cadena binaria a procesar.
 * @param len Longitud total de la cadena.
 * @param n Tamaño de cada bloque a invertir.
 * @return Nueva cadena con bloques invertidos.
 */
unsigned char* invertirCadaNBits(unsigned char* bloque, int len, int n);

// ===================== ENCRIPTACIÓN DE BITS =====================

/**
 * @brief Encripta una cadena binaria usando el algoritmo de bloques.
 * @param binary Cadena binaria a encriptar.
 * @param size Tamaño de la cadena binaria.
 * @param semilla Tamaño de los bloques para el procesamiento.
 * @return Cadena binaria encriptada.
 */
unsigned char* encriptarBits(const unsigned char* binary, int size, int semilla);

/**
 * @brief Desencripta una cadena binaria (proceso simétrico).
 * @param binary Cadena binaria encriptada.
 * @param size Tamaño de la cadena binaria.
 * @param semilla Tamaño de los bloques usado en la encriptación.
 * @return Cadena binaria desencriptada.
 */
unsigned char* desencriptarBits(const unsigned char* binary, int size, int semilla);

// ===================== FUNCIONES DE ALTO NIVEL =====================

/**
 * @brief Encripta un arreglo de líneas: texto → binario → encriptación.
 * @param datos Arreglo de cadenas a encriptar (se modifica in-place).
 * @param numLineas Número de líneas en el arreglo.
 * @param semilla Semilla para el algoritmo de encriptación.
 */
void encriptarArchivo(char** datos, int numLineas, int semilla);

/**
 * @brief Desencripta un arreglo de líneas: desencriptación → binario → texto.
 * @param datos Arreglo de cadenas encriptadas (se modifica in-place).
 * @param numLineas Número de líneas en el arreglo.
 * @param semilla Semilla usada en la encriptación.
 */
void desencriptarArchivo(char** datos, int numLineas, int semilla);

/**
 * @brief Verifica si los archivos están encriptados.
 * @param usuarios Arreglo de líneas del archivo de usuarios.
 * @param admins Arreglo de líneas del archivo de administradores.
 * @return true si ambos están encriptados, false si están en texto plano.
 */
bool verificarEstadoEncriptacion(char** usuarios, char** admins);

#endif // ENCRIPTACION_H
