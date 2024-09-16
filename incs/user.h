/// \file user.h
/// \brief Cabecera para user.c
#ifndef USER
#define USER
#include <stdio.h>
#include <string.h>
#include "folders.h"
#include "utilities.h"
#include "errors.h"

#define nameLenght 41
#define mailLenght 36

typedef struct _user
{
    char name[nameLenght];
    char mail[mailLenght];
} user;

void userConfig();

void getInfo(int lenght, char* dest, char* message);

#endif