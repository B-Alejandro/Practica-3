
#include <iostream>
#include <fstream>
    using namespace std;

void guardarUsuariosEnArchivo(char** usuarios, int numUsuarios, const char* ruta) {
    ofstream archivo(ruta, ios::trunc); // sobrescribe archivo
    if (!archivo) {
        cout << "Error al abrir el archivo de usuarios.\n";
        return;
    }

    for (int i = 0; i < numUsuarios; i++) {
        archivo << usuarios[i] << "\n";  // cada línea en formato cedula,clave,nombre,saldo COP
    }

    archivo.close();
}
/**
 * @brief Lee un archivo y devuelve sus líneas como un arreglo dinámico de cadenas.
 *
 * Cada línea se guarda como un `char*` en un arreglo de punteros (`char**`).
 *
 * @note El usuario es responsable de liberar la memoria con:
 *       primero cada `delete[] lineas[i]` y luego `delete[] lineas`.
 *
 * @param rutaArchivo Ruta del archivo a leer (cadena tipo C).
 * @param numLineas Referencia donde se almacenará el número de líneas leídas.
 * @return char** Arreglo dinámico de líneas, o nullptr si ocurre un error.
 */
char** leerArchivoLineas(const char* rutaArchivo, int& numLineas) {
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        numLineas = 0;
        return nullptr;
    }

    // Contar cuántas líneas tiene el archivo
    numLineas = 0;
    std::string temp;
    while (std::getline(archivo, temp)) {
        numLineas++;
    }

    if (numLineas == 0) {
        return nullptr;
    }

    // Reservar arreglo de punteros a char*
    char** lineas = new char*[numLineas];

    // Volver al inicio del archivo
    archivo.clear();
    archivo.seekg(0, std::ios::beg);

    // Leer línea por línea y copiarlas
    int i = 0;
    while (std::getline(archivo, temp)) {
        // Reservar memoria para la línea (+1 para '\0')
        lineas[i] = new char[temp.size() + 1];
        std::copy(temp.begin(), temp.end(), lineas[i]);
        lineas[i][temp.size()] = '\0'; // terminador nulo
        i++;
    }

    archivo.close();
    return lineas;
}

/**
 * @brief Muestra en consola el contenido de un arreglo de bytes.
 *
 * Recorre un arreglo de bytes y muestra:
 * - Los caracteres alfabéticos en minúscula directamente.
 * - Los demás caracteres se muestran como números enteros (su código ASCII).
 *
 * @param contenido Puntero al arreglo de bytes.
 * @param size Número de bytes en el arreglo.
 */
void mostrarContenido(unsigned char* contenido, int size) {
    for (int i = 0; i < size; ++i) {

            cout << contenido[i];
    }        // imprimir letras
    cout << endl << endl;
}
