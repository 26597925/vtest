#ifndef _VR_LINUX_CONFIG_
#define _VR_LINUX_CONFIG_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/prctl.h>
#include <sys/file.h>
#include <signal.h>
#include <stdarg.h>
#include <time.h>

#if (BUILD_EVENT == BUILD_KQUEUE)
#include <sys/event.h>
#else
#include <sys/epoll.h>
#endif

#endif