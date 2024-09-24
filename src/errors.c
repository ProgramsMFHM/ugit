/// \file errors.c
/// \brief Manejo de errores
/// \author Alan Almonacid y Milton Hernández
#include "errors.h"

/// @brief Envía un mensaje de error por consola
/// @param num Código de error (Leer documentación)
/// @param aux Mensaje auxiliar para comandos que lo requieren
/// @param obs Observación en caso de ser necesitada
void printError(int num, char* aux, char* obs) {
    if(num>=200 && num<300)
        printf(ANSI_COLOR_RED "Fatal Error %d: " ANSI_COLOR_RESET, num);
    else if(num>=300 && num<400)
        printf(ANSI_COLOR_MAGENTA "Warning %d: " ANSI_COLOR_RESET, num);
    else
        printf(ANSI_COLOR_RED "Error %d: " ANSI_COLOR_RESET, num);

    switch(num) {
        case 100:
            printf("Archivo %s no encontrado\n", aux);
            break;
        case 101:
            printf("Directorio %s no encontrado\n", aux);
            break;
        case 103:
            printf("Ugit inicializado en este directorio\n");
            break;
        case 104:
            printf("Comando %s no existe\n", aux);
            break;
        case 105:
            printf("Mensaje no ingresado\n");
            break;
        case 106:
            printf("Mensaje demasiado largo\n");
            break;
        case 107:
            printf("No se logro asignar un ID al commit\n");
            break;
        case 108:
            printf("StagingArea vacio\n");
            break;
        case 109:
            printf("No se logro leer el archivo %s\n", aux);
            break;
        case 110:
            printf("No se logro crear el archivo %s\n", aux);
            break;
        case 111:
            printf("No se logro guardar el archivo %s\n", aux);
            break;
        case 112:
            printf("No se logro abrir el archivo %s\n", aux);
            break;
        case 113:
            printf("No se logro crear el directorio %s\n", aux);
            break;
        case 114:
            printf("No se logro guardar el usuario\n");
            break;
        case 115:
            printf("No se encontro la informacion de la posicion del HEAD en el log\n");
            break;
        case 116:
            printf("El commit %s no existe\n", aux);
            break;
        case 117:
            printf("No se logro formatear la fecha\n");
            break;
        case 118:
            printf("El archivo %s no recibio ningun cambio\n", aux);
            break;
        case 119:
            printf("Entrada demasiado larga\n");
            break;
        case 120:
            printf("Error en la entrada\n");
            break;
        case 200:
            printf("No se logro almacenar %s bytes en memoria\n", aux);
            exit(-1);
            break;
        case 201:
            printf("No se logro cambiar de version\n");
            exit(-1);
            break;
        case 202:
            printf("No se ingresó un comando\n");
            exit(-1);
            break;
        case 300:
            printf("No se guardo ningun archivo en el StagingArea\n");
            break;
        case 301:
            printf("El %s fue truncado por ser demasiado argo\n", aux);
            break;
        case 302:
            printf("ID leido en el archivo de configuracion no coincide con el tamanno esperado\n");
            break;
        case 303:
            printf("No se logro guardar archivos antiguos\n");
            break;
        case 304:
            printf("No se logro eliminar el directorio %s\n", aux);
            break;
        default:
            printf("Codigo de error desconocido\n");
    }
    if (obs != NULL) {
        printf("%s\n", obs);
    }
}