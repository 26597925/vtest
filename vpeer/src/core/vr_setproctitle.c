#include "vr_config.h"
#include "vr_core.h"

extern char **environ;

static char *vr_os_argv_last;

int              vr_argc;
char           **vr_argv;
char           **vr_os_argv;

vr_int_t
vr_init_setproctitle()
{
    u_char      *p;
    size_t      size;
    vr_uint_t   i;

    size = 0;

    for (i = 0; environ[i]; i++) {
        size += vr_strlen(environ[i]) + 1;
    }

    p = vr_malloc(size);
    if (p == NULL) {
        return VR_ERROR;
    }

    vr_os_argv_last = vr_os_argv[0];

    for (i = 0; vr_os_argv[i]; i++) {
        if (vr_os_argv_last == vr_os_argv[i]) {
            vr_os_argv_last = vr_os_argv[i] + vr_strlen(vr_os_argv[i]) + 1;
        }
    }

    for (i = 0; environ[i]; i++) {
        if (vr_os_argv_last == environ[i]) {

            size = vr_strlen(environ[i]) + 1;
            vr_os_argv_last = environ[i] + size;

            vr_cpystrn(p, (u_char *) environ[i], size);
            environ[i] = (char *) p;
            p += size;
        }
    }

    vr_os_argv_last--;

    return VR_OK;
}


void
vr_setproctitle(char *title)
{
    u_char     *p;

#if (VR_SOLARIS)

    ngx_int_t   i;
    size_t      size;

#endif

    vr_os_argv[1] = NULL;

    p = vr_cpystrn((u_char *) vr_os_argv[0], (u_char *) "vpeer: ",
                    vr_os_argv_last - vr_os_argv[0]);

    p = vr_cpystrn(p, (u_char *) title, vr_os_argv_last - (char *) p);

#if (VR_SOLARIS)

    size = 0;

    for (i = 0; i < vr_argc; i++) {
        size += vr_strlen(vr_argv[i]) + 1;
    }

    if (size > (size_t) ((char *) p - vr_os_argv[0])) {

        p = vr_cpystrn(p, (u_char *) " (", vr_os_argv_last - (char *) p);

        for (i = 0; i < vr_argv; i++) {
            p = vr_cpystrn(p, (u_char *) vr_argv[i],
                            vr_os_argv_last - (char *) p);
            p = vr_cpystrn(p, (u_char *) " ", vr_os_argv_last - (char *) p);
        }

        if (*(p - 1) == ' ') {
            *(p - 1) = ')';
        }
    }

#endif

    if (vr_os_argv_last - (char *) p) {
       vr_memset(p, VR_SETPROCTITLE_PAD, vr_os_argv_last - (char *) p);
    }

}
