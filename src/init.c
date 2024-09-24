/// \file init.c
/// \brief Funciones relacionadas con la inicialización de un repositorio ugit
/// \author Alan Almonacid y Milton Hernández
#include"init.h"


/// @brief Función encargada de la iniciación de ugit en directorio
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