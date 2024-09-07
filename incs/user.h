#ifndef USER
#define USER
#include <stdio.h>
#include <string.h>
#include "folders.h"

#define nameLenght 30
#define mailLenght 32

typedef struct _user
{
    char name[nameLenght];
    char mail[mailLenght];
} user;

int userConfig();

#endif