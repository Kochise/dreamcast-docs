/****************************************************************************\
*  dgrecv.c -- sample program demonstrating NWLink.
*
*       Microsoft Developer Support
*       Copyright 1992 - 1997 Microsoft Corporation
*
*  This program is a simple example of using SPX connect.
*
****************************************************************************/
#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "wshisotp.h"

typedef struct tag_error_struct{
    int     errnum;
    LPSTR   errstr;
} ERROR_STRUCT;

SOCKADDR_TP addr;
SOCKADDR_TP caddr;

UCHAR ch = 0;

char LocalNetworkAddress[22];
char LocalNetworkAddressLength;
short   LocalTsel;
char RemoteNetworkAddress[22];
char RemoteNetworkAddressLength;
short   RemoteTsel;

int     verbose = 1;
int     Socket_Type = SOCK_SEQPACKET;
int     Protocol = ISOPROTO_TP4;
int     Local_Address_Family = AF_ISO;
int     Remote_Address_Family = AF_ISO;
int     Backlog = 1;
int     No_Broadcast = 0;
int     No_Loop = 0;
int     Sleep_Time = 1000;
int     Send_Length = 100;
int     Receive_Length = 200;
int     Local_Packet_Type = 0;

#define WSAERRGAP1 28
#define WSAERRGAP2 19

char msg_no_error[19] =      "No error occurred!";
char msg_unknown_error[14] = "Unknown error";

ERROR_STRUCT errlist[] = {
    {WSAEINTR,           "WSAEINTR - Interrupted"},
    {WSAEBADF,           "WSAEBADF - Bad file number"},
    {WSAEFAULT,          "WSAEFAULT - Bad address"},
    {WSAEINVAL,          "WSAEINVAL - Invalid argument"},
    {WSAEMFILE,          "WSAEMFILE - Too many open files"},

/*
*    Windows Sockets definitions of regular Berkeley error constants
*/

    {WSAEWOULDBLOCK,     "WSAEWOULDBLOCK - Socket marked as non-blocking"},
    {WSAEINPROGRESS,     "WSAEINPROGRESS - Blocking call in progress"},
    {WSAEALREADY,        "WSAEALREADY - Command already completed"},
    {WSAENOTSOCK,        "WSAENOTSOCK - Descriptor is not a socket"},
    {WSAEDESTADDRREQ,    "WSAEDESTADDRREQ - Destination address required"},
    {WSAEMSGSIZE,        "WSAEMSGSIZE - Data size too large"},
    {WSAEPROTOTYPE,      "WSAEPROTOTYPE - Protocol is of wrong type for this socket"},
    {WSAENOPROTOOPT,     "WSAENOPROTOOPT - Protocol option not supported for this socket type"},
    {WSAEPROTONOSUPPORT, "WSAEPROTONOSUPPORT - Protocol is not supported"},
    {WSAESOCKTNOSUPPORT, "WSAESOCKTNOSUPPORT - Socket type not supported by this address family"},
    {WSAEOPNOTSUPP,      "WSAEOPNOTSUPP - Option not supported"},
    {WSAEPFNOSUPPORT,    "WSAEPFNOSUPPORT - "},
    {WSAEAFNOSUPPORT,    "WSAEAFNOSUPPORT - Address family not supported by this protocol"},
    {WSAEADDRINUSE,      "WSAEADDRINUSE - Address is in use"},
    {WSAEADDRNOTAVAIL,   "WSAEADDRNOTAVAIL - Address not available from local machine"},
    {WSAENETDOWN,        "WSAENETDOWN - Network subsystem is down"},
    {WSAENETUNREACH,     "WSAENETUNREACH - Network cannot be reached"},
    {WSAENETRESET,       "WSAENETRESET - Connection has been dropped"},
    {WSAECONNABORTED,    "WSAECONNABORTED - "},
    {WSAECONNRESET,      "WSAECONNRESET - "},
    {WSAENOBUFS,         "WSAENOBUFS - No buffer space available"},
    {WSAEISCONN,         "WSAEISCONN - Socket is already connected"},
    {WSAENOTCONN,        "WSAENOTCONN - Socket is not connected"},
    {WSAESHUTDOWN,       "WSAESHUTDOWN - Socket has been shut down"},
    {WSAETOOMANYREFS,    "WSAETOOMANYREFS - "},
    {WSAETIMEDOUT,       "WSAETIMEDOUT - Command timed out"},
    {WSAECONNREFUSED,    "WSAECONNREFUSED - Connection refused"},
    {WSAELOOP,           "WSAELOOP - "},
    {WSAENAMETOOLONG,    "WSAENAMETOOLONG - "},
    {WSAEHOSTDOWN,       "WSAEHOSTDOWN - "},
    {WSAEHOSTUNREACH,    "WSAEHOSTUNREACH - "},
    {WSAENOTEMPTY,       "WSAENOTEMPTY - "},
    {WSAEPROCLIM,        "WSAEPROCLIM - "},
    {WSAEUSERS,          "WSAEUSERS - "},
    {WSAEDQUOT,          "WSAEDQUOT - "},
    {WSAESTALE,          "WSAESTALE - "},
    {WSAEREMOTE,         "WSAEREMOTE - "},

/*
*    Extended Windows Sockets error constant definitions
*/

    {WSASYSNOTREADY,     "WSASYSNOTREADY - Network subsystem not ready"},
    {WSAVERNOTSUPPORTED, "WSAVERNOTSUPPORTED - Version not supported"},
    {WSANOTINITIALISED,  "WSANOTINITIALISED - WSAStartup() has not been successfully called"},

/*
*    Other error constants.
*/

    {WSAHOST_NOT_FOUND,  "WSAHOST_NOT_FOUND - Host not found"},
    {WSATRY_AGAIN,       "WSATRY_AGAIN - Host not found or SERVERFAIL"},
    {WSANO_RECOVERY,     "WSANO_RECOVERY - Non-recoverable error"},
    {WSANO_DATA,         "WSANO_DATA - (or WSANO_ADDRESS) - No data record of requested type"},
    {-1,                 NULL}
};

/*
*   Function Prototypes
*/

extern int main(int, char **);
extern int net_init(SOCKET *);
extern int make_connection(SOCKET);
extern int do_send_receive(SOCKET);
extern void dos_net_perror(LPSTR );
extern LPCSTR dos_net_strerror(LPSTR );
extern LPCSTR get_error_text(int );

/****************************************************************************
*
*    FUNCTION:  main( int argc, char **argv )
*
*    PURPOSE:   This is the main entry for the program
*
*
*    ARGUMENTS: argc = Number of arguments
*               argv = Array of ptrs to cmd line args
*
*
*        RETURNS:   Exit code for the program
*
*\***************************************************************************/
int main(int argc, char **argv)
{
    SOCKET s;

   /*
   ** Read Local & Remote Transport Address fields from user
   */
   printf("LocalNetworkAddress(max. 20 chars) : ");
   scanf("%s", &LocalNetworkAddress[0]);
   printf("LocalTsel : ");
   scanf("%d", &LocalTsel);
   LocalNetworkAddressLength = strlen(LocalNetworkAddress) ;

   printf("RemoteNetworkAddress(max. 20 chars) : ");
   scanf("%s", &RemoteNetworkAddress[0]);
   printf("RemoteTsel : ");
   scanf("%d", &RemoteTsel);
   RemoteNetworkAddressLength = strlen(RemoteNetworkAddress) ;

printf("local Tsel(%d) Net_length(%d) Net(%s)\n",
        LocalTsel, LocalNetworkAddressLength, LocalNetworkAddress);
printf("Remote Tsel(%d) Net_length(%d) Net(%s)\n",
        RemoteTsel, RemoteNetworkAddressLength, RemoteNetworkAddress);


    /*
    *   Initialize the network and set up the socket
    */

    if (net_init(&s))
        return 1;

    /*
    *   Try to connect to our server
    */

    if (make_connection(s))
        return 1;

    /*
    *   Send/receive data to/from server
    */

    do_send_receive(s);

    /*
    *   All done - close up
    */

    if (verbose)
        printf("calling closesocket(socket = %d)\n", s);

    closesocket(s);
    return 0;
}

/****************************************************************************
*
*    FUNCTION:  net_init( SOCKET *skt )
*
*    PURPOSE:   Initializes the WinSock stuff and sets up our socket.
*
*
*    ARGUMENTS: SOCKET * => struct to fill in with opened socket.
*
*        RETURNS:   0 if ok
*                               1 if error
*
*\***************************************************************************/
int net_init(SOCKET *skt)
{
    SOCKET s;
    int rc, addrlen;
    int reuse = 1;
    WSADATA wsdata;
    WORD    wVersionRequested;

    wVersionRequested = MAKEWORD(1,1);


    /*
    *   Register with the socket library
    */

    rc = WSAStartup(wVersionRequested, &wsdata);

    if (verbose)
        printf("WSAStartup returned 0x%X\n", rc);

    if (rc) {
        printf("WSAStartup failed: error = %d\n", rc);
        return 1;
    }


    /*
    *   Open a STREAMING socket
    */

    s = socket(Local_Address_Family, Socket_Type, Protocol);

    if (verbose)
        printf("socket() returned 0x%X (%d)\n", s, s);

    if (s == INVALID_SOCKET) {
        printf("socket call failed");
        return 1;
    }

    /*
    *   Bind to any address
    */

    ISO_SET_TP_ADDR(&addr, &LocalTsel, sizeof(LocalTsel),
                        LocalNetworkAddress, LocalNetworkAddressLength);

    rc = setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char FAR *)&reuse, sizeof(int));
    if (rc == SOCKET_ERROR) {
        dos_net_perror("setsockopt call failed");
        return 1;
    }

    rc = bind(s, (const struct sockaddr *)&addr, sizeof(SOCKADDR_TP));

    if (verbose)
        printf("bind() returned 0x%X\n", rc);

    if (rc == SOCKET_ERROR) {
        dos_net_perror("bind call failed");
        return 1;
    }

    if (verbose)
        printf("calling getsockname(socket = %d)\n", s);

    addrlen = sizeof(SOCKADDR_TP);
    rc = getsockname(s, (struct sockaddr *) &addr, &addrlen);

    if (verbose)
        printf("getsockname() returned 0x%X\n", rc);

    if (rc == SOCKET_ERROR) {
        printf("Error binding to socket");
        closesocket(s);
        return 1;
    }
/*
    if (verbose) {
        printf("addrlen = %d\n", addrlen);
        print_netaddr(addr.sa_netnum, "Bound address = ", "\n");
    }
*/

    /*
    *   Build the address of the node to connect to
    */
ISO_SET_TP_ADDR(&caddr, &RemoteTsel, sizeof(RemoteTsel),
                        RemoteNetworkAddress, RemoteNetworkAddressLength);

/*
    caddr.sa_family = Remote_Address_Family;
    caddr.addr_type = HIERARCHICAL;
    caddr.taddr_len = RemoteNetworkAddressLength + RemoteTselLength;
    caddr.tsel_len = RemoteTselLength;
    memcpy(&caddr.addr, RemoteTsel, RemoteTselLength);
    memcpy(&caddr.addr[RemoteTselLength],
                RemoteNetworkAddress, RemoteNetworkAddressLength);
*/

    /*
    *   Set up socket for return
    */

    *skt = s;

    return 0;
}

/****************************************************************************
*
*    FUNCTION:  make_connection( SOCKET s )
*
*    PURPOSE:   Establishes a connection with our server.
*
*    ARGUMENTS: SOCKET socket to use for connection
*
*        RETURNS:   0 if ok
*                               1 if error
*
*\***************************************************************************/
int make_connection(SOCKET s)
{
    int rc, addrlen;

    /*
    *   Connect
    */

    if (verbose)
        printf("calling connect(socket = %d)\n", s);

    rc = connect(s, (const struct sockaddr FAR *)&caddr, sizeof(SOCKADDR_TP));

    if (verbose)
        printf("connect() returned 0x%X\n", rc);

    if (rc == SOCKET_ERROR) {
        dos_net_perror("connect call failed");
        return 1;
    }

    printf("Connect OK\n");

    /*
    *   Print out address we connected to
    */

    if (verbose)
        printf("calling getpeername(socket = %d)\n", s);

    addrlen = sizeof(SOCKADDR_TP);
    rc = getpeername(s, (struct sockaddr *) &caddr, &addrlen);

    if (verbose)
        printf("getpeername() returned 0x%X\n", rc);
/*
    if (verbose) {
        printf("addrlen = %d\n", addrlen);
        print_netaddr(caddr.sa_netnum, "Remote Address = ", "\n");
    }
*/

    return 0;
}
/****************************************************************************
*
*    FUNCTION:  do_send_receive( SOCKET *s )
*
*    PURPOSE:   Alternately sends/receives data to/from the server.
*
*    ARGUMENTS: SOCKET socket to transmit on
*
*        RETURNS:   0 if ok
*                               1 if error
*
*\***************************************************************************/
int do_send_receive(SOCKET s)
{
    int rc, errflag = 0;
    int sndpkts = 0, rcvpkts = 0;
    LPSTR sendbuf;

    /*
    *   Allocate a send buffer
    */

    if (verbose)
        printf("Allocating %d bytes for send buffer \n");

    sendbuf = malloc(Send_Length);

    if (!sendbuf) {
        printf("Error allocating %d bytes for send buffer\n");
        return 1;
    }

    /*
    *   Send data and recv it back
    */

    while (1) {

        /*
        *   Fill the buffer with our current character
        */

        memset(sendbuf, ch, Send_Length);

        /*
        *   Send data
        */

        if (verbose)
            printf("calling send(socket = %d, length = %d)\n", s, Send_Length);

        rc = send(s, sendbuf, Send_Length, 0);

        if (verbose)
            printf("send() returned 0x%X\n", rc);

        if (rc == SOCKET_ERROR) {
            printf("\nsend() call failed");
            errflag++;
            break;
        }

        if (verbose)
            printf("Sent packet %d: sent %d bytes\n", sndpkts++, rc);
        else
            printf("\rSent packet %d: sent %d bytes... ", sndpkts++, rc);

        /*
        *   Receive the data back
        */
/*
        if (verbose)
            printf("calling recv(socket = %d, length = %d)\n", s, Send_Length);

        rc = recv(s, sendbuf, Send_Length, 0);

        if (verbose)
            printf("recv() returned %d\n", rc);

        if (rc == SOCKET_ERROR) {
            printf("\nrecv() call failed");
            errflag++;
            break;
        }

        if (!rc) {
            printf("connection has been lost\n");
            break;
        }

        printf("Received %d bytes", rc);
*/
        if (verbose)
            printf("\n");

        /*
        *   See if our buffer has the same data in it
        */

        rc = mem_check(sendbuf, ch++, Send_Length);

        if (rc)
            printf("Data compare error: packet = %d, offset = %d\n", (sndpkts-1), rc);
        else if (verbose)
            printf("Data compares okay\n");

        /*
        *   If we are to send just 1, break out
        */

        if (No_Loop)
            break;

        /*
        *   Pause a little while (don't trash the network)
        Sleep(Sleep_Time);
        */

    }

    if (verbose)
        printf("\nFreeing send buffer\n");

    free(sendbuf);

    return errflag;
}


/****************************************************************************
*
*    FUNCTION:  mem_check( LPSTR p, UCHAR ch, int len)
*
*    PURPOSE:   Makes sure that a buffer is filled with only the character
*                   specified.
*
*    ARGUMENTS: LPSTR   => buffer to scan
*               char    character to check for
*               int     length of buffer to check
*
*        RETURNS:   0 if buffer has only the specified character
*                               offset to non-matching character if found
*
************************************************************************/
int mem_check(LPSTR p, UCHAR ch, int len)
{
    int buflen;

    buflen = len;

    while (len--) {
        if ((UCHAR)*p++ != ch) {
            return (buflen - len);
        }
    }

    return 0;
}

void dos_net_perror(LPSTR p)
{
    printf(dos_net_strerror(p));
    printf("\n");

    return;
}



LPCSTR dos_net_strerror(LPSTR p)
{
    int error = 0;
    static char return_string[256];

    /*
    *   Get the error number from the system
    */

    error = h_errno;

    /*
    *   Build the string to return
    */

    sprintf(return_string, "%s :(%d)%s", p, error, get_error_text(error));

    return (LPSTR)return_string;
}

LPCSTR get_error_text(int error)
{
    int search = 0;


    /*
    *   No error
    */

    if (!error)
        return (LPCSTR)msg_no_error;

    /*
    *   Search through our array of error number / string pairs
    *   until we find a matching error number or get to the end
    *   of our list.  If we found a matching error number,
    *   return a LPSTR to the corresponding string.
    */

    while (errlist[search].errstr) {
        if (error == errlist[search].errnum)
            return errlist[search].errstr;
        search++;
    }

    /*
    * If we didn't have the error in our list, return unkown
    */

    return (LPCSTR)msg_unknown_error;
}



