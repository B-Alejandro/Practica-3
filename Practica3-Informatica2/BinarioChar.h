#ifndef CONVERSION_BINARIO_H
#define CONVERSION_BINARIO_H

/**
 * @brief Convierte una cadena binaria a texto ASCII.
 *
 * Recorre un arreglo de caracteres binarios ('0' y '1') y los agrupa
 * en bloques de 8 bits para reconstruir cada carácter ASCII.
 *
 * Ejemplo:
 * - Entrada: "01100001" (8 bits)
 * - Salida: 'a'
 *
 * @param binario Cadena de bits (unsigned char*), debe tener longitud múltiplo de 8.
 * @param len Número total de bits en el arreglo (longitud de texto).
 * @return unsigned char* Texto ASCII resultante (memoria dinámica terminada en '\0').
 *
 * @note El usuario debe liberar la memoria con `delete[]` después de usar el resultado.
 */
unsigned char* binarioAtexto(const unsigned char* binario, int len);

/**
 * @brief Convierte un texto ASCII a su representación binaria (8 bits por carácter).
 *
 * Toma cada carácter del texto y lo convierte en su equivalente binario
 * de 8 bits, concatenando todos los bits en una sola cadena.
 *
 * Ejemplo:
 * - Entrada: "a"
 * - Salida: "01100001"
 *
 * @param text Texto ASCII de entrada (unsigned char*).
 * @param size Número de caracteres en el texto.
 * @return unsigned char* Cadena binaria resultante (memoria dinámica terminada en '\0').
 *
 * @note El usuario debe liberar la memoria con `delete[]` después de usar el resultado.
 */
unsigned char* textoAbinario(unsigned char* text, int size);

#endif // CONVERSION_BINARIO_H
