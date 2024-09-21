/// \file main.c
/// \author Alan Almonacid y Milton Hernández
/// \date 25 de Septiembre del 2024
/// \brief Archivo principal para el proyecto Ugit.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commit.h"
#include "errors.h"
#include "folders.h"
#include "hash.h"
#include "user.h"

int main(int argc, char* argv[])
{
    if(!strcmp("init\0", argv[1]))
        init();
    else if(!strcmp("config\0", argv[1]))
        userConfig();
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