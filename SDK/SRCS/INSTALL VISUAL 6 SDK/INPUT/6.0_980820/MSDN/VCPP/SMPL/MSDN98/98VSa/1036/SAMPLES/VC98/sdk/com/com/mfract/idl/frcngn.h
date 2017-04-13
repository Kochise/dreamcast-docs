/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 02:26:29 1998
 */
/* Compiler settings for frcngn.idl:
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

#ifndef __frcngn_h__
#define __frcngn_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IFractalEngine_FWD_DEFINED__
#define __IFractalEngine_FWD_DEFINED__
typedef interface IFractalEngine IFractalEngine;
#endif 	/* __IFractalEngine_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "frhost.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IFractalEngine_INTERFACE_DEFINED__
#define __IFractalEngine_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IFractalEngine
 * at Mon Mar 30 02:26:29 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IFractalEngine;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2a0e4f58-3908-101b-8963-00000b65c75b")
    IFractalEngine : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Init( 
            IFractalHost __RPC_FAR *pfh) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDefaults( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetProperties( 
            HWND hwnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetExtent( 
            double __RPC_FAR *pdLeft,
            double __RPC_FAR *pdTop,
            double __RPC_FAR *pdRight,
            double __RPC_FAR *pdBottom) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetExtent( 
            double dLeft,
            double dTop,
            double dRight,
            double dBottom) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetGraphSize( 
            unsigned int uWidth,
            unsigned int uHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Start( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFractalEngineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFractalEngine __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFractalEngine __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFractalEngine __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            IFractalEngine __RPC_FAR * This,
            IFractalHost __RPC_FAR *pfh);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDefaults )( 
            IFractalEngine __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetProperties )( 
            IFractalEngine __RPC_FAR * This,
            HWND hwnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetExtent )( 
            IFractalEngine __RPC_FAR * This,
            double __RPC_FAR *pdLeft,
            double __RPC_FAR *pdTop,
            double __RPC_FAR *pdRight,
            double __RPC_FAR *pdBottom);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetExtent )( 
            IFractalEngine __RPC_FAR * This,
            double dLeft,
            double dTop,
            double dRight,
            double dBottom);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGraphSize )( 
            IFractalEngine __RPC_FAR * This,
            unsigned int uWidth,
            unsigned int uHeight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Start )( 
            IFractalEngine __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IFractalEngine __RPC_FAR * This);
        
        END_INTERFACE
    } IFractalEngineVtbl;

    interface IFractalEngine
    {
        CONST_VTBL struct IFractalEngineVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFractalEngine_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFractalEngine_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFractalEngine_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFractalEngine_Init(This,pfh)	\
    (This)->lpVtbl -> Init(This,pfh)

#define IFractalEngine_SetDefaults(This)	\
    (This)->lpVtbl -> SetDefaults(This)

#define IFractalEngine_SetProperties(This,hwnd)	\
    (This)->lpVtbl -> SetProperties(This,hwnd)

#define IFractalEngine_GetExtent(This,pdLeft,pdTop,pdRight,pdBottom)	\
    (This)->lpVtbl -> GetExtent(This,pdLeft,pdTop,pdRight,pdBottom)

#define IFractalEngine_SetExtent(This,dLeft,dTop,dRight,dBottom)	\
    (This)->lpVtbl -> SetExtent(This,dLeft,dTop,dRight,dBottom)

#define IFractalEngine_SetGraphSize(This,uWidth,uHeight)	\
    (This)->lpVtbl -> SetGraphSize(This,uWidth,uHeight)

#define IFractalEngine_Start(This)	\
    (This)->lpVtbl -> Start(This)

#define IFractalEngine_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IFractalEngine_Init_Proxy( 
    IFractalEngine __RPC_FAR * This,
    IFractalHost __RPC_FAR *pfh);


void __RPC_STUB IFractalEngine_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFractalEngine_SetDefaults_Proxy( 
    IFractalEngine __RPC_FAR * This);


void __RPC_STUB IFractalEngine_SetDefaults_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFractalEngine_SetProperties_Proxy( 
    IFractalEngine __RPC_FAR * This,
    HWND hwnd);


void __RPC_STUB IFractalEngine_SetProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFractalEngine_GetExtent_Proxy( 
    IFractalEngine __RPC_FAR * This,
    double __RPC_FAR *pdLeft,
    double __RPC_FAR *pdTop,
    double __RPC_FAR *pdRight,
    double __RPC_FAR *pdBottom);


void __RPC_STUB IFractalEngine_GetExtent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFractalEngine_SetExtent_Proxy( 
    IFractalEngine __RPC_FAR * This,
    double dLeft,
    double dTop,
    double dRight,
    double dBottom);


void __RPC_STUB IFractalEngine_SetExtent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFractalEngine_SetGraphSize_Proxy( 
    IFractalEngine __RPC_FAR * This,
    unsigned int uWidth,
    unsigned int uHeight);


void __RPC_STUB IFractalEngine_SetGraphSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFractalEngine_Start_Proxy( 
    IFractalEngine __RPC_FAR * This);


void __RPC_STUB IFractalEngine_Start_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IFractalEngine_Stop_Proxy( 
    IFractalEngine __RPC_FAR * This);


void __RPC_STUB IFractalEngine_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFractalEngine_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
