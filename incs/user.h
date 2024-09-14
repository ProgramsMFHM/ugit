#ifndef USER
#define USER
#include <stdio.h>
#include <string.h>
#include "folders.h"
#include "utilities.h"

#define nameLenght 40
#define mailLenght 35

typedef struct _user
{
    char name[nameLenght];
    char mail[mailLenght];
} user;

int userConfig();

#endif