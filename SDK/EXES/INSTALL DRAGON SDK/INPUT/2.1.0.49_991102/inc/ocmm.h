/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.02.88 */
/* at Wed Dec 01 20:54:47 1999
 */
/* Compiler settings for .\ocmm.idl:
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

#ifndef __ocmm_h__
#define __ocmm_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IViewFilter_FWD_DEFINED__
#define __IViewFilter_FWD_DEFINED__
typedef interface IViewFilter IViewFilter;
#endif 	/* __IViewFilter_FWD_DEFINED__ */


#ifndef __IViewTransition_FWD_DEFINED__
#define __IViewTransition_FWD_DEFINED__
typedef interface IViewTransition IViewTransition;
#endif 	/* __IViewTransition_FWD_DEFINED__ */


#ifndef __IViewFilterSite_FWD_DEFINED__
#define __IViewFilterSite_FWD_DEFINED__
typedef interface IViewFilterSite IViewFilterSite;
#endif 	/* __IViewFilterSite_FWD_DEFINED__ */


#ifndef __IViewTransitionSite_FWD_DEFINED__
#define __IViewTransitionSite_FWD_DEFINED__
typedef interface IViewTransitionSite IViewTransitionSite;
#endif 	/* __IViewTransitionSite_FWD_DEFINED__ */


#ifndef __ITimerService_FWD_DEFINED__
#define __ITimerService_FWD_DEFINED__
typedef interface ITimerService ITimerService;
#endif 	/* __ITimerService_FWD_DEFINED__ */


#ifndef __ITimer_FWD_DEFINED__
#define __ITimer_FWD_DEFINED__
typedef interface ITimer ITimer;
#endif 	/* __ITimer_FWD_DEFINED__ */


#ifndef __ITimerSink_FWD_DEFINED__
#define __ITimerSink_FWD_DEFINED__
typedef interface ITimerSink ITimerSink;
#endif 	/* __ITimerSink_FWD_DEFINED__ */


#ifndef __IMapMIMEToCLSID_FWD_DEFINED__
#define __IMapMIMEToCLSID_FWD_DEFINED__
typedef interface IMapMIMEToCLSID IMapMIMEToCLSID;
#endif 	/* __IMapMIMEToCLSID_FWD_DEFINED__ */


#ifndef __IImageDecodeFilter_FWD_DEFINED__
#define __IImageDecodeFilter_FWD_DEFINED__
typedef interface IImageDecodeFilter IImageDecodeFilter;
#endif 	/* __IImageDecodeFilter_FWD_DEFINED__ */


#ifndef __IImageDecodeEventSink_FWD_DEFINED__
#define __IImageDecodeEventSink_FWD_DEFINED__
typedef interface IImageDecodeEventSink IImageDecodeEventSink;
#endif 	/* __IImageDecodeEventSink_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "oleidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_ocmm_0000
 * at Wed Dec 01 20:54:47 1999
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 




// GetStatusBits Flags
#define FILTER_STATUS_OPAQUE    (0x00000001)
#define FILTER_STATUS_INVISIBLE (0x00000002)
#define FILTER_STATUS_SURFACE   (0x00000004)
#define FILTER_STATUS_3DSURFACE (0x00000008)


extern RPC_IF_HANDLE __MIDL_itf_ocmm_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ocmm_0000_v0_0_s_ifspec;

#ifndef __IViewFilter_INTERFACE_DEFINED__
#define __IViewFilter_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IViewFilter
 * at Wed Dec 01 20:54:47 1999
 * using MIDL 3.02.88
 ****************************************/
/* [local][unique][uuid][object] */ 



EXTERN_C const IID IID_IViewFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("3050f2f1-98b5-11cf-bb82-00aa00bdce0b")
    IViewFilter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetSource( 
            /* [in] */ IViewFilter __RPC_FAR *pFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSource( 
            /* [out] */ IViewFilter __RPC_FAR *__RPC_FAR *ppFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSite( 
            /* [in] */ IViewFilterSite __RPC_FAR *pSink) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSite( 
            /* [out] */ IViewFilterSite __RPC_FAR *__RPC_FAR *ppSink) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPosition( 
            LPCRECT prc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Draw( 
            /* [in] */ HDC hdc,
            /* [in] */ LPCRECT prcBounds) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStatusBits( 
            /* [out] */ DWORD __RPC_FAR *pdwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IViewFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IViewFilter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IViewFilter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IViewFilter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSource )( 
            IViewFilter __RPC_FAR * This,
            /* [in] */ IViewFilter __RPC_FAR *pFilter);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSource )( 
            IViewFilter __RPC_FAR * This,
            /* [out] */ IViewFilter __RPC_FAR *__RPC_FAR *ppFilter);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSite )( 
            IViewFilter __RPC_FAR * This,
            /* [in] */ IViewFilterSite __RPC_FAR *pSink);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSite )( 
            IViewFilter __RPC_FAR * This,
            /* [out] */ IViewFilterSite __RPC_FAR *__RPC_FAR *ppSink);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPosition )( 
            IViewFilter __RPC_FAR * This,
            LPCRECT prc);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Draw )( 
            IViewFilter __RPC_FAR * This,
            /* [in] */ HDC hdc,
            /* [in] */ LPCRECT prcBounds);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStatusBits )( 
            IViewFilter __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwFlags);
        
        END_INTERFACE
    } IViewFilterVtbl;

    interface IViewFilter
    {
        CONST_VTBL struct IViewFilterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IViewFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IViewFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IViewFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IViewFilter_SetSource(This,pFilter)	\
    (This)->lpVtbl -> SetSource(This,pFilter)

#define IViewFilter_GetSource(This,ppFilter)	\
    (This)->lpVtbl -> GetSource(This,ppFilter)

#define IViewFilter_SetSite(This,pSink)	\
    (This)->lpVtbl -> SetSite(This,pSink)

#define IViewFilter_GetSite(This,ppSink)	\
    (This)->lpVtbl -> GetSite(This,ppSink)

#define IViewFilter_SetPosition(This,prc)	\
    (This)->lpVtbl -> SetPosition(This,prc)

#define IViewFilter_Draw(This,hdc,prcBounds)	\
    (This)->lpVtbl -> Draw(This,hdc,prcBounds)

#define IViewFilter_GetStatusBits(This,pdwFlags)	\
    (This)->lpVtbl -> GetStatusBits(This,pdwFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IViewFilter_SetSource_Proxy( 
    IViewFilter __RPC_FAR * This,
    /* [in] */ IViewFilter __RPC_FAR *pFilter);


void __RPC_STUB IViewFilter_SetSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IViewFilter_GetSource_Proxy( 
    IViewFilter __RPC_FAR * This,
    /* [out] */ IViewFilter __RPC_FAR *__RPC_FAR *ppFilter);


void __RPC_STUB IViewFilter_GetSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IViewFilter_SetSite_Proxy( 
    IViewFilter __RPC_FAR * This,
    /* [in] */ IViewFilterSite __RPC_FAR *pSink);


void __RPC_STUB IViewFilter_SetSite_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IViewFilter_GetSite_Proxy( 
    IViewFilter __RPC_FAR * This,
    /* [out] */ IViewFilterSite __RPC_FAR *__RPC_FAR *ppSink);


void __RPC_STUB IViewFilter_GetSite_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IViewFilter_SetPosition_Proxy( 
    IViewFilter __RPC_FAR * This,
    LPCRECT prc);


void __RPC_STUB IViewFilter_SetPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IViewFilter_Draw_Proxy( 
    IViewFilter __RPC_FAR * This,
    /* [in] */ HDC hdc,
    /* [in] */ LPCRECT prcBounds);


void __RPC_STUB IViewFilter_Draw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IViewFilter_GetStatusBits_Proxy( 
    IViewFilter __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwFlags);


void __RPC_STUB IViewFilter_GetStatusBits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IViewFilter_INTERFACE_DEFINED__ */


#ifndef __IViewTransition_INTERFACE_DEFINED__
#define __IViewTransition_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IViewTransition
 * at Wed Dec 01 20:54:47 1999
 * using MIDL 3.02.88
 ****************************************/
/* [local][unique][uuid][object] */ 



EXTERN_C const IID IID_IViewTransition;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("3050f372-98b5-11cf-bb82-00aa00bdce0b")
    IViewTransition : public IViewFilter
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ HDC __MIDL_0016,
            LPCRECT prc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Go( 
            /* [in] */ VARIANT vtimeDuration) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IViewTransitionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IViewTransition __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IViewTransition __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IViewTransition __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSource )( 
            IViewTransition __RPC_FAR * This,
            /* [in] */ IViewFilter __RPC_FAR *pFilter);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSource )( 
            IViewTransition __RPC_FAR * This,
            /* [out] */ IViewFilter __RPC_FAR *__RPC_FAR *ppFilter);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSite )( 
            IViewTransition __RPC_FAR * This,
            /* [in] */ IViewFilterSite __RPC_FAR *pSink);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSite )( 
            IViewTransition __RPC_FAR * This,
            /* [out] */ IViewFilterSite __RPC_FAR *__RPC_FAR *ppSink);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPosition )( 
            IViewTransition __RPC_FAR * This,
            LPCRECT prc);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Draw )( 
            IViewTransition __RPC_FAR * This,
            /* [in] */ HDC hdc,
            /* [in] */ LPCRECT prcBounds);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStatusBits )( 
            IViewTransition __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IViewTransition __RPC_FAR * This,
            /* [in] */ HDC __MIDL_0016,
            LPCRECT prc);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Go )( 
            IViewTransition __RPC_FAR * This,
            /* [in] */ VARIANT vtimeDuration);
        
        END_INTERFACE
    } IViewTransitionVtbl;

    interface IViewTransition
    {
        CONST_VTBL struct IViewTransitionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IViewTransition_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IViewTransition_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IViewTransition_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IViewTransition_SetSource(This,pFilter)	\
    (This)->lpVtbl -> SetSource(This,pFilter)

#define IViewTransition_GetSource(This,ppFilter)	\
    (This)->lpVtbl -> GetSource(This,ppFilter)

#define IViewTransition_SetSite(This,pSink)	\
    (This)->lpVtbl -> SetSite(This,pSink)

#define IViewTransition_GetSite(This,ppSink)	\
    (This)->lpVtbl -> GetSite(This,ppSink)

#define IViewTransition_SetPosition(This,prc)	\
    (This)->lpVtbl -> SetPosition(This,prc)

#define IViewTransition_Draw(This,hdc,prcBounds)	\
    (This)->lpVtbl -> Draw(This,hdc,prcBounds)

#define IViewTransition_GetStatusBits(This,pdwFlags)	\
    (This)->lpVtbl -> GetStatusBits(This,pdwFlags)


#define IViewTransition_Initialize(This,__MIDL_0016,prc)	\
    (This)->lpVtbl -> Initialize(This,__MIDL_0016,prc)

#define IViewTransition_Go(This,vtimeDuration)	\
    (This)->lpVtbl -> Go(This,vtimeDuration)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IViewTransition_Initialize_Proxy( 
    IViewTransition __RPC_FAR * This,
    /* [in] */ HDC __MIDL_0016,
    LPCRECT prc);


void __RPC_STUB IViewTransition_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IViewTransition_Go_Proxy( 
    IViewTransition __RPC_FAR * This,
    /* [in] */ VARIANT vtimeDuration);


void __RPC_STUB IViewTransition_Go_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IViewTransition_INTERFACE_DEFINED__ */


#ifndef __IViewFilterSite_INTERFACE_DEFINED__
#define __IViewFilterSite_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IViewFilterSite
 * at Wed Dec 01 20:54:47 1999
 * using MIDL 3.02.88
 ****************************************/
/* [local][unique][uuid][object] */ 



EXTERN_C const IID IID_IViewFilterSite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("3050f2f4-98b5-11cf-bb82-00aa00bdce0b")
    IViewFilterSite : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDC( 
            /* [in] */ LPCRECT prc,
            /* [in] */ DWORD dwFlags,
            /* [out] */ HDC __RPC_FAR *phdc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReleaseDC( 
            /* [in] */ HDC hdc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InvalidateRect( 
            /* [in] */ LPCRECT prc,
            /* [in] */ BOOL fErase) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InvalidateRgn( 
            /* [in] */ HRGN hrgn,
            /* [in] */ BOOL fErase) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnStatusBitsChange( 
            /* [in] */ DWORD dwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IViewFilterSiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IViewFilterSite __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IViewFilterSite __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IViewFilterSite __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDC )( 
            IViewFilterSite __RPC_FAR * This,
            /* [in] */ LPCRECT prc,
            /* [in] */ DWORD dwFlags,
            /* [out] */ HDC __RPC_FAR *phdc);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseDC )( 
            IViewFilterSite __RPC_FAR * This,
            /* [in] */ HDC hdc);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvalidateRect )( 
            IViewFilterSite __RPC_FAR * This,
            /* [in] */ LPCRECT prc,
            /* [in] */ BOOL fErase);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvalidateRgn )( 
            IViewFilterSite __RPC_FAR * This,
            /* [in] */ HRGN hrgn,
            /* [in] */ BOOL fErase);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnStatusBitsChange )( 
            IViewFilterSite __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        END_INTERFACE
    } IViewFilterSiteVtbl;

    interface IViewFilterSite
    {
        CONST_VTBL struct IViewFilterSiteVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IViewFilterSite_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IViewFilterSite_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IViewFilterSite_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IViewFilterSite_GetDC(This,prc,dwFlags,phdc)	\
    (This)->lpVtbl -> GetDC(This,prc,dwFlags,phdc)

#define IViewFilterSite_ReleaseDC(This,hdc)	\
    (This)->lpVtbl -> ReleaseDC(This,hdc)

#define IViewFilterSite_InvalidateRect(This,prc,fErase)	\
    (This)->lpVtbl -> InvalidateRect(This,prc,fErase)

#define IViewFilterSite_InvalidateRgn(This,hrgn,fErase)	\
    (This)->lpVtbl -> InvalidateRgn(This,hrgn,fErase)

#define IViewFilterSite_OnStatusBitsChange(This,dwFlags)	\
    (This)->lpVtbl -> OnStatusBitsChange(This,dwFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IViewFilterSite_GetDC_Proxy( 
    IViewFilterSite __RPC_FAR * This,
    /* [in] */ LPCRECT prc,
    /* [in] */ DWORD dwFlags,
    /* [out] */ HDC __RPC_FAR *phdc);


void __RPC_STUB IViewFilterSite_GetDC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IViewFilterSite_ReleaseDC_Proxy( 
    IViewFilterSite __RPC_FAR * This,
    /* [in] */ HDC hdc);


void __RPC_STUB IViewFilterSite_ReleaseDC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IViewFilterSite_InvalidateRect_Proxy( 
    IViewFilterSite __RPC_FAR * This,
    /* [in] */ LPCRECT prc,
    /* [in] */ BOOL fErase);


void __RPC_STUB IViewFilterSite_InvalidateRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IViewFilterSite_InvalidateRgn_Proxy( 
    IViewFilterSite __RPC_FAR * This,
    /* [in] */ HRGN hrgn,
    /* [in] */ BOOL fErase);


void __RPC_STUB IViewFilterSite_InvalidateRgn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IViewFilterSite_OnStatusBitsChange_Proxy( 
    IViewFilterSite __RPC_FAR * This,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IViewFilterSite_OnStatusBitsChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IViewFilterSite_INTERFACE_DEFINED__ */


#ifndef __IViewTransitionSite_INTERFACE_DEFINED__
#define __IViewTransitionSite_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IViewTransitionSite
 * at Wed Dec 01 20:54:47 1999
 * using MIDL 3.02.88
 ****************************************/
/* [local][unique][uuid][object] */ 



EXTERN_C const IID IID_IViewTransitionSite;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("3050f373-98b5-11cf-bb82-00aa00bdce0b")
    IViewTransitionSite : public IViewFilterSite
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnComplete( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IViewTransitionSiteVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IViewTransitionSite __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IViewTransitionSite __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IViewTransitionSite __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDC )( 
            IViewTransitionSite __RPC_FAR * This,
            /* [in] */ LPCRECT prc,
            /* [in] */ DWORD dwFlags,
            /* [out] */ HDC __RPC_FAR *phdc);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseDC )( 
            IViewTransitionSite __RPC_FAR * This,
            /* [in] */ HDC hdc);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvalidateRect )( 
            IViewTransitionSite __RPC_FAR * This,
            /* [in] */ LPCRECT prc,
            /* [in] */ BOOL fErase);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvalidateRgn )( 
            IViewTransitionSite __RPC_FAR * This,
            /* [in] */ HRGN hrgn,
            /* [in] */ BOOL fErase);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnStatusBitsChange )( 
            IViewTransitionSite __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnComplete )( 
            IViewTransitionSite __RPC_FAR * This);
        
        END_INTERFACE
    } IViewTransitionSiteVtbl;

    interface IViewTransitionSite
    {
        CONST_VTBL struct IViewTransitionSiteVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IViewTransitionSite_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IViewTransitionSite_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IViewTransitionSite_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IViewTransitionSite_GetDC(This,prc,dwFlags,phdc)	\
    (This)->lpVtbl -> GetDC(This,prc,dwFlags,phdc)

#define IViewTransitionSite_ReleaseDC(This,hdc)	\
    (This)->lpVtbl -> ReleaseDC(This,hdc)

#define IViewTransitionSite_InvalidateRect(This,prc,fErase)	\
    (This)->lpVtbl -> InvalidateRect(This,prc,fErase)

#define IViewTransitionSite_InvalidateRgn(This,hrgn,fErase)	\
    (This)->lpVtbl -> InvalidateRgn(This,hrgn,fErase)

#define IViewTransitionSite_OnStatusBitsChange(This,dwFlags)	\
    (This)->lpVtbl -> OnStatusBitsChange(This,dwFlags)


#define IViewTransitionSite_OnComplete(This)	\
    (This)->lpVtbl -> OnComplete(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IViewTransitionSite_OnComplete_Proxy( 
    IViewTransitionSite __RPC_FAR * This);


void __RPC_STUB IViewTransitionSite_OnComplete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IViewTransitionSite_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_ocmm_0099
 * at Wed Dec 01 20:54:47 1999
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


#define SURFACE_LOCK_EXCLUSIVE        0x01
#define SURFACE_LOCK_ALLOW_DISCARD    0x02
#define SURFACE_LOCK_WAIT             0x04

#define E_SURFACE_NOSURFACE             0x8000C000L
#define E_SURFACE_UNKNOWN_FORMAT        0x8000C001L
#define E_SURFACE_NOTMYPOINTER          0x8000C002L
#define E_SURFACE_DISCARDED             0x8000C003L
#define E_SURFACE_NODC                  0x8000C004L
#define E_SURFACE_NOTMYDC               0x8000C005L
#define S_SURFACE_DISCARDED             0x0000C003L

typedef GUID BFID;

typedef struct tagRGBQUAD RGBQUAD;

EXTERN_C const GUID BFID_MONOCHROME;
EXTERN_C const GUID BFID_RGB_4;
EXTERN_C const GUID BFID_RGB_8;
EXTERN_C const GUID BFID_RGB_555;
EXTERN_C const GUID BFID_RGB_565;
EXTERN_C const GUID BFID_RGB_24;
EXTERN_C const GUID BFID_RGB_32;
EXTERN_C const GUID BFID_RGBA_32;
EXTERN_C const GUID BFID_GRAY_8;
EXTERN_C const GUID BFID_GRAY_16;

#define SID_SDirectDraw3 IID_IDirectDraw3

#define COLOR_NO_TRANSPARENT 0xFFFFFFFF

#define IMGDECODE_EVENT_PROGRESS 0x01
#define IMGDECODE_EVENT_PALETTE 0x02
#define IMGDECODE_EVENT_BEGINBITS 0x04
#define IMGDECODE_EVENT_BITSCOMPLETE 0x08
#define IMGDECODE_EVENT_USEDDRAW 0x10

#define IMGDECODE_HINT_TOPDOWN 0x01
#define IMGDECODE_HINT_BOTTOMUP 0x02
#define IMGDECODE_HINT_FULLWIDTH 0x04

#define MAPMIME_DEFAULT 0
#define MAPMIME_CLSID 1
#define MAPMIME_DISABLE 2
#define MAPMIME_DEFAULT_ALWAYS 3

#define BFID_INDEXED_RGB_8 BFID_RGB_8
#define BFID_INDEXED_RGB_4 BFID_RGB_4
#define BFID_INDEXED_RGB_1 BFID_MONOCHROME

EXTERN_C const GUID CLSID_IImageDecodeFilter;

EXTERN_C const GUID NAMEDTIMER_DRAW;






extern RPC_IF_HANDLE __MIDL_itf_ocmm_0099_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ocmm_0099_v0_0_s_ifspec;

#ifndef __ITimerService_INTERFACE_DEFINED__
#define __ITimerService_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITimerService
 * at Wed Dec 01 20:54:47 1999
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_ITimerService;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("3050f35f-98b5-11cf-bb82-00aa00bdce0b")
    ITimerService : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateTimer( 
            /* [in] */ ITimer __RPC_FAR *pReferenceTimer,
            /* [out] */ ITimer __RPC_FAR *__RPC_FAR *ppNewTimer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNamedTimer( 
            /* [in] */ REFGUID rguidName,
            /* [out] */ ITimer __RPC_FAR *__RPC_FAR *ppTimer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetNamedTimerReference( 
            /* [in] */ REFGUID rguidName,
            /* [in] */ ITimer __RPC_FAR *pReferenceTimer) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITimerServiceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITimerService __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITimerService __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITimerService __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateTimer )( 
            ITimerService __RPC_FAR * This,
            /* [in] */ ITimer __RPC_FAR *pReferenceTimer,
            /* [out] */ ITimer __RPC_FAR *__RPC_FAR *ppNewTimer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNamedTimer )( 
            ITimerService __RPC_FAR * This,
            /* [in] */ REFGUID rguidName,
            /* [out] */ ITimer __RPC_FAR *__RPC_FAR *ppTimer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetNamedTimerReference )( 
            ITimerService __RPC_FAR * This,
            /* [in] */ REFGUID rguidName,
            /* [in] */ ITimer __RPC_FAR *pReferenceTimer);
        
        END_INTERFACE
    } ITimerServiceVtbl;

    interface ITimerService
    {
        CONST_VTBL struct ITimerServiceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITimerService_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITimerService_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITimerService_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITimerService_CreateTimer(This,pReferenceTimer,ppNewTimer)	\
    (This)->lpVtbl -> CreateTimer(This,pReferenceTimer,ppNewTimer)

#define ITimerService_GetNamedTimer(This,rguidName,ppTimer)	\
    (This)->lpVtbl -> GetNamedTimer(This,rguidName,ppTimer)

#define ITimerService_SetNamedTimerReference(This,rguidName,pReferenceTimer)	\
    (This)->lpVtbl -> SetNamedTimerReference(This,rguidName,pReferenceTimer)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITimerService_CreateTimer_Proxy( 
    ITimerService __RPC_FAR * This,
    /* [in] */ ITimer __RPC_FAR *pReferenceTimer,
    /* [out] */ ITimer __RPC_FAR *__RPC_FAR *ppNewTimer);


void __RPC_STUB ITimerService_CreateTimer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITimerService_GetNamedTimer_Proxy( 
    ITimerService __RPC_FAR * This,
    /* [in] */ REFGUID rguidName,
    /* [out] */ ITimer __RPC_FAR *__RPC_FAR *ppTimer);


void __RPC_STUB ITimerService_GetNamedTimer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITimerService_SetNamedTimerReference_Proxy( 
    ITimerService __RPC_FAR * This,
    /* [in] */ REFGUID rguidName,
    /* [in] */ ITimer __RPC_FAR *pReferenceTimer);


void __RPC_STUB ITimerService_SetNamedTimerReference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITimerService_INTERFACE_DEFINED__ */


#ifndef __ITimer_INTERFACE_DEFINED__
#define __ITimer_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITimer
 * at Wed Dec 01 20:54:47 1999
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_ITimer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("3050f360-98b5-11cf-bb82-00aa00bdce0b")
    ITimer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Advise( 
            /* [in] */ VARIANT vtimeMin,
            /* [in] */ VARIANT vtimeMax,
            /* [in] */ VARIANT vtimeInterval,
            /* [in] */ DWORD dwFlags,
            /* [in] */ ITimerSink __RPC_FAR *pTimerSink,
            /* [out] */ DWORD __RPC_FAR *pdwCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Unadvise( 
            /* [in] */ DWORD dwCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Freeze( 
            /* [in] */ BOOL fFreeze) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTime( 
            /* [out] */ VARIANT __RPC_FAR *pvtime) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITimerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITimer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITimer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITimer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Advise )( 
            ITimer __RPC_FAR * This,
            /* [in] */ VARIANT vtimeMin,
            /* [in] */ VARIANT vtimeMax,
            /* [in] */ VARIANT vtimeInterval,
            /* [in] */ DWORD dwFlags,
            /* [in] */ ITimerSink __RPC_FAR *pTimerSink,
            /* [out] */ DWORD __RPC_FAR *pdwCookie);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Unadvise )( 
            ITimer __RPC_FAR * This,
            /* [in] */ DWORD dwCookie);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Freeze )( 
            ITimer __RPC_FAR * This,
            /* [in] */ BOOL fFreeze);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTime )( 
            ITimer __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pvtime);
        
        END_INTERFACE
    } ITimerVtbl;

    interface ITimer
    {
        CONST_VTBL struct ITimerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITimer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITimer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITimer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITimer_Advise(This,vtimeMin,vtimeMax,vtimeInterval,dwFlags,pTimerSink,pdwCookie)	\
    (This)->lpVtbl -> Advise(This,vtimeMin,vtimeMax,vtimeInterval,dwFlags,pTimerSink,pdwCookie)

#define ITimer_Unadvise(This,dwCookie)	\
    (This)->lpVtbl -> Unadvise(This,dwCookie)

#define ITimer_Freeze(This,fFreeze)	\
    (This)->lpVtbl -> Freeze(This,fFreeze)

#define ITimer_GetTime(This,pvtime)	\
    (This)->lpVtbl -> GetTime(This,pvtime)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITimer_Advise_Proxy( 
    ITimer __RPC_FAR * This,
    /* [in] */ VARIANT vtimeMin,
    /* [in] */ VARIANT vtimeMax,
    /* [in] */ VARIANT vtimeInterval,
    /* [in] */ DWORD dwFlags,
    /* [in] */ ITimerSink __RPC_FAR *pTimerSink,
    /* [out] */ DWORD __RPC_FAR *pdwCookie);


void __RPC_STUB ITimer_Advise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITimer_Unadvise_Proxy( 
    ITimer __RPC_FAR * This,
    /* [in] */ DWORD dwCookie);


void __RPC_STUB ITimer_Unadvise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITimer_Freeze_Proxy( 
    ITimer __RPC_FAR * This,
    /* [in] */ BOOL fFreeze);


void __RPC_STUB ITimer_Freeze_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITimer_GetTime_Proxy( 
    ITimer __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pvtime);


void __RPC_STUB ITimer_GetTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITimer_INTERFACE_DEFINED__ */


#ifndef __ITimerSink_INTERFACE_DEFINED__
#define __ITimerSink_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITimerSink
 * at Wed Dec 01 20:54:47 1999
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_ITimerSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("3050f361-98b5-11cf-bb82-00aa00bdce0b")
    ITimerSink : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnTimer( 
            /* [in] */ VARIANT vtimeAdvise) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITimerSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITimerSink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITimerSink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITimerSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnTimer )( 
            ITimerSink __RPC_FAR * This,
            /* [in] */ VARIANT vtimeAdvise);
        
        END_INTERFACE
    } ITimerSinkVtbl;

    interface ITimerSink
    {
        CONST_VTBL struct ITimerSinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITimerSink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITimerSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITimerSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITimerSink_OnTimer(This,vtimeAdvise)	\
    (This)->lpVtbl -> OnTimer(This,vtimeAdvise)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITimerSink_OnTimer_Proxy( 
    ITimerSink __RPC_FAR * This,
    /* [in] */ VARIANT vtimeAdvise);


void __RPC_STUB ITimerSink_OnTimer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITimerSink_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_ocmm_0102
 * at Wed Dec 01 20:54:47 1999
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


#define SID_STimerService IID_ITimerService






extern RPC_IF_HANDLE __MIDL_itf_ocmm_0102_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ocmm_0102_v0_0_s_ifspec;

#ifndef __IMapMIMEToCLSID_INTERFACE_DEFINED__
#define __IMapMIMEToCLSID_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMapMIMEToCLSID
 * at Wed Dec 01 20:54:47 1999
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IMapMIMEToCLSID;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("D9E89500-30FA-11d0-B724-00AA006C1A01")
    IMapMIMEToCLSID : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE EnableDefaultMappings( 
            BOOL bEnable) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MapMIMEToCLSID( 
            LPCOLESTR pszMIMEType,
            CLSID __RPC_FAR *pCLSID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMapping( 
            LPCOLESTR pszMIMEType,
            DWORD dwMapMode,
            REFCLSID clsid) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMapMIMEToCLSIDVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMapMIMEToCLSID __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMapMIMEToCLSID __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMapMIMEToCLSID __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableDefaultMappings )( 
            IMapMIMEToCLSID __RPC_FAR * This,
            BOOL bEnable);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MapMIMEToCLSID )( 
            IMapMIMEToCLSID __RPC_FAR * This,
            LPCOLESTR pszMIMEType,
            CLSID __RPC_FAR *pCLSID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMapping )( 
            IMapMIMEToCLSID __RPC_FAR * This,
            LPCOLESTR pszMIMEType,
            DWORD dwMapMode,
            REFCLSID clsid);
        
        END_INTERFACE
    } IMapMIMEToCLSIDVtbl;

    interface IMapMIMEToCLSID
    {
        CONST_VTBL struct IMapMIMEToCLSIDVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMapMIMEToCLSID_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMapMIMEToCLSID_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMapMIMEToCLSID_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMapMIMEToCLSID_EnableDefaultMappings(This,bEnable)	\
    (This)->lpVtbl -> EnableDefaultMappings(This,bEnable)

#define IMapMIMEToCLSID_MapMIMEToCLSID(This,pszMIMEType,pCLSID)	\
    (This)->lpVtbl -> MapMIMEToCLSID(This,pszMIMEType,pCLSID)

#define IMapMIMEToCLSID_SetMapping(This,pszMIMEType,dwMapMode,clsid)	\
    (This)->lpVtbl -> SetMapping(This,pszMIMEType,dwMapMode,clsid)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMapMIMEToCLSID_EnableDefaultMappings_Proxy( 
    IMapMIMEToCLSID __RPC_FAR * This,
    BOOL bEnable);


void __RPC_STUB IMapMIMEToCLSID_EnableDefaultMappings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMapMIMEToCLSID_MapMIMEToCLSID_Proxy( 
    IMapMIMEToCLSID __RPC_FAR * This,
    LPCOLESTR pszMIMEType,
    CLSID __RPC_FAR *pCLSID);


void __RPC_STUB IMapMIMEToCLSID_MapMIMEToCLSID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMapMIMEToCLSID_SetMapping_Proxy( 
    IMapMIMEToCLSID __RPC_FAR * This,
    LPCOLESTR pszMIMEType,
    DWORD dwMapMode,
    REFCLSID clsid);


void __RPC_STUB IMapMIMEToCLSID_SetMapping_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMapMIMEToCLSID_INTERFACE_DEFINED__ */


#ifndef __IImageDecodeFilter_INTERFACE_DEFINED__
#define __IImageDecodeFilter_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IImageDecodeFilter
 * at Wed Dec 01 20:54:47 1999
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IImageDecodeFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("A3CCEDF3-2DE2-11D0-86F4-00A0C913F750")
    IImageDecodeFilter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            IImageDecodeEventSink __RPC_FAR *pEventSink) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Process( 
            IStream __RPC_FAR *pStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Terminate( 
            HRESULT hrStatus) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IImageDecodeFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IImageDecodeFilter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IImageDecodeFilter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IImageDecodeFilter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IImageDecodeFilter __RPC_FAR * This,
            IImageDecodeEventSink __RPC_FAR *pEventSink);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Process )( 
            IImageDecodeFilter __RPC_FAR * This,
            IStream __RPC_FAR *pStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Terminate )( 
            IImageDecodeFilter __RPC_FAR * This,
            HRESULT hrStatus);
        
        END_INTERFACE
    } IImageDecodeFilterVtbl;

    interface IImageDecodeFilter
    {
        CONST_VTBL struct IImageDecodeFilterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IImageDecodeFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IImageDecodeFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IImageDecodeFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IImageDecodeFilter_Initialize(This,pEventSink)	\
    (This)->lpVtbl -> Initialize(This,pEventSink)

#define IImageDecodeFilter_Process(This,pStream)	\
    (This)->lpVtbl -> Process(This,pStream)

#define IImageDecodeFilter_Terminate(This,hrStatus)	\
    (This)->lpVtbl -> Terminate(This,hrStatus)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IImageDecodeFilter_Initialize_Proxy( 
    IImageDecodeFilter __RPC_FAR * This,
    IImageDecodeEventSink __RPC_FAR *pEventSink);


void __RPC_STUB IImageDecodeFilter_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageDecodeFilter_Process_Proxy( 
    IImageDecodeFilter __RPC_FAR * This,
    IStream __RPC_FAR *pStream);


void __RPC_STUB IImageDecodeFilter_Process_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageDecodeFilter_Terminate_Proxy( 
    IImageDecodeFilter __RPC_FAR * This,
    HRESULT hrStatus);


void __RPC_STUB IImageDecodeFilter_Terminate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IImageDecodeFilter_INTERFACE_DEFINED__ */


#ifndef __IImageDecodeEventSink_INTERFACE_DEFINED__
#define __IImageDecodeEventSink_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IImageDecodeEventSink
 * at Wed Dec 01 20:54:47 1999
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IImageDecodeEventSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("BAA342A0-2DED-11d0-86F4-00A0C913F750")
    IImageDecodeEventSink : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetSurface( 
            /* [in] */ LONG nWidth,
            /* [in] */ LONG nHeight,
            /* [in] */ REFGUID bfid,
            /* [in] */ ULONG nPasses,
            /* [in] */ DWORD dwHints,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSurface) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnBeginDecode( 
            /* [out] */ DWORD __RPC_FAR *pdwEvents,
            /* [out] */ ULONG __RPC_FAR *pnFormats,
            /* [size_is][size_is][out] */ BFID __RPC_FAR *__RPC_FAR *ppFormats) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnBitsComplete( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnDecodeComplete( 
            /* [in] */ HRESULT hrStatus) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnPalette( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnProgress( 
            /* [in] */ RECT __RPC_FAR *pBounds,
            /* [in] */ BOOL bComplete) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IImageDecodeEventSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IImageDecodeEventSink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IImageDecodeEventSink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IImageDecodeEventSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSurface )( 
            IImageDecodeEventSink __RPC_FAR * This,
            /* [in] */ LONG nWidth,
            /* [in] */ LONG nHeight,
            /* [in] */ REFGUID bfid,
            /* [in] */ ULONG nPasses,
            /* [in] */ DWORD dwHints,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSurface);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnBeginDecode )( 
            IImageDecodeEventSink __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwEvents,
            /* [out] */ ULONG __RPC_FAR *pnFormats,
            /* [size_is][size_is][out] */ BFID __RPC_FAR *__RPC_FAR *ppFormats);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnBitsComplete )( 
            IImageDecodeEventSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnDecodeComplete )( 
            IImageDecodeEventSink __RPC_FAR * This,
            /* [in] */ HRESULT hrStatus);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnPalette )( 
            IImageDecodeEventSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnProgress )( 
            IImageDecodeEventSink __RPC_FAR * This,
            /* [in] */ RECT __RPC_FAR *pBounds,
            /* [in] */ BOOL bComplete);
        
        END_INTERFACE
    } IImageDecodeEventSinkVtbl;

    interface IImageDecodeEventSink
    {
        CONST_VTBL struct IImageDecodeEventSinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IImageDecodeEventSink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IImageDecodeEventSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IImageDecodeEventSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IImageDecodeEventSink_GetSurface(This,nWidth,nHeight,bfid,nPasses,dwHints,ppSurface)	\
    (This)->lpVtbl -> GetSurface(This,nWidth,nHeight,bfid,nPasses,dwHints,ppSurface)

#define IImageDecodeEventSink_OnBeginDecode(This,pdwEvents,pnFormats,ppFormats)	\
    (This)->lpVtbl -> OnBeginDecode(This,pdwEvents,pnFormats,ppFormats)

#define IImageDecodeEventSink_OnBitsComplete(This)	\
    (This)->lpVtbl -> OnBitsComplete(This)

#define IImageDecodeEventSink_OnDecodeComplete(This,hrStatus)	\
    (This)->lpVtbl -> OnDecodeComplete(This,hrStatus)

#define IImageDecodeEventSink_OnPalette(This)	\
    (This)->lpVtbl -> OnPalette(This)

#define IImageDecodeEventSink_OnProgress(This,pBounds,bComplete)	\
    (This)->lpVtbl -> OnProgress(This,pBounds,bComplete)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IImageDecodeEventSink_GetSurface_Proxy( 
    IImageDecodeEventSink __RPC_FAR * This,
    /* [in] */ LONG nWidth,
    /* [in] */ LONG nHeight,
    /* [in] */ REFGUID bfid,
    /* [in] */ ULONG nPasses,
    /* [in] */ DWORD dwHints,
    /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppSurface);


void __RPC_STUB IImageDecodeEventSink_GetSurface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageDecodeEventSink_OnBeginDecode_Proxy( 
    IImageDecodeEventSink __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwEvents,
    /* [out] */ ULONG __RPC_FAR *pnFormats,
    /* [size_is][size_is][out] */ BFID __RPC_FAR *__RPC_FAR *ppFormats);


void __RPC_STUB IImageDecodeEventSink_OnBeginDecode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageDecodeEventSink_OnBitsComplete_Proxy( 
    IImageDecodeEventSink __RPC_FAR * This);


void __RPC_STUB IImageDecodeEventSink_OnBitsComplete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageDecodeEventSink_OnDecodeComplete_Proxy( 
    IImageDecodeEventSink __RPC_FAR * This,
    /* [in] */ HRESULT hrStatus);


void __RPC_STUB IImageDecodeEventSink_OnDecodeComplete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageDecodeEventSink_OnPalette_Proxy( 
    IImageDecodeEventSink __RPC_FAR * This);


void __RPC_STUB IImageDecodeEventSink_OnPalette_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IImageDecodeEventSink_OnProgress_Proxy( 
    IImageDecodeEventSink __RPC_FAR * This,
    /* [in] */ RECT __RPC_FAR *pBounds,
    /* [in] */ BOOL bComplete);


void __RPC_STUB IImageDecodeEventSink_OnProgress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IImageDecodeEventSink_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
