#ifndef SYNC_H
#define SYNC_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include "list.h"
#include "config.h"
#include "cstring.h"

bool initSync(config *conf);
bool syncDir ();

#endif
