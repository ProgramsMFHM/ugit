/// \file userConfig.c
/// \brief Funciones al respecto de la creación de un usuario dentro del Ugit
/// \author Alan Almonacid y Milton Hernández
#include "userConfig.h"

/// @brief Inicializa el archivo de configuración del Ugit
void userConfig()
{
    if(folderExists(".ugit"))
    {
        printError(101, ".ugit", "Ejecute el comando init");
        return;
    }

    user userInfo;
    getInfo(nameLenght, userInfo.name, "nombre");
    getInfo(mailLenght, userInfo.mail, "mail");

    FILE *ugitFILE;
    if ((ugitFILE=fopen(".ugit/ugitConfig.txt","w+"))==NULL)
    {
        printError(114, NULL, NULL);
        return;
    }

    fprintf(ugitFILE,"name: %s\nmail: %s\nheadCommit: %.10u",userInfo.name, userInfo.mail,0);
    fclose(ugitFILE);
    printf("Usuario iniciado almacenado con exito.\n");
}

/// @brief Pide un recurso del usuario especifico para posteriormentte guardarlo
/// @param lenght Tamaño máximo del recurso
/// @param dest Cadena destino donde se almacenará el recurso
/// @param message Nombre del recurso
void getInfo(int lenght, char* dest, char* message){
    while(1) // Se rompera al ver entrada valida
    {
        printf("Ingrese su %s (%d caracteres): ",message, lenght-1);

        if(fgets(dest, lenght, stdin) != NULL) // Leemos entrada del usuario
        {
            if ((strlen(dest) > 0) && (dest[strlen(dest) - 1] == '\n'))
            { // En caso de entrar significa que se leyo un salto de linea al final. Entrada valida
                trimNewline(dest);
                break; // Entrada valida termina el bucle
            }
            else
            {
                flushInputBuffer();
                printError(119, NULL, NULL);
            }
        }
        else
        {
            flushInputBuffer();
            printError(120, NULL, NULL);
        }
    }
}