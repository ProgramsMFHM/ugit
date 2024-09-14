#include "commit.h"


void createCommit(char* message){
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
        if (strncmp(lineBuffer, "Nombre: ", 8) == 0) {
            // Extraer el valor después del igual
            if(snprintf(commitInfo.autor.name, nameLenght, "%s", lineBuffer + 8) >= nameLenght)
                printf("Advertencia: Nombre leido fue truncado por ser demasiado grande.\n\n");
            trimNewline(commitInfo.autor.name);
        }
        // Buscar si la línea contiene "Mail"
        else if (strncmp(lineBuffer, "Mail: ", 6) == 0) {
            // Extraer el valor después del igual
            if(snprintf(commitInfo.autor.mail, mailLenght, "%s", lineBuffer + 6) >= mailLenght)
                printf("Advertencia: Mail leido fue truncado por ser demasiado grande.\n\n");
            trimNewline(commitInfo.autor.mail);
        }
    }

    fclose(ugitFILE);

    // Pasamos fecha a string:
    char *dateString = dateToLocalString(commitInfo.date);

    // Mostramos Commit
    printf("Se guardara la siguiente informacion:\n\n\tFecha: %s\n\tAutor: %s <%s>\n\tMensaje: %s\n\n", dateString, commitInfo.autor.name, commitInfo.autor.mail, commitInfo.message);

    free(dateString);
}