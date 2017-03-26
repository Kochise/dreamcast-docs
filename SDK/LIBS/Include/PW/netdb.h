/*
 * netdb.h
 *
 * This is a direct implementation of the netdb.h header file, from
 * IEEE P1003.1g/D6.1, the POSIX network specification,
 * section 7.2.2.
 *
 * Copyright 1996 PlanetWeb, Inc.
 * Created 4 Nov 96 by scole
 *
 * $Header: c:/planetweb/katana/h:/RCS/api/netdb.h 1.3 1996-12-16 19:48:59+00 scole Exp $
 *
 * $Log: netdb.h $
 * Revision 1.3  1996-12-16 19:48:59+00  scole
 * Moved the AI...() functions to pweb_net.h
 *
 * Revision 1.2  1996-11-27 11:50:12-0800  scole
 * - Replaced tabs with blanks for better formatting.
 * - Added prototypes for AIsetup(), AIidle(), and AIabort().
 *
 * Revision 1.1  1996-11-18 11:43:23-0800  scole
 * Initial revision
 *
 */
#ifndef __NETDB_H__
#ifdef __cplusplus
extern "C" {
#endif
#define __NETDB_H__

#include <netinet/in.h>

struct hostent {
    char *          h_name;             /* Name of the host */
    char **         h_aliases;          /* A pointer to an array of pointers to */
                                        /* alternative host names, terminated by */
                                        /* a NULL pointer. */
    int             h_addrtype;         /* Address family */
    int             h_length;           /* the length, in bytes, of the address */
    char **         h_addr_list;        /* A pointer to an array of pointers to */
                                        /* network addresses (in network byte order) */
                                        /* for the host, terminated by a NULL pointer */
};

struct netent {
    char *          n_name;             /* Name of the network */
    char **         n_aliases;          /* A pointer to an array of pointers to */
                                        /* alternative network names, terminated by */
                                        /* a NULL pointer. */
    int             n_addrtype;         /* The address type of the network */
    in_addr_t       n_net;              /* The network number, in host byte order */
};

struct protoent {
    char *          p_name;             /* Official name of the protocol */
    char **         p_aliases;          /* A pointer to an array of pointers to */
                                        /* alternative protocol names, terminated */
                                        /* by a NULL pointer. */
    int             p_proto;            /* The protocol number */
};

struct servent {
    char *          s_name;             /* Official name of the service */
    char **         s_aliases;          /* A pointer to an array of pointers to */
                                        /* alternative service names, terminated */
                                        /* by a NULL pointer. */
    int             s_port;             /* The port number at which the service */
                                        /* resides, in network byte order */
    char *          s_proto;            /* The name of the protocol to use when */
                                        /* contacting the service. */
};

extern int h_errno;

/*
 * gethostbyaddr and gethostbyname error codes (in h_errno)
 */
#define HOST_NOT_FOUND      (-1)        /* Name is not known */
#define NO_DATA             (-2)        /* No address associated with name */
#define NO_RECOVERY         (-3)        /* Non-recoverable failure in name resolution */
#define TRY_AGAIN           (-4)        /* Temporary failure in name resolution */

/*
 * the addrinfo structure
 */
struct addrinfo {
    int             ai_flags;           /* input flags */
    int             ai_family;          /* proto family for socket */
    int             ai_socktype;        /* socket type */
    int             ai_protocol;        /* protocol for socket */
    int             ai_addrlen;         /* length of socket address */
    struct sockaddr *ai_addr;           /* socket-address for socket */
    char *          ai_canonname;       /* canonical name for service location */
    struct addrinfo *ai_next;           /* pointer to next in list */
};

/*
 * Flag values for addrinfo
 */
#define AI_PASSIVE          0x01        /* Socket address is intended for bind() */
#define AI_CANONNAME        0x02        /* Request for canonical name */

/*
 * Error values for getaddrinfo()
 */
#define EAI_BADFLAGS        (-1)        /* Invalid value for ai_flags */
#define EAI_NONAME          (-2)        /* name or service is not known */
#define EAI_AGAIN           (-3)        /* temporary failure in name resolution */
#define EAI_FAIL            (-4)        /* non-recoverable failure in name resolution */
#define EAI_NODATA          (-5)        /* no address associated with name */
#define EAI_FAMILY          (-6)        /* ai_family not supported */
#define EAI_SOCKTYPE        (-7)        /* ai_socktype not supported */
#define EAI_SERVICE         (-8)        /* service not supported for ai_socktype */
#define EAI_ADDRFAMILY      (-9)        /* address family for name not supported */
#define EAI_MEMORY          (-10)       /* memory allocation failure */
#define EAI_SYSTEM          (-11)       /* system error occurred */

void                endhostent(void);
void                endnetent(void);
void                endprotoent(void);
void                endservent(void);
int                 getaddrinfo(const char *, const char *,
                                const struct addrinfo *, struct addrinfo **);
void                freeaddrinfo(struct addrinfo *);
struct hostent *    gethostbyaddr(const void *, size_t, int);
struct hostent *    gethostbyname(const char *);
struct netent *     getnetbyaddr(in_addr_t, int);
struct netent *     getnetbyname(const char *);
struct protoent *   getprotobyname(const char *);
struct protoent *   getprotobynumber(int);
struct servent *    getservbyname(const char *, const char *);
struct servent *    getservbyport(int, const char *);
void                sethostent(int);
void                setnetent(int);
void                setprotoent(int);
void                setservent(int);

#ifdef __cplusplus
}
#endif
#endif /* __NETDB_H__ */
