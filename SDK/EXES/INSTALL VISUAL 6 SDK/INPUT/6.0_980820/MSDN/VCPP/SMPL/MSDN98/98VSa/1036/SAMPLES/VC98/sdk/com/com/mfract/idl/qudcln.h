/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 02:26:29 1998
 */
/* Compiler settings for qudcln.idl:
    Os (OptLev=s), W1, Zp4, env=Win32, ms_ext, c_ext
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

#ifndef __qudcln_h__
#define __qudcln_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IQuadrantClient_FWD_DEFINED__
#define __IQuadrantClient_FWD_DEFINED__
typedef interface IQuadrantClient IQuadrantClient;
#endif 	/* __IQuadrantClient_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IQuadrantClient_INTERFACE_DEFINED__
#define __IQuadrantClient_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IQuadrantClient
 * at Mon Mar 30 02:26:29 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][uuid][object][local] */ 



EXTERN_C const IID IID_IQuadrantClient;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2a0e4fbc-3908-101b-8963-00000b65c75b")
    IQuadrantClient : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ComputePoint( 
            unsigned int __RPC_FAR *puColor,
            int x,
            int y) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DoneDrawingGraph( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IQuadrantClientVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IQuadrantClient __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IQuadrantClient __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IQuadrantClient __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ComputePoint )( 
            IQuadrantClient __RPC_FAR * This,
            unsigned int __RPC_FAR *puColor,
            int x,
            int y);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DoneDrawingGraph )( 
            IQuadrantClient __RPC_FAR * This);
        
        END_INTERFACE
    } IQuadrantClientVtbl;

    interface IQuadrantClient
    {
        CONST_VTBL struct IQuadrantClientVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IQuadrantClient_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IQuadrantClient_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IQuadrantClient_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IQuadrantClient_ComputePoint(This,puColor,x,y)	\
    (This)->lpVtbl -> ComputePoint(This,puColor,x,y)

#define IQuadrantClient_DoneDrawingGraph(This)	\
    (This)->lpVtbl -> DoneDrawingGraph(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IQuadrantClient_ComputePoint_Proxy( 
    IQuadrantClient __RPC_FAR * This,
    unsigned int __RPC_FAR *puColor,
    int x,
    int y);


void __RPC_STUB IQuadrantClient_ComputePoint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IQuadrantClient_DoneDrawingGraph_Proxy( 
    IQuadrantClient __RPC_FAR * This);


void __RPC_STUB IQuadrantClient_DoneDrawingGraph_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IQuadrantClient_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
