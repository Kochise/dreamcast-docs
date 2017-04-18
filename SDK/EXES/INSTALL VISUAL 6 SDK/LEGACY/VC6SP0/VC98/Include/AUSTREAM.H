/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.02.88 */
/* at Thu Nov 13 19:28:38 1997
 */
/* Compiler settings for austream.idl:
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

#ifndef __austream_h__
#define __austream_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAudioMediaStream_FWD_DEFINED__
#define __IAudioMediaStream_FWD_DEFINED__
typedef interface IAudioMediaStream IAudioMediaStream;
#endif 	/* __IAudioMediaStream_FWD_DEFINED__ */


#ifndef __IAudioStreamSample_FWD_DEFINED__
#define __IAudioStreamSample_FWD_DEFINED__
typedef interface IAudioStreamSample IAudioStreamSample;
#endif 	/* __IAudioStreamSample_FWD_DEFINED__ */


#ifndef __IMemoryData_FWD_DEFINED__
#define __IMemoryData_FWD_DEFINED__
typedef interface IMemoryData IMemoryData;
#endif 	/* __IMemoryData_FWD_DEFINED__ */


#ifndef __IAudioData_FWD_DEFINED__
#define __IAudioData_FWD_DEFINED__
typedef interface IAudioData IAudioData;
#endif 	/* __IAudioData_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "mmstream.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_austream_0000
 * at Thu Nov 13 19:28:38 1997
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


//
//	The following declarations within the 'if 0' block are dummy typedefs used to make
//	the ddstream.idl file build.  The actual definitions are contained in DDRAW.H
//
#if 0
typedef struct tWAVEFORMATEX WAVEFORMATEX;

#endif






extern RPC_IF_HANDLE __MIDL_itf_austream_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_austream_0000_v0_0_s_ifspec;

#ifndef __IAudioMediaStream_INTERFACE_DEFINED__
#define __IAudioMediaStream_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAudioMediaStream
 * at Thu Nov 13 19:28:38 1997
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][local][object] */ 



EXTERN_C const IID IID_IAudioMediaStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("f7537560-a3be-11d0-8212-00c04fc32c45")
    IAudioMediaStream : public IMediaStream
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetFormat( 
            /* [optional][out] */ WAVEFORMATEX __RPC_FAR *pWaveFormatCurrent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFormat( 
            /* [in] */ const WAVEFORMATEX __RPC_FAR *lpWaveFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateSample( 
            /* [in] */ IAudioData __RPC_FAR *pAudioData,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IAudioStreamSample __RPC_FAR *__RPC_FAR *ppSample) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAudioMediaStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAudioMediaStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAudioMediaStream __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAudioMediaStream __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMultiMediaStream )( 
            IAudioMediaStream __RPC_FAR * This,
            /* [out] */ IMultiMediaStream __RPC_FAR *__RPC_FAR *ppMultiMediaStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInformation )( 
            IAudioMediaStream __RPC_FAR * This,
            /* [optional][out] */ MSPID __RPC_FAR *pPurposeId,
            /* [optional][out] */ STREAM_TYPE __RPC_FAR *pType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSameFormat )( 
            IAudioMediaStream __RPC_FAR * This,
            /* [in] */ IMediaStream __RPC_FAR *pStreamThatHasDesiredFormat,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AllocateSample )( 
            IAudioMediaStream __RPC_FAR * This,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IStreamSample __RPC_FAR *__RPC_FAR *ppSample);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateSharedSample )( 
            IAudioMediaStream __RPC_FAR * This,
            /* [in] */ IStreamSample __RPC_FAR *pExistingSample,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IStreamSample __RPC_FAR *__RPC_FAR *ppNewSample);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendEndOfStream )( 
            IAudioMediaStream __RPC_FAR * This,
            DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFormat )( 
            IAudioMediaStream __RPC_FAR * This,
            /* [optional][out] */ WAVEFORMATEX __RPC_FAR *pWaveFormatCurrent);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFormat )( 
            IAudioMediaStream __RPC_FAR * This,
            /* [in] */ const WAVEFORMATEX __RPC_FAR *lpWaveFormat);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateSample )( 
            IAudioMediaStream __RPC_FAR * This,
            /* [in] */ IAudioData __RPC_FAR *pAudioData,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IAudioStreamSample __RPC_FAR *__RPC_FAR *ppSample);
        
        END_INTERFACE
    } IAudioMediaStreamVtbl;

    interface IAudioMediaStream
    {
        CONST_VTBL struct IAudioMediaStreamVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAudioMediaStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAudioMediaStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAudioMediaStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAudioMediaStream_GetMultiMediaStream(This,ppMultiMediaStream)	\
    (This)->lpVtbl -> GetMultiMediaStream(This,ppMultiMediaStream)

#define IAudioMediaStream_GetInformation(This,pPurposeId,pType)	\
    (This)->lpVtbl -> GetInformation(This,pPurposeId,pType)

#define IAudioMediaStream_SetSameFormat(This,pStreamThatHasDesiredFormat,dwFlags)	\
    (This)->lpVtbl -> SetSameFormat(This,pStreamThatHasDesiredFormat,dwFlags)

#define IAudioMediaStream_AllocateSample(This,dwFlags,ppSample)	\
    (This)->lpVtbl -> AllocateSample(This,dwFlags,ppSample)

#define IAudioMediaStream_CreateSharedSample(This,pExistingSample,dwFlags,ppNewSample)	\
    (This)->lpVtbl -> CreateSharedSample(This,pExistingSample,dwFlags,ppNewSample)

#define IAudioMediaStream_SendEndOfStream(This,dwFlags)	\
    (This)->lpVtbl -> SendEndOfStream(This,dwFlags)


#define IAudioMediaStream_GetFormat(This,pWaveFormatCurrent)	\
    (This)->lpVtbl -> GetFormat(This,pWaveFormatCurrent)

#define IAudioMediaStream_SetFormat(This,lpWaveFormat)	\
    (This)->lpVtbl -> SetFormat(This,lpWaveFormat)

#define IAudioMediaStream_CreateSample(This,pAudioData,dwFlags,ppSample)	\
    (This)->lpVtbl -> CreateSample(This,pAudioData,dwFlags,ppSample)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAudioMediaStream_GetFormat_Proxy( 
    IAudioMediaStream __RPC_FAR * This,
    /* [optional][out] */ WAVEFORMATEX __RPC_FAR *pWaveFormatCurrent);


void __RPC_STUB IAudioMediaStream_GetFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAudioMediaStream_SetFormat_Proxy( 
    IAudioMediaStream __RPC_FAR * This,
    /* [in] */ const WAVEFORMATEX __RPC_FAR *lpWaveFormat);


void __RPC_STUB IAudioMediaStream_SetFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAudioMediaStream_CreateSample_Proxy( 
    IAudioMediaStream __RPC_FAR * This,
    /* [in] */ IAudioData __RPC_FAR *pAudioData,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IAudioStreamSample __RPC_FAR *__RPC_FAR *ppSample);


void __RPC_STUB IAudioMediaStream_CreateSample_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAudioMediaStream_INTERFACE_DEFINED__ */


#ifndef __IAudioStreamSample_INTERFACE_DEFINED__
#define __IAudioStreamSample_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAudioStreamSample
 * at Thu Nov 13 19:28:38 1997
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][local][object] */ 



EXTERN_C const IID IID_IAudioStreamSample;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("345fee00-aba5-11d0-8212-00c04fc32c45")
    IAudioStreamSample : public IStreamSample
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAudioData( 
            /* [out] */ IAudioData __RPC_FAR *__RPC_FAR *ppAudio) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAudioStreamSampleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAudioStreamSample __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAudioStreamSample __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAudioStreamSample __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMediaStream )( 
            IAudioStreamSample __RPC_FAR * This,
            /* [in] */ IMediaStream __RPC_FAR *__RPC_FAR *ppMediaStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSampleTimes )( 
            IAudioStreamSample __RPC_FAR * This,
            /* [optional][out] */ STREAM_TIME __RPC_FAR *pStartTime,
            /* [optional][out] */ STREAM_TIME __RPC_FAR *pEndTime,
            /* [optional][out] */ STREAM_TIME __RPC_FAR *pCurrentTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSampleTimes )( 
            IAudioStreamSample __RPC_FAR * This,
            /* [optional][in] */ const STREAM_TIME __RPC_FAR *pStartTime,
            /* [optional][in] */ const STREAM_TIME __RPC_FAR *pEndTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Update )( 
            IAudioStreamSample __RPC_FAR * This,
            /* [in] */ DWORD dwFlags,
            /* [optional][in] */ HANDLE hEvent,
            /* [optional][in] */ PAPCFUNC pfnAPC,
            /* [optional][in] */ DWORD dwAPCData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CompletionStatus )( 
            IAudioStreamSample __RPC_FAR * This,
            /* [in] */ DWORD dwFlags,
            /* [optional][in] */ DWORD dwMilliseconds);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAudioData )( 
            IAudioStreamSample __RPC_FAR * This,
            /* [out] */ IAudioData __RPC_FAR *__RPC_FAR *ppAudio);
        
        END_INTERFACE
    } IAudioStreamSampleVtbl;

    interface IAudioStreamSample
    {
        CONST_VTBL struct IAudioStreamSampleVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAudioStreamSample_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAudioStreamSample_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAudioStreamSample_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAudioStreamSample_GetMediaStream(This,ppMediaStream)	\
    (This)->lpVtbl -> GetMediaStream(This,ppMediaStream)

#define IAudioStreamSample_GetSampleTimes(This,pStartTime,pEndTime,pCurrentTime)	\
    (This)->lpVtbl -> GetSampleTimes(This,pStartTime,pEndTime,pCurrentTime)

#define IAudioStreamSample_SetSampleTimes(This,pStartTime,pEndTime)	\
    (This)->lpVtbl -> SetSampleTimes(This,pStartTime,pEndTime)

#define IAudioStreamSample_Update(This,dwFlags,hEvent,pfnAPC,dwAPCData)	\
    (This)->lpVtbl -> Update(This,dwFlags,hEvent,pfnAPC,dwAPCData)

#define IAudioStreamSample_CompletionStatus(This,dwFlags,dwMilliseconds)	\
    (This)->lpVtbl -> CompletionStatus(This,dwFlags,dwMilliseconds)


#define IAudioStreamSample_GetAudioData(This,ppAudio)	\
    (This)->lpVtbl -> GetAudioData(This,ppAudio)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAudioStreamSample_GetAudioData_Proxy( 
    IAudioStreamSample __RPC_FAR * This,
    /* [out] */ IAudioData __RPC_FAR *__RPC_FAR *ppAudio);


void __RPC_STUB IAudioStreamSample_GetAudioData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAudioStreamSample_INTERFACE_DEFINED__ */


#ifndef __IMemoryData_INTERFACE_DEFINED__
#define __IMemoryData_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMemoryData
 * at Thu Nov 13 19:28:38 1997
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][local][object] */ 



EXTERN_C const IID IID_IMemoryData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("327fc560-af60-11d0-8212-00c04fc32c45")
    IMemoryData : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetBuffer( 
            /* [in] */ DWORD cbSize,
            /* [in] */ BYTE __RPC_FAR *pbData,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInfo( 
            /* [out] */ DWORD __RPC_FAR *pdwLength,
            /* [out] */ BYTE __RPC_FAR *__RPC_FAR *ppbData,
            /* [out] */ DWORD __RPC_FAR *pcbActualData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetActual( 
            /* [in] */ DWORD cbDataValid) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMemoryDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMemoryData __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMemoryData __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMemoryData __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetBuffer )( 
            IMemoryData __RPC_FAR * This,
            /* [in] */ DWORD cbSize,
            /* [in] */ BYTE __RPC_FAR *pbData,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IMemoryData __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwLength,
            /* [out] */ BYTE __RPC_FAR *__RPC_FAR *ppbData,
            /* [out] */ DWORD __RPC_FAR *pcbActualData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetActual )( 
            IMemoryData __RPC_FAR * This,
            /* [in] */ DWORD cbDataValid);
        
        END_INTERFACE
    } IMemoryDataVtbl;

    interface IMemoryData
    {
        CONST_VTBL struct IMemoryDataVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMemoryData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMemoryData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMemoryData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMemoryData_SetBuffer(This,cbSize,pbData,dwFlags)	\
    (This)->lpVtbl -> SetBuffer(This,cbSize,pbData,dwFlags)

#define IMemoryData_GetInfo(This,pdwLength,ppbData,pcbActualData)	\
    (This)->lpVtbl -> GetInfo(This,pdwLength,ppbData,pcbActualData)

#define IMemoryData_SetActual(This,cbDataValid)	\
    (This)->lpVtbl -> SetActual(This,cbDataValid)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMemoryData_SetBuffer_Proxy( 
    IMemoryData __RPC_FAR * This,
    /* [in] */ DWORD cbSize,
    /* [in] */ BYTE __RPC_FAR *pbData,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IMemoryData_SetBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemoryData_GetInfo_Proxy( 
    IMemoryData __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwLength,
    /* [out] */ BYTE __RPC_FAR *__RPC_FAR *ppbData,
    /* [out] */ DWORD __RPC_FAR *pcbActualData);


void __RPC_STUB IMemoryData_GetInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMemoryData_SetActual_Proxy( 
    IMemoryData __RPC_FAR * This,
    /* [in] */ DWORD cbDataValid);


void __RPC_STUB IMemoryData_SetActual_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMemoryData_INTERFACE_DEFINED__ */


#ifndef __IAudioData_INTERFACE_DEFINED__
#define __IAudioData_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAudioData
 * at Thu Nov 13 19:28:38 1997
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][local][object] */ 



EXTERN_C const IID IID_IAudioData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("54c719c0-af60-11d0-8212-00c04fc32c45")
    IAudioData : public IMemoryData
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetFormat( 
            /* [optional][out] */ WAVEFORMATEX __RPC_FAR *pWaveFormatCurrent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFormat( 
            /* [in] */ const WAVEFORMATEX __RPC_FAR *lpWaveFormat) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAudioDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAudioData __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAudioData __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAudioData __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetBuffer )( 
            IAudioData __RPC_FAR * This,
            /* [in] */ DWORD cbSize,
            /* [in] */ BYTE __RPC_FAR *pbData,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IAudioData __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwLength,
            /* [out] */ BYTE __RPC_FAR *__RPC_FAR *ppbData,
            /* [out] */ DWORD __RPC_FAR *pcbActualData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetActual )( 
            IAudioData __RPC_FAR * This,
            /* [in] */ DWORD cbDataValid);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFormat )( 
            IAudioData __RPC_FAR * This,
            /* [optional][out] */ WAVEFORMATEX __RPC_FAR *pWaveFormatCurrent);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFormat )( 
            IAudioData __RPC_FAR * This,
            /* [in] */ const WAVEFORMATEX __RPC_FAR *lpWaveFormat);
        
        END_INTERFACE
    } IAudioDataVtbl;

    interface IAudioData
    {
        CONST_VTBL struct IAudioDataVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAudioData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAudioData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAudioData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAudioData_SetBuffer(This,cbSize,pbData,dwFlags)	\
    (This)->lpVtbl -> SetBuffer(This,cbSize,pbData,dwFlags)

#define IAudioData_GetInfo(This,pdwLength,ppbData,pcbActualData)	\
    (This)->lpVtbl -> GetInfo(This,pdwLength,ppbData,pcbActualData)

#define IAudioData_SetActual(This,cbDataValid)	\
    (This)->lpVtbl -> SetActual(This,cbDataValid)


#define IAudioData_GetFormat(This,pWaveFormatCurrent)	\
    (This)->lpVtbl -> GetFormat(This,pWaveFormatCurrent)

#define IAudioData_SetFormat(This,lpWaveFormat)	\
    (This)->lpVtbl -> SetFormat(This,lpWaveFormat)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAudioData_GetFormat_Proxy( 
    IAudioData __RPC_FAR * This,
    /* [optional][out] */ WAVEFORMATEX __RPC_FAR *pWaveFormatCurrent);


void __RPC_STUB IAudioData_GetFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAudioData_SetFormat_Proxy( 
    IAudioData __RPC_FAR * This,
    /* [in] */ const WAVEFORMATEX __RPC_FAR *lpWaveFormat);


void __RPC_STUB IAudioData_SetFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAudioData_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
