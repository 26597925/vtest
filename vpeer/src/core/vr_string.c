#include "vr_string.h"
#include "vr_malloc.h"

void 
vr_strlow(u_char *dst, u_char *src, size_t n)
{
	while (n) {
        *dst = vr_tolower(*src);
        dst++;
        src++;
        n--;
    }
}

char *
vr_strdup(char *str) {
	size_t sz = vr_strlen(str);
	char * ret = vr_malloc(sz+1);
	memcpy(ret, str, sz+1);
	return ret;
}

void
vr_trim(char *str, int *begin_ind, int *end_ind)
{
	int b = *begin_ind;
	int e = *end_ind;
	int i;

	for(i=b; i<e; i++)
	{
		char c = str[i];
		if(c != ' ' && c != '\t' && c != '\n' && c != '\r')
			break;
	}
	*begin_ind = i;
	
	for(i=e-1; i>=b; i--)
	{
		char c = str[i];
		if(c != ' ' && c != '\t' && c != '\n' && c != '\r')
			break;
	}
	*end_ind = i;
}

u_char *vr_cpystrn(u_char *dst, u_char *src, size_t n)
{
	if (n == 0) {
        return dst;
    }

    while (--n) {
        *dst = *src;

        if (*dst == '\0') {
            return dst;
        }

        dst++;
        src++;
    }

    *dst = '\0';

    return dst;
}