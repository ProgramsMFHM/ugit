/// \file utilities.c
/// \brief Funciones útiles para el manejo de información del programa
#include "utilities.h"

/// @brief Esta función limpia el buffer correspondiente a la entrada estándar del computador.
void flushInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/// @brief Elimina el caracter de salto de linea de un strng si lo tiene
/// @param str Corresponde al string analizado
void trimNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

/// @brief Transforma una fecha de tipo time_t (propia de <time.h>) a un atring formateado
/// @param date Fecha de tipo time_t
/// @return String donde se almacenará la cadena final
/// @note Asegúrese de liberar memoria una vez terminado el uso del puntero retornado por esta función.
char* dateToLocalString(time_t date){
    struct tm *local = localtime(&date);  // Convertir a tiempo local
    tzset(); // Inicializar la información de la zona horaria

    char *stringPointer = malloc(24);
    if(stringPointer==NULL)
        printError(200, "24", NULL);

    if(strftime(stringPointer, 24, "%Y-%m-%d %H:%M:%S %Z",local) == 0)
    {
        printError(117, NULL, NULL);
        return NULL;
    }

    return stringPointer;
}

/// @brief Imprime un guía con documentación sobre uGit y los comandos que se pueden usar
void printHelp(){
    printf("\tModo de uso: ./ugit <comando> [<parametro 1, parametro 2, …>]\n\n");
    printf("Comandos disponibles:\n");
    printf("\t* add <archivo1> <archivo2>...   Agrega los archivos deseados al Staging Area\n");
    printf("\t* checkout <commit_ID>           Lleva el directorio actual a su estado al momento de hacer el commit con el id: commit_ID\n");
    printf("\t* commit <\"mensaje\">             Genera un commit con los datos del Staging Area\n");
    printf("\t* config                         Inicializa una configuracion para un usuario\n");
    printf("\t* log                            Genera una lista de los commits realizados hasta el momento\n");
    printf("\t* help [comando]                 Imprime informacion sobre el funcionamiento de los comandos en uGit\n");
    printf("\t* init                           Inicia un repositorio vacio en el directorio actual\n");
    printf("\t* status                         Indica los archivos presentes en el Staging Area\n");
}

/// @brief Imprime la documentación para un comando en especifico
/// @param command Comando que se desea investigar
void commandHelp(char* command) {
    if (strcmp(command, "add") == 0) {
        printf("\t\t\tInformacion sobre el comando add\n\n");
        printf("Este comando agrega los archivos deseados al Staging Area, puede recibir como parametros nombres de varios archivos (separados por espacios) agregando varios al mismo tiempo al Staging Area.\n\n");
        printf("Adicionalmente es posible usar el caracter * de la misma manera que se usaria en la terminal para representar una cantidad indefinida de caracteres en una posicion de una cadena.\n\n");
        printf("Por ejemplo \"add *.c\" agrega todos los archivos que terminen en .c al Staging Area.\n\n");
    } else if (strcmp(command, "checkout") == 0) {
        printf("\t\t\tInformacion sobre el comando checkout\n\n\n");
        printf("Este comando lleva el directorio actual a su estado al momento de hacer el commit con el id: commit_ID.\n\n");
        printf("Si no conoce el ID de un commit basta con ejecutar el comando log para conocer el ID de cada uno de ellos.\n\n");
    } else if (strcmp(command, "commit") == 0) {
        printf("\t\t\tInformacion sobre el comando commit\n\n\n");
        printf("Este comando genera un commit con los datos del Staging Area.\n\n");
        printf("El mensaje del commit tiene una longitud maxima de 256 caracteres.\n\n");
        printf("No se puede ejecutar commit si el Staging Area esta vacio.\n\n");
    } else if (strcmp(command, "config") == 0) {
        printf("\t\t\tInformacion sobre el comando config\n\n\n");
        printf("Este comando inicializa una configuracion para un usuario.\n\n");
        printf("Se pedira un nombre de usuario (de maximo 40 caracteres) asi como un correo electronico (de maximo 35 caracteres).\n\n");
    } else if (strcmp(command, "log") == 0) {
        printf("\t\t\tInformacion sobre el comando log\n\n\n");
        printf("Este comando genera una lista de los commits realizados hasta el momento.\n\n");
        printf("Podra ver un indicador (main) que representa el ultimo commit que se ha realizado asi como un indicador (HEAD) que representa el commit donde se encuentra la visualizacion actual del directorio.\n\n");
    } else if (strcmp(command, "help") == 0) {
        printf("\t\t\tInformacion sobre el comando help\n\n\n");
        printf("Este comando imprime informacion sobre el funcionamiento de los comandos en uGit.\n\n");
        printf("Puede indicar el nombre de un comando especifico para conocer una descripcion mas completa de su funcionamiento.\n\n");
    } else if (strcmp(command, "init") == 0) {
        printf("\t\t\tInformacion sobre el comando init\n\n\n");
        printf("Este comando inicia un repositorio vacio en el directorio actual.\n\n");
        printf("Si el repositorio existe no podra inicializarse de nuevo.\n\n");
        printf("Se crean algunas carpetas y archivos que seran usados por el programa para su correcto funcionamiento; la eliminacion de estos archivos podria corromper el funcionamiento de uGit.\n\n");
    } else if (strcmp(command, "status") == 0) {
        printf("\t\t\tInformacion sobre el comando status\n\n\n");
        printf("Este comando indica los archivos presentes en el Staging Area.\n\n");
        printf("Los archivos que se encuentran en el Staging Area se encuentran en la version en que se encontraban al momento de usar el comando add, nuevas modificaciones deberan incluirse en el Staging Area antes de hacer commit si desean ser guardadas.\n\n");
    } else {
        printf("Comando %s no reconocido.\n\n", command);
    }
}