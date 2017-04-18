/*
 * sys/socket.h
 *
 * This is a direct implementation of the socket.h header file, from
 * IEEE P1003.1g/D6.1, the POSIX network specification, section 5.4.1.
 *
 * Copyright 1996 PlanetWeb, Inc.
 * Created 4 Nov 96 by scole
 *
 * $Header: c:/planetweb/katana/h:/RCS/api/sys/socket.h 1.10 1999-03-19 00:44:38+00 soohoo Exp $
 *
 * $Log: socket.h $
 * Revision 1.10  1999-03-19 00:44:38+00  soohoo
 * Added Katana to avoid some GCC includes.
 *
 * Revision 1.9  1999-02-11 15:11:18-0800  may
 * toshiba code
 *
 * Revision 1.8  1998-12-08 11:29:11-0800  soohoo
 * Added mediamatics.
 *
 * Revision 1.7  1998-06-04 13:22:57-0700  jason
 * Added defines to reduce namespace conflicts.
 *
 * Revision 1.6  1998-05-26 19:12:36-0700  soohoo
 * Added VideoSurfer.
 *
 * Revision 1.5  1998-03-24 14:08:50-0800  scole
 * PUMA fixes.
 *
 * Revision 1.4  1997-02-04 16:30:51-0800  scole
 * PSX was missing struct timeval also!
 *
 * Revision 1.3  1997-01-29 11:36:30-0800  scole
 * Added SO_RCVTMEO, which had been forgotten; also added struct timeval
 * for saturn.
 *
 * Revision 1.2  1996-11-27 11:48:05-0800  scole
 * - Replaced tabs with blanks for better formatting.
 * - Implemented CMSG_DATA(), CMSG_NXTHDR(), and CMSG_FIRSTHDR().
 *
 * Revision 1.1  1996-11-18 11:47:06-0800  scole
 * Initial revision
 *
 */
#ifndef __SOCKET_H__
#ifdef __cplusplus
extern "C" {
#endif
#define __SOCKET_H__

#ifndef NULL
#define NULL 0                          /* Is this even legal here??? */
#endif

typedef unsigned char sa_family_t;

/*
 * Values for the "type" field of socket() and socketpair()
 */
#define SOCK_STREAM     1               /* Data stream socket */
#define SOCK_DGRAM      2               /* Connectionless-mode socket */
#define SOCK_RAW        3               /* Raw protocol interface */
#define SOCK_SEQPACKET  4               /* Sequenced packet stream */

/*
 * Values for the "protofamily" field of socket() and socketpair()
 */
#define PF_UNSPEC       0               /* Unspecified */
#define PF_LOCAL        1               /* Local to this host */
#define PF_INET         2               /* Internetwork: UDP, TCP, etc. */
#define PF_ISO          3               /* ISO protocols */
#define PF_OSI          PF_ISO          /* ISO protocols */

/*
 * The sockaddr structure, used by bind(), connect(), getpeername(),
 * getsockname(), recvfrom(), and sendto().
 *
 * Note that the sa_data field's size actually depends on the
 * particular address family, so don't use this structure in
 * initialization.
 */
struct sockaddr {
    sa_family_t     sa_family;          /* Address family */
    char            sa_data[1];         /* Address value */
};

/*
 * Values for the sockaddr structure's "sa_family" field
 */
#define AF_UNSPEC       0               /* Unspecified */
#define AF_LOCAL        1               /* Local to this host */
#define AF_INET         2               /* Internetwork: UDP, TCP, etc. */
#define AF_ISO          3               /* ISO protocols */
#define AF_OSI          AF_ISO          /* ISO protocols */

/*
 * The msghdr structure is used in recvmsg() and sendmsg()
 */
struct msghdr {
    void *          msg_name;           /* Optional address */
    size_t          msg_namelen;        /* Size of address */
    struct iovec *  msg_iov;            /* Scatter/gather array */
    size_t          msg_iovlen;         /* Number of elements in msg_iov */
    void *          msg_control;        /* Ancillary data */
    size_t          msg_controllen;     /* Ancillary data buffer length */
    int             msg_flags;          /* Flags on received message */
};

/*
 * Values for the msghdr structure's "msg_flags" fields (each is
 * bitwise distinct).
 */
#define MSG_OOB         0x01            /* Process out-of-band data */
#define MSG_PEEK        0x02            /* Peek at incoming message */
#define MSG_DONTROUTE   0x04            /* Send without using routing tables */
#define MSG_EOR         0x08            /* This data completes the record */
#define MSG_TRUNC       0x10            /* Data was discarded before delivery */
#define MSG_CTRUNC      0x20            /* Control data was truncated to fit buffer */
#define MSG_WAITALL     0x40            /* Wait for full request of error */

/*
 * The cmsghdr structure is use for the maintenance of ancillary data
 */
struct cmsghdr {
    size_t          cmsg_len;           /* Length, in octets, of the data in the */
                                        /* cmsg_data[] array plus the length of */
                                        /* the cmsghdr structure */
    int             cmsg_level;         /* Originating protocol */
    int             cmsg_type;          /* Protocol-specific type */
};

/*
 * Ancillary data object manipulation macros
 */
#define CMSG_DATA(cmsg)         ((unsigned char *)(cmsg) + sizeof(struct cmsghdr))
#define CMSG_NXTHDR(mhdr,cmsg)  ({                                                                              \
                                    unsigned char *__xyzz;                                                      \
                                    __xyzz = (unsigned char *)(cmsg) + (cmsg)->cmsg_len;                        \
                                    if (__xyzz - (mhdr)->msg_control >= (mhdr)->msg_controllen) __xyzz = NULL;  \
                                    __xyzz;                                                                     \
                                })
#define CMSG_FIRSTHDR(mhdr)     (((mhdr)->msg_controllen > 0) ? (struct cmsghdr *)(mhdr)->msg_control : NULL)

/*
 * Values for "level" for socket options
 * (These should be different from the IPPROTO_* constants from
 * netinet/in.h.)
 */
#define SOL_SOCKET      2               /* Options are intended for the sockets level */

/*
 * Socket-level options (i.e.: level is SOL_SOCKET)
 */
#define SO_BROADCAST    1               /* Enable broadcast */
#define SO_DEBUG        2               /* Enable debugging */
#define SO_DONTROUTE    3               /* Bypass normal routing */
#define SO_ERROR        4               /* Request/clear pending error information */
#define SO_KEEPALIVE    5               /* Transmit keepalive messages */
#define SO_LINGER       6               /* Specify linger on close */
#define SO_OOBINLINE    7               /* Request out-of-band data in normal queue */
#define SO_RCVBUF       8               /* Receive buffer size */
#define SO_RCVLOWAT     9               /* Receive low water mark */
#define SO_REUSEADDR    10              /* Re-use local addresses */
#define SO_SNDBUF       11              /* Send buffer size */
#define SO_SNDLOWAT     12              /* Send low water mark */
#define SO_SNDTIMEO     13              /* Send timeout */
#define SO_TYPE         14              /* Identify socket type */
#define SO_RCVTIMEO     15              /* Receive timeout */

/*
 * The linger structure, used by the SO_LINGER option in
 * getsockopt() and setsockopt()
 */
struct linger {
    int             l_onoff;            /* Linger option set on or off; zero */
                                        /* indicates linger option off,  */
                                        /* nonzero indicates linger option on. */
    int             l_linger;           /* Linger time in seconds */
};

#if __SATURN__ || __PSX__ || __PUMA__ || __VSURF__ || __MMATICS__ || __TOSHIBA__ || __KATANA__
/*
 * The saturn and PSX don't have struct timeval in <time.h>, and since it's supposed
 * to be one of the option types for sockets, we define it here.
 */
struct timeval {
    long    tv_sec;     /* seconds */
    long    tv_usec;    /* microseconds */
};
#endif /* __SATURN__ || __PSX__ || __PUMA__ || __VSURF__ || __MMATICS__ || __TOSHIBA__ */

/*
 * Values of "how" for shutdown()
 */
#define SHUT_RD         0               /* Shutdown for reading */
#define SHUT_WR         1               /* Shutdown for writing */
#define SHUT_RDWR       2               /* Shutdown for both reading and writing */

/*
 * Miscellaneous
 */
#define SOMAXCONN       10              /* Maximum queue length which may be specified */
                                        /* by the "backlog" field of the listen() function */

/*
 * Socket functions
 */
#define accept pw_accept
#define bind pw_bind
#define connect pw_connect
#define getpeername pw_getpeername
#define getsockname pw_getsockname
#define getsockopt pw_getsockopt
#define setsockopt pw_setsockopt
#define isfdtype pw_isfdtype
#define listen pw_listen
#define recv pw_recv
#define recvfrom pw_recvfrom
#define recvmsg pw_recvmsg
#define send pw_send
#define sendto pw_sendto
#define sendmsg pw_sendmsg
#define shutdown pw_shutdown
#define sockatmark pw_sockatmark
#define socket pw_socket
#define socketpair pw_socketpair

int accept(int, struct sockaddr *, size_t *);
int bind(int, const struct sockaddr *, size_t);
int connect(int, const struct sockaddr *, size_t);
int getpeername(int, struct sockaddr *, size_t *);
int getsockname(int, struct sockaddr *, size_t *);
int getsockopt(int, int, int, void *, size_t *);
int setsockopt(int, int, int, const void *, size_t);
int isfdtype(int, int);
int listen(int, int);
ssize_t recv(int, void *, size_t, int);
ssize_t recvfrom(int, void *, size_t, int, struct sockaddr *, size_t *);
ssize_t recvmsg(int, struct msghdr *, int);
ssize_t send(int, const void *, size_t, int);
ssize_t sendto(int, const void *, size_t, int, const struct sockaddr *, size_t);
ssize_t sendmsg(int, const struct msghdr *, int);
int shutdown(int, int);
int sockatmark(int);
int socket(int, int, int);
int socketpair(int, int, int, int[2]);

#ifdef __cplusplus
}
#endif
#endif /* __SOCKET_H__ */
