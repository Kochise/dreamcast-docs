/*++

Copyright (c) 1992 Microsoft Corporation

Module Name:

    RnrClnt.c

Abstract:

    Setup program for installing/removing the "EchoExample" service.

Author:

    David Treadwell (davidtr)    30-June-1994

Revision History:

    Chuck Y. Chan   (chuckc)     17-July-1994
        Misc cleanup. Pointer based blobs.

--*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winsock.h>
#include <nspapi.h>

WSADATA WsaData;

//
// GUID for Echo-Example created with uuidgen:
//     "47da8500-96a1-11cd-901d-204c4f4f5020"
//

GUID ServiceGuid = { 0x47da8500, 0x96a1, 0x11cd, 0x90, 0x1d,
                     0x20, 0x4c, 0x4f, 0x4f, 0x50, 0x20 };

#define ECHO_SERVICE_TYPE_NAME "EchoExample"
#define ECHO_SERVICE_SAPID     999 
#define ECHO_SERVICE_TCPPORT   999 

void _CRTAPI1
main (
    int argc,
    char *argv[]
    )
{
    INT err;

    SERVICE_INFO serviceInfo;
    LPSERVICE_TYPE_INFO_ABS lpServiceTypeInfo ;
    LPSERVICE_TYPE_VALUE_ABS lpServiceTypeValues ;
    BYTE serviceTypeInfoBuffer[sizeof(SERVICE_TYPE_INFO) + 1024] ;

    DWORD statusFlags;
    DWORD Value1 = 1 ;
    DWORD SapValue = ECHO_SERVICE_SAPID ;
    DWORD TcpPortValue = ECHO_SERVICE_TCPPORT ;
    DWORD operation = SERVICE_ADD_TYPE;

    //
    // Initilize the Windows Sockets DLL.
    //

    err = WSAStartup( 0x0101, &WsaData );
    if ( err == SOCKET_ERROR ) {
        printf( "WSAStartup() failed: %ld\n", GetLastError( ) );
        exit(1);
    }

    //
    // Parse command-line arguments.
    //

    if (argc > 2) {
        printf( "usage: rnrsetup [/ADD | /DEL]\n") ;
        exit(1);
    }

    if (argc == 2) {
        if ( strnicmp( argv[1], "/add", 4 ) == 0 ) {
            operation = SERVICE_ADD_TYPE;
        } else if ( strnicmp( argv[1], "/delete", 4 ) == 0 ) {
            operation = SERVICE_DELETE_TYPE;
        } 
        else {
            printf( "usage: rnrsetup [/ADD | /DEL]\n") ;
            exit(1) ;
        }
    }

    //
    // Set up information to pass to SetService() to add or delete this
    // service.  Most of the SERVICE_INFO fields are not needed for
    // an add or delete operation. The main things of interest are the
    // GUID and the ServiceSpecificInfo structure.
    //

    serviceInfo.lpServiceType    = &ServiceGuid;
    serviceInfo.lpServiceName    = NULL ;           // not used
    serviceInfo.lpComment        = NULL ;           // not used 
    serviceInfo.lpLocale         = NULL;            // not used 
    serviceInfo.dwDisplayHint    = 0;               // not used 
    serviceInfo.dwVersion        = 0;               // not used 
    serviceInfo.dwTime           = 0;               // not used 
    serviceInfo.lpMachineName    = NULL ;           // not used 
    serviceInfo.lpServiceAddress = NULL ;           // not used 

    serviceInfo.ServiceSpecificInfo.pBlobData = serviceTypeInfoBuffer;
    serviceInfo.ServiceSpecificInfo.cbSize = sizeof(serviceTypeInfoBuffer) ;

    //
    // The "blob" receives operation-specific information.  In this 
    // case, fill it with a SERVICE_TYPE_INFO_ABS structure and associated 
    // information.
    //

    lpServiceTypeInfo = (LPSERVICE_TYPE_INFO_ABS) serviceTypeInfoBuffer ;

    lpServiceTypeInfo->dwValueCount = 3 ;
    lpServiceTypeInfo->lpTypeName   = ECHO_SERVICE_TYPE_NAME ;

    lpServiceTypeValues = lpServiceTypeInfo->Values ;

    //
    // The first value tells SAP that this is a connection-oriented
    // service.
    //

    lpServiceTypeValues[0].dwNameSpace = NS_SAP ;
    lpServiceTypeValues[0].dwValueType = REG_DWORD ;
    lpServiceTypeValues[0].dwValueSize = 4 ;
    lpServiceTypeValues[0].lpValueName = SERVICE_TYPE_VALUE_CONN ;
    lpServiceTypeValues[0].lpValue     = &Value1 ;

    //
    // Next, give SAP the object type to use when broadcasting the 
    // service name.  
    //

    lpServiceTypeValues[1].dwNameSpace = NS_SAP ;
    lpServiceTypeValues[1].dwValueType = REG_DWORD ;
    lpServiceTypeValues[1].dwValueSize = sizeof(DWORD) ;
    lpServiceTypeValues[1].lpValueName = SERVICE_TYPE_VALUE_SAPID ;
    lpServiceTypeValues[1].lpValue     = &SapValue ;

    //
    // Tell the TCPIP name space provider that we will be using TCP
    // port 0x999.
    //

    lpServiceTypeValues[2].dwNameSpace = NS_DNS ;
    lpServiceTypeValues[2].dwValueType = REG_DWORD ;
    lpServiceTypeValues[2].dwValueSize = sizeof(DWORD) ;
    lpServiceTypeValues[2].lpValueName = SERVICE_TYPE_VALUE_TCPPORT ;
    lpServiceTypeValues[2].lpValue     = &TcpPortValue ;

    //
    // Finally, call SetService to actually perform the operation.
    //

    err = SetService(
              NS_DEFAULT,             // all default name spaces
              operation,              // either ADD or DELETE
              0,                      // dwFlags not used 
              &serviceInfo,           // the service info structure
              NULL,                   // lpServiceAsyncInfo
              &statusFlags            // additional status information
              );

    if ( err != NO_ERROR ) {
        printf( "SetService failed: %ld\n", GetLastError( ) );
        exit(1);
    }

    printf( "SetService succeeded, status flags = %ld\n", statusFlags );

    exit(0);

} // main
