#ifndef _ITIMER_H
#ifdef __cplusplus
extern "C" {
#endif
#define _ITIMER_H
#include <_ansi.h>
#include <sys/time.h>

#define ITIMER_REAL     0
#define ITIMER_VIRTUAL  1
#define ITIMER_PROF     2

struct  itimerval {
  struct  timeval it_interval;
  struct  timeval it_value;
};

int _EXFUN(getitimer,( int which, struct itimerval *value ));
int _EXFUN(setitimer,( int which, struct itimerval *newval, struct itimerval *oldval ));
#ifdef __cplusplus
}
#endif
#endif
