#ifndef PARSE_H
#define PARSE_H

#include "config.h"
#include "dir.h"
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <syslog.h>

bool parse (int argc, char* argv[], config *Config);

#endif
