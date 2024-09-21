/// \file commit.h
/// \brief Cabecera para commit.c
#ifndef COMMIT
#define COMMIT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "user.h"
#include "hash.h"
#include "errors.h"
#include "folders.h"
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

void printCommit(commit commitInfo);

void createCommit(char* message);

void saveCommit(char* filename, commit commitInfo);

int createCommitDir(commit commitInfo);

int readCommit(FILE* logFile, commit* commitInfo);

void loggingCommits();

unsigned int lastCommitId();

unsigned int headCommitId(int* position);

void changeHeadCommit(unsigned int commitID);

void checkout(char* commitString);
#endif