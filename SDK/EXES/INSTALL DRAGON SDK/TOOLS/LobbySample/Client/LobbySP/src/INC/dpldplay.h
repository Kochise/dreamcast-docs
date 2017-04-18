/*==========================================================================
 *
 *	Copyright (C) 1996-1997 Microsoft Corporation.  All Rights Reserved.
 *
 *	File:       dpldplay.h
 *	Content:	Header file for all dpldplay.c related information
 *
 *	History:
 *	Date		By		Reason
 *	====		==		======
 *  5/13/96		myronth	Created it
 *	10/30/96	myronth	Changed to DX5 methods
 *	11/20/96	myronth	Fixed Thread Termination code
 *	2/12/97		myronth	Mass DX5 changes
 *	3/12/97		myronth	DPlay3 support, initial async enumsession stuff
 *	3/17/97		myronth	Added default timeout, WSTRLEN_BYTES
 *	3/31/97		myronth	Removed dead code
 *	4/9/97		myronth	Added SP dialog related stuff
 *	5/8/97		myronth	Added DPLCONNECTION packing & validation macros
 *	5/22/97		myronth	Added prototype for PRV_SendGeneralMethodMessage
 *	6/9/97		myronth	Added Send queue
 *	6/17/97		myronth	Changed Send to use DPID_SERVERPLAYER
 ***************************************************************************/
#ifndef __DPLDPLAY_INCLUDED__
#define __DPLDPLAY_INCLUDED__

#include "dpf.h"
#include "lobbysp.h"
#include "dplmess.h"
#include "memalloc.h"


//--------------------------------------------------------------------------
//
//	Definitions
//
//--------------------------------------------------------------------------
#define DEFAULT_COMM_BUFFER_SIZE		1024
#define DPLDPLAY_DEFAULT_TIMEOUT		(5 * 1000)
#define STRLEN OS_StrLen
#define WSTRLEN_BYTES(ptr) (OS_StrLen(ptr) * sizeof(WCHAR))

#ifndef UNDER_CE
#define ASSERT DDASSERT
#endif

#define DPMEM_ALLOC(size) MemAlloc(size)
#define DPMEM_FREE(ptr) MemFree(ptr)

#define VALID_READ_PTR(ptr,cnt) \
        (!IsBadReadPtr( ptr, cnt))

#define VALID_WRITE_PTR(ptr,cnt) \
        (!IsBadWritePtr( ptr, cnt))

#define VALID_UUID_PTR(ptr) \
        (ptr && !IsBadWritePtr( ptr, sizeof(UUID)))

#define VALID_READ_UUID_PTR(ptr) \
        (ptr && !IsBadReadPtr( ptr, sizeof(UUID)))

#define VALID_DPLOBBY_CONNECTION( ptr ) \
		(!IsBadWritePtr(ptr, sizeof(DPLCONNECTION)) && \
        (ptr->dwSize == sizeof(DPLCONNECTION)))

#define VALID_READ_DPSESSIONDESC2(ptr) \
        ( ptr && !IsBadReadPtr( ptr, sizeof( DPSESSIONDESC2 )) && \
        (ptr->dwSize == sizeof(DPSESSIONDESC2)))

#define VALID_READ_DPNAME_PTR( ptr ) \
        ( ptr && !IsBadReadPtr( ptr, sizeof( DPNAME )) && \
        (ptr->dwSize == sizeof(DPNAME)))

#define TRY 		_try
#define EXCEPT(a)	_except( a )

#ifdef DEBUG
	#define DPF_ERRVAL(a, b)  DPF( 0, DPF_MODNAME TEXT(": ") a, b );
#else
	#define DPF_ERRVAL(a, b)
#endif

// The following definitions are for the Service Provider dialog
#define IDC_STATIC						(-1)
#define IDD_SELECTSP					10100
#define IDC_SPLIST						10101

extern HANDLE ghInstance;		// From dllmain.c

//--------------------------------------------------------------------------
//
//	Declarations
//
//--------------------------------------------------------------------------
typedef struct MESSAGENODE
{
	LPVOID					lpMessage;
	DWORD					dwMessageSize;
	DWORD					dwFlags;
	struct MESSAGENODE *	lpNext;
} MESSAGENODE, * LPMESSAGENODE;


typedef struct SPDATABLOB
{
	LPDIRECTPLAY3		lpIDP;
	LPDPADDRESS			lpAddress;
	DPID				dwMyPlayerID;
	DWORD				dwTimeout;
	
	// Receive Thread Stuff
	HANDLE				hReceiveEvent;
	HANDLE				hKillEvent;
	HANDLE				hMethodEvent;
	HANDLE				hMethodAckEvent;
	HANDLE				hReceiveThread;
	DWORD				dwReceiveThreadID;
	LPVOID				lpCommBuffer;
	DWORD				dwCommBufferSize;

	// Send Thread Stuff
	HANDLE				hSendThread;
	HANDLE				hKillSendEvent;
	HANDLE				hSendEvent;
	DWORD				dwNumMessages;
	LPMESSAGENODE		lpMessageQueue;
	CRITICAL_SECTION	csMessageQueue;

}SPDATABLOB, * LPSPDATABLOB;


//--------------------------------------------------------------------------
//
//	Prototypes
//
//--------------------------------------------------------------------------

// From dplcomm.c
DWORD PRV_ReceiveThreadFunc(LPVOID);
DWORD PRV_SendThreadFunc(LPVOID);
HRESULT PRV_SendMethodMessage(LPSPDATABLOB, LPVOID, DWORD, DWORD);
HRESULT PRV_GetSPDataStuff(LPDPLOBBYSP, LPSPDATABLOB *, LPDIRECTPLAY3 *);
HRESULT PRV_SendGeneralMethodMessage(LPSPDATABLOB, LPVOID, DWORD, DWORD, DWORD);

// From dplpack.c
void PRV_GetDPLCONNECTIONPackageSize(LPDPLCONNECTION, LPDWORD, LPDWORD);
HRESULT PRV_PackageDPLCONNECTION(LPDPLCONNECTION, LPVOID);
HRESULT PRV_UnpackageDPLCONNECTIONUnicode(LPVOID, LPVOID);
HRESULT PRV_UnpackageDPLCONNECTIONAnsi(LPVOID, LPVOID);
HRESULT PRV_ValidateDPLCONNECTION(LPDPLCONNECTION, BOOL);
void PRV_FreeInternalDPLCONNECTION(LPDPLCONNECTION);
void PRV_FixupDPLCONNECTIONPointers(LPDPLCONNECTION);

// From spos.c
BOOL OS_IsPlatformUnicode();
HRESULT GetString(LPWSTR *, LPWSTR);
int OS_StrLen(LPCWSTR);
HANDLE OS_CreateEvent(LPSECURITY_ATTRIBUTES, BOOL, BOOL, LPWSTR);
HRESULT GetAnsiString(LPSTR *, LPWSTR);
int WideToAnsi(LPSTR, LPWSTR, int);

#endif // __DPLDPLAY_INCLUDED__
