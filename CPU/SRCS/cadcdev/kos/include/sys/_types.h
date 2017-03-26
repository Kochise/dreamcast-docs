#ifndef _SYS__TYPES_H
#define _SYS__TYPES_H

// This part copied from newlib's sys/_types.h.
typedef long _off_t;
__extension__ typedef long long _off64_t;

#if defined(__INT_MAX__) && __INT_MAX__ == 2147483647
typedef int _ssize_t;
#else
typedef long _ssize_t;
#endif

#define __need_wint_t
#include <stddef.h>

/* Conversion state information.  */
typedef struct
{
  int __count;
  union
  {
    wint_t __wch;
    unsigned char __wchb[4];
  } __value;            /* Value so far.  */
} _mbstate_t;

typedef int _flock_t;

/* Iconv descriptor type */
typedef void *_iconv_t;


// This part inserted to fix newlib brokenness.
#define FD_SETSIZE 1024

// And this is for old KOS source compatability.
#include <arch/types.h>

// Include stuff to make pthreads work as well.
#include <sys/_pthread.h>

#endif	/* _SYS__TYPES_H */
