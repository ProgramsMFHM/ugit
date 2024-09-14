#include "errors.h"

/// @brief Genera un error por pantalla y finaliza el proceso
/// @param error Cadena de texto representativa del error cometido
void fatal_error(char *error){
    printf("FALTAL ERROR: %s\n",error);
    exit(-1);
}

/// @brief Indica un error por consola por la falta de presencia de un directorio
/// @param folder Indica el nombre del directorio no encontrado
/// @param obs Indica algún comentario adicional para el mensaje por consola
void folder_error(char *folder, char *obs){
    printf("Directorio %s no existe. %s\n",folder, obs);
}


/// @brief Indica un error por consola por la falta de presencia de un archivo
/// @param file Indica el nombre del archivo no encontrado
/// @param obs Indica algún comentario adicional para el mensaje por consola
void file_error(char *file, char *obs){
    printf("Archivo %s no existe. %s\n", file, obs);
}