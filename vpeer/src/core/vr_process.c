#include "vr_config.h"
#include "vr_core.h"

static u_char  master_process[] = "master process";

vr_uint_t    vr_process;

static void
vr_start_worker_processes(vr_context_t *vr_context)
{
	vr_core_conf_t *ccf;
	
	ccf = vr_context->ccf;
	
	
}

void
vr_master_process(vr_context_t *vr_context)
{
	char              *title;
	size_t             size;
	u_char            *p;
	vr_int_t          i;
	
	vr_process = VR_PROCESS_MASTER;
	
	size = sizeof(master_process);
	
	for (i = 0; i < vr_argc; i++) {
        size += vr_strlen(vr_argv[i]) + 1;
    }
	
	title = vr_malloc(size);
	
	p = vr_cpymem(title, master_process, sizeof(master_process) - 1);
    for (i = 0; i < vr_argc; i++) {
        *p++ = ' ';
        p = vr_cpystrn(p, (u_char *) vr_argv[i], size);
    }

    vr_setproctitle(title);
	
	vr_start_worker_processes(vr_context);
}