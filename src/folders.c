#include "folders.h"
#include <sys/stat.h>

/// @brief Esta función revisa la existencia de un directorio.
/// @param folderName Cadena correspondiente al nombre del directorio a comprobar.
/// @return 1 si el directorio existe, 0 en caso contrario.
int folderExists(char *folderName) {
    struct stat st;
    if (stat(folderName, &st) == 0) {
        return 1;
    }
    return 0;
}