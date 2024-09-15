#include "commit.h"


void createCommit(char* message){
    if(!message)
    {
        printf("No ingreso un mensaje para el commit");
        return;
    }

    commit commitInfo;
    commitInfo.date = time(NULL);
    commitInfo.message = message;

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
        printCommit(commitInfo);
        saveCommit(".ugit/commits/log.txt", commitInfo);
    }
}
/// @brief Crea un directorio donde se copian los archivos del StagingArea
/// El directorio creado se almacena en .ugit/commits/<has_del_commit>
/// @param commitInfo Información del commit a almacenar
/// @return 1 en caso de error, 0 en caso favorable
int createCommitDir(commit commitInfo)
{
    char dirname[11];
    char command[150];
    char lineBuffer[100];
    snprintf(dirname, 11, "%.10ld", commitInfo.date);
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
    printf("Commit %ld:\n\tFecha: %s\n\tAutor: %s <%s>\n\tMensaje: %s\n\n",commitInfo.date, dateString, commitInfo.autor.name, commitInfo.autor.mail, commitInfo.message);

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
    fwrite(&commitInfo.date, sizeof(time_t), 1, logFile);

    // Guardamos al autor
    fwrite(&commitInfo.autor, sizeof(user), 1, logFile);

    // Guardamos el tamanio del mensaje del commit
    size_t messageLenght = strlen(commitInfo.message)+1;
    fwrite(&messageLenght, sizeof(size_t), 1, logFile);

    // Guardamos el mensaje
    fwrite(commitInfo.message, sizeof(char), messageLenght, logFile);

    fclose(logFile);
}

/// @brief Lee el siguiente commit dentro del fichero logFile
/// @param logFile Puntero a un archivo donde se leerá el commit
/// @param commitInfo Estructura donde se almacena la información del commit
/// @return 1 en caso de exito, 0 en caso de error
/// @note Se espera que logFile esté ya inicializado
int readCommit(FILE* logFile, commit* commitInfo){
    // Leemos la fecha del commit
    if(fread(&(commitInfo->date), sizeof(time_t), 1, logFile) < 1)
    {
        if(!feof(logFile))
            // Cuando se llega al fin del archivo y se intenta leer de nuevo una fecha genera error. En este caso solo nos interesa que aparezca por consola si no estamos en el fin del archivo.
            printf("No se pudo leer la fecha\n");
        return 0;
    }

    // Guardamos al autor
    if(fread(&(commitInfo->autor), sizeof(user), 1, logFile) < 1)
    {
        printf("No se pudo leer el autor\n");
        return 0;
    }

    // Guardamos el tamanio del mensaje del commit
    size_t messageLenght;
    if(fread(&messageLenght, sizeof(size_t), 1, logFile) < 1)
    {
        printf("No se pudo leer el tamanio del mensaje\n");
        return 0;
    }

    // Guardamos el mensaje
    commitInfo->message = malloc(messageLenght);
    if(fread(commitInfo->message, sizeof(char), messageLenght, logFile) < messageLenght)
    {
        printf("No se pudo leer el mensaje completo\n");
        return 0;
    }

    return -1;
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
        if(!readCommit(logFile, &tmpCommit))
            break;
        Insert(tmpCommit, commitLog, Header(commitLog));
    }

    fclose(logFile);

    PrintList(commitLog);

    DeleteList(commitLog);

    return -1;
}