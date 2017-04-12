/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Wed Sep 03 19:09:25 1997
 */
/* Compiler settings for sdpblb.idl:
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

#ifndef __sdpblb_h__
#define __sdpblb_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ITConferenceBlob_FWD_DEFINED__
#define __ITConferenceBlob_FWD_DEFINED__
typedef interface ITConferenceBlob ITConferenceBlob;
#endif 	/* __ITConferenceBlob_FWD_DEFINED__ */


#ifndef __ITMedia_FWD_DEFINED__
#define __ITMedia_FWD_DEFINED__
typedef interface ITMedia ITMedia;
#endif 	/* __ITMedia_FWD_DEFINED__ */


#ifndef __ITMediaCollection_FWD_DEFINED__
#define __ITMediaCollection_FWD_DEFINED__
typedef interface ITMediaCollection ITMediaCollection;
#endif 	/* __ITMediaCollection_FWD_DEFINED__ */


#ifndef __ITTime_FWD_DEFINED__
#define __ITTime_FWD_DEFINED__
typedef interface ITTime ITTime;
#endif 	/* __ITTime_FWD_DEFINED__ */


#ifndef __ITTimeCollection_FWD_DEFINED__
#define __ITTimeCollection_FWD_DEFINED__
typedef interface ITTimeCollection ITTimeCollection;
#endif 	/* __ITTimeCollection_FWD_DEFINED__ */


#ifndef __ITSdp_FWD_DEFINED__
#define __ITSdp_FWD_DEFINED__
typedef interface ITSdp ITSdp;
#endif 	/* __ITSdp_FWD_DEFINED__ */


#ifndef __ITConnection_FWD_DEFINED__
#define __ITConnection_FWD_DEFINED__
typedef interface ITConnection ITConnection;
#endif 	/* __ITConnection_FWD_DEFINED__ */


#ifndef __ITAttributeList_FWD_DEFINED__
#define __ITAttributeList_FWD_DEFINED__
typedef interface ITAttributeList ITAttributeList;
#endif 	/* __ITAttributeList_FWD_DEFINED__ */


#ifndef __SdpConferenceBlob_FWD_DEFINED__
#define __SdpConferenceBlob_FWD_DEFINED__

#ifdef __cplusplus
typedef class SdpConferenceBlob SdpConferenceBlob;
#else
typedef struct SdpConferenceBlob SdpConferenceBlob;
#endif /* __cplusplus */

#endif 	/* __SdpConferenceBlob_FWD_DEFINED__ */


#ifndef __MediaCollection_FWD_DEFINED__
#define __MediaCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class MediaCollection MediaCollection;
#else
typedef struct MediaCollection MediaCollection;
#endif /* __cplusplus */

#endif 	/* __MediaCollection_FWD_DEFINED__ */


#ifndef __TimeCollection_FWD_DEFINED__
#define __TimeCollection_FWD_DEFINED__

#ifdef __cplusplus
typedef class TimeCollection TimeCollection;
#else
typedef struct TimeCollection TimeCollection;
#endif /* __cplusplus */

#endif 	/* __TimeCollection_FWD_DEFINED__ */


#ifndef __Media_FWD_DEFINED__
#define __Media_FWD_DEFINED__

#ifdef __cplusplus
typedef class Media Media;
#else
typedef struct Media Media;
#endif /* __cplusplus */

#endif 	/* __Media_FWD_DEFINED__ */


#ifndef __Time_FWD_DEFINED__
#define __Time_FWD_DEFINED__

#ifdef __cplusplus
typedef class Time Time;
#else
typedef struct Time Time;
#endif /* __cplusplus */

#endif 	/* __Time_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "rndnot.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ITConferenceBlob_INTERFACE_DEFINED__
#define __ITConferenceBlob_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITConferenceBlob
 * at Wed Sep 03 19:09:25 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ITConferenceBlob;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C259D7AA-C8AB-11D0-8D58-00C04FD91AC0")
    ITConferenceBlob : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Init( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateDefault( 
            /* [in] */ BSTR pName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CommitBlob( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsModified( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfIsModified) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConferenceBlob( 
            /* [retval][out] */ BSTR __RPC_FAR *ppBlob) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ConferenceBlob( 
            /* [in] */ BSTR pBlob) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NotificationOwner( 
            /* [retval][out] */ ITNotification __RPC_FAR *__RPC_FAR *ppOwner) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NotificationOwner( 
            /* [in] */ ITNotification __RPC_FAR *pOwner) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITConferenceBlobVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITConferenceBlob __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITConferenceBlob __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITConferenceBlob __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITConferenceBlob __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITConferenceBlob __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITConferenceBlob __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITConferenceBlob __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            ITConferenceBlob __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateDefault )( 
            ITConferenceBlob __RPC_FAR * This,
            /* [in] */ BSTR pName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CommitBlob )( 
            ITConferenceBlob __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsModified )( 
            ITConferenceBlob __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfIsModified);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConferenceBlob )( 
            ITConferenceBlob __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppBlob);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConferenceBlob )( 
            ITConferenceBlob __RPC_FAR * This,
            /* [in] */ BSTR pBlob);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NotificationOwner )( 
            ITConferenceBlob __RPC_FAR * This,
            /* [retval][out] */ ITNotification __RPC_FAR *__RPC_FAR *ppOwner);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NotificationOwner )( 
            ITConferenceBlob __RPC_FAR * This,
            /* [in] */ ITNotification __RPC_FAR *pOwner);
        
        END_INTERFACE
    } ITConferenceBlobVtbl;

    interface ITConferenceBlob
    {
        CONST_VTBL struct ITConferenceBlobVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITConferenceBlob_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITConferenceBlob_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITConferenceBlob_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITConferenceBlob_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITConferenceBlob_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITConferenceBlob_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITConferenceBlob_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITConferenceBlob_Init(This)	\
    (This)->lpVtbl -> Init(This)

#define ITConferenceBlob_CreateDefault(This,pName)	\
    (This)->lpVtbl -> CreateDefault(This,pName)

#define ITConferenceBlob_CommitBlob(This)	\
    (This)->lpVtbl -> CommitBlob(This)

#define ITConferenceBlob_get_IsModified(This,pfIsModified)	\
    (This)->lpVtbl -> get_IsModified(This,pfIsModified)

#define ITConferenceBlob_get_ConferenceBlob(This,ppBlob)	\
    (This)->lpVtbl -> get_ConferenceBlob(This,ppBlob)

#define ITConferenceBlob_put_ConferenceBlob(This,pBlob)	\
    (This)->lpVtbl -> put_ConferenceBlob(This,pBlob)

#define ITConferenceBlob_get_NotificationOwner(This,ppOwner)	\
    (This)->lpVtbl -> get_NotificationOwner(This,ppOwner)

#define ITConferenceBlob_put_NotificationOwner(This,pOwner)	\
    (This)->lpVtbl -> put_NotificationOwner(This,pOwner)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITConferenceBlob_Init_Proxy( 
    ITConferenceBlob __RPC_FAR * This);


void __RPC_STUB ITConferenceBlob_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITConferenceBlob_CreateDefault_Proxy( 
    ITConferenceBlob __RPC_FAR * This,
    /* [in] */ BSTR pName);


void __RPC_STUB ITConferenceBlob_CreateDefault_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITConferenceBlob_CommitBlob_Proxy( 
    ITConferenceBlob __RPC_FAR * This);


void __RPC_STUB ITConferenceBlob_CommitBlob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConferenceBlob_get_IsModified_Proxy( 
    ITConferenceBlob __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfIsModified);


void __RPC_STUB ITConferenceBlob_get_IsModified_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConferenceBlob_get_ConferenceBlob_Proxy( 
    ITConferenceBlob __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppBlob);


void __RPC_STUB ITConferenceBlob_get_ConferenceBlob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITConferenceBlob_put_ConferenceBlob_Proxy( 
    ITConferenceBlob __RPC_FAR * This,
    /* [in] */ BSTR pBlob);


void __RPC_STUB ITConferenceBlob_put_ConferenceBlob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConferenceBlob_get_NotificationOwner_Proxy( 
    ITConferenceBlob __RPC_FAR * This,
    /* [retval][out] */ ITNotification __RPC_FAR *__RPC_FAR *ppOwner);


void __RPC_STUB ITConferenceBlob_get_NotificationOwner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITConferenceBlob_put_NotificationOwner_Proxy( 
    ITConferenceBlob __RPC_FAR * This,
    /* [in] */ ITNotification __RPC_FAR *pOwner);


void __RPC_STUB ITConferenceBlob_put_NotificationOwner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITConferenceBlob_INTERFACE_DEFINED__ */


#ifndef __ITMedia_INTERFACE_DEFINED__
#define __ITMedia_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITMedia
 * at Wed Sep 03 19:09:25 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ITMedia;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0CC1F053-CAEB-11D0-8D58-00C04FD91AC0")
    ITMedia : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaName( 
            /* [retval][out] */ BSTR __RPC_FAR *ppMediaName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MediaName( 
            /* [in] */ BSTR pMediaName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StartPort( 
            /* [retval][out] */ USHORT __RPC_FAR *pStartPort) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NumPorts( 
            /* [retval][out] */ USHORT __RPC_FAR *pNumPorts) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TransportProtocol( 
            /* [retval][out] */ BSTR __RPC_FAR *ppProtocol) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TransportProtocol( 
            /* [in] */ BSTR pProtocol) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FormatCodeList( 
            /* [retval][out] */ VARIANT __RPC_FAR *pList) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FormatCodeList( 
            /* [in] */ VARIANT List) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaTitle( 
            /* [retval][out] */ BSTR __RPC_FAR *ppMediaTitle) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MediaTitle( 
            /* [in] */ BSTR pMediaTitle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPortInfo( 
            /* [in] */ USHORT StartPort,
            /* [in] */ USHORT NumPorts) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITMediaVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITMedia __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITMedia __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITMedia __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITMedia __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITMedia __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITMedia __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITMedia __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MediaName )( 
            ITMedia __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppMediaName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MediaName )( 
            ITMedia __RPC_FAR * This,
            /* [in] */ BSTR pMediaName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartPort )( 
            ITMedia __RPC_FAR * This,
            /* [retval][out] */ USHORT __RPC_FAR *pStartPort);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumPorts )( 
            ITMedia __RPC_FAR * This,
            /* [retval][out] */ USHORT __RPC_FAR *pNumPorts);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TransportProtocol )( 
            ITMedia __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppProtocol);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TransportProtocol )( 
            ITMedia __RPC_FAR * This,
            /* [in] */ BSTR pProtocol);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FormatCodeList )( 
            ITMedia __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pList);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FormatCodeList )( 
            ITMedia __RPC_FAR * This,
            /* [in] */ VARIANT List);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MediaTitle )( 
            ITMedia __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppMediaTitle);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MediaTitle )( 
            ITMedia __RPC_FAR * This,
            /* [in] */ BSTR pMediaTitle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPortInfo )( 
            ITMedia __RPC_FAR * This,
            /* [in] */ USHORT StartPort,
            /* [in] */ USHORT NumPorts);
        
        END_INTERFACE
    } ITMediaVtbl;

    interface ITMedia
    {
        CONST_VTBL struct ITMediaVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITMedia_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITMedia_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITMedia_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITMedia_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITMedia_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITMedia_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITMedia_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITMedia_get_MediaName(This,ppMediaName)	\
    (This)->lpVtbl -> get_MediaName(This,ppMediaName)

#define ITMedia_put_MediaName(This,pMediaName)	\
    (This)->lpVtbl -> put_MediaName(This,pMediaName)

#define ITMedia_get_StartPort(This,pStartPort)	\
    (This)->lpVtbl -> get_StartPort(This,pStartPort)

#define ITMedia_get_NumPorts(This,pNumPorts)	\
    (This)->lpVtbl -> get_NumPorts(This,pNumPorts)

#define ITMedia_get_TransportProtocol(This,ppProtocol)	\
    (This)->lpVtbl -> get_TransportProtocol(This,ppProtocol)

#define ITMedia_put_TransportProtocol(This,pProtocol)	\
    (This)->lpVtbl -> put_TransportProtocol(This,pProtocol)

#define ITMedia_get_FormatCodeList(This,pList)	\
    (This)->lpVtbl -> get_FormatCodeList(This,pList)

#define ITMedia_put_FormatCodeList(This,List)	\
    (This)->lpVtbl -> put_FormatCodeList(This,List)

#define ITMedia_get_MediaTitle(This,ppMediaTitle)	\
    (This)->lpVtbl -> get_MediaTitle(This,ppMediaTitle)

#define ITMedia_put_MediaTitle(This,pMediaTitle)	\
    (This)->lpVtbl -> put_MediaTitle(This,pMediaTitle)

#define ITMedia_SetPortInfo(This,StartPort,NumPorts)	\
    (This)->lpVtbl -> SetPortInfo(This,StartPort,NumPorts)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITMedia_get_MediaName_Proxy( 
    ITMedia __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppMediaName);


void __RPC_STUB ITMedia_get_MediaName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITMedia_put_MediaName_Proxy( 
    ITMedia __RPC_FAR * This,
    /* [in] */ BSTR pMediaName);


void __RPC_STUB ITMedia_put_MediaName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITMedia_get_StartPort_Proxy( 
    ITMedia __RPC_FAR * This,
    /* [retval][out] */ USHORT __RPC_FAR *pStartPort);


void __RPC_STUB ITMedia_get_StartPort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITMedia_get_NumPorts_Proxy( 
    ITMedia __RPC_FAR * This,
    /* [retval][out] */ USHORT __RPC_FAR *pNumPorts);


void __RPC_STUB ITMedia_get_NumPorts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITMedia_get_TransportProtocol_Proxy( 
    ITMedia __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppProtocol);


void __RPC_STUB ITMedia_get_TransportProtocol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITMedia_put_TransportProtocol_Proxy( 
    ITMedia __RPC_FAR * This,
    /* [in] */ BSTR pProtocol);


void __RPC_STUB ITMedia_put_TransportProtocol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITMedia_get_FormatCodeList_Proxy( 
    ITMedia __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pList);


void __RPC_STUB ITMedia_get_FormatCodeList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITMedia_put_FormatCodeList_Proxy( 
    ITMedia __RPC_FAR * This,
    /* [in] */ VARIANT List);


void __RPC_STUB ITMedia_put_FormatCodeList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITMedia_get_MediaTitle_Proxy( 
    ITMedia __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppMediaTitle);


void __RPC_STUB ITMedia_get_MediaTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITMedia_put_MediaTitle_Proxy( 
    ITMedia __RPC_FAR * This,
    /* [in] */ BSTR pMediaTitle);


void __RPC_STUB ITMedia_put_MediaTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITMedia_SetPortInfo_Proxy( 
    ITMedia __RPC_FAR * This,
    /* [in] */ USHORT StartPort,
    /* [in] */ USHORT NumPorts);


void __RPC_STUB ITMedia_SetPortInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITMedia_INTERFACE_DEFINED__ */


#ifndef __ITMediaCollection_INTERFACE_DEFINED__
#define __ITMediaCollection_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITMediaCollection
 * at Wed Sep 03 19:09:25 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ITMediaCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6A8E16A2-0ABC-11D1-976D-00c04FD91AC0")
    ITMediaCollection : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ ULONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ ULONG Index,
            /* [retval][out] */ ITMedia __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ ULONG Index,
            /* [retval][out] */ ITMedia __RPC_FAR *__RPC_FAR *ppMedia) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Delete( 
            /* [in] */ ULONG Index) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITMediaCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITMediaCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITMediaCollection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITMediaCollection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITMediaCollection __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITMediaCollection __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITMediaCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITMediaCollection __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ITMediaCollection __RPC_FAR * This,
            /* [retval][out] */ ULONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ITMediaCollection __RPC_FAR * This,
            /* [in] */ ULONG Index,
            /* [retval][out] */ ITMedia __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ITMediaCollection __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Create )( 
            ITMediaCollection __RPC_FAR * This,
            /* [in] */ ULONG Index,
            /* [retval][out] */ ITMedia __RPC_FAR *__RPC_FAR *ppMedia);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            ITMediaCollection __RPC_FAR * This,
            /* [in] */ ULONG Index);
        
        END_INTERFACE
    } ITMediaCollectionVtbl;

    interface ITMediaCollection
    {
        CONST_VTBL struct ITMediaCollectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITMediaCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITMediaCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITMediaCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITMediaCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITMediaCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITMediaCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITMediaCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITMediaCollection_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITMediaCollection_get_Item(This,Index,pVal)	\
    (This)->lpVtbl -> get_Item(This,Index,pVal)

#define ITMediaCollection_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define ITMediaCollection_Create(This,Index,ppMedia)	\
    (This)->lpVtbl -> Create(This,Index,ppMedia)

#define ITMediaCollection_Delete(This,Index)	\
    (This)->lpVtbl -> Delete(This,Index)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITMediaCollection_get_Count_Proxy( 
    ITMediaCollection __RPC_FAR * This,
    /* [retval][out] */ ULONG __RPC_FAR *pVal);


void __RPC_STUB ITMediaCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITMediaCollection_get_Item_Proxy( 
    ITMediaCollection __RPC_FAR * This,
    /* [in] */ ULONG Index,
    /* [retval][out] */ ITMedia __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ITMediaCollection_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE ITMediaCollection_get__NewEnum_Proxy( 
    ITMediaCollection __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ITMediaCollection_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITMediaCollection_Create_Proxy( 
    ITMediaCollection __RPC_FAR * This,
    /* [in] */ ULONG Index,
    /* [retval][out] */ ITMedia __RPC_FAR *__RPC_FAR *ppMedia);


void __RPC_STUB ITMediaCollection_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITMediaCollection_Delete_Proxy( 
    ITMediaCollection __RPC_FAR * This,
    /* [in] */ ULONG Index);


void __RPC_STUB ITMediaCollection_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITMediaCollection_INTERFACE_DEFINED__ */


#ifndef __ITTime_INTERFACE_DEFINED__
#define __ITTime_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITTime
 * at Wed Sep 03 19:09:25 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ITTime;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2652BB78-1516-11D1-9771-00C04FD91AC0")
    ITTime : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StartTime( 
            /* [retval][out] */ ULONG __RPC_FAR *pTime) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StartTime( 
            /* [in] */ ULONG Time) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StopTime( 
            /* [retval][out] */ ULONG __RPC_FAR *pTime) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StopTime( 
            /* [in] */ ULONG Time) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITTimeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITTime __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITTime __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITTime __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITTime __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITTime __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITTime __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITTime __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartTime )( 
            ITTime __RPC_FAR * This,
            /* [retval][out] */ ULONG __RPC_FAR *pTime);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StartTime )( 
            ITTime __RPC_FAR * This,
            /* [in] */ ULONG Time);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StopTime )( 
            ITTime __RPC_FAR * This,
            /* [retval][out] */ ULONG __RPC_FAR *pTime);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StopTime )( 
            ITTime __RPC_FAR * This,
            /* [in] */ ULONG Time);
        
        END_INTERFACE
    } ITTimeVtbl;

    interface ITTime
    {
        CONST_VTBL struct ITTimeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITTime_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITTime_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITTime_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITTime_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITTime_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITTime_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITTime_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITTime_get_StartTime(This,pTime)	\
    (This)->lpVtbl -> get_StartTime(This,pTime)

#define ITTime_put_StartTime(This,Time)	\
    (This)->lpVtbl -> put_StartTime(This,Time)

#define ITTime_get_StopTime(This,pTime)	\
    (This)->lpVtbl -> get_StopTime(This,pTime)

#define ITTime_put_StopTime(This,Time)	\
    (This)->lpVtbl -> put_StopTime(This,Time)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTime_get_StartTime_Proxy( 
    ITTime __RPC_FAR * This,
    /* [retval][out] */ ULONG __RPC_FAR *pTime);


void __RPC_STUB ITTime_get_StartTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITTime_put_StartTime_Proxy( 
    ITTime __RPC_FAR * This,
    /* [in] */ ULONG Time);


void __RPC_STUB ITTime_put_StartTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTime_get_StopTime_Proxy( 
    ITTime __RPC_FAR * This,
    /* [retval][out] */ ULONG __RPC_FAR *pTime);


void __RPC_STUB ITTime_get_StopTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITTime_put_StopTime_Proxy( 
    ITTime __RPC_FAR * This,
    /* [in] */ ULONG Time);


void __RPC_STUB ITTime_put_StopTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITTime_INTERFACE_DEFINED__ */


#ifndef __ITTimeCollection_INTERFACE_DEFINED__
#define __ITTimeCollection_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITTimeCollection
 * at Wed Sep 03 19:09:25 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ITTimeCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0CC1F04F-CAEB-11D0-8D58-00C04FD91AC0")
    ITTimeCollection : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ ULONG __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ ULONG Index,
            /* [retval][out] */ ITTime __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ ULONG Index,
            /* [retval][out] */ ITTime __RPC_FAR *__RPC_FAR *ppTime) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Delete( 
            /* [in] */ ULONG Index) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITTimeCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITTimeCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITTimeCollection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITTimeCollection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITTimeCollection __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITTimeCollection __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITTimeCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITTimeCollection __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ITTimeCollection __RPC_FAR * This,
            /* [retval][out] */ ULONG __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ITTimeCollection __RPC_FAR * This,
            /* [in] */ ULONG Index,
            /* [retval][out] */ ITTime __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ITTimeCollection __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Create )( 
            ITTimeCollection __RPC_FAR * This,
            /* [in] */ ULONG Index,
            /* [retval][out] */ ITTime __RPC_FAR *__RPC_FAR *ppTime);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            ITTimeCollection __RPC_FAR * This,
            /* [in] */ ULONG Index);
        
        END_INTERFACE
    } ITTimeCollectionVtbl;

    interface ITTimeCollection
    {
        CONST_VTBL struct ITTimeCollectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITTimeCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITTimeCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITTimeCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITTimeCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITTimeCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITTimeCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITTimeCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITTimeCollection_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITTimeCollection_get_Item(This,Index,pVal)	\
    (This)->lpVtbl -> get_Item(This,Index,pVal)

#define ITTimeCollection_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define ITTimeCollection_Create(This,Index,ppTime)	\
    (This)->lpVtbl -> Create(This,Index,ppTime)

#define ITTimeCollection_Delete(This,Index)	\
    (This)->lpVtbl -> Delete(This,Index)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITTimeCollection_get_Count_Proxy( 
    ITTimeCollection __RPC_FAR * This,
    /* [retval][out] */ ULONG __RPC_FAR *pVal);


void __RPC_STUB ITTimeCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTimeCollection_get_Item_Proxy( 
    ITTimeCollection __RPC_FAR * This,
    /* [in] */ ULONG Index,
    /* [retval][out] */ ITTime __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ITTimeCollection_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE ITTimeCollection_get__NewEnum_Proxy( 
    ITTimeCollection __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ITTimeCollection_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITTimeCollection_Create_Proxy( 
    ITTimeCollection __RPC_FAR * This,
    /* [in] */ ULONG Index,
    /* [retval][out] */ ITTime __RPC_FAR *__RPC_FAR *ppTime);


void __RPC_STUB ITTimeCollection_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITTimeCollection_Delete_Proxy( 
    ITTimeCollection __RPC_FAR * This,
    /* [in] */ ULONG Index);


void __RPC_STUB ITTimeCollection_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITTimeCollection_INTERFACE_DEFINED__ */


#ifndef __ITSdp_INTERFACE_DEFINED__
#define __ITSdp_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITSdp
 * at Wed Sep 03 19:09:25 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ITSdp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9B2719D8-B696-11D0-A489-00C04FD91AC0")
    ITSdp : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsValid( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfIsValid) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProtocolVersion( 
            /* [retval][out] */ USHORT __RPC_FAR *pProtocolVersion) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SessionId( 
            /* [retval][out] */ ULONG __RPC_FAR *pSessionId) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SessionVersion( 
            /* [retval][out] */ ULONG __RPC_FAR *pSessionVersion) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SessionVersion( 
            /* [in] */ ULONG SessionVersion) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MachineAddress( 
            /* [retval][out] */ BSTR __RPC_FAR *ppMachineAddress) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MachineAddress( 
            /* [in] */ BSTR pMachineAddress) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SessionName( 
            /* [retval][out] */ BSTR __RPC_FAR *ppSessionName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SessionName( 
            /* [in] */ BSTR pSessionName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SessionInfo( 
            /* [retval][out] */ BSTR __RPC_FAR *ppSessionInfo) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SessionInfo( 
            /* [in] */ BSTR pSessionInfo) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Uri( 
            /* [retval][out] */ BSTR __RPC_FAR *ppUri) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Uri( 
            /* [in] */ BSTR pUri) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEmailNames( 
            /* [out] */ VARIANT __RPC_FAR *pAddresses,
            /* [out] */ VARIANT __RPC_FAR *pNames) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEmailNames( 
            /* [in] */ VARIANT Addresseses,
            /* [in] */ VARIANT Names) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPhoneNumbers( 
            /* [out] */ VARIANT __RPC_FAR *pNumbers,
            /* [out] */ VARIANT __RPC_FAR *pNames) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPhoneNumbers( 
            /* [in] */ VARIANT Numbers,
            /* [in] */ VARIANT Names) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CharacterSet( 
            /* [retval][out] */ BSTR __RPC_FAR *ppCharacterSet) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CharacterSet( 
            /* [in] */ BSTR pCharacterSet) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UserName( 
            /* [retval][out] */ BSTR __RPC_FAR *ppUserName) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UserName( 
            /* [in] */ BSTR pUserName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaCollection( 
            /* [retval][out] */ ITMediaCollection __RPC_FAR *__RPC_FAR *ppMediaCollection) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TimeCollection( 
            /* [retval][out] */ ITTimeCollection __RPC_FAR *__RPC_FAR *ppTimeCollection) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITSdpVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITSdp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITSdp __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITSdp __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITSdp __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITSdp __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITSdp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITSdp __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsValid )( 
            ITSdp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfIsValid);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProtocolVersion )( 
            ITSdp __RPC_FAR * This,
            /* [retval][out] */ USHORT __RPC_FAR *pProtocolVersion);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SessionId )( 
            ITSdp __RPC_FAR * This,
            /* [retval][out] */ ULONG __RPC_FAR *pSessionId);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SessionVersion )( 
            ITSdp __RPC_FAR * This,
            /* [retval][out] */ ULONG __RPC_FAR *pSessionVersion);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SessionVersion )( 
            ITSdp __RPC_FAR * This,
            /* [in] */ ULONG SessionVersion);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MachineAddress )( 
            ITSdp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppMachineAddress);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MachineAddress )( 
            ITSdp __RPC_FAR * This,
            /* [in] */ BSTR pMachineAddress);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SessionName )( 
            ITSdp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppSessionName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SessionName )( 
            ITSdp __RPC_FAR * This,
            /* [in] */ BSTR pSessionName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SessionInfo )( 
            ITSdp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppSessionInfo);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SessionInfo )( 
            ITSdp __RPC_FAR * This,
            /* [in] */ BSTR pSessionInfo);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Uri )( 
            ITSdp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppUri);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Uri )( 
            ITSdp __RPC_FAR * This,
            /* [in] */ BSTR pUri);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEmailNames )( 
            ITSdp __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pAddresses,
            /* [out] */ VARIANT __RPC_FAR *pNames);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEmailNames )( 
            ITSdp __RPC_FAR * This,
            /* [in] */ VARIANT Addresseses,
            /* [in] */ VARIANT Names);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPhoneNumbers )( 
            ITSdp __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pNumbers,
            /* [out] */ VARIANT __RPC_FAR *pNames);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPhoneNumbers )( 
            ITSdp __RPC_FAR * This,
            /* [in] */ VARIANT Numbers,
            /* [in] */ VARIANT Names);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CharacterSet )( 
            ITSdp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppCharacterSet);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CharacterSet )( 
            ITSdp __RPC_FAR * This,
            /* [in] */ BSTR pCharacterSet);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserName )( 
            ITSdp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppUserName);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UserName )( 
            ITSdp __RPC_FAR * This,
            /* [in] */ BSTR pUserName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MediaCollection )( 
            ITSdp __RPC_FAR * This,
            /* [retval][out] */ ITMediaCollection __RPC_FAR *__RPC_FAR *ppMediaCollection);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TimeCollection )( 
            ITSdp __RPC_FAR * This,
            /* [retval][out] */ ITTimeCollection __RPC_FAR *__RPC_FAR *ppTimeCollection);
        
        END_INTERFACE
    } ITSdpVtbl;

    interface ITSdp
    {
        CONST_VTBL struct ITSdpVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITSdp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITSdp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITSdp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITSdp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITSdp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITSdp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITSdp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITSdp_get_IsValid(This,pfIsValid)	\
    (This)->lpVtbl -> get_IsValid(This,pfIsValid)

#define ITSdp_get_ProtocolVersion(This,pProtocolVersion)	\
    (This)->lpVtbl -> get_ProtocolVersion(This,pProtocolVersion)

#define ITSdp_get_SessionId(This,pSessionId)	\
    (This)->lpVtbl -> get_SessionId(This,pSessionId)

#define ITSdp_get_SessionVersion(This,pSessionVersion)	\
    (This)->lpVtbl -> get_SessionVersion(This,pSessionVersion)

#define ITSdp_put_SessionVersion(This,SessionVersion)	\
    (This)->lpVtbl -> put_SessionVersion(This,SessionVersion)

#define ITSdp_get_MachineAddress(This,ppMachineAddress)	\
    (This)->lpVtbl -> get_MachineAddress(This,ppMachineAddress)

#define ITSdp_put_MachineAddress(This,pMachineAddress)	\
    (This)->lpVtbl -> put_MachineAddress(This,pMachineAddress)

#define ITSdp_get_SessionName(This,ppSessionName)	\
    (This)->lpVtbl -> get_SessionName(This,ppSessionName)

#define ITSdp_put_SessionName(This,pSessionName)	\
    (This)->lpVtbl -> put_SessionName(This,pSessionName)

#define ITSdp_get_SessionInfo(This,ppSessionInfo)	\
    (This)->lpVtbl -> get_SessionInfo(This,ppSessionInfo)

#define ITSdp_put_SessionInfo(This,pSessionInfo)	\
    (This)->lpVtbl -> put_SessionInfo(This,pSessionInfo)

#define ITSdp_get_Uri(This,ppUri)	\
    (This)->lpVtbl -> get_Uri(This,ppUri)

#define ITSdp_put_Uri(This,pUri)	\
    (This)->lpVtbl -> put_Uri(This,pUri)

#define ITSdp_GetEmailNames(This,pAddresses,pNames)	\
    (This)->lpVtbl -> GetEmailNames(This,pAddresses,pNames)

#define ITSdp_SetEmailNames(This,Addresseses,Names)	\
    (This)->lpVtbl -> SetEmailNames(This,Addresseses,Names)

#define ITSdp_GetPhoneNumbers(This,pNumbers,pNames)	\
    (This)->lpVtbl -> GetPhoneNumbers(This,pNumbers,pNames)

#define ITSdp_SetPhoneNumbers(This,Numbers,Names)	\
    (This)->lpVtbl -> SetPhoneNumbers(This,Numbers,Names)

#define ITSdp_get_CharacterSet(This,ppCharacterSet)	\
    (This)->lpVtbl -> get_CharacterSet(This,ppCharacterSet)

#define ITSdp_put_CharacterSet(This,pCharacterSet)	\
    (This)->lpVtbl -> put_CharacterSet(This,pCharacterSet)

#define ITSdp_get_UserName(This,ppUserName)	\
    (This)->lpVtbl -> get_UserName(This,ppUserName)

#define ITSdp_put_UserName(This,pUserName)	\
    (This)->lpVtbl -> put_UserName(This,pUserName)

#define ITSdp_get_MediaCollection(This,ppMediaCollection)	\
    (This)->lpVtbl -> get_MediaCollection(This,ppMediaCollection)

#define ITSdp_get_TimeCollection(This,ppTimeCollection)	\
    (This)->lpVtbl -> get_TimeCollection(This,ppTimeCollection)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITSdp_get_IsValid_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfIsValid);


void __RPC_STUB ITSdp_get_IsValid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITSdp_get_ProtocolVersion_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [retval][out] */ USHORT __RPC_FAR *pProtocolVersion);


void __RPC_STUB ITSdp_get_ProtocolVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITSdp_get_SessionId_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [retval][out] */ ULONG __RPC_FAR *pSessionId);


void __RPC_STUB ITSdp_get_SessionId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITSdp_get_SessionVersion_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [retval][out] */ ULONG __RPC_FAR *pSessionVersion);


void __RPC_STUB ITSdp_get_SessionVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITSdp_put_SessionVersion_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [in] */ ULONG SessionVersion);


void __RPC_STUB ITSdp_put_SessionVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITSdp_get_MachineAddress_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppMachineAddress);


void __RPC_STUB ITSdp_get_MachineAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITSdp_put_MachineAddress_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [in] */ BSTR pMachineAddress);


void __RPC_STUB ITSdp_put_MachineAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITSdp_get_SessionName_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppSessionName);


void __RPC_STUB ITSdp_get_SessionName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITSdp_put_SessionName_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [in] */ BSTR pSessionName);


void __RPC_STUB ITSdp_put_SessionName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITSdp_get_SessionInfo_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppSessionInfo);


void __RPC_STUB ITSdp_get_SessionInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITSdp_put_SessionInfo_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [in] */ BSTR pSessionInfo);


void __RPC_STUB ITSdp_put_SessionInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITSdp_get_Uri_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppUri);


void __RPC_STUB ITSdp_get_Uri_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITSdp_put_Uri_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [in] */ BSTR pUri);


void __RPC_STUB ITSdp_put_Uri_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITSdp_GetEmailNames_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pAddresses,
    /* [out] */ VARIANT __RPC_FAR *pNames);


void __RPC_STUB ITSdp_GetEmailNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITSdp_SetEmailNames_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [in] */ VARIANT Addresseses,
    /* [in] */ VARIANT Names);


void __RPC_STUB ITSdp_SetEmailNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITSdp_GetPhoneNumbers_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pNumbers,
    /* [out] */ VARIANT __RPC_FAR *pNames);


void __RPC_STUB ITSdp_GetPhoneNumbers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITSdp_SetPhoneNumbers_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [in] */ VARIANT Numbers,
    /* [in] */ VARIANT Names);


void __RPC_STUB ITSdp_SetPhoneNumbers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITSdp_get_CharacterSet_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppCharacterSet);


void __RPC_STUB ITSdp_get_CharacterSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITSdp_put_CharacterSet_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [in] */ BSTR pCharacterSet);


void __RPC_STUB ITSdp_put_CharacterSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITSdp_get_UserName_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppUserName);


void __RPC_STUB ITSdp_get_UserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITSdp_put_UserName_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [in] */ BSTR pUserName);


void __RPC_STUB ITSdp_put_UserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITSdp_get_MediaCollection_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [retval][out] */ ITMediaCollection __RPC_FAR *__RPC_FAR *ppMediaCollection);


void __RPC_STUB ITSdp_get_MediaCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITSdp_get_TimeCollection_Proxy( 
    ITSdp __RPC_FAR * This,
    /* [retval][out] */ ITTimeCollection __RPC_FAR *__RPC_FAR *ppTimeCollection);


void __RPC_STUB ITSdp_get_TimeCollection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITSdp_INTERFACE_DEFINED__ */


#ifndef __ITConnection_INTERFACE_DEFINED__
#define __ITConnection_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITConnection
 * at Wed Sep 03 19:09:25 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ITConnection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8fa381d4-c8c2-11d0-8d58-00c04fd91ac0")
    ITConnection : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NetworkType( 
            /* [retval][out] */ BSTR __RPC_FAR *ppNetworkType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NetworkType( 
            /* [in] */ BSTR pNetworkType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AddressType( 
            /* [retval][out] */ BSTR __RPC_FAR *ppAddressType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AddressType( 
            /* [in] */ BSTR pAddressType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StartAddress( 
            /* [retval][out] */ BSTR __RPC_FAR *ppStartAddress) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NumAddresses( 
            /* [retval][out] */ ULONG __RPC_FAR *pNumAddresses) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Ttl( 
            /* [retval][out] */ BYTE __RPC_FAR *pTtl) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BandwidthModifier( 
            /* [retval][out] */ BSTR __RPC_FAR *ppModifier) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Bandwidth( 
            /* [retval][out] */ ULONG __RPC_FAR *pBandwidth) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAddressInfo( 
            /* [in] */ BSTR pStartAddress,
            /* [in] */ ULONG NumAddresses,
            /* [in] */ BYTE Ttl) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetBandwidthInfo( 
            /* [in] */ BSTR pModifier,
            /* [in] */ ULONG Bandwidth) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEncryptionKey( 
            /* [in] */ BSTR pKeyType,
            /* [in] */ BSTR __RPC_FAR *ppKeyData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEncryptionKey( 
            /* [out] */ BSTR __RPC_FAR *ppKeyType,
            /* [out] */ VARIANT_BOOL __RPC_FAR *pfValidKeyData,
            /* [out] */ BSTR __RPC_FAR *ppKeyData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITConnectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITConnection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITConnection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITConnection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITConnection __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITConnection __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITConnection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITConnection __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NetworkType )( 
            ITConnection __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppNetworkType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NetworkType )( 
            ITConnection __RPC_FAR * This,
            /* [in] */ BSTR pNetworkType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AddressType )( 
            ITConnection __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppAddressType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AddressType )( 
            ITConnection __RPC_FAR * This,
            /* [in] */ BSTR pAddressType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StartAddress )( 
            ITConnection __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppStartAddress);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumAddresses )( 
            ITConnection __RPC_FAR * This,
            /* [retval][out] */ ULONG __RPC_FAR *pNumAddresses);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Ttl )( 
            ITConnection __RPC_FAR * This,
            /* [retval][out] */ BYTE __RPC_FAR *pTtl);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BandwidthModifier )( 
            ITConnection __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppModifier);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Bandwidth )( 
            ITConnection __RPC_FAR * This,
            /* [retval][out] */ ULONG __RPC_FAR *pBandwidth);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAddressInfo )( 
            ITConnection __RPC_FAR * This,
            /* [in] */ BSTR pStartAddress,
            /* [in] */ ULONG NumAddresses,
            /* [in] */ BYTE Ttl);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetBandwidthInfo )( 
            ITConnection __RPC_FAR * This,
            /* [in] */ BSTR pModifier,
            /* [in] */ ULONG Bandwidth);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEncryptionKey )( 
            ITConnection __RPC_FAR * This,
            /* [in] */ BSTR pKeyType,
            /* [in] */ BSTR __RPC_FAR *ppKeyData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEncryptionKey )( 
            ITConnection __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *ppKeyType,
            /* [out] */ VARIANT_BOOL __RPC_FAR *pfValidKeyData,
            /* [out] */ BSTR __RPC_FAR *ppKeyData);
        
        END_INTERFACE
    } ITConnectionVtbl;

    interface ITConnection
    {
        CONST_VTBL struct ITConnectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITConnection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITConnection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITConnection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITConnection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITConnection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITConnection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITConnection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITConnection_get_NetworkType(This,ppNetworkType)	\
    (This)->lpVtbl -> get_NetworkType(This,ppNetworkType)

#define ITConnection_put_NetworkType(This,pNetworkType)	\
    (This)->lpVtbl -> put_NetworkType(This,pNetworkType)

#define ITConnection_get_AddressType(This,ppAddressType)	\
    (This)->lpVtbl -> get_AddressType(This,ppAddressType)

#define ITConnection_put_AddressType(This,pAddressType)	\
    (This)->lpVtbl -> put_AddressType(This,pAddressType)

#define ITConnection_get_StartAddress(This,ppStartAddress)	\
    (This)->lpVtbl -> get_StartAddress(This,ppStartAddress)

#define ITConnection_get_NumAddresses(This,pNumAddresses)	\
    (This)->lpVtbl -> get_NumAddresses(This,pNumAddresses)

#define ITConnection_get_Ttl(This,pTtl)	\
    (This)->lpVtbl -> get_Ttl(This,pTtl)

#define ITConnection_get_BandwidthModifier(This,ppModifier)	\
    (This)->lpVtbl -> get_BandwidthModifier(This,ppModifier)

#define ITConnection_get_Bandwidth(This,pBandwidth)	\
    (This)->lpVtbl -> get_Bandwidth(This,pBandwidth)

#define ITConnection_SetAddressInfo(This,pStartAddress,NumAddresses,Ttl)	\
    (This)->lpVtbl -> SetAddressInfo(This,pStartAddress,NumAddresses,Ttl)

#define ITConnection_SetBandwidthInfo(This,pModifier,Bandwidth)	\
    (This)->lpVtbl -> SetBandwidthInfo(This,pModifier,Bandwidth)

#define ITConnection_SetEncryptionKey(This,pKeyType,ppKeyData)	\
    (This)->lpVtbl -> SetEncryptionKey(This,pKeyType,ppKeyData)

#define ITConnection_GetEncryptionKey(This,ppKeyType,pfValidKeyData,ppKeyData)	\
    (This)->lpVtbl -> GetEncryptionKey(This,ppKeyType,pfValidKeyData,ppKeyData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConnection_get_NetworkType_Proxy( 
    ITConnection __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppNetworkType);


void __RPC_STUB ITConnection_get_NetworkType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITConnection_put_NetworkType_Proxy( 
    ITConnection __RPC_FAR * This,
    /* [in] */ BSTR pNetworkType);


void __RPC_STUB ITConnection_put_NetworkType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConnection_get_AddressType_Proxy( 
    ITConnection __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppAddressType);


void __RPC_STUB ITConnection_get_AddressType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITConnection_put_AddressType_Proxy( 
    ITConnection __RPC_FAR * This,
    /* [in] */ BSTR pAddressType);


void __RPC_STUB ITConnection_put_AddressType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConnection_get_StartAddress_Proxy( 
    ITConnection __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppStartAddress);


void __RPC_STUB ITConnection_get_StartAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConnection_get_NumAddresses_Proxy( 
    ITConnection __RPC_FAR * This,
    /* [retval][out] */ ULONG __RPC_FAR *pNumAddresses);


void __RPC_STUB ITConnection_get_NumAddresses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConnection_get_Ttl_Proxy( 
    ITConnection __RPC_FAR * This,
    /* [retval][out] */ BYTE __RPC_FAR *pTtl);


void __RPC_STUB ITConnection_get_Ttl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConnection_get_BandwidthModifier_Proxy( 
    ITConnection __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppModifier);


void __RPC_STUB ITConnection_get_BandwidthModifier_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITConnection_get_Bandwidth_Proxy( 
    ITConnection __RPC_FAR * This,
    /* [retval][out] */ ULONG __RPC_FAR *pBandwidth);


void __RPC_STUB ITConnection_get_Bandwidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITConnection_SetAddressInfo_Proxy( 
    ITConnection __RPC_FAR * This,
    /* [in] */ BSTR pStartAddress,
    /* [in] */ ULONG NumAddresses,
    /* [in] */ BYTE Ttl);


void __RPC_STUB ITConnection_SetAddressInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITConnection_SetBandwidthInfo_Proxy( 
    ITConnection __RPC_FAR * This,
    /* [in] */ BSTR pModifier,
    /* [in] */ ULONG Bandwidth);


void __RPC_STUB ITConnection_SetBandwidthInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITConnection_SetEncryptionKey_Proxy( 
    ITConnection __RPC_FAR * This,
    /* [in] */ BSTR pKeyType,
    /* [in] */ BSTR __RPC_FAR *ppKeyData);


void __RPC_STUB ITConnection_SetEncryptionKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITConnection_GetEncryptionKey_Proxy( 
    ITConnection __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *ppKeyType,
    /* [out] */ VARIANT_BOOL __RPC_FAR *pfValidKeyData,
    /* [out] */ BSTR __RPC_FAR *ppKeyData);


void __RPC_STUB ITConnection_GetEncryptionKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITConnection_INTERFACE_DEFINED__ */


#ifndef __ITAttributeList_INTERFACE_DEFINED__
#define __ITAttributeList_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITAttributeList
 * at Wed Sep 03 19:09:25 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_ITAttributeList;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5037fb82-cae9-11d0-8d58-00c04fd91ac0")
    ITAttributeList : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ USHORT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ USHORT Index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ USHORT Index,
            /* [in] */ BSTR pAttribute) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Delete( 
            /* [in] */ USHORT Index) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AttributeList( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AttributeList( 
            /* [in] */ VARIANT newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITAttributeListVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITAttributeList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITAttributeList __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITAttributeList __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITAttributeList __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITAttributeList __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITAttributeList __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITAttributeList __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ITAttributeList __RPC_FAR * This,
            /* [retval][out] */ USHORT __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ITAttributeList __RPC_FAR * This,
            /* [in] */ USHORT Index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            ITAttributeList __RPC_FAR * This,
            /* [in] */ USHORT Index,
            /* [in] */ BSTR pAttribute);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            ITAttributeList __RPC_FAR * This,
            /* [in] */ USHORT Index);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttributeList )( 
            ITAttributeList __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AttributeList )( 
            ITAttributeList __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        END_INTERFACE
    } ITAttributeListVtbl;

    interface ITAttributeList
    {
        CONST_VTBL struct ITAttributeListVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITAttributeList_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITAttributeList_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITAttributeList_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITAttributeList_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITAttributeList_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITAttributeList_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITAttributeList_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITAttributeList_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define ITAttributeList_get_Item(This,Index,pVal)	\
    (This)->lpVtbl -> get_Item(This,Index,pVal)

#define ITAttributeList_Add(This,Index,pAttribute)	\
    (This)->lpVtbl -> Add(This,Index,pAttribute)

#define ITAttributeList_Delete(This,Index)	\
    (This)->lpVtbl -> Delete(This,Index)

#define ITAttributeList_get_AttributeList(This,pVal)	\
    (This)->lpVtbl -> get_AttributeList(This,pVal)

#define ITAttributeList_put_AttributeList(This,newVal)	\
    (This)->lpVtbl -> put_AttributeList(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITAttributeList_get_Count_Proxy( 
    ITAttributeList __RPC_FAR * This,
    /* [retval][out] */ USHORT __RPC_FAR *pVal);


void __RPC_STUB ITAttributeList_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITAttributeList_get_Item_Proxy( 
    ITAttributeList __RPC_FAR * This,
    /* [in] */ USHORT Index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITAttributeList_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITAttributeList_Add_Proxy( 
    ITAttributeList __RPC_FAR * This,
    /* [in] */ USHORT Index,
    /* [in] */ BSTR pAttribute);


void __RPC_STUB ITAttributeList_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITAttributeList_Delete_Proxy( 
    ITAttributeList __RPC_FAR * This,
    /* [in] */ USHORT Index);


void __RPC_STUB ITAttributeList_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITAttributeList_get_AttributeList_Proxy( 
    ITAttributeList __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB ITAttributeList_get_AttributeList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITAttributeList_put_AttributeList_Proxy( 
    ITAttributeList __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB ITAttributeList_put_AttributeList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITAttributeList_INTERFACE_DEFINED__ */



#ifndef __SDPBLBLib_LIBRARY_DEFINED__
#define __SDPBLBLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: SDPBLBLib
 * at Wed Sep 03 19:09:25 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_SDPBLBLib;

EXTERN_C const CLSID CLSID_SdpConferenceBlob;

#ifdef __cplusplus

class DECLSPEC_UUID("9B2719DD-B696-11D0-A489-00C04FD91AC0")
SdpConferenceBlob;
#endif

EXTERN_C const CLSID CLSID_MediaCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("0CC1F04D-CAEB-11D0-8D58-00C04FD91AC0")
MediaCollection;
#endif

EXTERN_C const CLSID CLSID_TimeCollection;

#ifdef __cplusplus

class DECLSPEC_UUID("2E4F4A20-0ABD-11D1-976D-00C04FD91AC0")
TimeCollection;
#endif

EXTERN_C const CLSID CLSID_Media;

#ifdef __cplusplus

class DECLSPEC_UUID("0CC1F056-CAEB-11D0-8D58-00C04FD91AC0")
Media;
#endif

EXTERN_C const CLSID CLSID_Time;

#ifdef __cplusplus

class DECLSPEC_UUID("0CC1F059-CAEB-11D0-8D58-00C04FD91AC0")
Time;
#endif
#endif /* __SDPBLBLib_LIBRARY_DEFINED__ */

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
