/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.02.88 */
/* at Wed Jan 13 10:52:24 1999
 */
/* Compiler settings for .\sip.idl:
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

#ifndef __sip_h__
#define __sip_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IIMCallback_FWD_DEFINED__
#define __IIMCallback_FWD_DEFINED__
typedef interface IIMCallback IIMCallback;
#endif 	/* __IIMCallback_FWD_DEFINED__ */


#ifndef __IIMCallback2_FWD_DEFINED__
#define __IIMCallback2_FWD_DEFINED__
typedef interface IIMCallback2 IIMCallback2;
#endif 	/* __IIMCallback2_FWD_DEFINED__ */


#ifndef __IIMCallbackEx_FWD_DEFINED__
#define __IIMCallbackEx_FWD_DEFINED__
typedef interface IIMCallbackEx IIMCallbackEx;
#endif 	/* __IIMCallbackEx_FWD_DEFINED__ */


#ifndef __IInputMethod_FWD_DEFINED__
#define __IInputMethod_FWD_DEFINED__
typedef interface IInputMethod IInputMethod;
#endif 	/* __IInputMethod_FWD_DEFINED__ */


#ifndef __IInputMethodEx_FWD_DEFINED__
#define __IInputMethodEx_FWD_DEFINED__
typedef interface IInputMethodEx IInputMethodEx;
#endif 	/* __IInputMethodEx_FWD_DEFINED__ */


#ifndef __IInputMethod2_FWD_DEFINED__
#define __IInputMethod2_FWD_DEFINED__
typedef interface IInputMethod2 IInputMethod2;
#endif 	/* __IInputMethod2_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "sipapi.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_sip_0000
 * at Wed Jan 13 10:52:24 1999
 * using MIDL 3.02.88
 ****************************************/
/* [local] */ 


typedef struct  _tagImInfo
    {
    DWORD cbSize;
    HANDLE hImageNarrow;
    HANDLE hImageWide;
    int iNarrow;
    int iWide;
    DWORD fdwFlags;
    RECT rcSipRect;
    }	IMINFO;

typedef struct  _tagLMDATA
    {
    DWORD dwVersion;
    DWORD flags;
    DWORD cnt;
    DWORD dwOffsetSymbols;
    DWORD dwOffsetSkip;
    DWORD dwOffsetScore;
    /* [max_is] */ BYTE ab[ 1 ];
    }	LMDATA;



extern RPC_IF_HANDLE __MIDL_itf_sip_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_sip_0000_v0_0_s_ifspec;

#ifndef __IIMCallback_INTERFACE_DEFINED__
#define __IIMCallback_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IIMCallback
 * at Wed Jan 13 10:52:24 1999
 * using MIDL 3.02.88
 ****************************************/
/* [uuid][object] */ 



EXTERN_C const IID IID_IIMCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("42429669-ae04-11d0-a4f8-00aa00a749b9")
    IIMCallback : public IUnknown
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetImInfo( 
            IMINFO __RPC_FAR *pimi) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SendVirtualKey( 
            BYTE bVK,
            DWORD dwFlags) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SendCharEvents( 
            UINT uVK,
            UINT uKeyFlags,
            UINT uChars,
            UINT __RPC_FAR *puShift,
            UINT __RPC_FAR *puChars) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SendString( 
            BSTR ptszStr,
            DWORD dwChars) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IIMCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IIMCallback __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IIMCallback __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IIMCallback __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetImInfo )( 
            IIMCallback __RPC_FAR * This,
            IMINFO __RPC_FAR *pimi);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendVirtualKey )( 
            IIMCallback __RPC_FAR * This,
            BYTE bVK,
            DWORD dwFlags);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendCharEvents )( 
            IIMCallback __RPC_FAR * This,
            UINT uVK,
            UINT uKeyFlags,
            UINT uChars,
            UINT __RPC_FAR *puShift,
            UINT __RPC_FAR *puChars);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendString )( 
            IIMCallback __RPC_FAR * This,
            BSTR ptszStr,
            DWORD dwChars);
        
        END_INTERFACE
    } IIMCallbackVtbl;

    interface IIMCallback
    {
        CONST_VTBL struct IIMCallbackVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIMCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IIMCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IIMCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IIMCallback_SetImInfo(This,pimi)	\
    (This)->lpVtbl -> SetImInfo(This,pimi)

#define IIMCallback_SendVirtualKey(This,bVK,dwFlags)	\
    (This)->lpVtbl -> SendVirtualKey(This,bVK,dwFlags)

#define IIMCallback_SendCharEvents(This,uVK,uKeyFlags,uChars,puShift,puChars)	\
    (This)->lpVtbl -> SendCharEvents(This,uVK,uKeyFlags,uChars,puShift,puChars)

#define IIMCallback_SendString(This,ptszStr,dwChars)	\
    (This)->lpVtbl -> SendString(This,ptszStr,dwChars)

#endif /* COBJMACROS */


#endif 	/* C style interface */





#endif 	/* __IIMCallback_INTERFACE_DEFINED__ */


#ifndef __IIMCallback2_INTERFACE_DEFINED__
#define __IIMCallback2_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IIMCallback2
 * at Wed Jan 13 10:52:24 1999
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IIMCallback2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0576F2E0-AA6B-11d2-A146-0000F8757270")
    IIMCallback2 : public IIMCallback
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SendAlternatives2( 
            LMDATA __RPC_FAR *plmd) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IIMCallback2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IIMCallback2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IIMCallback2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IIMCallback2 __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetImInfo )( 
            IIMCallback2 __RPC_FAR * This,
            IMINFO __RPC_FAR *pimi);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendVirtualKey )( 
            IIMCallback2 __RPC_FAR * This,
            BYTE bVK,
            DWORD dwFlags);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendCharEvents )( 
            IIMCallback2 __RPC_FAR * This,
            UINT uVK,
            UINT uKeyFlags,
            UINT uChars,
            UINT __RPC_FAR *puShift,
            UINT __RPC_FAR *puChars);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendString )( 
            IIMCallback2 __RPC_FAR * This,
            BSTR ptszStr,
            DWORD dwChars);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendAlternatives2 )( 
            IIMCallback2 __RPC_FAR * This,
            LMDATA __RPC_FAR *plmd);
        
        END_INTERFACE
    } IIMCallback2Vtbl;

    interface IIMCallback2
    {
        CONST_VTBL struct IIMCallback2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIMCallback2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IIMCallback2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IIMCallback2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IIMCallback2_SetImInfo(This,pimi)	\
    (This)->lpVtbl -> SetImInfo(This,pimi)

#define IIMCallback2_SendVirtualKey(This,bVK,dwFlags)	\
    (This)->lpVtbl -> SendVirtualKey(This,bVK,dwFlags)

#define IIMCallback2_SendCharEvents(This,uVK,uKeyFlags,uChars,puShift,puChars)	\
    (This)->lpVtbl -> SendCharEvents(This,uVK,uKeyFlags,uChars,puShift,puChars)

#define IIMCallback2_SendString(This,ptszStr,dwChars)	\
    (This)->lpVtbl -> SendString(This,ptszStr,dwChars)


#define IIMCallback2_SendAlternatives2(This,plmd)	\
    (This)->lpVtbl -> SendAlternatives2(This,plmd)

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IIMCallback2_INTERFACE_DEFINED__ */


#ifndef __IIMCallbackEx_INTERFACE_DEFINED__
#define __IIMCallbackEx_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IIMCallbackEx
 * at Wed Jan 13 10:52:24 1999
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IIMCallbackEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("9DDB3920-3606-11d2-A2EB-0000F8757270")
    IIMCallbackEx : public IIMCallback
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SendAlternatives( 
            LMDATA __RPC_FAR *plmd) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IIMCallbackExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IIMCallbackEx __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IIMCallbackEx __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IIMCallbackEx __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetImInfo )( 
            IIMCallbackEx __RPC_FAR * This,
            IMINFO __RPC_FAR *pimi);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendVirtualKey )( 
            IIMCallbackEx __RPC_FAR * This,
            BYTE bVK,
            DWORD dwFlags);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendCharEvents )( 
            IIMCallbackEx __RPC_FAR * This,
            UINT uVK,
            UINT uKeyFlags,
            UINT uChars,
            UINT __RPC_FAR *puShift,
            UINT __RPC_FAR *puChars);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendString )( 
            IIMCallbackEx __RPC_FAR * This,
            BSTR ptszStr,
            DWORD dwChars);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendAlternatives )( 
            IIMCallbackEx __RPC_FAR * This,
            LMDATA __RPC_FAR *plmd);
        
        END_INTERFACE
    } IIMCallbackExVtbl;

    interface IIMCallbackEx
    {
        CONST_VTBL struct IIMCallbackExVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IIMCallbackEx_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IIMCallbackEx_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IIMCallbackEx_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IIMCallbackEx_SetImInfo(This,pimi)	\
    (This)->lpVtbl -> SetImInfo(This,pimi)

#define IIMCallbackEx_SendVirtualKey(This,bVK,dwFlags)	\
    (This)->lpVtbl -> SendVirtualKey(This,bVK,dwFlags)

#define IIMCallbackEx_SendCharEvents(This,uVK,uKeyFlags,uChars,puShift,puChars)	\
    (This)->lpVtbl -> SendCharEvents(This,uVK,uKeyFlags,uChars,puShift,puChars)

#define IIMCallbackEx_SendString(This,ptszStr,dwChars)	\
    (This)->lpVtbl -> SendString(This,ptszStr,dwChars)


#define IIMCallbackEx_SendAlternatives(This,plmd)	\
    (This)->lpVtbl -> SendAlternatives(This,plmd)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IIMCallbackEx_INTERFACE_DEFINED__ */


#ifndef __IInputMethod_INTERFACE_DEFINED__
#define __IInputMethod_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IInputMethod
 * at Wed Jan 13 10:52:24 1999
 * using MIDL 3.02.88
 ****************************************/
/* [uuid][object] */ 



EXTERN_C const IID IID_IInputMethod;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("42429666-ae04-11d0-a4f8-00aa00a749b9")
    IInputMethod : public IUnknown
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Select( 
            /* [in] */ HWND hwndSip) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Deselect( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Showing( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Hiding( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetInfo( 
            /* [out] */ IMINFO __RPC_FAR *pimi) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ReceiveSipInfo( 
            /* [in] */ SIPINFO __RPC_FAR *psi) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RegisterCallback( 
            /* [in] */ IIMCallback __RPC_FAR *lpIMCallback) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetImData( 
            /* [in] */ DWORD dwSize,
            /* [out] */ void __RPC_FAR *pvImData) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetImData( 
            /* [in] */ DWORD dwSize,
            /* [in] */ void __RPC_FAR *pvImData) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE UserOptionsDlg( 
            /* [in] */ HWND hwndParent) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInputMethodVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInputMethod __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInputMethod __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInputMethod __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Select )( 
            IInputMethod __RPC_FAR * This,
            /* [in] */ HWND hwndSip);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Deselect )( 
            IInputMethod __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Showing )( 
            IInputMethod __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Hiding )( 
            IInputMethod __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IInputMethod __RPC_FAR * This,
            /* [out] */ IMINFO __RPC_FAR *pimi);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReceiveSipInfo )( 
            IInputMethod __RPC_FAR * This,
            /* [in] */ SIPINFO __RPC_FAR *psi);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterCallback )( 
            IInputMethod __RPC_FAR * This,
            /* [in] */ IIMCallback __RPC_FAR *lpIMCallback);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetImData )( 
            IInputMethod __RPC_FAR * This,
            /* [in] */ DWORD dwSize,
            /* [out] */ void __RPC_FAR *pvImData);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetImData )( 
            IInputMethod __RPC_FAR * This,
            /* [in] */ DWORD dwSize,
            /* [in] */ void __RPC_FAR *pvImData);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UserOptionsDlg )( 
            IInputMethod __RPC_FAR * This,
            /* [in] */ HWND hwndParent);
        
        END_INTERFACE
    } IInputMethodVtbl;

    interface IInputMethod
    {
        CONST_VTBL struct IInputMethodVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInputMethod_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInputMethod_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInputMethod_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInputMethod_Select(This,hwndSip)	\
    (This)->lpVtbl -> Select(This,hwndSip)

#define IInputMethod_Deselect(This)	\
    (This)->lpVtbl -> Deselect(This)

#define IInputMethod_Showing(This)	\
    (This)->lpVtbl -> Showing(This)

#define IInputMethod_Hiding(This)	\
    (This)->lpVtbl -> Hiding(This)

#define IInputMethod_GetInfo(This,pimi)	\
    (This)->lpVtbl -> GetInfo(This,pimi)

#define IInputMethod_ReceiveSipInfo(This,psi)	\
    (This)->lpVtbl -> ReceiveSipInfo(This,psi)

#define IInputMethod_RegisterCallback(This,lpIMCallback)	\
    (This)->lpVtbl -> RegisterCallback(This,lpIMCallback)

#define IInputMethod_GetImData(This,dwSize,pvImData)	\
    (This)->lpVtbl -> GetImData(This,dwSize,pvImData)

#define IInputMethod_SetImData(This,dwSize,pvImData)	\
    (This)->lpVtbl -> SetImData(This,dwSize,pvImData)

#define IInputMethod_UserOptionsDlg(This,hwndParent)	\
    (This)->lpVtbl -> UserOptionsDlg(This,hwndParent)

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IInputMethod_INTERFACE_DEFINED__ */


#ifndef __IInputMethodEx_INTERFACE_DEFINED__
#define __IInputMethodEx_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IInputMethodEx
 * at Wed Jan 13 10:52:24 1999
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IInputMethodEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("9DDB3921-3606-11d2-A2EB-0000F8757270")
    IInputMethodEx : public IInputMethod
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetIMMActiveContext( 
            /* [in] */ HWND hwnd,
            BOOL bOpen,
            DWORD dwConversion,
            DWORD dwSentence,
            DWORD hkl) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RegisterCallbackEx( 
            /* [in] */ IIMCallbackEx __RPC_FAR *lpIMCallback) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInputMethodExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInputMethodEx __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInputMethodEx __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInputMethodEx __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Select )( 
            IInputMethodEx __RPC_FAR * This,
            /* [in] */ HWND hwndSip);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Deselect )( 
            IInputMethodEx __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Showing )( 
            IInputMethodEx __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Hiding )( 
            IInputMethodEx __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IInputMethodEx __RPC_FAR * This,
            /* [out] */ IMINFO __RPC_FAR *pimi);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReceiveSipInfo )( 
            IInputMethodEx __RPC_FAR * This,
            /* [in] */ SIPINFO __RPC_FAR *psi);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterCallback )( 
            IInputMethodEx __RPC_FAR * This,
            /* [in] */ IIMCallback __RPC_FAR *lpIMCallback);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetImData )( 
            IInputMethodEx __RPC_FAR * This,
            /* [in] */ DWORD dwSize,
            /* [out] */ void __RPC_FAR *pvImData);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetImData )( 
            IInputMethodEx __RPC_FAR * This,
            /* [in] */ DWORD dwSize,
            /* [in] */ void __RPC_FAR *pvImData);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UserOptionsDlg )( 
            IInputMethodEx __RPC_FAR * This,
            /* [in] */ HWND hwndParent);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetIMMActiveContext )( 
            IInputMethodEx __RPC_FAR * This,
            /* [in] */ HWND hwnd,
            BOOL bOpen,
            DWORD dwConversion,
            DWORD dwSentence,
            DWORD hkl);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterCallbackEx )( 
            IInputMethodEx __RPC_FAR * This,
            /* [in] */ IIMCallbackEx __RPC_FAR *lpIMCallback);
        
        END_INTERFACE
    } IInputMethodExVtbl;

    interface IInputMethodEx
    {
        CONST_VTBL struct IInputMethodExVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInputMethodEx_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInputMethodEx_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInputMethodEx_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInputMethodEx_Select(This,hwndSip)	\
    (This)->lpVtbl -> Select(This,hwndSip)

#define IInputMethodEx_Deselect(This)	\
    (This)->lpVtbl -> Deselect(This)

#define IInputMethodEx_Showing(This)	\
    (This)->lpVtbl -> Showing(This)

#define IInputMethodEx_Hiding(This)	\
    (This)->lpVtbl -> Hiding(This)

#define IInputMethodEx_GetInfo(This,pimi)	\
    (This)->lpVtbl -> GetInfo(This,pimi)

#define IInputMethodEx_ReceiveSipInfo(This,psi)	\
    (This)->lpVtbl -> ReceiveSipInfo(This,psi)

#define IInputMethodEx_RegisterCallback(This,lpIMCallback)	\
    (This)->lpVtbl -> RegisterCallback(This,lpIMCallback)

#define IInputMethodEx_GetImData(This,dwSize,pvImData)	\
    (This)->lpVtbl -> GetImData(This,dwSize,pvImData)

#define IInputMethodEx_SetImData(This,dwSize,pvImData)	\
    (This)->lpVtbl -> SetImData(This,dwSize,pvImData)

#define IInputMethodEx_UserOptionsDlg(This,hwndParent)	\
    (This)->lpVtbl -> UserOptionsDlg(This,hwndParent)


#define IInputMethodEx_SetIMMActiveContext(This,hwnd,bOpen,dwConversion,dwSentence,hkl)	\
    (This)->lpVtbl -> SetIMMActiveContext(This,hwnd,bOpen,dwConversion,dwSentence,hkl)

#define IInputMethodEx_RegisterCallbackEx(This,lpIMCallback)	\
    (This)->lpVtbl -> RegisterCallbackEx(This,lpIMCallback)

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IInputMethodEx_INTERFACE_DEFINED__ */


#ifndef __IInputMethod2_INTERFACE_DEFINED__
#define __IInputMethod2_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IInputMethod2
 * at Wed Jan 13 10:52:24 1999
 * using MIDL 3.02.88
 ****************************************/
/* [unique][uuid][object] */ 



EXTERN_C const IID IID_IInputMethod2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0576F2E1-AA6B-11d2-A146-0000F8757270")
    IInputMethod2 : public IInputMethod
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetIMMActiveContext( 
            /* [in] */ HWND hwnd,
            BOOL bOpen,
            DWORD dwConversion,
            DWORD dwSentence,
            DWORD hkl) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE RegisterCallback2( 
            /* [in] */ IIMCallback2 __RPC_FAR *lpIMCallback) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IInputMethod2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IInputMethod2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IInputMethod2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IInputMethod2 __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Select )( 
            IInputMethod2 __RPC_FAR * This,
            /* [in] */ HWND hwndSip);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Deselect )( 
            IInputMethod2 __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Showing )( 
            IInputMethod2 __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Hiding )( 
            IInputMethod2 __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IInputMethod2 __RPC_FAR * This,
            /* [out] */ IMINFO __RPC_FAR *pimi);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReceiveSipInfo )( 
            IInputMethod2 __RPC_FAR * This,
            /* [in] */ SIPINFO __RPC_FAR *psi);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterCallback )( 
            IInputMethod2 __RPC_FAR * This,
            /* [in] */ IIMCallback __RPC_FAR *lpIMCallback);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetImData )( 
            IInputMethod2 __RPC_FAR * This,
            /* [in] */ DWORD dwSize,
            /* [out] */ void __RPC_FAR *pvImData);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetImData )( 
            IInputMethod2 __RPC_FAR * This,
            /* [in] */ DWORD dwSize,
            /* [in] */ void __RPC_FAR *pvImData);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UserOptionsDlg )( 
            IInputMethod2 __RPC_FAR * This,
            /* [in] */ HWND hwndParent);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetIMMActiveContext )( 
            IInputMethod2 __RPC_FAR * This,
            /* [in] */ HWND hwnd,
            BOOL bOpen,
            DWORD dwConversion,
            DWORD dwSentence,
            DWORD hkl);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterCallback2 )( 
            IInputMethod2 __RPC_FAR * This,
            /* [in] */ IIMCallback2 __RPC_FAR *lpIMCallback);
        
        END_INTERFACE
    } IInputMethod2Vtbl;

    interface IInputMethod2
    {
        CONST_VTBL struct IInputMethod2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IInputMethod2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IInputMethod2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IInputMethod2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IInputMethod2_Select(This,hwndSip)	\
    (This)->lpVtbl -> Select(This,hwndSip)

#define IInputMethod2_Deselect(This)	\
    (This)->lpVtbl -> Deselect(This)

#define IInputMethod2_Showing(This)	\
    (This)->lpVtbl -> Showing(This)

#define IInputMethod2_Hiding(This)	\
    (This)->lpVtbl -> Hiding(This)

#define IInputMethod2_GetInfo(This,pimi)	\
    (This)->lpVtbl -> GetInfo(This,pimi)

#define IInputMethod2_ReceiveSipInfo(This,psi)	\
    (This)->lpVtbl -> ReceiveSipInfo(This,psi)

#define IInputMethod2_RegisterCallback(This,lpIMCallback)	\
    (This)->lpVtbl -> RegisterCallback(This,lpIMCallback)

#define IInputMethod2_GetImData(This,dwSize,pvImData)	\
    (This)->lpVtbl -> GetImData(This,dwSize,pvImData)

#define IInputMethod2_SetImData(This,dwSize,pvImData)	\
    (This)->lpVtbl -> SetImData(This,dwSize,pvImData)

#define IInputMethod2_UserOptionsDlg(This,hwndParent)	\
    (This)->lpVtbl -> UserOptionsDlg(This,hwndParent)


#define IInputMethod2_SetIMMActiveContext(This,hwnd,bOpen,dwConversion,dwSentence,hkl)	\
    (This)->lpVtbl -> SetIMMActiveContext(This,hwnd,bOpen,dwConversion,dwSentence,hkl)

#define IInputMethod2_RegisterCallback2(This,lpIMCallback)	\
    (This)->lpVtbl -> RegisterCallback2(This,lpIMCallback)

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IInputMethod2_INTERFACE_DEFINED__ */



#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
//	{42429666-ae04-11d0-a4f8-00aa00a749b9}
DEFINE_GUID(IID_IInputMethod,
0x42429666, 0xae04, 0x11d0, 0xa4, 0xf8, 0x00, 0xaa, 0x00, 0xa7, 0x49, 0xb9);

//	{42429669-ae04-11d0-a4f8-00aa00a749b9}
DEFINE_GUID(IID_IIMCallback,
0x42429669, 0xae04, 0x11d0, 0xa4, 0xf8, 0x00, 0xaa, 0x00, 0xa7, 0x49, 0xb9);

//	{0576F2E1-AA6B-11d2-A146-0000F8757270}
DEFINE_GUID(IID_IInputMethod2,
0x0576f2e1, 0xaa6b, 0x11d2, 0xa1, 0x46, 0x00, 0x00, 0xf8, 0x75, 0x72, 0x70);

//	{0576F2E0-AA6B-11d2-A146-0000F8757270}
DEFINE_GUID(IID_IIMCallback2,
0x0576f2e0, 0xaa6b, 0x11d2, 0xa1, 0x46, 0x00, 0x00, 0xf8, 0x75, 0x72, 0x70);

EXTERN_C const CLSID CLSID_CMSQwertyIm;

class DECLSPEC_UUID("42429667-ae04-11d0-a4f8-00aa00a749b9")
CMSQwertyIm;
#endif


#endif
