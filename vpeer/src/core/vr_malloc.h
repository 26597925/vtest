#ifndef _VR_MALLOC_H_
#define _VR_MALLOC_H_

#if (VR_MALLOC_TYPE == JEMALLOC)

#include <jemalloc.h>

#define vr_malloc je_malloc
#define vr_calloc je_calloc
#define vr_realloc je_realloc
#define vr_free je_free

#elif (VR_MALLOC_TYPE == TCMALLOC)

#include <tcmalloc.h>

#define vr_malloc tc_malloc
#define vr_calloc tc_calloc
#define vr_realloc tc_realloc
#define vr_free tc_free

#else

#include <malloc.h>

#define vr_malloc malloc
#define vr_calloc calloc
#define vr_realloc realloc
#define vr_free free

#endif

#endif