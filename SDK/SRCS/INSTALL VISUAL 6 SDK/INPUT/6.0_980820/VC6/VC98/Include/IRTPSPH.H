/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Tue Sep 09 20:18:10 1997
 */
/* Compiler settings for irtpsph.idl:
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

#ifndef __irtpsph_h__
#define __irtpsph_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IRTPSPHFilter_FWD_DEFINED__
#define __IRTPSPHFilter_FWD_DEFINED__
typedef interface IRTPSPHFilter IRTPSPHFilter;
#endif 	/* __IRTPSPHFilter_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "strmif.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IRTPSPHFilter_INTERFACE_DEFINED__
#define __IRTPSPHFilter_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRTPSPHFilter
 * at Tue Sep 09 20:18:10 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][local][uuid][object] */ 



EXTERN_C const IID IID_IRTPSPHFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D5284681-B680-11d0-9643-00AA00A89C1D")
    IRTPSPHFilter : public IUnknown
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE OverridePayloadType( 
            /* [in] */ BYTE bPayloadType) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetPayloadType( 
            /* [out] */ BYTE __RPC_FAR *lpbPayloadType) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetMaxPacketSize( 
            /* [in] */ DWORD dwMaxPacketSize) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetMaxPacketSize( 
            /* [out] */ LPDWORD lpdwMaxPacketSize) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetOutputPinMinorType( 
            /* [in] */ GUID gMinorType) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetOutputPinMinorType( 
            /* [out] */ GUID __RPC_FAR *lpgMinorType) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetInputPinMediaType( 
            /* [in] */ AM_MEDIA_TYPE __RPC_FAR *lpMediaPinType) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetInputPinMediaType( 
            /* [out] */ AM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *ppMediaPinType) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTPSPHFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTPSPHFilter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTPSPHFilter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTPSPHFilter __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OverridePayloadType )( 
            IRTPSPHFilter __RPC_FAR * This,
            /* [in] */ BYTE bPayloadType);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPayloadType )( 
            IRTPSPHFilter __RPC_FAR * This,
            /* [out] */ BYTE __RPC_FAR *lpbPayloadType);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaxPacketSize )( 
            IRTPSPHFilter __RPC_FAR * This,
            /* [in] */ DWORD dwMaxPacketSize);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxPacketSize )( 
            IRTPSPHFilter __RPC_FAR * This,
            /* [out] */ LPDWORD lpdwMaxPacketSize);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOutputPinMinorType )( 
            IRTPSPHFilter __RPC_FAR * This,
            /* [in] */ GUID gMinorType);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOutputPinMinorType )( 
            IRTPSPHFilter __RPC_FAR * This,
            /* [out] */ GUID __RPC_FAR *lpgMinorType);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInputPinMediaType )( 
            IRTPSPHFilter __RPC_FAR * This,
            /* [in] */ AM_MEDIA_TYPE __RPC_FAR *lpMediaPinType);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInputPinMediaType )( 
            IRTPSPHFilter __RPC_FAR * This,
            /* [out] */ AM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *ppMediaPinType);
        
        END_INTERFACE
    } IRTPSPHFilterVtbl;

    interface IRTPSPHFilter
    {
        CONST_VTBL struct IRTPSPHFilterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTPSPHFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTPSPHFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTPSPHFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTPSPHFilter_OverridePayloadType(This,bPayloadType)	\
    (This)->lpVtbl -> OverridePayloadType(This,bPayloadType)

#define IRTPSPHFilter_GetPayloadType(This,lpbPayloadType)	\
    (This)->lpVtbl -> GetPayloadType(This,lpbPayloadType)

#define IRTPSPHFilter_SetMaxPacketSize(This,dwMaxPacketSize)	\
    (This)->lpVtbl -> SetMaxPacketSize(This,dwMaxPacketSize)

#define IRTPSPHFilter_GetMaxPacketSize(This,lpdwMaxPacketSize)	\
    (This)->lpVtbl -> GetMaxPacketSize(This,lpdwMaxPacketSize)

#define IRTPSPHFilter_SetOutputPinMinorType(This,gMinorType)	\
    (This)->lpVtbl -> SetOutputPinMinorType(This,gMinorType)

#define IRTPSPHFilter_GetOutputPinMinorType(This,lpgMinorType)	\
    (This)->lpVtbl -> GetOutputPinMinorType(This,lpgMinorType)

#define IRTPSPHFilter_SetInputPinMediaType(This,lpMediaPinType)	\
    (This)->lpVtbl -> SetInputPinMediaType(This,lpMediaPinType)

#define IRTPSPHFilter_GetInputPinMediaType(This,ppMediaPinType)	\
    (This)->lpVtbl -> GetInputPinMediaType(This,ppMediaPinType)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IRTPSPHFilter_OverridePayloadType_Proxy( 
    IRTPSPHFilter __RPC_FAR * This,
    /* [in] */ BYTE bPayloadType);


void __RPC_STUB IRTPSPHFilter_OverridePayloadType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IRTPSPHFilter_GetPayloadType_Proxy( 
    IRTPSPHFilter __RPC_FAR * This,
    /* [out] */ BYTE __RPC_FAR *lpbPayloadType);


void __RPC_STUB IRTPSPHFilter_GetPayloadType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IRTPSPHFilter_SetMaxPacketSize_Proxy( 
    IRTPSPHFilter __RPC_FAR * This,
    /* [in] */ DWORD dwMaxPacketSize);


void __RPC_STUB IRTPSPHFilter_SetMaxPacketSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IRTPSPHFilter_GetMaxPacketSize_Proxy( 
    IRTPSPHFilter __RPC_FAR * This,
    /* [out] */ LPDWORD lpdwMaxPacketSize);


void __RPC_STUB IRTPSPHFilter_GetMaxPacketSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IRTPSPHFilter_SetOutputPinMinorType_Proxy( 
    IRTPSPHFilter __RPC_FAR * This,
    /* [in] */ GUID gMinorType);


void __RPC_STUB IRTPSPHFilter_SetOutputPinMinorType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IRTPSPHFilter_GetOutputPinMinorType_Proxy( 
    IRTPSPHFilter __RPC_FAR * This,
    /* [out] */ GUID __RPC_FAR *lpgMinorType);


void __RPC_STUB IRTPSPHFilter_GetOutputPinMinorType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IRTPSPHFilter_SetInputPinMediaType_Proxy( 
    IRTPSPHFilter __RPC_FAR * This,
    /* [in] */ AM_MEDIA_TYPE __RPC_FAR *lpMediaPinType);


void __RPC_STUB IRTPSPHFilter_SetInputPinMediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IRTPSPHFilter_GetInputPinMediaType_Proxy( 
    IRTPSPHFilter __RPC_FAR * This,
    /* [out] */ AM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *ppMediaPinType);


void __RPC_STUB IRTPSPHFilter_GetInputPinMediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTPSPHFilter_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_irtpsph_0295
 * at Tue Sep 09 20:18:10 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


EXTERN_C const CLSID CLSID_INTEL_SPHH26X;
EXTERN_C const CLSID CLSID_INTEL_SPHAUD;
EXTERN_C const CLSID CLSID_INTEL_SPHGENA;
EXTERN_C const CLSID CLSID_INTEL_SPHGENV;
EXTERN_C const CLSID CLSID_INTEL_SPHAUD_PROPPAGE;
EXTERN_C const CLSID CLSID_INTEL_SPHGENA_PROPPAGE;
EXTERN_C const CLSID CLSID_INTEL_SPHGENV_PROPPAGE;
EXTERN_C const CLSID CLSID_INTEL_SPHH26X_PROPPAGE;


extern RPC_IF_HANDLE __MIDL_itf_irtpsph_0295_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_irtpsph_0295_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
