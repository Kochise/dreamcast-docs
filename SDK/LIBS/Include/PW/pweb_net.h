/*
 * pweb_net.h
 *
 * Network data structures and functions not present in the
 * POSIX spec., but which are necessary for the PlanetWeb
 * implementation of the net.
 *
 * Created 4 Nov 96 by scole
 * Copyright 1996 PlanetWeb, Inc.
 *
 * $Header: c:/planetweb/katana/h:/RCS/api/pweb_net.h 1.16 1999-08-31 09:54:06-07 scole Exp $
 *
 * $Log: pweb_net.h $
 * Revision 1.16  1999-08-31 09:54:06-07  scole
 * Added net_ioctl().
 *
 * Revision 1.15  1999-03-18 16:45:46-08  soohoo
 * Added code for Katana to avoid GCC dependencies.
 *
 * Revision 1.14  1998-09-03 09:04:21-0700  scole
 * Added NetworkActualState() & NetworkAdmState()
 *
 * Revision 1.13  1998-06-25 16:32:16-0700  scole
 * Added new WAITFORPPP flags.
 *
 * Revision 1.12  1998-02-12 15:53:23-0800  scole
 * Added new net flag: NETL_AVOIDSCRIPTING
 *
 * Revision 1.11  1997-12-03 14:16:00-0800  scole
 * Changes for a separate Ethernet build.
 *
 * Revision 1.10  1997-10-07 16:03:21-0700  Jay
 * Add ME_BADINIT for 8x8 pre-init check
 *
 * Revision 1.9  1997-09-09 12:20:58-0700  scole
 * Added ME_NONE to the error list.
 *
 * Revision 1.8  1997-08-26 12:44:41-0700  scole
 * Added NETL_DISABLESPEAKER.
 *
 * Revision 1.7  1997-02-05 17:57:00-0800  scole
 * Added pppIPaddr().
 *
 * Revision 1.6  1997-01-24 13:46:11-0800  scole
 * Added states for disconnection.
 *
 * Revision 1.5  1996-12-16 11:53:43-0800  scole
 * Needed to include netdb.h
 *
 * Revision 1.4  1996-12-16 11:48:28-0800  scole
 * - Moved AI...() functions here from netdb.h.
 * - Changed pClockTicks to a function.
 * - Added a bunch of comments
 *
 * Revision 1.3  1996-12-03 15:23:45-0800  scole
 * nl_pClockTicks made volatile.
 *
 * Revision 1.2  1996-11-27 11:52:30-0800  scole
 * - Replaced tabs with blanks for better formatting.
 * - Enlarged the netInfo structure considerably, as a number of additional
 *   initialization values and callback functions were identified in the
 *   network.
 *
 * Revision 1.1  1996-11-18 11:45:10-0800  scole
 * Initial revision
 *
 */
#ifndef __PWEB_NET_H__
#ifdef __cplusplus
extern "C" {
#endif
#define __PWEB_NET_H__

#ifdef __KATANA__
#ifndef __GNUC__
#include <stddef.h>                  /* Required for size_t */
#else
#include <sys/types.h>                  /* Required for size_t */
#endif
#else
#include <sys/types.h>                  /* Required for size_t */
#endif
#include <sys/types2.h>                 /* Required for <sys/socket.h> */
#include <sys/socket.h>                 /* Required for <netinet/in.h> */
#include <netinet/in.h>                 /* Required for struct in_addr */
#include <netdb.h>						/* Required for struct addrinfo */

typedef enum {
    MPS_INIT_PORT,
    MPS_INIT_MODEM,
    MPS_DIAL_MODEM,
    MPS_LOGGING_IN,
    MPS_CONNECTION_CONFIGURE,
    MPS_CONFIGURE_INTERNET,
    MPS_CONNECTION_ESTABLISHED,
	MPS_DISCONNECTING,
	MPS_HANGING_UP,
	MPS_DISCONNECTED
} modemProgressState;

typedef enum {
    RESP_NONE,
    RESP_CANCEL,
    RESP_RETRY,
    RESP_RETRY_TIL_CONNECTED
} errorResponse;

typedef enum {
	ME_NONE = 0,
    ME_BROKEN,
    ME_BUSY,
    ME_NODIALTONE,
    ME_CARRIERLOSS,
    ME_BADPASSWORD,
    ME_NOANSWER,
	ME_BADINIT
} modemErrorType;

typedef enum {
	NIS_DOWN,
	NIS_UP,
	NIS_OPENING,
	NIS_CLOSING,
	NIS_TESTING,
	NIS_BROKEN
} networkState;

#define NETL_USETONE            0x01    /* Use tone (not pulse) dialing */
#define NETL_BLINDDIAL          0x02    /* Don't wait for dialtone */
#define NETL_DIALAREA           0x04    /* Dial area code always */
#define NETL_DISABLESPEAKER		0x08	/* Disable modem speaker */
#define NETL_AVOIDSCRIPTING		0x10	/* Don't allow script mode to start */
#define NETL_WAITFORPPP			0x20	/* Don't transmit any PPP until we detect it coming in --- */
										/* --- this is useful to *force* scripting */

struct netInfo {
    int     maxTCP;                     /* Maximum simultaneous TCPs */
    int     maxUDP;                     /* Maximum simultaneous UDPs */
    int     maxSocket;                  /* Maximum open sockets */
    void *  (*netMalloc)(size_t size);  /* Memory allocator */
    void    (*netFree)(void *pMem);     /* Memory deallocator */
    void *  (*netRealloc)(void *pOld, size_t newSize); /* Memory reallocator */
    void    (*progressCallback)(modemProgressState);
    void    (*modemStringsStart)(void);
    void    (*modemStringsFinish)(void);
    void    (*modemString)(const char *);
    errorResponse   (*dlgHandler)(modemErrorType);
    unsigned long   (*nl_pClockTicks)(void); /* Function which returns system clock ticks */
    unsigned long   nl_ticksPerSecond;  /* The number of system clock ticks per second */
    int             nl_flags;           /* Combination of NETL_... flags, above */
    const char *    nl_outline;         /* Dial this for an outside line */
    const char *    nl_callwait;        /* Dial this to disable call waiting */
    const char *    nl_areacode;        /* This is user's area code */
    const char *    nl_longdist;        /* Dial this for long distance */
    const char *    nl_telephone;       /* Use this telephone (looks like "(ccc) ppp-dddd") */
    const char *    nl_alttelephone;    /* Alternate telephone if prior was broken */
    const char *    nl_loginID;         /* Login id used in authentication */
    const char *    nl_password;        /* Password used in authentication */
    const char *    nl_modem;           /* Extra AT command sent to modem */
    struct in_addr  nl_primaryDNS;      /* Primary DNS server, used if not configured by peer */
    struct in_addr  nl_secondaryDNS;    /* Secondary DNS server, used if not configured by peer */
};

int InitializeNetwork(const struct netInfo *pNI);
void NetworkIdle(void);
in_addr_t PW_IPaddr(void);
networkState NetworkActualState(void);
networkState NetworkAdmState(void);

/*
 * Non-blocking functions to do network database lookups (like getaddrinfo() --
 * see <netdb.h>)
 */
#define EAI_COMPLETE        1           /* Idle has completed successfully */
int                 AIsetup(const char *, const char *,
                            const struct addrinfo *, struct addrinfo **);
int                 AIidle(struct addrinfo **);
void                AIabort(struct addrinfo **);

/*
 * Net versions of standard file control functions
 */
int net_fcntl(int s, int cmd, long arg);
int net_close(int s);

/*
 * Net version of the Non-Posix function ioctl():
 */
#ifndef FIONREAD
#define FIONREAD 1
#endif
int net_ioctl(int s, int cmd, int *ret);

#ifdef __cplusplus
}
#endif
#endif /* __PWEB_NET_H__ */
