/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Wed Aug 13 21:04:17 1997
 */
/* Compiler settings for AgentServer.idl:
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

#ifndef __AgentServer_h__
#define __AgentServer_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAgentUserInput_FWD_DEFINED__
#define __IAgentUserInput_FWD_DEFINED__
typedef interface IAgentUserInput IAgentUserInput;
#endif 	/* __IAgentUserInput_FWD_DEFINED__ */


#ifndef __IAgentCommand_FWD_DEFINED__
#define __IAgentCommand_FWD_DEFINED__
typedef interface IAgentCommand IAgentCommand;
#endif 	/* __IAgentCommand_FWD_DEFINED__ */


#ifndef __IAgentCommands_FWD_DEFINED__
#define __IAgentCommands_FWD_DEFINED__
typedef interface IAgentCommands IAgentCommands;
#endif 	/* __IAgentCommands_FWD_DEFINED__ */


#ifndef __IAgentCommandWindow_FWD_DEFINED__
#define __IAgentCommandWindow_FWD_DEFINED__
typedef interface IAgentCommandWindow IAgentCommandWindow;
#endif 	/* __IAgentCommandWindow_FWD_DEFINED__ */


#ifndef __IAgentSpeechInputProperties_FWD_DEFINED__
#define __IAgentSpeechInputProperties_FWD_DEFINED__
typedef interface IAgentSpeechInputProperties IAgentSpeechInputProperties;
#endif 	/* __IAgentSpeechInputProperties_FWD_DEFINED__ */


#ifndef __IAgentAudioOutputProperties_FWD_DEFINED__
#define __IAgentAudioOutputProperties_FWD_DEFINED__
typedef interface IAgentAudioOutputProperties IAgentAudioOutputProperties;
#endif 	/* __IAgentAudioOutputProperties_FWD_DEFINED__ */


#ifndef __IAgentPropertySheet_FWD_DEFINED__
#define __IAgentPropertySheet_FWD_DEFINED__
typedef interface IAgentPropertySheet IAgentPropertySheet;
#endif 	/* __IAgentPropertySheet_FWD_DEFINED__ */


#ifndef __IAgentBalloon_FWD_DEFINED__
#define __IAgentBalloon_FWD_DEFINED__
typedef interface IAgentBalloon IAgentBalloon;
#endif 	/* __IAgentBalloon_FWD_DEFINED__ */


#ifndef __IAgentCharacter_FWD_DEFINED__
#define __IAgentCharacter_FWD_DEFINED__
typedef interface IAgentCharacter IAgentCharacter;
#endif 	/* __IAgentCharacter_FWD_DEFINED__ */


#ifndef __IAgent_FWD_DEFINED__
#define __IAgent_FWD_DEFINED__
typedef interface IAgent IAgent;
#endif 	/* __IAgent_FWD_DEFINED__ */


#ifndef __IAgentNotifySink_FWD_DEFINED__
#define __IAgentNotifySink_FWD_DEFINED__
typedef interface IAgentNotifySink IAgentNotifySink;
#endif 	/* __IAgentNotifySink_FWD_DEFINED__ */


#ifndef __IAgentPrivateNotifySink_FWD_DEFINED__
#define __IAgentPrivateNotifySink_FWD_DEFINED__
typedef interface IAgentPrivateNotifySink IAgentPrivateNotifySink;
#endif 	/* __IAgentPrivateNotifySink_FWD_DEFINED__ */


#ifndef __AgentServer_FWD_DEFINED__
#define __AgentServer_FWD_DEFINED__

#ifdef __cplusplus
typedef class AgentServer AgentServer;
#else
typedef struct AgentServer AgentServer;
#endif /* __cplusplus */

#endif 	/* __AgentServer_FWD_DEFINED__ */


#ifndef __IAgentUserInput_FWD_DEFINED__
#define __IAgentUserInput_FWD_DEFINED__
typedef interface IAgentUserInput IAgentUserInput;
#endif 	/* __IAgentUserInput_FWD_DEFINED__ */


#ifndef __IAgentCommand_FWD_DEFINED__
#define __IAgentCommand_FWD_DEFINED__
typedef interface IAgentCommand IAgentCommand;
#endif 	/* __IAgentCommand_FWD_DEFINED__ */


#ifndef __IAgentCommands_FWD_DEFINED__
#define __IAgentCommands_FWD_DEFINED__
typedef interface IAgentCommands IAgentCommands;
#endif 	/* __IAgentCommands_FWD_DEFINED__ */


#ifndef __IAgentSpeechInputProperties_FWD_DEFINED__
#define __IAgentSpeechInputProperties_FWD_DEFINED__
typedef interface IAgentSpeechInputProperties IAgentSpeechInputProperties;
#endif 	/* __IAgentSpeechInputProperties_FWD_DEFINED__ */


#ifndef __IAgentAudioOutputProperties_FWD_DEFINED__
#define __IAgentAudioOutputProperties_FWD_DEFINED__
typedef interface IAgentAudioOutputProperties IAgentAudioOutputProperties;
#endif 	/* __IAgentAudioOutputProperties_FWD_DEFINED__ */


#ifndef __IAgentPropertySheet_FWD_DEFINED__
#define __IAgentPropertySheet_FWD_DEFINED__
typedef interface IAgentPropertySheet IAgentPropertySheet;
#endif 	/* __IAgentPropertySheet_FWD_DEFINED__ */


#ifndef __IAgentBalloon_FWD_DEFINED__
#define __IAgentBalloon_FWD_DEFINED__
typedef interface IAgentBalloon IAgentBalloon;
#endif 	/* __IAgentBalloon_FWD_DEFINED__ */


#ifndef __IAgentCharacter_FWD_DEFINED__
#define __IAgentCharacter_FWD_DEFINED__
typedef interface IAgentCharacter IAgentCharacter;
#endif 	/* __IAgentCharacter_FWD_DEFINED__ */


#ifndef __IAgent_FWD_DEFINED__
#define __IAgent_FWD_DEFINED__
typedef interface IAgent IAgent;
#endif 	/* __IAgent_FWD_DEFINED__ */


#ifndef __IAgentNotifySink_FWD_DEFINED__
#define __IAgentNotifySink_FWD_DEFINED__
typedef interface IAgentNotifySink IAgentNotifySink;
#endif 	/* __IAgentNotifySink_FWD_DEFINED__ */


#ifndef __IAgentCommandWindow_FWD_DEFINED__
#define __IAgentCommandWindow_FWD_DEFINED__
typedef interface IAgentCommandWindow IAgentCommandWindow;
#endif 	/* __IAgentCommandWindow_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_AgentServer_0000
 * at Wed Aug 13 21:04:17 1997
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


#define	NeverMoved	( 0 )

#define	UserMoved	( 1 )

#define	ProgramMoved	( 2 )

#define	OtherProgramMoved	( 3 )

#define	NeverShown	( 0 )

#define	UserHid	( 1 )

#define	UserShowed	( 2 )

#define	ProgramHid	( 3 )

#define	ProgramShowed	( 4 )

#define	OtherProgramHid	( 5 )

#define	OtherProgramShowed	( 6 )

#define	ACTIVATE_NOTTOPMOST	( 0 )

#define	ACTIVATE_TOPMOST	( 1 )

#define	ACTIVATE_INPUTACTIVE	( 2 )

#define	PREPARE_ANIMATION	( 0 )

#define	PREPARE_STATE	( 1 )

#define	PREPARE_WAVE	( 2 )

#define	STOP_TYPE_PLAY	( 0x1 )

#define	STOP_TYPE_MOVE	( 0x2 )

#define	STOP_TYPE_SPEAK	( 0x4 )

#define	STOP_TYPE_PREPARE	( 0x8 )

#define	STOP_TYPE_NONQUEUEDPREPARE	( 0x10 )

#define	STOP_TYPE_VISIBLE	( 0x20 )

#define	STOP_TYPE_ALL	( 0xffffffff )



extern RPC_IF_HANDLE __MIDL_itf_AgentServer_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AgentServer_0000_v0_0_s_ifspec;

#ifndef __IAgentUserInput_INTERFACE_DEFINED__
#define __IAgentUserInput_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentUserInput
 * at Wed Aug 13 21:04:17 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAgentUserInput;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("A7B93C80-7B81-11D0-AC5F-00C04FD97575")
    IAgentUserInput : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCount( 
            /* [out] */ long __RPC_FAR *pdwCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetItemID( 
            /* [in] */ long dwItemIndex,
            /* [out] */ long __RPC_FAR *pdwCommandID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetItemConfidence( 
            /* [in] */ long dwItemIndex,
            /* [out] */ long __RPC_FAR *plConfidence) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetItemText( 
            /* [in] */ long dwItemIndex,
            /* [out] */ BSTR __RPC_FAR *pbszText) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAllItemData( 
            /* [out] */ VARIANT __RPC_FAR *pdwItemIndices,
            /* [out] */ VARIANT __RPC_FAR *plConfidences,
            /* [out] */ VARIANT __RPC_FAR *pbszText) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentUserInputVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentUserInput __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentUserInput __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentUserInput __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgentUserInput __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgentUserInput __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgentUserInput __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgentUserInput __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCount )( 
            IAgentUserInput __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pdwCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetItemID )( 
            IAgentUserInput __RPC_FAR * This,
            /* [in] */ long dwItemIndex,
            /* [out] */ long __RPC_FAR *pdwCommandID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetItemConfidence )( 
            IAgentUserInput __RPC_FAR * This,
            /* [in] */ long dwItemIndex,
            /* [out] */ long __RPC_FAR *plConfidence);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetItemText )( 
            IAgentUserInput __RPC_FAR * This,
            /* [in] */ long dwItemIndex,
            /* [out] */ BSTR __RPC_FAR *pbszText);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAllItemData )( 
            IAgentUserInput __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *pdwItemIndices,
            /* [out] */ VARIANT __RPC_FAR *plConfidences,
            /* [out] */ VARIANT __RPC_FAR *pbszText);
        
        END_INTERFACE
    } IAgentUserInputVtbl;

    interface IAgentUserInput
    {
        CONST_VTBL struct IAgentUserInputVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentUserInput_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentUserInput_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentUserInput_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentUserInput_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgentUserInput_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgentUserInput_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgentUserInput_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgentUserInput_GetCount(This,pdwCount)	\
    (This)->lpVtbl -> GetCount(This,pdwCount)

#define IAgentUserInput_GetItemID(This,dwItemIndex,pdwCommandID)	\
    (This)->lpVtbl -> GetItemID(This,dwItemIndex,pdwCommandID)

#define IAgentUserInput_GetItemConfidence(This,dwItemIndex,plConfidence)	\
    (This)->lpVtbl -> GetItemConfidence(This,dwItemIndex,plConfidence)

#define IAgentUserInput_GetItemText(This,dwItemIndex,pbszText)	\
    (This)->lpVtbl -> GetItemText(This,dwItemIndex,pbszText)

#define IAgentUserInput_GetAllItemData(This,pdwItemIndices,plConfidences,pbszText)	\
    (This)->lpVtbl -> GetAllItemData(This,pdwItemIndices,plConfidences,pbszText)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAgentUserInput_GetCount_Proxy( 
    IAgentUserInput __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pdwCount);


void __RPC_STUB IAgentUserInput_GetCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentUserInput_GetItemID_Proxy( 
    IAgentUserInput __RPC_FAR * This,
    /* [in] */ long dwItemIndex,
    /* [out] */ long __RPC_FAR *pdwCommandID);


void __RPC_STUB IAgentUserInput_GetItemID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentUserInput_GetItemConfidence_Proxy( 
    IAgentUserInput __RPC_FAR * This,
    /* [in] */ long dwItemIndex,
    /* [out] */ long __RPC_FAR *plConfidence);


void __RPC_STUB IAgentUserInput_GetItemConfidence_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentUserInput_GetItemText_Proxy( 
    IAgentUserInput __RPC_FAR * This,
    /* [in] */ long dwItemIndex,
    /* [out] */ BSTR __RPC_FAR *pbszText);


void __RPC_STUB IAgentUserInput_GetItemText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentUserInput_GetAllItemData_Proxy( 
    IAgentUserInput __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *pdwItemIndices,
    /* [out] */ VARIANT __RPC_FAR *plConfidences,
    /* [out] */ VARIANT __RPC_FAR *pbszText);


void __RPC_STUB IAgentUserInput_GetAllItemData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentUserInput_INTERFACE_DEFINED__ */


#ifndef __IAgentCommand_INTERFACE_DEFINED__
#define __IAgentCommand_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentCommand
 * at Wed Aug 13 21:04:17 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAgentCommand;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("A7B93C83-7B81-11D0-AC5F-00C04FD97575")
    IAgentCommand : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetCaption( 
            /* [in] */ BSTR bszCaption) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCaption( 
            /* [out] */ BSTR __RPC_FAR *pbszCaption) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetVoice( 
            /* [in] */ BSTR bszVoice) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVoice( 
            /* [out] */ BSTR __RPC_FAR *pbszVoice) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetEnabled( 
            /* [in] */ long bEnabled) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEnabled( 
            /* [out] */ long __RPC_FAR *pbEnabled) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetVisible( 
            /* [in] */ long bVisible) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVisible( 
            /* [out] */ long __RPC_FAR *pbVisible) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetConfidenceThreshold( 
            /* [in] */ long lThreshold) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetConfidenceThreshold( 
            /* [out] */ long __RPC_FAR *plThreshold) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetConfidenceText( 
            /* [in] */ BSTR bszTipText) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetConfidenceText( 
            /* [out] */ BSTR __RPC_FAR *pbszTipText) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetID( 
            /* [out] */ long __RPC_FAR *pdwID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentCommandVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentCommand __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentCommand __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentCommand __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgentCommand __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgentCommand __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgentCommand __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgentCommand __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCaption )( 
            IAgentCommand __RPC_FAR * This,
            /* [in] */ BSTR bszCaption);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCaption )( 
            IAgentCommand __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbszCaption);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVoice )( 
            IAgentCommand __RPC_FAR * This,
            /* [in] */ BSTR bszVoice);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVoice )( 
            IAgentCommand __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbszVoice);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEnabled )( 
            IAgentCommand __RPC_FAR * This,
            /* [in] */ long bEnabled);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEnabled )( 
            IAgentCommand __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pbEnabled);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVisible )( 
            IAgentCommand __RPC_FAR * This,
            /* [in] */ long bVisible);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVisible )( 
            IAgentCommand __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pbVisible);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfidenceThreshold )( 
            IAgentCommand __RPC_FAR * This,
            /* [in] */ long lThreshold);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfidenceThreshold )( 
            IAgentCommand __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plThreshold);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfidenceText )( 
            IAgentCommand __RPC_FAR * This,
            /* [in] */ BSTR bszTipText);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfidenceText )( 
            IAgentCommand __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbszTipText);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetID )( 
            IAgentCommand __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pdwID);
        
        END_INTERFACE
    } IAgentCommandVtbl;

    interface IAgentCommand
    {
        CONST_VTBL struct IAgentCommandVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentCommand_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentCommand_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentCommand_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentCommand_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgentCommand_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgentCommand_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgentCommand_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgentCommand_SetCaption(This,bszCaption)	\
    (This)->lpVtbl -> SetCaption(This,bszCaption)

#define IAgentCommand_GetCaption(This,pbszCaption)	\
    (This)->lpVtbl -> GetCaption(This,pbszCaption)

#define IAgentCommand_SetVoice(This,bszVoice)	\
    (This)->lpVtbl -> SetVoice(This,bszVoice)

#define IAgentCommand_GetVoice(This,pbszVoice)	\
    (This)->lpVtbl -> GetVoice(This,pbszVoice)

#define IAgentCommand_SetEnabled(This,bEnabled)	\
    (This)->lpVtbl -> SetEnabled(This,bEnabled)

#define IAgentCommand_GetEnabled(This,pbEnabled)	\
    (This)->lpVtbl -> GetEnabled(This,pbEnabled)

#define IAgentCommand_SetVisible(This,bVisible)	\
    (This)->lpVtbl -> SetVisible(This,bVisible)

#define IAgentCommand_GetVisible(This,pbVisible)	\
    (This)->lpVtbl -> GetVisible(This,pbVisible)

#define IAgentCommand_SetConfidenceThreshold(This,lThreshold)	\
    (This)->lpVtbl -> SetConfidenceThreshold(This,lThreshold)

#define IAgentCommand_GetConfidenceThreshold(This,plThreshold)	\
    (This)->lpVtbl -> GetConfidenceThreshold(This,plThreshold)

#define IAgentCommand_SetConfidenceText(This,bszTipText)	\
    (This)->lpVtbl -> SetConfidenceText(This,bszTipText)

#define IAgentCommand_GetConfidenceText(This,pbszTipText)	\
    (This)->lpVtbl -> GetConfidenceText(This,pbszTipText)

#define IAgentCommand_GetID(This,pdwID)	\
    (This)->lpVtbl -> GetID(This,pdwID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAgentCommand_SetCaption_Proxy( 
    IAgentCommand __RPC_FAR * This,
    /* [in] */ BSTR bszCaption);


void __RPC_STUB IAgentCommand_SetCaption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommand_GetCaption_Proxy( 
    IAgentCommand __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbszCaption);


void __RPC_STUB IAgentCommand_GetCaption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommand_SetVoice_Proxy( 
    IAgentCommand __RPC_FAR * This,
    /* [in] */ BSTR bszVoice);


void __RPC_STUB IAgentCommand_SetVoice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommand_GetVoice_Proxy( 
    IAgentCommand __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbszVoice);


void __RPC_STUB IAgentCommand_GetVoice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommand_SetEnabled_Proxy( 
    IAgentCommand __RPC_FAR * This,
    /* [in] */ long bEnabled);


void __RPC_STUB IAgentCommand_SetEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommand_GetEnabled_Proxy( 
    IAgentCommand __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pbEnabled);


void __RPC_STUB IAgentCommand_GetEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommand_SetVisible_Proxy( 
    IAgentCommand __RPC_FAR * This,
    /* [in] */ long bVisible);


void __RPC_STUB IAgentCommand_SetVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommand_GetVisible_Proxy( 
    IAgentCommand __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pbVisible);


void __RPC_STUB IAgentCommand_GetVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommand_SetConfidenceThreshold_Proxy( 
    IAgentCommand __RPC_FAR * This,
    /* [in] */ long lThreshold);


void __RPC_STUB IAgentCommand_SetConfidenceThreshold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommand_GetConfidenceThreshold_Proxy( 
    IAgentCommand __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plThreshold);


void __RPC_STUB IAgentCommand_GetConfidenceThreshold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommand_SetConfidenceText_Proxy( 
    IAgentCommand __RPC_FAR * This,
    /* [in] */ BSTR bszTipText);


void __RPC_STUB IAgentCommand_SetConfidenceText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommand_GetConfidenceText_Proxy( 
    IAgentCommand __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbszTipText);


void __RPC_STUB IAgentCommand_GetConfidenceText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommand_GetID_Proxy( 
    IAgentCommand __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pdwID);


void __RPC_STUB IAgentCommand_GetID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentCommand_INTERFACE_DEFINED__ */


#ifndef __IAgentCommands_INTERFACE_DEFINED__
#define __IAgentCommands_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentCommands
 * at Wed Aug 13 21:04:17 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAgentCommands;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("A7B93C85-7B81-11D0-AC5F-00C04FD97575")
    IAgentCommands : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCommand( 
            /* [in] */ long dwCommandID,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunkCommand) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCount( 
            /* [out] */ long __RPC_FAR *pdwCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCaption( 
            /* [in] */ BSTR bszCaption) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCaption( 
            /* [out] */ BSTR __RPC_FAR *pbszCaption) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetVoice( 
            /* [in] */ BSTR bszVoice) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVoice( 
            /* [out] */ BSTR __RPC_FAR *pbszVoice) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetVisible( 
            /* [in] */ long bVisible) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVisible( 
            /* [out] */ long __RPC_FAR *pbVisible) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR bszCaption,
            /* [in] */ BSTR bszVoice,
            /* [in] */ long bEnabled,
            /* [in] */ long bVisible,
            /* [out] */ long __RPC_FAR *pdwID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Insert( 
            /* [in] */ BSTR bszCaption,
            /* [in] */ BSTR bszVoice,
            /* [in] */ long bEnabled,
            /* [in] */ long bVisible,
            /* [in] */ long dwRefID,
            /* [in] */ long bBefore,
            /* [out] */ long __RPC_FAR *pdwID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ long dwID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentCommandsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentCommands __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentCommands __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentCommands __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgentCommands __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgentCommands __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgentCommands __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgentCommands __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCommand )( 
            IAgentCommands __RPC_FAR * This,
            /* [in] */ long dwCommandID,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunkCommand);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCount )( 
            IAgentCommands __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pdwCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCaption )( 
            IAgentCommands __RPC_FAR * This,
            /* [in] */ BSTR bszCaption);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCaption )( 
            IAgentCommands __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbszCaption);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVoice )( 
            IAgentCommands __RPC_FAR * This,
            /* [in] */ BSTR bszVoice);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVoice )( 
            IAgentCommands __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbszVoice);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVisible )( 
            IAgentCommands __RPC_FAR * This,
            /* [in] */ long bVisible);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVisible )( 
            IAgentCommands __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pbVisible);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IAgentCommands __RPC_FAR * This,
            /* [in] */ BSTR bszCaption,
            /* [in] */ BSTR bszVoice,
            /* [in] */ long bEnabled,
            /* [in] */ long bVisible,
            /* [out] */ long __RPC_FAR *pdwID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Insert )( 
            IAgentCommands __RPC_FAR * This,
            /* [in] */ BSTR bszCaption,
            /* [in] */ BSTR bszVoice,
            /* [in] */ long bEnabled,
            /* [in] */ long bVisible,
            /* [in] */ long dwRefID,
            /* [in] */ long bBefore,
            /* [out] */ long __RPC_FAR *pdwID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IAgentCommands __RPC_FAR * This,
            /* [in] */ long dwID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveAll )( 
            IAgentCommands __RPC_FAR * This);
        
        END_INTERFACE
    } IAgentCommandsVtbl;

    interface IAgentCommands
    {
        CONST_VTBL struct IAgentCommandsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentCommands_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentCommands_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentCommands_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentCommands_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgentCommands_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgentCommands_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgentCommands_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgentCommands_GetCommand(This,dwCommandID,ppunkCommand)	\
    (This)->lpVtbl -> GetCommand(This,dwCommandID,ppunkCommand)

#define IAgentCommands_GetCount(This,pdwCount)	\
    (This)->lpVtbl -> GetCount(This,pdwCount)

#define IAgentCommands_SetCaption(This,bszCaption)	\
    (This)->lpVtbl -> SetCaption(This,bszCaption)

#define IAgentCommands_GetCaption(This,pbszCaption)	\
    (This)->lpVtbl -> GetCaption(This,pbszCaption)

#define IAgentCommands_SetVoice(This,bszVoice)	\
    (This)->lpVtbl -> SetVoice(This,bszVoice)

#define IAgentCommands_GetVoice(This,pbszVoice)	\
    (This)->lpVtbl -> GetVoice(This,pbszVoice)

#define IAgentCommands_SetVisible(This,bVisible)	\
    (This)->lpVtbl -> SetVisible(This,bVisible)

#define IAgentCommands_GetVisible(This,pbVisible)	\
    (This)->lpVtbl -> GetVisible(This,pbVisible)

#define IAgentCommands_Add(This,bszCaption,bszVoice,bEnabled,bVisible,pdwID)	\
    (This)->lpVtbl -> Add(This,bszCaption,bszVoice,bEnabled,bVisible,pdwID)

#define IAgentCommands_Insert(This,bszCaption,bszVoice,bEnabled,bVisible,dwRefID,bBefore,pdwID)	\
    (This)->lpVtbl -> Insert(This,bszCaption,bszVoice,bEnabled,bVisible,dwRefID,bBefore,pdwID)

#define IAgentCommands_Remove(This,dwID)	\
    (This)->lpVtbl -> Remove(This,dwID)

#define IAgentCommands_RemoveAll(This)	\
    (This)->lpVtbl -> RemoveAll(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAgentCommands_GetCommand_Proxy( 
    IAgentCommands __RPC_FAR * This,
    /* [in] */ long dwCommandID,
    /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunkCommand);


void __RPC_STUB IAgentCommands_GetCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommands_GetCount_Proxy( 
    IAgentCommands __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pdwCount);


void __RPC_STUB IAgentCommands_GetCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommands_SetCaption_Proxy( 
    IAgentCommands __RPC_FAR * This,
    /* [in] */ BSTR bszCaption);


void __RPC_STUB IAgentCommands_SetCaption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommands_GetCaption_Proxy( 
    IAgentCommands __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbszCaption);


void __RPC_STUB IAgentCommands_GetCaption_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommands_SetVoice_Proxy( 
    IAgentCommands __RPC_FAR * This,
    /* [in] */ BSTR bszVoice);


void __RPC_STUB IAgentCommands_SetVoice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommands_GetVoice_Proxy( 
    IAgentCommands __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbszVoice);


void __RPC_STUB IAgentCommands_GetVoice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommands_SetVisible_Proxy( 
    IAgentCommands __RPC_FAR * This,
    /* [in] */ long bVisible);


void __RPC_STUB IAgentCommands_SetVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommands_GetVisible_Proxy( 
    IAgentCommands __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pbVisible);


void __RPC_STUB IAgentCommands_GetVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommands_Add_Proxy( 
    IAgentCommands __RPC_FAR * This,
    /* [in] */ BSTR bszCaption,
    /* [in] */ BSTR bszVoice,
    /* [in] */ long bEnabled,
    /* [in] */ long bVisible,
    /* [out] */ long __RPC_FAR *pdwID);


void __RPC_STUB IAgentCommands_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommands_Insert_Proxy( 
    IAgentCommands __RPC_FAR * This,
    /* [in] */ BSTR bszCaption,
    /* [in] */ BSTR bszVoice,
    /* [in] */ long bEnabled,
    /* [in] */ long bVisible,
    /* [in] */ long dwRefID,
    /* [in] */ long bBefore,
    /* [out] */ long __RPC_FAR *pdwID);


void __RPC_STUB IAgentCommands_Insert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommands_Remove_Proxy( 
    IAgentCommands __RPC_FAR * This,
    /* [in] */ long dwID);


void __RPC_STUB IAgentCommands_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommands_RemoveAll_Proxy( 
    IAgentCommands __RPC_FAR * This);


void __RPC_STUB IAgentCommands_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentCommands_INTERFACE_DEFINED__ */


#ifndef __IAgentCommandWindow_INTERFACE_DEFINED__
#define __IAgentCommandWindow_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentCommandWindow
 * at Wed Aug 13 21:04:17 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAgentCommandWindow;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("6D0ECB23-9968-11D0-AC6E-00C04FD97575")
    IAgentCommandWindow : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetVisible( 
            /* [in] */ long bVisible) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVisible( 
            /* [out] */ long __RPC_FAR *pbVisible) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPosition( 
            /* [out] */ long __RPC_FAR *plLeft,
            /* [out] */ long __RPC_FAR *plTop) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSize( 
            /* [out] */ long __RPC_FAR *plWidth,
            /* [out] */ long __RPC_FAR *plHeight) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentCommandWindowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentCommandWindow __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentCommandWindow __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentCommandWindow __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgentCommandWindow __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgentCommandWindow __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgentCommandWindow __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgentCommandWindow __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVisible )( 
            IAgentCommandWindow __RPC_FAR * This,
            /* [in] */ long bVisible);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVisible )( 
            IAgentCommandWindow __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pbVisible);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPosition )( 
            IAgentCommandWindow __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plLeft,
            /* [out] */ long __RPC_FAR *plTop);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSize )( 
            IAgentCommandWindow __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plWidth,
            /* [out] */ long __RPC_FAR *plHeight);
        
        END_INTERFACE
    } IAgentCommandWindowVtbl;

    interface IAgentCommandWindow
    {
        CONST_VTBL struct IAgentCommandWindowVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentCommandWindow_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentCommandWindow_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentCommandWindow_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentCommandWindow_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgentCommandWindow_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgentCommandWindow_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgentCommandWindow_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgentCommandWindow_SetVisible(This,bVisible)	\
    (This)->lpVtbl -> SetVisible(This,bVisible)

#define IAgentCommandWindow_GetVisible(This,pbVisible)	\
    (This)->lpVtbl -> GetVisible(This,pbVisible)

#define IAgentCommandWindow_GetPosition(This,plLeft,plTop)	\
    (This)->lpVtbl -> GetPosition(This,plLeft,plTop)

#define IAgentCommandWindow_GetSize(This,plWidth,plHeight)	\
    (This)->lpVtbl -> GetSize(This,plWidth,plHeight)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAgentCommandWindow_SetVisible_Proxy( 
    IAgentCommandWindow __RPC_FAR * This,
    /* [in] */ long bVisible);


void __RPC_STUB IAgentCommandWindow_SetVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommandWindow_GetVisible_Proxy( 
    IAgentCommandWindow __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pbVisible);


void __RPC_STUB IAgentCommandWindow_GetVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommandWindow_GetPosition_Proxy( 
    IAgentCommandWindow __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plLeft,
    /* [out] */ long __RPC_FAR *plTop);


void __RPC_STUB IAgentCommandWindow_GetPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCommandWindow_GetSize_Proxy( 
    IAgentCommandWindow __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plWidth,
    /* [out] */ long __RPC_FAR *plHeight);


void __RPC_STUB IAgentCommandWindow_GetSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentCommandWindow_INTERFACE_DEFINED__ */


#ifndef __IAgentSpeechInputProperties_INTERFACE_DEFINED__
#define __IAgentSpeechInputProperties_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentSpeechInputProperties
 * at Wed Aug 13 21:04:17 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAgentSpeechInputProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("A7B93C87-7B81-11D0-AC5F-00C04FD97575")
    IAgentSpeechInputProperties : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetInstalled( 
            /* [out] */ long __RPC_FAR *pbInstalled) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEnabled( 
            /* [out] */ long __RPC_FAR *pbEnabled) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHotKey( 
            /* [out] */ BSTR __RPC_FAR *pbszHotCharKey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLCID( 
            /* [out] */ LCID __RPC_FAR *plcidCurrent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEngine( 
            /* [out] */ BSTR __RPC_FAR *pbszEngine) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetEngine( 
            /* [in] */ BSTR bszEngine) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetListeningTip( 
            /* [out] */ long __RPC_FAR *pbListeningTip) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentSpeechInputPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentSpeechInputProperties __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentSpeechInputProperties __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentSpeechInputProperties __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgentSpeechInputProperties __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgentSpeechInputProperties __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgentSpeechInputProperties __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgentSpeechInputProperties __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInstalled )( 
            IAgentSpeechInputProperties __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pbInstalled);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEnabled )( 
            IAgentSpeechInputProperties __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pbEnabled);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHotKey )( 
            IAgentSpeechInputProperties __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbszHotCharKey);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLCID )( 
            IAgentSpeechInputProperties __RPC_FAR * This,
            /* [out] */ LCID __RPC_FAR *plcidCurrent);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEngine )( 
            IAgentSpeechInputProperties __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbszEngine);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEngine )( 
            IAgentSpeechInputProperties __RPC_FAR * This,
            /* [in] */ BSTR bszEngine);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetListeningTip )( 
            IAgentSpeechInputProperties __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pbListeningTip);
        
        END_INTERFACE
    } IAgentSpeechInputPropertiesVtbl;

    interface IAgentSpeechInputProperties
    {
        CONST_VTBL struct IAgentSpeechInputPropertiesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentSpeechInputProperties_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentSpeechInputProperties_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentSpeechInputProperties_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentSpeechInputProperties_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgentSpeechInputProperties_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgentSpeechInputProperties_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgentSpeechInputProperties_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgentSpeechInputProperties_GetInstalled(This,pbInstalled)	\
    (This)->lpVtbl -> GetInstalled(This,pbInstalled)

#define IAgentSpeechInputProperties_GetEnabled(This,pbEnabled)	\
    (This)->lpVtbl -> GetEnabled(This,pbEnabled)

#define IAgentSpeechInputProperties_GetHotKey(This,pbszHotCharKey)	\
    (This)->lpVtbl -> GetHotKey(This,pbszHotCharKey)

#define IAgentSpeechInputProperties_GetLCID(This,plcidCurrent)	\
    (This)->lpVtbl -> GetLCID(This,plcidCurrent)

#define IAgentSpeechInputProperties_GetEngine(This,pbszEngine)	\
    (This)->lpVtbl -> GetEngine(This,pbszEngine)

#define IAgentSpeechInputProperties_SetEngine(This,bszEngine)	\
    (This)->lpVtbl -> SetEngine(This,bszEngine)

#define IAgentSpeechInputProperties_GetListeningTip(This,pbListeningTip)	\
    (This)->lpVtbl -> GetListeningTip(This,pbListeningTip)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAgentSpeechInputProperties_GetInstalled_Proxy( 
    IAgentSpeechInputProperties __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pbInstalled);


void __RPC_STUB IAgentSpeechInputProperties_GetInstalled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentSpeechInputProperties_GetEnabled_Proxy( 
    IAgentSpeechInputProperties __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pbEnabled);


void __RPC_STUB IAgentSpeechInputProperties_GetEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentSpeechInputProperties_GetHotKey_Proxy( 
    IAgentSpeechInputProperties __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbszHotCharKey);


void __RPC_STUB IAgentSpeechInputProperties_GetHotKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentSpeechInputProperties_GetLCID_Proxy( 
    IAgentSpeechInputProperties __RPC_FAR * This,
    /* [out] */ LCID __RPC_FAR *plcidCurrent);


void __RPC_STUB IAgentSpeechInputProperties_GetLCID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentSpeechInputProperties_GetEngine_Proxy( 
    IAgentSpeechInputProperties __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbszEngine);


void __RPC_STUB IAgentSpeechInputProperties_GetEngine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentSpeechInputProperties_SetEngine_Proxy( 
    IAgentSpeechInputProperties __RPC_FAR * This,
    /* [in] */ BSTR bszEngine);


void __RPC_STUB IAgentSpeechInputProperties_SetEngine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentSpeechInputProperties_GetListeningTip_Proxy( 
    IAgentSpeechInputProperties __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pbListeningTip);


void __RPC_STUB IAgentSpeechInputProperties_GetListeningTip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentSpeechInputProperties_INTERFACE_DEFINED__ */


#ifndef __IAgentAudioOutputProperties_INTERFACE_DEFINED__
#define __IAgentAudioOutputProperties_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentAudioOutputProperties
 * at Wed Aug 13 21:04:17 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAgentAudioOutputProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("A7B93C89-7B81-11D0-AC5F-00C04FD97575")
    IAgentAudioOutputProperties : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetEnabled( 
            /* [out] */ long __RPC_FAR *pbEnabled) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetUsingSoundEffects( 
            /* [out] */ long __RPC_FAR *pbUsingSoundEffects) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentAudioOutputPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentAudioOutputProperties __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentAudioOutputProperties __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentAudioOutputProperties __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgentAudioOutputProperties __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgentAudioOutputProperties __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgentAudioOutputProperties __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgentAudioOutputProperties __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEnabled )( 
            IAgentAudioOutputProperties __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pbEnabled);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetUsingSoundEffects )( 
            IAgentAudioOutputProperties __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pbUsingSoundEffects);
        
        END_INTERFACE
    } IAgentAudioOutputPropertiesVtbl;

    interface IAgentAudioOutputProperties
    {
        CONST_VTBL struct IAgentAudioOutputPropertiesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentAudioOutputProperties_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentAudioOutputProperties_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentAudioOutputProperties_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentAudioOutputProperties_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgentAudioOutputProperties_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgentAudioOutputProperties_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgentAudioOutputProperties_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgentAudioOutputProperties_GetEnabled(This,pbEnabled)	\
    (This)->lpVtbl -> GetEnabled(This,pbEnabled)

#define IAgentAudioOutputProperties_GetUsingSoundEffects(This,pbUsingSoundEffects)	\
    (This)->lpVtbl -> GetUsingSoundEffects(This,pbUsingSoundEffects)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAgentAudioOutputProperties_GetEnabled_Proxy( 
    IAgentAudioOutputProperties __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pbEnabled);


void __RPC_STUB IAgentAudioOutputProperties_GetEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentAudioOutputProperties_GetUsingSoundEffects_Proxy( 
    IAgentAudioOutputProperties __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pbUsingSoundEffects);


void __RPC_STUB IAgentAudioOutputProperties_GetUsingSoundEffects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentAudioOutputProperties_INTERFACE_DEFINED__ */


#ifndef __IAgentPropertySheet_INTERFACE_DEFINED__
#define __IAgentPropertySheet_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentPropertySheet
 * at Wed Aug 13 21:04:17 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAgentPropertySheet;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("A7B93C8B-7B81-11D0-AC5F-00C04FD97575")
    IAgentPropertySheet : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetVisible( 
            /* [out] */ long __RPC_FAR *pbVisible) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetVisible( 
            /* [in] */ long bVisible) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPosition( 
            /* [out] */ long __RPC_FAR *plLeft,
            /* [out] */ long __RPC_FAR *plTop) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSize( 
            /* [out] */ long __RPC_FAR *plWidth,
            /* [out] */ long __RPC_FAR *plHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPage( 
            /* [out] */ BSTR __RPC_FAR *pbszPage) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPage( 
            /* [in] */ BSTR bszPage) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentPropertySheetVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentPropertySheet __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentPropertySheet __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentPropertySheet __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgentPropertySheet __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgentPropertySheet __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgentPropertySheet __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgentPropertySheet __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVisible )( 
            IAgentPropertySheet __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pbVisible);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVisible )( 
            IAgentPropertySheet __RPC_FAR * This,
            /* [in] */ long bVisible);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPosition )( 
            IAgentPropertySheet __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plLeft,
            /* [out] */ long __RPC_FAR *plTop);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSize )( 
            IAgentPropertySheet __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plWidth,
            /* [out] */ long __RPC_FAR *plHeight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPage )( 
            IAgentPropertySheet __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbszPage);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPage )( 
            IAgentPropertySheet __RPC_FAR * This,
            /* [in] */ BSTR bszPage);
        
        END_INTERFACE
    } IAgentPropertySheetVtbl;

    interface IAgentPropertySheet
    {
        CONST_VTBL struct IAgentPropertySheetVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentPropertySheet_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentPropertySheet_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentPropertySheet_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentPropertySheet_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgentPropertySheet_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgentPropertySheet_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgentPropertySheet_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgentPropertySheet_GetVisible(This,pbVisible)	\
    (This)->lpVtbl -> GetVisible(This,pbVisible)

#define IAgentPropertySheet_SetVisible(This,bVisible)	\
    (This)->lpVtbl -> SetVisible(This,bVisible)

#define IAgentPropertySheet_GetPosition(This,plLeft,plTop)	\
    (This)->lpVtbl -> GetPosition(This,plLeft,plTop)

#define IAgentPropertySheet_GetSize(This,plWidth,plHeight)	\
    (This)->lpVtbl -> GetSize(This,plWidth,plHeight)

#define IAgentPropertySheet_GetPage(This,pbszPage)	\
    (This)->lpVtbl -> GetPage(This,pbszPage)

#define IAgentPropertySheet_SetPage(This,bszPage)	\
    (This)->lpVtbl -> SetPage(This,bszPage)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAgentPropertySheet_GetVisible_Proxy( 
    IAgentPropertySheet __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pbVisible);


void __RPC_STUB IAgentPropertySheet_GetVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentPropertySheet_SetVisible_Proxy( 
    IAgentPropertySheet __RPC_FAR * This,
    /* [in] */ long bVisible);


void __RPC_STUB IAgentPropertySheet_SetVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentPropertySheet_GetPosition_Proxy( 
    IAgentPropertySheet __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plLeft,
    /* [out] */ long __RPC_FAR *plTop);


void __RPC_STUB IAgentPropertySheet_GetPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentPropertySheet_GetSize_Proxy( 
    IAgentPropertySheet __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plWidth,
    /* [out] */ long __RPC_FAR *plHeight);


void __RPC_STUB IAgentPropertySheet_GetSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentPropertySheet_GetPage_Proxy( 
    IAgentPropertySheet __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbszPage);


void __RPC_STUB IAgentPropertySheet_GetPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentPropertySheet_SetPage_Proxy( 
    IAgentPropertySheet __RPC_FAR * This,
    /* [in] */ BSTR bszPage);


void __RPC_STUB IAgentPropertySheet_SetPage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentPropertySheet_INTERFACE_DEFINED__ */


#ifndef __IAgentBalloon_INTERFACE_DEFINED__
#define __IAgentBalloon_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentBalloon
 * at Wed Aug 13 21:04:17 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAgentBalloon;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("A7B93C8D-7B81-11D0-AC5F-00C04FD97575")
    IAgentBalloon : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetEnabled( 
            /* [out] */ long __RPC_FAR *pbEnabled) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNumLines( 
            /* [out] */ long __RPC_FAR *plcLines) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNumCharsPerLine( 
            /* [out] */ long __RPC_FAR *plCharsPerLine) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFontName( 
            /* [out] */ BSTR __RPC_FAR *pbszFontName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFontSize( 
            /* [out] */ long __RPC_FAR *plFontSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFontBold( 
            /* [out] */ long __RPC_FAR *pbFontBold) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFontItalic( 
            /* [out] */ long __RPC_FAR *pbFontItalic) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFontStrikethru( 
            /* [out] */ long __RPC_FAR *pbFontStrikethru) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFontUnderline( 
            /* [out] */ long __RPC_FAR *pbFontUnderline) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetForeColor( 
            /* [out] */ long __RPC_FAR *plFGColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBackColor( 
            /* [out] */ long __RPC_FAR *plBGColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBorderColor( 
            /* [out] */ long __RPC_FAR *plBorderColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetVisible( 
            /* [in] */ long bVisible) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVisible( 
            /* [out] */ long __RPC_FAR *pbVisible) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFontName( 
            /* [in] */ BSTR bszFontName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFontSize( 
            /* [in] */ long lFontSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFontCharSet( 
            /* [in] */ short sFontCharSet) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFontCharSet( 
            /* [out] */ short __RPC_FAR *psFontCharSet) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentBalloonVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentBalloon __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentBalloon __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentBalloon __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgentBalloon __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgentBalloon __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgentBalloon __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgentBalloon __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEnabled )( 
            IAgentBalloon __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pbEnabled);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNumLines )( 
            IAgentBalloon __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plcLines);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetNumCharsPerLine )( 
            IAgentBalloon __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plCharsPerLine);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFontName )( 
            IAgentBalloon __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbszFontName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFontSize )( 
            IAgentBalloon __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plFontSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFontBold )( 
            IAgentBalloon __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pbFontBold);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFontItalic )( 
            IAgentBalloon __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pbFontItalic);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFontStrikethru )( 
            IAgentBalloon __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pbFontStrikethru);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFontUnderline )( 
            IAgentBalloon __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pbFontUnderline);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetForeColor )( 
            IAgentBalloon __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plFGColor);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBackColor )( 
            IAgentBalloon __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plBGColor);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBorderColor )( 
            IAgentBalloon __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plBorderColor);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVisible )( 
            IAgentBalloon __RPC_FAR * This,
            /* [in] */ long bVisible);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVisible )( 
            IAgentBalloon __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pbVisible);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFontName )( 
            IAgentBalloon __RPC_FAR * This,
            /* [in] */ BSTR bszFontName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFontSize )( 
            IAgentBalloon __RPC_FAR * This,
            /* [in] */ long lFontSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFontCharSet )( 
            IAgentBalloon __RPC_FAR * This,
            /* [in] */ short sFontCharSet);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFontCharSet )( 
            IAgentBalloon __RPC_FAR * This,
            /* [out] */ short __RPC_FAR *psFontCharSet);
        
        END_INTERFACE
    } IAgentBalloonVtbl;

    interface IAgentBalloon
    {
        CONST_VTBL struct IAgentBalloonVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentBalloon_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentBalloon_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentBalloon_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentBalloon_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgentBalloon_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgentBalloon_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgentBalloon_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgentBalloon_GetEnabled(This,pbEnabled)	\
    (This)->lpVtbl -> GetEnabled(This,pbEnabled)

#define IAgentBalloon_GetNumLines(This,plcLines)	\
    (This)->lpVtbl -> GetNumLines(This,plcLines)

#define IAgentBalloon_GetNumCharsPerLine(This,plCharsPerLine)	\
    (This)->lpVtbl -> GetNumCharsPerLine(This,plCharsPerLine)

#define IAgentBalloon_GetFontName(This,pbszFontName)	\
    (This)->lpVtbl -> GetFontName(This,pbszFontName)

#define IAgentBalloon_GetFontSize(This,plFontSize)	\
    (This)->lpVtbl -> GetFontSize(This,plFontSize)

#define IAgentBalloon_GetFontBold(This,pbFontBold)	\
    (This)->lpVtbl -> GetFontBold(This,pbFontBold)

#define IAgentBalloon_GetFontItalic(This,pbFontItalic)	\
    (This)->lpVtbl -> GetFontItalic(This,pbFontItalic)

#define IAgentBalloon_GetFontStrikethru(This,pbFontStrikethru)	\
    (This)->lpVtbl -> GetFontStrikethru(This,pbFontStrikethru)

#define IAgentBalloon_GetFontUnderline(This,pbFontUnderline)	\
    (This)->lpVtbl -> GetFontUnderline(This,pbFontUnderline)

#define IAgentBalloon_GetForeColor(This,plFGColor)	\
    (This)->lpVtbl -> GetForeColor(This,plFGColor)

#define IAgentBalloon_GetBackColor(This,plBGColor)	\
    (This)->lpVtbl -> GetBackColor(This,plBGColor)

#define IAgentBalloon_GetBorderColor(This,plBorderColor)	\
    (This)->lpVtbl -> GetBorderColor(This,plBorderColor)

#define IAgentBalloon_SetVisible(This,bVisible)	\
    (This)->lpVtbl -> SetVisible(This,bVisible)

#define IAgentBalloon_GetVisible(This,pbVisible)	\
    (This)->lpVtbl -> GetVisible(This,pbVisible)

#define IAgentBalloon_SetFontName(This,bszFontName)	\
    (This)->lpVtbl -> SetFontName(This,bszFontName)

#define IAgentBalloon_SetFontSize(This,lFontSize)	\
    (This)->lpVtbl -> SetFontSize(This,lFontSize)

#define IAgentBalloon_SetFontCharSet(This,sFontCharSet)	\
    (This)->lpVtbl -> SetFontCharSet(This,sFontCharSet)

#define IAgentBalloon_GetFontCharSet(This,psFontCharSet)	\
    (This)->lpVtbl -> GetFontCharSet(This,psFontCharSet)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAgentBalloon_GetEnabled_Proxy( 
    IAgentBalloon __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pbEnabled);


void __RPC_STUB IAgentBalloon_GetEnabled_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentBalloon_GetNumLines_Proxy( 
    IAgentBalloon __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plcLines);


void __RPC_STUB IAgentBalloon_GetNumLines_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentBalloon_GetNumCharsPerLine_Proxy( 
    IAgentBalloon __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plCharsPerLine);


void __RPC_STUB IAgentBalloon_GetNumCharsPerLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentBalloon_GetFontName_Proxy( 
    IAgentBalloon __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbszFontName);


void __RPC_STUB IAgentBalloon_GetFontName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentBalloon_GetFontSize_Proxy( 
    IAgentBalloon __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plFontSize);


void __RPC_STUB IAgentBalloon_GetFontSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentBalloon_GetFontBold_Proxy( 
    IAgentBalloon __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pbFontBold);


void __RPC_STUB IAgentBalloon_GetFontBold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentBalloon_GetFontItalic_Proxy( 
    IAgentBalloon __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pbFontItalic);


void __RPC_STUB IAgentBalloon_GetFontItalic_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentBalloon_GetFontStrikethru_Proxy( 
    IAgentBalloon __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pbFontStrikethru);


void __RPC_STUB IAgentBalloon_GetFontStrikethru_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentBalloon_GetFontUnderline_Proxy( 
    IAgentBalloon __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pbFontUnderline);


void __RPC_STUB IAgentBalloon_GetFontUnderline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentBalloon_GetForeColor_Proxy( 
    IAgentBalloon __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plFGColor);


void __RPC_STUB IAgentBalloon_GetForeColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentBalloon_GetBackColor_Proxy( 
    IAgentBalloon __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plBGColor);


void __RPC_STUB IAgentBalloon_GetBackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentBalloon_GetBorderColor_Proxy( 
    IAgentBalloon __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plBorderColor);


void __RPC_STUB IAgentBalloon_GetBorderColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentBalloon_SetVisible_Proxy( 
    IAgentBalloon __RPC_FAR * This,
    /* [in] */ long bVisible);


void __RPC_STUB IAgentBalloon_SetVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentBalloon_GetVisible_Proxy( 
    IAgentBalloon __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pbVisible);


void __RPC_STUB IAgentBalloon_GetVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentBalloon_SetFontName_Proxy( 
    IAgentBalloon __RPC_FAR * This,
    /* [in] */ BSTR bszFontName);


void __RPC_STUB IAgentBalloon_SetFontName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentBalloon_SetFontSize_Proxy( 
    IAgentBalloon __RPC_FAR * This,
    /* [in] */ long lFontSize);


void __RPC_STUB IAgentBalloon_SetFontSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentBalloon_SetFontCharSet_Proxy( 
    IAgentBalloon __RPC_FAR * This,
    /* [in] */ short sFontCharSet);


void __RPC_STUB IAgentBalloon_SetFontCharSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentBalloon_GetFontCharSet_Proxy( 
    IAgentBalloon __RPC_FAR * This,
    /* [out] */ short __RPC_FAR *psFontCharSet);


void __RPC_STUB IAgentBalloon_GetFontCharSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentBalloon_INTERFACE_DEFINED__ */


#ifndef __IAgentCharacter_INTERFACE_DEFINED__
#define __IAgentCharacter_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentCharacter
 * at Wed Aug 13 21:04:17 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAgentCharacter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("A7B93C8F-7B81-11D0-AC5F-00C04FD97575")
    IAgentCharacter : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetVisible( 
            /* [out] */ long __RPC_FAR *pbVisible) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPosition( 
            /* [in] */ long lLeft,
            /* [in] */ long lTop) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPosition( 
            /* [out] */ long __RPC_FAR *plLeft,
            /* [out] */ long __RPC_FAR *plTop) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSize( 
            /* [in] */ long lWidth,
            /* [in] */ long lHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSize( 
            /* [out] */ long __RPC_FAR *plWidth,
            /* [out] */ long __RPC_FAR *plHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetName( 
            /* [out] */ BSTR __RPC_FAR *pbszName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDescription( 
            /* [out] */ BSTR __RPC_FAR *pbszDescription) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTTSSpeed( 
            /* [out] */ long __RPC_FAR *pdwSpeed) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTTSPitch( 
            /* [out] */ short __RPC_FAR *pwPitch) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Activate( 
            /* [in] */ short sState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetIdleOn( 
            /* [in] */ long bOn) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIdleOn( 
            /* [out] */ long __RPC_FAR *pbOn) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Prepare( 
            /* [in] */ long dwType,
            /* [in] */ BSTR bszName,
            /* [in] */ long bQueue,
            /* [out] */ long __RPC_FAR *pdwReqID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Play( 
            /* [in] */ BSTR bszAnimation,
            /* [out] */ long __RPC_FAR *pdwReqID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stop( 
            /* [in] */ long dwReqID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StopAll( 
            /* [in] */ long lTypes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Wait( 
            /* [in] */ long dwReqID,
            /* [out] */ long __RPC_FAR *pdwReqID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Interrupt( 
            /* [in] */ long dwReqID,
            /* [out] */ long __RPC_FAR *pdwReqID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Show( 
            /* [in] */ long bFast,
            /* [out] */ long __RPC_FAR *pdwReqID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Hide( 
            /* [in] */ long bFast,
            /* [out] */ long __RPC_FAR *pdwReqID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Speak( 
            /* [in] */ BSTR bszText,
            /* [in] */ BSTR bszUrl,
            /* [out] */ long __RPC_FAR *pdwReqID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MoveTo( 
            /* [in] */ short x,
            /* [in] */ short y,
            /* [in] */ long lSpeed,
            /* [out] */ long __RPC_FAR *pdwReqID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GestureAt( 
            /* [in] */ short x,
            /* [in] */ short y,
            /* [out] */ long __RPC_FAR *pdwReqID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMoveCause( 
            /* [out] */ long __RPC_FAR *pdwCause) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVisibilityCause( 
            /* [out] */ long __RPC_FAR *pdwCause) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HasOtherClients( 
            /* [out] */ long __RPC_FAR *pbHasOtherClients) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSoundEffectsOn( 
            /* [in] */ long bOn) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSoundEffectsOn( 
            /* [out] */ long __RPC_FAR *pbOn) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetName( 
            /* [in] */ BSTR bszName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDescription( 
            /* [in] */ BSTR bszDescription) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetExtraData( 
            /* [out] */ BSTR __RPC_FAR *pbszExtraData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentCharacterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentCharacter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentCharacter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentCharacter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgentCharacter __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgentCharacter __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgentCharacter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgentCharacter __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVisible )( 
            IAgentCharacter __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pbVisible);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPosition )( 
            IAgentCharacter __RPC_FAR * This,
            /* [in] */ long lLeft,
            /* [in] */ long lTop);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPosition )( 
            IAgentCharacter __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plLeft,
            /* [out] */ long __RPC_FAR *plTop);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSize )( 
            IAgentCharacter __RPC_FAR * This,
            /* [in] */ long lWidth,
            /* [in] */ long lHeight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSize )( 
            IAgentCharacter __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *plWidth,
            /* [out] */ long __RPC_FAR *plHeight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            IAgentCharacter __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbszName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDescription )( 
            IAgentCharacter __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbszDescription);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTTSSpeed )( 
            IAgentCharacter __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pdwSpeed);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTTSPitch )( 
            IAgentCharacter __RPC_FAR * This,
            /* [out] */ short __RPC_FAR *pwPitch);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Activate )( 
            IAgentCharacter __RPC_FAR * This,
            /* [in] */ short sState);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetIdleOn )( 
            IAgentCharacter __RPC_FAR * This,
            /* [in] */ long bOn);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIdleOn )( 
            IAgentCharacter __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pbOn);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Prepare )( 
            IAgentCharacter __RPC_FAR * This,
            /* [in] */ long dwType,
            /* [in] */ BSTR bszName,
            /* [in] */ long bQueue,
            /* [out] */ long __RPC_FAR *pdwReqID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Play )( 
            IAgentCharacter __RPC_FAR * This,
            /* [in] */ BSTR bszAnimation,
            /* [out] */ long __RPC_FAR *pdwReqID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IAgentCharacter __RPC_FAR * This,
            /* [in] */ long dwReqID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopAll )( 
            IAgentCharacter __RPC_FAR * This,
            /* [in] */ long lTypes);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Wait )( 
            IAgentCharacter __RPC_FAR * This,
            /* [in] */ long dwReqID,
            /* [out] */ long __RPC_FAR *pdwReqID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Interrupt )( 
            IAgentCharacter __RPC_FAR * This,
            /* [in] */ long dwReqID,
            /* [out] */ long __RPC_FAR *pdwReqID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Show )( 
            IAgentCharacter __RPC_FAR * This,
            /* [in] */ long bFast,
            /* [out] */ long __RPC_FAR *pdwReqID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Hide )( 
            IAgentCharacter __RPC_FAR * This,
            /* [in] */ long bFast,
            /* [out] */ long __RPC_FAR *pdwReqID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Speak )( 
            IAgentCharacter __RPC_FAR * This,
            /* [in] */ BSTR bszText,
            /* [in] */ BSTR bszUrl,
            /* [out] */ long __RPC_FAR *pdwReqID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveTo )( 
            IAgentCharacter __RPC_FAR * This,
            /* [in] */ short x,
            /* [in] */ short y,
            /* [in] */ long lSpeed,
            /* [out] */ long __RPC_FAR *pdwReqID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GestureAt )( 
            IAgentCharacter __RPC_FAR * This,
            /* [in] */ short x,
            /* [in] */ short y,
            /* [out] */ long __RPC_FAR *pdwReqID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMoveCause )( 
            IAgentCharacter __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pdwCause);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVisibilityCause )( 
            IAgentCharacter __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pdwCause);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HasOtherClients )( 
            IAgentCharacter __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pbHasOtherClients);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSoundEffectsOn )( 
            IAgentCharacter __RPC_FAR * This,
            /* [in] */ long bOn);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSoundEffectsOn )( 
            IAgentCharacter __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pbOn);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetName )( 
            IAgentCharacter __RPC_FAR * This,
            /* [in] */ BSTR bszName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDescription )( 
            IAgentCharacter __RPC_FAR * This,
            /* [in] */ BSTR bszDescription);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetExtraData )( 
            IAgentCharacter __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbszExtraData);
        
        END_INTERFACE
    } IAgentCharacterVtbl;

    interface IAgentCharacter
    {
        CONST_VTBL struct IAgentCharacterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentCharacter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentCharacter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentCharacter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentCharacter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgentCharacter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgentCharacter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgentCharacter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgentCharacter_GetVisible(This,pbVisible)	\
    (This)->lpVtbl -> GetVisible(This,pbVisible)

#define IAgentCharacter_SetPosition(This,lLeft,lTop)	\
    (This)->lpVtbl -> SetPosition(This,lLeft,lTop)

#define IAgentCharacter_GetPosition(This,plLeft,plTop)	\
    (This)->lpVtbl -> GetPosition(This,plLeft,plTop)

#define IAgentCharacter_SetSize(This,lWidth,lHeight)	\
    (This)->lpVtbl -> SetSize(This,lWidth,lHeight)

#define IAgentCharacter_GetSize(This,plWidth,plHeight)	\
    (This)->lpVtbl -> GetSize(This,plWidth,plHeight)

#define IAgentCharacter_GetName(This,pbszName)	\
    (This)->lpVtbl -> GetName(This,pbszName)

#define IAgentCharacter_GetDescription(This,pbszDescription)	\
    (This)->lpVtbl -> GetDescription(This,pbszDescription)

#define IAgentCharacter_GetTTSSpeed(This,pdwSpeed)	\
    (This)->lpVtbl -> GetTTSSpeed(This,pdwSpeed)

#define IAgentCharacter_GetTTSPitch(This,pwPitch)	\
    (This)->lpVtbl -> GetTTSPitch(This,pwPitch)

#define IAgentCharacter_Activate(This,sState)	\
    (This)->lpVtbl -> Activate(This,sState)

#define IAgentCharacter_SetIdleOn(This,bOn)	\
    (This)->lpVtbl -> SetIdleOn(This,bOn)

#define IAgentCharacter_GetIdleOn(This,pbOn)	\
    (This)->lpVtbl -> GetIdleOn(This,pbOn)

#define IAgentCharacter_Prepare(This,dwType,bszName,bQueue,pdwReqID)	\
    (This)->lpVtbl -> Prepare(This,dwType,bszName,bQueue,pdwReqID)

#define IAgentCharacter_Play(This,bszAnimation,pdwReqID)	\
    (This)->lpVtbl -> Play(This,bszAnimation,pdwReqID)

#define IAgentCharacter_Stop(This,dwReqID)	\
    (This)->lpVtbl -> Stop(This,dwReqID)

#define IAgentCharacter_StopAll(This,lTypes)	\
    (This)->lpVtbl -> StopAll(This,lTypes)

#define IAgentCharacter_Wait(This,dwReqID,pdwReqID)	\
    (This)->lpVtbl -> Wait(This,dwReqID,pdwReqID)

#define IAgentCharacter_Interrupt(This,dwReqID,pdwReqID)	\
    (This)->lpVtbl -> Interrupt(This,dwReqID,pdwReqID)

#define IAgentCharacter_Show(This,bFast,pdwReqID)	\
    (This)->lpVtbl -> Show(This,bFast,pdwReqID)

#define IAgentCharacter_Hide(This,bFast,pdwReqID)	\
    (This)->lpVtbl -> Hide(This,bFast,pdwReqID)

#define IAgentCharacter_Speak(This,bszText,bszUrl,pdwReqID)	\
    (This)->lpVtbl -> Speak(This,bszText,bszUrl,pdwReqID)

#define IAgentCharacter_MoveTo(This,x,y,lSpeed,pdwReqID)	\
    (This)->lpVtbl -> MoveTo(This,x,y,lSpeed,pdwReqID)

#define IAgentCharacter_GestureAt(This,x,y,pdwReqID)	\
    (This)->lpVtbl -> GestureAt(This,x,y,pdwReqID)

#define IAgentCharacter_GetMoveCause(This,pdwCause)	\
    (This)->lpVtbl -> GetMoveCause(This,pdwCause)

#define IAgentCharacter_GetVisibilityCause(This,pdwCause)	\
    (This)->lpVtbl -> GetVisibilityCause(This,pdwCause)

#define IAgentCharacter_HasOtherClients(This,pbHasOtherClients)	\
    (This)->lpVtbl -> HasOtherClients(This,pbHasOtherClients)

#define IAgentCharacter_SetSoundEffectsOn(This,bOn)	\
    (This)->lpVtbl -> SetSoundEffectsOn(This,bOn)

#define IAgentCharacter_GetSoundEffectsOn(This,pbOn)	\
    (This)->lpVtbl -> GetSoundEffectsOn(This,pbOn)

#define IAgentCharacter_SetName(This,bszName)	\
    (This)->lpVtbl -> SetName(This,bszName)

#define IAgentCharacter_SetDescription(This,bszDescription)	\
    (This)->lpVtbl -> SetDescription(This,bszDescription)

#define IAgentCharacter_GetExtraData(This,pbszExtraData)	\
    (This)->lpVtbl -> GetExtraData(This,pbszExtraData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAgentCharacter_GetVisible_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pbVisible);


void __RPC_STUB IAgentCharacter_GetVisible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_SetPosition_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [in] */ long lLeft,
    /* [in] */ long lTop);


void __RPC_STUB IAgentCharacter_SetPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_GetPosition_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plLeft,
    /* [out] */ long __RPC_FAR *plTop);


void __RPC_STUB IAgentCharacter_GetPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_SetSize_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [in] */ long lWidth,
    /* [in] */ long lHeight);


void __RPC_STUB IAgentCharacter_SetSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_GetSize_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *plWidth,
    /* [out] */ long __RPC_FAR *plHeight);


void __RPC_STUB IAgentCharacter_GetSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_GetName_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbszName);


void __RPC_STUB IAgentCharacter_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_GetDescription_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbszDescription);


void __RPC_STUB IAgentCharacter_GetDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_GetTTSSpeed_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pdwSpeed);


void __RPC_STUB IAgentCharacter_GetTTSSpeed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_GetTTSPitch_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [out] */ short __RPC_FAR *pwPitch);


void __RPC_STUB IAgentCharacter_GetTTSPitch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_Activate_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [in] */ short sState);


void __RPC_STUB IAgentCharacter_Activate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_SetIdleOn_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [in] */ long bOn);


void __RPC_STUB IAgentCharacter_SetIdleOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_GetIdleOn_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pbOn);


void __RPC_STUB IAgentCharacter_GetIdleOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_Prepare_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [in] */ long dwType,
    /* [in] */ BSTR bszName,
    /* [in] */ long bQueue,
    /* [out] */ long __RPC_FAR *pdwReqID);


void __RPC_STUB IAgentCharacter_Prepare_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_Play_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [in] */ BSTR bszAnimation,
    /* [out] */ long __RPC_FAR *pdwReqID);


void __RPC_STUB IAgentCharacter_Play_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_Stop_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [in] */ long dwReqID);


void __RPC_STUB IAgentCharacter_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_StopAll_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [in] */ long lTypes);


void __RPC_STUB IAgentCharacter_StopAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_Wait_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [in] */ long dwReqID,
    /* [out] */ long __RPC_FAR *pdwReqID);


void __RPC_STUB IAgentCharacter_Wait_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_Interrupt_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [in] */ long dwReqID,
    /* [out] */ long __RPC_FAR *pdwReqID);


void __RPC_STUB IAgentCharacter_Interrupt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_Show_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [in] */ long bFast,
    /* [out] */ long __RPC_FAR *pdwReqID);


void __RPC_STUB IAgentCharacter_Show_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_Hide_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [in] */ long bFast,
    /* [out] */ long __RPC_FAR *pdwReqID);


void __RPC_STUB IAgentCharacter_Hide_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_Speak_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [in] */ BSTR bszText,
    /* [in] */ BSTR bszUrl,
    /* [out] */ long __RPC_FAR *pdwReqID);


void __RPC_STUB IAgentCharacter_Speak_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_MoveTo_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [in] */ short x,
    /* [in] */ short y,
    /* [in] */ long lSpeed,
    /* [out] */ long __RPC_FAR *pdwReqID);


void __RPC_STUB IAgentCharacter_MoveTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_GestureAt_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [in] */ short x,
    /* [in] */ short y,
    /* [out] */ long __RPC_FAR *pdwReqID);


void __RPC_STUB IAgentCharacter_GestureAt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_GetMoveCause_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pdwCause);


void __RPC_STUB IAgentCharacter_GetMoveCause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_GetVisibilityCause_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pdwCause);


void __RPC_STUB IAgentCharacter_GetVisibilityCause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_HasOtherClients_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pbHasOtherClients);


void __RPC_STUB IAgentCharacter_HasOtherClients_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_SetSoundEffectsOn_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [in] */ long bOn);


void __RPC_STUB IAgentCharacter_SetSoundEffectsOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_GetSoundEffectsOn_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pbOn);


void __RPC_STUB IAgentCharacter_GetSoundEffectsOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_SetName_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [in] */ BSTR bszName);


void __RPC_STUB IAgentCharacter_SetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_SetDescription_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [in] */ BSTR bszDescription);


void __RPC_STUB IAgentCharacter_SetDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentCharacter_GetExtraData_Proxy( 
    IAgentCharacter __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbszExtraData);


void __RPC_STUB IAgentCharacter_GetExtraData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentCharacter_INTERFACE_DEFINED__ */


#ifndef __IAgent_INTERFACE_DEFINED__
#define __IAgent_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgent
 * at Wed Aug 13 21:04:17 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAgent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("A7B93C91-7B81-11D0-AC5F-00C04FD97575")
    IAgent : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ VARIANT vLoadKey,
            /* [out] */ long __RPC_FAR *pdwCharID,
            /* [out] */ long __RPC_FAR *pdwReqID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Unload( 
            /* [in] */ long dwCharID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Register( 
            /* [in] */ IUnknown __RPC_FAR *punkNotifySink,
            /* [out] */ long __RPC_FAR *pdwSinkID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Unregister( 
            /* [in] */ long dwSinkID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCharacter( 
            /* [in] */ long dwCharID,
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppunkCharacter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSuspended( 
            /* [out] */ long __RPC_FAR *pbSuspended) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgent __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgent __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgent __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Load )( 
            IAgent __RPC_FAR * This,
            /* [in] */ VARIANT vLoadKey,
            /* [out] */ long __RPC_FAR *pdwCharID,
            /* [out] */ long __RPC_FAR *pdwReqID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Unload )( 
            IAgent __RPC_FAR * This,
            /* [in] */ long dwCharID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Register )( 
            IAgent __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *punkNotifySink,
            /* [out] */ long __RPC_FAR *pdwSinkID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Unregister )( 
            IAgent __RPC_FAR * This,
            /* [in] */ long dwSinkID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCharacter )( 
            IAgent __RPC_FAR * This,
            /* [in] */ long dwCharID,
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppunkCharacter);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSuspended )( 
            IAgent __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pbSuspended);
        
        END_INTERFACE
    } IAgentVtbl;

    interface IAgent
    {
        CONST_VTBL struct IAgentVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgent_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgent_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgent_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgent_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgent_Load(This,vLoadKey,pdwCharID,pdwReqID)	\
    (This)->lpVtbl -> Load(This,vLoadKey,pdwCharID,pdwReqID)

#define IAgent_Unload(This,dwCharID)	\
    (This)->lpVtbl -> Unload(This,dwCharID)

#define IAgent_Register(This,punkNotifySink,pdwSinkID)	\
    (This)->lpVtbl -> Register(This,punkNotifySink,pdwSinkID)

#define IAgent_Unregister(This,dwSinkID)	\
    (This)->lpVtbl -> Unregister(This,dwSinkID)

#define IAgent_GetCharacter(This,dwCharID,ppunkCharacter)	\
    (This)->lpVtbl -> GetCharacter(This,dwCharID,ppunkCharacter)

#define IAgent_GetSuspended(This,pbSuspended)	\
    (This)->lpVtbl -> GetSuspended(This,pbSuspended)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAgent_Load_Proxy( 
    IAgent __RPC_FAR * This,
    /* [in] */ VARIANT vLoadKey,
    /* [out] */ long __RPC_FAR *pdwCharID,
    /* [out] */ long __RPC_FAR *pdwReqID);


void __RPC_STUB IAgent_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgent_Unload_Proxy( 
    IAgent __RPC_FAR * This,
    /* [in] */ long dwCharID);


void __RPC_STUB IAgent_Unload_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgent_Register_Proxy( 
    IAgent __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *punkNotifySink,
    /* [out] */ long __RPC_FAR *pdwSinkID);


void __RPC_STUB IAgent_Register_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgent_Unregister_Proxy( 
    IAgent __RPC_FAR * This,
    /* [in] */ long dwSinkID);


void __RPC_STUB IAgent_Unregister_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgent_GetCharacter_Proxy( 
    IAgent __RPC_FAR * This,
    /* [in] */ long dwCharID,
    /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppunkCharacter);


void __RPC_STUB IAgent_GetCharacter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgent_GetSuspended_Proxy( 
    IAgent __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pbSuspended);


void __RPC_STUB IAgent_GetSuspended_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgent_INTERFACE_DEFINED__ */


#ifndef __IAgentNotifySink_INTERFACE_DEFINED__
#define __IAgentNotifySink_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentNotifySink
 * at Wed Aug 13 21:04:17 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][dual][uuid][object] */ 



EXTERN_C const IID IID_IAgentNotifySink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("00D18159-8466-11D0-AC63-00C04FD97575")
    IAgentNotifySink : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Command( 
            /* [in] */ long dwCommandID,
            /* [in] */ IUnknown __RPC_FAR *punkUserInput) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ActivateInputState( 
            /* [in] */ long dwCharID,
            /* [in] */ long bActivated) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Restart( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Shutdown( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE VisibleState( 
            /* [in] */ long dwCharID,
            /* [in] */ long bVisible,
            /* [in] */ long dwCause) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Click( 
            /* [in] */ long dwCharID,
            /* [in] */ short fwKeys,
            /* [in] */ long x,
            /* [in] */ long y) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DblClick( 
            /* [in] */ long dwCharID,
            /* [in] */ short fwKeys,
            /* [in] */ long x,
            /* [in] */ long y) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DragStart( 
            /* [in] */ long dwCharID,
            /* [in] */ short fwKeys,
            /* [in] */ long x,
            /* [in] */ long y) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DragComplete( 
            /* [in] */ long dwCharID,
            /* [in] */ short fwKeys,
            /* [in] */ long x,
            /* [in] */ long y) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RequestStart( 
            /* [in] */ long dwRequestID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RequestComplete( 
            /* [in] */ long dwRequestID,
            /* [in] */ long hrStatus) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BookMark( 
            /* [in] */ long dwBookMarkID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Idle( 
            /* [in] */ long dwCharID,
            /* [in] */ long bStart) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ long dwCharID,
            /* [in] */ long x,
            /* [in] */ long y,
            /* [in] */ long dwCause) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Size( 
            /* [in] */ long dwCharID,
            /* [in] */ long lWidth,
            /* [in] */ long lHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BalloonVisibleState( 
            /* [in] */ long dwCharID,
            /* [in] */ long bVisible) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentNotifySinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentNotifySink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentNotifySink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentNotifySink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAgentNotifySink __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAgentNotifySink __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAgentNotifySink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAgentNotifySink __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Command )( 
            IAgentNotifySink __RPC_FAR * This,
            /* [in] */ long dwCommandID,
            /* [in] */ IUnknown __RPC_FAR *punkUserInput);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ActivateInputState )( 
            IAgentNotifySink __RPC_FAR * This,
            /* [in] */ long dwCharID,
            /* [in] */ long bActivated);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Restart )( 
            IAgentNotifySink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Shutdown )( 
            IAgentNotifySink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VisibleState )( 
            IAgentNotifySink __RPC_FAR * This,
            /* [in] */ long dwCharID,
            /* [in] */ long bVisible,
            /* [in] */ long dwCause);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Click )( 
            IAgentNotifySink __RPC_FAR * This,
            /* [in] */ long dwCharID,
            /* [in] */ short fwKeys,
            /* [in] */ long x,
            /* [in] */ long y);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DblClick )( 
            IAgentNotifySink __RPC_FAR * This,
            /* [in] */ long dwCharID,
            /* [in] */ short fwKeys,
            /* [in] */ long x,
            /* [in] */ long y);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DragStart )( 
            IAgentNotifySink __RPC_FAR * This,
            /* [in] */ long dwCharID,
            /* [in] */ short fwKeys,
            /* [in] */ long x,
            /* [in] */ long y);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DragComplete )( 
            IAgentNotifySink __RPC_FAR * This,
            /* [in] */ long dwCharID,
            /* [in] */ short fwKeys,
            /* [in] */ long x,
            /* [in] */ long y);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestStart )( 
            IAgentNotifySink __RPC_FAR * This,
            /* [in] */ long dwRequestID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestComplete )( 
            IAgentNotifySink __RPC_FAR * This,
            /* [in] */ long dwRequestID,
            /* [in] */ long hrStatus);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BookMark )( 
            IAgentNotifySink __RPC_FAR * This,
            /* [in] */ long dwBookMarkID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Idle )( 
            IAgentNotifySink __RPC_FAR * This,
            /* [in] */ long dwCharID,
            /* [in] */ long bStart);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            IAgentNotifySink __RPC_FAR * This,
            /* [in] */ long dwCharID,
            /* [in] */ long x,
            /* [in] */ long y,
            /* [in] */ long dwCause);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Size )( 
            IAgentNotifySink __RPC_FAR * This,
            /* [in] */ long dwCharID,
            /* [in] */ long lWidth,
            /* [in] */ long lHeight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BalloonVisibleState )( 
            IAgentNotifySink __RPC_FAR * This,
            /* [in] */ long dwCharID,
            /* [in] */ long bVisible);
        
        END_INTERFACE
    } IAgentNotifySinkVtbl;

    interface IAgentNotifySink
    {
        CONST_VTBL struct IAgentNotifySinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentNotifySink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentNotifySink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentNotifySink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentNotifySink_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAgentNotifySink_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAgentNotifySink_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAgentNotifySink_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAgentNotifySink_Command(This,dwCommandID,punkUserInput)	\
    (This)->lpVtbl -> Command(This,dwCommandID,punkUserInput)

#define IAgentNotifySink_ActivateInputState(This,dwCharID,bActivated)	\
    (This)->lpVtbl -> ActivateInputState(This,dwCharID,bActivated)

#define IAgentNotifySink_Restart(This)	\
    (This)->lpVtbl -> Restart(This)

#define IAgentNotifySink_Shutdown(This)	\
    (This)->lpVtbl -> Shutdown(This)

#define IAgentNotifySink_VisibleState(This,dwCharID,bVisible,dwCause)	\
    (This)->lpVtbl -> VisibleState(This,dwCharID,bVisible,dwCause)

#define IAgentNotifySink_Click(This,dwCharID,fwKeys,x,y)	\
    (This)->lpVtbl -> Click(This,dwCharID,fwKeys,x,y)

#define IAgentNotifySink_DblClick(This,dwCharID,fwKeys,x,y)	\
    (This)->lpVtbl -> DblClick(This,dwCharID,fwKeys,x,y)

#define IAgentNotifySink_DragStart(This,dwCharID,fwKeys,x,y)	\
    (This)->lpVtbl -> DragStart(This,dwCharID,fwKeys,x,y)

#define IAgentNotifySink_DragComplete(This,dwCharID,fwKeys,x,y)	\
    (This)->lpVtbl -> DragComplete(This,dwCharID,fwKeys,x,y)

#define IAgentNotifySink_RequestStart(This,dwRequestID)	\
    (This)->lpVtbl -> RequestStart(This,dwRequestID)

#define IAgentNotifySink_RequestComplete(This,dwRequestID,hrStatus)	\
    (This)->lpVtbl -> RequestComplete(This,dwRequestID,hrStatus)

#define IAgentNotifySink_BookMark(This,dwBookMarkID)	\
    (This)->lpVtbl -> BookMark(This,dwBookMarkID)

#define IAgentNotifySink_Idle(This,dwCharID,bStart)	\
    (This)->lpVtbl -> Idle(This,dwCharID,bStart)

#define IAgentNotifySink_Move(This,dwCharID,x,y,dwCause)	\
    (This)->lpVtbl -> Move(This,dwCharID,x,y,dwCause)

#define IAgentNotifySink_Size(This,dwCharID,lWidth,lHeight)	\
    (This)->lpVtbl -> Size(This,dwCharID,lWidth,lHeight)

#define IAgentNotifySink_BalloonVisibleState(This,dwCharID,bVisible)	\
    (This)->lpVtbl -> BalloonVisibleState(This,dwCharID,bVisible)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAgentNotifySink_Command_Proxy( 
    IAgentNotifySink __RPC_FAR * This,
    /* [in] */ long dwCommandID,
    /* [in] */ IUnknown __RPC_FAR *punkUserInput);


void __RPC_STUB IAgentNotifySink_Command_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentNotifySink_ActivateInputState_Proxy( 
    IAgentNotifySink __RPC_FAR * This,
    /* [in] */ long dwCharID,
    /* [in] */ long bActivated);


void __RPC_STUB IAgentNotifySink_ActivateInputState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentNotifySink_Restart_Proxy( 
    IAgentNotifySink __RPC_FAR * This);


void __RPC_STUB IAgentNotifySink_Restart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentNotifySink_Shutdown_Proxy( 
    IAgentNotifySink __RPC_FAR * This);


void __RPC_STUB IAgentNotifySink_Shutdown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentNotifySink_VisibleState_Proxy( 
    IAgentNotifySink __RPC_FAR * This,
    /* [in] */ long dwCharID,
    /* [in] */ long bVisible,
    /* [in] */ long dwCause);


void __RPC_STUB IAgentNotifySink_VisibleState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentNotifySink_Click_Proxy( 
    IAgentNotifySink __RPC_FAR * This,
    /* [in] */ long dwCharID,
    /* [in] */ short fwKeys,
    /* [in] */ long x,
    /* [in] */ long y);


void __RPC_STUB IAgentNotifySink_Click_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentNotifySink_DblClick_Proxy( 
    IAgentNotifySink __RPC_FAR * This,
    /* [in] */ long dwCharID,
    /* [in] */ short fwKeys,
    /* [in] */ long x,
    /* [in] */ long y);


void __RPC_STUB IAgentNotifySink_DblClick_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentNotifySink_DragStart_Proxy( 
    IAgentNotifySink __RPC_FAR * This,
    /* [in] */ long dwCharID,
    /* [in] */ short fwKeys,
    /* [in] */ long x,
    /* [in] */ long y);


void __RPC_STUB IAgentNotifySink_DragStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentNotifySink_DragComplete_Proxy( 
    IAgentNotifySink __RPC_FAR * This,
    /* [in] */ long dwCharID,
    /* [in] */ short fwKeys,
    /* [in] */ long x,
    /* [in] */ long y);


void __RPC_STUB IAgentNotifySink_DragComplete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentNotifySink_RequestStart_Proxy( 
    IAgentNotifySink __RPC_FAR * This,
    /* [in] */ long dwRequestID);


void __RPC_STUB IAgentNotifySink_RequestStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentNotifySink_RequestComplete_Proxy( 
    IAgentNotifySink __RPC_FAR * This,
    /* [in] */ long dwRequestID,
    /* [in] */ long hrStatus);


void __RPC_STUB IAgentNotifySink_RequestComplete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentNotifySink_BookMark_Proxy( 
    IAgentNotifySink __RPC_FAR * This,
    /* [in] */ long dwBookMarkID);


void __RPC_STUB IAgentNotifySink_BookMark_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentNotifySink_Idle_Proxy( 
    IAgentNotifySink __RPC_FAR * This,
    /* [in] */ long dwCharID,
    /* [in] */ long bStart);


void __RPC_STUB IAgentNotifySink_Idle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentNotifySink_Move_Proxy( 
    IAgentNotifySink __RPC_FAR * This,
    /* [in] */ long dwCharID,
    /* [in] */ long x,
    /* [in] */ long y,
    /* [in] */ long dwCause);


void __RPC_STUB IAgentNotifySink_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentNotifySink_Size_Proxy( 
    IAgentNotifySink __RPC_FAR * This,
    /* [in] */ long dwCharID,
    /* [in] */ long lWidth,
    /* [in] */ long lHeight);


void __RPC_STUB IAgentNotifySink_Size_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentNotifySink_BalloonVisibleState_Proxy( 
    IAgentNotifySink __RPC_FAR * This,
    /* [in] */ long dwCharID,
    /* [in] */ long bVisible);


void __RPC_STUB IAgentNotifySink_BalloonVisibleState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentNotifySink_INTERFACE_DEFINED__ */


#ifndef __IAgentPrivateNotifySink_INTERFACE_DEFINED__
#define __IAgentPrivateNotifySink_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IAgentPrivateNotifySink
 * at Wed Aug 13 21:04:17 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][uuid][local][object] */ 



EXTERN_C const IID IID_IAgentPrivateNotifySink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("B741B760-8EA6-11d0-AC6A-00C04FD97575")
    IAgentPrivateNotifySink : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ReleaseAll( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReleaseOne( 
            void __RPC_FAR *pnNotify) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAgentPrivateNotifySinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAgentPrivateNotifySink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAgentPrivateNotifySink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAgentPrivateNotifySink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseAll )( 
            IAgentPrivateNotifySink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseOne )( 
            IAgentPrivateNotifySink __RPC_FAR * This,
            void __RPC_FAR *pnNotify);
        
        END_INTERFACE
    } IAgentPrivateNotifySinkVtbl;

    interface IAgentPrivateNotifySink
    {
        CONST_VTBL struct IAgentPrivateNotifySinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAgentPrivateNotifySink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAgentPrivateNotifySink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAgentPrivateNotifySink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAgentPrivateNotifySink_ReleaseAll(This)	\
    (This)->lpVtbl -> ReleaseAll(This)

#define IAgentPrivateNotifySink_ReleaseOne(This,pnNotify)	\
    (This)->lpVtbl -> ReleaseOne(This,pnNotify)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IAgentPrivateNotifySink_ReleaseAll_Proxy( 
    IAgentPrivateNotifySink __RPC_FAR * This);


void __RPC_STUB IAgentPrivateNotifySink_ReleaseAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IAgentPrivateNotifySink_ReleaseOne_Proxy( 
    IAgentPrivateNotifySink __RPC_FAR * This,
    void __RPC_FAR *pnNotify);


void __RPC_STUB IAgentPrivateNotifySink_ReleaseOne_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAgentPrivateNotifySink_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_AgentServer_0147
 * at Wed Aug 13 21:04:17 1997
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


#define	AGENT_VERSION_MAJOR	( 1 )

#define	AGENT_VERSION_MINOR	( 5 )



extern RPC_IF_HANDLE __MIDL_itf_AgentServer_0147_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AgentServer_0147_v0_0_s_ifspec;


#ifndef __AgentServerObjects_LIBRARY_DEFINED__
#define __AgentServerObjects_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: AgentServerObjects
 * at Wed Aug 13 21:04:17 1997
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 














EXTERN_C const IID LIBID_AgentServerObjects;

#ifdef __cplusplus
EXTERN_C const CLSID CLSID_AgentServer;

class DECLSPEC_UUID("A7B93C92-7B81-11D0-AC5F-00C04FD97575")
AgentServer;
#endif
#endif /* __AgentServerObjects_LIBRARY_DEFINED__ */

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
