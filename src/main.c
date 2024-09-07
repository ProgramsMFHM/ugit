#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "folders.h"
#include "hash.h"
#include "commit.h"
#include "user.h"
#include "errors.h"

int init();

int main(int argc, char* argv[]){

    if(!strcmp("init\0", argv[1]))
    {
        switch (init())
        {
        case 1:
            printf("Carpeta .ugit creada con exito\n");
            break;
        case 0:
            printf("No se pudo crear la carpeta\n");
            break;
        case -1:
            printf("ugit ya esta iniciado en este directorio\n");
            break;
        }
    }
    else if(!strcmp("config\0", argv[1]))
    {
        switch (userConfig())
        {
        case 1:
            printf("Usuario iniciado almacenado con exito.\n");
            break;
        case 0:
            printf("No se pudo guardar el usuario.\n");
            break;
        case -1:
            printf("No existe directorio .ugit, ejecute el comando init.\n");
            break;
        }
    }
    else if(!strcmp("add\0", argv[1]))
    {
        switch (addFiles(argc-2, argv+2))
        {
        case 0:
            printf("No se guardo ningun archivo\n");
            break;
        case -1:
            folder_error(".ugit","Se recomienda ejecutar el comando init");
            break;
        }
    }
    else if(!strcmp("status\0", argv[1]))
        stageStatus();
    else if(!strcmp("commit\0", argv[1]))
        createCommit(argv[2]);
    else
        printf("Comando %s no existe\n", argv[1]);

    return 0;
}

int init(){
    // Probamos si la carpeta de ugit existe
    if(folderExists(".ugit"))
        return -1;
    // Intentamos crear carpeta
    if(system("mkdir .ugit"))
        return 0;
    // Creamos carpeta para comits
    if(system("mkdir ./.ugit/commits"))
        return 0;

    return 1;
}