/*++

Copyright 1996-1997 Microsoft Corporation

Copyright (c) 1996 Intel Corp

Module Name:

    perftest.cpp

Abstract:

    This  module  contains  demonstration code which illustrates how to install
    and  use  a  service provider.  This demonstration code is designed to work
    together only with the temporary sample skeleton "null" service provider.

--*/

#include <windows.h>
#include "nullpdef.h"
#include "ws2spi.h"



//
//  Unique GUID generated with UUIDGEN:
//   ba657007-d615-11cf-9f5c-08003e301875
//
//  WARNING:  If you use this sample code, you must generate your own
//   GUID.  Under no circumstances should you use this GUID.
//

GUID ProviderIDGuid = { 0xba657007, 0xd615, 0x11cf, 0x9f, 0x5c,
                     0x08, 0x00, 0x3e, 0x30, 0x18, 0x75 };


//
// Dummy name as unicode string
//

#define SAMPLE_NAME_WSTRING L"Null Provider protocol for sample"

// The  nominal  size  of  send  and  receive operations.  Since we expect this
// sample code to be used only with a "null" provider that does not really send
// or receive data, the value is arbitrary and has no real effect.

#define SEND_RECEIVE_BYTES  100




static
void
Test_Send(
    IN  SOCKET  SendSock,
    IN  DWORD   NumTries
    )
/*++
Routine Description:

    This  procedure  performs the indicated number of send operations through a
    socket.

Arguments:

    SendSock - Supplies the socket to be used for the "send" operations.

    NumTries - Supplies the number of tries.

Return Value:

    none

Implementation:

    We  use  an "unrolled" loop to perform a large number of calls back-to-back
    without  loop turnaround overhead.  Then we perform the remaining number of
    calls.   This  should  help  reduce  the  overall  contribution of the loop
    overhead,  which  might  be  relevant  if this were being used as part of a
    performance measurement.
--*/
{
    DWORD    unrolled_iterations;
    DWORD    remaining_iterations;
    DWORD    i;
    int      send_result;
    WSABUF   send_bufs;
    CHAR     data_space[SEND_RECEIVE_BYTES];
    DWORD    bytes_sent;

#define SEND_ONCE \
    send_result = WSASend(                       \
        SendSock,      /* s                   */ \
        & send_bufs,   /* lpBuffers           */ \
        1,             /* dwBufferCount       */ \
        & bytes_sent,  /* lpNumberOfBytesSent */ \
        0,             /* dwFlags             */ \
        NULL,          /* lpOverlapped        */ \
        NULL)          /* lpCompletionRoutine */

#define UNROLLED_LENGTH 50

    unrolled_iterations  = NumTries / UNROLLED_LENGTH;
    remaining_iterations = NumTries % UNROLLED_LENGTH;
    send_bufs.len = SEND_RECEIVE_BYTES;
    send_bufs.buf = data_space;

    for (i = 0; i < unrolled_iterations; i++) {
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
        SEND_ONCE;
    } // for i

    for (i = 0; i < remaining_iterations; i++) {
        SEND_ONCE;
    } // for i
    
} // Test_Send




static
SOCKET
Create_Test_Socket(
    void)
/*++
Routine Description:

    This  procedure  creates a socket to be used for the tests through the null
    provider.

Arguments:

    none
    
Return Value:

    The  procedure  returns  the  newly  created  socket  if  it is successful,
    otherwise it returns INVALID_SOCKET.
--*/
{
    SOCKET  new_socket;

    new_socket = WSASocket(
        AF_SPECIAL_NULL,   // af
        SOCK_STREAM,       // type
        0,                 // protocol
        NULL,              // lpProtocolInfo
        0,                 // g
        0);                // dwFlags
    return(new_socket);

} // Create_Test_Socket




static
void
Destroy_Test_Socket(
    IN  SOCKET  TestSock
    )
/*++
Routine Description:

    This  procedure  closes  a socket that was being used for tests through the
    null provider.

Arguments:

    TestSock - Supplies the socket to be closed.
    
Return Value:

    none
--*/
{
    int    close_result;
    DWORD  last_error;

    close_result = closesocket(
        TestSock);
    if (close_result != ERROR_SUCCESS) {
        last_error = GetLastError();
        last_error = GetLastError();  // Redundant for single-step convenience.
    }
    
} // Destroy_Test_Socket




static
DWORD
Establish_Provider(
    void
    )
/*++
Routine Description:

    This procedure makes sure the null provider is installed and installs it if
    it is not already installed.

    Normally  an  application  program  would  NOT actually install a provider.
    Installation  was  bundled into this application example simply to make the
    example compact.

Arguments:

    none
    
Return Value:


--*/
{
    LPWSAPROTOCOL_INFOW  proto_buf;
    DWORD                size_guess;
    BOOL                 still_trying;
    BOOL                 got_protos;
    int                  enum_result;
    int                  error_code;
    BOOL                 found_null_prov;

    size_guess = 0;
    got_protos = FALSE;
    still_trying = TRUE;
    proto_buf = NULL;

    // We  call  WSCEnumProtocols  twice.   The first call determines how big a
    // buffer  we will actually need for the results.  The second call actually
    // retrieves  the  results.  In a situation such as this, I generally write
    // the  sequence  of  two  calls  as  a  loop,  since this way the call and
    // error-check code has to be written only once.
    while (still_trying) {
        enum_result = WSCEnumProtocols(
            NULL,           // lpiProtocols
            proto_buf,      // lpProtocolBuffer
            & size_guess,   // lpdwBufferLength
            & error_code);  // lpErrno
        if (enum_result != SOCKET_ERROR) {
            got_protos = TRUE;
            still_trying = FALSE;
        }
        else {
            if (error_code == WSAENOBUFS) {
                delete proto_buf;
                proto_buf = (LPWSAPROTOCOL_INFOW) new char[size_guess];
                if (proto_buf == NULL) {
                    still_trying = FALSE;
                }
            }
            else {
                still_trying = FALSE;
            }
        }
    } // while still_trying

    found_null_prov = FALSE;
    if (got_protos) {
        int  i;

        for (i = 0; i < enum_result; i++) {
            if (proto_buf[i].iAddressFamily == AF_SPECIAL_NULL) {
                found_null_prov = TRUE;
                break;
            }
        }
    }
    delete proto_buf;

    if (! found_null_prov) {
        WSAPROTOCOL_INFOW proto_info;
        int               install_result;
        int               install_error;

        proto_info.dwServiceFlags1 = 0;
        proto_info.dwServiceFlags2 = 0;
        proto_info.dwServiceFlags3 = 0;
        proto_info.dwServiceFlags4 = 0;
        proto_info.dwProviderFlags = PFL_MATCHES_PROTOCOL_ZERO;
        proto_info.dwCatalogEntryId = 0;   // filled in by system
        proto_info.ProtocolChain.ChainLen = BASE_PROTOCOL;
        proto_info.iVersion = 0;
        proto_info.iAddressFamily = AF_SPECIAL_NULL;
        proto_info.iMaxSockAddr = 16;
        proto_info.iMinSockAddr = 16;
        proto_info.iSocketType = SOCK_STREAM;
        proto_info.iProtocol = 0;
        proto_info.iProtocolMaxOffset = 0;
        proto_info.iNetworkByteOrder = BIGENDIAN;
        proto_info.iSecurityScheme = SECURITY_PROTOCOL_NONE;
        proto_info.dwMessageSize = 0;  // stream-oriented
        proto_info.dwProviderReserved = 0;

        proto_info.ProviderId = ProviderIDGuid ; // filled in by system.

        // copy unicode string into name parameter
        memcpy(proto_info.szProtocol, SAMPLE_NAME_WSTRING, sizeof SAMPLE_NAME_WSTRING);


        install_result = WSCInstallProvider(
            &ProviderIDGuid,   // lpProviderID
            L"nullprov.dll",   // lpszProviderDllPath (unicode string)
            & proto_info,      // lpProtocolInfoList
            1,                 // dwNumberOfEntries
            & install_error);  // lpErrno
        if (install_result != ERROR_SUCCESS) {
            install_error = install_error;
            // assert(install_result == ERROR_SUCCESS);
        }
    } // if not found_null_prov

    return(TRUE);
    
} // Establish_Provider
    



void
main(
    void
    )
/*++
--*/
{
    SOCKET   test_sock;
    int      start_return;
    WSADATA  winsock_data;
    DWORD    last_error;
    int      clean_return;
    DWORD    num_tries;

    Establish_Provider();

    start_return = WSAStartup(
        MAKEWORD(2,0),    // wVersionRequested
        & winsock_data);  // lpWSAData

    if (start_return == ERROR_SUCCESS) {
        test_sock = Create_Test_Socket();
        // To  keep  this  sample  simple,  this  demonstration program and the
        // matching  null  provider  do  not  bother  binding or connecting the
        // socket  before  doing  "send" operations.  With a real provider, one
        // should  bind  and possibly also connect the socket before proceeding
        // with a "send".
        if (test_sock != INVALID_SOCKET) {
            num_tries = 10;
            Test_Send(
                test_sock,   // SendSock
                num_tries);  // NumTries
            Destroy_Test_Socket(
                test_sock);
        } // if test_sock != NULL
        else {
            last_error = GetLastError();
            // The  following  is  just  a  redundant executable statement that
            // allows   me   to   see   the   return  value  conveniently  when
            // single-stepping.
            last_error = GetLastError();
        }
    } // if start_return == ERROR_SUCCESS
    else {
        last_error = GetLastError();
        last_error = GetLastError();  // Redundant for single-step convenience.
    }

    clean_return = WSACleanup();
    clean_return = clean_return; // Redundant for single-step convenience.
    
} // main
