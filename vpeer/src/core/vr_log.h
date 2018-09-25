#ifndef _VR_LOG_
#define _VR_LOG_

#include "vr_config.h"
#include "vr_core.h"

#define VR_LOG_BUFFER_SIZE 1024
#define VR_LOG_DATE_STRLEN  64
#define VR_LOG_LEVEL_STRLEN 7

typedef enum {
     VR_LOG_DEBUG = 0,
     VR_LOG_NOTICE,
	 VR_LOG_ERROR,
     VR_LOG_WARNING,
     VR_LOG_TRACE,
	 VR_LOG_INFO
} vr_log_level;

vr_int_t vr_init_log(vr_context_t *vr_context);

void vr_put_log(vr_context_t *vr_context, int level, char *cnt);

void vr_destroy_log(vr_context_t *vr_context);

#endif