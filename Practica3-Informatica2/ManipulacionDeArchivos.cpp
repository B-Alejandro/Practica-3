#include <iostream>
#include <fstream>
using namespace std;

/**
 * @brief Guarda el arreglo de usuarios en un archivo de texto plano.
 *
 * IMPORTANTE: Este archivo NO debe estar encriptado.
 * Se guarda en formato: cedula,clave,nombre,saldo COP
 */
void guardarUsuariosEnArchivo(char** usuarios, int numUsuarios, const char* ruta) {
    ofstream archivo(ruta, ios::trunc); // sobrescribe archivo
    if (!archivo) {
        cout << "❌ Error al abrir el archivo de usuarios.\n";
        return;
    }

    for (int i = 0; i < numUsuarios; i++) {
        archivo << usuarios[i] << "\n";
    }

    archivo.close();
    cout << "✅ Archivo guardado: " << numUsuarios << " usuarios" << endl;
}

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
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "❌ No se pudo abrir el archivo: " << rutaArchivo << std::endl;
        numLineas = 0;
        return nullptr;
    }

    // Verificar tamaño del archivo antes de cargarlo
    archivo.seekg(0, std::ios::end);
    long fileSize = archivo.tellg();
    archivo.seekg(0, std::ios::beg);

    cout << "📁 Leyendo archivo: " << rutaArchivo << " (" << fileSize << " bytes)" << endl;

    // Validación: archivos de usuarios no deberían superar 1 MB
    const long MAX_FILE_SIZE = 1000000; // 1 MB
    if (fileSize > MAX_FILE_SIZE) {
        cerr << "❌ ERROR CRÍTICO: Archivo demasiado grande (" << fileSize << " bytes)" << endl;
        cerr << "El archivo está corrupto o encriptado incorrectamente." << endl;
        cerr << "Tamaño máximo permitido: " << MAX_FILE_SIZE << " bytes" << endl;
        cerr << "\nSOLUCIÓN:" << endl;
        cerr << "1. Restaure el archivo desde un backup" << endl;
        cerr << "2. O cree un nuevo archivo con formato: cedula,clave,nombre,saldo COP" << endl;
        numLineas = 0;
        archivo.close();
        return nullptr;
    }

    // Contar cuántas líneas tiene el archivo
    numLineas = 0;
    std::string temp;
    while (std::getline(archivo, temp)) {
        if (temp.length() > 0) {  // Ignorar líneas vacías
            numLineas++;
        }
    }

    if (numLineas == 0) {
        cout << "⚠️  Advertencia: El archivo está vacío" << endl;
        archivo.close();
        return nullptr;
    }

    cout << "📊 Líneas detectadas: " << numLineas << endl;

    // Reservar arreglo de punteros a char*
    char** lineas = new char*[numLineas];

    // Volver al inicio del archivo
    archivo.clear();
    archivo.seekg(0, std::ios::beg);

    // Leer línea por línea y copiarlas
    int i = 0;
    while (std::getline(archivo, temp) && i < numLineas) {
        if (temp.length() > 0) {  // Solo procesar líneas no vacías
            // Reservar memoria para la línea (+1 para '\0')
            lineas[i] = new char[temp.size() + 1];
            std::copy(temp.begin(), temp.end(), lineas[i]);
            lineas[i][temp.size()] = '\0'; // terminador nulo
            i++;
        }
    }

    archivo.close();
    cout << "✅ Archivo cargado correctamente: " << i << " usuarios" << endl << endl;
    return lineas;
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
        cout << "⚠️  Contenido vacío" << endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        cout << contenido[i];
    }
    cout << endl << endl;
}
