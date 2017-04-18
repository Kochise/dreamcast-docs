/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 02:26:31 1998
 */
/* Compiler settings for frhost.idl:
    Os (OptLev=s), W1, Zp4, env=Win32, ms_ext, c_ext
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

#ifndef __frhost_h__
#define __frhost_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IFractalHost_FWD_DEFINED__
#define __IFractalHost_FWD_DEFINED__
typedef interface IFractalHost IFractalHost;
#endif 	/* __IFractalHost_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IFractalHost_INTERFACE_DEFINED__
#define __IFractalHost_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IFractalHost
 * at Mon Mar 30 02:26:31 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IFractalHost;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2a0e4ef4-3908-101b-8963-00000b65c75b")
    IFractalHost : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetGraphSize( 
            unsigned int uWidth,
            unsigned int uHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGraphSize( 
            unsigned int __RPC_FAR *puWidth,
            unsigned int __RPC_FAR *puHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPoint( 
            unsigned int __RPC_FAR *puColor,
            int x,
            int y) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Rect( 
            int iLeft,
            int iTop,
            int iRight,
            int iBottom,
            unsigned int uColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Line( 
            int x1,
            int y1,
            int x2,
            int y2,
            unsigned int uColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Point( 
            int x,
            int y,
            unsigned int uColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DoneDrawingGraph( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFractalHostVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFractalHost __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFractalHost __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFractalHost __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGraphSize )( 
            IFractalHost __RPC_FAR * This,
            unsigned int uWidth,
            unsigned int uHeight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGraphSize )( 
            IFractalHost __RPC_FAR * This,
            unsigned int __RPC_FAR *puWidth,
            unsigned int __RPC_FAR *puHeight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPoint )( 
            IFractalHost __RPC_FAR * This,
            unsigned int __RPC_FAR *puColor,
            int x,
            int y);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Rect )( 
            IFractalHost __RPC_FAR * This,
            int iLeft,
            int iTop,
            int iRight,
            int iBottom,
            unsigned int uColor);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Line )( 
            IFractalHost __RPC_FAR * This,
            int x1,
            int y1,
            int x2,
            int y2,
            unsigned int uColor);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Point )( 
            IFractalHost __RPC_FAR * This,
            int x,
            int y,
            unsigned int uColor);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DoneDrawingGraph )( 
            IFractalHost __RPC_FAR * This);
        
        END_INTERFACE
    } IFractalHostVtbl;

    interface IFractalHost
    {
        CONST_VTBL struct IFractalHostVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFractalHost_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFractalHost_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFractalHost_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFractalHost_SetGraphSize(This,uWidth,uHeight)	\
    (This)->lpVtbl -> SetGraphSize(This,uWidth,uHeight)

#define IFractalHost_GetGraphSize(This,puWidth,puHeight)	\
    (This)->lpVtbl -> GetGraphSize(This,puWidth,puHeight)

#define IFractalHost_GetPoint(This,puColor,x,y)	\
    (This)->lpVtbl -> GetPoint(This,puColor,x,y)

#define IFractalHost_Rect(This,iLeft,iTop,iRight,iBottom,uColor)	\
    (This)->lpVtbl -> Rect(This,iLeft,iTop,iRight,iBottom,uColor)

#define IFractalHost_Line(This,x1,y1,x2,y2,uColor)	\
    (This)->lpVtbl -> Line(This,x1,y1,x2,y2,uColor)

#define IFractalHost_Point(This,x,y,uColor)	\
    (This)->lpVtbl -> Point(This,x,y,uColor)

#define IFractalHost_DoneDrawingGraph(This)	\
    (This)->lpVtbl -> DoneDrawingGraph(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFractalHost_SetGraphSize_Proxy( 
    IFractalHost __RPC_FAR * This,
    unsigned int uWidth,
    unsigned int uHeight);


void __RPC_STUB IFractalHost_SetGraphSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFractalHost_GetGraphSize_Proxy( 
    IFractalHost __RPC_FAR * This,
    unsigned int __RPC_FAR *puWidth,
    unsigned int __RPC_FAR *puHeight);


void __RPC_STUB IFractalHost_GetGraphSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFractalHost_GetPoint_Proxy( 
    IFractalHost __RPC_FAR * This,
    unsigned int __RPC_FAR *puColor,
    int x,
    int y);


void __RPC_STUB IFractalHost_GetPoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFractalHost_Rect_Proxy( 
    IFractalHost __RPC_FAR * This,
    int iLeft,
    int iTop,
    int iRight,
    int iBottom,
    unsigned int uColor);


void __RPC_STUB IFractalHost_Rect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFractalHost_Line_Proxy( 
    IFractalHost __RPC_FAR * This,
    int x1,
    int y1,
    int x2,
    int y2,
    unsigned int uColor);


void __RPC_STUB IFractalHost_Line_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFractalHost_Point_Proxy( 
    IFractalHost __RPC_FAR * This,
    int x,
    int y,
    unsigned int uColor);


void __RPC_STUB IFractalHost_Point_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFractalHost_DoneDrawingGraph_Proxy( 
    IFractalHost __RPC_FAR * This);


void __RPC_STUB IFractalHost_DoneDrawingGraph_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFractalHost_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
