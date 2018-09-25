#ifndef _VR_STRING_H_
#define _VR_STRING_H_

#include "vr_config.h"

#define vr_tolower(c)      (u_char) ((c >= 'A' && c <= 'Z') ? (c | 0x20) : c)
#define vr_toupper(c)      (u_char) ((c >= 'a' && c <= 'z') ? (c & ~0x20) : c)

typedef struct {
    size_t      len;
	u_char     *data;
} vr_str_t;

#define vr_string(str)     { sizeof(str) - 1, (u_char *) str }
#define vr_null_string     { 0, NULL }
#define vr_str_set(str, text)                                               \
    (str)->len = sizeof(text) - 1; (str)->data = (u_char *) text
#define vr_str_null(str)   (str)->len = 0; (str)->data = NULL
		
void vr_strlow(u_char *dst, u_char *src, size_t n);

#define vr_strncmp(s1, s2, n)  strncmp((const char *) s1, (const char *) s2, n)

#define vr_strcmp(s1, s2)  strcmp((const char *) s1, (const char *) s2)

#define vr_strstr(s1, s2)  strstr((const char *) s1, (const char *) s2)
#define vr_strlen(s)       strlen((const char *) s)

#define vr_strchr(s1, c)   strchr((const char *) s1, (int) c)

static vr_inline u_char *
vr_strlchr(u_char *p, u_char *last, u_char c)
{
    while (p < last) {

        if (*p == c) {
            return p;
        }

        p++;
    }

    return NULL;
}

#define vr_memzero(buf, n)       (void) memset(buf, 0, n)
#define vr_memset(buf, c, n)     (void) memset(buf, c, n)

#define vr_memcpy(dst, src, n)   (void) memcpy(dst, src, n)
#define vr_cpymem(dst, src, n)   (((u_char *) memcpy(dst, src, n)) + (n))

char * vr_strdup(char *str);

void vr_trim(char *str, int *begin_ind, int *end_ind);

u_char *vr_cpystrn(u_char *dst, u_char *src, size_t n);

#endif