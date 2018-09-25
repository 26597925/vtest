#ifndef _VR_SOCKET_
#define _VR_SOCKET_

#include "vr_config.h"

typedef int  vr_socket_t;

#define vr_socket          socket
#define vr_socket_n        "socket()"

#define vr_accept 		   accept
#define vr_accept_n 	   "accept()"

#define vr_bind			   bind
#define vr_bind_n		   "bind()"

#define vr_connect 		   connect
#define vr_connect_n 	   "connect()"

#define vr_getpeername 	   getpeername
#define vr_getpeername_n   "getpeername()"

#define vr_getsockname     getsockname
#define vr_getsockname_n   "getsockname()"

#define vr_getsockopt 	   getsockopt
#define vr_getsockopt_n    "getsockopt()"

#define vr_listen		   listen
#define vr_listen_n		   "listen()"

#define vr_recv 		   recv
#define vr_recv_n 		   "recv()"

#define vr_recvfrom		   recvfrom
#define vr_recvfrom_n	   "recvfrom()"

#define vr_recvmsg		   recvmsg
#define vr_recvmsg_n	   "recvmsg()"

#define vr_send			   send
#define vr_send_n		   "send()"

#define vr_sendto		   sendto
#define vr_sendto_n		   "sendto()"
   
#define vr_sendmsg		   sendmsg
#define vr_sendmsg_n	   "sendmsg()"

#define vr_setsockopt      setsockopt
#define vr_setsockopt_n    "setsockopt()"

#define vr_socketpair	   socketpair
#define vr_socketpair_n	   "socketpair()"

#define vr_select	 	   select
#define vr_select_n	 	   "select()"

#if (VR_FIONBIO)

int vr_nonblocking(vr_socket_t s);
int vr_blocking(vr_socket_t s);

#define vr_nonblocking_n   "ioctl(FIONBIO)"
#define vr_blocking_n      "ioctl(!FIONBIO)"

#else

#define vr_nonblocking(s)  fcntl(s, F_SETFL, fcntl(s, F_GETFL) | O_NONBLOCK)
#define vr_nonblocking_n   "fcntl(O_NONBLOCK)"

#define vr_blocking(s)     fcntl(s, F_SETFL, fcntl(s, F_GETFL) & ~O_NONBLOCK)
#define vr_blocking_n      "fcntl(!O_NONBLOCK)"

#endif

int vr_tcp_nopush(vr_socket_t s);
int vr_tcp_push(vr_socket_t s);

#if (VR_LINUX)

#define vr_tcp_nopush_n   "setsockopt(TCP_CORK)"
#define vr_tcp_push_n     "setsockopt(!TCP_CORK)"

#else

#define vr_tcp_nopush_n   "setsockopt(TCP_NOPUSH)"
#define vr_tcp_push_n     "setsockopt(!TCP_NOPUSH)"

#endif

#define vr_shutdown_socket    shutdown
#define vr_shutdown_socket_n  "shutdown()"

#define vr_close_socket    close
#define vr_close_socket_n  "close() socket"

#endif