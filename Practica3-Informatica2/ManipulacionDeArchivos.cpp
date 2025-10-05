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
 */
char** leerArchivoLineas(const char* rutaArchivo, int& numLineas) {
    ifstream archivo(rutaArchivo, ios::binary);
    if (!archivo.is_open()) {
        cerr << "ERROR: No se pudo abrir el archivo: " << rutaArchivo << endl;
        numLineas = 0;
        return nullptr;
    }

    // Verificar tamaño del archivo antes de cargarlo
    archivo.seekg(0, ios::end);
    long fileSize = archivo.tellg();
    archivo.seekg(0, ios::beg);

    cout << "Leyendo archivo: " << rutaArchivo << " (" << fileSize << " bytes)" << endl;

    // Validación: archivos no deberían superar 10 MB
    const long MAX_FILE_SIZE = 10000000; // 10 MB (aumentado para datos encriptados)
    if (fileSize > MAX_FILE_SIZE) {
        cerr << "ERROR CRITICO: Archivo demasiado grande (" << fileSize << " bytes)" << endl;
        cerr << "El archivo esta corrupto." << endl;
        cerr << "Tamanio maximo permitido: " << MAX_FILE_SIZE << " bytes" << endl;
        cerr << "\nSOLUCION:" << endl;
        cerr << "1. Restaure el archivo desde un backup" << endl;
        cerr << "2. O cree un nuevo archivo con formato correcto" << endl;
        numLineas = 0;
        archivo.close();
        return nullptr;
    }

    // Contar cuántas líneas tiene el archivo
    numLineas = 0;
    string temp;
    while (getline(archivo, temp)) {
        if (temp.length() > 0) {  // Ignorar líneas vacías
            numLineas++;
        }
    }

    if (numLineas == 0) {
        cout << "ADVERTENCIA: El archivo esta vacio" << endl;
        archivo.close();
        return nullptr;
    }

    cout << "Lineas detectadas: " << numLineas << endl;

    // Reservar arreglo de punteros a char*
    char** lineas = new char*[numLineas];

    // Volver al inicio del archivo
    archivo.clear();
    archivo.seekg(0, ios::beg);

    // Leer línea por línea y copiarlas
    int i = 0;
    while (getline(archivo, temp) && i < numLineas) {
        if (temp.length() > 0) {  // Solo procesar líneas no vacías
            // Reservar memoria para la línea (+1 para '\0')
            lineas[i] = new char[temp.size() + 1];
            copy(temp.begin(), temp.end(), lineas[i]);
            lineas[i][temp.size()] = '\0'; // terminador nulo
            i++;
        }
    }

    archivo.close();
    cout << "Archivo cargado correctamente: " << i << " registros" << endl << endl;
    return lineas;
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
 */
void guardarArchivoLineas(const char* rutaArchivo, char** lineas, int numLineas) {
    ofstream archivo(rutaArchivo, ios::trunc | ios::binary);
    if (!archivo.is_open()) {
        cerr << "ERROR: No se pudo abrir el archivo para escribir: " << rutaArchivo << endl;
        return;
    }

    for (int i = 0; i < numLineas; i++) {
        archivo << lineas[i];
        if (i < numLineas - 1) {
            archivo << "\n";
        }
    }

    archivo.close();
    cout << "Archivo guardado: " << rutaArchivo << " (" << numLineas << " registros)" << endl;
}

/**
 * @brief Guarda el arreglo de usuarios en un archivo de texto plano.
 *
 * IMPORTANTE: Este archivo NO debe estar encriptado.
 * Se guarda en formato: cedula,clave,nombre,saldo COP
 *
 * @deprecated Use guardarArchivoLineas() en su lugar.
 */
void guardarUsuariosEnArchivo(char** usuarios, int numUsuarios, const char* ruta) {
    ofstream archivo(ruta, ios::trunc);
    if (!archivo) {
        cout << "ERROR: No se pudo abrir el archivo de usuarios." << endl;
        return;
    }

    for (int i = 0; i < numUsuarios; i++) {
        archivo << usuarios[i] << "\n";
    }

    archivo.close();
    cout << "Archivo guardado: " << numUsuarios << " usuarios" << endl;
}

/**
 * @brief Muestra en consola el contenido de un arreglo de bytes.
 *
 * Recorre un arreglo de bytes y muestra los caracteres directamente.
 *
 * @param contenido Puntero al arreglo de bytes.
 * @param size Número de bytes en el arreglo.
 */
void mostrarContenido(unsigned char* contenido, int size) {
    if (!contenido) {
        cout << "Contenido vacio" << endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        cout << contenido[i];
    }
    cout << endl << endl;
}

/**
 * @brief Muestra en consola el contenido de un arreglo de líneas.
 *
 * Útil para depuración: muestra cada línea numerada.
 *
 * @param lineas Arreglo de cadenas (char**).
 * @param numLineas Número de líneas en el arreglo.
 */
void mostrarLineas(char** lineas, int numLineas) {
    if (!lineas) {
        cout << "Arreglo vacio" << endl;
        return;
    }

    cout << "=== Contenido desencriptado ===" << endl;
    for (int i = 0; i < numLineas; i++) {
        cout << "[" << i << "] " << lineas[i] << endl;
    }
    cout << "================================" << endl << endl;
}
