#include "Encriptacion.h"
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// ================================================================
// === Conversión entre binario y texto ASCII =====================
// ================================================================

/**
 * @brief Convierte una cadena binaria en texto ASCII.
 *
 * @param binario Cadena de bits ('0' y '1') a convertir.
 * @return string Texto ASCII resultante.
 *
 * @throw const char* Si la cadena está vacía, su longitud no es múltiplo de 8
 *        o contiene caracteres inválidos.
 */
string binarioAtexto(const string& binario) {
    try {
        if (binario.empty())
            throw "Error: cadena binaria vacía al convertir a texto.";
        if (binario.size() % 8 != 0)
            throw "Error: longitud binaria no es múltiplo de 8.";

        string texto;
        texto.reserve(binario.size() / 8);

        for (size_t i = 0; i < binario.size(); i += 8) {
            unsigned char c = 0;
            for (int j = 0; j < 8; j++) {
                char bit = binario[i + j];
                if (bit != '0' && bit != '1')
                    throw "Error: caracter inválido en cadena binaria.";
                c = (c << 1) | static_cast<unsigned char>(bit - '0');
            }
            texto.push_back(static_cast<char>(c));
        }

        return texto;
    } catch (const char* msg) {
        cerr << "[Error] " << msg << endl;
        return "";
    }
}

/**
 * @brief Convierte un texto ASCII a su representación binaria.
 *
 * @param texto Texto plano a convertir.
 * @return string Cadena binaria resultante.
 *
 * @throw const char* Si el texto está vacío.
 */
string textoAbinario(const string& texto) {
    try {
        if (texto.empty())
            throw "Error: texto vacío al convertir a binario.";

        string resultado;
        resultado.reserve(texto.size() * 8);

        for (unsigned char c : texto) {
            for (int j = 7; j >= 0; j--) {
                resultado.push_back(((c >> j) & 1) ? '1' : '0');
            }
        }

        return resultado;
    } catch (const char* msg) {
        cerr << "[Error] " << msg << endl;
        return "";
    }
}

// ================================================================
// === Inversión de bits ==========================================
// ================================================================

/**
 * @brief Invierte todos los bits de una cadena ('0' ↔ '1').
 *
 * @param binario Cadena binaria de entrada.
 * @return string Cadena resultante con los bits invertidos.
 *
 * @throw const char* Si hay caracteres distintos de '0' y '1'.
 */
string invertirBits(const string& binario) {
    try {
        string res = binario;
        for (char& c : res) {
            if (c == '0') c = '1';
            else if (c == '1') c = '0';
            else throw "Error: caracter inválido en invertirBits.";
        }
        return res;
    } catch (const char* msg) {
        cerr << "[Error] " << msg << endl;
        return "";
    }
}

/**
 * @brief Invierte los bits de una cadena en bloques de tamaño n.
 *
 * @param binario Cadena binaria a procesar.
 * @param n Tamaño de bloque para invertir bits.
 * @return string Cadena resultante.
 *
 * @throw const char* Si n <= 0 o hay caracteres inválidos.
 */
string invertirCadaNBits(const string& binario, int n) {
    try {
        if (n <= 0)
            throw "Error: tamaño de bloque de inversión inválido.";

        string res = binario;
        for (size_t i = 0; i < res.size(); i += n) {
            for (int j = 0; j < n && i + j < res.size(); j++) {
                if (res[i + j] != '0' && res[i + j] != '1')
                    throw "Error: caracter inválido durante inversión por bloques.";
                res[i + j] = (res[i + j] == '0') ? '1' : '0';
            }
        }
        return res;
    } catch (const char* msg) {
        cerr << "[Error] " << msg << endl;
        return "";
    }
}

// ================================================================
// === Encriptación / Desencriptación (por bits) ==================
// ================================================================

/**
 * @brief Encripta una cadena binaria usando una semilla de bloques.
 *
 * @param binario Cadena binaria de entrada.
 * @param semilla Tamaño de bloque para aplicar inversión condicional.
 * @return string Cadena encriptada.
 *
 * @throw const char* Si la semilla es inválida o la cadena está vacía.
 */
string encriptarBits(const string& binario, int semilla) {
    try {
        if (semilla <= 0)
            throw "Error: semilla inválida (debe ser > 0).";
        if (binario.empty())
            throw "Error: cadena binaria vacía en encriptarBits.";

        string codificado;
        codificado.reserve(binario.size());
        string anterior;

        for (size_t i = 0; i < binario.size(); i += semilla) {
            int len = (i + semilla <= binario.size())
            ? semilla
            : static_cast<int>(binario.size() - i);

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
    } catch (const char* msg) {
        cerr << "[Error] " << msg << endl;
        return "";
    }
}

/**
 * @brief Desencripta una cadena binaria. Es simétrico a encriptarBits().
 *
 * @param binario Cadena encriptada.
 * @param semilla Semilla usada durante la encriptación.
 * @return string Cadena binaria original.
 */
string desencriptarBits(const string& binario, int semilla) {
    return encriptarBits(binario, semilla);
}

// ================================================================
// === Encriptar / Desencriptar cadenas ===========================
// ================================================================

/**
 * @brief Encripta una cadena de texto plano.
 *
 * @param textoPlano Texto original a encriptar.
 * @param semilla Semilla de encriptación.
 * @return string Texto encriptado en binario.
 */
string encriptarCadena(const string& textoPlano, int semilla) {
    try {
        if (textoPlano.empty())
            throw "Error: texto vacío en encriptarCadena.";

        string binario = textoAbinario(textoPlano);
        return encriptarBits(binario, semilla);
    } catch (const char* msg) {
        cerr << "[Error] " << msg << endl;
        return "";
    }
}

/**
 * @brief Desencripta una cadena binaria a texto ASCII legible.
 *
 * @param textoEncriptado Cadena en binario encriptado.
 * @param semilla Semilla de desencriptación.
 * @return string Texto plano desencriptado.
 *
 * @throw const char* Si el texto está vacío o los caracteres resultantes son ilegibles.
 */
string desencriptarCadena(const string& textoEncriptado, int semilla) {
    try {
        if (textoEncriptado.empty())
            throw "Error: texto encriptado vacío.";

        string binario = desencriptarBits(textoEncriptado, semilla);
        string texto = binarioAtexto(binario);

        int ilegibles = 0;
        for (unsigned char c : texto) {
            if (!isprint(c) && c != '\n' && c != '\r' && c != '\t')
                ilegibles++;
        }

        if (ilegibles > texto.size() / 2)
            throw "Advertencia: el texto desencriptado parece corrupto o no legible.";

        return texto;
    } catch (const char* msg) {
        cerr << "[Error] " << msg << endl;
        return "";
    }
}

// ================================================================
// === Implementaciones que el .h espera: sobre arreglos ==========
// ================================================================

/**
 * @brief Encripta cada línea de un arreglo de texto.
 *
 * @param datos Arreglo de cadenas.
 * @param numLineas Número de líneas a procesar.
 * @param semilla Semilla de encriptación.
 *
 * @throw const char* Si el puntero o el número de líneas es inválido.
 */
void encriptarArchivo(string* datos, int numLineas, int semilla) {
    try {
        if (!datos)
            throw "Error: puntero nulo en encriptarArchivo.";
        if (numLineas <= 0)
            throw "Error: número de líneas inválido.";

        for (int i = 0; i < numLineas; ++i) {
            if (datos[i].empty()) continue;

            bool esBin = true;
            for (char c : datos[i])
                if (c != '0' && c != '1') { esBin = false; break; }

            if (!esBin) {
                try {
                    datos[i] = encriptarCadena(datos[i], semilla);
                } catch (const char* msg) {
                    cerr << "Error en línea " << i << ": " << msg << endl;
                }
            }
        }
    } catch (const char* msg) {
        cerr << "[Error] " << msg << endl;
    }
}

/**
 * @brief Desencripta cada línea binaria de un arreglo de texto.
 *
 * @param datos Arreglo de cadenas (binario).
 * @param numLineas Número de líneas.
 * @param semilla Semilla usada en la encriptación.
 *
 * @throw const char* Si los punteros o parámetros son inválidos.
 */
void desencriptarArchivo(string* datos, int numLineas, int semilla) {
    try {
        if (!datos)
            throw "Error: puntero nulo en desencriptarArchivo.";
        if (numLineas <= 0)
            throw "Error: número de líneas inválido.";

        for (int i = 0; i < numLineas; ++i) {
            if (datos[i].empty()) continue;

            bool esBin = true;
            for (char c : datos[i])
                if (c != '0' && c != '1') { esBin = false; break; }

            if (esBin && (datos[i].size() % 8 == 0)) {
                try {
                    datos[i] = desencriptarCadena(datos[i], semilla);
                } catch (const char* msg) {
                    cerr << "Error en línea " << i << ": " << msg << endl;
                }
            }
        }
    } catch (const char* msg) {
        cerr << "[Error] " << msg << endl;
    }
}

/**
 * @brief Verifica si los arreglos de usuarios y admins están encriptados.
 *
 * @param usuarios Arreglo de usuarios.
 * @param admins Arreglo de administradores.
 * @return true Si ambos están en binario.
 * @return false Si ambos están en texto.
 *
 * @throw const char* Si hay inconsistencia entre los dos o punteros nulos.
 */
bool verificarEstadoEncriptacion(const string* usuarios, const string* admins) {
    try {
        if (!usuarios || !admins)
            throw "Error: punteros nulos al verificar estado de encriptación.";

        auto esBinario = [](const string& s) {
            if (s.empty()) return false;
            for (char c : s)
                if (c != '0' && c != '1') return false;
            return true;
        };

        bool usuariosEnc = esBinario(usuarios[0]);
        bool adminsEnc   = esBinario(admins[0]);

        if (usuariosEnc && adminsEnc) return true;
        if (!usuariosEnc && !adminsEnc) return false;

        throw "Estado inconsistente: un archivo parece binario y el otro no.";
    } catch (const char* msg) {
        cerr << "[Error] " << msg << endl;
        return false;
    }
}
