/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:39:58 1998
 */
/* Compiler settings for papint.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, app_config, c_ext
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

#ifndef __papint_h__
#define __papint_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISharePaper_FWD_DEFINED__
#define __ISharePaper_FWD_DEFINED__
typedef interface ISharePaper ISharePaper;
#endif 	/* __ISharePaper_FWD_DEFINED__ */


#ifndef __IPaperSink_FWD_DEFINED__
#define __IPaperSink_FWD_DEFINED__
typedef interface IPaperSink IPaperSink;
#endif 	/* __IPaperSink_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISharePaper_INTERFACE_DEFINED__
#define __ISharePaper_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ISharePaper
 * at Mon Mar 30 03:39:58 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_ISharePaper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0002da31-0000-0000-c000-000000000046")
    ISharePaper : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE InitPaper( 
            /* [out][in] */ RECT __RPC_FAR *pWinRect,
            /* [out] */ BOOL __RPC_FAR *pbFirst) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Lock( 
            /* [in] */ BOOL bLock) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Load( 
            /* [out] */ RECT __RPC_FAR *pWinRect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Save( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InkStart( 
            /* [in] */ SHORT nX,
            /* [in] */ SHORT nY,
            /* [in] */ SHORT nInkWidth,
            /* [in] */ COLORREF crInkColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InkDraw( 
            /* [in] */ SHORT nX,
            /* [in] */ SHORT nY) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InkStop( 
            /* [in] */ SHORT nX,
            /* [in] */ SHORT nY) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInk( 
            /* [in] */ LONG lIndex,
            /* [out] */ SHORT __RPC_FAR *pnInkType,
            /* [out] */ SHORT __RPC_FAR *pnX,
            /* [out] */ SHORT __RPC_FAR *pnY,
            /* [out] */ SHORT __RPC_FAR *pnInkWidth,
            /* [out] */ COLORREF __RPC_FAR *pcrInkColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Erase( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Resize( 
            /* [in] */ LONG lWidth,
            /* [in] */ LONG lHeight) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISharePaperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISharePaper __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISharePaper __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISharePaper __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InitPaper )( 
            ISharePaper __RPC_FAR * This,
            /* [out][in] */ RECT __RPC_FAR *pWinRect,
            /* [out] */ BOOL __RPC_FAR *pbFirst);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Lock )( 
            ISharePaper __RPC_FAR * This,
            /* [in] */ BOOL bLock);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Load )( 
            ISharePaper __RPC_FAR * This,
            /* [out] */ RECT __RPC_FAR *pWinRect);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            ISharePaper __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InkStart )( 
            ISharePaper __RPC_FAR * This,
            /* [in] */ SHORT nX,
            /* [in] */ SHORT nY,
            /* [in] */ SHORT nInkWidth,
            /* [in] */ COLORREF crInkColor);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InkDraw )( 
            ISharePaper __RPC_FAR * This,
            /* [in] */ SHORT nX,
            /* [in] */ SHORT nY);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InkStop )( 
            ISharePaper __RPC_FAR * This,
            /* [in] */ SHORT nX,
            /* [in] */ SHORT nY);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInk )( 
            ISharePaper __RPC_FAR * This,
            /* [in] */ LONG lIndex,
            /* [out] */ SHORT __RPC_FAR *pnInkType,
            /* [out] */ SHORT __RPC_FAR *pnX,
            /* [out] */ SHORT __RPC_FAR *pnY,
            /* [out] */ SHORT __RPC_FAR *pnInkWidth,
            /* [out] */ COLORREF __RPC_FAR *pcrInkColor);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Erase )( 
            ISharePaper __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Resize )( 
            ISharePaper __RPC_FAR * This,
            /* [in] */ LONG lWidth,
            /* [in] */ LONG lHeight);
        
        END_INTERFACE
    } ISharePaperVtbl;

    interface ISharePaper
    {
        CONST_VTBL struct ISharePaperVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISharePaper_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISharePaper_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISharePaper_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISharePaper_InitPaper(This,pWinRect,pbFirst)	\
    (This)->lpVtbl -> InitPaper(This,pWinRect,pbFirst)

#define ISharePaper_Lock(This,bLock)	\
    (This)->lpVtbl -> Lock(This,bLock)

#define ISharePaper_Load(This,pWinRect)	\
    (This)->lpVtbl -> Load(This,pWinRect)

#define ISharePaper_Save(This)	\
    (This)->lpVtbl -> Save(This)

#define ISharePaper_InkStart(This,nX,nY,nInkWidth,crInkColor)	\
    (This)->lpVtbl -> InkStart(This,nX,nY,nInkWidth,crInkColor)

#define ISharePaper_InkDraw(This,nX,nY)	\
    (This)->lpVtbl -> InkDraw(This,nX,nY)

#define ISharePaper_InkStop(This,nX,nY)	\
    (This)->lpVtbl -> InkStop(This,nX,nY)

#define ISharePaper_GetInk(This,lIndex,pnInkType,pnX,pnY,pnInkWidth,pcrInkColor)	\
    (This)->lpVtbl -> GetInk(This,lIndex,pnInkType,pnX,pnY,pnInkWidth,pcrInkColor)

#define ISharePaper_Erase(This)	\
    (This)->lpVtbl -> Erase(This)

#define ISharePaper_Resize(This,lWidth,lHeight)	\
    (This)->lpVtbl -> Resize(This,lWidth,lHeight)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISharePaper_InitPaper_Proxy( 
    ISharePaper __RPC_FAR * This,
    /* [out][in] */ RECT __RPC_FAR *pWinRect,
    /* [out] */ BOOL __RPC_FAR *pbFirst);


void __RPC_STUB ISharePaper_InitPaper_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISharePaper_Lock_Proxy( 
    ISharePaper __RPC_FAR * This,
    /* [in] */ BOOL bLock);


void __RPC_STUB ISharePaper_Lock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISharePaper_Load_Proxy( 
    ISharePaper __RPC_FAR * This,
    /* [out] */ RECT __RPC_FAR *pWinRect);


void __RPC_STUB ISharePaper_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISharePaper_Save_Proxy( 
    ISharePaper __RPC_FAR * This);


void __RPC_STUB ISharePaper_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISharePaper_InkStart_Proxy( 
    ISharePaper __RPC_FAR * This,
    /* [in] */ SHORT nX,
    /* [in] */ SHORT nY,
    /* [in] */ SHORT nInkWidth,
    /* [in] */ COLORREF crInkColor);


void __RPC_STUB ISharePaper_InkStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISharePaper_InkDraw_Proxy( 
    ISharePaper __RPC_FAR * This,
    /* [in] */ SHORT nX,
    /* [in] */ SHORT nY);


void __RPC_STUB ISharePaper_InkDraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISharePaper_InkStop_Proxy( 
    ISharePaper __RPC_FAR * This,
    /* [in] */ SHORT nX,
    /* [in] */ SHORT nY);


void __RPC_STUB ISharePaper_InkStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISharePaper_GetInk_Proxy( 
    ISharePaper __RPC_FAR * This,
    /* [in] */ LONG lIndex,
    /* [out] */ SHORT __RPC_FAR *pnInkType,
    /* [out] */ SHORT __RPC_FAR *pnX,
    /* [out] */ SHORT __RPC_FAR *pnY,
    /* [out] */ SHORT __RPC_FAR *pnInkWidth,
    /* [out] */ COLORREF __RPC_FAR *pcrInkColor);


void __RPC_STUB ISharePaper_GetInk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISharePaper_Erase_Proxy( 
    ISharePaper __RPC_FAR * This);


void __RPC_STUB ISharePaper_Erase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISharePaper_Resize_Proxy( 
    ISharePaper __RPC_FAR * This,
    /* [in] */ LONG lWidth,
    /* [in] */ LONG lHeight);


void __RPC_STUB ISharePaper_Resize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISharePaper_INTERFACE_DEFINED__ */


#ifndef __IPaperSink_INTERFACE_DEFINED__
#define __IPaperSink_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IPaperSink
 * at Mon Mar 30 03:39:58 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_IPaperSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0002da34-0000-0000-c000-000000000046")
    IPaperSink : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Locked( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Unlocked( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Loaded( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Saved( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InkStart( 
            /* [in] */ SHORT nX,
            /* [in] */ SHORT nY,
            /* [in] */ SHORT nInkWidth,
            /* [in] */ COLORREF crInkColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InkDraw( 
            /* [in] */ SHORT nX,
            /* [in] */ SHORT nY) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InkStop( 
            /* [in] */ SHORT nX,
            /* [in] */ SHORT nY) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Erased( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Resized( 
            /* [in] */ LONG lWidth,
            /* [in] */ LONG lHeight) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPaperSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPaperSink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPaperSink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPaperSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Locked )( 
            IPaperSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Unlocked )( 
            IPaperSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Loaded )( 
            IPaperSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Saved )( 
            IPaperSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InkStart )( 
            IPaperSink __RPC_FAR * This,
            /* [in] */ SHORT nX,
            /* [in] */ SHORT nY,
            /* [in] */ SHORT nInkWidth,
            /* [in] */ COLORREF crInkColor);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InkDraw )( 
            IPaperSink __RPC_FAR * This,
            /* [in] */ SHORT nX,
            /* [in] */ SHORT nY);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InkStop )( 
            IPaperSink __RPC_FAR * This,
            /* [in] */ SHORT nX,
            /* [in] */ SHORT nY);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Erased )( 
            IPaperSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Resized )( 
            IPaperSink __RPC_FAR * This,
            /* [in] */ LONG lWidth,
            /* [in] */ LONG lHeight);
        
        END_INTERFACE
    } IPaperSinkVtbl;

    interface IPaperSink
    {
        CONST_VTBL struct IPaperSinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPaperSink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPaperSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPaperSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPaperSink_Locked(This)	\
    (This)->lpVtbl -> Locked(This)

#define IPaperSink_Unlocked(This)	\
    (This)->lpVtbl -> Unlocked(This)

#define IPaperSink_Loaded(This)	\
    (This)->lpVtbl -> Loaded(This)

#define IPaperSink_Saved(This)	\
    (This)->lpVtbl -> Saved(This)

#define IPaperSink_InkStart(This,nX,nY,nInkWidth,crInkColor)	\
    (This)->lpVtbl -> InkStart(This,nX,nY,nInkWidth,crInkColor)

#define IPaperSink_InkDraw(This,nX,nY)	\
    (This)->lpVtbl -> InkDraw(This,nX,nY)

#define IPaperSink_InkStop(This,nX,nY)	\
    (This)->lpVtbl -> InkStop(This,nX,nY)

#define IPaperSink_Erased(This)	\
    (This)->lpVtbl -> Erased(This)

#define IPaperSink_Resized(This,lWidth,lHeight)	\
    (This)->lpVtbl -> Resized(This,lWidth,lHeight)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPaperSink_Locked_Proxy( 
    IPaperSink __RPC_FAR * This);


void __RPC_STUB IPaperSink_Locked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPaperSink_Unlocked_Proxy( 
    IPaperSink __RPC_FAR * This);


void __RPC_STUB IPaperSink_Unlocked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPaperSink_Loaded_Proxy( 
    IPaperSink __RPC_FAR * This);


void __RPC_STUB IPaperSink_Loaded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPaperSink_Saved_Proxy( 
    IPaperSink __RPC_FAR * This);


void __RPC_STUB IPaperSink_Saved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPaperSink_InkStart_Proxy( 
    IPaperSink __RPC_FAR * This,
    /* [in] */ SHORT nX,
    /* [in] */ SHORT nY,
    /* [in] */ SHORT nInkWidth,
    /* [in] */ COLORREF crInkColor);


void __RPC_STUB IPaperSink_InkStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPaperSink_InkDraw_Proxy( 
    IPaperSink __RPC_FAR * This,
    /* [in] */ SHORT nX,
    /* [in] */ SHORT nY);


void __RPC_STUB IPaperSink_InkDraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPaperSink_InkStop_Proxy( 
    IPaperSink __RPC_FAR * This,
    /* [in] */ SHORT nX,
    /* [in] */ SHORT nY);


void __RPC_STUB IPaperSink_InkStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPaperSink_Erased_Proxy( 
    IPaperSink __RPC_FAR * This);


void __RPC_STUB IPaperSink_Erased_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPaperSink_Resized_Proxy( 
    IPaperSink __RPC_FAR * This,
    /* [in] */ LONG lWidth,
    /* [in] */ LONG lHeight);


void __RPC_STUB IPaperSink_Resized_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPaperSink_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_papint_0008
 * at Mon Mar 30 03:39:58 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


// The types of Ink Data.
#define INKTYPE_NONE  0
#define INKTYPE_START 1
#define INKTYPE_DRAW  2
#define INKTYPE_STOP  3


extern RPC_IF_HANDLE __MIDL_itf_papint_0008_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_papint_0008_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
