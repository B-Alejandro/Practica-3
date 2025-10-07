#include <iostream>
#include <fstream>
#include <stdexcept>
using namespace std;

/**
 * @brief Lee un archivo y devuelve sus lineas como un arreglo dinamico de cadenas.
 *
 * Cada linea se guarda como un `char*` en un arreglo de punteros (`char**`).
 * Incluye validacion de tamaño para evitar cargar archivos corruptos.
 *
 * @param rutaArchivo Ruta del archivo a leer (cadena tipo C).
 * @param numLineas Referencia donde se almacenara el numero de lineas leidas.
 * @return char** Arreglo dinamico de lineas, o nullptr si ocurre un error.
 * @throws runtime_error Si el archivo no se puede abrir o esta corrupto.
 */
char** leerArchivoLineas(const char* rutaArchivo, int& numLineas) {
    try {
        ifstream archivo(rutaArchivo, ios::binary);
        if (!archivo.is_open()) {
            throw runtime_error("No se pudo abrir el archivo para lectura.");
        }

        archivo.seekg(0, ios::end);
        long fileSize = archivo.tellg();
        archivo.seekg(0, ios::beg);

        cout << "Leyendo archivo: " << rutaArchivo << " (" << fileSize << " bytes)" << endl;

        const long MAX_FILE_SIZE = 10000000; // 10 MB
        if (fileSize > MAX_FILE_SIZE) {
            archivo.close();
            throw runtime_error("Archivo demasiado grande o corrupto.");
        }

        numLineas = 0;
        string temp;
        while (getline(archivo, temp)) {
            if (!temp.empty()) numLineas++;
        }

        if (numLineas == 0) {
            archivo.close();
            throw runtime_error("El archivo esta vacio.");
        }

        char** lineas = new char*[numLineas];
        archivo.clear();
        archivo.seekg(0, ios::beg);

        int i = 0;
        while (getline(archivo, temp) && i < numLineas) {
            if (!temp.empty()) {
                lineas[i] = new char[temp.size() + 1];
                copy(temp.begin(), temp.end(), lineas[i]);
                lineas[i][temp.size()] = '\0';
                i++;
            }
        }

        archivo.close();
        cout << "Archivo cargado correctamente: " << i << " registros" << endl << endl;
        return lineas;
    } catch (const exception& e) {
        cerr << "ERROR en leerArchivoLineas(): " << e.what() << endl;
        numLineas = 0;
        return nullptr;
    }
}

/**
 * @brief Guarda un arreglo de lineas en un archivo.
 *
 * Escribe todas las lineas del arreglo en el archivo especificado,
 * sobrescribiendo su contenido anterior.
 *
 * @param rutaArchivo Ruta del archivo donde guardar.
 * @param lineas Arreglo de cadenas a guardar.
 * @param numLineas Numero de lineas en el arreglo.
 * @throws runtime_error Si no se puede abrir el archivo.
 */
void guardarArchivoLineas(const char* rutaArchivo, char** lineas, int numLineas) {
    try {
        ofstream archivo(rutaArchivo, ios::trunc | ios::binary);
        if (!archivo.is_open()) {
            throw runtime_error("No se pudo abrir el archivo para escritura.");
        }

        for (int i = 0; i < numLineas; i++) {
            archivo << lineas[i];
            if (i < numLineas - 1) archivo << "\n";
        }

        archivo.close();
        cout << "Archivo guardado: " << rutaArchivo << " (" << numLineas << " registros)" << endl;
    } catch (const exception& e) {
        cerr << "ERROR en guardarArchivoLineas(): " << e.what() << endl;
    }
}

/**
 * @brief Guarda el arreglo de usuarios en un archivo de texto plano.
 * @deprecated Use guardarArchivoLineas() en su lugar.
 */
void guardarUsuariosEnArchivo(char** usuarios, int numUsuarios, const char* ruta) {
    try {
        ofstream archivo(ruta, ios::trunc);
        if (!archivo.is_open()) {
            throw runtime_error("No se pudo abrir el archivo de usuarios.");
        }

        for (int i = 0; i < numUsuarios; i++) {
            archivo << usuarios[i] << "\n";
        }

        archivo.close();
        cout << "Archivo guardado: " << numUsuarios << " usuarios" << endl;
    } catch (const exception& e) {
        cerr << "ERROR en guardarUsuariosEnArchivo(): " << e.what() << endl;
    }
}

/**
 * @brief Muestra en consola el contenido de un arreglo de bytes.
 */
void mostrarContenido(unsigned char* contenido, int size) {
    try {
        if (!contenido) throw runtime_error("Contenido vacio.");
        for (int i = 0; i < size; ++i) cout << contenido[i];
        cout << endl << endl;
    } catch (const exception& e) {
        cerr << "ERROR en mostrarContenido(): " << e.what() << endl;
    }
}

/**
 * @brief Muestra en consola el contenido de un arreglo de lineas.
 */
void mostrarLineas(char** lineas, int numLineas) {
    try {
        if (!lineas) throw runtime_error("Arreglo vacio o no inicializado.");
        cout << "=== Contenido desencriptado ===" << endl;
        for (int i = 0; i < numLineas; i++) {
            cout << "[" << i << "] " << lineas[i] << endl;
        }
        cout << "================================" << endl << endl;
    } catch (const exception& e) {
        cerr << "ERROR en mostrarLineas(): " << e.what() << endl;
    }
}

