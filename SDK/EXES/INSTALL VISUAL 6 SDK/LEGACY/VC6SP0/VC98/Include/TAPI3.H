/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Wed Sep 03 19:02:55 1997
 */
/* Compiler settings for tapi3.idl:
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

#ifndef __tapi3_h__
#define __tapi3_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ITTAPI_FWD_DEFINED__
#define __ITTAPI_FWD_DEFINED__
typedef interface ITTAPI ITTAPI;
#endif 	/* __ITTAPI_FWD_DEFINED__ */


#ifndef __ITMediaSupport_FWD_DEFINED__
#define __ITMediaSupport_FWD_DEFINED__
typedef interface ITMediaSupport ITMediaSupport;
#endif 	/* __ITMediaSupport_FWD_DEFINED__ */


#ifndef __ITTerminalSupport_FWD_DEFINED__
#define __ITTerminalSupport_FWD_DEFINED__
typedef interface ITTerminalSupport ITTerminalSupport;
#endif 	/* __ITTerminalSupport_FWD_DEFINED__ */


#ifndef __ITAddress_FWD_DEFINED__
#define __ITAddress_FWD_DEFINED__
typedef interface ITAddress ITAddress;
#endif 	/* __ITAddress_FWD_DEFINED__ */


#ifndef __ITBasicCallControl_FWD_DEFINED__
#define __ITBasicCallControl_FWD_DEFINED__
typedef interface ITBasicCallControl ITBasicCallControl;
#endif 	/* __ITBasicCallControl_FWD_DEFINED__ */


#ifndef __ITCallInfo_FWD_DEFINED__
#define __ITCallInfo_FWD_DEFINED__
typedef interface ITCallInfo ITCallInfo;
#endif 	/* __ITCallInfo_FWD_DEFINED__ */


#ifndef __ITConsultCall_FWD_DEFINED__
#define __ITConsultCall_FWD_DEFINED__
typedef interface ITConsultCall ITConsultCall;
#endif 	/* __ITConsultCall_FWD_DEFINED__ */


#ifndef __ITTerminal_FWD_DEFINED__
#define __ITTerminal_FWD_DEFINED__
typedef interface ITTerminal ITTerminal;
#endif 	/* __ITTerminal_FWD_DEFINED__ */


#ifndef __ITAMTerminal_FWD_DEFINED__
#define __ITAMTerminal_FWD_DEFINED__
typedef interface ITAMTerminal ITAMTerminal;
#endif 	/* __ITAMTerminal_FWD_DEFINED__ */


#ifndef __ITFileTerminal_FWD_DEFINED__
#define __ITFileTerminal_FWD_DEFINED__
typedef interface ITFileTerminal ITFileTerminal;
#endif 	/* __ITFileTerminal_FWD_DEFINED__ */


#ifndef __ITBasicAudioTerminal_FWD_DEFINED__
#define __ITBasicAudioTerminal_FWD_DEFINED__
typedef interface ITBasicAudioTerminal ITBasicAudioTerminal;
#endif 	/* __ITBasicAudioTerminal_FWD_DEFINED__ */


#ifndef __ITMediaTerminal_FWD_DEFINED__
#define __ITMediaTerminal_FWD_DEFINED__
typedef interface ITMediaTerminal ITMediaTerminal;
#endif 	/* __ITMediaTerminal_FWD_DEFINED__ */


#ifndef __ITParticipantInfo_FWD_DEFINED__
#define __ITParticipantInfo_FWD_DEFINED__
typedef interface ITParticipantInfo ITParticipantInfo;
#endif 	/* __ITParticipantInfo_FWD_DEFINED__ */


#ifndef __ITCallTones_FWD_DEFINED__
#define __ITCallTones_FWD_DEFINED__
typedef interface ITCallTones ITCallTones;
#endif 	/* __ITCallTones_FWD_DEFINED__ */


#ifndef __IEnumAddressType_FWD_DEFINED__
#define __IEnumAddressType_FWD_DEFINED__
typedef interface IEnumAddressType IEnumAddressType;
#endif 	/* __IEnumAddressType_FWD_DEFINED__ */


#ifndef __IEnumMediaType_FWD_DEFINED__
#define __IEnumMediaType_FWD_DEFINED__
typedef interface IEnumMediaType IEnumMediaType;
#endif 	/* __IEnumMediaType_FWD_DEFINED__ */


#ifndef __IEnumTerminal_FWD_DEFINED__
#define __IEnumTerminal_FWD_DEFINED__
typedef interface IEnumTerminal IEnumTerminal;
#endif 	/* __IEnumTerminal_FWD_DEFINED__ */


#ifndef __IEnumTerminalClasses_FWD_DEFINED__
#define __IEnumTerminalClasses_FWD_DEFINED__
typedef interface IEnumTerminalClasses IEnumTerminalClasses;
#endif 	/* __IEnumTerminalClasses_FWD_DEFINED__ */


#ifndef __IEnumCall_FWD_DEFINED__
#define __IEnumCall_FWD_DEFINED__
typedef interface IEnumCall IEnumCall;
#endif 	/* __IEnumCall_FWD_DEFINED__ */


#ifndef __IEnumMediaTerminals_FWD_DEFINED__
#define __IEnumMediaTerminals_FWD_DEFINED__
typedef interface IEnumMediaTerminals IEnumMediaTerminals;
#endif 	/* __IEnumMediaTerminals_FWD_DEFINED__ */


#ifndef __IEnumParticipantInfo_FWD_DEFINED__
#define __IEnumParticipantInfo_FWD_DEFINED__
typedef interface IEnumParticipantInfo IEnumParticipantInfo;
#endif 	/* __IEnumParticipantInfo_FWD_DEFINED__ */


#ifndef __IEnumAddress_FWD_DEFINED__
#define __IEnumAddress_FWD_DEFINED__
typedef interface IEnumAddress IEnumAddress;
#endif 	/* __IEnumAddress_FWD_DEFINED__ */


#ifndef __IEnumExtendedMedia_FWD_DEFINED__
#define __IEnumExtendedMedia_FWD_DEFINED__
typedef interface IEnumExtendedMedia IEnumExtendedMedia;
#endif 	/* __IEnumExtendedMedia_FWD_DEFINED__ */


#ifndef __IEnumChannel_FWD_DEFINED__
#define __IEnumChannel_FWD_DEFINED__
typedef interface IEnumChannel IEnumChannel;
#endif 	/* __IEnumChannel_FWD_DEFINED__ */


#ifndef __ITTAPIEventNotification_FWD_DEFINED__
#define __ITTAPIEventNotification_FWD_DEFINED__
typedef interface ITTAPIEventNotification ITTAPIEventNotification;
#endif 	/* __ITTAPIEventNotification_FWD_DEFINED__ */


#ifndef __ITAddressEventNotification_FWD_DEFINED__
#define __ITAddressEventNotification_FWD_DEFINED__
typedef interface ITAddressEventNotification ITAddressEventNotification;
#endif 	/* __ITAddressEventNotification_FWD_DEFINED__ */


#ifndef __ITCallStateEvent_FWD_DEFINED__
#define __ITCallStateEvent_FWD_DEFINED__
typedef interface ITCallStateEvent ITCallStateEvent;
#endif 	/* __ITCallStateEvent_FWD_DEFINED__ */


#ifndef __ITCallMediaEvent_FWD_DEFINED__
#define __ITCallMediaEvent_FWD_DEFINED__
typedef interface ITCallMediaEvent ITCallMediaEvent;
#endif 	/* __ITCallMediaEvent_FWD_DEFINED__ */


#ifndef __ITCallNotification_FWD_DEFINED__
#define __ITCallNotification_FWD_DEFINED__
typedef interface ITCallNotification ITCallNotification;
#endif 	/* __ITCallNotification_FWD_DEFINED__ */


#ifndef __ITCallTonesNotification_FWD_DEFINED__
#define __ITCallTonesNotification_FWD_DEFINED__
typedef interface ITCallTonesNotification ITCallTonesNotification;
#endif 	/* __ITCallTonesNotification_FWD_DEFINED__ */


#ifndef __ITCollection_FWD_DEFINED__
#define __ITCollection_FWD_DEFINED__
typedef interface ITCollection ITCollection;
#endif 	/* __ITCollection_FWD_DEFINED__ */


#ifndef __ITTerminalManager_FWD_DEFINED__
#define __ITTerminalManager_FWD_DEFINED__
typedef interface ITTerminalManager ITTerminalManager;
#endif 	/* __ITTerminalManager_FWD_DEFINED__ */


#ifndef __ITChannel_FWD_DEFINED__
#define __ITChannel_FWD_DEFINED__
typedef interface ITChannel ITChannel;
#endif 	/* __ITChannel_FWD_DEFINED__ */


#ifndef __ITMultiChannelCall_FWD_DEFINED__
#define __ITMultiChannelCall_FWD_DEFINED__
typedef interface ITMultiChannelCall ITMultiChannelCall;
#endif 	/* __ITMultiChannelCall_FWD_DEFINED__ */


#ifndef __ITMultiChannelNotification_FWD_DEFINED__
#define __ITMultiChannelNotification_FWD_DEFINED__
typedef interface ITMultiChannelNotification ITMultiChannelNotification;
#endif 	/* __ITMultiChannelNotification_FWD_DEFINED__ */


#ifndef __ITCollection_FWD_DEFINED__
#define __ITCollection_FWD_DEFINED__
typedef interface ITCollection ITCollection;
#endif 	/* __ITCollection_FWD_DEFINED__ */


#ifndef __ITCallStateEvent_FWD_DEFINED__
#define __ITCallStateEvent_FWD_DEFINED__
typedef interface ITCallStateEvent ITCallStateEvent;
#endif 	/* __ITCallStateEvent_FWD_DEFINED__ */


#ifndef __ITCallNotification_FWD_DEFINED__
#define __ITCallNotification_FWD_DEFINED__
typedef interface ITCallNotification ITCallNotification;
#endif 	/* __ITCallNotification_FWD_DEFINED__ */


#ifndef __TAPI_FWD_DEFINED__
#define __TAPI_FWD_DEFINED__

#ifdef __cplusplus
typedef class TAPI TAPI;
#else
typedef struct TAPI TAPI;
#endif /* __cplusplus */

#endif 	/* __TAPI_FWD_DEFINED__ */


#ifndef __Terminal_FWD_DEFINED__
#define __Terminal_FWD_DEFINED__

#ifdef __cplusplus
typedef class Terminal Terminal;
#else
typedef struct Terminal Terminal;
#endif /* __cplusplus */

#endif 	/* __Terminal_FWD_DEFINED__ */


#ifndef __Address_FWD_DEFINED__
#define __Address_FWD_DEFINED__

#ifdef __cplusplus
typedef class Address Address;
#else
typedef struct Address Address;
#endif /* __cplusplus */

#endif 	/* __Address_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "strmif.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_tapi3_0000
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


typedef 
enum TAPI_EVENT
    {	TE_REINITIALIZE	= 0,
	TE_NEWADDRESS	= TE_REINITIALIZE + 1
    }	TAPI_EVENT;

typedef 
enum ADDRESS_EVENT
    {	AE_INSERVICE	= 0,
	AE_OUTOFSERVICE	= AE_INSERVICE + 1,
	AE_CLOSED	= AE_OUTOFSERVICE + 1
    }	ADDRESS_EVENT;

typedef 
enum ADDRESS_STATE
    {	AS_INSERVICE	= 0,
	AS_OUTOFSERVICE	= AS_INSERVICE + 1
    }	ADDRESS_STATE;

typedef 
enum CALL_EVENT_TYPE
    {	CET_CALLOWNER	= 0,
	CET_CALLMONITOR	= CET_CALLOWNER + 1,
	CET_CALLSTATEEVENT	= CET_CALLMONITOR + 1,
	CET_CALLMEDIAEVENT	= CET_CALLSTATEEVENT + 1
    }	CALL_EVENT_TYPE;

typedef 
enum CALL_STATE
    {	CS_IDLE	= 0,
	CS_INPROGRESS	= CS_IDLE + 1,
	CS_CONNECTED	= CS_INPROGRESS + 1,
	CS_DISCONNECTED	= CS_CONNECTED + 1,
	CS_OFFERING	= CS_DISCONNECTED + 1,
	CS_HOLD	= CS_OFFERING + 1,
	CS_QUEUED	= CS_HOLD + 1
    }	CALL_STATE;

typedef 
enum CALL_STATE_EVENT_CAUSE
    {	CEC_NONE	= 0,
	CEC_DISCONNECT_NORMAL	= CEC_NONE + 1,
	CEC_DISCONNECT_BUSY	= CEC_DISCONNECT_NORMAL + 1,
	CEC_DISCONNECT_BADADDRESS	= CEC_DISCONNECT_BUSY + 1,
	CEC_DISCONNECT_NOANSWER	= CEC_DISCONNECT_BADADDRESS + 1,
	CEC_DISCONNECT_CANCELLED	= CEC_DISCONNECT_NOANSWER + 1,
	CEC_DISCONNECT_REJECTED	= CEC_DISCONNECT_CANCELLED + 1,
	CEC_DISCONNECT_FAILED	= CEC_DISCONNECT_REJECTED + 1
    }	CALL_STATE_EVENT_CAUSE;

typedef 
enum CALL_MEDIA_EVENT
    {	CME_NOTDEFINED	= 0
    }	CALL_MEDIA_EVENT;

typedef 
enum CALL_MEDIA_CAUSE
    {	CMC_NOTDEFINED	= 0
    }	CALL_MEDIA_CAUSE;

typedef 
enum DISCONNECT_CODE
    {	DC_NORMAL	= 0,
	DC_NOANSWER	= DC_NORMAL + 1,
	DC_REJECTED	= DC_NOANSWER + 1
    }	DISCONNECT_CODE;

typedef 
enum TERMINAL_STATE
    {	TS_INUSE	= 0,
	TS_NOTINUSE	= TS_INUSE + 1
    }	TERMINAL_STATE;

typedef 
enum DIRECTION
    {	D_CAPTURE	= 0,
	D_RENDER	= D_CAPTURE + 1
    }	DIRECTION;

typedef 
enum TERMINAL_TYPE
    {	TT_STATIC	= 0,
	TT_DYNAMIC	= TT_STATIC + 1
    }	TERMINAL_TYPE;

typedef 
enum CALL_PRIVILEGE
    {	CP_OWNER	= 0,
	CP_MONITOR	= CP_OWNER + 1
    }	CALL_PRIVILEGE;























extern RPC_IF_HANDLE __MIDL_itf_tapi3_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_tapi3_0000_v0_0_s_ifspec;

#ifndef __ITTAPI_INTERFACE_DEFINED__
#define __ITTAPI_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITTAPI
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][unique][helpstring][uuid] */ 



EXTERN_C const IID IID_ITTAPI;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B1EFC382-9355-11d0-835C-00AA003CCABD")
    ITTAPI : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Shutdown( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Addresses( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE _EnumerateAddresses( 
            /* [retval][out] */ IEnumAddress __RPC_FAR *__RPC_FAR *ppEnumAddresses) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateMediaTerminal( 
            /* [in] */ BSTR pMediaType,
            /* [in] */ ITTerminal __RPC_FAR *pTerminal,
            /* [retval][out] */ ITMediaTerminal __RPC_FAR *__RPC_FAR *ppMediaTerminal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITTAPIVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITTAPI __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITTAPI __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITTAPI __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITTAPI __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITTAPI __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITTAPI __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITTAPI __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            ITTAPI __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Shutdown )( 
            ITTAPI __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Addresses )( 
            ITTAPI __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_EnumerateAddresses )( 
            ITTAPI __RPC_FAR * This,
            /* [retval][out] */ IEnumAddress __RPC_FAR *__RPC_FAR *ppEnumAddresses);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateMediaTerminal )( 
            ITTAPI __RPC_FAR * This,
            /* [in] */ BSTR pMediaType,
            /* [in] */ ITTerminal __RPC_FAR *pTerminal,
            /* [retval][out] */ ITMediaTerminal __RPC_FAR *__RPC_FAR *ppMediaTerminal);
        
        END_INTERFACE
    } ITTAPIVtbl;

    interface ITTAPI
    {
        CONST_VTBL struct ITTAPIVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITTAPI_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITTAPI_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITTAPI_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITTAPI_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITTAPI_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITTAPI_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITTAPI_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITTAPI_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define ITTAPI_Shutdown(This)	\
    (This)->lpVtbl -> Shutdown(This)

#define ITTAPI_get_Addresses(This,pVariant)	\
    (This)->lpVtbl -> get_Addresses(This,pVariant)

#define ITTAPI__EnumerateAddresses(This,ppEnumAddresses)	\
    (This)->lpVtbl -> _EnumerateAddresses(This,ppEnumAddresses)

#define ITTAPI_CreateMediaTerminal(This,pMediaType,pTerminal,ppMediaTerminal)	\
    (This)->lpVtbl -> CreateMediaTerminal(This,pMediaType,pTerminal,ppMediaTerminal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITTAPI_Initialize_Proxy( 
    ITTAPI __RPC_FAR * This);


void __RPC_STUB ITTAPI_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITTAPI_Shutdown_Proxy( 
    ITTAPI __RPC_FAR * This);


void __RPC_STUB ITTAPI_Shutdown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTAPI_get_Addresses_Proxy( 
    ITTAPI __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVariant);


void __RPC_STUB ITTAPI_get_Addresses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITTAPI__EnumerateAddresses_Proxy( 
    ITTAPI __RPC_FAR * This,
    /* [retval][out] */ IEnumAddress __RPC_FAR *__RPC_FAR *ppEnumAddresses);


void __RPC_STUB ITTAPI__EnumerateAddresses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITTAPI_CreateMediaTerminal_Proxy( 
    ITTAPI __RPC_FAR * This,
    /* [in] */ BSTR pMediaType,
    /* [in] */ ITTerminal __RPC_FAR *pTerminal,
    /* [retval][out] */ ITMediaTerminal __RPC_FAR *__RPC_FAR *ppMediaTerminal);


void __RPC_STUB ITTAPI_CreateMediaTerminal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITTAPI_INTERFACE_DEFINED__ */


#ifndef __ITMediaSupport_INTERFACE_DEFINED__
#define __ITMediaSupport_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITMediaSupport
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][helpstring][uuid] */ 



EXTERN_C const IID IID_ITMediaSupport;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B1EFC384-9355-11d0-835C-00AA003CCABD")
    ITMediaSupport : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaTypes( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE _EnumerateMediaTypes( 
            /* [retval][out] */ IEnumMediaType __RPC_FAR *__RPC_FAR *ppEnumMediaType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryDirectShowSupport( 
            /* [in] */ BSTR pMediaType,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfSupport) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryMediaType( 
            /* [in] */ BSTR pMediaType,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfSupport) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITMediaSupportVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITMediaSupport __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITMediaSupport __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITMediaSupport __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITMediaSupport __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITMediaSupport __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITMediaSupport __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITMediaSupport __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MediaTypes )( 
            ITMediaSupport __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_EnumerateMediaTypes )( 
            ITMediaSupport __RPC_FAR * This,
            /* [retval][out] */ IEnumMediaType __RPC_FAR *__RPC_FAR *ppEnumMediaType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryDirectShowSupport )( 
            ITMediaSupport __RPC_FAR * This,
            /* [in] */ BSTR pMediaType,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfSupport);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryMediaType )( 
            ITMediaSupport __RPC_FAR * This,
            /* [in] */ BSTR pMediaType,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfSupport);
        
        END_INTERFACE
    } ITMediaSupportVtbl;

    interface ITMediaSupport
    {
        CONST_VTBL struct ITMediaSupportVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITMediaSupport_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITMediaSupport_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITMediaSupport_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITMediaSupport_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITMediaSupport_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITMediaSupport_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITMediaSupport_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITMediaSupport_get_MediaTypes(This,pVariant)	\
    (This)->lpVtbl -> get_MediaTypes(This,pVariant)

#define ITMediaSupport__EnumerateMediaTypes(This,ppEnumMediaType)	\
    (This)->lpVtbl -> _EnumerateMediaTypes(This,ppEnumMediaType)

#define ITMediaSupport_QueryDirectShowSupport(This,pMediaType,pfSupport)	\
    (This)->lpVtbl -> QueryDirectShowSupport(This,pMediaType,pfSupport)

#define ITMediaSupport_QueryMediaType(This,pMediaType,pfSupport)	\
    (This)->lpVtbl -> QueryMediaType(This,pMediaType,pfSupport)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITMediaSupport_get_MediaTypes_Proxy( 
    ITMediaSupport __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVariant);


void __RPC_STUB ITMediaSupport_get_MediaTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITMediaSupport__EnumerateMediaTypes_Proxy( 
    ITMediaSupport __RPC_FAR * This,
    /* [retval][out] */ IEnumMediaType __RPC_FAR *__RPC_FAR *ppEnumMediaType);


void __RPC_STUB ITMediaSupport__EnumerateMediaTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITMediaSupport_QueryDirectShowSupport_Proxy( 
    ITMediaSupport __RPC_FAR * This,
    /* [in] */ BSTR pMediaType,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfSupport);


void __RPC_STUB ITMediaSupport_QueryDirectShowSupport_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITMediaSupport_QueryMediaType_Proxy( 
    ITMediaSupport __RPC_FAR * This,
    /* [in] */ BSTR pMediaType,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfSupport);


void __RPC_STUB ITMediaSupport_QueryMediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITMediaSupport_INTERFACE_DEFINED__ */


#ifndef __ITTerminalSupport_INTERFACE_DEFINED__
#define __ITTerminalSupport_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITTerminalSupport
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][helpstring][uuid] */ 



EXTERN_C const IID IID_ITTerminalSupport;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B1EFC385-9355-11d0-835C-00AA003CCABD")
    ITTerminalSupport : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StaticTerminals( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE _EnumerateStaticTerminals( 
            /* [retval][out] */ IEnumTerminal __RPC_FAR *__RPC_FAR *ppTerminalEnumerator) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DynamicTerminalClasses( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE _EnumerateDynamicTerminalClasses( 
            /* [retval][out] */ IEnumTerminalClasses __RPC_FAR *__RPC_FAR *ppTerminalClassEnumerator) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateTerminal( 
            /* [in] */ BSTR pTerminalClass,
            /* [retval][out] */ ITTerminal __RPC_FAR *__RPC_FAR *ppTerminal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDefaultTerminal( 
            /* [in] */ BSTR pMediaType,
            /* [retval][out] */ ITTerminal __RPC_FAR *__RPC_FAR *ppTerminal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITTerminalSupportVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITTerminalSupport __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITTerminalSupport __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITTerminalSupport __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITTerminalSupport __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITTerminalSupport __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITTerminalSupport __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITTerminalSupport __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StaticTerminals )( 
            ITTerminalSupport __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_EnumerateStaticTerminals )( 
            ITTerminalSupport __RPC_FAR * This,
            /* [retval][out] */ IEnumTerminal __RPC_FAR *__RPC_FAR *ppTerminalEnumerator);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DynamicTerminalClasses )( 
            ITTerminalSupport __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_EnumerateDynamicTerminalClasses )( 
            ITTerminalSupport __RPC_FAR * This,
            /* [retval][out] */ IEnumTerminalClasses __RPC_FAR *__RPC_FAR *ppTerminalClassEnumerator);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateTerminal )( 
            ITTerminalSupport __RPC_FAR * This,
            /* [in] */ BSTR pTerminalClass,
            /* [retval][out] */ ITTerminal __RPC_FAR *__RPC_FAR *ppTerminal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDefaultTerminal )( 
            ITTerminalSupport __RPC_FAR * This,
            /* [in] */ BSTR pMediaType,
            /* [retval][out] */ ITTerminal __RPC_FAR *__RPC_FAR *ppTerminal);
        
        END_INTERFACE
    } ITTerminalSupportVtbl;

    interface ITTerminalSupport
    {
        CONST_VTBL struct ITTerminalSupportVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITTerminalSupport_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITTerminalSupport_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITTerminalSupport_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITTerminalSupport_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITTerminalSupport_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITTerminalSupport_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITTerminalSupport_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITTerminalSupport_get_StaticTerminals(This,pVariant)	\
    (This)->lpVtbl -> get_StaticTerminals(This,pVariant)

#define ITTerminalSupport__EnumerateStaticTerminals(This,ppTerminalEnumerator)	\
    (This)->lpVtbl -> _EnumerateStaticTerminals(This,ppTerminalEnumerator)

#define ITTerminalSupport_get_DynamicTerminalClasses(This,pVariant)	\
    (This)->lpVtbl -> get_DynamicTerminalClasses(This,pVariant)

#define ITTerminalSupport__EnumerateDynamicTerminalClasses(This,ppTerminalClassEnumerator)	\
    (This)->lpVtbl -> _EnumerateDynamicTerminalClasses(This,ppTerminalClassEnumerator)

#define ITTerminalSupport_CreateTerminal(This,pTerminalClass,ppTerminal)	\
    (This)->lpVtbl -> CreateTerminal(This,pTerminalClass,ppTerminal)

#define ITTerminalSupport_GetDefaultTerminal(This,pMediaType,ppTerminal)	\
    (This)->lpVtbl -> GetDefaultTerminal(This,pMediaType,ppTerminal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTerminalSupport_get_StaticTerminals_Proxy( 
    ITTerminalSupport __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVariant);


void __RPC_STUB ITTerminalSupport_get_StaticTerminals_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITTerminalSupport__EnumerateStaticTerminals_Proxy( 
    ITTerminalSupport __RPC_FAR * This,
    /* [retval][out] */ IEnumTerminal __RPC_FAR *__RPC_FAR *ppTerminalEnumerator);


void __RPC_STUB ITTerminalSupport__EnumerateStaticTerminals_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTerminalSupport_get_DynamicTerminalClasses_Proxy( 
    ITTerminalSupport __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVariant);


void __RPC_STUB ITTerminalSupport_get_DynamicTerminalClasses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITTerminalSupport__EnumerateDynamicTerminalClasses_Proxy( 
    ITTerminalSupport __RPC_FAR * This,
    /* [retval][out] */ IEnumTerminalClasses __RPC_FAR *__RPC_FAR *ppTerminalClassEnumerator);


void __RPC_STUB ITTerminalSupport__EnumerateDynamicTerminalClasses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITTerminalSupport_CreateTerminal_Proxy( 
    ITTerminalSupport __RPC_FAR * This,
    /* [in] */ BSTR pTerminalClass,
    /* [retval][out] */ ITTerminal __RPC_FAR *__RPC_FAR *ppTerminal);


void __RPC_STUB ITTerminalSupport_CreateTerminal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITTerminalSupport_GetDefaultTerminal_Proxy( 
    ITTerminalSupport __RPC_FAR * This,
    /* [in] */ BSTR pMediaType,
    /* [retval][out] */ ITTerminal __RPC_FAR *__RPC_FAR *ppTerminal);


void __RPC_STUB ITTerminalSupport_GetDefaultTerminal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITTerminalSupport_INTERFACE_DEFINED__ */


#ifndef __ITAddress_INTERFACE_DEFINED__
#define __ITAddress_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITAddress
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][helpstring][uuid] */ 



EXTERN_C const IID IID_ITAddress;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B1EFC386-9355-11d0-835C-00AA003CCABD")
    ITAddress : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ ADDRESS_STATE __RPC_FAR *pAddressState) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AddressName( 
            /* [retval][out] */ BSTR __RPC_FAR *ppName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ServiceProviderName( 
            /* [retval][out] */ BSTR __RPC_FAR *ppName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TAPIObject( 
            /* [retval][out] */ ITTAPI __RPC_FAR *__RPC_FAR *ppTapiObject) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateCall( 
            /* [in] */ BSTR pDestAddress,
            /* [retval][out] */ ITBasicCallControl __RPC_FAR *__RPC_FAR *ppCall) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Calls( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE _EnumerateCalls( 
            /* [retval][out] */ IEnumCall __RPC_FAR *__RPC_FAR *ppCallEnum) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AddressTypes( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE _EnumerateAddressType( 
            /* [retval][out] */ IEnumAddressType __RPC_FAR *__RPC_FAR *ppEnumAddress) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RegisterCallTypes( 
            /* [in] */ VARIANT_BOOL fOutgoing,
            /* [in] */ VARIANT_BOOL fOwner,
            /* [in] */ VARIANT_BOOL fMonitor,
            /* [in] */ VARIANT MediaTypes) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITAddressVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITAddress __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITAddress __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITAddress __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITAddress __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITAddress __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITAddress __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITAddress __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            ITAddress __RPC_FAR * This,
            /* [retval][out] */ ADDRESS_STATE __RPC_FAR *pAddressState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AddressName )( 
            ITAddress __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ServiceProviderName )( 
            ITAddress __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TAPIObject )( 
            ITAddress __RPC_FAR * This,
            /* [retval][out] */ ITTAPI __RPC_FAR *__RPC_FAR *ppTapiObject);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateCall )( 
            ITAddress __RPC_FAR * This,
            /* [in] */ BSTR pDestAddress,
            /* [retval][out] */ ITBasicCallControl __RPC_FAR *__RPC_FAR *ppCall);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Calls )( 
            ITAddress __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_EnumerateCalls )( 
            ITAddress __RPC_FAR * This,
            /* [retval][out] */ IEnumCall __RPC_FAR *__RPC_FAR *ppCallEnum);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AddressTypes )( 
            ITAddress __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_EnumerateAddressType )( 
            ITAddress __RPC_FAR * This,
            /* [retval][out] */ IEnumAddressType __RPC_FAR *__RPC_FAR *ppEnumAddress);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterCallTypes )( 
            ITAddress __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fOutgoing,
            /* [in] */ VARIANT_BOOL fOwner,
            /* [in] */ VARIANT_BOOL fMonitor,
            /* [in] */ VARIANT MediaTypes);
        
        END_INTERFACE
    } ITAddressVtbl;

    interface ITAddress
    {
        CONST_VTBL struct ITAddressVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITAddress_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITAddress_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITAddress_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITAddress_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITAddress_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITAddress_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITAddress_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITAddress_get_State(This,pAddressState)	\
    (This)->lpVtbl -> get_State(This,pAddressState)

#define ITAddress_get_AddressName(This,ppName)	\
    (This)->lpVtbl -> get_AddressName(This,ppName)

#define ITAddress_get_ServiceProviderName(This,ppName)	\
    (This)->lpVtbl -> get_ServiceProviderName(This,ppName)

#define ITAddress_get_TAPIObject(This,ppTapiObject)	\
    (This)->lpVtbl -> get_TAPIObject(This,ppTapiObject)

#define ITAddress_CreateCall(This,pDestAddress,ppCall)	\
    (This)->lpVtbl -> CreateCall(This,pDestAddress,ppCall)

#define ITAddress_get_Calls(This,pVariant)	\
    (This)->lpVtbl -> get_Calls(This,pVariant)

#define ITAddress__EnumerateCalls(This,ppCallEnum)	\
    (This)->lpVtbl -> _EnumerateCalls(This,ppCallEnum)

#define ITAddress_get_AddressTypes(This,pVariant)	\
    (This)->lpVtbl -> get_AddressTypes(This,pVariant)

#define ITAddress__EnumerateAddressType(This,ppEnumAddress)	\
    (This)->lpVtbl -> _EnumerateAddressType(This,ppEnumAddress)

#define ITAddress_RegisterCallTypes(This,fOutgoing,fOwner,fMonitor,MediaTypes)	\
    (This)->lpVtbl -> RegisterCallTypes(This,fOutgoing,fOwner,fMonitor,MediaTypes)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITAddress_get_State_Proxy( 
    ITAddress __RPC_FAR * This,
    /* [retval][out] */ ADDRESS_STATE __RPC_FAR *pAddressState);


void __RPC_STUB ITAddress_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITAddress_get_AddressName_Proxy( 
    ITAddress __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppName);


void __RPC_STUB ITAddress_get_AddressName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITAddress_get_ServiceProviderName_Proxy( 
    ITAddress __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppName);


void __RPC_STUB ITAddress_get_ServiceProviderName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITAddress_get_TAPIObject_Proxy( 
    ITAddress __RPC_FAR * This,
    /* [retval][out] */ ITTAPI __RPC_FAR *__RPC_FAR *ppTapiObject);


void __RPC_STUB ITAddress_get_TAPIObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITAddress_CreateCall_Proxy( 
    ITAddress __RPC_FAR * This,
    /* [in] */ BSTR pDestAddress,
    /* [retval][out] */ ITBasicCallControl __RPC_FAR *__RPC_FAR *ppCall);


void __RPC_STUB ITAddress_CreateCall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITAddress_get_Calls_Proxy( 
    ITAddress __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVariant);


void __RPC_STUB ITAddress_get_Calls_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITAddress__EnumerateCalls_Proxy( 
    ITAddress __RPC_FAR * This,
    /* [retval][out] */ IEnumCall __RPC_FAR *__RPC_FAR *ppCallEnum);


void __RPC_STUB ITAddress__EnumerateCalls_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITAddress_get_AddressTypes_Proxy( 
    ITAddress __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVariant);


void __RPC_STUB ITAddress_get_AddressTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITAddress__EnumerateAddressType_Proxy( 
    ITAddress __RPC_FAR * This,
    /* [retval][out] */ IEnumAddressType __RPC_FAR *__RPC_FAR *ppEnumAddress);


void __RPC_STUB ITAddress__EnumerateAddressType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITAddress_RegisterCallTypes_Proxy( 
    ITAddress __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fOutgoing,
    /* [in] */ VARIANT_BOOL fOwner,
    /* [in] */ VARIANT_BOOL fMonitor,
    /* [in] */ VARIANT MediaTypes);


void __RPC_STUB ITAddress_RegisterCallTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITAddress_INTERFACE_DEFINED__ */


#ifndef __ITBasicCallControl_INTERFACE_DEFINED__
#define __ITBasicCallControl_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITBasicCallControl
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][helpstring][uuid] */ 



EXTERN_C const IID IID_ITBasicCallControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B1EFC389-9355-11d0-835C-00AA003CCABD")
    ITBasicCallControl : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectMediaTerminals( 
            VARIANT MediaTerminals) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnselectMediaTerminal( 
            /* [in] */ ITMediaTerminal __RPC_FAR *pMediaTerminal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Connect( 
            /* [in] */ VARIANT_BOOL fSync) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Answer( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Disconnect( 
            /* [in] */ DISCONNECT_CODE code) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Hold( 
            /* [in] */ VARIANT_BOOL fHold) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Handoff( 
            /* [in] */ BSTR pApplicationName,
            /* [in] */ BSTR pMediaType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddToConference( 
            /* [in] */ BSTR pDestAddress,
            /* [in] */ VARIANT_BOOL fSync,
            /* [retval][out] */ ITConsultCall __RPC_FAR *__RPC_FAR *ppConsultCall) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetupTransfer( 
            /* [in] */ BSTR pDestAddress,
            /* [in] */ VARIANT_BOOL fSync,
            /* [retval][out] */ ITConsultCall __RPC_FAR *__RPC_FAR *ppConsultCall) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDirectShowFilterGraph( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDirectShowFilter) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITBasicCallControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITBasicCallControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITBasicCallControl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITBasicCallControl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITBasicCallControl __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITBasicCallControl __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITBasicCallControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITBasicCallControl __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SelectMediaTerminals )( 
            ITBasicCallControl __RPC_FAR * This,
            VARIANT MediaTerminals);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnselectMediaTerminal )( 
            ITBasicCallControl __RPC_FAR * This,
            /* [in] */ ITMediaTerminal __RPC_FAR *pMediaTerminal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            ITBasicCallControl __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fSync);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Answer )( 
            ITBasicCallControl __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            ITBasicCallControl __RPC_FAR * This,
            /* [in] */ DISCONNECT_CODE code);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Hold )( 
            ITBasicCallControl __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fHold);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Handoff )( 
            ITBasicCallControl __RPC_FAR * This,
            /* [in] */ BSTR pApplicationName,
            /* [in] */ BSTR pMediaType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddToConference )( 
            ITBasicCallControl __RPC_FAR * This,
            /* [in] */ BSTR pDestAddress,
            /* [in] */ VARIANT_BOOL fSync,
            /* [retval][out] */ ITConsultCall __RPC_FAR *__RPC_FAR *ppConsultCall);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetupTransfer )( 
            ITBasicCallControl __RPC_FAR * This,
            /* [in] */ BSTR pDestAddress,
            /* [in] */ VARIANT_BOOL fSync,
            /* [retval][out] */ ITConsultCall __RPC_FAR *__RPC_FAR *ppConsultCall);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDirectShowFilterGraph )( 
            ITBasicCallControl __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDirectShowFilter);
        
        END_INTERFACE
    } ITBasicCallControlVtbl;

    interface ITBasicCallControl
    {
        CONST_VTBL struct ITBasicCallControlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITBasicCallControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITBasicCallControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITBasicCallControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITBasicCallControl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITBasicCallControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITBasicCallControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITBasicCallControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITBasicCallControl_SelectMediaTerminals(This,MediaTerminals)	\
    (This)->lpVtbl -> SelectMediaTerminals(This,MediaTerminals)

#define ITBasicCallControl_UnselectMediaTerminal(This,pMediaTerminal)	\
    (This)->lpVtbl -> UnselectMediaTerminal(This,pMediaTerminal)

#define ITBasicCallControl_Connect(This,fSync)	\
    (This)->lpVtbl -> Connect(This,fSync)

#define ITBasicCallControl_Answer(This)	\
    (This)->lpVtbl -> Answer(This)

#define ITBasicCallControl_Disconnect(This,code)	\
    (This)->lpVtbl -> Disconnect(This,code)

#define ITBasicCallControl_Hold(This,fHold)	\
    (This)->lpVtbl -> Hold(This,fHold)

#define ITBasicCallControl_Handoff(This,pApplicationName,pMediaType)	\
    (This)->lpVtbl -> Handoff(This,pApplicationName,pMediaType)

#define ITBasicCallControl_AddToConference(This,pDestAddress,fSync,ppConsultCall)	\
    (This)->lpVtbl -> AddToConference(This,pDestAddress,fSync,ppConsultCall)

#define ITBasicCallControl_SetupTransfer(This,pDestAddress,fSync,ppConsultCall)	\
    (This)->lpVtbl -> SetupTransfer(This,pDestAddress,fSync,ppConsultCall)

#define ITBasicCallControl_GetDirectShowFilterGraph(This,ppDirectShowFilter)	\
    (This)->lpVtbl -> GetDirectShowFilterGraph(This,ppDirectShowFilter)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITBasicCallControl_SelectMediaTerminals_Proxy( 
    ITBasicCallControl __RPC_FAR * This,
    VARIANT MediaTerminals);


void __RPC_STUB ITBasicCallControl_SelectMediaTerminals_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITBasicCallControl_UnselectMediaTerminal_Proxy( 
    ITBasicCallControl __RPC_FAR * This,
    /* [in] */ ITMediaTerminal __RPC_FAR *pMediaTerminal);


void __RPC_STUB ITBasicCallControl_UnselectMediaTerminal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITBasicCallControl_Connect_Proxy( 
    ITBasicCallControl __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fSync);


void __RPC_STUB ITBasicCallControl_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITBasicCallControl_Answer_Proxy( 
    ITBasicCallControl __RPC_FAR * This);


void __RPC_STUB ITBasicCallControl_Answer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITBasicCallControl_Disconnect_Proxy( 
    ITBasicCallControl __RPC_FAR * This,
    /* [in] */ DISCONNECT_CODE code);


void __RPC_STUB ITBasicCallControl_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITBasicCallControl_Hold_Proxy( 
    ITBasicCallControl __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fHold);


void __RPC_STUB ITBasicCallControl_Hold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITBasicCallControl_Handoff_Proxy( 
    ITBasicCallControl __RPC_FAR * This,
    /* [in] */ BSTR pApplicationName,
    /* [in] */ BSTR pMediaType);


void __RPC_STUB ITBasicCallControl_Handoff_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITBasicCallControl_AddToConference_Proxy( 
    ITBasicCallControl __RPC_FAR * This,
    /* [in] */ BSTR pDestAddress,
    /* [in] */ VARIANT_BOOL fSync,
    /* [retval][out] */ ITConsultCall __RPC_FAR *__RPC_FAR *ppConsultCall);


void __RPC_STUB ITBasicCallControl_AddToConference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITBasicCallControl_SetupTransfer_Proxy( 
    ITBasicCallControl __RPC_FAR * This,
    /* [in] */ BSTR pDestAddress,
    /* [in] */ VARIANT_BOOL fSync,
    /* [retval][out] */ ITConsultCall __RPC_FAR *__RPC_FAR *ppConsultCall);


void __RPC_STUB ITBasicCallControl_SetupTransfer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITBasicCallControl_GetDirectShowFilterGraph_Proxy( 
    ITBasicCallControl __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDirectShowFilter);


void __RPC_STUB ITBasicCallControl_GetDirectShowFilterGraph_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITBasicCallControl_INTERFACE_DEFINED__ */


#ifndef __ITCallInfo_INTERFACE_DEFINED__
#define __ITCallInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITCallInfo
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][helpstring][uuid] */ 



EXTERN_C const IID IID_ITCallInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B1EFC390-9355-11d0-835C-00AA003CCABD")
    ITCallInfo : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Address( 
            /* [retval][out] */ ITAddress __RPC_FAR *__RPC_FAR *ppAddress) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CallState( 
            /* [retval][out] */ CALL_STATE __RPC_FAR *pCallState) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Privilege( 
            /* [retval][out] */ CALL_PRIVILEGE __RPC_FAR *pPrivilege) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaTerminalsInUse( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE _EnumerateMediaTerminalsInUse( 
            /* [retval][out] */ IEnumMediaTerminals __RPC_FAR *__RPC_FAR *ppEnumMediaTerminals) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ParticipantInfo( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE _EnumerateParticipantInfo( 
            /* [retval][out] */ IEnumParticipantInfo __RPC_FAR *__RPC_FAR *ppEnumParticipantInfo) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ExtendedMediaTypes( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE _EnumerateExtendedMediaTypes( 
            /* [retval][out] */ IEnumExtendedMedia __RPC_FAR *__RPC_FAR *ppEnumExtendedMedia) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaTypesAvailable( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE _EnumerateMediaTypesAvailable( 
            /* [retval][out] */ IEnumMediaType __RPC_FAR *__RPC_FAR *ppEnumMediaType) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITCallInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITCallInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITCallInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITCallInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITCallInfo __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITCallInfo __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITCallInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITCallInfo __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Address )( 
            ITCallInfo __RPC_FAR * This,
            /* [retval][out] */ ITAddress __RPC_FAR *__RPC_FAR *ppAddress);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CallState )( 
            ITCallInfo __RPC_FAR * This,
            /* [retval][out] */ CALL_STATE __RPC_FAR *pCallState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Privilege )( 
            ITCallInfo __RPC_FAR * This,
            /* [retval][out] */ CALL_PRIVILEGE __RPC_FAR *pPrivilege);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MediaTerminalsInUse )( 
            ITCallInfo __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_EnumerateMediaTerminalsInUse )( 
            ITCallInfo __RPC_FAR * This,
            /* [retval][out] */ IEnumMediaTerminals __RPC_FAR *__RPC_FAR *ppEnumMediaTerminals);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ParticipantInfo )( 
            ITCallInfo __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_EnumerateParticipantInfo )( 
            ITCallInfo __RPC_FAR * This,
            /* [retval][out] */ IEnumParticipantInfo __RPC_FAR *__RPC_FAR *ppEnumParticipantInfo);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExtendedMediaTypes )( 
            ITCallInfo __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_EnumerateExtendedMediaTypes )( 
            ITCallInfo __RPC_FAR * This,
            /* [retval][out] */ IEnumExtendedMedia __RPC_FAR *__RPC_FAR *ppEnumExtendedMedia);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MediaTypesAvailable )( 
            ITCallInfo __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_EnumerateMediaTypesAvailable )( 
            ITCallInfo __RPC_FAR * This,
            /* [retval][out] */ IEnumMediaType __RPC_FAR *__RPC_FAR *ppEnumMediaType);
        
        END_INTERFACE
    } ITCallInfoVtbl;

    interface ITCallInfo
    {
        CONST_VTBL struct ITCallInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITCallInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITCallInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITCallInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITCallInfo_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITCallInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITCallInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITCallInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITCallInfo_get_Address(This,ppAddress)	\
    (This)->lpVtbl -> get_Address(This,ppAddress)

#define ITCallInfo_get_CallState(This,pCallState)	\
    (This)->lpVtbl -> get_CallState(This,pCallState)

#define ITCallInfo_get_Privilege(This,pPrivilege)	\
    (This)->lpVtbl -> get_Privilege(This,pPrivilege)

#define ITCallInfo_get_MediaTerminalsInUse(This,pVariant)	\
    (This)->lpVtbl -> get_MediaTerminalsInUse(This,pVariant)

#define ITCallInfo__EnumerateMediaTerminalsInUse(This,ppEnumMediaTerminals)	\
    (This)->lpVtbl -> _EnumerateMediaTerminalsInUse(This,ppEnumMediaTerminals)

#define ITCallInfo_get_ParticipantInfo(This,pVariant)	\
    (This)->lpVtbl -> get_ParticipantInfo(This,pVariant)

#define ITCallInfo__EnumerateParticipantInfo(This,ppEnumParticipantInfo)	\
    (This)->lpVtbl -> _EnumerateParticipantInfo(This,ppEnumParticipantInfo)

#define ITCallInfo_get_ExtendedMediaTypes(This,pVariant)	\
    (This)->lpVtbl -> get_ExtendedMediaTypes(This,pVariant)

#define ITCallInfo__EnumerateExtendedMediaTypes(This,ppEnumExtendedMedia)	\
    (This)->lpVtbl -> _EnumerateExtendedMediaTypes(This,ppEnumExtendedMedia)

#define ITCallInfo_get_MediaTypesAvailable(This,pVariant)	\
    (This)->lpVtbl -> get_MediaTypesAvailable(This,pVariant)

#define ITCallInfo__EnumerateMediaTypesAvailable(This,ppEnumMediaType)	\
    (This)->lpVtbl -> _EnumerateMediaTypesAvailable(This,ppEnumMediaType)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITCallInfo_get_Address_Proxy( 
    ITCallInfo __RPC_FAR * This,
    /* [retval][out] */ ITAddress __RPC_FAR *__RPC_FAR *ppAddress);


void __RPC_STUB ITCallInfo_get_Address_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITCallInfo_get_CallState_Proxy( 
    ITCallInfo __RPC_FAR * This,
    /* [retval][out] */ CALL_STATE __RPC_FAR *pCallState);


void __RPC_STUB ITCallInfo_get_CallState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITCallInfo_get_Privilege_Proxy( 
    ITCallInfo __RPC_FAR * This,
    /* [retval][out] */ CALL_PRIVILEGE __RPC_FAR *pPrivilege);


void __RPC_STUB ITCallInfo_get_Privilege_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITCallInfo_get_MediaTerminalsInUse_Proxy( 
    ITCallInfo __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVariant);


void __RPC_STUB ITCallInfo_get_MediaTerminalsInUse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITCallInfo__EnumerateMediaTerminalsInUse_Proxy( 
    ITCallInfo __RPC_FAR * This,
    /* [retval][out] */ IEnumMediaTerminals __RPC_FAR *__RPC_FAR *ppEnumMediaTerminals);


void __RPC_STUB ITCallInfo__EnumerateMediaTerminalsInUse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITCallInfo_get_ParticipantInfo_Proxy( 
    ITCallInfo __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVariant);


void __RPC_STUB ITCallInfo_get_ParticipantInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITCallInfo__EnumerateParticipantInfo_Proxy( 
    ITCallInfo __RPC_FAR * This,
    /* [retval][out] */ IEnumParticipantInfo __RPC_FAR *__RPC_FAR *ppEnumParticipantInfo);


void __RPC_STUB ITCallInfo__EnumerateParticipantInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITCallInfo_get_ExtendedMediaTypes_Proxy( 
    ITCallInfo __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVariant);


void __RPC_STUB ITCallInfo_get_ExtendedMediaTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITCallInfo__EnumerateExtendedMediaTypes_Proxy( 
    ITCallInfo __RPC_FAR * This,
    /* [retval][out] */ IEnumExtendedMedia __RPC_FAR *__RPC_FAR *ppEnumExtendedMedia);


void __RPC_STUB ITCallInfo__EnumerateExtendedMediaTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITCallInfo_get_MediaTypesAvailable_Proxy( 
    ITCallInfo __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVariant);


void __RPC_STUB ITCallInfo_get_MediaTypesAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITCallInfo__EnumerateMediaTypesAvailable_Proxy( 
    ITCallInfo __RPC_FAR * This,
    /* [retval][out] */ IEnumMediaType __RPC_FAR *__RPC_FAR *ppEnumMediaType);


void __RPC_STUB ITCallInfo__EnumerateMediaTypesAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITCallInfo_INTERFACE_DEFINED__ */


#ifndef __ITConsultCall_INTERFACE_DEFINED__
#define __ITConsultCall_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITConsultCall
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][helpstring][uuid] */ 



EXTERN_C const IID IID_ITConsultCall;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B1EFC391-9355-11d0-835C-00AA003CCABD")
    ITConsultCall : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CanIConsult( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfConsult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Finish( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITConsultCallVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITConsultCall __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITConsultCall __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITConsultCall __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITConsultCall __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITConsultCall __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITConsultCall __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITConsultCall __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CanIConsult )( 
            ITConsultCall __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfConsult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Finish )( 
            ITConsultCall __RPC_FAR * This);
        
        END_INTERFACE
    } ITConsultCallVtbl;

    interface ITConsultCall
    {
        CONST_VTBL struct ITConsultCallVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITConsultCall_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITConsultCall_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITConsultCall_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITConsultCall_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITConsultCall_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITConsultCall_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITConsultCall_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITConsultCall_CanIConsult(This,pfConsult)	\
    (This)->lpVtbl -> CanIConsult(This,pfConsult)

#define ITConsultCall_Finish(This)	\
    (This)->lpVtbl -> Finish(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITConsultCall_CanIConsult_Proxy( 
    ITConsultCall __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfConsult);


void __RPC_STUB ITConsultCall_CanIConsult_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITConsultCall_Finish_Proxy( 
    ITConsultCall __RPC_FAR * This);


void __RPC_STUB ITConsultCall_Finish_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITConsultCall_INTERFACE_DEFINED__ */


#ifndef __ITTerminal_INTERFACE_DEFINED__
#define __ITTerminal_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITTerminal
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][helpstring][uuid] */ 



EXTERN_C const IID IID_ITTerminal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B1EFC38A-9355-11d0-835C-00AA003CCABD")
    ITTerminal : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *ppName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ TERMINAL_STATE __RPC_FAR *pTerminalState) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Address( 
            /* [retval][out] */ ITAddress __RPC_FAR *__RPC_FAR *ppAddress) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TerminalType( 
            /* [retval][out] */ TERMINAL_TYPE __RPC_FAR *pType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TerminalClass( 
            /* [retval][out] */ BSTR __RPC_FAR *ppTerminalClass) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IsStandardTerminal( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfStandard) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CanRender( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfRender) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CanCapture( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfCapture) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITTerminalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITTerminal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITTerminal __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITTerminal __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITTerminal __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITTerminal __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITTerminal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITTerminal __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ITTerminal __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            ITTerminal __RPC_FAR * This,
            /* [retval][out] */ TERMINAL_STATE __RPC_FAR *pTerminalState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Address )( 
            ITTerminal __RPC_FAR * This,
            /* [retval][out] */ ITAddress __RPC_FAR *__RPC_FAR *ppAddress);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TerminalType )( 
            ITTerminal __RPC_FAR * This,
            /* [retval][out] */ TERMINAL_TYPE __RPC_FAR *pType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TerminalClass )( 
            ITTerminal __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppTerminalClass);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsStandardTerminal )( 
            ITTerminal __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfStandard);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CanRender )( 
            ITTerminal __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfRender);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CanCapture )( 
            ITTerminal __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfCapture);
        
        END_INTERFACE
    } ITTerminalVtbl;

    interface ITTerminal
    {
        CONST_VTBL struct ITTerminalVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITTerminal_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITTerminal_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITTerminal_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITTerminal_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITTerminal_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITTerminal_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITTerminal_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITTerminal_get_Name(This,ppName)	\
    (This)->lpVtbl -> get_Name(This,ppName)

#define ITTerminal_get_State(This,pTerminalState)	\
    (This)->lpVtbl -> get_State(This,pTerminalState)

#define ITTerminal_get_Address(This,ppAddress)	\
    (This)->lpVtbl -> get_Address(This,ppAddress)

#define ITTerminal_get_TerminalType(This,pType)	\
    (This)->lpVtbl -> get_TerminalType(This,pType)

#define ITTerminal_get_TerminalClass(This,ppTerminalClass)	\
    (This)->lpVtbl -> get_TerminalClass(This,ppTerminalClass)

#define ITTerminal_IsStandardTerminal(This,pfStandard)	\
    (This)->lpVtbl -> IsStandardTerminal(This,pfStandard)

#define ITTerminal_CanRender(This,pfRender)	\
    (This)->lpVtbl -> CanRender(This,pfRender)

#define ITTerminal_CanCapture(This,pfCapture)	\
    (This)->lpVtbl -> CanCapture(This,pfCapture)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTerminal_get_Name_Proxy( 
    ITTerminal __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppName);


void __RPC_STUB ITTerminal_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTerminal_get_State_Proxy( 
    ITTerminal __RPC_FAR * This,
    /* [retval][out] */ TERMINAL_STATE __RPC_FAR *pTerminalState);


void __RPC_STUB ITTerminal_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTerminal_get_Address_Proxy( 
    ITTerminal __RPC_FAR * This,
    /* [retval][out] */ ITAddress __RPC_FAR *__RPC_FAR *ppAddress);


void __RPC_STUB ITTerminal_get_Address_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTerminal_get_TerminalType_Proxy( 
    ITTerminal __RPC_FAR * This,
    /* [retval][out] */ TERMINAL_TYPE __RPC_FAR *pType);


void __RPC_STUB ITTerminal_get_TerminalType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITTerminal_get_TerminalClass_Proxy( 
    ITTerminal __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppTerminalClass);


void __RPC_STUB ITTerminal_get_TerminalClass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITTerminal_IsStandardTerminal_Proxy( 
    ITTerminal __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfStandard);


void __RPC_STUB ITTerminal_IsStandardTerminal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITTerminal_CanRender_Proxy( 
    ITTerminal __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfRender);


void __RPC_STUB ITTerminal_CanRender_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITTerminal_CanCapture_Proxy( 
    ITTerminal __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfCapture);


void __RPC_STUB ITTerminal_CanCapture_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITTerminal_INTERFACE_DEFINED__ */


#ifndef __ITAMTerminal_INTERFACE_DEFINED__
#define __ITAMTerminal_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITAMTerminal
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



EXTERN_C const IID IID_ITAMTerminal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("51011DE0-9FEE-11d0-A00D-00AA00B605A4")
    ITAMTerminal : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConnectPin( 
            /* [in] */ IGraphBuilder __RPC_FAR *pGraph,
            /* [in] */ IPin __RPC_FAR *pPin) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisconnectPin( 
            /* [in] */ IPin __RPC_FAR *pPin) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisconnectTerminal( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AMTAddress( 
            /* [retval][out] */ ITAddress __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AMTAddress( 
            /* [in] */ ITAddress __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaFormat( 
            /* [retval][out] */ AM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *pmt) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MediaFormat( 
            /* [in] */ AM_MEDIA_TYPE __RPC_FAR *pmt) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AllocatorProperties( 
            /* [retval][out] */ ALLOCATOR_PROPERTIES __RPC_FAR *pProperties) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AllocatorProperties( 
            /* [in] */ ALLOCATOR_PROPERTIES __RPC_FAR *pProperties) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITAMTerminalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITAMTerminal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITAMTerminal __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITAMTerminal __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectPin )( 
            ITAMTerminal __RPC_FAR * This,
            /* [in] */ IGraphBuilder __RPC_FAR *pGraph,
            /* [in] */ IPin __RPC_FAR *pPin);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisconnectPin )( 
            ITAMTerminal __RPC_FAR * This,
            /* [in] */ IPin __RPC_FAR *pPin);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisconnectTerminal )( 
            ITAMTerminal __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AMTAddress )( 
            ITAMTerminal __RPC_FAR * This,
            /* [retval][out] */ ITAddress __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AMTAddress )( 
            ITAMTerminal __RPC_FAR * This,
            /* [in] */ ITAddress __RPC_FAR *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MediaFormat )( 
            ITAMTerminal __RPC_FAR * This,
            /* [retval][out] */ AM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *pmt);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MediaFormat )( 
            ITAMTerminal __RPC_FAR * This,
            /* [in] */ AM_MEDIA_TYPE __RPC_FAR *pmt);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AllocatorProperties )( 
            ITAMTerminal __RPC_FAR * This,
            /* [retval][out] */ ALLOCATOR_PROPERTIES __RPC_FAR *pProperties);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AllocatorProperties )( 
            ITAMTerminal __RPC_FAR * This,
            /* [in] */ ALLOCATOR_PROPERTIES __RPC_FAR *pProperties);
        
        END_INTERFACE
    } ITAMTerminalVtbl;

    interface ITAMTerminal
    {
        CONST_VTBL struct ITAMTerminalVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITAMTerminal_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITAMTerminal_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITAMTerminal_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITAMTerminal_ConnectPin(This,pGraph,pPin)	\
    (This)->lpVtbl -> ConnectPin(This,pGraph,pPin)

#define ITAMTerminal_DisconnectPin(This,pPin)	\
    (This)->lpVtbl -> DisconnectPin(This,pPin)

#define ITAMTerminal_DisconnectTerminal(This)	\
    (This)->lpVtbl -> DisconnectTerminal(This)

#define ITAMTerminal_get_AMTAddress(This,pVal)	\
    (This)->lpVtbl -> get_AMTAddress(This,pVal)

#define ITAMTerminal_put_AMTAddress(This,newVal)	\
    (This)->lpVtbl -> put_AMTAddress(This,newVal)

#define ITAMTerminal_get_MediaFormat(This,pmt)	\
    (This)->lpVtbl -> get_MediaFormat(This,pmt)

#define ITAMTerminal_put_MediaFormat(This,pmt)	\
    (This)->lpVtbl -> put_MediaFormat(This,pmt)

#define ITAMTerminal_get_AllocatorProperties(This,pProperties)	\
    (This)->lpVtbl -> get_AllocatorProperties(This,pProperties)

#define ITAMTerminal_put_AllocatorProperties(This,pProperties)	\
    (This)->lpVtbl -> put_AllocatorProperties(This,pProperties)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITAMTerminal_ConnectPin_Proxy( 
    ITAMTerminal __RPC_FAR * This,
    /* [in] */ IGraphBuilder __RPC_FAR *pGraph,
    /* [in] */ IPin __RPC_FAR *pPin);


void __RPC_STUB ITAMTerminal_ConnectPin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITAMTerminal_DisconnectPin_Proxy( 
    ITAMTerminal __RPC_FAR * This,
    /* [in] */ IPin __RPC_FAR *pPin);


void __RPC_STUB ITAMTerminal_DisconnectPin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITAMTerminal_DisconnectTerminal_Proxy( 
    ITAMTerminal __RPC_FAR * This);


void __RPC_STUB ITAMTerminal_DisconnectTerminal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITAMTerminal_get_AMTAddress_Proxy( 
    ITAMTerminal __RPC_FAR * This,
    /* [retval][out] */ ITAddress __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB ITAMTerminal_get_AMTAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITAMTerminal_put_AMTAddress_Proxy( 
    ITAMTerminal __RPC_FAR * This,
    /* [in] */ ITAddress __RPC_FAR *newVal);


void __RPC_STUB ITAMTerminal_put_AMTAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITAMTerminal_get_MediaFormat_Proxy( 
    ITAMTerminal __RPC_FAR * This,
    /* [retval][out] */ AM_MEDIA_TYPE __RPC_FAR *__RPC_FAR *pmt);


void __RPC_STUB ITAMTerminal_get_MediaFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITAMTerminal_put_MediaFormat_Proxy( 
    ITAMTerminal __RPC_FAR * This,
    /* [in] */ AM_MEDIA_TYPE __RPC_FAR *pmt);


void __RPC_STUB ITAMTerminal_put_MediaFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITAMTerminal_get_AllocatorProperties_Proxy( 
    ITAMTerminal __RPC_FAR * This,
    /* [retval][out] */ ALLOCATOR_PROPERTIES __RPC_FAR *pProperties);


void __RPC_STUB ITAMTerminal_get_AllocatorProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITAMTerminal_put_AllocatorProperties_Proxy( 
    ITAMTerminal __RPC_FAR * This,
    /* [in] */ ALLOCATOR_PROPERTIES __RPC_FAR *pProperties);


void __RPC_STUB ITAMTerminal_put_AllocatorProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITAMTerminal_INTERFACE_DEFINED__ */


#ifndef __ITFileTerminal_INTERFACE_DEFINED__
#define __ITFileTerminal_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITFileTerminal
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][helpstring][uuid] */ 



EXTERN_C const IID IID_ITFileTerminal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B1EFC38C-9355-11d0-835C-00AA003CCABD")
    ITFileTerminal : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileName( 
            /* [in] */ BSTR pFileName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileName( 
            /* [retval][out] */ BSTR __RPC_FAR *ppFileName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITFileTerminalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITFileTerminal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITFileTerminal __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITFileTerminal __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITFileTerminal __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITFileTerminal __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITFileTerminal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITFileTerminal __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FileName )( 
            ITFileTerminal __RPC_FAR * This,
            /* [in] */ BSTR pFileName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FileName )( 
            ITFileTerminal __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppFileName);
        
        END_INTERFACE
    } ITFileTerminalVtbl;

    interface ITFileTerminal
    {
        CONST_VTBL struct ITFileTerminalVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITFileTerminal_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITFileTerminal_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITFileTerminal_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITFileTerminal_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITFileTerminal_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITFileTerminal_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITFileTerminal_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITFileTerminal_put_FileName(This,pFileName)	\
    (This)->lpVtbl -> put_FileName(This,pFileName)

#define ITFileTerminal_get_FileName(This,ppFileName)	\
    (This)->lpVtbl -> get_FileName(This,ppFileName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITFileTerminal_put_FileName_Proxy( 
    ITFileTerminal __RPC_FAR * This,
    /* [in] */ BSTR pFileName);


void __RPC_STUB ITFileTerminal_put_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITFileTerminal_get_FileName_Proxy( 
    ITFileTerminal __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppFileName);


void __RPC_STUB ITFileTerminal_get_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITFileTerminal_INTERFACE_DEFINED__ */


#ifndef __ITBasicAudioTerminal_INTERFACE_DEFINED__
#define __ITBasicAudioTerminal_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITBasicAudioTerminal
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][helpstring][uuid] */ 



EXTERN_C const IID IID_ITBasicAudioTerminal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B1EFC38D-9355-11d0-835C-00AA003CCABD")
    ITBasicAudioTerminal : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Volume( 
            /* [in] */ long lVolume) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Volume( 
            /* [retval][out] */ long __RPC_FAR *plVolume) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Balance( 
            /* [in] */ long lBalance) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Balance( 
            /* [retval][out] */ long __RPC_FAR *plBalance) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Gain( 
            /* [in] */ long lGain) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Gain( 
            /* [retval][out] */ long __RPC_FAR *plGain) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryFullDuplexSupport( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfSupport) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITBasicAudioTerminalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITBasicAudioTerminal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITBasicAudioTerminal __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITBasicAudioTerminal __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITBasicAudioTerminal __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITBasicAudioTerminal __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITBasicAudioTerminal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITBasicAudioTerminal __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Volume )( 
            ITBasicAudioTerminal __RPC_FAR * This,
            /* [in] */ long lVolume);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Volume )( 
            ITBasicAudioTerminal __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plVolume);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Balance )( 
            ITBasicAudioTerminal __RPC_FAR * This,
            /* [in] */ long lBalance);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Balance )( 
            ITBasicAudioTerminal __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plBalance);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Gain )( 
            ITBasicAudioTerminal __RPC_FAR * This,
            /* [in] */ long lGain);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Gain )( 
            ITBasicAudioTerminal __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plGain);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryFullDuplexSupport )( 
            ITBasicAudioTerminal __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfSupport);
        
        END_INTERFACE
    } ITBasicAudioTerminalVtbl;

    interface ITBasicAudioTerminal
    {
        CONST_VTBL struct ITBasicAudioTerminalVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITBasicAudioTerminal_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITBasicAudioTerminal_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITBasicAudioTerminal_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITBasicAudioTerminal_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITBasicAudioTerminal_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITBasicAudioTerminal_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITBasicAudioTerminal_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITBasicAudioTerminal_put_Volume(This,lVolume)	\
    (This)->lpVtbl -> put_Volume(This,lVolume)

#define ITBasicAudioTerminal_get_Volume(This,plVolume)	\
    (This)->lpVtbl -> get_Volume(This,plVolume)

#define ITBasicAudioTerminal_put_Balance(This,lBalance)	\
    (This)->lpVtbl -> put_Balance(This,lBalance)

#define ITBasicAudioTerminal_get_Balance(This,plBalance)	\
    (This)->lpVtbl -> get_Balance(This,plBalance)

#define ITBasicAudioTerminal_put_Gain(This,lGain)	\
    (This)->lpVtbl -> put_Gain(This,lGain)

#define ITBasicAudioTerminal_get_Gain(This,plGain)	\
    (This)->lpVtbl -> get_Gain(This,plGain)

#define ITBasicAudioTerminal_QueryFullDuplexSupport(This,pfSupport)	\
    (This)->lpVtbl -> QueryFullDuplexSupport(This,pfSupport)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITBasicAudioTerminal_put_Volume_Proxy( 
    ITBasicAudioTerminal __RPC_FAR * This,
    /* [in] */ long lVolume);


void __RPC_STUB ITBasicAudioTerminal_put_Volume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITBasicAudioTerminal_get_Volume_Proxy( 
    ITBasicAudioTerminal __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plVolume);


void __RPC_STUB ITBasicAudioTerminal_get_Volume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITBasicAudioTerminal_put_Balance_Proxy( 
    ITBasicAudioTerminal __RPC_FAR * This,
    /* [in] */ long lBalance);


void __RPC_STUB ITBasicAudioTerminal_put_Balance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITBasicAudioTerminal_get_Balance_Proxy( 
    ITBasicAudioTerminal __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plBalance);


void __RPC_STUB ITBasicAudioTerminal_get_Balance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITBasicAudioTerminal_put_Gain_Proxy( 
    ITBasicAudioTerminal __RPC_FAR * This,
    /* [in] */ long lGain);


void __RPC_STUB ITBasicAudioTerminal_put_Gain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITBasicAudioTerminal_get_Gain_Proxy( 
    ITBasicAudioTerminal __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plGain);


void __RPC_STUB ITBasicAudioTerminal_get_Gain_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITBasicAudioTerminal_QueryFullDuplexSupport_Proxy( 
    ITBasicAudioTerminal __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pfSupport);


void __RPC_STUB ITBasicAudioTerminal_QueryFullDuplexSupport_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITBasicAudioTerminal_INTERFACE_DEFINED__ */


#ifndef __ITMediaTerminal_INTERFACE_DEFINED__
#define __ITMediaTerminal_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITMediaTerminal
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][helpstring][uuid] */ 



EXTERN_C const IID IID_ITMediaTerminal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1EE10011-941B-11d0-835D-00AA003CCABD")
    ITMediaTerminal : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaType( 
            /* [retval][out] */ BSTR __RPC_FAR *ppMediaType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Terminal( 
            /* [retval][out] */ ITTerminal __RPC_FAR *__RPC_FAR *ppTerminal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITMediaTerminalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITMediaTerminal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITMediaTerminal __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITMediaTerminal __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITMediaTerminal __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITMediaTerminal __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITMediaTerminal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITMediaTerminal __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MediaType )( 
            ITMediaTerminal __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppMediaType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Terminal )( 
            ITMediaTerminal __RPC_FAR * This,
            /* [retval][out] */ ITTerminal __RPC_FAR *__RPC_FAR *ppTerminal);
        
        END_INTERFACE
    } ITMediaTerminalVtbl;

    interface ITMediaTerminal
    {
        CONST_VTBL struct ITMediaTerminalVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITMediaTerminal_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITMediaTerminal_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITMediaTerminal_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITMediaTerminal_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITMediaTerminal_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITMediaTerminal_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITMediaTerminal_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITMediaTerminal_get_MediaType(This,ppMediaType)	\
    (This)->lpVtbl -> get_MediaType(This,ppMediaType)

#define ITMediaTerminal_get_Terminal(This,ppTerminal)	\
    (This)->lpVtbl -> get_Terminal(This,ppTerminal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITMediaTerminal_get_MediaType_Proxy( 
    ITMediaTerminal __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppMediaType);


void __RPC_STUB ITMediaTerminal_get_MediaType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITMediaTerminal_get_Terminal_Proxy( 
    ITMediaTerminal __RPC_FAR * This,
    /* [retval][out] */ ITTerminal __RPC_FAR *__RPC_FAR *ppTerminal);


void __RPC_STUB ITMediaTerminal_get_Terminal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITMediaTerminal_INTERFACE_DEFINED__ */


#ifndef __ITParticipantInfo_INTERFACE_DEFINED__
#define __ITParticipantInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITParticipantInfo
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][helpstring][uuid] */ 



EXTERN_C const IID IID_ITParticipantInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3BD86751-9424-11d0-835D-00AA003CCABD")
    ITParticipantInfo : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *ppName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Address( 
            /* [retval][out] */ BSTR __RPC_FAR *ppAddressName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RelatedCall( 
            /* [retval][out] */ ITCallInfo __RPC_FAR *__RPC_FAR *ppCall) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Call( 
            /* [retval][out] */ ITCallInfo __RPC_FAR *__RPC_FAR *ppCall) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITParticipantInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITParticipantInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITParticipantInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITParticipantInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITParticipantInfo __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITParticipantInfo __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITParticipantInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITParticipantInfo __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ITParticipantInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Address )( 
            ITParticipantInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppAddressName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RelatedCall )( 
            ITParticipantInfo __RPC_FAR * This,
            /* [retval][out] */ ITCallInfo __RPC_FAR *__RPC_FAR *ppCall);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Call )( 
            ITParticipantInfo __RPC_FAR * This,
            /* [retval][out] */ ITCallInfo __RPC_FAR *__RPC_FAR *ppCall);
        
        END_INTERFACE
    } ITParticipantInfoVtbl;

    interface ITParticipantInfo
    {
        CONST_VTBL struct ITParticipantInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITParticipantInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITParticipantInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITParticipantInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITParticipantInfo_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITParticipantInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITParticipantInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITParticipantInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITParticipantInfo_get_Name(This,ppName)	\
    (This)->lpVtbl -> get_Name(This,ppName)

#define ITParticipantInfo_get_Address(This,ppAddressName)	\
    (This)->lpVtbl -> get_Address(This,ppAddressName)

#define ITParticipantInfo_get_RelatedCall(This,ppCall)	\
    (This)->lpVtbl -> get_RelatedCall(This,ppCall)

#define ITParticipantInfo_get_Call(This,ppCall)	\
    (This)->lpVtbl -> get_Call(This,ppCall)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITParticipantInfo_get_Name_Proxy( 
    ITParticipantInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppName);


void __RPC_STUB ITParticipantInfo_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITParticipantInfo_get_Address_Proxy( 
    ITParticipantInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppAddressName);


void __RPC_STUB ITParticipantInfo_get_Address_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITParticipantInfo_get_RelatedCall_Proxy( 
    ITParticipantInfo __RPC_FAR * This,
    /* [retval][out] */ ITCallInfo __RPC_FAR *__RPC_FAR *ppCall);


void __RPC_STUB ITParticipantInfo_get_RelatedCall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITParticipantInfo_get_Call_Proxy( 
    ITParticipantInfo __RPC_FAR * This,
    /* [retval][out] */ ITCallInfo __RPC_FAR *__RPC_FAR *ppCall);


void __RPC_STUB ITParticipantInfo_get_Call_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITParticipantInfo_INTERFACE_DEFINED__ */


#ifndef __ITCallTones_INTERFACE_DEFINED__
#define __ITCallTones_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITCallTones
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][helpstring][uuid] */ 



EXTERN_C const IID IID_ITCallTones;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("80B7F472-9CB2-11d0-8362-00AA003CCABD")
    ITCallTones : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GenerateDTMFs( 
            BSTR pDTMFs) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITCallTonesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITCallTones __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITCallTones __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITCallTones __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITCallTones __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITCallTones __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITCallTones __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITCallTones __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GenerateDTMFs )( 
            ITCallTones __RPC_FAR * This,
            BSTR pDTMFs);
        
        END_INTERFACE
    } ITCallTonesVtbl;

    interface ITCallTones
    {
        CONST_VTBL struct ITCallTonesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITCallTones_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITCallTones_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITCallTones_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITCallTones_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITCallTones_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITCallTones_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITCallTones_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITCallTones_GenerateDTMFs(This,pDTMFs)	\
    (This)->lpVtbl -> GenerateDTMFs(This,pDTMFs)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITCallTones_GenerateDTMFs_Proxy( 
    ITCallTones __RPC_FAR * This,
    BSTR pDTMFs);


void __RPC_STUB ITCallTones_GenerateDTMFs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITCallTones_INTERFACE_DEFINED__ */


#ifndef __IEnumAddressType_INTERFACE_DEFINED__
#define __IEnumAddressType_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IEnumAddressType
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



EXTERN_C const IID IID_IEnumAddressType;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AE269CF2-935E-11d0-835C-00AA003CCABD")
    IEnumAddressType : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ DWORD __RPC_FAR *pAddressTypes,
            /* [out] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IEnumAddressType __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumAddressTypeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumAddressType __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumAddressType __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumAddressType __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumAddressType __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [out] */ DWORD __RPC_FAR *pAddressTypes,
            /* [out] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumAddressType __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumAddressType __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumAddressType __RPC_FAR * This,
            /* [retval][out] */ IEnumAddressType __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IEnumAddressTypeVtbl;

    interface IEnumAddressType
    {
        CONST_VTBL struct IEnumAddressTypeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumAddressType_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumAddressType_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumAddressType_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumAddressType_Next(This,celt,pAddressTypes,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,pAddressTypes,pceltFetched)

#define IEnumAddressType_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumAddressType_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumAddressType_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumAddressType_Next_Proxy( 
    IEnumAddressType __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [out] */ DWORD __RPC_FAR *pAddressTypes,
    /* [out] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IEnumAddressType_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumAddressType_Reset_Proxy( 
    IEnumAddressType __RPC_FAR * This);


void __RPC_STUB IEnumAddressType_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumAddressType_Skip_Proxy( 
    IEnumAddressType __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumAddressType_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumAddressType_Clone_Proxy( 
    IEnumAddressType __RPC_FAR * This,
    /* [retval][out] */ IEnumAddressType __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IEnumAddressType_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumAddressType_INTERFACE_DEFINED__ */


#ifndef __IEnumMediaType_INTERFACE_DEFINED__
#define __IEnumMediaType_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IEnumMediaType
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



EXTERN_C const IID IID_IEnumMediaType;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AE269CF3-935E-11d0-835C-00AA003CCABD")
    IEnumMediaType : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ BSTR __RPC_FAR *ppElements,
            /* [out] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IEnumMediaType __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumMediaTypeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumMediaType __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumMediaType __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumMediaType __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumMediaType __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [out] */ BSTR __RPC_FAR *ppElements,
            /* [out] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumMediaType __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumMediaType __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumMediaType __RPC_FAR * This,
            /* [retval][out] */ IEnumMediaType __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IEnumMediaTypeVtbl;

    interface IEnumMediaType
    {
        CONST_VTBL struct IEnumMediaTypeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumMediaType_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumMediaType_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumMediaType_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumMediaType_Next(This,celt,ppElements,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,ppElements,pceltFetched)

#define IEnumMediaType_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumMediaType_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumMediaType_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumMediaType_Next_Proxy( 
    IEnumMediaType __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [out] */ BSTR __RPC_FAR *ppElements,
    /* [out] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IEnumMediaType_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumMediaType_Reset_Proxy( 
    IEnumMediaType __RPC_FAR * This);


void __RPC_STUB IEnumMediaType_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumMediaType_Skip_Proxy( 
    IEnumMediaType __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumMediaType_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumMediaType_Clone_Proxy( 
    IEnumMediaType __RPC_FAR * This,
    /* [retval][out] */ IEnumMediaType __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IEnumMediaType_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumMediaType_INTERFACE_DEFINED__ */


#ifndef __IEnumTerminal_INTERFACE_DEFINED__
#define __IEnumTerminal_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IEnumTerminal
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



EXTERN_C const IID IID_IEnumTerminal;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AE269CF4-935E-11d0-835C-00AA003CCABD")
    IEnumTerminal : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ITTerminal __RPC_FAR *__RPC_FAR *ppElements,
            /* [out] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IEnumTerminal __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumTerminalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumTerminal __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumTerminal __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumTerminal __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumTerminal __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [out] */ ITTerminal __RPC_FAR *__RPC_FAR *ppElements,
            /* [out] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumTerminal __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumTerminal __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumTerminal __RPC_FAR * This,
            /* [retval][out] */ IEnumTerminal __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IEnumTerminalVtbl;

    interface IEnumTerminal
    {
        CONST_VTBL struct IEnumTerminalVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumTerminal_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumTerminal_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumTerminal_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumTerminal_Next(This,celt,ppElements,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,ppElements,pceltFetched)

#define IEnumTerminal_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumTerminal_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumTerminal_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumTerminal_Next_Proxy( 
    IEnumTerminal __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [out] */ ITTerminal __RPC_FAR *__RPC_FAR *ppElements,
    /* [out] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IEnumTerminal_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumTerminal_Reset_Proxy( 
    IEnumTerminal __RPC_FAR * This);


void __RPC_STUB IEnumTerminal_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumTerminal_Skip_Proxy( 
    IEnumTerminal __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumTerminal_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumTerminal_Clone_Proxy( 
    IEnumTerminal __RPC_FAR * This,
    /* [retval][out] */ IEnumTerminal __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IEnumTerminal_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumTerminal_INTERFACE_DEFINED__ */


#ifndef __IEnumTerminalClasses_INTERFACE_DEFINED__
#define __IEnumTerminalClasses_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IEnumTerminalClasses
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



EXTERN_C const IID IID_IEnumTerminalClasses;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AE269CF5-935E-11d0-835C-00AA003CCABD")
    IEnumTerminalClasses : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ GUID __RPC_FAR *__RPC_FAR *ppElements,
            /* [out] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IEnumTerminalClasses __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumTerminalClassesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumTerminalClasses __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumTerminalClasses __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumTerminalClasses __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumTerminalClasses __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [out] */ GUID __RPC_FAR *__RPC_FAR *ppElements,
            /* [out] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumTerminalClasses __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumTerminalClasses __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumTerminalClasses __RPC_FAR * This,
            /* [retval][out] */ IEnumTerminalClasses __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IEnumTerminalClassesVtbl;

    interface IEnumTerminalClasses
    {
        CONST_VTBL struct IEnumTerminalClassesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumTerminalClasses_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumTerminalClasses_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumTerminalClasses_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumTerminalClasses_Next(This,celt,ppElements,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,ppElements,pceltFetched)

#define IEnumTerminalClasses_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumTerminalClasses_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumTerminalClasses_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumTerminalClasses_Next_Proxy( 
    IEnumTerminalClasses __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [out] */ GUID __RPC_FAR *__RPC_FAR *ppElements,
    /* [out] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IEnumTerminalClasses_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumTerminalClasses_Reset_Proxy( 
    IEnumTerminalClasses __RPC_FAR * This);


void __RPC_STUB IEnumTerminalClasses_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumTerminalClasses_Skip_Proxy( 
    IEnumTerminalClasses __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumTerminalClasses_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumTerminalClasses_Clone_Proxy( 
    IEnumTerminalClasses __RPC_FAR * This,
    /* [retval][out] */ IEnumTerminalClasses __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IEnumTerminalClasses_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumTerminalClasses_INTERFACE_DEFINED__ */


#ifndef __IEnumCall_INTERFACE_DEFINED__
#define __IEnumCall_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IEnumCall
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



EXTERN_C const IID IID_IEnumCall;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AE269CF6-935E-11d0-835C-00AA003CCABD")
    IEnumCall : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ITCallInfo __RPC_FAR *__RPC_FAR *ppElements,
            /* [out] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IEnumCall __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumCallVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumCall __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumCall __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumCall __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumCall __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [out] */ ITCallInfo __RPC_FAR *__RPC_FAR *ppElements,
            /* [out] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumCall __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumCall __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumCall __RPC_FAR * This,
            /* [retval][out] */ IEnumCall __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IEnumCallVtbl;

    interface IEnumCall
    {
        CONST_VTBL struct IEnumCallVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumCall_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumCall_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumCall_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumCall_Next(This,celt,ppElements,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,ppElements,pceltFetched)

#define IEnumCall_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumCall_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumCall_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumCall_Next_Proxy( 
    IEnumCall __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [out] */ ITCallInfo __RPC_FAR *__RPC_FAR *ppElements,
    /* [out] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IEnumCall_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumCall_Reset_Proxy( 
    IEnumCall __RPC_FAR * This);


void __RPC_STUB IEnumCall_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumCall_Skip_Proxy( 
    IEnumCall __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumCall_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumCall_Clone_Proxy( 
    IEnumCall __RPC_FAR * This,
    /* [retval][out] */ IEnumCall __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IEnumCall_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumCall_INTERFACE_DEFINED__ */


#ifndef __IEnumMediaTerminals_INTERFACE_DEFINED__
#define __IEnumMediaTerminals_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IEnumMediaTerminals
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



EXTERN_C const IID IID_IEnumMediaTerminals;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AE269CF8-935E-11d0-835C-00AA003CCABD")
    IEnumMediaTerminals : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ITMediaTerminal __RPC_FAR *__RPC_FAR *ppElements,
            /* [out] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IEnumMediaTerminals __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumMediaTerminalsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumMediaTerminals __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumMediaTerminals __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumMediaTerminals __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumMediaTerminals __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [out] */ ITMediaTerminal __RPC_FAR *__RPC_FAR *ppElements,
            /* [out] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumMediaTerminals __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumMediaTerminals __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumMediaTerminals __RPC_FAR * This,
            /* [retval][out] */ IEnumMediaTerminals __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IEnumMediaTerminalsVtbl;

    interface IEnumMediaTerminals
    {
        CONST_VTBL struct IEnumMediaTerminalsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumMediaTerminals_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumMediaTerminals_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumMediaTerminals_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumMediaTerminals_Next(This,celt,ppElements,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,ppElements,pceltFetched)

#define IEnumMediaTerminals_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumMediaTerminals_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumMediaTerminals_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumMediaTerminals_Next_Proxy( 
    IEnumMediaTerminals __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [out] */ ITMediaTerminal __RPC_FAR *__RPC_FAR *ppElements,
    /* [out] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IEnumMediaTerminals_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumMediaTerminals_Reset_Proxy( 
    IEnumMediaTerminals __RPC_FAR * This);


void __RPC_STUB IEnumMediaTerminals_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumMediaTerminals_Skip_Proxy( 
    IEnumMediaTerminals __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumMediaTerminals_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumMediaTerminals_Clone_Proxy( 
    IEnumMediaTerminals __RPC_FAR * This,
    /* [retval][out] */ IEnumMediaTerminals __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IEnumMediaTerminals_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumMediaTerminals_INTERFACE_DEFINED__ */


#ifndef __IEnumParticipantInfo_INTERFACE_DEFINED__
#define __IEnumParticipantInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IEnumParticipantInfo
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



EXTERN_C const IID IID_IEnumParticipantInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AE269CF9-935E-11d0-835C-00AA003CCABD")
    IEnumParticipantInfo : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ITParticipantInfo __RPC_FAR *__RPC_FAR *ppElements,
            /* [out] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IEnumParticipantInfo __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumParticipantInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumParticipantInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumParticipantInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumParticipantInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumParticipantInfo __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [out] */ ITParticipantInfo __RPC_FAR *__RPC_FAR *ppElements,
            /* [out] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumParticipantInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumParticipantInfo __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumParticipantInfo __RPC_FAR * This,
            /* [retval][out] */ IEnumParticipantInfo __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IEnumParticipantInfoVtbl;

    interface IEnumParticipantInfo
    {
        CONST_VTBL struct IEnumParticipantInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumParticipantInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumParticipantInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumParticipantInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumParticipantInfo_Next(This,celt,ppElements,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,ppElements,pceltFetched)

#define IEnumParticipantInfo_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumParticipantInfo_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumParticipantInfo_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumParticipantInfo_Next_Proxy( 
    IEnumParticipantInfo __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [out] */ ITParticipantInfo __RPC_FAR *__RPC_FAR *ppElements,
    /* [out] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IEnumParticipantInfo_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumParticipantInfo_Reset_Proxy( 
    IEnumParticipantInfo __RPC_FAR * This);


void __RPC_STUB IEnumParticipantInfo_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumParticipantInfo_Skip_Proxy( 
    IEnumParticipantInfo __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumParticipantInfo_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumParticipantInfo_Clone_Proxy( 
    IEnumParticipantInfo __RPC_FAR * This,
    /* [retval][out] */ IEnumParticipantInfo __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IEnumParticipantInfo_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumParticipantInfo_INTERFACE_DEFINED__ */


#ifndef __IEnumAddress_INTERFACE_DEFINED__
#define __IEnumAddress_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IEnumAddress
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



EXTERN_C const IID IID_IEnumAddress;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1666FCA1-9363-11d0-835C-00AA003CCABD")
    IEnumAddress : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ITAddress __RPC_FAR *__RPC_FAR *ppElements,
            /* [out] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IEnumAddress __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumAddressVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumAddress __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumAddress __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumAddress __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumAddress __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [out] */ ITAddress __RPC_FAR *__RPC_FAR *ppElements,
            /* [out] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumAddress __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumAddress __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumAddress __RPC_FAR * This,
            /* [retval][out] */ IEnumAddress __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IEnumAddressVtbl;

    interface IEnumAddress
    {
        CONST_VTBL struct IEnumAddressVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumAddress_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumAddress_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumAddress_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumAddress_Next(This,celt,ppElements,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,ppElements,pceltFetched)

#define IEnumAddress_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumAddress_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumAddress_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumAddress_Next_Proxy( 
    IEnumAddress __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [out] */ ITAddress __RPC_FAR *__RPC_FAR *ppElements,
    /* [out] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IEnumAddress_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumAddress_Reset_Proxy( 
    IEnumAddress __RPC_FAR * This);


void __RPC_STUB IEnumAddress_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumAddress_Skip_Proxy( 
    IEnumAddress __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumAddress_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumAddress_Clone_Proxy( 
    IEnumAddress __RPC_FAR * This,
    /* [retval][out] */ IEnumAddress __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IEnumAddress_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumAddress_INTERFACE_DEFINED__ */


#ifndef __IEnumExtendedMedia_INTERFACE_DEFINED__
#define __IEnumExtendedMedia_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IEnumExtendedMedia
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



EXTERN_C const IID IID_IEnumExtendedMedia;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5EC5ACF1-9C02-11d0-8362-00AA003CCABD")
    IEnumExtendedMedia : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ BSTR __RPC_FAR *ppElements,
            /* [out] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IEnumExtendedMedia __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumExtendedMediaVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumExtendedMedia __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumExtendedMedia __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumExtendedMedia __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumExtendedMedia __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [out] */ BSTR __RPC_FAR *ppElements,
            /* [out] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumExtendedMedia __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumExtendedMedia __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumExtendedMedia __RPC_FAR * This,
            /* [retval][out] */ IEnumExtendedMedia __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IEnumExtendedMediaVtbl;

    interface IEnumExtendedMedia
    {
        CONST_VTBL struct IEnumExtendedMediaVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumExtendedMedia_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumExtendedMedia_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumExtendedMedia_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumExtendedMedia_Next(This,celt,ppElements,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,ppElements,pceltFetched)

#define IEnumExtendedMedia_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumExtendedMedia_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumExtendedMedia_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumExtendedMedia_Next_Proxy( 
    IEnumExtendedMedia __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [out] */ BSTR __RPC_FAR *ppElements,
    /* [out] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IEnumExtendedMedia_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumExtendedMedia_Reset_Proxy( 
    IEnumExtendedMedia __RPC_FAR * This);


void __RPC_STUB IEnumExtendedMedia_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumExtendedMedia_Skip_Proxy( 
    IEnumExtendedMedia __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumExtendedMedia_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumExtendedMedia_Clone_Proxy( 
    IEnumExtendedMedia __RPC_FAR * This,
    /* [retval][out] */ IEnumExtendedMedia __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IEnumExtendedMedia_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumExtendedMedia_INTERFACE_DEFINED__ */


#ifndef __IEnumChannel_INTERFACE_DEFINED__
#define __IEnumChannel_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IEnumChannel
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



EXTERN_C const IID IID_IEnumChannel;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2D42EEC5-A70D-11d0-AB84-00AA003CCABD")
    IEnumChannel : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ ITChannel __RPC_FAR *__RPC_FAR *ppElements,
            /* [out] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IEnumChannel __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumChannelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumChannel __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumChannel __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumChannel __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumChannel __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [out] */ ITChannel __RPC_FAR *__RPC_FAR *ppElements,
            /* [out] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumChannel __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumChannel __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumChannel __RPC_FAR * This,
            /* [retval][out] */ IEnumChannel __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IEnumChannelVtbl;

    interface IEnumChannel
    {
        CONST_VTBL struct IEnumChannelVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumChannel_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumChannel_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumChannel_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumChannel_Next(This,celt,ppElements,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,ppElements,pceltFetched)

#define IEnumChannel_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumChannel_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumChannel_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumChannel_Next_Proxy( 
    IEnumChannel __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [out] */ ITChannel __RPC_FAR *__RPC_FAR *ppElements,
    /* [out] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IEnumChannel_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumChannel_Reset_Proxy( 
    IEnumChannel __RPC_FAR * This);


void __RPC_STUB IEnumChannel_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumChannel_Skip_Proxy( 
    IEnumChannel __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumChannel_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumChannel_Clone_Proxy( 
    IEnumChannel __RPC_FAR * This,
    /* [retval][out] */ IEnumChannel __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IEnumChannel_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumChannel_INTERFACE_DEFINED__ */


#ifndef __ITTAPIEventNotification_INTERFACE_DEFINED__
#define __ITTAPIEventNotification_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITTAPIEventNotification
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



EXTERN_C const IID IID_ITTAPIEventNotification;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62F47095-95C9-11d0-835D-00AA003CCABD")
    ITTAPIEventNotification : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Event( 
            /* [in] */ TAPI_EVENT Event) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITTAPIEventNotificationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITTAPIEventNotification __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITTAPIEventNotification __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITTAPIEventNotification __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITTAPIEventNotification __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITTAPIEventNotification __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITTAPIEventNotification __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITTAPIEventNotification __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Event )( 
            ITTAPIEventNotification __RPC_FAR * This,
            /* [in] */ TAPI_EVENT Event);
        
        END_INTERFACE
    } ITTAPIEventNotificationVtbl;

    interface ITTAPIEventNotification
    {
        CONST_VTBL struct ITTAPIEventNotificationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITTAPIEventNotification_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITTAPIEventNotification_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITTAPIEventNotification_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITTAPIEventNotification_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITTAPIEventNotification_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITTAPIEventNotification_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITTAPIEventNotification_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITTAPIEventNotification_Event(This,Event)	\
    (This)->lpVtbl -> Event(This,Event)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITTAPIEventNotification_Event_Proxy( 
    ITTAPIEventNotification __RPC_FAR * This,
    /* [in] */ TAPI_EVENT Event);


void __RPC_STUB ITTAPIEventNotification_Event_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITTAPIEventNotification_INTERFACE_DEFINED__ */


#ifndef __ITAddressEventNotification_INTERFACE_DEFINED__
#define __ITAddressEventNotification_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITAddressEventNotification
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



EXTERN_C const IID IID_ITAddressEventNotification;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62F47096-95C9-11d0-835D-00AA003CCABD")
    ITAddressEventNotification : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddressEventNotification( 
            /* [in] */ ITAddress __RPC_FAR *pAddress,
            /* [in] */ ADDRESS_EVENT Event) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITAddressEventNotificationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITAddressEventNotification __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITAddressEventNotification __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITAddressEventNotification __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITAddressEventNotification __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITAddressEventNotification __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITAddressEventNotification __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITAddressEventNotification __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddressEventNotification )( 
            ITAddressEventNotification __RPC_FAR * This,
            /* [in] */ ITAddress __RPC_FAR *pAddress,
            /* [in] */ ADDRESS_EVENT Event);
        
        END_INTERFACE
    } ITAddressEventNotificationVtbl;

    interface ITAddressEventNotification
    {
        CONST_VTBL struct ITAddressEventNotificationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITAddressEventNotification_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITAddressEventNotification_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITAddressEventNotification_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITAddressEventNotification_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITAddressEventNotification_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITAddressEventNotification_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITAddressEventNotification_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITAddressEventNotification_AddressEventNotification(This,pAddress,Event)	\
    (This)->lpVtbl -> AddressEventNotification(This,pAddress,Event)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITAddressEventNotification_AddressEventNotification_Proxy( 
    ITAddressEventNotification __RPC_FAR * This,
    /* [in] */ ITAddress __RPC_FAR *pAddress,
    /* [in] */ ADDRESS_EVENT Event);


void __RPC_STUB ITAddressEventNotification_AddressEventNotification_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITAddressEventNotification_INTERFACE_DEFINED__ */


#ifndef __ITCallStateEvent_INTERFACE_DEFINED__
#define __ITCallStateEvent_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITCallStateEvent
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][helpstring][uuid] */ 



EXTERN_C const IID IID_ITCallStateEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62F47097-95C9-11d0-835D-00AA003CCABD")
    ITCallStateEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Call( 
            /* [retval][out] */ ITCallInfo __RPC_FAR *__RPC_FAR *ppCallInfo) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ CALL_STATE __RPC_FAR *pCallState) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Cause( 
            /* [retval][out] */ CALL_STATE_EVENT_CAUSE __RPC_FAR *pCEC) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITCallStateEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITCallStateEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITCallStateEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITCallStateEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITCallStateEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITCallStateEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITCallStateEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITCallStateEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Call )( 
            ITCallStateEvent __RPC_FAR * This,
            /* [retval][out] */ ITCallInfo __RPC_FAR *__RPC_FAR *ppCallInfo);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            ITCallStateEvent __RPC_FAR * This,
            /* [retval][out] */ CALL_STATE __RPC_FAR *pCallState);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Cause )( 
            ITCallStateEvent __RPC_FAR * This,
            /* [retval][out] */ CALL_STATE_EVENT_CAUSE __RPC_FAR *pCEC);
        
        END_INTERFACE
    } ITCallStateEventVtbl;

    interface ITCallStateEvent
    {
        CONST_VTBL struct ITCallStateEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITCallStateEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITCallStateEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITCallStateEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITCallStateEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITCallStateEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITCallStateEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITCallStateEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITCallStateEvent_get_Call(This,ppCallInfo)	\
    (This)->lpVtbl -> get_Call(This,ppCallInfo)

#define ITCallStateEvent_get_State(This,pCallState)	\
    (This)->lpVtbl -> get_State(This,pCallState)

#define ITCallStateEvent_get_Cause(This,pCEC)	\
    (This)->lpVtbl -> get_Cause(This,pCEC)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITCallStateEvent_get_Call_Proxy( 
    ITCallStateEvent __RPC_FAR * This,
    /* [retval][out] */ ITCallInfo __RPC_FAR *__RPC_FAR *ppCallInfo);


void __RPC_STUB ITCallStateEvent_get_Call_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITCallStateEvent_get_State_Proxy( 
    ITCallStateEvent __RPC_FAR * This,
    /* [retval][out] */ CALL_STATE __RPC_FAR *pCallState);


void __RPC_STUB ITCallStateEvent_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITCallStateEvent_get_Cause_Proxy( 
    ITCallStateEvent __RPC_FAR * This,
    /* [retval][out] */ CALL_STATE_EVENT_CAUSE __RPC_FAR *pCEC);


void __RPC_STUB ITCallStateEvent_get_Cause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITCallStateEvent_INTERFACE_DEFINED__ */


#ifndef __ITCallMediaEvent_INTERFACE_DEFINED__
#define __ITCallMediaEvent_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITCallMediaEvent
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][helpstring][uuid] */ 



EXTERN_C const IID IID_ITCallMediaEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FF36B87F-EC3A-11d0-8EE4-00C04FB6809F")
    ITCallMediaEvent : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Call( 
            /* [retval][out] */ ITCallInfo __RPC_FAR *__RPC_FAR *ppCallInfo) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Event( 
            /* [retval][out] */ CALL_MEDIA_EVENT __RPC_FAR *pCallMediaEvent) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Cause( 
            /* [retval][out] */ CALL_MEDIA_CAUSE __RPC_FAR *pCallMediaCause) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITCallMediaEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITCallMediaEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITCallMediaEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITCallMediaEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITCallMediaEvent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITCallMediaEvent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITCallMediaEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITCallMediaEvent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Call )( 
            ITCallMediaEvent __RPC_FAR * This,
            /* [retval][out] */ ITCallInfo __RPC_FAR *__RPC_FAR *ppCallInfo);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Event )( 
            ITCallMediaEvent __RPC_FAR * This,
            /* [retval][out] */ CALL_MEDIA_EVENT __RPC_FAR *pCallMediaEvent);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Cause )( 
            ITCallMediaEvent __RPC_FAR * This,
            /* [retval][out] */ CALL_MEDIA_CAUSE __RPC_FAR *pCallMediaCause);
        
        END_INTERFACE
    } ITCallMediaEventVtbl;

    interface ITCallMediaEvent
    {
        CONST_VTBL struct ITCallMediaEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITCallMediaEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITCallMediaEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITCallMediaEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITCallMediaEvent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITCallMediaEvent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITCallMediaEvent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITCallMediaEvent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITCallMediaEvent_get_Call(This,ppCallInfo)	\
    (This)->lpVtbl -> get_Call(This,ppCallInfo)

#define ITCallMediaEvent_get_Event(This,pCallMediaEvent)	\
    (This)->lpVtbl -> get_Event(This,pCallMediaEvent)

#define ITCallMediaEvent_get_Cause(This,pCallMediaCause)	\
    (This)->lpVtbl -> get_Cause(This,pCallMediaCause)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITCallMediaEvent_get_Call_Proxy( 
    ITCallMediaEvent __RPC_FAR * This,
    /* [retval][out] */ ITCallInfo __RPC_FAR *__RPC_FAR *ppCallInfo);


void __RPC_STUB ITCallMediaEvent_get_Call_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITCallMediaEvent_get_Event_Proxy( 
    ITCallMediaEvent __RPC_FAR * This,
    /* [retval][out] */ CALL_MEDIA_EVENT __RPC_FAR *pCallMediaEvent);


void __RPC_STUB ITCallMediaEvent_get_Event_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITCallMediaEvent_get_Cause_Proxy( 
    ITCallMediaEvent __RPC_FAR * This,
    /* [retval][out] */ CALL_MEDIA_CAUSE __RPC_FAR *pCallMediaCause);


void __RPC_STUB ITCallMediaEvent_get_Cause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITCallMediaEvent_INTERFACE_DEFINED__ */


#ifndef __ITCallNotification_INTERFACE_DEFINED__
#define __ITCallNotification_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITCallNotification
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][helpstring][uuid] */ 



EXTERN_C const IID IID_ITCallNotification;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62F47093-95C9-11d0-835D-00AA003CCABD")
    ITCallNotification : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CallEventNotification( 
            /* [in] */ ITAddress __RPC_FAR *pAddress,
            /* [in] */ CALL_EVENT_TYPE CallEventType,
            /* [in] */ IDispatch __RPC_FAR *pEvent) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITCallNotificationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITCallNotification __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITCallNotification __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITCallNotification __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CallEventNotification )( 
            ITCallNotification __RPC_FAR * This,
            /* [in] */ ITAddress __RPC_FAR *pAddress,
            /* [in] */ CALL_EVENT_TYPE CallEventType,
            /* [in] */ IDispatch __RPC_FAR *pEvent);
        
        END_INTERFACE
    } ITCallNotificationVtbl;

    interface ITCallNotification
    {
        CONST_VTBL struct ITCallNotificationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITCallNotification_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITCallNotification_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITCallNotification_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITCallNotification_CallEventNotification(This,pAddress,CallEventType,pEvent)	\
    (This)->lpVtbl -> CallEventNotification(This,pAddress,CallEventType,pEvent)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITCallNotification_CallEventNotification_Proxy( 
    ITCallNotification __RPC_FAR * This,
    /* [in] */ ITAddress __RPC_FAR *pAddress,
    /* [in] */ CALL_EVENT_TYPE CallEventType,
    /* [in] */ IDispatch __RPC_FAR *pEvent);


void __RPC_STUB ITCallNotification_CallEventNotification_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITCallNotification_INTERFACE_DEFINED__ */


#ifndef __ITCallTonesNotification_INTERFACE_DEFINED__
#define __ITCallTonesNotification_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITCallTonesNotification
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][helpstring][uuid] */ 



EXTERN_C const IID IID_ITCallTonesNotification;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("80B7F471-9CB2-11d0-8362-00AA003CCABD")
    ITCallTonesNotification : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DTMF( 
            /* [in] */ ITCallInfo __RPC_FAR *pCall,
            /* [in] */ unsigned char DTMF) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITCallTonesNotificationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITCallTonesNotification __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITCallTonesNotification __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITCallTonesNotification __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITCallTonesNotification __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITCallTonesNotification __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITCallTonesNotification __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITCallTonesNotification __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DTMF )( 
            ITCallTonesNotification __RPC_FAR * This,
            /* [in] */ ITCallInfo __RPC_FAR *pCall,
            /* [in] */ unsigned char DTMF);
        
        END_INTERFACE
    } ITCallTonesNotificationVtbl;

    interface ITCallTonesNotification
    {
        CONST_VTBL struct ITCallTonesNotificationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITCallTonesNotification_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITCallTonesNotification_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITCallTonesNotification_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITCallTonesNotification_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITCallTonesNotification_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITCallTonesNotification_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITCallTonesNotification_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITCallTonesNotification_DTMF(This,pCall,DTMF)	\
    (This)->lpVtbl -> DTMF(This,pCall,DTMF)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITCallTonesNotification_DTMF_Proxy( 
    ITCallTonesNotification __RPC_FAR * This,
    /* [in] */ ITCallInfo __RPC_FAR *pCall,
    /* [in] */ unsigned char DTMF);


void __RPC_STUB ITCallTonesNotification_DTMF_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITCallTonesNotification_INTERFACE_DEFINED__ */


#ifndef __ITCollection_INTERFACE_DEFINED__
#define __ITCollection_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITCollection
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [dual][helpstring][uuid][public][object] */ 



EXTERN_C const IID IID_ITCollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5EC5ACF2-9C02-11d0-8362-00AA003CCABD")
    ITCollection : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *lCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ long Index,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant) = 0;
        
        virtual /* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppNewEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITCollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITCollection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITCollection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITCollection __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITCollection __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITCollection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITCollection __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            ITCollection __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *lCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            ITCollection __RPC_FAR * This,
            /* [in] */ long Index,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant);
        
        /* [helpstring][id][restricted][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            ITCollection __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppNewEnum);
        
        END_INTERFACE
    } ITCollectionVtbl;

    interface ITCollection
    {
        CONST_VTBL struct ITCollectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITCollection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITCollection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITCollection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITCollection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITCollection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITCollection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITCollection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITCollection_get_Count(This,lCount)	\
    (This)->lpVtbl -> get_Count(This,lCount)

#define ITCollection_get_Item(This,Index,pVariant)	\
    (This)->lpVtbl -> get_Item(This,Index,pVariant)

#define ITCollection_get__NewEnum(This,ppNewEnum)	\
    (This)->lpVtbl -> get__NewEnum(This,ppNewEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ITCollection_get_Count_Proxy( 
    ITCollection __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *lCount);


void __RPC_STUB ITCollection_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITCollection_get_Item_Proxy( 
    ITCollection __RPC_FAR * This,
    /* [in] */ long Index,
    /* [retval][out] */ VARIANT __RPC_FAR *pVariant);


void __RPC_STUB ITCollection_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][restricted][propget] */ HRESULT STDMETHODCALLTYPE ITCollection_get__NewEnum_Proxy( 
    ITCollection __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppNewEnum);


void __RPC_STUB ITCollection_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITCollection_INTERFACE_DEFINED__ */


#ifndef __ITTerminalManager_INTERFACE_DEFINED__
#define __ITTerminalManager_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITTerminalManager
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][uuid][object] */ 



EXTERN_C const IID IID_ITTerminalManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7170F2DE-9BE3-11D0-A009-00AA00B605A4")
    ITTerminalManager : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConnectPinsToTerminals( 
            /* [in] */ IGraphBuilder __RPC_FAR *pGraphBuilder,
            /* [in] */ DWORD dwPinCount,
            /* [size_is][in] */ IPin __RPC_FAR *__RPC_FAR ppPins[  ],
            /* [in] */ DWORD dwTerminalCount,
            /* [size_is][in] */ ITTerminal __RPC_FAR *__RPC_FAR ppTerminal[  ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITTerminalManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITTerminalManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITTerminalManager __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITTerminalManager __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectPinsToTerminals )( 
            ITTerminalManager __RPC_FAR * This,
            /* [in] */ IGraphBuilder __RPC_FAR *pGraphBuilder,
            /* [in] */ DWORD dwPinCount,
            /* [size_is][in] */ IPin __RPC_FAR *__RPC_FAR ppPins[  ],
            /* [in] */ DWORD dwTerminalCount,
            /* [size_is][in] */ ITTerminal __RPC_FAR *__RPC_FAR ppTerminal[  ]);
        
        END_INTERFACE
    } ITTerminalManagerVtbl;

    interface ITTerminalManager
    {
        CONST_VTBL struct ITTerminalManagerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITTerminalManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITTerminalManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITTerminalManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITTerminalManager_ConnectPinsToTerminals(This,pGraphBuilder,dwPinCount,ppPins,dwTerminalCount,ppTerminal)	\
    (This)->lpVtbl -> ConnectPinsToTerminals(This,pGraphBuilder,dwPinCount,ppPins,dwTerminalCount,ppTerminal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITTerminalManager_ConnectPinsToTerminals_Proxy( 
    ITTerminalManager __RPC_FAR * This,
    /* [in] */ IGraphBuilder __RPC_FAR *pGraphBuilder,
    /* [in] */ DWORD dwPinCount,
    /* [size_is][in] */ IPin __RPC_FAR *__RPC_FAR ppPins[  ],
    /* [in] */ DWORD dwTerminalCount,
    /* [size_is][in] */ ITTerminal __RPC_FAR *__RPC_FAR ppTerminal[  ]);


void __RPC_STUB ITTerminalManager_ConnectPinsToTerminals_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITTerminalManager_INTERFACE_DEFINED__ */


#ifndef __ITChannel_INTERFACE_DEFINED__
#define __ITChannel_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITChannel
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][helpstring][uuid] */ 



EXTERN_C const IID IID_ITChannel;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2D42EEC3-A70D-11d0-AB84-00AA003CCABD")
    ITChannel : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectTerminals( 
            /* [in] */ VARIANT Terminals) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnselectTerminal( 
            /* [in] */ ITTerminal __RPC_FAR *pTerminal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetParticipant( 
            /* [in] */ ITParticipantInfo __RPC_FAR *pParticipant) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetParticipant( 
            /* [retval][out] */ ITParticipantInfo __RPC_FAR *__RPC_FAR *ppParticipant) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITChannelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITChannel __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITChannel __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITChannel __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITChannel __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITChannel __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITChannel __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITChannel __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SelectTerminals )( 
            ITChannel __RPC_FAR * This,
            /* [in] */ VARIANT Terminals);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnselectTerminal )( 
            ITChannel __RPC_FAR * This,
            /* [in] */ ITTerminal __RPC_FAR *pTerminal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetParticipant )( 
            ITChannel __RPC_FAR * This,
            /* [in] */ ITParticipantInfo __RPC_FAR *pParticipant);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParticipant )( 
            ITChannel __RPC_FAR * This,
            /* [retval][out] */ ITParticipantInfo __RPC_FAR *__RPC_FAR *ppParticipant);
        
        END_INTERFACE
    } ITChannelVtbl;

    interface ITChannel
    {
        CONST_VTBL struct ITChannelVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITChannel_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITChannel_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITChannel_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITChannel_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITChannel_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITChannel_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITChannel_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITChannel_SelectTerminals(This,Terminals)	\
    (This)->lpVtbl -> SelectTerminals(This,Terminals)

#define ITChannel_UnselectTerminal(This,pTerminal)	\
    (This)->lpVtbl -> UnselectTerminal(This,pTerminal)

#define ITChannel_SetParticipant(This,pParticipant)	\
    (This)->lpVtbl -> SetParticipant(This,pParticipant)

#define ITChannel_GetParticipant(This,ppParticipant)	\
    (This)->lpVtbl -> GetParticipant(This,ppParticipant)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITChannel_SelectTerminals_Proxy( 
    ITChannel __RPC_FAR * This,
    /* [in] */ VARIANT Terminals);


void __RPC_STUB ITChannel_SelectTerminals_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITChannel_UnselectTerminal_Proxy( 
    ITChannel __RPC_FAR * This,
    /* [in] */ ITTerminal __RPC_FAR *pTerminal);


void __RPC_STUB ITChannel_UnselectTerminal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITChannel_SetParticipant_Proxy( 
    ITChannel __RPC_FAR * This,
    /* [in] */ ITParticipantInfo __RPC_FAR *pParticipant);


void __RPC_STUB ITChannel_SetParticipant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITChannel_GetParticipant_Proxy( 
    ITChannel __RPC_FAR * This,
    /* [retval][out] */ ITParticipantInfo __RPC_FAR *__RPC_FAR *ppParticipant);


void __RPC_STUB ITChannel_GetParticipant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITChannel_INTERFACE_DEFINED__ */


#ifndef __ITMultiChannelCall_INTERFACE_DEFINED__
#define __ITMultiChannelCall_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITMultiChannelCall
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][helpstring][uuid] */ 



EXTERN_C const IID IID_ITMultiChannelCall;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2D42EEC2-A70D-11d0-AB84-00AA003CCABD")
    ITMultiChannelCall : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NumChannels( 
            /* [retval][out] */ ULONG __RPC_FAR *pulChannels) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NumChannels( 
            /* [in] */ ULONG ulChannels) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Channels( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE _EnumerateChannels( 
            /* [retval][out] */ IEnumChannel __RPC_FAR *__RPC_FAR *ppEnumChannel) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITMultiChannelCallVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITMultiChannelCall __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITMultiChannelCall __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITMultiChannelCall __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITMultiChannelCall __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITMultiChannelCall __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITMultiChannelCall __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITMultiChannelCall __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumChannels )( 
            ITMultiChannelCall __RPC_FAR * This,
            /* [retval][out] */ ULONG __RPC_FAR *pulChannels);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NumChannels )( 
            ITMultiChannelCall __RPC_FAR * This,
            /* [in] */ ULONG ulChannels);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Channels )( 
            ITMultiChannelCall __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_EnumerateChannels )( 
            ITMultiChannelCall __RPC_FAR * This,
            /* [retval][out] */ IEnumChannel __RPC_FAR *__RPC_FAR *ppEnumChannel);
        
        END_INTERFACE
    } ITMultiChannelCallVtbl;

    interface ITMultiChannelCall
    {
        CONST_VTBL struct ITMultiChannelCallVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITMultiChannelCall_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITMultiChannelCall_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITMultiChannelCall_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITMultiChannelCall_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITMultiChannelCall_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITMultiChannelCall_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITMultiChannelCall_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITMultiChannelCall_get_NumChannels(This,pulChannels)	\
    (This)->lpVtbl -> get_NumChannels(This,pulChannels)

#define ITMultiChannelCall_put_NumChannels(This,ulChannels)	\
    (This)->lpVtbl -> put_NumChannels(This,ulChannels)

#define ITMultiChannelCall_get_Channels(This,pVariant)	\
    (This)->lpVtbl -> get_Channels(This,pVariant)

#define ITMultiChannelCall__EnumerateChannels(This,ppEnumChannel)	\
    (This)->lpVtbl -> _EnumerateChannels(This,ppEnumChannel)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITMultiChannelCall_get_NumChannels_Proxy( 
    ITMultiChannelCall __RPC_FAR * This,
    /* [retval][out] */ ULONG __RPC_FAR *pulChannels);


void __RPC_STUB ITMultiChannelCall_get_NumChannels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITMultiChannelCall_put_NumChannels_Proxy( 
    ITMultiChannelCall __RPC_FAR * This,
    /* [in] */ ULONG ulChannels);


void __RPC_STUB ITMultiChannelCall_put_NumChannels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITMultiChannelCall_get_Channels_Proxy( 
    ITMultiChannelCall __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVariant);


void __RPC_STUB ITMultiChannelCall_get_Channels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITMultiChannelCall__EnumerateChannels_Proxy( 
    ITMultiChannelCall __RPC_FAR * This,
    /* [retval][out] */ IEnumChannel __RPC_FAR *__RPC_FAR *ppEnumChannel);


void __RPC_STUB ITMultiChannelCall__EnumerateChannels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITMultiChannelCall_INTERFACE_DEFINED__ */


#ifndef __ITMultiChannelNotification_INTERFACE_DEFINED__
#define __ITMultiChannelNotification_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITMultiChannelNotification
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [object][dual][helpstring][uuid] */ 



EXTERN_C const IID IID_ITMultiChannelNotification;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2D42EEC1-A70D-11d0-AB84-00AA003CCABD")
    ITMultiChannelNotification : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChannelChangeEvent( 
            /* [in] */ ITChannel __RPC_FAR *pChannel) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITMultiChannelNotificationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITMultiChannelNotification __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITMultiChannelNotification __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITMultiChannelNotification __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITMultiChannelNotification __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITMultiChannelNotification __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITMultiChannelNotification __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITMultiChannelNotification __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChannelChangeEvent )( 
            ITMultiChannelNotification __RPC_FAR * This,
            /* [in] */ ITChannel __RPC_FAR *pChannel);
        
        END_INTERFACE
    } ITMultiChannelNotificationVtbl;

    interface ITMultiChannelNotification
    {
        CONST_VTBL struct ITMultiChannelNotificationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITMultiChannelNotification_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITMultiChannelNotification_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITMultiChannelNotification_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITMultiChannelNotification_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITMultiChannelNotification_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITMultiChannelNotification_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITMultiChannelNotification_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITMultiChannelNotification_ChannelChangeEvent(This,pChannel)	\
    (This)->lpVtbl -> ChannelChangeEvent(This,pChannel)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ITMultiChannelNotification_ChannelChangeEvent_Proxy( 
    ITMultiChannelNotification __RPC_FAR * This,
    /* [in] */ ITChannel __RPC_FAR *pChannel);


void __RPC_STUB ITMultiChannelNotification_ChannelChangeEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITMultiChannelNotification_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_tapi3_0331
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


/****************************************
 * Terminal Classes
 ****************************************/

// Video Windows - {F7438990-D6EB-11d0-82A6-00AA00B5CA1B}
EXTERN_C const CLSID CLSID_VideoWindowTerm;

// Video input (camera) {AAF578EC-DC70-11d0-8ED3-00C04FB6809F}
EXTERN_C const CLSID CLSID_VideoInputTerminal;

// Handset device {AAF578EB-DC70-11d0-8ED3-00C04FB6809F}
EXTERN_C const CLSID CLSID_HandsetTerminal;

// Headset device {AAF578ED-DC70-11d0-8ED3-00C04FB6809F}
EXTERN_C const CLSID CLSID_HeadsetTerminal;

// Speakerphone device {AAF578EE-DC70-11d0-8ED3-00C04FB6809F}
EXTERN_C const CLSID CLSID_SpeakerphoneTerminal;

// Microphone (sound card) {AAF578EF-DC70-11d0-8ED3-00C04FB6809F}
EXTERN_C const CLSID CLSID_MicrophoneTerminal;

// Speakers (sound card) {AAF578F0-DC70-11d0-8ED3-00C04FB6809F}
EXTERN_C const CLSID CLSID_SpeakersTerminal;

// File dynamic terminal {AAF578F1-DC70-11d0-8ED3-00C04FB6809F}
EXTERN_C const CLSID CLSID_FileTerminal;

// {028ED8C2-DC7A-11d0-8ED3-00C04FB6809F}
EXTERN_C const CLSID TAPIMEDIATYPE_AudioOut;

// {028ED8C3-DC7A-11d0-8ED3-00C04FB6809F}
EXTERN_C const CLSID TAPIMEDIATYPE_AudioIn;

// {028ED8C4-DC7A-11d0-8ED3-00C04FB6809F}
EXTERN_C const CLSID TAPIMEDIATYPE_VideoOut;

// {028ED8C5-DC7A-11d0-8ED3-00C04FB6809F}
EXTERN_C const CLSID TAPIMEDIATYPE_VideoIn;

// {028ED8C6-DC7A-11d0-8ED3-00C04FB6809F}
EXTERN_C const CLSID TAPIMEDIATYPE_DataModem;

// {028ED8C7-DC7A-11d0-8ED3-00C04FB6809F}
EXTERN_C const CLSID TAPIMEDIATYPE_G3Fax;

#define T3_ADDRESSTYPE_CONFERENCENAME   0x00000001
#define T3_ADDRESSTYPE_EMAILNAME        0x00000002
#define T3_ADDRESSTYPE_DOMAINNAME       0x00000004
#define T3_ADDRESSTYPE_PHONENUMBER      0x00000008
#define T3_ADDRESSTYPE_IPADDRESS        0x00000010

#define ____TapiConstants_MODULE_DEFINED__


extern RPC_IF_HANDLE __MIDL_itf_tapi3_0331_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_tapi3_0331_v0_0_s_ifspec;


#ifndef __TAPI3Lib_LIBRARY_DEFINED__
#define __TAPI3Lib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: TAPI3Lib
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [helpstring][version][uuid] */ 






EXTERN_C const IID LIBID_TAPI3Lib;

EXTERN_C const CLSID CLSID_TAPI;

#ifdef __cplusplus

class DECLSPEC_UUID("21D6D48E-A88B-11D0-83DD-00AA003CCABD")
TAPI;
#endif

EXTERN_C const CLSID CLSID_Terminal;

#ifdef __cplusplus

class DECLSPEC_UUID("29393A96-A9F2-11D0-83DF-00AA003CCABD")
Terminal;
#endif

EXTERN_C const CLSID CLSID_Address;

#ifdef __cplusplus

class DECLSPEC_UUID("A3AF1E17-CE32-11d0-8EC9-00C04FB6809F")
Address;
#endif


#ifndef __TapiConstants_MODULE_DEFINED__
#define __TapiConstants_MODULE_DEFINED__


/****************************************
 * Generated header for module: TapiConstants
 * at Wed Sep 03 19:02:55 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [helpstring][dllname][uuid] */ 


const BSTR CLSID_String_VideoWindowTerm	=	L"{F7438990-D6EB-11D0-82A6-00AA00B5CA1B}";

const BSTR CLSID_String_VideoInputTerminal	=	L"{AAF578EC-DC70-11D0-8ED3-00C04FB6809F}";

const BSTR CLSID_String_HandsetTerminal	=	L"{AAF578EB-DC70-11D0-8ED3-00C04FB6809F}";

const BSTR CLSID_String_HeadsetTerminal	=	L"{AAF578ED-DC70-11D0-8ED3-00C04FB6809F}";

const BSTR CLSID_String_SpeakerphoneTerminal	=	L"{AAF578EE-DC70-11D0-8ED3-00C04FB6809F}";

const BSTR CLSID_String_MicrophoneTerminal	=	L"{AAF578EF-DC70-11D0-8ED3-00C04FB6809F}";

const BSTR CLSID_String_SpeakersTerminal	=	L"{AAF578F0-DC70-11D0-8ED3-00C04FB6809F}";

const BSTR CLSID_String_FileTerminal	=	L"{AAF578F1-DC70-11D0-8ED3-00C04FB6809F}";

const BSTR TAPIMEDIATYPE_String_AudioOut	=	L"{028ED8C2-DC7A-11D0-8ED3-00C04FB6809F}";

const BSTR TAPIMEDIATYPE_String_AudioIn	=	L"{028ED8C3-DC7A-11D0-8ED3-00C04FB6809F}";

const BSTR TAPIMEDIATYPE_String_VideoOut	=	L"{028ED8C4-DC7A-11D0-8ED3-00C04FB6809F}";

const BSTR TAPIMEDIATYPE_String_VideoIn	=	L"{028ED8C5-DC7A-11D0-8ED3-00C04FB6809F}";

const BSTR TAPIMEDIATYPE_String_DataModem	=	L"{028ED8C6-DC7A-11D0-8ED3-00C04FB6809F}";

const BSTR TAPIMEDIATYPE_String_G3Fax	=	L"{028ED8C7-DC7A-11D0-8ED3-00C04FB6809F}";

const long ADDRESSTYPE_CONFERENCENAME	=	0x1;

const long ADDRESSTYPE_EMAILNAME	=	0x2;

const long ADDRESSTYPE_DOMAINNAME	=	0x4;

const long ADDRESSTYPE_PHONENUMBER	=	0x8;

const long ADDRESSTYPE_IPADDRESS	=	0x10;

#endif /* __TapiConstants_MODULE_DEFINED__ */
#endif /* __TAPI3Lib_LIBRARY_DEFINED__ */

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
