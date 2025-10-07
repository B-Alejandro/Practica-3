#ifndef ENCRIPTACION_H
#define ENCRIPTACION_H

#include <string>
using namespace std;

// ================================================================
// === Conversión entre binario y texto ASCII =====================
// ================================================================

/**
 * Convierte una cadena binaria (solo '0' y '1') en texto ASCII.
 * Cada 8 bits forman un carácter.
 */
string binarioAtexto(const string& binario);

/**
 * Convierte un texto ASCII a su representación binaria (cadena de '0' y '1').
 */
string textoAbinario(const string& texto);

// ================================================================
// === Inversión de bits ==========================================
// ================================================================

/**
 * Invierte todos los bits de una cadena binaria ('0' ↔ '1').
 */
string invertirBits(const string& binario);

/**
 * Invierte cada bloque de N bits dentro de la cadena binaria.
 */
string invertirCadaNBits(const string& binario, int n);

// ================================================================
// === Encriptación / Desencriptación (por bits) ==================
// ================================================================

/**
 * Encripta una cadena binaria aplicando las reglas de inversión
 * según una semilla determinada.
 */
string encriptarBits(const string& binario, int semilla);

/**
 * Desencripta una cadena binaria previamente encriptada.
 * (El algoritmo es simétrico, aplica la misma operación.)
 */
string desencriptarBits(const string& binario, int semilla);

// ================================================================
// === Helpers que operan sobre UNA cadena ========================
// ================================================================

/**
 * Encripta una cadena de texto (por ejemplo: "usuario,clave,saldo").
 * Retorna la cadena binaria resultante.
 */
string encriptarCadena(const string& textoPlano, int semilla);

/**
 * Desencripta una cadena binaria encriptada, devolviendo el texto plano.
 */
string desencriptarCadena(const string& textoEncriptado, int semilla);

// ================================================================
// === Funciones que operan sobre arreglos (archivos en memoria) ===
// ================================================================

/**
 * Encripta cada línea del arreglo si no está ya en formato binario.
 */
void encriptarArchivo(string* datos, int numLineas, int semilla);

/**
 * Desencripta cada línea del arreglo si está en formato binario.
 */
void desencriptarArchivo(string* datos, int numLineas, int semilla);

/**
 * Verifica si ambos arreglos (usuarios y administradores)
 * están o no encriptados. Retorna true si ambos lo están.
 */
bool verificarEstadoEncriptacion(const string* usuarios, const string* admins);

#endif // ENCRIPTACION_H
