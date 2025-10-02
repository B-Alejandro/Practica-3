
#ifndef SISTEMA_H
#define SISTEMA_H

    /**
 * @brief Invierte cada bloque de n bits dentro de un bloque dado.
 *
 * Recorre el arreglo de bits y aplica inversión sobre cada grupo de n posiciones.
 * Si el tamaño no es múltiplo de n, el último grupo puede ser más pequeño.
 *
 * @param block Puntero al bloque de bits (caracteres '0' y '1').
 * @param size Tamaño del bloque en caracteres.
 * @param n Cantidad de bits por grupo a invertir.
 * @return Nuevo puntero a bloque con los bits invertidos. Debe liberarse con delete[].
 */
    unsigned char* invertirCadaNBits(const unsigned char* block, int size, int n);

/**
 * @brief Invierte todos los bits de un bloque.
 *
 * Cambia cada '0' por '1' y cada '1' por '0'.
 *
 * @param block Puntero al bloque de bits (caracteres '0' y '1').
 * @param size Tamaño del bloque en caracteres.
 * @return Nuevo puntero a bloque con los bits invertidos. Debe liberarse con delete[].
 */
unsigned char* invertirBits(const unsigned char* block, int size);

/**
 * @brief Encripta una cadena binaria usando una semilla.
 *
 * Divide el binario en bloques de tamaño igual a la semilla y aplica reglas:
 *  - Primer bloque: se invierte.
 *  - Bloques siguientes: se decide el método según cantidad de 0s y 1s en el bloque anterior.
 *
 * @param binary Puntero al arreglo de bits de entrada.
 * @param size Tamaño de la secuencia binaria en caracteres.
 * @param semilla Tamaño de los bloques a procesar.
 * @return Nuevo puntero a bloque encriptado. Debe liberarse con delete[].
 */
unsigned char* encriptarBits(const unsigned char* binary, int size, int semilla);

/**
 * @brief Crea un archivo de texto y escribe contenido en él.
 *
 * @param rutaArchivo Ruta al archivo a crear.
 * @param texto Puntero al contenido que se escribirá.
 * @param size Número de caracteres a escribir.
 * @return true si se pudo crear/escribir, false en caso de error.
 */
void guardarUsuariosEnArchivo(char** usuarios, int numUsuarios, const char* ruta);

/**
 * @brief Lee el contenido de un archivo como arreglo de caracteres.
 *
 * @param rutaArchivo Ruta del archivo a leer.
 * @param size Referencia donde se guarda el tamaño leído.
 * @return Puntero al contenido del archivo. Debe liberarse con delete[].
 */
unsigned char* leerArchivoACharArray(const char* rutaArchivo, int& size);

/**
 * @brief Muestra el contenido de un arreglo de caracteres en consola.
 *
 * @param contenido Puntero al arreglo de caracteres.
 * @param size Tamaño del arreglo.
 */
void mostrarContenido(unsigned char* contenido, int size);

/**
 * @brief Convierte una cadena binaria a texto ASCII.
 *
 * Toma grupos de 8 bits y los transforma a caracteres.
 *
 * @param texto Puntero a la cadena de bits (caracteres '0' y '1').
 * @param size Tamaño de la cadena binaria en caracteres.
 * @return Nuevo puntero al texto ASCII. Debe liberarse con delete[].
 */
unsigned char* binarioAtexto(unsigned char* texto, int size);

/**
 * @brief Convierte texto ASCII a representación binaria.
 *
 * Toma cada carácter del texto y lo representa con 8 bits.
 *
 * @param text Puntero al texto en ASCII.
 * @param size Tamaño del texto en caracteres.
 * @return Nuevo puntero con representación binaria (0s y 1s). Debe liberarse con delete[].
 */
unsigned char* textoAbinario(unsigned char* text, int size);

char** leerArchivoLineas(const char* rutaArchivo, int& numLineas) ;
#endif // SISTEMA_H

