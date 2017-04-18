/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995-1998  Microsoft Corporation

Module Name:  

afdfunc.h

Abstract:

Functions exposed from the AFD system process

Notes: 


--*/

// @CESYSGEN IF CE_MODULES_AFD

#ifndef _AFDFUNC_H_
#define _AFDFUNC_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SOCKHAND_DEFINED
DECLARE_HANDLE(SOCKHAND);
typedef SOCKHAND *PSOCKHAND;
#define SOCKHAND_DEFINED
#endif

#include "ras.h"
#include "tapi.h"

//
// Start WINCE API definitions.
//
DWORD RasDial (LPRASDIALEXTENSIONS dialExtensions,
	       LPTSTR phoneBookPath,
	       LPRASDIALPARAMS rasDialParam,
	       DWORD NotifierType,
	       LPVOID notifier,
	       LPHRASCONN pRasConn);
DWORD RasHangup (HRASCONN Session);	// Kept for historical compatibility
DWORD RasHangUp (HRASCONN Session);
DWORD RasEnumEntries (LPWSTR Reserved,
		      LPWSTR lpszPhoneBookPath,
		      LPRASENTRYNAME lprasentryname,
		      LPDWORD lpcb,
		      LPDWORD lpcEntries);
DWORD RasGetEntryDialParams (LPWSTR lpszPhoneBook,
			     LPRASDIALPARAMS lpRasDialParams,	
			     LPBOOL lpfPassword);
DWORD RasSetEntryDialParams (LPWSTR lpszPhoneBook,
			     LPRASDIALPARAMS lpRasDialParams,
			     BOOL fRemovePassword);
DWORD RasGetEntryProperties (LPWSTR lpszPhoneBook,
			     LPWSTR szEntry,
			     LPBYTE lpbEntry,
			     LPDWORD lpdwEntrySize,
			     LPBYTE lpb,
			     LPDWORD lpdwSize);
DWORD RasSetEntryProperties (LPWSTR lpszPhoneBook,		
			     LPWSTR szEntry,
			     LPBYTE lpbEntry,
			     DWORD dwEntrySize,
			     LPBYTE lpb,
			     DWORD dwSize);
DWORD RasValidateEntryName (LPWSTR lpszPhonebook,		
			    LPWSTR lpszEntry);
DWORD RasDeleteEntry (LPWSTR lpszPhonebook,
		      LPWSTR lpszEntry);
DWORD RasRenameEntry (LPWSTR lpszPhonebook,
		      LPWSTR lpszOldEntry,
		      LPWSTR lpszNewEntry);
DWORD RasEnumConnections (LPRASCONN lprasconn,
			  LPDWORD lpcb,
			  LPDWORD lpcConnections);
DWORD RasGetConnectStatus (HRASCONN rasconn,				
			   LPRASCONNSTATUS lprasconnstatus);
DWORD RasGetEntryDevConfig (LPCTSTR szPhonebook,
			    LPCTSTR szEntry,
			    LPDWORD pdwDeviceID,
			    LPDWORD pdwSize,
			    LPVARSTRING pDeviceConfig);
DWORD RasSetEntryDevConfig (LPCTSTR szPhonebook,
			    LPCTSTR szEntry,
			    DWORD dwDeviceID,
			    LPVARSTRING lpDeviceConfig);
			    
#ifdef __cplusplus
}
#endif

#ifdef WINCEOEM
#ifdef WINCEMACRO
#include <mafdfunc.h>	// macros
#endif
#endif

#endif  // _AFDFUNC_H_

// @CESYSGEN ENDIF
