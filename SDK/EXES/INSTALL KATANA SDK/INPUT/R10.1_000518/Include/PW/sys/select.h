/*
 * select.h
 *
 * This is a direct implementation of the sys/select.h header file, from
 * IEEE P1003.1g/D6.1, the POSIX network specification,
 * section 6.2.1.
 *
 * Copyright 1996 PlanetWeb, Inc.
 * Created 13 Nov 96 by scole
 *
 * $Header: c:/planetweb/api/sys/h:/RCS/api/sys/select.h 1.5 1999-09-21 20:28:19-07 soohoo Exp $
 *
 * $Log: select.h $
 * Revision 1.5  1999-09-21 20:28:19-07  soohoo
 * Fixed FD_ZERO to loop on # of bytes not # of bits...
 *
 * Revision 1.4  1999-09-21 13:20:18-07  scole
 * Compiler fixes.
 *
 * Revision 1.3  1999-09-20 16:16:17-07  scole
 * Share the struct timeval with socket.h;
 * Remove the pselect prototype for now.
 *
 * Revision 1.2  1996-11-27 11:47:15-08  scole
 * Replaced tabs with blanks for better formatting.
 *
 * Revision 1.1  1996-11-18 11:47:53-0800  scole
 * Initial revision
 *
 */
#ifndef __SELECT_H__
#ifdef __cplusplus
extern "C" {
#endif
#define __SELECT_H__

#ifndef __SATURN__
#define __SATURN__ 0
#endif
#ifndef __PSX__
#define __PSX__ 0
#endif
#ifndef __PUMA__
#define __PUMA__ 0
#endif
#ifndef __VSURF__
#define __VSURF__ 0
#endif
#ifndef __MMATICS__
#define __MMATICS__ 0
#endif
#ifndef __TOSHIBA__
#define __TOSHIBA__ 0
#endif
#ifndef __KATANA__
#define __KATANA__ 0
#endif
	

#define FD_SETSIZE  256                 /* Maximum file descriptors in fd_set */

typedef struct {
    unsigned char set[(FD_SETSIZE + 7) / 8];
} fd_set;

#define FD_SET(fd, pset)                                    \
    do {                                                    \
        if ((fd) >= 0 && (fd) < FD_SETSIZE) {               \
            (pset)->set[(fd) >> 3] |= 1 << ((fd) & 0x07);   \
        }                                                   \
    } while (0)
#define FD_CLR(fd, pset)                                        \
    do {                                                        \
        if ((fd) >= 0 && (fd) <     FD_SETSIZE) {               \
            (pset)->set[(fd) >> 3] &= ~(1 << ((fd) & 0x07));    \
        }                                                       \
    } while (0)
#define FD_ISSET(fd, pset)                                  \
    (((fd) >= 0 && (fd) < FD_SETSIZE) ?                     \
        ((pset)->set[(fd)>>3] & (1 << ((fd) & 0x07))) : 0)
#define FD_ZERO(pset)                                               \
    do {                                                            \
        int __xyxxy__;                                              \
        for (__xyxxy__ = 0; __xyxxy__ < ((FD_SETSIZE + 7) / 8); __xyxxy__++)    \
            (pset)->set[__xyxxy__] = 0;                             \
    } while (0)

#if __SATURN__ || __PSX__ || __PUMA__ || __VSURF__ || __MMATICS__ || __TOSHIBA__ || __KATANA__
#ifndef PW_TIMEVAL_DEFINED
/*
 * The saturn and PSX don't have struct timeval in <time.h>, and since it's supposed
 * to be one of the option types for sockets, we define it here.
 */
struct timeval {
	long    tv_sec;     /* seconds */
	long    tv_usec;    /* microseconds */
};
#define PW_TIMEVAL_DEFINED
#endif
#endif /* __SATURN__ || __PSX__ || __PUMA__ || __VSURF__ || __MMATICS__ || __TOSHIBA__ */

#define select pw_select

//int pselect(int, fd_set *, fd_set *, fd_set *, const struct timespec *);
int select(int, fd_set *, fd_set *, fd_set *, const struct timeval *);

#ifdef __cplusplus
}
#endif
#endif /* __SELECT_H__ */
