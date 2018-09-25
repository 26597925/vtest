#ifndef _VR_MODULE_H_
#define _VR_MODULE_H_

struct vr_context;

typedef void * (*vr_dl_create)(void);
typedef int (*vr_dl_init)(void * inst, struct vr_context *, const char * parm);
typedef void (*vr_dl_release)(void * inst);
typedef void (*vr_dl_signal)(void * inst, int signal);

struct vr_module {
	const char * name;
	void * module;
	vr_dl_create create;
	vr_dl_init init;
	vr_dl_release release;
	vr_dl_signal signal;
};

void vr_module_insert(struct vr_module *mod);
struct vr_module * vr_module_query(const char * name);
void * vr_module_instance_create(struct vr_module *);
int vr_module_instance_init(struct vr_module *, void * inst, struct vr_context *ctx, const char * parm);
void vr_module_instance_release(struct vr_module *, void *inst);
void vr_module_instance_signal(struct vr_module *, void *inst, int signal);

void vr_module_init(const char *path);

#endif
