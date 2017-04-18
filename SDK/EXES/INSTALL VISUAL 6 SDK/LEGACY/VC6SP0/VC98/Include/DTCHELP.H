/* ----------------------------------------------------------------------------
Microsoft	D.T.C (Distributed Transaction Coordinator)

(c)	1996	Microsoft Corporation.	All Rights Reserved

@doc

@module		DTCHelp.h	|

			contains helper API for loading the DTCHelper DLL

-------------------------------------------------------------------------------
@rev 	0 	| 8th -Sep-1995	|	GaganC		| Created
----------------------------------------------------------------------------- */
#ifndef __DTCHELP_H__
#define __DTCHELP_H__


//---------------------------------------------------------
//		ALL INCLUDE FILES GO HERE
//---------------------------------------------------------
#include <windows.h>


//---------------------------------------------------------
// typedefs
//---------------------------------------------------------
typedef HRESULT  (STDAPIVCALLTYPE * DTC_GET_TRANSACTION_MANAGER)(LPTSTR  pszHost,
									LPTSTR	pszTmName,
									/* in */ REFIID rid,
									/* in */ DWORD	dwReserved1,
									/* in */ WORD	wcbReserved2,
									/* in */ void FAR * pvReserved2,
									/*out */ void** ppvObject )	;

//---------------------------------------------------------
//			Function Prototypes
//---------------------------------------------------------
EXTERN_C
{
	DTC_GET_TRANSACTION_MANAGER	__cdecl LoadDtcHelper (void);
	HMODULE __cdecl GetDtcLocaleResourceHandle(void);
}


//---------------------------------------------------------
//			ALL ERRORS GO HERE
//---------------------------------------------------------


#endif __DTCHELP_H__