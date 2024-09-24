/// \file commit.h
/// \brief Cabecera para commit.c
/// \author Alan Almonacid y Milton Hernández
#ifndef COMMIT
#define COMMIT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "errors.h"
#include "hash.h"
#include "userConfig.h"
#include "utilities.h"

#define commitLenght 256

/// @brief Estructura para almacenar información de un Commit dentro de uGit
struct _commitInfo
{
    /// @brief Número identificador del commit
    unsigned int ID;
    /// @brief Fecha de la creación del commit
    time_t date;
    /// @brief Mensaje resumen de las acciones del commit
    char message[commitLenght];
    /// @brief Creador del commit
    user autor;
};
typedef struct _commitInfo commit;

#include "list.h"

void createCommit(char* message);

int createCommitDir(commit commitInfo);

void saveCommit(char* filename, commit commitInfo);

void loggingCommits();

int readCommit(FILE* logFile, commit* commitInfo);

void printCommit(commit commitInfo);

unsigned int lastCommitId();

unsigned int headCommitId(int* position);

void changeHeadCommit(unsigned int commitID);

#endif