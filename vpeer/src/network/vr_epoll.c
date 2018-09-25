#include "../core/vr_config.h"
#include "../core/vr_core.h"
#include "vr_event.h"

#if (BUILD_EVENT == BUILD_EPOLL)
static int ep = -1;

static vr_int_t
vr_epoll_create() 
{
	ep = epoll_create(1024);
	
	if(ep == -1)
	{
		return VR_ERROR;
	}
	
	return VR_OK;
}

static void
vr_epoll_release() 
{
	close(ep);
}

static vr_int_t
vr_epoll_add(vr_socket_t sock, void *ud)
{
	struct epoll_event   ev;

	ev.events = EPOLLIN;
	ev.data.ptr = ud;
	if (epoll_ctl(ep, EPOLL_CTL_ADD, sock, &ev) == -1) {
		return VR_ERROR;
	}
	return VR_OK;
}

static void
vr_epoll_del(vr_socket_t sock) 
{
	epoll_ctl(ep, EPOLL_CTL_DEL, sock , NULL);
}

static void
vr_epoll_write(vr_socket_t sock, void *ud, int flags) 
{
	struct epoll_event ev;
	ev.events = EPOLLIN | (flags ? EPOLLOUT : 0);
	ev.data.ptr = ud;
	epoll_ctl(ep, EPOLL_CTL_MOD, sock, &ev);
}

static vr_int_t
vr_epoll_wait(struct vr_event_s *e, int max) 
{
	struct epoll_event ev[max];
	int n = epoll_wait(ep , ev, max, -1);
	int i;
	for (i=0;i<n;i++) {
		e[i].s = ev[i].data.ptr;
		unsigned flag = ev[i].events;
		e[i].write = (flag & EPOLLOUT) != 0;
		e[i].read = (flag & EPOLLIN) != 0;
	}

	return n;
}

static vr_str_t  epoll_name = vr_string("epoll");

vr_event_module_t vr_epoll_event = {
	.name           = &epoll_name,
	.vr_event_create = vr_epoll_create,
	{
		.vr_event_add = vr_epoll_add,
        .vr_event_del = vr_epoll_del,
		.vr_event_write = vr_epoll_write,
		.vr_event_wait = vr_epoll_wait,
	},
	.vr_event_release = vr_epoll_release,
};
#endif