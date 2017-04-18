/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0106 */
/* at Mon Aug 04 19:41:38 1997
 */
/* Compiler settings for certif.idl:
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

#ifndef __certif_h__
#define __certif_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICertServerPolicy_FWD_DEFINED__
#define __ICertServerPolicy_FWD_DEFINED__
typedef interface ICertServerPolicy ICertServerPolicy;
#endif 	/* __ICertServerPolicy_FWD_DEFINED__ */


#ifndef __ICertServerExit_FWD_DEFINED__
#define __ICertServerExit_FWD_DEFINED__
typedef interface ICertServerExit ICertServerExit;
#endif 	/* __ICertServerExit_FWD_DEFINED__ */


#ifndef __CCertServerPolicy_FWD_DEFINED__
#define __CCertServerPolicy_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCertServerPolicy CCertServerPolicy;
#else
typedef struct CCertServerPolicy CCertServerPolicy;
#endif /* __cplusplus */

#endif 	/* __CCertServerPolicy_FWD_DEFINED__ */


#ifndef __CCertServerExit_FWD_DEFINED__
#define __CCertServerExit_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCertServerExit CCertServerExit;
#else
typedef struct CCertServerExit CCertServerExit;
#endif /* __cplusplus */

#endif 	/* __CCertServerExit_FWD_DEFINED__ */


/* header files for imported files */
#include "wtypes.h"
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_certif_0000
 * at Mon Aug 04 19:41:38 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [local] */ 


#define	ENUMEXT_OBJECTID	( 0x1 )



extern RPC_IF_HANDLE __MIDL_itf_certif_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_certif_0000_v0_0_s_ifspec;

#ifndef __ICertServerPolicy_INTERFACE_DEFINED__
#define __ICertServerPolicy_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICertServerPolicy
 * at Mon Aug 04 19:41:38 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ICertServerPolicy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("aa000922-ffbe-11cf-8800-00a0c903b83c")
    ICertServerPolicy : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetContext( 
            /* [in] */ LONG Context) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRequestProperty( 
            /* [in] */ const BSTR strPropertyName,
            /* [in] */ LONG PropertyType,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarPropertyValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRequestAttribute( 
            /* [in] */ const BSTR strAttributeName,
            /* [retval][out] */ BSTR __RPC_FAR *pstrAttributeValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCertificateProperty( 
            /* [in] */ const BSTR strPropertyName,
            /* [in] */ LONG PropertyType,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarPropertyValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCertificateProperty( 
            /* [in] */ const BSTR strPropertyName,
            /* [in] */ LONG PropertyType,
            /* [in] */ const VARIANT __RPC_FAR *pvarPropertyValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCertificateExtension( 
            /* [in] */ const BSTR strExtensionName,
            /* [in] */ LONG Type,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCertificateExtensionFlags( 
            /* [retval][out] */ LONG __RPC_FAR *pExtFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCertificateExtension( 
            /* [in] */ const BSTR strExtensionName,
            /* [in] */ LONG Type,
            /* [in] */ LONG ExtFlags,
            /* [in] */ const VARIANT __RPC_FAR *pvarValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumerateExtensionsSetup( 
            /* [in] */ LONG Flags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumerateExtensions( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrExtensionName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumerateExtensionsClose( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumerateAttributesSetup( 
            /* [in] */ LONG Flags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumerateAttributes( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrAttributeName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumerateAttributesClose( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICertServerPolicyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICertServerPolicy __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICertServerPolicy __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICertServerPolicy __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICertServerPolicy __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICertServerPolicy __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICertServerPolicy __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICertServerPolicy __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetContext )( 
            ICertServerPolicy __RPC_FAR * This,
            /* [in] */ LONG Context);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRequestProperty )( 
            ICertServerPolicy __RPC_FAR * This,
            /* [in] */ const BSTR strPropertyName,
            /* [in] */ LONG PropertyType,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarPropertyValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRequestAttribute )( 
            ICertServerPolicy __RPC_FAR * This,
            /* [in] */ const BSTR strAttributeName,
            /* [retval][out] */ BSTR __RPC_FAR *pstrAttributeValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCertificateProperty )( 
            ICertServerPolicy __RPC_FAR * This,
            /* [in] */ const BSTR strPropertyName,
            /* [in] */ LONG PropertyType,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarPropertyValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCertificateProperty )( 
            ICertServerPolicy __RPC_FAR * This,
            /* [in] */ const BSTR strPropertyName,
            /* [in] */ LONG PropertyType,
            /* [in] */ const VARIANT __RPC_FAR *pvarPropertyValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCertificateExtension )( 
            ICertServerPolicy __RPC_FAR * This,
            /* [in] */ const BSTR strExtensionName,
            /* [in] */ LONG Type,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCertificateExtensionFlags )( 
            ICertServerPolicy __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pExtFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCertificateExtension )( 
            ICertServerPolicy __RPC_FAR * This,
            /* [in] */ const BSTR strExtensionName,
            /* [in] */ LONG Type,
            /* [in] */ LONG ExtFlags,
            /* [in] */ const VARIANT __RPC_FAR *pvarValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateExtensionsSetup )( 
            ICertServerPolicy __RPC_FAR * This,
            /* [in] */ LONG Flags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateExtensions )( 
            ICertServerPolicy __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrExtensionName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateExtensionsClose )( 
            ICertServerPolicy __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateAttributesSetup )( 
            ICertServerPolicy __RPC_FAR * This,
            /* [in] */ LONG Flags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateAttributes )( 
            ICertServerPolicy __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrAttributeName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateAttributesClose )( 
            ICertServerPolicy __RPC_FAR * This);
        
        END_INTERFACE
    } ICertServerPolicyVtbl;

    interface ICertServerPolicy
    {
        CONST_VTBL struct ICertServerPolicyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICertServerPolicy_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICertServerPolicy_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICertServerPolicy_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICertServerPolicy_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICertServerPolicy_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICertServerPolicy_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICertServerPolicy_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICertServerPolicy_SetContext(This,Context)	\
    (This)->lpVtbl -> SetContext(This,Context)

#define ICertServerPolicy_GetRequestProperty(This,strPropertyName,PropertyType,pvarPropertyValue)	\
    (This)->lpVtbl -> GetRequestProperty(This,strPropertyName,PropertyType,pvarPropertyValue)

#define ICertServerPolicy_GetRequestAttribute(This,strAttributeName,pstrAttributeValue)	\
    (This)->lpVtbl -> GetRequestAttribute(This,strAttributeName,pstrAttributeValue)

#define ICertServerPolicy_GetCertificateProperty(This,strPropertyName,PropertyType,pvarPropertyValue)	\
    (This)->lpVtbl -> GetCertificateProperty(This,strPropertyName,PropertyType,pvarPropertyValue)

#define ICertServerPolicy_SetCertificateProperty(This,strPropertyName,PropertyType,pvarPropertyValue)	\
    (This)->lpVtbl -> SetCertificateProperty(This,strPropertyName,PropertyType,pvarPropertyValue)

#define ICertServerPolicy_GetCertificateExtension(This,strExtensionName,Type,pvarValue)	\
    (This)->lpVtbl -> GetCertificateExtension(This,strExtensionName,Type,pvarValue)

#define ICertServerPolicy_GetCertificateExtensionFlags(This,pExtFlags)	\
    (This)->lpVtbl -> GetCertificateExtensionFlags(This,pExtFlags)

#define ICertServerPolicy_SetCertificateExtension(This,strExtensionName,Type,ExtFlags,pvarValue)	\
    (This)->lpVtbl -> SetCertificateExtension(This,strExtensionName,Type,ExtFlags,pvarValue)

#define ICertServerPolicy_EnumerateExtensionsSetup(This,Flags)	\
    (This)->lpVtbl -> EnumerateExtensionsSetup(This,Flags)

#define ICertServerPolicy_EnumerateExtensions(This,pstrExtensionName)	\
    (This)->lpVtbl -> EnumerateExtensions(This,pstrExtensionName)

#define ICertServerPolicy_EnumerateExtensionsClose(This)	\
    (This)->lpVtbl -> EnumerateExtensionsClose(This)

#define ICertServerPolicy_EnumerateAttributesSetup(This,Flags)	\
    (This)->lpVtbl -> EnumerateAttributesSetup(This,Flags)

#define ICertServerPolicy_EnumerateAttributes(This,pstrAttributeName)	\
    (This)->lpVtbl -> EnumerateAttributes(This,pstrAttributeName)

#define ICertServerPolicy_EnumerateAttributesClose(This)	\
    (This)->lpVtbl -> EnumerateAttributesClose(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICertServerPolicy_SetContext_Proxy( 
    ICertServerPolicy __RPC_FAR * This,
    /* [in] */ LONG Context);


void __RPC_STUB ICertServerPolicy_SetContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerPolicy_GetRequestProperty_Proxy( 
    ICertServerPolicy __RPC_FAR * This,
    /* [in] */ const BSTR strPropertyName,
    /* [in] */ LONG PropertyType,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarPropertyValue);


void __RPC_STUB ICertServerPolicy_GetRequestProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerPolicy_GetRequestAttribute_Proxy( 
    ICertServerPolicy __RPC_FAR * This,
    /* [in] */ const BSTR strAttributeName,
    /* [retval][out] */ BSTR __RPC_FAR *pstrAttributeValue);


void __RPC_STUB ICertServerPolicy_GetRequestAttribute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerPolicy_GetCertificateProperty_Proxy( 
    ICertServerPolicy __RPC_FAR * This,
    /* [in] */ const BSTR strPropertyName,
    /* [in] */ LONG PropertyType,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarPropertyValue);


void __RPC_STUB ICertServerPolicy_GetCertificateProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerPolicy_SetCertificateProperty_Proxy( 
    ICertServerPolicy __RPC_FAR * This,
    /* [in] */ const BSTR strPropertyName,
    /* [in] */ LONG PropertyType,
    /* [in] */ const VARIANT __RPC_FAR *pvarPropertyValue);


void __RPC_STUB ICertServerPolicy_SetCertificateProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerPolicy_GetCertificateExtension_Proxy( 
    ICertServerPolicy __RPC_FAR * This,
    /* [in] */ const BSTR strExtensionName,
    /* [in] */ LONG Type,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarValue);


void __RPC_STUB ICertServerPolicy_GetCertificateExtension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerPolicy_GetCertificateExtensionFlags_Proxy( 
    ICertServerPolicy __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pExtFlags);


void __RPC_STUB ICertServerPolicy_GetCertificateExtensionFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerPolicy_SetCertificateExtension_Proxy( 
    ICertServerPolicy __RPC_FAR * This,
    /* [in] */ const BSTR strExtensionName,
    /* [in] */ LONG Type,
    /* [in] */ LONG ExtFlags,
    /* [in] */ const VARIANT __RPC_FAR *pvarValue);


void __RPC_STUB ICertServerPolicy_SetCertificateExtension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerPolicy_EnumerateExtensionsSetup_Proxy( 
    ICertServerPolicy __RPC_FAR * This,
    /* [in] */ LONG Flags);


void __RPC_STUB ICertServerPolicy_EnumerateExtensionsSetup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerPolicy_EnumerateExtensions_Proxy( 
    ICertServerPolicy __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrExtensionName);


void __RPC_STUB ICertServerPolicy_EnumerateExtensions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerPolicy_EnumerateExtensionsClose_Proxy( 
    ICertServerPolicy __RPC_FAR * This);


void __RPC_STUB ICertServerPolicy_EnumerateExtensionsClose_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerPolicy_EnumerateAttributesSetup_Proxy( 
    ICertServerPolicy __RPC_FAR * This,
    /* [in] */ LONG Flags);


void __RPC_STUB ICertServerPolicy_EnumerateAttributesSetup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerPolicy_EnumerateAttributes_Proxy( 
    ICertServerPolicy __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrAttributeName);


void __RPC_STUB ICertServerPolicy_EnumerateAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerPolicy_EnumerateAttributesClose_Proxy( 
    ICertServerPolicy __RPC_FAR * This);


void __RPC_STUB ICertServerPolicy_EnumerateAttributesClose_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICertServerPolicy_INTERFACE_DEFINED__ */


#ifndef __ICertServerExit_INTERFACE_DEFINED__
#define __ICertServerExit_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ICertServerExit
 * at Mon Aug 04 19:41:38 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ICertServerExit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4ba9eb90-732c-11d0-8816-00a0c903b83c")
    ICertServerExit : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetContext( 
            /* [in] */ LONG Context) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRequestProperty( 
            /* [in] */ const BSTR strPropertyName,
            /* [in] */ LONG PropertyType,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarPropertyValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRequestAttribute( 
            /* [in] */ const BSTR strAttributeName,
            /* [retval][out] */ BSTR __RPC_FAR *pstrAttributeValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCertificateProperty( 
            /* [in] */ const BSTR strPropertyName,
            /* [in] */ LONG PropertyType,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarPropertyValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCertificateExtension( 
            /* [in] */ const BSTR strExtensionName,
            /* [in] */ LONG Type,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCertificateExtensionFlags( 
            /* [retval][out] */ LONG __RPC_FAR *pExtFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumerateExtensionsSetup( 
            /* [in] */ LONG Flags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumerateExtensions( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrExtensionName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumerateExtensionsClose( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumerateAttributesSetup( 
            /* [in] */ LONG Flags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumerateAttributes( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrAttributeName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumerateAttributesClose( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICertServerExitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICertServerExit __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICertServerExit __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICertServerExit __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICertServerExit __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICertServerExit __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICertServerExit __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICertServerExit __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetContext )( 
            ICertServerExit __RPC_FAR * This,
            /* [in] */ LONG Context);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRequestProperty )( 
            ICertServerExit __RPC_FAR * This,
            /* [in] */ const BSTR strPropertyName,
            /* [in] */ LONG PropertyType,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarPropertyValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRequestAttribute )( 
            ICertServerExit __RPC_FAR * This,
            /* [in] */ const BSTR strAttributeName,
            /* [retval][out] */ BSTR __RPC_FAR *pstrAttributeValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCertificateProperty )( 
            ICertServerExit __RPC_FAR * This,
            /* [in] */ const BSTR strPropertyName,
            /* [in] */ LONG PropertyType,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarPropertyValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCertificateExtension )( 
            ICertServerExit __RPC_FAR * This,
            /* [in] */ const BSTR strExtensionName,
            /* [in] */ LONG Type,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCertificateExtensionFlags )( 
            ICertServerExit __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pExtFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateExtensionsSetup )( 
            ICertServerExit __RPC_FAR * This,
            /* [in] */ LONG Flags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateExtensions )( 
            ICertServerExit __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrExtensionName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateExtensionsClose )( 
            ICertServerExit __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateAttributesSetup )( 
            ICertServerExit __RPC_FAR * This,
            /* [in] */ LONG Flags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateAttributes )( 
            ICertServerExit __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrAttributeName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateAttributesClose )( 
            ICertServerExit __RPC_FAR * This);
        
        END_INTERFACE
    } ICertServerExitVtbl;

    interface ICertServerExit
    {
        CONST_VTBL struct ICertServerExitVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICertServerExit_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICertServerExit_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICertServerExit_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICertServerExit_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICertServerExit_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICertServerExit_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICertServerExit_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICertServerExit_SetContext(This,Context)	\
    (This)->lpVtbl -> SetContext(This,Context)

#define ICertServerExit_GetRequestProperty(This,strPropertyName,PropertyType,pvarPropertyValue)	\
    (This)->lpVtbl -> GetRequestProperty(This,strPropertyName,PropertyType,pvarPropertyValue)

#define ICertServerExit_GetRequestAttribute(This,strAttributeName,pstrAttributeValue)	\
    (This)->lpVtbl -> GetRequestAttribute(This,strAttributeName,pstrAttributeValue)

#define ICertServerExit_GetCertificateProperty(This,strPropertyName,PropertyType,pvarPropertyValue)	\
    (This)->lpVtbl -> GetCertificateProperty(This,strPropertyName,PropertyType,pvarPropertyValue)

#define ICertServerExit_GetCertificateExtension(This,strExtensionName,Type,pvarValue)	\
    (This)->lpVtbl -> GetCertificateExtension(This,strExtensionName,Type,pvarValue)

#define ICertServerExit_GetCertificateExtensionFlags(This,pExtFlags)	\
    (This)->lpVtbl -> GetCertificateExtensionFlags(This,pExtFlags)

#define ICertServerExit_EnumerateExtensionsSetup(This,Flags)	\
    (This)->lpVtbl -> EnumerateExtensionsSetup(This,Flags)

#define ICertServerExit_EnumerateExtensions(This,pstrExtensionName)	\
    (This)->lpVtbl -> EnumerateExtensions(This,pstrExtensionName)

#define ICertServerExit_EnumerateExtensionsClose(This)	\
    (This)->lpVtbl -> EnumerateExtensionsClose(This)

#define ICertServerExit_EnumerateAttributesSetup(This,Flags)	\
    (This)->lpVtbl -> EnumerateAttributesSetup(This,Flags)

#define ICertServerExit_EnumerateAttributes(This,pstrAttributeName)	\
    (This)->lpVtbl -> EnumerateAttributes(This,pstrAttributeName)

#define ICertServerExit_EnumerateAttributesClose(This)	\
    (This)->lpVtbl -> EnumerateAttributesClose(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICertServerExit_SetContext_Proxy( 
    ICertServerExit __RPC_FAR * This,
    /* [in] */ LONG Context);


void __RPC_STUB ICertServerExit_SetContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerExit_GetRequestProperty_Proxy( 
    ICertServerExit __RPC_FAR * This,
    /* [in] */ const BSTR strPropertyName,
    /* [in] */ LONG PropertyType,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarPropertyValue);


void __RPC_STUB ICertServerExit_GetRequestProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerExit_GetRequestAttribute_Proxy( 
    ICertServerExit __RPC_FAR * This,
    /* [in] */ const BSTR strAttributeName,
    /* [retval][out] */ BSTR __RPC_FAR *pstrAttributeValue);


void __RPC_STUB ICertServerExit_GetRequestAttribute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerExit_GetCertificateProperty_Proxy( 
    ICertServerExit __RPC_FAR * This,
    /* [in] */ const BSTR strPropertyName,
    /* [in] */ LONG PropertyType,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarPropertyValue);


void __RPC_STUB ICertServerExit_GetCertificateProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerExit_GetCertificateExtension_Proxy( 
    ICertServerExit __RPC_FAR * This,
    /* [in] */ const BSTR strExtensionName,
    /* [in] */ LONG Type,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarValue);


void __RPC_STUB ICertServerExit_GetCertificateExtension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerExit_GetCertificateExtensionFlags_Proxy( 
    ICertServerExit __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pExtFlags);


void __RPC_STUB ICertServerExit_GetCertificateExtensionFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerExit_EnumerateExtensionsSetup_Proxy( 
    ICertServerExit __RPC_FAR * This,
    /* [in] */ LONG Flags);


void __RPC_STUB ICertServerExit_EnumerateExtensionsSetup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerExit_EnumerateExtensions_Proxy( 
    ICertServerExit __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrExtensionName);


void __RPC_STUB ICertServerExit_EnumerateExtensions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerExit_EnumerateExtensionsClose_Proxy( 
    ICertServerExit __RPC_FAR * This);


void __RPC_STUB ICertServerExit_EnumerateExtensionsClose_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerExit_EnumerateAttributesSetup_Proxy( 
    ICertServerExit __RPC_FAR * This,
    /* [in] */ LONG Flags);


void __RPC_STUB ICertServerExit_EnumerateAttributesSetup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerExit_EnumerateAttributes_Proxy( 
    ICertServerExit __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrAttributeName);


void __RPC_STUB ICertServerExit_EnumerateAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertServerExit_EnumerateAttributesClose_Proxy( 
    ICertServerExit __RPC_FAR * This);


void __RPC_STUB ICertServerExit_EnumerateAttributesClose_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICertServerExit_INTERFACE_DEFINED__ */



#ifndef __CERTIFLib_LIBRARY_DEFINED__
#define __CERTIFLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: CERTIFLib
 * at Mon Aug 04 19:41:38 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_CERTIFLib;

EXTERN_C const CLSID CLSID_CCertServerPolicy;

#ifdef __cplusplus

class DECLSPEC_UUID("aa000926-ffbe-11cf-8800-00a0c903b83c")
CCertServerPolicy;
#endif

EXTERN_C const CLSID CLSID_CCertServerExit;

#ifdef __cplusplus

class DECLSPEC_UUID("4c4a5e40-732c-11d0-8816-00a0c903b83c")
CCertServerExit;
#endif
#endif /* __CERTIFLib_LIBRARY_DEFINED__ */

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
