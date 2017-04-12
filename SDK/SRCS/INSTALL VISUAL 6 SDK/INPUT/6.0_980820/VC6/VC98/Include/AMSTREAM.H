/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.02.88 */
/* at Thu Nov 13 19:28:37 1997
 */
/* Compiler settings for amstream.idl:
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

#ifndef __amstream_h__
#define __amstream_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDirectShowStream_FWD_DEFINED__
#define __IDirectShowStream_FWD_DEFINED__
typedef interface IDirectShowStream IDirectShowStream;
#endif 	/* __IDirectShowStream_FWD_DEFINED__ */


#ifndef __IAMMultiMediaStream_FWD_DEFINED__
#define __IAMMultiMediaStream_FWD_DEFINED__
typedef interface IAMMultiMediaStream IAMMultiMediaStream;
#endif 	/* __IAMMultiMediaStream_FWD_DEFINED__ */


#ifndef __IAMMediaStream_FWD_DEFINED__
#define __IAMMediaStream_FWD_DEFINED__
typedef interface IAMMediaStream IAMMediaStream;
#endif 	/* __IAMMediaStream_FWD_DEFINED__ */


#ifndef __IMediaStreamFilter_FWD_DEFINED__
#define __IMediaStreamFilter_FWD_DEFINED__
typedef interface IMediaStreamFilter IMediaStreamFilter;
#endif 	/* __IMediaStreamFilter_FWD_DEFINED__ */


#ifndef __IDirectDrawMediaSampleAllocator_FWD_DEFINED__
#define __IDirectDrawMediaSampleAllocator_FWD_DEFINED__
typedef interface IDirectDrawMediaSampleAllocator IDirectDrawMediaSampleAllocator;
#endif 	/* __IDirectDrawMediaSampleAllocator_FWD_DEFINED__ */


#ifndef __IDirectDrawMediaSample_FWD_DEFINED__
#define __IDirectDrawMediaSample_FWD_DEFINED__
typedef interface IDirectDrawMediaSample IDirectDrawMediaSample;
#endif 	/* __IDirectDrawMediaSample_FWD_DEFINED__ */


#ifndef __IAMMediaTypeStream_FWD_DEFINED__
#define __IAMMediaTypeStream_FWD_DEFINED__
typedef interface IAMMediaTypeStream IAMMediaTypeStream;
#endif 	/* __IAMMediaTypeStream_FWD_DEFINED__ */


#ifndef __IAMMediaTypeSample_FWD_DEFINED__
#define __IAMMediaTypeSample_FWD_DEFINED__
typedef interface IAMMediaTypeSample IAMMediaTypeSample;
#endif 	/* __IAMMediaTypeSample_FWD_DEFINED__ */


#ifndef __AMMultiMediaStream_FWD_DEFINED__
#define __AMMultiMediaStream_FWD_DEFINED__

#ifdef __cplusplus
typedef class AMMultiMediaStream AMMultiMediaStream;
#else
typedef struct AMMultiMediaStream AMMultiMediaStream;
#endif /* __cplusplus */

#endif 	/* __AMMultiMediaStream_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "mmstream.h"
#include "strmif.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_amstream_0000
 * at Thu Nov 13 19:28:37 1997
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


#include <ddraw.h>
#include <mmstream.h>
#include <ddstream.h>
#include <austream.h>








enum __MIDL___MIDL_itf_amstream_0000_0001
    {	AMMSF_NOGRAPHTHREAD	= 0x1
    };

enum __MIDL___MIDL_itf_amstream_0000_0002
    {	AMMSF_ADDDEFAULTRENDERER	= 0x1,
	AMMSF_CREATEPEER	= 0x2
    };

enum __MIDL___MIDL_itf_amstream_0000_0003
    {	AMMSF_RENDERTYPEMASK	= 0x3,
	AMMSF_RENDERTOEXISTING	= 0,
	AMMSF_RENDERALLSTREAMS	= 0x1,
	AMMSF_NORENDER	= 0x2,
	AMMSF_NOCLOCK	= 0x4,
	AMMSF_RUN	= 0x8
    };
typedef /* [public][public][public][public][public][v1_enum] */ 
enum __MIDL___MIDL_itf_amstream_0000_0004
    {	Disabled	= 0,
	ReadData	= 1,
	RenderData	= 2
    }	OUTPUT_STATE;



extern RPC_IF_HANDLE __MIDL_itf_amstream_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_amstream_0000_v0_0_s_ifspec;

#ifndef __IDirectShowStream_INTERFACE_DEFINED__
#define __IDirectShowStream_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDirectShowStream
 * at Thu Nov 13 19:28:37 1997
 * using MIDL 3.02.88
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IDirectShowStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("7DB01C96-C0C3-11d0-8FF1-00C04FD9189D")
    IDirectShowStream : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Video( 
            /* [retval][out] */ OUTPUT_STATE __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Video( 
            /* [in] */ OUTPUT_STATE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Audio( 
            /* [retval][out] */ OUTPUT_STATE __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Audio( 
            /* [in] */ OUTPUT_STATE newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDirectShowStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDirectShowStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDirectShowStream __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDirectShowStream __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDirectShowStream __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDirectShowStream __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDirectShowStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDirectShowStream __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FileName )( 
            IDirectShowStream __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FileName )( 
            IDirectShowStream __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Video )( 
            IDirectShowStream __RPC_FAR * This,
            /* [retval][out] */ OUTPUT_STATE __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Video )( 
            IDirectShowStream __RPC_FAR * This,
            /* [in] */ OUTPUT_STATE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Audio )( 
            IDirectShowStream __RPC_FAR * This,
            /* [retval][out] */ OUTPUT_STATE __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Audio )( 
            IDirectShowStream __RPC_FAR * This,
            /* [in] */ OUTPUT_STATE newVal);
        
        END_INTERFACE
    } IDirectShowStreamVtbl;

    interface IDirectShowStream
    {
        CONST_VTBL struct IDirectShowStreamVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDirectShowStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDirectShowStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDirectShowStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDirectShowStream_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDirectShowStream_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDirectShowStream_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDirectShowStream_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDirectShowStream_get_FileName(This,pVal)	\
    (This)->lpVtbl -> get_FileName(This,pVal)

#define IDirectShowStream_put_FileName(This,newVal)	\
    (This)->lpVtbl -> put_FileName(This,newVal)

#define IDirectShowStream_get_Video(This,pVal)	\
    (This)->lpVtbl -> get_Video(This,pVal)

#define IDirectShowStream_put_Video(This,newVal)	\
    (This)->lpVtbl -> put_Video(This,newVal)

#define IDirectShowStream_get_Audio(This,pVal)	\
    (This)->lpVtbl -> get_Audio(This,pVal)

#define IDirectShowStream_put_Audio(This,newVal)	\
    (This)->lpVtbl -> put_Audio(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDirectShowStream_get_FileName_Proxy( 
    IDirectShowStream __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IDirectShowStream_get_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDirectShowStream_put_FileName_Proxy( 
    IDirectShowStream __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IDirectShowStream_put_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDirectShowStream_get_Video_Proxy( 
    IDirectShowStream __RPC_FAR * This,
    /* [retval][out] */ OUTPUT_STATE __RPC_FAR *pVal);


void __RPC_STUB IDirectShowStream_get_Video_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDirectShowStream_put_Video_Proxy( 
    IDirectShowStream __RPC_FAR * This,
    /* [in] */ OUTPUT_STATE newVal);


void __RPC_STUB IDirectShowStream_put_Video_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDirectShowStream_get_Audio_Proxy( 
    IDirectShowStream __RPC_FAR * This,
    /* [retval][out] */ OUTPUT_STATE __RPC_FAR *pVal);


void __RPC_STUB IDirectShowStream_get_Audio_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDirectShowStream_put_Audio_Proxy( 
    IDirectShowStream __RPC_FAR * This,
    /* [in] */ OUTPUT_STATE newVal);


void __RPC_STUB IDirectShowStream_put_Audio_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDirectShowStream_INTERFACE_DEFINED__ */


#ifndef __IAMMultiMediaStream_INTERFACE_DEFINED__
#define __IAMMultiMediaStream_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAMMultiMediaStream
 * at Thu Nov 13 19:28:37 1997
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IAMMultiMediaStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("BEBE595C-9A6F-11d0-8FDE-00C04FD9189D")
    IAMMultiMediaStream : public IMultiMediaStream
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ STREAM_TYPE StreamType,
            /* [in] */ DWORD dwFlags,
            /* [optional][in] */ IGraphBuilder __RPC_FAR *pFilterGraph) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFilterGraph( 
            /* [out] */ IGraphBuilder __RPC_FAR *__RPC_FAR *ppGraphBuilder) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFilter( 
            /* [out] */ IMediaStreamFilter __RPC_FAR *__RPC_FAR *ppFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddMediaStream( 
            /* [optional][in] */ IUnknown __RPC_FAR *pStreamObject,
            /* [optional][in] */ const MSPID __RPC_FAR *PurposeId,
            /* [in] */ DWORD dwFlags,
            /* [optional][out] */ IMediaStream __RPC_FAR *__RPC_FAR *ppNewStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OpenFile( 
            /* [in] */ LPCWSTR pszFileName,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OpenMoniker( 
            /* [in] */ IBindCtx __RPC_FAR *pCtx,
            /* [in] */ IMoniker __RPC_FAR *pMoniker,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Render( 
            /* [in] */ DWORD dwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMMultiMediaStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAMMultiMediaStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAMMultiMediaStream __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAMMultiMediaStream __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInformation )( 
            IAMMultiMediaStream __RPC_FAR * This,
            /* [optional][out] */ DWORD __RPC_FAR *pdwFlags,
            /* [optional][out] */ STREAM_TYPE __RPC_FAR *pStreamType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMediaStream )( 
            IAMMultiMediaStream __RPC_FAR * This,
            /* [in] */ REFMSPID idPurpose,
            /* [out] */ IMediaStream __RPC_FAR *__RPC_FAR *ppMediaStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumMediaStreams )( 
            IAMMultiMediaStream __RPC_FAR * This,
            /* [in] */ long Index,
            /* [out] */ IMediaStream __RPC_FAR *__RPC_FAR *ppMediaStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetState )( 
            IAMMultiMediaStream __RPC_FAR * This,
            /* [out] */ STREAM_STATE __RPC_FAR *pCurrentState);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetState )( 
            IAMMultiMediaStream __RPC_FAR * This,
            /* [in] */ STREAM_STATE NewState);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTime )( 
            IAMMultiMediaStream __RPC_FAR * This,
            /* [out] */ STREAM_TIME __RPC_FAR *pCurrentTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDuration )( 
            IAMMultiMediaStream __RPC_FAR * This,
            /* [out] */ STREAM_TIME __RPC_FAR *pDuration);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Seek )( 
            IAMMultiMediaStream __RPC_FAR * This,
            /* [in] */ STREAM_TIME SeekTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEndOfStreamEventHandle )( 
            IAMMultiMediaStream __RPC_FAR * This,
            /* [out] */ HANDLE __RPC_FAR *phEOS);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IAMMultiMediaStream __RPC_FAR * This,
            /* [in] */ STREAM_TYPE StreamType,
            /* [in] */ DWORD dwFlags,
            /* [optional][in] */ IGraphBuilder __RPC_FAR *pFilterGraph);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFilterGraph )( 
            IAMMultiMediaStream __RPC_FAR * This,
            /* [out] */ IGraphBuilder __RPC_FAR *__RPC_FAR *ppGraphBuilder);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFilter )( 
            IAMMultiMediaStream __RPC_FAR * This,
            /* [out] */ IMediaStreamFilter __RPC_FAR *__RPC_FAR *ppFilter);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddMediaStream )( 
            IAMMultiMediaStream __RPC_FAR * This,
            /* [optional][in] */ IUnknown __RPC_FAR *pStreamObject,
            /* [optional][in] */ const MSPID __RPC_FAR *PurposeId,
            /* [in] */ DWORD dwFlags,
            /* [optional][out] */ IMediaStream __RPC_FAR *__RPC_FAR *ppNewStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenFile )( 
            IAMMultiMediaStream __RPC_FAR * This,
            /* [in] */ LPCWSTR pszFileName,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenMoniker )( 
            IAMMultiMediaStream __RPC_FAR * This,
            /* [in] */ IBindCtx __RPC_FAR *pCtx,
            /* [in] */ IMoniker __RPC_FAR *pMoniker,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Render )( 
            IAMMultiMediaStream __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        END_INTERFACE
    } IAMMultiMediaStreamVtbl;

    interface IAMMultiMediaStream
    {
        CONST_VTBL struct IAMMultiMediaStreamVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMMultiMediaStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMMultiMediaStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMMultiMediaStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMMultiMediaStream_GetInformation(This,pdwFlags,pStreamType)	\
    (This)->lpVtbl -> GetInformation(This,pdwFlags,pStreamType)

#define IAMMultiMediaStream_GetMediaStream(This,idPurpose,ppMediaStream)	\
    (This)->lpVtbl -> GetMediaStream(This,idPurpose,ppMediaStream)

#define IAMMultiMediaStream_EnumMediaStreams(This,Index,ppMediaStream)	\
    (This)->lpVtbl -> EnumMediaStreams(This,Index,ppMediaStream)

#define IAMMultiMediaStream_GetState(This,pCurrentState)	\
    (This)->lpVtbl -> GetState(This,pCurrentState)

#define IAMMultiMediaStream_SetState(This,NewState)	\
    (This)->lpVtbl -> SetState(This,NewState)

#define IAMMultiMediaStream_GetTime(This,pCurrentTime)	\
    (This)->lpVtbl -> GetTime(This,pCurrentTime)

#define IAMMultiMediaStream_GetDuration(This,pDuration)	\
    (This)->lpVtbl -> GetDuration(This,pDuration)

#define IAMMultiMediaStream_Seek(This,SeekTime)	\
    (This)->lpVtbl -> Seek(This,SeekTime)

#define IAMMultiMediaStream_GetEndOfStreamEventHandle(This,phEOS)	\
    (This)->lpVtbl -> GetEndOfStreamEventHandle(This,phEOS)


#define IAMMultiMediaStream_Initialize(This,StreamType,dwFlags,pFilterGraph)	\
    (This)->lpVtbl -> Initialize(This,StreamType,dwFlags,pFilterGraph)

#define IAMMultiMediaStream_GetFilterGraph(This,ppGraphBuilder)	\
    (This)->lpVtbl -> GetFilterGraph(This,ppGraphBuilder)

#define IAMMultiMediaStream_GetFilter(This,ppFilter)	\
    (This)->lpVtbl -> GetFilter(This,ppFilter)

#define IAMMultiMediaStream_AddMediaStream(This,pStreamObject,PurposeId,dwFlags,ppNewStream)	\
    (This)->lpVtbl -> AddMediaStream(This,pStreamObject,PurposeId,dwFlags,ppNewStream)

#define IAMMultiMediaStream_OpenFile(This,pszFileName,dwFlags)	\
    (This)->lpVtbl -> OpenFile(This,pszFileName,dwFlags)

#define IAMMultiMediaStream_OpenMoniker(This,pCtx,pMoniker,dwFlags)	\
    (This)->lpVtbl -> OpenMoniker(This,pCtx,pMoniker,dwFlags)

#define IAMMultiMediaStream_Render(This,dwFlags)	\
    (This)->lpVtbl -> Render(This,dwFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMMultiMediaStream_Initialize_Proxy( 
    IAMMultiMediaStream __RPC_FAR * This,
    /* [in] */ STREAM_TYPE StreamType,
    /* [in] */ DWORD dwFlags,
    /* [optional][in] */ IGraphBuilder __RPC_FAR *pFilterGraph);


void __RPC_STUB IAMMultiMediaStream_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMultiMediaStream_GetFilterGraph_Proxy( 
    IAMMultiMediaStream __RPC_FAR * This,
    /* [out] */ IGraphBuilder __RPC_FAR *__RPC_FAR *ppGraphBuilder);


void __RPC_STUB IAMMultiMediaStream_GetFilterGraph_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMultiMediaStream_GetFilter_Proxy( 
    IAMMultiMediaStream __RPC_FAR * This,
    /* [out] */ IMediaStreamFilter __RPC_FAR *__RPC_FAR *ppFilter);


void __RPC_STUB IAMMultiMediaStream_GetFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMultiMediaStream_AddMediaStream_Proxy( 
    IAMMultiMediaStream __RPC_FAR * This,
    /* [optional][in] */ IUnknown __RPC_FAR *pStreamObject,
    /* [optional][in] */ const MSPID __RPC_FAR *PurposeId,
    /* [in] */ DWORD dwFlags,
    /* [optional][out] */ IMediaStream __RPC_FAR *__RPC_FAR *ppNewStream);


void __RPC_STUB IAMMultiMediaStream_AddMediaStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMultiMediaStream_OpenFile_Proxy( 
    IAMMultiMediaStream __RPC_FAR * This,
    /* [in] */ LPCWSTR pszFileName,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IAMMultiMediaStream_OpenFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMultiMediaStream_OpenMoniker_Proxy( 
    IAMMultiMediaStream __RPC_FAR * This,
    /* [in] */ IBindCtx __RPC_FAR *pCtx,
    /* [in] */ IMoniker __RPC_FAR *pMoniker,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IAMMultiMediaStream_OpenMoniker_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMultiMediaStream_Render_Proxy( 
    IAMMultiMediaStream __RPC_FAR * This,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IAMMultiMediaStream_Render_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMMultiMediaStream_INTERFACE_DEFINED__ */


#ifndef __IAMMediaStream_INTERFACE_DEFINED__
#define __IAMMediaStream_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAMMediaStream
 * at Thu Nov 13 19:28:37 1997
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IAMMediaStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("BEBE595D-9A6F-11d0-8FDE-00C04FD9189D")
    IAMMediaStream : public IMediaStream
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [optional][in] */ IUnknown __RPC_FAR *pSourceObject,
            /* [in] */ DWORD dwFlags,
            /* [in] */ REFMSPID PurposeId,
            /* [in] */ const STREAM_TYPE StreamType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetState( 
            /* [in] */ FILTER_STATE State) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE JoinAMMultiMediaStream( 
            /* [in] */ IAMMultiMediaStream __RPC_FAR *pAMMultiMediaStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE JoinFilter( 
            /* [in] */ IMediaStreamFilter __RPC_FAR *pMediaStreamFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE JoinFilterGraph( 
            /* [in] */ IFilterGraph __RPC_FAR *pFilterGraph) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMMediaStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAMMediaStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAMMediaStream __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAMMediaStream __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMultiMediaStream )( 
            IAMMediaStream __RPC_FAR * This,
            /* [out] */ IMultiMediaStream __RPC_FAR *__RPC_FAR *ppMultiMediaStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInformation )( 
            IAMMediaStream __RPC_FAR * This,
            /* [optional][out] */ MSPID __RPC_FAR *pPurposeId,
            /* [optional][out] */ STREAM_TYPE __RPC_FAR *pType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSameFormat )( 
            IAMMediaStream __RPC_FAR * This,
            /* [in] */ IMediaStream __RPC_FAR *pStreamThatHasDesiredFormat,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AllocateSample )( 
            IAMMediaStream __RPC_FAR * This,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IStreamSample __RPC_FAR *__RPC_FAR *ppSample);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateSharedSample )( 
            IAMMediaStream __RPC_FAR * This,
            /* [in] */ IStreamSample __RPC_FAR *pExistingSample,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IStreamSample __RPC_FAR *__RPC_FAR *ppNewSample);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendEndOfStream )( 
            IAMMediaStream __RPC_FAR * This,
            DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IAMMediaStream __RPC_FAR * This,
            /* [optional][in] */ IUnknown __RPC_FAR *pSourceObject,
            /* [in] */ DWORD dwFlags,
            /* [in] */ REFMSPID PurposeId,
            /* [in] */ const STREAM_TYPE StreamType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetState )( 
            IAMMediaStream __RPC_FAR * This,
            /* [in] */ FILTER_STATE State);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *JoinAMMultiMediaStream )( 
            IAMMediaStream __RPC_FAR * This,
            /* [in] */ IAMMultiMediaStream __RPC_FAR *pAMMultiMediaStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *JoinFilter )( 
            IAMMediaStream __RPC_FAR * This,
            /* [in] */ IMediaStreamFilter __RPC_FAR *pMediaStreamFilter);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *JoinFilterGraph )( 
            IAMMediaStream __RPC_FAR * This,
            /* [in] */ IFilterGraph __RPC_FAR *pFilterGraph);
        
        END_INTERFACE
    } IAMMediaStreamVtbl;

    interface IAMMediaStream
    {
        CONST_VTBL struct IAMMediaStreamVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMMediaStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMMediaStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMMediaStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMMediaStream_GetMultiMediaStream(This,ppMultiMediaStream)	\
    (This)->lpVtbl -> GetMultiMediaStream(This,ppMultiMediaStream)

#define IAMMediaStream_GetInformation(This,pPurposeId,pType)	\
    (This)->lpVtbl -> GetInformation(This,pPurposeId,pType)

#define IAMMediaStream_SetSameFormat(This,pStreamThatHasDesiredFormat,dwFlags)	\
    (This)->lpVtbl -> SetSameFormat(This,pStreamThatHasDesiredFormat,dwFlags)

#define IAMMediaStream_AllocateSample(This,dwFlags,ppSample)	\
    (This)->lpVtbl -> AllocateSample(This,dwFlags,ppSample)

#define IAMMediaStream_CreateSharedSample(This,pExistingSample,dwFlags,ppNewSample)	\
    (This)->lpVtbl -> CreateSharedSample(This,pExistingSample,dwFlags,ppNewSample)

#define IAMMediaStream_SendEndOfStream(This,dwFlags)	\
    (This)->lpVtbl -> SendEndOfStream(This,dwFlags)


#define IAMMediaStream_Initialize(This,pSourceObject,dwFlags,PurposeId,StreamType)	\
    (This)->lpVtbl -> Initialize(This,pSourceObject,dwFlags,PurposeId,StreamType)

#define IAMMediaStream_SetState(This,State)	\
    (This)->lpVtbl -> SetState(This,State)

#define IAMMediaStream_JoinAMMultiMediaStream(This,pAMMultiMediaStream)	\
    (This)->lpVtbl -> JoinAMMultiMediaStream(This,pAMMultiMediaStream)

#define IAMMediaStream_JoinFilter(This,pMediaStreamFilter)	\
    (This)->lpVtbl -> JoinFilter(This,pMediaStreamFilter)

#define IAMMediaStream_JoinFilterGraph(This,pFilterGraph)	\
    (This)->lpVtbl -> JoinFilterGraph(This,pFilterGraph)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMMediaStream_Initialize_Proxy( 
    IAMMediaStream __RPC_FAR * This,
    /* [optional][in] */ IUnknown __RPC_FAR *pSourceObject,
    /* [in] */ DWORD dwFlags,
    /* [in] */ REFMSPID PurposeId,
    /* [in] */ const STREAM_TYPE StreamType);


void __RPC_STUB IAMMediaStream_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMediaStream_SetState_Proxy( 
    IAMMediaStream __RPC_FAR * This,
    /* [in] */ FILTER_STATE State);


void __RPC_STUB IAMMediaStream_SetState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMediaStream_JoinAMMultiMediaStream_Proxy( 
    IAMMediaStream __RPC_FAR * This,
    /* [in] */ IAMMultiMediaStream __RPC_FAR *pAMMultiMediaStream);


void __RPC_STUB IAMMediaStream_JoinAMMultiMediaStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMediaStream_JoinFilter_Proxy( 
    IAMMediaStream __RPC_FAR * This,
    /* [in] */ IMediaStreamFilter __RPC_FAR *pMediaStreamFilter);


void __RPC_STUB IAMMediaStream_JoinFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMediaStream_JoinFilterGraph_Proxy( 
    IAMMediaStream __RPC_FAR * This,
    /* [in] */ IFilterGraph __RPC_FAR *pFilterGraph);


void __RPC_STUB IAMMediaStream_JoinFilterGraph_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMMediaStream_INTERFACE_DEFINED__ */


#ifndef __IMediaStreamFilter_INTERFACE_DEFINED__
#define __IMediaStreamFilter_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMediaStreamFilter
 * at Thu Nov 13 19:28:37 1997
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][local][object] */ 



EXTERN_C const IID IID_IMediaStreamFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("BEBE595E-9A6F-11d0-8FDE-00C04FD9189D")
    IMediaStreamFilter : public IBaseFilter
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AddMediaStream( 
            /* [in] */ IAMMediaStream __RPC_FAR *pAMMediaStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMediaStream( 
            /* [in] */ REFMSPID idPurpose,
            /* [out] */ IMediaStream __RPC_FAR *__RPC_FAR *ppMediaStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumMediaStreams( 
            /* [in] */ long Index,
            /* [out] */ IMediaStream __RPC_FAR *__RPC_FAR *ppMediaStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SupportSeeking( 
            /* [in] */ BOOL bRenderer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReferenceTimeToStreamTime( 
            /* [out][in] */ REFERENCE_TIME __RPC_FAR *pTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentStreamTime( 
            /* [out] */ REFERENCE_TIME __RPC_FAR *pCurrentStreamTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WaitUntil( 
            /* [in] */ REFERENCE_TIME WaitStreamTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Flush( 
            /* [in] */ BOOL bCancelEOS) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EndOfStream( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMediaStreamFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMediaStreamFilter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMediaStreamFilter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMediaStreamFilter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetClassID )( 
            IMediaStreamFilter __RPC_FAR * This,
            /* [out] */ CLSID __RPC_FAR *pClassID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IMediaStreamFilter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pause )( 
            IMediaStreamFilter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Run )( 
            IMediaStreamFilter __RPC_FAR * This,
            REFERENCE_TIME tStart);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetState )( 
            IMediaStreamFilter __RPC_FAR * This,
            /* [in] */ DWORD dwMilliSecsTimeout,
            /* [out] */ FILTER_STATE __RPC_FAR *State);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSyncSource )( 
            IMediaStreamFilter __RPC_FAR * This,
            /* [in] */ IReferenceClock __RPC_FAR *pClock);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSyncSource )( 
            IMediaStreamFilter __RPC_FAR * This,
            /* [out] */ IReferenceClock __RPC_FAR *__RPC_FAR *pClock);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumPins )( 
            IMediaStreamFilter __RPC_FAR * This,
            /* [out] */ IEnumPins __RPC_FAR *__RPC_FAR *ppEnum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindPin )( 
            IMediaStreamFilter __RPC_FAR * This,
            /* [string][in] */ LPCWSTR Id,
            /* [out] */ IPin __RPC_FAR *__RPC_FAR *ppPin);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryFilterInfo )( 
            IMediaStreamFilter __RPC_FAR * This,
            /* [out] */ FILTER_INFO __RPC_FAR *pInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *JoinFilterGraph )( 
            IMediaStreamFilter __RPC_FAR * This,
            /* [in] */ IFilterGraph __RPC_FAR *pGraph,
            /* [string][in] */ LPCWSTR pName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryVendorInfo )( 
            IMediaStreamFilter __RPC_FAR * This,
            /* [string][out] */ LPWSTR __RPC_FAR *pVendorInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddMediaStream )( 
            IMediaStreamFilter __RPC_FAR * This,
            /* [in] */ IAMMediaStream __RPC_FAR *pAMMediaStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMediaStream )( 
            IMediaStreamFilter __RPC_FAR * This,
            /* [in] */ REFMSPID idPurpose,
            /* [out] */ IMediaStream __RPC_FAR *__RPC_FAR *ppMediaStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumMediaStreams )( 
            IMediaStreamFilter __RPC_FAR * This,
            /* [in] */ long Index,
            /* [out] */ IMediaStream __RPC_FAR *__RPC_FAR *ppMediaStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SupportSeeking )( 
            IMediaStreamFilter __RPC_FAR * This,
            /* [in] */ BOOL bRenderer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReferenceTimeToStreamTime )( 
            IMediaStreamFilter __RPC_FAR * This,
            /* [out][in] */ REFERENCE_TIME __RPC_FAR *pTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCurrentStreamTime )( 
            IMediaStreamFilter __RPC_FAR * This,
            /* [out] */ REFERENCE_TIME __RPC_FAR *pCurrentStreamTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitUntil )( 
            IMediaStreamFilter __RPC_FAR * This,
            /* [in] */ REFERENCE_TIME WaitStreamTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Flush )( 
            IMediaStreamFilter __RPC_FAR * This,
            /* [in] */ BOOL bCancelEOS);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EndOfStream )( 
            IMediaStreamFilter __RPC_FAR * This);
        
        END_INTERFACE
    } IMediaStreamFilterVtbl;

    interface IMediaStreamFilter
    {
        CONST_VTBL struct IMediaStreamFilterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaStreamFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaStreamFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaStreamFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaStreamFilter_GetClassID(This,pClassID)	\
    (This)->lpVtbl -> GetClassID(This,pClassID)


#define IMediaStreamFilter_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IMediaStreamFilter_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IMediaStreamFilter_Run(This,tStart)	\
    (This)->lpVtbl -> Run(This,tStart)

#define IMediaStreamFilter_GetState(This,dwMilliSecsTimeout,State)	\
    (This)->lpVtbl -> GetState(This,dwMilliSecsTimeout,State)

#define IMediaStreamFilter_SetSyncSource(This,pClock)	\
    (This)->lpVtbl -> SetSyncSource(This,pClock)

#define IMediaStreamFilter_GetSyncSource(This,pClock)	\
    (This)->lpVtbl -> GetSyncSource(This,pClock)


#define IMediaStreamFilter_EnumPins(This,ppEnum)	\
    (This)->lpVtbl -> EnumPins(This,ppEnum)

#define IMediaStreamFilter_FindPin(This,Id,ppPin)	\
    (This)->lpVtbl -> FindPin(This,Id,ppPin)

#define IMediaStreamFilter_QueryFilterInfo(This,pInfo)	\
    (This)->lpVtbl -> QueryFilterInfo(This,pInfo)

#define IMediaStreamFilter_JoinFilterGraph(This,pGraph,pName)	\
    (This)->lpVtbl -> JoinFilterGraph(This,pGraph,pName)

#define IMediaStreamFilter_QueryVendorInfo(This,pVendorInfo)	\
    (This)->lpVtbl -> QueryVendorInfo(This,pVendorInfo)


#define IMediaStreamFilter_AddMediaStream(This,pAMMediaStream)	\
    (This)->lpVtbl -> AddMediaStream(This,pAMMediaStream)

#define IMediaStreamFilter_GetMediaStream(This,idPurpose,ppMediaStream)	\
    (This)->lpVtbl -> GetMediaStream(This,idPurpose,ppMediaStream)

#define IMediaStreamFilter_EnumMediaStreams(This,Index,ppMediaStream)	\
    (This)->lpVtbl -> EnumMediaStreams(This,Index,ppMediaStream)

#define IMediaStreamFilter_SupportSeeking(This,bRenderer)	\
    (This)->lpVtbl -> SupportSeeking(This,bRenderer)

#define IMediaStreamFilter_ReferenceTimeToStreamTime(This,pTime)	\
    (This)->lpVtbl -> ReferenceTimeToStreamTime(This,pTime)

#define IMediaStreamFilter_GetCurrentStreamTime(This,pCurrentStreamTime)	\
    (This)->lpVtbl -> GetCurrentStreamTime(This,pCurrentStreamTime)

#define IMediaStreamFilter_WaitUntil(This,WaitStreamTime)	\
    (This)->lpVtbl -> WaitUntil(This,WaitStreamTime)

#define IMediaStreamFilter_Flush(This,bCancelEOS)	\
    (This)->lpVtbl -> Flush(This,bCancelEOS)

#define IMediaStreamFilter_EndOfStream(This)	\
    (This)->lpVtbl -> EndOfStream(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMediaStreamFilter_AddMediaStream_Proxy( 
    IMediaStreamFilter __RPC_FAR * This,
    /* [in] */ IAMMediaStream __RPC_FAR *pAMMediaStream);


void __RPC_STUB IMediaStreamFilter_AddMediaStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaStreamFilter_GetMediaStream_Proxy( 
    IMediaStreamFilter __RPC_FAR * This,
    /* [in] */ REFMSPID idPurpose,
    /* [out] */ IMediaStream __RPC_FAR *__RPC_FAR *ppMediaStream);


void __RPC_STUB IMediaStreamFilter_GetMediaStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaStreamFilter_EnumMediaStreams_Proxy( 
    IMediaStreamFilter __RPC_FAR * This,
    /* [in] */ long Index,
    /* [out] */ IMediaStream __RPC_FAR *__RPC_FAR *ppMediaStream);


void __RPC_STUB IMediaStreamFilter_EnumMediaStreams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaStreamFilter_SupportSeeking_Proxy( 
    IMediaStreamFilter __RPC_FAR * This,
    /* [in] */ BOOL bRenderer);


void __RPC_STUB IMediaStreamFilter_SupportSeeking_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaStreamFilter_ReferenceTimeToStreamTime_Proxy( 
    IMediaStreamFilter __RPC_FAR * This,
    /* [out][in] */ REFERENCE_TIME __RPC_FAR *pTime);


void __RPC_STUB IMediaStreamFilter_ReferenceTimeToStreamTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaStreamFilter_GetCurrentStreamTime_Proxy( 
    IMediaStreamFilter __RPC_FAR * This,
    /* [out] */ REFERENCE_TIME __RPC_FAR *pCurrentStreamTime);


void __RPC_STUB IMediaStreamFilter_GetCurrentStreamTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaStreamFilter_WaitUntil_Proxy( 
    IMediaStreamFilter __RPC_FAR * This,
    /* [in] */ REFERENCE_TIME WaitStreamTime);


void __RPC_STUB IMediaStreamFilter_WaitUntil_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaStreamFilter_Flush_Proxy( 
    IMediaStreamFilter __RPC_FAR * This,
    /* [in] */ BOOL bCancelEOS);


void __RPC_STUB IMediaStreamFilter_Flush_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaStreamFilter_EndOfStream_Proxy( 
    IMediaStreamFilter __RPC_FAR * This);


void __RPC_STUB IMediaStreamFilter_EndOfStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMediaStreamFilter_INTERFACE_DEFINED__ */


#ifndef __IDirectDrawMediaSampleAllocator_INTERFACE_DEFINED__
#define __IDirectDrawMediaSampleAllocator_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDirectDrawMediaSampleAllocator
 * at Thu Nov 13 19:28:37 1997
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][local][object] */ 



EXTERN_C const IID IID_IDirectDrawMediaSampleAllocator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("AB6B4AFC-F6E4-11d0-900D-00C04FD9189D")
    IDirectDrawMediaSampleAllocator : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDirectDraw( 
            IDirectDraw __RPC_FAR *__RPC_FAR *ppDirectDraw) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDirectDrawMediaSampleAllocatorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDirectDrawMediaSampleAllocator __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDirectDrawMediaSampleAllocator __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDirectDrawMediaSampleAllocator __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDirectDraw )( 
            IDirectDrawMediaSampleAllocator __RPC_FAR * This,
            IDirectDraw __RPC_FAR *__RPC_FAR *ppDirectDraw);
        
        END_INTERFACE
    } IDirectDrawMediaSampleAllocatorVtbl;

    interface IDirectDrawMediaSampleAllocator
    {
        CONST_VTBL struct IDirectDrawMediaSampleAllocatorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDirectDrawMediaSampleAllocator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDirectDrawMediaSampleAllocator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDirectDrawMediaSampleAllocator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDirectDrawMediaSampleAllocator_GetDirectDraw(This,ppDirectDraw)	\
    (This)->lpVtbl -> GetDirectDraw(This,ppDirectDraw)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDirectDrawMediaSampleAllocator_GetDirectDraw_Proxy( 
    IDirectDrawMediaSampleAllocator __RPC_FAR * This,
    IDirectDraw __RPC_FAR *__RPC_FAR *ppDirectDraw);


void __RPC_STUB IDirectDrawMediaSampleAllocator_GetDirectDraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDirectDrawMediaSampleAllocator_INTERFACE_DEFINED__ */


#ifndef __IDirectDrawMediaSample_INTERFACE_DEFINED__
#define __IDirectDrawMediaSample_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDirectDrawMediaSample
 * at Thu Nov 13 19:28:37 1997
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][local][object] */ 



EXTERN_C const IID IID_IDirectDrawMediaSample;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("AB6B4AFE-F6E4-11d0-900D-00C04FD9189D")
    IDirectDrawMediaSample : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetSurfaceAndReleaseLock( 
            /* [out] */ IDirectDrawSurface __RPC_FAR *__RPC_FAR *ppDirectDrawSurface,
            /* [out] */ RECT __RPC_FAR *pRect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LockMediaSamplePointer( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDirectDrawMediaSampleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDirectDrawMediaSample __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDirectDrawMediaSample __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDirectDrawMediaSample __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSurfaceAndReleaseLock )( 
            IDirectDrawMediaSample __RPC_FAR * This,
            /* [out] */ IDirectDrawSurface __RPC_FAR *__RPC_FAR *ppDirectDrawSurface,
            /* [out] */ RECT __RPC_FAR *pRect);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LockMediaSamplePointer )( 
            IDirectDrawMediaSample __RPC_FAR * This);
        
        END_INTERFACE
    } IDirectDrawMediaSampleVtbl;

    interface IDirectDrawMediaSample
    {
        CONST_VTBL struct IDirectDrawMediaSampleVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDirectDrawMediaSample_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDirectDrawMediaSample_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDirectDrawMediaSample_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDirectDrawMediaSample_GetSurfaceAndReleaseLock(This,ppDirectDrawSurface,pRect)	\
    (This)->lpVtbl -> GetSurfaceAndReleaseLock(This,ppDirectDrawSurface,pRect)

#define IDirectDrawMediaSample_LockMediaSamplePointer(This)	\
    (This)->lpVtbl -> LockMediaSamplePointer(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDirectDrawMediaSample_GetSurfaceAndReleaseLock_Proxy( 
    IDirectDrawMediaSample __RPC_FAR * This,
    /* [out] */ IDirectDrawSurface __RPC_FAR *__RPC_FAR *ppDirectDrawSurface,
    /* [out] */ RECT __RPC_FAR *pRect);


void __RPC_STUB IDirectDrawMediaSample_GetSurfaceAndReleaseLock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDirectDrawMediaSample_LockMediaSamplePointer_Proxy( 
    IDirectDrawMediaSample __RPC_FAR * This);


void __RPC_STUB IDirectDrawMediaSample_LockMediaSamplePointer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDirectDrawMediaSample_INTERFACE_DEFINED__ */


#ifndef __IAMMediaTypeStream_INTERFACE_DEFINED__
#define __IAMMediaTypeStream_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAMMediaTypeStream
 * at Thu Nov 13 19:28:37 1997
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][local][object] */ 



EXTERN_C const IID IID_IAMMediaTypeStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("AB6B4AFA-F6E4-11d0-900D-00C04FD9189D")
    IAMMediaTypeStream : public IMediaStream
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetFormat( 
            /* [out] */ AM_MEDIA_TYPE __RPC_FAR *pMediaType,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFormat( 
            /* [in] */ AM_MEDIA_TYPE __RPC_FAR *pMediaType,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateSample( 
            /* [in] */ long lSampleSize,
            /* [optional][in] */ BYTE __RPC_FAR *pbBuffer,
            /* [in] */ DWORD dwFlags,
            /* [optional][in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [out] */ IAMMediaTypeSample __RPC_FAR *__RPC_FAR *ppAMMediaTypeSample) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStreamAllocatorRequirements( 
            /* [out] */ ALLOCATOR_PROPERTIES __RPC_FAR *pProps) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetStreamAllocatorRequirements( 
            /* [in] */ ALLOCATOR_PROPERTIES __RPC_FAR *pProps) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAMMediaTypeStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAMMediaTypeStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAMMediaTypeStream __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAMMediaTypeStream __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMultiMediaStream )( 
            IAMMediaTypeStream __RPC_FAR * This,
            /* [out] */ IMultiMediaStream __RPC_FAR *__RPC_FAR *ppMultiMediaStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInformation )( 
            IAMMediaTypeStream __RPC_FAR * This,
            /* [optional][out] */ MSPID __RPC_FAR *pPurposeId,
            /* [optional][out] */ STREAM_TYPE __RPC_FAR *pType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSameFormat )( 
            IAMMediaTypeStream __RPC_FAR * This,
            /* [in] */ IMediaStream __RPC_FAR *pStreamThatHasDesiredFormat,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AllocateSample )( 
            IAMMediaTypeStream __RPC_FAR * This,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IStreamSample __RPC_FAR *__RPC_FAR *ppSample);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateSharedSample )( 
            IAMMediaTypeStream __RPC_FAR * This,
            /* [in] */ IStreamSample __RPC_FAR *pExistingSample,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IStreamSample __RPC_FAR *__RPC_FAR *ppNewSample);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendEndOfStream )( 
            IAMMediaTypeStream __RPC_FAR * This,
            DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFormat )( 
            IAMMediaTypeStream __RPC_FAR * This,
            /* [out] */ AM_MEDIA_TYPE __RPC_FAR *pMediaType,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFormat )( 
            IAMMediaTypeStream __RPC_FAR * This,
            /* [in] */ AM_MEDIA_TYPE __RPC_FAR *pMediaType,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateSample )( 
            IAMMediaTypeStream __RPC_FAR * This,
            /* [in] */ long lSampleSize,
            /* [optional][in] */ BYTE __RPC_FAR *pbBuffer,
            /* [in] */ DWORD dwFlags,
            /* [optional][in] */ IUnknown __RPC_FAR *pUnkOuter,
            /* [out] */ IAMMediaTypeSample __RPC_FAR *__RPC_FAR *ppAMMediaTypeSample);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStreamAllocatorRequirements )( 
            IAMMediaTypeStream __RPC_FAR * This,
            /* [out] */ ALLOCATOR_PROPERTIES __RPC_FAR *pProps);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetStreamAllocatorRequirements )( 
            IAMMediaTypeStream __RPC_FAR * This,
            /* [in] */ ALLOCATOR_PROPERTIES __RPC_FAR *pProps);
        
        END_INTERFACE
    } IAMMediaTypeStreamVtbl;

    interface IAMMediaTypeStream
    {
        CONST_VTBL struct IAMMediaTypeStreamVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMMediaTypeStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMMediaTypeStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMMediaTypeStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMMediaTypeStream_GetMultiMediaStream(This,ppMultiMediaStream)	\
    (This)->lpVtbl -> GetMultiMediaStream(This,ppMultiMediaStream)

#define IAMMediaTypeStream_GetInformation(This,pPurposeId,pType)	\
    (This)->lpVtbl -> GetInformation(This,pPurposeId,pType)

#define IAMMediaTypeStream_SetSameFormat(This,pStreamThatHasDesiredFormat,dwFlags)	\
    (This)->lpVtbl -> SetSameFormat(This,pStreamThatHasDesiredFormat,dwFlags)

#define IAMMediaTypeStream_AllocateSample(This,dwFlags,ppSample)	\
    (This)->lpVtbl -> AllocateSample(This,dwFlags,ppSample)

#define IAMMediaTypeStream_CreateSharedSample(This,pExistingSample,dwFlags,ppNewSample)	\
    (This)->lpVtbl -> CreateSharedSample(This,pExistingSample,dwFlags,ppNewSample)

#define IAMMediaTypeStream_SendEndOfStream(This,dwFlags)	\
    (This)->lpVtbl -> SendEndOfStream(This,dwFlags)


#define IAMMediaTypeStream_GetFormat(This,pMediaType,dwFlags)	\
    (This)->lpVtbl -> GetFormat(This,pMediaType,dwFlags)

#define IAMMediaTypeStream_SetFormat(This,pMediaType,dwFlags)	\
    (This)->lpVtbl -> SetFormat(This,pMediaType,dwFlags)

#define IAMMediaTypeStream_CreateSample(This,lSampleSize,pbBuffer,dwFlags,pUnkOuter,ppAMMediaTypeSample)	\
    (This)->lpVtbl -> CreateSample(This,lSampleSize,pbBuffer,dwFlags,pUnkOuter,ppAMMediaTypeSample)

#define IAMMediaTypeStream_GetStreamAllocatorRequirements(This,pProps)	\
    (This)->lpVtbl -> GetStreamAllocatorRequirements(This,pProps)

#define IAMMediaTypeStream_SetStreamAllocatorRequirements(This,pProps)	\
    (This)->lpVtbl -> SetStreamAllocatorRequirements(This,pProps)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMMediaTypeStream_GetFormat_Proxy( 
    IAMMediaTypeStream __RPC_FAR * This,
    /* [out] */ AM_MEDIA_TYPE __RPC_FAR *pMediaType,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IAMMediaTypeStream_GetFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMediaTypeStream_SetFormat_Proxy( 
    IAMMediaTypeStream __RPC_FAR * This,
    /* [in] */ AM_MEDIA_TYPE __RPC_FAR *pMediaType,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IAMMediaTypeStream_SetFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMediaTypeStream_CreateSample_Proxy( 
    IAMMediaTypeStream __RPC_FAR * This,
    /* [in] */ long lSampleSize,
    /* [optional][in] */ BYTE __RPC_FAR *pbBuffer,
    /* [in] */ DWORD dwFlags,
    /* [optional][in] */ IUnknown __RPC_FAR *pUnkOuter,
    /* [out] */ IAMMediaTypeSample __RPC_FAR *__RPC_FAR *ppAMMediaTypeSample);


void __RPC_STUB IAMMediaTypeStream_CreateSample_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMediaTypeStream_GetStreamAllocatorRequirements_Proxy( 
    IAMMediaTypeStream __RPC_FAR * This,
    /* [out] */ ALLOCATOR_PROPERTIES __RPC_FAR *pProps);


void __RPC_STUB IAMMediaTypeStream_GetStreamAllocatorRequirements_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMediaTypeStream_SetStreamAllocatorRequirements_Proxy( 
    IAMMediaTypeStream __RPC_FAR * This,
    /* [in] */ ALLOCATOR_PROPERTIES __RPC_FAR *pProps);


void __RPC_STUB IAMMediaTypeStream_SetStreamAllocatorRequirements_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMMediaTypeStream_INTERFACE_DEFINED__ */


#ifndef __IAMMediaTypeSample_INTERFACE_DEFINED__
#define __IAMMediaTypeSample_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAMMediaTypeSample
 * at Thu Nov 13 19:28:37 1997
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][local][object] */ 



EXTERN_C const IID IID_IAMMediaTypeSample;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("AB6B4AFB-F6E4-11d0-900D-00C04FD9189D")
    IAMMediaTypeSample : public IStreamSample
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetPointer( 
            /* [in] */ BYTE __RPC_FAR *pBuffer,
            /* [in] */ long lSize) = 0;
        
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
            long __MIDL_0022) = 0;
        
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

    typedef struct IAMMediaTypeSampleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAMMediaTypeSample __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAMMediaTypeSample __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAMMediaTypeSample __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMediaStream )( 
            IAMMediaTypeSample __RPC_FAR * This,
            /* [in] */ IMediaStream __RPC_FAR *__RPC_FAR *ppMediaStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSampleTimes )( 
            IAMMediaTypeSample __RPC_FAR * This,
            /* [optional][out] */ STREAM_TIME __RPC_FAR *pStartTime,
            /* [optional][out] */ STREAM_TIME __RPC_FAR *pEndTime,
            /* [optional][out] */ STREAM_TIME __RPC_FAR *pCurrentTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSampleTimes )( 
            IAMMediaTypeSample __RPC_FAR * This,
            /* [optional][in] */ const STREAM_TIME __RPC_FAR *pStartTime,
            /* [optional][in] */ const STREAM_TIME __RPC_FAR *pEndTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Update )( 
            IAMMediaTypeSample __RPC_FAR * This,
            /* [in] */ DWORD dwFlags,
            /* [optional][in] */ HANDLE hEvent,
            /* [optional][in] */ PAPCFUNC pfnAPC,
            /* [optional][in] */ DWORD dwAPCData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CompletionStatus )( 
            IAMMediaTypeSample __RPC_FAR * This,
            /* [in] */ DWORD dwFlags,
            /* [optional][in] */ DWORD dwMilliseconds);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPointer )( 
            IAMMediaTypeSample __RPC_FAR * This,
            /* [in] */ BYTE __RPC_FAR *pBuffer,
            /* [in] */ long lSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPointer )( 
            IAMMediaTypeSample __RPC_FAR * This,
            /* [out] */ BYTE __RPC_FAR *__RPC_FAR *ppBuffer);
        
        long ( STDMETHODCALLTYPE __RPC_FAR *GetSize )( 
            IAMMediaTypeSample __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTime )( 
            IAMMediaTypeSample __RPC_FAR * This,
            /* [out] */ REFERENCE_TIME __RPC_FAR *pTimeStart,
            /* [out] */ REFERENCE_TIME __RPC_FAR *pTimeEnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTime )( 
            IAMMediaTypeSample __RPC_FAR * This,
            /* [in] */ REFERENCE_TIME __RPC_FAR *pTimeStart,
            /* [in] */ REFERENCE_TIME __RPC_FAR *pTimeEnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsSyncPoint )( 
            IAMMediaTypeSample __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSyncPoint )( 
            IAMMediaTypeSample __RPC_FAR * This,
            BOOL bIsSyncPoint);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsPreroll )( 
            IAMMediaTypeSample __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPreroll )( 
            IAMMediaTypeSample __RPC_FAR * This,
            BOOL bIsPreroll);
        
        long ( STDMETHODCALLTYPE __RPC_FAR *GetActualDataLength )( 
            IAMMediaTypeSample __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetActualDataLength )( 
            IAMMediaTypeSample __RPC_FAR * This,
            long __MIDL_0022);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMediaType )( 
            IAMMediaTypeSample __RPC_FAR * This,
            AM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *ppMediaType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMediaType )( 
            IAMMediaTypeSample __RPC_FAR * This,
            AM_MEDIA_TYPE __RPC_FAR *pMediaType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsDiscontinuity )( 
            IAMMediaTypeSample __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDiscontinuity )( 
            IAMMediaTypeSample __RPC_FAR * This,
            BOOL bDiscontinuity);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMediaTime )( 
            IAMMediaTypeSample __RPC_FAR * This,
            /* [out] */ LONGLONG __RPC_FAR *pTimeStart,
            /* [out] */ LONGLONG __RPC_FAR *pTimeEnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMediaTime )( 
            IAMMediaTypeSample __RPC_FAR * This,
            /* [in] */ LONGLONG __RPC_FAR *pTimeStart,
            /* [in] */ LONGLONG __RPC_FAR *pTimeEnd);
        
        END_INTERFACE
    } IAMMediaTypeSampleVtbl;

    interface IAMMediaTypeSample
    {
        CONST_VTBL struct IAMMediaTypeSampleVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAMMediaTypeSample_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAMMediaTypeSample_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAMMediaTypeSample_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAMMediaTypeSample_GetMediaStream(This,ppMediaStream)	\
    (This)->lpVtbl -> GetMediaStream(This,ppMediaStream)

#define IAMMediaTypeSample_GetSampleTimes(This,pStartTime,pEndTime,pCurrentTime)	\
    (This)->lpVtbl -> GetSampleTimes(This,pStartTime,pEndTime,pCurrentTime)

#define IAMMediaTypeSample_SetSampleTimes(This,pStartTime,pEndTime)	\
    (This)->lpVtbl -> SetSampleTimes(This,pStartTime,pEndTime)

#define IAMMediaTypeSample_Update(This,dwFlags,hEvent,pfnAPC,dwAPCData)	\
    (This)->lpVtbl -> Update(This,dwFlags,hEvent,pfnAPC,dwAPCData)

#define IAMMediaTypeSample_CompletionStatus(This,dwFlags,dwMilliseconds)	\
    (This)->lpVtbl -> CompletionStatus(This,dwFlags,dwMilliseconds)


#define IAMMediaTypeSample_SetPointer(This,pBuffer,lSize)	\
    (This)->lpVtbl -> SetPointer(This,pBuffer,lSize)

#define IAMMediaTypeSample_GetPointer(This,ppBuffer)	\
    (This)->lpVtbl -> GetPointer(This,ppBuffer)

#define IAMMediaTypeSample_GetSize(This)	\
    (This)->lpVtbl -> GetSize(This)

#define IAMMediaTypeSample_GetTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> GetTime(This,pTimeStart,pTimeEnd)

#define IAMMediaTypeSample_SetTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> SetTime(This,pTimeStart,pTimeEnd)

#define IAMMediaTypeSample_IsSyncPoint(This)	\
    (This)->lpVtbl -> IsSyncPoint(This)

#define IAMMediaTypeSample_SetSyncPoint(This,bIsSyncPoint)	\
    (This)->lpVtbl -> SetSyncPoint(This,bIsSyncPoint)

#define IAMMediaTypeSample_IsPreroll(This)	\
    (This)->lpVtbl -> IsPreroll(This)

#define IAMMediaTypeSample_SetPreroll(This,bIsPreroll)	\
    (This)->lpVtbl -> SetPreroll(This,bIsPreroll)

#define IAMMediaTypeSample_GetActualDataLength(This)	\
    (This)->lpVtbl -> GetActualDataLength(This)

#define IAMMediaTypeSample_SetActualDataLength(This,__MIDL_0022)	\
    (This)->lpVtbl -> SetActualDataLength(This,__MIDL_0022)

#define IAMMediaTypeSample_GetMediaType(This,ppMediaType)	\
    (This)->lpVtbl -> GetMediaType(This,ppMediaType)

#define IAMMediaTypeSample_SetMediaType(This,pMediaType)	\
    (This)->lpVtbl -> SetMediaType(This,pMediaType)

#define IAMMediaTypeSample_IsDiscontinuity(This)	\
    (This)->lpVtbl -> IsDiscontinuity(This)

#define IAMMediaTypeSample_SetDiscontinuity(This,bDiscontinuity)	\
    (This)->lpVtbl -> SetDiscontinuity(This,bDiscontinuity)

#define IAMMediaTypeSample_GetMediaTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> GetMediaTime(This,pTimeStart,pTimeEnd)

#define IAMMediaTypeSample_SetMediaTime(This,pTimeStart,pTimeEnd)	\
    (This)->lpVtbl -> SetMediaTime(This,pTimeStart,pTimeEnd)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_SetPointer_Proxy( 
    IAMMediaTypeSample __RPC_FAR * This,
    /* [in] */ BYTE __RPC_FAR *pBuffer,
    /* [in] */ long lSize);


void __RPC_STUB IAMMediaTypeSample_SetPointer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_GetPointer_Proxy( 
    IAMMediaTypeSample __RPC_FAR * This,
    /* [out] */ BYTE __RPC_FAR *__RPC_FAR *ppBuffer);


void __RPC_STUB IAMMediaTypeSample_GetPointer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


long STDMETHODCALLTYPE IAMMediaTypeSample_GetSize_Proxy( 
    IAMMediaTypeSample __RPC_FAR * This);


void __RPC_STUB IAMMediaTypeSample_GetSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_GetTime_Proxy( 
    IAMMediaTypeSample __RPC_FAR * This,
    /* [out] */ REFERENCE_TIME __RPC_FAR *pTimeStart,
    /* [out] */ REFERENCE_TIME __RPC_FAR *pTimeEnd);


void __RPC_STUB IAMMediaTypeSample_GetTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_SetTime_Proxy( 
    IAMMediaTypeSample __RPC_FAR * This,
    /* [in] */ REFERENCE_TIME __RPC_FAR *pTimeStart,
    /* [in] */ REFERENCE_TIME __RPC_FAR *pTimeEnd);


void __RPC_STUB IAMMediaTypeSample_SetTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_IsSyncPoint_Proxy( 
    IAMMediaTypeSample __RPC_FAR * This);


void __RPC_STUB IAMMediaTypeSample_IsSyncPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_SetSyncPoint_Proxy( 
    IAMMediaTypeSample __RPC_FAR * This,
    BOOL bIsSyncPoint);


void __RPC_STUB IAMMediaTypeSample_SetSyncPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_IsPreroll_Proxy( 
    IAMMediaTypeSample __RPC_FAR * This);


void __RPC_STUB IAMMediaTypeSample_IsPreroll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_SetPreroll_Proxy( 
    IAMMediaTypeSample __RPC_FAR * This,
    BOOL bIsPreroll);


void __RPC_STUB IAMMediaTypeSample_SetPreroll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


long STDMETHODCALLTYPE IAMMediaTypeSample_GetActualDataLength_Proxy( 
    IAMMediaTypeSample __RPC_FAR * This);


void __RPC_STUB IAMMediaTypeSample_GetActualDataLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_SetActualDataLength_Proxy( 
    IAMMediaTypeSample __RPC_FAR * This,
    long __MIDL_0022);


void __RPC_STUB IAMMediaTypeSample_SetActualDataLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_GetMediaType_Proxy( 
    IAMMediaTypeSample __RPC_FAR * This,
    AM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *ppMediaType);


void __RPC_STUB IAMMediaTypeSample_GetMediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_SetMediaType_Proxy( 
    IAMMediaTypeSample __RPC_FAR * This,
    AM_MEDIA_TYPE __RPC_FAR *pMediaType);


void __RPC_STUB IAMMediaTypeSample_SetMediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_IsDiscontinuity_Proxy( 
    IAMMediaTypeSample __RPC_FAR * This);


void __RPC_STUB IAMMediaTypeSample_IsDiscontinuity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_SetDiscontinuity_Proxy( 
    IAMMediaTypeSample __RPC_FAR * This,
    BOOL bDiscontinuity);


void __RPC_STUB IAMMediaTypeSample_SetDiscontinuity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_GetMediaTime_Proxy( 
    IAMMediaTypeSample __RPC_FAR * This,
    /* [out] */ LONGLONG __RPC_FAR *pTimeStart,
    /* [out] */ LONGLONG __RPC_FAR *pTimeEnd);


void __RPC_STUB IAMMediaTypeSample_GetMediaTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAMMediaTypeSample_SetMediaTime_Proxy( 
    IAMMediaTypeSample __RPC_FAR * This,
    /* [in] */ LONGLONG __RPC_FAR *pTimeStart,
    /* [in] */ LONGLONG __RPC_FAR *pTimeEnd);


void __RPC_STUB IAMMediaTypeSample_SetMediaTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAMMediaTypeSample_INTERFACE_DEFINED__ */



#ifndef __DirectShowStreamLib_LIBRARY_DEFINED__
#define __DirectShowStreamLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: DirectShowStreamLib
 * at Thu Nov 13 19:28:37 1997
 * using MIDL 3.02.88
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_DirectShowStreamLib;

EXTERN_C const CLSID CLSID_AMMultiMediaStream;

#ifdef __cplusplus

class DECLSPEC_UUID("49c47ce5-9ba4-11d0-8212-00c04fc32c45")
AMMultiMediaStream;
#endif
#endif /* __DirectShowStreamLib_LIBRARY_DEFINED__ */

/****************************************
 * Generated header for interface: __MIDL_itf_amstream_0239
 * at Thu Nov 13 19:28:37 1997
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


#ifndef __cplusplus
EXTERN_C const CLSID CLSID_AMMultiMediaStream;
#endif
DEFINE_GUID(CLSID_AMDirectDrawStream, /* 49c47ce4-9ba4-11d0-8212-00c04fc32c45 */
0x49c47ce4, 0x9ba4, 0x11d0, 0x82, 0x12, 0x00, 0xc0, 0x4f, 0xc3, 0x2c, 0x45);
DEFINE_GUID(CLSID_AMAudioStream, /* 8496e040-af4c-11d0-8212-00c04fc32c45 */
0x8496e040, 0xaf4c, 0x11d0, 0x82, 0x12, 0x00, 0xc0, 0x4f, 0xc3, 0x2c, 0x45);
DEFINE_GUID(CLSID_AMAudioData, /* f2468580-af8a-11d0-8212-00c04fc32c45 */
0xf2468580, 0xaf8a, 0x11d0, 0x82, 0x12, 0x00, 0xc0, 0x4f, 0xc3, 0x2c, 0x45);
DEFINE_GUID(CLSID_AMMediaTypeStream, /* CF0F2F7C-F7BF-11d0-900D-00C04FD9189D */
0xcf0f2f7c, 0xf7bf, 0x11d0, 0x90, 0xd, 0x0, 0xc0, 0x4f, 0xd9, 0x18, 0x9d);


extern RPC_IF_HANDLE __MIDL_itf_amstream_0239_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_amstream_0239_v0_0_s_ifspec;

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
