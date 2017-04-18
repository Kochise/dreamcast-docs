/*++

Copyright 1996-1997 Microsoft Corporation

Copyright (c) 1996 Intel Corp

Module Name:

    nullprov.cpp

Abstract:

    This  module  provides  a  "null" provider for the purpose of demonstrating
    what  it  takes  to  get  a  service  provider  installed and started.  The
    provider pretty much does nothing but pretend to send and receive data.

--*/


//
// The Service Provider Interface was widened to Unicode in version 2.2.
//  All of the parameters that involve strings in this module all provided
//  in their "transparent" form.  They are switched to the wide character
//  version, at compile time, by the following define:
//

#define UNICODE

#include <windows.h>
#include "ws2spi.h"

#include "nullpdef.h"


// Global Upcall table with WinSock 2 DLL upcall entry points.
WSPUPCALLTABLE g_upcalls;

// Global protocol info struct of the one protocol we support.
WSAPROTOCOL_INFOA  g_protoinfo;







SOCKET WSPAPI WSPAccept(
    SOCKET s,
    struct sockaddr FAR * addr,
    LPINT addrlen,
    LPCONDITIONPROC lpfnCondition,
    DWORD dwCallbackData,
    LPINT lpErrno
    )
/*++
--*/
{
    // Not implemented
    return(INVALID_SOCKET);
} // lpWSPAccept




INT WSPAPI WSPAddressToString(
    LPSOCKADDR lpsaAddress,
    DWORD dwAddressLength,
    LPWSAPROTOCOL_INFO lpProtocolInfo,
    LPTSTR lpszAddressString,
    LPDWORD lpdwAddressStringLength,
    LPINT lpErrno
    )
/*++
--*/
{
    // Not implemented
    return(SOCKET_ERROR);
} // lpWSPAddressToString




int WSPAPI WSPAsyncSelect(
    SOCKET s,
    HWND hWnd,
    unsigned int wMsg,
    long lEvent,
    LPINT lpErrno
    )
/*++
--*/
{
    // Not implemented
    return(SOCKET_ERROR);
} // lpWSPAsyncSelect




int WSPAPI WSPBind(
    SOCKET s,
    const struct sockaddr FAR * name,
    int namelen,
    LPINT lpErrno
    )
/*++
Implementation:

    A  simple  implementation  is  supplied.  The implementation simply returns
    success without really doing anything.
--*/
{
    * lpErrno = ERROR_SUCCESS;
    return(ERROR_SUCCESS);

} // lpWSPBind




int WSPAPI WSPCancelBlockingCall(
    LPINT lpErrno
    )
/*++
Implementation:

    A  simple  implementation  is  supplied.  The implementation simply returns
    success without really doing anything.
--*/
{
    * lpErrno = ERROR_SUCCESS;
    return(ERROR_SUCCESS);

} // lpWSPCancelBlockingCall




int WSPAPI WSPCleanup(
    LPINT lpErrno
    )
/*++
Implementation

    A  simple  implementation  is  supplied.  The implementation simply returns
    success  without  really  doing  anything.   This is technically incorrect,
    since  we  should really maintain an up/down count of Startup/Cleanup pairs
    and  return  an  error  code  if  WSPCleanup  is called when there is not a
    WSPStartup outstanding.
--*/
{
    * lpErrno = ERROR_SUCCESS;
    return(ERROR_SUCCESS);

} // lpWSPCleanup




int WSPAPI WSPCloseSocket(
    SOCKET s,
    LPINT lpErrno
    )
/*++
Implementation

    Perform  an  upcall to the WinSock 2 DLL to inform it of the removal of the
    socket handle.  Return the result.
--*/
{
    int close_result;

    close_result = (* g_upcalls.lpWPUCloseSocketHandle)(
        s,         // s
        lpErrno);  // lpErrno
    return(close_result);

} // lpWSPCloseSocket




int WSPAPI WSPConnect(
    SOCKET s,
    const struct sockaddr FAR * name,
    int namelen,
    LPWSABUF lpCallerData,
    LPWSABUF lpCalleeData,
    LPQOS lpSQOS,
    LPQOS lpGQOS,
    LPINT lpErrno
    )
/*++
Implementation

    A  simple implementation is supplied.  It indicates that no callee data was
    retrieved and returns success.
--*/
{
    if (lpCalleeData != NULL) {
        lpCalleeData->len = 0;
    }
    * lpErrno = ERROR_SUCCESS;
    return(ERROR_SUCCESS);

} // lpWSPConnect




int WSPAPI WSPDuplicateSocket(
    SOCKET s,
    DWORD dwProcessId,
    LPWSAPROTOCOL_INFO lpProtocolInfo,
    LPINT lpErrno
    )
/*++
--*/
{
    // Not implemented
    return(SOCKET_ERROR);
} // lpWSPDuplicateSocket




int WSPAPI WSPEnumNetworkEvents(
    SOCKET s,
    WSAEVENT hEventObject,
    LPWSANETWORKEVENTS lpNetworkEvents,
    LPINT lpErrno
    )
/*++
--*/
{
    // Not implemented
    return(SOCKET_ERROR);
} // lpWSPEnumNetworkEvents




int WSPAPI WSPEventSelect(
    SOCKET s,
    WSAEVENT hEventObject,
    long lNetworkEvents,
    LPINT lpErrno
    )
/*++
--*/
{
    // Not implemented
    return(SOCKET_ERROR);
} // lpWSPEventSelect




int WSPAPI WSPGetOverlappedResult(
    SOCKET s,
    LPWSAOVERLAPPED lpOverlapped,
    LPDWORD lpcbTransfer,
    BOOL fWait,
    LPDWORD lpdwFlags,
    LPINT lpErrno
    )
/*++
--*/
{
    // Not implemented
    return(FALSE);
} // lpWSPGetOverlappedResult




int WSPAPI WSPGetPeerName(
    SOCKET s,
    struct sockaddr FAR * name,
    LPINT namelen,
    LPINT lpErrno
    )
/*++
--*/
{
    // Not implemented
    return(SOCKET_ERROR);
} // lpWSPGetPeerName




int WSPAPI WSPGetSockName(
    SOCKET s,
    struct sockaddr FAR * name,
    LPINT namelen,
    LPINT lpErrno
    )
/*++
--*/
{
    // Not implemented
    return(SOCKET_ERROR);
} // lpWSPGetSockName




int WSPAPI WSPGetSockOpt(
    SOCKET s,
    int level,
    int optname,
    char FAR * optval,
    LPINT optlen,
    LPINT lpErrno
    )
/*++
--*/
{
    // Not implemented
    return(SOCKET_ERROR);
} // lpWSPGetSockOpt




BOOL WSPAPI WSPGetQOSByName(
    SOCKET s,
    LPWSABUF lpQOSName,
    LPQOS lpQOS,
    LPINT lpErrno
    )
/*++
--*/
{
    // Not implemented
    return(FALSE);
} // lpWSPGetQOSByName




int WSPAPI WSPIoctl(
    SOCKET s,
    DWORD dwIoControlCode,
    LPVOID lpvInBuffer,
    DWORD cbInBuffer,
    LPVOID lpvOutBuffer,
    DWORD cbOutBuffer,
    LPDWORD lpcbBytesReturned,
    LPWSAOVERLAPPED lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
    LPWSATHREADID lpThreadId,
    LPINT lpErrno
    )
/*++
Not implemented,
--*/
{
    // Not implemented
    return(SOCKET_ERROR);

} // lpWSPIoctl




SOCKET WSPAPI WSPJoinLeaf(
    SOCKET s,
    const struct sockaddr FAR * name,
    int namelen,
    LPWSABUF lpCallerData,
    LPWSABUF lpCalleeData,
    LPQOS lpSQOS,
    LPQOS lpGQOS,
    DWORD dwFlags,
    LPINT lpErrno
    )
/*++
--*/
{
    // Not implemented
    return(INVALID_SOCKET);
} // lpWSPJoinLeaf




int WSPAPI WSPListen(
    SOCKET s,
    int backlog,
    LPINT lpErrno
    )
/*++
--*/
{
    // Not implemented
    return(SOCKET_ERROR);
} // lpWSPListen




int WSPAPI WSPRecv(
    SOCKET s,
    LPWSABUF lpBuffers,
    DWORD dwBufferCount,
    LPDWORD lpNumberOfBytesRecvd,
    LPDWORD lpFlags,
    LPWSAOVERLAPPED lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
    LPWSATHREADID lpThreadId,
    LPINT lpErrno
    )
/*++
Implementation

    A  simple  implementation  is  supplied.   The  number of bytes received is
    simply  filled  in as the number requested.  No actual data is deposited in
    the  buffers.   The  client  will  "see"  whatever data happens to be there
    already.

    This  simple implementation also violates the specification in that it does
    not  support  overlapped  I/O.  It simply returns an error indication if an
    attempt is made to use overlapped I/O features.
--*/
{
    if ((lpOverlapped != NULL) ||
        (lpCompletionRoutine != NULL)) {
        // Overlapped I/O and its animal friends not implemented.
        *lpErrno = WSAEINVAL;
        return(SOCKET_ERROR);
    }

    // Pretend to receive some data
    * lpNumberOfBytesRecvd = lpBuffers[0].len;
    * lpFlags = 0;
    * lpErrno = ERROR_SUCCESS;
    return(ERROR_SUCCESS);

} // lpWSPRecv




int WSPAPI WSPRecvDisconnect(
    SOCKET s,
    LPWSABUF lpInboundDisconnectData,
    LPINT lpErrno
    )
/*++
--*/
{
    // Not implemented
    return(SOCKET_ERROR);
} // lpWSPRecvDisconnect




int WSPAPI WSPRecvFrom(
    SOCKET s,
    LPWSABUF lpBuffers,
    DWORD dwBufferCount,
    LPDWORD lpNumberOfBytesRecvd,
    LPDWORD lpFlags,
    struct sockaddr FAR * lpFrom,
    LPINT lpFromlen,
    LPWSAOVERLAPPED lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
    LPWSATHREADID lpThreadId,
    LPINT lpErrno
    )
/*++
Implementation

    A  simple  implementation  is  supplied.   The  number of bytes received is
    simply  filled  in as the number requested.  The "received from" address is
    filled  in  with  a length of zero.  This might be an unexpected result, in
    which case it could be changed to fill in some dummy constant address.

    This  simple implementation also violates the specification in that it does
    not  support  overlapped  I/O.  It simply returns an error indication if an
    attempt is made to use overlapped I/O features.
--*/
{
    if ((lpOverlapped != NULL) ||
        (lpCompletionRoutine != NULL)) {
        // Overlapped I/O and its animal friends not implemented.
        *lpErrno = WSAEINVAL;
        return(SOCKET_ERROR);
    }

    // Pretend to receive some data
    * lpNumberOfBytesRecvd = lpBuffers[0].len;
    * lpFlags = 0;
    if (lpFromlen != NULL) {
        * lpFromlen = 0;
    }
    * lpErrno = ERROR_SUCCESS;
    return(ERROR_SUCCESS);

} // lpWSPRecvFrom




int WSPAPI WSPSelect(
    int nfds,
    fd_set FAR * readfds,
    fd_set FAR * writefds,
    fd_set FAR * exceptfds,
    const struct timeval FAR * timeout,
    LPINT lpErrno
    )
/*++
--*/
{
    // Not implemented
    return(SOCKET_ERROR);
} // lpWSPSelect




int WSPAPI WSPSend(
    SOCKET s,
    LPWSABUF lpBuffers,
    DWORD dwBufferCount,
    LPDWORD lpNumberOfBytesSent,
    DWORD dwFlags,
    LPWSAOVERLAPPED lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
    LPWSATHREADID lpThreadId,
    LPINT lpErrno
    )
/*++
Implementation

    A  simple  implementation is supplied.  This implementation simply computes
    the total number of bytes the client is attempting to send and fills in the
    result to indicate that all the requested bytes were successfully sent.

    This  simple implementation also violates the specification in that it does
    not  support  overlapped  I/O.  It simply returns an error indication if an
    attempt is made to use overlapped I/O features.
--*/
{
    DWORD bytes_sent;
    DWORD buf_index;
    
    if ((lpOverlapped != NULL) ||
        (lpCompletionRoutine != NULL)) {
        // Overlapped I/O and its animal friends not implemented.
        *lpErrno = WSAEINVAL;
        return(SOCKET_ERROR);
    }

    bytes_sent = 0;
    for (buf_index = 0; buf_index < dwBufferCount; buf_index++) {
        bytes_sent += lpBuffers[buf_index].len;
    } // for buf_index
    * lpNumberOfBytesSent = bytes_sent;
    * lpErrno = ERROR_SUCCESS;
    return(ERROR_SUCCESS);

} // lpWSPSend




int WSPAPI WSPSendDisconnect(
    SOCKET s,
    LPWSABUF lpOutboundDisconnectData,
    LPINT lpErrno
    )
/*++
Implementation

    A  simple  implementation is supplied.  This implementation simply computes
    the total number of bytes the client is attempting to send and fills in the
    result to indicate that all the requested bytes were successfully sent.

    This  simple implementation also violates the specification in that it does
    not  support  overlapped  I/O.  It simply returns an error indication if an
    attempt is made to use overlapped I/O features.
--*/
{
    // Not implemented
    return(SOCKET_ERROR);
} // lpWSPSendDisconnect




int WSPAPI WSPSendTo(
    SOCKET s,
    LPWSABUF lpBuffers,
    DWORD dwBufferCount,
    LPDWORD lpNumberOfBytesSent,
    DWORD dwFlags,
    const struct sockaddr FAR * lpTo,
    int iTolen,
    LPWSAOVERLAPPED lpOverlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine,
    LPWSATHREADID lpThreadId,
    LPINT lpErrno
    )
/*++
--*/
{
    DWORD bytes_sent;
    DWORD buf_index;
    
    if ((lpOverlapped != NULL) ||
        (lpCompletionRoutine != NULL)) {
        // Overlapped I/O and its animal friends not implemented.
        *lpErrno = WSAEINVAL;
        return(SOCKET_ERROR);
    }

    bytes_sent = 0;
    for (buf_index = 0; buf_index < dwBufferCount; buf_index++) {
        bytes_sent += lpBuffers[buf_index].len;
    } // for buf_index
    * lpNumberOfBytesSent = bytes_sent;
    * lpErrno = ERROR_SUCCESS;
    return(ERROR_SUCCESS);
    
} // lpWSPSendTo




int WSPAPI WSPSetSockOpt(
    SOCKET s,
    int level,
    int optname,
    const char FAR * optval,
    int optlen,
    LPINT lpErrno
    )
/*++
--*/
{
    // Not implemented
    return(SOCKET_ERROR);
} // lpWSPSetSockOpt




int WSPAPI WSPShutdown(
    SOCKET s,
    int how,
    LPINT lpErrno
    )
/*++
--*/
{
    // Not implemented
    return(SOCKET_ERROR);
} // lpWSPShutdown




SOCKET WSPAPI WSPSocket(
    int af,
    int type,
    int protocol,
    LPWSAPROTOCOL_INFO lpProtocolInfo,
    GROUP g,
    DWORD dwFlags,
    LPINT lpErrno
    )
/*++
Implementation

    A  simple  implementation  is  supplied.   The procedure simply performs an
    upcall  to  the  WinSock  2 DLL to allocate a socket handle.  The allocated
    socket handle is returned as the new socket handle.

    Note that this implementation does not keep any state information about the
    "socket"  it  allocated.   Consequently,  it simply uses 0 as the "context"
    value  associated with the socket handle.  If it were desired to keep state
    information  for  the  socket,  the  implementation  would  allocate a data
    structure  to  store the state information, cast the data structure pointer
    into a DWORD, and use this value as the dwContext.  When the implementation
    needed    to    access    the    state    information,    it   would   call
    WPUQuerySocketHandleContext  and  cast  the  retrieved  DWORD  back  to the
    appropriate data structure pointer.
--*/
{
    SOCKET  new_socket;

    new_socket = (* g_upcalls.lpWPUCreateSocketHandle)(
        g_protoinfo.dwCatalogEntryId,  // dwCatalogEntryId
        0,                             // dwContext
        lpErrno);                      // lpErrno

    return(new_socket);

} // lpWSPSocket




INT WSPAPI WSPStringToAddress(
    LPTSTR AddressString,
    INT AddressFamily,
    LPWSAPROTOCOL_INFO lpProtocolInfo,
    LPSOCKADDR lpAddress,
    LPINT lpAddressLength,
    LPINT     lpErrno
    )
/*++
--*/
{
    // Not implemented
    return(SOCKET_ERROR);
} // lpWSPStringToAddress




int WSPAPI WSPStartup(
    WORD wVersionRequested,
    LPWSPDATA lpWSPData,
    LPWSAPROTOCOL_INFO lpProtocolInfo,
    WSPUPCALLTABLE UpcallTable,
    LPWSPPROC_TABLE lpProcTable
    )
/*++
Implementation

    A  simple implementation is provided.  This just fills in required WSPData,
    a  procedure  table,  and returns success.  Technically this implementation
    violates  the  specification  since  it should maintain an up/down count of
    WSPStartup/WSPCleanup pairs.
--*/
{
    // Make  sure  that  the version requested is == 2.0 because that is all we
    // support.
    //
    // The  low  byte  is  the  major  version  and  the high byte is the minor
    // version.

    if ( LOBYTE( wVersionRequested ) < 2) {
        return WSAVERNOTSUPPORTED;
    }

    lpWSPData->wVersion = MAKEWORD( 2, 0 );
    lpWSPData->wHighVersion = MAKEWORD( 2, 0 );

#define szDESCRIPTION "Null Provider for WinSock 2 preliminary sample source"
    memcpy (lpWSPData->szDescription, szDESCRIPTION, sizeof szDESCRIPTION);

    memcpy (&g_protoinfo, lpProtocolInfo, sizeof WSAPROTOCOL_INFO);
    
    g_upcalls = UpcallTable;

    lpProcTable->lpWSPAccept = WSPAccept;
    lpProcTable->lpWSPAddressToString = WSPAddressToString;
    lpProcTable->lpWSPAsyncSelect = WSPAsyncSelect;
    lpProcTable->lpWSPBind = WSPBind;
    lpProcTable->lpWSPCancelBlockingCall = WSPCancelBlockingCall;
    lpProcTable->lpWSPCleanup = WSPCleanup;
    lpProcTable->lpWSPCloseSocket = WSPCloseSocket;
    lpProcTable->lpWSPConnect = WSPConnect;
    lpProcTable->lpWSPDuplicateSocket = WSPDuplicateSocket;
    lpProcTable->lpWSPEnumNetworkEvents = WSPEnumNetworkEvents;
    lpProcTable->lpWSPEventSelect = WSPEventSelect;
    lpProcTable->lpWSPGetOverlappedResult = WSPGetOverlappedResult;
    lpProcTable->lpWSPGetPeerName = WSPGetPeerName;
    lpProcTable->lpWSPGetSockName = WSPGetSockName;
    lpProcTable->lpWSPGetSockOpt = WSPGetSockOpt;
    lpProcTable->lpWSPGetQOSByName = WSPGetQOSByName;
    lpProcTable->lpWSPIoctl = WSPIoctl;
    lpProcTable->lpWSPJoinLeaf = WSPJoinLeaf;
    lpProcTable->lpWSPListen = WSPListen;
    lpProcTable->lpWSPRecv = WSPRecv;
    lpProcTable->lpWSPRecvDisconnect = WSPRecvDisconnect;
    lpProcTable->lpWSPRecvFrom = WSPRecvFrom;
    lpProcTable->lpWSPSelect = WSPSelect;
    lpProcTable->lpWSPSend = WSPSend;
    lpProcTable->lpWSPSendDisconnect = WSPSendDisconnect;
    lpProcTable->lpWSPSendTo = WSPSendTo;
    lpProcTable->lpWSPSetSockOpt = WSPSetSockOpt;
    lpProcTable->lpWSPShutdown = WSPShutdown;
    lpProcTable->lpWSPSocket = WSPSocket;
    lpProcTable->lpWSPStringToAddress = WSPStringToAddress;

    return(ERROR_SUCCESS);
    
} // WSPStartup
