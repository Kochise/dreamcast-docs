/* This is file TIME.H */

/* time.h -- An implementation of the standard Unix <sys/time.h> file.
   Written by Geoffrey Noer <noer@cygnus.com>
   Public domain; no rights reserved. */

#ifndef _SYS_TIME_H_
#ifdef __cplusplus
extern "C" {
#endif
#define _SYS_TIME_H_

#include <_ansi.h>

#ifndef _GNU_H_WINDOWS32_SOCKETS
struct timeval {
  long tv_sec;
  long tv_usec;
};

struct timezone {
  int tz_minuteswest;
  int tz_dsttime;
};
#endif

/* Cygwin32 needs itimer headers */
#ifdef __CYGWIN32__
#define ITIMER_REAL     0
#define ITIMER_VIRTUAL  1
#define ITIMER_PROF     2

struct  itimerval {
  struct  timeval it_interval;
  struct  timeval it_value;
};

/* Functions provided by Cygwin32 */
int _EXFUN(gettimeofday, (struct timeval *p, struct timezone *z));
int _EXFUN(settimeofday, (const struct timeval *, const struct timezone *));
int _EXFUN(utimes, (const char *path, struct timeval *tvp));

#endif /* __CYGWIN32__ */

#ifdef __cplusplus
}
#endif
#endif /* _SYS_TIME_H_ */
