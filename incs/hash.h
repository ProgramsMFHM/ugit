/// \file hash.h
/// \brief Cabecera para hash.c
/// \author Alan Almonacid y Milton Hernández
#ifndef HASH
#define HASH

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

unsigned int jenkinsHash (unsigned char *key, size_t len);

unsigned int hashFile (char *filename);

#endif