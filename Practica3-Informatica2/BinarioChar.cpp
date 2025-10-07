
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
 * @param texto Cadena de bits (unsigned char*), debe tener longitud múltiplo de 8.
 * @param size Número total de bits en el arreglo (longitud de texto).
 * @return unsigned char* Texto ASCII resultante (memoria dinámica terminada en '\0').
 *
 * @note El usuario debe liberar la memoria con `delete[]` después de usar el resultado.
 */
unsigned char* binarioAtexto(const unsigned char* binario, int len) {
    // Asegurarse de usar múltiplo de 8
    int bitsValidos = (len / 8) * 8;
    if (bitsValidos == 0) return nullptr;

    int numChars = bitsValidos / 8;
    unsigned char* texto = new unsigned char[numChars + 1];

    for (int i = 0; i < numChars; i++) {
        unsigned char c = 0;
        for (int j = 0; j < 8; j++) {
            c = (c << 1) | (binario[i * 8 + j] - '0');
        }
        texto[i] = c;
    }
    texto[numChars] = '\0';
    return texto;
}

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
unsigned char* textoAbinario(unsigned char* text, int size) {
    // Reservar memoria para todos los bits (+1 para '\0')
    unsigned char* resultado = new unsigned char[size * 8 + 1];

    // Procesar cada carácter del texto
    for (int i = 0; i < size; i++) {
        unsigned char c = text[i];

        // Convertir cada bit del carácter
        for (int j = 7; j >= 0; j--) {
            // Extraer bit j y guardarlo como '0' o '1'
            resultado[i * 8 + (7 - j)] = ((c >> j) & 1) ? '1' : '0';
        }
    }

    // Terminar con '\0' para que sea string C válido
    resultado[size * 8] = '\0';
    return resultado;
}

