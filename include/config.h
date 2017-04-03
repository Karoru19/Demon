#ifndef CONFIG_H
#define CONFIG_H

#include <stdlib.h>
#include "string.h"

#define minute 60
#define hour ( 60 * minute )
#define kB 1024
#define MB ( 1024 * kB )
#define GB ( 1024 * MB )

struct config {
	bool recursive;
	int time;
	size_t byte;
	string pathFrom;
	string pathTo;
};

config default ();

#endif