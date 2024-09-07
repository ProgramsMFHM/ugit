#include "user.h"

int userConfig(){
    if(!folderExists(".ugit"))
        return -1;

    user userInfo;
    printf("Ingrese su nombre de usuario: ");
    fgets(userInfo.name, nameLenght, stdin);
    if ((strlen(userInfo.name) > 0) && (userInfo.name[strlen(userInfo.name) - 1] == '\n'))
        userInfo.name[strlen(userInfo.name) - 1] = '\0';

    printf("Ingrese su correo de usuario: ");
    fgets(userInfo.mail, mailLenght, stdin);
    if ((strlen(userInfo.mail) > 0) && (userInfo.mail[strlen(userInfo.mail) - 1] == '\n'))
        userInfo.mail[strlen(userInfo.mail) - 1] = '\0';

    FILE *ugitFILE;
    if ((ugitFILE=fopen(".ugit/ugitConfig.txt","w+"))==NULL)
        return 0;

    fprintf(ugitFILE,"Nombre = %s\nMail = %s",userInfo.name, userInfo.mail);
    fclose(ugitFILE);
    return 1;
}

