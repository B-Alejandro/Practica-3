#include <iostream>
#include <fstream>
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
 * @throws const char* Si el archivo no se puede abrir o está corrupto.
 */
string* leerArchivoLineas(const string& rutaArchivo, int& numLineas) {
    try {
        ifstream archivo(rutaArchivo, ios::binary);
        if (!archivo.is_open()) {
            throw "No se pudo abrir el archivo para lectura.";
        }

        archivo.seekg(0, ios::end);
        long fileSize = archivo.tellg();
        archivo.seekg(0, ios::beg);

        cout << "Leyendo archivo: " << rutaArchivo << " (" << fileSize << " bytes)" << endl;

        const long MAX_FILE_SIZE = 10'000'000; // 10 MB
        if (fileSize > MAX_FILE_SIZE) {
            throw "Archivo demasiado grande o corrupto.";
        }

        // Primera pasada: contar líneas no vacías
        numLineas = 0;
        string temp;
        while (getline(archivo, temp)) {
            if (!temp.empty()) numLineas++;
        }

        if (numLineas == 0) {
            throw "El archivo está vacío.";
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
    }
    catch (const char* e) {
        cerr << "ERROR en leerArchivoLineas(): " << e << endl;
        numLineas = 0;
        return nullptr;
    }
    catch (...) {
        cerr << "ERROR desconocido en leerArchivoLineas()." << endl;
        numLineas = 0;
        return nullptr;
    }
}

/**
 * @brief Guarda un arreglo de strings en un archivo de texto.
 *
 * Sobrescribe el archivo si ya existe.
 *
 * @param rutaArchivo Ruta donde se guardará el archivo.
 * @param lineas Arreglo dinámico de líneas a guardar.
 * @param numLineas Número de líneas a escribir.
 * @throws const char* Si el archivo no se puede abrir para escritura.
 */
void guardarArchivoLineas(const string& rutaArchivo, string* lineas, int numLineas) {
    try {
        ofstream archivo(rutaArchivo, ios::trunc | ios::binary);
        if (!archivo.is_open()) {
            throw "No se pudo abrir el archivo para escritura.";
        }

        for (int i = 0; i < numLineas; i++) {
            archivo << lineas[i];
            if (i < numLineas - 1) archivo << '\n';
        }

        archivo.close();
        cout << "Archivo guardado correctamente: " << numLineas << " líneas" << endl;
    }
    catch (const char* e) {
        cerr << "ERROR en guardarArchivoLineas(): " << e << endl;
    }
    catch (...) {
        cerr << "ERROR desconocido en guardarArchivoLineas()." << endl;
    }
}

/**
 * @brief Muestra en consola el contenido de un arreglo de strings.
 *
 * @param lineas Arreglo dinámico de líneas a mostrar.
 * @param numLineas Número de líneas a imprimir.
 * @throws const char* Si el arreglo es nulo o no inicializado.
 */
void mostrarLineas(string* lineas, int numLineas) {
    try {
        if (!lineas) throw "Arreglo vacío o no inicializado.";
        cout << "=== Contenido ===" << endl;
        for (int i = 0; i < numLineas; i++) {
            cout << "[" << i << "] " << lineas[i] << endl;
        }
        cout << "=================" << endl << endl;
    }
    catch (const char* e) {
        cerr << "ERROR en mostrarLineas(): " << e << endl;
    }
    catch (...) {
        cerr << "ERROR desconocido en mostrarLineas()." << endl;
    }
}

/**
 * @brief Libera la memoria del arreglo dinámico de strings.
 *
 * @param lineas Referencia al puntero del arreglo a liberar.
 */
void liberarLineas(string*& lineas) {
    delete[] lineas;
    lineas = nullptr;
}
