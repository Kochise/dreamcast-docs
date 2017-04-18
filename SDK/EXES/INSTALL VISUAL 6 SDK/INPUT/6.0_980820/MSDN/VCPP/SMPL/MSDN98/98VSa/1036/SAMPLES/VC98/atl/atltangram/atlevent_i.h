/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.76 */
/* at Mon Dec 08 20:38:21 1997
 */
/* Compiler settings for D:\ATL25\samples\ATLTangram\AtlEvent_i.idl:
	Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
	error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"
#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __AtlEvent_i_h__
#define __AtlEvent_i_h__

#ifdef __cplusplus
extern "C"{
#endif

/* Forward Declarations */

#ifndef __IATLTangramModelEvent_FWD_DEFINED__
#define __IATLTangramModelEvent_FWD_DEFINED__
typedef interface IATLTangramModelEvent IATLTangramModelEvent;
#endif  /* __IATLTangramModelEvent_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * );

#ifndef __IATLTangramModelEvent_INTERFACE_DEFINED__
#define __IATLTangramModelEvent_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IATLTangramModelEvent
 * at Mon Dec 08 20:38:21 1997
 * using MIDL 3.01.76
 ****************************************/
/* [unique][helpstring][uuid][object] */



EXTERN_C const IID IID_IATLTangramModelEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)

	interface DECLSPEC_UUID("4A6E83B0-B0F4-11d0-B69F-00A0C903487A")
	IATLTangramModelEvent : public IUnknown
	{
	public:
		virtual HRESULT STDMETHODCALLTYPE OnModelChange( void) = 0;

	};

#else   /* C style interface */

	typedef struct IATLTangramModelEventVtbl
	{
		BEGIN_INTERFACE

		HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )(
			IATLTangramModelEvent __RPC_FAR * This,
			/* [in] */ REFIID riid,
			/* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )(
			IATLTangramModelEvent __RPC_FAR * This);

		ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )(
			IATLTangramModelEvent __RPC_FAR * This);

		HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnModelChange )(
			IATLTangramModelEvent __RPC_FAR * This);

		END_INTERFACE
	} IATLTangramModelEventVtbl;

	interface IATLTangramModelEvent
	{
		CONST_VTBL struct IATLTangramModelEventVtbl __RPC_FAR *lpVtbl;
	};



#ifdef COBJMACROS


#define IATLTangramModelEvent_QueryInterface(This,riid,ppvObject)   \
	(This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IATLTangramModelEvent_AddRef(This)  \
	(This)->lpVtbl -> AddRef(This)

#define IATLTangramModelEvent_Release(This) \
	(This)->lpVtbl -> Release(This)


#define IATLTangramModelEvent_OnModelChange(This)   \
	(This)->lpVtbl -> OnModelChange(This)

#endif /* COBJMACROS */


#endif  /* C style interface */



HRESULT STDMETHODCALLTYPE IATLTangramModelEvent_OnModelChange_Proxy(
	IATLTangramModelEvent __RPC_FAR * This);


void __RPC_STUB IATLTangramModelEvent_OnModelChange_Stub(
	IRpcStubBuffer *This,
	IRpcChannelBuffer *_pRpcChannelBuffer,
	PRPC_MESSAGE _pRpcMessage,
	DWORD *_pdwStubPhase);



#endif  /* __IATLTangramModelEvent_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
