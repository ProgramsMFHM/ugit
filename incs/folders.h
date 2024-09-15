#ifndef FOLDERS
#define FOLDERS
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include "hash.h"
#include "errors.h"

int folderExists(char *folderName);
int fileExists(char *filename);

int addFiles(int argc, char* argv[]);

int stageStatus();

#endif