#ifndef _VR_EVENT_
#define _VR_EVENT_

#include "../core/vr_config.h"
#include "../core/vr_core.h"

struct vr_event_s {
	void * s;
	int read;
	int write;
};

typedef struct {
    vr_int_t  (*vr_event_add)(vr_socket_t sock, void *ud);
	
    void  (*vr_event_del)(vr_socket_t sock);
	
    void  (*vr_event_write)(vr_socket_t sock, void *ud, int flags);
	
	vr_int_t   (*vr_event_wait)(struct vr_event_s *e, int max);
} vr_event_actions_t;

typedef struct {
    vr_str_t  *name;
	
	vr_int_t  (*vr_event_create)();
	
	vr_event_actions_t  actions;
	
    void       (*vr_event_release)();
} vr_event_module_t;

#endif