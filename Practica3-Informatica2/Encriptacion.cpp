#include <iostream>
#include "Encriptacion.h"
#include "UtilidadesCadena.h"
#include "BinarioChar.h"
using namespace std;

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
