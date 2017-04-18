#ifndef __include_bdnapi_h
#define	__include_bdnapi_h

#include <winsock2.h>
#include <time.h>

#ifndef MSBDNAPI
#define MSBDNAPI __declspec( dllimport )
#endif

#ifndef EXTERN_C
#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif
#endif

#ifndef	BDN_TIME_UNBOUND
#define	BDN_TIME_UNBOUND	((time_t)0)
#endif

#ifndef	BDN_SLOT_NONE
#define	BDN_SLOT_NONE		0xFFFFFFFFUL
#endif

// opaque handles
typedef struct BDN_SERVICE * HBDNSERVICE;
typedef struct BDN_CONN * HBDNCONN;

typedef struct BDN_RSVP {
	DWORD		Version;
	DWORD		Size;
	DWORD		ReservationID;
	FLOWSPEC	Flowspec;
	time_t		StartTime;
	time_t		EndTime;
//	SOCKADDR	rsvpAddr;			// This is never actually used
} BDN_RSVP, * LPBDN_RSVP, MSBDNRSVP, *PMSBDNRSVP, *LPMSBDNRSVP;

#define	BDN_RSVP_VERSION	0x0100

typedef struct tagBDN_HARDWARE_ADDR {
	WORD		Type;
	LPVOID		Address;
	WORD		AddressLength;
} BDN_HARDWARE_ADDR, * LPBDN_HARDWARE_ADDR;

#define	BDN_HARDWARE_TYPE_IEEE8023	1
#define	BDN_HARDWARE_TYPE_ATM		2


typedef struct BDN_VALUE {
	WORD					Type;
	union {
		SOCKET_ADDRESS		SocketAddress;
		struct {
			union {
				LPSTR		AnsiString;
				LPWSTR		UnicodeString;
				LPTSTR		String;
			};
			DWORD			StringMaxLength;
		};
		DWORD				Dword;
	};
} BDN_VALUE, * LPBDN_VALUE;

// BDN_VALUE.Type
#define BDN_VALUE_ANSI_STRING		1
#define	BDN_VALUE_UNICODE_STRING	2
#define	BDN_VALUE_DWORD				3
#define BDN_VALUE_SOCKADDR			4

#ifdef _UNICODE
#define	BDN_VALUE_STRING			BDN_VALUE_UNICODE_STRING
#else
#define	BDN_VALUE_STRING			BDN_VALUE_ANSI_STRING
#endif

// value identifiers used with BDN service
#define	BDN_SERVICE_BRIDGE		1
#define	BDN_SERVICE_ARS			2
#define	BDN_SERVICE_BRS			3
#define	BDN_SERVICE_GLOBAL_ADDR	4
#define	BDN_SERVICE_LOCAL_ADDR	5
#define	BDN_SERVICE_APPLICATION	6
#define	BDN_SERVICE_CONTENT_SERVICE		7


EXTERN_C HRESULT WINAPI BdnLookupServiceA (LPCSTR, HBDNSERVICE *);
EXTERN_C HRESULT WINAPI BdnLookupServiceW (LPCWSTR, HBDNSERVICE *);

EXTERN_C HRESULT WINAPI BdnServiceCreate (HBDNSERVICE *);

EXTERN_C HRESULT WINAPI BdnServiceClose (HBDNSERVICE);

EXTERN_C HRESULT WINAPI BdnReserveAddress
(	HBDNSERVICE,
	time_t,
	time_t,
	DWORD,
	DWORD,
	const SOCKET_ADDRESS *
);

EXTERN_C HRESULT WINAPI BdnReleaseAddress
(	HBDNSERVICE,
	time_t,
	const SOCKET_ADDRESS *
);

EXTERN_C HRESULT WINAPI BdnServiceSetValue
(	HBDNSERVICE,
	DWORD,
	const BDN_VALUE *
);

EXTERN_C HRESULT WINAPI BdnServiceGetValue
(	HBDNSERVICE,
	DWORD,
	BDN_VALUE *
);

EXTERN_C HRESULT WINAPI BdnServiceSetValueStringA
(	HBDNSERVICE,
	DWORD,
	LPCSTR
);

EXTERN_C HRESULT WINAPI BdnServiceSetValueStringW
(	HBDNSERVICE,
	DWORD,
	LPCWSTR
);

EXTERN_C HRESULT WINAPI BdnServiceGetValueStringA
(	HBDNSERVICE,
	DWORD,
	LPSTR,
	DWORD
);

EXTERN_C HRESULT WINAPI BdnServiceGetValueStringW
(	HBDNSERVICE,
	DWORD,
	LPWSTR,
	DWORD
);

EXTERN_C HRESULT WINAPI BdnCreateRegulatedMulticast
(	HBDNSERVICE			service,
	LPBDN_RSVP			reservation,
	HBDNCONN *			conn
);

EXTERN_C HRESULT WINAPI BdnCreateRegulatedMulticastRaw
(	SOCKET				sock,
	LPBDN_RSVP			reservation,
	HBDNCONN *			conn
);

EXTERN_C HRESULT WINAPI BdnOpenTunnel
(	HBDNSERVICE				service,
	const SOCKET_ADDRESS *	destination_address,
	BYTE					mttl,
	DWORD					reservation_id,
	HBDNCONN *				conn
);

EXTERN_C HRESULT WINAPI BdnReserveBandwidthA
(	HBDNSERVICE		service,
	time_t			start_time,
	time_t			end_time,
	DWORD			slot,
	const FLOWSPEC *	flowspec,
	LPCSTR			description,
	DWORD *			resv_id
);

EXTERN_C HRESULT WINAPI BdnReserveBandwidthW
(	HBDNSERVICE		service,
	time_t			start_time,
	time_t			end_time,
	DWORD			slot,
	const FLOWSPEC *	flowspec,
	LPCWSTR			description,
	DWORD *			resv_id
);

EXTERN_C HRESULT WINAPI BdnGetReservationA
(	HBDNSERVICE		service,
	DWORD			resv_id,
	BDN_RSVP *		resv,
	LPSTR			description,
	DWORD			description_len
);

EXTERN_C HRESULT WINAPI BdnGetReservationW
(	HBDNSERVICE		service,
	DWORD			resv_id,
	BDN_RSVP *		resv,
	LPWSTR			description,
	DWORD			description_len
);

EXTERN_C HRESULT WINAPI BdnLookupReservationA
(	HBDNSERVICE		hBdnService,
	LPCSTR			szDescription,
	time_t			StartTime,
	time_t			EndTime,
	BDN_RSVP *		lpReservation,
	DWORD *			lpReservationCount		// in-out parameter
);

EXTERN_C HRESULT WINAPI BdnLookupReservationW
(	HBDNSERVICE		hBdnService,
	LPCWSTR			szDescription,
	time_t			StartTime,
	time_t			EndTime,
	BDN_RSVP *		lpReservation,
	DWORD *			lpReservationCount		// in-out parameter
);

EXTERN_C HRESULT WINAPI BdnClearReservation
(	HBDNSERVICE		hBdnService,
	DWORD			dwReservationID
);

EXTERN_C INT WINAPI BdnSend
(	HBDNCONN,
	const void *,
	WORD);

EXTERN_C INT WINAPI BdnSendTo (
	HBDNCONN		hBdnConn,
	const SOCKET_ADDRESS * lpDestAddress,
	WORD			wDestPort,
	const BDN_HARDWARE_ADDR * lpHardwareAddress,
	const void *	lpBuffer,
	WORD			nBufferLength
);

EXTERN_C INT WINAPI BdnSendRaw (
	HBDNCONN		hBdnConn,
	WORD			wProtocol,
	const BDN_HARDWARE_ADDR * lpHardwareAddress,
	const void *	lpBuffer,
	WORD			nBufferLength
);


#ifdef _UNICODE
#define	BdnGetReservation				BdnGetReservationW
#define	BdnLookupReservation			BdnLookupReservationW
#define	BdnLookupService				BdnLookupServiceW
#define	BdnServiceSetValueString		BdnServiceSetValueStringW
#else
#define	BdnGetReservation				BdnGetReservationA
#define	BdnLookupReservation			BdnLookupReservationA
#define	BdnLookupService				BdnLookupServiceA
#define	BdnServiceSetValueString		BdnServiceSetValueStringA
#endif


// #define MSBDNEDENIED        -1; // ???
// #define MSBDNEINVALID       -2; // ???


EXTERN_C MSBDNAPI INT WINAPI msbdnReserveAddress(
    LPCSADDR_INFO lpcsServerAddr,
    time_t StartTime,
    time_t EndTime,
    WORD wFLags,
    LPSOCKET_ADDRESS lpDestAddr
);

#define MSBDN_INET_EXISTING	0x0100  // The lpDestAddr is already filled with an existing value that the server should use for the reservation.
#define MSBDN_INET_GLOBAL	0x0001  // Reserve an internet-wide globally unique IP address for the duration is the reservation.  TTL >= 127.
#define MSBDN_INET_NETWORK	0x0002  // Reserve a IP address that is unique to the organization’s network. For DSS, this is equivalent to their entire Satellite.
#define MSBDN_INET_SUBNET	0x0003  // Reserve an address that is unique to a local subnet. For DSS, this is equivilent to a single channel or a group of channels, depending on how the network is configured.
    

EXTERN_C MSBDNAPI INT WINAPI msbdnRelinquishAddress(
    LPCSADDR_INFO lpcsServerAddr,
    time_t FromTime,
    LPSOCKET_ADDRESS lpDestAddr
);


EXTERN_C MSBDNAPI INT WINAPI msbdnReserveBandwidth(
    LPCSADDR_INFO lpcsServerAddr,
    time_t StartTime,
    time_t EndTime,
    LPFLOWSPEC lpFlowSpec,
    LPCTSTR lpszDescription,
    DWORD *lpReservationID
);


EXTERN_C MSBDNAPI INT WINAPI msbdnGetReservation(
    LPCSADDR_INFO lpcsServerAddr,
    DWORD dwReservationID, 
    LPMSBDNRSVP lpReservation,
    LPSTR lpszDescription,
    DWORD dwDescriptionLength
);


EXTERN_C MSBDNAPI INT WINAPI msbdnLookupReservation(
    LPCSADDR_INFO lpcsServerAddr,
    LPCSTR szDescription,
    time_t StartTime,
    time_t EndTime,
    LPMSBDNRSVP lpReservation,
    DWORD *lpdwReservationCount
);


EXTERN_C MSBDNAPI INT WINAPI msbdnClearReservation(
    LPCSADDR_INFO lpcsServerAddr,
    DWORD dwReservationID
);

EXTERN_C MSBDNAPI INT WINAPI msbdnForwardMulticast(
    LPCSADDR_INFO lpcsBridgeAddr,
    LPSOCKET_ADDRESS lpDestAddr,
    WORD wTTL,
    DWORD dwReservationID
);

EXTERN_C MSBDNAPI INT WINAPI msbdnStopMulticast(
    LPCSADDR_INFO lpcsBridgeAddr,
    LPSOCKET_ADDRESS lpDestAddr
);

EXTERN_C MSBDNAPI HBDNCONN msbdnCreateRegulatedMulticast (
    SOCKET hSocket,
    LPMSBDNRSVP lpReservation
); 

EXTERN_C MSBDNAPI HBDNCONN msbdnOpenTunnel (
    LPCSADDR_INFO lpcsBridgeAddr,
    LPSOCKET_ADDRESS lpDestAddr,
    WORD wTTL,
    DWORD dwReservationID
); 

EXTERN_C MSBDNAPI INT WINAPI msbdnSend (
    HBDNCONN hBdnConn,
    LPVOID lpBuffer,
    WORD nBytes
);

EXTERN_C MSBDNAPI INT WINAPI msbdnSendTo (
    HBDNCONN hBdnCon,
    LPSOCKET_ADDRESS lpDestAddress,
    WORD wDestPort,
    LPVOID lpHardwareAddress,
    LPVOID lpBuffer,
    WORD nBytes
);

EXTERN_C MSBDNAPI INT WINAPI msbdnSendRaw (
    HBDNCONN hBdnCon,
    WORD wProtocol,
    LPVOID lpHardwareAddress,
    LPVOID lpBuffer,
    WORD nBytes
);


EXTERN_C MSBDNAPI INT WINAPI msbdnClose (
    HBDNCONN hBdnCon
);


EXTERN_C MSBDNAPI INT WINAPI msbdnReserveAddressEx(
    LPCSTR szServer,
    time_t StartTime,
    time_t EndTime,
    WORD wFLags,
    LPCSTR szDestAddr,
    DWORD dwDestAddrLength
);

EXTERN_C MSBDNAPI INT WINAPI msbdnRelinquishAddressEx(
    LPCSTR szServer,
    time_t FromTime,
    LPCSTR szDestAddr
);

EXTERN_C MSBDNAPI INT WINAPI msbdnReserveBandwidthEx(
    LPCSTR szServer,
    time_t StartTime,
    time_t EndTime,
    LPFLOWSPEC lpFlowSpec,
    LPCTSTR lpszDescription,
    DWORD *lpReservationID
);


EXTERN_C MSBDNAPI INT WINAPI msbdnGetReservationEx(
    LPCSTR szServer,
    DWORD dwReservationID, 
    LPMSBDNRSVP lpReservation,
    LPSTR lpszDescription,
    DWORD dwDescriptionLength
);


EXTERN_C MSBDNAPI INT WINAPI msbdnLookupReservationEx(
    LPCSTR szServer,
    LPCSTR szDescription,
    time_t StartTime,
    time_t EndTime,
    LPMSBDNRSVP lpReservation,
    DWORD *lpdwReservationCount
);

EXTERN_C MSBDNAPI INT WINAPI msbdnClearReservationEx(
    LPCSTR szServer,
    DWORD dwReservationID
);

EXTERN_C MSBDNAPI INT WINAPI msbdnForwardMulticastEx(
    LPCSTR szBridge,
    LPCSTR szDestAddr,
    DWORD dwReservationID
);

EXTERN_C MSBDNAPI INT WINAPI msbdnStopMulticastEx(
    LPCSTR szBridge,
    LPCSTR szDestAddr
);

EXTERN_C MSBDNAPI HBDNCONN WINAPI msbdnOpenTunnelEx(
    LPCSTR szBridge,
    LPCSTR szDestAddr,
    WORD wDestPort,
    WORD wTTL,
    DWORD dwReservationID
); 


#endif // __include_bdnapi_h
