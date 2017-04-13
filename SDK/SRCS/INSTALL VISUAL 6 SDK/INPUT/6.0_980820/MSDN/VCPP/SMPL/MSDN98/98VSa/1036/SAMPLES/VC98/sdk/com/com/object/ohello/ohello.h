/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 02:27:39 1998
 */
/* Compiler settings for ohello.idl:
    Oi (OptLev=i0), W1, Zp8, env=Win32, ms_ext, c_ext
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

#ifndef __ohello_h__
#define __ohello_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IHello_FWD_DEFINED__
#define __IHello_FWD_DEFINED__
typedef interface IHello IHello;
#endif 	/* __IHello_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IHello_INTERFACE_DEFINED__
#define __IHello_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IHello
 * at Mon Mar 30 02:27:39 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [uuid][object] */ 



EXTERN_C const IID IID_IHello;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a46deb31-9f33-11cd-b23f-00aa00339cce")
    IHello : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE HelloProc( 
            /* [string][in] */ unsigned char __RPC_FAR *pszString) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHelloVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHello __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHello __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHello __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HelloProc )( 
            IHello __RPC_FAR * This,
            /* [string][in] */ unsigned char __RPC_FAR *pszString);
        
        END_INTERFACE
    } IHelloVtbl;

    interface IHello
    {
        CONST_VTBL struct IHelloVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHello_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHello_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHello_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHello_HelloProc(This,pszString)	\
    (This)->lpVtbl -> HelloProc(This,pszString)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IHello_HelloProc_Proxy( 
    IHello __RPC_FAR * This,
    /* [string][in] */ unsigned char __RPC_FAR *pszString);


void __RPC_STUB IHello_HelloProc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHello_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
