/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 02:34:57 1998
 */
/* Compiler settings for psperf.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
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

#ifndef __psperf_h__
#define __psperf_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICOMPerformance_FWD_DEFINED__
#define __ICOMPerformance_FWD_DEFINED__
typedef interface ICOMPerformance ICOMPerformance;
#endif 	/* __ICOMPerformance_FWD_DEFINED__ */


#ifndef __TestCOMPerformance_FWD_DEFINED__
#define __TestCOMPerformance_FWD_DEFINED__

#ifdef __cplusplus
typedef class TestCOMPerformance TestCOMPerformance;
#else
typedef struct TestCOMPerformance TestCOMPerformance;
#endif /* __cplusplus */

#endif 	/* __TestCOMPerformance_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ICOMPerformance_INTERFACE_DEFINED__
#define __ICOMPerformance_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICOMPerformance
 * at Mon Mar 30 02:34:57 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [object][oleautomation][dual][uuid] */ 



EXTERN_C const IID IID_ICOMPerformance;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DDC68871-E08E-11cf-A535-00AA00615B03")
    ICOMPerformance : public IUnknown
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Test1( 
            /* [in] */ int l) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Test23( 
            /* [in] */ BSTR szDesc) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICOMPerformanceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICOMPerformance __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICOMPerformance __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICOMPerformance __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Test1 )( 
            ICOMPerformance __RPC_FAR * This,
            /* [in] */ int l);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Test23 )( 
            ICOMPerformance __RPC_FAR * This,
            /* [in] */ BSTR szDesc);
        
        END_INTERFACE
    } ICOMPerformanceVtbl;

    interface ICOMPerformance
    {
        CONST_VTBL struct ICOMPerformanceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICOMPerformance_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICOMPerformance_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICOMPerformance_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICOMPerformance_Test1(This,l)	\
    (This)->lpVtbl -> Test1(This,l)

#define ICOMPerformance_Test23(This,szDesc)	\
    (This)->lpVtbl -> Test23(This,szDesc)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE ICOMPerformance_Test1_Proxy( 
    ICOMPerformance __RPC_FAR * This,
    /* [in] */ int l);


void __RPC_STUB ICOMPerformance_Test1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICOMPerformance_Test23_Proxy( 
    ICOMPerformance __RPC_FAR * This,
    /* [in] */ BSTR szDesc);


void __RPC_STUB ICOMPerformance_Test23_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICOMPerformance_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
