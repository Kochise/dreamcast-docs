/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0106 */
/* at Mon Aug 11 14:43:15 1997
 */
/* Compiler settings for certenc.idl:
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

#ifndef __certenc_h__
#define __certenc_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICertEncodeStringArray_FWD_DEFINED__
#define __ICertEncodeStringArray_FWD_DEFINED__
typedef interface ICertEncodeStringArray ICertEncodeStringArray;
#endif 	/* __ICertEncodeStringArray_FWD_DEFINED__ */


#ifndef __ICertEncodeLongArray_FWD_DEFINED__
#define __ICertEncodeLongArray_FWD_DEFINED__
typedef interface ICertEncodeLongArray ICertEncodeLongArray;
#endif 	/* __ICertEncodeLongArray_FWD_DEFINED__ */


#ifndef __ICertEncodeDateArray_FWD_DEFINED__
#define __ICertEncodeDateArray_FWD_DEFINED__
typedef interface ICertEncodeDateArray ICertEncodeDateArray;
#endif 	/* __ICertEncodeDateArray_FWD_DEFINED__ */


#ifndef __ICertEncodeSampleStructure1_FWD_DEFINED__
#define __ICertEncodeSampleStructure1_FWD_DEFINED__
typedef interface ICertEncodeSampleStructure1 ICertEncodeSampleStructure1;
#endif 	/* __ICertEncodeSampleStructure1_FWD_DEFINED__ */


#ifndef __ICertEncodeSampleStructure2_FWD_DEFINED__
#define __ICertEncodeSampleStructure2_FWD_DEFINED__
typedef interface ICertEncodeSampleStructure2 ICertEncodeSampleStructure2;
#endif 	/* __ICertEncodeSampleStructure2_FWD_DEFINED__ */


#ifndef __ICertEncodeCRLDistInfo_FWD_DEFINED__
#define __ICertEncodeCRLDistInfo_FWD_DEFINED__
typedef interface ICertEncodeCRLDistInfo ICertEncodeCRLDistInfo;
#endif 	/* __ICertEncodeCRLDistInfo_FWD_DEFINED__ */


#ifndef __ICertEncodeAltName_FWD_DEFINED__
#define __ICertEncodeAltName_FWD_DEFINED__
typedef interface ICertEncodeAltName ICertEncodeAltName;
#endif 	/* __ICertEncodeAltName_FWD_DEFINED__ */


#ifndef __ICertEncodeBitString_FWD_DEFINED__
#define __ICertEncodeBitString_FWD_DEFINED__
typedef interface ICertEncodeBitString ICertEncodeBitString;
#endif 	/* __ICertEncodeBitString_FWD_DEFINED__ */


#ifndef __CCertEncodeStringArray_FWD_DEFINED__
#define __CCertEncodeStringArray_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCertEncodeStringArray CCertEncodeStringArray;
#else
typedef struct CCertEncodeStringArray CCertEncodeStringArray;
#endif /* __cplusplus */

#endif 	/* __CCertEncodeStringArray_FWD_DEFINED__ */


#ifndef __CCertEncodeLongArray_FWD_DEFINED__
#define __CCertEncodeLongArray_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCertEncodeLongArray CCertEncodeLongArray;
#else
typedef struct CCertEncodeLongArray CCertEncodeLongArray;
#endif /* __cplusplus */

#endif 	/* __CCertEncodeLongArray_FWD_DEFINED__ */


#ifndef __CCertEncodeDateArray_FWD_DEFINED__
#define __CCertEncodeDateArray_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCertEncodeDateArray CCertEncodeDateArray;
#else
typedef struct CCertEncodeDateArray CCertEncodeDateArray;
#endif /* __cplusplus */

#endif 	/* __CCertEncodeDateArray_FWD_DEFINED__ */


#ifndef __CCertEncodeSampleStructure1_FWD_DEFINED__
#define __CCertEncodeSampleStructure1_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCertEncodeSampleStructure1 CCertEncodeSampleStructure1;
#else
typedef struct CCertEncodeSampleStructure1 CCertEncodeSampleStructure1;
#endif /* __cplusplus */

#endif 	/* __CCertEncodeSampleStructure1_FWD_DEFINED__ */


#ifndef __CCertEncodeSampleStructure2_FWD_DEFINED__
#define __CCertEncodeSampleStructure2_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCertEncodeSampleStructure2 CCertEncodeSampleStructure2;
#else
typedef struct CCertEncodeSampleStructure2 CCertEncodeSampleStructure2;
#endif /* __cplusplus */

#endif 	/* __CCertEncodeSampleStructure2_FWD_DEFINED__ */


#ifndef __CCertEncodeCRLDistInfo_FWD_DEFINED__
#define __CCertEncodeCRLDistInfo_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCertEncodeCRLDistInfo CCertEncodeCRLDistInfo;
#else
typedef struct CCertEncodeCRLDistInfo CCertEncodeCRLDistInfo;
#endif /* __cplusplus */

#endif 	/* __CCertEncodeCRLDistInfo_FWD_DEFINED__ */


#ifndef __CCertEncodeAltName_FWD_DEFINED__
#define __CCertEncodeAltName_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCertEncodeAltName CCertEncodeAltName;
#else
typedef struct CCertEncodeAltName CCertEncodeAltName;
#endif /* __cplusplus */

#endif 	/* __CCertEncodeAltName_FWD_DEFINED__ */


#ifndef __CCertEncodeBitString_FWD_DEFINED__
#define __CCertEncodeBitString_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCertEncodeBitString CCertEncodeBitString;
#else
typedef struct CCertEncodeBitString CCertEncodeBitString;
#endif /* __cplusplus */

#endif 	/* __CCertEncodeBitString_FWD_DEFINED__ */


/* header files for imported files */
#include "wtypes.h"
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ICertEncodeStringArray_INTERFACE_DEFINED__
#define __ICertEncodeStringArray_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICertEncodeStringArray
 * at Mon Aug 11 14:43:15 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ICertEncodeStringArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("12a88820-7494-11d0-8816-00a0c903b83c")
    ICertEncodeStringArray : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Decode( 
            /* [in] */ const BSTR strBinary) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStringType( 
            /* [retval][out] */ LONG __RPC_FAR *pStringType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCount( 
            /* [retval][out] */ LONG __RPC_FAR *pCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetValue( 
            /* [in] */ LONG Index,
            /* [retval][out] */ BSTR __RPC_FAR *pstr) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( 
            /* [in] */ LONG Count,
            /* [in] */ LONG StringType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetValue( 
            /* [in] */ LONG Index,
            /* [in] */ const BSTR str) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Encode( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrBinary) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICertEncodeStringArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICertEncodeStringArray __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICertEncodeStringArray __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICertEncodeStringArray __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICertEncodeStringArray __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICertEncodeStringArray __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICertEncodeStringArray __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICertEncodeStringArray __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Decode )( 
            ICertEncodeStringArray __RPC_FAR * This,
            /* [in] */ const BSTR strBinary);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStringType )( 
            ICertEncodeStringArray __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pStringType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCount )( 
            ICertEncodeStringArray __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetValue )( 
            ICertEncodeStringArray __RPC_FAR * This,
            /* [in] */ LONG Index,
            /* [retval][out] */ BSTR __RPC_FAR *pstr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            ICertEncodeStringArray __RPC_FAR * This,
            /* [in] */ LONG Count,
            /* [in] */ LONG StringType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetValue )( 
            ICertEncodeStringArray __RPC_FAR * This,
            /* [in] */ LONG Index,
            /* [in] */ const BSTR str);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Encode )( 
            ICertEncodeStringArray __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrBinary);
        
        END_INTERFACE
    } ICertEncodeStringArrayVtbl;

    interface ICertEncodeStringArray
    {
        CONST_VTBL struct ICertEncodeStringArrayVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICertEncodeStringArray_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICertEncodeStringArray_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICertEncodeStringArray_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICertEncodeStringArray_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICertEncodeStringArray_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICertEncodeStringArray_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICertEncodeStringArray_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICertEncodeStringArray_Decode(This,strBinary)	\
    (This)->lpVtbl -> Decode(This,strBinary)

#define ICertEncodeStringArray_GetStringType(This,pStringType)	\
    (This)->lpVtbl -> GetStringType(This,pStringType)

#define ICertEncodeStringArray_GetCount(This,pCount)	\
    (This)->lpVtbl -> GetCount(This,pCount)

#define ICertEncodeStringArray_GetValue(This,Index,pstr)	\
    (This)->lpVtbl -> GetValue(This,Index,pstr)

#define ICertEncodeStringArray_Reset(This,Count,StringType)	\
    (This)->lpVtbl -> Reset(This,Count,StringType)

#define ICertEncodeStringArray_SetValue(This,Index,str)	\
    (This)->lpVtbl -> SetValue(This,Index,str)

#define ICertEncodeStringArray_Encode(This,pstrBinary)	\
    (This)->lpVtbl -> Encode(This,pstrBinary)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICertEncodeStringArray_Decode_Proxy( 
    ICertEncodeStringArray __RPC_FAR * This,
    /* [in] */ const BSTR strBinary);


void __RPC_STUB ICertEncodeStringArray_Decode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeStringArray_GetStringType_Proxy( 
    ICertEncodeStringArray __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pStringType);


void __RPC_STUB ICertEncodeStringArray_GetStringType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeStringArray_GetCount_Proxy( 
    ICertEncodeStringArray __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pCount);


void __RPC_STUB ICertEncodeStringArray_GetCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeStringArray_GetValue_Proxy( 
    ICertEncodeStringArray __RPC_FAR * This,
    /* [in] */ LONG Index,
    /* [retval][out] */ BSTR __RPC_FAR *pstr);


void __RPC_STUB ICertEncodeStringArray_GetValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeStringArray_Reset_Proxy( 
    ICertEncodeStringArray __RPC_FAR * This,
    /* [in] */ LONG Count,
    /* [in] */ LONG StringType);


void __RPC_STUB ICertEncodeStringArray_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeStringArray_SetValue_Proxy( 
    ICertEncodeStringArray __RPC_FAR * This,
    /* [in] */ LONG Index,
    /* [in] */ const BSTR str);


void __RPC_STUB ICertEncodeStringArray_SetValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeStringArray_Encode_Proxy( 
    ICertEncodeStringArray __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrBinary);


void __RPC_STUB ICertEncodeStringArray_Encode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICertEncodeStringArray_INTERFACE_DEFINED__ */


#ifndef __ICertEncodeLongArray_INTERFACE_DEFINED__
#define __ICertEncodeLongArray_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICertEncodeLongArray
 * at Mon Aug 11 14:43:15 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ICertEncodeLongArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("15e2f230-a0a2-11d0-8821-00a0c903b83c")
    ICertEncodeLongArray : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Decode( 
            /* [in] */ const BSTR strBinary) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCount( 
            /* [retval][out] */ LONG __RPC_FAR *pCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetValue( 
            /* [in] */ LONG Index,
            /* [retval][out] */ LONG __RPC_FAR *pValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( 
            /* [in] */ LONG Count) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetValue( 
            /* [in] */ LONG Index,
            /* [in] */ LONG Value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Encode( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrBinary) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICertEncodeLongArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICertEncodeLongArray __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICertEncodeLongArray __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICertEncodeLongArray __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICertEncodeLongArray __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICertEncodeLongArray __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICertEncodeLongArray __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICertEncodeLongArray __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Decode )( 
            ICertEncodeLongArray __RPC_FAR * This,
            /* [in] */ const BSTR strBinary);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCount )( 
            ICertEncodeLongArray __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetValue )( 
            ICertEncodeLongArray __RPC_FAR * This,
            /* [in] */ LONG Index,
            /* [retval][out] */ LONG __RPC_FAR *pValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            ICertEncodeLongArray __RPC_FAR * This,
            /* [in] */ LONG Count);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetValue )( 
            ICertEncodeLongArray __RPC_FAR * This,
            /* [in] */ LONG Index,
            /* [in] */ LONG Value);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Encode )( 
            ICertEncodeLongArray __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrBinary);
        
        END_INTERFACE
    } ICertEncodeLongArrayVtbl;

    interface ICertEncodeLongArray
    {
        CONST_VTBL struct ICertEncodeLongArrayVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICertEncodeLongArray_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICertEncodeLongArray_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICertEncodeLongArray_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICertEncodeLongArray_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICertEncodeLongArray_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICertEncodeLongArray_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICertEncodeLongArray_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICertEncodeLongArray_Decode(This,strBinary)	\
    (This)->lpVtbl -> Decode(This,strBinary)

#define ICertEncodeLongArray_GetCount(This,pCount)	\
    (This)->lpVtbl -> GetCount(This,pCount)

#define ICertEncodeLongArray_GetValue(This,Index,pValue)	\
    (This)->lpVtbl -> GetValue(This,Index,pValue)

#define ICertEncodeLongArray_Reset(This,Count)	\
    (This)->lpVtbl -> Reset(This,Count)

#define ICertEncodeLongArray_SetValue(This,Index,Value)	\
    (This)->lpVtbl -> SetValue(This,Index,Value)

#define ICertEncodeLongArray_Encode(This,pstrBinary)	\
    (This)->lpVtbl -> Encode(This,pstrBinary)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICertEncodeLongArray_Decode_Proxy( 
    ICertEncodeLongArray __RPC_FAR * This,
    /* [in] */ const BSTR strBinary);


void __RPC_STUB ICertEncodeLongArray_Decode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeLongArray_GetCount_Proxy( 
    ICertEncodeLongArray __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pCount);


void __RPC_STUB ICertEncodeLongArray_GetCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeLongArray_GetValue_Proxy( 
    ICertEncodeLongArray __RPC_FAR * This,
    /* [in] */ LONG Index,
    /* [retval][out] */ LONG __RPC_FAR *pValue);


void __RPC_STUB ICertEncodeLongArray_GetValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeLongArray_Reset_Proxy( 
    ICertEncodeLongArray __RPC_FAR * This,
    /* [in] */ LONG Count);


void __RPC_STUB ICertEncodeLongArray_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeLongArray_SetValue_Proxy( 
    ICertEncodeLongArray __RPC_FAR * This,
    /* [in] */ LONG Index,
    /* [in] */ LONG Value);


void __RPC_STUB ICertEncodeLongArray_SetValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeLongArray_Encode_Proxy( 
    ICertEncodeLongArray __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrBinary);


void __RPC_STUB ICertEncodeLongArray_Encode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICertEncodeLongArray_INTERFACE_DEFINED__ */


#ifndef __ICertEncodeDateArray_INTERFACE_DEFINED__
#define __ICertEncodeDateArray_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICertEncodeDateArray
 * at Mon Aug 11 14:43:15 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ICertEncodeDateArray;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2f9469a0-a470-11d0-8821-00a0c903b83c")
    ICertEncodeDateArray : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Decode( 
            /* [in] */ const BSTR strBinary) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCount( 
            /* [retval][out] */ LONG __RPC_FAR *pCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetValue( 
            /* [in] */ LONG Index,
            /* [retval][out] */ DATE __RPC_FAR *pValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( 
            /* [in] */ LONG Count) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetValue( 
            /* [in] */ LONG Index,
            /* [in] */ DATE Value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Encode( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrBinary) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICertEncodeDateArrayVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICertEncodeDateArray __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICertEncodeDateArray __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICertEncodeDateArray __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICertEncodeDateArray __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICertEncodeDateArray __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICertEncodeDateArray __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICertEncodeDateArray __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Decode )( 
            ICertEncodeDateArray __RPC_FAR * This,
            /* [in] */ const BSTR strBinary);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCount )( 
            ICertEncodeDateArray __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetValue )( 
            ICertEncodeDateArray __RPC_FAR * This,
            /* [in] */ LONG Index,
            /* [retval][out] */ DATE __RPC_FAR *pValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            ICertEncodeDateArray __RPC_FAR * This,
            /* [in] */ LONG Count);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetValue )( 
            ICertEncodeDateArray __RPC_FAR * This,
            /* [in] */ LONG Index,
            /* [in] */ DATE Value);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Encode )( 
            ICertEncodeDateArray __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrBinary);
        
        END_INTERFACE
    } ICertEncodeDateArrayVtbl;

    interface ICertEncodeDateArray
    {
        CONST_VTBL struct ICertEncodeDateArrayVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICertEncodeDateArray_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICertEncodeDateArray_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICertEncodeDateArray_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICertEncodeDateArray_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICertEncodeDateArray_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICertEncodeDateArray_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICertEncodeDateArray_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICertEncodeDateArray_Decode(This,strBinary)	\
    (This)->lpVtbl -> Decode(This,strBinary)

#define ICertEncodeDateArray_GetCount(This,pCount)	\
    (This)->lpVtbl -> GetCount(This,pCount)

#define ICertEncodeDateArray_GetValue(This,Index,pValue)	\
    (This)->lpVtbl -> GetValue(This,Index,pValue)

#define ICertEncodeDateArray_Reset(This,Count)	\
    (This)->lpVtbl -> Reset(This,Count)

#define ICertEncodeDateArray_SetValue(This,Index,Value)	\
    (This)->lpVtbl -> SetValue(This,Index,Value)

#define ICertEncodeDateArray_Encode(This,pstrBinary)	\
    (This)->lpVtbl -> Encode(This,pstrBinary)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICertEncodeDateArray_Decode_Proxy( 
    ICertEncodeDateArray __RPC_FAR * This,
    /* [in] */ const BSTR strBinary);


void __RPC_STUB ICertEncodeDateArray_Decode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeDateArray_GetCount_Proxy( 
    ICertEncodeDateArray __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pCount);


void __RPC_STUB ICertEncodeDateArray_GetCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeDateArray_GetValue_Proxy( 
    ICertEncodeDateArray __RPC_FAR * This,
    /* [in] */ LONG Index,
    /* [retval][out] */ DATE __RPC_FAR *pValue);


void __RPC_STUB ICertEncodeDateArray_GetValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeDateArray_Reset_Proxy( 
    ICertEncodeDateArray __RPC_FAR * This,
    /* [in] */ LONG Count);


void __RPC_STUB ICertEncodeDateArray_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeDateArray_SetValue_Proxy( 
    ICertEncodeDateArray __RPC_FAR * This,
    /* [in] */ LONG Index,
    /* [in] */ DATE Value);


void __RPC_STUB ICertEncodeDateArray_SetValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeDateArray_Encode_Proxy( 
    ICertEncodeDateArray __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrBinary);


void __RPC_STUB ICertEncodeDateArray_Encode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICertEncodeDateArray_INTERFACE_DEFINED__ */


#ifndef __ICertEncodeSampleStructure1_INTERFACE_DEFINED__
#define __ICertEncodeSampleStructure1_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICertEncodeSampleStructure1
 * at Mon Aug 11 14:43:15 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ICertEncodeSampleStructure1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("eb244300-a0a0-11d0-8821-00a0c903b83c")
    ICertEncodeSampleStructure1 : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Decode( 
            /* [in] */ const BSTR strBinary) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStringField1( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrString) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStringField2( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrString) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLongField3( 
            /* [retval][out] */ LONG __RPC_FAR *pLong) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBinaryField4( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrBinary) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDateField5( 
            /* [retval][out] */ DATE __RPC_FAR *pDate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Encode( 
            /* [in] */ const BSTR strStringField1,
            /* [in] */ const BSTR strStringField2,
            /* [in] */ LONG LongField3,
            /* [in] */ const BSTR strBinaryField4,
            /* [in] */ DATE DateField5,
            /* [retval][out] */ BSTR __RPC_FAR *pstrBinary) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICertEncodeSampleStructure1Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICertEncodeSampleStructure1 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICertEncodeSampleStructure1 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICertEncodeSampleStructure1 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICertEncodeSampleStructure1 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICertEncodeSampleStructure1 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICertEncodeSampleStructure1 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICertEncodeSampleStructure1 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Decode )( 
            ICertEncodeSampleStructure1 __RPC_FAR * This,
            /* [in] */ const BSTR strBinary);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStringField1 )( 
            ICertEncodeSampleStructure1 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrString);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStringField2 )( 
            ICertEncodeSampleStructure1 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrString);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLongField3 )( 
            ICertEncodeSampleStructure1 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pLong);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBinaryField4 )( 
            ICertEncodeSampleStructure1 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrBinary);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDateField5 )( 
            ICertEncodeSampleStructure1 __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *pDate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Encode )( 
            ICertEncodeSampleStructure1 __RPC_FAR * This,
            /* [in] */ const BSTR strStringField1,
            /* [in] */ const BSTR strStringField2,
            /* [in] */ LONG LongField3,
            /* [in] */ const BSTR strBinaryField4,
            /* [in] */ DATE DateField5,
            /* [retval][out] */ BSTR __RPC_FAR *pstrBinary);
        
        END_INTERFACE
    } ICertEncodeSampleStructure1Vtbl;

    interface ICertEncodeSampleStructure1
    {
        CONST_VTBL struct ICertEncodeSampleStructure1Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICertEncodeSampleStructure1_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICertEncodeSampleStructure1_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICertEncodeSampleStructure1_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICertEncodeSampleStructure1_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICertEncodeSampleStructure1_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICertEncodeSampleStructure1_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICertEncodeSampleStructure1_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICertEncodeSampleStructure1_Decode(This,strBinary)	\
    (This)->lpVtbl -> Decode(This,strBinary)

#define ICertEncodeSampleStructure1_GetStringField1(This,pstrString)	\
    (This)->lpVtbl -> GetStringField1(This,pstrString)

#define ICertEncodeSampleStructure1_GetStringField2(This,pstrString)	\
    (This)->lpVtbl -> GetStringField2(This,pstrString)

#define ICertEncodeSampleStructure1_GetLongField3(This,pLong)	\
    (This)->lpVtbl -> GetLongField3(This,pLong)

#define ICertEncodeSampleStructure1_GetBinaryField4(This,pstrBinary)	\
    (This)->lpVtbl -> GetBinaryField4(This,pstrBinary)

#define ICertEncodeSampleStructure1_GetDateField5(This,pDate)	\
    (This)->lpVtbl -> GetDateField5(This,pDate)

#define ICertEncodeSampleStructure1_Encode(This,strStringField1,strStringField2,LongField3,strBinaryField4,DateField5,pstrBinary)	\
    (This)->lpVtbl -> Encode(This,strStringField1,strStringField2,LongField3,strBinaryField4,DateField5,pstrBinary)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICertEncodeSampleStructure1_Decode_Proxy( 
    ICertEncodeSampleStructure1 __RPC_FAR * This,
    /* [in] */ const BSTR strBinary);


void __RPC_STUB ICertEncodeSampleStructure1_Decode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeSampleStructure1_GetStringField1_Proxy( 
    ICertEncodeSampleStructure1 __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrString);


void __RPC_STUB ICertEncodeSampleStructure1_GetStringField1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeSampleStructure1_GetStringField2_Proxy( 
    ICertEncodeSampleStructure1 __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrString);


void __RPC_STUB ICertEncodeSampleStructure1_GetStringField2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeSampleStructure1_GetLongField3_Proxy( 
    ICertEncodeSampleStructure1 __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pLong);


void __RPC_STUB ICertEncodeSampleStructure1_GetLongField3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeSampleStructure1_GetBinaryField4_Proxy( 
    ICertEncodeSampleStructure1 __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrBinary);


void __RPC_STUB ICertEncodeSampleStructure1_GetBinaryField4_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeSampleStructure1_GetDateField5_Proxy( 
    ICertEncodeSampleStructure1 __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *pDate);


void __RPC_STUB ICertEncodeSampleStructure1_GetDateField5_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeSampleStructure1_Encode_Proxy( 
    ICertEncodeSampleStructure1 __RPC_FAR * This,
    /* [in] */ const BSTR strStringField1,
    /* [in] */ const BSTR strStringField2,
    /* [in] */ LONG LongField3,
    /* [in] */ const BSTR strBinaryField4,
    /* [in] */ DATE DateField5,
    /* [retval][out] */ BSTR __RPC_FAR *pstrBinary);


void __RPC_STUB ICertEncodeSampleStructure1_Encode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICertEncodeSampleStructure1_INTERFACE_DEFINED__ */


#ifndef __ICertEncodeSampleStructure2_INTERFACE_DEFINED__
#define __ICertEncodeSampleStructure2_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICertEncodeSampleStructure2
 * at Mon Aug 11 14:43:15 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ICertEncodeSampleStructure2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("68c58cd0-a0a0-11d0-8821-00a0c903b83c")
    ICertEncodeSampleStructure2 : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Decode( 
            /* [in] */ const BSTR strBinary) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLongField1( 
            /* [retval][out] */ LONG __RPC_FAR *pLong) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStringField2( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrString) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDateField3( 
            /* [retval][out] */ DATE __RPC_FAR *pDate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Encode( 
            /* [in] */ LONG lField1,
            /* [in] */ const BSTR strStringField2,
            /* [in] */ DATE DateField3,
            /* [retval][out] */ BSTR __RPC_FAR *pstrBinary) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICertEncodeSampleStructure2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICertEncodeSampleStructure2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICertEncodeSampleStructure2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICertEncodeSampleStructure2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICertEncodeSampleStructure2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICertEncodeSampleStructure2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICertEncodeSampleStructure2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICertEncodeSampleStructure2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Decode )( 
            ICertEncodeSampleStructure2 __RPC_FAR * This,
            /* [in] */ const BSTR strBinary);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLongField1 )( 
            ICertEncodeSampleStructure2 __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pLong);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStringField2 )( 
            ICertEncodeSampleStructure2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrString);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDateField3 )( 
            ICertEncodeSampleStructure2 __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *pDate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Encode )( 
            ICertEncodeSampleStructure2 __RPC_FAR * This,
            /* [in] */ LONG lField1,
            /* [in] */ const BSTR strStringField2,
            /* [in] */ DATE DateField3,
            /* [retval][out] */ BSTR __RPC_FAR *pstrBinary);
        
        END_INTERFACE
    } ICertEncodeSampleStructure2Vtbl;

    interface ICertEncodeSampleStructure2
    {
        CONST_VTBL struct ICertEncodeSampleStructure2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICertEncodeSampleStructure2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICertEncodeSampleStructure2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICertEncodeSampleStructure2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICertEncodeSampleStructure2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICertEncodeSampleStructure2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICertEncodeSampleStructure2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICertEncodeSampleStructure2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICertEncodeSampleStructure2_Decode(This,strBinary)	\
    (This)->lpVtbl -> Decode(This,strBinary)

#define ICertEncodeSampleStructure2_GetLongField1(This,pLong)	\
    (This)->lpVtbl -> GetLongField1(This,pLong)

#define ICertEncodeSampleStructure2_GetStringField2(This,pstrString)	\
    (This)->lpVtbl -> GetStringField2(This,pstrString)

#define ICertEncodeSampleStructure2_GetDateField3(This,pDate)	\
    (This)->lpVtbl -> GetDateField3(This,pDate)

#define ICertEncodeSampleStructure2_Encode(This,lField1,strStringField2,DateField3,pstrBinary)	\
    (This)->lpVtbl -> Encode(This,lField1,strStringField2,DateField3,pstrBinary)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICertEncodeSampleStructure2_Decode_Proxy( 
    ICertEncodeSampleStructure2 __RPC_FAR * This,
    /* [in] */ const BSTR strBinary);


void __RPC_STUB ICertEncodeSampleStructure2_Decode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeSampleStructure2_GetLongField1_Proxy( 
    ICertEncodeSampleStructure2 __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pLong);


void __RPC_STUB ICertEncodeSampleStructure2_GetLongField1_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeSampleStructure2_GetStringField2_Proxy( 
    ICertEncodeSampleStructure2 __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrString);


void __RPC_STUB ICertEncodeSampleStructure2_GetStringField2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeSampleStructure2_GetDateField3_Proxy( 
    ICertEncodeSampleStructure2 __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *pDate);


void __RPC_STUB ICertEncodeSampleStructure2_GetDateField3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeSampleStructure2_Encode_Proxy( 
    ICertEncodeSampleStructure2 __RPC_FAR * This,
    /* [in] */ LONG lField1,
    /* [in] */ const BSTR strStringField2,
    /* [in] */ DATE DateField3,
    /* [retval][out] */ BSTR __RPC_FAR *pstrBinary);


void __RPC_STUB ICertEncodeSampleStructure2_Encode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICertEncodeSampleStructure2_INTERFACE_DEFINED__ */


#ifndef __ICertEncodeCRLDistInfo_INTERFACE_DEFINED__
#define __ICertEncodeCRLDistInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICertEncodeCRLDistInfo
 * at Mon Aug 11 14:43:15 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ICertEncodeCRLDistInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("01958640-bbff-11d0-8825-00a0c903b83c")
    ICertEncodeCRLDistInfo : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Decode( 
            /* [in] */ const BSTR strBinary) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDistPointCount( 
            /* [retval][out] */ LONG __RPC_FAR *pDistPointCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNameCount( 
            /* [in] */ LONG DistPointIndex,
            /* [retval][out] */ LONG __RPC_FAR *pNameCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNameChoice( 
            /* [in] */ LONG DistPointIndex,
            /* [in] */ LONG NameIndex,
            /* [retval][out] */ LONG __RPC_FAR *pNameChoice) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetName( 
            /* [in] */ LONG DistPointIndex,
            /* [in] */ LONG NameIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pstrName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( 
            /* [in] */ LONG DistPointCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetNameCount( 
            /* [in] */ LONG DistPointIndex,
            /* [in] */ LONG NameCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetNameEntry( 
            /* [in] */ LONG DistPointIndex,
            /* [in] */ LONG NameIndex,
            /* [in] */ LONG NameChoice,
            /* [in] */ const BSTR strName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Encode( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrBinary) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICertEncodeCRLDistInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICertEncodeCRLDistInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICertEncodeCRLDistInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICertEncodeCRLDistInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICertEncodeCRLDistInfo __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICertEncodeCRLDistInfo __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICertEncodeCRLDistInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICertEncodeCRLDistInfo __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Decode )( 
            ICertEncodeCRLDistInfo __RPC_FAR * This,
            /* [in] */ const BSTR strBinary);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDistPointCount )( 
            ICertEncodeCRLDistInfo __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pDistPointCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameCount )( 
            ICertEncodeCRLDistInfo __RPC_FAR * This,
            /* [in] */ LONG DistPointIndex,
            /* [retval][out] */ LONG __RPC_FAR *pNameCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameChoice )( 
            ICertEncodeCRLDistInfo __RPC_FAR * This,
            /* [in] */ LONG DistPointIndex,
            /* [in] */ LONG NameIndex,
            /* [retval][out] */ LONG __RPC_FAR *pNameChoice);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            ICertEncodeCRLDistInfo __RPC_FAR * This,
            /* [in] */ LONG DistPointIndex,
            /* [in] */ LONG NameIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            ICertEncodeCRLDistInfo __RPC_FAR * This,
            /* [in] */ LONG DistPointCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetNameCount )( 
            ICertEncodeCRLDistInfo __RPC_FAR * This,
            /* [in] */ LONG DistPointIndex,
            /* [in] */ LONG NameCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetNameEntry )( 
            ICertEncodeCRLDistInfo __RPC_FAR * This,
            /* [in] */ LONG DistPointIndex,
            /* [in] */ LONG NameIndex,
            /* [in] */ LONG NameChoice,
            /* [in] */ const BSTR strName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Encode )( 
            ICertEncodeCRLDistInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrBinary);
        
        END_INTERFACE
    } ICertEncodeCRLDistInfoVtbl;

    interface ICertEncodeCRLDistInfo
    {
        CONST_VTBL struct ICertEncodeCRLDistInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICertEncodeCRLDistInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICertEncodeCRLDistInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICertEncodeCRLDistInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICertEncodeCRLDistInfo_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICertEncodeCRLDistInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICertEncodeCRLDistInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICertEncodeCRLDistInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICertEncodeCRLDistInfo_Decode(This,strBinary)	\
    (This)->lpVtbl -> Decode(This,strBinary)

#define ICertEncodeCRLDistInfo_GetDistPointCount(This,pDistPointCount)	\
    (This)->lpVtbl -> GetDistPointCount(This,pDistPointCount)

#define ICertEncodeCRLDistInfo_GetNameCount(This,DistPointIndex,pNameCount)	\
    (This)->lpVtbl -> GetNameCount(This,DistPointIndex,pNameCount)

#define ICertEncodeCRLDistInfo_GetNameChoice(This,DistPointIndex,NameIndex,pNameChoice)	\
    (This)->lpVtbl -> GetNameChoice(This,DistPointIndex,NameIndex,pNameChoice)

#define ICertEncodeCRLDistInfo_GetName(This,DistPointIndex,NameIndex,pstrName)	\
    (This)->lpVtbl -> GetName(This,DistPointIndex,NameIndex,pstrName)

#define ICertEncodeCRLDistInfo_Reset(This,DistPointCount)	\
    (This)->lpVtbl -> Reset(This,DistPointCount)

#define ICertEncodeCRLDistInfo_SetNameCount(This,DistPointIndex,NameCount)	\
    (This)->lpVtbl -> SetNameCount(This,DistPointIndex,NameCount)

#define ICertEncodeCRLDistInfo_SetNameEntry(This,DistPointIndex,NameIndex,NameChoice,strName)	\
    (This)->lpVtbl -> SetNameEntry(This,DistPointIndex,NameIndex,NameChoice,strName)

#define ICertEncodeCRLDistInfo_Encode(This,pstrBinary)	\
    (This)->lpVtbl -> Encode(This,pstrBinary)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICertEncodeCRLDistInfo_Decode_Proxy( 
    ICertEncodeCRLDistInfo __RPC_FAR * This,
    /* [in] */ const BSTR strBinary);


void __RPC_STUB ICertEncodeCRLDistInfo_Decode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeCRLDistInfo_GetDistPointCount_Proxy( 
    ICertEncodeCRLDistInfo __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pDistPointCount);


void __RPC_STUB ICertEncodeCRLDistInfo_GetDistPointCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeCRLDistInfo_GetNameCount_Proxy( 
    ICertEncodeCRLDistInfo __RPC_FAR * This,
    /* [in] */ LONG DistPointIndex,
    /* [retval][out] */ LONG __RPC_FAR *pNameCount);


void __RPC_STUB ICertEncodeCRLDistInfo_GetNameCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeCRLDistInfo_GetNameChoice_Proxy( 
    ICertEncodeCRLDistInfo __RPC_FAR * This,
    /* [in] */ LONG DistPointIndex,
    /* [in] */ LONG NameIndex,
    /* [retval][out] */ LONG __RPC_FAR *pNameChoice);


void __RPC_STUB ICertEncodeCRLDistInfo_GetNameChoice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeCRLDistInfo_GetName_Proxy( 
    ICertEncodeCRLDistInfo __RPC_FAR * This,
    /* [in] */ LONG DistPointIndex,
    /* [in] */ LONG NameIndex,
    /* [retval][out] */ BSTR __RPC_FAR *pstrName);


void __RPC_STUB ICertEncodeCRLDistInfo_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeCRLDistInfo_Reset_Proxy( 
    ICertEncodeCRLDistInfo __RPC_FAR * This,
    /* [in] */ LONG DistPointCount);


void __RPC_STUB ICertEncodeCRLDistInfo_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeCRLDistInfo_SetNameCount_Proxy( 
    ICertEncodeCRLDistInfo __RPC_FAR * This,
    /* [in] */ LONG DistPointIndex,
    /* [in] */ LONG NameCount);


void __RPC_STUB ICertEncodeCRLDistInfo_SetNameCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeCRLDistInfo_SetNameEntry_Proxy( 
    ICertEncodeCRLDistInfo __RPC_FAR * This,
    /* [in] */ LONG DistPointIndex,
    /* [in] */ LONG NameIndex,
    /* [in] */ LONG NameChoice,
    /* [in] */ const BSTR strName);


void __RPC_STUB ICertEncodeCRLDistInfo_SetNameEntry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeCRLDistInfo_Encode_Proxy( 
    ICertEncodeCRLDistInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrBinary);


void __RPC_STUB ICertEncodeCRLDistInfo_Encode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICertEncodeCRLDistInfo_INTERFACE_DEFINED__ */


#ifndef __ICertEncodeAltName_INTERFACE_DEFINED__
#define __ICertEncodeAltName_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICertEncodeAltName
 * at Mon Aug 11 14:43:15 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ICertEncodeAltName;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1c9a8c70-1271-11d1-9bd4-00c04fb683fa")
    ICertEncodeAltName : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Decode( 
            /* [in] */ const BSTR strBinary) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNameCount( 
            /* [retval][out] */ LONG __RPC_FAR *pNameCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNameChoice( 
            /* [in] */ LONG NameIndex,
            /* [retval][out] */ LONG __RPC_FAR *pNameChoice) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetName( 
            /* [in] */ LONG NameIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pstrName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( 
            /* [in] */ LONG NameCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetNameEntry( 
            /* [in] */ LONG NameIndex,
            /* [in] */ LONG NameChoice,
            /* [in] */ const BSTR strName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Encode( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrBinary) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICertEncodeAltNameVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICertEncodeAltName __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICertEncodeAltName __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICertEncodeAltName __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICertEncodeAltName __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICertEncodeAltName __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICertEncodeAltName __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICertEncodeAltName __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Decode )( 
            ICertEncodeAltName __RPC_FAR * This,
            /* [in] */ const BSTR strBinary);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameCount )( 
            ICertEncodeAltName __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pNameCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNameChoice )( 
            ICertEncodeAltName __RPC_FAR * This,
            /* [in] */ LONG NameIndex,
            /* [retval][out] */ LONG __RPC_FAR *pNameChoice);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            ICertEncodeAltName __RPC_FAR * This,
            /* [in] */ LONG NameIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            ICertEncodeAltName __RPC_FAR * This,
            /* [in] */ LONG NameCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetNameEntry )( 
            ICertEncodeAltName __RPC_FAR * This,
            /* [in] */ LONG NameIndex,
            /* [in] */ LONG NameChoice,
            /* [in] */ const BSTR strName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Encode )( 
            ICertEncodeAltName __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrBinary);
        
        END_INTERFACE
    } ICertEncodeAltNameVtbl;

    interface ICertEncodeAltName
    {
        CONST_VTBL struct ICertEncodeAltNameVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICertEncodeAltName_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICertEncodeAltName_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICertEncodeAltName_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICertEncodeAltName_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICertEncodeAltName_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICertEncodeAltName_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICertEncodeAltName_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICertEncodeAltName_Decode(This,strBinary)	\
    (This)->lpVtbl -> Decode(This,strBinary)

#define ICertEncodeAltName_GetNameCount(This,pNameCount)	\
    (This)->lpVtbl -> GetNameCount(This,pNameCount)

#define ICertEncodeAltName_GetNameChoice(This,NameIndex,pNameChoice)	\
    (This)->lpVtbl -> GetNameChoice(This,NameIndex,pNameChoice)

#define ICertEncodeAltName_GetName(This,NameIndex,pstrName)	\
    (This)->lpVtbl -> GetName(This,NameIndex,pstrName)

#define ICertEncodeAltName_Reset(This,NameCount)	\
    (This)->lpVtbl -> Reset(This,NameCount)

#define ICertEncodeAltName_SetNameEntry(This,NameIndex,NameChoice,strName)	\
    (This)->lpVtbl -> SetNameEntry(This,NameIndex,NameChoice,strName)

#define ICertEncodeAltName_Encode(This,pstrBinary)	\
    (This)->lpVtbl -> Encode(This,pstrBinary)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICertEncodeAltName_Decode_Proxy( 
    ICertEncodeAltName __RPC_FAR * This,
    /* [in] */ const BSTR strBinary);


void __RPC_STUB ICertEncodeAltName_Decode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeAltName_GetNameCount_Proxy( 
    ICertEncodeAltName __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pNameCount);


void __RPC_STUB ICertEncodeAltName_GetNameCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeAltName_GetNameChoice_Proxy( 
    ICertEncodeAltName __RPC_FAR * This,
    /* [in] */ LONG NameIndex,
    /* [retval][out] */ LONG __RPC_FAR *pNameChoice);


void __RPC_STUB ICertEncodeAltName_GetNameChoice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeAltName_GetName_Proxy( 
    ICertEncodeAltName __RPC_FAR * This,
    /* [in] */ LONG NameIndex,
    /* [retval][out] */ BSTR __RPC_FAR *pstrName);


void __RPC_STUB ICertEncodeAltName_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeAltName_Reset_Proxy( 
    ICertEncodeAltName __RPC_FAR * This,
    /* [in] */ LONG NameCount);


void __RPC_STUB ICertEncodeAltName_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeAltName_SetNameEntry_Proxy( 
    ICertEncodeAltName __RPC_FAR * This,
    /* [in] */ LONG NameIndex,
    /* [in] */ LONG NameChoice,
    /* [in] */ const BSTR strName);


void __RPC_STUB ICertEncodeAltName_SetNameEntry_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeAltName_Encode_Proxy( 
    ICertEncodeAltName __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrBinary);


void __RPC_STUB ICertEncodeAltName_Encode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICertEncodeAltName_INTERFACE_DEFINED__ */


#ifndef __ICertEncodeBitString_INTERFACE_DEFINED__
#define __ICertEncodeBitString_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICertEncodeBitString
 * at Mon Aug 11 14:43:15 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ICertEncodeBitString;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6db525be-1278-11d1-9bd4-00c04fb683fa")
    ICertEncodeBitString : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Decode( 
            /* [in] */ const BSTR strBinary) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBitCount( 
            /* [retval][out] */ LONG __RPC_FAR *pBitCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBitString( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrBitString) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Encode( 
            /* [in] */ LONG BitCount,
            /* [in] */ BSTR strBitString,
            /* [retval][out] */ BSTR __RPC_FAR *pstrBinary) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICertEncodeBitStringVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICertEncodeBitString __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICertEncodeBitString __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICertEncodeBitString __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICertEncodeBitString __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICertEncodeBitString __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICertEncodeBitString __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICertEncodeBitString __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Decode )( 
            ICertEncodeBitString __RPC_FAR * This,
            /* [in] */ const BSTR strBinary);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBitCount )( 
            ICertEncodeBitString __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pBitCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBitString )( 
            ICertEncodeBitString __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrBitString);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Encode )( 
            ICertEncodeBitString __RPC_FAR * This,
            /* [in] */ LONG BitCount,
            /* [in] */ BSTR strBitString,
            /* [retval][out] */ BSTR __RPC_FAR *pstrBinary);
        
        END_INTERFACE
    } ICertEncodeBitStringVtbl;

    interface ICertEncodeBitString
    {
        CONST_VTBL struct ICertEncodeBitStringVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICertEncodeBitString_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICertEncodeBitString_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICertEncodeBitString_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICertEncodeBitString_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICertEncodeBitString_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICertEncodeBitString_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICertEncodeBitString_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICertEncodeBitString_Decode(This,strBinary)	\
    (This)->lpVtbl -> Decode(This,strBinary)

#define ICertEncodeBitString_GetBitCount(This,pBitCount)	\
    (This)->lpVtbl -> GetBitCount(This,pBitCount)

#define ICertEncodeBitString_GetBitString(This,pstrBitString)	\
    (This)->lpVtbl -> GetBitString(This,pstrBitString)

#define ICertEncodeBitString_Encode(This,BitCount,strBitString,pstrBinary)	\
    (This)->lpVtbl -> Encode(This,BitCount,strBitString,pstrBinary)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICertEncodeBitString_Decode_Proxy( 
    ICertEncodeBitString __RPC_FAR * This,
    /* [in] */ const BSTR strBinary);


void __RPC_STUB ICertEncodeBitString_Decode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeBitString_GetBitCount_Proxy( 
    ICertEncodeBitString __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pBitCount);


void __RPC_STUB ICertEncodeBitString_GetBitCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeBitString_GetBitString_Proxy( 
    ICertEncodeBitString __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrBitString);


void __RPC_STUB ICertEncodeBitString_GetBitString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertEncodeBitString_Encode_Proxy( 
    ICertEncodeBitString __RPC_FAR * This,
    /* [in] */ LONG BitCount,
    /* [in] */ BSTR strBitString,
    /* [retval][out] */ BSTR __RPC_FAR *pstrBinary);


void __RPC_STUB ICertEncodeBitString_Encode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICertEncodeBitString_INTERFACE_DEFINED__ */



#ifndef __CERTENCODELib_LIBRARY_DEFINED__
#define __CERTENCODELib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: CERTENCODELib
 * at Mon Aug 11 14:43:15 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_CERTENCODELib;

EXTERN_C const CLSID CLSID_CCertEncodeStringArray;

#ifdef __cplusplus

class DECLSPEC_UUID("19a76fe0-7494-11d0-8816-00a0c903b83c")
CCertEncodeStringArray;
#endif

EXTERN_C const CLSID CLSID_CCertEncodeLongArray;

#ifdef __cplusplus

class DECLSPEC_UUID("4e0680a0-a0a2-11d0-8821-00a0c903b83c")
CCertEncodeLongArray;
#endif

EXTERN_C const CLSID CLSID_CCertEncodeDateArray;

#ifdef __cplusplus

class DECLSPEC_UUID("301f77b0-a470-11d0-8821-00a0c903b83c")
CCertEncodeDateArray;
#endif

EXTERN_C const CLSID CLSID_CCertEncodeSampleStructure1;

#ifdef __cplusplus

class DECLSPEC_UUID("14f92680-a0a2-11d0-8821-00a0c903b83c")
CCertEncodeSampleStructure1;
#endif

EXTERN_C const CLSID CLSID_CCertEncodeSampleStructure2;

#ifdef __cplusplus

class DECLSPEC_UUID("695e5b90-a0a0-11d0-8821-00a0c903b83c")
CCertEncodeSampleStructure2;
#endif

EXTERN_C const CLSID CLSID_CCertEncodeCRLDistInfo;

#ifdef __cplusplus

class DECLSPEC_UUID("01fa60a0-bbff-11d0-8825-00a0c903b83c")
CCertEncodeCRLDistInfo;
#endif

EXTERN_C const CLSID CLSID_CCertEncodeAltName;

#ifdef __cplusplus

class DECLSPEC_UUID("1cfc4cda-1271-11d1-9bd4-00c04fb683fa")
CCertEncodeAltName;
#endif

EXTERN_C const CLSID CLSID_CCertEncodeBitString;

#ifdef __cplusplus

class DECLSPEC_UUID("6d6b3cd8-1278-11d1-9bd4-00c04fb683fa")
CCertEncodeBitString;
#endif
#endif /* __CERTENCODELib_LIBRARY_DEFINED__ */

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
