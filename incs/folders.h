#ifndef FOLDERS
#define FOLDERS
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "folders.h"
#include <time.h>

int folderExists(char *folderName);
int fileExists(char *filename);

int addFiles(int argc, char* argv[]);

int stageStatus();

#endif