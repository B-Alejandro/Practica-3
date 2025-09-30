#include <iostream>
#include "Sistema.h"
using namespace std;

int main() {
    // Ruta donde se guardará el archivo binario
    char rutaDatos[] = "../../Datos/datos.bin";

    // Datos de prueba a guardar (abcd)
    unsigned char datosPrueba[] = {'a', 'b', 'c', 'd'};

    // Convertir texto a binario (cada char -> 8 bits)
    unsigned char* datosBinario = textoAbinario(datosPrueba, 4);

    // Guardar el archivo binario (como cadena de '0' y '1')
    if (crearArchivoConTexto(rutaDatos, datosBinario, 4 * 8)) {
        cout << "Archivo datos.bin creado correctamente.\n";
    } else {
        cerr << "Error: no se pudo crear el archivo.\n";
        delete[] datosBinario;
        return 1;
    }

    // Leer archivo
    int size = 0;
    unsigned char* data = leerArchivoACharArray(rutaDatos, size);

    if (data != nullptr && size > 0) {
        cout << "\n\n----- Contenido del archivo leído -----\n\n";
        mostrarContenido(data, size);

        delete[] data; // liberar memoria
    } else {
        cerr << "Error: no se pudo leer el archivo o está vacío.\n";
    }

    // Liberar binario generado
    delete[] datosBinario;

    return 0;
}
