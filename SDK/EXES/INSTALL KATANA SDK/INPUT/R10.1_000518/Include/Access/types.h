/************************************************************************/
/*    AVE-TCP Socket Library        types.h           92/04/15          */
/*       Copyright (C) 1992 ACCESS CO.,LTD.                             */
/************************************************************************/
/*
 *  Basic system types.
 */
#ifdef __cplusplus /* Support for C++ */
extern "C" {
#endif /* __cplusplus */

#ifndef TYPES_H
#define TYPES_H
 
typedef unsigned char	u_char;
typedef unsigned short	u_short;
typedef unsigned int	u_int;
typedef unsigned long	u_long;

typedef struct	_physadr { short r[1]; } *physadr;
typedef struct	label_t {
	int	val[8];
} label_t;

typedef struct	_quad { long val[2]; } quad;
typedef long	daddr_t;
typedef	char *	caddr_t;
typedef u_long	ino_t;
typedef long	swlbk_t;
/*typedef int	size_t;*/
typedef long	time_t;
typedef short	dev_t;
typedef long	off_t;
typedef u_short	uid_t;
typedef u_short	gid_t;
typedef long	key_t;

#define	NBBY	8                       /* number of bits in a byte */
#define FD_SETSIZE	256

typedef long	fd_mask;
#define NFDBITS (sizeof(fd_mask) * NBBY)        /* bits per mask */
#define howmany(x, y)  ((((u_int)(x))+(((u_int)(y))-1))/((u_int)(y)))

typedef struct fd_set {
	fd_mask fds_bits[howmany(FD_SETSIZE, NFDBITS)];
} fd_set;

typedef char *	addr_t;

#define FD_SET(n, p)  ((p)->fds_bits[(n)/NFDBITS] |= (1 << ((n) % NFDBITS)))
#define FD_CLR(n, p)  ((p)->fds_bits[(n)/NFDBITS] &= ~(1 << ((n) % NFDBITS)))
#define FD_ISSET(n, p)  ((p)->fds_bits[(n)/NFDBITS] & (1 << ((n) % NFDBITS)))
#define FD_ZERO(p)    bzero((char *)(p), sizeof(*(p)))

#endif

#ifdef __cplusplus
} /* End of extern "C" { */
#endif /* __cplusplus */
