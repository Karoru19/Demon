#ifndef FILE_H
#define FILE_H

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h>
#include <assert.h>
#include <sys/mman.h>
#include <syslog.h>
#include "cstring.h"
#include "list.h"
#include "bool.h"

void createFile(char* path);
void copyRW(char* source, char* target);
void copyMmap(char* source, char* target);
ssize_t write_all (int fd, const void* buffer, size_t count);

#endif
