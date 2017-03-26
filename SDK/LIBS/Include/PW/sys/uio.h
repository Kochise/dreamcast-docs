/*
 * sys/uio.h
 *
 * This is a direct implementation of the uio.h header file, from
 * IEEE P1003.1g/D6.1, the POSIX network specification, section 5.4.1.
 *
 * Copyright 1996 PlanetWeb, Inc.
 * Created 4 Nov 96 by scole
 *
 * $Header: c:/planetweb/katana/h:/RCS/api/sys/uio.h 1.2 1996-11-27 19:46:42+00 scole Exp $
 *
 * $Log: uio.h $
 * Revision 1.2  1996-11-27 19:46:42+00  scole
 * Replaced tabs with blanks for better formatting.
 *
 * Revision 1.1  1996-11-18 11:47:20-0800  scole
 * Initial revision
 *
 */
#ifndef __UIO_H__
#ifdef __cplusplus
extern "C" {
#endif
#define __UIO_H__

#define UIO_MAXIOV  256                 /* guaranteed lowest max # elems for iovec array */
struct iovec {
    void *      iov_base;               /* Pointer to data area within application */
    size_t      iov_len;                /* Size, in octets, of the data area */
};

#ifdef __cplusplus
}
#endif
#endif /* __UIO_H__ */
