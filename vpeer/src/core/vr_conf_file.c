#include "vr_config.h"
#include "vr_core.h"

enum States
{
	START,
	NEW_SECTION,	
	IN_SECTION,
	END_OF_FILE
};

struct read_conf
{
	char *filename;
	FILE *fin;
	char *tmp;
	int tmp_cap;
	int current_line;
	int state;
};

static int
read_line(struct read_conf *read_conf)
{
	int i = 0;
	int b;
	int new = 0;

	for(;;)
	{
		char c;

		if(i >= read_conf->tmp_cap)
		{
			read_conf->tmp_cap *= 2;
			read_conf->tmp = vr_realloc(read_conf->tmp, sizeof(*read_conf->tmp) * read_conf->tmp_cap);
		}

		b = getc(read_conf->fin);

		if(b == EOF)
		{
			read_conf->state = END_OF_FILE;
			break;
		}

		c = b;
		if(c == '\r' || c == '\n')
        {
            read_conf->current_line++;
			break;
        }

		read_conf->tmp[i++] = c;		
		new = 1;
	}
	
	if(new)
		read_conf->tmp[i] = '\0';

	return new;
}

static struct section *
parse_section(struct read_conf *read_conf)
{
	int new;
	struct section *section = vr_malloc(sizeof(*section));
	section->num_configs = 0;
	section->configs = NULL;

	for(;;)
	{
		new = 0;

		switch(read_conf->state)
		{
		case START:
		case IN_SECTION:
			new = read_line(read_conf);
			break;
		case NEW_SECTION:
			new = 1;
			break;
		case END_OF_FILE:
			return section;
		default:
			printf("invalid state %d in parse_section\n", read_conf->state);
			break;
		}

		if(new)
		{
			int i, x, y, b=0, e=strlen(read_conf->tmp);
			struct config *cfg;
			vr_trim(read_conf->tmp, &b, &e);

			if(read_conf->tmp[b] == '#' || read_conf->tmp[b] == ';')
				continue;

			if(read_conf->tmp[b] == '[')
			{
				if(read_conf->state == IN_SECTION)
				{
					read_conf->state = NEW_SECTION;
					break;
				}
				else
				{
					read_conf->tmp[e] = '\0';
					section->name = vr_strdup(&read_conf->tmp[b+1]);
					
					read_conf->state = IN_SECTION;
					continue;
				}
			}

			cfg = vr_malloc(sizeof(*cfg));

			for(i=b; i<=e; i++)		
			{
				char c = read_conf->tmp[i];
				if(c == ':' || c == '=')
					break;
			}
			x = b; y = i;
			vr_trim(read_conf->tmp, &x, &y);
			read_conf->tmp[y+1] = '\0';
			cfg->key = vr_strdup(&read_conf->tmp[x]);
			
			x = i+1;
			y = e+1;
			vr_trim(read_conf->tmp, &x, &y);
			read_conf->tmp[y+1] = '\0';
			cfg->value = vr_strdup(&read_conf->tmp[x]);
			
			if(section->configs)
			{
				section->num_configs++;
				section->configs = vr_realloc(section->configs, sizeof(*section->configs) * section->num_configs);
			}
			else
			{
				section->configs = vr_malloc(sizeof(*section->configs));
				section->num_configs = 1;
			}
			section->configs[section->num_configs-1] = cfg;
		}
	}

	return section;
}

static struct conf*
parse_conf(struct read_conf *read_conf)
{
	struct conf *conf = vr_malloc(sizeof(*conf));
	char finished = 0;

	conf->num_sections = 0;
	conf->sections = NULL;

	while(!finished)
	{
		switch(read_conf->state)
		{
		case START:
		case NEW_SECTION:
		{
			struct section * section = parse_section(read_conf);

			if(!section)
				break;

			if(conf->sections)
			{
				conf->num_sections++;
				conf->sections = vr_realloc(conf->sections, sizeof(*conf->sections) * conf->num_sections);
			}
			else
			{
				conf->sections = vr_malloc(sizeof(*conf->sections));			
				conf->num_sections = 1;
			}
			conf->sections[conf->num_sections-1] = section;
			break;
		}
		case END_OF_FILE:
			finished = 1;
			break;
		default:
			printf("error parsing file at line %d\n", read_conf->current_line);
			finished = 1;
			break;
		}
	}

	return conf;
}

struct conf*
read_conf(struct read_conf **read_confp,
		 char *filename)
{
	struct conf *conf;    
    struct read_conf *read_conf = *read_confp;
    if((access(filename, F_OK))==-1) 
		return NULL;
    if(!read_conf)
    {
        read_conf = vr_malloc(sizeof(*read_conf));
        *read_confp = read_conf;
    }
    else
    {
        vr_free(read_conf->tmp);
    }
	read_conf->filename = filename;
	read_conf->current_line = 0;
	read_conf->state = START;
	read_conf->tmp = vr_malloc(sizeof(*read_conf->tmp) * 4);
	read_conf->tmp_cap = 4;
	read_conf->fin = fopen(filename, "r");

	conf = parse_conf(read_conf);

	fclose(read_conf->fin);
	return conf;
}

char *
conf_get_value(struct conf* conf,
              char *section,
              char *key)
{
    int s, c;
	for(s=0; s<conf->num_sections; s++)
	{
        if( vr_strcmp(section, conf->sections[s]->name) == 0 )
            for(c=0; c<conf->sections[s]->num_configs; c++)
                if( vr_strcmp(key, conf->sections[s]->configs[c]->key) == 0)
                    return conf->sections[s]->configs[c]->value;        
	}

    return NULL;
}

void
destroy_conf(struct conf* conf)
{
	int s, c;
	for(s=0; s<conf->num_sections; s++)
	{
		for(c=0; c<conf->sections[s]->num_configs; c++)
		{
			vr_free(conf->sections[s]->configs[c]->key);
			vr_free(conf->sections[s]->configs[c]->value);
		}
		vr_free(conf->sections[s]->name);
		vr_free(conf->sections[s]->configs);
	}

	vr_free(conf->sections);
	vr_free(conf);
}

void
cleanup_readconf(struct read_conf* read_conf)
{
    vr_free(read_conf->tmp);
    vr_free(read_conf);
}
