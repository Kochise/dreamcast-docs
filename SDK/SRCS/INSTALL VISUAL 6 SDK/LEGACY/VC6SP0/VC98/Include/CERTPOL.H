/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0106 */
/* at Mon Aug 04 19:41:40 1997
 */
/* Compiler settings for certpol.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
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

#ifndef __certpol_h__
#define __certpol_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICertPolicy_FWD_DEFINED__
#define __ICertPolicy_FWD_DEFINED__
typedef interface ICertPolicy ICertPolicy;
#endif 	/* __ICertPolicy_FWD_DEFINED__ */


#ifndef __CCertPolicy_FWD_DEFINED__
#define __CCertPolicy_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCertPolicy CCertPolicy;
#else
typedef struct CCertPolicy CCertPolicy;
#endif /* __cplusplus */

#endif 	/* __CCertPolicy_FWD_DEFINED__ */


/* header files for imported files */
#include "wtypes.h"
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ICertPolicy_INTERFACE_DEFINED__
#define __ICertPolicy_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICertPolicy
 * at Mon Aug 04 19:41:40 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ICertPolicy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("38bb5a00-7636-11d0-b413-00a0c91bbf8c")
    ICertPolicy : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ const BSTR strConfig) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE VerifyRequest( 
            /* [in] */ const BSTR strConfig,
            /* [in] */ LONG Context,
            /* [in] */ LONG bNewRequest,
            /* [in] */ LONG Flags,
            /* [retval][out] */ LONG __RPC_FAR *pDisposition) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDescription( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrDescription) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ShutDown( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICertPolicyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICertPolicy __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICertPolicy __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICertPolicy __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICertPolicy __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICertPolicy __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICertPolicy __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICertPolicy __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            ICertPolicy __RPC_FAR * This,
            /* [in] */ const BSTR strConfig);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VerifyRequest )( 
            ICertPolicy __RPC_FAR * This,
            /* [in] */ const BSTR strConfig,
            /* [in] */ LONG Context,
            /* [in] */ LONG bNewRequest,
            /* [in] */ LONG Flags,
            /* [retval][out] */ LONG __RPC_FAR *pDisposition);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDescription )( 
            ICertPolicy __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrDescription);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShutDown )( 
            ICertPolicy __RPC_FAR * This);
        
        END_INTERFACE
    } ICertPolicyVtbl;

    interface ICertPolicy
    {
        CONST_VTBL struct ICertPolicyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICertPolicy_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICertPolicy_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICertPolicy_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICertPolicy_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICertPolicy_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICertPolicy_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICertPolicy_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICertPolicy_Initialize(This,strConfig)	\
    (This)->lpVtbl -> Initialize(This,strConfig)

#define ICertPolicy_VerifyRequest(This,strConfig,Context,bNewRequest,Flags,pDisposition)	\
    (This)->lpVtbl -> VerifyRequest(This,strConfig,Context,bNewRequest,Flags,pDisposition)

#define ICertPolicy_GetDescription(This,pstrDescription)	\
    (This)->lpVtbl -> GetDescription(This,pstrDescription)

#define ICertPolicy_ShutDown(This)	\
    (This)->lpVtbl -> ShutDown(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICertPolicy_Initialize_Proxy( 
    ICertPolicy __RPC_FAR * This,
    /* [in] */ const BSTR strConfig);


void __RPC_STUB ICertPolicy_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertPolicy_VerifyRequest_Proxy( 
    ICertPolicy __RPC_FAR * This,
    /* [in] */ const BSTR strConfig,
    /* [in] */ LONG Context,
    /* [in] */ LONG bNewRequest,
    /* [in] */ LONG Flags,
    /* [retval][out] */ LONG __RPC_FAR *pDisposition);


void __RPC_STUB ICertPolicy_VerifyRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertPolicy_GetDescription_Proxy( 
    ICertPolicy __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrDescription);


void __RPC_STUB ICertPolicy_GetDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertPolicy_ShutDown_Proxy( 
    ICertPolicy __RPC_FAR * This);


void __RPC_STUB ICertPolicy_ShutDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICertPolicy_INTERFACE_DEFINED__ */



#ifndef __CERTPOLICYLib_LIBRARY_DEFINED__
#define __CERTPOLICYLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: CERTPOLICYLib
 * at Mon Aug 04 19:41:40 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_CERTPOLICYLib;

EXTERN_C const CLSID CLSID_CCertPolicy;

#ifdef __cplusplus

class DECLSPEC_UUID("3a428a00-7636-11d0-b413-00a0c91bbf8c")
CCertPolicy;
#endif
#endif /* __CERTPOLICYLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
