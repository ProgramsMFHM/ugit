#include"folders.h"

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

/// @brief Esta función revisa la existencia de un archivo especifico.
/// @param fileName Cadena correspondiente al nombre del archivo a comprobar.
/// @return 1 si el archivo existe, 0 en caso contrario.
int fileExists(char *fileName){
    struct stat st;
    if (stat(fileName, &st) == 0) {
        return 1;
    }
    return 0;
}

/// @brief Esta función agrega archivos al staging area.
/// Esta función tiene en cuenta archivos duplicados para no volverlos a agregar al stage.
/// @param argc Indica la cantidad de archivos a agregar.
/// @param argv Es un arreglo que contiene los nombres de los archivos a agregar.
/// @return La cantidad de archivos agregados exitosamente.
int addFiles(int argc, char* argv[]){
    if(!folderExists(".ugit"))
        return -1;

    int duplicated = 0;
    int cont = 0;
    char fileName[30];
    FILE *stageFILE;

    if ((stageFILE=fopen(".ugit/stagingArea.txt","a+"))==NULL)
        return 0;

    for(int i=0; i<argc; i++){
        if(fileExists(argv[i])){
            duplicated = 0;
            rewind(stageFILE);
            while(!feof(stageFILE) && !duplicated){
                fscanf(stageFILE, "%s", fileName);
                if(!strcmp(fileName, argv[i])){
                    printf("Archivo %s ya esta en el staging area\n", argv[i]);
                    duplicated = 1;
                }
            }
            if(!duplicated)
            {
                fseek(stageFILE, 0, SEEK_END);
                fprintf(stageFILE, "%s\n", argv[i]);
                printf("Archivo %s agregado con exito\n", argv[i]);
                cont++;
            }
        }
        else
            printf("Archivo %s no existe\n", argv[i]);
    }

    return cont;
}

int stageStatus(){
    if(!folderExists(".ugit"))
        return -1;

    char filename[30];
    FILE *stageFILE;

    if ((stageFILE=fopen(".ugit/stagingArea.txt","r+"))==NULL)
        return 0;

    printf("Los siguientes archivos seran commiteados al usar el comando commit: \n");


    while(fscanf(stageFILE, "%s", filename)==1){
        printf("\t%s\n",filename);
    }
    return 0;
}