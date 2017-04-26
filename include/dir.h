#ifndef DIR_H
#define DIR_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include "cstring.h"

#define DIRECTORY 1
#define REGULAR 2
#define UNKNOWN -1

bool isDirectory(const char* path);
int getFileType (const char* path);
void checkDirectory (const char *path, bool recursive);

#endif
