#ifndef _VR_CONTEXT_
#define _VR_CONTEXT_

#include "vr_config.h"
#include "vr_core.h"

typedef struct {
	vr_int_t log_fd;
	
	struct read_conf *conf_r;
} vr_core_conf_t;

struct vr_context_s {
	struct conf *conf;
	
	vr_core_conf_t *ccf;
};

vr_int_t vr_init_context(vr_context_t *vr_context, u_char  *vr_conf_file);

void vr_destroy_context(vr_context_t *vr_context);

#endif