/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Wed Feb 11 11:48:29 1998
 */
/* Compiler settings for Connect.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __Connect_h__
#define __Connect_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IRandom_FWD_DEFINED__
#define __IRandom_FWD_DEFINED__
typedef interface IRandom IRandom;
#endif 	/* __IRandom_FWD_DEFINED__ */


#ifndef __IRandomEvent_FWD_DEFINED__
#define __IRandomEvent_FWD_DEFINED__
typedef interface IRandomEvent IRandomEvent;
#endif 	/* __IRandomEvent_FWD_DEFINED__ */


#ifndef __CoRandom_FWD_DEFINED__
#define __CoRandom_FWD_DEFINED__

#ifdef __cplusplus
typedef class CoRandom CoRandom;
#else
typedef struct CoRandom CoRandom;
#endif /* __cplusplus */

#endif 	/* __CoRandom_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IRandom_INTERFACE_DEFINED__
#define __IRandom_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRandom
 * at Wed Feb 11 11:48:29 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IRandom;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CCE84211-DB31-11CF-9D75-00A0C90391D3")
    IRandom : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Start( 
            /* [retval][out] */ long __RPC_FAR *pnID) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Stop( 
            /* [in] */ long nID) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE StopAll( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRandomVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRandom __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRandom __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRandom __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRandom __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRandom __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRandom __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRandom __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Start )( 
            IRandom __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pnID);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Stop )( 
            IRandom __RPC_FAR * This,
            /* [in] */ long nID);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopAll )( 
            IRandom __RPC_FAR * This);
        
        END_INTERFACE
    } IRandomVtbl;

    interface IRandom
    {
        CONST_VTBL struct IRandomVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRandom_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRandom_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRandom_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRandom_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRandom_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRandom_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRandom_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRandom_get_Start(This,pnID)	\
    (This)->lpVtbl -> get_Start(This,pnID)

#define IRandom_put_Stop(This,nID)	\
    (This)->lpVtbl -> put_Stop(This,nID)

#define IRandom_StopAll(This)	\
    (This)->lpVtbl -> StopAll(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IRandom_get_Start_Proxy( 
    IRandom __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pnID);


void __RPC_STUB IRandom_get_Start_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IRandom_put_Stop_Proxy( 
    IRandom __RPC_FAR * This,
    /* [in] */ long nID);


void __RPC_STUB IRandom_put_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IRandom_StopAll_Proxy( 
    IRandom __RPC_FAR * This);


void __RPC_STUB IRandom_StopAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRandom_INTERFACE_DEFINED__ */


#ifndef __IRandomEvent_INTERFACE_DEFINED__
#define __IRandomEvent_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRandomEvent
 * at Wed Feb 11 11:48:29 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IRandomEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CCE84212-DB31-11CF-9D75-00A0C90391D3")
    IRandomEvent : public IDispatch
    {
    public:
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Fire( 
            /* [in] */ long nID) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ID( 
            /* [in] */ int n) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRandomEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRandomEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRandomEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRandomEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRandomEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRandomEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRandomEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRandomEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Fire )( 
            IRandomEvent __RPC_FAR * This,
            /* [in] */ long nID);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ID )( 
            IRandomEvent __RPC_FAR * This,
            /* [in] */ int n);
        
        END_INTERFACE
    } IRandomEventVtbl;

    interface IRandomEvent
    {
        CONST_VTBL struct IRandomEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRandomEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRandomEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRandomEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRandomEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRandomEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRandomEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRandomEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRandomEvent_put_Fire(This,nID)	\
    (This)->lpVtbl -> put_Fire(This,nID)

#define IRandomEvent_put_ID(This,n)	\
    (This)->lpVtbl -> put_ID(This,n)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput][id] */ HRESULT STDMETHODCALLTYPE IRandomEvent_put_Fire_Proxy( 
    IRandomEvent __RPC_FAR * This,
    /* [in] */ long nID);


void __RPC_STUB IRandomEvent_put_Fire_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IRandomEvent_put_ID_Proxy( 
    IRandomEvent __RPC_FAR * This,
    /* [in] */ int n);


void __RPC_STUB IRandomEvent_put_ID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRandomEvent_INTERFACE_DEFINED__ */



#ifndef __CONNECTLib_LIBRARY_DEFINED__
#define __CONNECTLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: CONNECTLib
 * at Wed Feb 11 11:48:29 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_CONNECTLib;

EXTERN_C const CLSID CLSID_CoRandom;

#ifdef __cplusplus

class DECLSPEC_UUID("CCE84215-DB31-11CF-9D75-00A0C90391D3")
CoRandom;
#endif
#endif /* __CONNECTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
