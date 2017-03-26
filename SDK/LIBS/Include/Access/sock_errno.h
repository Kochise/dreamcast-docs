/************************************************************************/
/*    AVE-TCP Socket Library        errno.h           92/04/15          */
/*                                                    98/11/28 Update   */
/*                                  sock_errno.h      99/01/21 Update   */
/* Copyright (C) 1992, 1998 ACCESS CO.,LTD. All rights reserved.        */
/************************************************************************/

#ifdef __cplusplus /* Support for C++ */
extern "C" {
#endif /* __cplusplus */

/*
 * Error codes
 */

#define	EINTR	4	/* interrupted system call		*/
#ifndef EBADF
#define	EBADF	9	/* Bad file number			*/
#endif
#define	EACCES	13	/* Permission denied			*/
#define	EFAULT	14	/* Bad address				*/
#define	EINVAL	22	/* Invalid argument			*/
#define	ENFILE	23	/* Too many open files in system	*/
#define	EMFILE	24	/* Too many open files			*/

/* added for socket and network */
#define EWOULDBLOCK	35	/* Operation would block		*/
#define EINPROGRESS	36	/* Operation now in progress		*/
#define EALREADY	37	/* Operation already in progress	*/
#define ENOTSOCK	38	/* Socket operation on non-socket	*/
#define EDESTADDRREQ	39	/* Destination address required		*/
#define EMSGSIZE	40	/* Message too long			*/
#define EPROTOTYPE	41	/* Protocol wrong type for socket	*/
#define ENOPROTOOPT	42	/* Protocol not available		*/
#define EPROTONOSUPPORT	43	/* Protocol not supported		*/
#define	ESOCKTNOSUPPORT	44	/* Socket type not supported		*/
#define EOPNOTSUPP	45	/* Operation not supported on socket	*/
#define	EPFNESUPPORT	46	/* Protocol family not supported by protocol */
#define	EAFNOSUPPORT	47	/* Address family not supported by protocol family	*/
#define EADDRINUSE	48	/* Address already in use		*/
#define EADDRNOTAVAIL	49	/* Can't assign requested address	*/
#define	ENETDOWN	50	/* Network is down			*/
#define	ENETUNREACH	51	/* Network is unreachable		*/
#define	ENETRESET	52	/* Network dropped connection on reset 	*/
#define ECONNABORTED	53	/* Software caused connection abort	*/
#define ECONNRESET	54	/* Connection reset by peer		*/
#define ENOBUFS		55	/* No buffer space available		*/
#define EISCONN		56	/* Socket is already connected		*/
#define ENOTCONN	57	/* Socket is not connected		*/
#define	ESHUTDOWN	58	/* Can't send after socket shutdown 	*/
#define	ETOOMANYREFS	59	/* Too many references: can't splice 	*/
#define	ETIMEDOUT	60	/* Connetion timed out			*/
#define ECONNREFUSED	61	/* Connection refused			*/
#define	ELOOP		62	/* Too many levels of symbolic links 	*/
#define	ENAMETOOLONG	63	/* File name too long 			*/
#define EHOSTDOWN	64	/* Host is down				*/
#define	EHOSTUNREACH	65	/* No route to host			*/

extern volatile int sock_errno;

#ifdef __cplusplus
} /* End of extern "C" { */
#endif /* __cplusplus */
