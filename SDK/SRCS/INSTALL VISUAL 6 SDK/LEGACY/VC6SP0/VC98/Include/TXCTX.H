/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Sat Nov 08 05:10:50 1997
 */
/* Compiler settings for txctx.idl:
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

#ifndef __txctx_h__
#define __txctx_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ITransactionContextEx_FWD_DEFINED__
#define __ITransactionContextEx_FWD_DEFINED__
typedef interface ITransactionContextEx ITransactionContextEx;
#endif 	/* __ITransactionContextEx_FWD_DEFINED__ */


#ifndef __ITransactionContext_FWD_DEFINED__
#define __ITransactionContext_FWD_DEFINED__
typedef interface ITransactionContext ITransactionContext;
#endif 	/* __ITransactionContext_FWD_DEFINED__ */


#ifndef __TransactionContext_FWD_DEFINED__
#define __TransactionContext_FWD_DEFINED__

#ifdef __cplusplus
typedef class TransactionContext TransactionContext;
#else
typedef struct TransactionContext TransactionContext;
#endif /* __cplusplus */

#endif 	/* __TransactionContext_FWD_DEFINED__ */


#ifndef __TransactionContextEx_FWD_DEFINED__
#define __TransactionContextEx_FWD_DEFINED__

#ifdef __cplusplus
typedef class TransactionContextEx TransactionContextEx;
#else
typedef struct TransactionContextEx TransactionContextEx;
#endif /* __cplusplus */

#endif 	/* __TransactionContextEx_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_txctx_0000
 * at Sat Nov 08 05:10:50 1997
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


// -----------------------------------------------------------------------	
// txctx.h  -- Microsoft Transaction Server Transaction Context Interfaces	
//																			
// This file provides the COM interfaces for the Microsoft Transaction		
// Server Transaction Context Object.										
//																			
// Microsoft Transaction Server 2.0											
// Copyright (c) 1996-1997 Microsoft Corporation.  All Rights Reserved.		
// -----------------------------------------------------------------------	


extern RPC_IF_HANDLE __MIDL_itf_txctx_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_txctx_0000_v0_0_s_ifspec;

#ifndef __ITransactionContextEx_INTERFACE_DEFINED__
#define __ITransactionContextEx_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITransactionContextEx
 * at Sat Nov 08 05:10:50 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpcontext][helpstring][uuid][object] */ 



EXTERN_C const IID IID_ITransactionContextEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("7999FC22-D3C6-11CF-ACAB-00A024A55AEF")
    ITransactionContextEx : public IUnknown
    {
    public:
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE CreateInstance( 
            /* [in] */ REFCLSID cid,
            /* [in] */ REFIID rid,
            /* [iid_is][retval][out] */ void __RPC_FAR *__RPC_FAR *pObject) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Commit( void) = 0;
        
        virtual /* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE Abort( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITransactionContextExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITransactionContextEx __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITransactionContextEx __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITransactionContextEx __RPC_FAR * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateInstance )( 
            ITransactionContextEx __RPC_FAR * This,
            /* [in] */ REFCLSID cid,
            /* [in] */ REFIID rid,
            /* [iid_is][retval][out] */ void __RPC_FAR *__RPC_FAR *pObject);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Commit )( 
            ITransactionContextEx __RPC_FAR * This);
        
        /* [helpstring][helpcontext] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Abort )( 
            ITransactionContextEx __RPC_FAR * This);
        
        END_INTERFACE
    } ITransactionContextExVtbl;

    interface ITransactionContextEx
    {
        CONST_VTBL struct ITransactionContextExVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITransactionContextEx_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITransactionContextEx_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITransactionContextEx_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITransactionContextEx_CreateInstance(This,cid,rid,pObject)	\
    (This)->lpVtbl -> CreateInstance(This,cid,rid,pObject)

#define ITransactionContextEx_Commit(This)	\
    (This)->lpVtbl -> Commit(This)

#define ITransactionContextEx_Abort(This)	\
    (This)->lpVtbl -> Abort(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ITransactionContextEx_CreateInstance_Proxy( 
    ITransactionContextEx __RPC_FAR * This,
    /* [in] */ REFCLSID cid,
    /* [in] */ REFIID rid,
    /* [iid_is][retval][out] */ void __RPC_FAR *__RPC_FAR *pObject);


void __RPC_STUB ITransactionContextEx_CreateInstance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ITransactionContextEx_Commit_Proxy( 
    ITransactionContextEx __RPC_FAR * This);


void __RPC_STUB ITransactionContextEx_Commit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext] */ HRESULT STDMETHODCALLTYPE ITransactionContextEx_Abort_Proxy( 
    ITransactionContextEx __RPC_FAR * This);


void __RPC_STUB ITransactionContextEx_Abort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITransactionContextEx_INTERFACE_DEFINED__ */



#ifndef __TxCTx_LIBRARY_DEFINED__
#define __TxCTx_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: TxCTx
 * at Sat Nov 08 05:10:50 1997
 * using MIDL 3.01.75
 ****************************************/
/* [helpfile][helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_TxCTx;

#ifndef __ITransactionContext_INTERFACE_DEFINED__
#define __ITransactionContext_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITransactionContext
 * at Sat Nov 08 05:10:50 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ITransactionContext;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("7999FC21-D3C6-11CF-ACAB-00A024A55AEF")
    ITransactionContext : public IDispatch
    {
    public:
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE CreateInstance( 
            /* [in] */ BSTR pszProgId,
            /* [retval][out] */ VARIANT __RPC_FAR *pObject) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Commit( void) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Abort( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITransactionContextVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITransactionContext __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITransactionContext __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITransactionContext __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITransactionContext __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITransactionContext __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITransactionContext __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITransactionContext __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateInstance )( 
            ITransactionContext __RPC_FAR * This,
            /* [in] */ BSTR pszProgId,
            /* [retval][out] */ VARIANT __RPC_FAR *pObject);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Commit )( 
            ITransactionContext __RPC_FAR * This);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Abort )( 
            ITransactionContext __RPC_FAR * This);
        
        END_INTERFACE
    } ITransactionContextVtbl;

    interface ITransactionContext
    {
        CONST_VTBL struct ITransactionContextVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITransactionContext_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITransactionContext_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITransactionContext_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITransactionContext_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITransactionContext_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITransactionContext_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITransactionContext_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITransactionContext_CreateInstance(This,pszProgId,pObject)	\
    (This)->lpVtbl -> CreateInstance(This,pszProgId,pObject)

#define ITransactionContext_Commit(This)	\
    (This)->lpVtbl -> Commit(This)

#define ITransactionContext_Abort(This)	\
    (This)->lpVtbl -> Abort(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE ITransactionContext_CreateInstance_Proxy( 
    ITransactionContext __RPC_FAR * This,
    /* [in] */ BSTR pszProgId,
    /* [retval][out] */ VARIANT __RPC_FAR *pObject);


void __RPC_STUB ITransactionContext_CreateInstance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE ITransactionContext_Commit_Proxy( 
    ITransactionContext __RPC_FAR * This);


void __RPC_STUB ITransactionContext_Commit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE ITransactionContext_Abort_Proxy( 
    ITransactionContext __RPC_FAR * This);


void __RPC_STUB ITransactionContext_Abort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITransactionContext_INTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_TransactionContext;

class DECLSPEC_UUID("7999FC25-D3C6-11CF-ACAB-00A024A55AEF")
TransactionContext;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_TransactionContextEx;

class DECLSPEC_UUID("5cb66670-d3d4-11cf-acab-00a024a55aef")
TransactionContextEx;
#endif
#endif /* __TxCTx_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
