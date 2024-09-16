/// \file main.c
/// \author Alan Almonacid y Milton Hernández
/// \date 25 de Septiembre del 2024
/// \brief Archivo principal para el proyecto.
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
            printError(113, ".ugit", NULL);
            break;
        case -1:
            printError(103, NULL, NULL);
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
            printError(114, NULL, NULL);
            break;
        case -1:
            printError(101, ".ugit", "Ejecute el comando init");
            break;
        }
    }
    else if(!strcmp("add\0", argv[1]))
    {
        switch (addFiles(argc-2, argv+2))
        {
        case 0:
            printError(300, NULL, NULL);
            break;
        case -1:
            printError(101, ".ugit", "Ejecute el comando init");
            break;
        }
    }
    else if(!strcmp("status\0", argv[1]))
        stageStatus();
    else if(!strcmp("commit\0", argv[1]))
        createCommit(argv[2]);
    else if(!strcmp("checkout\0", argv[1]))
        checkout(argv[2]);
    else if(!strcmp("log\0", argv[1]))
        loggingCommits();
    else
        printError(104, argv[1], NULL);

    return 0;
}

int init(){
    // Probamos si la carpeta de ugit existe
    if(folderExists(".ugit"))
        return -1;
    // Intentamos crear carpeta
    if(system("mkdir .ugit"))
        return 0;
    // Creamos archivo de staging
    if(system("touch .ugit/stagingArea.txt"))
        return 0;
    // Creamos carpeta para comits
    if(system("mkdir ./.ugit/commits"))
        return 0;
    // Creamos archivo de log
    if(system("touch .ugit/commits/log.txt"))
        return 0;

    return 1;
}