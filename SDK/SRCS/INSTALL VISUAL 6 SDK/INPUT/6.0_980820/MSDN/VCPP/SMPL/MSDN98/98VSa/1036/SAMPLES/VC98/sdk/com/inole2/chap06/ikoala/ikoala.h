/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:48:23 1998
 */
/* Compiler settings for ikoala.idl:
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

#ifndef __ikoala_h__
#define __ikoala_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IKoala_FWD_DEFINED__
#define __IKoala_FWD_DEFINED__
typedef interface IKoala IKoala;
#endif 	/* __IKoala_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IKoala_INTERFACE_DEFINED__
#define __IKoala_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IKoala
 * at Mon Mar 30 03:48:23 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_IKoala;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0002114b-0000-0000-c000-000000000046")
    IKoala : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ClimbEucalyptusTree( 
            /* [in] */ short iTree) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PouchOpensDown( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SleepAfterEating( 
            /* [in] */ short cMinutes) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IKoalaVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IKoala __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IKoala __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IKoala __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClimbEucalyptusTree )( 
            IKoala __RPC_FAR * This,
            /* [in] */ short iTree);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PouchOpensDown )( 
            IKoala __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SleepAfterEating )( 
            IKoala __RPC_FAR * This,
            /* [in] */ short cMinutes);
        
        END_INTERFACE
    } IKoalaVtbl;

    interface IKoala
    {
        CONST_VTBL struct IKoalaVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IKoala_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IKoala_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IKoala_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IKoala_ClimbEucalyptusTree(This,iTree)	\
    (This)->lpVtbl -> ClimbEucalyptusTree(This,iTree)

#define IKoala_PouchOpensDown(This)	\
    (This)->lpVtbl -> PouchOpensDown(This)

#define IKoala_SleepAfterEating(This,cMinutes)	\
    (This)->lpVtbl -> SleepAfterEating(This,cMinutes)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IKoala_ClimbEucalyptusTree_Proxy( 
    IKoala __RPC_FAR * This,
    /* [in] */ short iTree);


void __RPC_STUB IKoala_ClimbEucalyptusTree_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKoala_PouchOpensDown_Proxy( 
    IKoala __RPC_FAR * This);


void __RPC_STUB IKoala_PouchOpensDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IKoala_SleepAfterEating_Proxy( 
    IKoala __RPC_FAR * This,
    /* [in] */ short cMinutes);


void __RPC_STUB IKoala_SleepAfterEating_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IKoala_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
