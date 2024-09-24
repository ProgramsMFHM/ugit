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

int fileExists(char *filename);

int folderExists(char *folderName);

void flushInputBuffer();

void trimNewline(char *str);

char* dateToLocalString(time_t date);

#endif