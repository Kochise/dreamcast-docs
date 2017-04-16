#include "rpc.h"
#include "rpcndr.h"

#ifndef __pd_h__
#define __pd_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ILookup_FWD_DEFINED__
#define __ILookup_FWD_DEFINED__
typedef interface ILookup ILookup;
#endif 	/* __ILookup_FWD_DEFINED__ */


#include "unknwn.h"
void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ILookup_INTERFACE_DEFINED__
#define __ILookup_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ILookup
 * at Fri Oct 28 14:11:30 1994
 * using MIDL 2.00.72
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_ILookup;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface ILookup : public IUnknown
    {
    public:
        virtual HRESULT __stdcall LookupByName( 
            /* [in] */ LPTSTR lpName,
            /* [string][out] */ WCHAR __RPC_FAR *__RPC_FAR *lplpNumber) = 0;
        
        virtual HRESULT __stdcall LookupByNumber( 
            /* [in] */ LPTSTR lpNumber,
            /* [string][out] */ WCHAR __RPC_FAR *__RPC_FAR *lplpName) = 0;
        
    };
    
#else 	/* C style interface */
    
    typedef struct ILookupVtbl
    {
        
        HRESULT ( __stdcall __RPC_FAR *QueryInterface )( 
            ILookup __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( __stdcall __RPC_FAR *AddRef )( 
            ILookup __RPC_FAR * This);
        
        ULONG ( __stdcall __RPC_FAR *Release )( 
            ILookup __RPC_FAR * This);
        
        HRESULT ( __stdcall __RPC_FAR *LookupByName )( 
            ILookup __RPC_FAR * This,
            /* [in] */ LPTSTR lpName,
            /* [string][out] */ WCHAR __RPC_FAR *__RPC_FAR *lplpNumber);
        
        HRESULT ( __stdcall __RPC_FAR *LookupByNumber )( 
            ILookup __RPC_FAR * This,
            /* [in] */ LPTSTR lpNumber,
            /* [string][out] */ WCHAR __RPC_FAR *__RPC_FAR *lplpName);
        
    } ILookupVtbl;
    
    interface ILookup
    {
        CONST_VTBL struct ILookupVtbl __RPC_FAR *lpVtbl;
    };
    
    

#ifdef COBJMACROS


#define ILookup_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILookup_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILookup_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILookup_LookupByName(This,lpName,lplpNumber)	\
    (This)->lpVtbl -> LookupByName(This,lpName,lplpNumber)

#define ILookup_LookupByNumber(This,lpNumber,lplpName)	\
    (This)->lpVtbl -> LookupByNumber(This,lpNumber,lplpName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT __stdcall ILookup_LookupByName_Proxy( 
    ILookup __RPC_FAR * This,
    /* [in] */ LPTSTR lpName,
    /* [string][out] */ WCHAR __RPC_FAR *__RPC_FAR *lplpNumber);


void __RPC_STUB ILookup_LookupByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT __stdcall ILookup_LookupByNumber_Proxy( 
    ILookup __RPC_FAR * This,
    /* [in] */ LPTSTR lpNumber,
    /* [string][out] */ WCHAR __RPC_FAR *__RPC_FAR *lplpName);


void __RPC_STUB ILookup_LookupByNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILookup_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
