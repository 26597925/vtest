#ifndef _VR_CONFFILE_
#define _VR_CONFFILE_

#include "vr_config.h"
#include "vr_core.h"

struct config
{
	char *key;
	char *value;
};

struct section
{
	char *name;
	int num_configs;
	struct config **configs;
};

struct conf
{
	int num_sections;
	struct section **sections;	
};

struct read_conf;

struct conf* read_conf(struct read_conf **read_confp, char *filename);

char *conf_get_value(struct conf* conf, char *section, char *key);

void destroy_conf(struct conf* conf);

void cleanup_readconf(struct read_conf* read_conf);

#endif
