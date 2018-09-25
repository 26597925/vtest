#include "../core/vr_config.h"
#include "../core/vr_core.h"
#include "vr_basesocket.h"

struct vr_tcp_s {
	vr_socket_t sock;
	int socket_domain;
	char *source_host;
	int *source_port;
	int listen_backlog;
};

vr_int_t  
vr_tcp_create(vr_tcp_t * vr_tcp)
{
	if(vr_tcp == NULL)
	{
		return VR_ERROR;
	}
	
	vr_socket_t sock = vr_create_socket(vr_tcp->socket_domain, SOCK_STREAM);
	
	if(sock == -1)
	{
		return VR_ERROR;
	}
	
	vr_tcp->sock = sock;
	
	return VR_OK;
}

vr_int_t 
vr_tcp_listen(vr_tcp_t * vr_tcp)
{	
	if(vr_config_reuse(vr_tcp->sock) == VR_ERROR)
	{
		return VR_ERROR;
	}
	
	if(vr_socket_bind(vr_tcp->sock, 
		vr_tcp->socket_domain, 
		vr_tcp->source_host, 
		vr_tcp->source_port) == VR_ERROR)
	{
		return VR_ERROR;
	}

	if (vr_listen(vr_tcp->sock, vr_tcp->listen_backlog) == -1) 
	{
		return VR_ERROR;
	}
	
	return VR_OK;
}

vr_socket_t 
vr_tcp_accept(vr_socket_t sock, vr_socketaddr client_addr, socklen_t client_addrlen)
{
	vr_socket_t new_sock;
	client_addrlen = sizeof(client_addr);
	
#ifdef HAVE_ACCEPT4
    new_sock = accept4(sock, (struct sockaddr *) &client_addr, &client_addrlen, SOCK_NONBLOCK);
#else
    new_sock = accept(sock, (struct sockaddr *) &client_addr, &client_addrlen);
#endif
	
	if (new_sock < 0)
    {
		return -1;
	}
	
#ifndef HAVE_ACCEPT4
	vr_nonblocking(new_sock);
#endif
	
	return new_sock;
}

vr_int_t
vr_tcp_connect(vr_tcp_t * vr_tcp)
{
	int ret;
	
	vr_socketaddr socketaddr;
	struct sockaddr_un addr_un;
	socklen_t len;
	
	if(vr_tcp->socket_domain == SOCKET_UNIX)
	{
		bzero(&addr_un, sizeof(addr_un));//memset((void*)s, 0,size_tn)
        unlink(vr_tcp->source_host);
        addr_un.sun_family = AF_UNIX;
        strncpy(addr_un.sun_path, vr_tcp->source_host, sizeof(addr_un.sun_path) - 1);
		ret = vr_connect(vr_tcp->sock, (struct sockaddr*) &addr_un, sizeof(addr_un));
	}else
	{
		bzero(&socketaddr, sizeof(socketaddr));
#if (VR_IP_TYPE == IP4)
		socketaddr.sin_family = AF_INET;
		if(inet_pton(AF_INET, vr_tcp->source_host, &socketaddr.sin_addr) == 0)
		{
			return VR_ERROR;
		}
		socketaddr.sin_port = htons(*(vr_tcp->source_port));
#else
		socketaddr.sin6_family = AF_INET6;
		if(inet_pton(AF_INET6, vr_tcp->source_host, &socketaddr.sin6_addr) < 0)
		{
			return VR_ERROR;
		}
		socketaddr.sin6_port = (uint16_t) htons(*(vr_tcp->source_port));
#endif
		ret = vr_connect(vr_tcp->sock, (struct sockaddr *) &socketaddr, sizeof(socketaddr));
		if (ret == 0 && *(vr_tcp->source_port) == 0)
        {
            len = sizeof(socketaddr);
            if (vr_getsockname(vr_tcp->sock, (struct sockaddr *) &socketaddr, &len) != -1)
            {
#if (VR_IP_TYPE == IP4)
				*(vr_tcp->source_port) = ntohs(socketaddr.sin_port);
#else
                *(vr_tcp->source_port) = ntohs(socketaddr.sin6_port);
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

ssize_t 
vr_recv_peek(vr_tcp_t * vr_tcp, void *buf, size_t len)    
{   
	int ret = -1;
    while (1)    
    {    
        ret = vr_recv(vr_tcp->sock, buf, len, MSG_PEEK);
		
        if (ret == -1 && errno == EINTR)    
            continue;
		
        break;
    }
	
	return ret;
}

ssize_t 
vr_tcp_read(vr_tcp_t * vr_tcp, void *buf, size_t count)    
{    
    size_t len = count;    
    ssize_t read_len = 0;    
    char *temp_buf = (char *)buf;    
    while (len > 0)    
    {    
        if ((read_len = read(vr_tcp->sock, temp_buf, len)) < 0)    
        {      
            if (errno == EINTR)    
                continue;
            else    
                return -1;    
        }
        else if (read_len == 0)    
            return count - len;    
      
        len -= read_len;    
        temp_buf += read_len;    
    }    
    return count;    
}

ssize_t 
vr_tcp_write(vr_tcp_t * vr_tcp, const void *buf, size_t count)    
{    
    size_t  len = count;    
    ssize_t write_len = 0;    
    char *temp_buf = (char *)buf;    
    while (len > 0)    
    {    
        if ((write_len = write(vr_tcp->sock, temp_buf, len)) < 0)    
        {    
            if (errno == EINTR)    
                continue;    
            else    
                return -1;    
        }
        else if (write_len == 0)    
            continue;    
      
        len -= write_len;    
        temp_buf += write_len;    
    }    
    return count;    
}