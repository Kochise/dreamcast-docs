#ifndef _NEWLIB_STDIO_H
#define _NEWLIB_STDIO_H

// Cribbed from newlib sys/stdio.h

/* Internal locking macros, used to protect stdio functions.  In the
   general case, expand to nothing. */
#if !defined(_flockfile)
#  define _flockfile(fp)
#endif

#if !defined(_funlockfile)
#  define _funlockfile(fp)
#endif

// Added for old KOS source compatability
#include <kos/dbglog.h>

#endif /* _NEWLIB_STDIO_H */
