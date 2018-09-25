#ifndef _VR_BASESOCKET_
#define _VR_BASESOCKET_

#include "../core/vr_config.h"
#include "../core/vr_core.h"

//http://www.2cto.com/os/201510/445212.html
//http://www.cnblogs.com/zhanggaofeng/p/6137168.html
//http://blog.csdn.net/nk_test/article/details/49007761

typedef struct vr_tcp_s vr_tcp_t;
vr_int_t vr_tcp_create(vr_tcp_t * vr_tcp);
vr_int_t vr_tcp_listen(vr_tcp_t * vr_tcp);
vr_socket_t vr_tcp_accept(vr_socket_t sock, vr_socketaddr client_addr, socklen_t client_addrlen);
vr_int_t vr_tcp_connect(vr_tcp_t * vr_tcp);
ssize_t vr_recv_peek(vr_tcp_t * vr_tcp, void *buf, size_t len);
ssize_t vr_tcp_read(vr_tcp_t * vr_tcp, void *buf, size_t count);
ssize_t vr_tcp_write(vr_tcp_t * vr_tcp, const void *buf, size_t count);

typedef struct vr_udp_s vr_udp_t;

static vr_socket_t
vr_create_socket(int socket_domain, int socket_type)
{
	int domain;
	vr_socket_t sock;
	
	if(socket_domain == SOCKET_UNIX)
	{
		domain = PF_UNIX;
	}else
	{
#if (VR_IP_TYPE == IP4)
		domain = PF_INET;
#else
		domain = PF_INET6;
#endif
	}
	
	sock = socket(domain, socket_type, 0);
	
	return sock;
}

static vr_int_t 
vr_socket_bind(vr_socket_t sock, int socket_domain, char *host, int *port)
{
	int ret;
	
	vr_socketaddr socketaddr;
	struct sockaddr_un addr_un;
	socklen_t len;

	if(socket_domain == SOCKET_UNIX)
	{
		bzero(&addr_un, sizeof(addr_un));
        unlink(host);
        addr_un.sun_family = AF_UNIX;
        strncpy(addr_un.sun_path, host, sizeof(addr_un.sun_path) - 1);
		ret = vr_bind(sock, (struct sockaddr*) &addr_un, sizeof(addr_un));
	}else
	{
		bzero(&socketaddr, sizeof(socketaddr));
#if (VR_IP_TYPE == IP4)
		socketaddr.sin_family = AF_INET;
		if(socket_domain == SOCKET_ANY)
		{
			socketaddr.sin_addr.s_addr = htonl(INADDR_ANY);
		}else
		{
			if(inet_pton(AF_INET, host, &socketaddr.sin_addr) == 0)
			{
				return VR_ERROR;
			}
		}
		socketaddr.sin_port = htons(*port);
#else
		socketaddr.sin6_family = AF_INET6;
		if(socket_domain == SOCKET_ANY)
		{
			socketaddr.sin6_addr.s6_addr = htonl(IN6ADDR_ANY);
		}else
		{
			if(inet_pton(AF_INET6, host, &socketaddr.sin6_addr) < 0)
			{
				return VR_ERROR;
			}
		}
		socketaddr.sin6_port = (uint16_t) htons(*port);
#endif
		ret = vr_bind(sock, (struct sockaddr *) &socketaddr, sizeof(socketaddr));
		if (ret == 0 && *port == 0)
        {
            len = sizeof(socketaddr);
            if (vr_getsockname(sock, (struct sockaddr *) &socketaddr, &len) != -1)
            {
#if (VR_IP_TYPE == IP4)
				*port = ntohs(socketaddr.sin_port);
#else
                *port = ntohs(socketaddr.sin6_port);
#endif
            }
        }
	}
	
	if (ret < 0)
    {
        return VR_ERROR;
    }
	
	return VR_OK;
}

static vr_int_t
vr_config_reuse(vr_socket_t sock)
{
	int option = 1;
    if (vr_setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(int)) < 0)
    {
        return VR_ERROR;
    }
	
#ifdef HAVE_REUSEPORT
	if (vr_setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &option, sizeof(int)) < 0)
	{
		return VR_ERROR;
	}
#endif
	
	return VR_OK;
}

#endif