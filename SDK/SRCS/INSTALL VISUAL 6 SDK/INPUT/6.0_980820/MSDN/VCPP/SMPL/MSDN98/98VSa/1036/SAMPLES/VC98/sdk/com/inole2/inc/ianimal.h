#include "rpc.h"
#include "rpcndr.h"

#ifndef __ianimal_h__
#define __ianimal_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAnimal_FWD_DEFINED__
#define __IAnimal_FWD_DEFINED__
typedef interface IAnimal IAnimal;
#endif 	/* __IAnimal_FWD_DEFINED__ */


#include "unknwn.h"
void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IAnimal_INTERFACE_DEFINED__
#define __IAnimal_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAnimal
 * at Thu Apr 20 09:35:58 1995
 * using MIDL 2.00.72
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_IAnimal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IAnimal : public IUnknown
    {
    public:
        virtual HRESULT __stdcall Eat( 
            /* [in] */ LPTSTR pszFoodRecommended,
            /* [out][in] */ LPTSTR pszFoodEaten,
            /* [in] */ short cchEaten) = 0;
        
        virtual HRESULT __stdcall Sleep( 
            /* [out][in] */ short __RPC_FAR *pcMinutes) = 0;
        
        virtual HRESULT __stdcall Procreate( 
            /* [out] */ short __RPC_FAR *pcOffspring) = 0;
        
        virtual HRESULT __stdcall WhatKindOfAnimal( 
            /* [out] */ IID __RPC_FAR *pIID) = 0;
        
    };
    
#else 	/* C style interface */
    
    typedef struct IAnimalVtbl
    {
        
        HRESULT ( __stdcall __RPC_FAR *QueryInterface )( 
            IAnimal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( __stdcall __RPC_FAR *AddRef )( 
            IAnimal __RPC_FAR * This);
        
        ULONG ( __stdcall __RPC_FAR *Release )( 
            IAnimal __RPC_FAR * This);
        
        HRESULT ( __stdcall __RPC_FAR *Eat )( 
            IAnimal __RPC_FAR * This,
            /* [in] */ LPTSTR pszFoodRecommended,
            /* [out][in] */ LPTSTR pszFoodEaten,
            /* [in] */ short cchEaten);
        
        HRESULT ( __stdcall __RPC_FAR *Sleep )( 
            IAnimal __RPC_FAR * This,
            /* [out][in] */ short __RPC_FAR *pcMinutes);
        
        HRESULT ( __stdcall __RPC_FAR *Procreate )( 
            IAnimal __RPC_FAR * This,
            /* [out] */ short __RPC_FAR *pcOffspring);
        
        HRESULT ( __stdcall __RPC_FAR *WhatKindOfAnimal )( 
            IAnimal __RPC_FAR * This,
            /* [out] */ IID __RPC_FAR *pIID);
        
    } IAnimalVtbl;
    
    interface IAnimal
    {
        CONST_VTBL struct IAnimalVtbl __RPC_FAR *lpVtbl;
    };
    
    

#ifdef COBJMACROS


#define IAnimal_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAnimal_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAnimal_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAnimal_Eat(This,pszFoodRecommended,pszFoodEaten,cchEaten)	\
    (This)->lpVtbl -> Eat(This,pszFoodRecommended,pszFoodEaten,cchEaten)

#define IAnimal_Sleep(This,pcMinutes)	\
    (This)->lpVtbl -> Sleep(This,pcMinutes)

#define IAnimal_Procreate(This,pcOffspring)	\
    (This)->lpVtbl -> Procreate(This,pcOffspring)

#define IAnimal_WhatKindOfAnimal(This,pIID)	\
    (This)->lpVtbl -> WhatKindOfAnimal(This,pIID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT __stdcall IAnimal_Eat_Proxy( 
    IAnimal __RPC_FAR * This,
    /* [in] */ LPTSTR pszFoodRecommended,
    /* [out][in] */ LPTSTR pszFoodEaten,
    /* [in] */ short cchEaten);


void __RPC_STUB IAnimal_Eat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT __stdcall IAnimal_Sleep_Proxy( 
    IAnimal __RPC_FAR * This,
    /* [out][in] */ short __RPC_FAR *pcMinutes);


void __RPC_STUB IAnimal_Sleep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT __stdcall IAnimal_Procreate_Proxy( 
    IAnimal __RPC_FAR * This,
    /* [out] */ short __RPC_FAR *pcOffspring);


void __RPC_STUB IAnimal_Procreate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT __stdcall IAnimal_WhatKindOfAnimal_Proxy( 
    IAnimal __RPC_FAR * This,
    /* [out] */ IID __RPC_FAR *pIID);


void __RPC_STUB IAnimal_WhatKindOfAnimal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAnimal_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
