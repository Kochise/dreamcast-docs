/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.02.88 */
/* at Tue Nov 11 12:35:36 1997
 */
/* Compiler settings for propbag2.idl:
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

#ifndef __propbag2_h__
#define __propbag2_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IPersistPropertyBag2_FWD_DEFINED__
#define __IPersistPropertyBag2_FWD_DEFINED__
typedef interface IPersistPropertyBag2 IPersistPropertyBag2;
#endif 	/* __IPersistPropertyBag2_FWD_DEFINED__ */


#ifndef __IPropertyBag2_FWD_DEFINED__
#define __IPropertyBag2_FWD_DEFINED__
typedef interface IPropertyBag2 IPropertyBag2;
#endif 	/* __IPropertyBag2_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"
#include "oleidl.h"
#include "servprov.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_propbag2_0000
 * at Tue Nov 11 12:35:36 1997
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright 1993 - 1998 Microsoft Corporation.
//
//--------------------------------------------------------------------------




extern RPC_IF_HANDLE __MIDL_itf_propbag2_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_propbag2_0000_v0_0_s_ifspec;

#ifndef __IPersistPropertyBag2_INTERFACE_DEFINED__
#define __IPersistPropertyBag2_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IPersistPropertyBag2
 * at Tue Nov 11 12:35:36 1997
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 


typedef /* [unique] */ IPersistPropertyBag2 __RPC_FAR *LPPERSISTPROPERTYBAG2;


EXTERN_C const IID IID_IPersistPropertyBag2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("22F55881-280B-11d0-A8A9-00A0C90C2004")
    IPersistPropertyBag2 : public IPersist
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE InitNew( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ IPropertyBag2 __RPC_FAR *pPropBag,
            /* [in] */ IErrorLog __RPC_FAR *pErrLog) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Save( 
            /* [in] */ IPropertyBag2 __RPC_FAR *pPropBag,
            /* [in] */ BOOL fClearDirty,
            /* [in] */ BOOL fSaveAllProperties) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsDirty( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPersistPropertyBag2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPersistPropertyBag2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPersistPropertyBag2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPersistPropertyBag2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetClassID )( 
            IPersistPropertyBag2 __RPC_FAR * This,
            /* [out] */ CLSID __RPC_FAR *pClassID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InitNew )( 
            IPersistPropertyBag2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Load )( 
            IPersistPropertyBag2 __RPC_FAR * This,
            /* [in] */ IPropertyBag2 __RPC_FAR *pPropBag,
            /* [in] */ IErrorLog __RPC_FAR *pErrLog);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IPersistPropertyBag2 __RPC_FAR * This,
            /* [in] */ IPropertyBag2 __RPC_FAR *pPropBag,
            /* [in] */ BOOL fClearDirty,
            /* [in] */ BOOL fSaveAllProperties);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsDirty )( 
            IPersistPropertyBag2 __RPC_FAR * This);
        
        END_INTERFACE
    } IPersistPropertyBag2Vtbl;

    interface IPersistPropertyBag2
    {
        CONST_VTBL struct IPersistPropertyBag2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPersistPropertyBag2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPersistPropertyBag2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPersistPropertyBag2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPersistPropertyBag2_GetClassID(This,pClassID)	\
    (This)->lpVtbl -> GetClassID(This,pClassID)


#define IPersistPropertyBag2_InitNew(This)	\
    (This)->lpVtbl -> InitNew(This)

#define IPersistPropertyBag2_Load(This,pPropBag,pErrLog)	\
    (This)->lpVtbl -> Load(This,pPropBag,pErrLog)

#define IPersistPropertyBag2_Save(This,pPropBag,fClearDirty,fSaveAllProperties)	\
    (This)->lpVtbl -> Save(This,pPropBag,fClearDirty,fSaveAllProperties)

#define IPersistPropertyBag2_IsDirty(This)	\
    (This)->lpVtbl -> IsDirty(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPersistPropertyBag2_InitNew_Proxy( 
    IPersistPropertyBag2 __RPC_FAR * This);


void __RPC_STUB IPersistPropertyBag2_InitNew_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPersistPropertyBag2_Load_Proxy( 
    IPersistPropertyBag2 __RPC_FAR * This,
    /* [in] */ IPropertyBag2 __RPC_FAR *pPropBag,
    /* [in] */ IErrorLog __RPC_FAR *pErrLog);


void __RPC_STUB IPersistPropertyBag2_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPersistPropertyBag2_Save_Proxy( 
    IPersistPropertyBag2 __RPC_FAR * This,
    /* [in] */ IPropertyBag2 __RPC_FAR *pPropBag,
    /* [in] */ BOOL fClearDirty,
    /* [in] */ BOOL fSaveAllProperties);


void __RPC_STUB IPersistPropertyBag2_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPersistPropertyBag2_IsDirty_Proxy( 
    IPersistPropertyBag2 __RPC_FAR * This);


void __RPC_STUB IPersistPropertyBag2_IsDirty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPersistPropertyBag2_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_propbag2_0141
 * at Tue Nov 11 12:35:36 1997
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef 
enum _tagPROPBAG2_TYPE
    {	PROPBAG2_TYPE_UNDEFINED	= 0,
	PROPBAG2_TYPE_DATA	= 1,
	PROPBAG2_TYPE_URL	= 2,
	PROPBAG2_TYPE_OBJECT	= 3,
	PROPBAG2_TYPE_STREAM	= 4,
	PROPBAG2_TYPE_STORAGE	= 5,
	PROPBAG2_TYPE_MONIKER	= 6
    }	PROPBAG2_TYPE;

typedef struct  _tagPROPBAG2
    {
    DWORD dwType;
    VARTYPE vt;
    CLIPFORMAT cfType;
    DWORD dwHint;
    LPOLESTR pstrName;
    CLSID clsid;
    }	PROPBAG2;



extern RPC_IF_HANDLE __MIDL_itf_propbag2_0141_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_propbag2_0141_v0_0_s_ifspec;

#ifndef __IPropertyBag2_INTERFACE_DEFINED__
#define __IPropertyBag2_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IPropertyBag2
 * at Tue Nov 11 12:35:36 1997
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 


typedef /* [unique] */ IPropertyBag2 __RPC_FAR *LPPROPERTYBAG2;


EXTERN_C const IID IID_IPropertyBag2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("22F55882-280B-11d0-A8A9-00A0C90C2004")
    IPropertyBag2 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Read( 
            /* [in] */ ULONG cProperties,
            /* [in] */ PROPBAG2 __RPC_FAR *pPropBag,
            /* [in] */ IErrorLog __RPC_FAR *pErrLog,
            /* [out] */ VARIANT __RPC_FAR *pvarValue,
            /* [out] */ HRESULT __RPC_FAR *phrError) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Write( 
            /* [in] */ ULONG cProperties,
            /* [in] */ PROPBAG2 __RPC_FAR *pPropBag,
            /* [in] */ VARIANT __RPC_FAR *pvarValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CountProperties( 
            /* [out] */ ULONG __RPC_FAR *pcProperties) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPropertyInfo( 
            /* [in] */ ULONG iProperty,
            /* [in] */ ULONG cProperties,
            /* [out] */ PROPBAG2 __RPC_FAR *pPropBag,
            /* [out] */ ULONG __RPC_FAR *pcProperties) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LoadObject( 
            /* [in] */ LPCOLESTR pstrName,
            /* [in] */ DWORD dwHint,
            /* [in] */ IUnknown __RPC_FAR *pUnkObject,
            /* [in] */ IErrorLog __RPC_FAR *pErrLog) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPropertyBag2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPropertyBag2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPropertyBag2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPropertyBag2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read )( 
            IPropertyBag2 __RPC_FAR * This,
            /* [in] */ ULONG cProperties,
            /* [in] */ PROPBAG2 __RPC_FAR *pPropBag,
            /* [in] */ IErrorLog __RPC_FAR *pErrLog,
            /* [out] */ VARIANT __RPC_FAR *pvarValue,
            /* [out] */ HRESULT __RPC_FAR *phrError);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Write )( 
            IPropertyBag2 __RPC_FAR * This,
            /* [in] */ ULONG cProperties,
            /* [in] */ PROPBAG2 __RPC_FAR *pPropBag,
            /* [in] */ VARIANT __RPC_FAR *pvarValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CountProperties )( 
            IPropertyBag2 __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *pcProperties);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPropertyInfo )( 
            IPropertyBag2 __RPC_FAR * This,
            /* [in] */ ULONG iProperty,
            /* [in] */ ULONG cProperties,
            /* [out] */ PROPBAG2 __RPC_FAR *pPropBag,
            /* [out] */ ULONG __RPC_FAR *pcProperties);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadObject )( 
            IPropertyBag2 __RPC_FAR * This,
            /* [in] */ LPCOLESTR pstrName,
            /* [in] */ DWORD dwHint,
            /* [in] */ IUnknown __RPC_FAR *pUnkObject,
            /* [in] */ IErrorLog __RPC_FAR *pErrLog);
        
        END_INTERFACE
    } IPropertyBag2Vtbl;

    interface IPropertyBag2
    {
        CONST_VTBL struct IPropertyBag2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPropertyBag2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPropertyBag2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPropertyBag2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPropertyBag2_Read(This,cProperties,pPropBag,pErrLog,pvarValue,phrError)	\
    (This)->lpVtbl -> Read(This,cProperties,pPropBag,pErrLog,pvarValue,phrError)

#define IPropertyBag2_Write(This,cProperties,pPropBag,pvarValue)	\
    (This)->lpVtbl -> Write(This,cProperties,pPropBag,pvarValue)

#define IPropertyBag2_CountProperties(This,pcProperties)	\
    (This)->lpVtbl -> CountProperties(This,pcProperties)

#define IPropertyBag2_GetPropertyInfo(This,iProperty,cProperties,pPropBag,pcProperties)	\
    (This)->lpVtbl -> GetPropertyInfo(This,iProperty,cProperties,pPropBag,pcProperties)

#define IPropertyBag2_LoadObject(This,pstrName,dwHint,pUnkObject,pErrLog)	\
    (This)->lpVtbl -> LoadObject(This,pstrName,dwHint,pUnkObject,pErrLog)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPropertyBag2_Read_Proxy( 
    IPropertyBag2 __RPC_FAR * This,
    /* [in] */ ULONG cProperties,
    /* [in] */ PROPBAG2 __RPC_FAR *pPropBag,
    /* [in] */ IErrorLog __RPC_FAR *pErrLog,
    /* [out] */ VARIANT __RPC_FAR *pvarValue,
    /* [out] */ HRESULT __RPC_FAR *phrError);


void __RPC_STUB IPropertyBag2_Read_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyBag2_Write_Proxy( 
    IPropertyBag2 __RPC_FAR * This,
    /* [in] */ ULONG cProperties,
    /* [in] */ PROPBAG2 __RPC_FAR *pPropBag,
    /* [in] */ VARIANT __RPC_FAR *pvarValue);


void __RPC_STUB IPropertyBag2_Write_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyBag2_CountProperties_Proxy( 
    IPropertyBag2 __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *pcProperties);


void __RPC_STUB IPropertyBag2_CountProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyBag2_GetPropertyInfo_Proxy( 
    IPropertyBag2 __RPC_FAR * This,
    /* [in] */ ULONG iProperty,
    /* [in] */ ULONG cProperties,
    /* [out] */ PROPBAG2 __RPC_FAR *pPropBag,
    /* [out] */ ULONG __RPC_FAR *pcProperties);


void __RPC_STUB IPropertyBag2_GetPropertyInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPropertyBag2_LoadObject_Proxy( 
    IPropertyBag2 __RPC_FAR * This,
    /* [in] */ LPCOLESTR pstrName,
    /* [in] */ DWORD dwHint,
    /* [in] */ IUnknown __RPC_FAR *pUnkObject,
    /* [in] */ IErrorLog __RPC_FAR *pErrLog);


void __RPC_STUB IPropertyBag2_LoadObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPropertyBag2_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  CLIPFORMAT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , CLIPFORMAT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  CLIPFORMAT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, CLIPFORMAT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  CLIPFORMAT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, CLIPFORMAT __RPC_FAR * ); 
void                      __RPC_USER  CLIPFORMAT_UserFree(     unsigned long __RPC_FAR *, CLIPFORMAT __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
