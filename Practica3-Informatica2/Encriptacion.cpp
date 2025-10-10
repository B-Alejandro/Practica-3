#include <iostream>
#include "Encriptacion.h"
#include "UtilidadesCadena.h"

using namespace std;

// ============================================================
//  CONVERSIÓN BINARIO <-> TEXTO
// ============================================================

/**
 * @brief Convierte una cadena binaria ('0' y '1') a texto ASCII.
 *
 * @param binario Cadena binaria (unsigned char*).
 * @param len Longitud total (múltiplo de 8 recomendado).
 * @return Puntero a texto ASCII nuevo o nullptr si hay error.
 * @note El usuario debe liberar la memoria con `delete[]`.
 */
unsigned char* binarioAtexto(const unsigned char* binario, int len) {
    try {
        if (binario == nullptr || len <= 0)
            throw "Error: puntero nulo o longitud inválida en binarioAtexto.";

        int bitsValidos = (len / 8) * 8;
        if (bitsValidos == 0)
            throw "Error: longitud no múltiplo de 8.";

        int numChars = bitsValidos / 8;
        unsigned char* texto = new unsigned char[numChars + 1];

        for (int i = 0; i < numChars; i++) {
            unsigned char c = 0;
            for (int j = 0; j < 8; j++) {
                if (binario[i * 8 + j] != '0' && binario[i * 8 + j] != '1')
                    throw "Error: carácter no binario detectado.";
                c = (c << 1) | (binario[i * 8 + j] - '0');
            }
            texto[i] = c;
        }

        texto[numChars] = '\0';
        return texto;
    } catch (const char* msg) {
        cerr << "[Excepción] " << msg << endl;
        return nullptr;
    }
}

/**
 * @brief Convierte texto ASCII a su representación binaria.
 *
 * @param text Texto ASCII.
 * @param size Número de caracteres.
 * @return Cadena binaria nueva o nullptr si hay error.
 */
unsigned char* textoAbinario(unsigned char* text, int size) {
    try {
        if (text == nullptr || size <= 0)
            throw "Error: texto nulo o tamaño inválido.";

        unsigned char* resultado = new unsigned char[size * 8 + 1];
        for (int i = 0; i < size; i++) {
            unsigned char c = text[i];
            for (int j = 7; j >= 0; j--)
                resultado[i * 8 + (7 - j)] = ((c >> j) & 1) ? '1' : '0';
        }

        resultado[size * 8] = '\0';
        return resultado;
    } catch (const char* msg) {
        cerr << "[Excepción] " << msg << endl;
        return nullptr;
    }
}

// ============================================================
//  INVERSIÓN DE BITS
// ============================================================

/**
 * @brief Invierte todos los bits ('0' ↔ '1') de un bloque.
 */
unsigned char* invertirBits(const unsigned char* bloque, int len) {
    try {
        if (bloque == nullptr || len <= 0)
            throw "Error: bloque nulo o longitud inválida en invertirBits.";

        unsigned char* res = new unsigned char[len + 1];
        for (int i = 0; i < len; i++) {
            if (bloque[i] == '0') res[i] = '1';
            else if (bloque[i] == '1') res[i] = '0';
            else throw "Error: carácter no binario en invertirBits.";
        }
        res[len] = '\0';
        return res;
    } catch (const char* msg) {
        cerr << "[Excepción] " << msg << endl;
        return nullptr;
    }
}

/**
 * @brief Invierte los bits de un bloque en grupos de N bits.
 */
unsigned char* invertirCadaNBits(unsigned char* bloque, int len, int n) {
    try {
        if (bloque == nullptr || len <= 0 || n <= 0)
            throw "Error: parámetros inválidos en invertirCadaNBits.";

        unsigned char* res = new unsigned char[len + 1];
        copiarN(reinterpret_cast<char*>(res), reinterpret_cast<const char*>(bloque), len);
        res[len] = '\0';

        for (int i = 0; i < len; i += n) {
            for (int j = 0; j < n && i + j < len; j++) {
                if (res[i + j] != '0' && res[i + j] != '1')
                    throw "Error: carácter no binario detectado en invertirCadaNBits.";
                res[i + j] = (res[i + j] == '0') ? '1' : '0';
            }
        }

        return res;
    } catch (const char* msg) {
        cerr << "[Excepción] " << msg << endl;
        return nullptr;
    }
}

// ============================================================
//  ENCRIPTACIÓN Y DESENCRIPTACIÓN
// ============================================================

unsigned char* encriptarBits(const unsigned char* binary, int size, int semilla) {
    try {
        if (binary == nullptr || size <= 0 || semilla <= 0)
            throw "Error: parámetros inválidos en encriptarBits.";

        unsigned char* codificado = new unsigned char[size + 1];
        int pos = 0;
        unsigned char* anterior = nullptr;

        for (int i = 0; i < size; i += semilla) {
            int len = (i + semilla <= size) ? semilla : (size - i);
            unsigned char* bloque = new unsigned char[len + 1];
            copiarN(reinterpret_cast<char*>(bloque), reinterpret_cast<const char*>(binary + i), len);
            bloque[len] = '\0';

            unsigned char* procesado = nullptr;

            if (i == 0) {
                procesado = invertirBits(bloque, len);
            } else {
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

            copiarN(reinterpret_cast<char*>(codificado + pos),
                    reinterpret_cast<const char*>(procesado), len);
            pos += len;

            delete[] bloque;
            if (anterior) delete[] anterior;
            anterior = procesado;
        }

        codificado[pos] = '\0';
        if (anterior) delete[] anterior;
        return codificado;

    } catch (const char* msg) {
        cerr << "[Excepción] " << msg << endl;
        return nullptr;
    }
}

/**
 * @brief Desencripta (idéntico al proceso de encriptar).
 */
unsigned char* desencriptarBits(const unsigned char* binary, int size, int semilla) {
    return encriptarBits(binary, size, semilla);
}

/**
 * @brief Encripta un arreglo de cadenas de texto.
 */
void encriptarArchivo(char** datos, int numLineas, int semilla) {
    try {
        if (datos == nullptr || numLineas <= 0)
            throw "Error: parámetros inválidos en encriptarArchivo.";

        for (int i = 0; i < numLineas; i++) {
            unsigned char* texto = reinterpret_cast<unsigned char*>(datos[i]);
            int sizeTxt = longitud(datos[i]);
            unsigned char* binario = textoAbinario(texto, sizeTxt);
            if (!binario) continue;

            int sizeBin = sizeTxt * 8;
            unsigned char* encriptado = encriptarBits(binario, sizeBin, semilla);
            if (!encriptado) {
                delete[] binario;
                continue;
            }

            delete[] datos[i];
            datos[i] = reinterpret_cast<char*>(encriptado);
            delete[] binario;
        }
    } catch (const char* msg) {
        cerr << "[Excepción] " << msg << endl;
    }
}

/**
 * @brief Desencripta un arreglo de cadenas de texto.
 */
void desencriptarArchivo(char** datos, int numLineas, int semilla) {
    try {
        if (datos == nullptr || numLineas <= 0)
            throw "Error: parámetros inválidos en desencriptarArchivo.";

        for (int i = 0; i < numLineas; i++) {
            unsigned char* encriptado = reinterpret_cast<unsigned char*>(datos[i]);
            int sizeEnc = longitud(datos[i]);
            unsigned char* binario = desencriptarBits(encriptado, sizeEnc, semilla);
            if (!binario) continue;

            int bitsValidos = (sizeEnc / 8) * 8;
            unsigned char* textoASCII = binarioAtexto(binario, bitsValidos);
            if (!textoASCII) {
                delete[] binario;
                continue;
            }

            delete[] datos[i];
            datos[i] = reinterpret_cast<char*>(textoASCII);
            delete[] binario;
        }
    } catch (const char* msg) {
        cerr << "[Excepción] " << msg << endl;
    }
}

/**
 * @brief Verifica si los archivos están encriptados o no.
 */
bool verificarEstadoEncriptacion(char** usuarios, char** admins) {
    try {
        if (!admins || !usuarios || !admins[0] || !usuarios[0])
            throw "Error: punteros nulos detectados en verificación.";

        bool adminsEnc = esBinario(admins[0]);
        bool usuariosEnc = esBinario(usuarios[0]);

        if (adminsEnc && usuariosEnc) return true;
        if (!adminsEnc && !usuariosEnc) return false;

        cerr << "[Advertencia] Estado inconsistente de encriptación.\n";
        return false;
    } catch (const char* msg) {
        cerr << "[Excepción] " << msg << endl;
        return false;
    }
}
