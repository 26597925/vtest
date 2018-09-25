#ifndef _VR_DAEMON_H_
#define _VR_DAEMON_H_

vr_int_t vr_daemon_init(const char *pidfile);

vr_int_t vr_daemon_exit(const char *pidfile);

#endif
