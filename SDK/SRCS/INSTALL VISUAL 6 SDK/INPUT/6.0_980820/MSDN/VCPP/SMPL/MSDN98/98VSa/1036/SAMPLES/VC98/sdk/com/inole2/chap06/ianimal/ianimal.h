/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:48:14 1998
 */
/* Compiler settings for ianimal.idl:
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


/* header files for imported files */
#include "unknwn.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IAnimal_INTERFACE_DEFINED__
#define __IAnimal_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAnimal
 * at Mon Mar 30 03:48:14 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][uuid] */ 



EXTERN_C const IID IID_IAnimal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0002114a-0000-0000-c000-000000000046")
    IAnimal : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Eat( 
            /* [in] */ LPTSTR pszFoodRecommended,
            /* [out][in] */ LPTSTR pszFoodEaten,
            /* [in] */ short cchEaten) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Sleep( 
            /* [out][in] */ short __RPC_FAR *pcMinutes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Procreate( 
            /* [out] */ short __RPC_FAR *pcOffspring) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WhatKindOfAnimal( 
            /* [out] */ IID __RPC_FAR *pIID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAnimalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAnimal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAnimal __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAnimal __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Eat )( 
            IAnimal __RPC_FAR * This,
            /* [in] */ LPTSTR pszFoodRecommended,
            /* [out][in] */ LPTSTR pszFoodEaten,
            /* [in] */ short cchEaten);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Sleep )( 
            IAnimal __RPC_FAR * This,
            /* [out][in] */ short __RPC_FAR *pcMinutes);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Procreate )( 
            IAnimal __RPC_FAR * This,
            /* [out] */ short __RPC_FAR *pcOffspring);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WhatKindOfAnimal )( 
            IAnimal __RPC_FAR * This,
            /* [out] */ IID __RPC_FAR *pIID);
        
        END_INTERFACE
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



HRESULT STDMETHODCALLTYPE IAnimal_Eat_Proxy( 
    IAnimal __RPC_FAR * This,
    /* [in] */ LPTSTR pszFoodRecommended,
    /* [out][in] */ LPTSTR pszFoodEaten,
    /* [in] */ short cchEaten);


void __RPC_STUB IAnimal_Eat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAnimal_Sleep_Proxy( 
    IAnimal __RPC_FAR * This,
    /* [out][in] */ short __RPC_FAR *pcMinutes);


void __RPC_STUB IAnimal_Sleep_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAnimal_Procreate_Proxy( 
    IAnimal __RPC_FAR * This,
    /* [out] */ short __RPC_FAR *pcOffspring);


void __RPC_STUB IAnimal_Procreate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAnimal_WhatKindOfAnimal_Proxy( 
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
