#ifndef DIR_H
#define DIR_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "cstring.h"

bool isDirectory(string path);
void check_directory (string argv, bool recursive);

#endif
