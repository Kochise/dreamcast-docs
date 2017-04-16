/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Tue Sep 09 20:17:58 1997
 */
/* Compiler settings for amrtpdmx.idl:
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

#ifndef __amrtpdmx_h__
#define __amrtpdmx_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEnumSSRCs_FWD_DEFINED__
#define __IEnumSSRCs_FWD_DEFINED__
typedef interface IEnumSSRCs IEnumSSRCs;
#endif 	/* __IEnumSSRCs_FWD_DEFINED__ */


#ifndef __IRTPDemuxFilter_FWD_DEFINED__
#define __IRTPDemuxFilter_FWD_DEFINED__
typedef interface IRTPDemuxFilter IRTPDemuxFilter;
#endif 	/* __IRTPDemuxFilter_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "strmif.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IEnumSSRCs_INTERFACE_DEFINED__
#define __IEnumSSRCs_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IEnumSSRCs
 * at Tue Sep 09 20:17:58 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IEnumSSRCs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("40CC70E8-6FC4-11d0-9CCF-00A0C9081C19")
    IEnumSSRCs : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG cSSRCs,
            /* [size_is][out] */ DWORD __RPC_FAR *pdwSSRCs,
            /* [out] */ ULONG __RPC_FAR *pcFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG cSSRCs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumSSRCs __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumSSRCsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumSSRCs __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumSSRCs __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumSSRCs __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumSSRCs __RPC_FAR * This,
            /* [in] */ ULONG cSSRCs,
            /* [size_is][out] */ DWORD __RPC_FAR *pdwSSRCs,
            /* [out] */ ULONG __RPC_FAR *pcFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumSSRCs __RPC_FAR * This,
            /* [in] */ ULONG cSSRCs);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumSSRCs __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumSSRCs __RPC_FAR * This,
            /* [out] */ IEnumSSRCs __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IEnumSSRCsVtbl;

    interface IEnumSSRCs
    {
        CONST_VTBL struct IEnumSSRCsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumSSRCs_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumSSRCs_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumSSRCs_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumSSRCs_Next(This,cSSRCs,pdwSSRCs,pcFetched)	\
    (This)->lpVtbl -> Next(This,cSSRCs,pdwSSRCs,pcFetched)

#define IEnumSSRCs_Skip(This,cSSRCs)	\
    (This)->lpVtbl -> Skip(This,cSSRCs)

#define IEnumSSRCs_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumSSRCs_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumSSRCs_Next_Proxy( 
    IEnumSSRCs __RPC_FAR * This,
    /* [in] */ ULONG cSSRCs,
    /* [size_is][out] */ DWORD __RPC_FAR *pdwSSRCs,
    /* [out] */ ULONG __RPC_FAR *pcFetched);


void __RPC_STUB IEnumSSRCs_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumSSRCs_Skip_Proxy( 
    IEnumSSRCs __RPC_FAR * This,
    /* [in] */ ULONG cSSRCs);


void __RPC_STUB IEnumSSRCs_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumSSRCs_Reset_Proxy( 
    IEnumSSRCs __RPC_FAR * This);


void __RPC_STUB IEnumSSRCs_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumSSRCs_Clone_Proxy( 
    IEnumSSRCs __RPC_FAR * This,
    /* [out] */ IEnumSSRCs __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IEnumSSRCs_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumSSRCs_INTERFACE_DEFINED__ */


#ifndef __IRTPDemuxFilter_INTERFACE_DEFINED__
#define __IRTPDemuxFilter_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRTPDemuxFilter
 * at Tue Sep 09 20:17:58 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][uuid][object] */ 



EXTERN_C const IID IID_IRTPDemuxFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("38F64CF0-A084-11d0-9CF3-00A0C9081C19")
    IRTPDemuxFilter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE EnumSSRCs( 
            /* [out] */ IEnumSSRCs __RPC_FAR *__RPC_FAR *ppIEnumSSRCs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPinInfo( 
            /* [in] */ IPin __RPC_FAR *pIPin,
            /* [out] */ DWORD __RPC_FAR *pdwSSRC,
            /* [out] */ BYTE __RPC_FAR *pbPT,
            /* [out] */ BOOL __RPC_FAR *pbAutoMapping,
            /* [out] */ DWORD __RPC_FAR *pdwTimeout) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSSRCInfo( 
            /* [in] */ DWORD dwSSRC,
            /* [out] */ BYTE __RPC_FAR *pbPT,
            /* [out] */ IPin __RPC_FAR *__RPC_FAR *ppIPin) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MapSSRCToPin( 
            /* [in] */ DWORD dwSSRC,
            /* [in] */ IPin __RPC_FAR *pIPin) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPinCount( 
            /* [in] */ DWORD dwPinCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPinTypeInfo( 
            /* [in] */ IPin __RPC_FAR *pIPin,
            /* [in] */ BYTE bPT,
            /* [in] */ GUID gMinorType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPinMode( 
            /* [in] */ IPin __RPC_FAR *pIPin,
            /* [in] */ BOOL bAutomatic) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPinSourceTimeout( 
            /* [in] */ IPin __RPC_FAR *pIPin,
            /* [in] */ DWORD dwMilliseconds) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnmapPin( 
            /* [in] */ IPin __RPC_FAR *pIPin,
            /* [out] */ DWORD __RPC_FAR *pdwSSRC) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnmapSSRC( 
            /* [in] */ DWORD dwSSRC,
            /* [out] */ IPin __RPC_FAR *__RPC_FAR *ppIPin) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRTPDemuxFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRTPDemuxFilter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRTPDemuxFilter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRTPDemuxFilter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumSSRCs )( 
            IRTPDemuxFilter __RPC_FAR * This,
            /* [out] */ IEnumSSRCs __RPC_FAR *__RPC_FAR *ppIEnumSSRCs);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPinInfo )( 
            IRTPDemuxFilter __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *pIPin,
            /* [out] */ DWORD __RPC_FAR *pdwSSRC,
            /* [out] */ BYTE __RPC_FAR *pbPT,
            /* [out] */ BOOL __RPC_FAR *pbAutoMapping,
            /* [out] */ DWORD __RPC_FAR *pdwTimeout);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSSRCInfo )( 
            IRTPDemuxFilter __RPC_FAR * This,
            /* [in] */ DWORD dwSSRC,
            /* [out] */ BYTE __RPC_FAR *pbPT,
            /* [out] */ IPin __RPC_FAR *__RPC_FAR *ppIPin);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MapSSRCToPin )( 
            IRTPDemuxFilter __RPC_FAR * This,
            /* [in] */ DWORD dwSSRC,
            /* [in] */ IPin __RPC_FAR *pIPin);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPinCount )( 
            IRTPDemuxFilter __RPC_FAR * This,
            /* [in] */ DWORD dwPinCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPinTypeInfo )( 
            IRTPDemuxFilter __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *pIPin,
            /* [in] */ BYTE bPT,
            /* [in] */ GUID gMinorType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPinMode )( 
            IRTPDemuxFilter __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *pIPin,
            /* [in] */ BOOL bAutomatic);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPinSourceTimeout )( 
            IRTPDemuxFilter __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *pIPin,
            /* [in] */ DWORD dwMilliseconds);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnmapPin )( 
            IRTPDemuxFilter __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *pIPin,
            /* [out] */ DWORD __RPC_FAR *pdwSSRC);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnmapSSRC )( 
            IRTPDemuxFilter __RPC_FAR * This,
            /* [in] */ DWORD dwSSRC,
            /* [out] */ IPin __RPC_FAR *__RPC_FAR *ppIPin);
        
        END_INTERFACE
    } IRTPDemuxFilterVtbl;

    interface IRTPDemuxFilter
    {
        CONST_VTBL struct IRTPDemuxFilterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRTPDemuxFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRTPDemuxFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRTPDemuxFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRTPDemuxFilter_EnumSSRCs(This,ppIEnumSSRCs)	\
    (This)->lpVtbl -> EnumSSRCs(This,ppIEnumSSRCs)

#define IRTPDemuxFilter_GetPinInfo(This,pIPin,pdwSSRC,pbPT,pbAutoMapping,pdwTimeout)	\
    (This)->lpVtbl -> GetPinInfo(This,pIPin,pdwSSRC,pbPT,pbAutoMapping,pdwTimeout)

#define IRTPDemuxFilter_GetSSRCInfo(This,dwSSRC,pbPT,ppIPin)	\
    (This)->lpVtbl -> GetSSRCInfo(This,dwSSRC,pbPT,ppIPin)

#define IRTPDemuxFilter_MapSSRCToPin(This,dwSSRC,pIPin)	\
    (This)->lpVtbl -> MapSSRCToPin(This,dwSSRC,pIPin)

#define IRTPDemuxFilter_SetPinCount(This,dwPinCount)	\
    (This)->lpVtbl -> SetPinCount(This,dwPinCount)

#define IRTPDemuxFilter_SetPinTypeInfo(This,pIPin,bPT,gMinorType)	\
    (This)->lpVtbl -> SetPinTypeInfo(This,pIPin,bPT,gMinorType)

#define IRTPDemuxFilter_SetPinMode(This,pIPin,bAutomatic)	\
    (This)->lpVtbl -> SetPinMode(This,pIPin,bAutomatic)

#define IRTPDemuxFilter_SetPinSourceTimeout(This,pIPin,dwMilliseconds)	\
    (This)->lpVtbl -> SetPinSourceTimeout(This,pIPin,dwMilliseconds)

#define IRTPDemuxFilter_UnmapPin(This,pIPin,pdwSSRC)	\
    (This)->lpVtbl -> UnmapPin(This,pIPin,pdwSSRC)

#define IRTPDemuxFilter_UnmapSSRC(This,dwSSRC,ppIPin)	\
    (This)->lpVtbl -> UnmapSSRC(This,dwSSRC,ppIPin)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRTPDemuxFilter_EnumSSRCs_Proxy( 
    IRTPDemuxFilter __RPC_FAR * This,
    /* [out] */ IEnumSSRCs __RPC_FAR *__RPC_FAR *ppIEnumSSRCs);


void __RPC_STUB IRTPDemuxFilter_EnumSSRCs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTPDemuxFilter_GetPinInfo_Proxy( 
    IRTPDemuxFilter __RPC_FAR * This,
    /* [in] */ IPin __RPC_FAR *pIPin,
    /* [out] */ DWORD __RPC_FAR *pdwSSRC,
    /* [out] */ BYTE __RPC_FAR *pbPT,
    /* [out] */ BOOL __RPC_FAR *pbAutoMapping,
    /* [out] */ DWORD __RPC_FAR *pdwTimeout);


void __RPC_STUB IRTPDemuxFilter_GetPinInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTPDemuxFilter_GetSSRCInfo_Proxy( 
    IRTPDemuxFilter __RPC_FAR * This,
    /* [in] */ DWORD dwSSRC,
    /* [out] */ BYTE __RPC_FAR *pbPT,
    /* [out] */ IPin __RPC_FAR *__RPC_FAR *ppIPin);


void __RPC_STUB IRTPDemuxFilter_GetSSRCInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTPDemuxFilter_MapSSRCToPin_Proxy( 
    IRTPDemuxFilter __RPC_FAR * This,
    /* [in] */ DWORD dwSSRC,
    /* [in] */ IPin __RPC_FAR *pIPin);


void __RPC_STUB IRTPDemuxFilter_MapSSRCToPin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTPDemuxFilter_SetPinCount_Proxy( 
    IRTPDemuxFilter __RPC_FAR * This,
    /* [in] */ DWORD dwPinCount);


void __RPC_STUB IRTPDemuxFilter_SetPinCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTPDemuxFilter_SetPinTypeInfo_Proxy( 
    IRTPDemuxFilter __RPC_FAR * This,
    /* [in] */ IPin __RPC_FAR *pIPin,
    /* [in] */ BYTE bPT,
    /* [in] */ GUID gMinorType);


void __RPC_STUB IRTPDemuxFilter_SetPinTypeInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTPDemuxFilter_SetPinMode_Proxy( 
    IRTPDemuxFilter __RPC_FAR * This,
    /* [in] */ IPin __RPC_FAR *pIPin,
    /* [in] */ BOOL bAutomatic);


void __RPC_STUB IRTPDemuxFilter_SetPinMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTPDemuxFilter_SetPinSourceTimeout_Proxy( 
    IRTPDemuxFilter __RPC_FAR * This,
    /* [in] */ IPin __RPC_FAR *pIPin,
    /* [in] */ DWORD dwMilliseconds);


void __RPC_STUB IRTPDemuxFilter_SetPinSourceTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTPDemuxFilter_UnmapPin_Proxy( 
    IRTPDemuxFilter __RPC_FAR * This,
    /* [in] */ IPin __RPC_FAR *pIPin,
    /* [out] */ DWORD __RPC_FAR *pdwSSRC);


void __RPC_STUB IRTPDemuxFilter_UnmapPin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRTPDemuxFilter_UnmapSSRC_Proxy( 
    IRTPDemuxFilter __RPC_FAR * This,
    /* [in] */ DWORD dwSSRC,
    /* [out] */ IPin __RPC_FAR *__RPC_FAR *ppIPin);


void __RPC_STUB IRTPDemuxFilter_UnmapSSRC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRTPDemuxFilter_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_amrtpdmx_0296
 * at Tue Sep 09 20:17:58 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


EXTERN_C const CLSID CLSID_IntelRTPDemux;
EXTERN_C const CLSID CLSID_IntelRTPDemuxPropertyPage;


extern RPC_IF_HANDLE __MIDL_itf_amrtpdmx_0296_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_amrtpdmx_0296_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
