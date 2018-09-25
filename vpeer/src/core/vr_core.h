#ifndef _VR_CORE_
#define _VR_CORE_

#include "vr_config.h"

typedef struct vr_context_s vr_context_t;
typedef struct vr_event_s   vr_event_t;

#define  VR_OK          0
#define  VR_ERROR      -1
#define  VR_AGAIN      -2
#define  VR_BUSY       -3
#define  VR_DONE       -4
#define  VR_DECLINED   -5
#define  VR_ABORT      -6

#include "vr_malloc.h"
#include "vr_string.h"
#include "vr_socket.h"
#include "vr_conf_file.h"
#include "vr_setproctitle.h"
#include "vr_daemon.h"
#include "vr_process.h"
#include "vr_context.h"
#include "vr_log.h"
#include "vpeer.h"

#define LF     (u_char) '\n'
#define CR     (u_char) '\r'
#define CRLF   "\r\n"


#define vr_abs(value)       (((value) >= 0) ? (value) : - (value))
#define vr_max(val1, val2)  ((val1 < val2) ? (val2) : (val1))
#define vr_min(val1, val2)  ((val1 > val2) ? (val2) : (val1))

#endif