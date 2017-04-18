/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Wed Jan 07 23:33:43 1998
 */
/* Compiler settings for RegPCtrs.idl:
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

#ifndef __RegPCtrs_h__
#define __RegPCtrs_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IRegisterPerfmonObject_FWD_DEFINED__
#define __IRegisterPerfmonObject_FWD_DEFINED__
typedef interface IRegisterPerfmonObject IRegisterPerfmonObject;
#endif 	/* __IRegisterPerfmonObject_FWD_DEFINED__ */


#ifndef __RegisterPerfmonObject_FWD_DEFINED__
#define __RegisterPerfmonObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class RegisterPerfmonObject RegisterPerfmonObject;
#else
typedef struct RegisterPerfmonObject RegisterPerfmonObject;
#endif /* __cplusplus */

#endif 	/* __RegisterPerfmonObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IRegisterPerfmonObject_INTERFACE_DEFINED__
#define __IRegisterPerfmonObject_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRegisterPerfmonObject
 * at Wed Jan 07 23:33:43 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IRegisterPerfmonObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0166BEA2-87E2-11D1-8DB5-204C4F4F5020")
    IRegisterPerfmonObject : public IDispatch
    {
    public:
        virtual /* [id][helpstring] */ HRESULT STDMETHODCALLTYPE Register( 
            /* [in] */ BSTR appName,
            /* [in] */ BSTR collectionGUID) = 0;
        
        virtual /* [id][helpstring] */ HRESULT STDMETHODCALLTYPE Unregister( 
            /* [in] */ BSTR appName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRegisterPerfmonObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRegisterPerfmonObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRegisterPerfmonObject __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRegisterPerfmonObject __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRegisterPerfmonObject __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRegisterPerfmonObject __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRegisterPerfmonObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRegisterPerfmonObject __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Register )( 
            IRegisterPerfmonObject __RPC_FAR * This,
            /* [in] */ BSTR appName,
            /* [in] */ BSTR collectionGUID);
        
        /* [id][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Unregister )( 
            IRegisterPerfmonObject __RPC_FAR * This,
            /* [in] */ BSTR appName);
        
        END_INTERFACE
    } IRegisterPerfmonObjectVtbl;

    interface IRegisterPerfmonObject
    {
        CONST_VTBL struct IRegisterPerfmonObjectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRegisterPerfmonObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRegisterPerfmonObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRegisterPerfmonObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRegisterPerfmonObject_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRegisterPerfmonObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRegisterPerfmonObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRegisterPerfmonObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRegisterPerfmonObject_Register(This,appName,collectionGUID)	\
    (This)->lpVtbl -> Register(This,appName,collectionGUID)

#define IRegisterPerfmonObject_Unregister(This,appName)	\
    (This)->lpVtbl -> Unregister(This,appName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][helpstring] */ HRESULT STDMETHODCALLTYPE IRegisterPerfmonObject_Register_Proxy( 
    IRegisterPerfmonObject __RPC_FAR * This,
    /* [in] */ BSTR appName,
    /* [in] */ BSTR collectionGUID);


void __RPC_STUB IRegisterPerfmonObject_Register_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][helpstring] */ HRESULT STDMETHODCALLTYPE IRegisterPerfmonObject_Unregister_Proxy( 
    IRegisterPerfmonObject __RPC_FAR * This,
    /* [in] */ BSTR appName);


void __RPC_STUB IRegisterPerfmonObject_Unregister_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRegisterPerfmonObject_INTERFACE_DEFINED__ */



#ifndef __REGPCTRSLib_LIBRARY_DEFINED__
#define __REGPCTRSLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: REGPCTRSLib
 * at Wed Jan 07 23:33:43 1998
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_REGPCTRSLib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_RegisterPerfmonObject;

class DECLSPEC_UUID("8F2BBC80-1257-11D1-9F91-400004491341")
RegisterPerfmonObject;
#endif
#endif /* __REGPCTRSLib_LIBRARY_DEFINED__ */

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
