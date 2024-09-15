#include "commit.h"


void createCommit(char* message){
    if(!message)
    {
        printf("No ingreso un mensaje para el commit");
        return;
    }
    if(strlen(message)>commitLenght)
    {
        printf("Mensaje de commit demasiado largo (Limite 256)");
        return;
    }

    commit commitInfo;
    commitInfo.date = time(NULL);
    strcpy(commitInfo.message,message);
    commitInfo.ID = nextCommitId();
    if(!commitInfo.ID)
        commit_error("No se puede asignar ID al commit");

    char lineBuffer[100];
    // Buscamos usuario
    FILE *ugitFILE;
    if ((ugitFILE=fopen(".ugit/ugitConfig.txt","r"))==NULL)
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

    // Crear carpeta y guardar archivos del commit
    if(!createCommitDir(commitInfo))
    {
        saveCommit(".ugit/commits/log.txt", commitInfo);
        printCommit(commitInfo);
    }
}
/// @brief Crea un directorio donde se copian los archivos del StagingArea
/// El directorio creado se almacena en .ugit/commits/<has_del_commit>
/// @param commitInfo Información del commit a almacenar
/// @return 1 en caso de error, 0 en caso favorable
int createCommitDir(commit commitInfo)
{
    if(hashFile(".ugit/stagingArea.txt")==0)
    {
        commit_error("El StagingArea esta vacio");
        return 1;
    }

    char dirname[11];
    char command[150];
    char lineBuffer[100];
    sprintf(dirname, "%u", commitInfo.ID);
    sprintf(command, "mkdir ./.ugit/commits/%s", dirname);

    if(system(command)){
        printf("No se pudo crear la carpeta %s\n\n", dirname);
        return 1;
    }

    FILE *stageFILE;

    if ((stageFILE=fopen(".ugit/stagingArea.txt","r"))==NULL)
    {
        file_error(".ugit/stagingArea.txt","");
        return 1;
    }

    // Leer línea por línea
    while (fgets(lineBuffer, sizeof(lineBuffer), stageFILE) != NULL) {
        trimNewline(lineBuffer);
        if(fileExists(lineBuffer))
        {
            file_error(lineBuffer,"");
            return 1;
        }

        sprintf(command, "cp ./%s ./.ugit/commits/%s/", lineBuffer, dirname);
        if(system(command)){
            printf("No se pudo guardar el archivo %s\n", lineBuffer);
            return 1;
        }

        if(fgets(lineBuffer, sizeof(lineBuffer), stageFILE) == NULL) // Saltamos hash del archivo leido
        {
            printf("Error al leer el archivo");
            return 1;
        }
    }

    fclose(stageFILE);

    // Borrando el archivo del staging area
    if ((stageFILE=fopen(".ugit/stagingArea.txt","w"))==NULL)
    {
        file_error(".ugit/stagingArea.txt","");
        return 1;
    }
    fclose(stageFILE);
    return 0;
}

/// @brief Imprime la informacion de un commit
/// @param commitInfo Estructura con la informacion del commit
void printCommit(commit commitInfo)
{
    // Pasamos fecha del commit a string:
    char *dateString = dateToLocalString(commitInfo.date);

    // Mostramos Commit
    printf("Commit %u:\n\tFecha: %s\n\tAutor: %s <%s>\n\tMensaje: %s\n\n",commitInfo.ID, dateString, commitInfo.autor.name, commitInfo.autor.mail, commitInfo.message);

    free(dateString);
}


/// @brief Guarda un commit al inicio de un archivo (en modo binario)
/// @param filename Es la ruta del archivo de log donde se guardará el commit
/// @param commitInfo Estructura correspondiente a la información del commit
void saveCommit(char* filename, commit commitInfo){
    FILE* logFile = fopen(filename, "ab");
    if(logFile == NULL)
    {
        fprintf(stderr, "No se pudo abrir o crear el archivo %s\n", filename);
        return;
    }

    // Guardamos la fecha del commit en el archivo
    fwrite(&commitInfo, sizeof(commit), 1, logFile);

    fclose(logFile);
}

/// @brief Lee el siguiente commit dentro del fichero logFile
/// @param logFile Puntero a un archivo donde se leerá el commit
/// @param commitInfo Estructura donde se almacena la información del commit
/// @return 0 en caso de exito, 1 en caso de error
/// @note Se espera que logFile esté ya inicializado
int readCommit(FILE* logFile, commit* commitInfo){
    if(fread(commitInfo, sizeof(commit), 1, logFile) == 0)
    {
        return 1;
    }
    return 0;
}

int loggingCommits(){
    Log commitLog = NULL;
    commit tmpCommit;
    commitLog = MakeEmpty(commitLog);

    FILE* logFile = fopen(".ugit/commits/log.txt", "rb");
    if(logFile == NULL)
    {
        file_error(".ugit/commits/log.txt","Puede que no haya hecho ningun commit");
        return -1;
    }

    while(!feof(logFile))
    {
        if(readCommit(logFile, &tmpCommit))
           break;

        Insert(tmpCommit, commitLog, Header(commitLog));
    }

    fclose(logFile);

    PrintList(commitLog);

    DeleteList(commitLog);

    return -1;
}

/// @brief Calcula el valor del ID del proximo commit a partir del tamaño del log de commits
/// @return Próximo ID
unsigned int nextCommitId()
{
    FILE* logFile = fopen(".ugit/commits/log.txt", "rb");
    if(logFile == NULL)
    {
        file_error(".ugit/commits/log.txt","Sería recomendable ejecutar comando init");
        return -1;
    }

    fseek(logFile,0,SEEK_END);
    return (unsigned int)((ftell(logFile)/sizeof(commit))+1);
}