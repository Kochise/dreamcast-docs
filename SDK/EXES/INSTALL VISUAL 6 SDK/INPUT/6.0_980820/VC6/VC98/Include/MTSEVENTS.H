/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Thu Sep 11 16:03:07 1997
 */
/* Compiler settings for mtsevents.idl:
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

#ifndef __mtsevents_h__
#define __mtsevents_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IMtsEvents_FWD_DEFINED__
#define __IMtsEvents_FWD_DEFINED__
typedef interface IMtsEvents IMtsEvents;
#endif 	/* __IMtsEvents_FWD_DEFINED__ */


#ifndef __IMtsEventInfo_FWD_DEFINED__
#define __IMtsEventInfo_FWD_DEFINED__
typedef interface IMtsEventInfo IMtsEventInfo;
#endif 	/* __IMtsEventInfo_FWD_DEFINED__ */


#ifndef __IEventMoniker_FWD_DEFINED__
#define __IEventMoniker_FWD_DEFINED__
typedef interface IEventMoniker IEventMoniker;
#endif 	/* __IEventMoniker_FWD_DEFINED__ */


#ifndef __IMTSLocater_FWD_DEFINED__
#define __IMTSLocater_FWD_DEFINED__
typedef interface IMTSLocater IMTSLocater;
#endif 	/* __IMTSLocater_FWD_DEFINED__ */


#ifndef __CoMTSEvents_FWD_DEFINED__
#define __CoMTSEvents_FWD_DEFINED__

#ifdef __cplusplus
typedef class CoMTSEvents CoMTSEvents;
#else
typedef struct CoMTSEvents CoMTSEvents;
#endif /* __cplusplus */

#endif 	/* __CoMTSEvents_FWD_DEFINED__ */


#ifndef __EventMoniker_FWD_DEFINED__
#define __EventMoniker_FWD_DEFINED__

#ifdef __cplusplus
typedef class EventMoniker EventMoniker;
#else
typedef struct EventMoniker EventMoniker;
#endif /* __cplusplus */

#endif 	/* __EventMoniker_FWD_DEFINED__ */


#ifndef __CoMTSLocater_FWD_DEFINED__
#define __CoMTSLocater_FWD_DEFINED__

#ifdef __cplusplus
typedef class CoMTSLocater CoMTSLocater;
#else
typedef struct CoMTSLocater CoMTSLocater;
#endif /* __cplusplus */

#endif 	/* __CoMTSLocater_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "eventcpts.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IMtsEvents_INTERFACE_DEFINED__
#define __IMtsEvents_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMtsEvents
 * at Thu Sep 11 16:03:07 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IMtsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("BACEDF4D-74AB-11D0-B162-00AA00BA3258")
    IMtsEvents : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PackageName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PackageGuid( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PostEvent( 
            /* [in] */ VARIANT __RPC_FAR *vEvent) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FireEvents( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetProcessID( 
            /* [retval][out] */ long __RPC_FAR *id) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMtsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMtsEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMtsEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMtsEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMtsEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMtsEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMtsEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMtsEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PackageName )( 
            IMtsEvents __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PackageGuid )( 
            IMtsEvents __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PostEvent )( 
            IMtsEvents __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *vEvent);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FireEvents )( 
            IMtsEvents __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProcessID )( 
            IMtsEvents __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *id);
        
        END_INTERFACE
    } IMtsEventsVtbl;

    interface IMtsEvents
    {
        CONST_VTBL struct IMtsEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMtsEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMtsEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMtsEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMtsEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMtsEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMtsEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMtsEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMtsEvents_get_PackageName(This,pVal)	\
    (This)->lpVtbl -> get_PackageName(This,pVal)

#define IMtsEvents_get_PackageGuid(This,pVal)	\
    (This)->lpVtbl -> get_PackageGuid(This,pVal)

#define IMtsEvents_PostEvent(This,vEvent)	\
    (This)->lpVtbl -> PostEvent(This,vEvent)

#define IMtsEvents_get_FireEvents(This,pVal)	\
    (This)->lpVtbl -> get_FireEvents(This,pVal)

#define IMtsEvents_GetProcessID(This,id)	\
    (This)->lpVtbl -> GetProcessID(This,id)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMtsEvents_get_PackageName_Proxy( 
    IMtsEvents __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IMtsEvents_get_PackageName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMtsEvents_get_PackageGuid_Proxy( 
    IMtsEvents __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IMtsEvents_get_PackageGuid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMtsEvents_PostEvent_Proxy( 
    IMtsEvents __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *vEvent);


void __RPC_STUB IMtsEvents_PostEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMtsEvents_get_FireEvents_Proxy( 
    IMtsEvents __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IMtsEvents_get_FireEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMtsEvents_GetProcessID_Proxy( 
    IMtsEvents __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *id);


void __RPC_STUB IMtsEvents_GetProcessID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMtsEvents_INTERFACE_DEFINED__ */


#ifndef __IMtsEventInfo_INTERFACE_DEFINED__
#define __IMtsEventInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMtsEventInfo
 * at Thu Sep 11 16:03:07 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IMtsEventInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("D56C3DC1-8482-11d0-B170-00AA00BA3258")
    IMtsEventInfo : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Names( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pUnk) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DisplayName( 
            /* [retval][out] */ BSTR __RPC_FAR *sDisplayName) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_EventID( 
            /* [retval][out] */ BSTR __RPC_FAR *sGuidEventID) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *lCount) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Value( 
            /* [in] */ BSTR sKey,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMtsEventInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMtsEventInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMtsEventInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMtsEventInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMtsEventInfo __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMtsEventInfo __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMtsEventInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMtsEventInfo __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Names )( 
            IMtsEventInfo __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pUnk);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DisplayName )( 
            IMtsEventInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *sDisplayName);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EventID )( 
            IMtsEventInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *sGuidEventID);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IMtsEventInfo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *lCount);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Value )( 
            IMtsEventInfo __RPC_FAR * This,
            /* [in] */ BSTR sKey,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        END_INTERFACE
    } IMtsEventInfoVtbl;

    interface IMtsEventInfo
    {
        CONST_VTBL struct IMtsEventInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMtsEventInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMtsEventInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMtsEventInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMtsEventInfo_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMtsEventInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMtsEventInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMtsEventInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMtsEventInfo_get_Names(This,pUnk)	\
    (This)->lpVtbl -> get_Names(This,pUnk)

#define IMtsEventInfo_get_DisplayName(This,sDisplayName)	\
    (This)->lpVtbl -> get_DisplayName(This,sDisplayName)

#define IMtsEventInfo_get_EventID(This,sGuidEventID)	\
    (This)->lpVtbl -> get_EventID(This,sGuidEventID)

#define IMtsEventInfo_get_Count(This,lCount)	\
    (This)->lpVtbl -> get_Count(This,lCount)

#define IMtsEventInfo_get_Value(This,sKey,pVal)	\
    (This)->lpVtbl -> get_Value(This,sKey,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMtsEventInfo_get_Names_Proxy( 
    IMtsEventInfo __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pUnk);


void __RPC_STUB IMtsEventInfo_get_Names_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMtsEventInfo_get_DisplayName_Proxy( 
    IMtsEventInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *sDisplayName);


void __RPC_STUB IMtsEventInfo_get_DisplayName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMtsEventInfo_get_EventID_Proxy( 
    IMtsEventInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *sGuidEventID);


void __RPC_STUB IMtsEventInfo_get_EventID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMtsEventInfo_get_Count_Proxy( 
    IMtsEventInfo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *lCount);


void __RPC_STUB IMtsEventInfo_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMtsEventInfo_get_Value_Proxy( 
    IMtsEventInfo __RPC_FAR * This,
    /* [in] */ BSTR sKey,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IMtsEventInfo_get_Value_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMtsEventInfo_INTERFACE_DEFINED__ */


#ifndef __IEventMoniker_INTERFACE_DEFINED__
#define __IEventMoniker_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IEventMoniker
 * at Thu Sep 11 16:03:07 1997
 * using MIDL 3.01.75
 ****************************************/
/* [object][unique][helpstring][hidden][uuid] */ 



EXTERN_C const IID IID_IEventMoniker;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C8CF32B3-7885-11D0-B169-00AA00BA3258")
    IEventMoniker : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ID( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_EventObj( 
            /* [in] */ IUnknown __RPC_FAR *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEventMonikerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEventMoniker __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEventMoniker __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEventMoniker __RPC_FAR * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IEventMoniker __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IEventMoniker __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ID )( 
            IEventMoniker __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ID )( 
            IEventMoniker __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EventObj )( 
            IEventMoniker __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *newVal);
        
        END_INTERFACE
    } IEventMonikerVtbl;

    interface IEventMoniker
    {
        CONST_VTBL struct IEventMonikerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEventMoniker_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEventMoniker_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEventMoniker_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEventMoniker_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IEventMoniker_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IEventMoniker_get_ID(This,pVal)	\
    (This)->lpVtbl -> get_ID(This,pVal)

#define IEventMoniker_put_ID(This,newVal)	\
    (This)->lpVtbl -> put_ID(This,newVal)

#define IEventMoniker_put_EventObj(This,newVal)	\
    (This)->lpVtbl -> put_EventObj(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IEventMoniker_get_Name_Proxy( 
    IEventMoniker __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IEventMoniker_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IEventMoniker_put_Name_Proxy( 
    IEventMoniker __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IEventMoniker_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IEventMoniker_get_ID_Proxy( 
    IEventMoniker __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEventMoniker_get_ID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IEventMoniker_put_ID_Proxy( 
    IEventMoniker __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IEventMoniker_put_ID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IEventMoniker_put_EventObj_Proxy( 
    IEventMoniker __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *newVal);


void __RPC_STUB IEventMoniker_put_EventObj_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEventMoniker_INTERFACE_DEFINED__ */


#ifndef __IMTSLocater_INTERFACE_DEFINED__
#define __IMTSLocater_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMTSLocater
 * at Thu Sep 11 16:03:07 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IMTSLocater;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("D19B8BFD-7F88-11D0-B16E-00AA00BA3258")
    IMTSLocater : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEventDispatcher( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pUnk) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMTSLocaterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMTSLocater __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMTSLocater __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMTSLocater __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMTSLocater __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMTSLocater __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMTSLocater __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMTSLocater __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEventDispatcher )( 
            IMTSLocater __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pUnk);
        
        END_INTERFACE
    } IMTSLocaterVtbl;

    interface IMTSLocater
    {
        CONST_VTBL struct IMTSLocaterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMTSLocater_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMTSLocater_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMTSLocater_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMTSLocater_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMTSLocater_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMTSLocater_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMTSLocater_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMTSLocater_GetEventDispatcher(This,pUnk)	\
    (This)->lpVtbl -> GetEventDispatcher(This,pUnk)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMTSLocater_GetEventDispatcher_Proxy( 
    IMTSLocater __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pUnk);


void __RPC_STUB IMTSLocater_GetEventDispatcher_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMTSLocater_INTERFACE_DEFINED__ */



#ifndef __MTSEVENTSLib_LIBRARY_DEFINED__
#define __MTSEVENTSLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: MTSEVENTSLib
 * at Thu Sep 11 16:03:07 1997
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_MTSEVENTSLib;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CoMTSEvents;

class DECLSPEC_UUID("BACEDF4E-74AB-11D0-B162-00AA00BA3258")
CoMTSEvents;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_EventMoniker;

class DECLSPEC_UUID("C8CF32B4-7885-11D0-B169-00AA00BA3258")
EventMoniker;
#endif

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_CoMTSLocater;

class DECLSPEC_UUID("D19B8BFE-7F88-11D0-B16E-00AA00BA3258")
CoMTSLocater;
#endif
#endif /* __MTSEVENTSLib_LIBRARY_DEFINED__ */

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
