/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0106 */
/* at Tue Oct 21 12:55:10 1997
 */
/* Compiler settings for D:\root\bpc\tssadmin\TSSAdmin.odl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __interfaces_h__
#define __interfaces_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IScheduledItems_FWD_DEFINED__
#define __IScheduledItems_FWD_DEFINED__
typedef interface IScheduledItems IScheduledItems;
#endif 	/* __IScheduledItems_FWD_DEFINED__ */


#ifndef __ScheduledItems_FWD_DEFINED__
#define __ScheduledItems_FWD_DEFINED__

#ifdef __cplusplus
typedef class ScheduledItems ScheduledItems;
#else
typedef struct ScheduledItems ScheduledItems;
#endif /* __cplusplus */

#endif 	/* __ScheduledItems_FWD_DEFINED__ */


#ifndef __ITelevisionServices_FWD_DEFINED__
#define __ITelevisionServices_FWD_DEFINED__
typedef interface ITelevisionServices ITelevisionServices;
#endif 	/* __ITelevisionServices_FWD_DEFINED__ */


#ifndef __TelevisionServices_FWD_DEFINED__
#define __TelevisionServices_FWD_DEFINED__

#ifdef __cplusplus
typedef class TelevisionServices TelevisionServices;
#else
typedef struct TelevisionServices TelevisionServices;
#endif /* __cplusplus */

#endif 	/* __TelevisionServices_FWD_DEFINED__ */


#ifndef __TaskTrigger_FWD_DEFINED__
#define __TaskTrigger_FWD_DEFINED__

#ifdef __cplusplus
typedef class TaskTrigger TaskTrigger;
#else
typedef struct TaskTrigger TaskTrigger;
#endif /* __cplusplus */

#endif 	/* __TaskTrigger_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __BPC_Television_Services_LIBRARY_DEFINED__
#define __BPC_Television_Services_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: BPC_Television_Services
 * at Tue Oct 21 12:55:10 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [helpstring][version][uuid] */ 


#define	LE_LOUD	( 0x1 )

#define	LE_DONTOVERWRITE	( 0x2 )


DEFINE_GUID(LIBID_BPC_Television_Services,0x5D0F9B81,0x500B,0x11CF,0xBE,0xBC,0x00,0xAA,0x00,0xB8,0xC3,0x2E);

#ifndef __IScheduledItems_INTERFACE_DEFINED__
#define __IScheduledItems_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IScheduledItems
 * at Tue Oct 21 12:55:10 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [object][oleautomation][dual][hidden][uuid] */ 



DEFINE_GUID(IID_IScheduledItems,0x8236d590,0x18b4,0x11d0,0xbd,0x2e,0x00,0xaa,0x00,0x61,0x56,0xad);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8236d590-18b4-11d0-bd2e-00aa006156ad")
    IScheduledItems : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ BSTR Index,
            /* [out] */ BSTR __RPC_FAR *User,
            /* [out] */ BSTR __RPC_FAR *ShowReference,
            /* [out] */ BSTR __RPC_FAR *Application,
            /* [out] */ BSTR __RPC_FAR *Directory,
            /* [out] */ unsigned long __RPC_FAR *AdvanceMinutes,
            /* [out] */ BSTR __RPC_FAR *Parameters,
            /* [retval][out] */ VARIANT __RPC_FAR *Task) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *plRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ BSTR Workspace,
            /* [in] */ BSTR ShowReference,
            /* [in] */ BSTR Application,
            /* [in] */ BSTR Directory,
            /* [in] */ unsigned long AdvanceMinutes,
            /* [in] */ BSTR Parameters,
            /* [out][retval] */ VARIANT __RPC_FAR *pSafeArray) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddFromQuery( 
            /* [in] */ BSTR Workspace,
            /* [in] */ BSTR QueryName,
            /* [in] */ BSTR Application,
            /* [in] */ BSTR Directory,
            /* [in] */ unsigned long AdvanceMinutes,
            /* [in] */ BSTR Parameters,
            /* [out][retval] */ VARIANT __RPC_FAR *pSafeArray) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ BSTR Index) = 0;
        
        virtual /* [restricted][id] */ HRESULT STDMETHODCALLTYPE _NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IScheduledItemsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IScheduledItems __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IScheduledItems __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IScheduledItems __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IScheduledItems __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IScheduledItems __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IScheduledItems __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IScheduledItems __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IScheduledItems __RPC_FAR * This,
            /* [in] */ BSTR Index,
            /* [out] */ BSTR __RPC_FAR *User,
            /* [out] */ BSTR __RPC_FAR *ShowReference,
            /* [out] */ BSTR __RPC_FAR *Application,
            /* [out] */ BSTR __RPC_FAR *Directory,
            /* [out] */ unsigned long __RPC_FAR *AdvanceMinutes,
            /* [out] */ BSTR __RPC_FAR *Parameters,
            /* [retval][out] */ VARIANT __RPC_FAR *Task);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IScheduledItems __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IScheduledItems __RPC_FAR * This,
            /* [in] */ BSTR Workspace,
            /* [in] */ BSTR ShowReference,
            /* [in] */ BSTR Application,
            /* [in] */ BSTR Directory,
            /* [in] */ unsigned long AdvanceMinutes,
            /* [in] */ BSTR Parameters,
            /* [out][retval] */ VARIANT __RPC_FAR *pSafeArray);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddFromQuery )( 
            IScheduledItems __RPC_FAR * This,
            /* [in] */ BSTR Workspace,
            /* [in] */ BSTR QueryName,
            /* [in] */ BSTR Application,
            /* [in] */ BSTR Directory,
            /* [in] */ unsigned long AdvanceMinutes,
            /* [in] */ BSTR Parameters,
            /* [out][retval] */ VARIANT __RPC_FAR *pSafeArray);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IScheduledItems __RPC_FAR * This,
            /* [in] */ BSTR Index);
        
        /* [restricted][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_NewEnum )( 
            IScheduledItems __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);
        
        END_INTERFACE
    } IScheduledItemsVtbl;

    interface IScheduledItems
    {
        CONST_VTBL struct IScheduledItemsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IScheduledItems_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IScheduledItems_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IScheduledItems_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IScheduledItems_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IScheduledItems_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IScheduledItems_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IScheduledItems_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IScheduledItems_Item(This,Index,User,ShowReference,Application,Directory,AdvanceMinutes,Parameters,Task)	\
    (This)->lpVtbl -> Item(This,Index,User,ShowReference,Application,Directory,AdvanceMinutes,Parameters,Task)

#define IScheduledItems_get_Count(This,plRetVal)	\
    (This)->lpVtbl -> get_Count(This,plRetVal)

#define IScheduledItems_Add(This,Workspace,ShowReference,Application,Directory,AdvanceMinutes,Parameters,pSafeArray)	\
    (This)->lpVtbl -> Add(This,Workspace,ShowReference,Application,Directory,AdvanceMinutes,Parameters,pSafeArray)

#define IScheduledItems_AddFromQuery(This,Workspace,QueryName,Application,Directory,AdvanceMinutes,Parameters,pSafeArray)	\
    (This)->lpVtbl -> AddFromQuery(This,Workspace,QueryName,Application,Directory,AdvanceMinutes,Parameters,pSafeArray)

#define IScheduledItems_Remove(This,Index)	\
    (This)->lpVtbl -> Remove(This,Index)

#define IScheduledItems__NewEnum(This,ppUnk)	\
    (This)->lpVtbl -> _NewEnum(This,ppUnk)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScheduledItems_Item_Proxy( 
    IScheduledItems __RPC_FAR * This,
    /* [in] */ BSTR Index,
    /* [out] */ BSTR __RPC_FAR *User,
    /* [out] */ BSTR __RPC_FAR *ShowReference,
    /* [out] */ BSTR __RPC_FAR *Application,
    /* [out] */ BSTR __RPC_FAR *Directory,
    /* [out] */ unsigned long __RPC_FAR *AdvanceMinutes,
    /* [out] */ BSTR __RPC_FAR *Parameters,
    /* [retval][out] */ VARIANT __RPC_FAR *Task);


void __RPC_STUB IScheduledItems_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE IScheduledItems_get_Count_Proxy( 
    IScheduledItems __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plRetVal);


void __RPC_STUB IScheduledItems_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScheduledItems_Add_Proxy( 
    IScheduledItems __RPC_FAR * This,
    /* [in] */ BSTR Workspace,
    /* [in] */ BSTR ShowReference,
    /* [in] */ BSTR Application,
    /* [in] */ BSTR Directory,
    /* [in] */ unsigned long AdvanceMinutes,
    /* [in] */ BSTR Parameters,
    /* [out][retval] */ VARIANT __RPC_FAR *pSafeArray);


void __RPC_STUB IScheduledItems_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IScheduledItems_AddFromQuery_Proxy( 
    IScheduledItems __RPC_FAR * This,
    /* [in] */ BSTR Workspace,
    /* [in] */ BSTR QueryName,
    /* [in] */ BSTR Application,
    /* [in] */ BSTR Directory,
    /* [in] */ unsigned long AdvanceMinutes,
    /* [in] */ BSTR Parameters,
    /* [out][retval] */ VARIANT __RPC_FAR *pSafeArray);


void __RPC_STUB IScheduledItems_AddFromQuery_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IScheduledItems_Remove_Proxy( 
    IScheduledItems __RPC_FAR * This,
    /* [in] */ BSTR Index);


void __RPC_STUB IScheduledItems_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][id] */ HRESULT STDMETHODCALLTYPE IScheduledItems__NewEnum_Proxy( 
    IScheduledItems __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppUnk);


void __RPC_STUB IScheduledItems__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IScheduledItems_INTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_ScheduledItems,0xe66dd600,0x18b5,0x11d0,0xbd,0x2e,0x00,0xaa,0x00,0x61,0x56,0xad);

#ifdef __cplusplus

class DECLSPEC_UUID("e66dd600-18b5-11d0-bd2e-00aa006156ad")
ScheduledItems;
#endif

#ifndef __ITelevisionServices_INTERFACE_DEFINED__
#define __ITelevisionServices_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ITelevisionServices
 * at Tue Oct 21 12:55:10 1997
 * using MIDL 3.03.0106
 ****************************************/
/* [object][oleautomation][dual][hidden][uuid] */ 



DEFINE_GUID(IID_ITelevisionServices,0x5D0F9B84,0x500B,0x11CF,0xBE,0xBC,0x00,0xAA,0x00,0xB8,0xC3,0x2E);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5D0F9B84-500B-11CF-BEBC-00AA00B8C32E")
    ITelevisionServices : public IDispatch
    {
    public:
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_SystemFile( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_DatabaseFile( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ScheduledItems( 
            /* [retval][out] */ IScheduledItems __RPC_FAR *__RPC_FAR *ppScheduledRet) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RestrictionQueryName( 
            /* [in] */ BSTR UserName,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CreateUser( 
            /* [in] */ /* external definition not present */ Workspace __RPC_FAR *Workspace,
            /* [in] */ BSTR UserName,
            /* [in] */ BSTR PID,
            /* [in] */ BSTR Password,
            /* [in] */ BSTR RestrictWhere,
            /* [in] */ VARIANT_BOOL Adult) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DeleteUser( 
            /* [in] */ /* external definition not present */ Workspace __RPC_FAR *Workspace,
            /* [in] */ BSTR UserName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ResolveBroadcast( 
            /* [in] */ BSTR Workspace,
            /* [in] */ BSTR QueryName,
            /* [in] */ BSTR ShowReference) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SplitBroadcastSchedule( 
            /* [in] */ BSTR ShowReference,
            /* [out] */ BSTR __RPC_FAR *EpisodeTitle,
            /* [out] */ short __RPC_FAR *Channel,
            /* [out] */ BSTR __RPC_FAR *Network,
            /* [out] */ BSTR __RPC_FAR *Station,
            /* [out] */ long __RPC_FAR *TuningSpace,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *TaskTrigger) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SplitSimpleBroadcastSchedule( 
            /* [in] */ BSTR ShowReference,
            /* [out] */ BSTR __RPC_FAR *EpisodeTitle,
            /* [out] */ short __RPC_FAR *Channel,
            /* [out] */ BSTR __RPC_FAR *Network,
            /* [out] */ BSTR __RPC_FAR *Station,
            /* [out] */ long __RPC_FAR *TuningSpace,
            /* [out] */ DATE __RPC_FAR *Time) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE MakeLocalBroadcastSchedule( 
            /* [in] */ BSTR EpisodeTitle,
            /* [in] */ short Channel,
            /* [in] */ BSTR Network,
            /* [in] */ BSTR Station,
            /* [in] */ long TuningSpace,
            /* [in] */ VARIANT Time,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE MakeRemoteBroadcastSchedule( 
            /* [in] */ BSTR EpisodeTitle,
            /* [in] */ BSTR Network,
            /* [in] */ VARIANT Time,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE TuningSpaceNameFromNumber( 
            /* [in] */ long TuningID,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE TuningSpaceNumberFromName( 
            /* [in] */ BSTR Name,
            /* [retval][out] */ long __RPC_FAR *plRetVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ResolveScheduledReminders( 
            /* [in] */ BSTR Workspace,
            /* [in] */ BSTR QueryName,
            /* [in] */ BSTR UserName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE LoadEnhancement( 
            /* [in] */ /* external definition not present */ Workspace __RPC_FAR *piDAOWorkspace,
            /* [in] */ BSTR bstrEnhancementID,
            /* [in] */ BSTR bstrShowReference,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrPreloadURL,
            /* [in] */ BSTR bstrAddress,
            /* [in] */ DATE dateExpire,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE LoadEnhancementsFromFile( 
            /* [in] */ /* external definition not present */ Workspace __RPC_FAR *piDAOWorkspace,
            /* [in] */ BSTR bstrEnhancementsFile) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DeleteEnhancementFromID( 
            /* [in] */ /* external definition not present */ Workspace __RPC_FAR *piDAOWorkspace,
            /* [in] */ BSTR bstrEnhancementsID) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DeleteOldEnhancements( 
            /* [in] */ /* external definition not present */ Workspace __RPC_FAR *piDAOWorkspace) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RemapEnhancements( 
            /* [in] */ /* external definition not present */ Workspace __RPC_FAR *piDAOWorkspace) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ClipboardFormat( 
            /* [retval][out] */ long __RPC_FAR *plRetVal) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ClipboardFormatName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ResolveBroadcastInclusively( 
            /* [in] */ BSTR Workspace,
            /* [in] */ BSTR QueryName,
            /* [in] */ BSTR ShowReference) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITelevisionServicesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITelevisionServices __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITelevisionServices __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITelevisionServices __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITelevisionServices __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITelevisionServices __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITelevisionServices __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITelevisionServices __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SystemFile )( 
            ITelevisionServices __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DatabaseFile )( 
            ITelevisionServices __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ScheduledItems )( 
            ITelevisionServices __RPC_FAR * This,
            /* [retval][out] */ IScheduledItems __RPC_FAR *__RPC_FAR *ppScheduledRet);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RestrictionQueryName )( 
            ITelevisionServices __RPC_FAR * This,
            /* [in] */ BSTR UserName,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateUser )( 
            ITelevisionServices __RPC_FAR * This,
            /* [in] */ /* external definition not present */ Workspace __RPC_FAR *Workspace,
            /* [in] */ BSTR UserName,
            /* [in] */ BSTR PID,
            /* [in] */ BSTR Password,
            /* [in] */ BSTR RestrictWhere,
            /* [in] */ VARIANT_BOOL Adult);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteUser )( 
            ITelevisionServices __RPC_FAR * This,
            /* [in] */ /* external definition not present */ Workspace __RPC_FAR *Workspace,
            /* [in] */ BSTR UserName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResolveBroadcast )( 
            ITelevisionServices __RPC_FAR * This,
            /* [in] */ BSTR Workspace,
            /* [in] */ BSTR QueryName,
            /* [in] */ BSTR ShowReference);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SplitBroadcastSchedule )( 
            ITelevisionServices __RPC_FAR * This,
            /* [in] */ BSTR ShowReference,
            /* [out] */ BSTR __RPC_FAR *EpisodeTitle,
            /* [out] */ short __RPC_FAR *Channel,
            /* [out] */ BSTR __RPC_FAR *Network,
            /* [out] */ BSTR __RPC_FAR *Station,
            /* [out] */ long __RPC_FAR *TuningSpace,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *TaskTrigger);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SplitSimpleBroadcastSchedule )( 
            ITelevisionServices __RPC_FAR * This,
            /* [in] */ BSTR ShowReference,
            /* [out] */ BSTR __RPC_FAR *EpisodeTitle,
            /* [out] */ short __RPC_FAR *Channel,
            /* [out] */ BSTR __RPC_FAR *Network,
            /* [out] */ BSTR __RPC_FAR *Station,
            /* [out] */ long __RPC_FAR *TuningSpace,
            /* [out] */ DATE __RPC_FAR *Time);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MakeLocalBroadcastSchedule )( 
            ITelevisionServices __RPC_FAR * This,
            /* [in] */ BSTR EpisodeTitle,
            /* [in] */ short Channel,
            /* [in] */ BSTR Network,
            /* [in] */ BSTR Station,
            /* [in] */ long TuningSpace,
            /* [in] */ VARIANT Time,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MakeRemoteBroadcastSchedule )( 
            ITelevisionServices __RPC_FAR * This,
            /* [in] */ BSTR EpisodeTitle,
            /* [in] */ BSTR Network,
            /* [in] */ VARIANT Time,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TuningSpaceNameFromNumber )( 
            ITelevisionServices __RPC_FAR * This,
            /* [in] */ long TuningID,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TuningSpaceNumberFromName )( 
            ITelevisionServices __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [retval][out] */ long __RPC_FAR *plRetVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResolveScheduledReminders )( 
            ITelevisionServices __RPC_FAR * This,
            /* [in] */ BSTR Workspace,
            /* [in] */ BSTR QueryName,
            /* [in] */ BSTR UserName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadEnhancement )( 
            ITelevisionServices __RPC_FAR * This,
            /* [in] */ /* external definition not present */ Workspace __RPC_FAR *piDAOWorkspace,
            /* [in] */ BSTR bstrEnhancementID,
            /* [in] */ BSTR bstrShowReference,
            /* [in] */ BSTR bstrTitle,
            /* [in] */ BSTR bstrPreloadURL,
            /* [in] */ BSTR bstrAddress,
            /* [in] */ DATE dateExpire,
            /* [in] */ DWORD dwFlags);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadEnhancementsFromFile )( 
            ITelevisionServices __RPC_FAR * This,
            /* [in] */ /* external definition not present */ Workspace __RPC_FAR *piDAOWorkspace,
            /* [in] */ BSTR bstrEnhancementsFile);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteEnhancementFromID )( 
            ITelevisionServices __RPC_FAR * This,
            /* [in] */ /* external definition not present */ Workspace __RPC_FAR *piDAOWorkspace,
            /* [in] */ BSTR bstrEnhancementsID);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteOldEnhancements )( 
            ITelevisionServices __RPC_FAR * This,
            /* [in] */ /* external definition not present */ Workspace __RPC_FAR *piDAOWorkspace);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemapEnhancements )( 
            ITelevisionServices __RPC_FAR * This,
            /* [in] */ /* external definition not present */ Workspace __RPC_FAR *piDAOWorkspace);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClipboardFormat )( 
            ITelevisionServices __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plRetVal);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClipboardFormatName )( 
            ITelevisionServices __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResolveBroadcastInclusively )( 
            ITelevisionServices __RPC_FAR * This,
            /* [in] */ BSTR Workspace,
            /* [in] */ BSTR QueryName,
            /* [in] */ BSTR ShowReference);
        
        END_INTERFACE
    } ITelevisionServicesVtbl;

    interface ITelevisionServices
    {
        CONST_VTBL struct ITelevisionServicesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITelevisionServices_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITelevisionServices_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITelevisionServices_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITelevisionServices_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITelevisionServices_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITelevisionServices_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITelevisionServices_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITelevisionServices_get_SystemFile(This,pbstrRetVal)	\
    (This)->lpVtbl -> get_SystemFile(This,pbstrRetVal)

#define ITelevisionServices_get_DatabaseFile(This,pbstrRetVal)	\
    (This)->lpVtbl -> get_DatabaseFile(This,pbstrRetVal)

#define ITelevisionServices_get_ScheduledItems(This,ppScheduledRet)	\
    (This)->lpVtbl -> get_ScheduledItems(This,ppScheduledRet)

#define ITelevisionServices_RestrictionQueryName(This,UserName,pbstrRetVal)	\
    (This)->lpVtbl -> RestrictionQueryName(This,UserName,pbstrRetVal)

#define ITelevisionServices_CreateUser(This,Workspace,UserName,PID,Password,RestrictWhere,Adult)	\
    (This)->lpVtbl -> CreateUser(This,Workspace,UserName,PID,Password,RestrictWhere,Adult)

#define ITelevisionServices_DeleteUser(This,Workspace,UserName)	\
    (This)->lpVtbl -> DeleteUser(This,Workspace,UserName)

#define ITelevisionServices_ResolveBroadcast(This,Workspace,QueryName,ShowReference)	\
    (This)->lpVtbl -> ResolveBroadcast(This,Workspace,QueryName,ShowReference)

#define ITelevisionServices_SplitBroadcastSchedule(This,ShowReference,EpisodeTitle,Channel,Network,Station,TuningSpace,TaskTrigger)	\
    (This)->lpVtbl -> SplitBroadcastSchedule(This,ShowReference,EpisodeTitle,Channel,Network,Station,TuningSpace,TaskTrigger)

#define ITelevisionServices_SplitSimpleBroadcastSchedule(This,ShowReference,EpisodeTitle,Channel,Network,Station,TuningSpace,Time)	\
    (This)->lpVtbl -> SplitSimpleBroadcastSchedule(This,ShowReference,EpisodeTitle,Channel,Network,Station,TuningSpace,Time)

#define ITelevisionServices_MakeLocalBroadcastSchedule(This,EpisodeTitle,Channel,Network,Station,TuningSpace,Time,pbstrRetVal)	\
    (This)->lpVtbl -> MakeLocalBroadcastSchedule(This,EpisodeTitle,Channel,Network,Station,TuningSpace,Time,pbstrRetVal)

#define ITelevisionServices_MakeRemoteBroadcastSchedule(This,EpisodeTitle,Network,Time,pbstrRetVal)	\
    (This)->lpVtbl -> MakeRemoteBroadcastSchedule(This,EpisodeTitle,Network,Time,pbstrRetVal)

#define ITelevisionServices_TuningSpaceNameFromNumber(This,TuningID,pbstrRetVal)	\
    (This)->lpVtbl -> TuningSpaceNameFromNumber(This,TuningID,pbstrRetVal)

#define ITelevisionServices_TuningSpaceNumberFromName(This,Name,plRetVal)	\
    (This)->lpVtbl -> TuningSpaceNumberFromName(This,Name,plRetVal)

#define ITelevisionServices_ResolveScheduledReminders(This,Workspace,QueryName,UserName)	\
    (This)->lpVtbl -> ResolveScheduledReminders(This,Workspace,QueryName,UserName)

#define ITelevisionServices_LoadEnhancement(This,piDAOWorkspace,bstrEnhancementID,bstrShowReference,bstrTitle,bstrPreloadURL,bstrAddress,dateExpire,fLoud)	\
    (This)->lpVtbl -> LoadEnhancement(This,piDAOWorkspace,bstrEnhancementID,bstrShowReference,bstrTitle,bstrPreloadURL,bstrAddress,dateExpire,dwFlags)

#define ITelevisionServices_LoadEnhancementsFromFile(This,piDAOWorkspace,bstrEnhancementsFile)	\
    (This)->lpVtbl -> LoadEnhancementsFromFile(This,piDAOWorkspace,bstrEnhancementsFile)

#define ITelevisionServices_DeleteEnhancementFromID(This,piDAOWorkspace,bstrEnhancementsID)	\
    (This)->lpVtbl -> DeleteEnhancementFromID(This,piDAOWorkspace,bstrEnhancementsID)

#define ITelevisionServices_DeleteOldEnhancements(This,piDAOWorkspace)	\
    (This)->lpVtbl -> DeleteOldEnhancements(This,piDAOWorkspace)

#define ITelevisionServices_RemapEnhancements(This,piDAOWorkspace)	\
    (This)->lpVtbl -> RemapEnhancements(This,piDAOWorkspace)

#define ITelevisionServices_get_ClipboardFormat(This,plRetVal)	\
    (This)->lpVtbl -> get_ClipboardFormat(This,plRetVal)

#define ITelevisionServices_get_ClipboardFormatName(This,pbstrName)	\
    (This)->lpVtbl -> get_ClipboardFormatName(This,pbstrName)

#define ITelevisionServices_ResolveBroadcastInclusively(This,Workspace,QueryName,ShowReference)	\
    (This)->lpVtbl -> ResolveBroadcastInclusively(This,Workspace,QueryName,ShowReference)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget][id] */ HRESULT STDMETHODCALLTYPE ITelevisionServices_get_SystemFile_Proxy( 
    ITelevisionServices __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal);


void __RPC_STUB ITelevisionServices_get_SystemFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ITelevisionServices_get_DatabaseFile_Proxy( 
    ITelevisionServices __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal);


void __RPC_STUB ITelevisionServices_get_DatabaseFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ITelevisionServices_get_ScheduledItems_Proxy( 
    ITelevisionServices __RPC_FAR * This,
    /* [retval][out] */ IScheduledItems __RPC_FAR *__RPC_FAR *ppScheduledRet);


void __RPC_STUB ITelevisionServices_get_ScheduledItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ITelevisionServices_RestrictionQueryName_Proxy( 
    ITelevisionServices __RPC_FAR * This,
    /* [in] */ BSTR UserName,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal);


void __RPC_STUB ITelevisionServices_RestrictionQueryName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ITelevisionServices_CreateUser_Proxy( 
    ITelevisionServices __RPC_FAR * This,
    /* [in] */ /* external definition not present */ Workspace __RPC_FAR *Workspace,
    /* [in] */ BSTR UserName,
    /* [in] */ BSTR PID,
    /* [in] */ BSTR Password,
    /* [in] */ BSTR RestrictWhere,
    /* [in] */ VARIANT_BOOL Adult);


void __RPC_STUB ITelevisionServices_CreateUser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ITelevisionServices_DeleteUser_Proxy( 
    ITelevisionServices __RPC_FAR * This,
    /* [in] */ /* external definition not present */ Workspace __RPC_FAR *Workspace,
    /* [in] */ BSTR UserName);


void __RPC_STUB ITelevisionServices_DeleteUser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ITelevisionServices_ResolveBroadcast_Proxy( 
    ITelevisionServices __RPC_FAR * This,
    /* [in] */ BSTR Workspace,
    /* [in] */ BSTR QueryName,
    /* [in] */ BSTR ShowReference);


void __RPC_STUB ITelevisionServices_ResolveBroadcast_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ITelevisionServices_SplitBroadcastSchedule_Proxy( 
    ITelevisionServices __RPC_FAR * This,
    /* [in] */ BSTR ShowReference,
    /* [out] */ BSTR __RPC_FAR *EpisodeTitle,
    /* [out] */ short __RPC_FAR *Channel,
    /* [out] */ BSTR __RPC_FAR *Network,
    /* [out] */ BSTR __RPC_FAR *Station,
    /* [out] */ long __RPC_FAR *TuningSpace,
    /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *TaskTrigger);


void __RPC_STUB ITelevisionServices_SplitBroadcastSchedule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ITelevisionServices_SplitSimpleBroadcastSchedule_Proxy( 
    ITelevisionServices __RPC_FAR * This,
    /* [in] */ BSTR ShowReference,
    /* [out] */ BSTR __RPC_FAR *EpisodeTitle,
    /* [out] */ short __RPC_FAR *Channel,
    /* [out] */ BSTR __RPC_FAR *Network,
    /* [out] */ BSTR __RPC_FAR *Station,
    /* [out] */ long __RPC_FAR *TuningSpace,
    /* [out] */ DATE __RPC_FAR *Time);


void __RPC_STUB ITelevisionServices_SplitSimpleBroadcastSchedule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ITelevisionServices_MakeLocalBroadcastSchedule_Proxy( 
    ITelevisionServices __RPC_FAR * This,
    /* [in] */ BSTR EpisodeTitle,
    /* [in] */ short Channel,
    /* [in] */ BSTR Network,
    /* [in] */ BSTR Station,
    /* [in] */ long TuningSpace,
    /* [in] */ VARIANT Time,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal);


void __RPC_STUB ITelevisionServices_MakeLocalBroadcastSchedule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ITelevisionServices_MakeRemoteBroadcastSchedule_Proxy( 
    ITelevisionServices __RPC_FAR * This,
    /* [in] */ BSTR EpisodeTitle,
    /* [in] */ BSTR Network,
    /* [in] */ VARIANT Time,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal);


void __RPC_STUB ITelevisionServices_MakeRemoteBroadcastSchedule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ITelevisionServices_TuningSpaceNameFromNumber_Proxy( 
    ITelevisionServices __RPC_FAR * This,
    /* [in] */ long TuningID,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrRetVal);


void __RPC_STUB ITelevisionServices_TuningSpaceNameFromNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ITelevisionServices_TuningSpaceNumberFromName_Proxy( 
    ITelevisionServices __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [retval][out] */ long __RPC_FAR *plRetVal);


void __RPC_STUB ITelevisionServices_TuningSpaceNumberFromName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ITelevisionServices_ResolveScheduledReminders_Proxy( 
    ITelevisionServices __RPC_FAR * This,
    /* [in] */ BSTR Workspace,
    /* [in] */ BSTR QueryName,
    /* [in] */ BSTR UserName);


void __RPC_STUB ITelevisionServices_ResolveScheduledReminders_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ITelevisionServices_LoadEnhancement_Proxy( 
    ITelevisionServices __RPC_FAR * This,
    /* [in] */ /* external definition not present */ Workspace __RPC_FAR *piDAOWorkspace,
    /* [in] */ BSTR bstrEnhancementID,
    /* [in] */ BSTR bstrShowReference,
    /* [in] */ BSTR bstrTitle,
    /* [in] */ BSTR bstrPreloadURL,
    /* [in] */ BSTR bstrAddress,
    /* [in] */ DATE dateExpire,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB ITelevisionServices_LoadEnhancement_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ITelevisionServices_LoadEnhancementsFromFile_Proxy( 
    ITelevisionServices __RPC_FAR * This,
    /* [in] */ /* external definition not present */ Workspace __RPC_FAR *piDAOWorkspace,
    /* [in] */ BSTR bstrEnhancementsFile);


void __RPC_STUB ITelevisionServices_LoadEnhancementsFromFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ITelevisionServices_DeleteEnhancementFromID_Proxy( 
    ITelevisionServices __RPC_FAR * This,
    /* [in] */ /* external definition not present */ Workspace __RPC_FAR *piDAOWorkspace,
    /* [in] */ BSTR bstrEnhancementsID);


void __RPC_STUB ITelevisionServices_DeleteEnhancementFromID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ITelevisionServices_DeleteOldEnhancements_Proxy( 
    ITelevisionServices __RPC_FAR * This,
    /* [in] */ /* external definition not present */ Workspace __RPC_FAR *piDAOWorkspace);


void __RPC_STUB ITelevisionServices_DeleteOldEnhancements_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ITelevisionServices_RemapEnhancements_Proxy( 
    ITelevisionServices __RPC_FAR * This,
    /* [in] */ /* external definition not present */ Workspace __RPC_FAR *piDAOWorkspace);


void __RPC_STUB ITelevisionServices_RemapEnhancements_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ITelevisionServices_get_ClipboardFormat_Proxy( 
    ITelevisionServices __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plRetVal);


void __RPC_STUB ITelevisionServices_get_ClipboardFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ITelevisionServices_get_ClipboardFormatName_Proxy( 
    ITelevisionServices __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB ITelevisionServices_get_ClipboardFormatName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ITelevisionServices_ResolveBroadcastInclusively_Proxy( 
    ITelevisionServices __RPC_FAR * This,
    /* [in] */ BSTR Workspace,
    /* [in] */ BSTR QueryName,
    /* [in] */ BSTR ShowReference);


void __RPC_STUB ITelevisionServices_ResolveBroadcastInclusively_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITelevisionServices_INTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_TelevisionServices,0x5D0F9B85,0x500B,0x11CF,0xBE,0xBC,0x00,0xAA,0x00,0xB8,0xC3,0x2E);

#ifdef __cplusplus

class DECLSPEC_UUID("5D0F9B85-500B-11CF-BEBC-00AA00B8C32E")
TelevisionServices;
#endif

DEFINE_GUID(CLSID_TaskTrigger,0xf1c70270,0xb1d1,0x11d0,0xbd,0x4e,0x00,0xaa,0x00,0x61,0x56,0xad);

#ifdef __cplusplus

class DECLSPEC_UUID("f1c70270-b1d1-11d0-bd4e-00aa006156ad")
TaskTrigger;
#endif
#endif /* __BPC_Television_Services_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
