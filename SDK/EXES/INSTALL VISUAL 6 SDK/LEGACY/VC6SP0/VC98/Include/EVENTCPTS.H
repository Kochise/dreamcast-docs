/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Thu Sep 11 16:03:12 1997
 */
/* Compiler settings for eventcpts.idl:
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

#ifndef __eventcpts_h__
#define __eventcpts_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IMtsUserEvent_FWD_DEFINED__
#define __IMtsUserEvent_FWD_DEFINED__
typedef interface IMtsUserEvent IMtsUserEvent;
#endif 	/* __IMtsUserEvent_FWD_DEFINED__ */


#ifndef __IMtsThreadEvents_FWD_DEFINED__
#define __IMtsThreadEvents_FWD_DEFINED__
typedef interface IMtsThreadEvents IMtsThreadEvents;
#endif 	/* __IMtsThreadEvents_FWD_DEFINED__ */


#ifndef __IMtsPackageEvents_FWD_DEFINED__
#define __IMtsPackageEvents_FWD_DEFINED__
typedef interface IMtsPackageEvents IMtsPackageEvents;
#endif 	/* __IMtsPackageEvents_FWD_DEFINED__ */


#ifndef __IMtsInstanceEvents_FWD_DEFINED__
#define __IMtsInstanceEvents_FWD_DEFINED__
typedef interface IMtsInstanceEvents IMtsInstanceEvents;
#endif 	/* __IMtsInstanceEvents_FWD_DEFINED__ */


#ifndef __IMtsTransactionEvents_FWD_DEFINED__
#define __IMtsTransactionEvents_FWD_DEFINED__
typedef interface IMtsTransactionEvents IMtsTransactionEvents;
#endif 	/* __IMtsTransactionEvents_FWD_DEFINED__ */


#ifndef __IMtsMethodEvents_FWD_DEFINED__
#define __IMtsMethodEvents_FWD_DEFINED__
typedef interface IMtsMethodEvents IMtsMethodEvents;
#endif 	/* __IMtsMethodEvents_FWD_DEFINED__ */


#ifndef __IMtsObjectEvents_FWD_DEFINED__
#define __IMtsObjectEvents_FWD_DEFINED__
typedef interface IMtsObjectEvents IMtsObjectEvents;
#endif 	/* __IMtsObjectEvents_FWD_DEFINED__ */


#ifndef __IMtsResourceEvents_FWD_DEFINED__
#define __IMtsResourceEvents_FWD_DEFINED__
typedef interface IMtsResourceEvents IMtsResourceEvents;
#endif 	/* __IMtsResourceEvents_FWD_DEFINED__ */


#ifndef __IMtsSecurityEvents_FWD_DEFINED__
#define __IMtsSecurityEvents_FWD_DEFINED__
typedef interface IMtsSecurityEvents IMtsSecurityEvents;
#endif 	/* __IMtsSecurityEvents_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_eventcpts_0000
 * at Thu Sep 11 16:03:12 1997
 * using MIDL 3.01.75
 ****************************************/
/* [local] */ 


typedef ULONG MTS_OBJID;

typedef ULONG MTS_RESID;



extern RPC_IF_HANDLE __MIDL_itf_eventcpts_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_eventcpts_0000_v0_0_s_ifspec;

#ifndef __IMtsUserEvent_INTERFACE_DEFINED__
#define __IMtsUserEvent_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMtsUserEvent
 * at Thu Sep 11 16:03:12 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][object] */ 



EXTERN_C const IID IID_IMtsUserEvent;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("D56C3DC0-8482-11d0-B170-00AA00BA3258")
    IMtsUserEvent : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnUserEvent( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ VARIANT __RPC_FAR *pvarEvent) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMtsUserEventVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMtsUserEvent __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMtsUserEvent __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMtsUserEvent __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnUserEvent )( 
            IMtsUserEvent __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ VARIANT __RPC_FAR *pvarEvent);
        
        END_INTERFACE
    } IMtsUserEventVtbl;

    interface IMtsUserEvent
    {
        CONST_VTBL struct IMtsUserEventVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMtsUserEvent_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMtsUserEvent_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMtsUserEvent_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMtsUserEvent_OnUserEvent(This,perfCount,pvarEvent)	\
    (This)->lpVtbl -> OnUserEvent(This,perfCount,pvarEvent)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMtsUserEvent_OnUserEvent_Proxy( 
    IMtsUserEvent __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ VARIANT __RPC_FAR *pvarEvent);


void __RPC_STUB IMtsUserEvent_OnUserEvent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMtsUserEvent_INTERFACE_DEFINED__ */


#ifndef __IMtsThreadEvents_INTERFACE_DEFINED__
#define __IMtsThreadEvents_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMtsThreadEvents
 * at Thu Sep 11 16:03:12 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][object] */ 



EXTERN_C const IID IID_IMtsThreadEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("BACEDF4F-74AB-11D0-B162-00AA00BA3258")
    IMtsThreadEvents : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnThreadStart( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ ULONG ThreadID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnThreadTerminate( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ ULONG ThreadID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnThreadAssignToActivity( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ REFGUID guidActivity,
            /* [in] */ ULONG ThreadID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnThreadUnassignFromActivity( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ REFGUID guidActivity,
            /* [in] */ ULONG ThreadID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMtsThreadEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMtsThreadEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMtsThreadEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMtsThreadEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnThreadStart )( 
            IMtsThreadEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ ULONG ThreadID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnThreadTerminate )( 
            IMtsThreadEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ ULONG ThreadID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnThreadAssignToActivity )( 
            IMtsThreadEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ REFGUID guidActivity,
            /* [in] */ ULONG ThreadID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnThreadUnassignFromActivity )( 
            IMtsThreadEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ REFGUID guidActivity,
            /* [in] */ ULONG ThreadID);
        
        END_INTERFACE
    } IMtsThreadEventsVtbl;

    interface IMtsThreadEvents
    {
        CONST_VTBL struct IMtsThreadEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMtsThreadEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMtsThreadEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMtsThreadEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMtsThreadEvents_OnThreadStart(This,perfCount,ThreadID)	\
    (This)->lpVtbl -> OnThreadStart(This,perfCount,ThreadID)

#define IMtsThreadEvents_OnThreadTerminate(This,perfCount,ThreadID)	\
    (This)->lpVtbl -> OnThreadTerminate(This,perfCount,ThreadID)

#define IMtsThreadEvents_OnThreadAssignToActivity(This,perfCount,guidActivity,ThreadID)	\
    (This)->lpVtbl -> OnThreadAssignToActivity(This,perfCount,guidActivity,ThreadID)

#define IMtsThreadEvents_OnThreadUnassignFromActivity(This,perfCount,guidActivity,ThreadID)	\
    (This)->lpVtbl -> OnThreadUnassignFromActivity(This,perfCount,guidActivity,ThreadID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMtsThreadEvents_OnThreadStart_Proxy( 
    IMtsThreadEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ ULONG ThreadID);


void __RPC_STUB IMtsThreadEvents_OnThreadStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMtsThreadEvents_OnThreadTerminate_Proxy( 
    IMtsThreadEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ ULONG ThreadID);


void __RPC_STUB IMtsThreadEvents_OnThreadTerminate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMtsThreadEvents_OnThreadAssignToActivity_Proxy( 
    IMtsThreadEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ REFGUID guidActivity,
    /* [in] */ ULONG ThreadID);


void __RPC_STUB IMtsThreadEvents_OnThreadAssignToActivity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMtsThreadEvents_OnThreadUnassignFromActivity_Proxy( 
    IMtsThreadEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ REFGUID guidActivity,
    /* [in] */ ULONG ThreadID);


void __RPC_STUB IMtsThreadEvents_OnThreadUnassignFromActivity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMtsThreadEvents_INTERFACE_DEFINED__ */


#ifndef __IMtsPackageEvents_INTERFACE_DEFINED__
#define __IMtsPackageEvents_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMtsPackageEvents
 * at Thu Sep 11 16:03:12 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][object] */ 



EXTERN_C const IID IID_IMtsPackageEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("BACEDF50-74AB-11D0-B162-00AA00BA3258")
    IMtsPackageEvents : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnPackageActivation( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ REFGUID guidPackage,
            /* [in] */ LPCOLESTR sPackageName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnPackageShutdown( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ REFGUID guidPackage,
            /* [in] */ LPCOLESTR sPackageName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMtsPackageEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMtsPackageEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMtsPackageEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMtsPackageEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnPackageActivation )( 
            IMtsPackageEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ REFGUID guidPackage,
            /* [in] */ LPCOLESTR sPackageName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnPackageShutdown )( 
            IMtsPackageEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ REFGUID guidPackage,
            /* [in] */ LPCOLESTR sPackageName);
        
        END_INTERFACE
    } IMtsPackageEventsVtbl;

    interface IMtsPackageEvents
    {
        CONST_VTBL struct IMtsPackageEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMtsPackageEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMtsPackageEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMtsPackageEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMtsPackageEvents_OnPackageActivation(This,perfCount,guidPackage,sPackageName)	\
    (This)->lpVtbl -> OnPackageActivation(This,perfCount,guidPackage,sPackageName)

#define IMtsPackageEvents_OnPackageShutdown(This,perfCount,guidPackage,sPackageName)	\
    (This)->lpVtbl -> OnPackageShutdown(This,perfCount,guidPackage,sPackageName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMtsPackageEvents_OnPackageActivation_Proxy( 
    IMtsPackageEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ REFGUID guidPackage,
    /* [in] */ LPCOLESTR sPackageName);


void __RPC_STUB IMtsPackageEvents_OnPackageActivation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMtsPackageEvents_OnPackageShutdown_Proxy( 
    IMtsPackageEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ REFGUID guidPackage,
    /* [in] */ LPCOLESTR sPackageName);


void __RPC_STUB IMtsPackageEvents_OnPackageShutdown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMtsPackageEvents_INTERFACE_DEFINED__ */


#ifndef __IMtsInstanceEvents_INTERFACE_DEFINED__
#define __IMtsInstanceEvents_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMtsInstanceEvents
 * at Thu Sep 11 16:03:12 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][object] */ 



EXTERN_C const IID IID_IMtsInstanceEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("BACEDF51-74AB-11D0-B162-00AA00BA3258")
    IMtsInstanceEvents : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnObjectCreate( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ REFGUID guidActivity,
            /* [in] */ REFCLSID clsid,
            /* [in] */ REFGUID tsid,
            /* [in] */ MTS_OBJID ObjectID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnObjectRelease( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ MTS_OBJID ObjectID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMtsInstanceEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMtsInstanceEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMtsInstanceEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMtsInstanceEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnObjectCreate )( 
            IMtsInstanceEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ REFGUID guidActivity,
            /* [in] */ REFCLSID clsid,
            /* [in] */ REFGUID tsid,
            /* [in] */ MTS_OBJID ObjectID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnObjectRelease )( 
            IMtsInstanceEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ MTS_OBJID ObjectID);
        
        END_INTERFACE
    } IMtsInstanceEventsVtbl;

    interface IMtsInstanceEvents
    {
        CONST_VTBL struct IMtsInstanceEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMtsInstanceEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMtsInstanceEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMtsInstanceEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMtsInstanceEvents_OnObjectCreate(This,perfCount,guidActivity,clsid,tsid,ObjectID)	\
    (This)->lpVtbl -> OnObjectCreate(This,perfCount,guidActivity,clsid,tsid,ObjectID)

#define IMtsInstanceEvents_OnObjectRelease(This,perfCount,ObjectID)	\
    (This)->lpVtbl -> OnObjectRelease(This,perfCount,ObjectID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMtsInstanceEvents_OnObjectCreate_Proxy( 
    IMtsInstanceEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ REFGUID guidActivity,
    /* [in] */ REFCLSID clsid,
    /* [in] */ REFGUID tsid,
    /* [in] */ MTS_OBJID ObjectID);


void __RPC_STUB IMtsInstanceEvents_OnObjectCreate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMtsInstanceEvents_OnObjectRelease_Proxy( 
    IMtsInstanceEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ MTS_OBJID ObjectID);


void __RPC_STUB IMtsInstanceEvents_OnObjectRelease_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMtsInstanceEvents_INTERFACE_DEFINED__ */


#ifndef __IMtsTransactionEvents_INTERFACE_DEFINED__
#define __IMtsTransactionEvents_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMtsTransactionEvents
 * at Thu Sep 11 16:03:12 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][object] */ 



EXTERN_C const IID IID_IMtsTransactionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("BACEDF52-74AB-11D0-B162-00AA00BA3258")
    IMtsTransactionEvents : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnTransactionStart( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ REFGUID guidTx,
            /* [in] */ REFGUID tsid,
            /* [in] */ BOOL fRoot) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnTransactionPrepared( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ REFGUID guidTx,
            /* [in] */ BOOL fVoteYes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnTransactionAborted( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ REFGUID guidTx) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMtsTransactionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMtsTransactionEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMtsTransactionEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMtsTransactionEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnTransactionStart )( 
            IMtsTransactionEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ REFGUID guidTx,
            /* [in] */ REFGUID tsid,
            /* [in] */ BOOL fRoot);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnTransactionPrepared )( 
            IMtsTransactionEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ REFGUID guidTx,
            /* [in] */ BOOL fVoteYes);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnTransactionAborted )( 
            IMtsTransactionEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ REFGUID guidTx);
        
        END_INTERFACE
    } IMtsTransactionEventsVtbl;

    interface IMtsTransactionEvents
    {
        CONST_VTBL struct IMtsTransactionEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMtsTransactionEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMtsTransactionEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMtsTransactionEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMtsTransactionEvents_OnTransactionStart(This,perfCount,guidTx,tsid,fRoot)	\
    (This)->lpVtbl -> OnTransactionStart(This,perfCount,guidTx,tsid,fRoot)

#define IMtsTransactionEvents_OnTransactionPrepared(This,perfCount,guidTx,fVoteYes)	\
    (This)->lpVtbl -> OnTransactionPrepared(This,perfCount,guidTx,fVoteYes)

#define IMtsTransactionEvents_OnTransactionAborted(This,perfCount,guidTx)	\
    (This)->lpVtbl -> OnTransactionAborted(This,perfCount,guidTx)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMtsTransactionEvents_OnTransactionStart_Proxy( 
    IMtsTransactionEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ REFGUID guidTx,
    /* [in] */ REFGUID tsid,
    /* [in] */ BOOL fRoot);


void __RPC_STUB IMtsTransactionEvents_OnTransactionStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMtsTransactionEvents_OnTransactionPrepared_Proxy( 
    IMtsTransactionEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ REFGUID guidTx,
    /* [in] */ BOOL fVoteYes);


void __RPC_STUB IMtsTransactionEvents_OnTransactionPrepared_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMtsTransactionEvents_OnTransactionAborted_Proxy( 
    IMtsTransactionEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ REFGUID guidTx);


void __RPC_STUB IMtsTransactionEvents_OnTransactionAborted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMtsTransactionEvents_INTERFACE_DEFINED__ */


#ifndef __IMtsMethodEvents_INTERFACE_DEFINED__
#define __IMtsMethodEvents_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMtsMethodEvents
 * at Thu Sep 11 16:03:12 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][object] */ 



EXTERN_C const IID IID_IMtsMethodEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("BACEDF53-74AB-11D0-B162-00AA00BA3258")
    IMtsMethodEvents : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnMethodCall( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ MTS_OBJID oid,
            /* [in] */ REFCLSID guidCid,
            /* [in] */ REFIID guidRid,
            /* [in] */ ULONG iMeth) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnMethodReturn( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ MTS_OBJID oid,
            /* [in] */ REFCLSID guidCid,
            /* [in] */ REFIID guidRid,
            /* [in] */ ULONG iMeth,
            /* [in] */ HRESULT hresult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnMethodException( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ MTS_OBJID oid,
            /* [in] */ REFCLSID guidCid,
            /* [in] */ REFIID guidRid,
            /* [in] */ ULONG iMeth) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMtsMethodEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMtsMethodEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMtsMethodEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMtsMethodEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnMethodCall )( 
            IMtsMethodEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ MTS_OBJID oid,
            /* [in] */ REFCLSID guidCid,
            /* [in] */ REFIID guidRid,
            /* [in] */ ULONG iMeth);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnMethodReturn )( 
            IMtsMethodEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ MTS_OBJID oid,
            /* [in] */ REFCLSID guidCid,
            /* [in] */ REFIID guidRid,
            /* [in] */ ULONG iMeth,
            /* [in] */ HRESULT hresult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnMethodException )( 
            IMtsMethodEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ MTS_OBJID oid,
            /* [in] */ REFCLSID guidCid,
            /* [in] */ REFIID guidRid,
            /* [in] */ ULONG iMeth);
        
        END_INTERFACE
    } IMtsMethodEventsVtbl;

    interface IMtsMethodEvents
    {
        CONST_VTBL struct IMtsMethodEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMtsMethodEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMtsMethodEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMtsMethodEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMtsMethodEvents_OnMethodCall(This,perfCount,oid,guidCid,guidRid,iMeth)	\
    (This)->lpVtbl -> OnMethodCall(This,perfCount,oid,guidCid,guidRid,iMeth)

#define IMtsMethodEvents_OnMethodReturn(This,perfCount,oid,guidCid,guidRid,iMeth,hresult)	\
    (This)->lpVtbl -> OnMethodReturn(This,perfCount,oid,guidCid,guidRid,iMeth,hresult)

#define IMtsMethodEvents_OnMethodException(This,perfCount,oid,guidCid,guidRid,iMeth)	\
    (This)->lpVtbl -> OnMethodException(This,perfCount,oid,guidCid,guidRid,iMeth)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMtsMethodEvents_OnMethodCall_Proxy( 
    IMtsMethodEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ MTS_OBJID oid,
    /* [in] */ REFCLSID guidCid,
    /* [in] */ REFIID guidRid,
    /* [in] */ ULONG iMeth);


void __RPC_STUB IMtsMethodEvents_OnMethodCall_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMtsMethodEvents_OnMethodReturn_Proxy( 
    IMtsMethodEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ MTS_OBJID oid,
    /* [in] */ REFCLSID guidCid,
    /* [in] */ REFIID guidRid,
    /* [in] */ ULONG iMeth,
    /* [in] */ HRESULT hresult);


void __RPC_STUB IMtsMethodEvents_OnMethodReturn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMtsMethodEvents_OnMethodException_Proxy( 
    IMtsMethodEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ MTS_OBJID oid,
    /* [in] */ REFCLSID guidCid,
    /* [in] */ REFIID guidRid,
    /* [in] */ ULONG iMeth);


void __RPC_STUB IMtsMethodEvents_OnMethodException_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMtsMethodEvents_INTERFACE_DEFINED__ */


#ifndef __IMtsObjectEvents_INTERFACE_DEFINED__
#define __IMtsObjectEvents_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMtsObjectEvents
 * at Thu Sep 11 16:03:12 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][object] */ 



EXTERN_C const IID IID_IMtsObjectEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("BACEDF54-74AB-11D0-B162-00AA00BA3258")
    IMtsObjectEvents : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnObjectActivate( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ MTS_OBJID ObjectID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnObjectDeactivate( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ MTS_OBJID ObjectID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnDisableCommit( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ MTS_OBJID ObjectID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnEnableCommit( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ MTS_OBJID ObjectID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnSetComplete( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ MTS_OBJID ObjectID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMtsObjectEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMtsObjectEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMtsObjectEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMtsObjectEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnObjectActivate )( 
            IMtsObjectEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ MTS_OBJID ObjectID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnObjectDeactivate )( 
            IMtsObjectEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ MTS_OBJID ObjectID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnDisableCommit )( 
            IMtsObjectEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ MTS_OBJID ObjectID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnEnableCommit )( 
            IMtsObjectEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ MTS_OBJID ObjectID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnSetComplete )( 
            IMtsObjectEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ MTS_OBJID ObjectID);
        
        END_INTERFACE
    } IMtsObjectEventsVtbl;

    interface IMtsObjectEvents
    {
        CONST_VTBL struct IMtsObjectEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMtsObjectEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMtsObjectEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMtsObjectEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMtsObjectEvents_OnObjectActivate(This,perfCount,ObjectID)	\
    (This)->lpVtbl -> OnObjectActivate(This,perfCount,ObjectID)

#define IMtsObjectEvents_OnObjectDeactivate(This,perfCount,ObjectID)	\
    (This)->lpVtbl -> OnObjectDeactivate(This,perfCount,ObjectID)

#define IMtsObjectEvents_OnDisableCommit(This,perfCount,ObjectID)	\
    (This)->lpVtbl -> OnDisableCommit(This,perfCount,ObjectID)

#define IMtsObjectEvents_OnEnableCommit(This,perfCount,ObjectID)	\
    (This)->lpVtbl -> OnEnableCommit(This,perfCount,ObjectID)

#define IMtsObjectEvents_OnSetComplete(This,perfCount,ObjectID)	\
    (This)->lpVtbl -> OnSetComplete(This,perfCount,ObjectID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMtsObjectEvents_OnObjectActivate_Proxy( 
    IMtsObjectEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ MTS_OBJID ObjectID);


void __RPC_STUB IMtsObjectEvents_OnObjectActivate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMtsObjectEvents_OnObjectDeactivate_Proxy( 
    IMtsObjectEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ MTS_OBJID ObjectID);


void __RPC_STUB IMtsObjectEvents_OnObjectDeactivate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMtsObjectEvents_OnDisableCommit_Proxy( 
    IMtsObjectEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ MTS_OBJID ObjectID);


void __RPC_STUB IMtsObjectEvents_OnDisableCommit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMtsObjectEvents_OnEnableCommit_Proxy( 
    IMtsObjectEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ MTS_OBJID ObjectID);


void __RPC_STUB IMtsObjectEvents_OnEnableCommit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMtsObjectEvents_OnSetComplete_Proxy( 
    IMtsObjectEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ MTS_OBJID ObjectID);


void __RPC_STUB IMtsObjectEvents_OnSetComplete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMtsObjectEvents_INTERFACE_DEFINED__ */


#ifndef __IMtsResourceEvents_INTERFACE_DEFINED__
#define __IMtsResourceEvents_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMtsResourceEvents
 * at Thu Sep 11 16:03:12 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][object] */ 



EXTERN_C const IID IID_IMtsResourceEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("BACEDF55-74AB-11D0-B162-00AA00BA3258")
    IMtsResourceEvents : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnResourceCreate( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ REFGUID guidActivity,
            /* [in] */ MTS_OBJID ObjectID,
            /* [in] */ LPCOLESTR pszType,
            /* [in] */ MTS_RESID resId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnResourceAllocate( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ REFGUID guidActivity,
            /* [in] */ MTS_OBJID ObjectID,
            /* [in] */ LPCOLESTR pszType,
            /* [in] */ MTS_RESID resId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnResourceRecycle( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ MTS_OBJID ObjectID,
            /* [in] */ LPCOLESTR pszType,
            /* [in] */ MTS_RESID resId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnResourceDestroy( 
            /* [in] */ LONGLONG perfCount,
            /* [in] */ MTS_OBJID ObjectID,
            /* [in] */ LPCOLESTR pszType,
            /* [in] */ MTS_RESID resId) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMtsResourceEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMtsResourceEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMtsResourceEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMtsResourceEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnResourceCreate )( 
            IMtsResourceEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ REFGUID guidActivity,
            /* [in] */ MTS_OBJID ObjectID,
            /* [in] */ LPCOLESTR pszType,
            /* [in] */ MTS_RESID resId);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnResourceAllocate )( 
            IMtsResourceEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ REFGUID guidActivity,
            /* [in] */ MTS_OBJID ObjectID,
            /* [in] */ LPCOLESTR pszType,
            /* [in] */ MTS_RESID resId);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnResourceRecycle )( 
            IMtsResourceEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ MTS_OBJID ObjectID,
            /* [in] */ LPCOLESTR pszType,
            /* [in] */ MTS_RESID resId);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnResourceDestroy )( 
            IMtsResourceEvents __RPC_FAR * This,
            /* [in] */ LONGLONG perfCount,
            /* [in] */ MTS_OBJID ObjectID,
            /* [in] */ LPCOLESTR pszType,
            /* [in] */ MTS_RESID resId);
        
        END_INTERFACE
    } IMtsResourceEventsVtbl;

    interface IMtsResourceEvents
    {
        CONST_VTBL struct IMtsResourceEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMtsResourceEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMtsResourceEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMtsResourceEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMtsResourceEvents_OnResourceCreate(This,perfCount,guidActivity,ObjectID,pszType,resId)	\
    (This)->lpVtbl -> OnResourceCreate(This,perfCount,guidActivity,ObjectID,pszType,resId)

#define IMtsResourceEvents_OnResourceAllocate(This,perfCount,guidActivity,ObjectID,pszType,resId)	\
    (This)->lpVtbl -> OnResourceAllocate(This,perfCount,guidActivity,ObjectID,pszType,resId)

#define IMtsResourceEvents_OnResourceRecycle(This,perfCount,ObjectID,pszType,resId)	\
    (This)->lpVtbl -> OnResourceRecycle(This,perfCount,ObjectID,pszType,resId)

#define IMtsResourceEvents_OnResourceDestroy(This,perfCount,ObjectID,pszType,resId)	\
    (This)->lpVtbl -> OnResourceDestroy(This,perfCount,ObjectID,pszType,resId)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMtsResourceEvents_OnResourceCreate_Proxy( 
    IMtsResourceEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ REFGUID guidActivity,
    /* [in] */ MTS_OBJID ObjectID,
    /* [in] */ LPCOLESTR pszType,
    /* [in] */ MTS_RESID resId);


void __RPC_STUB IMtsResourceEvents_OnResourceCreate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMtsResourceEvents_OnResourceAllocate_Proxy( 
    IMtsResourceEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ REFGUID guidActivity,
    /* [in] */ MTS_OBJID ObjectID,
    /* [in] */ LPCOLESTR pszType,
    /* [in] */ MTS_RESID resId);


void __RPC_STUB IMtsResourceEvents_OnResourceAllocate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMtsResourceEvents_OnResourceRecycle_Proxy( 
    IMtsResourceEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ MTS_OBJID ObjectID,
    /* [in] */ LPCOLESTR pszType,
    /* [in] */ MTS_RESID resId);


void __RPC_STUB IMtsResourceEvents_OnResourceRecycle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMtsResourceEvents_OnResourceDestroy_Proxy( 
    IMtsResourceEvents __RPC_FAR * This,
    /* [in] */ LONGLONG perfCount,
    /* [in] */ MTS_OBJID ObjectID,
    /* [in] */ LPCOLESTR pszType,
    /* [in] */ MTS_RESID resId);


void __RPC_STUB IMtsResourceEvents_OnResourceDestroy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMtsResourceEvents_INTERFACE_DEFINED__ */


#ifndef __IMtsSecurityEvents_INTERFACE_DEFINED__
#define __IMtsSecurityEvents_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IMtsSecurityEvents
 * at Thu Sep 11 16:03:12 1997
 * using MIDL 3.01.75
 ****************************************/
/* [uuid][object] */ 



EXTERN_C const IID IID_IMtsSecurityEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("55EB3AFB-0A11-11d1-B1B4-00AA00BA3258")
    IMtsSecurityEvents : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnAuthenticate( 
            LONGLONG perfCount,
            REFGUID guidActivity,
            ULONG cbByteOrig,
            /* [size_is][in] */ BYTE __RPC_FAR *pSidOriginalUser,
            ULONG cbByteCur,
            /* [size_is][in] */ BYTE __RPC_FAR *pSidCurrentUser,
            BOOL bCurrentUserInpersonatingInProc) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMtsSecurityEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMtsSecurityEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMtsSecurityEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMtsSecurityEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnAuthenticate )( 
            IMtsSecurityEvents __RPC_FAR * This,
            LONGLONG perfCount,
            REFGUID guidActivity,
            ULONG cbByteOrig,
            /* [size_is][in] */ BYTE __RPC_FAR *pSidOriginalUser,
            ULONG cbByteCur,
            /* [size_is][in] */ BYTE __RPC_FAR *pSidCurrentUser,
            BOOL bCurrentUserInpersonatingInProc);
        
        END_INTERFACE
    } IMtsSecurityEventsVtbl;

    interface IMtsSecurityEvents
    {
        CONST_VTBL struct IMtsSecurityEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMtsSecurityEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMtsSecurityEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMtsSecurityEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMtsSecurityEvents_OnAuthenticate(This,perfCount,guidActivity,cbByteOrig,pSidOriginalUser,cbByteCur,pSidCurrentUser,bCurrentUserInpersonatingInProc)	\
    (This)->lpVtbl -> OnAuthenticate(This,perfCount,guidActivity,cbByteOrig,pSidOriginalUser,cbByteCur,pSidCurrentUser,bCurrentUserInpersonatingInProc)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMtsSecurityEvents_OnAuthenticate_Proxy( 
    IMtsSecurityEvents __RPC_FAR * This,
    LONGLONG perfCount,
    REFGUID guidActivity,
    ULONG cbByteOrig,
    /* [size_is][in] */ BYTE __RPC_FAR *pSidOriginalUser,
    ULONG cbByteCur,
    /* [size_is][in] */ BYTE __RPC_FAR *pSidCurrentUser,
    BOOL bCurrentUserInpersonatingInProc);


void __RPC_STUB IMtsSecurityEvents_OnAuthenticate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMtsSecurityEvents_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
