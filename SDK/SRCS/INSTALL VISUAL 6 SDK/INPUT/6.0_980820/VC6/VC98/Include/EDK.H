// --edk.h----------------------------------------------------------------------
// 
//  Master include file for Microsoft Exchange SDK
// 
// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef __EDK_H__
#define __EDK_H__

//==============================================================================
//  VERSION INFORMATION
//==============================================================================

#define EDK_MAJOR_VERSION       1                   // major header version
#define EDK_MINOR_VERSION       0                   // minor header version
#define EDK_VERSION_NUMBER      ((EDK_MAJOR_VERSION<<8)|EDK_MINOR_VERSION)
#define EDK_VERSION_STR         "1.00.00\0"

//==============================================================================
// By default, the VC++ Workbench creates a make file with _DEBUG or NDEBUG.  
// We need to define DEBUG or SHIP to work with all the header files.
//==============================================================================

#if !defined(DEBUG) && !defined(SHIP)
    #ifdef _DEBUG
        #define DEBUG
        #define TEST
    #else   // NDEBUG should be defined
        #define SHIP
    #endif
#endif

//==============================================================================
//  NON-RESOURCE
//==============================================================================

#ifndef RC_INVOKED      // skip rest of file

#pragma warning(disable:4100 4103 4115 4200 4201 4204 4211 4214 4505 4514 4611 4706 4710)

#define _INC_OLE
#define INC_RPC
#define INC_OLE2

#ifdef UNICODE
#ifndef _UNICODE
#define _UNICODE
#endif
#endif

#if defined(_M_IX86)
#define _EXCHANGE_MACHINE_TYPE "i386"
#elif  defined(_M_ALPHA)
#define _EXCHANGE_MACHINE_TYPE "ALPHA"
#elif  defined(_M_MRX000)
#define _EXCHANGE_MACHINE_TYPE "MIPS"
#elif  defined(_M_PPC)
#define _EXCHANGE_MACHINE_TYPE "PPC"
#endif

#include <windows.h>
#include <windowsx.h>

#pragma warning(disable:4103)
#include <objbase.h>
#pragma warning(disable:4103)

#ifdef EXTERN_C
#undef EXTERN_C
#endif

#ifdef __cplusplus
    #define EXTERN_C    extern "C"
#else
    #define EXTERN_C    extern
#endif

EXTERN_C const IID IID_IExchangeManageStore;
EXTERN_C const IID IID_IExchangeModifyTable;
EXTERN_C const IID IID_IExchangeConfigureXfer;
EXTERN_C const IID IID_IExchangeXferBuffer;
EXTERN_C const IID IID_IExchangeExportChanges;
EXTERN_C const IID IID_IExchangeImportHierarchyChanges;
EXTERN_C const IID IID_IExchangeImportContentsChanges;
EXTERN_C const IID LIBID_aclcls;
EXTERN_C const IID IID_IExchangeFolderACLs;
EXTERN_C const IID LIBID_rulecls;
EXTERN_C const IID IID_IExchangeFolderRules;
EXTERN_C const IID IID_IEDKVirtualStreamOnProperty;
EXTERN_C const IID IID_IExchangeRuleAction;
EXTERN_C const IID IID_IExchangeFastTransfer;
EXTERN_C const IID IID_IExchangeFavorites;
EXTERN_C const IID IID_IExchangeMessageCpid0;
EXTERN_C const IID IID_IExchangeRuleExtCallback;
EXTERN_C const IID IID_IExchangeRuleExt;

#ifdef EDK_USES_IID
#define INITGUID

#include <initguid.h>

#pragma warning(disable:4200)
#include <edkguid.h>
#include <aclsid.h>
#include <rclsid.h>
#include <vsopcsid.h>
#pragma warning(disable:4200)

#define USES_IID_IUnknown
#define USES_IID_IMessage
#define USES_IID_IStream
#define USES_IID_IClassFactory
#define USES_IID_IPersistMessage
#define USES_IID_IMAPIForm
#define USES_IID_IMAPIProp
#define USES_IID_IMAPIPropData
#define USES_IID_IMAPIFolder
#define USES_IID_IABContainer
#define USES_IID_IAddrBook
#define USES_IID_IMAPIFormInfo
#define USES_IID_IMailUser
#define USES_IID_IAttachment
#define USES_IID_IDistList
#define USES_IID_IMAPIStatus
#define USES_IID_IMAPISession
#define USES_IID_IMsgStore
#define USES_IID_IProfSect
#define USES_IID_IMAPIContainer
#define USES_IID_IMAPITable
#define USES_PS_MAPI
#define USES_PS_PUBLIC_STRINGS
#endif

#include <assert.h>
#include <conio.h>
#include <ctl3d.h>
#include <ctype.h>
#include <fcntl.h>
#include <io.h>
#include <limits.h>
#include <malloc.h>

#define _MAPINLS_H_

#pragma warning(disable:4200)
#include <mapidefs.h>
#pragma warning(disable:4200)

#ifdef DEBUG
#ifdef MAPI_DEFERRED_ERRORS
#undef MAPI_DEFERRED_ERRORS
#endif
#define MAPI_DEFERRED_ERRORS    0
#endif

#include <mapicode.h>
#include <mapiform.h>
#include <mapiguid.h>
#include <mapispi.h>
#include <mapitags.h>
#include <mapiutil.h>
#include <mapival.h>
#include <mapiwin.h>
#include <mapix.h>
#include <rtflib.h>

#include <memory.h>

#pragma warning(disable:4200)
#include <edkmdb.h>
#pragma warning(disable:4200)

#pragma warning(disable:4200)
#include <_entryid.h>
#pragma warning(disable:4200)

#include <process.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

#pragma warning(disable:4200)
#include <tnef.h>
#pragma warning(disable:4200)

#include <wchar.h>
#include <winbase.h>
#include <winperf.h>


#pragma warning(disable:4200)
#include <imessage.h>
#pragma warning(disable:4200)

#include <emsabtag.h>

//==============================================================================
// EDK include files.  See end of file for more include files that need to be
// included after macro definitions.
//==============================================================================

#include "edkmsg.h"

#include "edkcode.h"
#include "edkdebug.h"

#include "edkmapi.h"
#include "addrlkup.h"
#include "edktrack.h"
#include "convstrc.h"
#include "convcwrp.h"
#include "edkevent.h"
#include "exchinst.h"
#include "monitor.h"
#include "gwreport.h"
#include "stats.h"
#include "stattype.h"
#include "winwrap.h"
#include "mblogon.h"
#include "edkutils.h"
#include "newpst.h"
#include "aclcls.h"
#include "rulecls.h"
#include "proptag.h"
#include "edkcfg.h"
#include "vsof.h"
#include "vsop.h"

//==============================================================================
//  MACROS
//==============================================================================

#ifdef __cplusplus
#ifdef FBadUnknown
#undef FBadUnknown
#endif
#define FBadUnknown( lpObj ) ((lpObj) == NULL)
#endif

// convenient macros for manipulating 64-bit integers to 32-bit integers
#define LOWPART_DWORDLONG		((DWORDLONG) 0x00000000FFFFFFFF)
#define HIGHPART_DWORDLONG		((DWORDLONG) 0xFFFFFFFF00000000)

#define MAKEDWORDLONG(lo,hi)	( (DWORDLONG) ( ( (hi) << 32 ) | (lo) ) )
#define LOWDWORD(x)				( (DWORD) ( (x) & LOWPART_DWORDLONG ) )
#define HIDWORD(x)				( (DWORD) ( ( (x) & HIGHPART_DWORDLONG ) >> 32 ) )

#define LOWPART_LONGLONG		((LONGLONG) 0x00000000FFFFFFFF)
#define HIGHPART_LONGLONG		((LONGLONG) 0xFFFFFFFF00000000)

#define LOWLONG(x)				( (DWORD) ( (x) & LOWPART_LONGLONG ) )
#define HILONG(x)				( (LONG) ( ( (x) & HIGHPART_LONGLONG ) >> 32 ) )

// definition of the Exchange address type.
#define EXCHANGE_ADDRTYPE	"EX"

#define MAX_ULONG (ULONG) ~0L   // All bits on.

#define EDK_MAX_QUERY_ROWS 1024

#define VALID_OBJ_TYPE(x) (((x) >= ((ULONG)0x00000001)) && \
			   ((x) <= ((ULONG)0x0000000B)))

#define VALID_PROP_ID(x)  ((PROP_ID((x)) != 0x0000) && (PROP_ID((x)) != 0xFFFF))

#define CbNewSPropValue(_centries) \
    ((_centries)*sizeof(SPropValue))

#define CbNewFlagList(_cflag) \
	(offsetof(FlagList,ulFlag) + (_cflag)*sizeof(ULONG))

#define OLECALL(x)  (x)->lpVtbl

#define ULOLERELEASE(x) \
{                                    \
	if((x) != NULL)                  \
	{                                \
	    OLECALL((x))->Release((x));  \
	}                                \
	(x) = NULL;                      \
}

#define VALID_BOOL(x)   (((x) == TRUE) || ((x) == FALSE))

#define VALID_EDK_CONTAINER(x) \
    ((((ULONG)(x)) == ((ULONG)EDK_FOLDER)) || \
    (((ULONG)(x)) == ((ULONG)EDK_PUBLIC_FOLDER)) || \
    (((ULONG)(x)) == ((ULONG)EDK_DIRECTORY)))

// Returns count of elements in any array.
#define ARRAY_CNT( array)    (sizeof( array) / sizeof(array[0]))

#if !defined(__cplusplus) || defined(CINTERFACE)
#define MAPICALL(x)     (x)->lpVtbl
#else
#define MAPICALL(x)     (x)
#endif

#ifdef  MAX_ALIGN
#undef  MAX_ALIGN
#endif
#define MAX_ALIGN    16

//$--cbStrLen@------------------------------------------------
//  Returns total number of bytes (including NULL) used by 
//  a string.  Useful for string allocations...
// -----------------------------------------------------------
#define cbStrLenA(sz)   ((lstrlenA((sz)) + 1) * sizeof(CHAR))

#if defined(_M_IX86)
#define cbStrLenW(sz)   ((lstrlenW((sz)) + 1) * sizeof(WCHAR))
#else
// lstrlenW can return 0 for UNALIGNED UNICODE strings on non-IX86 platforms
__inline static size_t cbStrLenW(
    IN UNALIGNED const WCHAR *wsz)
{
    size_t cbWsz = 0;

    for(; *wsz; wsz++)
        cbWsz += sizeof( WCHAR);

    return( cbWsz + sizeof( WCHAR));
}
#endif

#ifdef UNICODE
#define cbStrLen    cbStrLenW
#else 
#define cbStrLen    cbStrLenA
#endif

// Block transfer size for streams and files
#define EDK_CBTRANSFER  4096

#define ULRELEASE(x) \
{                    \
	UlRelease((x));  \
	(x) = NULL;      \
}

#define MAPIFREEBUFFER(x) \
{                         \
    MAPIFreeBuffer((x));  \
	(x) = NULL;           \
}

#define FREEPADRLIST(x) \
{                       \
    FreePadrlist((x));  \
	(x) = NULL;         \
}

#define FREEPROWS(x)    \
{                       \
    FreeProws((x));     \
	(x) = NULL;         \
}

#define FREE(x) { if((x) != NULL) { free((void *)(x)); (x) = NULL; } }

#define LOCALFREE(x) { if((x) != NULL) {LocalFree((void *)(x)); (x) = NULL;} }

#define GLOBALFREE(x) { if((x) != NULL) {GlobalFree((void *)(x)); (x) = NULL;} }

#define DLLIMPORT __declspec( dllimport )
#define DLLEXPORT __declspec( dllexport )

#define STRNCPY(dst,src) lstrcpyn((dst), (src), (sizeof(dst)/sizeof(TCHAR))-1)

#define STRNCAT(dst,src) _tcsncat((dst), (src), (sizeof(dst)/sizeof(TCHAR))-1)

#define FREEHSCM(h)                         \
{                                           \
    if ((h) != NULL)                        \
	{                                       \
        if(CloseServiceHandle(h) == FALSE)  \
        {                                   \
            HRESULT _hr = HR_LOG(E_FAIL);   \
        }                                   \
		(h) = NULL;                         \
	}                                       \
}

#define CLOSEHANDLE(h)                                  \
{                                                       \
    if(((h) != NULL) && ((h) != INVALID_HANDLE_VALUE))  \
    {                                                   \
        if(CloseHandle((h)) == FALSE)                   \
        {                                               \
            HRESULT _hr = HR_LOG(E_FAIL);               \
        }                                               \
        (h) = NULL;                                     \
    }                                                   \
}

#define REGCLOSEKEY(h)                                  \
{                                                       \
	if((h) != NULL && (h) != INVALID_HANDLE_VALUE)      \
	{                                                   \
		if(RegCloseKey((h)) != ERROR_SUCCESS)           \
        {                                               \
            HRESULT _hr = HR_LOG(E_FAIL);               \
        }                                               \
		(h) = NULL;                                     \
	}                                                   \
}

//==============================================================================
// EDK include files that depend upon above macros.
//==============================================================================

#ifdef __cplusplus  // C++ classes
    #include "EdkUtCPP.H"
#endif

//==============================================================================

#endif  // RC_INVOKED
#endif  // __EDK_H__
