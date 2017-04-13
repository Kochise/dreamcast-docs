/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 2.00.0102 */
/* at Tue May 21 15:05:31 1996
 */
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"
#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __idescrip_h__
#define __idescrip_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IDescription_FWD_DEFINED__
#define __IDescription_FWD_DEFINED__
typedef interface IDescription IDescription;
#endif 	/* __IDescription_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IDescription_INTERFACE_DEFINED__
#define __IDescription_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDescription
 * at Tue May 21 15:05:31 1996
 * using MIDL 2.00.0102
 ****************************************/
/* [unique][object][uuid] */ 



EXTERN_C const IID IID_IDescription;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface IDescription : public IUnknown
    {
    public:
        virtual HRESULT __stdcall GetText( 
            /* [size_is][out][in] */ LPOLESTR pszText,
            /* [in] */ ULONG cch) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDescriptionVtbl
    {
        
        HRESULT ( __stdcall __RPC_FAR *QueryInterface )( 
            IDescription __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( __stdcall __RPC_FAR *AddRef )( 
            IDescription __RPC_FAR * This);
        
        ULONG ( __stdcall __RPC_FAR *Release )( 
            IDescription __RPC_FAR * This);
        
        HRESULT ( __stdcall __RPC_FAR *GetText )( 
            IDescription __RPC_FAR * This,
            /* [size_is][out][in] */ LPOLESTR pszText,
            /* [in] */ ULONG cch);
        
    } IDescriptionVtbl;

    interface IDescription
    {
        CONST_VTBL struct IDescriptionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDescription_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDescription_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDescription_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDescription_GetText(This,pszText,cch)	\
    (This)->lpVtbl -> GetText(This,pszText,cch)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT __stdcall IDescription_GetText_Proxy( 
    IDescription __RPC_FAR * This,
    /* [size_is][out][in] */ LPOLESTR pszText,
    /* [in] */ ULONG cch);


void __RPC_STUB IDescription_GetText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDescription_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
