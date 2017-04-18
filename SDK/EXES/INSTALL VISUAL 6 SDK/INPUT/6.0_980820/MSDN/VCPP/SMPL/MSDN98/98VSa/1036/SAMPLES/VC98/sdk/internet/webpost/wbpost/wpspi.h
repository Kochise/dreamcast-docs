/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:02:38 1998
 */
/* Compiler settings for wpspi.idl:
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

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __wpspi_h__
#define __wpspi_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IWPSiteW_FWD_DEFINED__
#define __IWPSiteW_FWD_DEFINED__
typedef interface IWPSiteW IWPSiteW;
#endif 	/* __IWPSiteW_FWD_DEFINED__ */


#ifndef __IWPProvider_FWD_DEFINED__
#define __IWPProvider_FWD_DEFINED__
typedef interface IWPProvider IWPProvider;
#endif 	/* __IWPProvider_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "wptypes.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/****************************************
 * Generated header for interface: __MIDL_itf_wpspi_0000
 * at Mon Mar 30 03:02:38 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [local] */ 


#undef DeleteFile
#undef FindFirstFile
#undef FindNextFile
 
typedef HRESULT (CALLBACK *PFNPROGRESSUPDATEPROC)(LPCWSTR, DWORD);


extern RPC_IF_HANDLE __MIDL_itf_wpspi_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_wpspi_0000_v0_0_s_ifspec;

#ifndef __IWPSiteW_INTERFACE_DEFINED__
#define __IWPSiteW_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IWPSiteW
 * at Mon Mar 30 03:02:38 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][uuid][local][object] */ 


#ifndef _WINBASE_
typedef struct  tagWIN32_FIND_DATAW
    {
    long dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    long nFileSizeHigh;
    long nFileSizeLow;
    long dwReserved0;
    long dwReserved1;
    WCHAR cFileName[ 260 ];
    WCHAR cAlternateFileName[ 14 ];
    }	WIN32_FIND_DATAW;

typedef struct tagWIN32_FIND_DATAW __RPC_FAR *PWIN32_FIND_DATAW;

typedef struct tagWIN32_FIND_DATAW __RPC_FAR *LPWIN32_FIND_DATAW;

#endif

EXTERN_C const IID IID_IWPSiteW;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5261F720-6C4C-11CF-86B1-00AA0060F86C")
    IWPSiteW : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetSiteInfo( 
            /* [out] */ LPWPSITEINFOW lpbSite,
            /* [out][in] */ LONG __RPC_FAR *lpcbSite) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NetworkConnect( 
            /* [string][in] */ LPCWSTR lpszUserName,
            /* [string][in] */ LPCWSTR lpszPassword) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NetworkDisconnect( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ServerLogin( 
            /* [string][in] */ LPCWSTR lpszUserName,
            /* [string][in] */ LPCWSTR lpszPassword) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ServerLogout( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PostFiles( 
            /* [in] */ LONG cLocalPaths,
            /* [string][in] */ LPWSTR __RPC_FAR *lppszLocalPaths,
            /* [out][in] */ LONG __RPC_FAR *lpcbURL,
            /* [string][out][in] */ LPWSTR lpszURL,
            /* [in] */ LONG fdwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteFile( 
            /* [string][in] */ LPCWSTR lpszFile) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FindFirstFile( 
            /* [string][in] */ LPCWSTR lpszSearchFile,
            /* [out] */ LPWIN32_FIND_DATAW lpFindFileData,
            /* [out] */ LONG __RPC_FAR *lpSearchHandle) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FindNextFile( 
            /* [in] */ LONG hSearchHandle,
            /* [out] */ LPWIN32_FIND_DATAW lpFindFileData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FindClose( 
            /* [in] */ LONG hSearchHandle) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Commit( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetParam( 
            /* [string][in] */ LPCWSTR lpszParameter,
            /* [out][in] */ LONG __RPC_FAR *lpcbValue,
            /* [string][out] */ LPWSTR lpszValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetParam( 
            /* [string][in] */ LPCWSTR lpszParameter,
            /* [string][in] */ LPCWSTR lpszValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetError( 
            /* [out] */ LONG __RPC_FAR *lpdwErrorType,
            /* [out] */ LONG __RPC_FAR *lpdwErrorCode,
            /* [out][in] */ LONG __RPC_FAR *lpcbError,
            /* [string][out] */ LPWSTR lpszError) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddWizardPages( 
            /* [in] */ LONG __RPC_FAR *lpv,
            /* [in] */ LONG __RPC_FAR *lpfnAdd,
            /* [out][in] */ LONG __RPC_FAR *lParam) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWPSiteWVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWPSiteW __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWPSiteW __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWPSiteW __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSiteInfo )( 
            IWPSiteW __RPC_FAR * This,
            /* [out] */ LPWPSITEINFOW lpbSite,
            /* [out][in] */ LONG __RPC_FAR *lpcbSite);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NetworkConnect )( 
            IWPSiteW __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpszUserName,
            /* [string][in] */ LPCWSTR lpszPassword);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NetworkDisconnect )( 
            IWPSiteW __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ServerLogin )( 
            IWPSiteW __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpszUserName,
            /* [string][in] */ LPCWSTR lpszPassword);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ServerLogout )( 
            IWPSiteW __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PostFiles )( 
            IWPSiteW __RPC_FAR * This,
            /* [in] */ LONG cLocalPaths,
            /* [string][in] */ LPWSTR __RPC_FAR *lppszLocalPaths,
            /* [out][in] */ LONG __RPC_FAR *lpcbURL,
            /* [string][out][in] */ LPWSTR lpszURL,
            /* [in] */ LONG fdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteFile )( 
            IWPSiteW __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpszFile);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindFirstFile )( 
            IWPSiteW __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpszSearchFile,
            /* [out] */ LPWIN32_FIND_DATAW lpFindFileData,
            /* [out] */ LONG __RPC_FAR *lpSearchHandle);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindNextFile )( 
            IWPSiteW __RPC_FAR * This,
            /* [in] */ LONG hSearchHandle,
            /* [out] */ LPWIN32_FIND_DATAW lpFindFileData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindClose )( 
            IWPSiteW __RPC_FAR * This,
            /* [in] */ LONG hSearchHandle);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Commit )( 
            IWPSiteW __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParam )( 
            IWPSiteW __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpszParameter,
            /* [out][in] */ LONG __RPC_FAR *lpcbValue,
            /* [string][out] */ LPWSTR lpszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetParam )( 
            IWPSiteW __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpszParameter,
            /* [string][in] */ LPCWSTR lpszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetError )( 
            IWPSiteW __RPC_FAR * This,
            /* [out] */ LONG __RPC_FAR *lpdwErrorType,
            /* [out] */ LONG __RPC_FAR *lpdwErrorCode,
            /* [out][in] */ LONG __RPC_FAR *lpcbError,
            /* [string][out] */ LPWSTR lpszError);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddWizardPages )( 
            IWPSiteW __RPC_FAR * This,
            /* [in] */ LONG __RPC_FAR *lpv,
            /* [in] */ LONG __RPC_FAR *lpfnAdd,
            /* [out][in] */ LONG __RPC_FAR *lParam);
        
        END_INTERFACE
    } IWPSiteWVtbl;

    interface IWPSiteW
    {
        CONST_VTBL struct IWPSiteWVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWPSiteW_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWPSiteW_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWPSiteW_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWPSiteW_GetSiteInfo(This,lpbSite,lpcbSite)	\
    (This)->lpVtbl -> GetSiteInfo(This,lpbSite,lpcbSite)

#define IWPSiteW_NetworkConnect(This,lpszUserName,lpszPassword)	\
    (This)->lpVtbl -> NetworkConnect(This,lpszUserName,lpszPassword)

#define IWPSiteW_NetworkDisconnect(This)	\
    (This)->lpVtbl -> NetworkDisconnect(This)

#define IWPSiteW_ServerLogin(This,lpszUserName,lpszPassword)	\
    (This)->lpVtbl -> ServerLogin(This,lpszUserName,lpszPassword)

#define IWPSiteW_ServerLogout(This)	\
    (This)->lpVtbl -> ServerLogout(This)

#define IWPSiteW_PostFiles(This,cLocalPaths,lppszLocalPaths,lpcbURL,lpszURL,fdwFlags)	\
    (This)->lpVtbl -> PostFiles(This,cLocalPaths,lppszLocalPaths,lpcbURL,lpszURL,fdwFlags)

#define IWPSiteW_DeleteFile(This,lpszFile)	\
    (This)->lpVtbl -> DeleteFile(This,lpszFile)

#define IWPSiteW_FindFirstFile(This,lpszSearchFile,lpFindFileData,lpSearchHandle)	\
    (This)->lpVtbl -> FindFirstFile(This,lpszSearchFile,lpFindFileData,lpSearchHandle)

#define IWPSiteW_FindNextFile(This,hSearchHandle,lpFindFileData)	\
    (This)->lpVtbl -> FindNextFile(This,hSearchHandle,lpFindFileData)

#define IWPSiteW_FindClose(This,hSearchHandle)	\
    (This)->lpVtbl -> FindClose(This,hSearchHandle)

#define IWPSiteW_Commit(This)	\
    (This)->lpVtbl -> Commit(This)

#define IWPSiteW_GetParam(This,lpszParameter,lpcbValue,lpszValue)	\
    (This)->lpVtbl -> GetParam(This,lpszParameter,lpcbValue,lpszValue)

#define IWPSiteW_SetParam(This,lpszParameter,lpszValue)	\
    (This)->lpVtbl -> SetParam(This,lpszParameter,lpszValue)

#define IWPSiteW_GetError(This,lpdwErrorType,lpdwErrorCode,lpcbError,lpszError)	\
    (This)->lpVtbl -> GetError(This,lpdwErrorType,lpdwErrorCode,lpcbError,lpszError)

#define IWPSiteW_AddWizardPages(This,lpv,lpfnAdd,lParam)	\
    (This)->lpVtbl -> AddWizardPages(This,lpv,lpfnAdd,lParam)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWPSiteW_GetSiteInfo_Proxy( 
    IWPSiteW __RPC_FAR * This,
    /* [out] */ LPWPSITEINFOW lpbSite,
    /* [out][in] */ LONG __RPC_FAR *lpcbSite);


void __RPC_STUB IWPSiteW_GetSiteInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWPSiteW_NetworkConnect_Proxy( 
    IWPSiteW __RPC_FAR * This,
    /* [string][in] */ LPCWSTR lpszUserName,
    /* [string][in] */ LPCWSTR lpszPassword);


void __RPC_STUB IWPSiteW_NetworkConnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWPSiteW_NetworkDisconnect_Proxy( 
    IWPSiteW __RPC_FAR * This);


void __RPC_STUB IWPSiteW_NetworkDisconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWPSiteW_ServerLogin_Proxy( 
    IWPSiteW __RPC_FAR * This,
    /* [string][in] */ LPCWSTR lpszUserName,
    /* [string][in] */ LPCWSTR lpszPassword);


void __RPC_STUB IWPSiteW_ServerLogin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWPSiteW_ServerLogout_Proxy( 
    IWPSiteW __RPC_FAR * This);


void __RPC_STUB IWPSiteW_ServerLogout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWPSiteW_PostFiles_Proxy( 
    IWPSiteW __RPC_FAR * This,
    /* [in] */ LONG cLocalPaths,
    /* [string][in] */ LPWSTR __RPC_FAR *lppszLocalPaths,
    /* [out][in] */ LONG __RPC_FAR *lpcbURL,
    /* [string][out][in] */ LPWSTR lpszURL,
    /* [in] */ LONG fdwFlags);


void __RPC_STUB IWPSiteW_PostFiles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWPSiteW_DeleteFile_Proxy( 
    IWPSiteW __RPC_FAR * This,
    /* [string][in] */ LPCWSTR lpszFile);


void __RPC_STUB IWPSiteW_DeleteFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWPSiteW_FindFirstFile_Proxy( 
    IWPSiteW __RPC_FAR * This,
    /* [string][in] */ LPCWSTR lpszSearchFile,
    /* [out] */ LPWIN32_FIND_DATAW lpFindFileData,
    /* [out] */ LONG __RPC_FAR *lpSearchHandle);


void __RPC_STUB IWPSiteW_FindFirstFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWPSiteW_FindNextFile_Proxy( 
    IWPSiteW __RPC_FAR * This,
    /* [in] */ LONG hSearchHandle,
    /* [out] */ LPWIN32_FIND_DATAW lpFindFileData);


void __RPC_STUB IWPSiteW_FindNextFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWPSiteW_FindClose_Proxy( 
    IWPSiteW __RPC_FAR * This,
    /* [in] */ LONG hSearchHandle);


void __RPC_STUB IWPSiteW_FindClose_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWPSiteW_Commit_Proxy( 
    IWPSiteW __RPC_FAR * This);


void __RPC_STUB IWPSiteW_Commit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWPSiteW_GetParam_Proxy( 
    IWPSiteW __RPC_FAR * This,
    /* [string][in] */ LPCWSTR lpszParameter,
    /* [out][in] */ LONG __RPC_FAR *lpcbValue,
    /* [string][out] */ LPWSTR lpszValue);


void __RPC_STUB IWPSiteW_GetParam_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWPSiteW_SetParam_Proxy( 
    IWPSiteW __RPC_FAR * This,
    /* [string][in] */ LPCWSTR lpszParameter,
    /* [string][in] */ LPCWSTR lpszValue);


void __RPC_STUB IWPSiteW_SetParam_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWPSiteW_GetError_Proxy( 
    IWPSiteW __RPC_FAR * This,
    /* [out] */ LONG __RPC_FAR *lpdwErrorType,
    /* [out] */ LONG __RPC_FAR *lpdwErrorCode,
    /* [out][in] */ LONG __RPC_FAR *lpcbError,
    /* [string][out] */ LPWSTR lpszError);


void __RPC_STUB IWPSiteW_GetError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWPSiteW_AddWizardPages_Proxy( 
    IWPSiteW __RPC_FAR * This,
    /* [in] */ LONG __RPC_FAR *lpv,
    /* [in] */ LONG __RPC_FAR *lpfnAdd,
    /* [out][in] */ LONG __RPC_FAR *lParam);


void __RPC_STUB IWPSiteW_AddWizardPages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWPSiteW_INTERFACE_DEFINED__ */


#ifndef __IWPProvider_INTERFACE_DEFINED__
#define __IWPProvider_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IWPProvider
 * at Mon Mar 30 03:02:38 1998
 * using MIDL 3.03.0110
 ****************************************/
/* [unique][helpstring][uuid][local][object] */ 



EXTERN_C const IID IID_IWPProvider;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CB1D5316-30F6-11D0-AD03-00AA00A219AA")
    IWPProvider : public IWPSiteW
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetProgressUpdateProc( 
            /* [in] */ LONG __RPC_FAR *pfnProgressUpdateProc) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWPProviderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWPProvider __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWPProvider __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWPProvider __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSiteInfo )( 
            IWPProvider __RPC_FAR * This,
            /* [out] */ LPWPSITEINFOW lpbSite,
            /* [out][in] */ LONG __RPC_FAR *lpcbSite);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NetworkConnect )( 
            IWPProvider __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpszUserName,
            /* [string][in] */ LPCWSTR lpszPassword);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NetworkDisconnect )( 
            IWPProvider __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ServerLogin )( 
            IWPProvider __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpszUserName,
            /* [string][in] */ LPCWSTR lpszPassword);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ServerLogout )( 
            IWPProvider __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PostFiles )( 
            IWPProvider __RPC_FAR * This,
            /* [in] */ LONG cLocalPaths,
            /* [string][in] */ LPWSTR __RPC_FAR *lppszLocalPaths,
            /* [out][in] */ LONG __RPC_FAR *lpcbURL,
            /* [string][out][in] */ LPWSTR lpszURL,
            /* [in] */ LONG fdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteFile )( 
            IWPProvider __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpszFile);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindFirstFile )( 
            IWPProvider __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpszSearchFile,
            /* [out] */ LPWIN32_FIND_DATAW lpFindFileData,
            /* [out] */ LONG __RPC_FAR *lpSearchHandle);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindNextFile )( 
            IWPProvider __RPC_FAR * This,
            /* [in] */ LONG hSearchHandle,
            /* [out] */ LPWIN32_FIND_DATAW lpFindFileData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindClose )( 
            IWPProvider __RPC_FAR * This,
            /* [in] */ LONG hSearchHandle);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Commit )( 
            IWPProvider __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParam )( 
            IWPProvider __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpszParameter,
            /* [out][in] */ LONG __RPC_FAR *lpcbValue,
            /* [string][out] */ LPWSTR lpszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetParam )( 
            IWPProvider __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpszParameter,
            /* [string][in] */ LPCWSTR lpszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetError )( 
            IWPProvider __RPC_FAR * This,
            /* [out] */ LONG __RPC_FAR *lpdwErrorType,
            /* [out] */ LONG __RPC_FAR *lpdwErrorCode,
            /* [out][in] */ LONG __RPC_FAR *lpcbError,
            /* [string][out] */ LPWSTR lpszError);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddWizardPages )( 
            IWPProvider __RPC_FAR * This,
            /* [in] */ LONG __RPC_FAR *lpv,
            /* [in] */ LONG __RPC_FAR *lpfnAdd,
            /* [out][in] */ LONG __RPC_FAR *lParam);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetProgressUpdateProc )( 
            IWPProvider __RPC_FAR * This,
            /* [in] */ LONG __RPC_FAR *pfnProgressUpdateProc);
        
        END_INTERFACE
    } IWPProviderVtbl;

    interface IWPProvider
    {
        CONST_VTBL struct IWPProviderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWPProvider_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWPProvider_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWPProvider_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWPProvider_GetSiteInfo(This,lpbSite,lpcbSite)	\
    (This)->lpVtbl -> GetSiteInfo(This,lpbSite,lpcbSite)

#define IWPProvider_NetworkConnect(This,lpszUserName,lpszPassword)	\
    (This)->lpVtbl -> NetworkConnect(This,lpszUserName,lpszPassword)

#define IWPProvider_NetworkDisconnect(This)	\
    (This)->lpVtbl -> NetworkDisconnect(This)

#define IWPProvider_ServerLogin(This,lpszUserName,lpszPassword)	\
    (This)->lpVtbl -> ServerLogin(This,lpszUserName,lpszPassword)

#define IWPProvider_ServerLogout(This)	\
    (This)->lpVtbl -> ServerLogout(This)

#define IWPProvider_PostFiles(This,cLocalPaths,lppszLocalPaths,lpcbURL,lpszURL,fdwFlags)	\
    (This)->lpVtbl -> PostFiles(This,cLocalPaths,lppszLocalPaths,lpcbURL,lpszURL,fdwFlags)

#define IWPProvider_DeleteFile(This,lpszFile)	\
    (This)->lpVtbl -> DeleteFile(This,lpszFile)

#define IWPProvider_FindFirstFile(This,lpszSearchFile,lpFindFileData,lpSearchHandle)	\
    (This)->lpVtbl -> FindFirstFile(This,lpszSearchFile,lpFindFileData,lpSearchHandle)

#define IWPProvider_FindNextFile(This,hSearchHandle,lpFindFileData)	\
    (This)->lpVtbl -> FindNextFile(This,hSearchHandle,lpFindFileData)

#define IWPProvider_FindClose(This,hSearchHandle)	\
    (This)->lpVtbl -> FindClose(This,hSearchHandle)

#define IWPProvider_Commit(This)	\
    (This)->lpVtbl -> Commit(This)

#define IWPProvider_GetParam(This,lpszParameter,lpcbValue,lpszValue)	\
    (This)->lpVtbl -> GetParam(This,lpszParameter,lpcbValue,lpszValue)

#define IWPProvider_SetParam(This,lpszParameter,lpszValue)	\
    (This)->lpVtbl -> SetParam(This,lpszParameter,lpszValue)

#define IWPProvider_GetError(This,lpdwErrorType,lpdwErrorCode,lpcbError,lpszError)	\
    (This)->lpVtbl -> GetError(This,lpdwErrorType,lpdwErrorCode,lpcbError,lpszError)

#define IWPProvider_AddWizardPages(This,lpv,lpfnAdd,lParam)	\
    (This)->lpVtbl -> AddWizardPages(This,lpv,lpfnAdd,lParam)


#define IWPProvider_SetProgressUpdateProc(This,pfnProgressUpdateProc)	\
    (This)->lpVtbl -> SetProgressUpdateProc(This,pfnProgressUpdateProc)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWPProvider_SetProgressUpdateProc_Proxy( 
    IWPProvider __RPC_FAR * This,
    /* [in] */ LONG __RPC_FAR *pfnProgressUpdateProc);


void __RPC_STUB IWPProvider_SetProgressUpdateProc_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWPProvider_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
