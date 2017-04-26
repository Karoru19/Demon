#ifndef DIR_H
#define DIR_H

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <unistd.h>
#include "cstring.h"
#include "list.h"
#include "config.h"

#define DIRECTORY 1
#define REGULAR 2
#define UNKNOWN -1

bool isDirectory(const char* path);
int getFileType (const char* path);
list *checkDirectory(char *path, bool recursive, list *first);
void deleteFiles(config Conf);

#endif
