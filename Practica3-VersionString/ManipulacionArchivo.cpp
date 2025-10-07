#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
using namespace std;

/**
 * @brief Lee un archivo y devuelve sus líneas como un arreglo dinámico de strings.
 *
 * Cada línea se guarda como un `std::string` dentro de un arreglo `string*`.
 * Incluye validación de tamaño para evitar cargar archivos corruptos.
 *
 * @param rutaArchivo Ruta del archivo a leer.
 * @param numLineas Referencia donde se almacenará el número de líneas leídas.
 * @return string* Arreglo dinámico de líneas, o nullptr si ocurre un error.
 * @throws runtime_error Si el archivo no se puede abrir o está corrupto.
 */
string* leerArchivoLineas(const string& rutaArchivo, int& numLineas) {
    try {
        ifstream archivo(rutaArchivo, ios::binary);
        if (!archivo.is_open()) {
            throw runtime_error("No se pudo abrir el archivo para lectura.");
        }

        archivo.seekg(0, ios::end);
        long fileSize = archivo.tellg();
        archivo.seekg(0, ios::beg);

        cout << "Leyendo archivo: " << rutaArchivo << " (" << fileSize << " bytes)" << endl;

        const long MAX_FILE_SIZE = 10'000'000; // 10 MB
        if (fileSize > MAX_FILE_SIZE) {
            throw runtime_error("Archivo demasiado grande o corrupto.");
        }

        // Primera pasada: contar líneas no vacías
        numLineas = 0;
        string temp;
        while (getline(archivo, temp)) {
            if (!temp.empty()) numLineas++;
        }

        if (numLineas == 0) {
            throw runtime_error("El archivo está vacío.");
        }

        // Segunda pasada: leer y almacenar líneas
        archivo.clear();
        archivo.seekg(0, ios::beg);

        string* lineas = new string[numLineas];
        int i = 0;
        while (getline(archivo, temp) && i < numLineas) {
            if (!temp.empty()) {
                lineas[i] = temp;
                i++;
            }
        }

        archivo.close();
        cout << "Archivo cargado correctamente: " << numLineas << " líneas" << endl << endl;
        return lineas;
    } catch (const exception& e) {
        cerr << "ERROR en leerArchivoLineas(): " << e.what() << endl;
        numLineas = 0;
        return nullptr;
    }
}

/**
 * @brief Guarda un arreglo de strings en un archivo de texto.
 *
 * Sobrescribe el archivo si ya existe.
 */
void guardarArchivoLineas(const string& rutaArchivo, string* lineas, int numLineas) {
    try {
        ofstream archivo(rutaArchivo, ios::trunc | ios::binary);
        if (!archivo.is_open()) {
            throw runtime_error("No se pudo abrir el archivo para escritura.");
        }

        for (int i = 0; i < numLineas; i++) {
            archivo << lineas[i];
            if (i < numLineas - 1) archivo << '\n';
        }

        archivo.close();
        cout << "Archivo guardado correctamente: " << numLineas << " líneas" << endl;
    } catch (const exception& e) {
        cerr << "ERROR en guardarArchivoLineas(): " << e.what() << endl;
    }
}

/**
 * @brief Muestra en consola el contenido de un arreglo de strings.
 */
void mostrarLineas(string* lineas, int numLineas) {
    try {
        if (!lineas) throw runtime_error("Arreglo vacío o no inicializado.");
        cout << "=== Contenido ===" << endl;
        for (int i = 0; i < numLineas; i++) {
            cout << "[" << i << "] " << lineas[i] << endl;
        }
        cout << "=================" << endl << endl;
    } catch (const exception& e) {
        cerr << "ERROR en mostrarLineas(): " << e.what() << endl;
    }
}

/**
 * @brief Libera la memoria del arreglo dinámico de strings.
 */
void liberarLineas(string*& lineas) {
    delete[] lineas;
    lineas = nullptr;
}
