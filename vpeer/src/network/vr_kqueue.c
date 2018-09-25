#include "../core/vr_config.h"
#include "../core/vr_core.h"
#include "vr_event.h"

#if (BUILD_EVENT == BUILD_KQUEUE)
static int kq = -1;

static vr_int_t
vr_kqueue_create() 
{
	kq = kqueue();
	
	if(kq == -1)
	{
		return VR_ERROR;
	}
	
	return VR_OK;
}

static void
vr_kqueue_release() 
{
	close(kq);
}

static void 
vr_kqueue_del(vr_socket_t sock) 
{
	struct kevent ke;
	EV_SET(&ke, sock, EVFILT_READ, EV_DELETE, 0, 0, NULL);
	kevent(kq, &ke, 1, NULL, 0, NULL);
	EV_SET(&ke, sock, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
	kevent(kq, &ke, 1, NULL, 0, NULL);
}

static vr_int_t 
vr_kqueue_add(vr_socket_t sock, void *ud) 
{
	struct kevent ke;
	EV_SET(&ke, sock, EVFILT_READ, EV_ADD, 0, 0, ud);
	if (kevent(kq, &ke, 1, NULL, 0, NULL) == -1) {
		return VR_ERROR;
	}
	EV_SET(&ke, sock, EVFILT_WRITE, EV_ADD, 0, 0, ud);
	if (kevent(kq, &ke, 1, NULL, 0, NULL) == -1) {
		EV_SET(&ke, sock, EVFILT_READ, EV_DELETE, 0, 0, NULL);
		kevent(kq, &ke, 1, NULL, 0, NULL);
		return VR_ERROR;
	}
	EV_SET(&ke, sock, EVFILT_WRITE, EV_DISABLE, 0, 0, ud);
	if (kevent(kq, &ke, 1, NULL, 0, NULL) == -1) {
		sp_del(kq, sock);
		return VR_ERROR;
	}
	return VR_OK;
}

static void 
vr_kqueue_write(vr_socket_t sock, void *ud, int flags) 
{
	struct kevent ke;
	EV_SET(&ke, sock, EVFILT_WRITE, flags ? EV_ENABLE : EV_DISABLE, 0, 0, ud);
	if (kevent(kq, &ke, 1, NULL, 0, NULL) == -1) {
		// todo: check error
	}
}

static vr_int_t 
vr_kqueue_wait(struct vr_event_s *e, int max) 
{
	struct kevent ev[max];
	int n = kevent(kq, NULL, 0, ev, max, NULL);

	int i;
	for (i=0;i<n;i++) {
		e[i].s = ev[i].udata;
		unsigned filter = ev[i].filter;
		e[i].write = (filter == EVFILT_WRITE);
		e[i].read = (filter == EVFILT_READ);
	}

	return n;
}

static vr_str_t  kqueue_name = vr_string("kqueue");

vr_event_module_t vr_kqueue_event = {
	.name           = &kqueue_name,
	.vr_event_create = vr_kqueue_create,
	{
		.vr_event_add = vr_kqueue_add,
        .vr_event_del = vr_kqueue_del,
		.vr_event_write = vr_kqueue_write,
		.vr_event_wait = vr_kqueue_wait,
	},
	.vr_event_release = vr_kqueue_release,
};
#endif