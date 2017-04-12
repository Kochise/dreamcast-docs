/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Thu Sep 11 10:59:06 1997
 */
/* Compiler settings for urlhist.idl:
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

#ifndef __urlhist_h__
#define __urlhist_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEnumSTATURL_FWD_DEFINED__
#define __IEnumSTATURL_FWD_DEFINED__
typedef interface IEnumSTATURL IEnumSTATURL;
#endif 	/* __IEnumSTATURL_FWD_DEFINED__ */


#ifndef __IUrlHistoryStg_FWD_DEFINED__
#define __IUrlHistoryStg_FWD_DEFINED__
typedef interface IUrlHistoryStg IUrlHistoryStg;
#endif 	/* __IUrlHistoryStg_FWD_DEFINED__ */


#ifndef __IUrlHistoryStg2_FWD_DEFINED__
#define __IUrlHistoryStg2_FWD_DEFINED__
typedef interface IUrlHistoryStg2 IUrlHistoryStg2;
#endif 	/* __IUrlHistoryStg2_FWD_DEFINED__ */


#ifndef __IUrlHistoryNotify_FWD_DEFINED__
#define __IUrlHistoryNotify_FWD_DEFINED__
typedef interface IUrlHistoryNotify IUrlHistoryNotify;
#endif 	/* __IUrlHistoryNotify_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"
#include "oleidl.h"
#include "oaidl.h"
#include "docobj.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_urlhist_0000
 * at Thu Sep 11 10:59:06 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


//=--------------------------------------------------------------------------=
// UrlHist.h
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
// Url History Interfaces.



#define STATURL_QUERYFLAG_ISCACHED		0x00010000
#define STATURL_QUERYFLAG_NOURL              0x00020000
#define STATURL_QUERYFLAG_NOTITLE            0x00040000
#define STATURLFLAG_ISCACHED		0x00000001

////////////////////////////////////////////////////////////////////////////
//  Interface Definitions
#ifndef _LPENUMSTATURL_DEFINED
#define _LPENUMSTATURL_DEFINED


extern RPC_IF_HANDLE __MIDL_itf_urlhist_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_urlhist_0000_v0_0_s_ifspec;

#ifndef __IEnumSTATURL_INTERFACE_DEFINED__
#define __IEnumSTATURL_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IEnumSTATURL
 * at Thu Sep 11 10:59:06 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][uuid][object] */ 


typedef /* [unique] */ IEnumSTATURL __RPC_FAR *LPENUMSTATURL;

typedef struct  _STATURL
    {
    DWORD cbSize;
    LPWSTR pwcsUrl;
    LPWSTR pwcsTitle;
    FILETIME ftLastVisited;
    FILETIME ftLastUpdated;
    FILETIME ftExpires;
    DWORD dwFlags;
    }	STATURL;

typedef struct _STATURL __RPC_FAR *LPSTATURL;


EXTERN_C const IID IID_IEnumSTATURL;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3C374A42-BAE4-11CF-BF7D-00AA006946EE")
    IEnumSTATURL : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out][in] */ LPSTATURL rgelt,
            /* [out][in] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumSTATURL __RPC_FAR *__RPC_FAR *ppenum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFilter( 
            /* [in] */ LPCOLESTR poszFilter,
            /* [in] */ DWORD dwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumSTATURLVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumSTATURL __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumSTATURL __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumSTATURL __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumSTATURL __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [out][in] */ LPSTATURL rgelt,
            /* [out][in] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumSTATURL __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumSTATURL __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumSTATURL __RPC_FAR * This,
            /* [out] */ IEnumSTATURL __RPC_FAR *__RPC_FAR *ppenum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFilter )( 
            IEnumSTATURL __RPC_FAR * This,
            /* [in] */ LPCOLESTR poszFilter,
            /* [in] */ DWORD dwFlags);
        
        END_INTERFACE
    } IEnumSTATURLVtbl;

    interface IEnumSTATURL
    {
        CONST_VTBL struct IEnumSTATURLVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumSTATURL_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumSTATURL_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumSTATURL_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumSTATURL_Next(This,celt,rgelt,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched)

#define IEnumSTATURL_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumSTATURL_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumSTATURL_Clone(This,ppenum)	\
    (This)->lpVtbl -> Clone(This,ppenum)

#define IEnumSTATURL_SetFilter(This,poszFilter,dwFlags)	\
    (This)->lpVtbl -> SetFilter(This,poszFilter,dwFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumSTATURL_Next_Proxy( 
    IEnumSTATURL __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [out][in] */ LPSTATURL rgelt,
    /* [out][in] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IEnumSTATURL_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumSTATURL_Skip_Proxy( 
    IEnumSTATURL __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumSTATURL_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumSTATURL_Reset_Proxy( 
    IEnumSTATURL __RPC_FAR * This);


void __RPC_STUB IEnumSTATURL_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumSTATURL_Clone_Proxy( 
    IEnumSTATURL __RPC_FAR * This,
    /* [out] */ IEnumSTATURL __RPC_FAR *__RPC_FAR *ppenum);


void __RPC_STUB IEnumSTATURL_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumSTATURL_SetFilter_Proxy( 
    IEnumSTATURL __RPC_FAR * This,
    /* [in] */ LPCOLESTR poszFilter,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IEnumSTATURL_SetFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumSTATURL_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_urlhist_0226
 * at Thu Sep 11 10:59:06 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


#endif
#ifndef _LPURLHISTORYSTG_DEFINED
#define _LPURLHISTORYSTG_DEFINED


extern RPC_IF_HANDLE __MIDL_itf_urlhist_0226_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_urlhist_0226_v0_0_s_ifspec;

#ifndef __IUrlHistoryStg_INTERFACE_DEFINED__
#define __IUrlHistoryStg_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IUrlHistoryStg
 * at Thu Sep 11 10:59:06 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][uuid][object] */ 


typedef /* [unique] */ IUrlHistoryStg __RPC_FAR *LPURLHISTORYSTG;


EXTERN_C const IID IID_IUrlHistoryStg;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3C374A41-BAE4-11CF-BF7D-00AA006946EE")
    IUrlHistoryStg : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AddUrl( 
            /* [in] */ LPCOLESTR pocsUrl,
            /* [unique][in] */ LPCOLESTR pocsTitle,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteUrl( 
            /* [in] */ LPCOLESTR pocsUrl,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE QueryUrl( 
            /* [in] */ LPCOLESTR pocsUrl,
            /* [in] */ DWORD dwFlags,
            /* [unique][out][in] */ LPSTATURL lpSTATURL) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BindToObject( 
            /* [in] */ LPCOLESTR pocsUrl,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvOut) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumUrls( 
            /* [out] */ IEnumSTATURL __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUrlHistoryStgVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IUrlHistoryStg __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IUrlHistoryStg __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IUrlHistoryStg __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddUrl )( 
            IUrlHistoryStg __RPC_FAR * This,
            /* [in] */ LPCOLESTR pocsUrl,
            /* [unique][in] */ LPCOLESTR pocsTitle,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteUrl )( 
            IUrlHistoryStg __RPC_FAR * This,
            /* [in] */ LPCOLESTR pocsUrl,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryUrl )( 
            IUrlHistoryStg __RPC_FAR * This,
            /* [in] */ LPCOLESTR pocsUrl,
            /* [in] */ DWORD dwFlags,
            /* [unique][out][in] */ LPSTATURL lpSTATURL);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BindToObject )( 
            IUrlHistoryStg __RPC_FAR * This,
            /* [in] */ LPCOLESTR pocsUrl,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvOut);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumUrls )( 
            IUrlHistoryStg __RPC_FAR * This,
            /* [out] */ IEnumSTATURL __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IUrlHistoryStgVtbl;

    interface IUrlHistoryStg
    {
        CONST_VTBL struct IUrlHistoryStgVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUrlHistoryStg_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUrlHistoryStg_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUrlHistoryStg_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUrlHistoryStg_AddUrl(This,pocsUrl,pocsTitle,dwFlags)	\
    (This)->lpVtbl -> AddUrl(This,pocsUrl,pocsTitle,dwFlags)

#define IUrlHistoryStg_DeleteUrl(This,pocsUrl,dwFlags)	\
    (This)->lpVtbl -> DeleteUrl(This,pocsUrl,dwFlags)

#define IUrlHistoryStg_QueryUrl(This,pocsUrl,dwFlags,lpSTATURL)	\
    (This)->lpVtbl -> QueryUrl(This,pocsUrl,dwFlags,lpSTATURL)

#define IUrlHistoryStg_BindToObject(This,pocsUrl,riid,ppvOut)	\
    (This)->lpVtbl -> BindToObject(This,pocsUrl,riid,ppvOut)

#define IUrlHistoryStg_EnumUrls(This,ppEnum)	\
    (This)->lpVtbl -> EnumUrls(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IUrlHistoryStg_AddUrl_Proxy( 
    IUrlHistoryStg __RPC_FAR * This,
    /* [in] */ LPCOLESTR pocsUrl,
    /* [unique][in] */ LPCOLESTR pocsTitle,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IUrlHistoryStg_AddUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IUrlHistoryStg_DeleteUrl_Proxy( 
    IUrlHistoryStg __RPC_FAR * This,
    /* [in] */ LPCOLESTR pocsUrl,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IUrlHistoryStg_DeleteUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IUrlHistoryStg_QueryUrl_Proxy( 
    IUrlHistoryStg __RPC_FAR * This,
    /* [in] */ LPCOLESTR pocsUrl,
    /* [in] */ DWORD dwFlags,
    /* [unique][out][in] */ LPSTATURL lpSTATURL);


void __RPC_STUB IUrlHistoryStg_QueryUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IUrlHistoryStg_BindToObject_Proxy( 
    IUrlHistoryStg __RPC_FAR * This,
    /* [in] */ LPCOLESTR pocsUrl,
    /* [in] */ REFIID riid,
    /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvOut);


void __RPC_STUB IUrlHistoryStg_BindToObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IUrlHistoryStg_EnumUrls_Proxy( 
    IUrlHistoryStg __RPC_FAR * This,
    /* [out] */ IEnumSTATURL __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IUrlHistoryStg_EnumUrls_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUrlHistoryStg_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_urlhist_0227
 * at Thu Sep 11 10:59:06 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


#endif
#ifndef _LPURLHISTORYSTG2_DEFINED
#define _LPURLHISTORYSTG2_DEFINED


extern RPC_IF_HANDLE __MIDL_itf_urlhist_0227_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_urlhist_0227_v0_0_s_ifspec;

#ifndef __IUrlHistoryStg2_INTERFACE_DEFINED__
#define __IUrlHistoryStg2_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IUrlHistoryStg2
 * at Thu Sep 11 10:59:06 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][uuid][object] */ 


typedef /* [unique] */ IUrlHistoryStg2 __RPC_FAR *LPURLHISTORYSTG2;


EXTERN_C const IID IID_IUrlHistoryStg2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AFA0DC11-C313-11d0-831A-00C04FD5AE38")
    IUrlHistoryStg2 : public IUrlHistoryStg
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AddUrlAndNotify( 
            /* [in] */ LPCOLESTR pocsUrl,
            /* [unique][in] */ LPCOLESTR pocsTitle,
            /* [in] */ DWORD dwFlags,
            /* [in] */ BOOL fWriteHistory,
            /* [in] */ IOleCommandTarget __RPC_FAR *poctNotify,
            /* [unique][in] */ IUnknown __RPC_FAR *punkISFolder) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ClearHistory( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUrlHistoryStg2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IUrlHistoryStg2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IUrlHistoryStg2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IUrlHistoryStg2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddUrl )( 
            IUrlHistoryStg2 __RPC_FAR * This,
            /* [in] */ LPCOLESTR pocsUrl,
            /* [unique][in] */ LPCOLESTR pocsTitle,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteUrl )( 
            IUrlHistoryStg2 __RPC_FAR * This,
            /* [in] */ LPCOLESTR pocsUrl,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryUrl )( 
            IUrlHistoryStg2 __RPC_FAR * This,
            /* [in] */ LPCOLESTR pocsUrl,
            /* [in] */ DWORD dwFlags,
            /* [unique][out][in] */ LPSTATURL lpSTATURL);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BindToObject )( 
            IUrlHistoryStg2 __RPC_FAR * This,
            /* [in] */ LPCOLESTR pocsUrl,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvOut);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumUrls )( 
            IUrlHistoryStg2 __RPC_FAR * This,
            /* [out] */ IEnumSTATURL __RPC_FAR *__RPC_FAR *ppEnum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddUrlAndNotify )( 
            IUrlHistoryStg2 __RPC_FAR * This,
            /* [in] */ LPCOLESTR pocsUrl,
            /* [unique][in] */ LPCOLESTR pocsTitle,
            /* [in] */ DWORD dwFlags,
            /* [in] */ BOOL fWriteHistory,
            /* [in] */ IOleCommandTarget __RPC_FAR *poctNotify,
            /* [unique][in] */ IUnknown __RPC_FAR *punkISFolder);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearHistory )( 
            IUrlHistoryStg2 __RPC_FAR * This);
        
        END_INTERFACE
    } IUrlHistoryStg2Vtbl;

    interface IUrlHistoryStg2
    {
        CONST_VTBL struct IUrlHistoryStg2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUrlHistoryStg2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUrlHistoryStg2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUrlHistoryStg2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUrlHistoryStg2_AddUrl(This,pocsUrl,pocsTitle,dwFlags)	\
    (This)->lpVtbl -> AddUrl(This,pocsUrl,pocsTitle,dwFlags)

#define IUrlHistoryStg2_DeleteUrl(This,pocsUrl,dwFlags)	\
    (This)->lpVtbl -> DeleteUrl(This,pocsUrl,dwFlags)

#define IUrlHistoryStg2_QueryUrl(This,pocsUrl,dwFlags,lpSTATURL)	\
    (This)->lpVtbl -> QueryUrl(This,pocsUrl,dwFlags,lpSTATURL)

#define IUrlHistoryStg2_BindToObject(This,pocsUrl,riid,ppvOut)	\
    (This)->lpVtbl -> BindToObject(This,pocsUrl,riid,ppvOut)

#define IUrlHistoryStg2_EnumUrls(This,ppEnum)	\
    (This)->lpVtbl -> EnumUrls(This,ppEnum)


#define IUrlHistoryStg2_AddUrlAndNotify(This,pocsUrl,pocsTitle,dwFlags,fWriteHistory,poctNotify,punkISFolder)	\
    (This)->lpVtbl -> AddUrlAndNotify(This,pocsUrl,pocsTitle,dwFlags,fWriteHistory,poctNotify,punkISFolder)

#define IUrlHistoryStg2_ClearHistory(This)	\
    (This)->lpVtbl -> ClearHistory(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IUrlHistoryStg2_AddUrlAndNotify_Proxy( 
    IUrlHistoryStg2 __RPC_FAR * This,
    /* [in] */ LPCOLESTR pocsUrl,
    /* [unique][in] */ LPCOLESTR pocsTitle,
    /* [in] */ DWORD dwFlags,
    /* [in] */ BOOL fWriteHistory,
    /* [in] */ IOleCommandTarget __RPC_FAR *poctNotify,
    /* [unique][in] */ IUnknown __RPC_FAR *punkISFolder);


void __RPC_STUB IUrlHistoryStg2_AddUrlAndNotify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IUrlHistoryStg2_ClearHistory_Proxy( 
    IUrlHistoryStg2 __RPC_FAR * This);


void __RPC_STUB IUrlHistoryStg2_ClearHistory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUrlHistoryStg2_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_urlhist_0228
 * at Thu Sep 11 10:59:06 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


#endif
#ifndef _LPURLHISTORYNOTIFY_DEFINED
#define _LPURLHISTORYNOTIFY_DEFINED


extern RPC_IF_HANDLE __MIDL_itf_urlhist_0228_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_urlhist_0228_v0_0_s_ifspec;

#ifndef __IUrlHistoryNotify_INTERFACE_DEFINED__
#define __IUrlHistoryNotify_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IUrlHistoryNotify
 * at Thu Sep 11 10:59:06 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][uuid][object] */ 


typedef /* [unique] */ IUrlHistoryNotify __RPC_FAR *LPURLHISTORYNOTIFY;


EXTERN_C const IID IID_IUrlHistoryNotify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BC40BEC1-C493-11d0-831B-00C04FD5AE38")
    IUrlHistoryNotify : public IOleCommandTarget
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IUrlHistoryNotifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IUrlHistoryNotify __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IUrlHistoryNotify __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IUrlHistoryNotify __RPC_FAR * This);
        
        /* [input_sync] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryStatus )( 
            IUrlHistoryNotify __RPC_FAR * This,
            /* [unique][in] */ const GUID __RPC_FAR *pguidCmdGroup,
            /* [in] */ ULONG cCmds,
            /* [out][in][size_is] */ OLECMD __RPC_FAR prgCmds[  ],
            /* [unique][out][in] */ OLECMDTEXT __RPC_FAR *pCmdText);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Exec )( 
            IUrlHistoryNotify __RPC_FAR * This,
            /* [unique][in] */ const GUID __RPC_FAR *pguidCmdGroup,
            /* [in] */ DWORD nCmdID,
            /* [in] */ DWORD nCmdexecopt,
            /* [unique][in] */ VARIANT __RPC_FAR *pvaIn,
            /* [unique][out][in] */ VARIANT __RPC_FAR *pvaOut);
        
        END_INTERFACE
    } IUrlHistoryNotifyVtbl;

    interface IUrlHistoryNotify
    {
        CONST_VTBL struct IUrlHistoryNotifyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUrlHistoryNotify_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUrlHistoryNotify_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUrlHistoryNotify_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUrlHistoryNotify_QueryStatus(This,pguidCmdGroup,cCmds,prgCmds,pCmdText)	\
    (This)->lpVtbl -> QueryStatus(This,pguidCmdGroup,cCmds,prgCmds,pCmdText)

#define IUrlHistoryNotify_Exec(This,pguidCmdGroup,nCmdID,nCmdexecopt,pvaIn,pvaOut)	\
    (This)->lpVtbl -> Exec(This,pguidCmdGroup,nCmdID,nCmdexecopt,pvaIn,pvaOut)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IUrlHistoryNotify_INTERFACE_DEFINED__ */


/****************************************
 * Generated header for interface: __MIDL_itf_urlhist_0229
 * at Thu Sep 11 10:59:06 1997
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


#endif


extern RPC_IF_HANDLE __MIDL_itf_urlhist_0229_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_urlhist_0229_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
