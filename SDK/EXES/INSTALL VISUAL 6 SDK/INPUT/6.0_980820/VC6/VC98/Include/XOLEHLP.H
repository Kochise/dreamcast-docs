/* ----------------------------------------------------------------------------
Microsoft	D.T.C (Distributed Transaction Coordinator)

(c)	1995	Microsoft Corporation.	All Rights Reserved


@module		XOLEHLP.H	|
		// contains DTC helper APIs used by SQL Server and application clients
		// to obtain the transaction manager
-------------------------------------------------------------------------------
@rev	0	|	13-Mar-1995	|	GaganC	|	Created
----------------------------------------------------------------------------- */

#ifndef __XOLEHLP__H__
#define __XOLEHLP__H__


//----------------------------------------
//	All defines and constants go here
//----------------------------------------
#define EXPORTAPI __declspec( dllexport )HRESULT

//----------------------------------------
//	All function prototypes go here
//----------------------------------------

//This API should be used to obtain an IUnknown or a ITransactionDispenser
//interface from the Microsoft Distributed Transaction Coordinator's proxy.
//Typically, a NULL is passed for the host name and the TM Name. In which 
//case the MS DTC on the same host is contacted and the interface provided
//for it.
EXPORTAPI __cdecl DtcGetTransactionManager( char *  pszHost,
									char *	pszTmName,
									/* in */ REFIID rid,
								    /* in */ DWORD	dwReserved1,
								    /* in */ WORD	wcbReserved2,
								    /* in */ void FAR * pvReserved2,
									/*out */ void** ppvObject
									)	;
EXTERN_C EXPORTAPI __cdecl DtcGetTransactionManagerC
									(	char *  pszHost,
										char *	pszTmName,
										/* in */ REFIID rid,
										/* in */ DWORD	dwReserved1,
										/* in */ WORD	wcbReserved2,
										/* in */ void FAR * pvReserved2,
										/*out */ void** ppvObject
									);

//----------------------------------

#ifndef EXTERN_GUID
#define EXTERN_GUID(g,l1,s1,s2,c1,c2,c3,c4,c5,c6,c7,c8) DEFINE_GUID(g,l1,s1,s2,c1,c2,c3,c4,c5,c6,c7,c8)
#endif

///////////////////////////////////////////////////////////////////////////////////////////////
//
// Define a CLSID that can be used to obtain a transaction manager instance via CoCreateInstance;
// this is an alternate to using DtcGetTransactionManager. 
//
// CLSID_MSDtcTransactionManager = {5B18AB61-091D-11d1-97DF-00C04FB9618A}
//
EXTERN_GUID(CLSID_MSDtcTransactionManager, 0x5b18ab61, 0x91d, 0x11d1, 0x97, 0xdf, 0x0, 0xc0, 0x4f, 0xb9, 0x61, 0x8a);

///////////////////////////////////////////////////////////////////////////////////////////////
//
// Define a CLSID that can be used with CoCreateInstance to instantiate a vanilla transaction
// object with the local transaction manager. It's equivalent to doing 
//
//  pTransactionDispenser->BeginTransaction(NULL, ISOLATIONLEVEL_UNSPECIFIED, ISOFLAG_RETAIN_DONTCARE, NULL, &ptx);
//
// CLSID_MSDtcTransaction = {39F8D76B-0928-11d1-97DF-00C04FB9618A}
//
EXTERN_GUID(CLSID_MSDtcTransaction, 0x39f8d76b, 0x928, 0x11d1, 0x97, 0xdf, 0x0, 0xc0, 0x4f, 0xb9, 0x61, 0x8a);

///////////////////////////////////////////////////////////////////////////////////////////////


#endif // __XOLEHLP__H__
