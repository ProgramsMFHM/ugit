#include"commit.h"


void createCommit(char* message){
    commit commitInfo;
    commitInfo.date = time(NULL);
    commitInfo.message = message;
    commitInfo.hash = jenkinsHash((unsigned char*)message, strlen(message));

    // Buscamos usuario
    FILE *ugitFILE;
    if ((ugitFILE=fopen(".ugit/ugitConfig.txt","rb"))==NULL)
        return;
    fread(&(commitInfo.autor), sizeof(user), 1, ugitFILE);
    fclose(ugitFILE);

    // Fehca a texto:
    struct tm *local = localtime(&commitInfo.date);  // Convertir a tiempo local
    char datestring[24];
    // Formatear la fecha y la hora con la zona horaria
    strftime(datestring, sizeof(datestring), "%Y-%m-%d %H:%M:%S %Z",local);

    // Mostramos Commit
    printf("Se guardara la siguiente informacion:\n\n\tHash: %u\n\tFecha: %s\n\tAutor: %s<%s>\n\tMensaje: %s\n\n", commitInfo.hash, datestring, commitInfo.autor.name, commitInfo.autor.mail, commitInfo.message);
}