/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.02.88 */
/* at Fri Feb 18 03:27:35 2000
 */
/* Compiler settings for e:\dragon21\private\dshowdm6\idl\.\control.odl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"

#ifndef __control_h__
#define __control_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IMediaControl_FWD_DEFINED__
#define __IMediaControl_FWD_DEFINED__
typedef interface IMediaControl IMediaControl;
#endif 	/* __IMediaControl_FWD_DEFINED__ */


#ifndef __IMediaEvent_FWD_DEFINED__
#define __IMediaEvent_FWD_DEFINED__
typedef interface IMediaEvent IMediaEvent;
#endif 	/* __IMediaEvent_FWD_DEFINED__ */


#ifndef __IMediaEventEx_FWD_DEFINED__
#define __IMediaEventEx_FWD_DEFINED__
typedef interface IMediaEventEx IMediaEventEx;
#endif 	/* __IMediaEventEx_FWD_DEFINED__ */


#ifndef __IMediaPosition_FWD_DEFINED__
#define __IMediaPosition_FWD_DEFINED__
typedef interface IMediaPosition IMediaPosition;
#endif 	/* __IMediaPosition_FWD_DEFINED__ */


#ifndef __IBasicAudio_FWD_DEFINED__
#define __IBasicAudio_FWD_DEFINED__
typedef interface IBasicAudio IBasicAudio;
#endif 	/* __IBasicAudio_FWD_DEFINED__ */


#ifndef __IVideoWindow_FWD_DEFINED__
#define __IVideoWindow_FWD_DEFINED__
typedef interface IVideoWindow IVideoWindow;
#endif 	/* __IVideoWindow_FWD_DEFINED__ */


#ifndef __IBasicVideo_FWD_DEFINED__
#define __IBasicVideo_FWD_DEFINED__
typedef interface IBasicVideo IBasicVideo;
#endif 	/* __IBasicVideo_FWD_DEFINED__ */


#ifndef __FilgraphManager_FWD_DEFINED__
#define __FilgraphManager_FWD_DEFINED__

#ifdef __cplusplus
typedef class FilgraphManager FilgraphManager;
#else
typedef struct FilgraphManager FilgraphManager;
#endif /* __cplusplus */

#endif 	/* __FilgraphManager_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __QuartzTypeLib_LIBRARY_DEFINED__
#define __QuartzTypeLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: QuartzTypeLib
 * at Fri Feb 18 03:27:35 2000
 * using MIDL 3.02.88
 ****************************************/
/* [version][lcid][helpstring][uuid] */ 


#define OATRUE (-1)
#define OAFALSE (0)
typedef double REFTIME;

typedef long OAEVENT;

typedef long OAHWND;

typedef long OAFilterState;


DEFINE_GUID(LIBID_QuartzTypeLib,0x56a868b0,0x0ad4,0x11ce,0xb0,0x3a,0x00,0x20,0xaf,0x0b,0xa7,0x70);

#ifndef __IMediaControl_INTERFACE_DEFINED__
#define __IMediaControl_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMediaControl
 * at Fri Feb 18 03:27:35 2000
 * using MIDL 3.02.88
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



DEFINE_GUID(IID_IMediaControl,0x56a868b1,0x0ad4,0x11ce,0xb0,0x3a,0x00,0x20,0xaf,0x0b,0xa7,0x70);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a868b1-0ad4-11ce-b03a-0020af0ba770")
    IMediaControl : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Run( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Pause( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetState( 
            /* [in] */ LONG msTimeout,
            /* [out] */ OAFilterState __RPC_FAR *pfs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RenderFile( 
            /* [in] */ BSTR strFilename) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddSourceFilter( 
            /* [in] */ BSTR strFilename,
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppUnk) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_FilterCollection( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppUnk) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_RegFilterCollection( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppUnk) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StopWhenReady( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMediaControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMediaControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMediaControl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMediaControl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMediaControl __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMediaControl __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMediaControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMediaControl __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Run )( 
            IMediaControl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pause )( 
            IMediaControl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IMediaControl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetState )( 
            IMediaControl __RPC_FAR * This,
            /* [in] */ LONG msTimeout,
            /* [out] */ OAFilterState __RPC_FAR *pfs);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RenderFile )( 
            IMediaControl __RPC_FAR * This,
            /* [in] */ BSTR strFilename);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddSourceFilter )( 
            IMediaControl __RPC_FAR * This,
            /* [in] */ BSTR strFilename,
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppUnk);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FilterCollection )( 
            IMediaControl __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppUnk);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RegFilterCollection )( 
            IMediaControl __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppUnk);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopWhenReady )( 
            IMediaControl __RPC_FAR * This);
        
        END_INTERFACE
    } IMediaControlVtbl;

    interface IMediaControl
    {
        CONST_VTBL struct IMediaControlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaControl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMediaControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMediaControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMediaControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMediaControl_Run(This)	\
    (This)->lpVtbl -> Run(This)

#define IMediaControl_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IMediaControl_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IMediaControl_GetState(This,msTimeout,pfs)	\
    (This)->lpVtbl -> GetState(This,msTimeout,pfs)

#define IMediaControl_RenderFile(This,strFilename)	\
    (This)->lpVtbl -> RenderFile(This,strFilename)

#define IMediaControl_AddSourceFilter(This,strFilename,ppUnk)	\
    (This)->lpVtbl -> AddSourceFilter(This,strFilename,ppUnk)

#define IMediaControl_get_FilterCollection(This,ppUnk)	\
    (This)->lpVtbl -> get_FilterCollection(This,ppUnk)

#define IMediaControl_get_RegFilterCollection(This,ppUnk)	\
    (This)->lpVtbl -> get_RegFilterCollection(This,ppUnk)

#define IMediaControl_StopWhenReady(This)	\
    (This)->lpVtbl -> StopWhenReady(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMediaControl_Run_Proxy( 
    IMediaControl __RPC_FAR * This);


void __RPC_STUB IMediaControl_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaControl_Pause_Proxy( 
    IMediaControl __RPC_FAR * This);


void __RPC_STUB IMediaControl_Pause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaControl_Stop_Proxy( 
    IMediaControl __RPC_FAR * This);


void __RPC_STUB IMediaControl_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaControl_GetState_Proxy( 
    IMediaControl __RPC_FAR * This,
    /* [in] */ LONG msTimeout,
    /* [out] */ OAFilterState __RPC_FAR *pfs);


void __RPC_STUB IMediaControl_GetState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaControl_RenderFile_Proxy( 
    IMediaControl __RPC_FAR * This,
    /* [in] */ BSTR strFilename);


void __RPC_STUB IMediaControl_RenderFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaControl_AddSourceFilter_Proxy( 
    IMediaControl __RPC_FAR * This,
    /* [in] */ BSTR strFilename,
    /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppUnk);


void __RPC_STUB IMediaControl_AddSourceFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IMediaControl_get_FilterCollection_Proxy( 
    IMediaControl __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppUnk);


void __RPC_STUB IMediaControl_get_FilterCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IMediaControl_get_RegFilterCollection_Proxy( 
    IMediaControl __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppUnk);


void __RPC_STUB IMediaControl_get_RegFilterCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaControl_StopWhenReady_Proxy( 
    IMediaControl __RPC_FAR * This);


void __RPC_STUB IMediaControl_StopWhenReady_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMediaControl_INTERFACE_DEFINED__ */


#ifndef __IMediaEvent_INTERFACE_DEFINED__
#define __IMediaEvent_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMediaEvent
 * at Fri Feb 18 03:27:35 2000
 * using MIDL 3.02.88
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



DEFINE_GUID(IID_IMediaEvent,0x56a868b6,0x0ad4,0x11ce,0xb0,0x3a,0x00,0x20,0xaf,0x0b,0xa7,0x70);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a868b6-0ad4-11ce-b03a-0020af0ba770")
    IMediaEvent : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetEventHandle( 
            /* [out] */ OAEVENT __RPC_FAR *hEvent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEvent( 
            /* [out] */ long __RPC_FAR *lEventCode,
            /* [out] */ long __RPC_FAR *lParam1,
            /* [out] */ long __RPC_FAR *lParam2,
            /* [in] */ long msTimeout) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WaitForCompletion( 
            /* [in] */ long msTimeout,
            /* [out] */ long __RPC_FAR *pEvCode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CancelDefaultHandling( 
            /* [in] */ long lEvCode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RestoreDefaultHandling( 
            /* [in] */ long lEvCode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FreeEventParams( 
            /* [in] */ long lEvCode,
            /* [in] */ long lParam1,
            /* [in] */ long lParam2) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMediaEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMediaEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMediaEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMediaEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMediaEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMediaEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMediaEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMediaEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEventHandle )( 
            IMediaEvent __RPC_FAR * This,
            /* [out] */ OAEVENT __RPC_FAR *hEvent);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEvent )( 
            IMediaEvent __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *lEventCode,
            /* [out] */ long __RPC_FAR *lParam1,
            /* [out] */ long __RPC_FAR *lParam2,
            /* [in] */ long msTimeout);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitForCompletion )( 
            IMediaEvent __RPC_FAR * This,
            /* [in] */ long msTimeout,
            /* [out] */ long __RPC_FAR *pEvCode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CancelDefaultHandling )( 
            IMediaEvent __RPC_FAR * This,
            /* [in] */ long lEvCode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RestoreDefaultHandling )( 
            IMediaEvent __RPC_FAR * This,
            /* [in] */ long lEvCode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FreeEventParams )( 
            IMediaEvent __RPC_FAR * This,
            /* [in] */ long lEvCode,
            /* [in] */ long lParam1,
            /* [in] */ long lParam2);
        
        END_INTERFACE
    } IMediaEventVtbl;

    interface IMediaEvent
    {
        CONST_VTBL struct IMediaEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMediaEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMediaEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMediaEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMediaEvent_GetEventHandle(This,hEvent)	\
    (This)->lpVtbl -> GetEventHandle(This,hEvent)

#define IMediaEvent_GetEvent(This,lEventCode,lParam1,lParam2,msTimeout)	\
    (This)->lpVtbl -> GetEvent(This,lEventCode,lParam1,lParam2,msTimeout)

#define IMediaEvent_WaitForCompletion(This,msTimeout,pEvCode)	\
    (This)->lpVtbl -> WaitForCompletion(This,msTimeout,pEvCode)

#define IMediaEvent_CancelDefaultHandling(This,lEvCode)	\
    (This)->lpVtbl -> CancelDefaultHandling(This,lEvCode)

#define IMediaEvent_RestoreDefaultHandling(This,lEvCode)	\
    (This)->lpVtbl -> RestoreDefaultHandling(This,lEvCode)

#define IMediaEvent_FreeEventParams(This,lEvCode,lParam1,lParam2)	\
    (This)->lpVtbl -> FreeEventParams(This,lEvCode,lParam1,lParam2)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMediaEvent_GetEventHandle_Proxy( 
    IMediaEvent __RPC_FAR * This,
    /* [out] */ OAEVENT __RPC_FAR *hEvent);


void __RPC_STUB IMediaEvent_GetEventHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaEvent_GetEvent_Proxy( 
    IMediaEvent __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *lEventCode,
    /* [out] */ long __RPC_FAR *lParam1,
    /* [out] */ long __RPC_FAR *lParam2,
    /* [in] */ long msTimeout);


void __RPC_STUB IMediaEvent_GetEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaEvent_WaitForCompletion_Proxy( 
    IMediaEvent __RPC_FAR * This,
    /* [in] */ long msTimeout,
    /* [out] */ long __RPC_FAR *pEvCode);


void __RPC_STUB IMediaEvent_WaitForCompletion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaEvent_CancelDefaultHandling_Proxy( 
    IMediaEvent __RPC_FAR * This,
    /* [in] */ long lEvCode);


void __RPC_STUB IMediaEvent_CancelDefaultHandling_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaEvent_RestoreDefaultHandling_Proxy( 
    IMediaEvent __RPC_FAR * This,
    /* [in] */ long lEvCode);


void __RPC_STUB IMediaEvent_RestoreDefaultHandling_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaEvent_FreeEventParams_Proxy( 
    IMediaEvent __RPC_FAR * This,
    /* [in] */ long lEvCode,
    /* [in] */ long lParam1,
    /* [in] */ long lParam2);


void __RPC_STUB IMediaEvent_FreeEventParams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMediaEvent_INTERFACE_DEFINED__ */


#ifndef __IMediaEventEx_INTERFACE_DEFINED__
#define __IMediaEventEx_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMediaEventEx
 * at Fri Feb 18 03:27:35 2000
 * using MIDL 3.02.88
 ****************************************/
/* [object][helpstring][uuid] */ 



DEFINE_GUID(IID_IMediaEventEx,0x56a868c0,0x0ad4,0x11ce,0xb0,0x3a,0x00,0x20,0xaf,0x0b,0xa7,0x70);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a868c0-0ad4-11ce-b03a-0020af0ba770")
    IMediaEventEx : public IMediaEvent
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetNotifyWindow( 
            /* [in] */ OAHWND hwnd,
            /* [in] */ long lMsg,
            /* [in] */ long lInstanceData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetNotifyFlags( 
            /* [in] */ long lNoNotifyFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNotifyFlags( 
            /* [out] */ long __RPC_FAR *lplNoNotifyFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMediaEventExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMediaEventEx __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMediaEventEx __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMediaEventEx __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMediaEventEx __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMediaEventEx __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMediaEventEx __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMediaEventEx __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEventHandle )( 
            IMediaEventEx __RPC_FAR * This,
            /* [out] */ OAEVENT __RPC_FAR *hEvent);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEvent )( 
            IMediaEventEx __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *lEventCode,
            /* [out] */ long __RPC_FAR *lParam1,
            /* [out] */ long __RPC_FAR *lParam2,
            /* [in] */ long msTimeout);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WaitForCompletion )( 
            IMediaEventEx __RPC_FAR * This,
            /* [in] */ long msTimeout,
            /* [out] */ long __RPC_FAR *pEvCode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CancelDefaultHandling )( 
            IMediaEventEx __RPC_FAR * This,
            /* [in] */ long lEvCode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RestoreDefaultHandling )( 
            IMediaEventEx __RPC_FAR * This,
            /* [in] */ long lEvCode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FreeEventParams )( 
            IMediaEventEx __RPC_FAR * This,
            /* [in] */ long lEvCode,
            /* [in] */ long lParam1,
            /* [in] */ long lParam2);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetNotifyWindow )( 
            IMediaEventEx __RPC_FAR * This,
            /* [in] */ OAHWND hwnd,
            /* [in] */ long lMsg,
            /* [in] */ long lInstanceData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetNotifyFlags )( 
            IMediaEventEx __RPC_FAR * This,
            /* [in] */ long lNoNotifyFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNotifyFlags )( 
            IMediaEventEx __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *lplNoNotifyFlags);
        
        END_INTERFACE
    } IMediaEventExVtbl;

    interface IMediaEventEx
    {
        CONST_VTBL struct IMediaEventExVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaEventEx_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaEventEx_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaEventEx_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaEventEx_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMediaEventEx_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMediaEventEx_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMediaEventEx_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMediaEventEx_GetEventHandle(This,hEvent)	\
    (This)->lpVtbl -> GetEventHandle(This,hEvent)

#define IMediaEventEx_GetEvent(This,lEventCode,lParam1,lParam2,msTimeout)	\
    (This)->lpVtbl -> GetEvent(This,lEventCode,lParam1,lParam2,msTimeout)

#define IMediaEventEx_WaitForCompletion(This,msTimeout,pEvCode)	\
    (This)->lpVtbl -> WaitForCompletion(This,msTimeout,pEvCode)

#define IMediaEventEx_CancelDefaultHandling(This,lEvCode)	\
    (This)->lpVtbl -> CancelDefaultHandling(This,lEvCode)

#define IMediaEventEx_RestoreDefaultHandling(This,lEvCode)	\
    (This)->lpVtbl -> RestoreDefaultHandling(This,lEvCode)

#define IMediaEventEx_FreeEventParams(This,lEvCode,lParam1,lParam2)	\
    (This)->lpVtbl -> FreeEventParams(This,lEvCode,lParam1,lParam2)


#define IMediaEventEx_SetNotifyWindow(This,hwnd,lMsg,lInstanceData)	\
    (This)->lpVtbl -> SetNotifyWindow(This,hwnd,lMsg,lInstanceData)

#define IMediaEventEx_SetNotifyFlags(This,lNoNotifyFlags)	\
    (This)->lpVtbl -> SetNotifyFlags(This,lNoNotifyFlags)

#define IMediaEventEx_GetNotifyFlags(This,lplNoNotifyFlags)	\
    (This)->lpVtbl -> GetNotifyFlags(This,lplNoNotifyFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMediaEventEx_SetNotifyWindow_Proxy( 
    IMediaEventEx __RPC_FAR * This,
    /* [in] */ OAHWND hwnd,
    /* [in] */ long lMsg,
    /* [in] */ long lInstanceData);


void __RPC_STUB IMediaEventEx_SetNotifyWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaEventEx_SetNotifyFlags_Proxy( 
    IMediaEventEx __RPC_FAR * This,
    /* [in] */ long lNoNotifyFlags);


void __RPC_STUB IMediaEventEx_SetNotifyFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaEventEx_GetNotifyFlags_Proxy( 
    IMediaEventEx __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *lplNoNotifyFlags);


void __RPC_STUB IMediaEventEx_GetNotifyFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMediaEventEx_INTERFACE_DEFINED__ */


#ifndef __IMediaPosition_INTERFACE_DEFINED__
#define __IMediaPosition_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMediaPosition
 * at Fri Feb 18 03:27:35 2000
 * using MIDL 3.02.88
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



DEFINE_GUID(IID_IMediaPosition,0x56a868b2,0x0ad4,0x11ce,0xb0,0x3a,0x00,0x20,0xaf,0x0b,0xa7,0x70);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a868b2-0ad4-11ce-b03a-0020af0ba770")
    IMediaPosition : public IDispatch
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Duration( 
            /* [retval][out] */ REFTIME __RPC_FAR *plength) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_CurrentPosition( 
            /* [in] */ REFTIME llTime) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CurrentPosition( 
            /* [retval][out] */ REFTIME __RPC_FAR *pllTime) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_StopTime( 
            /* [retval][out] */ REFTIME __RPC_FAR *pllTime) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_StopTime( 
            /* [in] */ REFTIME llTime) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_PrerollTime( 
            /* [retval][out] */ REFTIME __RPC_FAR *pllTime) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_PrerollTime( 
            /* [in] */ REFTIME llTime) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Rate( 
            /* [in] */ double dRate) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Rate( 
            /* [retval][out] */ double __RPC_FAR *pdRate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CanSeekForward( 
            /* [retval][out] */ LONG __RPC_FAR *pCanSeekForward) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CanSeekBackward( 
            /* [retval][out] */ LONG __RPC_FAR *pCanSeekBackward) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMediaPositionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMediaPosition __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMediaPosition __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMediaPosition __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMediaPosition __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMediaPosition __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMediaPosition __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMediaPosition __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Duration )( 
            IMediaPosition __RPC_FAR * This,
            /* [retval][out] */ REFTIME __RPC_FAR *plength);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CurrentPosition )( 
            IMediaPosition __RPC_FAR * This,
            /* [in] */ REFTIME llTime);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CurrentPosition )( 
            IMediaPosition __RPC_FAR * This,
            /* [retval][out] */ REFTIME __RPC_FAR *pllTime);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StopTime )( 
            IMediaPosition __RPC_FAR * This,
            /* [retval][out] */ REFTIME __RPC_FAR *pllTime);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StopTime )( 
            IMediaPosition __RPC_FAR * This,
            /* [in] */ REFTIME llTime);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrerollTime )( 
            IMediaPosition __RPC_FAR * This,
            /* [retval][out] */ REFTIME __RPC_FAR *pllTime);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PrerollTime )( 
            IMediaPosition __RPC_FAR * This,
            /* [in] */ REFTIME llTime);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Rate )( 
            IMediaPosition __RPC_FAR * This,
            /* [in] */ double dRate);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Rate )( 
            IMediaPosition __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pdRate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CanSeekForward )( 
            IMediaPosition __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pCanSeekForward);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CanSeekBackward )( 
            IMediaPosition __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pCanSeekBackward);
        
        END_INTERFACE
    } IMediaPositionVtbl;

    interface IMediaPosition
    {
        CONST_VTBL struct IMediaPositionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaPosition_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaPosition_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaPosition_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaPosition_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMediaPosition_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMediaPosition_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMediaPosition_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMediaPosition_get_Duration(This,plength)	\
    (This)->lpVtbl -> get_Duration(This,plength)

#define IMediaPosition_put_CurrentPosition(This,llTime)	\
    (This)->lpVtbl -> put_CurrentPosition(This,llTime)

#define IMediaPosition_get_CurrentPosition(This,pllTime)	\
    (This)->lpVtbl -> get_CurrentPosition(This,pllTime)

#define IMediaPosition_get_StopTime(This,pllTime)	\
    (This)->lpVtbl -> get_StopTime(This,pllTime)

#define IMediaPosition_put_StopTime(This,llTime)	\
    (This)->lpVtbl -> put_StopTime(This,llTime)

#define IMediaPosition_get_PrerollTime(This,pllTime)	\
    (This)->lpVtbl -> get_PrerollTime(This,pllTime)

#define IMediaPosition_put_PrerollTime(This,llTime)	\
    (This)->lpVtbl -> put_PrerollTime(This,llTime)

#define IMediaPosition_put_Rate(This,dRate)	\
    (This)->lpVtbl -> put_Rate(This,dRate)

#define IMediaPosition_get_Rate(This,pdRate)	\
    (This)->lpVtbl -> get_Rate(This,pdRate)

#define IMediaPosition_CanSeekForward(This,pCanSeekForward)	\
    (This)->lpVtbl -> CanSeekForward(This,pCanSeekForward)

#define IMediaPosition_CanSeekBackward(This,pCanSeekBackward)	\
    (This)->lpVtbl -> CanSeekBackward(This,pCanSeekBackward)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IMediaPosition_get_Duration_Proxy( 
    IMediaPosition __RPC_FAR * This,
    /* [retval][out] */ REFTIME __RPC_FAR *plength);


void __RPC_STUB IMediaPosition_get_Duration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IMediaPosition_put_CurrentPosition_Proxy( 
    IMediaPosition __RPC_FAR * This,
    /* [in] */ REFTIME llTime);


void __RPC_STUB IMediaPosition_put_CurrentPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IMediaPosition_get_CurrentPosition_Proxy( 
    IMediaPosition __RPC_FAR * This,
    /* [retval][out] */ REFTIME __RPC_FAR *pllTime);


void __RPC_STUB IMediaPosition_get_CurrentPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IMediaPosition_get_StopTime_Proxy( 
    IMediaPosition __RPC_FAR * This,
    /* [retval][out] */ REFTIME __RPC_FAR *pllTime);


void __RPC_STUB IMediaPosition_get_StopTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IMediaPosition_put_StopTime_Proxy( 
    IMediaPosition __RPC_FAR * This,
    /* [in] */ REFTIME llTime);


void __RPC_STUB IMediaPosition_put_StopTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IMediaPosition_get_PrerollTime_Proxy( 
    IMediaPosition __RPC_FAR * This,
    /* [retval][out] */ REFTIME __RPC_FAR *pllTime);


void __RPC_STUB IMediaPosition_get_PrerollTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IMediaPosition_put_PrerollTime_Proxy( 
    IMediaPosition __RPC_FAR * This,
    /* [in] */ REFTIME llTime);


void __RPC_STUB IMediaPosition_put_PrerollTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IMediaPosition_put_Rate_Proxy( 
    IMediaPosition __RPC_FAR * This,
    /* [in] */ double dRate);


void __RPC_STUB IMediaPosition_put_Rate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IMediaPosition_get_Rate_Proxy( 
    IMediaPosition __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pdRate);


void __RPC_STUB IMediaPosition_get_Rate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaPosition_CanSeekForward_Proxy( 
    IMediaPosition __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pCanSeekForward);


void __RPC_STUB IMediaPosition_CanSeekForward_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMediaPosition_CanSeekBackward_Proxy( 
    IMediaPosition __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pCanSeekBackward);


void __RPC_STUB IMediaPosition_CanSeekBackward_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMediaPosition_INTERFACE_DEFINED__ */


#ifndef __IBasicAudio_INTERFACE_DEFINED__
#define __IBasicAudio_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IBasicAudio
 * at Fri Feb 18 03:27:35 2000
 * using MIDL 3.02.88
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



DEFINE_GUID(IID_IBasicAudio,0x56a868b3,0x0ad4,0x11ce,0xb0,0x3a,0x00,0x20,0xaf,0x0b,0xa7,0x70);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a868b3-0ad4-11ce-b03a-0020af0ba770")
    IBasicAudio : public IDispatch
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Volume( 
            /* [in] */ long lVolume) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Volume( 
            /* [retval][out] */ long __RPC_FAR *plVolume) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Balance( 
            /* [in] */ long lBalance) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Balance( 
            /* [retval][out] */ long __RPC_FAR *plBalance) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBasicAudioVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBasicAudio __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBasicAudio __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBasicAudio __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IBasicAudio __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IBasicAudio __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IBasicAudio __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IBasicAudio __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Volume )( 
            IBasicAudio __RPC_FAR * This,
            /* [in] */ long lVolume);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Volume )( 
            IBasicAudio __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plVolume);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Balance )( 
            IBasicAudio __RPC_FAR * This,
            /* [in] */ long lBalance);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Balance )( 
            IBasicAudio __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plBalance);
        
        END_INTERFACE
    } IBasicAudioVtbl;

    interface IBasicAudio
    {
        CONST_VTBL struct IBasicAudioVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBasicAudio_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBasicAudio_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBasicAudio_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBasicAudio_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IBasicAudio_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IBasicAudio_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IBasicAudio_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IBasicAudio_put_Volume(This,lVolume)	\
    (This)->lpVtbl -> put_Volume(This,lVolume)

#define IBasicAudio_get_Volume(This,plVolume)	\
    (This)->lpVtbl -> get_Volume(This,plVolume)

#define IBasicAudio_put_Balance(This,lBalance)	\
    (This)->lpVtbl -> put_Balance(This,lBalance)

#define IBasicAudio_get_Balance(This,plBalance)	\
    (This)->lpVtbl -> get_Balance(This,plBalance)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IBasicAudio_put_Volume_Proxy( 
    IBasicAudio __RPC_FAR * This,
    /* [in] */ long lVolume);


void __RPC_STUB IBasicAudio_put_Volume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IBasicAudio_get_Volume_Proxy( 
    IBasicAudio __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plVolume);


void __RPC_STUB IBasicAudio_get_Volume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IBasicAudio_put_Balance_Proxy( 
    IBasicAudio __RPC_FAR * This,
    /* [in] */ long lBalance);


void __RPC_STUB IBasicAudio_put_Balance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IBasicAudio_get_Balance_Proxy( 
    IBasicAudio __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plBalance);


void __RPC_STUB IBasicAudio_get_Balance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBasicAudio_INTERFACE_DEFINED__ */


#ifndef __IVideoWindow_INTERFACE_DEFINED__
#define __IVideoWindow_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IVideoWindow
 * at Fri Feb 18 03:27:35 2000
 * using MIDL 3.02.88
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



DEFINE_GUID(IID_IVideoWindow,0x56a868b4,0x0ad4,0x11ce,0xb0,0x3a,0x00,0x20,0xaf,0x0b,0xa7,0x70);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a868b4-0ad4-11ce-b03a-0020af0ba770")
    IVideoWindow : public IDispatch
    {
    public:
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Caption( 
            /* [in] */ BSTR strCaption) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Caption( 
            /* [retval][out] */ BSTR __RPC_FAR *strCaption) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_WindowStyle( 
            /* [in] */ long WindowStyle) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_WindowStyle( 
            /* [retval][out] */ long __RPC_FAR *WindowStyle) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_WindowStyleEx( 
            /* [in] */ long WindowStyleEx) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_WindowStyleEx( 
            /* [retval][out] */ long __RPC_FAR *WindowStyleEx) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_AutoShow( 
            /* [in] */ long AutoShow) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_AutoShow( 
            /* [retval][out] */ long __RPC_FAR *AutoShow) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_WindowState( 
            /* [in] */ long WindowState) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_WindowState( 
            /* [retval][out] */ long __RPC_FAR *WindowState) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_BackgroundPalette( 
            /* [in] */ long BackgroundPalette) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_BackgroundPalette( 
            /* [retval][out] */ long __RPC_FAR *pBackgroundPalette) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ long Visible) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ long __RPC_FAR *pVisible) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Left( 
            /* [in] */ long Left) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Left( 
            /* [retval][out] */ long __RPC_FAR *pLeft) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ long Width) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ long __RPC_FAR *pWidth) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Top( 
            /* [in] */ long Top) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Top( 
            /* [retval][out] */ long __RPC_FAR *pTop) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Height( 
            /* [in] */ long Height) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ long __RPC_FAR *pHeight) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Owner( 
            /* [in] */ OAHWND Owner) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Owner( 
            /* [retval][out] */ OAHWND __RPC_FAR *Owner) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_MessageDrain( 
            /* [in] */ OAHWND Drain) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_MessageDrain( 
            /* [retval][out] */ OAHWND __RPC_FAR *Drain) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_BorderColor( 
            /* [retval][out] */ long __RPC_FAR *Color) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_BorderColor( 
            /* [in] */ long Color) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_FullScreenMode( 
            /* [retval][out] */ long __RPC_FAR *FullScreenMode) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_FullScreenMode( 
            /* [in] */ long FullScreenMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetWindowForeground( 
            /* [in] */ long Focus) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NotifyOwnerMessage( 
            /* [in] */ long hwnd,
            /* [in] */ long uMsg,
            /* [in] */ long wParam,
            /* [in] */ long lParam) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetWindowPosition( 
            /* [in] */ long Left,
            /* [in] */ long Top,
            /* [in] */ long Width,
            /* [in] */ long Height) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWindowPosition( 
            /* [out] */ long __RPC_FAR *pLeft,
            /* [out] */ long __RPC_FAR *pTop,
            /* [out] */ long __RPC_FAR *pWidth,
            /* [out] */ long __RPC_FAR *pHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMinIdealImageSize( 
            /* [out] */ long __RPC_FAR *pWidth,
            /* [out] */ long __RPC_FAR *pHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxIdealImageSize( 
            /* [out] */ long __RPC_FAR *pWidth,
            /* [out] */ long __RPC_FAR *pHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRestorePosition( 
            /* [out] */ long __RPC_FAR *pLeft,
            /* [out] */ long __RPC_FAR *pTop,
            /* [out] */ long __RPC_FAR *pWidth,
            /* [out] */ long __RPC_FAR *pHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HideCursor( 
            /* [in] */ long HideCursor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsCursorHidden( 
            /* [out] */ long __RPC_FAR *CursorHidden) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVideoWindowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVideoWindow __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVideoWindow __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVideoWindow __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Caption )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ BSTR strCaption);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Caption )( 
            IVideoWindow __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *strCaption);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WindowStyle )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ long WindowStyle);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WindowStyle )( 
            IVideoWindow __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *WindowStyle);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WindowStyleEx )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ long WindowStyleEx);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WindowStyleEx )( 
            IVideoWindow __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *WindowStyleEx);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AutoShow )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ long AutoShow);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AutoShow )( 
            IVideoWindow __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *AutoShow);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WindowState )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ long WindowState);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WindowState )( 
            IVideoWindow __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *WindowState);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BackgroundPalette )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ long BackgroundPalette);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BackgroundPalette )( 
            IVideoWindow __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pBackgroundPalette);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ long Visible);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            IVideoWindow __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVisible);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Left )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ long Left);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Left )( 
            IVideoWindow __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pLeft);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Width )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ long Width);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            IVideoWindow __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pWidth);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Top )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ long Top);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Top )( 
            IVideoWindow __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pTop);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Height )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ long Height);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Height )( 
            IVideoWindow __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pHeight);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Owner )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ OAHWND Owner);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Owner )( 
            IVideoWindow __RPC_FAR * This,
            /* [retval][out] */ OAHWND __RPC_FAR *Owner);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MessageDrain )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ OAHWND Drain);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MessageDrain )( 
            IVideoWindow __RPC_FAR * This,
            /* [retval][out] */ OAHWND __RPC_FAR *Drain);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BorderColor )( 
            IVideoWindow __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Color);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BorderColor )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ long Color);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullScreenMode )( 
            IVideoWindow __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *FullScreenMode);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FullScreenMode )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ long FullScreenMode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetWindowForeground )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ long Focus);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NotifyOwnerMessage )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ long hwnd,
            /* [in] */ long uMsg,
            /* [in] */ long wParam,
            /* [in] */ long lParam);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetWindowPosition )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ long Left,
            /* [in] */ long Top,
            /* [in] */ long Width,
            /* [in] */ long Height);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWindowPosition )( 
            IVideoWindow __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pLeft,
            /* [out] */ long __RPC_FAR *pTop,
            /* [out] */ long __RPC_FAR *pWidth,
            /* [out] */ long __RPC_FAR *pHeight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMinIdealImageSize )( 
            IVideoWindow __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pWidth,
            /* [out] */ long __RPC_FAR *pHeight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxIdealImageSize )( 
            IVideoWindow __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pWidth,
            /* [out] */ long __RPC_FAR *pHeight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRestorePosition )( 
            IVideoWindow __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pLeft,
            /* [out] */ long __RPC_FAR *pTop,
            /* [out] */ long __RPC_FAR *pWidth,
            /* [out] */ long __RPC_FAR *pHeight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HideCursor )( 
            IVideoWindow __RPC_FAR * This,
            /* [in] */ long HideCursor);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsCursorHidden )( 
            IVideoWindow __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *CursorHidden);
        
        END_INTERFACE
    } IVideoWindowVtbl;

    interface IVideoWindow
    {
        CONST_VTBL struct IVideoWindowVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVideoWindow_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVideoWindow_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVideoWindow_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVideoWindow_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVideoWindow_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVideoWindow_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVideoWindow_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVideoWindow_put_Caption(This,strCaption)	\
    (This)->lpVtbl -> put_Caption(This,strCaption)

#define IVideoWindow_get_Caption(This,strCaption)	\
    (This)->lpVtbl -> get_Caption(This,strCaption)

#define IVideoWindow_put_WindowStyle(This,WindowStyle)	\
    (This)->lpVtbl -> put_WindowStyle(This,WindowStyle)

#define IVideoWindow_get_WindowStyle(This,WindowStyle)	\
    (This)->lpVtbl -> get_WindowStyle(This,WindowStyle)

#define IVideoWindow_put_WindowStyleEx(This,WindowStyleEx)	\
    (This)->lpVtbl -> put_WindowStyleEx(This,WindowStyleEx)

#define IVideoWindow_get_WindowStyleEx(This,WindowStyleEx)	\
    (This)->lpVtbl -> get_WindowStyleEx(This,WindowStyleEx)

#define IVideoWindow_put_AutoShow(This,AutoShow)	\
    (This)->lpVtbl -> put_AutoShow(This,AutoShow)

#define IVideoWindow_get_AutoShow(This,AutoShow)	\
    (This)->lpVtbl -> get_AutoShow(This,AutoShow)

#define IVideoWindow_put_WindowState(This,WindowState)	\
    (This)->lpVtbl -> put_WindowState(This,WindowState)

#define IVideoWindow_get_WindowState(This,WindowState)	\
    (This)->lpVtbl -> get_WindowState(This,WindowState)

#define IVideoWindow_put_BackgroundPalette(This,BackgroundPalette)	\
    (This)->lpVtbl -> put_BackgroundPalette(This,BackgroundPalette)

#define IVideoWindow_get_BackgroundPalette(This,pBackgroundPalette)	\
    (This)->lpVtbl -> get_BackgroundPalette(This,pBackgroundPalette)

#define IVideoWindow_put_Visible(This,Visible)	\
    (This)->lpVtbl -> put_Visible(This,Visible)

#define IVideoWindow_get_Visible(This,pVisible)	\
    (This)->lpVtbl -> get_Visible(This,pVisible)

#define IVideoWindow_put_Left(This,Left)	\
    (This)->lpVtbl -> put_Left(This,Left)

#define IVideoWindow_get_Left(This,pLeft)	\
    (This)->lpVtbl -> get_Left(This,pLeft)

#define IVideoWindow_put_Width(This,Width)	\
    (This)->lpVtbl -> put_Width(This,Width)

#define IVideoWindow_get_Width(This,pWidth)	\
    (This)->lpVtbl -> get_Width(This,pWidth)

#define IVideoWindow_put_Top(This,Top)	\
    (This)->lpVtbl -> put_Top(This,Top)

#define IVideoWindow_get_Top(This,pTop)	\
    (This)->lpVtbl -> get_Top(This,pTop)

#define IVideoWindow_put_Height(This,Height)	\
    (This)->lpVtbl -> put_Height(This,Height)

#define IVideoWindow_get_Height(This,pHeight)	\
    (This)->lpVtbl -> get_Height(This,pHeight)

#define IVideoWindow_put_Owner(This,Owner)	\
    (This)->lpVtbl -> put_Owner(This,Owner)

#define IVideoWindow_get_Owner(This,Owner)	\
    (This)->lpVtbl -> get_Owner(This,Owner)

#define IVideoWindow_put_MessageDrain(This,Drain)	\
    (This)->lpVtbl -> put_MessageDrain(This,Drain)

#define IVideoWindow_get_MessageDrain(This,Drain)	\
    (This)->lpVtbl -> get_MessageDrain(This,Drain)

#define IVideoWindow_get_BorderColor(This,Color)	\
    (This)->lpVtbl -> get_BorderColor(This,Color)

#define IVideoWindow_put_BorderColor(This,Color)	\
    (This)->lpVtbl -> put_BorderColor(This,Color)

#define IVideoWindow_get_FullScreenMode(This,FullScreenMode)	\
    (This)->lpVtbl -> get_FullScreenMode(This,FullScreenMode)

#define IVideoWindow_put_FullScreenMode(This,FullScreenMode)	\
    (This)->lpVtbl -> put_FullScreenMode(This,FullScreenMode)

#define IVideoWindow_SetWindowForeground(This,Focus)	\
    (This)->lpVtbl -> SetWindowForeground(This,Focus)

#define IVideoWindow_NotifyOwnerMessage(This,hwnd,uMsg,wParam,lParam)	\
    (This)->lpVtbl -> NotifyOwnerMessage(This,hwnd,uMsg,wParam,lParam)

#define IVideoWindow_SetWindowPosition(This,Left,Top,Width,Height)	\
    (This)->lpVtbl -> SetWindowPosition(This,Left,Top,Width,Height)

#define IVideoWindow_GetWindowPosition(This,pLeft,pTop,pWidth,pHeight)	\
    (This)->lpVtbl -> GetWindowPosition(This,pLeft,pTop,pWidth,pHeight)

#define IVideoWindow_GetMinIdealImageSize(This,pWidth,pHeight)	\
    (This)->lpVtbl -> GetMinIdealImageSize(This,pWidth,pHeight)

#define IVideoWindow_GetMaxIdealImageSize(This,pWidth,pHeight)	\
    (This)->lpVtbl -> GetMaxIdealImageSize(This,pWidth,pHeight)

#define IVideoWindow_GetRestorePosition(This,pLeft,pTop,pWidth,pHeight)	\
    (This)->lpVtbl -> GetRestorePosition(This,pLeft,pTop,pWidth,pHeight)

#define IVideoWindow_HideCursor(This,HideCursor)	\
    (This)->lpVtbl -> HideCursor(This,HideCursor)

#define IVideoWindow_IsCursorHidden(This,CursorHidden)	\
    (This)->lpVtbl -> IsCursorHidden(This,CursorHidden)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput] */ HRESULT STDMETHODCALLTYPE IVideoWindow_put_Caption_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [in] */ BSTR strCaption);


void __RPC_STUB IVideoWindow_put_Caption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVideoWindow_get_Caption_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *strCaption);


void __RPC_STUB IVideoWindow_get_Caption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVideoWindow_put_WindowStyle_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [in] */ long WindowStyle);


void __RPC_STUB IVideoWindow_put_WindowStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVideoWindow_get_WindowStyle_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *WindowStyle);


void __RPC_STUB IVideoWindow_get_WindowStyle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVideoWindow_put_WindowStyleEx_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [in] */ long WindowStyleEx);


void __RPC_STUB IVideoWindow_put_WindowStyleEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVideoWindow_get_WindowStyleEx_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *WindowStyleEx);


void __RPC_STUB IVideoWindow_get_WindowStyleEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVideoWindow_put_AutoShow_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [in] */ long AutoShow);


void __RPC_STUB IVideoWindow_put_AutoShow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVideoWindow_get_AutoShow_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *AutoShow);


void __RPC_STUB IVideoWindow_get_AutoShow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVideoWindow_put_WindowState_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [in] */ long WindowState);


void __RPC_STUB IVideoWindow_put_WindowState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVideoWindow_get_WindowState_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *WindowState);


void __RPC_STUB IVideoWindow_get_WindowState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVideoWindow_put_BackgroundPalette_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [in] */ long BackgroundPalette);


void __RPC_STUB IVideoWindow_put_BackgroundPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVideoWindow_get_BackgroundPalette_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pBackgroundPalette);


void __RPC_STUB IVideoWindow_get_BackgroundPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVideoWindow_put_Visible_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [in] */ long Visible);


void __RPC_STUB IVideoWindow_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVideoWindow_get_Visible_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVisible);


void __RPC_STUB IVideoWindow_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVideoWindow_put_Left_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [in] */ long Left);


void __RPC_STUB IVideoWindow_put_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVideoWindow_get_Left_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pLeft);


void __RPC_STUB IVideoWindow_get_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVideoWindow_put_Width_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [in] */ long Width);


void __RPC_STUB IVideoWindow_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVideoWindow_get_Width_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pWidth);


void __RPC_STUB IVideoWindow_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVideoWindow_put_Top_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [in] */ long Top);


void __RPC_STUB IVideoWindow_put_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVideoWindow_get_Top_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pTop);


void __RPC_STUB IVideoWindow_get_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVideoWindow_put_Height_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [in] */ long Height);


void __RPC_STUB IVideoWindow_put_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVideoWindow_get_Height_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pHeight);


void __RPC_STUB IVideoWindow_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVideoWindow_put_Owner_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [in] */ OAHWND Owner);


void __RPC_STUB IVideoWindow_put_Owner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVideoWindow_get_Owner_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [retval][out] */ OAHWND __RPC_FAR *Owner);


void __RPC_STUB IVideoWindow_get_Owner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVideoWindow_put_MessageDrain_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [in] */ OAHWND Drain);


void __RPC_STUB IVideoWindow_put_MessageDrain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVideoWindow_get_MessageDrain_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [retval][out] */ OAHWND __RPC_FAR *Drain);


void __RPC_STUB IVideoWindow_get_MessageDrain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVideoWindow_get_BorderColor_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Color);


void __RPC_STUB IVideoWindow_get_BorderColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVideoWindow_put_BorderColor_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [in] */ long Color);


void __RPC_STUB IVideoWindow_put_BorderColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IVideoWindow_get_FullScreenMode_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *FullScreenMode);


void __RPC_STUB IVideoWindow_get_FullScreenMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IVideoWindow_put_FullScreenMode_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [in] */ long FullScreenMode);


void __RPC_STUB IVideoWindow_put_FullScreenMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoWindow_SetWindowForeground_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [in] */ long Focus);


void __RPC_STUB IVideoWindow_SetWindowForeground_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoWindow_NotifyOwnerMessage_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [in] */ long hwnd,
    /* [in] */ long uMsg,
    /* [in] */ long wParam,
    /* [in] */ long lParam);


void __RPC_STUB IVideoWindow_NotifyOwnerMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoWindow_SetWindowPosition_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [in] */ long Left,
    /* [in] */ long Top,
    /* [in] */ long Width,
    /* [in] */ long Height);


void __RPC_STUB IVideoWindow_SetWindowPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoWindow_GetWindowPosition_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pLeft,
    /* [out] */ long __RPC_FAR *pTop,
    /* [out] */ long __RPC_FAR *pWidth,
    /* [out] */ long __RPC_FAR *pHeight);


void __RPC_STUB IVideoWindow_GetWindowPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoWindow_GetMinIdealImageSize_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pWidth,
    /* [out] */ long __RPC_FAR *pHeight);


void __RPC_STUB IVideoWindow_GetMinIdealImageSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoWindow_GetMaxIdealImageSize_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pWidth,
    /* [out] */ long __RPC_FAR *pHeight);


void __RPC_STUB IVideoWindow_GetMaxIdealImageSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoWindow_GetRestorePosition_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pLeft,
    /* [out] */ long __RPC_FAR *pTop,
    /* [out] */ long __RPC_FAR *pWidth,
    /* [out] */ long __RPC_FAR *pHeight);


void __RPC_STUB IVideoWindow_GetRestorePosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoWindow_HideCursor_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [in] */ long HideCursor);


void __RPC_STUB IVideoWindow_HideCursor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IVideoWindow_IsCursorHidden_Proxy( 
    IVideoWindow __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *CursorHidden);


void __RPC_STUB IVideoWindow_IsCursorHidden_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVideoWindow_INTERFACE_DEFINED__ */


#ifndef __IBasicVideo_INTERFACE_DEFINED__
#define __IBasicVideo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IBasicVideo
 * at Fri Feb 18 03:27:35 2000
 * using MIDL 3.02.88
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



DEFINE_GUID(IID_IBasicVideo,0x56a868b5,0x0ad4,0x11ce,0xb0,0x3a,0x00,0x20,0xaf,0x0b,0xa7,0x70);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("56a868b5-0ad4-11ce-b03a-0020af0ba770")
    IBasicVideo : public IDispatch
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_AvgTimePerFrame( 
            /* [retval][out] */ REFTIME __RPC_FAR *pAvgTimePerFrame) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_BitRate( 
            /* [retval][out] */ long __RPC_FAR *pBitRate) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_BitErrorRate( 
            /* [retval][out] */ long __RPC_FAR *pBitErrorRate) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_VideoWidth( 
            /* [retval][out] */ long __RPC_FAR *pVideoWidth) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_VideoHeight( 
            /* [retval][out] */ long __RPC_FAR *pVideoHeight) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_SourceLeft( 
            /* [in] */ long SourceLeft) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SourceLeft( 
            /* [retval][out] */ long __RPC_FAR *pSourceLeft) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_SourceWidth( 
            /* [in] */ long SourceWidth) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SourceWidth( 
            /* [retval][out] */ long __RPC_FAR *pSourceWidth) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_SourceTop( 
            /* [in] */ long SourceTop) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SourceTop( 
            /* [retval][out] */ long __RPC_FAR *pSourceTop) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_SourceHeight( 
            /* [in] */ long SourceHeight) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_SourceHeight( 
            /* [retval][out] */ long __RPC_FAR *pSourceHeight) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_DestinationLeft( 
            /* [in] */ long DestinationLeft) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DestinationLeft( 
            /* [retval][out] */ long __RPC_FAR *pDestinationLeft) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_DestinationWidth( 
            /* [in] */ long DestinationWidth) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DestinationWidth( 
            /* [retval][out] */ long __RPC_FAR *pDestinationWidth) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_DestinationTop( 
            /* [in] */ long DestinationTop) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DestinationTop( 
            /* [retval][out] */ long __RPC_FAR *pDestinationTop) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_DestinationHeight( 
            /* [in] */ long DestinationHeight) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_DestinationHeight( 
            /* [retval][out] */ long __RPC_FAR *pDestinationHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSourcePosition( 
            /* [in] */ long Left,
            /* [in] */ long Top,
            /* [in] */ long Width,
            /* [in] */ long Height) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSourcePosition( 
            /* [out] */ long __RPC_FAR *pLeft,
            /* [out] */ long __RPC_FAR *pTop,
            /* [out] */ long __RPC_FAR *pWidth,
            /* [out] */ long __RPC_FAR *pHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDefaultSourcePosition( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDestinationPosition( 
            /* [in] */ long Left,
            /* [in] */ long Top,
            /* [in] */ long Width,
            /* [in] */ long Height) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDestinationPosition( 
            /* [out] */ long __RPC_FAR *pLeft,
            /* [out] */ long __RPC_FAR *pTop,
            /* [out] */ long __RPC_FAR *pWidth,
            /* [out] */ long __RPC_FAR *pHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDefaultDestinationPosition( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVideoSize( 
            /* [out] */ long __RPC_FAR *pWidth,
            /* [out] */ long __RPC_FAR *pHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVideoPaletteEntries( 
            /* [in] */ long StartIndex,
            /* [in] */ long Entries,
            /* [out] */ long __RPC_FAR *pRetrieved,
            /* [out] */ long __RPC_FAR *pPalette) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurrentImage( 
            /* [out][in] */ long __RPC_FAR *pBufferSize,
            /* [out] */ long __RPC_FAR *pDIBImage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsUsingDefaultSource( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsUsingDefaultDestination( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBasicVideoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBasicVideo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBasicVideo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBasicVideo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IBasicVideo __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IBasicVideo __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IBasicVideo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IBasicVideo __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AvgTimePerFrame )( 
            IBasicVideo __RPC_FAR * This,
            /* [retval][out] */ REFTIME __RPC_FAR *pAvgTimePerFrame);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitRate )( 
            IBasicVideo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pBitRate);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BitErrorRate )( 
            IBasicVideo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pBitErrorRate);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VideoWidth )( 
            IBasicVideo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVideoWidth);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VideoHeight )( 
            IBasicVideo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVideoHeight);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SourceLeft )( 
            IBasicVideo __RPC_FAR * This,
            /* [in] */ long SourceLeft);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SourceLeft )( 
            IBasicVideo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pSourceLeft);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SourceWidth )( 
            IBasicVideo __RPC_FAR * This,
            /* [in] */ long SourceWidth);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SourceWidth )( 
            IBasicVideo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pSourceWidth);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SourceTop )( 
            IBasicVideo __RPC_FAR * This,
            /* [in] */ long SourceTop);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SourceTop )( 
            IBasicVideo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pSourceTop);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SourceHeight )( 
            IBasicVideo __RPC_FAR * This,
            /* [in] */ long SourceHeight);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SourceHeight )( 
            IBasicVideo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pSourceHeight);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DestinationLeft )( 
            IBasicVideo __RPC_FAR * This,
            /* [in] */ long DestinationLeft);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DestinationLeft )( 
            IBasicVideo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pDestinationLeft);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DestinationWidth )( 
            IBasicVideo __RPC_FAR * This,
            /* [in] */ long DestinationWidth);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DestinationWidth )( 
            IBasicVideo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pDestinationWidth);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DestinationTop )( 
            IBasicVideo __RPC_FAR * This,
            /* [in] */ long DestinationTop);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DestinationTop )( 
            IBasicVideo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pDestinationTop);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DestinationHeight )( 
            IBasicVideo __RPC_FAR * This,
            /* [in] */ long DestinationHeight);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DestinationHeight )( 
            IBasicVideo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pDestinationHeight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSourcePosition )( 
            IBasicVideo __RPC_FAR * This,
            /* [in] */ long Left,
            /* [in] */ long Top,
            /* [in] */ long Width,
            /* [in] */ long Height);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourcePosition )( 
            IBasicVideo __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pLeft,
            /* [out] */ long __RPC_FAR *pTop,
            /* [out] */ long __RPC_FAR *pWidth,
            /* [out] */ long __RPC_FAR *pHeight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDefaultSourcePosition )( 
            IBasicVideo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDestinationPosition )( 
            IBasicVideo __RPC_FAR * This,
            /* [in] */ long Left,
            /* [in] */ long Top,
            /* [in] */ long Width,
            /* [in] */ long Height);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDestinationPosition )( 
            IBasicVideo __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pLeft,
            /* [out] */ long __RPC_FAR *pTop,
            /* [out] */ long __RPC_FAR *pWidth,
            /* [out] */ long __RPC_FAR *pHeight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDefaultDestinationPosition )( 
            IBasicVideo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVideoSize )( 
            IBasicVideo __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pWidth,
            /* [out] */ long __RPC_FAR *pHeight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVideoPaletteEntries )( 
            IBasicVideo __RPC_FAR * This,
            /* [in] */ long StartIndex,
            /* [in] */ long Entries,
            /* [out] */ long __RPC_FAR *pRetrieved,
            /* [out] */ long __RPC_FAR *pPalette);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCurrentImage )( 
            IBasicVideo __RPC_FAR * This,
            /* [out][in] */ long __RPC_FAR *pBufferSize,
            /* [out] */ long __RPC_FAR *pDIBImage);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsUsingDefaultSource )( 
            IBasicVideo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsUsingDefaultDestination )( 
            IBasicVideo __RPC_FAR * This);
        
        END_INTERFACE
    } IBasicVideoVtbl;

    interface IBasicVideo
    {
        CONST_VTBL struct IBasicVideoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBasicVideo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBasicVideo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBasicVideo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBasicVideo_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IBasicVideo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IBasicVideo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IBasicVideo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IBasicVideo_get_AvgTimePerFrame(This,pAvgTimePerFrame)	\
    (This)->lpVtbl -> get_AvgTimePerFrame(This,pAvgTimePerFrame)

#define IBasicVideo_get_BitRate(This,pBitRate)	\
    (This)->lpVtbl -> get_BitRate(This,pBitRate)

#define IBasicVideo_get_BitErrorRate(This,pBitErrorRate)	\
    (This)->lpVtbl -> get_BitErrorRate(This,pBitErrorRate)

#define IBasicVideo_get_VideoWidth(This,pVideoWidth)	\
    (This)->lpVtbl -> get_VideoWidth(This,pVideoWidth)

#define IBasicVideo_get_VideoHeight(This,pVideoHeight)	\
    (This)->lpVtbl -> get_VideoHeight(This,pVideoHeight)

#define IBasicVideo_put_SourceLeft(This,SourceLeft)	\
    (This)->lpVtbl -> put_SourceLeft(This,SourceLeft)

#define IBasicVideo_get_SourceLeft(This,pSourceLeft)	\
    (This)->lpVtbl -> get_SourceLeft(This,pSourceLeft)

#define IBasicVideo_put_SourceWidth(This,SourceWidth)	\
    (This)->lpVtbl -> put_SourceWidth(This,SourceWidth)

#define IBasicVideo_get_SourceWidth(This,pSourceWidth)	\
    (This)->lpVtbl -> get_SourceWidth(This,pSourceWidth)

#define IBasicVideo_put_SourceTop(This,SourceTop)	\
    (This)->lpVtbl -> put_SourceTop(This,SourceTop)

#define IBasicVideo_get_SourceTop(This,pSourceTop)	\
    (This)->lpVtbl -> get_SourceTop(This,pSourceTop)

#define IBasicVideo_put_SourceHeight(This,SourceHeight)	\
    (This)->lpVtbl -> put_SourceHeight(This,SourceHeight)

#define IBasicVideo_get_SourceHeight(This,pSourceHeight)	\
    (This)->lpVtbl -> get_SourceHeight(This,pSourceHeight)

#define IBasicVideo_put_DestinationLeft(This,DestinationLeft)	\
    (This)->lpVtbl -> put_DestinationLeft(This,DestinationLeft)

#define IBasicVideo_get_DestinationLeft(This,pDestinationLeft)	\
    (This)->lpVtbl -> get_DestinationLeft(This,pDestinationLeft)

#define IBasicVideo_put_DestinationWidth(This,DestinationWidth)	\
    (This)->lpVtbl -> put_DestinationWidth(This,DestinationWidth)

#define IBasicVideo_get_DestinationWidth(This,pDestinationWidth)	\
    (This)->lpVtbl -> get_DestinationWidth(This,pDestinationWidth)

#define IBasicVideo_put_DestinationTop(This,DestinationTop)	\
    (This)->lpVtbl -> put_DestinationTop(This,DestinationTop)

#define IBasicVideo_get_DestinationTop(This,pDestinationTop)	\
    (This)->lpVtbl -> get_DestinationTop(This,pDestinationTop)

#define IBasicVideo_put_DestinationHeight(This,DestinationHeight)	\
    (This)->lpVtbl -> put_DestinationHeight(This,DestinationHeight)

#define IBasicVideo_get_DestinationHeight(This,pDestinationHeight)	\
    (This)->lpVtbl -> get_DestinationHeight(This,pDestinationHeight)

#define IBasicVideo_SetSourcePosition(This,Left,Top,Width,Height)	\
    (This)->lpVtbl -> SetSourcePosition(This,Left,Top,Width,Height)

#define IBasicVideo_GetSourcePosition(This,pLeft,pTop,pWidth,pHeight)	\
    (This)->lpVtbl -> GetSourcePosition(This,pLeft,pTop,pWidth,pHeight)

#define IBasicVideo_SetDefaultSourcePosition(This)	\
    (This)->lpVtbl -> SetDefaultSourcePosition(This)

#define IBasicVideo_SetDestinationPosition(This,Left,Top,Width,Height)	\
    (This)->lpVtbl -> SetDestinationPosition(This,Left,Top,Width,Height)

#define IBasicVideo_GetDestinationPosition(This,pLeft,pTop,pWidth,pHeight)	\
    (This)->lpVtbl -> GetDestinationPosition(This,pLeft,pTop,pWidth,pHeight)

#define IBasicVideo_SetDefaultDestinationPosition(This)	\
    (This)->lpVtbl -> SetDefaultDestinationPosition(This)

#define IBasicVideo_GetVideoSize(This,pWidth,pHeight)	\
    (This)->lpVtbl -> GetVideoSize(This,pWidth,pHeight)

#define IBasicVideo_GetVideoPaletteEntries(This,StartIndex,Entries,pRetrieved,pPalette)	\
    (This)->lpVtbl -> GetVideoPaletteEntries(This,StartIndex,Entries,pRetrieved,pPalette)

#define IBasicVideo_GetCurrentImage(This,pBufferSize,pDIBImage)	\
    (This)->lpVtbl -> GetCurrentImage(This,pBufferSize,pDIBImage)

#define IBasicVideo_IsUsingDefaultSource(This)	\
    (This)->lpVtbl -> IsUsingDefaultSource(This)

#define IBasicVideo_IsUsingDefaultDestination(This)	\
    (This)->lpVtbl -> IsUsingDefaultDestination(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IBasicVideo_get_AvgTimePerFrame_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [retval][out] */ REFTIME __RPC_FAR *pAvgTimePerFrame);


void __RPC_STUB IBasicVideo_get_AvgTimePerFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IBasicVideo_get_BitRate_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pBitRate);


void __RPC_STUB IBasicVideo_get_BitRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IBasicVideo_get_BitErrorRate_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pBitErrorRate);


void __RPC_STUB IBasicVideo_get_BitErrorRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IBasicVideo_get_VideoWidth_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVideoWidth);


void __RPC_STUB IBasicVideo_get_VideoWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IBasicVideo_get_VideoHeight_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVideoHeight);


void __RPC_STUB IBasicVideo_get_VideoHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IBasicVideo_put_SourceLeft_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [in] */ long SourceLeft);


void __RPC_STUB IBasicVideo_put_SourceLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IBasicVideo_get_SourceLeft_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pSourceLeft);


void __RPC_STUB IBasicVideo_get_SourceLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IBasicVideo_put_SourceWidth_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [in] */ long SourceWidth);


void __RPC_STUB IBasicVideo_put_SourceWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IBasicVideo_get_SourceWidth_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pSourceWidth);


void __RPC_STUB IBasicVideo_get_SourceWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IBasicVideo_put_SourceTop_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [in] */ long SourceTop);


void __RPC_STUB IBasicVideo_put_SourceTop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IBasicVideo_get_SourceTop_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pSourceTop);


void __RPC_STUB IBasicVideo_get_SourceTop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IBasicVideo_put_SourceHeight_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [in] */ long SourceHeight);


void __RPC_STUB IBasicVideo_put_SourceHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IBasicVideo_get_SourceHeight_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pSourceHeight);


void __RPC_STUB IBasicVideo_get_SourceHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IBasicVideo_put_DestinationLeft_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [in] */ long DestinationLeft);


void __RPC_STUB IBasicVideo_put_DestinationLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IBasicVideo_get_DestinationLeft_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pDestinationLeft);


void __RPC_STUB IBasicVideo_get_DestinationLeft_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IBasicVideo_put_DestinationWidth_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [in] */ long DestinationWidth);


void __RPC_STUB IBasicVideo_put_DestinationWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IBasicVideo_get_DestinationWidth_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pDestinationWidth);


void __RPC_STUB IBasicVideo_get_DestinationWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IBasicVideo_put_DestinationTop_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [in] */ long DestinationTop);


void __RPC_STUB IBasicVideo_put_DestinationTop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IBasicVideo_get_DestinationTop_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pDestinationTop);


void __RPC_STUB IBasicVideo_get_DestinationTop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IBasicVideo_put_DestinationHeight_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [in] */ long DestinationHeight);


void __RPC_STUB IBasicVideo_put_DestinationHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IBasicVideo_get_DestinationHeight_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pDestinationHeight);


void __RPC_STUB IBasicVideo_get_DestinationHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBasicVideo_SetSourcePosition_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [in] */ long Left,
    /* [in] */ long Top,
    /* [in] */ long Width,
    /* [in] */ long Height);


void __RPC_STUB IBasicVideo_SetSourcePosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBasicVideo_GetSourcePosition_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pLeft,
    /* [out] */ long __RPC_FAR *pTop,
    /* [out] */ long __RPC_FAR *pWidth,
    /* [out] */ long __RPC_FAR *pHeight);


void __RPC_STUB IBasicVideo_GetSourcePosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBasicVideo_SetDefaultSourcePosition_Proxy( 
    IBasicVideo __RPC_FAR * This);


void __RPC_STUB IBasicVideo_SetDefaultSourcePosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBasicVideo_SetDestinationPosition_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [in] */ long Left,
    /* [in] */ long Top,
    /* [in] */ long Width,
    /* [in] */ long Height);


void __RPC_STUB IBasicVideo_SetDestinationPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBasicVideo_GetDestinationPosition_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pLeft,
    /* [out] */ long __RPC_FAR *pTop,
    /* [out] */ long __RPC_FAR *pWidth,
    /* [out] */ long __RPC_FAR *pHeight);


void __RPC_STUB IBasicVideo_GetDestinationPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBasicVideo_SetDefaultDestinationPosition_Proxy( 
    IBasicVideo __RPC_FAR * This);


void __RPC_STUB IBasicVideo_SetDefaultDestinationPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBasicVideo_GetVideoSize_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pWidth,
    /* [out] */ long __RPC_FAR *pHeight);


void __RPC_STUB IBasicVideo_GetVideoSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBasicVideo_GetVideoPaletteEntries_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [in] */ long StartIndex,
    /* [in] */ long Entries,
    /* [out] */ long __RPC_FAR *pRetrieved,
    /* [out] */ long __RPC_FAR *pPalette);


void __RPC_STUB IBasicVideo_GetVideoPaletteEntries_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBasicVideo_GetCurrentImage_Proxy( 
    IBasicVideo __RPC_FAR * This,
    /* [out][in] */ long __RPC_FAR *pBufferSize,
    /* [out] */ long __RPC_FAR *pDIBImage);


void __RPC_STUB IBasicVideo_GetCurrentImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBasicVideo_IsUsingDefaultSource_Proxy( 
    IBasicVideo __RPC_FAR * This);


void __RPC_STUB IBasicVideo_IsUsingDefaultSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IBasicVideo_IsUsingDefaultDestination_Proxy( 
    IBasicVideo __RPC_FAR * This);


void __RPC_STUB IBasicVideo_IsUsingDefaultDestination_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBasicVideo_INTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_FilgraphManager,0xe436ebb3,0x524f,0x11ce,0x9f,0x53,0x00,0x20,0xaf,0x0b,0xa7,0x70);

#ifdef __cplusplus

class DECLSPEC_UUID("e436ebb3-524f-11ce-9f53-0020af0ba770")
FilgraphManager;
#endif
#endif /* __QuartzTypeLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
