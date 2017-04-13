/****************************************************************************\
*  listen.c -- sample program demonstrating NWLink.
*
*       Microsoft Developer Support
*       Copyright 1992 - 1997 Microsoft Corporation
*
*  This program is a simple example of opening a SPX socket,
*  binding to the socket, and listening for a connection.
*
****************************************************************************/
#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "wshisotp.h"

/*
*   Sockaddr structures
*/

SOCKADDR_TP addr;
SOCKADDR_TP baddr;
SOCKADDR_TP saddr;

/*
*   Function Prototypes
*/

extern int main(int, char **);
extern int net_init(SOCKET *);
extern int do_listen(SOCKET);
extern int wait_for_connection(SOCKET, SOCKET *);
extern int do_recv_send(SOCKET);

char LocalNetworkAddress[22];
char LocalNetworkAddressLength;
short   LocalTsel;

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
    SOCKET s, s2;

   /*
   ** Read Local Transport Address fields from user
   */
   printf("LocalNetworkAddress(max. 20 chars) : ");
   scanf("%s", &LocalNetworkAddress[0]);
   printf("LocalTsel : ");
   scanf("%d", &LocalTsel);

   LocalNetworkAddressLength = strlen(LocalNetworkAddress) ;

printf("Local Tsel(%d) Net_length(%d) Net(%s)\n",
        LocalTsel, LocalNetworkAddressLength, LocalNetworkAddress);


    /*
    *   Initialize the network and set up our socket
    */

    if (net_init(&s))
        return 1;

    if (verbose)
        printf("calling do_listen\n");

    /*
    *   Go listen for a call
    */

    if (do_listen(s))
        return 1;

    /*
    *   Then wait for a connection
    */

    if (verbose)
        printf("calling wait_for_connection\n");

    if (wait_for_connection(s, &s2))
        return 1;

    /*
    *   Receive data then send it back
    */

    if (verbose)
        printf("calling do_recv_send\n");

    if (do_recv_send(s2))
        return 1;

    /*
    *   All done
    */

    if (verbose)
        printf("closing both sockets\n");

    closesocket(s2);
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
*    ARGUMENTS: SOCKET * => struct to receive our socket info
*
*        RETURNS:   0 if ok
*                               1 if error
*
*\***************************************************************************/
int net_init(SOCKET *skt)
{
    int i, rc, addrlen;
    WSADATA wsdata;
    SOCKET s;
    char *adr;

    /*
    *   Initialize with the WINSOCK library
    */

    if (verbose)
        printf("calling WSAStartup(), ");

    rc = WSAStartup(MAKEWORD(1,1), &wsdata);

    if (verbose)
        printf("return = 0x%X, (%d)\n", rc, rc);

    if (rc) {
        printf("WSAStartup failed: error code = %d\n", rc);
        return 1;
    }


    /*
    *   Open a STREAM socket with SPX
    */

    if (verbose)
        printf("calling socket(addresss family = %d, socket type = %d, protocol = %d)\n", Local_Address_Family, Socket_Type, Protocol);

    s = socket(Local_Address_Family, Socket_Type, Protocol);


    if (verbose)
        printf("socket() returned 0x%X (%d)\n", s, s);

    if (s == INVALID_SOCKET) {
        printf("Socket call failed\n");
        exit(1);
    }

    /*
    *   Bind to a socket.  We want to bind to a well known
    *   socket so that who ever calls us will be able to.
    */
ISO_SET_TP_ADDR(&addr, &LocalTsel, sizeof(LocalTsel),
                        LocalNetworkAddress, LocalNetworkAddressLength);

/*
    addr.sa_family = Local_Address_Family;
    addr.addr_type = HIERARCHICAL;
    addr.taddr_len = LocalNetworkAddressLength + LocalTselLength;
    addr.tsel_len = LocalTselLength;
    memcpy(&addr.addr, LocalTsel, LocalTselLength);
    memcpy(&addr.addr[LocalTselLength],
                LocalNetworkAddress, LocalNetworkAddressLength);
*/

    if (verbose) {
        printf("calling bind(socket = %d): \n  ", s);
    }

    rc = bind(s, (const struct sockaddr *) &addr, sizeof(SOCKADDR_TP));

    if (verbose)
        printf("bind() returned 0x%X (%d)\n", rc, rc);

    if (rc == SOCKET_ERROR) {
        printf("Error binding to socket\n");
        closesocket(s);
        return 1;
    }

    if (verbose)
        printf("calling getsockname(socket = %d), ", s);

    /*
    *   Get the address we bound to and print it out
    */

    addrlen = sizeof(SOCKADDR_TP);
    rc = getsockname(s, (struct sockaddr *) &baddr, &addrlen);

    if (verbose)
        printf("return = 0x%X (%d)\n", rc, rc);

    if (rc == SOCKET_ERROR) {
        printf("Error getting socket name");
        closesocket(s);
        return 1;
    }

    /*
     *   Print out the network address
     */
    if (verbose) {
        adr = (char *)&baddr;
        printf("len(%d) addr : ", addrlen);
        for ( i = 0; i < addrlen; i++)
                printf(" %x ", *(adr + i));
    }

    *skt = s;

    return 0;
}

/****************************************************************************
*
*    FUNCTION:  do_listen( SOCKET s )
*
*    PURPOSE:   Sets the socket up for listening.
*
*    ARGUMENTS: SOCKET socket to listen on
*
*        RETURNS:   0 if ok
*                               1 if error
*
*\***************************************************************************/
int do_listen(SOCKET s)
{
    int rc;

    /*
    *   Enable this socket as a listen socket that can
    *   take <Backlog> connection indication(s) at a time.
    */

    if (verbose)
        printf("calling listen(socket = %d, backlog = %d), ", s, Backlog);

    rc = listen(s, Backlog);

    if (verbose)
        printf("return = 0x%X (%d)\n", rc, rc);

    if (rc == SOCKET_ERROR) {
        printf("listen call failed");
        closesocket(s);
        return 1;
    }

    /*
    *   Wait for a connection and get the connecting socket
    */

    return 0;
}

/****************************************************************************
*
*    FUNCTION:  wait_for_connection( SOCKET s, SOCKET *callsock )
*
*    PURPOSE:   Waits for someone to connect.
*
*    ARGUMENTS: SOCKET socket we are listening on
*                               SOCKET * => area to store client socket info after
*                                           connect
*
*        RETURNS:   0 if ok
*                               1 if error
*
*\***************************************************************************/
int wait_for_connection(SOCKET s, SOCKET *callsock)
{
    SOCKET s2;
    int addrlen = sizeof(SOCKADDR_TP);

    /*
    *   Go wait for somebody to connect
    */

    if (verbose)
        printf("calling accept(socket = %d), ", s);
    else
        printf("Waiting for call...\n");

    s2 = accept(s, (struct sockaddr *) &saddr, &addrlen);

    if (verbose)
        printf("return (socket) = 0x%X (%d)\n", s2, s2);

    if (s2 == INVALID_SOCKET) {
        printf("accept call failed");
        closesocket(s);
        return 1;
    }

    /*
    *   Print out who connected to us

    if (verbose) {
        printf("addrlen = %d\n", addrlen);
        print_netaddr(saddr.sa_netnum, "Callers address = ", "\n");
    }
    */

    *callsock = s2;

    return 0;
}

/****************************************************************************
*
*    FUNCTION:  do_recv_send( SOCKET s2 )
*
*    PURPOSE:   Waits for someone to connect.
*
*    ARGUMENTS: SOCKET socket to transmit on
*
*        RETURNS:   0 if ok
*                               1 if error
*
*\***************************************************************************/
int do_recv_send(SOCKET s2)
{
    int rc, rcount = 0;
    int nbytes, errflag = 0;
    LPSTR recvbuf;

    if (verbose)
        printf("allocating %d bytes for receive buffer\n", Receive_Length);

    recvbuf = malloc(Receive_Length);

    if (!recvbuf) {
        printf("Error allocating %d bytes for receive buffer\n", Receive_Length);
        return 1;
    }

    /*
    *   Recv packets and send them back
    */

    while (1) {

        /*
        *   Receive data
        */

        if (verbose)
            printf("calling recv(socket = %d, receive length = %d)\n", s2, Receive_Length);

        Sleep(Sleep_Time);

        nbytes = recv(s2, recvbuf, Receive_Length, 0);

        if (nbytes == SOCKET_ERROR) {
            printf("recv call failed");
            errflag++;
            break;
        }

        if (verbose)
            printf("Received packet %d: received %d bytes\n", rcount++, nbytes);
        else
            printf("\rReceived packet %d: received %d bytes... ", rcount++, nbytes);

        /*
        *   Send the data back
        */
/*
        if (verbose)
            printf("calling send(socket = %d, send length = %d)\n", s2, nbytes);

        rc = send(s2, recvbuf, nbytes, 0);

        if (rc == SOCKET_ERROR) {
            printf("send call failed\n");
            errflag++;
            break;
        }

        printf("Sent %d bytes", rc);
*/
        if (verbose)
            printf("\n");

        if (No_Loop)
            break;
    }

    if (verbose)
        printf("freeing receive buffer\n");

    free(recvbuf);

    return errflag;
}
