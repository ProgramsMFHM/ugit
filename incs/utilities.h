/// \file utilities.h
/// \brief Cabecera para utilities.c
/// \author Alan Almonacid y Milton Hernández
#ifndef UTILITIES
#define UTILITIES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#include "errors.h"

// Definiciones para uso de Colores en los printf
#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"

int fileExists(char *filename);

int folderExists(char *folderName);

void flushInputBuffer();

void trimNewline(char *str);

char* dateToLocalString(time_t date);

#endif