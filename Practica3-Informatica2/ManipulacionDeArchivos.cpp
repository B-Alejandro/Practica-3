#include <iostream>
#include <fstream>
using namespace std;

/**
 * @brief Lee un archivo y devuelve sus líneas como un arreglo dinámico de cadenas.
 *
 * Cada línea se guarda como un `char*` en un arreglo de punteros (`char**`).
 * Incluye validación de tamaño para evitar cargar archivos corruptos.
 *
 * @param rutaArchivo Ruta del archivo a leer (cadena tipo C).
 * @param numLineas Referencia donde se almacenará el número de líneas leídas.
 * @return char** Arreglo dinámico de líneas, o nullptr si ocurre un error.
 * @throws const char* Si el archivo no se puede abrir o está corrupto.
 */
char** leerArchivoLineas(const char* rutaArchivo, int& numLineas) {
    try {
        ifstream archivo(rutaArchivo, ios::binary);
        if (!archivo.is_open()) {
            throw "No se pudo abrir el archivo para lectura.";
        }

        archivo.seekg(0, ios::end);
        long fileSize = archivo.tellg();
        archivo.seekg(0, ios::beg);

        cout << "Leyendo archivo: " << rutaArchivo << " (" << fileSize << " bytes)" << endl;

        const long MAX_FILE_SIZE = 10000000; // 10 MB
        if (fileSize > MAX_FILE_SIZE) {
            archivo.close();
            throw "Archivo demasiado grande o corrupto.";
        }

        numLineas = 0;
        string temp;
        while (getline(archivo, temp)) {
            if (!temp.empty()) numLineas++;
        }

        if (numLineas == 0) {
            archivo.close();
            throw "El archivo está vacío.";
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
    }
    catch (const char* msg) {
        cerr << "ERROR en leerArchivoLineas(): " << msg << endl;
        numLineas = 0;
        return nullptr;
    }
}

/**
 * @brief Guarda un arreglo de líneas en un archivo.
 *
 * Escribe todas las líneas del arreglo en el archivo especificado,
 * sobrescribiendo su contenido anterior.
 *
 * @param rutaArchivo Ruta del archivo donde guardar.
 * @param lineas Arreglo de cadenas a guardar.
 * @param numLineas Número de líneas en el arreglo.
 * @throws const char* Si no se puede abrir el archivo.
 */
void guardarArchivoLineas(const char* rutaArchivo, char** lineas, int numLineas) {
    try {
        ofstream archivo(rutaArchivo, ios::trunc | ios::binary);
        if (!archivo.is_open()) {
            throw "No se pudo abrir el archivo para escritura.";
        }

        for (int i = 0; i < numLineas; i++) {
            archivo << lineas[i];
            if (i < numLineas - 1) archivo << "\n";
        }

        archivo.close();
        cout << "Archivo guardado: " << rutaArchivo << " (" << numLineas << " registros)" << endl;
    }
    catch (const char* msg) {
        cerr << "ERROR en guardarArchivoLineas(): " << msg << endl;
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
            throw "No se pudo abrir el archivo de usuarios.";
        }

        for (int i = 0; i < numUsuarios; i++) {
            archivo << usuarios[i] << "\n";
        }

        archivo.close();
        cout << "Archivo guardado: " << numUsuarios << " usuarios" << endl;
    }
    catch (const char* msg) {
        cerr << "ERROR en guardarUsuariosEnArchivo(): " << msg << endl;
    }
}

/**
 * @brief Muestra en consola el contenido de un arreglo de bytes.
 */
void mostrarContenido(unsigned char* contenido, int size) {
    try {
        if (!contenido) throw "Contenido vacío.";
        for (int i = 0; i < size; ++i) cout << contenido[i];
        cout << endl << endl;
    }
    catch (const char* msg) {
        cerr << "ERROR en mostrarContenido(): " << msg << endl;
    }
}

/**
 * @brief Muestra en consola el contenido de un arreglo de líneas.
 */
void mostrarLineas(char** lineas, int numLineas) {
    try {
        if (!lineas) throw "Arreglo vacío o no inicializado.";
        cout << "=== Contenido desencriptado ===" << endl;
        for (int i = 0; i < numLineas; i++) {
            cout << "[" << i << "] " << lineas[i] << endl;
        }
        cout << "================================" << endl << endl;
    }
    catch (const char* msg) {
        cerr << "ERROR en mostrarLineas(): " << msg << endl;
    }
}
