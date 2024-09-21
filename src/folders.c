/// \file folders.c
/// \brief Funciones relacionadas con manejo directorios y archivos
#include"folders.h"

/// @brief Esta función revisa la existencia de un directorio.
/// @param folderName Cadena correspondiente al nombre del directorio a comprobar.
/// @return 0 si el directorio existe, 1 en caso contrario.
int folderExists(char *folderName) {
    struct stat st;
    return stat(folderName, &st);
}

/// @brief Esta función revisa la existencia de un archivo especifico.
/// @param fileName Cadena correspondiente al nombre del archivo a comprobar.
/// @return 0 si el archivo existe, 1 en caso contrario.
int fileExists(char *fileName){
    struct stat st;
    return stat(fileName, &st);
}

/// @brief Esta función agrega archivos al staging area.
/// Esta función tiene en cuenta archivos duplicados para no volverlos a agregar al stage así como no poder agregar archivos si no han sido modificados desde su última agregación al StagingArea.
/// @param argc Indica la cantidad de archivos a agregar.
/// @param argv Es un arreglo que contiene los nombres de los archivos a agregar.
/// @return La cantidad de archivos agregados exitosamente.
int addFiles(int argc, char* argv[]){
    if(folderExists("./.ugit"))
    {
        printError(101, ".ugit","Se recomienda ejecutar comando init");
        return -1;
    }
    int duplicated = 0;
    int cont = 0;
    char inputhash[11];
    char lineBuffer[100];
    FILE *stageFILE;

    if ((stageFILE=fopen(".ugit/stagingArea.txt","r+"))==NULL)
    {
        printError(100, ".ugit/stagingArea.txt", "Cree el archivo o ejecute el comando init");
        return 0;
    }

    for(int i=0; i<argc; i++)
    {
        duplicated = 0;
        if(!fileExists(argv[i]))
        {
            snprintf(inputhash, 11,"%.10u",hashFile(argv[i]));

            // Vemos si el archivo ya fue guardado
            rewind(stageFILE);

            // Leer línea por línea
            while (fgets(lineBuffer, sizeof(lineBuffer), stageFILE) != NULL)
            {
                // Buscar si la línea contiene el nombre del archivo
                if (strncmp(lineBuffer, argv[i], strlen(argv[i])) == 0)
                {
                    if(fgets(lineBuffer, sizeof(lineBuffer), stageFILE) != NULL && !strncmp(inputhash, lineBuffer, 10)) // Leemos la linea de hash
                    {
                        printError(118, argv[i], NULL);
                    }
                    else{
                        fseek(stageFILE, (ftell(stageFILE)-strlen(lineBuffer)), SEEK_SET);
                        fprintf(stageFILE, "%s\n", inputhash);
                        printf("Archivo %s agregado con exito\n", argv[i]);
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
            printError(112, argv[i], NULL);
    }
    fclose(stageFILE);
    return cont;
}

/// @brief Indica los archivos que están presentes en el StagingArea
/// @return -1 en caso de que no exista el directorio de .ugit, 0 si todo sale bien
void stageStatus(){
    if(folderExists("./.ugit"))
    {
        printError(101, ".ugit","Se recomienda ejecutar comando init");
        return;
    }
    if(hashFile(".ugit/stagingArea.txt")==0)
    {
        printError(108, NULL, NULL);
        return;
    }

    char filename[30];
    FILE *stageFILE;

    if ((stageFILE=fopen(".ugit/stagingArea.txt","r+"))==NULL)
    {
        printError(112, ".ugit/stagingArea.txt", NULL);
        return;
    }

    printf("Los siguientes archivos seran commiteados al usar el comando commit: \n");

    while(fscanf(stageFILE, "%s", filename)==1){
        printf("\t%s\n",filename);
        fseek(stageFILE, 11, SEEK_CUR); // Saltamos el hash correspondiente al archivo filename
    }
}

void init()
{
    // Probamos si la carpeta de ugit existe
    if(!folderExists(".ugit"))
    {
        printError(103, NULL, NULL);
        return;
    }
    // Intentamos crear carpeta
    if(system("mkdir .ugit"))
    {
        printError(113, ".ugit", NULL);
        return;
    }
    // Creamos archivo de staging
    if(system("touch .ugit/stagingArea.txt"))
    {
        printError(113, ".ugit", NULL);
        return;
    }
    // Creamos carpeta para comits
    if(system("mkdir ./.ugit/commits"))
    {
        printError(113, ".ugit", NULL);
        return;
    }
    // Creamos archivo de log
    if(system("touch .ugit/commits/log.txt"))
    {
        printError(113, ".ugit", NULL);
        return;
    }

    printf("Carpeta .ugit creada con exito\n");
}