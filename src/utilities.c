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
/// @return String donde se almacenará la cadea final
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