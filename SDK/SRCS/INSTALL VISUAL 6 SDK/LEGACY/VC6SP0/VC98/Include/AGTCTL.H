/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Wed Aug 13 20:54:44 1997
 */
/* Compiler settings for AgentControl.idl:
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

#ifndef __AgentControl_h__
#define __AgentControl_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAgentCtlRequest_FWD_DEFINED__
#define __IAgentCtlRequest_FWD_DEFINED__
typedef interface IAgentCtlRequest IAgentCtlRequest;
#endif 	/* __IAgentCtlRequest_FWD_DEFINED__ */


#ifndef __IAgentCtlUserInput_FWD_DEFINED__
#define __IAgentCtlUserInput_FWD_DEFINED__
typedef interface IAgentCtlUserInput IAgentCtlUserInput;
#endif 	/* __IAgentCtlUserInput_FWD_DEFINED__ */


#ifndef __IAgentCtlBalloon_FWD_DEFINED__
#define __IAgentCtlBalloon_FWD_DEFINED__
typedef interface IAgentCtlBalloon IAgentCtlBalloon;
#endif 	/* __IAgentCtlBalloon_FWD_DEFINED__ */


#ifndef __IAgentCtlCommand_FWD_DEFINED__
#define __IAgentCtlCommand_FWD_DEFINED__
typedef interface IAgentCtlCommand IAgentCtlCommand;
#endif 	/* __IAgentCtlCommand_FWD_DEFINED__ */


#ifndef __IAgentCtlCommands_FWD_DEFINED__
#define __IAgentCtlCommands_FWD_DEFINED__
typedef interface IAgentCtlCommands IAgentCtlCommands;
#endif 	/* __IAgentCtlCommands_FWD_DEFINED__ */


#ifndef __IAgentCtlCharacter_FWD_DEFINED__
#define __IAgentCtlCharacter_FWD_DEFINED__
typedef interface IAgentCtlCharacter IAgentCtlCharacter;
#endif 	/* __IAgentCtlCharacter_FWD_DEFINED__ */


#ifndef __IAgentCtlCharacters_FWD_DEFINED__
#define __IAgentCtlCharacters_FWD_DEFINED__
typedef interface IAgentCtlCharacters IAgentCtlCharacters;
#endif 	/* __IAgentCtlCharacters_FWD_DEFINED__ */


#ifndef __IAgentCtlAudioObject_FWD_DEFINED__
#define __IAgentCtlAudioObject_FWD_DEFINED__
typedef interface IAgentCtlAudioObject IAgentCtlAudioObject;
#endif 	/* __IAgentCtlAudioObject_FWD_DEFINED__ */


#ifndef __IAgentCtlSpeechInput_FWD_DEFINED__
#define __IAgentCtlSpeechInput_FWD_DEFINED__
typedef interface IAgentCtlSpeechInput IAgentCtlSpeechInput;
#endif 	/* __IAgentCtlSpeechInput_FWD_DEFINED__ */


#ifndef __IAgentCtlPropertySheet_FWD_DEFINED__
#define __IAgentCtlPropertySheet_FWD_DEFINED__
typedef interface IAgentCtlPropertySheet IAgentCtlPropertySheet;
#endif 	/* __IAgentCtlPropertySheet_FWD_DEFINED__ */


#ifndef __IAgentCtlCommandsWindow_FWD_DEFINED__
#define __IAgentCtlCommandsWindow_FWD_DEFINED__
typedef interface IAgentCtlCommandsWindow IAgentCtlCommandsWindow;
#endif 	/* __IAgentCtlCommandsWindow_FWD_DEFINED__ */


#ifndef __IAgentCtl_FWD_DEFINED__
#define __IAgentCtl_FWD_DEFINED__
typedef interface IAgentCtl IAgentCtl;
#endif 	/* __IAgentCtl_FWD_DEFINED__ */


#ifndef __IAgentCtlCharacters_FWD_DEFINED__
#define __IAgentCtlCharacters_FWD_DEFINED__
typedef interface IAgentCtlCharacters IAgentCtlCharacters;
#endif 	/* __IAgentCtlCharacters_FWD_DEFINED__ */


#ifndef __IAgentCtlBalloon_FWD_DEFINED__
#define __IAgentCtlBalloon_FWD_DEFINED__
typedef interface IAgentCtlBalloon IAgentCtlBalloon;
#endif 	/* __IAgentCtlBalloon_FWD_DEFINED__ */


#ifndef __IAgentCtlCharacter_FWD_DEFINED__
#define __IAgentCtlCharacter_FWD_DEFINED__
typedef interface IAgentCtlCharacter IAgentCtlCharacter;
#endif 	/* __IAgentCtlCharacter_FWD_DEFINED__ */


#ifndef __IAgentCtlAudioObject_FWD_DEFINED__
#define __IAgentCtlAudioObject_FWD_DEFINED__
typedef interface IAgentCtlAudioObject IAgentCtlAudioObject;
#endif 	/* __IAgentCtlAudioObject_FWD_DEFINED__ */


#ifndef __IAgentCtlSpeechInput_FWD_DEFINED__
#define __IAgentCtlSpeechInput_FWD_DEFINED__
typedef interface IAgentCtlSpeechInput IAgentCtlSpeechInput;
#endif 	/* __IAgentCtlSpeechInput_FWD_DEFINED__ */


#ifndef __IAgentCtlPropertySheet_FWD_DEFINED__
#define __IAgentCtlPropertySheet_FWD_DEFINED__
typedef interface IAgentCtlPropertySheet IAgentCtlPropertySheet;
#endif 	/* __IAgentCtlPropertySheet_FWD_DEFINED__ */


#ifndef __IAgentCtlCommands_FWD_DEFINED__
#define __IAgentCtlCommands_FWD_DEFINED__
typedef interface IAgentCtlCommands IAgentCtlCommands;
#endif 	/* __IAgentCtlCommands_FWD_DEFINED__ */


#ifndef __IAgentCtlCommand_FWD_DEFINED__
#define __IAgentCtlCommand_FWD_DEFINED__
typedef interface IAgentCtlCommand IAgentCtlCommand;
#endif 	/* __IAgentCtlCommand_FWD_DEFINED__ */


#ifndef __IAgentCtlRequest_FWD_DEFINED__
#define __IAgentCtlRequest_FWD_DEFINED__
typedef interface IAgentCtlRequest IAgentCtlRequest;
#endif 	/* __IAgentCtlRequest_FWD_DEFINED__ */


#ifndef __IAgentCtlUserInput_FWD_DEFINED__
#define __IAgentCtlUserInput_FWD_DEFINED__
typedef interface IAgentCtlUserInput IAgentCtlUserInput;
#endif 	/* __IAgentCtlUserInput_FWD_DEFINED__ */


#ifndef __IAgentCtlCommandsWindow_FWD_DEFINED__
#define __IAgentCtlCommandsWindow_FWD_DEFINED__
typedef interface IAgentCtlCommandsWindow IAgentCtlCommandsWindow;
#endif 	/* __IAgentCtlCommandsWindow_FWD_DEFINED__ */


#ifndef ___AgentEvents_FWD_DEFINED__
#define ___AgentEvents_FWD_DEFINED__
typedef interface _AgentEvents _AgentEvents;
#endif 	/* ___AgentEvents_FWD_DEFINED__ */


#ifndef __Agent_FWD_DEFINED__
#define __Agent_FWD_DEFINED__

#ifdef __cplusplus
typedef class Agent Agent;
#else
typedef struct Agent Agent;
#endif /* __cplusplus */

#endif 	/* __Agent_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_AgentControl_0000
 * at Wed Aug 13 20:54:44 1997
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


#define	RequestSuccess	( 0 )

#define	RequestFailed	( 1 )

#define	RequestPending	( 2 )

#define	RequestInterrupted	( 3 )

#define	RequestInProgress	( 4 )



extern RPC_IF_HANDLE __MIDL_itf_AgentControl_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AgentControl_0000_v0_0_s_ifspec;

#ifndef __IAgentCtlRequest_INTERFACE_DEFINED__
#define __IAgentCtlRequest_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentCtlRequest
 * at Wed Aug 13 20:54:44 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAgentCtlRequest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("1DAB85C3-803A-11D0-AC63-00C04FD97575")
    IAgentCtlRequest : public IDispatch
    {
    public:
        virtual /* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE get_ID( 
            /* [retval][out] */ long __RPC_FAR *ID) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ long __RPC_FAR *Status) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *Description) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Number( 
            /* [retval][out] */ long __RPC_FAR *Number) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentCtlRequestVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentCtlRequest __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentCtlRequest __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentCtlRequest __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgentCtlRequest __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgentCtlRequest __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgentCtlRequest __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgentCtlRequest __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [hidden][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ID )( 
            IAgentCtlRequest __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *ID);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Status )( 
            IAgentCtlRequest __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Status);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            IAgentCtlRequest __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Description);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Number )( 
            IAgentCtlRequest __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Number);
        
        END_INTERFACE
    } IAgentCtlRequestVtbl;

    interface IAgentCtlRequest
    {
        CONST_VTBL struct IAgentCtlRequestVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentCtlRequest_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentCtlRequest_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentCtlRequest_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentCtlRequest_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgentCtlRequest_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgentCtlRequest_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgentCtlRequest_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgentCtlRequest_get_ID(This,ID)	\
    (This)->lpVtbl -> get_ID(This,ID)

#define IAgentCtlRequest_get_Status(This,Status)	\
    (This)->lpVtbl -> get_Status(This,Status)

#define IAgentCtlRequest_get_Description(This,Description)	\
    (This)->lpVtbl -> get_Description(This,Description)

#define IAgentCtlRequest_get_Number(This,Number)	\
    (This)->lpVtbl -> get_Number(This,Number)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [hidden][propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlRequest_get_ID_Proxy( 
    IAgentCtlRequest __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *ID);


void __RPC_STUB IAgentCtlRequest_get_ID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlRequest_get_Status_Proxy( 
    IAgentCtlRequest __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Status);


void __RPC_STUB IAgentCtlRequest_get_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlRequest_get_Description_Proxy( 
    IAgentCtlRequest __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Description);


void __RPC_STUB IAgentCtlRequest_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlRequest_get_Number_Proxy( 
    IAgentCtlRequest __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Number);


void __RPC_STUB IAgentCtlRequest_get_Number_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentCtlRequest_INTERFACE_DEFINED__ */


#ifndef __IAgentCtlUserInput_INTERFACE_DEFINED__
#define __IAgentCtlUserInput_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentCtlUserInput
 * at Wed Aug 13 20:54:44 1997
 * using MIDL 3.01.75
 ****************************************/
/* [object][dual][uuid] */ 



EXTERN_C const IID IID_IAgentCtlUserInput;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C4ABF875-8100-11D0-AC63-00C04FD97575")
    IAgentCtlUserInput : public IDispatch
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ short __RPC_FAR *pCount) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pName) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_CharacterID( 
            /* [retval][out] */ BSTR __RPC_FAR *pCharacterID) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Confidence( 
            /* [retval][out] */ long __RPC_FAR *pConfidence) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Voice( 
            /* [retval][out] */ BSTR __RPC_FAR *pVoice) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Alt1Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pAlt1Name) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Alt1Confidence( 
            /* [retval][out] */ long __RPC_FAR *pAlt1Confidence) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Alt1Voice( 
            /* [retval][out] */ BSTR __RPC_FAR *pAlt1Voice) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Alt2Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pAlt2Name) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Alt2Confidence( 
            /* [retval][out] */ long __RPC_FAR *pAlt2Confidence) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Alt2Voice( 
            /* [retval][out] */ BSTR __RPC_FAR *pAlt2Voice) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentCtlUserInputVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentCtlUserInput __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentCtlUserInput __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentCtlUserInput __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgentCtlUserInput __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgentCtlUserInput __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgentCtlUserInput __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgentCtlUserInput __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IAgentCtlUserInput __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pCount);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IAgentCtlUserInput __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pName);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CharacterID )( 
            IAgentCtlUserInput __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pCharacterID);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Confidence )( 
            IAgentCtlUserInput __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pConfidence);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Voice )( 
            IAgentCtlUserInput __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVoice);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Alt1Name )( 
            IAgentCtlUserInput __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pAlt1Name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Alt1Confidence )( 
            IAgentCtlUserInput __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pAlt1Confidence);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Alt1Voice )( 
            IAgentCtlUserInput __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pAlt1Voice);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Alt2Name )( 
            IAgentCtlUserInput __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pAlt2Name);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Alt2Confidence )( 
            IAgentCtlUserInput __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pAlt2Confidence);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Alt2Voice )( 
            IAgentCtlUserInput __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pAlt2Voice);
        
        END_INTERFACE
    } IAgentCtlUserInputVtbl;

    interface IAgentCtlUserInput
    {
        CONST_VTBL struct IAgentCtlUserInputVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentCtlUserInput_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentCtlUserInput_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentCtlUserInput_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentCtlUserInput_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgentCtlUserInput_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgentCtlUserInput_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgentCtlUserInput_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgentCtlUserInput_get_Count(This,pCount)	\
    (This)->lpVtbl -> get_Count(This,pCount)

#define IAgentCtlUserInput_get_Name(This,pName)	\
    (This)->lpVtbl -> get_Name(This,pName)

#define IAgentCtlUserInput_get_CharacterID(This,pCharacterID)	\
    (This)->lpVtbl -> get_CharacterID(This,pCharacterID)

#define IAgentCtlUserInput_get_Confidence(This,pConfidence)	\
    (This)->lpVtbl -> get_Confidence(This,pConfidence)

#define IAgentCtlUserInput_get_Voice(This,pVoice)	\
    (This)->lpVtbl -> get_Voice(This,pVoice)

#define IAgentCtlUserInput_get_Alt1Name(This,pAlt1Name)	\
    (This)->lpVtbl -> get_Alt1Name(This,pAlt1Name)

#define IAgentCtlUserInput_get_Alt1Confidence(This,pAlt1Confidence)	\
    (This)->lpVtbl -> get_Alt1Confidence(This,pAlt1Confidence)

#define IAgentCtlUserInput_get_Alt1Voice(This,pAlt1Voice)	\
    (This)->lpVtbl -> get_Alt1Voice(This,pAlt1Voice)

#define IAgentCtlUserInput_get_Alt2Name(This,pAlt2Name)	\
    (This)->lpVtbl -> get_Alt2Name(This,pAlt2Name)

#define IAgentCtlUserInput_get_Alt2Confidence(This,pAlt2Confidence)	\
    (This)->lpVtbl -> get_Alt2Confidence(This,pAlt2Confidence)

#define IAgentCtlUserInput_get_Alt2Voice(This,pAlt2Voice)	\
    (This)->lpVtbl -> get_Alt2Voice(This,pAlt2Voice)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IAgentCtlUserInput_get_Count_Proxy( 
    IAgentCtlUserInput __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pCount);


void __RPC_STUB IAgentCtlUserInput_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IAgentCtlUserInput_get_Name_Proxy( 
    IAgentCtlUserInput __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pName);


void __RPC_STUB IAgentCtlUserInput_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IAgentCtlUserInput_get_CharacterID_Proxy( 
    IAgentCtlUserInput __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pCharacterID);


void __RPC_STUB IAgentCtlUserInput_get_CharacterID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IAgentCtlUserInput_get_Confidence_Proxy( 
    IAgentCtlUserInput __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pConfidence);


void __RPC_STUB IAgentCtlUserInput_get_Confidence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IAgentCtlUserInput_get_Voice_Proxy( 
    IAgentCtlUserInput __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVoice);


void __RPC_STUB IAgentCtlUserInput_get_Voice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IAgentCtlUserInput_get_Alt1Name_Proxy( 
    IAgentCtlUserInput __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pAlt1Name);


void __RPC_STUB IAgentCtlUserInput_get_Alt1Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IAgentCtlUserInput_get_Alt1Confidence_Proxy( 
    IAgentCtlUserInput __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pAlt1Confidence);


void __RPC_STUB IAgentCtlUserInput_get_Alt1Confidence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IAgentCtlUserInput_get_Alt1Voice_Proxy( 
    IAgentCtlUserInput __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pAlt1Voice);


void __RPC_STUB IAgentCtlUserInput_get_Alt1Voice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IAgentCtlUserInput_get_Alt2Name_Proxy( 
    IAgentCtlUserInput __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pAlt2Name);


void __RPC_STUB IAgentCtlUserInput_get_Alt2Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IAgentCtlUserInput_get_Alt2Confidence_Proxy( 
    IAgentCtlUserInput __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pAlt2Confidence);


void __RPC_STUB IAgentCtlUserInput_get_Alt2Confidence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IAgentCtlUserInput_get_Alt2Voice_Proxy( 
    IAgentCtlUserInput __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pAlt2Voice);


void __RPC_STUB IAgentCtlUserInput_get_Alt2Voice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentCtlUserInput_INTERFACE_DEFINED__ */


#ifndef __IAgentCtlBalloon_INTERFACE_DEFINED__
#define __IAgentCtlBalloon_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentCtlBalloon
 * at Wed Aug 13 20:54:44 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAgentCtlBalloon;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("F5BE8BD3-7DE6-11D0-91FE-00C04FD701A5")
    IAgentCtlBalloon : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Enabled) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_NumberOfLines( 
            /* [retval][out] */ long __RPC_FAR *Lines) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_CharsPerLine( 
            /* [retval][out] */ long __RPC_FAR *CharsPerLine) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_FontName( 
            /* [retval][out] */ BSTR __RPC_FAR *FontName) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_FontSize( 
            /* [retval][out] */ long __RPC_FAR *FontSize) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_FontBold( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *FontBold) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_FontItalic( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *FontItalic) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_FontStrikethru( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *FontStrikethru) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_FontUnderline( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *FontUnderline) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ForeColor( 
            /* [retval][out] */ long __RPC_FAR *ForeColor) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ long __RPC_FAR *BackColor) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_BorderColor( 
            /* [retval][out] */ long __RPC_FAR *BorderColor) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ VARIANT_BOOL Visible) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Visible) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_FontName( 
            /* [in] */ BSTR FontName) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_FontSize( 
            /* [in] */ long FontSize) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_FontCharSet( 
            /* [in] */ short FontCharSet) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_FontCharSet( 
            /* [retval][out] */ short __RPC_FAR *FontCharSet) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentCtlBalloonVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentCtlBalloon __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentCtlBalloon __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Enabled )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Enabled);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumberOfLines )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Lines);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CharsPerLine )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *CharsPerLine);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FontName )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *FontName);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FontSize )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *FontSize);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FontBold )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *FontBold);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FontItalic )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *FontItalic);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FontStrikethru )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *FontStrikethru);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FontUnderline )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *FontUnderline);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ForeColor )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *ForeColor);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BackColor )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *BackColor);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BorderColor )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *BorderColor);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Visible);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Visible);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FontName )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [in] */ BSTR FontName);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FontSize )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [in] */ long FontSize);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FontCharSet )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [in] */ short FontCharSet);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FontCharSet )( 
            IAgentCtlBalloon __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *FontCharSet);
        
        END_INTERFACE
    } IAgentCtlBalloonVtbl;

    interface IAgentCtlBalloon
    {
        CONST_VTBL struct IAgentCtlBalloonVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentCtlBalloon_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentCtlBalloon_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentCtlBalloon_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentCtlBalloon_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgentCtlBalloon_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgentCtlBalloon_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgentCtlBalloon_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgentCtlBalloon_get_Enabled(This,Enabled)	\
    (This)->lpVtbl -> get_Enabled(This,Enabled)

#define IAgentCtlBalloon_get_NumberOfLines(This,Lines)	\
    (This)->lpVtbl -> get_NumberOfLines(This,Lines)

#define IAgentCtlBalloon_get_CharsPerLine(This,CharsPerLine)	\
    (This)->lpVtbl -> get_CharsPerLine(This,CharsPerLine)

#define IAgentCtlBalloon_get_FontName(This,FontName)	\
    (This)->lpVtbl -> get_FontName(This,FontName)

#define IAgentCtlBalloon_get_FontSize(This,FontSize)	\
    (This)->lpVtbl -> get_FontSize(This,FontSize)

#define IAgentCtlBalloon_get_FontBold(This,FontBold)	\
    (This)->lpVtbl -> get_FontBold(This,FontBold)

#define IAgentCtlBalloon_get_FontItalic(This,FontItalic)	\
    (This)->lpVtbl -> get_FontItalic(This,FontItalic)

#define IAgentCtlBalloon_get_FontStrikethru(This,FontStrikethru)	\
    (This)->lpVtbl -> get_FontStrikethru(This,FontStrikethru)

#define IAgentCtlBalloon_get_FontUnderline(This,FontUnderline)	\
    (This)->lpVtbl -> get_FontUnderline(This,FontUnderline)

#define IAgentCtlBalloon_get_ForeColor(This,ForeColor)	\
    (This)->lpVtbl -> get_ForeColor(This,ForeColor)

#define IAgentCtlBalloon_get_BackColor(This,BackColor)	\
    (This)->lpVtbl -> get_BackColor(This,BackColor)

#define IAgentCtlBalloon_get_BorderColor(This,BorderColor)	\
    (This)->lpVtbl -> get_BorderColor(This,BorderColor)

#define IAgentCtlBalloon_put_Visible(This,Visible)	\
    (This)->lpVtbl -> put_Visible(This,Visible)

#define IAgentCtlBalloon_get_Visible(This,Visible)	\
    (This)->lpVtbl -> get_Visible(This,Visible)

#define IAgentCtlBalloon_put_FontName(This,FontName)	\
    (This)->lpVtbl -> put_FontName(This,FontName)

#define IAgentCtlBalloon_put_FontSize(This,FontSize)	\
    (This)->lpVtbl -> put_FontSize(This,FontSize)

#define IAgentCtlBalloon_put_FontCharSet(This,FontCharSet)	\
    (This)->lpVtbl -> put_FontCharSet(This,FontCharSet)

#define IAgentCtlBalloon_get_FontCharSet(This,FontCharSet)	\
    (This)->lpVtbl -> get_FontCharSet(This,FontCharSet)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlBalloon_get_Enabled_Proxy( 
    IAgentCtlBalloon __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Enabled);


void __RPC_STUB IAgentCtlBalloon_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlBalloon_get_NumberOfLines_Proxy( 
    IAgentCtlBalloon __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Lines);


void __RPC_STUB IAgentCtlBalloon_get_NumberOfLines_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlBalloon_get_CharsPerLine_Proxy( 
    IAgentCtlBalloon __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *CharsPerLine);


void __RPC_STUB IAgentCtlBalloon_get_CharsPerLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlBalloon_get_FontName_Proxy( 
    IAgentCtlBalloon __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *FontName);


void __RPC_STUB IAgentCtlBalloon_get_FontName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlBalloon_get_FontSize_Proxy( 
    IAgentCtlBalloon __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *FontSize);


void __RPC_STUB IAgentCtlBalloon_get_FontSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlBalloon_get_FontBold_Proxy( 
    IAgentCtlBalloon __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *FontBold);


void __RPC_STUB IAgentCtlBalloon_get_FontBold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlBalloon_get_FontItalic_Proxy( 
    IAgentCtlBalloon __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *FontItalic);


void __RPC_STUB IAgentCtlBalloon_get_FontItalic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlBalloon_get_FontStrikethru_Proxy( 
    IAgentCtlBalloon __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *FontStrikethru);


void __RPC_STUB IAgentCtlBalloon_get_FontStrikethru_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlBalloon_get_FontUnderline_Proxy( 
    IAgentCtlBalloon __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *FontUnderline);


void __RPC_STUB IAgentCtlBalloon_get_FontUnderline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlBalloon_get_ForeColor_Proxy( 
    IAgentCtlBalloon __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *ForeColor);


void __RPC_STUB IAgentCtlBalloon_get_ForeColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlBalloon_get_BackColor_Proxy( 
    IAgentCtlBalloon __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *BackColor);


void __RPC_STUB IAgentCtlBalloon_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlBalloon_get_BorderColor_Proxy( 
    IAgentCtlBalloon __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *BorderColor);


void __RPC_STUB IAgentCtlBalloon_get_BorderColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlBalloon_put_Visible_Proxy( 
    IAgentCtlBalloon __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Visible);


void __RPC_STUB IAgentCtlBalloon_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlBalloon_get_Visible_Proxy( 
    IAgentCtlBalloon __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Visible);


void __RPC_STUB IAgentCtlBalloon_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlBalloon_put_FontName_Proxy( 
    IAgentCtlBalloon __RPC_FAR * This,
    /* [in] */ BSTR FontName);


void __RPC_STUB IAgentCtlBalloon_put_FontName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlBalloon_put_FontSize_Proxy( 
    IAgentCtlBalloon __RPC_FAR * This,
    /* [in] */ long FontSize);


void __RPC_STUB IAgentCtlBalloon_put_FontSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlBalloon_put_FontCharSet_Proxy( 
    IAgentCtlBalloon __RPC_FAR * This,
    /* [in] */ short FontCharSet);


void __RPC_STUB IAgentCtlBalloon_put_FontCharSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlBalloon_get_FontCharSet_Proxy( 
    IAgentCtlBalloon __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *FontCharSet);


void __RPC_STUB IAgentCtlBalloon_get_FontCharSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentCtlBalloon_INTERFACE_DEFINED__ */


#ifndef __IAgentCtlCommand_INTERFACE_DEFINED__
#define __IAgentCtlCommand_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentCtlCommand
 * at Wed Aug 13 20:54:44 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAgentCtlCommand;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("F5BE8BE3-7DE6-11D0-91FE-00C04FD701A5")
    IAgentCtlCommand : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Voice( 
            /* [retval][out] */ BSTR __RPC_FAR *Voice) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Voice( 
            /* [in] */ BSTR Voice) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Caption( 
            /* [retval][out] */ BSTR __RPC_FAR *Caption) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Caption( 
            /* [in] */ BSTR Caption) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Enabled) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Enabled( 
            /* [in] */ VARIANT_BOOL Enabled) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Visible) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ VARIANT_BOOL Visible) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Confidence( 
            /* [retval][out] */ long __RPC_FAR *Confidence) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Confidence( 
            /* [in] */ long Confidence) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ConfidenceText( 
            /* [retval][out] */ BSTR __RPC_FAR *Text) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ConfidenceText( 
            /* [in] */ BSTR Text) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentCtlCommandVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentCtlCommand __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentCtlCommand __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentCtlCommand __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgentCtlCommand __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgentCtlCommand __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgentCtlCommand __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgentCtlCommand __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Voice )( 
            IAgentCtlCommand __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Voice);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Voice )( 
            IAgentCtlCommand __RPC_FAR * This,
            /* [in] */ BSTR Voice);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Caption )( 
            IAgentCtlCommand __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Caption);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Caption )( 
            IAgentCtlCommand __RPC_FAR * This,
            /* [in] */ BSTR Caption);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Enabled )( 
            IAgentCtlCommand __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Enabled);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Enabled )( 
            IAgentCtlCommand __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Enabled);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            IAgentCtlCommand __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Visible);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            IAgentCtlCommand __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Visible);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Confidence )( 
            IAgentCtlCommand __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Confidence);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Confidence )( 
            IAgentCtlCommand __RPC_FAR * This,
            /* [in] */ long Confidence);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ConfidenceText )( 
            IAgentCtlCommand __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Text);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ConfidenceText )( 
            IAgentCtlCommand __RPC_FAR * This,
            /* [in] */ BSTR Text);
        
        END_INTERFACE
    } IAgentCtlCommandVtbl;

    interface IAgentCtlCommand
    {
        CONST_VTBL struct IAgentCtlCommandVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentCtlCommand_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentCtlCommand_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentCtlCommand_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentCtlCommand_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgentCtlCommand_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgentCtlCommand_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgentCtlCommand_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgentCtlCommand_get_Voice(This,Voice)	\
    (This)->lpVtbl -> get_Voice(This,Voice)

#define IAgentCtlCommand_put_Voice(This,Voice)	\
    (This)->lpVtbl -> put_Voice(This,Voice)

#define IAgentCtlCommand_get_Caption(This,Caption)	\
    (This)->lpVtbl -> get_Caption(This,Caption)

#define IAgentCtlCommand_put_Caption(This,Caption)	\
    (This)->lpVtbl -> put_Caption(This,Caption)

#define IAgentCtlCommand_get_Enabled(This,Enabled)	\
    (This)->lpVtbl -> get_Enabled(This,Enabled)

#define IAgentCtlCommand_put_Enabled(This,Enabled)	\
    (This)->lpVtbl -> put_Enabled(This,Enabled)

#define IAgentCtlCommand_get_Visible(This,Visible)	\
    (This)->lpVtbl -> get_Visible(This,Visible)

#define IAgentCtlCommand_put_Visible(This,Visible)	\
    (This)->lpVtbl -> put_Visible(This,Visible)

#define IAgentCtlCommand_get_Confidence(This,Confidence)	\
    (This)->lpVtbl -> get_Confidence(This,Confidence)

#define IAgentCtlCommand_put_Confidence(This,Confidence)	\
    (This)->lpVtbl -> put_Confidence(This,Confidence)

#define IAgentCtlCommand_get_ConfidenceText(This,Text)	\
    (This)->lpVtbl -> get_ConfidenceText(This,Text)

#define IAgentCtlCommand_put_ConfidenceText(This,Text)	\
    (This)->lpVtbl -> put_ConfidenceText(This,Text)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommand_get_Voice_Proxy( 
    IAgentCtlCommand __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Voice);


void __RPC_STUB IAgentCtlCommand_get_Voice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommand_put_Voice_Proxy( 
    IAgentCtlCommand __RPC_FAR * This,
    /* [in] */ BSTR Voice);


void __RPC_STUB IAgentCtlCommand_put_Voice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommand_get_Caption_Proxy( 
    IAgentCtlCommand __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Caption);


void __RPC_STUB IAgentCtlCommand_get_Caption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommand_put_Caption_Proxy( 
    IAgentCtlCommand __RPC_FAR * This,
    /* [in] */ BSTR Caption);


void __RPC_STUB IAgentCtlCommand_put_Caption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommand_get_Enabled_Proxy( 
    IAgentCtlCommand __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Enabled);


void __RPC_STUB IAgentCtlCommand_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommand_put_Enabled_Proxy( 
    IAgentCtlCommand __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Enabled);


void __RPC_STUB IAgentCtlCommand_put_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommand_get_Visible_Proxy( 
    IAgentCtlCommand __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Visible);


void __RPC_STUB IAgentCtlCommand_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommand_put_Visible_Proxy( 
    IAgentCtlCommand __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Visible);


void __RPC_STUB IAgentCtlCommand_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommand_get_Confidence_Proxy( 
    IAgentCtlCommand __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Confidence);


void __RPC_STUB IAgentCtlCommand_get_Confidence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommand_put_Confidence_Proxy( 
    IAgentCtlCommand __RPC_FAR * This,
    /* [in] */ long Confidence);


void __RPC_STUB IAgentCtlCommand_put_Confidence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommand_get_ConfidenceText_Proxy( 
    IAgentCtlCommand __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Text);


void __RPC_STUB IAgentCtlCommand_get_ConfidenceText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommand_put_ConfidenceText_Proxy( 
    IAgentCtlCommand __RPC_FAR * This,
    /* [in] */ BSTR Text);


void __RPC_STUB IAgentCtlCommand_put_ConfidenceText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentCtlCommand_INTERFACE_DEFINED__ */


#ifndef __IAgentCtlCommands_INTERFACE_DEFINED__
#define __IAgentCtlCommands_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentCtlCommands
 * at Wed Aug 13 20:54:44 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAgentCtlCommands;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("F5BE8BE1-7DE6-11D0-91FE-00C04FD701A5")
    IAgentCtlCommands : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ IAgentCtlCommand __RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Command( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ IAgentCtlCommand __RPC_FAR *__RPC_FAR *Item) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Caption( 
            /* [retval][out] */ BSTR __RPC_FAR *Caption) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Caption( 
            /* [in] */ BSTR Caption) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Voice( 
            /* [retval][out] */ BSTR __RPC_FAR *Voice) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Voice( 
            /* [in] */ BSTR Voice) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Visible) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ VARIANT_BOOL Visible) = 0;
        
        virtual /* [restricted][propget][id] */ HRESULT STDMETHODCALLTYPE get_Enum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunkEnum) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Name,
            /* [optional][in] */ VARIANT Caption,
            /* [optional][in] */ VARIANT Voice,
            /* [optional][in] */ VARIANT Enabled,
            /* [optional][in] */ VARIANT Visible,
            /* [retval][out] */ IAgentCtlCommand __RPC_FAR *__RPC_FAR *Command) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ BSTR Name,
            /* [in] */ BSTR RefName,
            /* [optional][in] */ VARIANT Before,
            /* [optional][in] */ VARIANT Caption,
            /* [optional][in] */ VARIANT Voice,
            /* [optional][in] */ VARIANT Enabled,
            /* [optional][in] */ VARIANT Visible,
            /* [retval][out] */ IAgentCtlCommand __RPC_FAR *__RPC_FAR *Command) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentCtlCommandsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentCtlCommands __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentCtlCommands __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentCtlCommands __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgentCtlCommands __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgentCtlCommands __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgentCtlCommands __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgentCtlCommands __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IAgentCtlCommands __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ IAgentCtlCommand __RPC_FAR *__RPC_FAR *Item);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Command )( 
            IAgentCtlCommands __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ IAgentCtlCommand __RPC_FAR *__RPC_FAR *Item);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IAgentCtlCommands __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Caption )( 
            IAgentCtlCommands __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Caption);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Caption )( 
            IAgentCtlCommands __RPC_FAR * This,
            /* [in] */ BSTR Caption);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Voice )( 
            IAgentCtlCommands __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Voice);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Voice )( 
            IAgentCtlCommands __RPC_FAR * This,
            /* [in] */ BSTR Voice);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            IAgentCtlCommands __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Visible);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            IAgentCtlCommands __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Visible);
        
        /* [restricted][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Enum )( 
            IAgentCtlCommands __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunkEnum);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IAgentCtlCommands __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [optional][in] */ VARIANT Caption,
            /* [optional][in] */ VARIANT Voice,
            /* [optional][in] */ VARIANT Enabled,
            /* [optional][in] */ VARIANT Visible,
            /* [retval][out] */ IAgentCtlCommand __RPC_FAR *__RPC_FAR *Command);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Insert )( 
            IAgentCtlCommands __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR RefName,
            /* [optional][in] */ VARIANT Before,
            /* [optional][in] */ VARIANT Caption,
            /* [optional][in] */ VARIANT Voice,
            /* [optional][in] */ VARIANT Enabled,
            /* [optional][in] */ VARIANT Visible,
            /* [retval][out] */ IAgentCtlCommand __RPC_FAR *__RPC_FAR *Command);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IAgentCtlCommands __RPC_FAR * This,
            /* [in] */ BSTR Name);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveAll )( 
            IAgentCtlCommands __RPC_FAR * This);
        
        END_INTERFACE
    } IAgentCtlCommandsVtbl;

    interface IAgentCtlCommands
    {
        CONST_VTBL struct IAgentCtlCommandsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentCtlCommands_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentCtlCommands_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentCtlCommands_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentCtlCommands_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgentCtlCommands_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgentCtlCommands_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgentCtlCommands_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgentCtlCommands_get_Item(This,Name,Item)	\
    (This)->lpVtbl -> get_Item(This,Name,Item)

#define IAgentCtlCommands_Command(This,Name,Item)	\
    (This)->lpVtbl -> Command(This,Name,Item)

#define IAgentCtlCommands_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IAgentCtlCommands_get_Caption(This,Caption)	\
    (This)->lpVtbl -> get_Caption(This,Caption)

#define IAgentCtlCommands_put_Caption(This,Caption)	\
    (This)->lpVtbl -> put_Caption(This,Caption)

#define IAgentCtlCommands_get_Voice(This,Voice)	\
    (This)->lpVtbl -> get_Voice(This,Voice)

#define IAgentCtlCommands_put_Voice(This,Voice)	\
    (This)->lpVtbl -> put_Voice(This,Voice)

#define IAgentCtlCommands_get_Visible(This,Visible)	\
    (This)->lpVtbl -> get_Visible(This,Visible)

#define IAgentCtlCommands_put_Visible(This,Visible)	\
    (This)->lpVtbl -> put_Visible(This,Visible)

#define IAgentCtlCommands_get_Enum(This,ppunkEnum)	\
    (This)->lpVtbl -> get_Enum(This,ppunkEnum)

#define IAgentCtlCommands_Add(This,Name,Caption,Voice,Enabled,Visible,Command)	\
    (This)->lpVtbl -> Add(This,Name,Caption,Voice,Enabled,Visible,Command)

#define IAgentCtlCommands_Insert(This,Name,RefName,Before,Caption,Voice,Enabled,Visible,Command)	\
    (This)->lpVtbl -> Insert(This,Name,RefName,Before,Caption,Voice,Enabled,Visible,Command)

#define IAgentCtlCommands_Remove(This,Name)	\
    (This)->lpVtbl -> Remove(This,Name)

#define IAgentCtlCommands_RemoveAll(This)	\
    (This)->lpVtbl -> RemoveAll(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommands_get_Item_Proxy( 
    IAgentCtlCommands __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ IAgentCtlCommand __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB IAgentCtlCommands_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommands_Command_Proxy( 
    IAgentCtlCommands __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ IAgentCtlCommand __RPC_FAR *__RPC_FAR *Item);


void __RPC_STUB IAgentCtlCommands_Command_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommands_get_Count_Proxy( 
    IAgentCtlCommands __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB IAgentCtlCommands_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommands_get_Caption_Proxy( 
    IAgentCtlCommands __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Caption);


void __RPC_STUB IAgentCtlCommands_get_Caption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommands_put_Caption_Proxy( 
    IAgentCtlCommands __RPC_FAR * This,
    /* [in] */ BSTR Caption);


void __RPC_STUB IAgentCtlCommands_put_Caption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommands_get_Voice_Proxy( 
    IAgentCtlCommands __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Voice);


void __RPC_STUB IAgentCtlCommands_get_Voice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommands_put_Voice_Proxy( 
    IAgentCtlCommands __RPC_FAR * This,
    /* [in] */ BSTR Voice);


void __RPC_STUB IAgentCtlCommands_put_Voice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommands_get_Visible_Proxy( 
    IAgentCtlCommands __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Visible);


void __RPC_STUB IAgentCtlCommands_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommands_put_Visible_Proxy( 
    IAgentCtlCommands __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Visible);


void __RPC_STUB IAgentCtlCommands_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommands_get_Enum_Proxy( 
    IAgentCtlCommands __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunkEnum);


void __RPC_STUB IAgentCtlCommands_get_Enum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommands_Add_Proxy( 
    IAgentCtlCommands __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [optional][in] */ VARIANT Caption,
    /* [optional][in] */ VARIANT Voice,
    /* [optional][in] */ VARIANT Enabled,
    /* [optional][in] */ VARIANT Visible,
    /* [retval][out] */ IAgentCtlCommand __RPC_FAR *__RPC_FAR *Command);


void __RPC_STUB IAgentCtlCommands_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommands_Insert_Proxy( 
    IAgentCtlCommands __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ BSTR RefName,
    /* [optional][in] */ VARIANT Before,
    /* [optional][in] */ VARIANT Caption,
    /* [optional][in] */ VARIANT Voice,
    /* [optional][in] */ VARIANT Enabled,
    /* [optional][in] */ VARIANT Visible,
    /* [retval][out] */ IAgentCtlCommand __RPC_FAR *__RPC_FAR *Command);


void __RPC_STUB IAgentCtlCommands_Insert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommands_Remove_Proxy( 
    IAgentCtlCommands __RPC_FAR * This,
    /* [in] */ BSTR Name);


void __RPC_STUB IAgentCtlCommands_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommands_RemoveAll_Proxy( 
    IAgentCtlCommands __RPC_FAR * This);


void __RPC_STUB IAgentCtlCommands_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentCtlCommands_INTERFACE_DEFINED__ */


#ifndef __IAgentCtlCharacter_INTERFACE_DEFINED__
#define __IAgentCtlCharacter_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentCtlCharacter
 * at Wed Aug 13 20:54:44 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAgentCtlCharacter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("F5BE8BD9-7DE6-11D0-91FE-00C04FD701A5")
    IAgentCtlCharacter : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Balloon( 
            /* [retval][out] */ IAgentCtlBalloon __RPC_FAR *__RPC_FAR *ppidBalloon) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Commands( 
            /* [retval][out] */ IAgentCtlCommands __RPC_FAR *__RPC_FAR *ppidCommands) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pName) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *pDescription) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVisible) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Left( 
            short Left) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Left( 
            /* [retval][out] */ short __RPC_FAR *pLeft) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Top( 
            short Top) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Top( 
            /* [retval][out] */ short __RPC_FAR *pTop) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Height( 
            short Height) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ short __RPC_FAR *pHeight) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Width( 
            short Width) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ short __RPC_FAR *pWidth) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Speed( 
            /* [retval][out] */ long __RPC_FAR *pSpeed) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Pitch( 
            /* [retval][out] */ long __RPC_FAR *pPitch) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_IdleOn( 
            VARIANT_BOOL On) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_IdleOn( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOn) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Activate( 
            /* [optional][in] */ VARIANT State,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSuccess) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Play( 
            /* [in] */ BSTR Animation,
            /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Get( 
            /* [in] */ BSTR Type,
            /* [in] */ BSTR Name,
            /* [optional][in] */ VARIANT Queue,
            /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Stop( 
            /* [optional][in] */ VARIANT Request) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Wait( 
            /* [in] */ IDispatch __RPC_FAR *WaitForRequest,
            /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Interrupt( 
            /* [in] */ IDispatch __RPC_FAR *InterruptRequest,
            /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Speak( 
            /* [optional][in] */ VARIANT Text,
            /* [optional][in] */ VARIANT Url,
            /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GestureAt( 
            /* [in] */ short x,
            /* [in] */ short y,
            /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE MoveTo( 
            /* [in] */ short x,
            /* [in] */ short y,
            /* [optional][in] */ VARIANT Speed,
            /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Hide( 
            /* [optional][in] */ VARIANT Fast,
            /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Show( 
            /* [optional][in] */ VARIANT Fast,
            /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE StopAll( 
            /* [optional][in] */ VARIANT Types) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_MoveCause( 
            /* [retval][out] */ short __RPC_FAR *MoveCause) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_VisibilityCause( 
            /* [retval][out] */ short __RPC_FAR *VisibilityCause) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_HasOtherClients( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *HasOtherClients) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_SoundEffectsOn( 
            VARIANT_BOOL On) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_SoundEffectsOn( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOn) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR Name) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR Description) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ExtraData( 
            /* [retval][out] */ BSTR __RPC_FAR *pExtraData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentCtlCharacterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentCtlCharacter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentCtlCharacter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Balloon )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [retval][out] */ IAgentCtlBalloon __RPC_FAR *__RPC_FAR *ppidBalloon);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Commands )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [retval][out] */ IAgentCtlCommands __RPC_FAR *__RPC_FAR *ppidCommands);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pName);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pDescription);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVisible);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Left )( 
            IAgentCtlCharacter __RPC_FAR * This,
            short Left);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Left )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pLeft);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Top )( 
            IAgentCtlCharacter __RPC_FAR * This,
            short Top);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Top )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pTop);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Height )( 
            IAgentCtlCharacter __RPC_FAR * This,
            short Height);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Height )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pHeight);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Width )( 
            IAgentCtlCharacter __RPC_FAR * This,
            short Width);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pWidth);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Speed )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pSpeed);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Pitch )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pPitch);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IdleOn )( 
            IAgentCtlCharacter __RPC_FAR * This,
            VARIANT_BOOL On);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IdleOn )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOn);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Activate )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [optional][in] */ VARIANT State,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSuccess);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Play )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [in] */ BSTR Animation,
            /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [in] */ BSTR Type,
            /* [in] */ BSTR Name,
            /* [optional][in] */ VARIANT Queue,
            /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [optional][in] */ VARIANT Request);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Wait )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *WaitForRequest,
            /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Interrupt )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *InterruptRequest,
            /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Speak )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [optional][in] */ VARIANT Text,
            /* [optional][in] */ VARIANT Url,
            /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GestureAt )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [in] */ short x,
            /* [in] */ short y,
            /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveTo )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [in] */ short x,
            /* [in] */ short y,
            /* [optional][in] */ VARIANT Speed,
            /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Hide )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [optional][in] */ VARIANT Fast,
            /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Show )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [optional][in] */ VARIANT Fast,
            /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopAll )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [optional][in] */ VARIANT Types);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MoveCause )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *MoveCause);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_VisibilityCause )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *VisibilityCause);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HasOtherClients )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *HasOtherClients);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SoundEffectsOn )( 
            IAgentCtlCharacter __RPC_FAR * This,
            VARIANT_BOOL On);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SoundEffectsOn )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOn);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [in] */ BSTR Name);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Description )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [in] */ BSTR Description);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ExtraData )( 
            IAgentCtlCharacter __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pExtraData);
        
        END_INTERFACE
    } IAgentCtlCharacterVtbl;

    interface IAgentCtlCharacter
    {
        CONST_VTBL struct IAgentCtlCharacterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentCtlCharacter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentCtlCharacter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentCtlCharacter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentCtlCharacter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgentCtlCharacter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgentCtlCharacter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgentCtlCharacter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgentCtlCharacter_get_Balloon(This,ppidBalloon)	\
    (This)->lpVtbl -> get_Balloon(This,ppidBalloon)

#define IAgentCtlCharacter_get_Commands(This,ppidCommands)	\
    (This)->lpVtbl -> get_Commands(This,ppidCommands)

#define IAgentCtlCharacter_get_Name(This,pName)	\
    (This)->lpVtbl -> get_Name(This,pName)

#define IAgentCtlCharacter_get_Description(This,pDescription)	\
    (This)->lpVtbl -> get_Description(This,pDescription)

#define IAgentCtlCharacter_get_Visible(This,pVisible)	\
    (This)->lpVtbl -> get_Visible(This,pVisible)

#define IAgentCtlCharacter_put_Left(This,Left)	\
    (This)->lpVtbl -> put_Left(This,Left)

#define IAgentCtlCharacter_get_Left(This,pLeft)	\
    (This)->lpVtbl -> get_Left(This,pLeft)

#define IAgentCtlCharacter_put_Top(This,Top)	\
    (This)->lpVtbl -> put_Top(This,Top)

#define IAgentCtlCharacter_get_Top(This,pTop)	\
    (This)->lpVtbl -> get_Top(This,pTop)

#define IAgentCtlCharacter_put_Height(This,Height)	\
    (This)->lpVtbl -> put_Height(This,Height)

#define IAgentCtlCharacter_get_Height(This,pHeight)	\
    (This)->lpVtbl -> get_Height(This,pHeight)

#define IAgentCtlCharacter_put_Width(This,Width)	\
    (This)->lpVtbl -> put_Width(This,Width)

#define IAgentCtlCharacter_get_Width(This,pWidth)	\
    (This)->lpVtbl -> get_Width(This,pWidth)

#define IAgentCtlCharacter_get_Speed(This,pSpeed)	\
    (This)->lpVtbl -> get_Speed(This,pSpeed)

#define IAgentCtlCharacter_get_Pitch(This,pPitch)	\
    (This)->lpVtbl -> get_Pitch(This,pPitch)

#define IAgentCtlCharacter_put_IdleOn(This,On)	\
    (This)->lpVtbl -> put_IdleOn(This,On)

#define IAgentCtlCharacter_get_IdleOn(This,pOn)	\
    (This)->lpVtbl -> get_IdleOn(This,pOn)

#define IAgentCtlCharacter_Activate(This,State,pSuccess)	\
    (This)->lpVtbl -> Activate(This,State,pSuccess)

#define IAgentCtlCharacter_Play(This,Animation,Request)	\
    (This)->lpVtbl -> Play(This,Animation,Request)

#define IAgentCtlCharacter_Get(This,Type,Name,Queue,Request)	\
    (This)->lpVtbl -> Get(This,Type,Name,Queue,Request)

#define IAgentCtlCharacter_Stop(This,Request)	\
    (This)->lpVtbl -> Stop(This,Request)

#define IAgentCtlCharacter_Wait(This,WaitForRequest,Request)	\
    (This)->lpVtbl -> Wait(This,WaitForRequest,Request)

#define IAgentCtlCharacter_Interrupt(This,InterruptRequest,Request)	\
    (This)->lpVtbl -> Interrupt(This,InterruptRequest,Request)

#define IAgentCtlCharacter_Speak(This,Text,Url,Request)	\
    (This)->lpVtbl -> Speak(This,Text,Url,Request)

#define IAgentCtlCharacter_GestureAt(This,x,y,Request)	\
    (This)->lpVtbl -> GestureAt(This,x,y,Request)

#define IAgentCtlCharacter_MoveTo(This,x,y,Speed,Request)	\
    (This)->lpVtbl -> MoveTo(This,x,y,Speed,Request)

#define IAgentCtlCharacter_Hide(This,Fast,Request)	\
    (This)->lpVtbl -> Hide(This,Fast,Request)

#define IAgentCtlCharacter_Show(This,Fast,Request)	\
    (This)->lpVtbl -> Show(This,Fast,Request)

#define IAgentCtlCharacter_StopAll(This,Types)	\
    (This)->lpVtbl -> StopAll(This,Types)

#define IAgentCtlCharacter_get_MoveCause(This,MoveCause)	\
    (This)->lpVtbl -> get_MoveCause(This,MoveCause)

#define IAgentCtlCharacter_get_VisibilityCause(This,VisibilityCause)	\
    (This)->lpVtbl -> get_VisibilityCause(This,VisibilityCause)

#define IAgentCtlCharacter_get_HasOtherClients(This,HasOtherClients)	\
    (This)->lpVtbl -> get_HasOtherClients(This,HasOtherClients)

#define IAgentCtlCharacter_put_SoundEffectsOn(This,On)	\
    (This)->lpVtbl -> put_SoundEffectsOn(This,On)

#define IAgentCtlCharacter_get_SoundEffectsOn(This,pOn)	\
    (This)->lpVtbl -> get_SoundEffectsOn(This,pOn)

#define IAgentCtlCharacter_put_Name(This,Name)	\
    (This)->lpVtbl -> put_Name(This,Name)

#define IAgentCtlCharacter_put_Description(This,Description)	\
    (This)->lpVtbl -> put_Description(This,Description)

#define IAgentCtlCharacter_get_ExtraData(This,pExtraData)	\
    (This)->lpVtbl -> get_ExtraData(This,pExtraData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_get_Balloon_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [retval][out] */ IAgentCtlBalloon __RPC_FAR *__RPC_FAR *ppidBalloon);


void __RPC_STUB IAgentCtlCharacter_get_Balloon_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_get_Commands_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [retval][out] */ IAgentCtlCommands __RPC_FAR *__RPC_FAR *ppidCommands);


void __RPC_STUB IAgentCtlCharacter_get_Commands_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_get_Name_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pName);


void __RPC_STUB IAgentCtlCharacter_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_get_Description_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pDescription);


void __RPC_STUB IAgentCtlCharacter_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_get_Visible_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVisible);


void __RPC_STUB IAgentCtlCharacter_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_put_Left_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    short Left);


void __RPC_STUB IAgentCtlCharacter_put_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_get_Left_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pLeft);


void __RPC_STUB IAgentCtlCharacter_get_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_put_Top_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    short Top);


void __RPC_STUB IAgentCtlCharacter_put_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_get_Top_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pTop);


void __RPC_STUB IAgentCtlCharacter_get_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_put_Height_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    short Height);


void __RPC_STUB IAgentCtlCharacter_put_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_get_Height_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pHeight);


void __RPC_STUB IAgentCtlCharacter_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_put_Width_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    short Width);


void __RPC_STUB IAgentCtlCharacter_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_get_Width_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pWidth);


void __RPC_STUB IAgentCtlCharacter_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_get_Speed_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pSpeed);


void __RPC_STUB IAgentCtlCharacter_get_Speed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_get_Pitch_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pPitch);


void __RPC_STUB IAgentCtlCharacter_get_Pitch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_put_IdleOn_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    VARIANT_BOOL On);


void __RPC_STUB IAgentCtlCharacter_put_IdleOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_get_IdleOn_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOn);


void __RPC_STUB IAgentCtlCharacter_get_IdleOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_Activate_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [optional][in] */ VARIANT State,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pSuccess);


void __RPC_STUB IAgentCtlCharacter_Activate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_Play_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [in] */ BSTR Animation,
    /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request);


void __RPC_STUB IAgentCtlCharacter_Play_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_Get_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [in] */ BSTR Type,
    /* [in] */ BSTR Name,
    /* [optional][in] */ VARIANT Queue,
    /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request);


void __RPC_STUB IAgentCtlCharacter_Get_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_Stop_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [optional][in] */ VARIANT Request);


void __RPC_STUB IAgentCtlCharacter_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_Wait_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *WaitForRequest,
    /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request);


void __RPC_STUB IAgentCtlCharacter_Wait_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_Interrupt_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *InterruptRequest,
    /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request);


void __RPC_STUB IAgentCtlCharacter_Interrupt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_Speak_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [optional][in] */ VARIANT Text,
    /* [optional][in] */ VARIANT Url,
    /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request);


void __RPC_STUB IAgentCtlCharacter_Speak_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_GestureAt_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [in] */ short x,
    /* [in] */ short y,
    /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request);


void __RPC_STUB IAgentCtlCharacter_GestureAt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_MoveTo_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [in] */ short x,
    /* [in] */ short y,
    /* [optional][in] */ VARIANT Speed,
    /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request);


void __RPC_STUB IAgentCtlCharacter_MoveTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_Hide_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [optional][in] */ VARIANT Fast,
    /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request);


void __RPC_STUB IAgentCtlCharacter_Hide_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_Show_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [optional][in] */ VARIANT Fast,
    /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *Request);


void __RPC_STUB IAgentCtlCharacter_Show_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_StopAll_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [optional][in] */ VARIANT Types);


void __RPC_STUB IAgentCtlCharacter_StopAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_get_MoveCause_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *MoveCause);


void __RPC_STUB IAgentCtlCharacter_get_MoveCause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_get_VisibilityCause_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *VisibilityCause);


void __RPC_STUB IAgentCtlCharacter_get_VisibilityCause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_get_HasOtherClients_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *HasOtherClients);


void __RPC_STUB IAgentCtlCharacter_get_HasOtherClients_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_put_SoundEffectsOn_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    VARIANT_BOOL On);


void __RPC_STUB IAgentCtlCharacter_put_SoundEffectsOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_get_SoundEffectsOn_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pOn);


void __RPC_STUB IAgentCtlCharacter_get_SoundEffectsOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_put_Name_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [in] */ BSTR Name);


void __RPC_STUB IAgentCtlCharacter_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_put_Description_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [in] */ BSTR Description);


void __RPC_STUB IAgentCtlCharacter_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacter_get_ExtraData_Proxy( 
    IAgentCtlCharacter __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pExtraData);


void __RPC_STUB IAgentCtlCharacter_get_ExtraData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentCtlCharacter_INTERFACE_DEFINED__ */


#ifndef __IAgentCtlCharacters_INTERFACE_DEFINED__
#define __IAgentCtlCharacters_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentCtlCharacters
 * at Wed Aug 13 20:54:44 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAgentCtlCharacters;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("F5BE8BE8-7DE6-11D0-91FE-00C04FD701A5")
    IAgentCtlCharacters : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ BSTR CharacterID,
            /* [retval][out] */ IAgentCtlCharacter __RPC_FAR *__RPC_FAR *ppidItem) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Character( 
            /* [in] */ BSTR CharacterID,
            /* [retval][out] */ IAgentCtlCharacter __RPC_FAR *__RPC_FAR *ppidItem) = 0;
        
        virtual /* [restricted][propget][id] */ HRESULT STDMETHODCALLTYPE get_Enum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunkEnum) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Unload( 
            /* [in] */ BSTR CharacterID) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ BSTR CharacterID,
            /* [in] */ VARIANT LoadKey,
            /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *pidRequest) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentCtlCharactersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentCtlCharacters __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentCtlCharacters __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentCtlCharacters __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgentCtlCharacters __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgentCtlCharacters __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgentCtlCharacters __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgentCtlCharacters __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IAgentCtlCharacters __RPC_FAR * This,
            /* [in] */ BSTR CharacterID,
            /* [retval][out] */ IAgentCtlCharacter __RPC_FAR *__RPC_FAR *ppidItem);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Character )( 
            IAgentCtlCharacters __RPC_FAR * This,
            /* [in] */ BSTR CharacterID,
            /* [retval][out] */ IAgentCtlCharacter __RPC_FAR *__RPC_FAR *ppidItem);
        
        /* [restricted][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Enum )( 
            IAgentCtlCharacters __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunkEnum);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Unload )( 
            IAgentCtlCharacters __RPC_FAR * This,
            /* [in] */ BSTR CharacterID);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Load )( 
            IAgentCtlCharacters __RPC_FAR * This,
            /* [in] */ BSTR CharacterID,
            /* [in] */ VARIANT LoadKey,
            /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *pidRequest);
        
        END_INTERFACE
    } IAgentCtlCharactersVtbl;

    interface IAgentCtlCharacters
    {
        CONST_VTBL struct IAgentCtlCharactersVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentCtlCharacters_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentCtlCharacters_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentCtlCharacters_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentCtlCharacters_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgentCtlCharacters_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgentCtlCharacters_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgentCtlCharacters_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgentCtlCharacters_get_Item(This,CharacterID,ppidItem)	\
    (This)->lpVtbl -> get_Item(This,CharacterID,ppidItem)

#define IAgentCtlCharacters_Character(This,CharacterID,ppidItem)	\
    (This)->lpVtbl -> Character(This,CharacterID,ppidItem)

#define IAgentCtlCharacters_get_Enum(This,ppunkEnum)	\
    (This)->lpVtbl -> get_Enum(This,ppunkEnum)

#define IAgentCtlCharacters_Unload(This,CharacterID)	\
    (This)->lpVtbl -> Unload(This,CharacterID)

#define IAgentCtlCharacters_Load(This,CharacterID,LoadKey,pidRequest)	\
    (This)->lpVtbl -> Load(This,CharacterID,LoadKey,pidRequest)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacters_get_Item_Proxy( 
    IAgentCtlCharacters __RPC_FAR * This,
    /* [in] */ BSTR CharacterID,
    /* [retval][out] */ IAgentCtlCharacter __RPC_FAR *__RPC_FAR *ppidItem);


void __RPC_STUB IAgentCtlCharacters_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacters_Character_Proxy( 
    IAgentCtlCharacters __RPC_FAR * This,
    /* [in] */ BSTR CharacterID,
    /* [retval][out] */ IAgentCtlCharacter __RPC_FAR *__RPC_FAR *ppidItem);


void __RPC_STUB IAgentCtlCharacters_Character_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacters_get_Enum_Proxy( 
    IAgentCtlCharacters __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunkEnum);


void __RPC_STUB IAgentCtlCharacters_get_Enum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacters_Unload_Proxy( 
    IAgentCtlCharacters __RPC_FAR * This,
    /* [in] */ BSTR CharacterID);


void __RPC_STUB IAgentCtlCharacters_Unload_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCharacters_Load_Proxy( 
    IAgentCtlCharacters __RPC_FAR * This,
    /* [in] */ BSTR CharacterID,
    /* [in] */ VARIANT LoadKey,
    /* [retval][out] */ IAgentCtlRequest __RPC_FAR *__RPC_FAR *pidRequest);


void __RPC_STUB IAgentCtlCharacters_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentCtlCharacters_INTERFACE_DEFINED__ */


#ifndef __IAgentCtlAudioObject_INTERFACE_DEFINED__
#define __IAgentCtlAudioObject_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentCtlAudioObject
 * at Wed Aug 13 20:54:44 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAgentCtlAudioObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("F5BE8BDB-7DE6-11D0-91FE-00C04FD701A5")
    IAgentCtlAudioObject : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *AudioEnabled) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_SoundEffects( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *SoundEffects) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentCtlAudioObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentCtlAudioObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentCtlAudioObject __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentCtlAudioObject __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgentCtlAudioObject __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgentCtlAudioObject __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgentCtlAudioObject __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgentCtlAudioObject __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Enabled )( 
            IAgentCtlAudioObject __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *AudioEnabled);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SoundEffects )( 
            IAgentCtlAudioObject __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *SoundEffects);
        
        END_INTERFACE
    } IAgentCtlAudioObjectVtbl;

    interface IAgentCtlAudioObject
    {
        CONST_VTBL struct IAgentCtlAudioObjectVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentCtlAudioObject_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentCtlAudioObject_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentCtlAudioObject_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentCtlAudioObject_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgentCtlAudioObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgentCtlAudioObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgentCtlAudioObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgentCtlAudioObject_get_Enabled(This,AudioEnabled)	\
    (This)->lpVtbl -> get_Enabled(This,AudioEnabled)

#define IAgentCtlAudioObject_get_SoundEffects(This,SoundEffects)	\
    (This)->lpVtbl -> get_SoundEffects(This,SoundEffects)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlAudioObject_get_Enabled_Proxy( 
    IAgentCtlAudioObject __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *AudioEnabled);


void __RPC_STUB IAgentCtlAudioObject_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlAudioObject_get_SoundEffects_Proxy( 
    IAgentCtlAudioObject __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *SoundEffects);


void __RPC_STUB IAgentCtlAudioObject_get_SoundEffects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentCtlAudioObject_INTERFACE_DEFINED__ */


#ifndef __IAgentCtlSpeechInput_INTERFACE_DEFINED__
#define __IAgentCtlSpeechInput_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentCtlSpeechInput
 * at Wed Aug 13 20:54:44 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAgentCtlSpeechInput;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("F5BE8BDD-7DE6-11D0-91FE-00C04FD701A5")
    IAgentCtlSpeechInput : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Enabled( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *VoiceEnabled) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Language( 
            /* [retval][out] */ BSTR __RPC_FAR *Language) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_HotKey( 
            /* [retval][out] */ BSTR __RPC_FAR *HotKey) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Installed( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *VoiceInstalled) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Engine( 
            /* [retval][out] */ BSTR __RPC_FAR *Engine) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Engine( 
            /* [in] */ BSTR Engine) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ListeningTip( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *ListeningTip) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentCtlSpeechInputVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentCtlSpeechInput __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentCtlSpeechInput __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentCtlSpeechInput __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgentCtlSpeechInput __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgentCtlSpeechInput __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgentCtlSpeechInput __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgentCtlSpeechInput __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Enabled )( 
            IAgentCtlSpeechInput __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *VoiceEnabled);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Language )( 
            IAgentCtlSpeechInput __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Language);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HotKey )( 
            IAgentCtlSpeechInput __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *HotKey);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Installed )( 
            IAgentCtlSpeechInput __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *VoiceInstalled);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Engine )( 
            IAgentCtlSpeechInput __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Engine);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Engine )( 
            IAgentCtlSpeechInput __RPC_FAR * This,
            /* [in] */ BSTR Engine);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ListeningTip )( 
            IAgentCtlSpeechInput __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *ListeningTip);
        
        END_INTERFACE
    } IAgentCtlSpeechInputVtbl;

    interface IAgentCtlSpeechInput
    {
        CONST_VTBL struct IAgentCtlSpeechInputVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentCtlSpeechInput_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentCtlSpeechInput_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentCtlSpeechInput_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentCtlSpeechInput_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgentCtlSpeechInput_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgentCtlSpeechInput_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgentCtlSpeechInput_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgentCtlSpeechInput_get_Enabled(This,VoiceEnabled)	\
    (This)->lpVtbl -> get_Enabled(This,VoiceEnabled)

#define IAgentCtlSpeechInput_get_Language(This,Language)	\
    (This)->lpVtbl -> get_Language(This,Language)

#define IAgentCtlSpeechInput_get_HotKey(This,HotKey)	\
    (This)->lpVtbl -> get_HotKey(This,HotKey)

#define IAgentCtlSpeechInput_get_Installed(This,VoiceInstalled)	\
    (This)->lpVtbl -> get_Installed(This,VoiceInstalled)

#define IAgentCtlSpeechInput_get_Engine(This,Engine)	\
    (This)->lpVtbl -> get_Engine(This,Engine)

#define IAgentCtlSpeechInput_put_Engine(This,Engine)	\
    (This)->lpVtbl -> put_Engine(This,Engine)

#define IAgentCtlSpeechInput_get_ListeningTip(This,ListeningTip)	\
    (This)->lpVtbl -> get_ListeningTip(This,ListeningTip)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlSpeechInput_get_Enabled_Proxy( 
    IAgentCtlSpeechInput __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *VoiceEnabled);


void __RPC_STUB IAgentCtlSpeechInput_get_Enabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlSpeechInput_get_Language_Proxy( 
    IAgentCtlSpeechInput __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Language);


void __RPC_STUB IAgentCtlSpeechInput_get_Language_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlSpeechInput_get_HotKey_Proxy( 
    IAgentCtlSpeechInput __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *HotKey);


void __RPC_STUB IAgentCtlSpeechInput_get_HotKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlSpeechInput_get_Installed_Proxy( 
    IAgentCtlSpeechInput __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *VoiceInstalled);


void __RPC_STUB IAgentCtlSpeechInput_get_Installed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlSpeechInput_get_Engine_Proxy( 
    IAgentCtlSpeechInput __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Engine);


void __RPC_STUB IAgentCtlSpeechInput_get_Engine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlSpeechInput_put_Engine_Proxy( 
    IAgentCtlSpeechInput __RPC_FAR * This,
    /* [in] */ BSTR Engine);


void __RPC_STUB IAgentCtlSpeechInput_put_Engine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlSpeechInput_get_ListeningTip_Proxy( 
    IAgentCtlSpeechInput __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *ListeningTip);


void __RPC_STUB IAgentCtlSpeechInput_get_ListeningTip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentCtlSpeechInput_INTERFACE_DEFINED__ */


#ifndef __IAgentCtlPropertySheet_INTERFACE_DEFINED__
#define __IAgentCtlPropertySheet_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentCtlPropertySheet
 * at Wed Aug 13 20:54:44 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAgentCtlPropertySheet;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("F5BE8BDF-7DE6-11D0-91FE-00C04FD701A5")
    IAgentCtlPropertySheet : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Left( 
            /* [retval][out] */ short __RPC_FAR *Left) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Top( 
            /* [retval][out] */ short __RPC_FAR *Top) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ short __RPC_FAR *Height) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ short __RPC_FAR *Width) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ VARIANT_BOOL Visible) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Visible) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Page( 
            /* [in] */ BSTR Page) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Page( 
            /* [retval][out] */ BSTR __RPC_FAR *Page) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentCtlPropertySheetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentCtlPropertySheet __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentCtlPropertySheet __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentCtlPropertySheet __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgentCtlPropertySheet __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgentCtlPropertySheet __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgentCtlPropertySheet __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgentCtlPropertySheet __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Left )( 
            IAgentCtlPropertySheet __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *Left);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Top )( 
            IAgentCtlPropertySheet __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *Top);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Height )( 
            IAgentCtlPropertySheet __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *Height);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            IAgentCtlPropertySheet __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *Width);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            IAgentCtlPropertySheet __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Visible);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            IAgentCtlPropertySheet __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Visible);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Page )( 
            IAgentCtlPropertySheet __RPC_FAR * This,
            /* [in] */ BSTR Page);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Page )( 
            IAgentCtlPropertySheet __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Page);
        
        END_INTERFACE
    } IAgentCtlPropertySheetVtbl;

    interface IAgentCtlPropertySheet
    {
        CONST_VTBL struct IAgentCtlPropertySheetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentCtlPropertySheet_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentCtlPropertySheet_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentCtlPropertySheet_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentCtlPropertySheet_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgentCtlPropertySheet_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgentCtlPropertySheet_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgentCtlPropertySheet_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgentCtlPropertySheet_get_Left(This,Left)	\
    (This)->lpVtbl -> get_Left(This,Left)

#define IAgentCtlPropertySheet_get_Top(This,Top)	\
    (This)->lpVtbl -> get_Top(This,Top)

#define IAgentCtlPropertySheet_get_Height(This,Height)	\
    (This)->lpVtbl -> get_Height(This,Height)

#define IAgentCtlPropertySheet_get_Width(This,Width)	\
    (This)->lpVtbl -> get_Width(This,Width)

#define IAgentCtlPropertySheet_put_Visible(This,Visible)	\
    (This)->lpVtbl -> put_Visible(This,Visible)

#define IAgentCtlPropertySheet_get_Visible(This,Visible)	\
    (This)->lpVtbl -> get_Visible(This,Visible)

#define IAgentCtlPropertySheet_put_Page(This,Page)	\
    (This)->lpVtbl -> put_Page(This,Page)

#define IAgentCtlPropertySheet_get_Page(This,Page)	\
    (This)->lpVtbl -> get_Page(This,Page)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlPropertySheet_get_Left_Proxy( 
    IAgentCtlPropertySheet __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *Left);


void __RPC_STUB IAgentCtlPropertySheet_get_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlPropertySheet_get_Top_Proxy( 
    IAgentCtlPropertySheet __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *Top);


void __RPC_STUB IAgentCtlPropertySheet_get_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlPropertySheet_get_Height_Proxy( 
    IAgentCtlPropertySheet __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *Height);


void __RPC_STUB IAgentCtlPropertySheet_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlPropertySheet_get_Width_Proxy( 
    IAgentCtlPropertySheet __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *Width);


void __RPC_STUB IAgentCtlPropertySheet_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlPropertySheet_put_Visible_Proxy( 
    IAgentCtlPropertySheet __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Visible);


void __RPC_STUB IAgentCtlPropertySheet_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlPropertySheet_get_Visible_Proxy( 
    IAgentCtlPropertySheet __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Visible);


void __RPC_STUB IAgentCtlPropertySheet_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlPropertySheet_put_Page_Proxy( 
    IAgentCtlPropertySheet __RPC_FAR * This,
    /* [in] */ BSTR Page);


void __RPC_STUB IAgentCtlPropertySheet_put_Page_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlPropertySheet_get_Page_Proxy( 
    IAgentCtlPropertySheet __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Page);


void __RPC_STUB IAgentCtlPropertySheet_get_Page_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentCtlPropertySheet_INTERFACE_DEFINED__ */


#ifndef __IAgentCtlCommandsWindow_INTERFACE_DEFINED__
#define __IAgentCtlCommandsWindow_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentCtlCommandsWindow
 * at Wed Aug 13 20:54:44 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAgentCtlCommandsWindow;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("6D0ECB27-9968-11D0-AC6E-00C04FD97575")
    IAgentCtlCommandsWindow : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Visible) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ VARIANT_BOOL Visible) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Left( 
            /* [retval][out] */ short __RPC_FAR *Left) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Top( 
            /* [retval][out] */ short __RPC_FAR *Top) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ short __RPC_FAR *Height) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ short __RPC_FAR *Width) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentCtlCommandsWindowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentCtlCommandsWindow __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentCtlCommandsWindow __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentCtlCommandsWindow __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgentCtlCommandsWindow __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgentCtlCommandsWindow __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgentCtlCommandsWindow __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgentCtlCommandsWindow __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            IAgentCtlCommandsWindow __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Visible);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            IAgentCtlCommandsWindow __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Visible);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Left )( 
            IAgentCtlCommandsWindow __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *Left);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Top )( 
            IAgentCtlCommandsWindow __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *Top);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Height )( 
            IAgentCtlCommandsWindow __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *Height);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            IAgentCtlCommandsWindow __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *Width);
        
        END_INTERFACE
    } IAgentCtlCommandsWindowVtbl;

    interface IAgentCtlCommandsWindow
    {
        CONST_VTBL struct IAgentCtlCommandsWindowVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentCtlCommandsWindow_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentCtlCommandsWindow_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentCtlCommandsWindow_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentCtlCommandsWindow_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgentCtlCommandsWindow_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgentCtlCommandsWindow_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgentCtlCommandsWindow_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgentCtlCommandsWindow_get_Visible(This,Visible)	\
    (This)->lpVtbl -> get_Visible(This,Visible)

#define IAgentCtlCommandsWindow_put_Visible(This,Visible)	\
    (This)->lpVtbl -> put_Visible(This,Visible)

#define IAgentCtlCommandsWindow_get_Left(This,Left)	\
    (This)->lpVtbl -> get_Left(This,Left)

#define IAgentCtlCommandsWindow_get_Top(This,Top)	\
    (This)->lpVtbl -> get_Top(This,Top)

#define IAgentCtlCommandsWindow_get_Height(This,Height)	\
    (This)->lpVtbl -> get_Height(This,Height)

#define IAgentCtlCommandsWindow_get_Width(This,Width)	\
    (This)->lpVtbl -> get_Width(This,Width)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommandsWindow_get_Visible_Proxy( 
    IAgentCtlCommandsWindow __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Visible);


void __RPC_STUB IAgentCtlCommandsWindow_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommandsWindow_put_Visible_Proxy( 
    IAgentCtlCommandsWindow __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Visible);


void __RPC_STUB IAgentCtlCommandsWindow_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommandsWindow_get_Left_Proxy( 
    IAgentCtlCommandsWindow __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *Left);


void __RPC_STUB IAgentCtlCommandsWindow_get_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommandsWindow_get_Top_Proxy( 
    IAgentCtlCommandsWindow __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *Top);


void __RPC_STUB IAgentCtlCommandsWindow_get_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommandsWindow_get_Height_Proxy( 
    IAgentCtlCommandsWindow __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *Height);


void __RPC_STUB IAgentCtlCommandsWindow_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtlCommandsWindow_get_Width_Proxy( 
    IAgentCtlCommandsWindow __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *Width);


void __RPC_STUB IAgentCtlCommandsWindow_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentCtlCommandsWindow_INTERFACE_DEFINED__ */


#ifndef __IAgentCtl_INTERFACE_DEFINED__
#define __IAgentCtl_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentCtl
 * at Wed Aug 13 20:54:44 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAgentCtl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("F5BE8BD1-7DE6-11D0-91FE-00C04FD701A5")
    IAgentCtl : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Characters( 
            /* [retval][out] */ IAgentCtlCharacters __RPC_FAR *__RPC_FAR *Characters) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_AudioOutput( 
            /* [retval][out] */ IAgentCtlAudioObject __RPC_FAR *__RPC_FAR *AudioOutput) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_SpeechInput( 
            /* [retval][out] */ IAgentCtlSpeechInput __RPC_FAR *__RPC_FAR *SpeechInput) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_PropertySheet( 
            /* [retval][out] */ IAgentCtlPropertySheet __RPC_FAR *__RPC_FAR *PropSheet) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_CommandsWindow( 
            /* [retval][out] */ IAgentCtlCommandsWindow __RPC_FAR *__RPC_FAR *CommandsWindow) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Connected( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Connected) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Connected( 
            VARIANT_BOOL Connected) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Suspended( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Suspended) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentCtlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentCtl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentCtl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentCtl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgentCtl __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgentCtl __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgentCtl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgentCtl __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Characters )( 
            IAgentCtl __RPC_FAR * This,
            /* [retval][out] */ IAgentCtlCharacters __RPC_FAR *__RPC_FAR *Characters);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AudioOutput )( 
            IAgentCtl __RPC_FAR * This,
            /* [retval][out] */ IAgentCtlAudioObject __RPC_FAR *__RPC_FAR *AudioOutput);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SpeechInput )( 
            IAgentCtl __RPC_FAR * This,
            /* [retval][out] */ IAgentCtlSpeechInput __RPC_FAR *__RPC_FAR *SpeechInput);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PropertySheet )( 
            IAgentCtl __RPC_FAR * This,
            /* [retval][out] */ IAgentCtlPropertySheet __RPC_FAR *__RPC_FAR *PropSheet);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CommandsWindow )( 
            IAgentCtl __RPC_FAR * This,
            /* [retval][out] */ IAgentCtlCommandsWindow __RPC_FAR *__RPC_FAR *CommandsWindow);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Connected )( 
            IAgentCtl __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Connected);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Connected )( 
            IAgentCtl __RPC_FAR * This,
            VARIANT_BOOL Connected);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Suspended )( 
            IAgentCtl __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Suspended);
        
        END_INTERFACE
    } IAgentCtlVtbl;

    interface IAgentCtl
    {
        CONST_VTBL struct IAgentCtlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentCtl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentCtl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentCtl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentCtl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgentCtl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgentCtl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgentCtl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgentCtl_get_Characters(This,Characters)	\
    (This)->lpVtbl -> get_Characters(This,Characters)

#define IAgentCtl_get_AudioOutput(This,AudioOutput)	\
    (This)->lpVtbl -> get_AudioOutput(This,AudioOutput)

#define IAgentCtl_get_SpeechInput(This,SpeechInput)	\
    (This)->lpVtbl -> get_SpeechInput(This,SpeechInput)

#define IAgentCtl_get_PropertySheet(This,PropSheet)	\
    (This)->lpVtbl -> get_PropertySheet(This,PropSheet)

#define IAgentCtl_get_CommandsWindow(This,CommandsWindow)	\
    (This)->lpVtbl -> get_CommandsWindow(This,CommandsWindow)

#define IAgentCtl_get_Connected(This,Connected)	\
    (This)->lpVtbl -> get_Connected(This,Connected)

#define IAgentCtl_put_Connected(This,Connected)	\
    (This)->lpVtbl -> put_Connected(This,Connected)

#define IAgentCtl_get_Suspended(This,Suspended)	\
    (This)->lpVtbl -> get_Suspended(This,Suspended)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtl_get_Characters_Proxy( 
    IAgentCtl __RPC_FAR * This,
    /* [retval][out] */ IAgentCtlCharacters __RPC_FAR *__RPC_FAR *Characters);


void __RPC_STUB IAgentCtl_get_Characters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtl_get_AudioOutput_Proxy( 
    IAgentCtl __RPC_FAR * This,
    /* [retval][out] */ IAgentCtlAudioObject __RPC_FAR *__RPC_FAR *AudioOutput);


void __RPC_STUB IAgentCtl_get_AudioOutput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtl_get_SpeechInput_Proxy( 
    IAgentCtl __RPC_FAR * This,
    /* [retval][out] */ IAgentCtlSpeechInput __RPC_FAR *__RPC_FAR *SpeechInput);


void __RPC_STUB IAgentCtl_get_SpeechInput_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtl_get_PropertySheet_Proxy( 
    IAgentCtl __RPC_FAR * This,
    /* [retval][out] */ IAgentCtlPropertySheet __RPC_FAR *__RPC_FAR *PropSheet);


void __RPC_STUB IAgentCtl_get_PropertySheet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtl_get_CommandsWindow_Proxy( 
    IAgentCtl __RPC_FAR * This,
    /* [retval][out] */ IAgentCtlCommandsWindow __RPC_FAR *__RPC_FAR *CommandsWindow);


void __RPC_STUB IAgentCtl_get_CommandsWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtl_get_Connected_Proxy( 
    IAgentCtl __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Connected);


void __RPC_STUB IAgentCtl_get_Connected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IAgentCtl_put_Connected_Proxy( 
    IAgentCtl __RPC_FAR * This,
    VARIANT_BOOL Connected);


void __RPC_STUB IAgentCtl_put_Connected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IAgentCtl_get_Suspended_Proxy( 
    IAgentCtl __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Suspended);


void __RPC_STUB IAgentCtl_get_Suspended_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentCtl_INTERFACE_DEFINED__ */



#ifndef __AgentObjects_LIBRARY_DEFINED__
#define __AgentObjects_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: AgentObjects
 * at Wed Aug 13 20:54:44 1997
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 















EXTERN_C const IID LIBID_AgentObjects;

#ifndef ___AgentEvents_DISPINTERFACE_DEFINED__
#define ___AgentEvents_DISPINTERFACE_DEFINED__

/****************************************
 * Generated header for dispinterface: _AgentEvents
 * at Wed Aug 13 20:54:44 1997
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][uuid] */ 



EXTERN_C const IID DIID__AgentEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface DECLSPEC_UUID("F5BE8BD4-7DE6-11D0-91FE-00C04FD701A5")
    _AgentEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _AgentEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _AgentEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _AgentEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _AgentEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _AgentEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _AgentEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _AgentEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _AgentEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _AgentEventsVtbl;

    interface _AgentEvents
    {
        CONST_VTBL struct _AgentEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _AgentEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _AgentEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _AgentEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _AgentEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _AgentEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _AgentEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _AgentEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___AgentEvents_DISPINTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_Agent;

class DECLSPEC_UUID("F5BE8BD2-7DE6-11D0-91FE-00C04FD701A5")
Agent;
#endif
#endif /* __AgentObjects_LIBRARY_DEFINED__ */

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
