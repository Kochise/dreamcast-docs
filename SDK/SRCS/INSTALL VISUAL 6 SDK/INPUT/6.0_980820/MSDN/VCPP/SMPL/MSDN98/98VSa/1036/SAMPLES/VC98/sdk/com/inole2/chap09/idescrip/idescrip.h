/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:49:41 1998
 */
/* Compiler settings for idescrip.idl:
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
 * at Mon Mar 30 03:49:41 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][object][uuid] */ 



EXTERN_C const IID IID_IDescription;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("00021152-0000-0000-c000-000000000046")
    IDescription : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetText( 
            /* [size_is][out][in] */ LPOLESTR pszText,
            /* [in] */ ULONG cch) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDescriptionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDescription __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDescription __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDescription __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetText )( 
            IDescription __RPC_FAR * This,
            /* [size_is][out][in] */ LPOLESTR pszText,
            /* [in] */ ULONG cch);
        
        END_INTERFACE
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



HRESULT STDMETHODCALLTYPE IDescription_GetText_Proxy( 
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
