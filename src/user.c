#include "user.h"

int userConfig(){
    if(!folderExists(".ugit"))
        return -1;

    user userInfo;

    while(1) // Se rompera al ver entrada valida
    {
        printf("Ingrese su nombre de usuario (%d caracteres): ",nameLenght-1);

        if(fgets(userInfo.name, nameLenght, stdin) != NULL) // Leemos entrada del usuario
        {
            if ((strlen(userInfo.name) > 0) && (userInfo.name[strlen(userInfo.name) - 1] == '\n'))
            {
                // En caso de entrar significa que se leyo un salto de linea al final. Entrada valida
                userInfo.name[strlen(userInfo.name) - 1] = '\0';
                break; // Entrada valida termina el bucle
            }
            else
            {
                flushInputBuffer();
                printf("Entrada demasiado larga. Intente nuevamente.\n");
            }
        }
        else
        {
            flushInputBuffer();
            printf("Error en la entrada. Intente nuevamente.\n");
        }
    }

    while(1) // Se rompera al ver entrada valida
    {
        printf("Ingrese su correo electrónico de usuario (%d caracteres): ",mailLenght-1);

        if(fgets(userInfo.mail, mailLenght, stdin) != NULL) // Leemos entrada del usuario
        {
            if ((strlen(userInfo.mail) > 0) && (userInfo.mail[strlen(userInfo.mail) - 1] == '\n'))
            {
                // En caso de entrar significa que se leyo un salto de linea al final. Entrada valida
                userInfo.mail[strlen(userInfo.mail) - 1] = '\0';
                break; // Entrada valida termina el bucle
            }
            else
            {
                flushInputBuffer();
                printf("Entrada demasiado larga. Intente nuevamente.\n");
            }
        }
        else
        {
            flushInputBuffer();
            printf("Error en la entrada. Intente nuevamente.\n");
        }
    }

    FILE *ugitFILE;
    if ((ugitFILE=fopen(".ugit/ugitConfig.txt","w+"))==NULL)
        return 0;

    fprintf(ugitFILE,"Nombre: %s\nMail: %s",userInfo.name, userInfo.mail);
    fclose(ugitFILE);
    return 1;
}

