#ifndef MODTIME_H
#define MODTIME_H

#include <sys/stat.h>
#include <utime.h>
#include "bool.h"

bool compareTime(char* source, char *target);
void setTime(char* source, char* target);

#endif
