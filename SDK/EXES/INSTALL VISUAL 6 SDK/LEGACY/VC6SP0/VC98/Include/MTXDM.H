/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Thu Sep 11 16:03:06 1997
 */
/* Compiler settings for mtxdm.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"
#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __mtxdm_h__
#define __mtxdm_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDispenserManager_FWD_DEFINED__
#define __IDispenserManager_FWD_DEFINED__
typedef interface IDispenserManager IDispenserManager;
#endif 	/* __IDispenserManager_FWD_DEFINED__ */


#ifndef __IHolder_FWD_DEFINED__
#define __IHolder_FWD_DEFINED__
typedef interface IHolder IHolder;
#endif 	/* __IHolder_FWD_DEFINED__ */


#ifndef __IDispenserDriver_FWD_DEFINED__
#define __IDispenserDriver_FWD_DEFINED__
typedef interface IDispenserDriver IDispenserDriver;
#endif 	/* __IDispenserDriver_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_mtxdm_0000
 * at Thu Sep 11 16:03:06 1997
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


// -----------------------------------------------------------------------	
// mtxdm.h  -- Microsoft Transaction Server Resource Dispenser Interfaces				
//																			
// This file provides the prototypes for the APIs and COM interfaces			
// used by Microsoft Transaction Server Resource Dispensers.													
//																			
// Microsoft Transaction Server 2.0												
// Copyright (c) 1996-1997 Microsoft Corporation.  All Rights Reserved.		
// -----------------------------------------------------------------------	
 
#ifndef DECLSPEC_UUID
#if _MSC_VER >= 1100
#define DECLSPEC_UUID(x)    __declspec(uuid(x))
#else
#define DECLSPEC_UUID(x)
#endif
#endif
typedef DWORD RESTYPID;

typedef DWORD RESID;

typedef LPOLESTR SRESID;

typedef LPCOLESTR constSRESID;

typedef DWORD RESOURCERATING;

typedef long TIMEINSECS;

typedef DWORD INSTID;

typedef DWORD TRANSID;



//
// Error Codes
//
#define MTXDM_E_ENLISTRESOURCEFAILED 0x8004E100 // return from EnlistResource, is then returned by AllocResource
 
//
// GetDispenserManager
// A Dispenser calls this API to get a reference to DispenserManager.
//
__declspec(dllimport) HRESULT __cdecl GetDispenserManager(IDispenserManager**);
 
//
// IDispenserManager
// Implemented by Dispenser Manager, called by all Dispensers.
//


extern RPC_IF_HANDLE __MIDL_itf_mtxdm_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mtxdm_0000_v0_0_s_ifspec;

#ifndef __IDispenserManager_INTERFACE_DEFINED__
#define __IDispenserManager_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDispenserManager
 * at Thu Sep 11 16:03:06 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][uuid][object] */ 



EXTERN_C const IID IID_IDispenserManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("5cb31e10-2b5f-11cf-be10-00aa00a2fa25")
    IDispenserManager : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RegisterDispenser( 
            /* [in] */ IDispenserDriver __RPC_FAR *__MIDL_0015,
            /* [in] */ LPCOLESTR szDispenserName,
            /* [out] */ IHolder __RPC_FAR *__RPC_FAR *__MIDL_0016) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetContext( 
            /* [out] */ INSTID __RPC_FAR *__MIDL_0017,
            /* [out] */ TRANSID __RPC_FAR *__MIDL_0018) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDispenserManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDispenserManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDispenserManager __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDispenserManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterDispenser )( 
            IDispenserManager __RPC_FAR * This,
            /* [in] */ IDispenserDriver __RPC_FAR *__MIDL_0015,
            /* [in] */ LPCOLESTR szDispenserName,
            /* [out] */ IHolder __RPC_FAR *__RPC_FAR *__MIDL_0016);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetContext )( 
            IDispenserManager __RPC_FAR * This,
            /* [out] */ INSTID __RPC_FAR *__MIDL_0017,
            /* [out] */ TRANSID __RPC_FAR *__MIDL_0018);
        
        END_INTERFACE
    } IDispenserManagerVtbl;

    interface IDispenserManager
    {
        CONST_VTBL struct IDispenserManagerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDispenserManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDispenserManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDispenserManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDispenserManager_RegisterDispenser(This,__MIDL_0015,szDispenserName,__MIDL_0016)	\
    (This)->lpVtbl -> RegisterDispenser(This,__MIDL_0015,szDispenserName,__MIDL_0016)

#define IDispenserManager_GetContext(This,__MIDL_0017,__MIDL_0018)	\
    (This)->lpVtbl -> GetContext(This,__MIDL_0017,__MIDL_0018)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDispenserManager_RegisterDispenser_Proxy( 
    IDispenserManager __RPC_FAR * This,
    /* [in] */ IDispenserDriver __RPC_FAR *__MIDL_0015,
    /* [in] */ LPCOLESTR szDispenserName,
    /* [out] */ IHolder __RPC_FAR *__RPC_FAR *__MIDL_0016);


void __RPC_STUB IDispenserManager_RegisterDispenser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDispenserManager_GetContext_Proxy( 
    IDispenserManager __RPC_FAR * This,
    /* [out] */ INSTID __RPC_FAR *__MIDL_0017,
    /* [out] */ TRANSID __RPC_FAR *__MIDL_0018);


void __RPC_STUB IDispenserManager_GetContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDispenserManager_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_mtxdm_0094
 * at Thu Sep 11 16:03:06 1997
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


//
// IHolder
// Implemented by Dispenser Manager, called by one Dispenser.
//


extern RPC_IF_HANDLE __MIDL_itf_mtxdm_0094_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mtxdm_0094_v0_0_s_ifspec;

#ifndef __IHolder_INTERFACE_DEFINED__
#define __IHolder_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IHolder
 * at Thu Sep 11 16:03:06 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][uuid][object] */ 



EXTERN_C const IID IID_IHolder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("bf6a1850-2b45-11cf-be10-00aa00a2fa25")
    IHolder : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AllocResource( 
            /* [in] */ const RESTYPID __MIDL_0019,
            /* [out] */ RESID __RPC_FAR *__MIDL_0020) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FreeResource( 
            /* [in] */ const RESID __MIDL_0021) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TrackResource( 
            /* [in] */ const RESID __MIDL_0022) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TrackResourceS( 
            /* [in] */ constSRESID __MIDL_0023) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UntrackResource( 
            /* [in] */ const RESID __MIDL_0024,
            /* [in] */ const BOOL __MIDL_0025) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UntrackResourceS( 
            /* [in] */ constSRESID __MIDL_0026,
            /* [in] */ const BOOL __MIDL_0027) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RequestDestroyResource( 
            /* [in] */ const RESID __MIDL_0028) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHolderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHolder __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHolder __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHolder __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AllocResource )( 
            IHolder __RPC_FAR * This,
            /* [in] */ const RESTYPID __MIDL_0019,
            /* [out] */ RESID __RPC_FAR *__MIDL_0020);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FreeResource )( 
            IHolder __RPC_FAR * This,
            /* [in] */ const RESID __MIDL_0021);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TrackResource )( 
            IHolder __RPC_FAR * This,
            /* [in] */ const RESID __MIDL_0022);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TrackResourceS )( 
            IHolder __RPC_FAR * This,
            /* [in] */ constSRESID __MIDL_0023);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UntrackResource )( 
            IHolder __RPC_FAR * This,
            /* [in] */ const RESID __MIDL_0024,
            /* [in] */ const BOOL __MIDL_0025);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UntrackResourceS )( 
            IHolder __RPC_FAR * This,
            /* [in] */ constSRESID __MIDL_0026,
            /* [in] */ const BOOL __MIDL_0027);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IHolder __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestDestroyResource )( 
            IHolder __RPC_FAR * This,
            /* [in] */ const RESID __MIDL_0028);
        
        END_INTERFACE
    } IHolderVtbl;

    interface IHolder
    {
        CONST_VTBL struct IHolderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHolder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHolder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHolder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHolder_AllocResource(This,__MIDL_0019,__MIDL_0020)	\
    (This)->lpVtbl -> AllocResource(This,__MIDL_0019,__MIDL_0020)

#define IHolder_FreeResource(This,__MIDL_0021)	\
    (This)->lpVtbl -> FreeResource(This,__MIDL_0021)

#define IHolder_TrackResource(This,__MIDL_0022)	\
    (This)->lpVtbl -> TrackResource(This,__MIDL_0022)

#define IHolder_TrackResourceS(This,__MIDL_0023)	\
    (This)->lpVtbl -> TrackResourceS(This,__MIDL_0023)

#define IHolder_UntrackResource(This,__MIDL_0024,__MIDL_0025)	\
    (This)->lpVtbl -> UntrackResource(This,__MIDL_0024,__MIDL_0025)

#define IHolder_UntrackResourceS(This,__MIDL_0026,__MIDL_0027)	\
    (This)->lpVtbl -> UntrackResourceS(This,__MIDL_0026,__MIDL_0027)

#define IHolder_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define IHolder_RequestDestroyResource(This,__MIDL_0028)	\
    (This)->lpVtbl -> RequestDestroyResource(This,__MIDL_0028)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHolder_AllocResource_Proxy( 
    IHolder __RPC_FAR * This,
    /* [in] */ const RESTYPID __MIDL_0019,
    /* [out] */ RESID __RPC_FAR *__MIDL_0020);


void __RPC_STUB IHolder_AllocResource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHolder_FreeResource_Proxy( 
    IHolder __RPC_FAR * This,
    /* [in] */ const RESID __MIDL_0021);


void __RPC_STUB IHolder_FreeResource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHolder_TrackResource_Proxy( 
    IHolder __RPC_FAR * This,
    /* [in] */ const RESID __MIDL_0022);


void __RPC_STUB IHolder_TrackResource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHolder_TrackResourceS_Proxy( 
    IHolder __RPC_FAR * This,
    /* [in] */ constSRESID __MIDL_0023);


void __RPC_STUB IHolder_TrackResourceS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHolder_UntrackResource_Proxy( 
    IHolder __RPC_FAR * This,
    /* [in] */ const RESID __MIDL_0024,
    /* [in] */ const BOOL __MIDL_0025);


void __RPC_STUB IHolder_UntrackResource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHolder_UntrackResourceS_Proxy( 
    IHolder __RPC_FAR * This,
    /* [in] */ constSRESID __MIDL_0026,
    /* [in] */ const BOOL __MIDL_0027);


void __RPC_STUB IHolder_UntrackResourceS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHolder_Close_Proxy( 
    IHolder __RPC_FAR * This);


void __RPC_STUB IHolder_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IHolder_RequestDestroyResource_Proxy( 
    IHolder __RPC_FAR * This,
    /* [in] */ const RESID __MIDL_0028);


void __RPC_STUB IHolder_RequestDestroyResource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHolder_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_mtxdm_0095
 * at Thu Sep 11 16:03:06 1997
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


//
// IDispenserDriver
// Implemented by a Dispenser, called by Dispenser Manager.
//


extern RPC_IF_HANDLE __MIDL_itf_mtxdm_0095_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mtxdm_0095_v0_0_s_ifspec;

#ifndef __IDispenserDriver_INTERFACE_DEFINED__
#define __IDispenserDriver_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDispenserDriver
 * at Thu Sep 11 16:03:06 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][uuid][object] */ 



EXTERN_C const IID IID_IDispenserDriver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("208b3651-2b48-11cf-be10-00aa00a2fa25")
    IDispenserDriver : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateResource( 
            /* [in] */ const RESTYPID ResTypId,
            /* [out] */ RESID __RPC_FAR *pResId,
            /* [out] */ TIMEINSECS __RPC_FAR *pSecsFreeBeforeDestroy) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RateResource( 
            /* [in] */ const RESTYPID ResTypId,
            /* [in] */ const RESID ResId,
            /* [in] */ const BOOL fRequiresTransactionEnlistment,
            /* [out] */ RESOURCERATING __RPC_FAR *pRating) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnlistResource( 
            /* [in] */ const RESID ResId,
            /* [in] */ const TRANSID TransId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResetResource( 
            /* [in] */ const RESID ResId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DestroyResource( 
            /* [in] */ const RESID ResId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DestroyResourceS( 
            /* [in] */ constSRESID ResId) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDispenserDriverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDispenserDriver __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDispenserDriver __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDispenserDriver __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateResource )( 
            IDispenserDriver __RPC_FAR * This,
            /* [in] */ const RESTYPID ResTypId,
            /* [out] */ RESID __RPC_FAR *pResId,
            /* [out] */ TIMEINSECS __RPC_FAR *pSecsFreeBeforeDestroy);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RateResource )( 
            IDispenserDriver __RPC_FAR * This,
            /* [in] */ const RESTYPID ResTypId,
            /* [in] */ const RESID ResId,
            /* [in] */ const BOOL fRequiresTransactionEnlistment,
            /* [out] */ RESOURCERATING __RPC_FAR *pRating);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnlistResource )( 
            IDispenserDriver __RPC_FAR * This,
            /* [in] */ const RESID ResId,
            /* [in] */ const TRANSID TransId);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetResource )( 
            IDispenserDriver __RPC_FAR * This,
            /* [in] */ const RESID ResId);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DestroyResource )( 
            IDispenserDriver __RPC_FAR * This,
            /* [in] */ const RESID ResId);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DestroyResourceS )( 
            IDispenserDriver __RPC_FAR * This,
            /* [in] */ constSRESID ResId);
        
        END_INTERFACE
    } IDispenserDriverVtbl;

    interface IDispenserDriver
    {
        CONST_VTBL struct IDispenserDriverVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDispenserDriver_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDispenserDriver_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDispenserDriver_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDispenserDriver_CreateResource(This,ResTypId,pResId,pSecsFreeBeforeDestroy)	\
    (This)->lpVtbl -> CreateResource(This,ResTypId,pResId,pSecsFreeBeforeDestroy)

#define IDispenserDriver_RateResource(This,ResTypId,ResId,fRequiresTransactionEnlistment,pRating)	\
    (This)->lpVtbl -> RateResource(This,ResTypId,ResId,fRequiresTransactionEnlistment,pRating)

#define IDispenserDriver_EnlistResource(This,ResId,TransId)	\
    (This)->lpVtbl -> EnlistResource(This,ResId,TransId)

#define IDispenserDriver_ResetResource(This,ResId)	\
    (This)->lpVtbl -> ResetResource(This,ResId)

#define IDispenserDriver_DestroyResource(This,ResId)	\
    (This)->lpVtbl -> DestroyResource(This,ResId)

#define IDispenserDriver_DestroyResourceS(This,ResId)	\
    (This)->lpVtbl -> DestroyResourceS(This,ResId)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDispenserDriver_CreateResource_Proxy( 
    IDispenserDriver __RPC_FAR * This,
    /* [in] */ const RESTYPID ResTypId,
    /* [out] */ RESID __RPC_FAR *pResId,
    /* [out] */ TIMEINSECS __RPC_FAR *pSecsFreeBeforeDestroy);


void __RPC_STUB IDispenserDriver_CreateResource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDispenserDriver_RateResource_Proxy( 
    IDispenserDriver __RPC_FAR * This,
    /* [in] */ const RESTYPID ResTypId,
    /* [in] */ const RESID ResId,
    /* [in] */ const BOOL fRequiresTransactionEnlistment,
    /* [out] */ RESOURCERATING __RPC_FAR *pRating);


void __RPC_STUB IDispenserDriver_RateResource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDispenserDriver_EnlistResource_Proxy( 
    IDispenserDriver __RPC_FAR * This,
    /* [in] */ const RESID ResId,
    /* [in] */ const TRANSID TransId);


void __RPC_STUB IDispenserDriver_EnlistResource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDispenserDriver_ResetResource_Proxy( 
    IDispenserDriver __RPC_FAR * This,
    /* [in] */ const RESID ResId);


void __RPC_STUB IDispenserDriver_ResetResource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDispenserDriver_DestroyResource_Proxy( 
    IDispenserDriver __RPC_FAR * This,
    /* [in] */ const RESID ResId);


void __RPC_STUB IDispenserDriver_DestroyResource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDispenserDriver_DestroyResourceS_Proxy( 
    IDispenserDriver __RPC_FAR * This,
    /* [in] */ constSRESID ResId);


void __RPC_STUB IDispenserDriver_DestroyResourceS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDispenserDriver_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_mtxdm_0096
 * at Thu Sep 11 16:03:06 1997
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


#ifdef USE_UUIDOF_FOR_IID_
#define  IID_IHolder             __uuidof(IIHolder)
#define  IID_IDispenserManager   __uuidof(IDispenserManager)
#define  IID_IDispenserDriver    __uuidof(IDispenserDriver)
#endif


extern RPC_IF_HANDLE __MIDL_itf_mtxdm_0096_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_mtxdm_0096_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
