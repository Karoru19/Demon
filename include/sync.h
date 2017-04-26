#ifndef SYNC_H
#define SYNC_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <unistd.h>

#include "list.h"
#include "config.h"
#include "cstring.h"
#include "dir.h"
#include "file.h"
#include "modtime.h"

void syncDir (config Conf);

#endif
