/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Thu Jan 08 00:20:49 1998
 */
/* Compiler settings for FinSrvr.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"
#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __FinSrvr_h__
#define __FinSrvr_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IPerfmonObject_FWD_DEFINED__
#define __IPerfmonObject_FWD_DEFINED__
typedef interface IPerfmonObject IPerfmonObject;
#endif 	/* __IPerfmonObject_FWD_DEFINED__ */


#ifndef __IPerfmonCounter_FWD_DEFINED__
#define __IPerfmonCounter_FWD_DEFINED__
typedef interface IPerfmonCounter IPerfmonCounter;
#endif 	/* __IPerfmonCounter_FWD_DEFINED__ */


#ifndef __IFinSessn_FWD_DEFINED__
#define __IFinSessn_FWD_DEFINED__
typedef interface IFinSessn IFinSessn;
#endif 	/* __IFinSessn_FWD_DEFINED__ */


#ifndef __ICFinCntrs_FWD_DEFINED__
#define __ICFinCntrs_FWD_DEFINED__
typedef interface ICFinCntrs ICFinCntrs;
#endif 	/* __ICFinCntrs_FWD_DEFINED__ */


#ifndef __FinSessn_FWD_DEFINED__
#define __FinSessn_FWD_DEFINED__

#ifdef __cplusplus
typedef class FinSessn FinSessn;
#else
typedef struct FinSessn FinSessn;
#endif /* __cplusplus */

#endif 	/* __FinSessn_FWD_DEFINED__ */


#ifndef __CFinCntrs_FWD_DEFINED__
#define __CFinCntrs_FWD_DEFINED__

#ifdef __cplusplus
typedef class CFinCntrs CFinCntrs;
#else
typedef struct CFinCntrs CFinCntrs;
#endif /* __cplusplus */

#endif 	/* __CFinCntrs_FWD_DEFINED__ */


#ifndef __CTemp1_FWD_DEFINED__
#define __CTemp1_FWD_DEFINED__

#ifdef __cplusplus
typedef class CTemp1 CTemp1;
#else
typedef struct CTemp1 CTemp1;
#endif /* __cplusplus */

#endif 	/* __CTemp1_FWD_DEFINED__ */


#ifndef __CTemp2_FWD_DEFINED__
#define __CTemp2_FWD_DEFINED__

#ifdef __cplusplus
typedef class CTemp2 CTemp2;
#else
typedef struct CTemp2 CTemp2;
#endif /* __cplusplus */

#endif 	/* __CTemp2_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IPerfmonObject_INTERFACE_DEFINED__
#define __IPerfmonObject_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IPerfmonObject
 * at Thu Jan 08 00:20:49 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IPerfmonObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("3DBD6FB0-FFA7-11d0-9F8C-400004491341")
    IPerfmonObject : public IDispatch
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetName( 
            /* [retval][out] */ BSTR __RPC_FAR *pName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHelp( 
            /* [retval][out] */ BSTR __RPC_FAR *pHelp) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetIndex( 
            /* [retval][out] */ long __RPC_FAR *pIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetNumCounters( 
            /* [retval][out] */ long __RPC_FAR *pNumCounters) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCounters( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pCounters) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPerfmonObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPerfmonObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPerfmonObject __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPerfmonObject __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPerfmonObject __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPerfmonObject __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPerfmonObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPerfmonObject __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            IPerfmonObject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHelp )( 
            IPerfmonObject __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pHelp);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIndex )( 
            IPerfmonObject __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNumCounters )( 
            IPerfmonObject __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pNumCounters);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCounters )( 
            IPerfmonObject __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pCounters);
        
        END_INTERFACE
    } IPerfmonObjectVtbl;

    interface IPerfmonObject
    {
        CONST_VTBL struct IPerfmonObjectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPerfmonObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPerfmonObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPerfmonObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPerfmonObject_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPerfmonObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPerfmonObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPerfmonObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPerfmonObject_GetName(This,pName)	\
    (This)->lpVtbl -> GetName(This,pName)

#define IPerfmonObject_GetHelp(This,pHelp)	\
    (This)->lpVtbl -> GetHelp(This,pHelp)

#define IPerfmonObject_GetIndex(This,pIndex)	\
    (This)->lpVtbl -> GetIndex(This,pIndex)

#define IPerfmonObject_GetNumCounters(This,pNumCounters)	\
    (This)->lpVtbl -> GetNumCounters(This,pNumCounters)

#define IPerfmonObject_GetCounters(This,pCounters)	\
    (This)->lpVtbl -> GetCounters(This,pCounters)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPerfmonObject_GetName_Proxy( 
    IPerfmonObject __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pName);


void __RPC_STUB IPerfmonObject_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPerfmonObject_GetHelp_Proxy( 
    IPerfmonObject __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pHelp);


void __RPC_STUB IPerfmonObject_GetHelp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPerfmonObject_GetIndex_Proxy( 
    IPerfmonObject __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pIndex);


void __RPC_STUB IPerfmonObject_GetIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPerfmonObject_GetNumCounters_Proxy( 
    IPerfmonObject __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pNumCounters);


void __RPC_STUB IPerfmonObject_GetNumCounters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPerfmonObject_GetCounters_Proxy( 
    IPerfmonObject __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pCounters);


void __RPC_STUB IPerfmonObject_GetCounters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPerfmonObject_INTERFACE_DEFINED__ */


#ifndef __IPerfmonCounter_INTERFACE_DEFINED__
#define __IPerfmonCounter_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IPerfmonCounter
 * at Thu Jan 08 00:20:49 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IPerfmonCounter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("3DBD6FB1-FFA7-11d0-9F8C-400004491341")
    IPerfmonCounter : public IDispatch
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Collect( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetName( 
            /* [retval][out] */ BSTR __RPC_FAR *pName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetHelp( 
            /* [retval][out] */ BSTR __RPC_FAR *pHelp) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetIndex( 
            /* [retval][out] */ long __RPC_FAR *pIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDataType( 
            /* [retval][out] */ short __RPC_FAR *pDataType) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPerfmonCounterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPerfmonCounter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPerfmonCounter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPerfmonCounter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IPerfmonCounter __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IPerfmonCounter __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IPerfmonCounter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IPerfmonCounter __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Collect )( 
            IPerfmonCounter __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            IPerfmonCounter __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHelp )( 
            IPerfmonCounter __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pHelp);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIndex )( 
            IPerfmonCounter __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDataType )( 
            IPerfmonCounter __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pDataType);
        
        END_INTERFACE
    } IPerfmonCounterVtbl;

    interface IPerfmonCounter
    {
        CONST_VTBL struct IPerfmonCounterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPerfmonCounter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPerfmonCounter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPerfmonCounter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPerfmonCounter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IPerfmonCounter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IPerfmonCounter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IPerfmonCounter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IPerfmonCounter_Collect(This,pVariant)	\
    (This)->lpVtbl -> Collect(This,pVariant)

#define IPerfmonCounter_GetName(This,pName)	\
    (This)->lpVtbl -> GetName(This,pName)

#define IPerfmonCounter_GetHelp(This,pHelp)	\
    (This)->lpVtbl -> GetHelp(This,pHelp)

#define IPerfmonCounter_GetIndex(This,pIndex)	\
    (This)->lpVtbl -> GetIndex(This,pIndex)

#define IPerfmonCounter_GetDataType(This,pDataType)	\
    (This)->lpVtbl -> GetDataType(This,pDataType)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPerfmonCounter_Collect_Proxy( 
    IPerfmonCounter __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVariant);


void __RPC_STUB IPerfmonCounter_Collect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPerfmonCounter_GetName_Proxy( 
    IPerfmonCounter __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pName);


void __RPC_STUB IPerfmonCounter_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPerfmonCounter_GetHelp_Proxy( 
    IPerfmonCounter __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pHelp);


void __RPC_STUB IPerfmonCounter_GetHelp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPerfmonCounter_GetIndex_Proxy( 
    IPerfmonCounter __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pIndex);


void __RPC_STUB IPerfmonCounter_GetIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPerfmonCounter_GetDataType_Proxy( 
    IPerfmonCounter __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pDataType);


void __RPC_STUB IPerfmonCounter_GetDataType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPerfmonCounter_INTERFACE_DEFINED__ */


#ifndef __IFinSessn_INTERFACE_DEFINED__
#define __IFinSessn_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IFinSessn
 * at Thu Jan 08 00:20:49 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IFinSessn;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0166BE92-87E2-11D1-8DB5-204C4F4F5020")
    IFinSessn : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IFinSessnVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFinSessn __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFinSessn __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFinSessn __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IFinSessn __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IFinSessn __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IFinSessn __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IFinSessn __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IFinSessnVtbl;

    interface IFinSessn
    {
        CONST_VTBL struct IFinSessnVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFinSessn_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFinSessn_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFinSessn_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFinSessn_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IFinSessn_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IFinSessn_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IFinSessn_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFinSessn_INTERFACE_DEFINED__ */


#ifndef __ICFinCntrs_INTERFACE_DEFINED__
#define __ICFinCntrs_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICFinCntrs
 * at Thu Jan 08 00:20:49 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ICFinCntrs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0166BE94-87E2-11D1-8DB5-204C4F4F5020")
    ICFinCntrs : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ICFinCntrsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICFinCntrs __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICFinCntrs __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICFinCntrs __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICFinCntrs __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICFinCntrs __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICFinCntrs __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICFinCntrs __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ICFinCntrsVtbl;

    interface ICFinCntrs
    {
        CONST_VTBL struct ICFinCntrsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICFinCntrs_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICFinCntrs_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICFinCntrs_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICFinCntrs_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICFinCntrs_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICFinCntrs_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICFinCntrs_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICFinCntrs_INTERFACE_DEFINED__ */



#ifndef __FINSRVRLib_LIBRARY_DEFINED__
#define __FINSRVRLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: FINSRVRLib
 * at Thu Jan 08 00:20:49 1998
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_FINSRVRLib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_FinSessn;

class DECLSPEC_UUID("0166BE93-87E2-11D1-8DB5-204C4F4F5020")
FinSessn;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CFinCntrs;

class DECLSPEC_UUID("B0A6AA96-76F5-11D1-8D92-204C4F4F5020")
CFinCntrs;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CTemp1;

class DECLSPEC_UUID("7E3EC2E1-87F0-11d1-8DB5-204C4F4F5020")
CTemp1;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CTemp2;

class DECLSPEC_UUID("EE91F7C2-87EF-11d1-8DB5-204C4F4F5020")
CTemp2;
#endif
#endif /* __FINSRVRLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
