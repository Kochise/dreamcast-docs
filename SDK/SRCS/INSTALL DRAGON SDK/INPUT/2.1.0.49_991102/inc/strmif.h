/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.02.88 */
/* at Fri Feb 18 03:27:33 2000
 */
/* Compiler settings for .\strmif.idl:
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

#ifndef __strmif_h__
#define __strmif_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IPin_FWD_DEFINED__
#define __IPin_FWD_DEFINED__
typedef interface IPin IPin;
#endif 	/* __IPin_FWD_DEFINED__ */


#ifndef __IEnumPins_FWD_DEFINED__
#define __IEnumPins_FWD_DEFINED__
typedef interface IEnumPins IEnumPins;
#endif 	/* __IEnumPins_FWD_DEFINED__ */


#ifndef __IEnumMediaTypes_FWD_DEFINED__
#define __IEnumMediaTypes_FWD_DEFINED__
typedef interface IEnumMediaTypes IEnumMediaTypes;
#endif 	/* __IEnumMediaTypes_FWD_DEFINED__ */


#ifndef __IFilterGraph_FWD_DEFINED__
#define __IFilterGraph_FWD_DEFINED__
typedef interface IFilterGraph IFilterGraph;
#endif 	/* __IFilterGraph_FWD_DEFINED__ */


#ifndef __IEnumFilters_FWD_DEFINED__
#define __IEnumFilters_FWD_DEFINED__
typedef interface IEnumFilters IEnumFilters;
#endif 	/* __IEnumFilters_FWD_DEFINED__ */


#ifndef __IMediaFilter_FWD_DEFINED__
#define __IMediaFilter_FWD_DEFINED__
typedef interface IMediaFilter IMediaFilter;
#endif 	/* __IMediaFilter_FWD_DEFINED__ */


#ifndef __IBaseFilter_FWD_DEFINED__
#define __IBaseFilter_FWD_DEFINED__
typedef interface IBaseFilter IBaseFilter;
#endif 	/* __IBaseFilter_FWD_DEFINED__ */


#ifndef __IReferenceClock_FWD_DEFINED__
#define __IReferenceClock_FWD_DEFINED__
typedef interface IReferenceClock IReferenceClock;
#endif 	/* __IReferenceClock_FWD_DEFINED__ */


#ifndef __IMediaSample_FWD_DEFINED__
#define __IMediaSample_FWD_DEFINED__
typedef interface IMediaSample IMediaSample;
#endif 	/* __IMediaSample_FWD_DEFINED__ */


#ifndef __IMediaSample2_FWD_DEFINED__
#define __IMediaSample2_FWD_DEFINED__
typedef interface IMediaSample2 IMediaSample2;
#endif 	/* __IMediaSample2_FWD_DEFINED__ */


#ifndef __IMemAllocator_FWD_DEFINED__
#define __IMemAllocator_FWD_DEFINED__
typedef interface IMemAllocator IMemAllocator;
#endif 	/* __IMemAllocator_FWD_DEFINED__ */


#ifndef __IMemAllocator2_FWD_DEFINED__
#define __IMemAllocator2_FWD_DEFINED__
typedef interface IMemAllocator2 IMemAllocator2;
#endif 	/* __IMemAllocator2_FWD_DEFINED__ */


#ifndef __IMemInputPin_FWD_DEFINED__
#define __IMemInputPin_FWD_DEFINED__
typedef interface IMemInputPin IMemInputPin;
#endif 	/* __IMemInputPin_FWD_DEFINED__ */


#ifndef __IMediaSeeking_FWD_DEFINED__
#define __IMediaSeeking_FWD_DEFINED__
typedef interface IMediaSeeking IMediaSeeking;
#endif 	/* __IMediaSeeking_FWD_DEFINED__ */


#ifndef __IEnumRegFilters_FWD_DEFINED__
#define __IEnumRegFilters_FWD_DEFINED__
typedef interface IEnumRegFilters IEnumRegFilters;
#endif 	/* __IEnumRegFilters_FWD_DEFINED__ */


#ifndef __IFilterMapper_FWD_DEFINED__
#define __IFilterMapper_FWD_DEFINED__
typedef interface IFilterMapper IFilterMapper;
#endif 	/* __IFilterMapper_FWD_DEFINED__ */


#ifndef __IQualityControl_FWD_DEFINED__
#define __IQualityControl_FWD_DEFINED__
typedef interface IQualityControl IQualityControl;
#endif 	/* __IQualityControl_FWD_DEFINED__ */


#ifndef __IOverlayNotify_FWD_DEFINED__
#define __IOverlayNotify_FWD_DEFINED__
typedef interface IOverlayNotify IOverlayNotify;
#endif 	/* __IOverlayNotify_FWD_DEFINED__ */


#ifndef __IOverlay_FWD_DEFINED__
#define __IOverlay_FWD_DEFINED__
typedef interface IOverlay IOverlay;
#endif 	/* __IOverlay_FWD_DEFINED__ */


#ifndef __IMediaEventSink_FWD_DEFINED__
#define __IMediaEventSink_FWD_DEFINED__
typedef interface IMediaEventSink IMediaEventSink;
#endif 	/* __IMediaEventSink_FWD_DEFINED__ */


#ifndef __IFileSourceFilter_FWD_DEFINED__
#define __IFileSourceFilter_FWD_DEFINED__
typedef interface IFileSourceFilter IFileSourceFilter;
#endif 	/* __IFileSourceFilter_FWD_DEFINED__ */


#ifndef __IGraphBuilder_FWD_DEFINED__
#define __IGraphBuilder_FWD_DEFINED__
typedef interface IGraphBuilder IGraphBuilder;
#endif 	/* __IGraphBuilder_FWD_DEFINED__ */


#ifndef __IFilterGraph2_FWD_DEFINED__
#define __IFilterGraph2_FWD_DEFINED__
typedef interface IFilterGraph2 IFilterGraph2;
#endif 	/* __IFilterGraph2_FWD_DEFINED__ */


#ifndef __IStreamBuilder_FWD_DEFINED__
#define __IStreamBuilder_FWD_DEFINED__
typedef interface IStreamBuilder IStreamBuilder;
#endif 	/* __IStreamBuilder_FWD_DEFINED__ */


#ifndef __IAsyncReader_FWD_DEFINED__
#define __IAsyncReader_FWD_DEFINED__
typedef interface IAsyncReader IAsyncReader;
#endif 	/* __IAsyncReader_FWD_DEFINED__ */


#ifndef __IGraphVersion_FWD_DEFINED__
#define __IGraphVersion_FWD_DEFINED__
typedef interface IGraphVersion IGraphVersion;
#endif 	/* __IGraphVersion_FWD_DEFINED__ */


#ifndef __IDistributorNotify_FWD_DEFINED__
#define __IDistributorNotify_FWD_DEFINED__
typedef interface IDistributorNotify IDistributorNotify;
#endif 	/* __IDistributorNotify_FWD_DEFINED__ */


#ifndef __IAMStreamControl_FWD_DEFINED__
#define __IAMStreamControl_FWD_DEFINED__
typedef interface IAMStreamControl IAMStreamControl;
#endif 	/* __IAMStreamControl_FWD_DEFINED__ */


#ifndef __ISeekingPassThru_FWD_DEFINED__
#define __ISeekingPassThru_FWD_DEFINED__
typedef interface ISeekingPassThru ISeekingPassThru;
#endif 	/* __ISeekingPassThru_FWD_DEFINED__ */


#ifndef __IAMDevMemoryAllocator_FWD_DEFINED__
#define __IAMDevMemoryAllocator_FWD_DEFINED__
typedef interface IAMDevMemoryAllocator IAMDevMemoryAllocator;
#endif 	/* __IAMDevMemoryAllocator_FWD_DEFINED__ */


#ifndef __IAMDevMemoryControl_FWD_DEFINED__
#define __IAMDevMemoryControl_FWD_DEFINED__
typedef interface IAMDevMemoryControl IAMDevMemoryControl;
#endif 	/* __IAMDevMemoryControl_FWD_DEFINED__ */


#ifndef __IAMStreamSelect_FWD_DEFINED__
#define __IAMStreamSelect_FWD_DEFINED__
typedef interface IAMStreamSelect IAMStreamSelect;
#endif 	/* __IAMStreamSelect_FWD_DEFINED__ */


#ifndef __IVideoCDPlaybackSource_FWD_DEFINED__
#define __IVideoCDPlaybackSource_FWD_DEFINED__
typedef interface IVideoCDPlaybackSource IVideoCDPlaybackSource;
#endif 	/* __IVideoCDPlaybackSource_FWD_DEFINED__ */


#ifndef __IVideoCDPlaybackRendering_FWD_DEFINED__
#define __IVideoCDPlaybackRendering_FWD_DEFINED__
typedef interface IVideoCDPlaybackRendering IVideoCDPlaybackRendering;
#endif 	/* __IVideoCDPlaybackRendering_FWD_DEFINED__ */


#ifndef __IVideoCDManager_FWD_DEFINED__
#define __IVideoCDManager_FWD_DEFINED__
typedef interface IVideoCDManager IVideoCDManager;
#endif 	/* __IVideoCDManager_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "objidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0000
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


#define CHARS_IN_GUID     39
typedef struct  _AMMediaType
    {
    GUID majortype;
    GUID subtype;
    BOOL bFixedSizeSamples;
    BOOL bTemporalCompression;
    ULONG lSampleSize;
    GUID formattype;
    IUnknown __RPC_FAR *pUnk;
    ULONG cbFormat;
    /* [size_is] */ BYTE __RPC_FAR *pbFormat;
    }	AM_MEDIA_TYPE;

typedef 
enum _PinDirection
    {	PINDIR_INPUT	= 0,
	PINDIR_OUTPUT	= PINDIR_INPUT + 1
    }	PIN_DIRECTION;

#define MAX_PIN_NAME     128
#define MAX_FILTER_NAME  128
typedef LONGLONG REFERENCE_TIME;

typedef double REFTIME;

typedef unsigned long HSEMAPHORE;

typedef unsigned long HEVENT;

typedef struct  _AllocatorProperties
    {
    long cBuffers;
    long cbBuffer;
    long cbAlign;
    long cbPrefix;
    }	ALLOCATOR_PROPERTIES;














extern RPC_IF_HANDLE __MIDL_itf_strmif_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0000_v0_0_s_ifspec;

#ifndef __IPin_INTERFACE_DEFINED__
#define __IPin_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IPin
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 


typedef struct  _PinInfo
    {
    IBaseFilter __RPC_FAR *pFilter;
    PIN_DIRECTION dir;
    WCHAR achName[ 128 ];
    }	PIN_INFO;


EXTERN_C const IID IID_IPin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a86891-0ad4-11ce-b03a-0020af0ba770")
    IPin : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Connect( 
            /* [in] */ IPin __RPC_FAR *pReceivePin,
            /* [in] */ const AM_MEDIA_TYPE __RPC_FAR *pmt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReceiveConnection( 
            /* [in] */ IPin __RPC_FAR *pConnector,
            /* [in] */ const AM_MEDIA_TYPE __RPC_FAR *pmt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Disconnect( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConnectedTo( 
            /* [out] */ IPin __RPC_FAR *__RPC_FAR *pPin) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConnectionMediaType( 
            /* [out] */ AM_MEDIA_TYPE __RPC_FAR *pmt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QueryPinInfo( 
            /* [out] */ PIN_INFO __RPC_FAR *pInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QueryDirection( 
            /* [out] */ PIN_DIRECTION __RPC_FAR *pPinDir) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QueryId( 
            /* [out] */ LPWSTR __RPC_FAR *Id) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QueryAccept( 
            /* [in] */ const AM_MEDIA_TYPE __RPC_FAR *pmt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumMediaTypes( 
            /* [out] */ IEnumMediaTypes __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QueryInternalConnections( 
            /* [out] */ IPin __RPC_FAR *__RPC_FAR *apPin,
            /* [out][in] */ ULONG __RPC_FAR *nPin) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EndOfStream( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BeginFlush( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EndFlush( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NewSegment( 
            /* [in] */ REFERENCE_TIME tStart,
            /* [in] */ REFERENCE_TIME tStop,
            /* [in] */ double dRate) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPinVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPin __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPin __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPin __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            IPin __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *pReceivePin,
            /* [in] */ const AM_MEDIA_TYPE __RPC_FAR *pmt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReceiveConnection )( 
            IPin __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *pConnector,
            /* [in] */ const AM_MEDIA_TYPE __RPC_FAR *pmt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            IPin __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectedTo )( 
            IPin __RPC_FAR * This,
            /* [out] */ IPin __RPC_FAR *__RPC_FAR *pPin);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectionMediaType )( 
            IPin __RPC_FAR * This,
            /* [out] */ AM_MEDIA_TYPE __RPC_FAR *pmt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryPinInfo )( 
            IPin __RPC_FAR * This,
            /* [out] */ PIN_INFO __RPC_FAR *pInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryDirection )( 
            IPin __RPC_FAR * This,
            /* [out] */ PIN_DIRECTION __RPC_FAR *pPinDir);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryId )( 
            IPin __RPC_FAR * This,
            /* [out] */ LPWSTR __RPC_FAR *Id);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryAccept )( 
            IPin __RPC_FAR * This,
            /* [in] */ const AM_MEDIA_TYPE __RPC_FAR *pmt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumMediaTypes )( 
            IPin __RPC_FAR * This,
            /* [out] */ IEnumMediaTypes __RPC_FAR *__RPC_FAR *ppEnum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInternalConnections )( 
            IPin __RPC_FAR * This,
            /* [out] */ IPin __RPC_FAR *__RPC_FAR *apPin,
            /* [out][in] */ ULONG __RPC_FAR *nPin);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EndOfStream )( 
            IPin __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BeginFlush )( 
            IPin __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EndFlush )( 
            IPin __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NewSegment )( 
            IPin __RPC_FAR * This,
            /* [in] */ REFERENCE_TIME tStart,
            /* [in] */ REFERENCE_TIME tStop,
            /* [in] */ double dRate);
        
        END_INTERFACE
    } IPinVtbl;

    interface IPin
    {
        CONST_VTBL struct IPinVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPin_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPin_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPin_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPin_Connect(This,pReceivePin,pmt)	\
    (This)->lpVtbl -> Connect(This,pReceivePin,pmt)

#define IPin_ReceiveConnection(This,pConnector,pmt)	\
    (This)->lpVtbl -> ReceiveConnection(This,pConnector,pmt)

#define IPin_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#define IPin_ConnectedTo(This,pPin)	\
    (This)->lpVtbl -> ConnectedTo(This,pPin)

#define IPin_ConnectionMediaType(This,pmt)	\
    (This)->lpVtbl -> ConnectionMediaType(This,pmt)

#define IPin_QueryPinInfo(This,pInfo)	\
    (This)->lpVtbl -> QueryPinInfo(This,pInfo)

#define IPin_QueryDirection(This,pPinDir)	\
    (This)->lpVtbl -> QueryDirection(This,pPinDir)

#define IPin_QueryId(This,Id)	\
    (This)->lpVtbl -> QueryId(This,Id)

#define IPin_QueryAccept(This,pmt)	\
    (This)->lpVtbl -> QueryAccept(This,pmt)

#define IPin_EnumMediaTypes(This,ppEnum)	\
    (This)->lpVtbl -> EnumMediaTypes(This,ppEnum)

#define IPin_QueryInternalConnections(This,apPin,nPin)	\
    (This)->lpVtbl -> QueryInternalConnections(This,apPin,nPin)

#define IPin_EndOfStream(This)	\
    (This)->lpVtbl -> EndOfStream(This)

#define IPin_BeginFlush(This)	\
    (This)->lpVtbl -> BeginFlush(This)

#define IPin_EndFlush(This)	\
    (This)->lpVtbl -> EndFlush(This)

#define IPin_NewSegment(This,tStart,tStop,dRate)	\
    (This)->lpVtbl -> NewSegment(This,tStart,tStop,dRate)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPin_Connect_Proxy( 
    IPin __RPC_FAR * This,
    /* [in] */ IPin __RPC_FAR *pReceivePin,
    /* [in] */ const AM_MEDIA_TYPE __RPC_FAR *pmt);


void __RPC_STUB IPin_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_ReceiveConnection_Proxy( 
    IPin __RPC_FAR * This,
    /* [in] */ IPin __RPC_FAR *pConnector,
    /* [in] */ const AM_MEDIA_TYPE __RPC_FAR *pmt);


void __RPC_STUB IPin_ReceiveConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_Disconnect_Proxy( 
    IPin __RPC_FAR * This);


void __RPC_STUB IPin_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_ConnectedTo_Proxy( 
    IPin __RPC_FAR * This,
    /* [out] */ IPin __RPC_FAR *__RPC_FAR *pPin);


void __RPC_STUB IPin_ConnectedTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_ConnectionMediaType_Proxy( 
    IPin __RPC_FAR * This,
    /* [out] */ AM_MEDIA_TYPE __RPC_FAR *pmt);


void __RPC_STUB IPin_ConnectionMediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_QueryPinInfo_Proxy( 
    IPin __RPC_FAR * This,
    /* [out] */ PIN_INFO __RPC_FAR *pInfo);


void __RPC_STUB IPin_QueryPinInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_QueryDirection_Proxy( 
    IPin __RPC_FAR * This,
    /* [out] */ PIN_DIRECTION __RPC_FAR *pPinDir);


void __RPC_STUB IPin_QueryDirection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_QueryId_Proxy( 
    IPin __RPC_FAR * This,
    /* [out] */ LPWSTR __RPC_FAR *Id);


void __RPC_STUB IPin_QueryId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_QueryAccept_Proxy( 
    IPin __RPC_FAR * This,
    /* [in] */ const AM_MEDIA_TYPE __RPC_FAR *pmt);


void __RPC_STUB IPin_QueryAccept_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_EnumMediaTypes_Proxy( 
    IPin __RPC_FAR * This,
    /* [out] */ IEnumMediaTypes __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IPin_EnumMediaTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_QueryInternalConnections_Proxy( 
    IPin __RPC_FAR * This,
    /* [out] */ IPin __RPC_FAR *__RPC_FAR *apPin,
    /* [out][in] */ ULONG __RPC_FAR *nPin);


void __RPC_STUB IPin_QueryInternalConnections_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_EndOfStream_Proxy( 
    IPin __RPC_FAR * This);


void __RPC_STUB IPin_EndOfStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_BeginFlush_Proxy( 
    IPin __RPC_FAR * This);


void __RPC_STUB IPin_BeginFlush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_EndFlush_Proxy( 
    IPin __RPC_FAR * This);


void __RPC_STUB IPin_EndFlush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPin_NewSegment_Proxy( 
    IPin __RPC_FAR * This,
    /* [in] */ REFERENCE_TIME tStart,
    /* [in] */ REFERENCE_TIME tStop,
    /* [in] */ double dRate);


void __RPC_STUB IPin_NewSegment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPin_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0055
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef IPin __RPC_FAR *PPIN;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0055_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0055_v0_0_s_ifspec;

#ifndef __IEnumPins_INTERFACE_DEFINED__
#define __IEnumPins_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IEnumPins
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IEnumPins;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a86892-0ad4-11ce-b03a-0020af0ba770")
    IEnumPins : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG cPins,
            /* [size_is][out] */ IPin __RPC_FAR *__RPC_FAR *ppPins,
            /* [out] */ ULONG __RPC_FAR *pcFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG cPins) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumPins __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumPinsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumPins __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumPins __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumPins __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumPins __RPC_FAR * This,
            /* [in] */ ULONG cPins,
            /* [size_is][out] */ IPin __RPC_FAR *__RPC_FAR *ppPins,
            /* [out] */ ULONG __RPC_FAR *pcFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumPins __RPC_FAR * This,
            /* [in] */ ULONG cPins);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumPins __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumPins __RPC_FAR * This,
            /* [out] */ IEnumPins __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IEnumPinsVtbl;

    interface IEnumPins
    {
        CONST_VTBL struct IEnumPinsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumPins_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumPins_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumPins_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumPins_Next(This,cPins,ppPins,pcFetched)	\
    (This)->lpVtbl -> Next(This,cPins,ppPins,pcFetched)

#define IEnumPins_Skip(This,cPins)	\
    (This)->lpVtbl -> Skip(This,cPins)

#define IEnumPins_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumPins_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumPins_Next_Proxy( 
    IEnumPins __RPC_FAR * This,
    /* [in] */ ULONG cPins,
    /* [size_is][out] */ IPin __RPC_FAR *__RPC_FAR *ppPins,
    /* [out] */ ULONG __RPC_FAR *pcFetched);


void __RPC_STUB IEnumPins_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumPins_Skip_Proxy( 
    IEnumPins __RPC_FAR * This,
    /* [in] */ ULONG cPins);


void __RPC_STUB IEnumPins_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumPins_Reset_Proxy( 
    IEnumPins __RPC_FAR * This);


void __RPC_STUB IEnumPins_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumPins_Clone_Proxy( 
    IEnumPins __RPC_FAR * This,
    /* [out] */ IEnumPins __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IEnumPins_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumPins_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0056
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef IEnumPins __RPC_FAR *PENUMPINS;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0056_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0056_v0_0_s_ifspec;

#ifndef __IEnumMediaTypes_INTERFACE_DEFINED__
#define __IEnumMediaTypes_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IEnumMediaTypes
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IEnumMediaTypes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("89c31040-846b-11ce-97d3-00aa0055595a")
    IEnumMediaTypes : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG cMediaTypes,
            /* [size_is][out] */ AM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *ppMediaTypes,
            /* [out] */ ULONG __RPC_FAR *pcFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG cMediaTypes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumMediaTypes __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumMediaTypesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumMediaTypes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumMediaTypes __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumMediaTypes __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumMediaTypes __RPC_FAR * This,
            /* [in] */ ULONG cMediaTypes,
            /* [size_is][out] */ AM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *ppMediaTypes,
            /* [out] */ ULONG __RPC_FAR *pcFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumMediaTypes __RPC_FAR * This,
            /* [in] */ ULONG cMediaTypes);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumMediaTypes __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumMediaTypes __RPC_FAR * This,
            /* [out] */ IEnumMediaTypes __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IEnumMediaTypesVtbl;

    interface IEnumMediaTypes
    {
        CONST_VTBL struct IEnumMediaTypesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumMediaTypes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumMediaTypes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumMediaTypes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumMediaTypes_Next(This,cMediaTypes,ppMediaTypes,pcFetched)	\
    (This)->lpVtbl -> Next(This,cMediaTypes,ppMediaTypes,pcFetched)

#define IEnumMediaTypes_Skip(This,cMediaTypes)	\
    (This)->lpVtbl -> Skip(This,cMediaTypes)

#define IEnumMediaTypes_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumMediaTypes_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumMediaTypes_Next_Proxy( 
    IEnumMediaTypes __RPC_FAR * This,
    /* [in] */ ULONG cMediaTypes,
    /* [size_is][out] */ AM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *ppMediaTypes,
    /* [out] */ ULONG __RPC_FAR *pcFetched);


void __RPC_STUB IEnumMediaTypes_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumMediaTypes_Skip_Proxy( 
    IEnumMediaTypes __RPC_FAR * This,
    /* [in] */ ULONG cMediaTypes);


void __RPC_STUB IEnumMediaTypes_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumMediaTypes_Reset_Proxy( 
    IEnumMediaTypes __RPC_FAR * This);


void __RPC_STUB IEnumMediaTypes_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumMediaTypes_Clone_Proxy( 
    IEnumMediaTypes __RPC_FAR * This,
    /* [out] */ IEnumMediaTypes __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IEnumMediaTypes_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumMediaTypes_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0057
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef IEnumMediaTypes __RPC_FAR *PENUMMEDIATYPES;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0057_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0057_v0_0_s_ifspec;

#ifndef __IFilterGraph_INTERFACE_DEFINED__
#define __IFilterGraph_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IFilterGraph
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IFilterGraph;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a8689f-0ad4-11ce-b03a-0020af0ba770")
    IFilterGraph : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AddFilter( 
            /* [in] */ IBaseFilter __RPC_FAR *pFilter,
            /* [string][in] */ LPCWSTR pName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveFilter( 
            /* [in] */ IBaseFilter __RPC_FAR *pFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumFilters( 
            /* [out] */ IEnumFilters __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FindFilterByName( 
            /* [string][in] */ LPCWSTR pName,
            /* [out] */ IBaseFilter __RPC_FAR *__RPC_FAR *ppFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConnectDirect( 
            /* [in] */ IPin __RPC_FAR *ppinOut,
            /* [in] */ IPin __RPC_FAR *ppinIn,
            /* [in] */ const AM_MEDIA_TYPE __RPC_FAR *pmt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reconnect( 
            /* [in] */ IPin __RPC_FAR *ppin) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Disconnect( 
            /* [in] */ IPin __RPC_FAR *ppin) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDefaultSyncSource( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFilterGraphVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFilterGraph __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFilterGraph __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFilterGraph __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddFilter )( 
            IFilterGraph __RPC_FAR * This,
            /* [in] */ IBaseFilter __RPC_FAR *pFilter,
            /* [string][in] */ LPCWSTR pName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveFilter )( 
            IFilterGraph __RPC_FAR * This,
            /* [in] */ IBaseFilter __RPC_FAR *pFilter);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumFilters )( 
            IFilterGraph __RPC_FAR * This,
            /* [out] */ IEnumFilters __RPC_FAR *__RPC_FAR *ppEnum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindFilterByName )( 
            IFilterGraph __RPC_FAR * This,
            /* [string][in] */ LPCWSTR pName,
            /* [out] */ IBaseFilter __RPC_FAR *__RPC_FAR *ppFilter);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectDirect )( 
            IFilterGraph __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *ppinOut,
            /* [in] */ IPin __RPC_FAR *ppinIn,
            /* [in] */ const AM_MEDIA_TYPE __RPC_FAR *pmt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reconnect )( 
            IFilterGraph __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *ppin);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            IFilterGraph __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *ppin);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDefaultSyncSource )( 
            IFilterGraph __RPC_FAR * This);
        
        END_INTERFACE
    } IFilterGraphVtbl;

    interface IFilterGraph
    {
        CONST_VTBL struct IFilterGraphVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFilterGraph_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFilterGraph_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFilterGraph_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFilterGraph_AddFilter(This,pFilter,pName)	\
    (This)->lpVtbl -> AddFilter(This,pFilter,pName)

#define IFilterGraph_RemoveFilter(This,pFilter)	\
    (This)->lpVtbl -> RemoveFilter(This,pFilter)

#define IFilterGraph_EnumFilters(This,ppEnum)	\
    (This)->lpVtbl -> EnumFilters(This,ppEnum)

#define IFilterGraph_FindFilterByName(This,pName,ppFilter)	\
    (This)->lpVtbl -> FindFilterByName(This,pName,ppFilter)

#define IFilterGraph_ConnectDirect(This,ppinOut,ppinIn,pmt)	\
    (This)->lpVtbl -> ConnectDirect(This,ppinOut,ppinIn,pmt)

#define IFilterGraph_Reconnect(This,ppin)	\
    (This)->lpVtbl -> Reconnect(This,ppin)

#define IFilterGraph_Disconnect(This,ppin)	\
    (This)->lpVtbl -> Disconnect(This,ppin)

#define IFilterGraph_SetDefaultSyncSource(This)	\
    (This)->lpVtbl -> SetDefaultSyncSource(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFilterGraph_AddFilter_Proxy( 
    IFilterGraph __RPC_FAR * This,
    /* [in] */ IBaseFilter __RPC_FAR *pFilter,
    /* [string][in] */ LPCWSTR pName);


void __RPC_STUB IFilterGraph_AddFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterGraph_RemoveFilter_Proxy( 
    IFilterGraph __RPC_FAR * This,
    /* [in] */ IBaseFilter __RPC_FAR *pFilter);


void __RPC_STUB IFilterGraph_RemoveFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterGraph_EnumFilters_Proxy( 
    IFilterGraph __RPC_FAR * This,
    /* [out] */ IEnumFilters __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IFilterGraph_EnumFilters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterGraph_FindFilterByName_Proxy( 
    IFilterGraph __RPC_FAR * This,
    /* [string][in] */ LPCWSTR pName,
    /* [out] */ IBaseFilter __RPC_FAR *__RPC_FAR *ppFilter);


void __RPC_STUB IFilterGraph_FindFilterByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterGraph_ConnectDirect_Proxy( 
    IFilterGraph __RPC_FAR * This,
    /* [in] */ IPin __RPC_FAR *ppinOut,
    /* [in] */ IPin __RPC_FAR *ppinIn,
    /* [in] */ const AM_MEDIA_TYPE __RPC_FAR *pmt);


void __RPC_STUB IFilterGraph_ConnectDirect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterGraph_Reconnect_Proxy( 
    IFilterGraph __RPC_FAR * This,
    /* [in] */ IPin __RPC_FAR *ppin);


void __RPC_STUB IFilterGraph_Reconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterGraph_Disconnect_Proxy( 
    IFilterGraph __RPC_FAR * This,
    /* [in] */ IPin __RPC_FAR *ppin);


void __RPC_STUB IFilterGraph_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterGraph_SetDefaultSyncSource_Proxy( 
    IFilterGraph __RPC_FAR * This);


void __RPC_STUB IFilterGraph_SetDefaultSyncSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFilterGraph_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0058
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef IFilterGraph __RPC_FAR *PFILTERGRAPH;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0058_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0058_v0_0_s_ifspec;

#ifndef __IEnumFilters_INTERFACE_DEFINED__
#define __IEnumFilters_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IEnumFilters
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IEnumFilters;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a86893-0ad4-11ce-b03a-0020af0ba770")
    IEnumFilters : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG cFilters,
            /* [out] */ IBaseFilter __RPC_FAR *__RPC_FAR *ppFilter,
            /* [out] */ ULONG __RPC_FAR *pcFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG cFilters) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumFilters __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumFiltersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumFilters __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumFilters __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumFilters __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumFilters __RPC_FAR * This,
            /* [in] */ ULONG cFilters,
            /* [out] */ IBaseFilter __RPC_FAR *__RPC_FAR *ppFilter,
            /* [out] */ ULONG __RPC_FAR *pcFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumFilters __RPC_FAR * This,
            /* [in] */ ULONG cFilters);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumFilters __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumFilters __RPC_FAR * This,
            /* [out] */ IEnumFilters __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IEnumFiltersVtbl;

    interface IEnumFilters
    {
        CONST_VTBL struct IEnumFiltersVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumFilters_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumFilters_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumFilters_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumFilters_Next(This,cFilters,ppFilter,pcFetched)	\
    (This)->lpVtbl -> Next(This,cFilters,ppFilter,pcFetched)

#define IEnumFilters_Skip(This,cFilters)	\
    (This)->lpVtbl -> Skip(This,cFilters)

#define IEnumFilters_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumFilters_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumFilters_Next_Proxy( 
    IEnumFilters __RPC_FAR * This,
    /* [in] */ ULONG cFilters,
    /* [out] */ IBaseFilter __RPC_FAR *__RPC_FAR *ppFilter,
    /* [out] */ ULONG __RPC_FAR *pcFetched);


void __RPC_STUB IEnumFilters_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumFilters_Skip_Proxy( 
    IEnumFilters __RPC_FAR * This,
    /* [in] */ ULONG cFilters);


void __RPC_STUB IEnumFilters_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumFilters_Reset_Proxy( 
    IEnumFilters __RPC_FAR * This);


void __RPC_STUB IEnumFilters_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumFilters_Clone_Proxy( 
    IEnumFilters __RPC_FAR * This,
    /* [out] */ IEnumFilters __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IEnumFilters_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumFilters_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0059
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef IEnumFilters __RPC_FAR *PENUMFILTERS;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0059_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0059_v0_0_s_ifspec;

#ifndef __IMediaFilter_INTERFACE_DEFINED__
#define __IMediaFilter_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMediaFilter
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 


typedef 
enum _FilterState
    {	State_Stopped	= 0,
	State_Paused	= State_Stopped + 1,
	State_Running	= State_Paused + 1
    }	FILTER_STATE;


EXTERN_C const IID IID_IMediaFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a86899-0ad4-11ce-b03a-0020af0ba770")
    IMediaFilter : public IPersist
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Pause( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Run( 
            REFERENCE_TIME tStart) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetState( 
            /* [in] */ DWORD dwMilliSecsTimeout,
            /* [out] */ FILTER_STATE __RPC_FAR *State) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSyncSource( 
            /* [in] */ IReferenceClock __RPC_FAR *pClock) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSyncSource( 
            /* [out] */ IReferenceClock __RPC_FAR *__RPC_FAR *pClock) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMediaFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMediaFilter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMediaFilter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMediaFilter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetClassID )( 
            IMediaFilter __RPC_FAR * This,
            /* [out] */ CLSID __RPC_FAR *pClassID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IMediaFilter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pause )( 
            IMediaFilter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Run )( 
            IMediaFilter __RPC_FAR * This,
            REFERENCE_TIME tStart);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetState )( 
            IMediaFilter __RPC_FAR * This,
            /* [in] */ DWORD dwMilliSecsTimeout,
            /* [out] */ FILTER_STATE __RPC_FAR *State);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSyncSource )( 
            IMediaFilter __RPC_FAR * This,
            /* [in] */ IReferenceClock __RPC_FAR *pClock);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSyncSource )( 
            IMediaFilter __RPC_FAR * This,
            /* [out] */ IReferenceClock __RPC_FAR *__RPC_FAR *pClock);
        
        END_INTERFACE
    } IMediaFilterVtbl;

    interface IMediaFilter
    {
        CONST_VTBL struct IMediaFilterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaFilter_GetClassID(This,pClassID)	\
    (This)->lpVtbl -> GetClassID(This,pClassID)


#define IMediaFilter_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IMediaFilter_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IMediaFilter_Run(This,tStart)	\
    (This)->lpVtbl -> Run(This,tStart)

#define IMediaFilter_GetState(This,dwMilliSecsTimeout,State)	\
    (This)->lpVtbl -> GetState(This,dwMilliSecsTimeout,State)

#define IMediaFilter_SetSyncSource(This,pClock)	\
    (This)->lpVtbl -> SetSyncSource(This,pClock)

#define IMediaFilter_GetSyncSource(This,pClock)	\
    (This)->lpVtbl -> GetSyncSource(This,pClock)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMediaFilter_Stop_Proxy( 
    IMediaFilter __RPC_FAR * This);


void __RPC_STUB IMediaFilter_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaFilter_Pause_Proxy( 
    IMediaFilter __RPC_FAR * This);


void __RPC_STUB IMediaFilter_Pause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaFilter_Run_Proxy( 
    IMediaFilter __RPC_FAR * This,
    REFERENCE_TIME tStart);


void __RPC_STUB IMediaFilter_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaFilter_GetState_Proxy( 
    IMediaFilter __RPC_FAR * This,
    /* [in] */ DWORD dwMilliSecsTimeout,
    /* [out] */ FILTER_STATE __RPC_FAR *State);


void __RPC_STUB IMediaFilter_GetState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaFilter_SetSyncSource_Proxy( 
    IMediaFilter __RPC_FAR * This,
    /* [in] */ IReferenceClock __RPC_FAR *pClock);


void __RPC_STUB IMediaFilter_SetSyncSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaFilter_GetSyncSource_Proxy( 
    IMediaFilter __RPC_FAR * This,
    /* [out] */ IReferenceClock __RPC_FAR *__RPC_FAR *pClock);


void __RPC_STUB IMediaFilter_GetSyncSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMediaFilter_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0060
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef IMediaFilter __RPC_FAR *PMEDIAFILTER;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0060_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0060_v0_0_s_ifspec;

#ifndef __IBaseFilter_INTERFACE_DEFINED__
#define __IBaseFilter_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IBaseFilter
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 


typedef struct  _FilterInfo
    {
    WCHAR achName[ 128 ];
    IFilterGraph __RPC_FAR *pGraph;
    }	FILTER_INFO;


EXTERN_C const IID IID_IBaseFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a86895-0ad4-11ce-b03a-0020af0ba770")
    IBaseFilter : public IMediaFilter
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE EnumPins( 
            /* [out] */ IEnumPins __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FindPin( 
            /* [string][in] */ LPCWSTR Id,
            /* [out] */ IPin __RPC_FAR *__RPC_FAR *ppPin) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QueryFilterInfo( 
            /* [out] */ FILTER_INFO __RPC_FAR *pInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE JoinFilterGraph( 
            /* [in] */ IFilterGraph __RPC_FAR *pGraph,
            /* [string][in] */ LPCWSTR pName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QueryVendorInfo( 
            /* [string][out] */ LPWSTR __RPC_FAR *pVendorInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBaseFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBaseFilter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBaseFilter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBaseFilter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetClassID )( 
            IBaseFilter __RPC_FAR * This,
            /* [out] */ CLSID __RPC_FAR *pClassID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IBaseFilter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pause )( 
            IBaseFilter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Run )( 
            IBaseFilter __RPC_FAR * This,
            REFERENCE_TIME tStart);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetState )( 
            IBaseFilter __RPC_FAR * This,
            /* [in] */ DWORD dwMilliSecsTimeout,
            /* [out] */ FILTER_STATE __RPC_FAR *State);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSyncSource )( 
            IBaseFilter __RPC_FAR * This,
            /* [in] */ IReferenceClock __RPC_FAR *pClock);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSyncSource )( 
            IBaseFilter __RPC_FAR * This,
            /* [out] */ IReferenceClock __RPC_FAR *__RPC_FAR *pClock);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumPins )( 
            IBaseFilter __RPC_FAR * This,
            /* [out] */ IEnumPins __RPC_FAR *__RPC_FAR *ppEnum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindPin )( 
            IBaseFilter __RPC_FAR * This,
            /* [string][in] */ LPCWSTR Id,
            /* [out] */ IPin __RPC_FAR *__RPC_FAR *ppPin);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryFilterInfo )( 
            IBaseFilter __RPC_FAR * This,
            /* [out] */ FILTER_INFO __RPC_FAR *pInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *JoinFilterGraph )( 
            IBaseFilter __RPC_FAR * This,
            /* [in] */ IFilterGraph __RPC_FAR *pGraph,
            /* [string][in] */ LPCWSTR pName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryVendorInfo )( 
            IBaseFilter __RPC_FAR * This,
            /* [string][out] */ LPWSTR __RPC_FAR *pVendorInfo);
        
        END_INTERFACE
    } IBaseFilterVtbl;

    interface IBaseFilter
    {
        CONST_VTBL struct IBaseFilterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBaseFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBaseFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBaseFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBaseFilter_GetClassID(This,pClassID)	\
    (This)->lpVtbl -> GetClassID(This,pClassID)


#define IBaseFilter_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IBaseFilter_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IBaseFilter_Run(This,tStart)	\
    (This)->lpVtbl -> Run(This,tStart)

#define IBaseFilter_GetState(This,dwMilliSecsTimeout,State)	\
    (This)->lpVtbl -> GetState(This,dwMilliSecsTimeout,State)

#define IBaseFilter_SetSyncSource(This,pClock)	\
    (This)->lpVtbl -> SetSyncSource(This,pClock)

#define IBaseFilter_GetSyncSource(This,pClock)	\
    (This)->lpVtbl -> GetSyncSource(This,pClock)


#define IBaseFilter_EnumPins(This,ppEnum)	\
    (This)->lpVtbl -> EnumPins(This,ppEnum)

#define IBaseFilter_FindPin(This,Id,ppPin)	\
    (This)->lpVtbl -> FindPin(This,Id,ppPin)

#define IBaseFilter_QueryFilterInfo(This,pInfo)	\
    (This)->lpVtbl -> QueryFilterInfo(This,pInfo)

#define IBaseFilter_JoinFilterGraph(This,pGraph,pName)	\
    (This)->lpVtbl -> JoinFilterGraph(This,pGraph,pName)

#define IBaseFilter_QueryVendorInfo(This,pVendorInfo)	\
    (This)->lpVtbl -> QueryVendorInfo(This,pVendorInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IBaseFilter_EnumPins_Proxy( 
    IBaseFilter __RPC_FAR * This,
    /* [out] */ IEnumPins __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IBaseFilter_EnumPins_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBaseFilter_FindPin_Proxy( 
    IBaseFilter __RPC_FAR * This,
    /* [string][in] */ LPCWSTR Id,
    /* [out] */ IPin __RPC_FAR *__RPC_FAR *ppPin);


void __RPC_STUB IBaseFilter_FindPin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBaseFilter_QueryFilterInfo_Proxy( 
    IBaseFilter __RPC_FAR * This,
    /* [out] */ FILTER_INFO __RPC_FAR *pInfo);


void __RPC_STUB IBaseFilter_QueryFilterInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBaseFilter_JoinFilterGraph_Proxy( 
    IBaseFilter __RPC_FAR * This,
    /* [in] */ IFilterGraph __RPC_FAR *pGraph,
    /* [string][in] */ LPCWSTR pName);


void __RPC_STUB IBaseFilter_JoinFilterGraph_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBaseFilter_QueryVendorInfo_Proxy( 
    IBaseFilter __RPC_FAR * This,
    /* [string][out] */ LPWSTR __RPC_FAR *pVendorInfo);


void __RPC_STUB IBaseFilter_QueryVendorInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBaseFilter_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0061
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef IBaseFilter __RPC_FAR *PFILTER;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0061_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0061_v0_0_s_ifspec;

#ifndef __IReferenceClock_INTERFACE_DEFINED__
#define __IReferenceClock_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IReferenceClock
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IReferenceClock;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a86897-0ad4-11ce-b03a-0020af0ba770")
    IReferenceClock : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetTime( 
            /* [out] */ REFERENCE_TIME __RPC_FAR *pTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AdviseTime( 
            /* [in] */ REFERENCE_TIME baseTime,
            /* [in] */ REFERENCE_TIME streamTime,
            /* [in] */ HEVENT hEvent,
            /* [out] */ DWORD __RPC_FAR *pdwAdviseCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AdvisePeriodic( 
            /* [in] */ REFERENCE_TIME startTime,
            /* [in] */ REFERENCE_TIME periodTime,
            /* [in] */ HSEMAPHORE hSemaphore,
            /* [out] */ DWORD __RPC_FAR *pdwAdviseCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Unadvise( 
            /* [in] */ DWORD dwAdviseCookie) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IReferenceClockVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IReferenceClock __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IReferenceClock __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IReferenceClock __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTime )( 
            IReferenceClock __RPC_FAR * This,
            /* [out] */ REFERENCE_TIME __RPC_FAR *pTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AdviseTime )( 
            IReferenceClock __RPC_FAR * This,
            /* [in] */ REFERENCE_TIME baseTime,
            /* [in] */ REFERENCE_TIME streamTime,
            /* [in] */ HEVENT hEvent,
            /* [out] */ DWORD __RPC_FAR *pdwAdviseCookie);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AdvisePeriodic )( 
            IReferenceClock __RPC_FAR * This,
            /* [in] */ REFERENCE_TIME startTime,
            /* [in] */ REFERENCE_TIME periodTime,
            /* [in] */ HSEMAPHORE hSemaphore,
            /* [out] */ DWORD __RPC_FAR *pdwAdviseCookie);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Unadvise )( 
            IReferenceClock __RPC_FAR * This,
            /* [in] */ DWORD dwAdviseCookie);
        
        END_INTERFACE
    } IReferenceClockVtbl;

    interface IReferenceClock
    {
        CONST_VTBL struct IReferenceClockVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IReferenceClock_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IReferenceClock_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IReferenceClock_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IReferenceClock_GetTime(This,pTime)	\
    (This)->lpVtbl -> GetTime(This,pTime)

#define IReferenceClock_AdviseTime(This,baseTime,streamTime,hEvent,pdwAdviseCookie)	\
    (This)->lpVtbl -> AdviseTime(This,baseTime,streamTime,hEvent,pdwAdviseCookie)

#define IReferenceClock_AdvisePeriodic(This,startTime,periodTime,hSemaphore,pdwAdviseCookie)	\
    (This)->lpVtbl -> AdvisePeriodic(This,startTime,periodTime,hSemaphore,pdwAdviseCookie)

#define IReferenceClock_Unadvise(This,dwAdviseCookie)	\
    (This)->lpVtbl -> Unadvise(This,dwAdviseCookie)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IReferenceClock_GetTime_Proxy( 
    IReferenceClock __RPC_FAR * This,
    /* [out] */ REFERENCE_TIME __RPC_FAR *pTime);


void __RPC_STUB IReferenceClock_GetTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IReferenceClock_AdviseTime_Proxy( 
    IReferenceClock __RPC_FAR * This,
    /* [in] */ REFERENCE_TIME baseTime,
    /* [in] */ REFERENCE_TIME streamTime,
    /* [in] */ HEVENT hEvent,
    /* [out] */ DWORD __RPC_FAR *pdwAdviseCookie);


void __RPC_STUB IReferenceClock_AdviseTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IReferenceClock_AdvisePeriodic_Proxy( 
    IReferenceClock __RPC_FAR * This,
    /* [in] */ REFERENCE_TIME startTime,
    /* [in] */ REFERENCE_TIME periodTime,
    /* [in] */ HSEMAPHORE hSemaphore,
    /* [out] */ DWORD __RPC_FAR *pdwAdviseCookie);


void __RPC_STUB IReferenceClock_AdvisePeriodic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IReferenceClock_Unadvise_Proxy( 
    IReferenceClock __RPC_FAR * This,
    /* [in] */ DWORD dwAdviseCookie);


void __RPC_STUB IReferenceClock_Unadvise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IReferenceClock_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0062
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef IReferenceClock __RPC_FAR *PREFERENCECLOCK;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0062_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0062_v0_0_s_ifspec;

#ifndef __IMediaSample_INTERFACE_DEFINED__
#define __IMediaSample_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMediaSample
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IMediaSample;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a8689a-0ad4-11ce-b03a-0020af0ba770")
    IMediaSample : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetPointer( 
            /* [out] */ BYTE __RPC_FAR *__RPC_FAR *ppBuffer) = 0;
        
        virtual long STDMETHODCALLTYPE GetSize( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTime( 
            /* [out] */ REFERENCE_TIME __RPC_FAR *pTimeStart,
            /* [out] */ REFERENCE_TIME __RPC_FAR *pTimeEnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTime( 
            /* [in] */ REFERENCE_TIME __RPC_FAR *pTimeStart,
            /* [in] */ REFERENCE_TIME __RPC_FAR *pTimeEnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsSyncPoint( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSyncPoint( 
            BOOL bIsSyncPoint) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsPreroll( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPreroll( 
            BOOL bIsPreroll) = 0;
        
        virtual long STDMETHODCALLTYPE GetActualDataLength( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetActualDataLength( 
            long __MIDL_0008) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMediaType( 
            AM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *ppMediaType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMediaType( 
            AM_MEDIA_TYPE __RPC_FAR *pMediaType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsDiscontinuity( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDiscontinuity( 
            BOOL bDiscontinuity) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMediaTime( 
            /* [out] */ LONGLONG __RPC_FAR *pTimeStart,
            /* [out] */ LONGLONG __RPC_FAR *pTimeEnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMediaTime( 
            /* [in] */ LONGLONG __RPC_FAR *pTimeStart,
            /* [in] */ LONGLONG __RPC_FAR *pTimeEnd) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMediaSampleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMediaSample __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMediaSample __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMediaSample __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPointer )( 
            IMediaSample __RPC_FAR * This,
            /* [out] */ BYTE __RPC_FAR *__RPC_FAR *ppBuffer);
        
        long ( STDMETHODCALLTYPE __RPC_FAR *GetSize )( 
            IMediaSample __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTime )( 
            IMediaSample __RPC_FAR * This,
            /* [out] */ REFERENCE_TIME __RPC_FAR *pTimeStart,
            /* [out] */ REFERENCE_TIME __RPC_FAR *pTimeEnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTime )( 
            IMediaSample __RPC_FAR * This,
            /* [in] */ REFERENCE_TIME __RPC_FAR *pTimeStart,
            /* [in] */ REFERENCE_TIME __RPC_FAR *pTimeEnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsSyncPoint )( 
            IMediaSample __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSyncPoint )( 
            IMediaSample __RPC_FAR * This,
            BOOL bIsSyncPoint);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsPreroll )( 
            IMediaSample __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPreroll )( 
            IMediaSample __RPC_FAR * This,
            BOOL bIsPreroll);
        
        long ( STDMETHODCALLTYPE __RPC_FAR *GetActualDataLength )( 
            IMediaSample __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetActualDataLength )( 
            IMediaSample __RPC_FAR * This,
            long __MIDL_0008);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMediaType )( 
            IMediaSample __RPC_FAR * This,
            AM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *ppMediaType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMediaType )( 
            IMediaSample __RPC_FAR * This,
            AM_MEDIA_TYPE __RPC_FAR *pMediaType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsDiscontinuity )( 
            IMediaSample __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDiscontinuity )( 
            IMediaSample __RPC_FAR * This,
            BOOL bDiscontinuity);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMediaTime )( 
            IMediaSample __RPC_FAR * This,
            /* [out] */ LONGLONG __RPC_FAR *pTimeStart,
            /* [out] */ LONGLONG __RPC_FAR *pTimeEnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMediaTime )( 
            IMediaSample __RPC_FAR * This,
            /* [in] */ LONGLONG __RPC_FAR *pTimeStart,
            /* [in] */ LONGLONG __RPC_FAR *pTimeEnd);
        
        END_INTERFACE
    } IMediaSampleVtbl;

    interface IMediaSample
    {
        CONST_VTBL struct IMediaSampleVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaSample_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaSample_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaSample_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaSample_GetPointer(This,ppBuffer)	\
    (This)->lpVtbl -> GetPointer(This,ppBuffer)

#define IMediaSample_GetSize(This)	\
    (This)->lpVtbl -> GetSize(This)

#define IMediaSample_GetTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> GetTime(This,pTimeStart,pTimeEnd)

#define IMediaSample_SetTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> SetTime(This,pTimeStart,pTimeEnd)

#define IMediaSample_IsSyncPoint(This)	\
    (This)->lpVtbl -> IsSyncPoint(This)

#define IMediaSample_SetSyncPoint(This,bIsSyncPoint)	\
    (This)->lpVtbl -> SetSyncPoint(This,bIsSyncPoint)

#define IMediaSample_IsPreroll(This)	\
    (This)->lpVtbl -> IsPreroll(This)

#define IMediaSample_SetPreroll(This,bIsPreroll)	\
    (This)->lpVtbl -> SetPreroll(This,bIsPreroll)

#define IMediaSample_GetActualDataLength(This)	\
    (This)->lpVtbl -> GetActualDataLength(This)

#define IMediaSample_SetActualDataLength(This,__MIDL_0008)	\
    (This)->lpVtbl -> SetActualDataLength(This,__MIDL_0008)

#define IMediaSample_GetMediaType(This,ppMediaType)	\
    (This)->lpVtbl -> GetMediaType(This,ppMediaType)

#define IMediaSample_SetMediaType(This,pMediaType)	\
    (This)->lpVtbl -> SetMediaType(This,pMediaType)

#define IMediaSample_IsDiscontinuity(This)	\
    (This)->lpVtbl -> IsDiscontinuity(This)

#define IMediaSample_SetDiscontinuity(This,bDiscontinuity)	\
    (This)->lpVtbl -> SetDiscontinuity(This,bDiscontinuity)

#define IMediaSample_GetMediaTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> GetMediaTime(This,pTimeStart,pTimeEnd)

#define IMediaSample_SetMediaTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> SetMediaTime(This,pTimeStart,pTimeEnd)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMediaSample_GetPointer_Proxy( 
    IMediaSample __RPC_FAR * This,
    /* [out] */ BYTE __RPC_FAR *__RPC_FAR *ppBuffer);


void __RPC_STUB IMediaSample_GetPointer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


long STDMETHODCALLTYPE IMediaSample_GetSize_Proxy( 
    IMediaSample __RPC_FAR * This);


void __RPC_STUB IMediaSample_GetSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_GetTime_Proxy( 
    IMediaSample __RPC_FAR * This,
    /* [out] */ REFERENCE_TIME __RPC_FAR *pTimeStart,
    /* [out] */ REFERENCE_TIME __RPC_FAR *pTimeEnd);


void __RPC_STUB IMediaSample_GetTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_SetTime_Proxy( 
    IMediaSample __RPC_FAR * This,
    /* [in] */ REFERENCE_TIME __RPC_FAR *pTimeStart,
    /* [in] */ REFERENCE_TIME __RPC_FAR *pTimeEnd);


void __RPC_STUB IMediaSample_SetTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_IsSyncPoint_Proxy( 
    IMediaSample __RPC_FAR * This);


void __RPC_STUB IMediaSample_IsSyncPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_SetSyncPoint_Proxy( 
    IMediaSample __RPC_FAR * This,
    BOOL bIsSyncPoint);


void __RPC_STUB IMediaSample_SetSyncPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_IsPreroll_Proxy( 
    IMediaSample __RPC_FAR * This);


void __RPC_STUB IMediaSample_IsPreroll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_SetPreroll_Proxy( 
    IMediaSample __RPC_FAR * This,
    BOOL bIsPreroll);


void __RPC_STUB IMediaSample_SetPreroll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


long STDMETHODCALLTYPE IMediaSample_GetActualDataLength_Proxy( 
    IMediaSample __RPC_FAR * This);


void __RPC_STUB IMediaSample_GetActualDataLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_SetActualDataLength_Proxy( 
    IMediaSample __RPC_FAR * This,
    long __MIDL_0008);


void __RPC_STUB IMediaSample_SetActualDataLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_GetMediaType_Proxy( 
    IMediaSample __RPC_FAR * This,
    AM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *ppMediaType);


void __RPC_STUB IMediaSample_GetMediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_SetMediaType_Proxy( 
    IMediaSample __RPC_FAR * This,
    AM_MEDIA_TYPE __RPC_FAR *pMediaType);


void __RPC_STUB IMediaSample_SetMediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_IsDiscontinuity_Proxy( 
    IMediaSample __RPC_FAR * This);


void __RPC_STUB IMediaSample_IsDiscontinuity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_SetDiscontinuity_Proxy( 
    IMediaSample __RPC_FAR * This,
    BOOL bDiscontinuity);


void __RPC_STUB IMediaSample_SetDiscontinuity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_GetMediaTime_Proxy( 
    IMediaSample __RPC_FAR * This,
    /* [out] */ LONGLONG __RPC_FAR *pTimeStart,
    /* [out] */ LONGLONG __RPC_FAR *pTimeEnd);


void __RPC_STUB IMediaSample_GetMediaTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample_SetMediaTime_Proxy( 
    IMediaSample __RPC_FAR * This,
    /* [in] */ LONGLONG __RPC_FAR *pTimeStart,
    /* [in] */ LONGLONG __RPC_FAR *pTimeEnd);


void __RPC_STUB IMediaSample_SetMediaTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMediaSample_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0063
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef IMediaSample __RPC_FAR *PMEDIASAMPLE;


enum tagAM_SAMPLE_PROPERTY_FLAGS
    {	AM_SAMPLE_SPLICEPOINT	= 0x1,
	AM_SAMPLE_PREROLL	= 0x2,
	AM_SAMPLE_DATADISCONTINUITY	= 0x4,
	AM_SAMPLE_TYPECHANGED	= 0x8,
	AM_SAMPLE_TIMEVALID	= 0x10,
	AM_SAMPLE_TIMEDISCONTINUITY	= 0x40,
	AM_SAMPLE_FLUSH_ON_PAUSE	= 0x80,
	AM_SAMPLE_STOPVALID	= 0x100,
	AM_SAMPLE_ENDOFSTREAM	= 0x200,
	AM_STREAM_MEDIA	= 0,
	AM_STREAM_CONTROL	= 1
    };
typedef struct  tagAM_SAMPLE2_PROPERTIES
    {
    DWORD cbData;
    DWORD dwTypeSpecificFlags;
    DWORD dwSampleFlags;
    LONG lActual;
    REFERENCE_TIME tStart;
    REFERENCE_TIME tStop;
    DWORD dwStreamId;
    AM_MEDIA_TYPE __RPC_FAR *pMediaType;
    BYTE __RPC_FAR *pbBuffer;
    LONG cbBuffer;
    }	AM_SAMPLE2_PROPERTIES;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0063_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0063_v0_0_s_ifspec;

#ifndef __IMediaSample2_INTERFACE_DEFINED__
#define __IMediaSample2_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMediaSample2
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IMediaSample2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("36b73884-c2c8-11cf-8b46-00805f6cef60")
    IMediaSample2 : public IMediaSample
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetProperties( 
            /* [in] */ DWORD cbProperties,
            /* [size_is][out] */ BYTE __RPC_FAR *pbProperties) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetProperties( 
            /* [in] */ DWORD cbProperties,
            /* [size_is][in] */ const BYTE __RPC_FAR *pbProperties) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMediaSample2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMediaSample2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMediaSample2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMediaSample2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPointer )( 
            IMediaSample2 __RPC_FAR * This,
            /* [out] */ BYTE __RPC_FAR *__RPC_FAR *ppBuffer);
        
        long ( STDMETHODCALLTYPE __RPC_FAR *GetSize )( 
            IMediaSample2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTime )( 
            IMediaSample2 __RPC_FAR * This,
            /* [out] */ REFERENCE_TIME __RPC_FAR *pTimeStart,
            /* [out] */ REFERENCE_TIME __RPC_FAR *pTimeEnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTime )( 
            IMediaSample2 __RPC_FAR * This,
            /* [in] */ REFERENCE_TIME __RPC_FAR *pTimeStart,
            /* [in] */ REFERENCE_TIME __RPC_FAR *pTimeEnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsSyncPoint )( 
            IMediaSample2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSyncPoint )( 
            IMediaSample2 __RPC_FAR * This,
            BOOL bIsSyncPoint);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsPreroll )( 
            IMediaSample2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPreroll )( 
            IMediaSample2 __RPC_FAR * This,
            BOOL bIsPreroll);
        
        long ( STDMETHODCALLTYPE __RPC_FAR *GetActualDataLength )( 
            IMediaSample2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetActualDataLength )( 
            IMediaSample2 __RPC_FAR * This,
            long __MIDL_0008);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMediaType )( 
            IMediaSample2 __RPC_FAR * This,
            AM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *ppMediaType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMediaType )( 
            IMediaSample2 __RPC_FAR * This,
            AM_MEDIA_TYPE __RPC_FAR *pMediaType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsDiscontinuity )( 
            IMediaSample2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDiscontinuity )( 
            IMediaSample2 __RPC_FAR * This,
            BOOL bDiscontinuity);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMediaTime )( 
            IMediaSample2 __RPC_FAR * This,
            /* [out] */ LONGLONG __RPC_FAR *pTimeStart,
            /* [out] */ LONGLONG __RPC_FAR *pTimeEnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMediaTime )( 
            IMediaSample2 __RPC_FAR * This,
            /* [in] */ LONGLONG __RPC_FAR *pTimeStart,
            /* [in] */ LONGLONG __RPC_FAR *pTimeEnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProperties )( 
            IMediaSample2 __RPC_FAR * This,
            /* [in] */ DWORD cbProperties,
            /* [size_is][out] */ BYTE __RPC_FAR *pbProperties);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetProperties )( 
            IMediaSample2 __RPC_FAR * This,
            /* [in] */ DWORD cbProperties,
            /* [size_is][in] */ const BYTE __RPC_FAR *pbProperties);
        
        END_INTERFACE
    } IMediaSample2Vtbl;

    interface IMediaSample2
    {
        CONST_VTBL struct IMediaSample2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaSample2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaSample2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaSample2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaSample2_GetPointer(This,ppBuffer)	\
    (This)->lpVtbl -> GetPointer(This,ppBuffer)

#define IMediaSample2_GetSize(This)	\
    (This)->lpVtbl -> GetSize(This)

#define IMediaSample2_GetTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> GetTime(This,pTimeStart,pTimeEnd)

#define IMediaSample2_SetTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> SetTime(This,pTimeStart,pTimeEnd)

#define IMediaSample2_IsSyncPoint(This)	\
    (This)->lpVtbl -> IsSyncPoint(This)

#define IMediaSample2_SetSyncPoint(This,bIsSyncPoint)	\
    (This)->lpVtbl -> SetSyncPoint(This,bIsSyncPoint)

#define IMediaSample2_IsPreroll(This)	\
    (This)->lpVtbl -> IsPreroll(This)

#define IMediaSample2_SetPreroll(This,bIsPreroll)	\
    (This)->lpVtbl -> SetPreroll(This,bIsPreroll)

#define IMediaSample2_GetActualDataLength(This)	\
    (This)->lpVtbl -> GetActualDataLength(This)

#define IMediaSample2_SetActualDataLength(This,__MIDL_0008)	\
    (This)->lpVtbl -> SetActualDataLength(This,__MIDL_0008)

#define IMediaSample2_GetMediaType(This,ppMediaType)	\
    (This)->lpVtbl -> GetMediaType(This,ppMediaType)

#define IMediaSample2_SetMediaType(This,pMediaType)	\
    (This)->lpVtbl -> SetMediaType(This,pMediaType)

#define IMediaSample2_IsDiscontinuity(This)	\
    (This)->lpVtbl -> IsDiscontinuity(This)

#define IMediaSample2_SetDiscontinuity(This,bDiscontinuity)	\
    (This)->lpVtbl -> SetDiscontinuity(This,bDiscontinuity)

#define IMediaSample2_GetMediaTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> GetMediaTime(This,pTimeStart,pTimeEnd)

#define IMediaSample2_SetMediaTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> SetMediaTime(This,pTimeStart,pTimeEnd)


#define IMediaSample2_GetProperties(This,cbProperties,pbProperties)	\
    (This)->lpVtbl -> GetProperties(This,cbProperties,pbProperties)

#define IMediaSample2_SetProperties(This,cbProperties,pbProperties)	\
    (This)->lpVtbl -> SetProperties(This,cbProperties,pbProperties)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMediaSample2_GetProperties_Proxy( 
    IMediaSample2 __RPC_FAR * This,
    /* [in] */ DWORD cbProperties,
    /* [size_is][out] */ BYTE __RPC_FAR *pbProperties);


void __RPC_STUB IMediaSample2_GetProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSample2_SetProperties_Proxy( 
    IMediaSample2 __RPC_FAR * This,
    /* [in] */ DWORD cbProperties,
    /* [size_is][in] */ const BYTE __RPC_FAR *pbProperties);


void __RPC_STUB IMediaSample2_SetProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMediaSample2_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0064
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef IMediaSample2 __RPC_FAR *PMEDIASAMPLE2;

#define AM_GBF_PREVFRAMESKIPPED 1
#define AM_GBF_NOTASYNCPOINT 2
#define AM_GBF_NOWAIT 4


extern RPC_IF_HANDLE __MIDL_itf_strmif_0064_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0064_v0_0_s_ifspec;

#ifndef __IMemAllocator_INTERFACE_DEFINED__
#define __IMemAllocator_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMemAllocator
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IMemAllocator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a8689c-0ad4-11ce-b03a-0020af0ba770")
    IMemAllocator : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetProperties( 
            /* [in] */ ALLOCATOR_PROPERTIES __RPC_FAR *pRequest,
            /* [out] */ ALLOCATOR_PROPERTIES __RPC_FAR *pActual) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetProperties( 
            /* [out] */ ALLOCATOR_PROPERTIES __RPC_FAR *pProps) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Commit( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Decommit( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBuffer( 
            /* [out] */ IMediaSample __RPC_FAR *__RPC_FAR *ppBuffer,
            /* [in] */ REFERENCE_TIME __RPC_FAR *pStartTime,
            /* [in] */ REFERENCE_TIME __RPC_FAR *pEndTime,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReleaseBuffer( 
            /* [in] */ IMediaSample __RPC_FAR *pBuffer) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMemAllocatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMemAllocator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMemAllocator __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMemAllocator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetProperties )( 
            IMemAllocator __RPC_FAR * This,
            /* [in] */ ALLOCATOR_PROPERTIES __RPC_FAR *pRequest,
            /* [out] */ ALLOCATOR_PROPERTIES __RPC_FAR *pActual);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProperties )( 
            IMemAllocator __RPC_FAR * This,
            /* [out] */ ALLOCATOR_PROPERTIES __RPC_FAR *pProps);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Commit )( 
            IMemAllocator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Decommit )( 
            IMemAllocator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBuffer )( 
            IMemAllocator __RPC_FAR * This,
            /* [out] */ IMediaSample __RPC_FAR *__RPC_FAR *ppBuffer,
            /* [in] */ REFERENCE_TIME __RPC_FAR *pStartTime,
            /* [in] */ REFERENCE_TIME __RPC_FAR *pEndTime,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseBuffer )( 
            IMemAllocator __RPC_FAR * This,
            /* [in] */ IMediaSample __RPC_FAR *pBuffer);
        
        END_INTERFACE
    } IMemAllocatorVtbl;

    interface IMemAllocator
    {
        CONST_VTBL struct IMemAllocatorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMemAllocator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMemAllocator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMemAllocator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMemAllocator_SetProperties(This,pRequest,pActual)	\
    (This)->lpVtbl -> SetProperties(This,pRequest,pActual)

#define IMemAllocator_GetProperties(This,pProps)	\
    (This)->lpVtbl -> GetProperties(This,pProps)

#define IMemAllocator_Commit(This)	\
    (This)->lpVtbl -> Commit(This)

#define IMemAllocator_Decommit(This)	\
    (This)->lpVtbl -> Decommit(This)

#define IMemAllocator_GetBuffer(This,ppBuffer,pStartTime,pEndTime,dwFlags)	\
    (This)->lpVtbl -> GetBuffer(This,ppBuffer,pStartTime,pEndTime,dwFlags)

#define IMemAllocator_ReleaseBuffer(This,pBuffer)	\
    (This)->lpVtbl -> ReleaseBuffer(This,pBuffer)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMemAllocator_SetProperties_Proxy( 
    IMemAllocator __RPC_FAR * This,
    /* [in] */ ALLOCATOR_PROPERTIES __RPC_FAR *pRequest,
    /* [out] */ ALLOCATOR_PROPERTIES __RPC_FAR *pActual);


void __RPC_STUB IMemAllocator_SetProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemAllocator_GetProperties_Proxy( 
    IMemAllocator __RPC_FAR * This,
    /* [out] */ ALLOCATOR_PROPERTIES __RPC_FAR *pProps);


void __RPC_STUB IMemAllocator_GetProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemAllocator_Commit_Proxy( 
    IMemAllocator __RPC_FAR * This);


void __RPC_STUB IMemAllocator_Commit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemAllocator_Decommit_Proxy( 
    IMemAllocator __RPC_FAR * This);


void __RPC_STUB IMemAllocator_Decommit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemAllocator_GetBuffer_Proxy( 
    IMemAllocator __RPC_FAR * This,
    /* [out] */ IMediaSample __RPC_FAR *__RPC_FAR *ppBuffer,
    /* [in] */ REFERENCE_TIME __RPC_FAR *pStartTime,
    /* [in] */ REFERENCE_TIME __RPC_FAR *pEndTime,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IMemAllocator_GetBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemAllocator_ReleaseBuffer_Proxy( 
    IMemAllocator __RPC_FAR * This,
    /* [in] */ IMediaSample __RPC_FAR *pBuffer);


void __RPC_STUB IMemAllocator_ReleaseBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMemAllocator_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0065
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef IMemAllocator __RPC_FAR *PMEMALLOCATOR;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0065_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0065_v0_0_s_ifspec;

#ifndef __IMemAllocator2_INTERFACE_DEFINED__
#define __IMemAllocator2_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMemAllocator2
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IMemAllocator2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("fa04cdc8-cb49-11d1-a4ef-00c04fb6fa12")
    IMemAllocator2 : public IMemAllocator
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetBusyCount( 
            DWORD __RPC_FAR *pdwBusyCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFreeCount( 
            DWORD __RPC_FAR *pdwFreeCount) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMemAllocator2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMemAllocator2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMemAllocator2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMemAllocator2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetProperties )( 
            IMemAllocator2 __RPC_FAR * This,
            /* [in] */ ALLOCATOR_PROPERTIES __RPC_FAR *pRequest,
            /* [out] */ ALLOCATOR_PROPERTIES __RPC_FAR *pActual);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProperties )( 
            IMemAllocator2 __RPC_FAR * This,
            /* [out] */ ALLOCATOR_PROPERTIES __RPC_FAR *pProps);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Commit )( 
            IMemAllocator2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Decommit )( 
            IMemAllocator2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBuffer )( 
            IMemAllocator2 __RPC_FAR * This,
            /* [out] */ IMediaSample __RPC_FAR *__RPC_FAR *ppBuffer,
            /* [in] */ REFERENCE_TIME __RPC_FAR *pStartTime,
            /* [in] */ REFERENCE_TIME __RPC_FAR *pEndTime,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseBuffer )( 
            IMemAllocator2 __RPC_FAR * This,
            /* [in] */ IMediaSample __RPC_FAR *pBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBusyCount )( 
            IMemAllocator2 __RPC_FAR * This,
            DWORD __RPC_FAR *pdwBusyCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFreeCount )( 
            IMemAllocator2 __RPC_FAR * This,
            DWORD __RPC_FAR *pdwFreeCount);
        
        END_INTERFACE
    } IMemAllocator2Vtbl;

    interface IMemAllocator2
    {
        CONST_VTBL struct IMemAllocator2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMemAllocator2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMemAllocator2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMemAllocator2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMemAllocator2_SetProperties(This,pRequest,pActual)	\
    (This)->lpVtbl -> SetProperties(This,pRequest,pActual)

#define IMemAllocator2_GetProperties(This,pProps)	\
    (This)->lpVtbl -> GetProperties(This,pProps)

#define IMemAllocator2_Commit(This)	\
    (This)->lpVtbl -> Commit(This)

#define IMemAllocator2_Decommit(This)	\
    (This)->lpVtbl -> Decommit(This)

#define IMemAllocator2_GetBuffer(This,ppBuffer,pStartTime,pEndTime,dwFlags)	\
    (This)->lpVtbl -> GetBuffer(This,ppBuffer,pStartTime,pEndTime,dwFlags)

#define IMemAllocator2_ReleaseBuffer(This,pBuffer)	\
    (This)->lpVtbl -> ReleaseBuffer(This,pBuffer)


#define IMemAllocator2_GetBusyCount(This,pdwBusyCount)	\
    (This)->lpVtbl -> GetBusyCount(This,pdwBusyCount)

#define IMemAllocator2_GetFreeCount(This,pdwFreeCount)	\
    (This)->lpVtbl -> GetFreeCount(This,pdwFreeCount)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMemAllocator2_GetBusyCount_Proxy( 
    IMemAllocator2 __RPC_FAR * This,
    DWORD __RPC_FAR *pdwBusyCount);


void __RPC_STUB IMemAllocator2_GetBusyCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemAllocator2_GetFreeCount_Proxy( 
    IMemAllocator2 __RPC_FAR * This,
    DWORD __RPC_FAR *pdwFreeCount);


void __RPC_STUB IMemAllocator2_GetFreeCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMemAllocator2_INTERFACE_DEFINED__ */


#ifndef __IMemInputPin_INTERFACE_DEFINED__
#define __IMemInputPin_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMemInputPin
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IMemInputPin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a8689d-0ad4-11ce-b03a-0020af0ba770")
    IMemInputPin : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAllocator( 
            /* [out] */ IMemAllocator __RPC_FAR *__RPC_FAR *ppAllocator) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NotifyAllocator( 
            /* [in] */ IMemAllocator __RPC_FAR *pAllocator,
            /* [in] */ BOOL bReadOnly) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAllocatorRequirements( 
            /* [out] */ ALLOCATOR_PROPERTIES __RPC_FAR *pProps) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Receive( 
            /* [in] */ IMediaSample __RPC_FAR *pSample) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReceiveMultiple( 
            /* [size_is][in] */ IMediaSample __RPC_FAR *__RPC_FAR *pSamples,
            /* [in] */ long nSamples,
            /* [out] */ long __RPC_FAR *nSamplesProcessed) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReceiveCanBlock( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMemInputPinVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMemInputPin __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMemInputPin __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMemInputPin __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAllocator )( 
            IMemInputPin __RPC_FAR * This,
            /* [out] */ IMemAllocator __RPC_FAR *__RPC_FAR *ppAllocator);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NotifyAllocator )( 
            IMemInputPin __RPC_FAR * This,
            /* [in] */ IMemAllocator __RPC_FAR *pAllocator,
            /* [in] */ BOOL bReadOnly);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAllocatorRequirements )( 
            IMemInputPin __RPC_FAR * This,
            /* [out] */ ALLOCATOR_PROPERTIES __RPC_FAR *pProps);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Receive )( 
            IMemInputPin __RPC_FAR * This,
            /* [in] */ IMediaSample __RPC_FAR *pSample);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReceiveMultiple )( 
            IMemInputPin __RPC_FAR * This,
            /* [size_is][in] */ IMediaSample __RPC_FAR *__RPC_FAR *pSamples,
            /* [in] */ long nSamples,
            /* [out] */ long __RPC_FAR *nSamplesProcessed);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReceiveCanBlock )( 
            IMemInputPin __RPC_FAR * This);
        
        END_INTERFACE
    } IMemInputPinVtbl;

    interface IMemInputPin
    {
        CONST_VTBL struct IMemInputPinVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMemInputPin_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMemInputPin_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMemInputPin_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMemInputPin_GetAllocator(This,ppAllocator)	\
    (This)->lpVtbl -> GetAllocator(This,ppAllocator)

#define IMemInputPin_NotifyAllocator(This,pAllocator,bReadOnly)	\
    (This)->lpVtbl -> NotifyAllocator(This,pAllocator,bReadOnly)

#define IMemInputPin_GetAllocatorRequirements(This,pProps)	\
    (This)->lpVtbl -> GetAllocatorRequirements(This,pProps)

#define IMemInputPin_Receive(This,pSample)	\
    (This)->lpVtbl -> Receive(This,pSample)

#define IMemInputPin_ReceiveMultiple(This,pSamples,nSamples,nSamplesProcessed)	\
    (This)->lpVtbl -> ReceiveMultiple(This,pSamples,nSamples,nSamplesProcessed)

#define IMemInputPin_ReceiveCanBlock(This)	\
    (This)->lpVtbl -> ReceiveCanBlock(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMemInputPin_GetAllocator_Proxy( 
    IMemInputPin __RPC_FAR * This,
    /* [out] */ IMemAllocator __RPC_FAR *__RPC_FAR *ppAllocator);


void __RPC_STUB IMemInputPin_GetAllocator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemInputPin_NotifyAllocator_Proxy( 
    IMemInputPin __RPC_FAR * This,
    /* [in] */ IMemAllocator __RPC_FAR *pAllocator,
    /* [in] */ BOOL bReadOnly);


void __RPC_STUB IMemInputPin_NotifyAllocator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemInputPin_GetAllocatorRequirements_Proxy( 
    IMemInputPin __RPC_FAR * This,
    /* [out] */ ALLOCATOR_PROPERTIES __RPC_FAR *pProps);


void __RPC_STUB IMemInputPin_GetAllocatorRequirements_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemInputPin_Receive_Proxy( 
    IMemInputPin __RPC_FAR * This,
    /* [in] */ IMediaSample __RPC_FAR *pSample);


void __RPC_STUB IMemInputPin_Receive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemInputPin_ReceiveMultiple_Proxy( 
    IMemInputPin __RPC_FAR * This,
    /* [size_is][in] */ IMediaSample __RPC_FAR *__RPC_FAR *pSamples,
    /* [in] */ long nSamples,
    /* [out] */ long __RPC_FAR *nSamplesProcessed);


void __RPC_STUB IMemInputPin_ReceiveMultiple_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemInputPin_ReceiveCanBlock_Proxy( 
    IMemInputPin __RPC_FAR * This);


void __RPC_STUB IMemInputPin_ReceiveCanBlock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMemInputPin_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0067
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef IMemInputPin __RPC_FAR *PMEMINPUTPIN;

typedef 
enum AM_SEEKING_SeekingFlags
    {	AM_SEEKING_NoPositioning	= 0,
	AM_SEEKING_AbsolutePositioning	= 0x1,
	AM_SEEKING_RelativePositioning	= 0x2,
	AM_SEEKING_IncrementalPositioning	= 0x3,
	AM_SEEKING_PositioningBitsMask	= 0x3,
	AM_SEEKING_SeekToKeyFrame	= 0x4,
	AM_SEEKING_ReturnTime	= 0x8,
	AM_SEEKING_Segment	= 0x10,
	AM_SEEKING_NoFlush	= 0x20
    }	AM_SEEKING_SEEKING_FLAGS;

typedef 
enum AM_SEEKING_SeekingCapabilities
    {	AM_SEEKING_CanSeekAbsolute	= 0x1,
	AM_SEEKING_CanSeekForwards	= 0x2,
	AM_SEEKING_CanSeekBackwards	= 0x4,
	AM_SEEKING_CanGetCurrentPos	= 0x8,
	AM_SEEKING_CanGetStopPos	= 0x10,
	AM_SEEKING_CanGetDuration	= 0x20,
	AM_SEEKING_CanPlayBackwards	= 0x40,
	AM_SEEKING_CanDoSegments	= 0x80,
	AM_SEEKING_Source	= 0x100
    }	AM_SEEKING_SEEKING_CAPABILITIES;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0067_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0067_v0_0_s_ifspec;

#ifndef __IMediaSeeking_INTERFACE_DEFINED__
#define __IMediaSeeking_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMediaSeeking
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IMediaSeeking;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("36b73880-c2c8-11cf-8b46-00805f6cef60")
    IMediaSeeking : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCapabilities( 
            /* [out] */ DWORD __RPC_FAR *pCapabilities) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckCapabilities( 
            /* [out][in] */ DWORD __RPC_FAR *pCapabilities) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsFormatSupported( 
            /* [in] */ const GUID __RPC_FAR *pFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QueryPreferredFormat( 
            /* [out] */ GUID __RPC_FAR *pFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTimeFormat( 
            /* [out] */ GUID __RPC_FAR *pFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsUsingTimeFormat( 
            /* [in] */ const GUID __RPC_FAR *pFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTimeFormat( 
            /* [in] */ const GUID __RPC_FAR *pFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDuration( 
            /* [out] */ LONGLONG __RPC_FAR *pDuration) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStopPosition( 
            /* [out] */ LONGLONG __RPC_FAR *pStop) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentPosition( 
            /* [out] */ LONGLONG __RPC_FAR *pCurrent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConvertTimeFormat( 
            /* [out] */ LONGLONG __RPC_FAR *pTarget,
            /* [in] */ const GUID __RPC_FAR *pTargetFormat,
            /* [in] */ LONGLONG Source,
            /* [in] */ const GUID __RPC_FAR *pSourceFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPositions( 
            /* [out][in] */ LONGLONG __RPC_FAR *pCurrent,
            /* [in] */ DWORD dwCurrentFlags,
            /* [out][in] */ LONGLONG __RPC_FAR *pStop,
            /* [in] */ DWORD dwStopFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPositions( 
            /* [out] */ LONGLONG __RPC_FAR *pCurrent,
            /* [out] */ LONGLONG __RPC_FAR *pStop) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAvailable( 
            /* [out] */ LONGLONG __RPC_FAR *pEarliest,
            /* [out] */ LONGLONG __RPC_FAR *pLatest) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetRate( 
            /* [in] */ double dRate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRate( 
            /* [out] */ double __RPC_FAR *pdRate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPreroll( 
            /* [out] */ LONGLONG __RPC_FAR *pllPreroll) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMediaSeekingVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMediaSeeking __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMediaSeeking __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMediaSeeking __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCapabilities )( 
            IMediaSeeking __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pCapabilities);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckCapabilities )( 
            IMediaSeeking __RPC_FAR * This,
            /* [out][in] */ DWORD __RPC_FAR *pCapabilities);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsFormatSupported )( 
            IMediaSeeking __RPC_FAR * This,
            /* [in] */ const GUID __RPC_FAR *pFormat);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryPreferredFormat )( 
            IMediaSeeking __RPC_FAR * This,
            /* [out] */ GUID __RPC_FAR *pFormat);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTimeFormat )( 
            IMediaSeeking __RPC_FAR * This,
            /* [out] */ GUID __RPC_FAR *pFormat);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsUsingTimeFormat )( 
            IMediaSeeking __RPC_FAR * This,
            /* [in] */ const GUID __RPC_FAR *pFormat);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTimeFormat )( 
            IMediaSeeking __RPC_FAR * This,
            /* [in] */ const GUID __RPC_FAR *pFormat);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDuration )( 
            IMediaSeeking __RPC_FAR * This,
            /* [out] */ LONGLONG __RPC_FAR *pDuration);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStopPosition )( 
            IMediaSeeking __RPC_FAR * This,
            /* [out] */ LONGLONG __RPC_FAR *pStop);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCurrentPosition )( 
            IMediaSeeking __RPC_FAR * This,
            /* [out] */ LONGLONG __RPC_FAR *pCurrent);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConvertTimeFormat )( 
            IMediaSeeking __RPC_FAR * This,
            /* [out] */ LONGLONG __RPC_FAR *pTarget,
            /* [in] */ const GUID __RPC_FAR *pTargetFormat,
            /* [in] */ LONGLONG Source,
            /* [in] */ const GUID __RPC_FAR *pSourceFormat);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPositions )( 
            IMediaSeeking __RPC_FAR * This,
            /* [out][in] */ LONGLONG __RPC_FAR *pCurrent,
            /* [in] */ DWORD dwCurrentFlags,
            /* [out][in] */ LONGLONG __RPC_FAR *pStop,
            /* [in] */ DWORD dwStopFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPositions )( 
            IMediaSeeking __RPC_FAR * This,
            /* [out] */ LONGLONG __RPC_FAR *pCurrent,
            /* [out] */ LONGLONG __RPC_FAR *pStop);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAvailable )( 
            IMediaSeeking __RPC_FAR * This,
            /* [out] */ LONGLONG __RPC_FAR *pEarliest,
            /* [out] */ LONGLONG __RPC_FAR *pLatest);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetRate )( 
            IMediaSeeking __RPC_FAR * This,
            /* [in] */ double dRate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRate )( 
            IMediaSeeking __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *pdRate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPreroll )( 
            IMediaSeeking __RPC_FAR * This,
            /* [out] */ LONGLONG __RPC_FAR *pllPreroll);
        
        END_INTERFACE
    } IMediaSeekingVtbl;

    interface IMediaSeeking
    {
        CONST_VTBL struct IMediaSeekingVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaSeeking_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaSeeking_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaSeeking_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaSeeking_GetCapabilities(This,pCapabilities)	\
    (This)->lpVtbl -> GetCapabilities(This,pCapabilities)

#define IMediaSeeking_CheckCapabilities(This,pCapabilities)	\
    (This)->lpVtbl -> CheckCapabilities(This,pCapabilities)

#define IMediaSeeking_IsFormatSupported(This,pFormat)	\
    (This)->lpVtbl -> IsFormatSupported(This,pFormat)

#define IMediaSeeking_QueryPreferredFormat(This,pFormat)	\
    (This)->lpVtbl -> QueryPreferredFormat(This,pFormat)

#define IMediaSeeking_GetTimeFormat(This,pFormat)	\
    (This)->lpVtbl -> GetTimeFormat(This,pFormat)

#define IMediaSeeking_IsUsingTimeFormat(This,pFormat)	\
    (This)->lpVtbl -> IsUsingTimeFormat(This,pFormat)

#define IMediaSeeking_SetTimeFormat(This,pFormat)	\
    (This)->lpVtbl -> SetTimeFormat(This,pFormat)

#define IMediaSeeking_GetDuration(This,pDuration)	\
    (This)->lpVtbl -> GetDuration(This,pDuration)

#define IMediaSeeking_GetStopPosition(This,pStop)	\
    (This)->lpVtbl -> GetStopPosition(This,pStop)

#define IMediaSeeking_GetCurrentPosition(This,pCurrent)	\
    (This)->lpVtbl -> GetCurrentPosition(This,pCurrent)

#define IMediaSeeking_ConvertTimeFormat(This,pTarget,pTargetFormat,Source,pSourceFormat)	\
    (This)->lpVtbl -> ConvertTimeFormat(This,pTarget,pTargetFormat,Source,pSourceFormat)

#define IMediaSeeking_SetPositions(This,pCurrent,dwCurrentFlags,pStop,dwStopFlags)	\
    (This)->lpVtbl -> SetPositions(This,pCurrent,dwCurrentFlags,pStop,dwStopFlags)

#define IMediaSeeking_GetPositions(This,pCurrent,pStop)	\
    (This)->lpVtbl -> GetPositions(This,pCurrent,pStop)

#define IMediaSeeking_GetAvailable(This,pEarliest,pLatest)	\
    (This)->lpVtbl -> GetAvailable(This,pEarliest,pLatest)

#define IMediaSeeking_SetRate(This,dRate)	\
    (This)->lpVtbl -> SetRate(This,dRate)

#define IMediaSeeking_GetRate(This,pdRate)	\
    (This)->lpVtbl -> GetRate(This,pdRate)

#define IMediaSeeking_GetPreroll(This,pllPreroll)	\
    (This)->lpVtbl -> GetPreroll(This,pllPreroll)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMediaSeeking_GetCapabilities_Proxy( 
    IMediaSeeking __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pCapabilities);


void __RPC_STUB IMediaSeeking_GetCapabilities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_CheckCapabilities_Proxy( 
    IMediaSeeking __RPC_FAR * This,
    /* [out][in] */ DWORD __RPC_FAR *pCapabilities);


void __RPC_STUB IMediaSeeking_CheckCapabilities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_IsFormatSupported_Proxy( 
    IMediaSeeking __RPC_FAR * This,
    /* [in] */ const GUID __RPC_FAR *pFormat);


void __RPC_STUB IMediaSeeking_IsFormatSupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_QueryPreferredFormat_Proxy( 
    IMediaSeeking __RPC_FAR * This,
    /* [out] */ GUID __RPC_FAR *pFormat);


void __RPC_STUB IMediaSeeking_QueryPreferredFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_GetTimeFormat_Proxy( 
    IMediaSeeking __RPC_FAR * This,
    /* [out] */ GUID __RPC_FAR *pFormat);


void __RPC_STUB IMediaSeeking_GetTimeFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_IsUsingTimeFormat_Proxy( 
    IMediaSeeking __RPC_FAR * This,
    /* [in] */ const GUID __RPC_FAR *pFormat);


void __RPC_STUB IMediaSeeking_IsUsingTimeFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_SetTimeFormat_Proxy( 
    IMediaSeeking __RPC_FAR * This,
    /* [in] */ const GUID __RPC_FAR *pFormat);


void __RPC_STUB IMediaSeeking_SetTimeFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_GetDuration_Proxy( 
    IMediaSeeking __RPC_FAR * This,
    /* [out] */ LONGLONG __RPC_FAR *pDuration);


void __RPC_STUB IMediaSeeking_GetDuration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_GetStopPosition_Proxy( 
    IMediaSeeking __RPC_FAR * This,
    /* [out] */ LONGLONG __RPC_FAR *pStop);


void __RPC_STUB IMediaSeeking_GetStopPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_GetCurrentPosition_Proxy( 
    IMediaSeeking __RPC_FAR * This,
    /* [out] */ LONGLONG __RPC_FAR *pCurrent);


void __RPC_STUB IMediaSeeking_GetCurrentPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_ConvertTimeFormat_Proxy( 
    IMediaSeeking __RPC_FAR * This,
    /* [out] */ LONGLONG __RPC_FAR *pTarget,
    /* [in] */ const GUID __RPC_FAR *pTargetFormat,
    /* [in] */ LONGLONG Source,
    /* [in] */ const GUID __RPC_FAR *pSourceFormat);


void __RPC_STUB IMediaSeeking_ConvertTimeFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_SetPositions_Proxy( 
    IMediaSeeking __RPC_FAR * This,
    /* [out][in] */ LONGLONG __RPC_FAR *pCurrent,
    /* [in] */ DWORD dwCurrentFlags,
    /* [out][in] */ LONGLONG __RPC_FAR *pStop,
    /* [in] */ DWORD dwStopFlags);


void __RPC_STUB IMediaSeeking_SetPositions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_GetPositions_Proxy( 
    IMediaSeeking __RPC_FAR * This,
    /* [out] */ LONGLONG __RPC_FAR *pCurrent,
    /* [out] */ LONGLONG __RPC_FAR *pStop);


void __RPC_STUB IMediaSeeking_GetPositions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_GetAvailable_Proxy( 
    IMediaSeeking __RPC_FAR * This,
    /* [out] */ LONGLONG __RPC_FAR *pEarliest,
    /* [out] */ LONGLONG __RPC_FAR *pLatest);


void __RPC_STUB IMediaSeeking_GetAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_SetRate_Proxy( 
    IMediaSeeking __RPC_FAR * This,
    /* [in] */ double dRate);


void __RPC_STUB IMediaSeeking_SetRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_GetRate_Proxy( 
    IMediaSeeking __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *pdRate);


void __RPC_STUB IMediaSeeking_GetRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaSeeking_GetPreroll_Proxy( 
    IMediaSeeking __RPC_FAR * This,
    /* [out] */ LONGLONG __RPC_FAR *pllPreroll);


void __RPC_STUB IMediaSeeking_GetPreroll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMediaSeeking_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0068
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef IMediaSeeking __RPC_FAR *PMEDIASEEKING;

enum tagAM_MEDIAEVENT_FLAGS
{
    AM_MEDIAEVENT_NONOTIFY = 0x01
};











typedef /* [public][public] */ struct  __MIDL___MIDL_itf_strmif_0068_0001
    {
    CLSID Clsid;
    LPWSTR Name;
    }	REGFILTER;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0068_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0068_v0_0_s_ifspec;

#ifndef __IEnumRegFilters_INTERFACE_DEFINED__
#define __IEnumRegFilters_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IEnumRegFilters
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IEnumRegFilters;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a868a4-0ad4-11ce-b03a-0020af0ba770")
    IEnumRegFilters : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG cFilters,
            /* [out] */ REGFILTER __RPC_FAR *__RPC_FAR *apRegFilter,
            /* [out] */ ULONG __RPC_FAR *pcFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG cFilters) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumRegFilters __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumRegFiltersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumRegFilters __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumRegFilters __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumRegFilters __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumRegFilters __RPC_FAR * This,
            /* [in] */ ULONG cFilters,
            /* [out] */ REGFILTER __RPC_FAR *__RPC_FAR *apRegFilter,
            /* [out] */ ULONG __RPC_FAR *pcFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumRegFilters __RPC_FAR * This,
            /* [in] */ ULONG cFilters);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumRegFilters __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumRegFilters __RPC_FAR * This,
            /* [out] */ IEnumRegFilters __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IEnumRegFiltersVtbl;

    interface IEnumRegFilters
    {
        CONST_VTBL struct IEnumRegFiltersVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumRegFilters_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumRegFilters_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumRegFilters_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumRegFilters_Next(This,cFilters,apRegFilter,pcFetched)	\
    (This)->lpVtbl -> Next(This,cFilters,apRegFilter,pcFetched)

#define IEnumRegFilters_Skip(This,cFilters)	\
    (This)->lpVtbl -> Skip(This,cFilters)

#define IEnumRegFilters_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumRegFilters_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumRegFilters_Next_Proxy( 
    IEnumRegFilters __RPC_FAR * This,
    /* [in] */ ULONG cFilters,
    /* [out] */ REGFILTER __RPC_FAR *__RPC_FAR *apRegFilter,
    /* [out] */ ULONG __RPC_FAR *pcFetched);


void __RPC_STUB IEnumRegFilters_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumRegFilters_Skip_Proxy( 
    IEnumRegFilters __RPC_FAR * This,
    /* [in] */ ULONG cFilters);


void __RPC_STUB IEnumRegFilters_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumRegFilters_Reset_Proxy( 
    IEnumRegFilters __RPC_FAR * This);


void __RPC_STUB IEnumRegFilters_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumRegFilters_Clone_Proxy( 
    IEnumRegFilters __RPC_FAR * This,
    /* [out] */ IEnumRegFilters __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IEnumRegFilters_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumRegFilters_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0070
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef IEnumRegFilters __RPC_FAR *PENUMREGFILTERS;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0070_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0070_v0_0_s_ifspec;

#ifndef __IFilterMapper_INTERFACE_DEFINED__
#define __IFilterMapper_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IFilterMapper
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



enum __MIDL_IFilterMapper_0001
    {	MERIT_PREFERRED	= 0x800000,
	MERIT_NORMAL	= 0x600000,
	MERIT_UNLIKELY	= 0x400000,
	MERIT_DO_NOT_USE	= 0x200000
    };

EXTERN_C const IID IID_IFilterMapper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a868a3-0ad4-11ce-b03a-0020af0ba770")
    IFilterMapper : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RegisterFilter( 
            /* [in] */ CLSID clsid,
            /* [in] */ LPCWSTR Name,
            /* [in] */ DWORD dwMerit) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RegisterFilterInstance( 
            /* [in] */ CLSID clsid,
            /* [in] */ LPCWSTR Name,
            /* [out] */ CLSID __RPC_FAR *MRId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RegisterPin( 
            /* [in] */ CLSID Filter,
            /* [in] */ LPCWSTR Name,
            /* [in] */ BOOL bRendered,
            /* [in] */ BOOL bOutput,
            /* [in] */ BOOL bZero,
            /* [in] */ BOOL bMany,
            /* [in] */ CLSID ConnectsToFilter,
            /* [in] */ LPCWSTR ConnectsToPin) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RegisterPinType( 
            /* [in] */ CLSID clsFilter,
            /* [in] */ LPCWSTR strName,
            /* [in] */ CLSID clsMajorType,
            /* [in] */ CLSID clsSubType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnregisterFilter( 
            /* [in] */ CLSID Filter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnregisterFilterInstance( 
            /* [in] */ CLSID MRId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnregisterPin( 
            /* [in] */ CLSID Filter,
            /* [in] */ LPCWSTR Name) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumMatchingFilters( 
            /* [out] */ IEnumRegFilters __RPC_FAR *__RPC_FAR *ppEnum,
            /* [in] */ DWORD dwMerit,
            /* [in] */ BOOL bInputNeeded,
            /* [in] */ CLSID clsInMaj,
            /* [in] */ CLSID clsInSub,
            /* [in] */ BOOL bRender,
            /* [in] */ BOOL bOututNeeded,
            /* [in] */ CLSID clsOutMaj,
            /* [in] */ CLSID clsOutSub) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFilterMapperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFilterMapper __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFilterMapper __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFilterMapper __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterFilter )( 
            IFilterMapper __RPC_FAR * This,
            /* [in] */ CLSID clsid,
            /* [in] */ LPCWSTR Name,
            /* [in] */ DWORD dwMerit);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterFilterInstance )( 
            IFilterMapper __RPC_FAR * This,
            /* [in] */ CLSID clsid,
            /* [in] */ LPCWSTR Name,
            /* [out] */ CLSID __RPC_FAR *MRId);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterPin )( 
            IFilterMapper __RPC_FAR * This,
            /* [in] */ CLSID Filter,
            /* [in] */ LPCWSTR Name,
            /* [in] */ BOOL bRendered,
            /* [in] */ BOOL bOutput,
            /* [in] */ BOOL bZero,
            /* [in] */ BOOL bMany,
            /* [in] */ CLSID ConnectsToFilter,
            /* [in] */ LPCWSTR ConnectsToPin);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterPinType )( 
            IFilterMapper __RPC_FAR * This,
            /* [in] */ CLSID clsFilter,
            /* [in] */ LPCWSTR strName,
            /* [in] */ CLSID clsMajorType,
            /* [in] */ CLSID clsSubType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnregisterFilter )( 
            IFilterMapper __RPC_FAR * This,
            /* [in] */ CLSID Filter);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnregisterFilterInstance )( 
            IFilterMapper __RPC_FAR * This,
            /* [in] */ CLSID MRId);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnregisterPin )( 
            IFilterMapper __RPC_FAR * This,
            /* [in] */ CLSID Filter,
            /* [in] */ LPCWSTR Name);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumMatchingFilters )( 
            IFilterMapper __RPC_FAR * This,
            /* [out] */ IEnumRegFilters __RPC_FAR *__RPC_FAR *ppEnum,
            /* [in] */ DWORD dwMerit,
            /* [in] */ BOOL bInputNeeded,
            /* [in] */ CLSID clsInMaj,
            /* [in] */ CLSID clsInSub,
            /* [in] */ BOOL bRender,
            /* [in] */ BOOL bOututNeeded,
            /* [in] */ CLSID clsOutMaj,
            /* [in] */ CLSID clsOutSub);
        
        END_INTERFACE
    } IFilterMapperVtbl;

    interface IFilterMapper
    {
        CONST_VTBL struct IFilterMapperVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFilterMapper_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFilterMapper_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFilterMapper_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFilterMapper_RegisterFilter(This,clsid,Name,dwMerit)	\
    (This)->lpVtbl -> RegisterFilter(This,clsid,Name,dwMerit)

#define IFilterMapper_RegisterFilterInstance(This,clsid,Name,MRId)	\
    (This)->lpVtbl -> RegisterFilterInstance(This,clsid,Name,MRId)

#define IFilterMapper_RegisterPin(This,Filter,Name,bRendered,bOutput,bZero,bMany,ConnectsToFilter,ConnectsToPin)	\
    (This)->lpVtbl -> RegisterPin(This,Filter,Name,bRendered,bOutput,bZero,bMany,ConnectsToFilter,ConnectsToPin)

#define IFilterMapper_RegisterPinType(This,clsFilter,strName,clsMajorType,clsSubType)	\
    (This)->lpVtbl -> RegisterPinType(This,clsFilter,strName,clsMajorType,clsSubType)

#define IFilterMapper_UnregisterFilter(This,Filter)	\
    (This)->lpVtbl -> UnregisterFilter(This,Filter)

#define IFilterMapper_UnregisterFilterInstance(This,MRId)	\
    (This)->lpVtbl -> UnregisterFilterInstance(This,MRId)

#define IFilterMapper_UnregisterPin(This,Filter,Name)	\
    (This)->lpVtbl -> UnregisterPin(This,Filter,Name)

#define IFilterMapper_EnumMatchingFilters(This,ppEnum,dwMerit,bInputNeeded,clsInMaj,clsInSub,bRender,bOututNeeded,clsOutMaj,clsOutSub)	\
    (This)->lpVtbl -> EnumMatchingFilters(This,ppEnum,dwMerit,bInputNeeded,clsInMaj,clsInSub,bRender,bOututNeeded,clsOutMaj,clsOutSub)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFilterMapper_RegisterFilter_Proxy( 
    IFilterMapper __RPC_FAR * This,
    /* [in] */ CLSID clsid,
    /* [in] */ LPCWSTR Name,
    /* [in] */ DWORD dwMerit);


void __RPC_STUB IFilterMapper_RegisterFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterMapper_RegisterFilterInstance_Proxy( 
    IFilterMapper __RPC_FAR * This,
    /* [in] */ CLSID clsid,
    /* [in] */ LPCWSTR Name,
    /* [out] */ CLSID __RPC_FAR *MRId);


void __RPC_STUB IFilterMapper_RegisterFilterInstance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterMapper_RegisterPin_Proxy( 
    IFilterMapper __RPC_FAR * This,
    /* [in] */ CLSID Filter,
    /* [in] */ LPCWSTR Name,
    /* [in] */ BOOL bRendered,
    /* [in] */ BOOL bOutput,
    /* [in] */ BOOL bZero,
    /* [in] */ BOOL bMany,
    /* [in] */ CLSID ConnectsToFilter,
    /* [in] */ LPCWSTR ConnectsToPin);


void __RPC_STUB IFilterMapper_RegisterPin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterMapper_RegisterPinType_Proxy( 
    IFilterMapper __RPC_FAR * This,
    /* [in] */ CLSID clsFilter,
    /* [in] */ LPCWSTR strName,
    /* [in] */ CLSID clsMajorType,
    /* [in] */ CLSID clsSubType);


void __RPC_STUB IFilterMapper_RegisterPinType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterMapper_UnregisterFilter_Proxy( 
    IFilterMapper __RPC_FAR * This,
    /* [in] */ CLSID Filter);


void __RPC_STUB IFilterMapper_UnregisterFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterMapper_UnregisterFilterInstance_Proxy( 
    IFilterMapper __RPC_FAR * This,
    /* [in] */ CLSID MRId);


void __RPC_STUB IFilterMapper_UnregisterFilterInstance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterMapper_UnregisterPin_Proxy( 
    IFilterMapper __RPC_FAR * This,
    /* [in] */ CLSID Filter,
    /* [in] */ LPCWSTR Name);


void __RPC_STUB IFilterMapper_UnregisterPin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterMapper_EnumMatchingFilters_Proxy( 
    IFilterMapper __RPC_FAR * This,
    /* [out] */ IEnumRegFilters __RPC_FAR *__RPC_FAR *ppEnum,
    /* [in] */ DWORD dwMerit,
    /* [in] */ BOOL bInputNeeded,
    /* [in] */ CLSID clsInMaj,
    /* [in] */ CLSID clsInSub,
    /* [in] */ BOOL bRender,
    /* [in] */ BOOL bOututNeeded,
    /* [in] */ CLSID clsOutMaj,
    /* [in] */ CLSID clsOutSub);


void __RPC_STUB IFilterMapper_EnumMatchingFilters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFilterMapper_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0072
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef /* [public][public] */ struct  __MIDL___MIDL_itf_strmif_0072_0001
    {
    const CLSID __RPC_FAR *clsMajorType;
    const CLSID __RPC_FAR *clsMinorType;
    }	REGPINTYPES;

typedef /* [public] */ struct  __MIDL___MIDL_itf_strmif_0072_0002
    {
    LPWSTR strName;
    BOOL bRendered;
    BOOL bOutput;
    BOOL bZero;
    BOOL bMany;
    const CLSID __RPC_FAR *clsConnectsToFilter;
    const WCHAR __RPC_FAR *strConnectsToPin;
    UINT nMediaTypes;
    const REGPINTYPES __RPC_FAR *lpMediaType;
    }	REGFILTERPINS;

typedef 
enum tagQualityMessageType
    {	Famine	= 0,
	Flood	= Famine + 1
    }	QualityMessageType;

typedef struct  tagQuality
    {
    QualityMessageType Type;
    long Proportion;
    REFERENCE_TIME Late;
    REFERENCE_TIME TimeStamp;
    }	Quality;

typedef IQualityControl __RPC_FAR *PQUALITYCONTROL;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0072_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0072_v0_0_s_ifspec;

#ifndef __IQualityControl_INTERFACE_DEFINED__
#define __IQualityControl_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IQualityControl
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IQualityControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a868a5-0ad4-11ce-b03a-0020af0ba770")
    IQualityControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Notify( 
            /* [in] */ IBaseFilter __RPC_FAR *pSelf,
            /* [in] */ Quality q) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSink( 
            /* [in] */ IQualityControl __RPC_FAR *piqc) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IQualityControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IQualityControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IQualityControl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IQualityControl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Notify )( 
            IQualityControl __RPC_FAR * This,
            /* [in] */ IBaseFilter __RPC_FAR *pSelf,
            /* [in] */ Quality q);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSink )( 
            IQualityControl __RPC_FAR * This,
            /* [in] */ IQualityControl __RPC_FAR *piqc);
        
        END_INTERFACE
    } IQualityControlVtbl;

    interface IQualityControl
    {
        CONST_VTBL struct IQualityControlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IQualityControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IQualityControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IQualityControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IQualityControl_Notify(This,pSelf,q)	\
    (This)->lpVtbl -> Notify(This,pSelf,q)

#define IQualityControl_SetSink(This,piqc)	\
    (This)->lpVtbl -> SetSink(This,piqc)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IQualityControl_Notify_Proxy( 
    IQualityControl __RPC_FAR * This,
    /* [in] */ IBaseFilter __RPC_FAR *pSelf,
    /* [in] */ Quality q);


void __RPC_STUB IQualityControl_Notify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IQualityControl_SetSink_Proxy( 
    IQualityControl __RPC_FAR * This,
    /* [in] */ IQualityControl __RPC_FAR *piqc);


void __RPC_STUB IQualityControl_SetSink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IQualityControl_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0073
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 



enum __MIDL___MIDL_itf_strmif_0073_0001
    {	CK_NOCOLORKEY	= 0,
	CK_INDEX	= 0x1,
	CK_RGB	= 0x2
    };
typedef struct  tagCOLORKEY
    {
    DWORD KeyType;
    DWORD PaletteIndex;
    COLORREF LowColorValue;
    COLORREF HighColorValue;
    }	COLORKEY;


enum __MIDL___MIDL_itf_strmif_0073_0002
    {	ADVISE_NONE	= 0,
	ADVISE_CLIPPING	= 0x1,
	ADVISE_PALETTE	= 0x2,
	ADVISE_COLORKEY	= 0x4,
	ADVISE_POSITION	= 0x8
    };
#define	ADVISE_ALL	( ADVISE_CLIPPING | ADVISE_PALETTE | ADVISE_COLORKEY | ADVISE_POSITION )

#ifdef UNDER_CE
#define _WINGDI_	_WINGDI_H_
#endif
typedef struct  _RGNDATAHEADER1
    {
    DWORD dwSize;
    DWORD iType;
    DWORD nCount;
    DWORD nRgnSize;
    RECT rcBound;
    }	RGNDATAHEADER1;

typedef struct  _RGNDATA1
    {
    RGNDATAHEADER1 rdh;
    char Buffer[ 1 ];
    }	RGNDATA1;

#define RGNDATAHEADER RGNDATAHEADER1
#define RGNDATA       RGNDATA1
#ifndef _WINGDI_
typedef struct  _RGNDATAHEADER
    {
    DWORD dwSize;
    DWORD iType;
    DWORD nCount;
    DWORD nRgnSize;
    RECT rcBound;
    }	RGNDATAHEADER;

typedef struct  _RGNDATA
    {
    RGNDATAHEADER rdh;
    char Buffer[ 1 ];
    }	RGNDATA;

#endif


extern RPC_IF_HANDLE __MIDL_itf_strmif_0073_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0073_v0_0_s_ifspec;

#ifndef __IOverlayNotify_INTERFACE_DEFINED__
#define __IOverlayNotify_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IOverlayNotify
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][local][object] */ 



EXTERN_C const IID IID_IOverlayNotify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a868a0-0ad4-11ce-b03a-0020af0ba770")
    IOverlayNotify : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnPaletteChange( 
            /* [in] */ DWORD dwColors,
            /* [in] */ const PALETTEENTRY __RPC_FAR *pPalette) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnClipChange( 
            /* [in] */ const RECT __RPC_FAR *pSourceRect,
            /* [in] */ const RECT __RPC_FAR *pDestinationRect,
            /* [in] */ const RGNDATA __RPC_FAR *pRgnData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnColorKeyChange( 
            /* [in] */ const COLORKEY __RPC_FAR *pColorKey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnPositionChange( 
            /* [in] */ const RECT __RPC_FAR *pSourceRect,
            /* [in] */ const RECT __RPC_FAR *pDestinationRect) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IOverlayNotifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IOverlayNotify __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IOverlayNotify __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IOverlayNotify __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnPaletteChange )( 
            IOverlayNotify __RPC_FAR * This,
            /* [in] */ DWORD dwColors,
            /* [in] */ const PALETTEENTRY __RPC_FAR *pPalette);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnClipChange )( 
            IOverlayNotify __RPC_FAR * This,
            /* [in] */ const RECT __RPC_FAR *pSourceRect,
            /* [in] */ const RECT __RPC_FAR *pDestinationRect,
            /* [in] */ const RGNDATA __RPC_FAR *pRgnData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnColorKeyChange )( 
            IOverlayNotify __RPC_FAR * This,
            /* [in] */ const COLORKEY __RPC_FAR *pColorKey);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnPositionChange )( 
            IOverlayNotify __RPC_FAR * This,
            /* [in] */ const RECT __RPC_FAR *pSourceRect,
            /* [in] */ const RECT __RPC_FAR *pDestinationRect);
        
        END_INTERFACE
    } IOverlayNotifyVtbl;

    interface IOverlayNotify
    {
        CONST_VTBL struct IOverlayNotifyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOverlayNotify_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IOverlayNotify_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IOverlayNotify_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IOverlayNotify_OnPaletteChange(This,dwColors,pPalette)	\
    (This)->lpVtbl -> OnPaletteChange(This,dwColors,pPalette)

#define IOverlayNotify_OnClipChange(This,pSourceRect,pDestinationRect,pRgnData)	\
    (This)->lpVtbl -> OnClipChange(This,pSourceRect,pDestinationRect,pRgnData)

#define IOverlayNotify_OnColorKeyChange(This,pColorKey)	\
    (This)->lpVtbl -> OnColorKeyChange(This,pColorKey)

#define IOverlayNotify_OnPositionChange(This,pSourceRect,pDestinationRect)	\
    (This)->lpVtbl -> OnPositionChange(This,pSourceRect,pDestinationRect)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IOverlayNotify_OnPaletteChange_Proxy( 
    IOverlayNotify __RPC_FAR * This,
    /* [in] */ DWORD dwColors,
    /* [in] */ const PALETTEENTRY __RPC_FAR *pPalette);


void __RPC_STUB IOverlayNotify_OnPaletteChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayNotify_OnClipChange_Proxy( 
    IOverlayNotify __RPC_FAR * This,
    /* [in] */ const RECT __RPC_FAR *pSourceRect,
    /* [in] */ const RECT __RPC_FAR *pDestinationRect,
    /* [in] */ const RGNDATA __RPC_FAR *pRgnData);


void __RPC_STUB IOverlayNotify_OnClipChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayNotify_OnColorKeyChange_Proxy( 
    IOverlayNotify __RPC_FAR * This,
    /* [in] */ const COLORKEY __RPC_FAR *pColorKey);


void __RPC_STUB IOverlayNotify_OnColorKeyChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlayNotify_OnPositionChange_Proxy( 
    IOverlayNotify __RPC_FAR * This,
    /* [in] */ const RECT __RPC_FAR *pSourceRect,
    /* [in] */ const RECT __RPC_FAR *pDestinationRect);


void __RPC_STUB IOverlayNotify_OnPositionChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IOverlayNotify_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0074
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef IOverlayNotify __RPC_FAR *POVERLAYNOTIFY;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0074_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0074_v0_0_s_ifspec;

#ifndef __IOverlay_INTERFACE_DEFINED__
#define __IOverlay_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IOverlay
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][local][object] */ 



EXTERN_C const IID IID_IOverlay;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a868a1-0ad4-11ce-b03a-0020af0ba770")
    IOverlay : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetPalette( 
            /* [out] */ DWORD __RPC_FAR *pdwColors,
            /* [out] */ PALETTEENTRY __RPC_FAR *__RPC_FAR *ppPalette) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPalette( 
            /* [in] */ DWORD dwColors,
            /* [in] */ PALETTEENTRY __RPC_FAR *pPalette) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDefaultColorKey( 
            /* [out] */ COLORKEY __RPC_FAR *pColorKey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetColorKey( 
            /* [out] */ COLORKEY __RPC_FAR *pColorKey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetColorKey( 
            /* [out][in] */ COLORKEY __RPC_FAR *pColorKey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWindowHandle( 
            /* [out] */ HWND __RPC_FAR *pHwnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetClipList( 
            /* [out] */ RECT __RPC_FAR *pSourceRect,
            /* [out] */ RECT __RPC_FAR *pDestinationRect,
            /* [out] */ RGNDATA __RPC_FAR *__RPC_FAR *ppRgnData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVideoPosition( 
            /* [out] */ RECT __RPC_FAR *pSourceRect,
            /* [out] */ RECT __RPC_FAR *pDestinationRect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Advise( 
            /* [in] */ IOverlayNotify __RPC_FAR *pOverlayNotify,
            /* [in] */ DWORD dwInterests) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Unadvise( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IOverlayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IOverlay __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IOverlay __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IOverlay __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPalette )( 
            IOverlay __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwColors,
            /* [out] */ PALETTEENTRY __RPC_FAR *__RPC_FAR *ppPalette);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPalette )( 
            IOverlay __RPC_FAR * This,
            /* [in] */ DWORD dwColors,
            /* [in] */ PALETTEENTRY __RPC_FAR *pPalette);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDefaultColorKey )( 
            IOverlay __RPC_FAR * This,
            /* [out] */ COLORKEY __RPC_FAR *pColorKey);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetColorKey )( 
            IOverlay __RPC_FAR * This,
            /* [out] */ COLORKEY __RPC_FAR *pColorKey);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetColorKey )( 
            IOverlay __RPC_FAR * This,
            /* [out][in] */ COLORKEY __RPC_FAR *pColorKey);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWindowHandle )( 
            IOverlay __RPC_FAR * This,
            /* [out] */ HWND __RPC_FAR *pHwnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetClipList )( 
            IOverlay __RPC_FAR * This,
            /* [out] */ RECT __RPC_FAR *pSourceRect,
            /* [out] */ RECT __RPC_FAR *pDestinationRect,
            /* [out] */ RGNDATA __RPC_FAR *__RPC_FAR *ppRgnData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVideoPosition )( 
            IOverlay __RPC_FAR * This,
            /* [out] */ RECT __RPC_FAR *pSourceRect,
            /* [out] */ RECT __RPC_FAR *pDestinationRect);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Advise )( 
            IOverlay __RPC_FAR * This,
            /* [in] */ IOverlayNotify __RPC_FAR *pOverlayNotify,
            /* [in] */ DWORD dwInterests);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Unadvise )( 
            IOverlay __RPC_FAR * This);
        
        END_INTERFACE
    } IOverlayVtbl;

    interface IOverlay
    {
        CONST_VTBL struct IOverlayVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IOverlay_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IOverlay_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IOverlay_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IOverlay_GetPalette(This,pdwColors,ppPalette)	\
    (This)->lpVtbl -> GetPalette(This,pdwColors,ppPalette)

#define IOverlay_SetPalette(This,dwColors,pPalette)	\
    (This)->lpVtbl -> SetPalette(This,dwColors,pPalette)

#define IOverlay_GetDefaultColorKey(This,pColorKey)	\
    (This)->lpVtbl -> GetDefaultColorKey(This,pColorKey)

#define IOverlay_GetColorKey(This,pColorKey)	\
    (This)->lpVtbl -> GetColorKey(This,pColorKey)

#define IOverlay_SetColorKey(This,pColorKey)	\
    (This)->lpVtbl -> SetColorKey(This,pColorKey)

#define IOverlay_GetWindowHandle(This,pHwnd)	\
    (This)->lpVtbl -> GetWindowHandle(This,pHwnd)

#define IOverlay_GetClipList(This,pSourceRect,pDestinationRect,ppRgnData)	\
    (This)->lpVtbl -> GetClipList(This,pSourceRect,pDestinationRect,ppRgnData)

#define IOverlay_GetVideoPosition(This,pSourceRect,pDestinationRect)	\
    (This)->lpVtbl -> GetVideoPosition(This,pSourceRect,pDestinationRect)

#define IOverlay_Advise(This,pOverlayNotify,dwInterests)	\
    (This)->lpVtbl -> Advise(This,pOverlayNotify,dwInterests)

#define IOverlay_Unadvise(This)	\
    (This)->lpVtbl -> Unadvise(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IOverlay_GetPalette_Proxy( 
    IOverlay __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwColors,
    /* [out] */ PALETTEENTRY __RPC_FAR *__RPC_FAR *ppPalette);


void __RPC_STUB IOverlay_GetPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlay_SetPalette_Proxy( 
    IOverlay __RPC_FAR * This,
    /* [in] */ DWORD dwColors,
    /* [in] */ PALETTEENTRY __RPC_FAR *pPalette);


void __RPC_STUB IOverlay_SetPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlay_GetDefaultColorKey_Proxy( 
    IOverlay __RPC_FAR * This,
    /* [out] */ COLORKEY __RPC_FAR *pColorKey);


void __RPC_STUB IOverlay_GetDefaultColorKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlay_GetColorKey_Proxy( 
    IOverlay __RPC_FAR * This,
    /* [out] */ COLORKEY __RPC_FAR *pColorKey);


void __RPC_STUB IOverlay_GetColorKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlay_SetColorKey_Proxy( 
    IOverlay __RPC_FAR * This,
    /* [out][in] */ COLORKEY __RPC_FAR *pColorKey);


void __RPC_STUB IOverlay_SetColorKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlay_GetWindowHandle_Proxy( 
    IOverlay __RPC_FAR * This,
    /* [out] */ HWND __RPC_FAR *pHwnd);


void __RPC_STUB IOverlay_GetWindowHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlay_GetClipList_Proxy( 
    IOverlay __RPC_FAR * This,
    /* [out] */ RECT __RPC_FAR *pSourceRect,
    /* [out] */ RECT __RPC_FAR *pDestinationRect,
    /* [out] */ RGNDATA __RPC_FAR *__RPC_FAR *ppRgnData);


void __RPC_STUB IOverlay_GetClipList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlay_GetVideoPosition_Proxy( 
    IOverlay __RPC_FAR * This,
    /* [out] */ RECT __RPC_FAR *pSourceRect,
    /* [out] */ RECT __RPC_FAR *pDestinationRect);


void __RPC_STUB IOverlay_GetVideoPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlay_Advise_Proxy( 
    IOverlay __RPC_FAR * This,
    /* [in] */ IOverlayNotify __RPC_FAR *pOverlayNotify,
    /* [in] */ DWORD dwInterests);


void __RPC_STUB IOverlay_Advise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IOverlay_Unadvise_Proxy( 
    IOverlay __RPC_FAR * This);


void __RPC_STUB IOverlay_Unadvise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IOverlay_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0075
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef IOverlay __RPC_FAR *POVERLAY;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0075_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0075_v0_0_s_ifspec;

#ifndef __IMediaEventSink_INTERFACE_DEFINED__
#define __IMediaEventSink_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMediaEventSink
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IMediaEventSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a868a2-0ad4-11ce-b03a-0020af0ba770")
    IMediaEventSink : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Notify( 
            /* [in] */ long EventCode,
            /* [in] */ long EventParam1,
            /* [in] */ long EventParam2) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMediaEventSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMediaEventSink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMediaEventSink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMediaEventSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Notify )( 
            IMediaEventSink __RPC_FAR * This,
            /* [in] */ long EventCode,
            /* [in] */ long EventParam1,
            /* [in] */ long EventParam2);
        
        END_INTERFACE
    } IMediaEventSinkVtbl;

    interface IMediaEventSink
    {
        CONST_VTBL struct IMediaEventSinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaEventSink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaEventSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaEventSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaEventSink_Notify(This,EventCode,EventParam1,EventParam2)	\
    (This)->lpVtbl -> Notify(This,EventCode,EventParam1,EventParam2)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMediaEventSink_Notify_Proxy( 
    IMediaEventSink __RPC_FAR * This,
    /* [in] */ long EventCode,
    /* [in] */ long EventParam1,
    /* [in] */ long EventParam2);


void __RPC_STUB IMediaEventSink_Notify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMediaEventSink_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0076
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef IMediaEventSink __RPC_FAR *PMEDIAEVENTSINK;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0076_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0076_v0_0_s_ifspec;

#ifndef __IFileSourceFilter_INTERFACE_DEFINED__
#define __IFileSourceFilter_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IFileSourceFilter
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IFileSourceFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a868a6-0ad4-11ce-b03a-0020af0ba770")
    IFileSourceFilter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ LPCOLESTR pszFileName,
            /* [in] */ const AM_MEDIA_TYPE __RPC_FAR *pmt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurFile( 
            /* [out] */ LPOLESTR __RPC_FAR *ppszFileName,
            /* [out] */ AM_MEDIA_TYPE __RPC_FAR *pmt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFileSourceFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFileSourceFilter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFileSourceFilter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFileSourceFilter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Load )( 
            IFileSourceFilter __RPC_FAR * This,
            /* [in] */ LPCOLESTR pszFileName,
            /* [in] */ const AM_MEDIA_TYPE __RPC_FAR *pmt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCurFile )( 
            IFileSourceFilter __RPC_FAR * This,
            /* [out] */ LPOLESTR __RPC_FAR *ppszFileName,
            /* [out] */ AM_MEDIA_TYPE __RPC_FAR *pmt);
        
        END_INTERFACE
    } IFileSourceFilterVtbl;

    interface IFileSourceFilter
    {
        CONST_VTBL struct IFileSourceFilterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFileSourceFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFileSourceFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFileSourceFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFileSourceFilter_Load(This,pszFileName,pmt)	\
    (This)->lpVtbl -> Load(This,pszFileName,pmt)

#define IFileSourceFilter_GetCurFile(This,ppszFileName,pmt)	\
    (This)->lpVtbl -> GetCurFile(This,ppszFileName,pmt)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFileSourceFilter_Load_Proxy( 
    IFileSourceFilter __RPC_FAR * This,
    /* [in] */ LPCOLESTR pszFileName,
    /* [in] */ const AM_MEDIA_TYPE __RPC_FAR *pmt);


void __RPC_STUB IFileSourceFilter_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFileSourceFilter_GetCurFile_Proxy( 
    IFileSourceFilter __RPC_FAR * This,
    /* [out] */ LPOLESTR __RPC_FAR *ppszFileName,
    /* [out] */ AM_MEDIA_TYPE __RPC_FAR *pmt);


void __RPC_STUB IFileSourceFilter_GetCurFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFileSourceFilter_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0077
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef IFileSourceFilter __RPC_FAR *PFILTERFILESOURCE;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0077_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0077_v0_0_s_ifspec;

#ifndef __IGraphBuilder_INTERFACE_DEFINED__
#define __IGraphBuilder_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IGraphBuilder
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][local][object] */ 



EXTERN_C const IID IID_IGraphBuilder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a868a9-0ad4-11ce-b03a-0020af0ba770")
    IGraphBuilder : public IFilterGraph
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Connect( 
            /* [in] */ IPin __RPC_FAR *ppinOut,
            /* [in] */ IPin __RPC_FAR *ppinIn) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Render( 
            /* [in] */ IPin __RPC_FAR *ppinOut) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RenderFile( 
            /* [in] */ LPCWSTR lpcwstrFile,
            /* [in] */ LPCWSTR lpcwstrPlayList) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddSourceFilter( 
            /* [in] */ LPCWSTR lpcwstrFileName,
            /* [in] */ LPCWSTR lpcwstrFilterName,
            /* [out] */ IBaseFilter __RPC_FAR *__RPC_FAR *ppFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetLogFile( 
            /* [in] */ HANDLE hFile) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Abort( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ShouldOperationContinue( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGraphBuilderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IGraphBuilder __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IGraphBuilder __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IGraphBuilder __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddFilter )( 
            IGraphBuilder __RPC_FAR * This,
            /* [in] */ IBaseFilter __RPC_FAR *pFilter,
            /* [string][in] */ LPCWSTR pName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveFilter )( 
            IGraphBuilder __RPC_FAR * This,
            /* [in] */ IBaseFilter __RPC_FAR *pFilter);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumFilters )( 
            IGraphBuilder __RPC_FAR * This,
            /* [out] */ IEnumFilters __RPC_FAR *__RPC_FAR *ppEnum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindFilterByName )( 
            IGraphBuilder __RPC_FAR * This,
            /* [string][in] */ LPCWSTR pName,
            /* [out] */ IBaseFilter __RPC_FAR *__RPC_FAR *ppFilter);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectDirect )( 
            IGraphBuilder __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *ppinOut,
            /* [in] */ IPin __RPC_FAR *ppinIn,
            /* [in] */ const AM_MEDIA_TYPE __RPC_FAR *pmt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reconnect )( 
            IGraphBuilder __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *ppin);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            IGraphBuilder __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *ppin);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDefaultSyncSource )( 
            IGraphBuilder __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            IGraphBuilder __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *ppinOut,
            /* [in] */ IPin __RPC_FAR *ppinIn);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Render )( 
            IGraphBuilder __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *ppinOut);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RenderFile )( 
            IGraphBuilder __RPC_FAR * This,
            /* [in] */ LPCWSTR lpcwstrFile,
            /* [in] */ LPCWSTR lpcwstrPlayList);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddSourceFilter )( 
            IGraphBuilder __RPC_FAR * This,
            /* [in] */ LPCWSTR lpcwstrFileName,
            /* [in] */ LPCWSTR lpcwstrFilterName,
            /* [out] */ IBaseFilter __RPC_FAR *__RPC_FAR *ppFilter);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLogFile )( 
            IGraphBuilder __RPC_FAR * This,
            /* [in] */ HANDLE hFile);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Abort )( 
            IGraphBuilder __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShouldOperationContinue )( 
            IGraphBuilder __RPC_FAR * This);
        
        END_INTERFACE
    } IGraphBuilderVtbl;

    interface IGraphBuilder
    {
        CONST_VTBL struct IGraphBuilderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGraphBuilder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGraphBuilder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGraphBuilder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGraphBuilder_AddFilter(This,pFilter,pName)	\
    (This)->lpVtbl -> AddFilter(This,pFilter,pName)

#define IGraphBuilder_RemoveFilter(This,pFilter)	\
    (This)->lpVtbl -> RemoveFilter(This,pFilter)

#define IGraphBuilder_EnumFilters(This,ppEnum)	\
    (This)->lpVtbl -> EnumFilters(This,ppEnum)

#define IGraphBuilder_FindFilterByName(This,pName,ppFilter)	\
    (This)->lpVtbl -> FindFilterByName(This,pName,ppFilter)

#define IGraphBuilder_ConnectDirect(This,ppinOut,ppinIn,pmt)	\
    (This)->lpVtbl -> ConnectDirect(This,ppinOut,ppinIn,pmt)

#define IGraphBuilder_Reconnect(This,ppin)	\
    (This)->lpVtbl -> Reconnect(This,ppin)

#define IGraphBuilder_Disconnect(This,ppin)	\
    (This)->lpVtbl -> Disconnect(This,ppin)

#define IGraphBuilder_SetDefaultSyncSource(This)	\
    (This)->lpVtbl -> SetDefaultSyncSource(This)


#define IGraphBuilder_Connect(This,ppinOut,ppinIn)	\
    (This)->lpVtbl -> Connect(This,ppinOut,ppinIn)

#define IGraphBuilder_Render(This,ppinOut)	\
    (This)->lpVtbl -> Render(This,ppinOut)

#define IGraphBuilder_RenderFile(This,lpcwstrFile,lpcwstrPlayList)	\
    (This)->lpVtbl -> RenderFile(This,lpcwstrFile,lpcwstrPlayList)

#define IGraphBuilder_AddSourceFilter(This,lpcwstrFileName,lpcwstrFilterName,ppFilter)	\
    (This)->lpVtbl -> AddSourceFilter(This,lpcwstrFileName,lpcwstrFilterName,ppFilter)

#define IGraphBuilder_SetLogFile(This,hFile)	\
    (This)->lpVtbl -> SetLogFile(This,hFile)

#define IGraphBuilder_Abort(This)	\
    (This)->lpVtbl -> Abort(This)

#define IGraphBuilder_ShouldOperationContinue(This)	\
    (This)->lpVtbl -> ShouldOperationContinue(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IGraphBuilder_Connect_Proxy( 
    IGraphBuilder __RPC_FAR * This,
    /* [in] */ IPin __RPC_FAR *ppinOut,
    /* [in] */ IPin __RPC_FAR *ppinIn);


void __RPC_STUB IGraphBuilder_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGraphBuilder_Render_Proxy( 
    IGraphBuilder __RPC_FAR * This,
    /* [in] */ IPin __RPC_FAR *ppinOut);


void __RPC_STUB IGraphBuilder_Render_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGraphBuilder_RenderFile_Proxy( 
    IGraphBuilder __RPC_FAR * This,
    /* [in] */ LPCWSTR lpcwstrFile,
    /* [in] */ LPCWSTR lpcwstrPlayList);


void __RPC_STUB IGraphBuilder_RenderFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGraphBuilder_AddSourceFilter_Proxy( 
    IGraphBuilder __RPC_FAR * This,
    /* [in] */ LPCWSTR lpcwstrFileName,
    /* [in] */ LPCWSTR lpcwstrFilterName,
    /* [out] */ IBaseFilter __RPC_FAR *__RPC_FAR *ppFilter);


void __RPC_STUB IGraphBuilder_AddSourceFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGraphBuilder_SetLogFile_Proxy( 
    IGraphBuilder __RPC_FAR * This,
    /* [in] */ HANDLE hFile);


void __RPC_STUB IGraphBuilder_SetLogFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGraphBuilder_Abort_Proxy( 
    IGraphBuilder __RPC_FAR * This);


void __RPC_STUB IGraphBuilder_Abort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IGraphBuilder_ShouldOperationContinue_Proxy( 
    IGraphBuilder __RPC_FAR * This);


void __RPC_STUB IGraphBuilder_ShouldOperationContinue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGraphBuilder_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0078
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 



enum _AM_RENSDEREXFLAGS
    {	AM_RENDEREX_RENDERTOEXISTINGRENDERERS	= 0x1
    };


extern RPC_IF_HANDLE __MIDL_itf_strmif_0078_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0078_v0_0_s_ifspec;

#ifndef __IFilterGraph2_INTERFACE_DEFINED__
#define __IFilterGraph2_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IFilterGraph2
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][local][object] */ 



EXTERN_C const IID IID_IFilterGraph2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("36b73882-c2c8-11cf-8b46-00805f6cef60")
    IFilterGraph2 : public IGraphBuilder
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AddSourceFilterForMoniker( 
            /* [in] */ IMoniker __RPC_FAR *pMoniker,
            /* [in] */ IBindCtx __RPC_FAR *pCtx,
            /* [in] */ LPCWSTR lpcwstrFilterName,
            /* [out] */ IBaseFilter __RPC_FAR *__RPC_FAR *ppFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReconnectEx( 
            /* [in] */ IPin __RPC_FAR *ppin,
            /* [in] */ const AM_MEDIA_TYPE __RPC_FAR *pmt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RenderEx( 
            /* [in] */ IPin __RPC_FAR *pPinOut,
            /* [in] */ DWORD dwFlags,
            /* [out][in] */ LPVOID pvContext) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFilterGraph2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFilterGraph2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFilterGraph2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFilterGraph2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddFilter )( 
            IFilterGraph2 __RPC_FAR * This,
            /* [in] */ IBaseFilter __RPC_FAR *pFilter,
            /* [string][in] */ LPCWSTR pName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveFilter )( 
            IFilterGraph2 __RPC_FAR * This,
            /* [in] */ IBaseFilter __RPC_FAR *pFilter);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumFilters )( 
            IFilterGraph2 __RPC_FAR * This,
            /* [out] */ IEnumFilters __RPC_FAR *__RPC_FAR *ppEnum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindFilterByName )( 
            IFilterGraph2 __RPC_FAR * This,
            /* [string][in] */ LPCWSTR pName,
            /* [out] */ IBaseFilter __RPC_FAR *__RPC_FAR *ppFilter);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectDirect )( 
            IFilterGraph2 __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *ppinOut,
            /* [in] */ IPin __RPC_FAR *ppinIn,
            /* [in] */ const AM_MEDIA_TYPE __RPC_FAR *pmt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reconnect )( 
            IFilterGraph2 __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *ppin);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            IFilterGraph2 __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *ppin);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDefaultSyncSource )( 
            IFilterGraph2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            IFilterGraph2 __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *ppinOut,
            /* [in] */ IPin __RPC_FAR *ppinIn);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Render )( 
            IFilterGraph2 __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *ppinOut);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RenderFile )( 
            IFilterGraph2 __RPC_FAR * This,
            /* [in] */ LPCWSTR lpcwstrFile,
            /* [in] */ LPCWSTR lpcwstrPlayList);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddSourceFilter )( 
            IFilterGraph2 __RPC_FAR * This,
            /* [in] */ LPCWSTR lpcwstrFileName,
            /* [in] */ LPCWSTR lpcwstrFilterName,
            /* [out] */ IBaseFilter __RPC_FAR *__RPC_FAR *ppFilter);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLogFile )( 
            IFilterGraph2 __RPC_FAR * This,
            /* [in] */ HANDLE hFile);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Abort )( 
            IFilterGraph2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShouldOperationContinue )( 
            IFilterGraph2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddSourceFilterForMoniker )( 
            IFilterGraph2 __RPC_FAR * This,
            /* [in] */ IMoniker __RPC_FAR *pMoniker,
            /* [in] */ IBindCtx __RPC_FAR *pCtx,
            /* [in] */ LPCWSTR lpcwstrFilterName,
            /* [out] */ IBaseFilter __RPC_FAR *__RPC_FAR *ppFilter);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReconnectEx )( 
            IFilterGraph2 __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *ppin,
            /* [in] */ const AM_MEDIA_TYPE __RPC_FAR *pmt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RenderEx )( 
            IFilterGraph2 __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *pPinOut,
            /* [in] */ DWORD dwFlags,
            /* [out][in] */ LPVOID pvContext);
        
        END_INTERFACE
    } IFilterGraph2Vtbl;

    interface IFilterGraph2
    {
        CONST_VTBL struct IFilterGraph2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFilterGraph2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFilterGraph2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFilterGraph2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFilterGraph2_AddFilter(This,pFilter,pName)	\
    (This)->lpVtbl -> AddFilter(This,pFilter,pName)

#define IFilterGraph2_RemoveFilter(This,pFilter)	\
    (This)->lpVtbl -> RemoveFilter(This,pFilter)

#define IFilterGraph2_EnumFilters(This,ppEnum)	\
    (This)->lpVtbl -> EnumFilters(This,ppEnum)

#define IFilterGraph2_FindFilterByName(This,pName,ppFilter)	\
    (This)->lpVtbl -> FindFilterByName(This,pName,ppFilter)

#define IFilterGraph2_ConnectDirect(This,ppinOut,ppinIn,pmt)	\
    (This)->lpVtbl -> ConnectDirect(This,ppinOut,ppinIn,pmt)

#define IFilterGraph2_Reconnect(This,ppin)	\
    (This)->lpVtbl -> Reconnect(This,ppin)

#define IFilterGraph2_Disconnect(This,ppin)	\
    (This)->lpVtbl -> Disconnect(This,ppin)

#define IFilterGraph2_SetDefaultSyncSource(This)	\
    (This)->lpVtbl -> SetDefaultSyncSource(This)


#define IFilterGraph2_Connect(This,ppinOut,ppinIn)	\
    (This)->lpVtbl -> Connect(This,ppinOut,ppinIn)

#define IFilterGraph2_Render(This,ppinOut)	\
    (This)->lpVtbl -> Render(This,ppinOut)

#define IFilterGraph2_RenderFile(This,lpcwstrFile,lpcwstrPlayList)	\
    (This)->lpVtbl -> RenderFile(This,lpcwstrFile,lpcwstrPlayList)

#define IFilterGraph2_AddSourceFilter(This,lpcwstrFileName,lpcwstrFilterName,ppFilter)	\
    (This)->lpVtbl -> AddSourceFilter(This,lpcwstrFileName,lpcwstrFilterName,ppFilter)

#define IFilterGraph2_SetLogFile(This,hFile)	\
    (This)->lpVtbl -> SetLogFile(This,hFile)

#define IFilterGraph2_Abort(This)	\
    (This)->lpVtbl -> Abort(This)

#define IFilterGraph2_ShouldOperationContinue(This)	\
    (This)->lpVtbl -> ShouldOperationContinue(This)


#define IFilterGraph2_AddSourceFilterForMoniker(This,pMoniker,pCtx,lpcwstrFilterName,ppFilter)	\
    (This)->lpVtbl -> AddSourceFilterForMoniker(This,pMoniker,pCtx,lpcwstrFilterName,ppFilter)

#define IFilterGraph2_ReconnectEx(This,ppin,pmt)	\
    (This)->lpVtbl -> ReconnectEx(This,ppin,pmt)

#define IFilterGraph2_RenderEx(This,pPinOut,dwFlags,pvContext)	\
    (This)->lpVtbl -> RenderEx(This,pPinOut,dwFlags,pvContext)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFilterGraph2_AddSourceFilterForMoniker_Proxy( 
    IFilterGraph2 __RPC_FAR * This,
    /* [in] */ IMoniker __RPC_FAR *pMoniker,
    /* [in] */ IBindCtx __RPC_FAR *pCtx,
    /* [in] */ LPCWSTR lpcwstrFilterName,
    /* [out] */ IBaseFilter __RPC_FAR *__RPC_FAR *ppFilter);


void __RPC_STUB IFilterGraph2_AddSourceFilterForMoniker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterGraph2_ReconnectEx_Proxy( 
    IFilterGraph2 __RPC_FAR * This,
    /* [in] */ IPin __RPC_FAR *ppin,
    /* [in] */ const AM_MEDIA_TYPE __RPC_FAR *pmt);


void __RPC_STUB IFilterGraph2_ReconnectEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFilterGraph2_RenderEx_Proxy( 
    IFilterGraph2 __RPC_FAR * This,
    /* [in] */ IPin __RPC_FAR *pPinOut,
    /* [in] */ DWORD dwFlags,
    /* [out][in] */ LPVOID pvContext);


void __RPC_STUB IFilterGraph2_RenderEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFilterGraph2_INTERFACE_DEFINED__ */


#ifndef __IStreamBuilder_INTERFACE_DEFINED__
#define __IStreamBuilder_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IStreamBuilder
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][local][object] */ 



EXTERN_C const IID IID_IStreamBuilder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a868bf-0ad4-11ce-b03a-0020af0ba770")
    IStreamBuilder : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Render( 
            /* [in] */ IPin __RPC_FAR *ppinOut,
            /* [in] */ IGraphBuilder __RPC_FAR *pGraph) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Backout( 
            /* [in] */ IPin __RPC_FAR *ppinOut,
            /* [in] */ IGraphBuilder __RPC_FAR *pGraph) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStreamBuilderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IStreamBuilder __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IStreamBuilder __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IStreamBuilder __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Render )( 
            IStreamBuilder __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *ppinOut,
            /* [in] */ IGraphBuilder __RPC_FAR *pGraph);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Backout )( 
            IStreamBuilder __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *ppinOut,
            /* [in] */ IGraphBuilder __RPC_FAR *pGraph);
        
        END_INTERFACE
    } IStreamBuilderVtbl;

    interface IStreamBuilder
    {
        CONST_VTBL struct IStreamBuilderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStreamBuilder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStreamBuilder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStreamBuilder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStreamBuilder_Render(This,ppinOut,pGraph)	\
    (This)->lpVtbl -> Render(This,ppinOut,pGraph)

#define IStreamBuilder_Backout(This,ppinOut,pGraph)	\
    (This)->lpVtbl -> Backout(This,ppinOut,pGraph)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IStreamBuilder_Render_Proxy( 
    IStreamBuilder __RPC_FAR * This,
    /* [in] */ IPin __RPC_FAR *ppinOut,
    /* [in] */ IGraphBuilder __RPC_FAR *pGraph);


void __RPC_STUB IStreamBuilder_Render_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStreamBuilder_Backout_Proxy( 
    IStreamBuilder __RPC_FAR * This,
    /* [in] */ IPin __RPC_FAR *ppinOut,
    /* [in] */ IGraphBuilder __RPC_FAR *pGraph);


void __RPC_STUB IStreamBuilder_Backout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IStreamBuilder_INTERFACE_DEFINED__ */


#ifndef __IAsyncReader_INTERFACE_DEFINED__
#define __IAsyncReader_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAsyncReader
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IAsyncReader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a868aa-0ad4-11ce-b03a-0020af0ba770")
    IAsyncReader : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RequestAllocator( 
            /* [in] */ IMemAllocator __RPC_FAR *pPreferred,
            /* [in] */ ALLOCATOR_PROPERTIES __RPC_FAR *pProps,
            /* [out] */ IMemAllocator __RPC_FAR *__RPC_FAR *ppActual) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Request( 
            /* [in] */ IMediaSample __RPC_FAR *pSample,
            /* [in] */ DWORD dwUser) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WaitForNext( 
            /* [in] */ DWORD dwTimeout,
            /* [out] */ IMediaSample __RPC_FAR *__RPC_FAR *ppSample,
            /* [out] */ DWORD __RPC_FAR *pdwUser) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SyncReadAligned( 
            /* [in] */ IMediaSample __RPC_FAR *pSample) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SyncRead( 
            /* [in] */ LONGLONG llPosition,
            /* [in] */ LONG lLength,
            /* [size_is][out] */ BYTE __RPC_FAR *pBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Length( 
            /* [out] */ LONGLONG __RPC_FAR *pTotal,
            /* [out] */ LONGLONG __RPC_FAR *pAvailable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BeginFlush( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EndFlush( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAsyncReaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAsyncReader __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAsyncReader __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAsyncReader __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestAllocator )( 
            IAsyncReader __RPC_FAR * This,
            /* [in] */ IMemAllocator __RPC_FAR *pPreferred,
            /* [in] */ ALLOCATOR_PROPERTIES __RPC_FAR *pProps,
            /* [out] */ IMemAllocator __RPC_FAR *__RPC_FAR *ppActual);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Request )( 
            IAsyncReader __RPC_FAR * This,
            /* [in] */ IMediaSample __RPC_FAR *pSample,
            /* [in] */ DWORD dwUser);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitForNext )( 
            IAsyncReader __RPC_FAR * This,
            /* [in] */ DWORD dwTimeout,
            /* [out] */ IMediaSample __RPC_FAR *__RPC_FAR *ppSample,
            /* [out] */ DWORD __RPC_FAR *pdwUser);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SyncReadAligned )( 
            IAsyncReader __RPC_FAR * This,
            /* [in] */ IMediaSample __RPC_FAR *pSample);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SyncRead )( 
            IAsyncReader __RPC_FAR * This,
            /* [in] */ LONGLONG llPosition,
            /* [in] */ LONG lLength,
            /* [size_is][out] */ BYTE __RPC_FAR *pBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Length )( 
            IAsyncReader __RPC_FAR * This,
            /* [out] */ LONGLONG __RPC_FAR *pTotal,
            /* [out] */ LONGLONG __RPC_FAR *pAvailable);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BeginFlush )( 
            IAsyncReader __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EndFlush )( 
            IAsyncReader __RPC_FAR * This);
        
        END_INTERFACE
    } IAsyncReaderVtbl;

    interface IAsyncReader
    {
        CONST_VTBL struct IAsyncReaderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAsyncReader_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAsyncReader_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAsyncReader_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAsyncReader_RequestAllocator(This,pPreferred,pProps,ppActual)	\
    (This)->lpVtbl -> RequestAllocator(This,pPreferred,pProps,ppActual)

#define IAsyncReader_Request(This,pSample,dwUser)	\
    (This)->lpVtbl -> Request(This,pSample,dwUser)

#define IAsyncReader_WaitForNext(This,dwTimeout,ppSample,pdwUser)	\
    (This)->lpVtbl -> WaitForNext(This,dwTimeout,ppSample,pdwUser)

#define IAsyncReader_SyncReadAligned(This,pSample)	\
    (This)->lpVtbl -> SyncReadAligned(This,pSample)

#define IAsyncReader_SyncRead(This,llPosition,lLength,pBuffer)	\
    (This)->lpVtbl -> SyncRead(This,llPosition,lLength,pBuffer)

#define IAsyncReader_Length(This,pTotal,pAvailable)	\
    (This)->lpVtbl -> Length(This,pTotal,pAvailable)

#define IAsyncReader_BeginFlush(This)	\
    (This)->lpVtbl -> BeginFlush(This)

#define IAsyncReader_EndFlush(This)	\
    (This)->lpVtbl -> EndFlush(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAsyncReader_RequestAllocator_Proxy( 
    IAsyncReader __RPC_FAR * This,
    /* [in] */ IMemAllocator __RPC_FAR *pPreferred,
    /* [in] */ ALLOCATOR_PROPERTIES __RPC_FAR *pProps,
    /* [out] */ IMemAllocator __RPC_FAR *__RPC_FAR *ppActual);


void __RPC_STUB IAsyncReader_RequestAllocator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAsyncReader_Request_Proxy( 
    IAsyncReader __RPC_FAR * This,
    /* [in] */ IMediaSample __RPC_FAR *pSample,
    /* [in] */ DWORD dwUser);


void __RPC_STUB IAsyncReader_Request_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAsyncReader_WaitForNext_Proxy( 
    IAsyncReader __RPC_FAR * This,
    /* [in] */ DWORD dwTimeout,
    /* [out] */ IMediaSample __RPC_FAR *__RPC_FAR *ppSample,
    /* [out] */ DWORD __RPC_FAR *pdwUser);


void __RPC_STUB IAsyncReader_WaitForNext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAsyncReader_SyncReadAligned_Proxy( 
    IAsyncReader __RPC_FAR * This,
    /* [in] */ IMediaSample __RPC_FAR *pSample);


void __RPC_STUB IAsyncReader_SyncReadAligned_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAsyncReader_SyncRead_Proxy( 
    IAsyncReader __RPC_FAR * This,
    /* [in] */ LONGLONG llPosition,
    /* [in] */ LONG lLength,
    /* [size_is][out] */ BYTE __RPC_FAR *pBuffer);


void __RPC_STUB IAsyncReader_SyncRead_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAsyncReader_Length_Proxy( 
    IAsyncReader __RPC_FAR * This,
    /* [out] */ LONGLONG __RPC_FAR *pTotal,
    /* [out] */ LONGLONG __RPC_FAR *pAvailable);


void __RPC_STUB IAsyncReader_Length_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAsyncReader_BeginFlush_Proxy( 
    IAsyncReader __RPC_FAR * This);


void __RPC_STUB IAsyncReader_BeginFlush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAsyncReader_EndFlush_Proxy( 
    IAsyncReader __RPC_FAR * This);


void __RPC_STUB IAsyncReader_EndFlush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAsyncReader_INTERFACE_DEFINED__ */


#ifndef __IGraphVersion_INTERFACE_DEFINED__
#define __IGraphVersion_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IGraphVersion
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IGraphVersion;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a868ab-0ad4-11ce-b03a-0020af0ba770")
    IGraphVersion : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE QueryVersion( 
            LONG __RPC_FAR *pVersion) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGraphVersionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IGraphVersion __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IGraphVersion __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IGraphVersion __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryVersion )( 
            IGraphVersion __RPC_FAR * This,
            LONG __RPC_FAR *pVersion);
        
        END_INTERFACE
    } IGraphVersionVtbl;

    interface IGraphVersion
    {
        CONST_VTBL struct IGraphVersionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGraphVersion_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGraphVersion_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGraphVersion_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGraphVersion_QueryVersion(This,pVersion)	\
    (This)->lpVtbl -> QueryVersion(This,pVersion)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IGraphVersion_QueryVersion_Proxy( 
    IGraphVersion __RPC_FAR * This,
    LONG __RPC_FAR *pVersion);


void __RPC_STUB IGraphVersion_QueryVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGraphVersion_INTERFACE_DEFINED__ */


#ifndef __IDistributorNotify_INTERFACE_DEFINED__
#define __IDistributorNotify_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDistributorNotify
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IDistributorNotify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a868af-0ad4-11ce-b03a-0020af0ba770")
    IDistributorNotify : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Pause( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Run( 
            REFERENCE_TIME tStart) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSyncSource( 
            /* [in] */ IReferenceClock __RPC_FAR *pClock) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NotifyGraphChange( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDistributorNotifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDistributorNotify __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDistributorNotify __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDistributorNotify __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IDistributorNotify __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pause )( 
            IDistributorNotify __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Run )( 
            IDistributorNotify __RPC_FAR * This,
            REFERENCE_TIME tStart);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSyncSource )( 
            IDistributorNotify __RPC_FAR * This,
            /* [in] */ IReferenceClock __RPC_FAR *pClock);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NotifyGraphChange )( 
            IDistributorNotify __RPC_FAR * This);
        
        END_INTERFACE
    } IDistributorNotifyVtbl;

    interface IDistributorNotify
    {
        CONST_VTBL struct IDistributorNotifyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDistributorNotify_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDistributorNotify_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDistributorNotify_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDistributorNotify_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IDistributorNotify_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IDistributorNotify_Run(This,tStart)	\
    (This)->lpVtbl -> Run(This,tStart)

#define IDistributorNotify_SetSyncSource(This,pClock)	\
    (This)->lpVtbl -> SetSyncSource(This,pClock)

#define IDistributorNotify_NotifyGraphChange(This)	\
    (This)->lpVtbl -> NotifyGraphChange(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDistributorNotify_Stop_Proxy( 
    IDistributorNotify __RPC_FAR * This);


void __RPC_STUB IDistributorNotify_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDistributorNotify_Pause_Proxy( 
    IDistributorNotify __RPC_FAR * This);


void __RPC_STUB IDistributorNotify_Pause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDistributorNotify_Run_Proxy( 
    IDistributorNotify __RPC_FAR * This,
    REFERENCE_TIME tStart);


void __RPC_STUB IDistributorNotify_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDistributorNotify_SetSyncSource_Proxy( 
    IDistributorNotify __RPC_FAR * This,
    /* [in] */ IReferenceClock __RPC_FAR *pClock);


void __RPC_STUB IDistributorNotify_SetSyncSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDistributorNotify_NotifyGraphChange_Proxy( 
    IDistributorNotify __RPC_FAR * This);


void __RPC_STUB IDistributorNotify_NotifyGraphChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDistributorNotify_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0083
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef /* [public] */ 
enum __MIDL___MIDL_itf_strmif_0083_0001
    {	AM_STREAM_INFO_START_DEFINED	= 0x1,
	AM_STREAM_INFO_STOP_DEFINED	= 0x2,
	AM_STREAM_INFO_DISCARDING	= 0x4,
	AM_STREAM_INFO_STOP_SEND_EXTRA	= 0x10
    }	AM_STREAM_INFO_FLAGS;

typedef /* [public][public] */ struct  __MIDL___MIDL_itf_strmif_0083_0002
    {
    REFERENCE_TIME tStart;
    REFERENCE_TIME tStop;
    DWORD dwStartCookie;
    DWORD dwStopCookie;
    DWORD dwFlags;
    }	AM_STREAM_INFO;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0083_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0083_v0_0_s_ifspec;

#ifndef __IAMStreamControl_INTERFACE_DEFINED__
#define __IAMStreamControl_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAMStreamControl
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IAMStreamControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("36b73881-c2c8-11cf-8b46-00805f6cef60")
    IAMStreamControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE StartAt( 
            /* [in] */ const REFERENCE_TIME __RPC_FAR *ptStart,
            /* [in] */ DWORD dwCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StopAt( 
            /* [in] */ const REFERENCE_TIME __RPC_FAR *ptStop,
            /* [in] */ BOOL bSendExtra,
            /* [in] */ DWORD dwCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInfo( 
            /* [out] */ AM_STREAM_INFO __RPC_FAR *pInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMStreamControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAMStreamControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAMStreamControl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAMStreamControl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartAt )( 
            IAMStreamControl __RPC_FAR * This,
            /* [in] */ const REFERENCE_TIME __RPC_FAR *ptStart,
            /* [in] */ DWORD dwCookie);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopAt )( 
            IAMStreamControl __RPC_FAR * This,
            /* [in] */ const REFERENCE_TIME __RPC_FAR *ptStop,
            /* [in] */ BOOL bSendExtra,
            /* [in] */ DWORD dwCookie);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IAMStreamControl __RPC_FAR * This,
            /* [out] */ AM_STREAM_INFO __RPC_FAR *pInfo);
        
        END_INTERFACE
    } IAMStreamControlVtbl;

    interface IAMStreamControl
    {
        CONST_VTBL struct IAMStreamControlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMStreamControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMStreamControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMStreamControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMStreamControl_StartAt(This,ptStart,dwCookie)	\
    (This)->lpVtbl -> StartAt(This,ptStart,dwCookie)

#define IAMStreamControl_StopAt(This,ptStop,bSendExtra,dwCookie)	\
    (This)->lpVtbl -> StopAt(This,ptStop,bSendExtra,dwCookie)

#define IAMStreamControl_GetInfo(This,pInfo)	\
    (This)->lpVtbl -> GetInfo(This,pInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMStreamControl_StartAt_Proxy( 
    IAMStreamControl __RPC_FAR * This,
    /* [in] */ const REFERENCE_TIME __RPC_FAR *ptStart,
    /* [in] */ DWORD dwCookie);


void __RPC_STUB IAMStreamControl_StartAt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMStreamControl_StopAt_Proxy( 
    IAMStreamControl __RPC_FAR * This,
    /* [in] */ const REFERENCE_TIME __RPC_FAR *ptStop,
    /* [in] */ BOOL bSendExtra,
    /* [in] */ DWORD dwCookie);


void __RPC_STUB IAMStreamControl_StopAt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMStreamControl_GetInfo_Proxy( 
    IAMStreamControl __RPC_FAR * This,
    /* [out] */ AM_STREAM_INFO __RPC_FAR *pInfo);


void __RPC_STUB IAMStreamControl_GetInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMStreamControl_INTERFACE_DEFINED__ */


#ifndef __ISeekingPassThru_INTERFACE_DEFINED__
#define __ISeekingPassThru_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ISeekingPassThru
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_ISeekingPassThru;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("36b73883-c2c8-11cf-8b46-00805f6cef60")
    ISeekingPassThru : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ BOOL bSupportRendering,
            /* [in] */ IPin __RPC_FAR *pPin) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISeekingPassThruVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISeekingPassThru __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISeekingPassThru __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISeekingPassThru __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            ISeekingPassThru __RPC_FAR * This,
            /* [in] */ BOOL bSupportRendering,
            /* [in] */ IPin __RPC_FAR *pPin);
        
        END_INTERFACE
    } ISeekingPassThruVtbl;

    interface ISeekingPassThru
    {
        CONST_VTBL struct ISeekingPassThruVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISeekingPassThru_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISeekingPassThru_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISeekingPassThru_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISeekingPassThru_Init(This,bSupportRendering,pPin)	\
    (This)->lpVtbl -> Init(This,bSupportRendering,pPin)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISeekingPassThru_Init_Proxy( 
    ISeekingPassThru __RPC_FAR * This,
    /* [in] */ BOOL bSupportRendering,
    /* [in] */ IPin __RPC_FAR *pPin);


void __RPC_STUB ISeekingPassThru_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISeekingPassThru_INTERFACE_DEFINED__ */


#ifndef __IAMDevMemoryAllocator_INTERFACE_DEFINED__
#define __IAMDevMemoryAllocator_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAMDevMemoryAllocator
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IAMDevMemoryAllocator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("c6545bf0-e76b-11d0-bd52-00a0c911ce86")
    IAMDevMemoryAllocator : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetInfo( 
            /* [out] */ DWORD __RPC_FAR *pdwcbTotalFree,
            /* [out] */ DWORD __RPC_FAR *pdwcbLargestFree,
            /* [out] */ DWORD __RPC_FAR *pdwcbTotalMemory,
            /* [out] */ DWORD __RPC_FAR *pdwcbMinimumChunk) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckMemory( 
            /* [in] */ const BYTE __RPC_FAR *pBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Alloc( 
            /* [out] */ BYTE __RPC_FAR *__RPC_FAR *ppBuffer,
            /* [out][in] */ DWORD __RPC_FAR *pdwcbBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Free( 
            /* [in] */ BYTE __RPC_FAR *pBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDevMemoryObject( 
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnkInnner,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMDevMemoryAllocatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAMDevMemoryAllocator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAMDevMemoryAllocator __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAMDevMemoryAllocator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IAMDevMemoryAllocator __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwcbTotalFree,
            /* [out] */ DWORD __RPC_FAR *pdwcbLargestFree,
            /* [out] */ DWORD __RPC_FAR *pdwcbTotalMemory,
            /* [out] */ DWORD __RPC_FAR *pdwcbMinimumChunk);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckMemory )( 
            IAMDevMemoryAllocator __RPC_FAR * This,
            /* [in] */ const BYTE __RPC_FAR *pBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Alloc )( 
            IAMDevMemoryAllocator __RPC_FAR * This,
            /* [out] */ BYTE __RPC_FAR *__RPC_FAR *ppBuffer,
            /* [out][in] */ DWORD __RPC_FAR *pdwcbBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Free )( 
            IAMDevMemoryAllocator __RPC_FAR * This,
            /* [in] */ BYTE __RPC_FAR *pBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDevMemoryObject )( 
            IAMDevMemoryAllocator __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnkInnner,
            /* [in] */ IUnknown __RPC_FAR *pUnkOuter);
        
        END_INTERFACE
    } IAMDevMemoryAllocatorVtbl;

    interface IAMDevMemoryAllocator
    {
        CONST_VTBL struct IAMDevMemoryAllocatorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMDevMemoryAllocator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMDevMemoryAllocator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMDevMemoryAllocator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMDevMemoryAllocator_GetInfo(This,pdwcbTotalFree,pdwcbLargestFree,pdwcbTotalMemory,pdwcbMinimumChunk)	\
    (This)->lpVtbl -> GetInfo(This,pdwcbTotalFree,pdwcbLargestFree,pdwcbTotalMemory,pdwcbMinimumChunk)

#define IAMDevMemoryAllocator_CheckMemory(This,pBuffer)	\
    (This)->lpVtbl -> CheckMemory(This,pBuffer)

#define IAMDevMemoryAllocator_Alloc(This,ppBuffer,pdwcbBuffer)	\
    (This)->lpVtbl -> Alloc(This,ppBuffer,pdwcbBuffer)

#define IAMDevMemoryAllocator_Free(This,pBuffer)	\
    (This)->lpVtbl -> Free(This,pBuffer)

#define IAMDevMemoryAllocator_GetDevMemoryObject(This,ppUnkInnner,pUnkOuter)	\
    (This)->lpVtbl -> GetDevMemoryObject(This,ppUnkInnner,pUnkOuter)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMDevMemoryAllocator_GetInfo_Proxy( 
    IAMDevMemoryAllocator __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwcbTotalFree,
    /* [out] */ DWORD __RPC_FAR *pdwcbLargestFree,
    /* [out] */ DWORD __RPC_FAR *pdwcbTotalMemory,
    /* [out] */ DWORD __RPC_FAR *pdwcbMinimumChunk);


void __RPC_STUB IAMDevMemoryAllocator_GetInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMDevMemoryAllocator_CheckMemory_Proxy( 
    IAMDevMemoryAllocator __RPC_FAR * This,
    /* [in] */ const BYTE __RPC_FAR *pBuffer);


void __RPC_STUB IAMDevMemoryAllocator_CheckMemory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMDevMemoryAllocator_Alloc_Proxy( 
    IAMDevMemoryAllocator __RPC_FAR * This,
    /* [out] */ BYTE __RPC_FAR *__RPC_FAR *ppBuffer,
    /* [out][in] */ DWORD __RPC_FAR *pdwcbBuffer);


void __RPC_STUB IAMDevMemoryAllocator_Alloc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMDevMemoryAllocator_Free_Proxy( 
    IAMDevMemoryAllocator __RPC_FAR * This,
    /* [in] */ BYTE __RPC_FAR *pBuffer);


void __RPC_STUB IAMDevMemoryAllocator_Free_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMDevMemoryAllocator_GetDevMemoryObject_Proxy( 
    IAMDevMemoryAllocator __RPC_FAR * This,
    /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnkInnner,
    /* [in] */ IUnknown __RPC_FAR *pUnkOuter);


void __RPC_STUB IAMDevMemoryAllocator_GetDevMemoryObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMDevMemoryAllocator_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0086
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef IAMDevMemoryAllocator __RPC_FAR *PAMDEVMEMORYALLOCATOR;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0086_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0086_v0_0_s_ifspec;

#ifndef __IAMDevMemoryControl_INTERFACE_DEFINED__
#define __IAMDevMemoryControl_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAMDevMemoryControl
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IAMDevMemoryControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("c6545bf1-e76b-11d0-bd52-00a0c911ce86")
    IAMDevMemoryControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE QueryWriteSync( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WriteSync( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDevId( 
            /* [out] */ DWORD __RPC_FAR *pdwDevId) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMDevMemoryControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAMDevMemoryControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAMDevMemoryControl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAMDevMemoryControl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryWriteSync )( 
            IAMDevMemoryControl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteSync )( 
            IAMDevMemoryControl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDevId )( 
            IAMDevMemoryControl __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwDevId);
        
        END_INTERFACE
    } IAMDevMemoryControlVtbl;

    interface IAMDevMemoryControl
    {
        CONST_VTBL struct IAMDevMemoryControlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMDevMemoryControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMDevMemoryControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMDevMemoryControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMDevMemoryControl_QueryWriteSync(This)	\
    (This)->lpVtbl -> QueryWriteSync(This)

#define IAMDevMemoryControl_WriteSync(This)	\
    (This)->lpVtbl -> WriteSync(This)

#define IAMDevMemoryControl_GetDevId(This,pdwDevId)	\
    (This)->lpVtbl -> GetDevId(This,pdwDevId)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMDevMemoryControl_QueryWriteSync_Proxy( 
    IAMDevMemoryControl __RPC_FAR * This);


void __RPC_STUB IAMDevMemoryControl_QueryWriteSync_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMDevMemoryControl_WriteSync_Proxy( 
    IAMDevMemoryControl __RPC_FAR * This);


void __RPC_STUB IAMDevMemoryControl_WriteSync_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMDevMemoryControl_GetDevId_Proxy( 
    IAMDevMemoryControl __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwDevId);


void __RPC_STUB IAMDevMemoryControl_GetDevId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMDevMemoryControl_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0087
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef IAMDevMemoryControl __RPC_FAR *PAMDEVMEMORYCONTROL;


enum _AMSTREAMSELECTINFOFLAGS
    {	AMSTREAMSELECTINFO_ENABLED	= 0x1,
	AMSTREAMSELECTINFO_EXCLUSIVE	= 0x2
    };

enum _AMSTREAMSELECTENABLEFLAGS
    {	AMSTREAMSELECTENABLE_ENABLE	= 0x1,
	AMSTREAMSELECTENABLE_ENABLEALL	= 0x2
    };


extern RPC_IF_HANDLE __MIDL_itf_strmif_0087_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0087_v0_0_s_ifspec;

#ifndef __IAMStreamSelect_INTERFACE_DEFINED__
#define __IAMStreamSelect_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAMStreamSelect
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IAMStreamSelect;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("c1960960-17f5-11d1-abe1-00a0c905f375")
    IAMStreamSelect : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Count( 
            /* [out] */ DWORD __RPC_FAR *pcStreams) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Info( 
            /* [in] */ long lIndex,
            /* [out] */ AM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *ppmt,
            /* [out] */ DWORD __RPC_FAR *pdwFlags,
            /* [out] */ LCID __RPC_FAR *plcid,
            /* [out] */ DWORD __RPC_FAR *pdwGroup,
            /* [out] */ WCHAR __RPC_FAR *__RPC_FAR *ppszName,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppObject,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Enable( 
            /* [in] */ long lIndex,
            /* [in] */ DWORD dwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMStreamSelectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAMStreamSelect __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAMStreamSelect __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAMStreamSelect __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Count )( 
            IAMStreamSelect __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pcStreams);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Info )( 
            IAMStreamSelect __RPC_FAR * This,
            /* [in] */ long lIndex,
            /* [out] */ AM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *ppmt,
            /* [out] */ DWORD __RPC_FAR *pdwFlags,
            /* [out] */ LCID __RPC_FAR *plcid,
            /* [out] */ DWORD __RPC_FAR *pdwGroup,
            /* [out] */ WCHAR __RPC_FAR *__RPC_FAR *ppszName,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppObject,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Enable )( 
            IAMStreamSelect __RPC_FAR * This,
            /* [in] */ long lIndex,
            /* [in] */ DWORD dwFlags);
        
        END_INTERFACE
    } IAMStreamSelectVtbl;

    interface IAMStreamSelect
    {
        CONST_VTBL struct IAMStreamSelectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMStreamSelect_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMStreamSelect_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMStreamSelect_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMStreamSelect_Count(This,pcStreams)	\
    (This)->lpVtbl -> Count(This,pcStreams)

#define IAMStreamSelect_Info(This,lIndex,ppmt,pdwFlags,plcid,pdwGroup,ppszName,ppObject,ppUnk)	\
    (This)->lpVtbl -> Info(This,lIndex,ppmt,pdwFlags,plcid,pdwGroup,ppszName,ppObject,ppUnk)

#define IAMStreamSelect_Enable(This,lIndex,dwFlags)	\
    (This)->lpVtbl -> Enable(This,lIndex,dwFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMStreamSelect_Count_Proxy( 
    IAMStreamSelect __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pcStreams);


void __RPC_STUB IAMStreamSelect_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMStreamSelect_Info_Proxy( 
    IAMStreamSelect __RPC_FAR * This,
    /* [in] */ long lIndex,
    /* [out] */ AM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *ppmt,
    /* [out] */ DWORD __RPC_FAR *pdwFlags,
    /* [out] */ LCID __RPC_FAR *plcid,
    /* [out] */ DWORD __RPC_FAR *pdwGroup,
    /* [out] */ WCHAR __RPC_FAR *__RPC_FAR *ppszName,
    /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppObject,
    /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);


void __RPC_STUB IAMStreamSelect_Info_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMStreamSelect_Enable_Proxy( 
    IAMStreamSelect __RPC_FAR * This,
    /* [in] */ long lIndex,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IAMStreamSelect_Enable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMStreamSelect_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_strmif_0088
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef IAMStreamSelect __RPC_FAR *PAMSTREAMSELECT;

typedef struct  _REPEAT_AB
    {
    int iPlayItem;
    long lStart;
    long lStop;
    }	REPEAT_AB;

typedef struct _REPEAT_AB __RPC_FAR *PREPEAT_AB;

typedef struct  _STRIDE
    {
    int iPlayItem;
    BOOL bForward;
    int iStep;
    }	STRIDE;

typedef struct _STRIDE __RPC_FAR *PSTRIDE;



extern RPC_IF_HANDLE __MIDL_itf_strmif_0088_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_strmif_0088_v0_0_s_ifspec;

#ifndef __IVideoCDPlaybackSource_INTERFACE_DEFINED__
#define __IVideoCDPlaybackSource_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IVideoCDPlaybackSource
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IVideoCDPlaybackSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("71b0aca0-b5f4-11d0-88b8-08002be53f4a")
    IVideoCDPlaybackSource : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CheckPlayNext( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayNext( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckPlayPrevious( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayPrevious( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckPlayReturn( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayReturn( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayDefault( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayNumeric( 
            /* [in] */ int iNum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckPlayTrack( 
            /* [in] */ int iNum,
            /* [in] */ long lOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayTrack( 
            /* [in] */ int iNum,
            /* [in] */ long lOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckRepeatAB( 
            /* [in] */ PREPEAT_AB pAB) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RepeatAB( 
            /* [in] */ PREPEAT_AB pAB) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckStride( 
            /* [in] */ PSTRIDE pStride) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stride( 
            /* [in] */ PSTRIDE pStride) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVideoCDPlaybackSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVideoCDPlaybackSource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVideoCDPlaybackSource __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVideoCDPlaybackSource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckPlayNext )( 
            IVideoCDPlaybackSource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PlayNext )( 
            IVideoCDPlaybackSource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckPlayPrevious )( 
            IVideoCDPlaybackSource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PlayPrevious )( 
            IVideoCDPlaybackSource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckPlayReturn )( 
            IVideoCDPlaybackSource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PlayReturn )( 
            IVideoCDPlaybackSource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PlayDefault )( 
            IVideoCDPlaybackSource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PlayNumeric )( 
            IVideoCDPlaybackSource __RPC_FAR * This,
            /* [in] */ int iNum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckPlayTrack )( 
            IVideoCDPlaybackSource __RPC_FAR * This,
            /* [in] */ int iNum,
            /* [in] */ long lOffset);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PlayTrack )( 
            IVideoCDPlaybackSource __RPC_FAR * This,
            /* [in] */ int iNum,
            /* [in] */ long lOffset);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckRepeatAB )( 
            IVideoCDPlaybackSource __RPC_FAR * This,
            /* [in] */ PREPEAT_AB pAB);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RepeatAB )( 
            IVideoCDPlaybackSource __RPC_FAR * This,
            /* [in] */ PREPEAT_AB pAB);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckStride )( 
            IVideoCDPlaybackSource __RPC_FAR * This,
            /* [in] */ PSTRIDE pStride);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stride )( 
            IVideoCDPlaybackSource __RPC_FAR * This,
            /* [in] */ PSTRIDE pStride);
        
        END_INTERFACE
    } IVideoCDPlaybackSourceVtbl;

    interface IVideoCDPlaybackSource
    {
        CONST_VTBL struct IVideoCDPlaybackSourceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVideoCDPlaybackSource_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVideoCDPlaybackSource_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVideoCDPlaybackSource_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVideoCDPlaybackSource_CheckPlayNext(This)	\
    (This)->lpVtbl -> CheckPlayNext(This)

#define IVideoCDPlaybackSource_PlayNext(This)	\
    (This)->lpVtbl -> PlayNext(This)

#define IVideoCDPlaybackSource_CheckPlayPrevious(This)	\
    (This)->lpVtbl -> CheckPlayPrevious(This)

#define IVideoCDPlaybackSource_PlayPrevious(This)	\
    (This)->lpVtbl -> PlayPrevious(This)

#define IVideoCDPlaybackSource_CheckPlayReturn(This)	\
    (This)->lpVtbl -> CheckPlayReturn(This)

#define IVideoCDPlaybackSource_PlayReturn(This)	\
    (This)->lpVtbl -> PlayReturn(This)

#define IVideoCDPlaybackSource_PlayDefault(This)	\
    (This)->lpVtbl -> PlayDefault(This)

#define IVideoCDPlaybackSource_PlayNumeric(This,iNum)	\
    (This)->lpVtbl -> PlayNumeric(This,iNum)

#define IVideoCDPlaybackSource_CheckPlayTrack(This,iNum,lOffset)	\
    (This)->lpVtbl -> CheckPlayTrack(This,iNum,lOffset)

#define IVideoCDPlaybackSource_PlayTrack(This,iNum,lOffset)	\
    (This)->lpVtbl -> PlayTrack(This,iNum,lOffset)

#define IVideoCDPlaybackSource_CheckRepeatAB(This,pAB)	\
    (This)->lpVtbl -> CheckRepeatAB(This,pAB)

#define IVideoCDPlaybackSource_RepeatAB(This,pAB)	\
    (This)->lpVtbl -> RepeatAB(This,pAB)

#define IVideoCDPlaybackSource_CheckStride(This,pStride)	\
    (This)->lpVtbl -> CheckStride(This,pStride)

#define IVideoCDPlaybackSource_Stride(This,pStride)	\
    (This)->lpVtbl -> Stride(This,pStride)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVideoCDPlaybackSource_CheckPlayNext_Proxy( 
    IVideoCDPlaybackSource __RPC_FAR * This);


void __RPC_STUB IVideoCDPlaybackSource_CheckPlayNext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDPlaybackSource_PlayNext_Proxy( 
    IVideoCDPlaybackSource __RPC_FAR * This);


void __RPC_STUB IVideoCDPlaybackSource_PlayNext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDPlaybackSource_CheckPlayPrevious_Proxy( 
    IVideoCDPlaybackSource __RPC_FAR * This);


void __RPC_STUB IVideoCDPlaybackSource_CheckPlayPrevious_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDPlaybackSource_PlayPrevious_Proxy( 
    IVideoCDPlaybackSource __RPC_FAR * This);


void __RPC_STUB IVideoCDPlaybackSource_PlayPrevious_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDPlaybackSource_CheckPlayReturn_Proxy( 
    IVideoCDPlaybackSource __RPC_FAR * This);


void __RPC_STUB IVideoCDPlaybackSource_CheckPlayReturn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDPlaybackSource_PlayReturn_Proxy( 
    IVideoCDPlaybackSource __RPC_FAR * This);


void __RPC_STUB IVideoCDPlaybackSource_PlayReturn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDPlaybackSource_PlayDefault_Proxy( 
    IVideoCDPlaybackSource __RPC_FAR * This);


void __RPC_STUB IVideoCDPlaybackSource_PlayDefault_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDPlaybackSource_PlayNumeric_Proxy( 
    IVideoCDPlaybackSource __RPC_FAR * This,
    /* [in] */ int iNum);


void __RPC_STUB IVideoCDPlaybackSource_PlayNumeric_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDPlaybackSource_CheckPlayTrack_Proxy( 
    IVideoCDPlaybackSource __RPC_FAR * This,
    /* [in] */ int iNum,
    /* [in] */ long lOffset);


void __RPC_STUB IVideoCDPlaybackSource_CheckPlayTrack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDPlaybackSource_PlayTrack_Proxy( 
    IVideoCDPlaybackSource __RPC_FAR * This,
    /* [in] */ int iNum,
    /* [in] */ long lOffset);


void __RPC_STUB IVideoCDPlaybackSource_PlayTrack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDPlaybackSource_CheckRepeatAB_Proxy( 
    IVideoCDPlaybackSource __RPC_FAR * This,
    /* [in] */ PREPEAT_AB pAB);


void __RPC_STUB IVideoCDPlaybackSource_CheckRepeatAB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDPlaybackSource_RepeatAB_Proxy( 
    IVideoCDPlaybackSource __RPC_FAR * This,
    /* [in] */ PREPEAT_AB pAB);


void __RPC_STUB IVideoCDPlaybackSource_RepeatAB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDPlaybackSource_CheckStride_Proxy( 
    IVideoCDPlaybackSource __RPC_FAR * This,
    /* [in] */ PSTRIDE pStride);


void __RPC_STUB IVideoCDPlaybackSource_CheckStride_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDPlaybackSource_Stride_Proxy( 
    IVideoCDPlaybackSource __RPC_FAR * This,
    /* [in] */ PSTRIDE pStride);


void __RPC_STUB IVideoCDPlaybackSource_Stride_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVideoCDPlaybackSource_INTERFACE_DEFINED__ */


#ifndef __IVideoCDPlaybackRendering_INTERFACE_DEFINED__
#define __IVideoCDPlaybackRendering_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IVideoCDPlaybackRendering
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IVideoCDPlaybackRendering;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("71b0aca1-b5f4-11d0-88b8-08002be53f4a")
    IVideoCDPlaybackRendering : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetPlayItem( 
            /* [out] */ int __RPC_FAR *pPlayItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTrack( 
            /* [out] */ int __RPC_FAR *pTrackNum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMediaTime( 
            /* [out] */ long __RPC_FAR *pSeconds) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DisplayStillFrame( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SlowForward( 
            /* [in] */ double dRate) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVideoCDPlaybackRenderingVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVideoCDPlaybackRendering __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVideoCDPlaybackRendering __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVideoCDPlaybackRendering __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPlayItem )( 
            IVideoCDPlaybackRendering __RPC_FAR * This,
            /* [out] */ int __RPC_FAR *pPlayItem);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTrack )( 
            IVideoCDPlaybackRendering __RPC_FAR * This,
            /* [out] */ int __RPC_FAR *pTrackNum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMediaTime )( 
            IVideoCDPlaybackRendering __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pSeconds);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisplayStillFrame )( 
            IVideoCDPlaybackRendering __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SlowForward )( 
            IVideoCDPlaybackRendering __RPC_FAR * This,
            /* [in] */ double dRate);
        
        END_INTERFACE
    } IVideoCDPlaybackRenderingVtbl;

    interface IVideoCDPlaybackRendering
    {
        CONST_VTBL struct IVideoCDPlaybackRenderingVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVideoCDPlaybackRendering_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVideoCDPlaybackRendering_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVideoCDPlaybackRendering_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVideoCDPlaybackRendering_GetPlayItem(This,pPlayItem)	\
    (This)->lpVtbl -> GetPlayItem(This,pPlayItem)

#define IVideoCDPlaybackRendering_GetTrack(This,pTrackNum)	\
    (This)->lpVtbl -> GetTrack(This,pTrackNum)

#define IVideoCDPlaybackRendering_GetMediaTime(This,pSeconds)	\
    (This)->lpVtbl -> GetMediaTime(This,pSeconds)

#define IVideoCDPlaybackRendering_DisplayStillFrame(This)	\
    (This)->lpVtbl -> DisplayStillFrame(This)

#define IVideoCDPlaybackRendering_SlowForward(This,dRate)	\
    (This)->lpVtbl -> SlowForward(This,dRate)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVideoCDPlaybackRendering_GetPlayItem_Proxy( 
    IVideoCDPlaybackRendering __RPC_FAR * This,
    /* [out] */ int __RPC_FAR *pPlayItem);


void __RPC_STUB IVideoCDPlaybackRendering_GetPlayItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDPlaybackRendering_GetTrack_Proxy( 
    IVideoCDPlaybackRendering __RPC_FAR * This,
    /* [out] */ int __RPC_FAR *pTrackNum);


void __RPC_STUB IVideoCDPlaybackRendering_GetTrack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDPlaybackRendering_GetMediaTime_Proxy( 
    IVideoCDPlaybackRendering __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pSeconds);


void __RPC_STUB IVideoCDPlaybackRendering_GetMediaTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDPlaybackRendering_DisplayStillFrame_Proxy( 
    IVideoCDPlaybackRendering __RPC_FAR * This);


void __RPC_STUB IVideoCDPlaybackRendering_DisplayStillFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDPlaybackRendering_SlowForward_Proxy( 
    IVideoCDPlaybackRendering __RPC_FAR * This,
    /* [in] */ double dRate);


void __RPC_STUB IVideoCDPlaybackRendering_SlowForward_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVideoCDPlaybackRendering_INTERFACE_DEFINED__ */


#ifndef __IVideoCDManager_INTERFACE_DEFINED__
#define __IVideoCDManager_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IVideoCDManager
 * at Fri Feb 18 03:27:33 2000
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IVideoCDManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("15818aa0-a6da-11d0-88b8-08002be53f4a")
    IVideoCDManager : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Run( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Pause( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEventHandle( 
            /* [out] */ HEVENT __RPC_FAR *hEvent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEvent( 
            /* [out] */ long __RPC_FAR *lEventCode,
            /* [out] */ long __RPC_FAR *lParam1,
            /* [out] */ long __RPC_FAR *lParam2,
            /* [in] */ long msTimeout) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FreeEventParams( 
            /* [in] */ long lEvCode,
            /* [in] */ long lParam1,
            /* [in] */ long lParam2) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WaitForCompletion( 
            /* [in] */ long msTimeout,
            /* [out] */ long __RPC_FAR *pEvCode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CancelDefaultHandling( 
            /* [in] */ long lEvCode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RestoreDefaultHandling( 
            /* [in] */ long lEvCode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayNext( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayPrevious( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayDefault( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayReturn( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayNumeric( 
            /* [in] */ int iNum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PlayTrack( 
            /* [in] */ int iNum,
            /* [in] */ long lOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RepeatAB( 
            /* [in] */ PREPEAT_AB pAB) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stride( 
            /* [in] */ PSTRIDE pStride) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPlayItem( 
            /* [out] */ int __RPC_FAR *pPlayItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTrack( 
            /* [out] */ int __RPC_FAR *pTrackNum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMediaTime( 
            /* [out] */ long __RPC_FAR *pSeconds) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DisplayStillFrame( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SlowForward( 
            double dRate) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVideoCDManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVideoCDManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVideoCDManager __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVideoCDManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Run )( 
            IVideoCDManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pause )( 
            IVideoCDManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IVideoCDManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEventHandle )( 
            IVideoCDManager __RPC_FAR * This,
            /* [out] */ HEVENT __RPC_FAR *hEvent);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEvent )( 
            IVideoCDManager __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *lEventCode,
            /* [out] */ long __RPC_FAR *lParam1,
            /* [out] */ long __RPC_FAR *lParam2,
            /* [in] */ long msTimeout);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FreeEventParams )( 
            IVideoCDManager __RPC_FAR * This,
            /* [in] */ long lEvCode,
            /* [in] */ long lParam1,
            /* [in] */ long lParam2);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitForCompletion )( 
            IVideoCDManager __RPC_FAR * This,
            /* [in] */ long msTimeout,
            /* [out] */ long __RPC_FAR *pEvCode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CancelDefaultHandling )( 
            IVideoCDManager __RPC_FAR * This,
            /* [in] */ long lEvCode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RestoreDefaultHandling )( 
            IVideoCDManager __RPC_FAR * This,
            /* [in] */ long lEvCode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PlayNext )( 
            IVideoCDManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PlayPrevious )( 
            IVideoCDManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PlayDefault )( 
            IVideoCDManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PlayReturn )( 
            IVideoCDManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PlayNumeric )( 
            IVideoCDManager __RPC_FAR * This,
            /* [in] */ int iNum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PlayTrack )( 
            IVideoCDManager __RPC_FAR * This,
            /* [in] */ int iNum,
            /* [in] */ long lOffset);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RepeatAB )( 
            IVideoCDManager __RPC_FAR * This,
            /* [in] */ PREPEAT_AB pAB);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stride )( 
            IVideoCDManager __RPC_FAR * This,
            /* [in] */ PSTRIDE pStride);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPlayItem )( 
            IVideoCDManager __RPC_FAR * This,
            /* [out] */ int __RPC_FAR *pPlayItem);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTrack )( 
            IVideoCDManager __RPC_FAR * This,
            /* [out] */ int __RPC_FAR *pTrackNum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMediaTime )( 
            IVideoCDManager __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pSeconds);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisplayStillFrame )( 
            IVideoCDManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SlowForward )( 
            IVideoCDManager __RPC_FAR * This,
            double dRate);
        
        END_INTERFACE
    } IVideoCDManagerVtbl;

    interface IVideoCDManager
    {
        CONST_VTBL struct IVideoCDManagerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVideoCDManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVideoCDManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVideoCDManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVideoCDManager_Run(This)	\
    (This)->lpVtbl -> Run(This)

#define IVideoCDManager_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IVideoCDManager_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IVideoCDManager_GetEventHandle(This,hEvent)	\
    (This)->lpVtbl -> GetEventHandle(This,hEvent)

#define IVideoCDManager_GetEvent(This,lEventCode,lParam1,lParam2,msTimeout)	\
    (This)->lpVtbl -> GetEvent(This,lEventCode,lParam1,lParam2,msTimeout)

#define IVideoCDManager_FreeEventParams(This,lEvCode,lParam1,lParam2)	\
    (This)->lpVtbl -> FreeEventParams(This,lEvCode,lParam1,lParam2)

#define IVideoCDManager_WaitForCompletion(This,msTimeout,pEvCode)	\
    (This)->lpVtbl -> WaitForCompletion(This,msTimeout,pEvCode)

#define IVideoCDManager_CancelDefaultHandling(This,lEvCode)	\
    (This)->lpVtbl -> CancelDefaultHandling(This,lEvCode)

#define IVideoCDManager_RestoreDefaultHandling(This,lEvCode)	\
    (This)->lpVtbl -> RestoreDefaultHandling(This,lEvCode)

#define IVideoCDManager_PlayNext(This)	\
    (This)->lpVtbl -> PlayNext(This)

#define IVideoCDManager_PlayPrevious(This)	\
    (This)->lpVtbl -> PlayPrevious(This)

#define IVideoCDManager_PlayDefault(This)	\
    (This)->lpVtbl -> PlayDefault(This)

#define IVideoCDManager_PlayReturn(This)	\
    (This)->lpVtbl -> PlayReturn(This)

#define IVideoCDManager_PlayNumeric(This,iNum)	\
    (This)->lpVtbl -> PlayNumeric(This,iNum)

#define IVideoCDManager_PlayTrack(This,iNum,lOffset)	\
    (This)->lpVtbl -> PlayTrack(This,iNum,lOffset)

#define IVideoCDManager_RepeatAB(This,pAB)	\
    (This)->lpVtbl -> RepeatAB(This,pAB)

#define IVideoCDManager_Stride(This,pStride)	\
    (This)->lpVtbl -> Stride(This,pStride)

#define IVideoCDManager_GetPlayItem(This,pPlayItem)	\
    (This)->lpVtbl -> GetPlayItem(This,pPlayItem)

#define IVideoCDManager_GetTrack(This,pTrackNum)	\
    (This)->lpVtbl -> GetTrack(This,pTrackNum)

#define IVideoCDManager_GetMediaTime(This,pSeconds)	\
    (This)->lpVtbl -> GetMediaTime(This,pSeconds)

#define IVideoCDManager_DisplayStillFrame(This)	\
    (This)->lpVtbl -> DisplayStillFrame(This)

#define IVideoCDManager_SlowForward(This,dRate)	\
    (This)->lpVtbl -> SlowForward(This,dRate)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVideoCDManager_Run_Proxy( 
    IVideoCDManager __RPC_FAR * This);


void __RPC_STUB IVideoCDManager_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDManager_Pause_Proxy( 
    IVideoCDManager __RPC_FAR * This);


void __RPC_STUB IVideoCDManager_Pause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDManager_Stop_Proxy( 
    IVideoCDManager __RPC_FAR * This);


void __RPC_STUB IVideoCDManager_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDManager_GetEventHandle_Proxy( 
    IVideoCDManager __RPC_FAR * This,
    /* [out] */ HEVENT __RPC_FAR *hEvent);


void __RPC_STUB IVideoCDManager_GetEventHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDManager_GetEvent_Proxy( 
    IVideoCDManager __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *lEventCode,
    /* [out] */ long __RPC_FAR *lParam1,
    /* [out] */ long __RPC_FAR *lParam2,
    /* [in] */ long msTimeout);


void __RPC_STUB IVideoCDManager_GetEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDManager_FreeEventParams_Proxy( 
    IVideoCDManager __RPC_FAR * This,
    /* [in] */ long lEvCode,
    /* [in] */ long lParam1,
    /* [in] */ long lParam2);


void __RPC_STUB IVideoCDManager_FreeEventParams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDManager_WaitForCompletion_Proxy( 
    IVideoCDManager __RPC_FAR * This,
    /* [in] */ long msTimeout,
    /* [out] */ long __RPC_FAR *pEvCode);


void __RPC_STUB IVideoCDManager_WaitForCompletion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDManager_CancelDefaultHandling_Proxy( 
    IVideoCDManager __RPC_FAR * This,
    /* [in] */ long lEvCode);


void __RPC_STUB IVideoCDManager_CancelDefaultHandling_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDManager_RestoreDefaultHandling_Proxy( 
    IVideoCDManager __RPC_FAR * This,
    /* [in] */ long lEvCode);


void __RPC_STUB IVideoCDManager_RestoreDefaultHandling_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDManager_PlayNext_Proxy( 
    IVideoCDManager __RPC_FAR * This);


void __RPC_STUB IVideoCDManager_PlayNext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDManager_PlayPrevious_Proxy( 
    IVideoCDManager __RPC_FAR * This);


void __RPC_STUB IVideoCDManager_PlayPrevious_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDManager_PlayDefault_Proxy( 
    IVideoCDManager __RPC_FAR * This);


void __RPC_STUB IVideoCDManager_PlayDefault_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDManager_PlayReturn_Proxy( 
    IVideoCDManager __RPC_FAR * This);


void __RPC_STUB IVideoCDManager_PlayReturn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDManager_PlayNumeric_Proxy( 
    IVideoCDManager __RPC_FAR * This,
    /* [in] */ int iNum);


void __RPC_STUB IVideoCDManager_PlayNumeric_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDManager_PlayTrack_Proxy( 
    IVideoCDManager __RPC_FAR * This,
    /* [in] */ int iNum,
    /* [in] */ long lOffset);


void __RPC_STUB IVideoCDManager_PlayTrack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDManager_RepeatAB_Proxy( 
    IVideoCDManager __RPC_FAR * This,
    /* [in] */ PREPEAT_AB pAB);


void __RPC_STUB IVideoCDManager_RepeatAB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDManager_Stride_Proxy( 
    IVideoCDManager __RPC_FAR * This,
    /* [in] */ PSTRIDE pStride);


void __RPC_STUB IVideoCDManager_Stride_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDManager_GetPlayItem_Proxy( 
    IVideoCDManager __RPC_FAR * This,
    /* [out] */ int __RPC_FAR *pPlayItem);


void __RPC_STUB IVideoCDManager_GetPlayItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDManager_GetTrack_Proxy( 
    IVideoCDManager __RPC_FAR * This,
    /* [out] */ int __RPC_FAR *pTrackNum);


void __RPC_STUB IVideoCDManager_GetTrack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDManager_GetMediaTime_Proxy( 
    IVideoCDManager __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pSeconds);


void __RPC_STUB IVideoCDManager_GetMediaTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDManager_DisplayStillFrame_Proxy( 
    IVideoCDManager __RPC_FAR * This);


void __RPC_STUB IVideoCDManager_DisplayStillFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoCDManager_SlowForward_Proxy( 
    IVideoCDManager __RPC_FAR * This,
    double dRate);


void __RPC_STUB IVideoCDManager_SlowForward_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVideoCDManager_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
