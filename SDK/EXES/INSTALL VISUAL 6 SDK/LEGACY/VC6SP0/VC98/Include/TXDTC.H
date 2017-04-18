/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Fri Nov 14 05:07:21 1997
 */
/* Compiler settings for txdtc.idl:
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

#ifndef __txdtc_h__
#define __txdtc_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IXATransLookup_FWD_DEFINED__
#define __IXATransLookup_FWD_DEFINED__
typedef interface IXATransLookup IXATransLookup;
#endif 	/* __IXATransLookup_FWD_DEFINED__ */


#ifndef __IResourceManagerSink_FWD_DEFINED__
#define __IResourceManagerSink_FWD_DEFINED__
typedef interface IResourceManagerSink IResourceManagerSink;
#endif 	/* __IResourceManagerSink_FWD_DEFINED__ */


#ifndef __IResourceManager_FWD_DEFINED__
#define __IResourceManager_FWD_DEFINED__
typedef interface IResourceManager IResourceManager;
#endif 	/* __IResourceManager_FWD_DEFINED__ */


#ifndef __IXAConfig_FWD_DEFINED__
#define __IXAConfig_FWD_DEFINED__
typedef interface IXAConfig IXAConfig;
#endif 	/* __IXAConfig_FWD_DEFINED__ */


#ifndef __IRMHelper_FWD_DEFINED__
#define __IRMHelper_FWD_DEFINED__
typedef interface IRMHelper IRMHelper;
#endif 	/* __IRMHelper_FWD_DEFINED__ */


#ifndef __IXAObtainRMInfo_FWD_DEFINED__
#define __IXAObtainRMInfo_FWD_DEFINED__
typedef interface IXAObtainRMInfo IXAObtainRMInfo;
#endif 	/* __IXAObtainRMInfo_FWD_DEFINED__ */


#ifndef __IXAResourceManager_FWD_DEFINED__
#define __IXAResourceManager_FWD_DEFINED__
typedef interface IXAResourceManager IXAResourceManager;
#endif 	/* __IXAResourceManager_FWD_DEFINED__ */


#ifndef __IXAResourceManagerFactory_FWD_DEFINED__
#define __IXAResourceManagerFactory_FWD_DEFINED__
typedef interface IXAResourceManagerFactory IXAResourceManagerFactory;
#endif 	/* __IXAResourceManagerFactory_FWD_DEFINED__ */


#ifndef __IXATransaction_FWD_DEFINED__
#define __IXATransaction_FWD_DEFINED__
typedef interface IXATransaction IXATransaction;
#endif 	/* __IXATransaction_FWD_DEFINED__ */


#ifndef __IResourceManagerFactory_FWD_DEFINED__
#define __IResourceManagerFactory_FWD_DEFINED__
typedef interface IResourceManagerFactory IResourceManagerFactory;
#endif 	/* __IResourceManagerFactory_FWD_DEFINED__ */


#ifndef __IPrepareInfo_FWD_DEFINED__
#define __IPrepareInfo_FWD_DEFINED__
typedef interface IPrepareInfo IPrepareInfo;
#endif 	/* __IPrepareInfo_FWD_DEFINED__ */


#ifndef __IGetDispenser_FWD_DEFINED__
#define __IGetDispenser_FWD_DEFINED__
typedef interface IGetDispenser IGetDispenser;
#endif 	/* __IGetDispenser_FWD_DEFINED__ */


#ifndef __ITransactionVoterBallotAsync_FWD_DEFINED__
#define __ITransactionVoterBallotAsync_FWD_DEFINED__
typedef interface ITransactionVoterBallotAsync ITransactionVoterBallotAsync;
#endif 	/* __ITransactionVoterBallotAsync_FWD_DEFINED__ */


#ifndef __ITransactionVoterNotifyAsync_FWD_DEFINED__
#define __ITransactionVoterNotifyAsync_FWD_DEFINED__
typedef interface ITransactionVoterNotifyAsync ITransactionVoterNotifyAsync;
#endif 	/* __ITransactionVoterNotifyAsync_FWD_DEFINED__ */


#ifndef __ITransactionVoterFactory_FWD_DEFINED__
#define __ITransactionVoterFactory_FWD_DEFINED__
typedef interface ITransactionVoterFactory ITransactionVoterFactory;
#endif 	/* __ITransactionVoterFactory_FWD_DEFINED__ */


#ifndef __ITransactionTransmitter_FWD_DEFINED__
#define __ITransactionTransmitter_FWD_DEFINED__
typedef interface ITransactionTransmitter ITransactionTransmitter;
#endif 	/* __ITransactionTransmitter_FWD_DEFINED__ */


#ifndef __ITransactionTransmitterFactory_FWD_DEFINED__
#define __ITransactionTransmitterFactory_FWD_DEFINED__
typedef interface ITransactionTransmitterFactory ITransactionTransmitterFactory;
#endif 	/* __ITransactionTransmitterFactory_FWD_DEFINED__ */


#ifndef __ITransactionReceiver_FWD_DEFINED__
#define __ITransactionReceiver_FWD_DEFINED__
typedef interface ITransactionReceiver ITransactionReceiver;
#endif 	/* __ITransactionReceiver_FWD_DEFINED__ */


#ifndef __ITransactionReceiverFactory_FWD_DEFINED__
#define __ITransactionReceiverFactory_FWD_DEFINED__
typedef interface ITransactionReceiverFactory ITransactionReceiverFactory;
#endif 	/* __ITransactionReceiverFactory_FWD_DEFINED__ */


#ifndef __IDtcLuConfigure_FWD_DEFINED__
#define __IDtcLuConfigure_FWD_DEFINED__
typedef interface IDtcLuConfigure IDtcLuConfigure;
#endif 	/* __IDtcLuConfigure_FWD_DEFINED__ */


#ifndef __IDtcLuRecovery_FWD_DEFINED__
#define __IDtcLuRecovery_FWD_DEFINED__
typedef interface IDtcLuRecovery IDtcLuRecovery;
#endif 	/* __IDtcLuRecovery_FWD_DEFINED__ */


#ifndef __IDtcLuRecoveryFactory_FWD_DEFINED__
#define __IDtcLuRecoveryFactory_FWD_DEFINED__
typedef interface IDtcLuRecoveryFactory IDtcLuRecoveryFactory;
#endif 	/* __IDtcLuRecoveryFactory_FWD_DEFINED__ */


#ifndef __IDtcLuRecoveryInitiatedByDtcTransWork_FWD_DEFINED__
#define __IDtcLuRecoveryInitiatedByDtcTransWork_FWD_DEFINED__
typedef interface IDtcLuRecoveryInitiatedByDtcTransWork IDtcLuRecoveryInitiatedByDtcTransWork;
#endif 	/* __IDtcLuRecoveryInitiatedByDtcTransWork_FWD_DEFINED__ */


#ifndef __IDtcLuRecoveryInitiatedByDtcStatusWork_FWD_DEFINED__
#define __IDtcLuRecoveryInitiatedByDtcStatusWork_FWD_DEFINED__
typedef interface IDtcLuRecoveryInitiatedByDtcStatusWork IDtcLuRecoveryInitiatedByDtcStatusWork;
#endif 	/* __IDtcLuRecoveryInitiatedByDtcStatusWork_FWD_DEFINED__ */


#ifndef __IDtcLuRecoveryInitiatedByDtc_FWD_DEFINED__
#define __IDtcLuRecoveryInitiatedByDtc_FWD_DEFINED__
typedef interface IDtcLuRecoveryInitiatedByDtc IDtcLuRecoveryInitiatedByDtc;
#endif 	/* __IDtcLuRecoveryInitiatedByDtc_FWD_DEFINED__ */


#ifndef __IDtcLuRecoveryInitiatedByLuWork_FWD_DEFINED__
#define __IDtcLuRecoveryInitiatedByLuWork_FWD_DEFINED__
typedef interface IDtcLuRecoveryInitiatedByLuWork IDtcLuRecoveryInitiatedByLuWork;
#endif 	/* __IDtcLuRecoveryInitiatedByLuWork_FWD_DEFINED__ */


#ifndef __IDtcLuRecoveryInitiatedByLu_FWD_DEFINED__
#define __IDtcLuRecoveryInitiatedByLu_FWD_DEFINED__
typedef interface IDtcLuRecoveryInitiatedByLu IDtcLuRecoveryInitiatedByLu;
#endif 	/* __IDtcLuRecoveryInitiatedByLu_FWD_DEFINED__ */


#ifndef __IDtcLuRmEnlistment_FWD_DEFINED__
#define __IDtcLuRmEnlistment_FWD_DEFINED__
typedef interface IDtcLuRmEnlistment IDtcLuRmEnlistment;
#endif 	/* __IDtcLuRmEnlistment_FWD_DEFINED__ */


#ifndef __IDtcLuRmEnlistmentSink_FWD_DEFINED__
#define __IDtcLuRmEnlistmentSink_FWD_DEFINED__
typedef interface IDtcLuRmEnlistmentSink IDtcLuRmEnlistmentSink;
#endif 	/* __IDtcLuRmEnlistmentSink_FWD_DEFINED__ */


#ifndef __IDtcLuRmEnlistmentFactory_FWD_DEFINED__
#define __IDtcLuRmEnlistmentFactory_FWD_DEFINED__
typedef interface IDtcLuRmEnlistmentFactory IDtcLuRmEnlistmentFactory;
#endif 	/* __IDtcLuRmEnlistmentFactory_FWD_DEFINED__ */


#ifndef __IDtcLuSubordinateDtc_FWD_DEFINED__
#define __IDtcLuSubordinateDtc_FWD_DEFINED__
typedef interface IDtcLuSubordinateDtc IDtcLuSubordinateDtc;
#endif 	/* __IDtcLuSubordinateDtc_FWD_DEFINED__ */


#ifndef __IDtcLuSubordinateDtcSink_FWD_DEFINED__
#define __IDtcLuSubordinateDtcSink_FWD_DEFINED__
typedef interface IDtcLuSubordinateDtcSink IDtcLuSubordinateDtcSink;
#endif 	/* __IDtcLuSubordinateDtcSink_FWD_DEFINED__ */


#ifndef __IDtcLuSubordinateDtcFactory_FWD_DEFINED__
#define __IDtcLuSubordinateDtcFactory_FWD_DEFINED__
typedef interface IDtcLuSubordinateDtcFactory IDtcLuSubordinateDtcFactory;
#endif 	/* __IDtcLuSubordinateDtcFactory_FWD_DEFINED__ */


/* header files for imported files */
#include "txcoord.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_txdtc_0000
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


#define XACTTOMSG(dwXact) (dwXact-0x00040000+0x40000000)
typedef 
enum XACT_DTC_CONSTANTS
    {	XACT_E_CONNECTION_REQUEST_DENIED	= 0x8004d100L,
	XACT_E_TOOMANY_ENLISTMENTS	= 0x8004d101L,
	XACT_E_DUPLICATE_GUID	= 0x8004d102L,
	XACT_E_NOTSINGLEPHASE	= 0x8004d103L,
	XACT_E_RECOVERYALREADYDONE	= 0x8004d104L,
	XACT_E_PROTOCOL	= 0x8004d105L,
	XACT_E_RM_FAILURE	= 0x8004d106L,
	XACT_E_RECOVERY_FAILED	= 0x8004d107L,
	XACT_E_LU_NOT_FOUND	= 0x8004d108L,
	XACT_E_DUPLICATE_LU	= 0x8004d109L,
	XACT_E_LU_NOT_CONNECTED	= 0x8004d10aL,
	XACT_E_DUPLICATE_TRANSID	= 0x8004d10bL,
	XACT_E_LU_BUSY	= 0x8004d10cL,
	XACT_E_LU_NO_RECOVERY_PROCESS	= 0x8004d10dL,
	XACT_E_LU_DOWN	= 0x8004d10eL,
	XACT_E_LU_RECOVERING	= 0x8004d10fL,
	XACT_E_LU_RECOVERY_MISMATCH	= 0x8004d110L,
	XACT_S_NONOTIFY	= 0x4d100L,
	XACT_OK_NONOTIFY	= 0x4d101L,
	dwUSER_MS_SQLSERVER	= 0xffff
    }	XACT_DTC_CONSTANTS;



extern RPC_IF_HANDLE __MIDL_itf_txdtc_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_txdtc_0000_v0_0_s_ifspec;

#ifndef __IXATransLookup_INTERFACE_DEFINED__
#define __IXATransLookup_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IXATransLookup
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][object][uuid] */ 



EXTERN_C const IID IID_IXATransLookup;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("F3B1F131-EEDA-11ce-AED4-00AA0051E2C4")
    IXATransLookup : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Lookup( 
            /* [out] */ ITransaction __RPC_FAR *__RPC_FAR *ppTransaction) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXATransLookupVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXATransLookup __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXATransLookup __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXATransLookup __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Lookup )( 
            IXATransLookup __RPC_FAR * This,
            /* [out] */ ITransaction __RPC_FAR *__RPC_FAR *ppTransaction);
        
        END_INTERFACE
    } IXATransLookupVtbl;

    interface IXATransLookup
    {
        CONST_VTBL struct IXATransLookupVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXATransLookup_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXATransLookup_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXATransLookup_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXATransLookup_Lookup(This,ppTransaction)	\
    (This)->lpVtbl -> Lookup(This,ppTransaction)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IXATransLookup_Lookup_Proxy( 
    IXATransLookup __RPC_FAR * This,
    /* [out] */ ITransaction __RPC_FAR *__RPC_FAR *ppTransaction);


void __RPC_STUB IXATransLookup_Lookup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXATransLookup_INTERFACE_DEFINED__ */


#ifndef __IResourceManagerSink_INTERFACE_DEFINED__
#define __IResourceManagerSink_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IResourceManagerSink
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][object][uuid] */ 



EXTERN_C const IID IID_IResourceManagerSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0D563181-DEFB-11ce-AED1-00AA0051E2C4")
    IResourceManagerSink : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE TMDown( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IResourceManagerSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IResourceManagerSink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IResourceManagerSink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IResourceManagerSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TMDown )( 
            IResourceManagerSink __RPC_FAR * This);
        
        END_INTERFACE
    } IResourceManagerSinkVtbl;

    interface IResourceManagerSink
    {
        CONST_VTBL struct IResourceManagerSinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IResourceManagerSink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IResourceManagerSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IResourceManagerSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IResourceManagerSink_TMDown(This)	\
    (This)->lpVtbl -> TMDown(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IResourceManagerSink_TMDown_Proxy( 
    IResourceManagerSink __RPC_FAR * This);


void __RPC_STUB IResourceManagerSink_TMDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IResourceManagerSink_INTERFACE_DEFINED__ */


#ifndef __IResourceManager_INTERFACE_DEFINED__
#define __IResourceManager_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IResourceManager
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][object][uuid] */ 



EXTERN_C const IID IID_IResourceManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("13741d21-87eb-11ce-8081-0080c758527e")
    IResourceManager : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Enlist( 
            /* [in] */ ITransaction __RPC_FAR *pTransaction,
            /* [in] */ ITransactionResourceAsync __RPC_FAR *pRes,
            /* [out][in] */ GUID __RPC_FAR *pUOW,
            /* [out] */ LONG __RPC_FAR *pisoLevel,
            /* [out] */ ITransactionEnlistmentAsync __RPC_FAR *__RPC_FAR *ppEnlist) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reenlist( 
            /* [in] */ unsigned char __RPC_FAR *pPrepInfo,
            /* [in] */ ULONG cbPrepInfo,
            /* [in] */ DWORD lTimeout,
            /* [out][in] */ XACTSTAT __RPC_FAR *pXactStat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReenlistmentComplete( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDistributedTransactionManager( 
            /* [in] */ REFIID iid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IResourceManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IResourceManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IResourceManager __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IResourceManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Enlist )( 
            IResourceManager __RPC_FAR * This,
            /* [in] */ ITransaction __RPC_FAR *pTransaction,
            /* [in] */ ITransactionResourceAsync __RPC_FAR *pRes,
            /* [out][in] */ GUID __RPC_FAR *pUOW,
            /* [out] */ LONG __RPC_FAR *pisoLevel,
            /* [out] */ ITransactionEnlistmentAsync __RPC_FAR *__RPC_FAR *ppEnlist);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reenlist )( 
            IResourceManager __RPC_FAR * This,
            /* [in] */ unsigned char __RPC_FAR *pPrepInfo,
            /* [in] */ ULONG cbPrepInfo,
            /* [in] */ DWORD lTimeout,
            /* [out][in] */ XACTSTAT __RPC_FAR *pXactStat);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReenlistmentComplete )( 
            IResourceManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDistributedTransactionManager )( 
            IResourceManager __RPC_FAR * This,
            /* [in] */ REFIID iid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        END_INTERFACE
    } IResourceManagerVtbl;

    interface IResourceManager
    {
        CONST_VTBL struct IResourceManagerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IResourceManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IResourceManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IResourceManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IResourceManager_Enlist(This,pTransaction,pRes,pUOW,pisoLevel,ppEnlist)	\
    (This)->lpVtbl -> Enlist(This,pTransaction,pRes,pUOW,pisoLevel,ppEnlist)

#define IResourceManager_Reenlist(This,pPrepInfo,cbPrepInfo,lTimeout,pXactStat)	\
    (This)->lpVtbl -> Reenlist(This,pPrepInfo,cbPrepInfo,lTimeout,pXactStat)

#define IResourceManager_ReenlistmentComplete(This)	\
    (This)->lpVtbl -> ReenlistmentComplete(This)

#define IResourceManager_GetDistributedTransactionManager(This,iid,ppvObject)	\
    (This)->lpVtbl -> GetDistributedTransactionManager(This,iid,ppvObject)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IResourceManager_Enlist_Proxy( 
    IResourceManager __RPC_FAR * This,
    /* [in] */ ITransaction __RPC_FAR *pTransaction,
    /* [in] */ ITransactionResourceAsync __RPC_FAR *pRes,
    /* [out][in] */ GUID __RPC_FAR *pUOW,
    /* [out] */ LONG __RPC_FAR *pisoLevel,
    /* [out] */ ITransactionEnlistmentAsync __RPC_FAR *__RPC_FAR *ppEnlist);


void __RPC_STUB IResourceManager_Enlist_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IResourceManager_Reenlist_Proxy( 
    IResourceManager __RPC_FAR * This,
    /* [in] */ unsigned char __RPC_FAR *pPrepInfo,
    /* [in] */ ULONG cbPrepInfo,
    /* [in] */ DWORD lTimeout,
    /* [out][in] */ XACTSTAT __RPC_FAR *pXactStat);


void __RPC_STUB IResourceManager_Reenlist_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IResourceManager_ReenlistmentComplete_Proxy( 
    IResourceManager __RPC_FAR * This);


void __RPC_STUB IResourceManager_ReenlistmentComplete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IResourceManager_GetDistributedTransactionManager_Proxy( 
    IResourceManager __RPC_FAR * This,
    /* [in] */ REFIID iid,
    /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);


void __RPC_STUB IResourceManager_GetDistributedTransactionManager_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IResourceManager_INTERFACE_DEFINED__ */


#ifndef __IXAConfig_INTERFACE_DEFINED__
#define __IXAConfig_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IXAConfig
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][object][uuid] */ 



EXTERN_C const IID IID_IXAConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("C8A6E3A1-9A8C-11cf-A308-00A0C905416E")
    IXAConfig : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ GUID clsidHelperDll) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Terminate( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXAConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXAConfig __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXAConfig __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXAConfig __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IXAConfig __RPC_FAR * This,
            /* [in] */ GUID clsidHelperDll);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Terminate )( 
            IXAConfig __RPC_FAR * This);
        
        END_INTERFACE
    } IXAConfigVtbl;

    interface IXAConfig
    {
        CONST_VTBL struct IXAConfigVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXAConfig_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXAConfig_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXAConfig_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXAConfig_Initialize(This,clsidHelperDll)	\
    (This)->lpVtbl -> Initialize(This,clsidHelperDll)

#define IXAConfig_Terminate(This)	\
    (This)->lpVtbl -> Terminate(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IXAConfig_Initialize_Proxy( 
    IXAConfig __RPC_FAR * This,
    /* [in] */ GUID clsidHelperDll);


void __RPC_STUB IXAConfig_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXAConfig_Terminate_Proxy( 
    IXAConfig __RPC_FAR * This);


void __RPC_STUB IXAConfig_Terminate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXAConfig_INTERFACE_DEFINED__ */


#ifndef __IRMHelper_INTERFACE_DEFINED__
#define __IRMHelper_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRMHelper
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [local][unique][object][uuid] */ 


#ifndef _XID_T_DEFINED
#define _XID_T_DEFINED
typedef struct  xid_t
    {
    long formatID;
    long gtrid_length;
    long bqual_length;
    char data[ 128 ];
    }	XID;

#endif
#ifndef _XA_SWITCH_T_DEFINED
#define _XA_SWITCH_T_DEFINED
typedef struct  xa_switch_t
    {
    char name[ 32 ];
    long flags;
    long version;
    int ( __cdecl __RPC_FAR *xa_open_entry )( 
        char __RPC_FAR *__MIDL_0008,
        int __MIDL_0009,
        long __MIDL_0010);
    int ( __cdecl __RPC_FAR *xa_close_entry )( 
        char __RPC_FAR *__MIDL_0012,
        int __MIDL_0013,
        long __MIDL_0014);
    int ( __cdecl __RPC_FAR *xa_start_entry )( 
        XID __RPC_FAR *__MIDL_0016,
        int __MIDL_0017,
        long __MIDL_0018);
    int ( __cdecl __RPC_FAR *xa_end_entry )( 
        XID __RPC_FAR *__MIDL_0020,
        int __MIDL_0021,
        long __MIDL_0022);
    int ( __cdecl __RPC_FAR *xa_rollback_entry )( 
        XID __RPC_FAR *__MIDL_0024,
        int __MIDL_0025,
        long __MIDL_0026);
    int ( __cdecl __RPC_FAR *xa_prepare_entry )( 
        XID __RPC_FAR *__MIDL_0028,
        int __MIDL_0029,
        long __MIDL_0030);
    int ( __cdecl __RPC_FAR *xa_commit_entry )( 
        XID __RPC_FAR *__MIDL_0032,
        int __MIDL_0033,
        long __MIDL_0034);
    int ( __cdecl __RPC_FAR *xa_recover_entry )( 
        XID __RPC_FAR *__MIDL_0036,
        long __MIDL_0037,
        int __MIDL_0038,
        long __MIDL_0039);
    int ( __cdecl __RPC_FAR *xa_forget_entry )( 
        XID __RPC_FAR *__MIDL_0041,
        int __MIDL_0042,
        long __MIDL_0043);
    int ( __cdecl __RPC_FAR *xa_complete_entry )( 
        int __RPC_FAR *__MIDL_0045,
        int __RPC_FAR *__MIDL_0046,
        int __MIDL_0047,
        long __MIDL_0048);
    }	xa_switch_t;

#endif

EXTERN_C const IID IID_IRMHelper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("E793F6D1-F53D-11cf-A60D-00A0C905416E")
    IRMHelper : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RMCount( 
            /* [in] */ DWORD dwcTotalNumberOfRMs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RMInfo( 
            /* [in] */ xa_switch_t __RPC_FAR *pXa_Switch,
            /* [in] */ BOOL fCDeclCallingConv,
            /* [string][in] */ char __RPC_FAR *pszOpenString,
            /* [string][in] */ char __RPC_FAR *pszCloseString,
            /* [in] */ GUID guidRMRecovery) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRMHelperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRMHelper __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRMHelper __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRMHelper __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RMCount )( 
            IRMHelper __RPC_FAR * This,
            /* [in] */ DWORD dwcTotalNumberOfRMs);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RMInfo )( 
            IRMHelper __RPC_FAR * This,
            /* [in] */ xa_switch_t __RPC_FAR *pXa_Switch,
            /* [in] */ BOOL fCDeclCallingConv,
            /* [string][in] */ char __RPC_FAR *pszOpenString,
            /* [string][in] */ char __RPC_FAR *pszCloseString,
            /* [in] */ GUID guidRMRecovery);
        
        END_INTERFACE
    } IRMHelperVtbl;

    interface IRMHelper
    {
        CONST_VTBL struct IRMHelperVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRMHelper_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRMHelper_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRMHelper_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRMHelper_RMCount(This,dwcTotalNumberOfRMs)	\
    (This)->lpVtbl -> RMCount(This,dwcTotalNumberOfRMs)

#define IRMHelper_RMInfo(This,pXa_Switch,fCDeclCallingConv,pszOpenString,pszCloseString,guidRMRecovery)	\
    (This)->lpVtbl -> RMInfo(This,pXa_Switch,fCDeclCallingConv,pszOpenString,pszCloseString,guidRMRecovery)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IRMHelper_RMCount_Proxy( 
    IRMHelper __RPC_FAR * This,
    /* [in] */ DWORD dwcTotalNumberOfRMs);


void __RPC_STUB IRMHelper_RMCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IRMHelper_RMInfo_Proxy( 
    IRMHelper __RPC_FAR * This,
    /* [in] */ xa_switch_t __RPC_FAR *pXa_Switch,
    /* [in] */ BOOL fCDeclCallingConv,
    /* [string][in] */ char __RPC_FAR *pszOpenString,
    /* [string][in] */ char __RPC_FAR *pszCloseString,
    /* [in] */ GUID guidRMRecovery);


void __RPC_STUB IRMHelper_RMInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRMHelper_INTERFACE_DEFINED__ */


#ifndef __IXAObtainRMInfo_INTERFACE_DEFINED__
#define __IXAObtainRMInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IXAObtainRMInfo
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][object][uuid] */ 



EXTERN_C const IID IID_IXAObtainRMInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("E793F6D2-F53D-11cf-A60D-00A0C905416E")
    IXAObtainRMInfo : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ObtainRMInfo( 
            /* [in] */ IRMHelper __RPC_FAR *pIRMHelper) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXAObtainRMInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXAObtainRMInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXAObtainRMInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXAObtainRMInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ObtainRMInfo )( 
            IXAObtainRMInfo __RPC_FAR * This,
            /* [in] */ IRMHelper __RPC_FAR *pIRMHelper);
        
        END_INTERFACE
    } IXAObtainRMInfoVtbl;

    interface IXAObtainRMInfo
    {
        CONST_VTBL struct IXAObtainRMInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXAObtainRMInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXAObtainRMInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXAObtainRMInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXAObtainRMInfo_ObtainRMInfo(This,pIRMHelper)	\
    (This)->lpVtbl -> ObtainRMInfo(This,pIRMHelper)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IXAObtainRMInfo_ObtainRMInfo_Proxy( 
    IXAObtainRMInfo __RPC_FAR * This,
    /* [in] */ IRMHelper __RPC_FAR *pIRMHelper);


void __RPC_STUB IXAObtainRMInfo_ObtainRMInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXAObtainRMInfo_INTERFACE_DEFINED__ */


#ifndef __IXAResourceManager_INTERFACE_DEFINED__
#define __IXAResourceManager_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IXAResourceManager
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][object][uuid] */ 



EXTERN_C const IID IID_IXAResourceManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("4131E751-1AEA-11d0-944B-00A0C905416E")
    IXAResourceManager : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IXAResourceManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXAResourceManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXAResourceManager __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXAResourceManager __RPC_FAR * This);
        
        END_INTERFACE
    } IXAResourceManagerVtbl;

    interface IXAResourceManager
    {
        CONST_VTBL struct IXAResourceManagerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXAResourceManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXAResourceManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXAResourceManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IXAResourceManager_INTERFACE_DEFINED__ */


#ifndef __IXAResourceManagerFactory_INTERFACE_DEFINED__
#define __IXAResourceManagerFactory_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IXAResourceManagerFactory
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][object][uuid] */ 



EXTERN_C const IID IID_IXAResourceManagerFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("4131E750-1AEA-11d0-944B-00A0C905416E")
    IXAResourceManagerFactory : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Create( 
            /* [string][in] */ char __RPC_FAR *pszDSN,
            /* [in] */ CLSID clsidRMHelper,
            /* [out] */ IXAResourceManager __RPC_FAR *__RPC_FAR *ppIXaResMgr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXAResourceManagerFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXAResourceManagerFactory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXAResourceManagerFactory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXAResourceManagerFactory __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Create )( 
            IXAResourceManagerFactory __RPC_FAR * This,
            /* [string][in] */ char __RPC_FAR *pszDSN,
            /* [in] */ CLSID clsidRMHelper,
            /* [out] */ IXAResourceManager __RPC_FAR *__RPC_FAR *ppIXaResMgr);
        
        END_INTERFACE
    } IXAResourceManagerFactoryVtbl;

    interface IXAResourceManagerFactory
    {
        CONST_VTBL struct IXAResourceManagerFactoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXAResourceManagerFactory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXAResourceManagerFactory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXAResourceManagerFactory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXAResourceManagerFactory_Create(This,pszDSN,clsidRMHelper,ppIXaResMgr)	\
    (This)->lpVtbl -> Create(This,pszDSN,clsidRMHelper,ppIXaResMgr)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IXAResourceManagerFactory_Create_Proxy( 
    IXAResourceManagerFactory __RPC_FAR * This,
    /* [string][in] */ char __RPC_FAR *pszDSN,
    /* [in] */ CLSID clsidRMHelper,
    /* [out] */ IXAResourceManager __RPC_FAR *__RPC_FAR *ppIXaResMgr);


void __RPC_STUB IXAResourceManagerFactory_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXAResourceManagerFactory_INTERFACE_DEFINED__ */


#ifndef __IXATransaction_INTERFACE_DEFINED__
#define __IXATransaction_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IXATransaction
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][object][uuid] */ 



EXTERN_C const IID IID_IXATransaction;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("4131E752-1AEA-11d0-944B-00A0C905416E")
    IXATransaction : public ITransaction
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Join( 
            /* [in] */ IXAResourceManager __RPC_FAR *pIXAResourceManager) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnJoin( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IXATransactionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IXATransaction __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IXATransaction __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IXATransaction __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Commit )( 
            IXATransaction __RPC_FAR * This,
            /* [in] */ BOOL fRetaining,
            /* [in] */ DWORD grfTC,
            /* [in] */ DWORD grfRM);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Abort )( 
            IXATransaction __RPC_FAR * This,
            /* [in] */ BOID __RPC_FAR *pboidReason,
            /* [in] */ BOOL fRetaining,
            /* [in] */ BOOL fAsync);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTransactionInfo )( 
            IXATransaction __RPC_FAR * This,
            /* [out] */ XACTTRANSINFO __RPC_FAR *pinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Join )( 
            IXATransaction __RPC_FAR * This,
            /* [in] */ IXAResourceManager __RPC_FAR *pIXAResourceManager);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnJoin )( 
            IXATransaction __RPC_FAR * This);
        
        END_INTERFACE
    } IXATransactionVtbl;

    interface IXATransaction
    {
        CONST_VTBL struct IXATransactionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IXATransaction_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IXATransaction_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IXATransaction_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IXATransaction_Commit(This,fRetaining,grfTC,grfRM)	\
    (This)->lpVtbl -> Commit(This,fRetaining,grfTC,grfRM)

#define IXATransaction_Abort(This,pboidReason,fRetaining,fAsync)	\
    (This)->lpVtbl -> Abort(This,pboidReason,fRetaining,fAsync)

#define IXATransaction_GetTransactionInfo(This,pinfo)	\
    (This)->lpVtbl -> GetTransactionInfo(This,pinfo)


#define IXATransaction_Join(This,pIXAResourceManager)	\
    (This)->lpVtbl -> Join(This,pIXAResourceManager)

#define IXATransaction_UnJoin(This)	\
    (This)->lpVtbl -> UnJoin(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IXATransaction_Join_Proxy( 
    IXATransaction __RPC_FAR * This,
    /* [in] */ IXAResourceManager __RPC_FAR *pIXAResourceManager);


void __RPC_STUB IXATransaction_Join_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IXATransaction_UnJoin_Proxy( 
    IXATransaction __RPC_FAR * This);


void __RPC_STUB IXATransaction_UnJoin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IXATransaction_INTERFACE_DEFINED__ */


#ifndef __IResourceManagerFactory_INTERFACE_DEFINED__
#define __IResourceManagerFactory_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IResourceManagerFactory
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][object][uuid] */ 



EXTERN_C const IID IID_IResourceManagerFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("13741d20-87eb-11ce-8081-0080c758527e")
    IResourceManagerFactory : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ GUID __RPC_FAR *pguidRM,
            /* [string][in] */ CHAR __RPC_FAR *pszRMName,
            /* [in] */ IResourceManagerSink __RPC_FAR *pIResMgrSink,
            /* [out] */ IResourceManager __RPC_FAR *__RPC_FAR *ppResMgr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IResourceManagerFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IResourceManagerFactory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IResourceManagerFactory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IResourceManagerFactory __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Create )( 
            IResourceManagerFactory __RPC_FAR * This,
            /* [in] */ GUID __RPC_FAR *pguidRM,
            /* [string][in] */ CHAR __RPC_FAR *pszRMName,
            /* [in] */ IResourceManagerSink __RPC_FAR *pIResMgrSink,
            /* [out] */ IResourceManager __RPC_FAR *__RPC_FAR *ppResMgr);
        
        END_INTERFACE
    } IResourceManagerFactoryVtbl;

    interface IResourceManagerFactory
    {
        CONST_VTBL struct IResourceManagerFactoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IResourceManagerFactory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IResourceManagerFactory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IResourceManagerFactory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IResourceManagerFactory_Create(This,pguidRM,pszRMName,pIResMgrSink,ppResMgr)	\
    (This)->lpVtbl -> Create(This,pguidRM,pszRMName,pIResMgrSink,ppResMgr)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IResourceManagerFactory_Create_Proxy( 
    IResourceManagerFactory __RPC_FAR * This,
    /* [in] */ GUID __RPC_FAR *pguidRM,
    /* [string][in] */ CHAR __RPC_FAR *pszRMName,
    /* [in] */ IResourceManagerSink __RPC_FAR *pIResMgrSink,
    /* [out] */ IResourceManager __RPC_FAR *__RPC_FAR *ppResMgr);


void __RPC_STUB IResourceManagerFactory_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IResourceManagerFactory_INTERFACE_DEFINED__ */


#ifndef __IPrepareInfo_INTERFACE_DEFINED__
#define __IPrepareInfo_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IPrepareInfo
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][object][uuid] */ 



EXTERN_C const IID IID_IPrepareInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("80c7bfd0-87ee-11ce-8081-0080c758527e")
    IPrepareInfo : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetPrepareInfoSize( 
            /* [out] */ ULONG __RPC_FAR *pcbPrepInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPrepareInfo( 
            /* [out][in] */ BYTE __RPC_FAR *pPrepInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPrepareInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPrepareInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPrepareInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPrepareInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPrepareInfoSize )( 
            IPrepareInfo __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *pcbPrepInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPrepareInfo )( 
            IPrepareInfo __RPC_FAR * This,
            /* [out][in] */ BYTE __RPC_FAR *pPrepInfo);
        
        END_INTERFACE
    } IPrepareInfoVtbl;

    interface IPrepareInfo
    {
        CONST_VTBL struct IPrepareInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPrepareInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPrepareInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPrepareInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPrepareInfo_GetPrepareInfoSize(This,pcbPrepInfo)	\
    (This)->lpVtbl -> GetPrepareInfoSize(This,pcbPrepInfo)

#define IPrepareInfo_GetPrepareInfo(This,pPrepInfo)	\
    (This)->lpVtbl -> GetPrepareInfo(This,pPrepInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IPrepareInfo_GetPrepareInfoSize_Proxy( 
    IPrepareInfo __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *pcbPrepInfo);


void __RPC_STUB IPrepareInfo_GetPrepareInfoSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IPrepareInfo_GetPrepareInfo_Proxy( 
    IPrepareInfo __RPC_FAR * This,
    /* [out][in] */ BYTE __RPC_FAR *pPrepInfo);


void __RPC_STUB IPrepareInfo_GetPrepareInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPrepareInfo_INTERFACE_DEFINED__ */


#ifndef __IGetDispenser_INTERFACE_DEFINED__
#define __IGetDispenser_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IGetDispenser
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][object][uuid] */ 



EXTERN_C const IID IID_IGetDispenser;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("c23cc370-87ef-11ce-8081-0080c758527e")
    IGetDispenser : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDispenser( 
            /* [in] */ REFIID iid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IGetDispenserVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IGetDispenser __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IGetDispenser __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IGetDispenser __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDispenser )( 
            IGetDispenser __RPC_FAR * This,
            /* [in] */ REFIID iid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        END_INTERFACE
    } IGetDispenserVtbl;

    interface IGetDispenser
    {
        CONST_VTBL struct IGetDispenserVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGetDispenser_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IGetDispenser_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IGetDispenser_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IGetDispenser_GetDispenser(This,iid,ppvObject)	\
    (This)->lpVtbl -> GetDispenser(This,iid,ppvObject)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IGetDispenser_GetDispenser_Proxy( 
    IGetDispenser __RPC_FAR * This,
    /* [in] */ REFIID iid,
    /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);


void __RPC_STUB IGetDispenser_GetDispenser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IGetDispenser_INTERFACE_DEFINED__ */


#ifndef __ITransactionVoterBallotAsync_INTERFACE_DEFINED__
#define __ITransactionVoterBallotAsync_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITransactionVoterBallotAsync
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][object][uuid] */ 



EXTERN_C const IID IID_ITransactionVoterBallotAsync;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("319FAC12-A391-11cf-A535-00AA006887C3")
    ITransactionVoterBallotAsync : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE VoteRequestDone( 
            /* [in] */ HRESULT hr,
            /* [in] */ BOID __RPC_FAR *pboidReason) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITransactionVoterBallotAsyncVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITransactionVoterBallotAsync __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITransactionVoterBallotAsync __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITransactionVoterBallotAsync __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VoteRequestDone )( 
            ITransactionVoterBallotAsync __RPC_FAR * This,
            /* [in] */ HRESULT hr,
            /* [in] */ BOID __RPC_FAR *pboidReason);
        
        END_INTERFACE
    } ITransactionVoterBallotAsyncVtbl;

    interface ITransactionVoterBallotAsync
    {
        CONST_VTBL struct ITransactionVoterBallotAsyncVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITransactionVoterBallotAsync_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITransactionVoterBallotAsync_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITransactionVoterBallotAsync_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITransactionVoterBallotAsync_VoteRequestDone(This,hr,pboidReason)	\
    (This)->lpVtbl -> VoteRequestDone(This,hr,pboidReason)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITransactionVoterBallotAsync_VoteRequestDone_Proxy( 
    ITransactionVoterBallotAsync __RPC_FAR * This,
    /* [in] */ HRESULT hr,
    /* [in] */ BOID __RPC_FAR *pboidReason);


void __RPC_STUB ITransactionVoterBallotAsync_VoteRequestDone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITransactionVoterBallotAsync_INTERFACE_DEFINED__ */


#ifndef __ITransactionVoterNotifyAsync_INTERFACE_DEFINED__
#define __ITransactionVoterNotifyAsync_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITransactionVoterNotifyAsync
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][object][uuid] */ 



EXTERN_C const IID IID_ITransactionVoterNotifyAsync;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("B94ABFDC-FFC9-11d0-B164-00C04FC2F3EF")
    ITransactionVoterNotifyAsync : public ITransactionOutcomeEvents
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE VoteRequest( 
            ITransactionVoterBallotAsync __RPC_FAR *pVoterBallot) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITransactionVoterNotifyAsyncVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITransactionVoterNotifyAsync __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITransactionVoterNotifyAsync __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITransactionVoterNotifyAsync __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Committed )( 
            ITransactionVoterNotifyAsync __RPC_FAR * This,
            /* [in] */ BOOL fRetaining,
            /* [in] */ XACTUOW __RPC_FAR *pNewUOW,
            /* [in] */ HRESULT hr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Aborted )( 
            ITransactionVoterNotifyAsync __RPC_FAR * This,
            /* [in] */ BOID __RPC_FAR *pboidReason,
            /* [in] */ BOOL fRetaining,
            /* [in] */ XACTUOW __RPC_FAR *pNewUOW,
            /* [in] */ HRESULT hr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HeuristicDecision )( 
            ITransactionVoterNotifyAsync __RPC_FAR * This,
            /* [in] */ DWORD dwDecision,
            /* [in] */ BOID __RPC_FAR *pboidReason,
            /* [in] */ HRESULT hr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Indoubt )( 
            ITransactionVoterNotifyAsync __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VoteRequest )( 
            ITransactionVoterNotifyAsync __RPC_FAR * This,
            ITransactionVoterBallotAsync __RPC_FAR *pVoterBallot);
        
        END_INTERFACE
    } ITransactionVoterNotifyAsyncVtbl;

    interface ITransactionVoterNotifyAsync
    {
        CONST_VTBL struct ITransactionVoterNotifyAsyncVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITransactionVoterNotifyAsync_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITransactionVoterNotifyAsync_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITransactionVoterNotifyAsync_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITransactionVoterNotifyAsync_Committed(This,fRetaining,pNewUOW,hr)	\
    (This)->lpVtbl -> Committed(This,fRetaining,pNewUOW,hr)

#define ITransactionVoterNotifyAsync_Aborted(This,pboidReason,fRetaining,pNewUOW,hr)	\
    (This)->lpVtbl -> Aborted(This,pboidReason,fRetaining,pNewUOW,hr)

#define ITransactionVoterNotifyAsync_HeuristicDecision(This,dwDecision,pboidReason,hr)	\
    (This)->lpVtbl -> HeuristicDecision(This,dwDecision,pboidReason,hr)

#define ITransactionVoterNotifyAsync_Indoubt(This)	\
    (This)->lpVtbl -> Indoubt(This)


#define ITransactionVoterNotifyAsync_VoteRequest(This,pVoterBallot)	\
    (This)->lpVtbl -> VoteRequest(This,pVoterBallot)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITransactionVoterNotifyAsync_VoteRequest_Proxy( 
    ITransactionVoterNotifyAsync __RPC_FAR * This,
    ITransactionVoterBallotAsync __RPC_FAR *pVoterBallot);


void __RPC_STUB ITransactionVoterNotifyAsync_VoteRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITransactionVoterNotifyAsync_INTERFACE_DEFINED__ */


#ifndef __ITransactionVoterFactory_INTERFACE_DEFINED__
#define __ITransactionVoterFactory_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITransactionVoterFactory
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][object][uuid] */ 



EXTERN_C const IID IID_ITransactionVoterFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("319FAC10-A391-11cf-A535-00AA006887C3")
    ITransactionVoterFactory : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ ITransaction __RPC_FAR *pTransaction,
            /* [in] */ ITransactionVoterNotifyAsync __RPC_FAR *pVoterNotify,
            /* [out] */ ITransactionVoterBallotAsync __RPC_FAR *__RPC_FAR *ppVoterBallot) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITransactionVoterFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITransactionVoterFactory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITransactionVoterFactory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITransactionVoterFactory __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Create )( 
            ITransactionVoterFactory __RPC_FAR * This,
            /* [in] */ ITransaction __RPC_FAR *pTransaction,
            /* [in] */ ITransactionVoterNotifyAsync __RPC_FAR *pVoterNotify,
            /* [out] */ ITransactionVoterBallotAsync __RPC_FAR *__RPC_FAR *ppVoterBallot);
        
        END_INTERFACE
    } ITransactionVoterFactoryVtbl;

    interface ITransactionVoterFactory
    {
        CONST_VTBL struct ITransactionVoterFactoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITransactionVoterFactory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITransactionVoterFactory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITransactionVoterFactory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITransactionVoterFactory_Create(This,pTransaction,pVoterNotify,ppVoterBallot)	\
    (This)->lpVtbl -> Create(This,pTransaction,pVoterNotify,ppVoterBallot)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITransactionVoterFactory_Create_Proxy( 
    ITransactionVoterFactory __RPC_FAR * This,
    /* [in] */ ITransaction __RPC_FAR *pTransaction,
    /* [in] */ ITransactionVoterNotifyAsync __RPC_FAR *pVoterNotify,
    /* [out] */ ITransactionVoterBallotAsync __RPC_FAR *__RPC_FAR *ppVoterBallot);


void __RPC_STUB ITransactionVoterFactory_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITransactionVoterFactory_INTERFACE_DEFINED__ */


#ifndef __ITransactionTransmitter_INTERFACE_DEFINED__
#define __ITransactionTransmitter_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITransactionTransmitter
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][object][uuid] */ 



EXTERN_C const IID IID_ITransactionTransmitter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("59313E01-B36C-11cf-A539-00AA006887C3")
    ITransactionTransmitter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Set( 
            /* [in] */ ITransaction __RPC_FAR *pTransaction) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPropagationTokenSize( 
            /* [out] */ ULONG __RPC_FAR *pcbToken) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MarshalPropagationToken( 
            /* [in] */ ULONG cbToken,
            /* [size_is][out] */ BYTE __RPC_FAR *rgbToken,
            /* [out] */ ULONG __RPC_FAR *pcbUsed) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnmarshalReturnToken( 
            /* [in] */ ULONG cbReturnToken,
            /* [size_is][in] */ BYTE __RPC_FAR *rgbReturnToken) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITransactionTransmitterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITransactionTransmitter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITransactionTransmitter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITransactionTransmitter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Set )( 
            ITransactionTransmitter __RPC_FAR * This,
            /* [in] */ ITransaction __RPC_FAR *pTransaction);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPropagationTokenSize )( 
            ITransactionTransmitter __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *pcbToken);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MarshalPropagationToken )( 
            ITransactionTransmitter __RPC_FAR * This,
            /* [in] */ ULONG cbToken,
            /* [size_is][out] */ BYTE __RPC_FAR *rgbToken,
            /* [out] */ ULONG __RPC_FAR *pcbUsed);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnmarshalReturnToken )( 
            ITransactionTransmitter __RPC_FAR * This,
            /* [in] */ ULONG cbReturnToken,
            /* [size_is][in] */ BYTE __RPC_FAR *rgbReturnToken);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            ITransactionTransmitter __RPC_FAR * This);
        
        END_INTERFACE
    } ITransactionTransmitterVtbl;

    interface ITransactionTransmitter
    {
        CONST_VTBL struct ITransactionTransmitterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITransactionTransmitter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITransactionTransmitter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITransactionTransmitter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITransactionTransmitter_Set(This,pTransaction)	\
    (This)->lpVtbl -> Set(This,pTransaction)

#define ITransactionTransmitter_GetPropagationTokenSize(This,pcbToken)	\
    (This)->lpVtbl -> GetPropagationTokenSize(This,pcbToken)

#define ITransactionTransmitter_MarshalPropagationToken(This,cbToken,rgbToken,pcbUsed)	\
    (This)->lpVtbl -> MarshalPropagationToken(This,cbToken,rgbToken,pcbUsed)

#define ITransactionTransmitter_UnmarshalReturnToken(This,cbReturnToken,rgbReturnToken)	\
    (This)->lpVtbl -> UnmarshalReturnToken(This,cbReturnToken,rgbReturnToken)

#define ITransactionTransmitter_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITransactionTransmitter_Set_Proxy( 
    ITransactionTransmitter __RPC_FAR * This,
    /* [in] */ ITransaction __RPC_FAR *pTransaction);


void __RPC_STUB ITransactionTransmitter_Set_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITransactionTransmitter_GetPropagationTokenSize_Proxy( 
    ITransactionTransmitter __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *pcbToken);


void __RPC_STUB ITransactionTransmitter_GetPropagationTokenSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITransactionTransmitter_MarshalPropagationToken_Proxy( 
    ITransactionTransmitter __RPC_FAR * This,
    /* [in] */ ULONG cbToken,
    /* [size_is][out] */ BYTE __RPC_FAR *rgbToken,
    /* [out] */ ULONG __RPC_FAR *pcbUsed);


void __RPC_STUB ITransactionTransmitter_MarshalPropagationToken_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITransactionTransmitter_UnmarshalReturnToken_Proxy( 
    ITransactionTransmitter __RPC_FAR * This,
    /* [in] */ ULONG cbReturnToken,
    /* [size_is][in] */ BYTE __RPC_FAR *rgbReturnToken);


void __RPC_STUB ITransactionTransmitter_UnmarshalReturnToken_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITransactionTransmitter_Reset_Proxy( 
    ITransactionTransmitter __RPC_FAR * This);


void __RPC_STUB ITransactionTransmitter_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITransactionTransmitter_INTERFACE_DEFINED__ */


#ifndef __ITransactionTransmitterFactory_INTERFACE_DEFINED__
#define __ITransactionTransmitterFactory_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITransactionTransmitterFactory
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][object][uuid] */ 



EXTERN_C const IID IID_ITransactionTransmitterFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("59313E00-B36C-11cf-A539-00AA006887C3")
    ITransactionTransmitterFactory : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Create( 
            /* [out] */ ITransactionTransmitter __RPC_FAR *__RPC_FAR *ppTransmitter) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITransactionTransmitterFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITransactionTransmitterFactory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITransactionTransmitterFactory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITransactionTransmitterFactory __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Create )( 
            ITransactionTransmitterFactory __RPC_FAR * This,
            /* [out] */ ITransactionTransmitter __RPC_FAR *__RPC_FAR *ppTransmitter);
        
        END_INTERFACE
    } ITransactionTransmitterFactoryVtbl;

    interface ITransactionTransmitterFactory
    {
        CONST_VTBL struct ITransactionTransmitterFactoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITransactionTransmitterFactory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITransactionTransmitterFactory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITransactionTransmitterFactory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITransactionTransmitterFactory_Create(This,ppTransmitter)	\
    (This)->lpVtbl -> Create(This,ppTransmitter)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITransactionTransmitterFactory_Create_Proxy( 
    ITransactionTransmitterFactory __RPC_FAR * This,
    /* [out] */ ITransactionTransmitter __RPC_FAR *__RPC_FAR *ppTransmitter);


void __RPC_STUB ITransactionTransmitterFactory_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITransactionTransmitterFactory_INTERFACE_DEFINED__ */


#ifndef __ITransactionReceiver_INTERFACE_DEFINED__
#define __ITransactionReceiver_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITransactionReceiver
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][object][uuid] */ 



EXTERN_C const IID IID_ITransactionReceiver;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("59313E03-B36C-11cf-A539-00AA006887C3")
    ITransactionReceiver : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE UnmarshalPropagationToken( 
            /* [in] */ ULONG cbToken,
            /* [size_is][in] */ BYTE __RPC_FAR *rgbToken,
            /* [out] */ ITransaction __RPC_FAR *__RPC_FAR *ppTransaction) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetReturnTokenSize( 
            /* [out] */ ULONG __RPC_FAR *pcbReturnToken) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MarshalReturnToken( 
            /* [in] */ ULONG cbReturnToken,
            /* [size_is][out] */ BYTE __RPC_FAR *rgbReturnToken,
            /* [out] */ ULONG __RPC_FAR *pcbUsed) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITransactionReceiverVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITransactionReceiver __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITransactionReceiver __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITransactionReceiver __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnmarshalPropagationToken )( 
            ITransactionReceiver __RPC_FAR * This,
            /* [in] */ ULONG cbToken,
            /* [size_is][in] */ BYTE __RPC_FAR *rgbToken,
            /* [out] */ ITransaction __RPC_FAR *__RPC_FAR *ppTransaction);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetReturnTokenSize )( 
            ITransactionReceiver __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *pcbReturnToken);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MarshalReturnToken )( 
            ITransactionReceiver __RPC_FAR * This,
            /* [in] */ ULONG cbReturnToken,
            /* [size_is][out] */ BYTE __RPC_FAR *rgbReturnToken,
            /* [out] */ ULONG __RPC_FAR *pcbUsed);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            ITransactionReceiver __RPC_FAR * This);
        
        END_INTERFACE
    } ITransactionReceiverVtbl;

    interface ITransactionReceiver
    {
        CONST_VTBL struct ITransactionReceiverVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITransactionReceiver_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITransactionReceiver_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITransactionReceiver_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITransactionReceiver_UnmarshalPropagationToken(This,cbToken,rgbToken,ppTransaction)	\
    (This)->lpVtbl -> UnmarshalPropagationToken(This,cbToken,rgbToken,ppTransaction)

#define ITransactionReceiver_GetReturnTokenSize(This,pcbReturnToken)	\
    (This)->lpVtbl -> GetReturnTokenSize(This,pcbReturnToken)

#define ITransactionReceiver_MarshalReturnToken(This,cbReturnToken,rgbReturnToken,pcbUsed)	\
    (This)->lpVtbl -> MarshalReturnToken(This,cbReturnToken,rgbReturnToken,pcbUsed)

#define ITransactionReceiver_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITransactionReceiver_UnmarshalPropagationToken_Proxy( 
    ITransactionReceiver __RPC_FAR * This,
    /* [in] */ ULONG cbToken,
    /* [size_is][in] */ BYTE __RPC_FAR *rgbToken,
    /* [out] */ ITransaction __RPC_FAR *__RPC_FAR *ppTransaction);


void __RPC_STUB ITransactionReceiver_UnmarshalPropagationToken_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITransactionReceiver_GetReturnTokenSize_Proxy( 
    ITransactionReceiver __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *pcbReturnToken);


void __RPC_STUB ITransactionReceiver_GetReturnTokenSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITransactionReceiver_MarshalReturnToken_Proxy( 
    ITransactionReceiver __RPC_FAR * This,
    /* [in] */ ULONG cbReturnToken,
    /* [size_is][out] */ BYTE __RPC_FAR *rgbReturnToken,
    /* [out] */ ULONG __RPC_FAR *pcbUsed);


void __RPC_STUB ITransactionReceiver_MarshalReturnToken_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ITransactionReceiver_Reset_Proxy( 
    ITransactionReceiver __RPC_FAR * This);


void __RPC_STUB ITransactionReceiver_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITransactionReceiver_INTERFACE_DEFINED__ */


#ifndef __ITransactionReceiverFactory_INTERFACE_DEFINED__
#define __ITransactionReceiverFactory_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITransactionReceiverFactory
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [unique][object][uuid] */ 



EXTERN_C const IID IID_ITransactionReceiverFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("59313E02-B36C-11cf-A539-00AA006887C3")
    ITransactionReceiverFactory : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Create( 
            /* [out] */ ITransactionReceiver __RPC_FAR *__RPC_FAR *ppReceiver) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITransactionReceiverFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITransactionReceiverFactory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITransactionReceiverFactory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITransactionReceiverFactory __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Create )( 
            ITransactionReceiverFactory __RPC_FAR * This,
            /* [out] */ ITransactionReceiver __RPC_FAR *__RPC_FAR *ppReceiver);
        
        END_INTERFACE
    } ITransactionReceiverFactoryVtbl;

    interface ITransactionReceiverFactory
    {
        CONST_VTBL struct ITransactionReceiverFactoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITransactionReceiverFactory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITransactionReceiverFactory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITransactionReceiverFactory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITransactionReceiverFactory_Create(This,ppReceiver)	\
    (This)->lpVtbl -> Create(This,ppReceiver)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ITransactionReceiverFactory_Create_Proxy( 
    ITransactionReceiverFactory __RPC_FAR * This,
    /* [out] */ ITransactionReceiver __RPC_FAR *__RPC_FAR *ppReceiver);


void __RPC_STUB ITransactionReceiverFactory_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITransactionReceiverFactory_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_txdtc_0108
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


typedef struct  _ProxyConfigParams
    {
    WORD wcThreadsMax;
    }	PROXY_CONFIG_PARAMS;



extern RPC_IF_HANDLE __MIDL_itf_txdtc_0108_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_txdtc_0108_v0_0_s_ifspec;

#ifndef __IDtcLuConfigure_INTERFACE_DEFINED__
#define __IDtcLuConfigure_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDtcLuConfigure
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][unique][object] */ 



EXTERN_C const IID IID_IDtcLuConfigure;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("4131E760-1AEA-11d0-944B-00A0C905416E")
    IDtcLuConfigure : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ unsigned char __RPC_FAR *pucLuPair,
            /* [in] */ DWORD cbLuPair) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Delete( 
            /* [in] */ unsigned char __RPC_FAR *pucLuPair,
            /* [in] */ DWORD cbLuPair) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDtcLuConfigureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDtcLuConfigure __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDtcLuConfigure __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDtcLuConfigure __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IDtcLuConfigure __RPC_FAR * This,
            /* [in] */ unsigned char __RPC_FAR *pucLuPair,
            /* [in] */ DWORD cbLuPair);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IDtcLuConfigure __RPC_FAR * This,
            /* [in] */ unsigned char __RPC_FAR *pucLuPair,
            /* [in] */ DWORD cbLuPair);
        
        END_INTERFACE
    } IDtcLuConfigureVtbl;

    interface IDtcLuConfigure
    {
        CONST_VTBL struct IDtcLuConfigureVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDtcLuConfigure_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDtcLuConfigure_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDtcLuConfigure_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDtcLuConfigure_Add(This,pucLuPair,cbLuPair)	\
    (This)->lpVtbl -> Add(This,pucLuPair,cbLuPair)

#define IDtcLuConfigure_Delete(This,pucLuPair,cbLuPair)	\
    (This)->lpVtbl -> Delete(This,pucLuPair,cbLuPair)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDtcLuConfigure_Add_Proxy( 
    IDtcLuConfigure __RPC_FAR * This,
    /* [in] */ unsigned char __RPC_FAR *pucLuPair,
    /* [in] */ DWORD cbLuPair);


void __RPC_STUB IDtcLuConfigure_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuConfigure_Delete_Proxy( 
    IDtcLuConfigure __RPC_FAR * This,
    /* [in] */ unsigned char __RPC_FAR *pucLuPair,
    /* [in] */ DWORD cbLuPair);


void __RPC_STUB IDtcLuConfigure_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDtcLuConfigure_INTERFACE_DEFINED__ */


#ifndef __IDtcLuRecovery_INTERFACE_DEFINED__
#define __IDtcLuRecovery_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDtcLuRecovery
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][unique][object] */ 



EXTERN_C const IID IID_IDtcLuRecovery;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("AC2B8AD2-D6F0-11d0-B386-00A0C9083365")
    IDtcLuRecovery : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IDtcLuRecoveryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDtcLuRecovery __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDtcLuRecovery __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDtcLuRecovery __RPC_FAR * This);
        
        END_INTERFACE
    } IDtcLuRecoveryVtbl;

    interface IDtcLuRecovery
    {
        CONST_VTBL struct IDtcLuRecoveryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDtcLuRecovery_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDtcLuRecovery_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDtcLuRecovery_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDtcLuRecovery_INTERFACE_DEFINED__ */


#ifndef __IDtcLuRecoveryFactory_INTERFACE_DEFINED__
#define __IDtcLuRecoveryFactory_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDtcLuRecoveryFactory
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][unique][object] */ 



EXTERN_C const IID IID_IDtcLuRecoveryFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("4131E762-1AEA-11d0-944B-00A0C905416E")
    IDtcLuRecoveryFactory : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ unsigned char __RPC_FAR *pucLuPair,
            /* [in] */ DWORD cbLuPair,
            /* [out][in] */ IDtcLuRecovery __RPC_FAR *__RPC_FAR *ppRecovery) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDtcLuRecoveryFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDtcLuRecoveryFactory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDtcLuRecoveryFactory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDtcLuRecoveryFactory __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Create )( 
            IDtcLuRecoveryFactory __RPC_FAR * This,
            /* [in] */ unsigned char __RPC_FAR *pucLuPair,
            /* [in] */ DWORD cbLuPair,
            /* [out][in] */ IDtcLuRecovery __RPC_FAR *__RPC_FAR *ppRecovery);
        
        END_INTERFACE
    } IDtcLuRecoveryFactoryVtbl;

    interface IDtcLuRecoveryFactory
    {
        CONST_VTBL struct IDtcLuRecoveryFactoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDtcLuRecoveryFactory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDtcLuRecoveryFactory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDtcLuRecoveryFactory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDtcLuRecoveryFactory_Create(This,pucLuPair,cbLuPair,ppRecovery)	\
    (This)->lpVtbl -> Create(This,pucLuPair,cbLuPair,ppRecovery)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDtcLuRecoveryFactory_Create_Proxy( 
    IDtcLuRecoveryFactory __RPC_FAR * This,
    /* [in] */ unsigned char __RPC_FAR *pucLuPair,
    /* [in] */ DWORD cbLuPair,
    /* [out][in] */ IDtcLuRecovery __RPC_FAR *__RPC_FAR *ppRecovery);


void __RPC_STUB IDtcLuRecoveryFactory_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDtcLuRecoveryFactory_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_txdtc_0111
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


typedef 
enum _DtcLu_LocalRecovery_Work
    {	DTCINITIATEDRECOVERYWORK_CHECKLUSTATUS	= 1,
	DTCINITIATEDRECOVERYWORK_TRANS	= DTCINITIATEDRECOVERYWORK_CHECKLUSTATUS + 1,
	DTCINITIATEDRECOVERYWORK_TMDOWN	= DTCINITIATEDRECOVERYWORK_TRANS + 1
    }	DTCINITIATEDRECOVERYWORK;

typedef 
enum _DtcLu_Xln
    {	DTCLUXLN_COLD	= 1,
	DTCLUXLN_WARM	= DTCLUXLN_COLD + 1
    }	DTCLUXLN;

typedef 
enum _DtcLu_Xln_Confirmation
    {	DTCLUXLNCONFIRMATION_CONFIRM	= 1,
	DTCLUXLNCONFIRMATION_LOGNAMEMISMATCH	= DTCLUXLNCONFIRMATION_CONFIRM + 1,
	DTCLUXLNCONFIRMATION_COLDWARMMISMATCH	= DTCLUXLNCONFIRMATION_LOGNAMEMISMATCH + 1,
	DTCLUXLNCONFIRMATION_OBSOLETE	= DTCLUXLNCONFIRMATION_COLDWARMMISMATCH + 1
    }	DTCLUXLNCONFIRMATION;

typedef 
enum _DtcLu_Xln_Response
    {	DTCLUXLNRESPONSE_OK_SENDOURXLNBACK	= 1,
	DTCLUXLNRESPONSE_OK_SENDCONFIRMATION	= DTCLUXLNRESPONSE_OK_SENDOURXLNBACK + 1,
	DTCLUXLNRESPONSE_LOGNAMEMISMATCH	= DTCLUXLNRESPONSE_OK_SENDCONFIRMATION + 1,
	DTCLUXLNRESPONSE_COLDWARMMISMATCH	= DTCLUXLNRESPONSE_LOGNAMEMISMATCH + 1
    }	DTCLUXLNRESPONSE;

typedef 
enum _DtcLu_Xln_Error
    {	DTCLUXLNERROR_PROTOCOL	= 1,
	DTCLUXLNERROR_LOGNAMEMISMATCH	= DTCLUXLNERROR_PROTOCOL + 1,
	DTCLUXLNERROR_COLDWARMMISMATCH	= DTCLUXLNERROR_LOGNAMEMISMATCH + 1
    }	DTCLUXLNERROR;

typedef 
enum _DtcLu_CompareState
    {	DTCLUCOMPARESTATE_COMMITTED	= 1,
	DTCLUCOMPARESTATE_HEURISTICCOMMITTED	= DTCLUCOMPARESTATE_COMMITTED + 1,
	DTCLUCOMPARESTATE_HEURISTICMIXED	= DTCLUCOMPARESTATE_HEURISTICCOMMITTED + 1,
	DTCLUCOMPARESTATE_HEURISTICRESET	= DTCLUCOMPARESTATE_HEURISTICMIXED + 1,
	DTCLUCOMPARESTATE_INDOUBT	= DTCLUCOMPARESTATE_HEURISTICRESET + 1,
	DTCLUCOMPARESTATE_RESET	= DTCLUCOMPARESTATE_INDOUBT + 1
    }	DTCLUCOMPARESTATE;

typedef 
enum _DtcLu_CompareStates_Confirmation
    {	DTCLUCOMPARESTATESCONFIRMATION_CONFIRM	= 1,
	DTCLUCOMPARESTATESCONFIRMATION_PROTOCOL	= DTCLUCOMPARESTATESCONFIRMATION_CONFIRM + 1
    }	DTCLUCOMPARESTATESCONFIRMATION;

typedef 
enum _DtcLu_CompareStates_Error
    {	DTCLUCOMPARESTATESERROR_PROTOCOL	= 1
    }	DTCLUCOMPARESTATESERROR;

typedef 
enum _DtcLu_CompareStates_Response
    {	DTCLUCOMPARESTATESRESPONSE_OK	= 1,
	DTCLUCOMPARESTATESRESPONSE_PROTOCOL	= DTCLUCOMPARESTATESRESPONSE_OK + 1
    }	DTCLUCOMPARESTATESRESPONSE;



extern RPC_IF_HANDLE __MIDL_itf_txdtc_0111_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_txdtc_0111_v0_0_s_ifspec;

#ifndef __IDtcLuRecoveryInitiatedByDtcTransWork_INTERFACE_DEFINED__
#define __IDtcLuRecoveryInitiatedByDtcTransWork_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDtcLuRecoveryInitiatedByDtcTransWork
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][unique][object] */ 



EXTERN_C const IID IID_IDtcLuRecoveryInitiatedByDtcTransWork;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("4131E765-1AEA-11d0-944B-00A0C905416E")
    IDtcLuRecoveryInitiatedByDtcTransWork : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetLogNameSizes( 
            /* [out] */ DWORD __RPC_FAR *pcbOurLogName,
            /* [out] */ DWORD __RPC_FAR *pcbRemoteLogName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOurXln( 
            /* [out] */ DTCLUXLN __RPC_FAR *pXln,
            /* [out][in] */ unsigned char __RPC_FAR *pOurLogName,
            /* [out][in] */ unsigned char __RPC_FAR *pRemoteLogName,
            /* [out] */ DWORD __RPC_FAR *pdwProtocol) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HandleConfirmationFromOurXln( 
            /* [in] */ DTCLUXLNCONFIRMATION Confirmation) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HandleTheirXlnResponse( 
            /* [in] */ DTCLUXLN Xln,
            /* [in] */ unsigned char __RPC_FAR *pRemoteLogName,
            /* [in] */ DWORD cbRemoteLogName,
            /* [in] */ DWORD dwProtocol,
            /* [out] */ DTCLUXLNCONFIRMATION __RPC_FAR *pConfirmation) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HandleErrorFromOurXln( 
            /* [in] */ DTCLUXLNERROR Error) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckForCompareStates( 
            /* [out] */ BOOL __RPC_FAR *fCompareStates) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOurTransIdSize( 
            /* [out][in] */ DWORD __RPC_FAR *pcbOurTransId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOurCompareStates( 
            /* [out][in] */ unsigned char __RPC_FAR *pOurTransId,
            /* [out] */ DTCLUCOMPARESTATE __RPC_FAR *pCompareState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HandleTheirCompareStatesResponse( 
            /* [in] */ DTCLUCOMPARESTATE CompareState,
            /* [out] */ DTCLUCOMPARESTATESCONFIRMATION __RPC_FAR *pConfirmation) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HandleErrorFromOurCompareStates( 
            /* [in] */ DTCLUCOMPARESTATESERROR Error) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConversationLost( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRecoverySeqNum( 
            /* [out] */ LONG __RPC_FAR *plRecoverySeqNum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ObsoleteRecoverySeqNum( 
            /* [in] */ LONG lNewRecoverySeqNum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDtcLuRecoveryInitiatedByDtcTransWorkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLogNameSizes )( 
            IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pcbOurLogName,
            /* [out] */ DWORD __RPC_FAR *pcbRemoteLogName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOurXln )( 
            IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
            /* [out] */ DTCLUXLN __RPC_FAR *pXln,
            /* [out][in] */ unsigned char __RPC_FAR *pOurLogName,
            /* [out][in] */ unsigned char __RPC_FAR *pRemoteLogName,
            /* [out] */ DWORD __RPC_FAR *pdwProtocol);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HandleConfirmationFromOurXln )( 
            IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
            /* [in] */ DTCLUXLNCONFIRMATION Confirmation);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HandleTheirXlnResponse )( 
            IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
            /* [in] */ DTCLUXLN Xln,
            /* [in] */ unsigned char __RPC_FAR *pRemoteLogName,
            /* [in] */ DWORD cbRemoteLogName,
            /* [in] */ DWORD dwProtocol,
            /* [out] */ DTCLUXLNCONFIRMATION __RPC_FAR *pConfirmation);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HandleErrorFromOurXln )( 
            IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
            /* [in] */ DTCLUXLNERROR Error);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckForCompareStates )( 
            IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *fCompareStates);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOurTransIdSize )( 
            IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
            /* [out][in] */ DWORD __RPC_FAR *pcbOurTransId);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOurCompareStates )( 
            IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
            /* [out][in] */ unsigned char __RPC_FAR *pOurTransId,
            /* [out] */ DTCLUCOMPARESTATE __RPC_FAR *pCompareState);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HandleTheirCompareStatesResponse )( 
            IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
            /* [in] */ DTCLUCOMPARESTATE CompareState,
            /* [out] */ DTCLUCOMPARESTATESCONFIRMATION __RPC_FAR *pConfirmation);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HandleErrorFromOurCompareStates )( 
            IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
            /* [in] */ DTCLUCOMPARESTATESERROR Error);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConversationLost )( 
            IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRecoverySeqNum )( 
            IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
            /* [out] */ LONG __RPC_FAR *plRecoverySeqNum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ObsoleteRecoverySeqNum )( 
            IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
            /* [in] */ LONG lNewRecoverySeqNum);
        
        END_INTERFACE
    } IDtcLuRecoveryInitiatedByDtcTransWorkVtbl;

    interface IDtcLuRecoveryInitiatedByDtcTransWork
    {
        CONST_VTBL struct IDtcLuRecoveryInitiatedByDtcTransWorkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDtcLuRecoveryInitiatedByDtcTransWork_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDtcLuRecoveryInitiatedByDtcTransWork_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDtcLuRecoveryInitiatedByDtcTransWork_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDtcLuRecoveryInitiatedByDtcTransWork_GetLogNameSizes(This,pcbOurLogName,pcbRemoteLogName)	\
    (This)->lpVtbl -> GetLogNameSizes(This,pcbOurLogName,pcbRemoteLogName)

#define IDtcLuRecoveryInitiatedByDtcTransWork_GetOurXln(This,pXln,pOurLogName,pRemoteLogName,pdwProtocol)	\
    (This)->lpVtbl -> GetOurXln(This,pXln,pOurLogName,pRemoteLogName,pdwProtocol)

#define IDtcLuRecoveryInitiatedByDtcTransWork_HandleConfirmationFromOurXln(This,Confirmation)	\
    (This)->lpVtbl -> HandleConfirmationFromOurXln(This,Confirmation)

#define IDtcLuRecoveryInitiatedByDtcTransWork_HandleTheirXlnResponse(This,Xln,pRemoteLogName,cbRemoteLogName,dwProtocol,pConfirmation)	\
    (This)->lpVtbl -> HandleTheirXlnResponse(This,Xln,pRemoteLogName,cbRemoteLogName,dwProtocol,pConfirmation)

#define IDtcLuRecoveryInitiatedByDtcTransWork_HandleErrorFromOurXln(This,Error)	\
    (This)->lpVtbl -> HandleErrorFromOurXln(This,Error)

#define IDtcLuRecoveryInitiatedByDtcTransWork_CheckForCompareStates(This,fCompareStates)	\
    (This)->lpVtbl -> CheckForCompareStates(This,fCompareStates)

#define IDtcLuRecoveryInitiatedByDtcTransWork_GetOurTransIdSize(This,pcbOurTransId)	\
    (This)->lpVtbl -> GetOurTransIdSize(This,pcbOurTransId)

#define IDtcLuRecoveryInitiatedByDtcTransWork_GetOurCompareStates(This,pOurTransId,pCompareState)	\
    (This)->lpVtbl -> GetOurCompareStates(This,pOurTransId,pCompareState)

#define IDtcLuRecoveryInitiatedByDtcTransWork_HandleTheirCompareStatesResponse(This,CompareState,pConfirmation)	\
    (This)->lpVtbl -> HandleTheirCompareStatesResponse(This,CompareState,pConfirmation)

#define IDtcLuRecoveryInitiatedByDtcTransWork_HandleErrorFromOurCompareStates(This,Error)	\
    (This)->lpVtbl -> HandleErrorFromOurCompareStates(This,Error)

#define IDtcLuRecoveryInitiatedByDtcTransWork_ConversationLost(This)	\
    (This)->lpVtbl -> ConversationLost(This)

#define IDtcLuRecoveryInitiatedByDtcTransWork_GetRecoverySeqNum(This,plRecoverySeqNum)	\
    (This)->lpVtbl -> GetRecoverySeqNum(This,plRecoverySeqNum)

#define IDtcLuRecoveryInitiatedByDtcTransWork_ObsoleteRecoverySeqNum(This,lNewRecoverySeqNum)	\
    (This)->lpVtbl -> ObsoleteRecoverySeqNum(This,lNewRecoverySeqNum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByDtcTransWork_GetLogNameSizes_Proxy( 
    IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pcbOurLogName,
    /* [out] */ DWORD __RPC_FAR *pcbRemoteLogName);


void __RPC_STUB IDtcLuRecoveryInitiatedByDtcTransWork_GetLogNameSizes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByDtcTransWork_GetOurXln_Proxy( 
    IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
    /* [out] */ DTCLUXLN __RPC_FAR *pXln,
    /* [out][in] */ unsigned char __RPC_FAR *pOurLogName,
    /* [out][in] */ unsigned char __RPC_FAR *pRemoteLogName,
    /* [out] */ DWORD __RPC_FAR *pdwProtocol);


void __RPC_STUB IDtcLuRecoveryInitiatedByDtcTransWork_GetOurXln_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByDtcTransWork_HandleConfirmationFromOurXln_Proxy( 
    IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
    /* [in] */ DTCLUXLNCONFIRMATION Confirmation);


void __RPC_STUB IDtcLuRecoveryInitiatedByDtcTransWork_HandleConfirmationFromOurXln_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByDtcTransWork_HandleTheirXlnResponse_Proxy( 
    IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
    /* [in] */ DTCLUXLN Xln,
    /* [in] */ unsigned char __RPC_FAR *pRemoteLogName,
    /* [in] */ DWORD cbRemoteLogName,
    /* [in] */ DWORD dwProtocol,
    /* [out] */ DTCLUXLNCONFIRMATION __RPC_FAR *pConfirmation);


void __RPC_STUB IDtcLuRecoveryInitiatedByDtcTransWork_HandleTheirXlnResponse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByDtcTransWork_HandleErrorFromOurXln_Proxy( 
    IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
    /* [in] */ DTCLUXLNERROR Error);


void __RPC_STUB IDtcLuRecoveryInitiatedByDtcTransWork_HandleErrorFromOurXln_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByDtcTransWork_CheckForCompareStates_Proxy( 
    IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *fCompareStates);


void __RPC_STUB IDtcLuRecoveryInitiatedByDtcTransWork_CheckForCompareStates_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByDtcTransWork_GetOurTransIdSize_Proxy( 
    IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
    /* [out][in] */ DWORD __RPC_FAR *pcbOurTransId);


void __RPC_STUB IDtcLuRecoveryInitiatedByDtcTransWork_GetOurTransIdSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByDtcTransWork_GetOurCompareStates_Proxy( 
    IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
    /* [out][in] */ unsigned char __RPC_FAR *pOurTransId,
    /* [out] */ DTCLUCOMPARESTATE __RPC_FAR *pCompareState);


void __RPC_STUB IDtcLuRecoveryInitiatedByDtcTransWork_GetOurCompareStates_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByDtcTransWork_HandleTheirCompareStatesResponse_Proxy( 
    IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
    /* [in] */ DTCLUCOMPARESTATE CompareState,
    /* [out] */ DTCLUCOMPARESTATESCONFIRMATION __RPC_FAR *pConfirmation);


void __RPC_STUB IDtcLuRecoveryInitiatedByDtcTransWork_HandleTheirCompareStatesResponse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByDtcTransWork_HandleErrorFromOurCompareStates_Proxy( 
    IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
    /* [in] */ DTCLUCOMPARESTATESERROR Error);


void __RPC_STUB IDtcLuRecoveryInitiatedByDtcTransWork_HandleErrorFromOurCompareStates_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByDtcTransWork_ConversationLost_Proxy( 
    IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This);


void __RPC_STUB IDtcLuRecoveryInitiatedByDtcTransWork_ConversationLost_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByDtcTransWork_GetRecoverySeqNum_Proxy( 
    IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
    /* [out] */ LONG __RPC_FAR *plRecoverySeqNum);


void __RPC_STUB IDtcLuRecoveryInitiatedByDtcTransWork_GetRecoverySeqNum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByDtcTransWork_ObsoleteRecoverySeqNum_Proxy( 
    IDtcLuRecoveryInitiatedByDtcTransWork __RPC_FAR * This,
    /* [in] */ LONG lNewRecoverySeqNum);


void __RPC_STUB IDtcLuRecoveryInitiatedByDtcTransWork_ObsoleteRecoverySeqNum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDtcLuRecoveryInitiatedByDtcTransWork_INTERFACE_DEFINED__ */


#ifndef __IDtcLuRecoveryInitiatedByDtcStatusWork_INTERFACE_DEFINED__
#define __IDtcLuRecoveryInitiatedByDtcStatusWork_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDtcLuRecoveryInitiatedByDtcStatusWork
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][unique][object] */ 



EXTERN_C const IID IID_IDtcLuRecoveryInitiatedByDtcStatusWork;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("4131E766-1AEA-11d0-944B-00A0C905416E")
    IDtcLuRecoveryInitiatedByDtcStatusWork : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE HandleCheckLuStatus( 
            /* [in] */ LONG lRecoverySeqNum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDtcLuRecoveryInitiatedByDtcStatusWorkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDtcLuRecoveryInitiatedByDtcStatusWork __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDtcLuRecoveryInitiatedByDtcStatusWork __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDtcLuRecoveryInitiatedByDtcStatusWork __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HandleCheckLuStatus )( 
            IDtcLuRecoveryInitiatedByDtcStatusWork __RPC_FAR * This,
            /* [in] */ LONG lRecoverySeqNum);
        
        END_INTERFACE
    } IDtcLuRecoveryInitiatedByDtcStatusWorkVtbl;

    interface IDtcLuRecoveryInitiatedByDtcStatusWork
    {
        CONST_VTBL struct IDtcLuRecoveryInitiatedByDtcStatusWorkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDtcLuRecoveryInitiatedByDtcStatusWork_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDtcLuRecoveryInitiatedByDtcStatusWork_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDtcLuRecoveryInitiatedByDtcStatusWork_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDtcLuRecoveryInitiatedByDtcStatusWork_HandleCheckLuStatus(This,lRecoverySeqNum)	\
    (This)->lpVtbl -> HandleCheckLuStatus(This,lRecoverySeqNum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByDtcStatusWork_HandleCheckLuStatus_Proxy( 
    IDtcLuRecoveryInitiatedByDtcStatusWork __RPC_FAR * This,
    /* [in] */ LONG lRecoverySeqNum);


void __RPC_STUB IDtcLuRecoveryInitiatedByDtcStatusWork_HandleCheckLuStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDtcLuRecoveryInitiatedByDtcStatusWork_INTERFACE_DEFINED__ */


#ifndef __IDtcLuRecoveryInitiatedByDtc_INTERFACE_DEFINED__
#define __IDtcLuRecoveryInitiatedByDtc_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDtcLuRecoveryInitiatedByDtc
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [local][uuid][unique][object] */ 



EXTERN_C const IID IID_IDtcLuRecoveryInitiatedByDtc;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("4131E764-1AEA-11d0-944B-00A0C905416E")
    IDtcLuRecoveryInitiatedByDtc : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetWork( 
            /* [out][in] */ DTCINITIATEDRECOVERYWORK __RPC_FAR *pWork,
            /* [out][in] */ void __RPC_FAR *__RPC_FAR *ppv) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDtcLuRecoveryInitiatedByDtcVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDtcLuRecoveryInitiatedByDtc __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDtcLuRecoveryInitiatedByDtc __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDtcLuRecoveryInitiatedByDtc __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWork )( 
            IDtcLuRecoveryInitiatedByDtc __RPC_FAR * This,
            /* [out][in] */ DTCINITIATEDRECOVERYWORK __RPC_FAR *pWork,
            /* [out][in] */ void __RPC_FAR *__RPC_FAR *ppv);
        
        END_INTERFACE
    } IDtcLuRecoveryInitiatedByDtcVtbl;

    interface IDtcLuRecoveryInitiatedByDtc
    {
        CONST_VTBL struct IDtcLuRecoveryInitiatedByDtcVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDtcLuRecoveryInitiatedByDtc_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDtcLuRecoveryInitiatedByDtc_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDtcLuRecoveryInitiatedByDtc_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDtcLuRecoveryInitiatedByDtc_GetWork(This,pWork,ppv)	\
    (This)->lpVtbl -> GetWork(This,pWork,ppv)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByDtc_GetWork_Proxy( 
    IDtcLuRecoveryInitiatedByDtc __RPC_FAR * This,
    /* [out][in] */ DTCINITIATEDRECOVERYWORK __RPC_FAR *pWork,
    /* [out][in] */ void __RPC_FAR *__RPC_FAR *ppv);


void __RPC_STUB IDtcLuRecoveryInitiatedByDtc_GetWork_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDtcLuRecoveryInitiatedByDtc_INTERFACE_DEFINED__ */


#ifndef __IDtcLuRecoveryInitiatedByLuWork_INTERFACE_DEFINED__
#define __IDtcLuRecoveryInitiatedByLuWork_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDtcLuRecoveryInitiatedByLuWork
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][unique][object] */ 



EXTERN_C const IID IID_IDtcLuRecoveryInitiatedByLuWork;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("AC2B8AD1-D6F0-11d0-B386-00A0C9083365")
    IDtcLuRecoveryInitiatedByLuWork : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE HandleTheirXln( 
            /* [in] */ LONG lRecoverySeqNum,
            /* [in] */ DTCLUXLN Xln,
            /* [in] */ unsigned char __RPC_FAR *pRemoteLogName,
            /* [in] */ DWORD cbRemoteLogName,
            /* [in] */ unsigned char __RPC_FAR *pOurLogName,
            /* [in] */ DWORD cbOurLogName,
            /* [in] */ DWORD dwProtocol,
            /* [out] */ DTCLUXLNRESPONSE __RPC_FAR *pResponse) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOurLogNameSize( 
            /* [out][in] */ DWORD __RPC_FAR *pcbOurLogName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOurXln( 
            /* [out] */ DTCLUXLN __RPC_FAR *pXln,
            /* [out][in] */ unsigned char __RPC_FAR *pOurLogName,
            /* [out] */ DWORD __RPC_FAR *pdwProtocol) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HandleConfirmationOfOurXln( 
            /* [in] */ DTCLUXLNCONFIRMATION Confirmation) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HandleTheirCompareStates( 
            /* [out][in] */ unsigned char __RPC_FAR *pRemoteTransId,
            /* [in] */ DWORD cbRemoteTransId,
            /* [in] */ DTCLUCOMPARESTATE CompareState,
            /* [out] */ DTCLUCOMPARESTATESRESPONSE __RPC_FAR *pResponse,
            /* [out] */ DTCLUCOMPARESTATE __RPC_FAR *pCompareState) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HandleConfirmationOfOurCompareStates( 
            /* [in] */ DTCLUCOMPARESTATESCONFIRMATION Confirmation) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE HandleErrorFromOurCompareStates( 
            /* [in] */ DTCLUCOMPARESTATESERROR Error) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConversationLost( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDtcLuRecoveryInitiatedByLuWorkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDtcLuRecoveryInitiatedByLuWork __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDtcLuRecoveryInitiatedByLuWork __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDtcLuRecoveryInitiatedByLuWork __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HandleTheirXln )( 
            IDtcLuRecoveryInitiatedByLuWork __RPC_FAR * This,
            /* [in] */ LONG lRecoverySeqNum,
            /* [in] */ DTCLUXLN Xln,
            /* [in] */ unsigned char __RPC_FAR *pRemoteLogName,
            /* [in] */ DWORD cbRemoteLogName,
            /* [in] */ unsigned char __RPC_FAR *pOurLogName,
            /* [in] */ DWORD cbOurLogName,
            /* [in] */ DWORD dwProtocol,
            /* [out] */ DTCLUXLNRESPONSE __RPC_FAR *pResponse);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOurLogNameSize )( 
            IDtcLuRecoveryInitiatedByLuWork __RPC_FAR * This,
            /* [out][in] */ DWORD __RPC_FAR *pcbOurLogName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOurXln )( 
            IDtcLuRecoveryInitiatedByLuWork __RPC_FAR * This,
            /* [out] */ DTCLUXLN __RPC_FAR *pXln,
            /* [out][in] */ unsigned char __RPC_FAR *pOurLogName,
            /* [out] */ DWORD __RPC_FAR *pdwProtocol);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HandleConfirmationOfOurXln )( 
            IDtcLuRecoveryInitiatedByLuWork __RPC_FAR * This,
            /* [in] */ DTCLUXLNCONFIRMATION Confirmation);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HandleTheirCompareStates )( 
            IDtcLuRecoveryInitiatedByLuWork __RPC_FAR * This,
            /* [out][in] */ unsigned char __RPC_FAR *pRemoteTransId,
            /* [in] */ DWORD cbRemoteTransId,
            /* [in] */ DTCLUCOMPARESTATE CompareState,
            /* [out] */ DTCLUCOMPARESTATESRESPONSE __RPC_FAR *pResponse,
            /* [out] */ DTCLUCOMPARESTATE __RPC_FAR *pCompareState);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HandleConfirmationOfOurCompareStates )( 
            IDtcLuRecoveryInitiatedByLuWork __RPC_FAR * This,
            /* [in] */ DTCLUCOMPARESTATESCONFIRMATION Confirmation);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HandleErrorFromOurCompareStates )( 
            IDtcLuRecoveryInitiatedByLuWork __RPC_FAR * This,
            /* [in] */ DTCLUCOMPARESTATESERROR Error);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConversationLost )( 
            IDtcLuRecoveryInitiatedByLuWork __RPC_FAR * This);
        
        END_INTERFACE
    } IDtcLuRecoveryInitiatedByLuWorkVtbl;

    interface IDtcLuRecoveryInitiatedByLuWork
    {
        CONST_VTBL struct IDtcLuRecoveryInitiatedByLuWorkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDtcLuRecoveryInitiatedByLuWork_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDtcLuRecoveryInitiatedByLuWork_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDtcLuRecoveryInitiatedByLuWork_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDtcLuRecoveryInitiatedByLuWork_HandleTheirXln(This,lRecoverySeqNum,Xln,pRemoteLogName,cbRemoteLogName,pOurLogName,cbOurLogName,dwProtocol,pResponse)	\
    (This)->lpVtbl -> HandleTheirXln(This,lRecoverySeqNum,Xln,pRemoteLogName,cbRemoteLogName,pOurLogName,cbOurLogName,dwProtocol,pResponse)

#define IDtcLuRecoveryInitiatedByLuWork_GetOurLogNameSize(This,pcbOurLogName)	\
    (This)->lpVtbl -> GetOurLogNameSize(This,pcbOurLogName)

#define IDtcLuRecoveryInitiatedByLuWork_GetOurXln(This,pXln,pOurLogName,pdwProtocol)	\
    (This)->lpVtbl -> GetOurXln(This,pXln,pOurLogName,pdwProtocol)

#define IDtcLuRecoveryInitiatedByLuWork_HandleConfirmationOfOurXln(This,Confirmation)	\
    (This)->lpVtbl -> HandleConfirmationOfOurXln(This,Confirmation)

#define IDtcLuRecoveryInitiatedByLuWork_HandleTheirCompareStates(This,pRemoteTransId,cbRemoteTransId,CompareState,pResponse,pCompareState)	\
    (This)->lpVtbl -> HandleTheirCompareStates(This,pRemoteTransId,cbRemoteTransId,CompareState,pResponse,pCompareState)

#define IDtcLuRecoveryInitiatedByLuWork_HandleConfirmationOfOurCompareStates(This,Confirmation)	\
    (This)->lpVtbl -> HandleConfirmationOfOurCompareStates(This,Confirmation)

#define IDtcLuRecoveryInitiatedByLuWork_HandleErrorFromOurCompareStates(This,Error)	\
    (This)->lpVtbl -> HandleErrorFromOurCompareStates(This,Error)

#define IDtcLuRecoveryInitiatedByLuWork_ConversationLost(This)	\
    (This)->lpVtbl -> ConversationLost(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByLuWork_HandleTheirXln_Proxy( 
    IDtcLuRecoveryInitiatedByLuWork __RPC_FAR * This,
    /* [in] */ LONG lRecoverySeqNum,
    /* [in] */ DTCLUXLN Xln,
    /* [in] */ unsigned char __RPC_FAR *pRemoteLogName,
    /* [in] */ DWORD cbRemoteLogName,
    /* [in] */ unsigned char __RPC_FAR *pOurLogName,
    /* [in] */ DWORD cbOurLogName,
    /* [in] */ DWORD dwProtocol,
    /* [out] */ DTCLUXLNRESPONSE __RPC_FAR *pResponse);


void __RPC_STUB IDtcLuRecoveryInitiatedByLuWork_HandleTheirXln_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByLuWork_GetOurLogNameSize_Proxy( 
    IDtcLuRecoveryInitiatedByLuWork __RPC_FAR * This,
    /* [out][in] */ DWORD __RPC_FAR *pcbOurLogName);


void __RPC_STUB IDtcLuRecoveryInitiatedByLuWork_GetOurLogNameSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByLuWork_GetOurXln_Proxy( 
    IDtcLuRecoveryInitiatedByLuWork __RPC_FAR * This,
    /* [out] */ DTCLUXLN __RPC_FAR *pXln,
    /* [out][in] */ unsigned char __RPC_FAR *pOurLogName,
    /* [out] */ DWORD __RPC_FAR *pdwProtocol);


void __RPC_STUB IDtcLuRecoveryInitiatedByLuWork_GetOurXln_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByLuWork_HandleConfirmationOfOurXln_Proxy( 
    IDtcLuRecoveryInitiatedByLuWork __RPC_FAR * This,
    /* [in] */ DTCLUXLNCONFIRMATION Confirmation);


void __RPC_STUB IDtcLuRecoveryInitiatedByLuWork_HandleConfirmationOfOurXln_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByLuWork_HandleTheirCompareStates_Proxy( 
    IDtcLuRecoveryInitiatedByLuWork __RPC_FAR * This,
    /* [out][in] */ unsigned char __RPC_FAR *pRemoteTransId,
    /* [in] */ DWORD cbRemoteTransId,
    /* [in] */ DTCLUCOMPARESTATE CompareState,
    /* [out] */ DTCLUCOMPARESTATESRESPONSE __RPC_FAR *pResponse,
    /* [out] */ DTCLUCOMPARESTATE __RPC_FAR *pCompareState);


void __RPC_STUB IDtcLuRecoveryInitiatedByLuWork_HandleTheirCompareStates_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByLuWork_HandleConfirmationOfOurCompareStates_Proxy( 
    IDtcLuRecoveryInitiatedByLuWork __RPC_FAR * This,
    /* [in] */ DTCLUCOMPARESTATESCONFIRMATION Confirmation);


void __RPC_STUB IDtcLuRecoveryInitiatedByLuWork_HandleConfirmationOfOurCompareStates_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByLuWork_HandleErrorFromOurCompareStates_Proxy( 
    IDtcLuRecoveryInitiatedByLuWork __RPC_FAR * This,
    /* [in] */ DTCLUCOMPARESTATESERROR Error);


void __RPC_STUB IDtcLuRecoveryInitiatedByLuWork_HandleErrorFromOurCompareStates_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByLuWork_ConversationLost_Proxy( 
    IDtcLuRecoveryInitiatedByLuWork __RPC_FAR * This);


void __RPC_STUB IDtcLuRecoveryInitiatedByLuWork_ConversationLost_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDtcLuRecoveryInitiatedByLuWork_INTERFACE_DEFINED__ */


#ifndef __IDtcLuRecoveryInitiatedByLu_INTERFACE_DEFINED__
#define __IDtcLuRecoveryInitiatedByLu_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDtcLuRecoveryInitiatedByLu
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][unique][object] */ 



EXTERN_C const IID IID_IDtcLuRecoveryInitiatedByLu;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("4131E768-1AEA-11d0-944B-00A0C905416E")
    IDtcLuRecoveryInitiatedByLu : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetObjectToHandleWorkFromLu( 
            /* [out][in] */ IDtcLuRecoveryInitiatedByLuWork __RPC_FAR *__RPC_FAR *ppWork) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDtcLuRecoveryInitiatedByLuVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDtcLuRecoveryInitiatedByLu __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDtcLuRecoveryInitiatedByLu __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDtcLuRecoveryInitiatedByLu __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetObjectToHandleWorkFromLu )( 
            IDtcLuRecoveryInitiatedByLu __RPC_FAR * This,
            /* [out][in] */ IDtcLuRecoveryInitiatedByLuWork __RPC_FAR *__RPC_FAR *ppWork);
        
        END_INTERFACE
    } IDtcLuRecoveryInitiatedByLuVtbl;

    interface IDtcLuRecoveryInitiatedByLu
    {
        CONST_VTBL struct IDtcLuRecoveryInitiatedByLuVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDtcLuRecoveryInitiatedByLu_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDtcLuRecoveryInitiatedByLu_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDtcLuRecoveryInitiatedByLu_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDtcLuRecoveryInitiatedByLu_GetObjectToHandleWorkFromLu(This,ppWork)	\
    (This)->lpVtbl -> GetObjectToHandleWorkFromLu(This,ppWork)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDtcLuRecoveryInitiatedByLu_GetObjectToHandleWorkFromLu_Proxy( 
    IDtcLuRecoveryInitiatedByLu __RPC_FAR * This,
    /* [out][in] */ IDtcLuRecoveryInitiatedByLuWork __RPC_FAR *__RPC_FAR *ppWork);


void __RPC_STUB IDtcLuRecoveryInitiatedByLu_GetObjectToHandleWorkFromLu_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDtcLuRecoveryInitiatedByLu_INTERFACE_DEFINED__ */


#ifndef __IDtcLuRmEnlistment_INTERFACE_DEFINED__
#define __IDtcLuRmEnlistment_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDtcLuRmEnlistment
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][unique][object] */ 



EXTERN_C const IID IID_IDtcLuRmEnlistment;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("4131E769-1AEA-11d0-944B-00A0C905416E")
    IDtcLuRmEnlistment : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Unplug( 
            BOOL fConversationLost) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BackedOut( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BackOut( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Committed( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Forget( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RequestCommit( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDtcLuRmEnlistmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDtcLuRmEnlistment __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDtcLuRmEnlistment __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDtcLuRmEnlistment __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Unplug )( 
            IDtcLuRmEnlistment __RPC_FAR * This,
            BOOL fConversationLost);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BackedOut )( 
            IDtcLuRmEnlistment __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BackOut )( 
            IDtcLuRmEnlistment __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Committed )( 
            IDtcLuRmEnlistment __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Forget )( 
            IDtcLuRmEnlistment __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestCommit )( 
            IDtcLuRmEnlistment __RPC_FAR * This);
        
        END_INTERFACE
    } IDtcLuRmEnlistmentVtbl;

    interface IDtcLuRmEnlistment
    {
        CONST_VTBL struct IDtcLuRmEnlistmentVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDtcLuRmEnlistment_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDtcLuRmEnlistment_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDtcLuRmEnlistment_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDtcLuRmEnlistment_Unplug(This,fConversationLost)	\
    (This)->lpVtbl -> Unplug(This,fConversationLost)

#define IDtcLuRmEnlistment_BackedOut(This)	\
    (This)->lpVtbl -> BackedOut(This)

#define IDtcLuRmEnlistment_BackOut(This)	\
    (This)->lpVtbl -> BackOut(This)

#define IDtcLuRmEnlistment_Committed(This)	\
    (This)->lpVtbl -> Committed(This)

#define IDtcLuRmEnlistment_Forget(This)	\
    (This)->lpVtbl -> Forget(This)

#define IDtcLuRmEnlistment_RequestCommit(This)	\
    (This)->lpVtbl -> RequestCommit(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDtcLuRmEnlistment_Unplug_Proxy( 
    IDtcLuRmEnlistment __RPC_FAR * This,
    BOOL fConversationLost);


void __RPC_STUB IDtcLuRmEnlistment_Unplug_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRmEnlistment_BackedOut_Proxy( 
    IDtcLuRmEnlistment __RPC_FAR * This);


void __RPC_STUB IDtcLuRmEnlistment_BackedOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRmEnlistment_BackOut_Proxy( 
    IDtcLuRmEnlistment __RPC_FAR * This);


void __RPC_STUB IDtcLuRmEnlistment_BackOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRmEnlistment_Committed_Proxy( 
    IDtcLuRmEnlistment __RPC_FAR * This);


void __RPC_STUB IDtcLuRmEnlistment_Committed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRmEnlistment_Forget_Proxy( 
    IDtcLuRmEnlistment __RPC_FAR * This);


void __RPC_STUB IDtcLuRmEnlistment_Forget_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRmEnlistment_RequestCommit_Proxy( 
    IDtcLuRmEnlistment __RPC_FAR * This);


void __RPC_STUB IDtcLuRmEnlistment_RequestCommit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDtcLuRmEnlistment_INTERFACE_DEFINED__ */


#ifndef __IDtcLuRmEnlistmentSink_INTERFACE_DEFINED__
#define __IDtcLuRmEnlistmentSink_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDtcLuRmEnlistmentSink
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][unique][object] */ 



EXTERN_C const IID IID_IDtcLuRmEnlistmentSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("4131E770-1AEA-11d0-944B-00A0C905416E")
    IDtcLuRmEnlistmentSink : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AckUnplug( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TmDown( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SessionLost( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BackedOut( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BackOut( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Committed( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Forget( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Prepare( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RequestCommit( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDtcLuRmEnlistmentSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDtcLuRmEnlistmentSink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDtcLuRmEnlistmentSink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDtcLuRmEnlistmentSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AckUnplug )( 
            IDtcLuRmEnlistmentSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TmDown )( 
            IDtcLuRmEnlistmentSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SessionLost )( 
            IDtcLuRmEnlistmentSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BackedOut )( 
            IDtcLuRmEnlistmentSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BackOut )( 
            IDtcLuRmEnlistmentSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Committed )( 
            IDtcLuRmEnlistmentSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Forget )( 
            IDtcLuRmEnlistmentSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Prepare )( 
            IDtcLuRmEnlistmentSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestCommit )( 
            IDtcLuRmEnlistmentSink __RPC_FAR * This);
        
        END_INTERFACE
    } IDtcLuRmEnlistmentSinkVtbl;

    interface IDtcLuRmEnlistmentSink
    {
        CONST_VTBL struct IDtcLuRmEnlistmentSinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDtcLuRmEnlistmentSink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDtcLuRmEnlistmentSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDtcLuRmEnlistmentSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDtcLuRmEnlistmentSink_AckUnplug(This)	\
    (This)->lpVtbl -> AckUnplug(This)

#define IDtcLuRmEnlistmentSink_TmDown(This)	\
    (This)->lpVtbl -> TmDown(This)

#define IDtcLuRmEnlistmentSink_SessionLost(This)	\
    (This)->lpVtbl -> SessionLost(This)

#define IDtcLuRmEnlistmentSink_BackedOut(This)	\
    (This)->lpVtbl -> BackedOut(This)

#define IDtcLuRmEnlistmentSink_BackOut(This)	\
    (This)->lpVtbl -> BackOut(This)

#define IDtcLuRmEnlistmentSink_Committed(This)	\
    (This)->lpVtbl -> Committed(This)

#define IDtcLuRmEnlistmentSink_Forget(This)	\
    (This)->lpVtbl -> Forget(This)

#define IDtcLuRmEnlistmentSink_Prepare(This)	\
    (This)->lpVtbl -> Prepare(This)

#define IDtcLuRmEnlistmentSink_RequestCommit(This)	\
    (This)->lpVtbl -> RequestCommit(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDtcLuRmEnlistmentSink_AckUnplug_Proxy( 
    IDtcLuRmEnlistmentSink __RPC_FAR * This);


void __RPC_STUB IDtcLuRmEnlistmentSink_AckUnplug_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRmEnlistmentSink_TmDown_Proxy( 
    IDtcLuRmEnlistmentSink __RPC_FAR * This);


void __RPC_STUB IDtcLuRmEnlistmentSink_TmDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRmEnlistmentSink_SessionLost_Proxy( 
    IDtcLuRmEnlistmentSink __RPC_FAR * This);


void __RPC_STUB IDtcLuRmEnlistmentSink_SessionLost_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRmEnlistmentSink_BackedOut_Proxy( 
    IDtcLuRmEnlistmentSink __RPC_FAR * This);


void __RPC_STUB IDtcLuRmEnlistmentSink_BackedOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRmEnlistmentSink_BackOut_Proxy( 
    IDtcLuRmEnlistmentSink __RPC_FAR * This);


void __RPC_STUB IDtcLuRmEnlistmentSink_BackOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRmEnlistmentSink_Committed_Proxy( 
    IDtcLuRmEnlistmentSink __RPC_FAR * This);


void __RPC_STUB IDtcLuRmEnlistmentSink_Committed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRmEnlistmentSink_Forget_Proxy( 
    IDtcLuRmEnlistmentSink __RPC_FAR * This);


void __RPC_STUB IDtcLuRmEnlistmentSink_Forget_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRmEnlistmentSink_Prepare_Proxy( 
    IDtcLuRmEnlistmentSink __RPC_FAR * This);


void __RPC_STUB IDtcLuRmEnlistmentSink_Prepare_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuRmEnlistmentSink_RequestCommit_Proxy( 
    IDtcLuRmEnlistmentSink __RPC_FAR * This);


void __RPC_STUB IDtcLuRmEnlistmentSink_RequestCommit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDtcLuRmEnlistmentSink_INTERFACE_DEFINED__ */


#ifndef __IDtcLuRmEnlistmentFactory_INTERFACE_DEFINED__
#define __IDtcLuRmEnlistmentFactory_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDtcLuRmEnlistmentFactory
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][unique][object] */ 



EXTERN_C const IID IID_IDtcLuRmEnlistmentFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("4131E771-1AEA-11d0-944B-00A0C905416E")
    IDtcLuRmEnlistmentFactory : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ unsigned char __RPC_FAR *pucLuPair,
            /* [in] */ DWORD cbLuPair,
            /* [in] */ ITransaction __RPC_FAR *pITransaction,
            /* [in] */ unsigned char __RPC_FAR *pTransId,
            /* [in] */ DWORD cbTransId,
            /* [in] */ IDtcLuRmEnlistmentSink __RPC_FAR *pRmEnlistmentSink,
            /* [out][in] */ IDtcLuRmEnlistment __RPC_FAR *__RPC_FAR *ppRmEnlistment) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDtcLuRmEnlistmentFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDtcLuRmEnlistmentFactory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDtcLuRmEnlistmentFactory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDtcLuRmEnlistmentFactory __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Create )( 
            IDtcLuRmEnlistmentFactory __RPC_FAR * This,
            /* [in] */ unsigned char __RPC_FAR *pucLuPair,
            /* [in] */ DWORD cbLuPair,
            /* [in] */ ITransaction __RPC_FAR *pITransaction,
            /* [in] */ unsigned char __RPC_FAR *pTransId,
            /* [in] */ DWORD cbTransId,
            /* [in] */ IDtcLuRmEnlistmentSink __RPC_FAR *pRmEnlistmentSink,
            /* [out][in] */ IDtcLuRmEnlistment __RPC_FAR *__RPC_FAR *ppRmEnlistment);
        
        END_INTERFACE
    } IDtcLuRmEnlistmentFactoryVtbl;

    interface IDtcLuRmEnlistmentFactory
    {
        CONST_VTBL struct IDtcLuRmEnlistmentFactoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDtcLuRmEnlistmentFactory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDtcLuRmEnlistmentFactory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDtcLuRmEnlistmentFactory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDtcLuRmEnlistmentFactory_Create(This,pucLuPair,cbLuPair,pITransaction,pTransId,cbTransId,pRmEnlistmentSink,ppRmEnlistment)	\
    (This)->lpVtbl -> Create(This,pucLuPair,cbLuPair,pITransaction,pTransId,cbTransId,pRmEnlistmentSink,ppRmEnlistment)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDtcLuRmEnlistmentFactory_Create_Proxy( 
    IDtcLuRmEnlistmentFactory __RPC_FAR * This,
    /* [in] */ unsigned char __RPC_FAR *pucLuPair,
    /* [in] */ DWORD cbLuPair,
    /* [in] */ ITransaction __RPC_FAR *pITransaction,
    /* [in] */ unsigned char __RPC_FAR *pTransId,
    /* [in] */ DWORD cbTransId,
    /* [in] */ IDtcLuRmEnlistmentSink __RPC_FAR *pRmEnlistmentSink,
    /* [out][in] */ IDtcLuRmEnlistment __RPC_FAR *__RPC_FAR *ppRmEnlistment);


void __RPC_STUB IDtcLuRmEnlistmentFactory_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDtcLuRmEnlistmentFactory_INTERFACE_DEFINED__ */


#ifndef __IDtcLuSubordinateDtc_INTERFACE_DEFINED__
#define __IDtcLuSubordinateDtc_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDtcLuSubordinateDtc
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][unique][object] */ 



EXTERN_C const IID IID_IDtcLuSubordinateDtc;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("4131E773-1AEA-11d0-944B-00A0C905416E")
    IDtcLuSubordinateDtc : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Unplug( 
            BOOL fConversationLost) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BackedOut( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BackOut( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Committed( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Forget( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Prepare( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RequestCommit( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDtcLuSubordinateDtcVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDtcLuSubordinateDtc __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDtcLuSubordinateDtc __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDtcLuSubordinateDtc __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Unplug )( 
            IDtcLuSubordinateDtc __RPC_FAR * This,
            BOOL fConversationLost);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BackedOut )( 
            IDtcLuSubordinateDtc __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BackOut )( 
            IDtcLuSubordinateDtc __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Committed )( 
            IDtcLuSubordinateDtc __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Forget )( 
            IDtcLuSubordinateDtc __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Prepare )( 
            IDtcLuSubordinateDtc __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestCommit )( 
            IDtcLuSubordinateDtc __RPC_FAR * This);
        
        END_INTERFACE
    } IDtcLuSubordinateDtcVtbl;

    interface IDtcLuSubordinateDtc
    {
        CONST_VTBL struct IDtcLuSubordinateDtcVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDtcLuSubordinateDtc_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDtcLuSubordinateDtc_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDtcLuSubordinateDtc_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDtcLuSubordinateDtc_Unplug(This,fConversationLost)	\
    (This)->lpVtbl -> Unplug(This,fConversationLost)

#define IDtcLuSubordinateDtc_BackedOut(This)	\
    (This)->lpVtbl -> BackedOut(This)

#define IDtcLuSubordinateDtc_BackOut(This)	\
    (This)->lpVtbl -> BackOut(This)

#define IDtcLuSubordinateDtc_Committed(This)	\
    (This)->lpVtbl -> Committed(This)

#define IDtcLuSubordinateDtc_Forget(This)	\
    (This)->lpVtbl -> Forget(This)

#define IDtcLuSubordinateDtc_Prepare(This)	\
    (This)->lpVtbl -> Prepare(This)

#define IDtcLuSubordinateDtc_RequestCommit(This)	\
    (This)->lpVtbl -> RequestCommit(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDtcLuSubordinateDtc_Unplug_Proxy( 
    IDtcLuSubordinateDtc __RPC_FAR * This,
    BOOL fConversationLost);


void __RPC_STUB IDtcLuSubordinateDtc_Unplug_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuSubordinateDtc_BackedOut_Proxy( 
    IDtcLuSubordinateDtc __RPC_FAR * This);


void __RPC_STUB IDtcLuSubordinateDtc_BackedOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuSubordinateDtc_BackOut_Proxy( 
    IDtcLuSubordinateDtc __RPC_FAR * This);


void __RPC_STUB IDtcLuSubordinateDtc_BackOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuSubordinateDtc_Committed_Proxy( 
    IDtcLuSubordinateDtc __RPC_FAR * This);


void __RPC_STUB IDtcLuSubordinateDtc_Committed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuSubordinateDtc_Forget_Proxy( 
    IDtcLuSubordinateDtc __RPC_FAR * This);


void __RPC_STUB IDtcLuSubordinateDtc_Forget_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuSubordinateDtc_Prepare_Proxy( 
    IDtcLuSubordinateDtc __RPC_FAR * This);


void __RPC_STUB IDtcLuSubordinateDtc_Prepare_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuSubordinateDtc_RequestCommit_Proxy( 
    IDtcLuSubordinateDtc __RPC_FAR * This);


void __RPC_STUB IDtcLuSubordinateDtc_RequestCommit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDtcLuSubordinateDtc_INTERFACE_DEFINED__ */


#ifndef __IDtcLuSubordinateDtcSink_INTERFACE_DEFINED__
#define __IDtcLuSubordinateDtcSink_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDtcLuSubordinateDtcSink
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][unique][object] */ 



EXTERN_C const IID IID_IDtcLuSubordinateDtcSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("4131E774-1AEA-11d0-944B-00A0C905416E")
    IDtcLuSubordinateDtcSink : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AckUnplug( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TmDown( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SessionLost( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BackedOut( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BackOut( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Committed( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Forget( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RequestCommit( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDtcLuSubordinateDtcSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDtcLuSubordinateDtcSink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDtcLuSubordinateDtcSink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDtcLuSubordinateDtcSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AckUnplug )( 
            IDtcLuSubordinateDtcSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TmDown )( 
            IDtcLuSubordinateDtcSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SessionLost )( 
            IDtcLuSubordinateDtcSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BackedOut )( 
            IDtcLuSubordinateDtcSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BackOut )( 
            IDtcLuSubordinateDtcSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Committed )( 
            IDtcLuSubordinateDtcSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Forget )( 
            IDtcLuSubordinateDtcSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestCommit )( 
            IDtcLuSubordinateDtcSink __RPC_FAR * This);
        
        END_INTERFACE
    } IDtcLuSubordinateDtcSinkVtbl;

    interface IDtcLuSubordinateDtcSink
    {
        CONST_VTBL struct IDtcLuSubordinateDtcSinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDtcLuSubordinateDtcSink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDtcLuSubordinateDtcSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDtcLuSubordinateDtcSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDtcLuSubordinateDtcSink_AckUnplug(This)	\
    (This)->lpVtbl -> AckUnplug(This)

#define IDtcLuSubordinateDtcSink_TmDown(This)	\
    (This)->lpVtbl -> TmDown(This)

#define IDtcLuSubordinateDtcSink_SessionLost(This)	\
    (This)->lpVtbl -> SessionLost(This)

#define IDtcLuSubordinateDtcSink_BackedOut(This)	\
    (This)->lpVtbl -> BackedOut(This)

#define IDtcLuSubordinateDtcSink_BackOut(This)	\
    (This)->lpVtbl -> BackOut(This)

#define IDtcLuSubordinateDtcSink_Committed(This)	\
    (This)->lpVtbl -> Committed(This)

#define IDtcLuSubordinateDtcSink_Forget(This)	\
    (This)->lpVtbl -> Forget(This)

#define IDtcLuSubordinateDtcSink_RequestCommit(This)	\
    (This)->lpVtbl -> RequestCommit(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDtcLuSubordinateDtcSink_AckUnplug_Proxy( 
    IDtcLuSubordinateDtcSink __RPC_FAR * This);


void __RPC_STUB IDtcLuSubordinateDtcSink_AckUnplug_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuSubordinateDtcSink_TmDown_Proxy( 
    IDtcLuSubordinateDtcSink __RPC_FAR * This);


void __RPC_STUB IDtcLuSubordinateDtcSink_TmDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuSubordinateDtcSink_SessionLost_Proxy( 
    IDtcLuSubordinateDtcSink __RPC_FAR * This);


void __RPC_STUB IDtcLuSubordinateDtcSink_SessionLost_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuSubordinateDtcSink_BackedOut_Proxy( 
    IDtcLuSubordinateDtcSink __RPC_FAR * This);


void __RPC_STUB IDtcLuSubordinateDtcSink_BackedOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuSubordinateDtcSink_BackOut_Proxy( 
    IDtcLuSubordinateDtcSink __RPC_FAR * This);


void __RPC_STUB IDtcLuSubordinateDtcSink_BackOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuSubordinateDtcSink_Committed_Proxy( 
    IDtcLuSubordinateDtcSink __RPC_FAR * This);


void __RPC_STUB IDtcLuSubordinateDtcSink_Committed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuSubordinateDtcSink_Forget_Proxy( 
    IDtcLuSubordinateDtcSink __RPC_FAR * This);


void __RPC_STUB IDtcLuSubordinateDtcSink_Forget_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IDtcLuSubordinateDtcSink_RequestCommit_Proxy( 
    IDtcLuSubordinateDtcSink __RPC_FAR * This);


void __RPC_STUB IDtcLuSubordinateDtcSink_RequestCommit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDtcLuSubordinateDtcSink_INTERFACE_DEFINED__ */


#ifndef __IDtcLuSubordinateDtcFactory_INTERFACE_DEFINED__
#define __IDtcLuSubordinateDtcFactory_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IDtcLuSubordinateDtcFactory
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][unique][object] */ 



EXTERN_C const IID IID_IDtcLuSubordinateDtcFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("4131E775-1AEA-11d0-944B-00A0C905416E")
    IDtcLuSubordinateDtcFactory : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Create( 
            /* [in] */ unsigned char __RPC_FAR *pucLuPair,
            /* [in] */ DWORD cbLuPair,
            /* [in] */ IUnknown __RPC_FAR *punkTransactionOuter,
            /* [in] */ ISOLEVEL isoLevel,
            /* [in] */ ULONG isoFlags,
            /* [in] */ ITransactionOptions __RPC_FAR *pOptions,
            /* [out] */ ITransaction __RPC_FAR *__RPC_FAR *ppTransaction,
            /* [in] */ unsigned char __RPC_FAR *pTransId,
            /* [in] */ DWORD cbTransId,
            /* [in] */ IDtcLuSubordinateDtcSink __RPC_FAR *pSubordinateDtcSink,
            /* [out][in] */ IDtcLuSubordinateDtc __RPC_FAR *__RPC_FAR *ppSubordinateDtc) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDtcLuSubordinateDtcFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDtcLuSubordinateDtcFactory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDtcLuSubordinateDtcFactory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDtcLuSubordinateDtcFactory __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Create )( 
            IDtcLuSubordinateDtcFactory __RPC_FAR * This,
            /* [in] */ unsigned char __RPC_FAR *pucLuPair,
            /* [in] */ DWORD cbLuPair,
            /* [in] */ IUnknown __RPC_FAR *punkTransactionOuter,
            /* [in] */ ISOLEVEL isoLevel,
            /* [in] */ ULONG isoFlags,
            /* [in] */ ITransactionOptions __RPC_FAR *pOptions,
            /* [out] */ ITransaction __RPC_FAR *__RPC_FAR *ppTransaction,
            /* [in] */ unsigned char __RPC_FAR *pTransId,
            /* [in] */ DWORD cbTransId,
            /* [in] */ IDtcLuSubordinateDtcSink __RPC_FAR *pSubordinateDtcSink,
            /* [out][in] */ IDtcLuSubordinateDtc __RPC_FAR *__RPC_FAR *ppSubordinateDtc);
        
        END_INTERFACE
    } IDtcLuSubordinateDtcFactoryVtbl;

    interface IDtcLuSubordinateDtcFactory
    {
        CONST_VTBL struct IDtcLuSubordinateDtcFactoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDtcLuSubordinateDtcFactory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDtcLuSubordinateDtcFactory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDtcLuSubordinateDtcFactory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDtcLuSubordinateDtcFactory_Create(This,pucLuPair,cbLuPair,punkTransactionOuter,isoLevel,isoFlags,pOptions,ppTransaction,pTransId,cbTransId,pSubordinateDtcSink,ppSubordinateDtc)	\
    (This)->lpVtbl -> Create(This,pucLuPair,cbLuPair,punkTransactionOuter,isoLevel,isoFlags,pOptions,ppTransaction,pTransId,cbTransId,pSubordinateDtcSink,ppSubordinateDtc)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IDtcLuSubordinateDtcFactory_Create_Proxy( 
    IDtcLuSubordinateDtcFactory __RPC_FAR * This,
    /* [in] */ unsigned char __RPC_FAR *pucLuPair,
    /* [in] */ DWORD cbLuPair,
    /* [in] */ IUnknown __RPC_FAR *punkTransactionOuter,
    /* [in] */ ISOLEVEL isoLevel,
    /* [in] */ ULONG isoFlags,
    /* [in] */ ITransactionOptions __RPC_FAR *pOptions,
    /* [out] */ ITransaction __RPC_FAR *__RPC_FAR *ppTransaction,
    /* [in] */ unsigned char __RPC_FAR *pTransId,
    /* [in] */ DWORD cbTransId,
    /* [in] */ IDtcLuSubordinateDtcSink __RPC_FAR *pSubordinateDtcSink,
    /* [out][in] */ IDtcLuSubordinateDtc __RPC_FAR *__RPC_FAR *ppSubordinateDtc);


void __RPC_STUB IDtcLuSubordinateDtcFactory_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDtcLuSubordinateDtcFactory_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_txdtc_0122
 * at Fri Nov 14 05:07:21 1997
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 




#if _MSC_VER < 1100 || !defined(__cplusplus)

DEFINE_GUID(IID_IXATransLookup, 0xF3B1F131, 0xEEDA, 0x11ce, 0xAE, 0xD4, 0x00, 0xAA, 0x00, 0x51, 0xE2, 0xC4);
DEFINE_GUID(IID_IResourceManagerSink, 0x0D563181, 0xDEFB, 0x11ce, 0xAE, 0xD1, 0x00, 0xAA, 0x00, 0x51, 0xE2, 0xC4);
DEFINE_GUID(IID_IResourceManager, 0x3741d21, 0x87eb, 0x11ce, 0x80, 0x81, 0x00, 0x80, 0xc7, 0x58, 0x52, 0x7e);
DEFINE_GUID(IID_IXAConfig, 0xC8A6E3A1, 0x9A8C, 0x11cf, 0xA3, 0x08, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IRMHelper, 0xE793F6D1, 0xF53D, 0x11cf, 0xA6, 0x0D, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IXAObtainRMInfo, 0xE793F6D2, 0xF53D, 0x11cf, 0xA6, 0x0D, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IXAResourceManager, 0x4131E751, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IXAResourceManagerFactory, 0x4131E750, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IXATransaction, 0x4131E752, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IResourceManagerFactory, 0x13741d20, 0x87eb, 0x11ce, 0x80, 0x81, 0x00, 0x80, 0xc7, 0x58, 0x52, 0x7e);
DEFINE_GUID(IID_IPrepareInfo, 0x80c7bfd0, 0x87ee, 0x11ce, 0x80, 0x81, 0x00, 0x80, 0xc7, 0x58, 0x52, 0x7e);
DEFINE_GUID(IID_IGetDispenser, 0xc23cc370, 0x87ef, 0x11ce, 0x80, 0x81, 0x00, 0x80, 0xc7, 0x58, 0x52, 0x7e);
DEFINE_GUID(IID_ITransactionVoterNotifyAsync, 0xB94ABFDC, 0xFFC9, 0x11d0, 0xB1, 0x64, 0x00, 0xC0, 0x4F, 0xC2, 0xF3, 0xEF);
DEFINE_GUID(IID_ITransactionVoterBallotAsync, 0x319FAC12, 0xA391, 0x11cf, 0xA5, 0x35, 0x00, 0xAA, 0x00, 0x68, 0x87, 0xC3);
DEFINE_GUID(IID_ITransactionVoterFactory, 0x319FAC10, 0xA391, 0x11cf, 0xA5, 0x35, 0x00, 0xAA, 0x00, 0x68, 0x87, 0xC3);
DEFINE_GUID(IID_ITransactionTransmitter, 0x59313E01, 0xB36C, 0x11cf, 0xA5, 0x39, 0x00, 0xAA, 0x00, 0x68, 0x87, 0xC3);
DEFINE_GUID(IID_ITransactionTransmitterFactory, 0x59313E00, 0xB36C, 0x11cf, 0xA5, 0x39, 0x00, 0xAA, 0x00, 0x68, 0x87, 0xC3);
DEFINE_GUID(IID_ITransactionReceiver, 0x59313E03, 0xB36C, 0x11cf, 0xA5, 0x39, 0x00, 0xAA, 0x00, 0x68, 0x87, 0xC3);
DEFINE_GUID(IID_ITransactionReceiverFactory, 0x59313E02, 0xB36C, 0x11cf, 0xA5, 0x39, 0x00, 0xAA, 0x00, 0x68, 0x87, 0xC3);

DEFINE_GUID(IID_IDtcLuConfigure, 0x4131E760, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IDtcLuRecovery, 0xac2b8ad2, 0xd6f0, 0x11d0, 0xb3, 0x86, 0x0, 0xa0, 0xc9, 0x8, 0x33, 0x65);
DEFINE_GUID(IID_IDtcLuRecoveryFactory, 0x4131E762, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IDtcLuRecoveryInitiatedByDtcTransWork, 0x4131E765, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IDtcLuRecoveryInitiatedByDtcStatusWork, 0x4131E766, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IDtcLuRecoveryInitiatedByDtc, 0x4131E764, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IDtcLuRecoveryInitiatedByLuWork, 0xac2b8ad1, 0xd6f0, 0x11d0, 0xb3, 0x86, 0x0, 0xa0, 0xc9, 0x8, 0x33, 0x65);
DEFINE_GUID(IID_IDtcLuRecoveryInitiatedByLu, 0x4131E768, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IDtcLuRmEnlistment, 0x4131E769, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IDtcLuRmEnlistmentSink, 0x4131E770, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IDtcLuRmEnlistmentFactory, 0x4131E771, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IDtcLuSubordinateDtc, 0x4131E773, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IDtcLuSubordinateDtcSink, 0x4131E774, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_IDtcLuSubordinateDtcFactory, 0x4131E775, 0x1AEA, 0x11d0, 0x94, 0x4B, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);

#else

#define  IID_IXATransLookup							__uuidof(IXATransLookup)
#define  IID_IResourceManagerSink					__uuidof(IResourceManagerSink)
#define  IID_IResourceManager						__uuidof(IResourceManager)
#define  IID_IXAConfig								__uuidof(IXAConfig)
#define  IID_IRMHelper								__uuidof(IRMHelper)
#define  IID_IXAObtainRMInfo							__uuidof(IXAObtainRMInfo)
#define  IID_IXAResourceManager						__uuidof(IXAResourceManager)
#define  IID_IXAResourceManagerFactory				__uuidof(IXAResourceManagerFactory)
#define  IID_IXATransaction      		            __uuidof(IXATransaction)
#define  IID_IResourceManagerFactory         		__uuidof(IResourceManagerFactory)
#define  IID_IPrepareInfo                		    __uuidof(IPrepareInfo)
#define  IID_IGetDispenser							__uuidof(IGetDispenser)
#define  IID_ITransactionVoterNotifyAsync		    __uuidof(ITransactionVoterNotifyAsync)
#define  IID_ITransactionVoterBallotAsync			__uuidof(ITransactionVoterBallotAsync)
#define  IID_ITransactionVoterFactory				__uuidof(ITransactionVoterFactory)
#define  IID_ITransactionTransmitter					__uuidof(ITransactionTransmitter)
#define  IID_ITransactionTransmitterFactory			__uuidof(ITransactionTransmitterFactory)
#define  IID_ITransactionReceiver					__uuidof(ITransactionReceiver)
#define  IID_ITransactionReceiverFactory				__uuidof(ITransactionReceiverFactory)

#define  IID_IDtcLuConfigure							__uuidof(IDtcLuConfigure)
#define  IID_IDtcLuRecovery							__uuidof(IDtcLuRecovery)
#define  IID_IDtcLuRecoveryFactory					__uuidof(IDtcLuRecoveryFactory)
#define  IID_IDtcLuRecoveryInitiatedByDtcTransWork   __uuidof(IDtcLuRecoveryInitiatedByDtcTransWork)
#define  IID_IDtcLuRecoveryInitiatedByDtcStatusWork  __uuidof(IDtcLuRecoveryInitiatedByDtcStatusWork)
#define  IID_IDtcLuRecoveryInitiatedByDtc			__uuidof(IDtcLuRecoveryInitiatedByDtc)
#define  IID_IDtcLuRecoveryInitiatedByLuWork			__uuidof(IDtcLuRecoveryInitiatedByLuWork)
#define  IID_IDtcLuRecoveryInitiatedByLu			    __uuidof(IDtcLuRecoveryInitiatedByLu)
#define  IID_IDtcLuRmEnlistment					    __uuidof(IDtcLuRmEnlistment)
#define  IID_IDtcLuRmEnlistmentSink					__uuidof(IDtcLuRmEnlistmentSink)
#define  IID_IDtcLuRmEnlistmentFactory				__uuidof(IDtcLuRmEnlistmentFactory)
#define  IID_IDtcLuSubordinateDtc				    __uuidof(IDtcLuSubordinateDtc)
#define  IID_IDtcLuSubordinateDtcSink				__uuidof(IDtcLuSubordinateDtcSink)
#define  IID_IDtcLuSubordinateDtcFactory				__uuidof(IDtcLuSubordinateDtcFactory)

#endif


extern RPC_IF_HANDLE __MIDL_itf_txdtc_0122_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_txdtc_0122_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
