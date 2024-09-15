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
/// @return 0 si el archivo existe, 1 en caso contrario.
int fileExists(char *fileName){
    struct stat st;
    if (stat(fileName, &st) == 0) {
        return 0;
    }
    return 1;
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
    char inputhash[11];
    char lineBuffer[100];
    long fileposition;
    FILE *stageFILE;

    if ((stageFILE=fopen(".ugit/stagingArea.txt","r+"))==NULL)
    {
        file_error(".ugit/stagingArea.txt", "Cree el archivo o ejecute el comando init");
        return 0;
    }

    for(int i=0; i<argc; i++){
        duplicated = 0;
        if(!fileExists(argv[i])){
            snprintf(inputhash, 11,"%.10u",hashFile(argv[i]));

            // Vemos si el archivo ya fue guardado
            rewind(stageFILE);

            // Leer línea por línea
            while (fgets(lineBuffer, sizeof(lineBuffer), stageFILE) != NULL) {
                fileposition = ftell(stageFILE);
                // Buscar si la línea contiene el nombre del archivo
                if (strncmp(lineBuffer, argv[i], strlen(argv[i])) == 0) {
                    if(fgets(lineBuffer, sizeof(lineBuffer), stageFILE) != NULL && !strncmp(inputhash, lineBuffer, 10)) // Leemos la linea de hash
                    {
                        printf("El archivo %s no ha recibido un cambio desde que se agrego al staging area\n", argv[i]);
                    }else{
                        fseek(stageFILE, fileposition, SEEK_SET);
                        fprintf(stageFILE, "%s\n", inputhash);
                        cont++;
                    }
                    duplicated = 1;
                    break;
                }
                else if(fgets(lineBuffer, sizeof(lineBuffer), stageFILE) == NULL) // Saltamos la linea de hash
                    break;
            }
            if(!duplicated)
            {
                fseek(stageFILE, 0, SEEK_END);
                fprintf(stageFILE, "%s\n%.10u\n", argv[i], hashFile(argv[i]));
                printf("Archivo %s agregado con exito\n", argv[i]);
                cont++;
            }
        }
        else
            printf("Archivo %s no existe\n", argv[i]);
    }

    return cont;
}

/// @brief Indica los archivos que están presentes en el StagingArea
/// @return -1 en caso de que no exista el directorio de .ugit, 0 si todo sale bien
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
        fseek(stageFILE, 11, SEEK_CUR); // Saltamos el hash correspondiente al archivo filename
    }
    return 0;
}