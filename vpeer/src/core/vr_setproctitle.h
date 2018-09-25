#ifndef _VR_SETPROCTITLE_
#define _VR_SETPROCTITLE_

#if (VR_SOLARIS)
#define VR_SETPROCTITLE_PAD       ' '
#elif (VR_LINUX) || (VR_DARWIN)
#define VR_SETPROCTITLE_PAD       '\0'
#endif

#if (HAVE_SETPROCTITLE)
#define vr_init_setproctitle() VR_OK
#define vr_setproctitle(title)    setproctitle("%s", title)
#else
vr_int_t vr_init_setproctitle();
void vr_setproctitle(char *title);
#endif

extern int            vr_argc;
extern char         **vr_argv;
extern char         **vr_os_argv;

#endif
