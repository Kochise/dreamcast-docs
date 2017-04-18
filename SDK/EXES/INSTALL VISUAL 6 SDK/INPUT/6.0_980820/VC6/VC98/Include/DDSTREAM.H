/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.02.88 */
/* at Thu Nov 13 19:28:35 1997
 */
/* Compiler settings for ddstream.idl:
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

#ifndef __ddstream_h__
#define __ddstream_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDirectDrawMediaStream_FWD_DEFINED__
#define __IDirectDrawMediaStream_FWD_DEFINED__
typedef interface IDirectDrawMediaStream IDirectDrawMediaStream;
#endif 	/* __IDirectDrawMediaStream_FWD_DEFINED__ */


#ifndef __IDirectDrawStreamSample_FWD_DEFINED__
#define __IDirectDrawStreamSample_FWD_DEFINED__
typedef interface IDirectDrawStreamSample IDirectDrawStreamSample;
#endif 	/* __IDirectDrawStreamSample_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "mmstream.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_ddstream_0000
 * at Thu Nov 13 19:28:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


//
//	The following declarations within the 'if 0' block are dummy typedefs used to make
//	the ddstream.idl file build.  The actual definitions are contained in DDRAW.H
//
#if 0
typedef void __RPC_FAR *LPDDSURFACEDESC;

typedef struct tDDSURFACEDESC DDSURFACEDESC;

#endif
#include <ddraw.h>

enum __MIDL___MIDL_itf_ddstream_0000_0001
    {	DDSFF_PROGRESSIVERENDER	= 0x1
    };







extern RPC_IF_HANDLE __MIDL_itf_ddstream_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ddstream_0000_v0_0_s_ifspec;

#ifndef __IDirectDrawMediaStream_INTERFACE_DEFINED__
#define __IDirectDrawMediaStream_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDirectDrawMediaStream
 * at Thu Nov 13 19:28:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][local][object] */ 



EXTERN_C const IID IID_IDirectDrawMediaStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("F4104FCE-9A70-11d0-8FDE-00C04FD9189D")
    IDirectDrawMediaStream : public IMediaStream
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetFormat( 
            /* [optional][out] */ DDSURFACEDESC __RPC_FAR *pDDSDCurrent,
            /* [optional][out] */ IDirectDrawPalette __RPC_FAR *__RPC_FAR *ppDirectDrawPalette,
            /* [optional][out] */ DDSURFACEDESC __RPC_FAR *pDDSDDesired,
            /* [optional][out] */ DWORD __RPC_FAR *pdwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFormat( 
            /* [in] */ const DDSURFACEDESC __RPC_FAR *pDDSurfaceDesc,
            /* [optional][in] */ IDirectDrawPalette __RPC_FAR *pDirectDrawPalette) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDirectDraw( 
            /* [out] */ IDirectDraw __RPC_FAR *__RPC_FAR *ppDirectDraw) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDirectDraw( 
            /* [in] */ IDirectDraw __RPC_FAR *pDirectDraw) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateSample( 
            /* [optional][in] */ IDirectDrawSurface __RPC_FAR *pSurface,
            /* [optional][in] */ const RECT __RPC_FAR *pRect,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDirectDrawStreamSample __RPC_FAR *__RPC_FAR *ppSample) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTimePerFrame( 
            /* [out] */ STREAM_TIME __RPC_FAR *pFrameTime) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDirectDrawMediaStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDirectDrawMediaStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDirectDrawMediaStream __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDirectDrawMediaStream __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMultiMediaStream )( 
            IDirectDrawMediaStream __RPC_FAR * This,
            /* [out] */ IMultiMediaStream __RPC_FAR *__RPC_FAR *ppMultiMediaStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInformation )( 
            IDirectDrawMediaStream __RPC_FAR * This,
            /* [optional][out] */ MSPID __RPC_FAR *pPurposeId,
            /* [optional][out] */ STREAM_TYPE __RPC_FAR *pType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSameFormat )( 
            IDirectDrawMediaStream __RPC_FAR * This,
            /* [in] */ IMediaStream __RPC_FAR *pStreamThatHasDesiredFormat,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AllocateSample )( 
            IDirectDrawMediaStream __RPC_FAR * This,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IStreamSample __RPC_FAR *__RPC_FAR *ppSample);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateSharedSample )( 
            IDirectDrawMediaStream __RPC_FAR * This,
            /* [in] */ IStreamSample __RPC_FAR *pExistingSample,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IStreamSample __RPC_FAR *__RPC_FAR *ppNewSample);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendEndOfStream )( 
            IDirectDrawMediaStream __RPC_FAR * This,
            DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFormat )( 
            IDirectDrawMediaStream __RPC_FAR * This,
            /* [optional][out] */ DDSURFACEDESC __RPC_FAR *pDDSDCurrent,
            /* [optional][out] */ IDirectDrawPalette __RPC_FAR *__RPC_FAR *ppDirectDrawPalette,
            /* [optional][out] */ DDSURFACEDESC __RPC_FAR *pDDSDDesired,
            /* [optional][out] */ DWORD __RPC_FAR *pdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFormat )( 
            IDirectDrawMediaStream __RPC_FAR * This,
            /* [in] */ const DDSURFACEDESC __RPC_FAR *pDDSurfaceDesc,
            /* [optional][in] */ IDirectDrawPalette __RPC_FAR *pDirectDrawPalette);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDirectDraw )( 
            IDirectDrawMediaStream __RPC_FAR * This,
            /* [out] */ IDirectDraw __RPC_FAR *__RPC_FAR *ppDirectDraw);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDirectDraw )( 
            IDirectDrawMediaStream __RPC_FAR * This,
            /* [in] */ IDirectDraw __RPC_FAR *pDirectDraw);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateSample )( 
            IDirectDrawMediaStream __RPC_FAR * This,
            /* [optional][in] */ IDirectDrawSurface __RPC_FAR *pSurface,
            /* [optional][in] */ const RECT __RPC_FAR *pRect,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IDirectDrawStreamSample __RPC_FAR *__RPC_FAR *ppSample);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTimePerFrame )( 
            IDirectDrawMediaStream __RPC_FAR * This,
            /* [out] */ STREAM_TIME __RPC_FAR *pFrameTime);
        
        END_INTERFACE
    } IDirectDrawMediaStreamVtbl;

    interface IDirectDrawMediaStream
    {
        CONST_VTBL struct IDirectDrawMediaStreamVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDirectDrawMediaStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDirectDrawMediaStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDirectDrawMediaStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDirectDrawMediaStream_GetMultiMediaStream(This,ppMultiMediaStream)	\
    (This)->lpVtbl -> GetMultiMediaStream(This,ppMultiMediaStream)

#define IDirectDrawMediaStream_GetInformation(This,pPurposeId,pType)	\
    (This)->lpVtbl -> GetInformation(This,pPurposeId,pType)

#define IDirectDrawMediaStream_SetSameFormat(This,pStreamThatHasDesiredFormat,dwFlags)	\
    (This)->lpVtbl -> SetSameFormat(This,pStreamThatHasDesiredFormat,dwFlags)

#define IDirectDrawMediaStream_AllocateSample(This,dwFlags,ppSample)	\
    (This)->lpVtbl -> AllocateSample(This,dwFlags,ppSample)

#define IDirectDrawMediaStream_CreateSharedSample(This,pExistingSample,dwFlags,ppNewSample)	\
    (This)->lpVtbl -> CreateSharedSample(This,pExistingSample,dwFlags,ppNewSample)

#define IDirectDrawMediaStream_SendEndOfStream(This,dwFlags)	\
    (This)->lpVtbl -> SendEndOfStream(This,dwFlags)


#define IDirectDrawMediaStream_GetFormat(This,pDDSDCurrent,ppDirectDrawPalette,pDDSDDesired,pdwFlags)	\
    (This)->lpVtbl -> GetFormat(This,pDDSDCurrent,ppDirectDrawPalette,pDDSDDesired,pdwFlags)

#define IDirectDrawMediaStream_SetFormat(This,pDDSurfaceDesc,pDirectDrawPalette)	\
    (This)->lpVtbl -> SetFormat(This,pDDSurfaceDesc,pDirectDrawPalette)

#define IDirectDrawMediaStream_GetDirectDraw(This,ppDirectDraw)	\
    (This)->lpVtbl -> GetDirectDraw(This,ppDirectDraw)

#define IDirectDrawMediaStream_SetDirectDraw(This,pDirectDraw)	\
    (This)->lpVtbl -> SetDirectDraw(This,pDirectDraw)

#define IDirectDrawMediaStream_CreateSample(This,pSurface,pRect,dwFlags,ppSample)	\
    (This)->lpVtbl -> CreateSample(This,pSurface,pRect,dwFlags,ppSample)

#define IDirectDrawMediaStream_GetTimePerFrame(This,pFrameTime)	\
    (This)->lpVtbl -> GetTimePerFrame(This,pFrameTime)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDirectDrawMediaStream_GetFormat_Proxy( 
    IDirectDrawMediaStream __RPC_FAR * This,
    /* [optional][out] */ DDSURFACEDESC __RPC_FAR *pDDSDCurrent,
    /* [optional][out] */ IDirectDrawPalette __RPC_FAR *__RPC_FAR *ppDirectDrawPalette,
    /* [optional][out] */ DDSURFACEDESC __RPC_FAR *pDDSDDesired,
    /* [optional][out] */ DWORD __RPC_FAR *pdwFlags);


void __RPC_STUB IDirectDrawMediaStream_GetFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectDrawMediaStream_SetFormat_Proxy( 
    IDirectDrawMediaStream __RPC_FAR * This,
    /* [in] */ const DDSURFACEDESC __RPC_FAR *pDDSurfaceDesc,
    /* [optional][in] */ IDirectDrawPalette __RPC_FAR *pDirectDrawPalette);


void __RPC_STUB IDirectDrawMediaStream_SetFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectDrawMediaStream_GetDirectDraw_Proxy( 
    IDirectDrawMediaStream __RPC_FAR * This,
    /* [out] */ IDirectDraw __RPC_FAR *__RPC_FAR *ppDirectDraw);


void __RPC_STUB IDirectDrawMediaStream_GetDirectDraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectDrawMediaStream_SetDirectDraw_Proxy( 
    IDirectDrawMediaStream __RPC_FAR * This,
    /* [in] */ IDirectDraw __RPC_FAR *pDirectDraw);


void __RPC_STUB IDirectDrawMediaStream_SetDirectDraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectDrawMediaStream_CreateSample_Proxy( 
    IDirectDrawMediaStream __RPC_FAR * This,
    /* [optional][in] */ IDirectDrawSurface __RPC_FAR *pSurface,
    /* [optional][in] */ const RECT __RPC_FAR *pRect,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IDirectDrawStreamSample __RPC_FAR *__RPC_FAR *ppSample);


void __RPC_STUB IDirectDrawMediaStream_CreateSample_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectDrawMediaStream_GetTimePerFrame_Proxy( 
    IDirectDrawMediaStream __RPC_FAR * This,
    /* [out] */ STREAM_TIME __RPC_FAR *pFrameTime);


void __RPC_STUB IDirectDrawMediaStream_GetTimePerFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDirectDrawMediaStream_INTERFACE_DEFINED__ */


#ifndef __IDirectDrawStreamSample_INTERFACE_DEFINED__
#define __IDirectDrawStreamSample_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDirectDrawStreamSample
 * at Thu Nov 13 19:28:35 1997
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][local][object] */ 



EXTERN_C const IID IID_IDirectDrawStreamSample;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("F4104FCF-9A70-11d0-8FDE-00C04FD9189D")
    IDirectDrawStreamSample : public IStreamSample
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetSurface( 
            /* [optional][out] */ IDirectDrawSurface __RPC_FAR *__RPC_FAR *ppDirectDrawSurface,
            /* [optional][out] */ RECT __RPC_FAR *pRect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetRect( 
            /* [in] */ const RECT __RPC_FAR *pRect) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDirectDrawStreamSampleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDirectDrawStreamSample __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDirectDrawStreamSample __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDirectDrawStreamSample __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMediaStream )( 
            IDirectDrawStreamSample __RPC_FAR * This,
            /* [in] */ IMediaStream __RPC_FAR *__RPC_FAR *ppMediaStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSampleTimes )( 
            IDirectDrawStreamSample __RPC_FAR * This,
            /* [optional][out] */ STREAM_TIME __RPC_FAR *pStartTime,
            /* [optional][out] */ STREAM_TIME __RPC_FAR *pEndTime,
            /* [optional][out] */ STREAM_TIME __RPC_FAR *pCurrentTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSampleTimes )( 
            IDirectDrawStreamSample __RPC_FAR * This,
            /* [optional][in] */ const STREAM_TIME __RPC_FAR *pStartTime,
            /* [optional][in] */ const STREAM_TIME __RPC_FAR *pEndTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Update )( 
            IDirectDrawStreamSample __RPC_FAR * This,
            /* [in] */ DWORD dwFlags,
            /* [optional][in] */ HANDLE hEvent,
            /* [optional][in] */ PAPCFUNC pfnAPC,
            /* [optional][in] */ DWORD dwAPCData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CompletionStatus )( 
            IDirectDrawStreamSample __RPC_FAR * This,
            /* [in] */ DWORD dwFlags,
            /* [optional][in] */ DWORD dwMilliseconds);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSurface )( 
            IDirectDrawStreamSample __RPC_FAR * This,
            /* [optional][out] */ IDirectDrawSurface __RPC_FAR *__RPC_FAR *ppDirectDrawSurface,
            /* [optional][out] */ RECT __RPC_FAR *pRect);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetRect )( 
            IDirectDrawStreamSample __RPC_FAR * This,
            /* [in] */ const RECT __RPC_FAR *pRect);
        
        END_INTERFACE
    } IDirectDrawStreamSampleVtbl;

    interface IDirectDrawStreamSample
    {
        CONST_VTBL struct IDirectDrawStreamSampleVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDirectDrawStreamSample_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDirectDrawStreamSample_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDirectDrawStreamSample_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDirectDrawStreamSample_GetMediaStream(This,ppMediaStream)	\
    (This)->lpVtbl -> GetMediaStream(This,ppMediaStream)

#define IDirectDrawStreamSample_GetSampleTimes(This,pStartTime,pEndTime,pCurrentTime)	\
    (This)->lpVtbl -> GetSampleTimes(This,pStartTime,pEndTime,pCurrentTime)

#define IDirectDrawStreamSample_SetSampleTimes(This,pStartTime,pEndTime)	\
    (This)->lpVtbl -> SetSampleTimes(This,pStartTime,pEndTime)

#define IDirectDrawStreamSample_Update(This,dwFlags,hEvent,pfnAPC,dwAPCData)	\
    (This)->lpVtbl -> Update(This,dwFlags,hEvent,pfnAPC,dwAPCData)

#define IDirectDrawStreamSample_CompletionStatus(This,dwFlags,dwMilliseconds)	\
    (This)->lpVtbl -> CompletionStatus(This,dwFlags,dwMilliseconds)


#define IDirectDrawStreamSample_GetSurface(This,ppDirectDrawSurface,pRect)	\
    (This)->lpVtbl -> GetSurface(This,ppDirectDrawSurface,pRect)

#define IDirectDrawStreamSample_SetRect(This,pRect)	\
    (This)->lpVtbl -> SetRect(This,pRect)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDirectDrawStreamSample_GetSurface_Proxy( 
    IDirectDrawStreamSample __RPC_FAR * This,
    /* [optional][out] */ IDirectDrawSurface __RPC_FAR *__RPC_FAR *ppDirectDrawSurface,
    /* [optional][out] */ RECT __RPC_FAR *pRect);


void __RPC_STUB IDirectDrawStreamSample_GetSurface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectDrawStreamSample_SetRect_Proxy( 
    IDirectDrawStreamSample __RPC_FAR * This,
    /* [in] */ const RECT __RPC_FAR *pRect);


void __RPC_STUB IDirectDrawStreamSample_SetRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDirectDrawStreamSample_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
