/// \file checkout.c
/// \brief Funciones relaiconadas con el Checkout.
/// \author Alan Almonacid y Milton Hernández
#include "checkout.h"

/// @brief Regresa el directorio actual de trabajo a una versión anterior
/// @param commitID ID del commit correspondiente a la versión destino
void checkout(char* commitString){
    char command[100];
    unsigned int commitID;
    commitID = strtoul(commitString, NULL, 10);

    if(folderExists("./.ugit"))
    {
        printError(101, ".ugit","Se recomienda ejecutar comando init");
        return;
    }
    if(commitID > lastCommitId() || commitID < 1)
    {
        sprintf(command, "%u",commitID);
        printError(116, command, NULL);
        return;
    }

    sprintf(command, "./.ugit/commits/%u/",commitID);
    if(folderExists(command))
    {
        printError(101, "del commit",NULL);
        return;
    }

    // Eliminamos recursivamente el directorio actual a excepción del .ugit y del ugit
    sprintf(command, "find . -mindepth 1 -maxdepth 1 ! -name '.ugit' ! -name 'ugit' -exec rm -rf {} +");
    if(system(command))
    {
        printError(201, NULL,NULL);
        return;
    }

    // Copiar archivos del commit al directorio de trabajo
    sprintf(command, "cp -r ./.ugit/commits/%u/. .",commitID);
    if(system(command))
    {
        printError(201, NULL,NULL);
        return;
    }
    changeHeadCommit(commitID);
    printf("Ahora esta en la version %u\n",commitID);
}