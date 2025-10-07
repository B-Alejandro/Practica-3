#include "Encriptacion.h"
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

// ================================================================
// === Conversión entre binario y texto ASCII =====================
// ================================================================

string binarioAtexto(const string& binario) {
    if (binario.empty() || binario.size() % 8 != 0)
        return "";

    string texto;
    texto.reserve(binario.size() / 8);

    for (size_t i = 0; i < binario.size(); i += 8) {
        unsigned char c = 0;
        for (int j = 0; j < 8; j++) {
            c = (c << 1) | static_cast<unsigned char>(binario[i + j] - '0');
        }
        texto.push_back(static_cast<char>(c));
    }

    return texto;
}

string textoAbinario(const string& texto) {
    string resultado;
    resultado.reserve(texto.size() * 8);

    for (unsigned char c : texto) {
        for (int j = 7; j >= 0; j--) {
            resultado.push_back(((c >> j) & 1) ? '1' : '0');
        }
    }

    return resultado;
}

// ================================================================
// === Inversión de bits ==========================================
// ================================================================

string invertirBits(const string& binario) {
    string res = binario;
    for (char& c : res) {
        if (c == '0') c = '1';
        else if (c == '1') c = '0';
    }
    return res;
}

string invertirCadaNBits(const string& binario, int n) {
    string res = binario;
    for (size_t i = 0; i < res.size(); i += n) {
        for (int j = 0; j < n && i + j < res.size(); j++) {
            res[i + j] = (res[i + j] == '0') ? '1' : '0';
        }
    }
    return res;
}

// ================================================================
// === Encriptación / Desencriptación (por bits) ==================
// ================================================================

string encriptarBits(const string& binario, int semilla) {
    string codificado;
    codificado.reserve(binario.size());

    string anterior;

    for (size_t i = 0; i < binario.size(); i += semilla) {
        int len = (i + semilla <= binario.size()) ? semilla : static_cast<int>(binario.size() - i);
        string bloque = binario.substr(i, len);
        string procesado;

        if (i == 0) {
            procesado = invertirBits(bloque);
        } else {
            int unos = 0, ceros = 0;
            for (char c : anterior) {
                if (c == '1') unos++;
                else if (c == '0') ceros++;
            }

            if (unos == ceros)
                procesado = invertirBits(bloque);
            else if (ceros > unos)
                procesado = invertirCadaNBits(bloque, 2);
            else
                procesado = invertirCadaNBits(bloque, 3);
        }

        codificado += procesado;
        anterior = procesado;
    }

    return codificado;
}

string desencriptarBits(const string& binario, int semilla) {
    // El algoritmo es simétrico: aplicar la misma operación devuelve el original
    return encriptarBits(binario, semilla);
}

// ================================================================
// === Helpers que operan sobre UNA cadena (sobrecargas útiles) =====
// ================================================================

/**
 * Encripta una cadena de texto (p. ej. "juan,clave,Nombre,5000 COP")
 * -> devuelve cadena binaria encriptada (solo '0' y '1').
 */
string encriptarCadena(const string& textoPlano, int semilla) {
    string binario = textoAbinario(textoPlano);
    return encriptarBits(binario, semilla);
}

/**
 * Desencripta cadena binaria encriptada a texto plano.
 */
string desencriptarCadena(const string& textoEncriptado, int semilla) {
    string binario = desencriptarBits(textoEncriptado, semilla);
    return binarioAtexto(binario);
}

// ================================================================
// === Implementaciones que el .h espera: operan sobre arreglos ===
// ================================================================

void encriptarArchivo(string* datos, int numLineas, int semilla) {
    if (!datos || numLineas <= 0) return;
    for (int i = 0; i < numLineas; ++i) {
        // si la línea ya parece binaria (solo 0/1), la dejamos como está
        bool esBin = true;
        if (datos[i].empty()) esBin = false;
        else {
            for (char c : datos[i]) { if (c != '0' && c != '1') { esBin = false; break; } }
        }
        if (!esBin) {
            datos[i] = encriptarCadena(datos[i], semilla);
        }
    }
}

void desencriptarArchivo(string* datos, int numLineas, int semilla) {
    if (!datos || numLineas <= 0) return;
    for (int i = 0; i < numLineas; ++i) {
        // Solo intentar desencriptar si la cadena está en binario (sólo 0/1 y múltiplo de 8)
        bool esBin = true;
        if (datos[i].empty()) esBin = false;
        else {
            for (char c : datos[i]) { if (c != '0' && c != '1') { esBin = false; break; } }
        }
        if (esBin && (datos[i].size() % 8 == 0)) {
            datos[i] = desencriptarCadena(datos[i], semilla);
        }
    }
}

/**
 * Verifica si los arreglos están encriptados. Se basa en el primer elemento de cada arreglo.
 * Retorna true si ambos parecen binarios, false si ambos parecen texto. Si hay inconsistencia,
 * muestra advertencia y devuelve false.
 */
bool verificarEstadoEncriptacion(const string* usuarios, const string* admins) {
    if (!usuarios || !admins) return false;

    auto esBinario = [](const string& s) {
        if (s.empty()) return false;
        for (char c : s) if (c != '0' && c != '1') return false;
        return true;
    };

    bool usuariosEnc = esBinario(usuarios[0]);
    bool adminsEnc   = esBinario(admins[0]);

    if (usuariosEnc && adminsEnc) return true;
    if (!usuariosEnc && !adminsEnc) return false;

    cerr << "Advertencia: Estado inconsistente de encriptación.\n";
    return false;
}
