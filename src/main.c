/// \file main.c
/// \author Alan Almonacid y Milton Hernández
/// \date 24 de Septiembre del 2024
/// \brief Archivo principal para el proyecto Ugit.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stagingArea.h"
#include "checkout.h"
#include "commit.h"
#include "errors.h"
#include "hash.h"
#include "help.h"
#include "init.h"
#include "userConfig.h"

int main(int argc, char* argv[])
{
    if(!argv[1])
    {
        printHelp();
        return 0;
    }

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
    else if(!strcmp("help\0", argv[1]))
    {
        if(argv[2])
            commandHelp(argv[2]);
        else
            printHelp();
    }
    else
        printError(104, argv[1], NULL);

    return 0;
}