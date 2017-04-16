/* ----------------------------------------------------------------------------
Microsoft	D.T.C (Distributed Transaction Coordinator)

(c)	1996	Microsoft Corporation.	All Rights Reserved

@doc

@module		RMFacade.h	|

			Contains helper API and interfaces for RMFacade which faciliates
			OLE TX to XA protocol mapping

-------------------------------------------------------------------------------
@rev 	0 	| 23rd-Nov-1996	|	GaganC		| Created with API
----------------------------------------------------------------------------- */
#ifndef __RMFACADE_H__
#define __RMFACADE_H__


//---------------------------------------------------------
//		ALL INCLUDE FILES GO HERE
//---------------------------------------------------------
#include <windows.h>
#include "transact.h"
#include "txcoord.h"
#include "xa.h"


//---------------------------------------------------------
//			Typedefs
//---------------------------------------------------------
typedef enum _XactStatus
	{
		XACT_STATUS_NONE = 0,		//should never be encountered
		XACT_STATUS_ABORTED,
		XACT_STATUS_COMMITTED,		
		XACT_STATUS_NOT_MY_TRANSACTION,
		XACT_STATUS_TIMEOUT
	} XACT_STATUS;



//---------------------------------------------------------
//			Function Prototypes
//---------------------------------------------------------

extern "C"
{
	HRESULT __stdcall GetDtcTxToXaMapperHelper
									(
									 /* [in] */		REFIID riid, 
									 /* [out] */	void ** ppv
									);

	HRESULT	__stdcall GetXARMClient 
									(
									 /* [in] */		REFIID riid, 
									 /* [out] */	void ** ppv
									);
} //end all 'C' language API




//---------------------------------------------------------
//			ALL Errors Go Here
//---------------------------------------------------------
#define E_FAILED_TO_LOAD_DLL		0x8004D201L



//---------------------------------------------------------
//			All	Interface IIDs go here 
//---------------------------------------------------------

//IID_IResourceManagerFacade {EE5FF7B1-4572-11d0-9452-00A0C905416E}
DEFINE_GUID(IID_IResourceManagerFacade, 
			0xee5ff7b1,
			0x4572,
			0x11d0,
			0x94, 0x52, 0x0, 0xa0, 0xc9, 0x5, 0x41, 0x6e);


//IID_IResourceManagerClient {EE5FF7B2-4572-11d0-9452-00A0C905416E}
DEFINE_GUID(IID_IResourceManagerClient, 
			0xee5ff7b2,
			0x4572,
			0x11d0,
			0x94, 0x52, 0x0, 0xa0, 0xc9, 0x5, 0x41, 0x6e);


//---------------------------------------------------------
//			All	Interfaces go here 
//---------------------------------------------------------


/* ----------------------------------------------------------------------------
@interface <IResourceManagerFacade>

	Implemented by DTC Proxy for use by the client libraries of the XA RMs so 
	they can get the OLE TX to XA Mapping
---------------------------------------------------------------------------- */
#undef INTERFACE
#define INTERFACE IResourceManagerFacade

DECLARE_INTERFACE_ (IResourceManagerFacade, IUnknown)
{
	// IUnknown interface methods:
	STDMETHOD	(QueryInterface)	(THIS_ REFIID riid, LPVOID FAR * ppv) PURE;
 	STDMETHOD_	(ULONG, AddRef)		(THIS) 	PURE;
 	STDMETHOD_	(ULONG, Release)	(THIS) 	PURE;

	//methods for this interface
	STDMETHOD (CreateNewResourceManager) 
								(
									/*[in]*/ char * pszDSN,
									/*[in]*/ char * pszClientDllName,
									/* [in-out] */ DWORD * pdwRMCookie
								) PURE;

	STDMETHOD (EnlistOnTransaction)
								(
									/* [in] */ DWORD dwRMCookie,
									/* [in] */ ITransaction * pITransaction,
									/* [in-out] */ XID * pxid,
									/* [in] */ ITransactionResource * pITransRes
								) PURE;

	STDMETHOD (FindTransactionOutcome)
								(
									/* [in] */ DWORD dwRMCookie,
									/* [in] */ XID * pxid,
									/* [in-out] */ XACT_STATUS * pXactStatus
								) PURE;

	STDMETHOD (RecoveryComplete)
								(
									/* [in] */ DWORD dwRMCookie
								) PURE;

}; //end interface IResourceManagerFacade



/* ----------------------------------------------------------------------------
@interface <IID_IResourceManagerClient>

	Implemented by the client libraries of the XA RMs which are providing the
	OLE TX to XA Mapping. This interface will be used by DTC to drive recovery
---------------------------------------------------------------------------- */
#undef INTERFACE
#define INTERFACE IID_IResourceManagerClient

DECLARE_INTERFACE_ (IID_IResourceManagerClient, IUnknown)
{
	// IUnknown interface methods:
	STDMETHOD	(QueryInterface)	(THIS_ REFIID riid, LPVOID FAR * ppv) PURE;
 	STDMETHOD_	(ULONG, AddRef)		(THIS) 	PURE;
 	STDMETHOD_	(ULONG, Release)	(THIS) 	PURE;

	STDMETHOD (DoRecovery)
								(
									/* [in] */ DWORD dwRMCookie,
									/* [in] */ char * pszDSN
								) PURE;

}; //end interface IResourceManagerClient



#endif __RMFACADE_H__