/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.02.88 */
/* at Mon Nov 17 12:05:10 1997
 */
/* Compiler settings for chanmgr.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"

#ifndef __chanmgr_h__
#define __chanmgr_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IChannelMgr_FWD_DEFINED__
#define __IChannelMgr_FWD_DEFINED__
typedef interface IChannelMgr IChannelMgr;
#endif 	/* __IChannelMgr_FWD_DEFINED__ */


#ifndef __IEnumChannels_FWD_DEFINED__
#define __IEnumChannels_FWD_DEFINED__
typedef interface IEnumChannels IEnumChannels;
#endif 	/* __IEnumChannels_FWD_DEFINED__ */


#ifndef __ChannelMgr_FWD_DEFINED__
#define __ChannelMgr_FWD_DEFINED__

#ifdef __cplusplus
typedef class ChannelMgr ChannelMgr;
#else
typedef struct ChannelMgr ChannelMgr;
#endif /* __cplusplus */

#endif 	/* __ChannelMgr_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_chanmgr_0000
 * at Mon Nov 17 12:05:10 1997
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


//=--------------------------------------------------------------------------=
// chanmgr.h
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





extern RPC_IF_HANDLE __MIDL_itf_chanmgr_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_chanmgr_0000_v0_0_s_ifspec;


#ifndef __CHANNELMGR_LIBRARY_DEFINED__
#define __CHANNELMGR_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: CHANNELMGR
 * at Mon Nov 17 12:05:10 1997
 * using MIDL 3.02.88
 ****************************************/
/* [version][lcid][helpstring][uuid] */ 



EXTERN_C const IID LIBID_CHANNELMGR;

#ifndef __IChannelMgr_INTERFACE_DEFINED__
#define __IChannelMgr_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IChannelMgr
 * at Mon Nov 17 12:05:10 1997
 * using MIDL 3.02.88
 ****************************************/
/* [object][helpstring][uuid] */ 


typedef struct  _tagChannelShortcutInfo
    {
    DWORD cbSize;
    LPWSTR pszTitle;
    LPWSTR pszURL;
    LPWSTR pszLogo;
    LPWSTR pszIcon;
    LPWSTR pszWideLogo;
    BOOL bIsSoftware;
    }	CHANNELSHORTCUTINFO;

typedef struct  _tagChannelCategoryInfo
    {
    DWORD cbSize;
    LPWSTR pszTitle;
    LPWSTR pszURL;
    LPWSTR pszLogo;
    LPWSTR pszIcon;
    LPWSTR pszWideLogo;
    }	CHANNELCATEGORYINFO;

typedef 
enum _tagChannelEnumFlags
    {	CHANENUM_CHANNELFOLDER	= 0x1,
	CHANENUM_SOFTUPDATEFOLDER	= 0x2,
	CHANENUM_DESKTOPFOLDER	= 0x4,
	CHANENUM_TITLE	= 0x10000,
	CHANENUM_PATH	= 0x20000,
	CHANENUM_URL	= 0x40000,
	CHANENUM_SUBSCRIBESTATE	= 0x80000
    }	CHANNELENUMFLAGS;

#define CHANENUM_ALLFOLDERS (CHANENUM_CHANNELFOLDER    |    \
                             CHANENUM_SOFTUPDATEFOLDER |    \
                             CHANENUM_DESKTOPFOLDER          )

#define CHANENUM_ALLDATA    (CHANENUM_TITLE            |    \
                             CHANENUM_PATH             |    \
                             CHANENUM_URL              |    \
                             CHANENUM_SUBSCRIBESTATE         )

#define CHANENUM_ALL        (CHANENUM_CHANNELFOLDER    |    \
                             CHANENUM_SOFTUPDATEFOLDER |    \
                             CHANENUM_DESKTOPFOLDER    |    \
                             CHANENUM_TITLE            |    \
                             CHANENUM_PATH             |    \
                             CHANENUM_URL              |    \
                             CHANENUM_SUBSCRIBESTATE         )


EXTERN_C const IID IID_IChannelMgr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("85BD8E82-0FBA-11d1-90C3-00C04FC2F568")
    IChannelMgr : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AddChannelShortcut( 
            /* [in] */ CHANNELSHORTCUTINFO __RPC_FAR *pChannelInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteChannelShortcut( 
            /* [in] */ LPWSTR pszTitle) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddCategory( 
            /* [in] */ CHANNELCATEGORYINFO __RPC_FAR *pCategoryInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteCategory( 
            /* [in] */ LPWSTR pszTitle) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumChannels( 
            /* [in] */ DWORD dwEnumFlags,
            /* [in] */ LPCWSTR pszURL,
            /* [out] */ IEnumChannels __RPC_FAR *__RPC_FAR *pIEnumChannels) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IChannelMgrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IChannelMgr __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IChannelMgr __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IChannelMgr __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddChannelShortcut )( 
            IChannelMgr __RPC_FAR * This,
            /* [in] */ CHANNELSHORTCUTINFO __RPC_FAR *pChannelInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteChannelShortcut )( 
            IChannelMgr __RPC_FAR * This,
            /* [in] */ LPWSTR pszTitle);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddCategory )( 
            IChannelMgr __RPC_FAR * This,
            /* [in] */ CHANNELCATEGORYINFO __RPC_FAR *pCategoryInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteCategory )( 
            IChannelMgr __RPC_FAR * This,
            /* [in] */ LPWSTR pszTitle);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumChannels )( 
            IChannelMgr __RPC_FAR * This,
            /* [in] */ DWORD dwEnumFlags,
            /* [in] */ LPCWSTR pszURL,
            /* [out] */ IEnumChannels __RPC_FAR *__RPC_FAR *pIEnumChannels);
        
        END_INTERFACE
    } IChannelMgrVtbl;

    interface IChannelMgr
    {
        CONST_VTBL struct IChannelMgrVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IChannelMgr_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IChannelMgr_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IChannelMgr_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IChannelMgr_AddChannelShortcut(This,pChannelInfo)	\
    (This)->lpVtbl -> AddChannelShortcut(This,pChannelInfo)

#define IChannelMgr_DeleteChannelShortcut(This,pszTitle)	\
    (This)->lpVtbl -> DeleteChannelShortcut(This,pszTitle)

#define IChannelMgr_AddCategory(This,pCategoryInfo)	\
    (This)->lpVtbl -> AddCategory(This,pCategoryInfo)

#define IChannelMgr_DeleteCategory(This,pszTitle)	\
    (This)->lpVtbl -> DeleteCategory(This,pszTitle)

#define IChannelMgr_EnumChannels(This,dwEnumFlags,pszURL,pIEnumChannels)	\
    (This)->lpVtbl -> EnumChannels(This,dwEnumFlags,pszURL,pIEnumChannels)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IChannelMgr_AddChannelShortcut_Proxy( 
    IChannelMgr __RPC_FAR * This,
    /* [in] */ CHANNELSHORTCUTINFO __RPC_FAR *pChannelInfo);


void __RPC_STUB IChannelMgr_AddChannelShortcut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IChannelMgr_DeleteChannelShortcut_Proxy( 
    IChannelMgr __RPC_FAR * This,
    /* [in] */ LPWSTR pszTitle);


void __RPC_STUB IChannelMgr_DeleteChannelShortcut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IChannelMgr_AddCategory_Proxy( 
    IChannelMgr __RPC_FAR * This,
    /* [in] */ CHANNELCATEGORYINFO __RPC_FAR *pCategoryInfo);


void __RPC_STUB IChannelMgr_AddCategory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IChannelMgr_DeleteCategory_Proxy( 
    IChannelMgr __RPC_FAR * This,
    /* [in] */ LPWSTR pszTitle);


void __RPC_STUB IChannelMgr_DeleteCategory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IChannelMgr_EnumChannels_Proxy( 
    IChannelMgr __RPC_FAR * This,
    /* [in] */ DWORD dwEnumFlags,
    /* [in] */ LPCWSTR pszURL,
    /* [out] */ IEnumChannels __RPC_FAR *__RPC_FAR *pIEnumChannels);


void __RPC_STUB IChannelMgr_EnumChannels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IChannelMgr_INTERFACE_DEFINED__ */


#ifndef __IEnumChannels_INTERFACE_DEFINED__
#define __IEnumChannels_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IEnumChannels
 * at Mon Nov 17 12:05:10 1997
 * using MIDL 3.02.88
 ****************************************/
/* [object][helpstring][uuid] */ 


typedef 
enum _tagSubcriptionState
    {	SUBSTATE_NOTSUBSCRIBED	= 0,
	SUBSTATE_PARTIALSUBSCRIPTION	= SUBSTATE_NOTSUBSCRIBED + 1,
	SUBSTATE_FULLSUBSCRIPTION	= SUBSTATE_PARTIALSUBSCRIPTION + 1
    }	SUBSCRIPTIONSTATE;

typedef struct  _tagChannelInfo
    {
    LPOLESTR pszTitle;
    LPOLESTR pszPath;
    LPOLESTR pszURL;
    SUBSCRIPTIONSTATE stSubscriptionState;
    }	CHANNELENUMINFO;


EXTERN_C const IID IID_IEnumChannels;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("A4C65425-0F82-11d1-90C3-00C04FC2F568")
    IEnumChannels : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            ULONG celt,
            CHANNELENUMINFO __RPC_FAR *rgChanInf,
            ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            IEnumChannels __RPC_FAR *__RPC_FAR *ppenum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumChannelsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumChannels __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumChannels __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumChannels __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumChannels __RPC_FAR * This,
            ULONG celt,
            CHANNELENUMINFO __RPC_FAR *rgChanInf,
            ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumChannels __RPC_FAR * This,
            ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumChannels __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumChannels __RPC_FAR * This,
            IEnumChannels __RPC_FAR *__RPC_FAR *ppenum);
        
        END_INTERFACE
    } IEnumChannelsVtbl;

    interface IEnumChannels
    {
        CONST_VTBL struct IEnumChannelsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumChannels_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumChannels_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumChannels_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumChannels_Next(This,celt,rgChanInf,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,rgChanInf,pceltFetched)

#define IEnumChannels_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumChannels_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumChannels_Clone(This,ppenum)	\
    (This)->lpVtbl -> Clone(This,ppenum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumChannels_Next_Proxy( 
    IEnumChannels __RPC_FAR * This,
    ULONG celt,
    CHANNELENUMINFO __RPC_FAR *rgChanInf,
    ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IEnumChannels_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumChannels_Skip_Proxy( 
    IEnumChannels __RPC_FAR * This,
    ULONG celt);


void __RPC_STUB IEnumChannels_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumChannels_Reset_Proxy( 
    IEnumChannels __RPC_FAR * This);


void __RPC_STUB IEnumChannels_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumChannels_Clone_Proxy( 
    IEnumChannels __RPC_FAR * This,
    IEnumChannels __RPC_FAR *__RPC_FAR *ppenum);


void __RPC_STUB IEnumChannels_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumChannels_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ChannelMgr;

#ifdef __cplusplus

class DECLSPEC_UUID("b3cdae90-d170-11d0-802b-00c04fd75d13")
ChannelMgr;
#endif
#endif /* __CHANNELMGR_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
