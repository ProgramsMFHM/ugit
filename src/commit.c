#include "commit.h"


void createCommit(char* message){
    fileStatus("main.c");

    if(!message)
        printf("No ingreso un mensaje para el commit");

    commit commitInfo;
    commitInfo.date = time(NULL);
    commitInfo.message = message;
    //commitInfo.hash = jenkinsHash((unsigned char*)message, strlen(message));
    char lineBuffer[100];

    // Buscamos usuario
    FILE *ugitFILE;
    if ((ugitFILE=fopen(".ugit/ugitConfig.txt","rb"))==NULL)
    {
        file_error("ugitConfig.txt", "Se recomienda ejecutar el comando config");
        return;
    }

    // Leer línea por línea
    while (fgets(lineBuffer, sizeof(lineBuffer), ugitFILE) != NULL) {
        // Buscar si la línea contiene "Nombre"
        if (strncmp(lineBuffer, "Nombre =", 8) == 0) {
            // Extraer el valor después del igual
            sscanf(lineBuffer + 8, "%s", commitInfo.autor.name);
        }
        // Buscar si la línea contiene "Mail"
        else if (strncmp(lineBuffer, "Mail =", 6) == 0) {
            // Extraer el valor después del igual
            sscanf(lineBuffer + 6, "%s", commitInfo.autor.mail);
        }
    }

    // Fecha a texto:
    struct tm *local = localtime(&commitInfo.date);  // Convertir a tiempo local
    char datestring[24];
    // Formatear la fecha y la hora con la zona horaria
    strftime(datestring, sizeof(datestring), "%Y-%m-%d %H:%M:%S %Z",local);

    // Mostramos Commit
    printf("Se guardara la siguiente informacion:\n\n\tFecha: %s\n\tAutor: %s <%s>\n\tMensaje: %s\n\n", datestring, commitInfo.autor.name, commitInfo.autor.mail, commitInfo.message);
}