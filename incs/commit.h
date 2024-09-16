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

struct _commitInfo
{
    unsigned int ID;
    time_t date;
    char message[commitLenght];
    user autor;
};
typedef struct _commitInfo commit;

#include "list.h"

void printCommit(commit commitInfo);

void createCommit(char* message);

void saveCommit(char* filename, commit commitInfo);

int createCommitDir(commit commitInfo);

int readCommit(FILE* logFile, commit* commitInfo);

int loggingCommits();

unsigned int nextCommitId();

unsigned int mainCommitId(int* position);

unsigned int headCommitId(int* position);
#endif