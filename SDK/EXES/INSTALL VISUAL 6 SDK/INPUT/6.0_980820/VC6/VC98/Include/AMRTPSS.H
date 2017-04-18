/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Tue Sep 09 20:18:00 1997
 */
/* Compiler settings for amrtpss.idl:
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

#ifndef __amrtpss_h__
#define __amrtpss_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISilenceSuppressor_FWD_DEFINED__
#define __ISilenceSuppressor_FWD_DEFINED__
typedef interface ISilenceSuppressor ISilenceSuppressor;
#endif 	/* __ISilenceSuppressor_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISilenceSuppressor_INTERFACE_DEFINED__
#define __ISilenceSuppressor_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ISilenceSuppressor
 * at Tue Sep 09 20:18:00 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][local][uuid][object] */ 



EXTERN_C const IID IID_ISilenceSuppressor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("40C1D160-52F2-11d0-A874-00AA00B5CA1B")
    ISilenceSuppressor : public IUnknown
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetPreplayBufferTime( 
            /* [out] */ LPDWORD lpdwPreplayBufferTime) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetPreplayBufferTime( 
            /* [in] */ DWORD dwPreplayBufferTime) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetPostplayBufferTime( 
            /* [out] */ LPDWORD lpdwPostplayBufferTime) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetPostplayBufferTime( 
            /* [in] */ DWORD dwPostplayBufferTime) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetRunningAverageTime( 
            /* [out] */ LPDWORD lpdwRunningAverageTime) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetRunningAverageTime( 
            /* [in] */ DWORD dwRunningAverageTime) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetAverageIncrementor( 
            /* [out] */ LPDWORD lpdwAverageIncrementor) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetAverageIncrementor( 
            /* [in] */ DWORD dwAverageIncrementor) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetEchoThreshold( 
            /* [out] */ LPDWORD lpdwEchoThreshold) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetEchoThreshold( 
            /* [in] */ DWORD dwEchoThreshold) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetUseAverageEnergyFunction( 
            /* [out] */ BOOL __RPC_FAR *lpfUseAverageEnergyFunction) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetUseAverageEnergyFunction( 
            /* [in] */ BOOL fUseAverageEnergyFunction) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISilenceSuppressorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISilenceSuppressor __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISilenceSuppressor __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISilenceSuppressor __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPreplayBufferTime )( 
            ISilenceSuppressor __RPC_FAR * This,
            /* [out] */ LPDWORD lpdwPreplayBufferTime);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPreplayBufferTime )( 
            ISilenceSuppressor __RPC_FAR * This,
            /* [in] */ DWORD dwPreplayBufferTime);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPostplayBufferTime )( 
            ISilenceSuppressor __RPC_FAR * This,
            /* [out] */ LPDWORD lpdwPostplayBufferTime);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPostplayBufferTime )( 
            ISilenceSuppressor __RPC_FAR * This,
            /* [in] */ DWORD dwPostplayBufferTime);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRunningAverageTime )( 
            ISilenceSuppressor __RPC_FAR * This,
            /* [out] */ LPDWORD lpdwRunningAverageTime);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetRunningAverageTime )( 
            ISilenceSuppressor __RPC_FAR * This,
            /* [in] */ DWORD dwRunningAverageTime);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAverageIncrementor )( 
            ISilenceSuppressor __RPC_FAR * This,
            /* [out] */ LPDWORD lpdwAverageIncrementor);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAverageIncrementor )( 
            ISilenceSuppressor __RPC_FAR * This,
            /* [in] */ DWORD dwAverageIncrementor);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEchoThreshold )( 
            ISilenceSuppressor __RPC_FAR * This,
            /* [out] */ LPDWORD lpdwEchoThreshold);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEchoThreshold )( 
            ISilenceSuppressor __RPC_FAR * This,
            /* [in] */ DWORD dwEchoThreshold);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetUseAverageEnergyFunction )( 
            ISilenceSuppressor __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *lpfUseAverageEnergyFunction);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetUseAverageEnergyFunction )( 
            ISilenceSuppressor __RPC_FAR * This,
            /* [in] */ BOOL fUseAverageEnergyFunction);
        
        END_INTERFACE
    } ISilenceSuppressorVtbl;

    interface ISilenceSuppressor
    {
        CONST_VTBL struct ISilenceSuppressorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISilenceSuppressor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISilenceSuppressor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISilenceSuppressor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISilenceSuppressor_GetPreplayBufferTime(This,lpdwPreplayBufferTime)	\
    (This)->lpVtbl -> GetPreplayBufferTime(This,lpdwPreplayBufferTime)

#define ISilenceSuppressor_SetPreplayBufferTime(This,dwPreplayBufferTime)	\
    (This)->lpVtbl -> SetPreplayBufferTime(This,dwPreplayBufferTime)

#define ISilenceSuppressor_GetPostplayBufferTime(This,lpdwPostplayBufferTime)	\
    (This)->lpVtbl -> GetPostplayBufferTime(This,lpdwPostplayBufferTime)

#define ISilenceSuppressor_SetPostplayBufferTime(This,dwPostplayBufferTime)	\
    (This)->lpVtbl -> SetPostplayBufferTime(This,dwPostplayBufferTime)

#define ISilenceSuppressor_GetRunningAverageTime(This,lpdwRunningAverageTime)	\
    (This)->lpVtbl -> GetRunningAverageTime(This,lpdwRunningAverageTime)

#define ISilenceSuppressor_SetRunningAverageTime(This,dwRunningAverageTime)	\
    (This)->lpVtbl -> SetRunningAverageTime(This,dwRunningAverageTime)

#define ISilenceSuppressor_GetAverageIncrementor(This,lpdwAverageIncrementor)	\
    (This)->lpVtbl -> GetAverageIncrementor(This,lpdwAverageIncrementor)

#define ISilenceSuppressor_SetAverageIncrementor(This,dwAverageIncrementor)	\
    (This)->lpVtbl -> SetAverageIncrementor(This,dwAverageIncrementor)

#define ISilenceSuppressor_GetEchoThreshold(This,lpdwEchoThreshold)	\
    (This)->lpVtbl -> GetEchoThreshold(This,lpdwEchoThreshold)

#define ISilenceSuppressor_SetEchoThreshold(This,dwEchoThreshold)	\
    (This)->lpVtbl -> SetEchoThreshold(This,dwEchoThreshold)

#define ISilenceSuppressor_GetUseAverageEnergyFunction(This,lpfUseAverageEnergyFunction)	\
    (This)->lpVtbl -> GetUseAverageEnergyFunction(This,lpfUseAverageEnergyFunction)

#define ISilenceSuppressor_SetUseAverageEnergyFunction(This,fUseAverageEnergyFunction)	\
    (This)->lpVtbl -> SetUseAverageEnergyFunction(This,fUseAverageEnergyFunction)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE ISilenceSuppressor_GetPreplayBufferTime_Proxy( 
    ISilenceSuppressor __RPC_FAR * This,
    /* [out] */ LPDWORD lpdwPreplayBufferTime);


void __RPC_STUB ISilenceSuppressor_GetPreplayBufferTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ISilenceSuppressor_SetPreplayBufferTime_Proxy( 
    ISilenceSuppressor __RPC_FAR * This,
    /* [in] */ DWORD dwPreplayBufferTime);


void __RPC_STUB ISilenceSuppressor_SetPreplayBufferTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ISilenceSuppressor_GetPostplayBufferTime_Proxy( 
    ISilenceSuppressor __RPC_FAR * This,
    /* [out] */ LPDWORD lpdwPostplayBufferTime);


void __RPC_STUB ISilenceSuppressor_GetPostplayBufferTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ISilenceSuppressor_SetPostplayBufferTime_Proxy( 
    ISilenceSuppressor __RPC_FAR * This,
    /* [in] */ DWORD dwPostplayBufferTime);


void __RPC_STUB ISilenceSuppressor_SetPostplayBufferTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ISilenceSuppressor_GetRunningAverageTime_Proxy( 
    ISilenceSuppressor __RPC_FAR * This,
    /* [out] */ LPDWORD lpdwRunningAverageTime);


void __RPC_STUB ISilenceSuppressor_GetRunningAverageTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ISilenceSuppressor_SetRunningAverageTime_Proxy( 
    ISilenceSuppressor __RPC_FAR * This,
    /* [in] */ DWORD dwRunningAverageTime);


void __RPC_STUB ISilenceSuppressor_SetRunningAverageTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ISilenceSuppressor_GetAverageIncrementor_Proxy( 
    ISilenceSuppressor __RPC_FAR * This,
    /* [out] */ LPDWORD lpdwAverageIncrementor);


void __RPC_STUB ISilenceSuppressor_GetAverageIncrementor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ISilenceSuppressor_SetAverageIncrementor_Proxy( 
    ISilenceSuppressor __RPC_FAR * This,
    /* [in] */ DWORD dwAverageIncrementor);


void __RPC_STUB ISilenceSuppressor_SetAverageIncrementor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ISilenceSuppressor_GetEchoThreshold_Proxy( 
    ISilenceSuppressor __RPC_FAR * This,
    /* [out] */ LPDWORD lpdwEchoThreshold);


void __RPC_STUB ISilenceSuppressor_GetEchoThreshold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ISilenceSuppressor_SetEchoThreshold_Proxy( 
    ISilenceSuppressor __RPC_FAR * This,
    /* [in] */ DWORD dwEchoThreshold);


void __RPC_STUB ISilenceSuppressor_SetEchoThreshold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ISilenceSuppressor_GetUseAverageEnergyFunction_Proxy( 
    ISilenceSuppressor __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *lpfUseAverageEnergyFunction);


void __RPC_STUB ISilenceSuppressor_GetUseAverageEnergyFunction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ISilenceSuppressor_SetUseAverageEnergyFunction_Proxy( 
    ISilenceSuppressor __RPC_FAR * This,
    /* [in] */ BOOL fUseAverageEnergyFunction);


void __RPC_STUB ISilenceSuppressor_SetUseAverageEnergyFunction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISilenceSuppressor_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_amrtpss_0094
 * at Tue Sep 09 20:18:00 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


EXTERN_C const CLSID CLSID_SilenceSuppressionFilter;
EXTERN_C const CLSID CLSID_SilenceSuppressionProperties;


extern RPC_IF_HANDLE __MIDL_itf_amrtpss_0094_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_amrtpss_0094_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
