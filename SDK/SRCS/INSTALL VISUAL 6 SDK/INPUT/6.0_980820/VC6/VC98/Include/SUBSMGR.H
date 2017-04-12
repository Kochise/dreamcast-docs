/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.02.88 */
/* at Mon Nov 17 12:04:08 1997
 */
/* Compiler settings for subsmgr.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"

#ifndef __subsmgr_h__
#define __subsmgr_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISubscriptionMgr_FWD_DEFINED__
#define __ISubscriptionMgr_FWD_DEFINED__
typedef interface ISubscriptionMgr ISubscriptionMgr;
#endif 	/* __ISubscriptionMgr_FWD_DEFINED__ */


#ifndef __SubscriptionMgr_FWD_DEFINED__
#define __SubscriptionMgr_FWD_DEFINED__

#ifdef __cplusplus
typedef class SubscriptionMgr SubscriptionMgr;
#else
typedef struct SubscriptionMgr SubscriptionMgr;
#endif /* __cplusplus */

#endif 	/* __SubscriptionMgr_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_subsmgr_0000
 * at Mon Nov 17 12:04:08 1997
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


//=--------------------------------------------------------------------------=
// subsmgr.h
//=--------------------------------------------------------------------------=
// (C) Copyright 1995 - 1998 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=

#pragma comment(lib,"uuid.lib")

//---------------------------------------------------------------------------=
// Channel Manager Interfaces.



extern RPC_IF_HANDLE __MIDL_itf_subsmgr_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_subsmgr_0000_v0_0_s_ifspec;


#ifndef __SubscriptionMgr_LIBRARY_DEFINED__
#define __SubscriptionMgr_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: SubscriptionMgr
 * at Mon Nov 17 12:04:08 1997
 * using MIDL 3.02.88
 ****************************************/
/* [version][lcid][helpstring][uuid] */ 



EXTERN_C const IID LIBID_SubscriptionMgr;

#ifndef __ISubscriptionMgr_INTERFACE_DEFINED__
#define __ISubscriptionMgr_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: ISubscriptionMgr
 * at Mon Nov 17 12:04:08 1997
 * using MIDL 3.02.88
 ****************************************/
/* [object][helpstring][uuid] */ 


typedef 
enum SUBSCRIPTIONTYPE
    {	SUBSTYPE_URL	= 0,
	SUBSTYPE_CHANNEL	= 1,
	SUBSTYPE_DESKTOPURL	= 2,
	SUBSTYPE_EXTERNAL	= 3,
	SUBSTYPE_DESKTOPCHANNEL	= 4
    }	SUBSCRIPTIONTYPE;

typedef 
enum SUBSCRIPTIONINFOFLAGS
    {	SUBSINFO_SCHEDULE	= 0x1,
	SUBSINFO_RECURSE	= 0x2,
	SUBSINFO_WEBCRAWL	= 0x4,
	SUBSINFO_MAILNOT	= 0x8,
	SUBSINFO_MAXSIZEKB	= 0x10,
	SUBSINFO_USER	= 0x20,
	SUBSINFO_PASSWORD	= 0x40,
	SUBSINFO_TASKFLAGS	= 0x100,
	SUBSINFO_GLEAM	= 0x200,
	SUBSINFO_CHANGESONLY	= 0x400,
	SUBSINFO_CHANNELFLAGS	= 0x800,
	SUBSINFO_FRIENDLYNAME	= 0x2000,
	SUBSINFO_NEEDPASSWORD	= 0x4000,
	SUBSINFO_TYPE	= 0x8000
    }	SUBSCRIPTIONINFOFLAGS;

#define SUBSINFO_ALLFLAGS      0x0000EF7F
typedef 
enum CREATESUBSCRIPTIONFLAGS
    {	CREATESUBS_ADDTOFAVORITES	= 0x1,
	CREATESUBS_FROMFAVORITES	= 0x2,
	CREATESUBS_NOUI	= 0x4,
	CREATESUBS_NOSAVE	= 0x8,
	CREATESUBS_SOFTWAREUPDATE	= 0x10
    }	CREATESUBSCRIPTIONFLAGS;

typedef 
enum SUBSCRIPTIONSCHEDULE
    {	SUBSSCHED_AUTO	= 0,
	SUBSSCHED_DAILY	= 1,
	SUBSSCHED_WEEKLY	= 2,
	SUBSSCHED_CUSTOM	= 3,
	SUBSSCHED_MANUAL	= 4
    }	SUBSCRIPTIONSCHEDULE;

typedef struct  _tagSubscriptionInfo
    {
    DWORD cbSize;
    DWORD fUpdateFlags;
    SUBSCRIPTIONSCHEDULE schedule;
    CLSID customGroupCookie;
    LPVOID pTrigger;
    DWORD dwRecurseLevels;
    DWORD fWebcrawlerFlags;
    BOOL bMailNotification;
    BOOL bGleam;
    BOOL bChangesOnly;
    BOOL bNeedPassword;
    DWORD fChannelFlags;
    BSTR bstrUserName;
    BSTR bstrPassword;
    BSTR bstrFriendlyName;
    DWORD dwMaxSizeKB;
    SUBSCRIPTIONTYPE subType;
    DWORD fTaskFlags;
    DWORD dwReserved;
    }	SUBSCRIPTIONINFO;

typedef struct _tagSubscriptionInfo __RPC_FAR *LPSUBSCRIPTIONINFO;

typedef struct _tagSubscriptionInfo __RPC_FAR *PSUBSCRIPTIONINFO;


EXTERN_C const IID IID_ISubscriptionMgr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("085FB2C0-0DF8-11d1-8F4B-00A0C905413F")
    ISubscriptionMgr : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE DeleteSubscription( 
            /* [in] */ LPCWSTR pwszURL,
            /* [in] */ HWND hwnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UpdateSubscription( 
            /* [in] */ LPCWSTR pwszURL) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UpdateAll( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsSubscribed( 
            /* [in] */ LPCWSTR pwszURL,
            /* [out] */ BOOL __RPC_FAR *pfSubscribed) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSubscriptionInfo( 
            /* [in] */ LPCWSTR pwszURL,
            /* [out] */ SUBSCRIPTIONINFO __RPC_FAR *pInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDefaultInfo( 
            /* [in] */ SUBSCRIPTIONTYPE subType,
            /* [out] */ SUBSCRIPTIONINFO __RPC_FAR *pInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ShowSubscriptionProperties( 
            /* [in] */ LPCWSTR pwszURL,
            /* [in] */ HWND hwnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateSubscription( 
            /* [in] */ HWND hwnd,
            /* [in] */ LPCWSTR pwszURL,
            /* [in] */ LPCWSTR pwszFriendlyName,
            /* [in] */ DWORD dwFlags,
            /* [in] */ SUBSCRIPTIONTYPE subsType,
            /* [out][in] */ SUBSCRIPTIONINFO __RPC_FAR *pInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISubscriptionMgrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISubscriptionMgr __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISubscriptionMgr __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISubscriptionMgr __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteSubscription )( 
            ISubscriptionMgr __RPC_FAR * This,
            /* [in] */ LPCWSTR pwszURL,
            /* [in] */ HWND hwnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UpdateSubscription )( 
            ISubscriptionMgr __RPC_FAR * This,
            /* [in] */ LPCWSTR pwszURL);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UpdateAll )( 
            ISubscriptionMgr __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsSubscribed )( 
            ISubscriptionMgr __RPC_FAR * This,
            /* [in] */ LPCWSTR pwszURL,
            /* [out] */ BOOL __RPC_FAR *pfSubscribed);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSubscriptionInfo )( 
            ISubscriptionMgr __RPC_FAR * This,
            /* [in] */ LPCWSTR pwszURL,
            /* [out] */ SUBSCRIPTIONINFO __RPC_FAR *pInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDefaultInfo )( 
            ISubscriptionMgr __RPC_FAR * This,
            /* [in] */ SUBSCRIPTIONTYPE subType,
            /* [out] */ SUBSCRIPTIONINFO __RPC_FAR *pInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowSubscriptionProperties )( 
            ISubscriptionMgr __RPC_FAR * This,
            /* [in] */ LPCWSTR pwszURL,
            /* [in] */ HWND hwnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateSubscription )( 
            ISubscriptionMgr __RPC_FAR * This,
            /* [in] */ HWND hwnd,
            /* [in] */ LPCWSTR pwszURL,
            /* [in] */ LPCWSTR pwszFriendlyName,
            /* [in] */ DWORD dwFlags,
            /* [in] */ SUBSCRIPTIONTYPE subsType,
            /* [out][in] */ SUBSCRIPTIONINFO __RPC_FAR *pInfo);
        
        END_INTERFACE
    } ISubscriptionMgrVtbl;

    interface ISubscriptionMgr
    {
        CONST_VTBL struct ISubscriptionMgrVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISubscriptionMgr_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISubscriptionMgr_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISubscriptionMgr_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISubscriptionMgr_DeleteSubscription(This,pwszURL,hwnd)	\
    (This)->lpVtbl -> DeleteSubscription(This,pwszURL,hwnd)

#define ISubscriptionMgr_UpdateSubscription(This,pwszURL)	\
    (This)->lpVtbl -> UpdateSubscription(This,pwszURL)

#define ISubscriptionMgr_UpdateAll(This)	\
    (This)->lpVtbl -> UpdateAll(This)

#define ISubscriptionMgr_IsSubscribed(This,pwszURL,pfSubscribed)	\
    (This)->lpVtbl -> IsSubscribed(This,pwszURL,pfSubscribed)

#define ISubscriptionMgr_GetSubscriptionInfo(This,pwszURL,pInfo)	\
    (This)->lpVtbl -> GetSubscriptionInfo(This,pwszURL,pInfo)

#define ISubscriptionMgr_GetDefaultInfo(This,subType,pInfo)	\
    (This)->lpVtbl -> GetDefaultInfo(This,subType,pInfo)

#define ISubscriptionMgr_ShowSubscriptionProperties(This,pwszURL,hwnd)	\
    (This)->lpVtbl -> ShowSubscriptionProperties(This,pwszURL,hwnd)

#define ISubscriptionMgr_CreateSubscription(This,hwnd,pwszURL,pwszFriendlyName,dwFlags,subsType,pInfo)	\
    (This)->lpVtbl -> CreateSubscription(This,hwnd,pwszURL,pwszFriendlyName,dwFlags,subsType,pInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ISubscriptionMgr_DeleteSubscription_Proxy( 
    ISubscriptionMgr __RPC_FAR * This,
    /* [in] */ LPCWSTR pwszURL,
    /* [in] */ HWND hwnd);


void __RPC_STUB ISubscriptionMgr_DeleteSubscription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISubscriptionMgr_UpdateSubscription_Proxy( 
    ISubscriptionMgr __RPC_FAR * This,
    /* [in] */ LPCWSTR pwszURL);


void __RPC_STUB ISubscriptionMgr_UpdateSubscription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISubscriptionMgr_UpdateAll_Proxy( 
    ISubscriptionMgr __RPC_FAR * This);


void __RPC_STUB ISubscriptionMgr_UpdateAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISubscriptionMgr_IsSubscribed_Proxy( 
    ISubscriptionMgr __RPC_FAR * This,
    /* [in] */ LPCWSTR pwszURL,
    /* [out] */ BOOL __RPC_FAR *pfSubscribed);


void __RPC_STUB ISubscriptionMgr_IsSubscribed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISubscriptionMgr_GetSubscriptionInfo_Proxy( 
    ISubscriptionMgr __RPC_FAR * This,
    /* [in] */ LPCWSTR pwszURL,
    /* [out] */ SUBSCRIPTIONINFO __RPC_FAR *pInfo);


void __RPC_STUB ISubscriptionMgr_GetSubscriptionInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISubscriptionMgr_GetDefaultInfo_Proxy( 
    ISubscriptionMgr __RPC_FAR * This,
    /* [in] */ SUBSCRIPTIONTYPE subType,
    /* [out] */ SUBSCRIPTIONINFO __RPC_FAR *pInfo);


void __RPC_STUB ISubscriptionMgr_GetDefaultInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISubscriptionMgr_ShowSubscriptionProperties_Proxy( 
    ISubscriptionMgr __RPC_FAR * This,
    /* [in] */ LPCWSTR pwszURL,
    /* [in] */ HWND hwnd);


void __RPC_STUB ISubscriptionMgr_ShowSubscriptionProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ISubscriptionMgr_CreateSubscription_Proxy( 
    ISubscriptionMgr __RPC_FAR * This,
    /* [in] */ HWND hwnd,
    /* [in] */ LPCWSTR pwszURL,
    /* [in] */ LPCWSTR pwszFriendlyName,
    /* [in] */ DWORD dwFlags,
    /* [in] */ SUBSCRIPTIONTYPE subsType,
    /* [out][in] */ SUBSCRIPTIONINFO __RPC_FAR *pInfo);


void __RPC_STUB ISubscriptionMgr_CreateSubscription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISubscriptionMgr_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_SubscriptionMgr;

#ifdef __cplusplus

class DECLSPEC_UUID("abbe31d0-6dae-11d0-beca-00c04fd940be")
SubscriptionMgr;
#endif
#endif /* __SubscriptionMgr_LIBRARY_DEFINED__ */

/****************************************
 * Generated header for interface: __MIDL_itf_subsmgr_0073
 * at Mon Nov 17 12:04:08 1997
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 




////////////////////////////////////////////////////////////////////////////
// Information Delivery Agent definitions
EXTERN_C const CLSID CLSID_WebCrawlerAgent;      
EXTERN_C const CLSID CLSID_ChannelAgent;         
EXTERN_C const CLSID CLSID_DialAgent;            
EXTERN_C const CLSID CLSID_CDLAgent;            

// RecurseFlags property for web crawler
typedef 
enum WEBCRAWL_RECURSEFLAGS
    {	WEBCRAWL_DONT_MAKE_STICKY	= 0x1,
	WEBCRAWL_GET_IMAGES	= 0x2,
	WEBCRAWL_GET_VIDEOS	= 0x4,
	WEBCRAWL_GET_BGSOUNDS	= 0x8,
	WEBCRAWL_GET_CONTROLS	= 0x10,
	WEBCRAWL_LINKS_ELSEWHERE	= 0x20,
	WEBCRAWL_IGNORE_ROBOTSTXT	= 0x80
    }	WEBCRAWL_RECURSEFLAGS;


// ChannelFlags property for channel agent
typedef 
enum CHANNEL_AGENT_FLAGS
    {	CHANNEL_AGENT_DYNAMIC_SCHEDULE	= 0x1,
	CHANNEL_AGENT_PRECACHE_SOME	= 0x2,
	CHANNEL_AGENT_PRECACHE_ALL	= 0x4,
	CHANNEL_AGENT_PRECACHE_SCRNSAVER	= 0x8
    }	CHANNEL_AGENT_FLAGS;


// Status codes for completed delivery agents

// Maximum specified subscription size limit reached
#define INET_E_AGENT_MAX_SIZE_EXCEEDED       _HRESULT_TYPEDEF_(0x800C0F80L)      

// Maximum cache limit reached
#define INET_E_AGENT_CACHE_SIZE_EXCEEDED     _HRESULT_TYPEDEF_(0x800C0F82L)      

// Connection to Internet failed
#define INET_E_AGENT_CONNECTION_FAILED       _HRESULT_TYPEDEF_(0x800C0F83L)      

// A few URLs failed but the base url and most sub-urls succeeded
#define INET_S_AGENT_PART_FAIL               _HRESULT_TYPEDEF_(0x000C0F81L)      

// End Information Delivery Agent definitions
////////////////////////////////////////////////////////////////////////////




extern RPC_IF_HANDLE __MIDL_itf_subsmgr_0073_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_subsmgr_0073_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
