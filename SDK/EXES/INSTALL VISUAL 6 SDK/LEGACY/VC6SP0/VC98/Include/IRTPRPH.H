/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Tue Sep 09 20:18:07 1997
 */
/* Compiler settings for irtprph.idl:
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

#ifndef __irtprph_h__
#define __irtprph_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IRTPRPHFilter_FWD_DEFINED__
#define __IRTPRPHFilter_FWD_DEFINED__
typedef interface IRTPRPHFilter IRTPRPHFilter;
#endif 	/* __IRTPRPHFilter_FWD_DEFINED__ */


#ifndef __IRPHH26XSettings_FWD_DEFINED__
#define __IRPHH26XSettings_FWD_DEFINED__
typedef interface IRPHH26XSettings IRPHH26XSettings;
#endif 	/* __IRPHH26XSettings_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "strmif.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IRTPRPHFilter_INTERFACE_DEFINED__
#define __IRTPRPHFilter_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRTPRPHFilter
 * at Tue Sep 09 20:18:07 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][local][uuid][object] */ 



EXTERN_C const IID IID_IRTPRPHFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D5284680-B680-11d0-9643-00AA00A89C1D")
    IRTPRPHFilter : public IUnknown
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE OverridePayloadType( 
            /* [in] */ BYTE bPayloadType) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetPayloadType( 
            /* [out] */ BYTE __RPC_FAR *lpbPayloadType) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetMediaBufferSize( 
            /* [in] */ DWORD dwMaxMediaBufferSize) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetMediaBufferSize( 
            /* [out] */ LPDWORD lpdwMaxMediaBufferSize) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetOutputPinMediaType( 
            /* [in] */ AM_MEDIA_TYPE __RPC_FAR *lpMediaPinType) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetOutputPinMediaType( 
            /* [out] */ AM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *ppMediaPinType) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetTimeoutDuration( 
            /* [in] */ DWORD dwDejitterTime,
            /* [in] */ DWORD dwLostPacketTime) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetTimeoutDuration( 
            /* [out] */ LPDWORD lpdwDejitterTime,
            /* [out] */ LPDWORD lpdwLostPacketTime) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTPRPHFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTPRPHFilter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTPRPHFilter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTPRPHFilter __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OverridePayloadType )( 
            IRTPRPHFilter __RPC_FAR * This,
            /* [in] */ BYTE bPayloadType);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPayloadType )( 
            IRTPRPHFilter __RPC_FAR * This,
            /* [out] */ BYTE __RPC_FAR *lpbPayloadType);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMediaBufferSize )( 
            IRTPRPHFilter __RPC_FAR * This,
            /* [in] */ DWORD dwMaxMediaBufferSize);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMediaBufferSize )( 
            IRTPRPHFilter __RPC_FAR * This,
            /* [out] */ LPDWORD lpdwMaxMediaBufferSize);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOutputPinMediaType )( 
            IRTPRPHFilter __RPC_FAR * This,
            /* [in] */ AM_MEDIA_TYPE __RPC_FAR *lpMediaPinType);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOutputPinMediaType )( 
            IRTPRPHFilter __RPC_FAR * This,
            /* [out] */ AM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *ppMediaPinType);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTimeoutDuration )( 
            IRTPRPHFilter __RPC_FAR * This,
            /* [in] */ DWORD dwDejitterTime,
            /* [in] */ DWORD dwLostPacketTime);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTimeoutDuration )( 
            IRTPRPHFilter __RPC_FAR * This,
            /* [out] */ LPDWORD lpdwDejitterTime,
            /* [out] */ LPDWORD lpdwLostPacketTime);
        
        END_INTERFACE
    } IRTPRPHFilterVtbl;

    interface IRTPRPHFilter
    {
        CONST_VTBL struct IRTPRPHFilterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTPRPHFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTPRPHFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTPRPHFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTPRPHFilter_OverridePayloadType(This,bPayloadType)	\
    (This)->lpVtbl -> OverridePayloadType(This,bPayloadType)

#define IRTPRPHFilter_GetPayloadType(This,lpbPayloadType)	\
    (This)->lpVtbl -> GetPayloadType(This,lpbPayloadType)

#define IRTPRPHFilter_SetMediaBufferSize(This,dwMaxMediaBufferSize)	\
    (This)->lpVtbl -> SetMediaBufferSize(This,dwMaxMediaBufferSize)

#define IRTPRPHFilter_GetMediaBufferSize(This,lpdwMaxMediaBufferSize)	\
    (This)->lpVtbl -> GetMediaBufferSize(This,lpdwMaxMediaBufferSize)

#define IRTPRPHFilter_SetOutputPinMediaType(This,lpMediaPinType)	\
    (This)->lpVtbl -> SetOutputPinMediaType(This,lpMediaPinType)

#define IRTPRPHFilter_GetOutputPinMediaType(This,ppMediaPinType)	\
    (This)->lpVtbl -> GetOutputPinMediaType(This,ppMediaPinType)

#define IRTPRPHFilter_SetTimeoutDuration(This,dwDejitterTime,dwLostPacketTime)	\
    (This)->lpVtbl -> SetTimeoutDuration(This,dwDejitterTime,dwLostPacketTime)

#define IRTPRPHFilter_GetTimeoutDuration(This,lpdwDejitterTime,lpdwLostPacketTime)	\
    (This)->lpVtbl -> GetTimeoutDuration(This,lpdwDejitterTime,lpdwLostPacketTime)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IRTPRPHFilter_OverridePayloadType_Proxy( 
    IRTPRPHFilter __RPC_FAR * This,
    /* [in] */ BYTE bPayloadType);


void __RPC_STUB IRTPRPHFilter_OverridePayloadType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IRTPRPHFilter_GetPayloadType_Proxy( 
    IRTPRPHFilter __RPC_FAR * This,
    /* [out] */ BYTE __RPC_FAR *lpbPayloadType);


void __RPC_STUB IRTPRPHFilter_GetPayloadType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IRTPRPHFilter_SetMediaBufferSize_Proxy( 
    IRTPRPHFilter __RPC_FAR * This,
    /* [in] */ DWORD dwMaxMediaBufferSize);


void __RPC_STUB IRTPRPHFilter_SetMediaBufferSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IRTPRPHFilter_GetMediaBufferSize_Proxy( 
    IRTPRPHFilter __RPC_FAR * This,
    /* [out] */ LPDWORD lpdwMaxMediaBufferSize);


void __RPC_STUB IRTPRPHFilter_GetMediaBufferSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IRTPRPHFilter_SetOutputPinMediaType_Proxy( 
    IRTPRPHFilter __RPC_FAR * This,
    /* [in] */ AM_MEDIA_TYPE __RPC_FAR *lpMediaPinType);


void __RPC_STUB IRTPRPHFilter_SetOutputPinMediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IRTPRPHFilter_GetOutputPinMediaType_Proxy( 
    IRTPRPHFilter __RPC_FAR * This,
    /* [out] */ AM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *ppMediaPinType);


void __RPC_STUB IRTPRPHFilter_GetOutputPinMediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IRTPRPHFilter_SetTimeoutDuration_Proxy( 
    IRTPRPHFilter __RPC_FAR * This,
    /* [in] */ DWORD dwDejitterTime,
    /* [in] */ DWORD dwLostPacketTime);


void __RPC_STUB IRTPRPHFilter_SetTimeoutDuration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IRTPRPHFilter_GetTimeoutDuration_Proxy( 
    IRTPRPHFilter __RPC_FAR * This,
    /* [out] */ LPDWORD lpdwDejitterTime,
    /* [out] */ LPDWORD lpdwLostPacketTime);


void __RPC_STUB IRTPRPHFilter_GetTimeoutDuration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTPRPHFilter_INTERFACE_DEFINED__ */


#ifndef __IRPHH26XSettings_INTERFACE_DEFINED__
#define __IRPHH26XSettings_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRPHH26XSettings
 * at Tue Sep 09 20:18:07 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][local][uuid][object] */ 



EXTERN_C const IID IID_IRPHH26XSettings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("835A6361-9547-11d0-9643-00AA00A89C1D")
    IRPHH26XSettings : public IUnknown
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetCIF( 
            /* [in] */ BOOL bCIF) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetCIF( 
            /* [out] */ BOOL __RPC_FAR *lpbCIF) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRPHH26XSettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRPHH26XSettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRPHH26XSettings __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRPHH26XSettings __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCIF )( 
            IRPHH26XSettings __RPC_FAR * This,
            /* [in] */ BOOL bCIF);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCIF )( 
            IRPHH26XSettings __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *lpbCIF);
        
        END_INTERFACE
    } IRPHH26XSettingsVtbl;

    interface IRPHH26XSettings
    {
        CONST_VTBL struct IRPHH26XSettingsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRPHH26XSettings_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRPHH26XSettings_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRPHH26XSettings_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRPHH26XSettings_SetCIF(This,bCIF)	\
    (This)->lpVtbl -> SetCIF(This,bCIF)

#define IRPHH26XSettings_GetCIF(This,lpbCIF)	\
    (This)->lpVtbl -> GetCIF(This,lpbCIF)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE IRPHH26XSettings_SetCIF_Proxy( 
    IRPHH26XSettings __RPC_FAR * This,
    /* [in] */ BOOL bCIF);


void __RPC_STUB IRPHH26XSettings_SetCIF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IRPHH26XSettings_GetCIF_Proxy( 
    IRPHH26XSettings __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *lpbCIF);


void __RPC_STUB IRPHH26XSettings_GetCIF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRPHH26XSettings_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_irtprph_0296
 * at Tue Sep 09 20:18:07 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


EXTERN_C const CLSID CLSID_INTEL_RPHH26X;
EXTERN_C const CLSID CLSID_INTEL_RPHAUD;
EXTERN_C const CLSID CLSID_INTEL_RPHGENA;
EXTERN_C const CLSID CLSID_INTEL_RPHGENV;
EXTERN_C const CLSID CLSID_INTEL_RPHAUD_PROPPAGE;
EXTERN_C const CLSID CLSID_INTEL_RPHGENA_PROPPAGE;
EXTERN_C const CLSID CLSID_INTEL_RPHGENV_PROPPAGE;
EXTERN_C const CLSID CLSID_INTEL_RPHH26X_PROPPAGE;
EXTERN_C const CLSID CLSID_INTEL_RPHH26X1_PROPPAGE;


extern RPC_IF_HANDLE __MIDL_itf_irtprph_0296_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_irtprph_0296_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
