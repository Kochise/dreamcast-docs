
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
//  File:       pop3.c
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

DWORD
WINAPI
WorkerThread (
    LPVOID WorkContext
    );


HANDLE
InitializeThreads (
    VOID
    )

/*++

Routine Description:

    Starts up the POP3SRV worker threads.  We use two worker threads
    for eachprocessor on the system--this is choosen as a good balance
    that ensures that there are a sufficient number of threads available
    to get useful work done but not too many that context switches
    consume significant overhead.

Arguments:

    None.

Return Value:

    HANDLE - A handle to the completion port if everything was 
        successful, or NULL if there was a failure.  

--*/

{

    SOCKET s;
    DWORD i;
    HANDLE hCompletionPort;
    HANDLE hThreadHandle;
    DWORD dwThreadId;
    SYSTEM_INFO systemInfo;

    //
    // First open a temporary socket that we will use to create the
    // completion port.  In NT 3.51 it will not be necessary to specify
    // the FileHandle parameter of CreateIoCompletionPort()--it will
    // be legal to specify FileHandle as NULL.  However, for NT 3.5
    // we need an overlapped file handle.
    //

    s = socket( AF_INET, SOCK_DGRAM, 0 );
    if ( s == INVALID_SOCKET ) {
        return NULL;
    }

    //
    // Create the completion port that will be used by all the worker
    // threads.
    //

    hCompletionPort = CreateIoCompletionPort( (HANDLE)s, NULL, 0, 0 );
    if ( hCompletionPort == NULL ) {
        closesocket( s );
        return NULL;
    }

    //
    // Close the socket, we don't need it any longer.
    //

    closesocket( s );

    //
    // Determine how many processors are on the system.
    //

    GetSystemInfo( &systemInfo );

    //
    // Create worker threads that will service the actual overlapped
    // I/O requests.  Create two worker threads for each processor
    // on the system.
    //

    for ( i = 0; i < systemInfo.dwNumberOfProcessors*2; i++ ) {

        hThreadHandle = CreateThread(
                            NULL,
                            0,
                            WorkerThread,
                            hCompletionPort,
                            0,
                            &dwThreadId
                            );
        if ( hThreadHandle == NULL ) {
            CloseHandle( hCompletionPort );
            return NULL;
        }

        //
        // Close each thread handle as we open them.  We do not need
        // the thread handles.  Note that each thread will continue
        // executing.
        //

        CloseHandle( hThreadHandle );
    }

    //
    // All was successful.
    //

    return hCompletionPort;

} // InitializeThreads


DWORD
WINAPI
WorkerThread (
    LPVOID WorkContext
    )

/*++

Routine Description:

    This is the main worker routine for the POP3SRV worker threads.  
    Worker threads wait on a completion port for I/O to complete.  When 
    it completes, the worker thread processes the I/O, then either pends 
    new I/O or closes the client's connection.  When the service shuts 
    down, other code closes the completion port which causes 
    GetQueuedCompletionStatus() to wake up and the worker thread then 
    exits.  

Arguments:

    WorkContext - the completion port handle that will get I/O completion
        notifications.

Return Value:

    DWORD - status of the thread.

--*/

{
    HANDLE hCompletionPort = WorkContext;
    BOOL bSuccess;
    DWORD dwIoSize;
    LPOVERLAPPED lpOverlapped;
    PCLIENT_CONTEXT lpClientContext;
    Pop3Disposition Disposition;
    HANDLE hFile;
    CHAR * OutputBuffer;
    DWORD OutputBufferLen;
    TRANSMIT_FILE_BUFFERS TranfileBuffers;

    //
    // Loop servicing I/O completions.
    //

    while ( TRUE ) {

        // --- DavidTr: Slide 14(b) ------------------------------------------
        //
        // Get a completed IO request.
        //

        bSuccess = GetQueuedCompletionStatus(
                       hCompletionPort,
                       &dwIoSize,
                       (LPDWORD)&lpClientContext,
                       &lpOverlapped,
                       (DWORD)-1
                       );

        //
        // If the service is terminating, exit this thread.
        //

        if ( bServiceTerminating ) {
            return 0;
        }

        //
        // If the IO failed, close the socket and free context.
        //

        if ( !bSuccess ) {
            CloseClient( lpClientContext, FALSE );
            continue;
        }

        //
        // If the request was a read, process the client request.
        //

        if ( lpClientContext->LastClientIo == ClientIoRead ) {

            //
            // BUGBUG: if this were a real production piece of code,
            // we would check here for an incomplete read.  Because
            // TCP/IP is a stream oriented protocol, it is feasible
            // that we could receive part of a client request.
            // Therefore, we should check for the CRLF that ends a
            // client request.
            //

            //
            // Process the request.  Pop3Dispatch() handles all aspects 
            // of the request and tells us how to respond to the client.  
            //

            Disposition = Pop3Dispatch(
                              lpClientContext->Context,
                              lpClientContext->Buffer,
                              dwIoSize,
                              &hFile,
                              &OutputBuffer,
                              &OutputBufferLen
                              );

            //
            // Act based on the Disposition.
            //

            switch ( Disposition ) {

            case Pop3_Discard:
                break;

            case Pop3_SendError:
            case Pop3_SendBuffer:

                // --- DavidTr: Slide 7(a) -----------------------------------
                //
                // Set up context information and perform an overlapped 
                // write on the socket.  
                //

                lpClientContext->LastClientIo = ClientIoWrite;
                lpClientContext->TransmittedBuffer = OutputBuffer;

                bSuccess = WriteFile(
                               (HANDLE)lpClientContext->Socket,
                               OutputBuffer,
                               OutputBufferLen,
                               &dwIoSize,
                               &lpClientContext->Overlapped
                               );
                if ( !bSuccess && GetLastError( ) != ERROR_IO_PENDING ) {
                    CloseClient( lpClientContext, FALSE );
                    continue;
                }

                //
                // Continue looping to get completed IO requests--we
                // do not want to pend another read now.
                //

                continue;

            case Pop3_SendFile:
            case Pop3_SendBufferThenFile:

                //
                // Determine based on the disposition whether we will
                // need to send a head or tail buffer.
                //

                if ( Disposition == Pop3_SendFile ) {
                    TranfileBuffers.Head = NULL;
                    TranfileBuffers.HeadLength = 0;
                } else if ( Disposition == Pop3_SendBufferThenFile ) {
                    TranfileBuffers.Head = OutputBuffer;
                    TranfileBuffers.HeadLength = OutputBufferLen;
                }

                //
                // After the file, we're going to send a .CRLF sequence 
                // so that the client detects EOF.  Note that 
                // TransmitFile() will send this terminator in the same 
                // packet as the last chunk of the file, thereby saving 
                // network traffic.  
                //

                TranfileBuffers.Tail = ".\r\n";
                TranfileBuffers.TailLength = 3;

                //
                // Set up context for the I/O so that we know how to act 
                // when the I/O completes.  
                //

                lpClientContext->LastClientIo = ClientIoTransmitFile;
                lpClientContext->TransmittedFile = hFile;
                lpClientContext->TransmittedBuffer = OutputBuffer;

                // --- DavidTr: Slide 21 ---------------------------------
                //
                // Now transmit the file and the data buffers.
                //

                bSuccess = TransmitFile(
                               lpClientContext->Socket,
                               hFile,
                               0,
                               0,
                               &lpClientContext->Overlapped,
                               &TranfileBuffers,
                               0
                               );
                if ( !bSuccess && GetLastError( ) != ERROR_IO_PENDING ) {
                    CloseClient( lpClientContext, FALSE );
                    continue;
                }

                //
                // Continue looping to get completed IO requests--we
                // do not want to pend another read now.
                //

                continue;
            }

        } else if ( lpClientContext->LastClientIo == ClientIoWrite ) {

            //
            // Clean up after the WriteFile().
            //

            LocalFree( lpClientContext->TransmittedBuffer );

        } else if ( lpClientContext->LastClientIo == ClientIoTransmitFile ) {

            //
            // Clean up after the TransmitFile().
            //

            CloseHandle( lpClientContext->TransmittedFile );
            LocalFree( lpClientContext->TransmittedBuffer );
        } 

        // --- DavidTr: Slide 7(b) ---------------------------------------
        //
        // Pend another read request to get the next client request.
        //

        lpClientContext->LastClientIo = ClientIoRead;
        lpClientContext->BytesReadSoFar = 0;

        bSuccess = ReadFile(
                       (HANDLE)lpClientContext->Socket,
                       lpClientContext->Buffer,
                       sizeof(lpClientContext->Buffer),
                       &dwIoSize,
                       &lpClientContext->Overlapped
                       );
        if ( !bSuccess && GetLastError( ) != ERROR_IO_PENDING ) {
            CloseClient( lpClientContext, FALSE );
            continue;
        }

        //
        // Loop around to get another completed IO request.
        //
    }

    return 0;

} // WorkThread
