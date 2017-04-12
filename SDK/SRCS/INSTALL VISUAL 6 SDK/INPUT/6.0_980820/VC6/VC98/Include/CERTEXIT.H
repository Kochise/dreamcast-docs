/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0106 */
/* at Mon Aug 04 19:41:37 1997
 */
/* Compiler settings for certexit.idl:
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

#ifndef __certexit_h__
#define __certexit_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICertExit_FWD_DEFINED__
#define __ICertExit_FWD_DEFINED__
typedef interface ICertExit ICertExit;
#endif 	/* __ICertExit_FWD_DEFINED__ */


#ifndef __CCertExit_FWD_DEFINED__
#define __CCertExit_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCertExit CCertExit;
#else
typedef struct CCertExit CCertExit;
#endif /* __cplusplus */

#endif 	/* __CCertExit_FWD_DEFINED__ */


/* header files for imported files */
#include "wtypes.h"
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_certexit_0000
 * at Mon Aug 04 19:41:37 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [local] */ 


#define	EXITEVENT_INVALID	( 0 )

#define	EXITEVENT_CERTISSUED	( 0x1 )

#define	EXITEVENT_CERTPENDING	( 0x2 )

#define	EXITEVENT_CERTDENIED	( 0x4 )

#define	EXITEVENT_CERTREVOKED	( 0x8 )

#define	EXITEVENT_CERTRETRIEVEPENDING	( 0x10 )

#define	EXITEVENT_CRLISSUED	( 0x20 )

#define	EXITEVENT_SHUTDOWN	( 0x40 )



extern RPC_IF_HANDLE __MIDL_itf_certexit_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_certexit_0000_v0_0_s_ifspec;

#ifndef __ICertExit_INTERFACE_DEFINED__
#define __ICertExit_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICertExit
 * at Mon Aug 04 19:41:37 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ICertExit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("e19ae1a0-7364-11d0-8816-00a0c903b83c")
    ICertExit : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ const BSTR strConfig,
            /* [retval][out] */ LONG __RPC_FAR *pEventMask) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Notify( 
            /* [in] */ LONG Event,
            /* [in] */ LONG Context) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDescription( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrDescription) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICertExitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICertExit __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICertExit __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICertExit __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICertExit __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICertExit __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICertExit __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICertExit __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            ICertExit __RPC_FAR * This,
            /* [in] */ const BSTR strConfig,
            /* [retval][out] */ LONG __RPC_FAR *pEventMask);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Notify )( 
            ICertExit __RPC_FAR * This,
            /* [in] */ LONG Event,
            /* [in] */ LONG Context);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDescription )( 
            ICertExit __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrDescription);
        
        END_INTERFACE
    } ICertExitVtbl;

    interface ICertExit
    {
        CONST_VTBL struct ICertExitVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICertExit_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICertExit_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICertExit_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICertExit_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICertExit_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICertExit_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICertExit_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICertExit_Initialize(This,strConfig,pEventMask)	\
    (This)->lpVtbl -> Initialize(This,strConfig,pEventMask)

#define ICertExit_Notify(This,Event,Context)	\
    (This)->lpVtbl -> Notify(This,Event,Context)

#define ICertExit_GetDescription(This,pstrDescription)	\
    (This)->lpVtbl -> GetDescription(This,pstrDescription)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICertExit_Initialize_Proxy( 
    ICertExit __RPC_FAR * This,
    /* [in] */ const BSTR strConfig,
    /* [retval][out] */ LONG __RPC_FAR *pEventMask);


void __RPC_STUB ICertExit_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertExit_Notify_Proxy( 
    ICertExit __RPC_FAR * This,
    /* [in] */ LONG Event,
    /* [in] */ LONG Context);


void __RPC_STUB ICertExit_Notify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertExit_GetDescription_Proxy( 
    ICertExit __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrDescription);


void __RPC_STUB ICertExit_GetDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICertExit_INTERFACE_DEFINED__ */



#ifndef __CERTEXITLib_LIBRARY_DEFINED__
#define __CERTEXITLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: CERTEXITLib
 * at Mon Aug 04 19:41:37 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_CERTEXITLib;

EXTERN_C const CLSID CLSID_CCertExit;

#ifdef __cplusplus

class DECLSPEC_UUID("c9e6e410-7364-11d0-8816-00a0c903b83c")
CCertExit;
#endif
#endif /* __CERTEXITLib_LIBRARY_DEFINED__ */

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
