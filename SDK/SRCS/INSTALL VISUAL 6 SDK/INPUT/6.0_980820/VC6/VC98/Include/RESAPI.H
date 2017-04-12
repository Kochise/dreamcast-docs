/*++

Copyright (c) 1995-1997  Microsoft Corporation

Module Name:

    resapi.h

Abstract:

    This module defines the interface exported by Windows Clusters resources.

Revision History:

--*/

#ifndef _RESAPI_DEFINES_
#define _RESAPI_DEFINES_

#ifdef __cplusplus
extern "C" {
#endif

#include "windows.h"
#include "clusapi.h"
#include "stdio.h"

#define IN
#define OUT

//
// Definitions for entrypoints exported by a resource DLL.
//
#define STARTUP_ROUTINE "Startup"

#define CLRES_V1_FUNCTION_SIZE   sizeof(CLRES_V1_FUNCTIONS)
#define CLRES_VERSION_V1_00    0x100

#define CLRES_V1_FUNCTION_TABLE( _Name,                     \
                                 _Version,                  \
                                 _Prefix,                   \
                                 _Arbitrate,                \
                                 _Release,                  \
                                 _ResControl,               \
                                 _ResTypeControl            \
                                 )                          \
CLRES_FUNCTION_TABLE _Name = { CLRES_V1_FUNCTION_SIZE,      \
                               _Version,                    \
                               _Prefix##Open,               \
                               _Prefix##Close,              \
                               _Prefix##Online,             \
                               _Prefix##Offline,            \
                               _Prefix##Terminate,          \
                               _Prefix##LooksAlive,         \
                               _Prefix##IsAlive,            \
                               _Arbitrate,                  \
                               _Release,                    \
                               _ResControl,                 \
                               _ResTypeControl }

#endif // ifndef _RESAPI_DEFINES_

#ifndef _RESAPI_
#define _RESAPI_

//
// Define a RESID
//

typedef PVOID RESID;

//
// Define a RESOURCE_HANDLE
//

typedef HANDLE   RESOURCE_HANDLE;

//
// Define the Resource Status structure.
//

typedef struct RESOURCE_STATUS {
    CLUSTER_RESOURCE_STATE  ResourceState;
    DWORD           CheckPoint;
    DWORD           WaitHint;
    HANDLE          EventHandle;
} RESOURCE_STATUS, *PRESOURCE_STATUS;


#define ResUtilInitializeResourceStatus( _resource_status_ ) \
    ZeroMemory( _resource_status_, sizeof(RESOURCE_STATUS) )

//
// Define Resource DLL callback method for updating the state of a resource.
//

typedef
VOID
(_stdcall *PSET_RESOURCE_STATUS_ROUTINE) (
    IN RESOURCE_HANDLE ResourceHandle,
    IN PRESOURCE_STATUS ResourceStatus
    );

//
// Define Resource DLL callback method for notifying that a quorum
// resource DLL failed to hold the quorum resource.
//
typedef
VOID
(_stdcall *PQUORUM_RESOURCE_LOST) (
    IN RESOURCE_HANDLE Resource
    );

//
// Define Resource DLL callback method for logging events.
//
typedef enum LOG_LEVEL {
    LOG_INFORMATION,
    LOG_WARNING,
    LOG_ERROR,
    LOG_SEVERE
} LOG_LEVEL, *PLOG_LEVEL;

typedef
VOID
(_stdcall *PLOG_EVENT_ROUTINE) (
    IN RESOURCE_HANDLE ResourceHandle,
    IN LOG_LEVEL LogLevel,
    IN LPCWSTR FormatString,
    ...
    );

typedef
RESID
(_stdcall *POPEN_ROUTINE) (
    IN LPCWSTR ResourceName,
    IN HKEY ResourceKey,
    IN RESOURCE_HANDLE ResourceHandle
    );

typedef
VOID
(_stdcall *PCLOSE_ROUTINE) (
    IN RESID Resource
    );

typedef
DWORD
(_stdcall *PONLINE_ROUTINE) (
    IN RESID Resource,
    IN OUT LPHANDLE EventHandle
    );

typedef
DWORD
(_stdcall *POFFLINE_ROUTINE) (
    IN RESID Resource
    );

typedef
VOID
(_stdcall *PTERMINATE_ROUTINE) (
    IN RESID Resource
    );

typedef
BOOL
(_stdcall *PIS_ALIVE_ROUTINE) (
    IN RESID Resource
    );

typedef
BOOL
(_stdcall *PLOOKS_ALIVE_ROUTINE) (
    IN RESID Resource
    );

typedef
DWORD
(_stdcall *PARBITRATE_ROUTINE) (
    IN RESID Resource,
    IN PQUORUM_RESOURCE_LOST LostQuorumResource
    );

typedef
DWORD
(_stdcall *PRELEASE_ROUTINE) (
    IN RESID Resource
    );

typedef
DWORD
(_stdcall *PRESOURCE_CONTROL_ROUTINE) (
    IN RESID Resource,
    IN DWORD ControlCode,
    IN PVOID InBuffer,
    IN DWORD InBufferSize,
    OUT PVOID OutBuffer,
    IN DWORD OutBufferSize,
    OUT LPDWORD BytesReturned
    );

typedef
DWORD
(_stdcall *PRESOURCE_TYPE_CONTROL_ROUTINE) (
    IN LPCWSTR ResourceTypeName,
    IN DWORD ControlCode,
    IN PVOID InBuffer,
    IN DWORD InBufferSize,
    OUT PVOID OutBuffer,
    IN DWORD OutBufferSize,
    OUT LPDWORD BytesReturned
    );


//***************************************************************
//
// Define the Function Table Format
//
//***************************************************************

//
// Version 1 Resource DLL Interface definition
//
typedef struct CLRES_V1_FUNCTIONS {
    POPEN_ROUTINE Open;
    PCLOSE_ROUTINE Close;
    PONLINE_ROUTINE Online;
    POFFLINE_ROUTINE Offline;
    PTERMINATE_ROUTINE Terminate;
    PLOOKS_ALIVE_ROUTINE LooksAlive;
    PIS_ALIVE_ROUTINE IsAlive;
    PARBITRATE_ROUTINE Arbitrate;
    PRELEASE_ROUTINE Release;
    PRESOURCE_CONTROL_ROUTINE ResourceControl;
    PRESOURCE_TYPE_CONTROL_ROUTINE ResourceTypeControl;
} CLRES_V1_FUNCTIONS, *PCLRES_V1_FUNCTIONS;

//
// Resource DLL Function Table definition
//
#pragma warning( disable : 4201 ) // nonstandard extension used : nameless struct/union
typedef struct CLRES_FUNCTION_TABLE {
    DWORD   TableSize;
    DWORD   Version;
    union {
        CLRES_V1_FUNCTIONS V1Functions;
    };
} CLRES_FUNCTION_TABLE, *PCLRES_FUNCTION_TABLE;
#pragma warning( default : 4201 ) // nonstandard extension used : nameless struct/union

//
// Define the Resource DLL Startup routine. This is the only routine
// that should be exported from a resource DLL.
//

//
// Calculate the byte offset of a field in a structure of type type.
//

#ifndef FIELD_OFFSET
#define FIELD_OFFSET(type, field)    ((LONG)&(((type *)0)->field))
#endif

//
// Property list structures and functions
//
typedef struct RESUTIL_PROPERTY_ITEM {
    LPWSTR  Name;               // Property name
    LPWSTR  KeyName;            // Name of value in cluster database
    DWORD   Format;             // Format: REG_SZ, REG_DWORD, etc.
    DWORD   Default;            // Default value
    DWORD   Minimum;            // Minimum value
    DWORD   Maximum;            // Maximum value
    DWORD   Flags;              // Flags for this item
#define RESUTIL_PROPITEM_READ_ONLY  0x00000001  // Property is read-only
#define RESUTIL_PROPITEM_REQUIRED   0x00000002  // Property is required
#define RESUTIL_PROPITEM_SIGNED     0x00000004  // Numeric property is signed (defaults to unsigned)

    DWORD   Offset;             // Byte offset to value in parameter block
                                //   Assumes MULTI_SZ and BINARY parameters
                                //   are LPWSTRs followed by DWORDs for length
} RESUTIL_PROPERTY_ITEM, *PRESUTIL_PROPERTY_ITEM;


typedef
DWORD
(_stdcall *PSTARTUP_ROUTINE) (
    IN LPCWSTR ResourceType,
    IN DWORD MinVersionSupported,
    IN DWORD MaxVersionSupported,
    IN PSET_RESOURCE_STATUS_ROUTINE SetResourceStatus,
    IN PLOG_EVENT_ROUTINE LogEvent,
    OUT PCLRES_FUNCTION_TABLE *FunctionTable
    );

//
// Define layout of shared memory used for tracking Resource Monitor state.
//
typedef enum RESOURCE_MONITOR_STATE {
    RmonInitializing,
    RmonIdle,
    RmonStartingResource,
    RmonInitializingResource,
    RmonOnlineResource,
    RmonOfflineResource,
    RmonShutdownResource,
    RmonDeletingResource,
    RmonIsAlivePoll,
    RmonLooksAlivePoll,
    RmonArbitrateResource,
    RmonReleaseResource,
    RmonResourceControl,
    RmonResourceTypeControl
} RESOURCE_MONITOR_STATE;

typedef struct MONITOR_STATE {
    LARGE_INTEGER LastUpdate;
    RESOURCE_MONITOR_STATE State;
    HANDLE ActiveResource;
    BOOL   ResmonStop;
} MONITOR_STATE, *PMONITOR_STATE;


//
// Resource Utility Routines
//

DWORD
WINAPI
ResUtilStartResourceService(
    IN LPCTSTR ServiceName,
    OUT LPHANDLE ServiceHandle
    );

DWORD
WINAPI
ResUtilVerifyResourceService(
    IN LPCTSTR ServiceName
    );

DWORD
WINAPI
ResUtilStopResourceService(
    IN LPCTSTR ServiceName
    );

DWORD
WINAPI
ResUtilVerifyService(
    IN HANDLE ServiceHandle
    );

DWORD
WINAPI
ResUtilStopService(
    IN HANDLE ServiceHandle
    );

BOOL
WINAPI
ResUtilIsPathValid(
    IN LPCWSTR Path
    );

DWORD
WINAPI
ResUtilEnumProperties(
    IN const PRESUTIL_PROPERTY_ITEM PropertyTable,
    OUT LPWSTR OutBuffer,
    IN DWORD OutBufferSize,
    OUT LPDWORD BytesReturned,
    OUT LPDWORD Required
    );

DWORD
WINAPI
ResUtilEnumPrivateProperties(
    IN PVOID ClusterKey,
    OUT LPWSTR OutBuffer,
    IN DWORD OutBufferSize,
    OUT LPDWORD BytesReturned,
    OUT LPDWORD Required
    );

DWORD
WINAPI
ResUtilGetProperties(
    IN PVOID ClusterKey,
    IN const PRESUTIL_PROPERTY_ITEM PropertyTable,
    OUT PVOID OutBuffer,
    IN DWORD OutBufferSize,
    OUT LPDWORD BytesReturned,
    OUT LPDWORD Required
    );

DWORD
WINAPI
ResUtilGetAllProperties(
    IN PVOID ClusterKey,
    IN const PRESUTIL_PROPERTY_ITEM PropertyTable,
    OUT PVOID OutBuffer,
    IN DWORD OutBufferSize,
    OUT LPDWORD BytesReturned,
    OUT LPDWORD Required
    );

DWORD
WINAPI
ResUtilGetPrivateProperties(
    IN PVOID ClusterKey,
    OUT PVOID OutBuffer,
    IN DWORD OutBufferSize,
    OUT LPDWORD BytesReturned,
    OUT LPDWORD Required
    );

DWORD
WINAPI
ResUtilGetPropertySize(
    IN PVOID ClusterKey,
    IN const PRESUTIL_PROPERTY_ITEM Property,
    IN OUT LPDWORD BufferSize,
    IN OUT LPDWORD ItemCount
    );

DWORD
WINAPI
ResUtilGetProperty(
    IN PVOID ClusterKey,
    IN const PRESUTIL_PROPERTY_ITEM Property,
    OUT PVOID * OutBuffer,
    IN OUT LPDWORD OutBufferSize
    );

DWORD
WINAPI
ResUtilVerifyPropertyTable(
    IN const PRESUTIL_PROPERTY_ITEM PropertyTable,
    IN PVOID Reserved,
    IN BOOL AllowUnknownProperties,
    IN const PVOID InBuffer,
    IN DWORD InBufferSize,
    OUT OPTIONAL LPBYTE OutParams
    );

DWORD
WINAPI
ResUtilSetPropertyTable(
    IN PVOID ClusterKey,
    IN const PRESUTIL_PROPERTY_ITEM PropertyTable,
    IN PVOID Reserved,
    IN BOOL AllowUnknownProperties,
    IN const PVOID InBuffer,
    IN DWORD InBufferSize,
    OUT OPTIONAL LPBYTE OutParams
    );

DWORD
WINAPI
ResUtilSetPropertyParameterBlock(
    IN PVOID ClusterKey,
    IN const PRESUTIL_PROPERTY_ITEM PropertyTable,
    IN PVOID Reserved,
    IN const LPBYTE InParams,
    IN const PVOID InBuffer,
    IN DWORD InBufferSize,
    OUT OPTIONAL LPBYTE OutParams
    );

DWORD
WINAPI
ResUtilGetPropertiesToParameterBlock(
    IN PVOID ClusterKey,
    IN const PRESUTIL_PROPERTY_ITEM PropertyTable,
    OUT LPBYTE OutParams,
    IN BOOL CheckForRequiredProperties,
    OUT OPTIONAL LPWSTR * NameOfPropInError
    );

DWORD
WINAPI
ResUtilPropertyListFromParameterBlock(
    IN const PRESUTIL_PROPERTY_ITEM PropertyTable,
    OUT PVOID * OutBuffer,
    IN OUT LPDWORD OutBufferSize,
    IN const LPBYTE InParams,
    OUT LPDWORD BytesReturned,
    OUT LPDWORD Required
    );

DWORD
WINAPI
ResUtilDupParameterBlock(
    OUT LPBYTE OutParams,
    IN const LPBYTE InParams,
    IN const PRESUTIL_PROPERTY_ITEM PropertyTable
    );

void
WINAPI
ResUtilFreeParameterBlock(
    IN OUT LPBYTE OutParams,
    IN const LPBYTE InParams,
    IN const PRESUTIL_PROPERTY_ITEM PropertyTable
    );

DWORD
WINAPI
ResUtilAddUnknownProperties(
    IN PVOID ClusterKey,
    IN const PRESUTIL_PROPERTY_ITEM PropertyTable,
    IN OUT PVOID OutBuffer,
    IN DWORD OutBufferSize,
    IN OUT LPDWORD BytesReturned,
    IN OUT LPDWORD Required
    );

DWORD
WINAPI
ResUtilSetPrivatePropertyList(
    IN PVOID ClusterKey,
    IN const PVOID InBuffer,
    IN DWORD InBufferSize
    );

DWORD
WINAPI
ResUtilVerifyPrivatePropertyList(
    IN const PVOID InBuffer,
    IN DWORD InBufferSize
    );

DWORD
WINAPI
ResUtilGetBinaryValue(
    IN HKEY ClusterKey,
    IN LPCWSTR ValueName,
    OUT LPBYTE * OutValue,
    OUT DWORD * OutValueSize
    );

PWSTR
WINAPI
ResUtilDupString(
    IN LPCWSTR Value
    );

LPWSTR
WINAPI
ResUtilGetSzValue(
    IN HKEY ClusterKey,
    IN LPCWSTR ValueName
    );

#define ResUtilGetMultiSzValue( ClusterKey, ValueName, OutValue, OutValueSize ) \
    ResUtilGetBinaryValue( ClusterKey, ValueName, (LPBYTE *) OutValue, OutValueSize )

DWORD
WINAPI
ResUtilGetDwordValue(
    IN HKEY ClusterKey,
    IN LPCWSTR ValueName,
    OUT LPDWORD OutValue,
    IN DWORD DefaultValue OPTIONAL
    );

DWORD
WINAPI
ResUtilSetBinaryVakye(
    IN HKEY ClusterKey,
    IN LPCWSTR ValueName,
    IN const LPBYTE NewValue,
    IN DWORD NewValueSize,
    IN OUT LPBYTE * OutValue,
    IN OUT LPDWORD OutValueSize
    );

DWORD
WINAPI
ResUtilSetSzValue(
    IN HKEY ClusterKey,
    IN LPCWSTR ValueName,
    IN LPCWSTR NewValue,
    IN OUT LPWSTR * OutString
    );

DWORD
WINAPI
ResUtilSetExpandSzValue(
    IN HKEY ClusterKey,
    IN LPCWSTR ValueName,
    IN LPCWSTR NewValue,
    IN OUT LPWSTR * OutString
    );

DWORD
WINAPI
ResUtilSetMultiSzValue(
    IN HKEY ClusterKey,
    IN LPCWSTR ValueName,
    IN LPCWSTR NewValue,
    IN DWORD NewValueSize,
    IN OUT LPWSTR * OutValue,
    IN OUT LPDWORD OutValueSize
    );

DWORD
WINAPI
ResUtilSetDwordValue(
    IN HKEY ClusterKey,
    IN LPCWSTR ValueName,
    IN DWORD NewValue,
    IN OUT LPDWORD OutValue
    );

DWORD
WINAPI
ResUtilGetBinaryProperty(
    OUT LPBYTE * OutValue,
    OUT LPDWORD OutValueSize,
    IN const PCLUSPROP_BINARY ValueStruct,
    IN const LPBYTE OldValue,
    IN DWORD OldValueSize,
    OUT LPBYTE * PropBuffer,
    OUT LPDWORD PropBufferSize
    );

DWORD
WINAPI
ResUtilGetSzProperty(
    OUT LPWSTR * OutValue,
    IN const PCLUSPROP_SZ ValueStruct,
    IN LPCWSTR OldValue,
    OUT LPBYTE * PropBuffer,
    OUT LPDWORD PropBufferSize
    );

DWORD
WINAPI
ResUtilGetMultiSzProperty(
    OUT LPWSTR * OutValue,
    OUT LPDWORD OutValueSize,
    IN const PCLUSPROP_SZ ValueStruct,
    IN LPCWSTR OldValue,
    IN DWORD OldValueSize,
    OUT LPBYTE * PropBuffer,
    OUT LPDWORD PropBufferSize
    );

DWORD
WINAPI
ResUtilGetDwordProperty(
    OUT LPDWORD OutValue,
    IN const PCLUSPROP_DWORD ValueStruct,
    IN DWORD OldValue,
    IN DWORD Minimum,
    IN DWORD Maximum,
    OUT LPBYTE * PropBuffer,
    OUT LPDWORD PropBufferSize
    );

LPVOID
WINAPI
ResUtilGetEnvironmentWithNetName(
    IN HRESOURCE hResource
    );

DWORD
WINAPI
ResUtilFindSzProperty(
    IN const PVOID Buffer,
    IN DWORD BufferSize,
    IN LPCWSTR PropName,
    OUT LPWSTR * FoundString
    );

DWORD
WINAPI
ResUtilFindDwordProperty(
    IN const PVOID Buffer,
    IN DWORD BufferSize,
    IN LPCWSTR PropName,
    OUT LPDWORD FoundDword
    );

//
// Common worker thread routines that allow a pending operation to
// be cancelled with CORRECT synchronization.
//
typedef struct CLUS_WORKER {
    HANDLE hThread;
    BOOL Terminate;
} CLUS_WORKER, *PCLUS_WORKER;

typedef DWORD (WINAPI *PWORKER_START_ROUTINE)(
    PCLUS_WORKER pWorker,
    LPVOID lpThreadParameter
    );

DWORD
WINAPI
ClusWorkerCreate(
    OUT PCLUS_WORKER Worker,
    IN PWORKER_START_ROUTINE lpStartAddress,
    IN PVOID lpParameter
    );

BOOL
WINAPI
ClusWorkerCheckTerminate(
    IN PCLUS_WORKER Worker
    );

VOID
WINAPI
ClusWorkerTerminate(
    IN PCLUS_WORKER Worker
    );


//Define enumerate resource callback function. This gets called for each resource enumerated
//by ResUtilEnumResources
typedef   DWORD (*LPRESOURCE_CALLBACK)( HRESOURCE, HRESOURCE , PVOID );


BOOL
WINAPI
ResUtilResourcesEqual(
    IN HRESOURCE    hSelf,
    IN HRESOURCE    hResource
    );


BOOL
WINAPI
ResUtilResourceTypesEqual(
    IN LPCWSTR      lpszResourceTypeName,
    IN HRESOURCE    hResource
    );

DWORD
WINAPI
ResUtilEnumResources(
    IN HRESOURCE            hSelf,
    IN LPCWSTR              lpszResTypeName,
    IN LPRESOURCE_CALLBACK  pResCallBack,
    IN PVOID                pParameter
    );

HRESOURCE
WINAPI
ResUtilGetResourceDependency(
    IN HANDLE       hSelf,
    IN LPCWSTR      lpszResourceType
    );

HRESOURCE
WINAPI
ResUtilGetResourceNameDependency(
    IN LPCWSTR      lpszResourceName,
    IN LPCWSTR      lpszResourceType
    );


#ifdef __cplusplus
}
#endif


#endif // ifdef _RESAPI_DEFINES_
