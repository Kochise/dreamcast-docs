/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Wed Feb 11 11:57:34 1998
 */
/* Compiler settings for AtlCont.idl:
    Oic (OptLev=i1), W1, Zp8, env=Win32, ms_ext, c_ext
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

#ifndef __AtlCont_h__
#define __AtlCont_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAtlCont_FWD_DEFINED__
#define __IAtlCont_FWD_DEFINED__
typedef interface IAtlCont IAtlCont;
#endif 	/* __IAtlCont_FWD_DEFINED__ */


#ifndef __CAtlCont_FWD_DEFINED__
#define __CAtlCont_FWD_DEFINED__

#ifdef __cplusplus
typedef class CAtlCont CAtlCont;
#else
typedef struct CAtlCont CAtlCont;
#endif /* __cplusplus */

#endif 	/* __CAtlCont_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IAtlCont_INTERFACE_DEFINED__
#define __IAtlCont_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAtlCont
 * at Wed Feb 11 11:57:34 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][uuid][object] */ 



EXTERN_C const IID IID_IAtlCont;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BFD466C3-376C-11D0-96B5-00A0C90DC94B")
    IAtlCont : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Run( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAtlContVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAtlCont __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAtlCont __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAtlCont __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Run )( 
            IAtlCont __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IAtlCont __RPC_FAR * This);
        
        END_INTERFACE
    } IAtlContVtbl;

    interface IAtlCont
    {
        CONST_VTBL struct IAtlContVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAtlCont_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAtlCont_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAtlCont_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAtlCont_Run(This)	\
    (This)->lpVtbl -> Run(This)

#define IAtlCont_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAtlCont_Run_Proxy( 
    IAtlCont __RPC_FAR * This);


void __RPC_STUB IAtlCont_Run_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAtlCont_Stop_Proxy( 
    IAtlCont __RPC_FAR * This);


void __RPC_STUB IAtlCont_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAtlCont_INTERFACE_DEFINED__ */



#ifndef __ATLCONTLib_LIBRARY_DEFINED__
#define __ATLCONTLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: ATLCONTLib
 * at Wed Feb 11 11:57:34 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_ATLCONTLib;

EXTERN_C const CLSID CLSID_CAtlCont;

#ifdef __cplusplus

class DECLSPEC_UUID("BFD466C2-376C-11D0-96B5-00A0C90DC94B")
CAtlCont;
#endif
#endif /* __ATLCONTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
