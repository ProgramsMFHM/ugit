/// \file commit.c
/// \brief Funciones relacionadas con Commits y el Log.
/// \author Alan Almonacid y Milton Hernández
#include "commit.h"

/// @brief Gestiona la creación de un commit a partir de un mensaje
/// @param message Cadena que contiene el mensaje correspondiente al commit
void createCommit(char* message){
    if(!message)
    {
        printError(105, NULL, NULL);
        return;
    }
    if(strlen(message)>commitLenght)
    {
        printError(106, NULL, NULL);
        return;
    }
    char lineBuffer[100];

    commit commitInfo;
    commitInfo.date = time(NULL);
    strcpy(commitInfo.message,message);
    commitInfo.ID = lastCommitId()+1;
    if(!commitInfo.ID)
        printError(107, NULL, NULL);

    // Buscamos usuario
    FILE *ugitFILE;
    if ((ugitFILE=fopen(".ugit/ugitConfig.txt","r"))==NULL)
    {
        printError(100, ".ugit/ugitConfig.txt", "Se recomienda ejecutar el comando config");
        return;
    }

    // Leer línea por línea
    while (fgets(lineBuffer, sizeof(lineBuffer), ugitFILE) != NULL)
    {
        // Buscar si la línea contiene "Nombre"
        if (strncmp(lineBuffer, "name: ", 6) == 0)
        {
            // Extraer el valor después del igual
            if(snprintf(commitInfo.autor.name, nameLenght, "%s", lineBuffer + 6) >= nameLenght)
                printError(301, "nombre", NULL);
            trimNewline(commitInfo.autor.name);
        }
        // Buscar si la línea contiene "Mail"
        else if (strncmp(lineBuffer, "mail: ", 6) == 0)
        {
            // Extraer el valor después del igual
            if(snprintf(commitInfo.autor.mail, mailLenght, "%s", lineBuffer + 6) >= mailLenght)
                printError(301, "correo", NULL);
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

/// @brief Crea un directorio donde se copian los archivos del StagingArea y archivos no modificados desde el último commit
/// El directorio creado se almacena en .ugit/commits/<ID_del_commit>
/// @param commitInfo Información del commit a almacenar
/// @return 1 en caso de error, 0 en caso favorable
int createCommitDir(commit commitInfo)
{
    if(hashFile(".ugit/stagingArea.txt")==0)
    {
        printError(108, NULL, NULL);
        return 1;
    }

    char dirname[11];
    char command[150];

    sprintf(dirname, "%u", commitInfo.ID);
    sprintf(command, "mkdir ./.ugit/commits/%s", dirname);

    if(system(command))
    {
        printError(113, dirname, NULL);
        return 1;
    }

    if(folderExists("./.ugit/commits/tmp"))
    {
        printError(113, "./.ugit/commits/tmp", "No se tienen registros de los archivos en el StagingArea");
        return 1;
    }

    sprintf(command, "cp ./.ugit/commits/tmp/* ./.ugit/commits/%s", dirname);

    if(system(command))
    {
        printError(303, NULL, "La informacion del commit no fue guardada");
        return 1;
    }

    // Borrando carpeta temporal de staging area
    if(system("rm -r ./.ugit/commits/tmp/"))
    {
        printError(121, "./.ugit/commits/tmp/", "Se recomienda eliminarlo antes de continuar usando Ugit");
    }

    // Borrando el archivo del staging area
    FILE *stageFILE;
    if ((stageFILE=fopen(".ugit/stagingArea.txt","w"))==NULL)
    {
        printError(100, ".ugit/stagingArea.txt", NULL);
        return 1;
    }
    fclose(stageFILE);
    if(commitInfo.ID>1)
    {
        sprintf(command,"cp -rn ./.ugit/commits/%u/. ./.ugit/commits/%u/", headCommitId(NULL), commitInfo.ID);
        if(system(command))
            printError(303, NULL, NULL);
    }
    return 0;
}

/// @brief Imprime la informacion de un commit
/// @param commitInfo Estructura con la informacion del commit
void printCommit(commit commitInfo)
{
    // Pasamos fecha del commit a string:
    char *dateString = dateToLocalString(commitInfo.date);

    //Comprobamos si el commit corresponde al main:
    if(commitInfo.ID == lastCommitId())
        printf(ANSI_COLOR_BLUE"(main) "ANSI_COLOR_RESET);
    //Comprobamos si el commit corresponde al head:
    if(commitInfo.ID == headCommitId(NULL))
        printf(ANSI_COLOR_CYAN"(HEAD) "ANSI_COLOR_RESET);

    // Mostramos Commit
    printf("Commit %u:\n\tFecha: %s\n\tAutor: %s <%s>\n\tMensaje: %s\n\n",commitInfo.ID, dateString, commitInfo.autor.name, commitInfo.autor.mail, commitInfo.message);

    free(dateString);
}

/// @brief Guarda un commit al inicio de un archivo (en modo binario)
/// @param filename Es la ruta del archivo de log donde se guardará el commit
/// @param commitInfo Estructura correspondiente a la información del commit
void saveCommit(char* filename, commit commitInfo){
    // Guardamos commit en el log
    FILE* logFile = fopen(filename, "ab");
    if(logFile == NULL)
    {
        printError(112, filename, NULL);
        return;
    }
    fwrite(&commitInfo, sizeof(commit), 1, logFile);
    fclose(logFile);

    changeHeadCommit(commitInfo.ID);
}

/// @brief Lee el siguiente commit dentro del fichero logFile
/// @param logFile Puntero a un archivo donde se leerá el commit
/// @param commitInfo Estructura donde se almacena la información del commit
/// @return 0 en caso de exito, 1 en caso de error
/// @note Se espera que logFile esté ya inicializado
int readCommit(FILE* logFile, commit* commitInfo){
    return !fread(commitInfo, sizeof(commit), 1, logFile);
}

/// @brief Imprime el Log del directorio
/// Se almacena la información en una lista enlazada para su posterior lectura
void loggingCommits(){
    Log commitLog = NULL;
    commit tmpCommit;
    commitLog = makeEmpty(commitLog);

    FILE* logFile = fopen(".ugit/commits/log.txt", "rb");
    if(logFile == NULL)
    {
        printError(100, ".ugit/commits/log.txt","Puede que no haya hecho ningun commit");
        return;
    }

    while(!feof(logFile))
    {
        if(readCommit(logFile, &tmpCommit))
           break;

        insert(tmpCommit, header(commitLog));
    }

    fclose(logFile);

    printList(commitLog);

    deleteList(commitLog);

    return;
}

/// @brief Calcula el valor del ID del último commit commit a partir del tamaño del log de commits
/// @return ID del último commit
unsigned int lastCommitId()
{
    long filePosition;
    FILE* logFile = fopen(".ugit/commits/log.txt", "rb");
    if(logFile == NULL)
    {
        printError(100, ".ugit/commits/log.txt","Sería recomendable ejecutar comando init");
        return 0;
    }

    fseek(logFile,0,SEEK_END);
    filePosition = ftell(logFile);
    fclose(logFile);
    return (unsigned int)(filePosition/sizeof(commit));
}

/// @brief Devuelve el ID del commit donde se encuentra el usuario en el momento
/// @return Id encontrado (-1 en caso de error, 0 en caso de que no haya commits)
unsigned int headCommitId(int* position)
{
    unsigned int ID = 0;
    char IDstring[11];
    char lineBuffer[100];
    int found = 0;

    FILE *configFile;
    if ((configFile=fopen(".ugit/ugitConfig.txt","r"))==NULL)
    {
        printError(100, "ugitConfig.txt", "Se recomienda ejecutar el comando config");
        return 0;
    }

    // Leer línea por línea
    while (fgets(lineBuffer, sizeof(lineBuffer), configFile) != NULL) {
        // Buscar si la línea contiene "nmainCommit"
        if (strncmp(lineBuffer, "headCommit: ", 12) == 0) {
            // Extraer el valor después del igual
            if(snprintf(IDstring, 11, "%s", lineBuffer + 12) > 11)
                printError(302, NULL, NULL);
            trimNewline(IDstring);
            found = 1;
            break;
        }
        if(position) // Si se requiere la posicion entonces pasamos la ubicacion de la linea en cuestion
            *position = ftell(configFile);
    }

    fclose(configFile);

    if(!found)
        printf("Error: No se encontro la informacion de la posicion del HEAD en el log, archivo corrupto\n");
    else
        ID = strtoul(IDstring, NULL, 10);

    return ID;
}

/// @brief Altera el archivo de configuración para indicar que el HEAD cambió de lugar
/// @param commitID Nuevo ID para el HEAD
void changeHeadCommit(unsigned int commitID){
    int configHeadCommitPosition;

    headCommitId(&configHeadCommitPosition);
    FILE* configFile = fopen("./.ugit/ugitConfig.txt", "r+");
    if(configFile == NULL)
    {
        printError(302, "./.ugit/ugitConfig.txt", NULL);
        return;
    }
    fseek(configFile, configHeadCommitPosition, SEEK_SET);
    fprintf(configFile,"headCommit: %.10u",commitID);
    fclose(configFile);
}