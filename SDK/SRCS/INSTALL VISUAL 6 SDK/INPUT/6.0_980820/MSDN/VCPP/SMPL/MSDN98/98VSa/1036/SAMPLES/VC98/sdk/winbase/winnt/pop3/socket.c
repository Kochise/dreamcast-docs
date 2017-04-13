
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1992-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

//+---------------------------------------------------------------------------
//
//  File:       pop3svr.c
//
//  Contents:
//
//  Classes:
//
//  Functions:
//
//----------------------------------------------------------------------------

#include "pop3srvp.h"
#pragma hdrstop

extern BOOL bServiceTerminating;
extern SOCKET sListener;

#define POP3_PORT 110

PCHAR Welcome = "+OK Welcome to the NT Example POP3 Server (POP3SRV)\r\n";

BOOL
AcceptClients (
    HANDLE hCompletionPort
    )

/*++

Routine Description:

    This routine sets up a listening socket on the POP3 port, then
    loops accepting incoming connections from clients.  Whenever
    it gets a connection, it sends the greeting message and starts
    a read on the newly connected socket.

Arguments:

    hCompletionPort - the completion port that the POP3SRV worker 
        threads are waiting on.  

Return Value:

    BOOL - FALSE if there was an error in starting the listening
        socket.

--*/

{
    SOCKET s;
    SOCKADDR_IN sin;
    int err;
    BOOL bSuccess;
    PCLIENT_CONTEXT lpClientContext;
    DWORD dwBytesRead;
    int zero;

    //
    // Create a listening socket that we'll use to accept incoming
    // conections.
    //

    sListener = socket( AF_INET, SOCK_STREAM, 0 );
    if ( sListener == INVALID_SOCKET ) {
        return FALSE;
    }

    //
    // Bind the socket to the POP3 well-known port.
    //

    sin.sin_family = AF_INET;
    sin.sin_port = htons( POP3_PORT );
    sin.sin_addr.s_addr = INADDR_ANY;

    err = bind( sListener, (LPSOCKADDR)&sin, sizeof(sin) );
    if ( err == SOCKET_ERROR ) {
        closesocket( sListener );
        return FALSE;
    }

    //
    // Listen for incoming connections on the socket.
    //

    err = listen( sListener, 5 );
    if ( err == SOCKET_ERROR ) {
        closesocket( sListener );
        return FALSE;
    }

    //
    // Loop forever accepting connections from clients.
    //

    while ( TRUE ) {

        s = accept( sListener, NULL, NULL );
        if ( s == INVALID_SOCKET ) {
            closesocket( sListener );
            return FALSE;
        }

        //
        // If the service if terminating, exit this thread.
        //

        if ( bServiceTerminating ) {
            return FALSE;
        }

        //
        // Allocate a socket context for the new connection.  We use
        // this context structure to track socket-level information
        // about the client.
        //

        lpClientContext = LocalAlloc( 0, sizeof(*lpClientContext) );
        if ( lpClientContext == NULL ) {
            closesocket( s );
            continue;
        }

        //
        // Initialize the context structure.
        //

        lpClientContext->Socket = s;
        lpClientContext->Context = CreatePop3Context( );
        lpClientContext->Overlapped.Internal = 0;
        lpClientContext->Overlapped.InternalHigh = 0;
        lpClientContext->Overlapped.Offset = 0;
        lpClientContext->Overlapped.OffsetHigh = 0;
        lpClientContext->Overlapped.hEvent = NULL;

        //
        // Send the welcome banner.
        //

        err = send( s, Welcome, strlen(Welcome), 0 );
        if ( err == SOCKET_ERROR ) {
            LocalFree( lpClientContext );
            closesocket( s );
            continue;
        }

        // --- DavidTr: Slide 14(a) ----------------------------------------
        //
        // Associate the new socket with a completion port.
        //

        hCompletionPort = CreateIoCompletionPort(
                              (HANDLE)s,
                              hCompletionPort,
                              (DWORD)lpClientContext,
                              0
                              );
        if ( hCompletionPort == NULL ) {
            LocalFree( lpClientContext );
            closesocket( s );
            closesocket( sListener );
            return FALSE;
        }

        // --- DavidTr: Slide 16 -------------------------------------------
        //
        // Disable send bufferring on the socket.  Setting SO_SNDBUF
        // to 0 causes winsock to stop bufferring sends and perform
        // sends directly from our buffers, thereby reducing CPU
        // usage.
        //

        zero = 0;
        err = setsockopt( s, SOL_SOCKET, SO_SNDBUF, (char *)&zero, sizeof(zero) );
        if ( err == SOCKET_ERROR ) {
            LocalFree( lpClientContext );
            closesocket( s );
            closesocket( sListener );
            return FALSE;
        }

        //
        // Start an overlapped read on the socket.  This read will
        // complete in one of the worker threads, which will continue
        // processing of the client.
        //

        lpClientContext->LastClientIo = ClientIoRead;
        lpClientContext->BytesReadSoFar = 0;

        bSuccess = ReadFile(
                       (HANDLE)s,
                       lpClientContext->Buffer,
                       sizeof(lpClientContext->Buffer),
                       &dwBytesRead,
                       &lpClientContext->Overlapped
                       );
        if ( !bSuccess && GetLastError( ) != ERROR_IO_PENDING ) {
            LocalFree( lpClientContext );
            closesocket( s );
            continue;
        }
    }

} // AcceptClients


VOID
CloseClient (
    PCLIENT_CONTEXT lpClientContext,
    BOOL bGraceful
    )

/*++

Routine Description:

    Terminates a connection with a client and frees up resources.

Arguments:

    lpClientContext - a pointer to the context structure that contains
        information about this client.

    bGraceful - TRUE if the close should be graceful, FALSE otherwise.

Return Value:

    None.

--*/

{
    LINGER lingerStruct;

    //
    // If we're supposed to abort the connection, set the linger value
    // on the socket to 0.
    //

    if ( !bGraceful ) {
        lingerStruct.l_onoff = 1;
        lingerStruct.l_linger = 0;
        setsockopt( lpClientContext->Socket, SOL_SOCKET, SO_LINGER,
                    (char *)&lingerStruct, sizeof(lingerStruct) );
    }

    //
    // Now close the socket handle.  This will do an abortive or 
    // graceful close, as requested.  
    //

    closesocket( lpClientContext->Socket );

    //
    // Free context structuyres.
    //

    LocalFree( lpClientContext->Context );
    LocalFree( lpClientContext );

    return;
    
} // CloseClient
