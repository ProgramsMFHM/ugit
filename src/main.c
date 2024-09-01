#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "folders.h"
#include "user.h"

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
            printf("No se pudo abrir el archivo de staging\n");
            break;
        }
    }
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

    return 1;
}