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

struct _commitInfo
{
    time_t date;
    char *message;
    user autor;
};
typedef struct _commitInfo commit;

void createCommit(char* message);
#endif