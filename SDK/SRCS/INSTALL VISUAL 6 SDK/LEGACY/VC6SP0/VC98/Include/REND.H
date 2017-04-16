/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Wed Sep 03 19:09:28 1997
 */
/* Compiler settings for rend.idl:
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

#ifndef __rend_h__
#define __rend_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ITConference_FWD_DEFINED__
#define __ITConference_FWD_DEFINED__
typedef interface ITConference ITConference;
#endif 	/* __ITConference_FWD_DEFINED__ */


#ifndef __ITConferenceDirectory_FWD_DEFINED__
#define __ITConferenceDirectory_FWD_DEFINED__
typedef interface ITConferenceDirectory ITConferenceDirectory;
#endif 	/* __ITConferenceDirectory_FWD_DEFINED__ */


#ifndef __ConferenceDirectory_FWD_DEFINED__
#define __ConferenceDirectory_FWD_DEFINED__

#ifdef __cplusplus
typedef class ConferenceDirectory ConferenceDirectory;
#else
typedef struct ConferenceDirectory ConferenceDirectory;
#endif /* __cplusplus */

#endif 	/* __ConferenceDirectory_FWD_DEFINED__ */


#ifndef __Conference_FWD_DEFINED__
#define __Conference_FWD_DEFINED__

#ifdef __cplusplus
typedef class Conference Conference;
#else
typedef struct Conference Conference;
#endif /* __cplusplus */

#endif 	/* __Conference_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "rndnot.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ITConference_INTERFACE_DEFINED__
#define __ITConference_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITConference
 * at Wed Sep 03 19:09:28 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ITConference;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F1029E5D-CB5B-11D0-8D59-00C04FD91AC0")
    ITConference : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *ppName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR pName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProtocolId( 
            /* [retval][out] */ BSTR __RPC_FAR *ppProtocolId) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProtocolId( 
            /* [in] */ BSTR pProtocolId) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SubType( 
            /* [retval][out] */ BSTR __RPC_FAR *ppSubType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SubType( 
            /* [in] */ BSTR pSubType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Originator( 
            /* [retval][out] */ BSTR __RPC_FAR *ppOriginator) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Originator( 
            /* [in] */ BSTR pOriginator) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AnnouncementScope( 
            /* [retval][out] */ BSTR __RPC_FAR *ppAnnoucementScope) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AnnouncementScope( 
            /* [in] */ BSTR pAnnouncementScope) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AdvertisingScope( 
            /* [retval][out] */ RND_ADVERTISING_SCOPE __RPC_FAR *pAdvertisingScope) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AdvertisingScope( 
            /* [in] */ RND_ADVERTISING_SCOPE AdvertisingScope) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Url( 
            /* [retval][out] */ BSTR __RPC_FAR *ppUrl) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Url( 
            /* [in] */ BSTR pUrl) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *ppDescription) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR pDescription) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsEncrypted( 
            /* [retval][out] */ BSTR __RPC_FAR *ppIsEncrypted) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IsEncrypted( 
            /* [in] */ BSTR pIsEncrypted) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConferenceBlob( 
            /* [retval][out] */ BSTR __RPC_FAR *ppConferenceBlob) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConferenceBlob( 
            /* [in] */ BSTR pConferenceBlob) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetStartTime( 
            /* [out] */ USHORT __RPC_FAR *pYear,
            /* [out] */ BYTE __RPC_FAR *pMonth,
            /* [out] */ BYTE __RPC_FAR *pDay,
            /* [out] */ BYTE __RPC_FAR *pHour,
            /* [out] */ BYTE __RPC_FAR *pMinute) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetStartTime( 
            /* [in] */ USHORT Year,
            /* [in] */ BYTE Month,
            /* [in] */ BYTE Day,
            /* [in] */ BYTE Hour,
            /* [in] */ BYTE Minute) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetStopTime( 
            /* [out] */ USHORT __RPC_FAR *pYear,
            /* [out] */ BYTE __RPC_FAR *pMonth,
            /* [out] */ BYTE __RPC_FAR *pDay,
            /* [out] */ BYTE __RPC_FAR *pHour,
            /* [out] */ BYTE __RPC_FAR *pMinute) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetStopTime( 
            /* [in] */ USHORT Year,
            /* [in] */ BYTE Month,
            /* [in] */ BYTE Day,
            /* [in] */ BYTE Hour,
            /* [in] */ BYTE Minute) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITConferenceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITConference __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITConference __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITConference __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITConference __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITConference __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITConference __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITConference __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ITConference __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            ITConference __RPC_FAR * This,
            /* [in] */ BSTR pName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProtocolId )( 
            ITConference __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppProtocolId);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProtocolId )( 
            ITConference __RPC_FAR * This,
            /* [in] */ BSTR pProtocolId);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SubType )( 
            ITConference __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppSubType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SubType )( 
            ITConference __RPC_FAR * This,
            /* [in] */ BSTR pSubType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Originator )( 
            ITConference __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppOriginator);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Originator )( 
            ITConference __RPC_FAR * This,
            /* [in] */ BSTR pOriginator);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AnnouncementScope )( 
            ITConference __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppAnnoucementScope);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AnnouncementScope )( 
            ITConference __RPC_FAR * This,
            /* [in] */ BSTR pAnnouncementScope);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AdvertisingScope )( 
            ITConference __RPC_FAR * This,
            /* [retval][out] */ RND_ADVERTISING_SCOPE __RPC_FAR *pAdvertisingScope);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AdvertisingScope )( 
            ITConference __RPC_FAR * This,
            /* [in] */ RND_ADVERTISING_SCOPE AdvertisingScope);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Url )( 
            ITConference __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppUrl);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Url )( 
            ITConference __RPC_FAR * This,
            /* [in] */ BSTR pUrl);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            ITConference __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppDescription);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Description )( 
            ITConference __RPC_FAR * This,
            /* [in] */ BSTR pDescription);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsEncrypted )( 
            ITConference __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppIsEncrypted);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IsEncrypted )( 
            ITConference __RPC_FAR * This,
            /* [in] */ BSTR pIsEncrypted);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConferenceBlob )( 
            ITConference __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppConferenceBlob);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConferenceBlob )( 
            ITConference __RPC_FAR * This,
            /* [in] */ BSTR pConferenceBlob);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStartTime )( 
            ITConference __RPC_FAR * This,
            /* [out] */ USHORT __RPC_FAR *pYear,
            /* [out] */ BYTE __RPC_FAR *pMonth,
            /* [out] */ BYTE __RPC_FAR *pDay,
            /* [out] */ BYTE __RPC_FAR *pHour,
            /* [out] */ BYTE __RPC_FAR *pMinute);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetStartTime )( 
            ITConference __RPC_FAR * This,
            /* [in] */ USHORT Year,
            /* [in] */ BYTE Month,
            /* [in] */ BYTE Day,
            /* [in] */ BYTE Hour,
            /* [in] */ BYTE Minute);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStopTime )( 
            ITConference __RPC_FAR * This,
            /* [out] */ USHORT __RPC_FAR *pYear,
            /* [out] */ BYTE __RPC_FAR *pMonth,
            /* [out] */ BYTE __RPC_FAR *pDay,
            /* [out] */ BYTE __RPC_FAR *pHour,
            /* [out] */ BYTE __RPC_FAR *pMinute);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetStopTime )( 
            ITConference __RPC_FAR * This,
            /* [in] */ USHORT Year,
            /* [in] */ BYTE Month,
            /* [in] */ BYTE Day,
            /* [in] */ BYTE Hour,
            /* [in] */ BYTE Minute);
        
        END_INTERFACE
    } ITConferenceVtbl;

    interface ITConference
    {
        CONST_VTBL struct ITConferenceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITConference_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITConference_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITConference_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITConference_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITConference_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITConference_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITConference_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITConference_get_Name(This,ppName)	\
    (This)->lpVtbl -> get_Name(This,ppName)

#define ITConference_put_Name(This,pName)	\
    (This)->lpVtbl -> put_Name(This,pName)

#define ITConference_get_ProtocolId(This,ppProtocolId)	\
    (This)->lpVtbl -> get_ProtocolId(This,ppProtocolId)

#define ITConference_put_ProtocolId(This,pProtocolId)	\
    (This)->lpVtbl -> put_ProtocolId(This,pProtocolId)

#define ITConference_get_SubType(This,ppSubType)	\
    (This)->lpVtbl -> get_SubType(This,ppSubType)

#define ITConference_put_SubType(This,pSubType)	\
    (This)->lpVtbl -> put_SubType(This,pSubType)

#define ITConference_get_Originator(This,ppOriginator)	\
    (This)->lpVtbl -> get_Originator(This,ppOriginator)

#define ITConference_put_Originator(This,pOriginator)	\
    (This)->lpVtbl -> put_Originator(This,pOriginator)

#define ITConference_get_AnnouncementScope(This,ppAnnoucementScope)	\
    (This)->lpVtbl -> get_AnnouncementScope(This,ppAnnoucementScope)

#define ITConference_put_AnnouncementScope(This,pAnnouncementScope)	\
    (This)->lpVtbl -> put_AnnouncementScope(This,pAnnouncementScope)

#define ITConference_get_AdvertisingScope(This,pAdvertisingScope)	\
    (This)->lpVtbl -> get_AdvertisingScope(This,pAdvertisingScope)

#define ITConference_put_AdvertisingScope(This,AdvertisingScope)	\
    (This)->lpVtbl -> put_AdvertisingScope(This,AdvertisingScope)

#define ITConference_get_Url(This,ppUrl)	\
    (This)->lpVtbl -> get_Url(This,ppUrl)

#define ITConference_put_Url(This,pUrl)	\
    (This)->lpVtbl -> put_Url(This,pUrl)

#define ITConference_get_Description(This,ppDescription)	\
    (This)->lpVtbl -> get_Description(This,ppDescription)

#define ITConference_put_Description(This,pDescription)	\
    (This)->lpVtbl -> put_Description(This,pDescription)

#define ITConference_get_IsEncrypted(This,ppIsEncrypted)	\
    (This)->lpVtbl -> get_IsEncrypted(This,ppIsEncrypted)

#define ITConference_put_IsEncrypted(This,pIsEncrypted)	\
    (This)->lpVtbl -> put_IsEncrypted(This,pIsEncrypted)

#define ITConference_get_ConferenceBlob(This,ppConferenceBlob)	\
    (This)->lpVtbl -> get_ConferenceBlob(This,ppConferenceBlob)

#define ITConference_put_ConferenceBlob(This,pConferenceBlob)	\
    (This)->lpVtbl -> put_ConferenceBlob(This,pConferenceBlob)

#define ITConference_GetStartTime(This,pYear,pMonth,pDay,pHour,pMinute)	\
    (This)->lpVtbl -> GetStartTime(This,pYear,pMonth,pDay,pHour,pMinute)

#define ITConference_SetStartTime(This,Year,Month,Day,Hour,Minute)	\
    (This)->lpVtbl -> SetStartTime(This,Year,Month,Day,Hour,Minute)

#define ITConference_GetStopTime(This,pYear,pMonth,pDay,pHour,pMinute)	\
    (This)->lpVtbl -> GetStopTime(This,pYear,pMonth,pDay,pHour,pMinute)

#define ITConference_SetStopTime(This,Year,Month,Day,Hour,Minute)	\
    (This)->lpVtbl -> SetStopTime(This,Year,Month,Day,Hour,Minute)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConference_get_Name_Proxy( 
    ITConference __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppName);


void __RPC_STUB ITConference_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITConference_put_Name_Proxy( 
    ITConference __RPC_FAR * This,
    /* [in] */ BSTR pName);


void __RPC_STUB ITConference_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConference_get_ProtocolId_Proxy( 
    ITConference __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppProtocolId);


void __RPC_STUB ITConference_get_ProtocolId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITConference_put_ProtocolId_Proxy( 
    ITConference __RPC_FAR * This,
    /* [in] */ BSTR pProtocolId);


void __RPC_STUB ITConference_put_ProtocolId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConference_get_SubType_Proxy( 
    ITConference __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppSubType);


void __RPC_STUB ITConference_get_SubType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITConference_put_SubType_Proxy( 
    ITConference __RPC_FAR * This,
    /* [in] */ BSTR pSubType);


void __RPC_STUB ITConference_put_SubType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConference_get_Originator_Proxy( 
    ITConference __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppOriginator);


void __RPC_STUB ITConference_get_Originator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITConference_put_Originator_Proxy( 
    ITConference __RPC_FAR * This,
    /* [in] */ BSTR pOriginator);


void __RPC_STUB ITConference_put_Originator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConference_get_AnnouncementScope_Proxy( 
    ITConference __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppAnnoucementScope);


void __RPC_STUB ITConference_get_AnnouncementScope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITConference_put_AnnouncementScope_Proxy( 
    ITConference __RPC_FAR * This,
    /* [in] */ BSTR pAnnouncementScope);


void __RPC_STUB ITConference_put_AnnouncementScope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConference_get_AdvertisingScope_Proxy( 
    ITConference __RPC_FAR * This,
    /* [retval][out] */ RND_ADVERTISING_SCOPE __RPC_FAR *pAdvertisingScope);


void __RPC_STUB ITConference_get_AdvertisingScope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITConference_put_AdvertisingScope_Proxy( 
    ITConference __RPC_FAR * This,
    /* [in] */ RND_ADVERTISING_SCOPE AdvertisingScope);


void __RPC_STUB ITConference_put_AdvertisingScope_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConference_get_Url_Proxy( 
    ITConference __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppUrl);


void __RPC_STUB ITConference_get_Url_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITConference_put_Url_Proxy( 
    ITConference __RPC_FAR * This,
    /* [in] */ BSTR pUrl);


void __RPC_STUB ITConference_put_Url_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConference_get_Description_Proxy( 
    ITConference __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppDescription);


void __RPC_STUB ITConference_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITConference_put_Description_Proxy( 
    ITConference __RPC_FAR * This,
    /* [in] */ BSTR pDescription);


void __RPC_STUB ITConference_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConference_get_IsEncrypted_Proxy( 
    ITConference __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppIsEncrypted);


void __RPC_STUB ITConference_get_IsEncrypted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITConference_put_IsEncrypted_Proxy( 
    ITConference __RPC_FAR * This,
    /* [in] */ BSTR pIsEncrypted);


void __RPC_STUB ITConference_put_IsEncrypted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConference_get_ConferenceBlob_Proxy( 
    ITConference __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppConferenceBlob);


void __RPC_STUB ITConference_get_ConferenceBlob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITConference_put_ConferenceBlob_Proxy( 
    ITConference __RPC_FAR * This,
    /* [in] */ BSTR pConferenceBlob);


void __RPC_STUB ITConference_put_ConferenceBlob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITConference_GetStartTime_Proxy( 
    ITConference __RPC_FAR * This,
    /* [out] */ USHORT __RPC_FAR *pYear,
    /* [out] */ BYTE __RPC_FAR *pMonth,
    /* [out] */ BYTE __RPC_FAR *pDay,
    /* [out] */ BYTE __RPC_FAR *pHour,
    /* [out] */ BYTE __RPC_FAR *pMinute);


void __RPC_STUB ITConference_GetStartTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITConference_SetStartTime_Proxy( 
    ITConference __RPC_FAR * This,
    /* [in] */ USHORT Year,
    /* [in] */ BYTE Month,
    /* [in] */ BYTE Day,
    /* [in] */ BYTE Hour,
    /* [in] */ BYTE Minute);


void __RPC_STUB ITConference_SetStartTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITConference_GetStopTime_Proxy( 
    ITConference __RPC_FAR * This,
    /* [out] */ USHORT __RPC_FAR *pYear,
    /* [out] */ BYTE __RPC_FAR *pMonth,
    /* [out] */ BYTE __RPC_FAR *pDay,
    /* [out] */ BYTE __RPC_FAR *pHour,
    /* [out] */ BYTE __RPC_FAR *pMinute);


void __RPC_STUB ITConference_GetStopTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITConference_SetStopTime_Proxy( 
    ITConference __RPC_FAR * This,
    /* [in] */ USHORT Year,
    /* [in] */ BYTE Month,
    /* [in] */ BYTE Day,
    /* [in] */ BYTE Hour,
    /* [in] */ BYTE Minute);


void __RPC_STUB ITConference_SetStopTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITConference_INTERFACE_DEFINED__ */


#ifndef __ITConferenceDirectory_INTERFACE_DEFINED__
#define __ITConferenceDirectory_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITConferenceDirectory
 * at Wed Sep 03 19:09:28 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [dual][helpstring][dual][uuid][public][object] */ 



EXTERN_C const IID IID_ITConferenceDirectory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F1029E5A-CB5B-11D0-8D59-00C04FD91AC0")
    ITConferenceDirectory : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DirectoryPath( 
            /* [retval][out] */ BSTR __RPC_FAR *ppDirectoryPath) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ServerName( 
            /* [retval][out] */ BSTR __RPC_FAR *ppServerName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ BSTR pServerName,
            /* [in] */ BSTR pDirectoryPath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateConference( 
            /* [in] */ BSTR pConferenceName,
            /* [retval][out] */ ITConference __RPC_FAR *__RPC_FAR *ppConference) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteConference( 
            /* [in] */ BSTR pConferenceName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetConference( 
            /* [in] */ BSTR pConferenceName,
            /* [retval][out] */ ITConference __RPC_FAR *__RPC_FAR *ppConference) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Filter( 
            /* [retval][out] */ BSTR __RPC_FAR *ppFilter) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Filter( 
            /* [in] */ BSTR pFilter) = 0;
        
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITConferenceDirectoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITConferenceDirectory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITConferenceDirectory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITConferenceDirectory __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITConferenceDirectory __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITConferenceDirectory __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITConferenceDirectory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITConferenceDirectory __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DirectoryPath )( 
            ITConferenceDirectory __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppDirectoryPath);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ServerName )( 
            ITConferenceDirectory __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppServerName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            ITConferenceDirectory __RPC_FAR * This,
            /* [in] */ BSTR pServerName,
            /* [in] */ BSTR pDirectoryPath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateConference )( 
            ITConferenceDirectory __RPC_FAR * This,
            /* [in] */ BSTR pConferenceName,
            /* [retval][out] */ ITConference __RPC_FAR *__RPC_FAR *ppConference);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteConference )( 
            ITConferenceDirectory __RPC_FAR * This,
            /* [in] */ BSTR pConferenceName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConference )( 
            ITConferenceDirectory __RPC_FAR * This,
            /* [in] */ BSTR pConferenceName,
            /* [retval][out] */ ITConference __RPC_FAR *__RPC_FAR *ppConference);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Filter )( 
            ITConferenceDirectory __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppFilter);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Filter )( 
            ITConferenceDirectory __RPC_FAR * This,
            /* [in] */ BSTR pFilter);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ITConferenceDirectory __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } ITConferenceDirectoryVtbl;

    interface ITConferenceDirectory
    {
        CONST_VTBL struct ITConferenceDirectoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITConferenceDirectory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITConferenceDirectory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITConferenceDirectory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITConferenceDirectory_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITConferenceDirectory_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITConferenceDirectory_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITConferenceDirectory_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITConferenceDirectory_get_DirectoryPath(This,ppDirectoryPath)	\
    (This)->lpVtbl -> get_DirectoryPath(This,ppDirectoryPath)

#define ITConferenceDirectory_get_ServerName(This,ppServerName)	\
    (This)->lpVtbl -> get_ServerName(This,ppServerName)

#define ITConferenceDirectory_Init(This,pServerName,pDirectoryPath)	\
    (This)->lpVtbl -> Init(This,pServerName,pDirectoryPath)

#define ITConferenceDirectory_CreateConference(This,pConferenceName,ppConference)	\
    (This)->lpVtbl -> CreateConference(This,pConferenceName,ppConference)

#define ITConferenceDirectory_DeleteConference(This,pConferenceName)	\
    (This)->lpVtbl -> DeleteConference(This,pConferenceName)

#define ITConferenceDirectory_GetConference(This,pConferenceName,ppConference)	\
    (This)->lpVtbl -> GetConference(This,pConferenceName,ppConference)

#define ITConferenceDirectory_get_Filter(This,ppFilter)	\
    (This)->lpVtbl -> get_Filter(This,ppFilter)

#define ITConferenceDirectory_put_Filter(This,pFilter)	\
    (This)->lpVtbl -> put_Filter(This,pFilter)

#define ITConferenceDirectory_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConferenceDirectory_get_DirectoryPath_Proxy( 
    ITConferenceDirectory __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppDirectoryPath);


void __RPC_STUB ITConferenceDirectory_get_DirectoryPath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConferenceDirectory_get_ServerName_Proxy( 
    ITConferenceDirectory __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppServerName);


void __RPC_STUB ITConferenceDirectory_get_ServerName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITConferenceDirectory_Init_Proxy( 
    ITConferenceDirectory __RPC_FAR * This,
    /* [in] */ BSTR pServerName,
    /* [in] */ BSTR pDirectoryPath);


void __RPC_STUB ITConferenceDirectory_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITConferenceDirectory_CreateConference_Proxy( 
    ITConferenceDirectory __RPC_FAR * This,
    /* [in] */ BSTR pConferenceName,
    /* [retval][out] */ ITConference __RPC_FAR *__RPC_FAR *ppConference);


void __RPC_STUB ITConferenceDirectory_CreateConference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITConferenceDirectory_DeleteConference_Proxy( 
    ITConferenceDirectory __RPC_FAR * This,
    /* [in] */ BSTR pConferenceName);


void __RPC_STUB ITConferenceDirectory_DeleteConference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITConferenceDirectory_GetConference_Proxy( 
    ITConferenceDirectory __RPC_FAR * This,
    /* [in] */ BSTR pConferenceName,
    /* [retval][out] */ ITConference __RPC_FAR *__RPC_FAR *ppConference);


void __RPC_STUB ITConferenceDirectory_GetConference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConferenceDirectory_get_Filter_Proxy( 
    ITConferenceDirectory __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppFilter);


void __RPC_STUB ITConferenceDirectory_get_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITConferenceDirectory_put_Filter_Proxy( 
    ITConferenceDirectory __RPC_FAR * This,
    /* [in] */ BSTR pFilter);


void __RPC_STUB ITConferenceDirectory_put_Filter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE ITConferenceDirectory_get__NewEnum_Proxy( 
    ITConferenceDirectory __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ITConferenceDirectory_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITConferenceDirectory_INTERFACE_DEFINED__ */



#ifndef __RENDLib_LIBRARY_DEFINED__
#define __RENDLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: RENDLib
 * at Wed Sep 03 19:09:28 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_RENDLib;

EXTERN_C const CLSID CLSID_ConferenceDirectory;

#ifdef __cplusplus

class DECLSPEC_UUID("F1029E5B-CB5B-11D0-8D59-00C04FD91AC0")
ConferenceDirectory;
#endif

EXTERN_C const CLSID CLSID_Conference;

#ifdef __cplusplus

class DECLSPEC_UUID("F1029E5E-CB5B-11D0-8D59-00C04FD91AC0")
Conference;
#endif
#endif /* __RENDLib_LIBRARY_DEFINED__ */

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
