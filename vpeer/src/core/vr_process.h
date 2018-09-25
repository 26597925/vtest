#ifndef _VR_PROCESS_
#define _VR_PROCESS_

#define VR_PROCESS_MASTER     1
#define VR_PROCESS_WORKER     2

#define VR_MAX_PROCESSES         1024

typedef void (*vr_spawn_proc_pt) (ngx_cycle_t *cycle, void *data);

typedef struct {
    vr_pid_t           pid;
    int                status;
    vr_socket_t        channel[2];

    vr_spawn_proc_pt   proc;
    void               *data;
    char               *name;

} vr_process_t;

extern vr_uint_t     vr_process;

extern vr_process_t  vr_processes[VR_MAX_PROCESSES];

void vr_master_process(vr_context_t *vr_context);

#endif