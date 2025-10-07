#include <iostream>
#include "Encriptacion.h"
#include "UtilidadesCadena.h"

using namespace std;

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


// ===================== INVERSIÓN DE BITS =====================

unsigned char* invertirBits(const unsigned char* bloque, int len) {
    unsigned char* res = new unsigned char[len + 1];
    for (int i = 0; i < len; i++) {
        if (bloque[i] == '0') res[i] = '1';
        else if (bloque[i] == '1') res[i] = '0';
        else res[i] = bloque[i];
    }
    res[len] = '\0';
    return res;
}

unsigned char* invertirCadaNBits(unsigned char* bloque, int len, int n) {
    unsigned char* res = new unsigned char[len + 1];
    copiarN(reinterpret_cast<char*>(res), reinterpret_cast<const char*>(bloque), len);
    res[len] = '\0';

    for (int i = 0; i < len; i += n) {
        for (int j = 0; j < n && i + j < len; j++) {
            res[i + j] = (res[i + j] == '0') ? '1' : '0';
        }
    }

    return res;
}

// ===================== ENCRIPTACIÓN =====================

unsigned char* encriptarBits(const unsigned char* binary, int size, int semilla) {
    unsigned char* codificado = new unsigned char[size + 1];
    int pos = 0;
    unsigned char* anterior = nullptr;

    for (int i = 0; i < size; i += semilla) {
        int len = (i + semilla <= size) ? semilla : (size - i);
        unsigned char* bloque = new unsigned char[len + 1];
        copiarN(reinterpret_cast<char*>(bloque), reinterpret_cast<const char*>(binary + i), len);
        bloque[len] = '\0';

        unsigned char* procesado = nullptr;
        if (i == 0)
            procesado = invertirBits(bloque, len);
        else {
            int unos = 0, ceros = 0;
            for (int j = 0; anterior[j] != '\0'; j++) {
                if (anterior[j] == '1') unos++;
                else if (anterior[j] == '0') ceros++;
            }

            if (unos == ceros)
                procesado = invertirBits(bloque, len);
            else if (ceros > unos)
                procesado = invertirCadaNBits(bloque, len, 2);
            else
                procesado = invertirCadaNBits(bloque, len, 3);
        }

        copiarN(reinterpret_cast<char*>(codificado + pos), reinterpret_cast<const char*>(procesado), len);
        pos += len;

        delete[] bloque;
        if (anterior) delete[] anterior;
        anterior = procesado;
    }

    codificado[pos] = '\0';
    if (anterior) delete[] anterior;

    return codificado;
}

unsigned char* desencriptarBits(const unsigned char* binary, int size, int semilla) {
    return encriptarBits(binary, size, semilla);
}

void encriptarArchivo(char** datos, int numLineas, int semilla) {
    for (int i = 0; i < numLineas; i++) {
        unsigned char* texto = reinterpret_cast<unsigned char*>(datos[i]);
        int sizeTxt = longitud(datos[i]);
        unsigned char* binario = textoAbinario(texto, sizeTxt);
        int sizeBin = sizeTxt * 8;
        unsigned char* encriptado = encriptarBits(binario, sizeBin, semilla);
        delete[] datos[i];
        datos[i] = reinterpret_cast<char*>(encriptado);
        delete[] binario;
    }
}

void desencriptarArchivo(char** datos, int numLineas, int semilla) {
    for (int i = 0; i < numLineas; i++) {
        unsigned char* encriptado = reinterpret_cast<unsigned char*>(datos[i]);
        int sizeEnc = longitud(datos[i]);
        unsigned char* binario = desencriptarBits(encriptado, sizeEnc, semilla);
        int bitsValidos = (sizeEnc / 8) * 8;
        unsigned char* textoASCII = binarioAtexto(binario, bitsValidos);
        delete[] datos[i];
        datos[i] = reinterpret_cast<char*>(textoASCII);
        delete[] binario;
    }
}

bool verificarEstadoEncriptacion(char** usuarios, char** admins) {
    if (!admins || !usuarios || !admins[0] || !usuarios[0]) {
        cerr << "Error: punteros nulos en verificación.\n";
        return false;
    }
    bool adminsEnc = esBinario(admins[0]);
    bool usuariosEnc = esBinario(usuarios[0]);
    if (adminsEnc && usuariosEnc) return true;
    if (!adminsEnc && !usuariosEnc) return false;
    cerr << "Advertencia: Estado inconsistente de encriptación.\n";
    return false;
}
