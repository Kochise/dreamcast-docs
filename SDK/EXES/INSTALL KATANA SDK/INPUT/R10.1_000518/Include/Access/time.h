/************************************************************************/
/*    AVE-TCP Socket Library        time.h            92/04/15          */
/*       Copyright (C) 1992 ACCESS CO.,LTD.                             */
/************************************************************************/

#ifdef __cplusplus /* Support for C++ */
extern "C" {
#endif /* __cplusplus */

#ifndef TIME_H
#define TIME_H
/* 
 * Structure returnes by gettimeofday(2) system call,
 * and used in other calls.
 */
struct timeval {
	long	tv_sec;		/* seconds */
	long	tv_usec;	/* and microseconds */
};

#endif

#ifdef __cplusplus
} /* End of extern "C" { */
#endif /* __cplusplus */
