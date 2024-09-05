#ifndef HASH
#define HASH

#include <stdio.h>
#include <stdlib.h>

// Funci ón de hash de Jenkins (One-at-a-time)
unsigned int jenkinsHash (unsigned char *key, size_t len);

// Funcion para leer el contenido de un archivo y calcular el hash
unsigned int hashFile ( const char *filename);

#endif