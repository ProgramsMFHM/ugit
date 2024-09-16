/// \file utilities.h
/// \brief Cabecera para utilities.c
#ifndef UTILITIES
#define UTILITIES

#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>
#include "errors.h"

void flushInputBuffer();
void trimNewline(char *str);
char* dateToLocalString(time_t date);

#endif