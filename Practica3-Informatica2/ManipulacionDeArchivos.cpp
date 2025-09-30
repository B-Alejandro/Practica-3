
#include <iostream>
#include <fstream>
    using namespace std;

/**
 * @brief Crea un archivo y escribe un texto dentro de él.
 *
 * Esta función abre (o crea si no existe) un archivo en modo binario
 * y escribe en él el contenido de un arreglo de bytes.
 *
 * - Si el archivo ya existe, será sobrescrito.
 * - Si no se puede abrir o crear, se muestra un mensaje de error en consola.
 *
 * @param rutaArchivo Ruta del archivo a crear o sobrescribir (cadena tipo C).
 * @param texto Puntero al arreglo de bytes a escribir.
 * @param size Número de bytes a escribir en el archivo.
 * @return true si el archivo se creó y escribió correctamente, false en caso de error.
 */
bool crearArchivoConTexto(const char* rutaArchivo, unsigned char* texto, int size) {
    // Abrir archivo en modo binario (crea o sobrescribe)
    ofstream archivo(rutaArchivo, ios::binary);

    // Validar apertura
    if (!archivo.is_open()) {
        cerr << "No se pudo crear o abrir el archivo." << endl;
        return false;
    }

    // Escribir contenido en el archivo
    archivo.write(reinterpret_cast<const char*>(texto), size);

    // Cerrar archivo
    archivo.close();

    return true;
}

/**
 * @brief Lee un archivo y devuelve su contenido como un arreglo dinámico.
 *
 * Abre un archivo en modo binario, obtiene su tamaño y lo carga
 * completamente en memoria. El arreglo devuelto incluye un carácter
 * nulo adicional (`'\0'`) al final para permitir imprimirlo como string.
 *
 * @note El usuario es responsable de liberar la memoria con `delete[]`.
 *
 * @param rutaArchivo Ruta del archivo a leer (cadena tipo C).
 * @param size Referencia donde se almacenará el tamaño del archivo leído.
 * @return unsigned char* Puntero al contenido leído, o nullptr si ocurre un error.
 */

unsigned char* leerArchivoACharArray(const char* rutaArchivo, int& size) {
    std::ifstream archivo(rutaArchivo, std::ios::binary);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
        size = 0;
        return nullptr;
    }

    // Primero contar los caracteres
    size = 0;
    char c;
    while (archivo.get(c)) {
        size++;
    }

    // Reservar memoria (+1 para '\0')
    unsigned char* buffer = new unsigned char[size + 1];

    // Volvemos al inicio del archivo
    archivo.clear();
    archivo.seekg(0, std::ios::beg);

    // Leer caracter por caracter y guardarlo en el buffer
    int i = 0;
    while (archivo.get(c)) {
        buffer[i++] = static_cast<unsigned char>(c);
    }

    buffer[size] = '\0'; // terminador nulo
    archivo.close();
    return buffer;
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
