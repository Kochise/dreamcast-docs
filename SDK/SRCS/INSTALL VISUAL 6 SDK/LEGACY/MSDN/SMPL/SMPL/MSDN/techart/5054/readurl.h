/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Thu Apr 03 15:34:20 1997
 */
/* Compiler settings for rdurl.idl:
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

#ifndef __readurl_h__
#define __readurl_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IUrlReader_FWD_DEFINED__
#define __IUrlReader_FWD_DEFINED__
typedef interface IUrlReader IUrlReader;
#endif 	/* __IUrlReader_FWD_DEFINED__ */


#ifndef __IUrlReaderEvents_FWD_DEFINED__
#define __IUrlReaderEvents_FWD_DEFINED__
typedef interface IUrlReaderEvents IUrlReaderEvents;
#endif 	/* __IUrlReaderEvents_FWD_DEFINED__ */


#ifndef __DIUrlReaderEvents_FWD_DEFINED__
#define __DIUrlReaderEvents_FWD_DEFINED__
typedef interface DIUrlReaderEvents DIUrlReaderEvents;
#endif 	/* __DIUrlReaderEvents_FWD_DEFINED__ */


#ifndef __UrlReader_FWD_DEFINED__
#define __UrlReader_FWD_DEFINED__

#ifdef __cplusplus
typedef class UrlReader UrlReader;
#else
typedef struct UrlReader UrlReader;
#endif /* __cplusplus */

#endif 	/* __UrlReader_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IUrlReader_INTERFACE_DEFINED__
#define __IUrlReader_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IUrlReader
 * at Thu Apr 03 15:34:20 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IUrlReader;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("511A6700-9EEE-11D0-BD88-00A0C90F282F")
    IUrlReader : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadUrl( 
            BSTR sURL,
            BSTR sOutputSpec) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUrlReaderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IUrlReader __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IUrlReader __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IUrlReader __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IUrlReader __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IUrlReader __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IUrlReader __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IUrlReader __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadUrl )( 
            IUrlReader __RPC_FAR * This,
            BSTR sURL,
            BSTR sOutputSpec);
        
        END_INTERFACE
    } IUrlReaderVtbl;

    interface IUrlReader
    {
        CONST_VTBL struct IUrlReaderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUrlReader_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUrlReader_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUrlReader_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUrlReader_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IUrlReader_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IUrlReader_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IUrlReader_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IUrlReader_ReadUrl(This,sURL,sOutputSpec)	\
    (This)->lpVtbl -> ReadUrl(This,sURL,sOutputSpec)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IUrlReader_ReadUrl_Proxy( 
    IUrlReader __RPC_FAR * This,
    BSTR sURL,
    BSTR sOutputSpec);


void __RPC_STUB IUrlReader_ReadUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUrlReader_INTERFACE_DEFINED__ */


#ifndef __IUrlReaderEvents_INTERFACE_DEFINED__
#define __IUrlReaderEvents_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IUrlReaderEvents
 * at Thu Apr 03 15:34:20 1997
 * using MIDL 3.01.75
 ****************************************/
/* [version][helpstring][uuid][dual][object] */ 



EXTERN_C const IID IID_IUrlReaderEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("723B5B11-9EEF-11d0-BD88-00A0C90F282F")
    IUrlReaderEvents : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ReadUrlFinished( 
            long lFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReadUrlError( 
            long lErrorCode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUrlReaderEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IUrlReaderEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IUrlReaderEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IUrlReaderEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IUrlReaderEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IUrlReaderEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IUrlReaderEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IUrlReaderEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadUrlFinished )( 
            IUrlReaderEvents __RPC_FAR * This,
            long lFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadUrlError )( 
            IUrlReaderEvents __RPC_FAR * This,
            long lErrorCode);
        
        END_INTERFACE
    } IUrlReaderEventsVtbl;

    interface IUrlReaderEvents
    {
        CONST_VTBL struct IUrlReaderEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUrlReaderEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUrlReaderEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUrlReaderEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUrlReaderEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IUrlReaderEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IUrlReaderEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IUrlReaderEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IUrlReaderEvents_ReadUrlFinished(This,lFlags)	\
    (This)->lpVtbl -> ReadUrlFinished(This,lFlags)

#define IUrlReaderEvents_ReadUrlError(This,lErrorCode)	\
    (This)->lpVtbl -> ReadUrlError(This,lErrorCode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IUrlReaderEvents_ReadUrlFinished_Proxy( 
    IUrlReaderEvents __RPC_FAR * This,
    long lFlags);


void __RPC_STUB IUrlReaderEvents_ReadUrlFinished_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IUrlReaderEvents_ReadUrlError_Proxy( 
    IUrlReaderEvents __RPC_FAR * This,
    long lErrorCode);


void __RPC_STUB IUrlReaderEvents_ReadUrlError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUrlReaderEvents_INTERFACE_DEFINED__ */



#ifndef __READURLLib_LIBRARY_DEFINED__
#define __READURLLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: READURLLib
 * at Thu Apr 03 15:34:20 1997
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_READURLLib;

#ifndef __DIUrlReaderEvents_DISPINTERFACE_DEFINED__
#define __DIUrlReaderEvents_DISPINTERFACE_DEFINED__

/****************************************
 * Generated header for dispinterface: DIUrlReaderEvents
 * at Thu Apr 03 15:34:20 1997
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][nonextensible][uuid] */ 



EXTERN_C const IID DIID_DIUrlReaderEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface DECLSPEC_UUID("723B5B10-9EEF-11d0-BD88-00A0C90F282F")
    DIUrlReaderEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct DIUrlReaderEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DIUrlReaderEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DIUrlReaderEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DIUrlReaderEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            DIUrlReaderEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            DIUrlReaderEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            DIUrlReaderEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            DIUrlReaderEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } DIUrlReaderEventsVtbl;

    interface DIUrlReaderEvents
    {
        CONST_VTBL struct DIUrlReaderEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DIUrlReaderEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DIUrlReaderEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DIUrlReaderEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DIUrlReaderEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define DIUrlReaderEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define DIUrlReaderEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define DIUrlReaderEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __DIUrlReaderEvents_DISPINTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_UrlReader;

class DECLSPEC_UUID("511A6703-9EEE-11D0-BD88-00A0C90F282F")
UrlReader;
#endif
#endif /* __READURLLib_LIBRARY_DEFINED__ */

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
