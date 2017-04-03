#include "config.h"

config default () {
	config conf;
	conf.recursive = false;
	conf.time = 5 * minute;
	conf.byte = MB;
	return conf;
}
