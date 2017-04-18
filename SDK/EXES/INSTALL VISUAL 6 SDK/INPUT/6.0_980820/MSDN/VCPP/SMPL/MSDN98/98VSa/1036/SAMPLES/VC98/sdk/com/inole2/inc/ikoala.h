#include "rpc.h"
#include "rpcndr.h"

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


#include "unknwn.h"
void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IKoala_INTERFACE_DEFINED__
#define __IKoala_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IKoala
 * at Mon May 01 08:28:33 1995
 * using MIDL 2.00.72
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_IKoala;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IKoala : public IUnknown
    {
    public:
        virtual HRESULT __stdcall ClimbEucalyptusTree( 
            /* [in] */ short iTree) = 0;
        
        virtual HRESULT __stdcall PouchOpensDown( void) = 0;
        
        virtual HRESULT __stdcall SleepAfterEating( 
            /* [in] */ short cMinutes) = 0;
        
    };
    
#else 	/* C style interface */
    
    typedef struct IKoalaVtbl
    {
        
        HRESULT ( __stdcall __RPC_FAR *QueryInterface )( 
            IKoala __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( __stdcall __RPC_FAR *AddRef )( 
            IKoala __RPC_FAR * This);
        
        ULONG ( __stdcall __RPC_FAR *Release )( 
            IKoala __RPC_FAR * This);
        
        HRESULT ( __stdcall __RPC_FAR *ClimbEucalyptusTree )( 
            IKoala __RPC_FAR * This,
            /* [in] */ short iTree);
        
        HRESULT ( __stdcall __RPC_FAR *PouchOpensDown )( 
            IKoala __RPC_FAR * This);
        
        HRESULT ( __stdcall __RPC_FAR *SleepAfterEating )( 
            IKoala __RPC_FAR * This,
            /* [in] */ short cMinutes);
        
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



HRESULT __stdcall IKoala_ClimbEucalyptusTree_Proxy( 
    IKoala __RPC_FAR * This,
    /* [in] */ short iTree);


void __RPC_STUB IKoala_ClimbEucalyptusTree_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT __stdcall IKoala_PouchOpensDown_Proxy( 
    IKoala __RPC_FAR * This);


void __RPC_STUB IKoala_PouchOpensDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT __stdcall IKoala_SleepAfterEating_Proxy( 
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
