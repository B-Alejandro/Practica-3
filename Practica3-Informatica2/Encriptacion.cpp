#include <iostream>
#include "Encriptacion.h"
using namespace std;

// ===================== FUNCIONES AUXILIARES =====================

// Calcula la longitud de una cadena terminada en '\0'
int longitud(const unsigned char* texto) {
    int len = 0;
    while (texto[len] != '\0') len++;
    return len;
}

// Copia manualmente len caracteres de origen a destino
void copiar(unsigned char* destino, const unsigned char* origen, int len) {
    for (int i = 0; i < len; i++) destino[i] = origen[i];
}

// ===================== CONVERSIÓN BINARIO ↔ TEXTO =====================



// ===================== INVERSIÓN DE BITS =====================

// Invierte todos los bits ('0' ↔ '1')
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

// Invierte cada bloque de N bits dentro del arreglo
unsigned char* invertirCadaNBits(unsigned char* bloque, int len, int n) {
    unsigned char* res = new unsigned char[len + 1];
    copiar(res, bloque, len);
    res[len] = '\0';

    for (int i = 0; i < len; i += n) {
        for (int j = 0; j < n && i + j < len; j++) {
            res[i + j] = (res[i + j] == '0') ? '1' : '0';
        }
    }

    return res;
}

// ===================== ENCRIPTACIÓN DE BITS =====================

unsigned char* encriptarBits(const unsigned char* binary, int size, int semilla) {
    unsigned char* codificado = new unsigned char[size + 1];
    int pos = 0;
    unsigned char* anterior = nullptr;

    for (int i = 0; i < size; i += semilla) {
        int len = (i + semilla <= size) ? semilla : (size - i);

        // Copiar bloque actual
        unsigned char* bloque = new unsigned char[len + 1];
        copiar(bloque, binary + i, len);
        bloque[len] = '\0';

        unsigned char* procesado = nullptr;

        if (i == 0) {
            // Primer bloque → invertir bits
            procesado = invertirBits(bloque, len);
        } else {
            // Contar 1s y 0s del bloque anterior
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

        // Copiar bloque procesado al resultado final
        copiar(codificado + pos, procesado, len);
        pos += len;

        delete[] bloque;
        if (anterior) delete[] anterior;
        anterior = procesado;
    }

    codificado[pos] = '\0';
    if (anterior) delete[] anterior;

    return codificado;
}

// Desencriptación simétrica (mismo proceso)
unsigned char* desencriptarBits(const unsigned char* binary, int size, int semilla) {
    return encriptarBits(binary, size, semilla);
}

// ===================== VERIFICACIÓN =====================

// Verifica si una cadena contiene solo '0' y '1'
bool esBinario(const char* texto) {
    for (int i = 0; texto[i] != '\0'; i++) {
        if (texto[i] != '0' && texto[i] != '1') return false;
    }
    return true;
}

// ===================== FUNCIONES DE ALTO NIVEL =====================

/**
 * @brief Encripta un arreglo de líneas: texto → binario → encriptación
 * @param datos Arreglo de cadenas a encriptar (se modifica in-place)
 * @param numLineas Número de líneas en el arreglo
 * @param semilla Semilla para el algoritmo de encriptación
 */
void encriptarArchivo(char** datos, int numLineas, int semilla) {
    for (int i = 0; i < numLineas; i++) {
        unsigned char* texto = reinterpret_cast<unsigned char*>(datos[i]);
        int sizeTxt = longitud(texto);

        // 1. Convertir texto a binario
        unsigned char* binario = textoAbinario(texto, sizeTxt);
        int sizeBin = sizeTxt * 8;

        // 2. Encriptar el binario
        unsigned char* encriptado = encriptarBits(binario, sizeBin, semilla);

        // 3. Reemplazar la línea original
        delete[] datos[i];
        datos[i] = reinterpret_cast<char*>(encriptado);

        delete[] binario;
    }
}

/**
 * @brief Desencripta un arreglo de líneas: desencriptación → binario → texto
 * @param datos Arreglo de cadenas encriptadas (se modifica in-place)
 * @param numLineas Número de líneas en el arreglo
 * @param semilla Semilla usada en la encriptación
 */
void desencriptarArchivo(char** datos, int numLineas, int semilla) {
    for (int i = 0; i < numLineas; i++) {
        unsigned char* encriptado = reinterpret_cast<unsigned char*>(datos[i]);
        int sizeEnc = longitud(encriptado);

        // 1. Desencriptar
        unsigned char* binario = desencriptarBits(encriptado, sizeEnc, semilla);

        // 2. Convertir binario a texto ASCII
        unsigned char* textoASCII = binarioAtexto(binario, sizeEnc);

        // 3. Reemplazar la línea original
        delete[] datos[i];
        datos[i] = reinterpret_cast<char*>(textoASCII);

        delete[] binario;
    }
}

/**
 * @brief Verifica si los archivos están encriptados
 * @return true si ambos están encriptados, false si están en texto plano
 */
bool verificarEstadoEncriptacion(char** usuarios, char** admins) {
    if (!admins || !usuarios || !admins[0] || !usuarios[0]) {
        cerr << "Error: punteros nulos en verificación.\n";
        return false;
    }

    bool adminsEnc = esBinario(admins[0]);
    bool usuariosEnc = esBinario(usuarios[0]);

    if (adminsEnc && usuariosEnc) {
        return true; // Ambos encriptados
    } else if (!adminsEnc && !usuariosEnc) {
        return false; // Ambos en texto plano
    } else {
        cerr << "Advertencia: Estado inconsistente de encriptación.\n";
        return false;
    }
}
