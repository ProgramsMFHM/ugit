#include <stdio.h>
#include "user.h"
#include "folders.h"

int userConfig(){
    if(!folderExists(".ugit"))
        return -1;

    user usuario;
    printf("Ingrese su nombre de usuario: ");
    scanf("%s",usuario.name);
    printf("Ingrese su correo de usuario: ");
    scanf("%s",usuario.mail);

    FILE *ugitFILE;
    if ((ugitFILE=fopen(".ugit/ugitConfig.txt","w+b"))==NULL)
        return 0;

    fwrite(&usuario, sizeof(user), 1, ugitFILE);
    fclose(ugitFILE);
    return 1;
}

