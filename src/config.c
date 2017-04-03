#include "../include/config.h"

struct config default_default () {
	struct config conf;
	conf.recursive = false;
	conf.time = 5 * minute;
	conf.byte = MB;
	return conf;
}
