#include "hash.h"

// Función de hash de Jenkins (One-at-a-time)
unsigned int jenkinsHash(unsigned char *key, size_t len) {
    unsigned int hash = 0;
    for (size_t i = 0; i < len; i++) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

// Función para leer el contenido de un archivo y calcular el hash
unsigned int hashFile(const char *filename) {
    FILE *file = fopen(filename, "rb"); // Abrir el archivo en modo binario
    if (!file) {
        perror("No se puede abrir el archivo");
        exit(EXIT_FAILURE);
    }

    // Determinar el tamaño del archivo
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Leer el contenido del archivo
    unsigned char *buffer = (unsigned char *)malloc(fileSize * sizeof(unsigned char));
    if (!buffer) {
        perror("No se puede asignar memoria");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(buffer, sizeof(unsigned char), fileSize, file);
    fclose(file);

    // Calcular el hash del contenido
    unsigned int hash = jenkinsHash(buffer, fileSize);

    // Liberar la memoria del buffer
    free(buffer);

    return hash;
}
