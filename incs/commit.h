#ifndef COMMIT
#define COMMIT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "user.h"
#include "hash.h"

struct _commitInfo
{
    unsigned int hash;
    time_t date;
    user autor;
    char *message;
};
typedef struct _commitInfo commit;

void createCommit(char* message);
#endif