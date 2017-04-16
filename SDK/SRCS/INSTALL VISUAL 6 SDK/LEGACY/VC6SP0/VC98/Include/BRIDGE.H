// Copyright (C) 1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   bridge.h
//
//  PURPOSE:  DLL output service functions for MSBDN Bridge
//
//  FUNCTIONS DEFINED BY BRIDGE.DLL:
// msbdnPacketLength        - length of a packet
// msbdnPacketMemcpy        - copies data from a packet
// msbdnPacketGetData       - returns pointer to raw packet data
//
//  FUNCTIONS DEFINED BY LOADABLE OUTPUT DLL:
// msbdnOutputStartup       - called once during initialization
// msbdnOutputSetState      - enable/disable output
// msbdnOutputShutdown      - called once during shutdown
// msbdnOutputSetHWAddr     - override for network MAC address
// msbdnOutputSetBandwidth  - set self throttling rate
// msbdnOutputSetRoutingInfo - set routing information
// msbdnOutputStreamStatus  - called when "streams" start and stop
// msbdnOutputSendPacket    - called to send data
// 
//  COMMENTS:
// 

#ifndef BRIDGE_H
#define BRIDGE_H

#include "packet.h"

#ifndef	EXTERN_C
#ifdef	__cplusplus
#define	EXTERN_C	extern "C"
#else
#define	EXTERN_C
#endif
#endif

#define	MSBDN_BRIDGE_CALLBACKS_VERSION	0x00020000U

typedef DWORD MSBDN_SUBSYSTEM_ID;

struct MSBDN_OUTPUT_SUBSYSTEM;

typedef struct MSBDN_BRIDGE_CALLBACKS {
	DWORD	Version;
	HRESULT	(*ReportState)		(struct MSBDN_OUTPUT_SUBSYSTEM *, DWORD state, LPCSTR message);
	HRESULT	(*ReportActivity)	(struct MSBDN_OUTPUT_SUBSYSTEM *, WORD type, DWORD amount);
	HRESULT	(*ReportEvent)		(struct MSBDN_OUTPUT_SUBSYSTEM *, WORD, DWORD, LPCWSTR);
} MSBDN_BRIDGE_CALLBACKS;

// this is analogous to the kernel's DEVICE_OBJECT, kind of.
typedef struct MSBDN_OUTPUT_SUBSYSTEM {
	DWORD						Version;
	MSBDN_BRIDGE_CALLBACKS		BridgeCallbacks;
	MSBDN_SUBSYSTEM_ID			OutputSubsystemID;
	HKEY						RegistryKey;
	LPVOID						DriverContext;
} MSBDN_OUTPUT_SUBSYSTEM;

#define	MSBDN_OUTPUT_SUBSYSTEM_VERSION_1	1
#define	MSBDN_OUTPUT_SUBSYSTEM_VERSION		MSBDN_OUTPUT_SUBSYSTEM_VERSION_1

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


#ifndef MSBDNOUTPUTAPI
#define MSBDNOUTPUTAPI __declspec (dllexport)
#endif

#ifndef MSBDNBRIDGEAPI
#define MSBDNBRIDGEAPI __declspec (dllimport)
#endif

// for backward combustibility, i mean compatability
typedef PACKET_BUFFER * HPACKET;


// this is the second parameter in msbdnBridgeReportState
#define MSBDN_OUTPUT_DISABLED   0
#define MSBDN_OUTPUT_ENABLED    1
#define MSBDN_OUTPUT_FORCED     2
#define MSBDN_OUTPUT_WARNING    10

// this is the first parameer in msbdnBridgeReportActivity
#define MSBDN_REPORT_RATE       100
#define MSBDN_REPORT_OUTPUT     101
#define MSBDN_REPORT_ERROR      102
#define MSBDN_REPORT_TIMEOUT    103     // dwOutputTimeouts
#define MSBDN_REPORT_FULLFIFO   104     // dwOutputFullFifo

#define	MSBDN_OUTPUT_API_VERSION	0x00020000

#define	MSBDN_OUTPUT_VALUE_STRING		0
#define	MSBDN_OUTPUT_VALUE_DWORD		1
#define	MSBDN_OUTPUT_VALUE_IPADDRESS	2
#define	MSBDN_OUTPUT_VALUE_BOOLEAN		3

typedef struct MSBDN_OUTPUT_VALUE {
	DWORD	Index;
	DWORD	Type;
	LPWSTR	Name;
	union {
		DWORD	Dword;
		LPWSTR	String;
		IN_ADDR	IPAddress;
		BOOL	Boolean;
	};
} MSBDN_OUTPUT_VALUE;

typedef	HRESULT	(*PMSBDNOUTPUTCREATE)			(MSBDN_OUTPUT_SUBSYSTEM *, DWORD);
typedef	HRESULT	(*PMSBDNOUTPUTDESTROY)			(MSBDN_OUTPUT_SUBSYSTEM *);
typedef	HRESULT	(*PMSBDNOUTPUTSETHWADDR)		(MSBDN_OUTPUT_SUBSYSTEM *, LPBYTE, LPBYTE, LPWORD);
typedef	HRESULT	(*PMSBDNOUTPUTSETBANDWIDTH)		(MSBDN_OUTPUT_SUBSYSTEM *, DWORD);
typedef	HRESULT	(*PMSBDNOUTPUTSETROUTINGINFO)	(MSBDN_OUTPUT_SUBSYSTEM *, LPVOID);
typedef	HRESULT	(*PMSBDNOUTPUTSTREAMSTATUS)		(MSBDN_OUTPUT_SUBSYSTEM *, WORD, LPBYTE, BOOL);
typedef	HRESULT	(*PMSBDNOUTPUTSENDPACKET)		(MSBDN_OUTPUT_SUBSYSTEM *, PACKET_BUFFER *);
typedef	HRESULT	(*PMSBDNOUTPUTSETVALUE)			(MSBDN_OUTPUT_SUBSYSTEM *, MSBDN_OUTPUT_VALUE *);
typedef	HRESULT	(*PMSBDNOUTPUTGETVALUE)			(MSBDN_OUTPUT_SUBSYSTEM *, MSBDN_OUTPUT_VALUE *);
typedef	HRESULT	(*PMSBDNOUTPUTGETVALUECOUNT)	(MSBDN_OUTPUT_SUBSYSTEM *, DWORD *);
typedef	HRESULT	(*PMSBDNOUTPUTFREEBUFFER)		(MSBDN_OUTPUT_SUBSYSTEM *, LPVOID);
typedef	HRESULT	(*PMSBDNOUTPUTGETSTATUS)		(MSBDN_OUTPUT_SUBSYSTEM *, HRESULT *);

MSBDNOUTPUTAPI HRESULT msbdnOutputCreate			(MSBDN_OUTPUT_SUBSYSTEM *, DWORD);
MSBDNOUTPUTAPI HRESULT msbdnOutputDestroy			(MSBDN_OUTPUT_SUBSYSTEM *);
MSBDNOUTPUTAPI HRESULT msbdnOutputSetHWAddr			(MSBDN_OUTPUT_SUBSYSTEM *, LPBYTE pData, LPBYTE pHWAddr, LPWORD pwHWAddrLength);
MSBDNOUTPUTAPI HRESULT msbdnOutputSetBandwidth		(MSBDN_OUTPUT_SUBSYSTEM *, DWORD Bps);
MSBDNOUTPUTAPI HRESULT msbdnOutputSetRoutingInfo	(MSBDN_OUTPUT_SUBSYSTEM *, LPVOID pRouteInfo);
MSBDNOUTPUTAPI HRESULT msbdnOutputStreamStatus		(MSBDN_OUTPUT_SUBSYSTEM *, WORD wProtocol, LPBYTE pAddress, BOOL isActive);
MSBDNOUTPUTAPI HRESULT msbdnOutputSendPacket		(MSBDN_OUTPUT_SUBSYSTEM *, PACKET_BUFFER *);
MSBDNOUTPUTAPI HRESULT msbdnOutputSetValue			(MSBDN_OUTPUT_SUBSYSTEM *, MSBDN_OUTPUT_VALUE *);
MSBDNOUTPUTAPI HRESULT msbdnOutputGetValue			(MSBDN_OUTPUT_SUBSYSTEM *, MSBDN_OUTPUT_VALUE *);
MSBDNOUTPUTAPI HRESULT msbdnOutputGetValueCount		(MSBDN_OUTPUT_SUBSYSTEM *, DWORD *);
MSBDNOUTPUTAPI HRESULT msbdnOutputFreeBuffer		(MSBDN_OUTPUT_SUBSYSTEM *, LPVOID);
MSBDNOUTPUTAPI HRESULT msbdnOutputGetStatus			(MSBDN_OUTPUT_SUBSYSTEM *, HRESULT *);

#ifdef __cplusplus
}
#endif // __cplusplus

#ifdef	IS_BRIDGE_OUTPUT_DRIVER

// driver DLL is expected to provide the instance
extern	MSBDN_BRIDGE_CALLBACKS	g_BridgeCallbacks;

static __inline DWORD msbdnPacketLength (PACKET_BUFFER * packet)
{
	return packet -> End - packet -> Start;
}

static __inline DWORD msbdnPacketMemcpy (LPVOID dest, PACKET_BUFFER * packet, DWORD pos, DWORD length)
{
	DWORD	buffer_length = packet -> End - packet -> Start;

	if (pos > buffer_length)
		return 0;

	if (pos + length > buffer_length)
		length = buffer_length - pos;

	memcpy (dest, packet -> Data + pos, length);
	return length;
}

static __inline PACKET_BUFFER * msbdnPacketGetData (PACKET_BUFFER * packet, LPBYTE * ret_data, LPDWORD ret_length)
{
	if (ret_length) *ret_length = packet -> End - packet -> Start;
	if (ret_data) *ret_data = packet -> Data;
	return NULL;
}

static __inline HRESULT msbdnBridgeReportState (MSBDN_OUTPUT_SUBSYSTEM * subsystem, DWORD state, LPCSTR message)
{
	return (*subsystem -> BridgeCallbacks.ReportState) (subsystem, state, message);
}

static __inline HRESULT msbdnBridgeReportActivity (MSBDN_OUTPUT_SUBSYSTEM * subsystem, WORD type, DWORD amount)
{
	return (*subsystem -> BridgeCallbacks.ReportActivity) (subsystem, type, amount);
}

static __inline HRESULT msbdnBridgeReportEvent (MSBDN_OUTPUT_SUBSYSTEM * subsystem, WORD type, DWORD error_code, LPCWSTR message)
{
	return (*subsystem -> BridgeCallbacks.ReportEvent)
		(subsystem, type, error_code, message);
}

#endif // IS_BRIDGE_OUTPUT_DRIVER

// decorated names for GetProcAddress
#define	MSBDN_PROC_MSBDNOUTPUTCREATE			"msbdnOutputCreate"
#define	MSBDN_PROC_MSBDNOUTPUTDESTROY			"msbdnOutputDestroy"
#define	MSBDN_PROC_MSBDNOUTPUTGETSTATUS			"msbdnOutputGetStatus"
#define	MSBDN_PROC_MSBDNOUTPUTSETHWADDR			"msbdnOutputSetHWAddr"
#define	MSBDN_PROC_MSBDNOUTPUTSETBANDWIDTH		"msbdnOutputSetBandwidth"
#define	MSBDN_PROC_MSBDNOUTPUTSETROUTINGINFO	"msbdnOutputSetRoutingInfo"
#define	MSBDN_PROC_MSBDNOUTPUTSTREAMSTATUS		"msbdnOutputStreamStatus"
#define	MSBDN_PROC_MSBDNOUTPUTSENDPACKET		"msbdnOutputSendPacket"
#define	MSBDN_PROC_MSBDNOUTPUTSETVALUE			"msbdnOutputSetValue"
#define	MSBDN_PROC_MSBDNOUTPUTGETVALUE			"msbdnOutputGetValue"
#define	MSBDN_PROC_MSBDNOUTPUTGETVALUECOUNT		"msbdnOutputGetValueCount"
#define	MSBDN_PROC_MSBDNOUTPUTFREEBUFFER		"msbdnOutputFreeBuffer"

#endif // BRIDGE_H
