/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0106 */
/* at Mon Aug 04 19:41:30 1997
 */
/* Compiler settings for certadm.idl:
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

#ifndef __certadm_h__
#define __certadm_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICertAdmin_FWD_DEFINED__
#define __ICertAdmin_FWD_DEFINED__
typedef interface ICertAdmin ICertAdmin;
#endif 	/* __ICertAdmin_FWD_DEFINED__ */


#ifndef __CCertAdmin_FWD_DEFINED__
#define __CCertAdmin_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCertAdmin CCertAdmin;
#else
typedef struct CCertAdmin CCertAdmin;
#endif /* __cplusplus */

#endif 	/* __CCertAdmin_FWD_DEFINED__ */


/* header files for imported files */
#include "wtypes.h"
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_certadm_0000
 * at Mon Aug 04 19:41:30 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [local] */ 


#define	CA_DISP_INCOMPLETE	( 0 )

#define	CA_DISP_ERROR	( 0x1 )

#define	CA_DISP_REVOKED	( 0x2 )

#define	CA_DISP_VALID	( 0x3 )

#define	CA_DISP_INVALID	( 0x4 )

#define	CA_DISP_UNDER_SUBMISSION	( 0x5 )



extern RPC_IF_HANDLE __MIDL_itf_certadm_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_certadm_0000_v0_0_s_ifspec;

#ifndef __ICertAdmin_INTERFACE_DEFINED__
#define __ICertAdmin_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICertAdmin
 * at Mon Aug 04 19:41:30 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ICertAdmin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("34df6950-7fb6-11d0-8817-00a0c903b83c")
    ICertAdmin : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IsValidCertificate( 
            /* [in] */ const BSTR strConfig,
            /* [in] */ const BSTR strSerialNumber,
            /* [retval][out] */ LONG __RPC_FAR *pDisposition) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRevocationReason( 
            /* [retval][out] */ LONG __RPC_FAR *pReason) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RevokeCertificate( 
            /* [in] */ const BSTR strConfig,
            /* [in] */ const BSTR strSerialNumber,
            /* [in] */ LONG Reason,
            /* [in] */ DATE Date) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetRequestAttributes( 
            /* [in] */ const BSTR strConfig,
            /* [in] */ LONG RequestId,
            /* [in] */ const BSTR strAttributes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCertificateExtension( 
            /* [in] */ const BSTR strConfig,
            /* [in] */ LONG RequestId,
            /* [in] */ const BSTR strExtensionName,
            /* [in] */ LONG Type,
            /* [in] */ LONG Flags,
            /* [in] */ const VARIANT __RPC_FAR *pvarValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DenyRequest( 
            /* [in] */ const BSTR strConfig,
            /* [in] */ LONG RequestId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResubmitRequest( 
            /* [in] */ const BSTR strConfig,
            /* [in] */ LONG RequestId,
            /* [retval][out] */ LONG __RPC_FAR *pDisposition) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PublishCRL( 
            /* [in] */ const BSTR strConfig,
            /* [in] */ DATE Date) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCRL( 
            /* [in] */ const BSTR strConfig,
            /* [in] */ LONG Flags,
            /* [retval][out] */ BSTR __RPC_FAR *pstrCRL) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICertAdminVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICertAdmin __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICertAdmin __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICertAdmin __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICertAdmin __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICertAdmin __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICertAdmin __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICertAdmin __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsValidCertificate )( 
            ICertAdmin __RPC_FAR * This,
            /* [in] */ const BSTR strConfig,
            /* [in] */ const BSTR strSerialNumber,
            /* [retval][out] */ LONG __RPC_FAR *pDisposition);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRevocationReason )( 
            ICertAdmin __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pReason);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RevokeCertificate )( 
            ICertAdmin __RPC_FAR * This,
            /* [in] */ const BSTR strConfig,
            /* [in] */ const BSTR strSerialNumber,
            /* [in] */ LONG Reason,
            /* [in] */ DATE Date);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetRequestAttributes )( 
            ICertAdmin __RPC_FAR * This,
            /* [in] */ const BSTR strConfig,
            /* [in] */ LONG RequestId,
            /* [in] */ const BSTR strAttributes);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCertificateExtension )( 
            ICertAdmin __RPC_FAR * This,
            /* [in] */ const BSTR strConfig,
            /* [in] */ LONG RequestId,
            /* [in] */ const BSTR strExtensionName,
            /* [in] */ LONG Type,
            /* [in] */ LONG Flags,
            /* [in] */ const VARIANT __RPC_FAR *pvarValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DenyRequest )( 
            ICertAdmin __RPC_FAR * This,
            /* [in] */ const BSTR strConfig,
            /* [in] */ LONG RequestId);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResubmitRequest )( 
            ICertAdmin __RPC_FAR * This,
            /* [in] */ const BSTR strConfig,
            /* [in] */ LONG RequestId,
            /* [retval][out] */ LONG __RPC_FAR *pDisposition);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PublishCRL )( 
            ICertAdmin __RPC_FAR * This,
            /* [in] */ const BSTR strConfig,
            /* [in] */ DATE Date);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCRL )( 
            ICertAdmin __RPC_FAR * This,
            /* [in] */ const BSTR strConfig,
            /* [in] */ LONG Flags,
            /* [retval][out] */ BSTR __RPC_FAR *pstrCRL);
        
        END_INTERFACE
    } ICertAdminVtbl;

    interface ICertAdmin
    {
        CONST_VTBL struct ICertAdminVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICertAdmin_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICertAdmin_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICertAdmin_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICertAdmin_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICertAdmin_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICertAdmin_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICertAdmin_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICertAdmin_IsValidCertificate(This,strConfig,strSerialNumber,pDisposition)	\
    (This)->lpVtbl -> IsValidCertificate(This,strConfig,strSerialNumber,pDisposition)

#define ICertAdmin_GetRevocationReason(This,pReason)	\
    (This)->lpVtbl -> GetRevocationReason(This,pReason)

#define ICertAdmin_RevokeCertificate(This,strConfig,strSerialNumber,Reason,Date)	\
    (This)->lpVtbl -> RevokeCertificate(This,strConfig,strSerialNumber,Reason,Date)

#define ICertAdmin_SetRequestAttributes(This,strConfig,RequestId,strAttributes)	\
    (This)->lpVtbl -> SetRequestAttributes(This,strConfig,RequestId,strAttributes)

#define ICertAdmin_SetCertificateExtension(This,strConfig,RequestId,strExtensionName,Type,Flags,pvarValue)	\
    (This)->lpVtbl -> SetCertificateExtension(This,strConfig,RequestId,strExtensionName,Type,Flags,pvarValue)

#define ICertAdmin_DenyRequest(This,strConfig,RequestId)	\
    (This)->lpVtbl -> DenyRequest(This,strConfig,RequestId)

#define ICertAdmin_ResubmitRequest(This,strConfig,RequestId,pDisposition)	\
    (This)->lpVtbl -> ResubmitRequest(This,strConfig,RequestId,pDisposition)

#define ICertAdmin_PublishCRL(This,strConfig,Date)	\
    (This)->lpVtbl -> PublishCRL(This,strConfig,Date)

#define ICertAdmin_GetCRL(This,strConfig,Flags,pstrCRL)	\
    (This)->lpVtbl -> GetCRL(This,strConfig,Flags,pstrCRL)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICertAdmin_IsValidCertificate_Proxy( 
    ICertAdmin __RPC_FAR * This,
    /* [in] */ const BSTR strConfig,
    /* [in] */ const BSTR strSerialNumber,
    /* [retval][out] */ LONG __RPC_FAR *pDisposition);


void __RPC_STUB ICertAdmin_IsValidCertificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertAdmin_GetRevocationReason_Proxy( 
    ICertAdmin __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pReason);


void __RPC_STUB ICertAdmin_GetRevocationReason_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertAdmin_RevokeCertificate_Proxy( 
    ICertAdmin __RPC_FAR * This,
    /* [in] */ const BSTR strConfig,
    /* [in] */ const BSTR strSerialNumber,
    /* [in] */ LONG Reason,
    /* [in] */ DATE Date);


void __RPC_STUB ICertAdmin_RevokeCertificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertAdmin_SetRequestAttributes_Proxy( 
    ICertAdmin __RPC_FAR * This,
    /* [in] */ const BSTR strConfig,
    /* [in] */ LONG RequestId,
    /* [in] */ const BSTR strAttributes);


void __RPC_STUB ICertAdmin_SetRequestAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertAdmin_SetCertificateExtension_Proxy( 
    ICertAdmin __RPC_FAR * This,
    /* [in] */ const BSTR strConfig,
    /* [in] */ LONG RequestId,
    /* [in] */ const BSTR strExtensionName,
    /* [in] */ LONG Type,
    /* [in] */ LONG Flags,
    /* [in] */ const VARIANT __RPC_FAR *pvarValue);


void __RPC_STUB ICertAdmin_SetCertificateExtension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertAdmin_DenyRequest_Proxy( 
    ICertAdmin __RPC_FAR * This,
    /* [in] */ const BSTR strConfig,
    /* [in] */ LONG RequestId);


void __RPC_STUB ICertAdmin_DenyRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertAdmin_ResubmitRequest_Proxy( 
    ICertAdmin __RPC_FAR * This,
    /* [in] */ const BSTR strConfig,
    /* [in] */ LONG RequestId,
    /* [retval][out] */ LONG __RPC_FAR *pDisposition);


void __RPC_STUB ICertAdmin_ResubmitRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertAdmin_PublishCRL_Proxy( 
    ICertAdmin __RPC_FAR * This,
    /* [in] */ const BSTR strConfig,
    /* [in] */ DATE Date);


void __RPC_STUB ICertAdmin_PublishCRL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertAdmin_GetCRL_Proxy( 
    ICertAdmin __RPC_FAR * This,
    /* [in] */ const BSTR strConfig,
    /* [in] */ LONG Flags,
    /* [retval][out] */ BSTR __RPC_FAR *pstrCRL);


void __RPC_STUB ICertAdmin_GetCRL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICertAdmin_INTERFACE_DEFINED__ */



#ifndef __CERTADMINLib_LIBRARY_DEFINED__
#define __CERTADMINLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: CERTADMINLib
 * at Mon Aug 04 19:41:30 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_CERTADMINLib;

EXTERN_C const CLSID CLSID_CCertAdmin;

#ifdef __cplusplus

class DECLSPEC_UUID("37eabaf0-7fb6-11d0-8817-00a0c903b83c")
CCertAdmin;
#endif
#endif /* __CERTADMINLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
