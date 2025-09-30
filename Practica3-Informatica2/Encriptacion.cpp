#include <iostream>
    using namespace std;

/**
 * @brief Invierte cada bloque de N bits dentro de una cadena binaria.
 *
 * Recorre el arreglo binario en bloques de tamaño `n` y cambia cada bit:
 * - '1' → '0'
 * - '0' → '1'
 *
 * Si el último bloque no tiene tamaño completo `n`, se invierte lo que alcance.
 *
 * @param block Cadena binaria de entrada (como unsigned char*).
 * @param size Número de bits en la cadena de entrada.
 * @param n Tamaño del bloque a invertir.
 * @return unsigned char* Nueva cadena con los bits invertidos (memoria dinámica).
 *
 * @note El usuario debe liberar la memoria con `delete[]` después de usar el resultado.
 */
unsigned char* invertirCadaNBits(const unsigned char* block, int size, int n) {
    // Crear copia del bloque para el resultado
    unsigned char* resultado = new unsigned char[size + 1];

    // Recorrer bloques de tamaño n
    for (int i = 0; i < size; i += n) {
        for (int j = 0; j < n && i + j < size; j++) {
            resultado[i + j] = (block[i + j] == '1') ? '0' : '1';
        }
    }

    // Finalizar con terminador nulo estilo C
    resultado[size] = '\0';
    return resultado;
}

/**
 * @brief Invierte todos los bits de una cadena binaria.
 *
 * Cambia cada bit de la cadena:
 * - '1' → '0'
 * - '0' → '1'
 *
 * @param block Cadena binaria de entrada (unsigned char*).
 * @param size Número de bits en la cadena de entrada.
 * @return unsigned char* Nueva cadena con bits invertidos (memoria dinámica).
 *
 * @note El usuario debe liberar la memoria con `delete[]` después de usar el resultado.
 */
unsigned char* invertirBits(const unsigned char* block, int size) {
    unsigned char* resultado = new unsigned char[size + 1];

    // Invertir bit por bit
    for (int i = 0; i < size; i++) {
        resultado[i] = (block[i] == '1') ? '0' : '1';
    }

    resultado[size] = '\0';
    return resultado;
}

/**
 * @brief Encripta una cadena binaria usando un esquema basado en bloques y semilla.
 *
 * El proceso divide la cadena en bloques de tamaño `semilla` y aplica reglas:
 * - Primer bloque: se invierten todos los bits.
 * - Bloques siguientes:
 *   - Si el bloque anterior tiene igual número de 1s y 0s → invertir todos los bits.
 *   - Si el bloque anterior tiene más ceros que unos → invertir cada 2 bits.
 *   - Si el bloque anterior tiene más unos que ceros → invertir cada 3 bits.
 *
 * @param binary Cadena binaria de entrada (unsigned char*).
 * @param size Número total de bits en la entrada.
 * @param semilla Tamaño de los bloques de procesamiento.
 * @return unsigned char* Cadena resultante encriptada (memoria dinámica).
 *
 * @note El usuario debe liberar la memoria con `delete[]` después de usar el resultado.
 */
unsigned char* encriptarBits(const unsigned char* binary, int size, int semilla) {
    // Cadena de salida
    unsigned char* codificado = new unsigned char[size + 1];
    int pos = 0;

    // "anterior" guarda el último bloque procesado
    unsigned char* anterior = nullptr;

    // Recorrer la entrada en bloques de longitud semilla
    for (int i = 0; i < size; i += semilla) {
        // Longitud real del bloque (el último puede ser más pequeño)
        int len = (i + semilla <= size) ? semilla : (size - i);

        // Copiar bloque actual en memoria nueva
        unsigned char* bloque = new unsigned char[len + 1];
        for (int k = 0; k < len; k++) {
            bloque[k] = binary[i + k];
        }
        bloque[len] = '\0';

        unsigned char* procesado = nullptr;

        if (i == 0) {
            // Primer bloque → invertir todos los bits
            procesado = invertirBits(bloque, len);
        } else {
            // Contar 1s y 0s en el bloque anterior procesado
            int unos = 0, ceros = 0;
            for (int j = 0; anterior[j] != '\0'; j++) {
                if (anterior[j] == '1') unos++;
                else ceros++;
            }

            // Decidir la operación según las reglas
            if (unos == ceros) {
                procesado = invertirBits(bloque, len);
            } else if (ceros > unos) {
                procesado = invertirCadaNBits(bloque, len, 2);
            } else {
                procesado = invertirCadaNBits(bloque, len, 3);
            }
        }

        // Copiar resultado procesado en la salida final
        for (int k = 0; procesado[k] != '\0'; k++) {
            codificado[pos++] = procesado[k];
        }

        // Liberar bloque temporal y anterior
        delete[] bloque;
        if (anterior) delete[] anterior;

        // Guardar el bloque procesado como "anterior" para la siguiente iteración
        anterior = procesado;
    }

    // Terminar cadena final con '\0'
    codificado[pos] = '\0';

    // Liberar el último "anterior"
    if (anterior) delete[] anterior;

    return codificado;
}

