/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Nov 03 15:42:56 1997
 */
/* Compiler settings for .\admex.idl:
    Oi (OptLev=i0), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref 
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

#ifndef __admex_h__
#define __admex_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IMSAdminReplication_FWD_DEFINED__
#define __IMSAdminReplication_FWD_DEFINED__
typedef interface IMSAdminReplication IMSAdminReplication;
#endif 	/* __IMSAdminReplication_FWD_DEFINED__ */


#ifndef __IMSAdminCryptoCapabilities_FWD_DEFINED__
#define __IMSAdminCryptoCapabilities_FWD_DEFINED__
typedef interface IMSAdminCryptoCapabilities IMSAdminCryptoCapabilities;
#endif 	/* __IMSAdminCryptoCapabilities_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "objidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_admex_0000
 * at Mon Nov 03 15:42:56 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


/*++
                                                                                
Copyright (c) 1997 Microsoft Corporation
                                                                                
Module Name: admex.h
                                                                                
    Admin Extension Objects Interfaces
                                                                                
--*/
#ifndef _ADMEX_IADM_
#define _ADMEX_IADM_
DEFINE_GUID(IID_IMSAdminReplication, 0xc804d980, 0xebec, 0x11d0, 0xa6, 0xa0, 0x0,0xa0, 0xc9, 0x22, 0xe7, 0x52);
DEFINE_GUID(IID_IMSAdminCryptoCapabilities, 0x78b64540, 0xf26d, 0x11d0, 0xa6, 0xa3, 0x0,0xa0, 0xc9, 0x22, 0xe7, 0x52);
DEFINE_GUID(CLSID_MSCryptoAdmEx, 0x9f0bd3a0, 0xec01, 0x11d0, 0xa6, 0xa0, 0x0,0xa0, 0xc9, 0x22, 0xe7, 0x52);
/*                                                                              
The Replication Interface                                                              
*/                                                                              


extern RPC_IF_HANDLE __MIDL_itf_admex_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_admex_0000_v0_0_s_ifspec;

#ifndef __IMSAdminReplication_INTERFACE_DEFINED__
#define __IMSAdminReplication_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMSAdminReplication
 * at Mon Nov 03 15:42:56 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IMSAdminReplication;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("c804d980-ebec-11d0-a6a0-00a0c922e752")
    IMSAdminReplication : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetSignature( 
            /* [in] */ DWORD dwBufferSize,
            /* [size_is][out] */ unsigned char __RPC_FAR *pbBuffer,
            /* [out] */ DWORD __RPC_FAR *pdwMDRequiredBufferSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Propagate( 
            /* [in] */ DWORD dwBufferSize,
            /* [size_is][in] */ unsigned char __RPC_FAR *pszBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Propagate2( 
            /* [in] */ DWORD dwBufferSize,
            /* [size_is][in] */ unsigned char __RPC_FAR *pszBuffer,
            /* [in] */ DWORD dwSignatureMismatch) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Serialize( 
            /* [in] */ DWORD dwBufferSize,
            /* [size_is][out] */ unsigned char __RPC_FAR *pbBuffer,
            /* [out] */ DWORD __RPC_FAR *pdwMDRequiredBufferSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeSerialize( 
            /* [in] */ DWORD dwBufferSize,
            /* [size_is][in] */ unsigned char __RPC_FAR *pbBuffer) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMSAdminReplicationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMSAdminReplication __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMSAdminReplication __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMSAdminReplication __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSignature )( 
            IMSAdminReplication __RPC_FAR * This,
            /* [in] */ DWORD dwBufferSize,
            /* [size_is][out] */ unsigned char __RPC_FAR *pbBuffer,
            /* [out] */ DWORD __RPC_FAR *pdwMDRequiredBufferSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Propagate )( 
            IMSAdminReplication __RPC_FAR * This,
            /* [in] */ DWORD dwBufferSize,
            /* [size_is][in] */ unsigned char __RPC_FAR *pszBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Propagate2 )( 
            IMSAdminReplication __RPC_FAR * This,
            /* [in] */ DWORD dwBufferSize,
            /* [size_is][in] */ unsigned char __RPC_FAR *pszBuffer,
            /* [in] */ DWORD dwSignatureMismatch);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Serialize )( 
            IMSAdminReplication __RPC_FAR * This,
            /* [in] */ DWORD dwBufferSize,
            /* [size_is][out] */ unsigned char __RPC_FAR *pbBuffer,
            /* [out] */ DWORD __RPC_FAR *pdwMDRequiredBufferSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeSerialize )( 
            IMSAdminReplication __RPC_FAR * This,
            /* [in] */ DWORD dwBufferSize,
            /* [size_is][in] */ unsigned char __RPC_FAR *pbBuffer);
        
        END_INTERFACE
    } IMSAdminReplicationVtbl;

    interface IMSAdminReplication
    {
        CONST_VTBL struct IMSAdminReplicationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMSAdminReplication_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMSAdminReplication_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMSAdminReplication_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMSAdminReplication_GetSignature(This,dwBufferSize,pbBuffer,pdwMDRequiredBufferSize)	\
    (This)->lpVtbl -> GetSignature(This,dwBufferSize,pbBuffer,pdwMDRequiredBufferSize)

#define IMSAdminReplication_Propagate(This,dwBufferSize,pszBuffer)	\
    (This)->lpVtbl -> Propagate(This,dwBufferSize,pszBuffer)

#define IMSAdminReplication_Propagate2(This,dwBufferSize,pszBuffer,dwSignatureMismatch)	\
    (This)->lpVtbl -> Propagate2(This,dwBufferSize,pszBuffer,dwSignatureMismatch)

#define IMSAdminReplication_Serialize(This,dwBufferSize,pbBuffer,pdwMDRequiredBufferSize)	\
    (This)->lpVtbl -> Serialize(This,dwBufferSize,pbBuffer,pdwMDRequiredBufferSize)

#define IMSAdminReplication_DeSerialize(This,dwBufferSize,pbBuffer)	\
    (This)->lpVtbl -> DeSerialize(This,dwBufferSize,pbBuffer)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMSAdminReplication_GetSignature_Proxy( 
    IMSAdminReplication __RPC_FAR * This,
    /* [in] */ DWORD dwBufferSize,
    /* [size_is][out] */ unsigned char __RPC_FAR *pbBuffer,
    /* [out] */ DWORD __RPC_FAR *pdwMDRequiredBufferSize);


void __RPC_STUB IMSAdminReplication_GetSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMSAdminReplication_Propagate_Proxy( 
    IMSAdminReplication __RPC_FAR * This,
    /* [in] */ DWORD dwBufferSize,
    /* [size_is][in] */ unsigned char __RPC_FAR *pszBuffer);


void __RPC_STUB IMSAdminReplication_Propagate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMSAdminReplication_Propagate2_Proxy( 
    IMSAdminReplication __RPC_FAR * This,
    /* [in] */ DWORD dwBufferSize,
    /* [size_is][in] */ unsigned char __RPC_FAR *pszBuffer,
    /* [in] */ DWORD dwSignatureMismatch);


void __RPC_STUB IMSAdminReplication_Propagate2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMSAdminReplication_Serialize_Proxy( 
    IMSAdminReplication __RPC_FAR * This,
    /* [in] */ DWORD dwBufferSize,
    /* [size_is][out] */ unsigned char __RPC_FAR *pbBuffer,
    /* [out] */ DWORD __RPC_FAR *pdwMDRequiredBufferSize);


void __RPC_STUB IMSAdminReplication_Serialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMSAdminReplication_DeSerialize_Proxy( 
    IMSAdminReplication __RPC_FAR * This,
    /* [in] */ DWORD dwBufferSize,
    /* [size_is][in] */ unsigned char __RPC_FAR *pbBuffer);


void __RPC_STUB IMSAdminReplication_DeSerialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMSAdminReplication_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_admex_0213
 * at Mon Nov 03 15:42:56 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


/*                                                                              
The Crypto capabilities Interface                                                              
*/                                                                              


extern RPC_IF_HANDLE __MIDL_itf_admex_0213_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_admex_0213_v0_0_s_ifspec;

#ifndef __IMSAdminCryptoCapabilities_INTERFACE_DEFINED__
#define __IMSAdminCryptoCapabilities_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMSAdminCryptoCapabilities
 * at Mon Nov 03 15:42:56 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IMSAdminCryptoCapabilities;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("78b64540-f26d-11d0-a6a3-00a0c922e752")
    IMSAdminCryptoCapabilities : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetProtocols( 
            /* [in] */ DWORD dwBufferSize,
            /* [size_is][out] */ unsigned char __RPC_FAR *pbBuffer,
            /* [out] */ DWORD __RPC_FAR *pdwMDRequiredBufferSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaximumCipherStrength( 
            /* [out] */ LPDWORD pdwMaximumCipherStrength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRootCertificates( 
            /* [in] */ DWORD dwBufferSize,
            /* [size_is][out] */ unsigned char __RPC_FAR *pbBuffer,
            /* [out] */ DWORD __RPC_FAR *pdwMDRequiredBufferSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSupportedAlgs( 
            /* [in] */ DWORD dwBufferSize,
            /* [size_is][out] */ DWORD __RPC_FAR *pbBuffer,
            /* [out] */ DWORD __RPC_FAR *pdwMDRequiredBufferSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCAList( 
            /* [in] */ DWORD dwBufferSize,
            /* [size_is][in] */ unsigned char __RPC_FAR *pbBuffer) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMSAdminCryptoCapabilitiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMSAdminCryptoCapabilities __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMSAdminCryptoCapabilities __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMSAdminCryptoCapabilities __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProtocols )( 
            IMSAdminCryptoCapabilities __RPC_FAR * This,
            /* [in] */ DWORD dwBufferSize,
            /* [size_is][out] */ unsigned char __RPC_FAR *pbBuffer,
            /* [out] */ DWORD __RPC_FAR *pdwMDRequiredBufferSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaximumCipherStrength )( 
            IMSAdminCryptoCapabilities __RPC_FAR * This,
            /* [out] */ LPDWORD pdwMaximumCipherStrength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRootCertificates )( 
            IMSAdminCryptoCapabilities __RPC_FAR * This,
            /* [in] */ DWORD dwBufferSize,
            /* [size_is][out] */ unsigned char __RPC_FAR *pbBuffer,
            /* [out] */ DWORD __RPC_FAR *pdwMDRequiredBufferSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSupportedAlgs )( 
            IMSAdminCryptoCapabilities __RPC_FAR * This,
            /* [in] */ DWORD dwBufferSize,
            /* [size_is][out] */ DWORD __RPC_FAR *pbBuffer,
            /* [out] */ DWORD __RPC_FAR *pdwMDRequiredBufferSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCAList )( 
            IMSAdminCryptoCapabilities __RPC_FAR * This,
            /* [in] */ DWORD dwBufferSize,
            /* [size_is][in] */ unsigned char __RPC_FAR *pbBuffer);
        
        END_INTERFACE
    } IMSAdminCryptoCapabilitiesVtbl;

    interface IMSAdminCryptoCapabilities
    {
        CONST_VTBL struct IMSAdminCryptoCapabilitiesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMSAdminCryptoCapabilities_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMSAdminCryptoCapabilities_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMSAdminCryptoCapabilities_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMSAdminCryptoCapabilities_GetProtocols(This,dwBufferSize,pbBuffer,pdwMDRequiredBufferSize)	\
    (This)->lpVtbl -> GetProtocols(This,dwBufferSize,pbBuffer,pdwMDRequiredBufferSize)

#define IMSAdminCryptoCapabilities_GetMaximumCipherStrength(This,pdwMaximumCipherStrength)	\
    (This)->lpVtbl -> GetMaximumCipherStrength(This,pdwMaximumCipherStrength)

#define IMSAdminCryptoCapabilities_GetRootCertificates(This,dwBufferSize,pbBuffer,pdwMDRequiredBufferSize)	\
    (This)->lpVtbl -> GetRootCertificates(This,dwBufferSize,pbBuffer,pdwMDRequiredBufferSize)

#define IMSAdminCryptoCapabilities_GetSupportedAlgs(This,dwBufferSize,pbBuffer,pdwMDRequiredBufferSize)	\
    (This)->lpVtbl -> GetSupportedAlgs(This,dwBufferSize,pbBuffer,pdwMDRequiredBufferSize)

#define IMSAdminCryptoCapabilities_SetCAList(This,dwBufferSize,pbBuffer)	\
    (This)->lpVtbl -> SetCAList(This,dwBufferSize,pbBuffer)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMSAdminCryptoCapabilities_GetProtocols_Proxy( 
    IMSAdminCryptoCapabilities __RPC_FAR * This,
    /* [in] */ DWORD dwBufferSize,
    /* [size_is][out] */ unsigned char __RPC_FAR *pbBuffer,
    /* [out] */ DWORD __RPC_FAR *pdwMDRequiredBufferSize);


void __RPC_STUB IMSAdminCryptoCapabilities_GetProtocols_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMSAdminCryptoCapabilities_GetMaximumCipherStrength_Proxy( 
    IMSAdminCryptoCapabilities __RPC_FAR * This,
    /* [out] */ LPDWORD pdwMaximumCipherStrength);


void __RPC_STUB IMSAdminCryptoCapabilities_GetMaximumCipherStrength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMSAdminCryptoCapabilities_GetRootCertificates_Proxy( 
    IMSAdminCryptoCapabilities __RPC_FAR * This,
    /* [in] */ DWORD dwBufferSize,
    /* [size_is][out] */ unsigned char __RPC_FAR *pbBuffer,
    /* [out] */ DWORD __RPC_FAR *pdwMDRequiredBufferSize);


void __RPC_STUB IMSAdminCryptoCapabilities_GetRootCertificates_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMSAdminCryptoCapabilities_GetSupportedAlgs_Proxy( 
    IMSAdminCryptoCapabilities __RPC_FAR * This,
    /* [in] */ DWORD dwBufferSize,
    /* [size_is][out] */ DWORD __RPC_FAR *pbBuffer,
    /* [out] */ DWORD __RPC_FAR *pdwMDRequiredBufferSize);


void __RPC_STUB IMSAdminCryptoCapabilities_GetSupportedAlgs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMSAdminCryptoCapabilities_SetCAList_Proxy( 
    IMSAdminCryptoCapabilities __RPC_FAR * This,
    /* [in] */ DWORD dwBufferSize,
    /* [size_is][in] */ unsigned char __RPC_FAR *pbBuffer);


void __RPC_STUB IMSAdminCryptoCapabilities_SetCAList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMSAdminCryptoCapabilities_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_admex_0214
 * at Mon Nov 03 15:42:56 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


#endif


extern RPC_IF_HANDLE __MIDL_itf_admex_0214_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_admex_0214_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
