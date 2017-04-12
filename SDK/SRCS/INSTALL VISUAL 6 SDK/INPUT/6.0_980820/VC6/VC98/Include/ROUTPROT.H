/*++

Copyright (c) 1995 - 1997 Microsoft Corporation

Module Name:

    routprot.h

Abstract:
    Include file for Routing Protocol inteface to Router Managers

--*/

#ifndef __ROUTING_ROUTPROT_H__
#define __ROUTING_ROUTPROT_H__

#include "stm.h"

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Supported functionality flags                                            //
//                                                                          //
// ROUTING 		            Imports Routing Table Manager APIs              //
// SERVICES		            Exports Service Table Manager APIs              //
// DEMAND_UPDATE_ROUTES     IP and IPX RIP support for Autostatic           //
// DEMAND_UPDATE_SERVICES   IPX SAP, NLSP support for Autostatic            //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

#define ROUTING 		        0x00000001
#define DEMAND_UPDATE_ROUTES    0x00000004

#if MPR40
#define MS_ROUTER_VERSION       0x00000400
#else
    #if MPR50
    #define MS_ROUTER_VERSION       0x00000500
    #else
    #error Router version not defined
    #endif
#endif

typedef enum _ROUTING_PROTOCOL_EVENTS
{
    ROUTER_STOPPED,              // Result is empty
    SAVE_GLOBAL_CONFIG_INFO,     // Result is empty
    SAVE_INTERFACE_CONFIG_INFO,  // Result is interface index
                                 // for which config info is to be saved.
    UPDATE_COMPLETE,             // Result is UPDATE_COMPLETE_MESSAGE structure
}ROUTING_PROTOCOL_EVENTS;


typedef enum _NET_INTERFACE_TYPE
{
    PERMANENT,                   // Permanent connectivity
                                 // (LAN, Frame Relay, etc.)
    DEMAND_DIAL,                 // Demand Dial connectivity
                                 // (analog, ISDN, switched FR)
    LOCAL_WORKSTATION_DIAL,	     // Local Workstation connectivity only
    REMOTE_WORKSTATION_DIAL      // Remote Workstation connectivity
} NET_INTERFACE_TYPE;

typedef struct _SUPPORT_FUNCTIONS
{
    //
    // Function called by routing protocol to initiate demand dial connection
    //

    OUT DWORD
    (WINAPI *DemandDialRequest)(
        IN      DWORD           ProtocolId,
        IN      DWORD           InterfaceIndex
        ) ;

    //
    // The following entrypoints are provided as a way for getting 
    // information that spans components
    //

    OUT DWORD
    (WINAPI *MIBEntryCreate)(
        IN      DWORD           dwRoutingPid,
        IN      DWORD           dwEntrySize,
        IN      LPVOID          lpEntry 
        );

    OUT DWORD
    (WINAPI *MIBEntryDelete)(
        IN      DWORD           dwRoutingPid,
        IN      DWORD           dwEntrySize,
        IN      LPVOID          lpEntry 
        );

    OUT DWORD
    (WINAPI *MIBEntrySet)(
        IN      DWORD           dwRoutingPid,
        IN      DWORD           dwEntrySize,
        IN      LPVOID          lpEntry 
        );

    OUT DWORD
    (WINAPI *MIBEntryGet)(
        IN      DWORD           dwRoutingPid,
        IN      DWORD           dwInEntrySize,
        IN      LPVOID          lpInEntry,
        IN OUT  LPDWORD         lpOutEntrySize,
        OUT     LPVOID          lpOutEntry );

    OUT DWORD
    (WINAPI *MIBEntryGetFirst)(
        IN      DWORD           dwRoutingPid,
        IN      DWORD           dwInEntrySize,
        IN      LPVOID          lpInEntry,
        IN OUT  LPDWORD         lpOutEntrySize,
        OUT     LPVOID          lpOutEntry 
        );

    OUT DWORD
    (WINAPI *MIBEntryGetNext)(
        IN      DWORD           dwRoutingPid,
        IN      DWORD           dwInEntrySize,
        IN      LPVOID          lpInEntry,
        IN OUT  LPDWORD         lpOutEntrySize,
        OUT     LPVOID          lpOutEntry 
        );

} SUPPORT_FUNCTIONS, *PSUPPORT_FUNCTIONS ;


//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// All IP Protocols must use the protocol ids defined in the range below.   //
// Protocols not identified below can use any unassigned number BELOW       //
// 0xffff0000                                                               //
//                                                                          //
// NOTE: These numbers have been chosen to coincide with MIB-II protocol    //
// numbers. Allocation should not be arbitrary.                             //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

#define IP_OTHER		1
#define IP_LOCAL		2
#define IP_NETMGMT		3
#define IP_ICMP			4
#define IP_EGP			5
#define IP_GGP			6
#define IP_HELLO		7
#define IP_RIP			8
#define IP_IS_IS		9
#define IP_ES_IS		10
#define IP_CISCO		11
#define IP_BBN			12
#define IP_OSPF			13
#define IP_BGP			14

//
// The IPRTRMGR_PID is 10000
//

#define IP_BOOTP            9999
#define IP_NT_AUTOSTATIC    10002

//
// For all future development, the following macro must be used to generate
// Ids
//

//
//  Type            -   4 bits,
//  VendorMajor     -   4 bits,
//  VendorMinor     -   8 bits,
//  ProtocolId      -   8 bits
//

#define PROTOCOL_ID(Type, VendorMajor, VendorMinor, Id) \
    (((Type)<<28)|((VendorMajor)<<24)|((VendorMinor)<<16)|(Id))

//
//  |----|----|----|----|----|----|----|----|
//   Type VenMj VenMn    0000 0000 ProtocolId
//



#define PROTO_TYPE_UNICAST          0
#define PROTO_TYPE_MCAST            1

#define PROTO_VENDOR_MJ_IETF        0
#define PROTO_VENDOR_MN_IETF        0
#define PROTO_VENDOR_MJ_MS          15  // 0xF


//
// All IPX Protocols must use the protocol ids defined in the range below.
// Protocols not identified below can use any unassigned number greater than
// IPX_PROTOCOL_BASE.
//

#define IPX_PROTOCOL_BASE   0x0001ffff
#define IPX_PROTOCOL_RIP    IPX_PROTOCOL_BASE + 1
#define IPX_PROTOCOL_SAP    IPX_PROTOCOL_BASE + 2
#define IPX_PROTOCOL_NLSP   IPX_PROTOCOL_BASE + 3

typedef struct _UPDATE_COMPLETE_MESSAGE
{
    ULONG	InterfaceIndex;
    ULONG	UpdateType;	       // DEMAND_UPDATE_ROUTES, DEMAND_UPDATE_SERVICES
    ULONG	UpdateStatus;	   // NO_ERROR if successfull

}   UPDATE_COMPLETE_MESSAGE, *PUPDATE_COMPLETE_MESSAGE;

//
//  Message returned in Result parameter to GET_EVENT_MESSAGE api call.
//  UpdateCompleteMessage   returned for UPDATE_COMPLETE message
//  InterfaceIndex          returned for SAVE_INTERFACE_CONFIG_INFO message
//

typedef union _MESSAGE
{
    UPDATE_COMPLETE_MESSAGE UpdateCompleteMessage;
    DWORD                   InterfaceIndex;

}   MESSAGE, *PMESSAGE;

//
//     IPX Adapter Binding Info - Used in ActivateInterface
//

typedef struct	IPX_ADAPTER_BINDING_INFO
{
    ULONG	AdapterIndex;
    UCHAR	Network[4];
    UCHAR	LocalNode[6];
    UCHAR	RemoteNode[6];
    ULONG	MaxPacketSize;
    ULONG	LinkSpeed;

}IPX_ADAPTER_BINDING_INFO, *PIPX_ADAPTER_BINDING_INFO;

//
//     IP Adapter Binding Info
//

typedef struct IP_LOCAL_BINDING
{
    DWORD   IPAddress;
    DWORD   Mask;
}IP_LOCAL_BINDING, *PIP_LOCAL_BINDING;

typedef struct	IP_ADAPTER_BINDING_INFO
{
    DWORD               NumAddresses;
    DWORD               RemoteAddress;
    IP_LOCAL_BINDING    Address[1];
}IP_ADAPTER_BINDING_INFO, *PIP_ADAPTER_BINDING_INFO;

#define SIZEOF_IP_BINDING(X)                                \
    (FIELD_OFFSET(IP_ADAPTER_BINDING_INFO,Address[0]) +     \
     ((X) * sizeof(IP_LOCAL_BINDING)))


//
//  Protocol Start/Stop Entry Points
//


typedef
DWORD
(WINAPI * PSTART_PROTOCOL) (
    IN HANDLE 	            NotificationEvent,
    IN PSUPPORT_FUNCTIONS   SupportFunctions,
    IN LPVOID               GlobalInfo
    );

typedef
DWORD
(WINAPI * PSTOP_PROTOCOL) (
    VOID
    );

typedef
DWORD
(WINAPI * PADD_INTERFACE) (
    IN LPWSTR               InterfaceName,
    IN ULONG	            InterfaceIndex,
    IN NET_INTERFACE_TYPE   InterfaceType,
    IN PVOID	            InterfaceInfo
    );

typedef
DWORD
(WINAPI * PDELETE_INTERFACE) (
    IN ULONG	InterfaceIndex
    );

typedef
DWORD
(WINAPI * PGET_EVENT_MESSAGE) (
    OUT ROUTING_PROTOCOL_EVENTS  *Event,
    OUT MESSAGE                  *Result
    );

typedef
DWORD
(WINAPI * PGET_INTERFACE_INFO) (
    IN      ULONG	InterfaceIndex,
    IN      PVOID   InterfaceInfo,
    IN OUT PULONG	InterfaceInfoSize
    );

typedef
DWORD
(WINAPI * PSET_INTERFACE_INFO) (
    IN ULONG	InterfaceIndex,
    IN PVOID	InterfaceInfo
    );

typedef
DWORD
(WINAPI * PBIND_INTERFACE) (
    IN ULONG	InterfaceIndex,
    IN PVOID	BindingInfo
    ) ;

typedef
DWORD
(WINAPI * PUNBIND_INTERFACE) (
    IN ULONG	InterfaceIndex
    );

typedef
DWORD
(WINAPI * PENABLE_INTERFACE) (
    IN ULONG	InterfaceIndex
    ) ;

typedef
DWORD
(WINAPI * PDISABLE_INTERFACE) (
    IN ULONG	InterfaceIndex
    );

typedef
DWORD
(WINAPI * PGET_GLOBAL_INFO) (
    IN     PVOID 	GlobalInfo,
    IN OUT PULONG   GlobalInfoSize
    );

typedef
DWORD
(WINAPI * PSET_GLOBAL_INFO) (
    IN PVOID 	GlobalInfo
    );

typedef
DWORD
(WINAPI * PDO_UPDATE_ROUTES) (
    IN ULONG	InterfaceIndex
    );

typedef
DWORD
(WINAPI * PMIB_CREATE) (
    IN ULONG 	InputDataSize,
    IN PVOID 	InputData
    );

typedef
DWORD
(WINAPI * PMIB_DELETE) (
    IN ULONG 	InputDataSize,
    IN PVOID 	InputData
    );

typedef
DWORD
(WINAPI * PMIB_GET) (
    IN  ULONG	InputDataSize,
    IN  PVOID	InputData,
    OUT PULONG	OutputDataSize,
    OUT PVOID	OutputData
    );

typedef
DWORD
(WINAPI * PMIB_SET) (
    IN ULONG 	InputDataSize,
    IN PVOID	InputData
    );

typedef
DWORD
(WINAPI * PMIB_GET_FIRST) (
    IN  ULONG	InputDataSize,
    IN  PVOID	InputData,
    OUT PULONG  OutputDataSize,
    OUT PVOID   OutputData
    );

typedef
DWORD
(WINAPI * PMIB_GET_NEXT) (
    IN  ULONG   InputDataSize,
    IN  PVOID	InputData,
    OUT PULONG  OutputDataSize,
    OUT PVOID	OutputData
    );

typedef
DWORD
(WINAPI * PMIB_SET_TRAP_INFO) (
    IN  HANDLE  Event,
    IN  ULONG   InputDataSize,
    IN  PVOID	InputData,
    OUT PULONG	OutputDataSize,
    OUT PVOID	OutputData
    );

typedef
DWORD
(WINAPI * PMIB_GET_TRAP_INFO) (
    IN  ULONG	InputDataSize,
    IN  PVOID	InputData,
    OUT PULONG  OutputDataSize,
    OUT PVOID	OutputData
    );


//
// This is the structure passed between the router manager
// and a registering protocol.
//
// IN OUT DWORD dwVersion
// This is filled by the router manager to indicate the version it supports.
// The DLL MUST set this to the version that the protocol will support.
//
// IN DWORD dwProtocolId
// This the protocol the router manager is expecting the DLL to register.
// If the DLL does not support this protocol, it must return
// ERROR_NOT_SUPPORTED
// A DLL will be called once for every protocol it supports
//
// IN OUT DWORD fSupportedFunctionality
// These are the flags denoting the functionality the router manager
// supports. The DLL must reset this to the functionality that it
// supports
//


typedef struct _MPR40_ROUTING_CHARACTERISTICS
{
    DWORD               dwVersion;
    DWORD               dwProtocolId;
    DWORD               fSupportedFunctionality;
    PSTART_PROTOCOL     pfnStartProtocol;
    PSTOP_PROTOCOL      pfnStopProtocol;
    PADD_INTERFACE      pfnAddInterface;
    PDELETE_INTERFACE   pfnDeleteInterface;
    PGET_EVENT_MESSAGE  pfnGetEventMessage;
    PGET_INTERFACE_INFO pfnGetInterfaceInfo;
    PSET_INTERFACE_INFO pfnSetInterfaceInfo;
    PBIND_INTERFACE     pfnBindInterface;
    PUNBIND_INTERFACE   pfnUnbindInterface;
    PENABLE_INTERFACE   pfnEnableInterface;
    PDISABLE_INTERFACE  pfnDisableInterface;
    PGET_GLOBAL_INFO    pfnGetGlobalInfo;
    PSET_GLOBAL_INFO    pfnSetGlobalInfo;
    PDO_UPDATE_ROUTES   pfnUpdateRoutes;
    PMIB_CREATE         pfnMibCreateEntry;
    PMIB_DELETE         pfnMibDeleteEntry;
    PMIB_GET            pfnMibGetEntry;
    PMIB_SET            pfnMibSetEntry;
    PMIB_GET_FIRST      pfnMibGetFirstEntry;
    PMIB_GET_NEXT       pfnMibGetNextEntry;
    PMIB_SET_TRAP_INFO  pfnMibSetTrapInfo;
    PMIB_GET_TRAP_INFO  pfnMibGetTrapInfo;
}MPR40_ROUTING_CHARACTERISTICS;

typedef struct _MPR50_ROUTING_CHARACTERISTICS
{

#ifdef __cplusplus
    MPR40_ROUTING_CHARACTERISTICS   mrcMpr40Chars;
#else
    MPR40_ROUTING_CHARACTERISTICS;
#endif

}MPR50_ROUTING_CHARACTERISTICS;

#if MPR50
typedef MPR50_ROUTING_CHARACTERISTICS MPR_ROUTING_CHARACTERISTICS;
#else
    #if MPR40
    typedef MPR40_ROUTING_CHARACTERISTICS MPR_ROUTING_CHARACTERISTICS;
    #endif
#endif

typedef MPR_ROUTING_CHARACTERISTICS *PMPR_ROUTING_CHARACTERISTICS;


//
// All routing protocols must export the following entry point.
// The router manager calls this function to allow the routing
// protocol to register
//

#define REGISTER_PROTOCOL_ENTRY_POINT           RegisterProtocol
#define REGISTER_PROTOCOL_ENTRY_POINT_STRING    "RegisterProtocol"

typedef 
DWORD
(WINAPI * PREGISTER_PROTOCOL) (
    IN OUT PMPR_ROUTING_CHARACTERISTICS pRoutingChar,
    IN OUT PMPR_SERVICE_CHARACTERISTICS pServiceChar
    );


#ifdef __cplusplus
}
#endif

#endif //__ROUTING_ROUTPROT_H__
