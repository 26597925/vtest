#ifndef _VR_CONFIG_H_
#define _VR_CONFIG_H_

#define VR_DAEMON "vpeer.pid"

#define VR_LINUX 1
/*
#define VR_SOLARIS 1
#define VR_DARWIN 1
#define VR_FREEBSD 1
*/
	
/* FreeBSD, NetBSD, OpenBSD */
#define HAVE_SETPROCTITLE 0 

#define BUILD_EPOLL  1
#define BUILD_KQUEUE 2
	
#ifndef BUILD_EVENT
#define BUILD_EVENT  BUILD_EPOLL
#endif

#if (VR_LINUX)
#include "../os/vr_linux_config.h"
#endif

/*todo: linux kernel > 3.9 
#ifndef HAVE_REUSEPORT
#define HAVE_REUSEPORT
#endif
*/

#ifndef VR_PTHREAD_LOCK
#define VR_PTHREAD_LOCK  0
#endif

/* TODO: RAW JEMALLOC TCMALLOC*/
#define RAW 0
#define JEMALLOC 1
#define TCMALLOC 2
	
#ifndef VR_MALLOC_TYPE
#define VR_MALLOC_TYPE  RAW
#endif

/* TODO: inline __inline __inline__ */
#ifndef vr_inline
#define vr_inline  inline
#endif
	
#define IP4 1
#define IP6 2

#ifndef VR_IP_TYPE
#define VR_IP_TYPE  IP4
#endif
	
#define SOCKET_UNIX  1
#define SOCKET_ANY  2
#define SOCKET_OTHER 3
	
#if (VR_IP_TYPE == IP4)
typedef struct sockaddr_in vr_socketaddr;
#else
typedef struct sockaddr_in6 vr_socketaddr;
#endif

typedef unsigned char  u_char;

typedef intptr_t    vr_int_t;
typedef uintptr_t   vr_uint_t;
typedef intptr_t    vr_flag_t;
	
#endif