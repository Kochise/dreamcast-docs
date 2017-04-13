/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.00.44 */
/* at Wed Nov 06 19:30:10 1996
 */
/* Compiler settings for iball.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"
#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __iball_h__
#define __iball_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IBall_FWD_DEFINED__
#define __IBall_FWD_DEFINED__
typedef interface IBall IBall;
#endif  /* __IBall_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IBall_INTERFACE_DEFINED__
#define __IBall_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IBall
 * at Wed Nov 06 19:30:10 1996
 * using MIDL 3.00.44
 ****************************************/
/* [unique][helpstring][uuid][object] */ 



EXTERN_C const IID IID_IBall;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IBall : public IUnknown
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Ball( 
            /* [out] */ POINT __RPC_FAR *pOrg,
            /* [out] */ POINT __RPC_FAR *pExt,
            /* [retval][out] */ COLORREF __RPC_FAR *pcrColor) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Reset( 
            /* [in] */ RECT __RPC_FAR *pNewRect,
            /* [in] */ short nBallSize) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ BOOL bAlive,
            /* [retval][out] */ BOOL __RPC_FAR *bRet) = 0;
        
    };
    
#else   /* C style interface */

    typedef struct IBallVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBall __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBall __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBall __RPC_FAR * This);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Ball )( 
            IBall __RPC_FAR * This,
            /* [out] */ POINT __RPC_FAR *pOrg,
            /* [out] */ POINT __RPC_FAR *pExt,
            /* [retval][out] */ COLORREF __RPC_FAR *pcrColor);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IBall __RPC_FAR * This,
            /* [in] */ RECT __RPC_FAR *pNewRect,
            /* [in] */ short nBallSize);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            IBall __RPC_FAR * This,
            /* [in] */ BOOL bAlive,
            /* [retval][out] */ BOOL __RPC_FAR *bRet);
        
        END_INTERFACE
    } IBallVtbl;

    interface IBall
    {
        CONST_VTBL struct IBallVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBall_QueryInterface(This,riid,ppvObject)   \
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBall_AddRef(This)  \
    (This)->lpVtbl -> AddRef(This)

#define IBall_Release(This) \
    (This)->lpVtbl -> Release(This)


#define IBall_get_Ball(This,pOrg,pExt,pcrColor) \
    (This)->lpVtbl -> get_Ball(This,pOrg,pExt,pcrColor)

#define IBall_Reset(This,pNewRect,nBallSize)    \
    (This)->lpVtbl -> Reset(This,pNewRect,nBallSize)

#define IBall_Move(This,bAlive,bRet)    \
    (This)->lpVtbl -> Move(This,bAlive,bRet)

#endif /* COBJMACROS */


#endif  /* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IBall_get_Ball_Proxy( 
    IBall __RPC_FAR * This,
    /* [out] */ POINT __RPC_FAR *pOrg,
    /* [out] */ POINT __RPC_FAR *pExt,
    /* [retval][out] */ COLORREF __RPC_FAR *pcrColor);


void __RPC_STUB IBall_get_Ball_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IBall_Reset_Proxy( 
    IBall __RPC_FAR * This,
    /* [in] */ RECT __RPC_FAR *pNewRect,
    /* [in] */ short nBallSize);


void __RPC_STUB IBall_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IBall_Move_Proxy( 
    IBall __RPC_FAR * This,
    /* [in] */ BOOL bAlive,
    /* [retval][out] */ BOOL __RPC_FAR *bRet);


void __RPC_STUB IBall_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif  /* __IBall_INTERFACE_DEFINED__ */



#ifndef __BallLib_LIBRARY_DEFINED__
#define __BallLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: BallLib
 * at Wed Nov 06 19:30:10 1996
 * using MIDL 3.00.44
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_BallLib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Ball;

class Ball;
#endif
#endif /* __BallLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
