#include "vr_config.h"
#include "vr_core.h"

static u_char      *vr_conf_file;
static char        *vr_signal;

static vr_int_t
vr_save_argv(int argc, char **argv)
{
#if (VR_FREEBSD)

    vr_os_argv = (char **) argv;
    vr_argc = argc;
    vr_argv = (char **) argv;

#else
    size_t     len;
    vr_int_t  i;

    vr_os_argv = (char **) argv;
    vr_argc = argc;

    vr_argv = vr_malloc((argc + 1) * sizeof(char *));
    if (vr_argv == NULL) {
        return VR_ERROR;
    }

    for (i = 0; i < argc; i++) {
        len = vr_strlen(argv[i]) + 1;

        vr_argv[i] = vr_malloc(len);
        if (vr_argv[i] == NULL) {
            return VR_ERROR;
        }

        (void) vr_cpystrn((u_char *) vr_argv[i], (u_char *) argv[i], len);
    }

    vr_argv[i] = NULL;

#endif

    return VR_OK;
}

static vr_int_t
vr_get_options(int argc, char **argv)
{
	u_char     *p;
    vr_int_t   i;

    for (i = 1; i < argc; i++) {

        p = (u_char *) argv[i];

        if (*p++ != '-') {
            return VR_ERROR;
        }
		
		switch (*p++) {
			case 'c':
				if (*p) {
                    vr_conf_file = p;
                    goto next;
                }

                if (argv[++i]) {
                    vr_conf_file = (u_char *) argv[i];
                    goto next;
                }
				return VR_ERROR;
			break;
			case 's':
				if (*p) {
                    vr_signal = (char *) p;

                } else if (argv[++i]) {
                    vr_signal = argv[i];

                } else {
                    return VR_ERROR;
                }

                if (vr_strcmp(vr_signal, "stop") == 0
                    || vr_strcmp(vr_signal, "quit") == 0
                    || vr_strcmp(vr_signal, "reload") == 0)
                {
                    goto next;
                }

                return VR_ERROR;
			break;
		}
		
	next:
        continue;
	}
	return VR_OK;
}

int main(int argc, char **argv)
{
	vr_context_t *vr_context;
	
	vr_context = (vr_context_t *) vr_malloc(sizeof(vr_context_t));
	
	if(vr_context == NULL)
		return 1;
	
	if(vr_save_argv(argc, argv) != VR_OK)
		return 1;
	
	if(vr_get_options(argc, argv) != VR_OK)
		return 1;
	
	if(vr_signal != NULL)
	{
		printf("call %s %s %d %s\n",__FILE__, __FUNCTION__, __LINE__, vr_signal);
		vr_daemon_exit(VR_DAEMON);
		return 1;
	}
	
	if(vr_init_context(vr_context, vr_conf_file) != VR_OK)
		return 1;
	
	if(vr_init_log(vr_context) != VR_OK)
		return 1;
	
	if(vr_daemon_init(VR_DAEMON) != VR_OK)
		return 1;
	
	if(vr_init_setproctitle() != VR_OK) 
		return 1;
	
	vr_master_process(vr_context);
	
	sleep(1000);
	
	return 0;
}