/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.02.88 */
/* at Mon Nov 17 12:05:03 1997
 */
/* Compiler settings for exdisp.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"

#ifndef __exdisp_h__
#define __exdisp_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IWebBrowser_FWD_DEFINED__
#define __IWebBrowser_FWD_DEFINED__
typedef interface IWebBrowser IWebBrowser;
#endif 	/* __IWebBrowser_FWD_DEFINED__ */


#ifndef __DWebBrowserEvents_FWD_DEFINED__
#define __DWebBrowserEvents_FWD_DEFINED__
typedef interface DWebBrowserEvents DWebBrowserEvents;
#endif 	/* __DWebBrowserEvents_FWD_DEFINED__ */


#ifndef __IWebBrowserApp_FWD_DEFINED__
#define __IWebBrowserApp_FWD_DEFINED__
typedef interface IWebBrowserApp IWebBrowserApp;
#endif 	/* __IWebBrowserApp_FWD_DEFINED__ */


#ifndef __IWebBrowser2_FWD_DEFINED__
#define __IWebBrowser2_FWD_DEFINED__
typedef interface IWebBrowser2 IWebBrowser2;
#endif 	/* __IWebBrowser2_FWD_DEFINED__ */


#ifndef __DWebBrowserEvents2_FWD_DEFINED__
#define __DWebBrowserEvents2_FWD_DEFINED__
typedef interface DWebBrowserEvents2 DWebBrowserEvents2;
#endif 	/* __DWebBrowserEvents2_FWD_DEFINED__ */


#ifndef __WebBrowser_V1_FWD_DEFINED__
#define __WebBrowser_V1_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebBrowser_V1 WebBrowser_V1;
#else
typedef struct WebBrowser_V1 WebBrowser_V1;
#endif /* __cplusplus */

#endif 	/* __WebBrowser_V1_FWD_DEFINED__ */


#ifndef __WebBrowser_FWD_DEFINED__
#define __WebBrowser_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebBrowser WebBrowser;
#else
typedef struct WebBrowser WebBrowser;
#endif /* __cplusplus */

#endif 	/* __WebBrowser_FWD_DEFINED__ */


#ifndef __InternetExplorer_FWD_DEFINED__
#define __InternetExplorer_FWD_DEFINED__

#ifdef __cplusplus
typedef class InternetExplorer InternetExplorer;
#else
typedef struct InternetExplorer InternetExplorer;
#endif /* __cplusplus */

#endif 	/* __InternetExplorer_FWD_DEFINED__ */


#ifndef __IFolderViewOC_FWD_DEFINED__
#define __IFolderViewOC_FWD_DEFINED__
typedef interface IFolderViewOC IFolderViewOC;
#endif 	/* __IFolderViewOC_FWD_DEFINED__ */


#ifndef __DShellFolderViewEvents_FWD_DEFINED__
#define __DShellFolderViewEvents_FWD_DEFINED__
typedef interface DShellFolderViewEvents DShellFolderViewEvents;
#endif 	/* __DShellFolderViewEvents_FWD_DEFINED__ */


#ifndef __ShellFolderViewOC_FWD_DEFINED__
#define __ShellFolderViewOC_FWD_DEFINED__

#ifdef __cplusplus
typedef class ShellFolderViewOC ShellFolderViewOC;
#else
typedef struct ShellFolderViewOC ShellFolderViewOC;
#endif /* __cplusplus */

#endif 	/* __ShellFolderViewOC_FWD_DEFINED__ */


#ifndef __DShellWindowsEvents_FWD_DEFINED__
#define __DShellWindowsEvents_FWD_DEFINED__
typedef interface DShellWindowsEvents DShellWindowsEvents;
#endif 	/* __DShellWindowsEvents_FWD_DEFINED__ */


#ifndef __IShellWindows_FWD_DEFINED__
#define __IShellWindows_FWD_DEFINED__
typedef interface IShellWindows IShellWindows;
#endif 	/* __IShellWindows_FWD_DEFINED__ */


#ifndef __ShellWindows_FWD_DEFINED__
#define __ShellWindows_FWD_DEFINED__

#ifdef __cplusplus
typedef class ShellWindows ShellWindows;
#else
typedef struct ShellWindows ShellWindows;
#endif /* __cplusplus */

#endif 	/* __ShellWindows_FWD_DEFINED__ */


#ifndef __IShellLinkDual_FWD_DEFINED__
#define __IShellLinkDual_FWD_DEFINED__
typedef interface IShellLinkDual IShellLinkDual;
#endif 	/* __IShellLinkDual_FWD_DEFINED__ */


#ifndef __ShellLinkObject_FWD_DEFINED__
#define __ShellLinkObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class ShellLinkObject ShellLinkObject;
#else
typedef struct ShellLinkObject ShellLinkObject;
#endif /* __cplusplus */

#endif 	/* __ShellLinkObject_FWD_DEFINED__ */


#ifndef __FolderItemVerb_FWD_DEFINED__
#define __FolderItemVerb_FWD_DEFINED__
typedef interface FolderItemVerb FolderItemVerb;
#endif 	/* __FolderItemVerb_FWD_DEFINED__ */


#ifndef __FolderItemVerbs_FWD_DEFINED__
#define __FolderItemVerbs_FWD_DEFINED__
typedef interface FolderItemVerbs FolderItemVerbs;
#endif 	/* __FolderItemVerbs_FWD_DEFINED__ */


#ifndef __Folder_FWD_DEFINED__
#define __Folder_FWD_DEFINED__
typedef interface Folder Folder;
#endif 	/* __Folder_FWD_DEFINED__ */


#ifndef __FolderItem_FWD_DEFINED__
#define __FolderItem_FWD_DEFINED__
typedef interface FolderItem FolderItem;
#endif 	/* __FolderItem_FWD_DEFINED__ */


#ifndef __FolderItems_FWD_DEFINED__
#define __FolderItems_FWD_DEFINED__
typedef interface FolderItems FolderItems;
#endif 	/* __FolderItems_FWD_DEFINED__ */


#ifndef __IShellFolderViewDual_FWD_DEFINED__
#define __IShellFolderViewDual_FWD_DEFINED__
typedef interface IShellFolderViewDual IShellFolderViewDual;
#endif 	/* __IShellFolderViewDual_FWD_DEFINED__ */


#ifndef __ShellFolderView_FWD_DEFINED__
#define __ShellFolderView_FWD_DEFINED__

#ifdef __cplusplus
typedef class ShellFolderView ShellFolderView;
#else
typedef struct ShellFolderView ShellFolderView;
#endif /* __cplusplus */

#endif 	/* __ShellFolderView_FWD_DEFINED__ */


#ifndef __IShellDispatch_FWD_DEFINED__
#define __IShellDispatch_FWD_DEFINED__
typedef interface IShellDispatch IShellDispatch;
#endif 	/* __IShellDispatch_FWD_DEFINED__ */


#ifndef __Shell_FWD_DEFINED__
#define __Shell_FWD_DEFINED__

#ifdef __cplusplus
typedef class Shell Shell;
#else
typedef struct Shell Shell;
#endif /* __cplusplus */

#endif 	/* __Shell_FWD_DEFINED__ */


#ifndef __ShellDispatchInproc_FWD_DEFINED__
#define __ShellDispatchInproc_FWD_DEFINED__

#ifdef __cplusplus
typedef class ShellDispatchInproc ShellDispatchInproc;
#else
typedef struct ShellDispatchInproc ShellDispatchInproc;
#endif /* __cplusplus */

#endif 	/* __ShellDispatchInproc_FWD_DEFINED__ */


#ifndef __WebViewFolderContents_FWD_DEFINED__
#define __WebViewFolderContents_FWD_DEFINED__

#ifdef __cplusplus
typedef class WebViewFolderContents WebViewFolderContents;
#else
typedef struct WebViewFolderContents WebViewFolderContents;
#endif /* __cplusplus */

#endif 	/* __WebViewFolderContents_FWD_DEFINED__ */


#ifndef __IShellUIHelper_FWD_DEFINED__
#define __IShellUIHelper_FWD_DEFINED__
typedef interface IShellUIHelper IShellUIHelper;
#endif 	/* __IShellUIHelper_FWD_DEFINED__ */


#ifndef __ShellUIHelper_FWD_DEFINED__
#define __ShellUIHelper_FWD_DEFINED__

#ifdef __cplusplus
typedef class ShellUIHelper ShellUIHelper;
#else
typedef struct ShellUIHelper ShellUIHelper;
#endif /* __cplusplus */

#endif 	/* __ShellUIHelper_FWD_DEFINED__ */


/* header files for imported files */
#include "ocidl.h"
#include "docobj.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __SHDocVw_LIBRARY_DEFINED__
#define __SHDocVw_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: SHDocVw
 * at Mon Nov 17 12:05:03 1997
 * using MIDL 3.02.88
 ****************************************/
/* [version][lcid][helpstring][uuid] */ 


typedef /* [helpstring][uuid] */ 
enum CommandStateChangeConstants
    {	CSC_UPDATECOMMANDS	= 0xffffffff,
	CSC_NAVIGATEFORWARD	= 0x1,
	CSC_NAVIGATEBACK	= 0x2
    }	CommandStateChangeConstants;

typedef /* [helpstring][uuid] */ 
enum ShellWindowTypeConstants
    {	SWC_EXPLORER	= 0,
	SWC_BROWSER	= 0x1,
	SWC_3RDPARTY	= 0x2,
	SWC_CALLBACK	= 0x4
    }	ShellWindowTypeConstants;

typedef /* [hidden][helpstring][uuid] */ 
enum ShellWindowFindWindowOptions
    {	SWFO_NEEDDISPATCH	= 0x1,
	SWFO_INCLUDEPENDING	= 0x2,
	SWFO_COOKIEPASSED	= 0x4
    }	ShellWindowFindWindowOptions;


typedef /* [helpstring][uuid] */ 
enum ShellFolderViewOptions
    {	SFVVO_SHOWALLOBJECTS	= 0x1,
	SFVVO_SHOWEXTENSIONS	= 0x2,
	SFVVO_SHOWCOMPCOLOR	= 0x8,
	SFVVO_SHOWSYSFILES	= 0x20,
	SFVVO_WIN95CLASSIC	= 0x40,
	SFVVO_DOUBLECLICKINWEBVIEW	= 0x80,
	SFVVO_DESKTOPHTML	= 0x200
    }	ShellFolderViewOptions;

typedef /* [helpstring][uuid] */ 
enum ShellSpecialFolderConstants
    {	ssfDESKTOP	= 0,
	ssfPROGRAMS	= 0x2,
	ssfCONTROLS	= 0x3,
	ssfPRINTERS	= 0x4,
	ssfPERSONAL	= 0x5,
	ssfFAVORITES	= 0x6,
	ssfSTARTUP	= 0x7,
	ssfRECENT	= 0x8,
	ssfSENDTO	= 0x9,
	ssfBITBUCKET	= 0xa,
	ssfSTARTMENU	= 0xb,
	ssfDESKTOPDIRECTORY	= 0x10,
	ssfDRIVES	= 0x11,
	ssfNETWORK	= 0x12,
	ssfNETHOOD	= 0x13,
	ssfFONTS	= 0x14,
	ssfTEMPLATES	= 0x15
    }	ShellSpecialFolderConstants;


EXTERN_C const IID LIBID_SHDocVw;

#ifndef __IWebBrowser_INTERFACE_DEFINED__
#define __IWebBrowser_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IWebBrowser
 * at Mon Nov 17 12:05:03 1997
 * using MIDL 3.02.88
 ****************************************/
/* [object][oleautomation][dual][hidden][helpcontext][helpstring][uuid] */ 


typedef /* [helpstring][uuid] */ 
enum BrowserNavConstants
    {	navOpenInNewWindow	= 0x1,
	navNoHistory	= 0x2,
	navNoReadFromCache	= 0x4,
	navNoWriteToCache	= 0x8,
	navAllowAutosearch	= 0x10,
	navBrowserBar	= 0x20
    }	BrowserNavConstants;

typedef /* [helpstring][uuid] */ 
enum RefreshConstants
    {	REFRESH_NORMAL	= 0,
	REFRESH_IFEXPIRED	= 1,
	REFRESH_COMPLETELY	= 3
    }	RefreshConstants;


EXTERN_C const IID IID_IWebBrowser;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("EAB22AC1-30C1-11CF-A7EB-0000C05BAE0B")
    IWebBrowser : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GoBack( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GoForward( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GoHome( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GoSearch( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Navigate( 
            /* [in] */ BSTR URL,
            /* [optional][in] */ VARIANT __RPC_FAR *Flags,
            /* [optional][in] */ VARIANT __RPC_FAR *TargetFrameName,
            /* [optional][in] */ VARIANT __RPC_FAR *PostData,
            /* [optional][in] */ VARIANT __RPC_FAR *Headers) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh2( 
            /* [optional][in] */ VARIANT __RPC_FAR *Level) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Container( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Document( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_TopLevelContainer( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBool) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ BSTR __RPC_FAR *Type) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Left( 
            /* [retval][out] */ long __RPC_FAR *pl) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Left( 
            /* [in] */ long Left) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Top( 
            /* [retval][out] */ long __RPC_FAR *pl) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Top( 
            /* [in] */ long Top) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ long __RPC_FAR *pl) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ long Width) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ long __RPC_FAR *pl) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_Height( 
            /* [in] */ long Height) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_LocationName( 
            /* [retval][out] */ BSTR __RPC_FAR *LocationName) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_LocationURL( 
            /* [retval][out] */ BSTR __RPC_FAR *LocationURL) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Busy( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBool) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebBrowserVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebBrowser __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebBrowser __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebBrowser __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebBrowser __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebBrowser __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebBrowser __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebBrowser __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GoBack )( 
            IWebBrowser __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GoForward )( 
            IWebBrowser __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GoHome )( 
            IWebBrowser __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GoSearch )( 
            IWebBrowser __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Navigate )( 
            IWebBrowser __RPC_FAR * This,
            /* [in] */ BSTR URL,
            /* [optional][in] */ VARIANT __RPC_FAR *Flags,
            /* [optional][in] */ VARIANT __RPC_FAR *TargetFrameName,
            /* [optional][in] */ VARIANT __RPC_FAR *PostData,
            /* [optional][in] */ VARIANT __RPC_FAR *Headers);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWebBrowser __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh2 )( 
            IWebBrowser __RPC_FAR * This,
            /* [optional][in] */ VARIANT __RPC_FAR *Level);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IWebBrowser __RPC_FAR * This);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            IWebBrowser __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IWebBrowser __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Container )( 
            IWebBrowser __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Document )( 
            IWebBrowser __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TopLevelContainer )( 
            IWebBrowser __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBool);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IWebBrowser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Type);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Left )( 
            IWebBrowser __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pl);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Left )( 
            IWebBrowser __RPC_FAR * This,
            /* [in] */ long Left);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Top )( 
            IWebBrowser __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pl);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Top )( 
            IWebBrowser __RPC_FAR * This,
            /* [in] */ long Top);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            IWebBrowser __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pl);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Width )( 
            IWebBrowser __RPC_FAR * This,
            /* [in] */ long Width);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Height )( 
            IWebBrowser __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pl);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Height )( 
            IWebBrowser __RPC_FAR * This,
            /* [in] */ long Height);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocationName )( 
            IWebBrowser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *LocationName);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocationURL )( 
            IWebBrowser __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *LocationURL);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Busy )( 
            IWebBrowser __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBool);
        
        END_INTERFACE
    } IWebBrowserVtbl;

    interface IWebBrowser
    {
        CONST_VTBL struct IWebBrowserVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebBrowser_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebBrowser_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebBrowser_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebBrowser_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebBrowser_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebBrowser_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebBrowser_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebBrowser_GoBack(This)	\
    (This)->lpVtbl -> GoBack(This)

#define IWebBrowser_GoForward(This)	\
    (This)->lpVtbl -> GoForward(This)

#define IWebBrowser_GoHome(This)	\
    (This)->lpVtbl -> GoHome(This)

#define IWebBrowser_GoSearch(This)	\
    (This)->lpVtbl -> GoSearch(This)

#define IWebBrowser_Navigate(This,URL,Flags,TargetFrameName,PostData,Headers)	\
    (This)->lpVtbl -> Navigate(This,URL,Flags,TargetFrameName,PostData,Headers)

#define IWebBrowser_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IWebBrowser_Refresh2(This,Level)	\
    (This)->lpVtbl -> Refresh2(This,Level)

#define IWebBrowser_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IWebBrowser_get_Application(This,ppDisp)	\
    (This)->lpVtbl -> get_Application(This,ppDisp)

#define IWebBrowser_get_Parent(This,ppDisp)	\
    (This)->lpVtbl -> get_Parent(This,ppDisp)

#define IWebBrowser_get_Container(This,ppDisp)	\
    (This)->lpVtbl -> get_Container(This,ppDisp)

#define IWebBrowser_get_Document(This,ppDisp)	\
    (This)->lpVtbl -> get_Document(This,ppDisp)

#define IWebBrowser_get_TopLevelContainer(This,pBool)	\
    (This)->lpVtbl -> get_TopLevelContainer(This,pBool)

#define IWebBrowser_get_Type(This,Type)	\
    (This)->lpVtbl -> get_Type(This,Type)

#define IWebBrowser_get_Left(This,pl)	\
    (This)->lpVtbl -> get_Left(This,pl)

#define IWebBrowser_put_Left(This,Left)	\
    (This)->lpVtbl -> put_Left(This,Left)

#define IWebBrowser_get_Top(This,pl)	\
    (This)->lpVtbl -> get_Top(This,pl)

#define IWebBrowser_put_Top(This,Top)	\
    (This)->lpVtbl -> put_Top(This,Top)

#define IWebBrowser_get_Width(This,pl)	\
    (This)->lpVtbl -> get_Width(This,pl)

#define IWebBrowser_put_Width(This,Width)	\
    (This)->lpVtbl -> put_Width(This,Width)

#define IWebBrowser_get_Height(This,pl)	\
    (This)->lpVtbl -> get_Height(This,pl)

#define IWebBrowser_put_Height(This,Height)	\
    (This)->lpVtbl -> put_Height(This,Height)

#define IWebBrowser_get_LocationName(This,LocationName)	\
    (This)->lpVtbl -> get_LocationName(This,LocationName)

#define IWebBrowser_get_LocationURL(This,LocationURL)	\
    (This)->lpVtbl -> get_LocationURL(This,LocationURL)

#define IWebBrowser_get_Busy(This,pBool)	\
    (This)->lpVtbl -> get_Busy(This,pBool)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_GoBack_Proxy( 
    IWebBrowser __RPC_FAR * This);


void __RPC_STUB IWebBrowser_GoBack_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_GoForward_Proxy( 
    IWebBrowser __RPC_FAR * This);


void __RPC_STUB IWebBrowser_GoForward_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_GoHome_Proxy( 
    IWebBrowser __RPC_FAR * This);


void __RPC_STUB IWebBrowser_GoHome_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_GoSearch_Proxy( 
    IWebBrowser __RPC_FAR * This);


void __RPC_STUB IWebBrowser_GoSearch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_Navigate_Proxy( 
    IWebBrowser __RPC_FAR * This,
    /* [in] */ BSTR URL,
    /* [optional][in] */ VARIANT __RPC_FAR *Flags,
    /* [optional][in] */ VARIANT __RPC_FAR *TargetFrameName,
    /* [optional][in] */ VARIANT __RPC_FAR *PostData,
    /* [optional][in] */ VARIANT __RPC_FAR *Headers);


void __RPC_STUB IWebBrowser_Navigate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_Refresh_Proxy( 
    IWebBrowser __RPC_FAR * This);


void __RPC_STUB IWebBrowser_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_Refresh2_Proxy( 
    IWebBrowser __RPC_FAR * This,
    /* [optional][in] */ VARIANT __RPC_FAR *Level);


void __RPC_STUB IWebBrowser_Refresh2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_Stop_Proxy( 
    IWebBrowser __RPC_FAR * This);


void __RPC_STUB IWebBrowser_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_get_Application_Proxy( 
    IWebBrowser __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);


void __RPC_STUB IWebBrowser_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_get_Parent_Proxy( 
    IWebBrowser __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);


void __RPC_STUB IWebBrowser_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_get_Container_Proxy( 
    IWebBrowser __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);


void __RPC_STUB IWebBrowser_get_Container_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_get_Document_Proxy( 
    IWebBrowser __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);


void __RPC_STUB IWebBrowser_get_Document_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_get_TopLevelContainer_Proxy( 
    IWebBrowser __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBool);


void __RPC_STUB IWebBrowser_get_TopLevelContainer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_get_Type_Proxy( 
    IWebBrowser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Type);


void __RPC_STUB IWebBrowser_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_get_Left_Proxy( 
    IWebBrowser __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pl);


void __RPC_STUB IWebBrowser_get_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_put_Left_Proxy( 
    IWebBrowser __RPC_FAR * This,
    /* [in] */ long Left);


void __RPC_STUB IWebBrowser_put_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_get_Top_Proxy( 
    IWebBrowser __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pl);


void __RPC_STUB IWebBrowser_get_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_put_Top_Proxy( 
    IWebBrowser __RPC_FAR * This,
    /* [in] */ long Top);


void __RPC_STUB IWebBrowser_put_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_get_Width_Proxy( 
    IWebBrowser __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pl);


void __RPC_STUB IWebBrowser_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_put_Width_Proxy( 
    IWebBrowser __RPC_FAR * This,
    /* [in] */ long Width);


void __RPC_STUB IWebBrowser_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_get_Height_Proxy( 
    IWebBrowser __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pl);


void __RPC_STUB IWebBrowser_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_put_Height_Proxy( 
    IWebBrowser __RPC_FAR * This,
    /* [in] */ long Height);


void __RPC_STUB IWebBrowser_put_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_get_LocationName_Proxy( 
    IWebBrowser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *LocationName);


void __RPC_STUB IWebBrowser_get_LocationName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_get_LocationURL_Proxy( 
    IWebBrowser __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *LocationURL);


void __RPC_STUB IWebBrowser_get_LocationURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser_get_Busy_Proxy( 
    IWebBrowser __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBool);


void __RPC_STUB IWebBrowser_get_Busy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebBrowser_INTERFACE_DEFINED__ */


#ifndef __DWebBrowserEvents_DISPINTERFACE_DEFINED__
#define __DWebBrowserEvents_DISPINTERFACE_DEFINED__

/****************************************
 * Generated header for dispinterface: DWebBrowserEvents
 * at Mon Nov 17 12:05:03 1997
 * using MIDL 3.02.88
 ****************************************/
/* [hidden][helpstring][uuid] */ 



EXTERN_C const IID DIID_DWebBrowserEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface DECLSPEC_UUID("EAB22AC2-30C1-11CF-A7EB-0000C05BAE0B")
    DWebBrowserEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct DWebBrowserEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DWebBrowserEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DWebBrowserEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DWebBrowserEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            DWebBrowserEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            DWebBrowserEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            DWebBrowserEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            DWebBrowserEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } DWebBrowserEventsVtbl;

    interface DWebBrowserEvents
    {
        CONST_VTBL struct DWebBrowserEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DWebBrowserEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DWebBrowserEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DWebBrowserEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DWebBrowserEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define DWebBrowserEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define DWebBrowserEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define DWebBrowserEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __DWebBrowserEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IWebBrowserApp_INTERFACE_DEFINED__
#define __IWebBrowserApp_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IWebBrowserApp
 * at Mon Nov 17 12:05:03 1997
 * using MIDL 3.02.88
 ****************************************/
/* [object][dual][oleautomation][hidden][helpcontext][helpstring][uuid] */ 



EXTERN_C const IID IID_IWebBrowserApp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("0002DF05-0000-0000-C000-000000000046")
    IWebBrowserApp : public IWebBrowser
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Quit( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ClientToWindow( 
            /* [out][in] */ int __RPC_FAR *pcx,
            /* [out][in] */ int __RPC_FAR *pcy) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE PutProperty( 
            /* [in] */ BSTR Property,
            /* [in] */ VARIANT vtValue) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE GetProperty( 
            /* [in] */ BSTR Property,
            /* [retval][out] */ VARIANT __RPC_FAR *pvtValue) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *Name) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_HWND( 
            /* [retval][out] */ long __RPC_FAR *pHWND) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_FullName( 
            /* [retval][out] */ BSTR __RPC_FAR *FullName) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Path( 
            /* [retval][out] */ BSTR __RPC_FAR *Path) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Visible( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBool) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Visible( 
            /* [in] */ VARIANT_BOOL Value) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_StatusBar( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBool) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_StatusBar( 
            /* [in] */ VARIANT_BOOL Value) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_StatusText( 
            /* [retval][out] */ BSTR __RPC_FAR *StatusText) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_StatusText( 
            /* [in] */ BSTR StatusText) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_ToolBar( 
            /* [retval][out] */ int __RPC_FAR *Value) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_ToolBar( 
            /* [in] */ int Value) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_MenuBar( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Value) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_MenuBar( 
            /* [in] */ VARIANT_BOOL Value) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_FullScreen( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbFullScreen) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_FullScreen( 
            /* [in] */ VARIANT_BOOL bFullScreen) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebBrowserAppVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebBrowserApp __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebBrowserApp __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GoBack )( 
            IWebBrowserApp __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GoForward )( 
            IWebBrowserApp __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GoHome )( 
            IWebBrowserApp __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GoSearch )( 
            IWebBrowserApp __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Navigate )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [in] */ BSTR URL,
            /* [optional][in] */ VARIANT __RPC_FAR *Flags,
            /* [optional][in] */ VARIANT __RPC_FAR *TargetFrameName,
            /* [optional][in] */ VARIANT __RPC_FAR *PostData,
            /* [optional][in] */ VARIANT __RPC_FAR *Headers);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWebBrowserApp __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh2 )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [optional][in] */ VARIANT __RPC_FAR *Level);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IWebBrowserApp __RPC_FAR * This);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Container )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Document )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TopLevelContainer )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBool);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Type);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Left )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pl);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Left )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [in] */ long Left);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Top )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pl);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Top )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [in] */ long Top);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pl);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Width )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [in] */ long Width);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Height )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pl);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Height )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [in] */ long Height);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocationName )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *LocationName);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocationURL )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *LocationURL);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Busy )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBool);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Quit )( 
            IWebBrowserApp __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClientToWindow )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [out][in] */ int __RPC_FAR *pcx,
            /* [out][in] */ int __RPC_FAR *pcy);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutProperty )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [in] */ BSTR Property,
            /* [in] */ VARIANT vtValue);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProperty )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [in] */ BSTR Property,
            /* [retval][out] */ VARIANT __RPC_FAR *pvtValue);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Name);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HWND )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pHWND);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullName )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *FullName);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Path )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Path);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBool);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Value);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusBar )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBool);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StatusBar )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Value);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusText )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *StatusText);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StatusText )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [in] */ BSTR StatusText);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ToolBar )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Value);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ToolBar )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [in] */ int Value);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MenuBar )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Value);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MenuBar )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Value);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullScreen )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbFullScreen);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FullScreen )( 
            IWebBrowserApp __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bFullScreen);
        
        END_INTERFACE
    } IWebBrowserAppVtbl;

    interface IWebBrowserApp
    {
        CONST_VTBL struct IWebBrowserAppVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebBrowserApp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebBrowserApp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebBrowserApp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebBrowserApp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebBrowserApp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebBrowserApp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebBrowserApp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebBrowserApp_GoBack(This)	\
    (This)->lpVtbl -> GoBack(This)

#define IWebBrowserApp_GoForward(This)	\
    (This)->lpVtbl -> GoForward(This)

#define IWebBrowserApp_GoHome(This)	\
    (This)->lpVtbl -> GoHome(This)

#define IWebBrowserApp_GoSearch(This)	\
    (This)->lpVtbl -> GoSearch(This)

#define IWebBrowserApp_Navigate(This,URL,Flags,TargetFrameName,PostData,Headers)	\
    (This)->lpVtbl -> Navigate(This,URL,Flags,TargetFrameName,PostData,Headers)

#define IWebBrowserApp_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IWebBrowserApp_Refresh2(This,Level)	\
    (This)->lpVtbl -> Refresh2(This,Level)

#define IWebBrowserApp_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IWebBrowserApp_get_Application(This,ppDisp)	\
    (This)->lpVtbl -> get_Application(This,ppDisp)

#define IWebBrowserApp_get_Parent(This,ppDisp)	\
    (This)->lpVtbl -> get_Parent(This,ppDisp)

#define IWebBrowserApp_get_Container(This,ppDisp)	\
    (This)->lpVtbl -> get_Container(This,ppDisp)

#define IWebBrowserApp_get_Document(This,ppDisp)	\
    (This)->lpVtbl -> get_Document(This,ppDisp)

#define IWebBrowserApp_get_TopLevelContainer(This,pBool)	\
    (This)->lpVtbl -> get_TopLevelContainer(This,pBool)

#define IWebBrowserApp_get_Type(This,Type)	\
    (This)->lpVtbl -> get_Type(This,Type)

#define IWebBrowserApp_get_Left(This,pl)	\
    (This)->lpVtbl -> get_Left(This,pl)

#define IWebBrowserApp_put_Left(This,Left)	\
    (This)->lpVtbl -> put_Left(This,Left)

#define IWebBrowserApp_get_Top(This,pl)	\
    (This)->lpVtbl -> get_Top(This,pl)

#define IWebBrowserApp_put_Top(This,Top)	\
    (This)->lpVtbl -> put_Top(This,Top)

#define IWebBrowserApp_get_Width(This,pl)	\
    (This)->lpVtbl -> get_Width(This,pl)

#define IWebBrowserApp_put_Width(This,Width)	\
    (This)->lpVtbl -> put_Width(This,Width)

#define IWebBrowserApp_get_Height(This,pl)	\
    (This)->lpVtbl -> get_Height(This,pl)

#define IWebBrowserApp_put_Height(This,Height)	\
    (This)->lpVtbl -> put_Height(This,Height)

#define IWebBrowserApp_get_LocationName(This,LocationName)	\
    (This)->lpVtbl -> get_LocationName(This,LocationName)

#define IWebBrowserApp_get_LocationURL(This,LocationURL)	\
    (This)->lpVtbl -> get_LocationURL(This,LocationURL)

#define IWebBrowserApp_get_Busy(This,pBool)	\
    (This)->lpVtbl -> get_Busy(This,pBool)


#define IWebBrowserApp_Quit(This)	\
    (This)->lpVtbl -> Quit(This)

#define IWebBrowserApp_ClientToWindow(This,pcx,pcy)	\
    (This)->lpVtbl -> ClientToWindow(This,pcx,pcy)

#define IWebBrowserApp_PutProperty(This,Property,vtValue)	\
    (This)->lpVtbl -> PutProperty(This,Property,vtValue)

#define IWebBrowserApp_GetProperty(This,Property,pvtValue)	\
    (This)->lpVtbl -> GetProperty(This,Property,pvtValue)

#define IWebBrowserApp_get_Name(This,Name)	\
    (This)->lpVtbl -> get_Name(This,Name)

#define IWebBrowserApp_get_HWND(This,pHWND)	\
    (This)->lpVtbl -> get_HWND(This,pHWND)

#define IWebBrowserApp_get_FullName(This,FullName)	\
    (This)->lpVtbl -> get_FullName(This,FullName)

#define IWebBrowserApp_get_Path(This,Path)	\
    (This)->lpVtbl -> get_Path(This,Path)

#define IWebBrowserApp_get_Visible(This,pBool)	\
    (This)->lpVtbl -> get_Visible(This,pBool)

#define IWebBrowserApp_put_Visible(This,Value)	\
    (This)->lpVtbl -> put_Visible(This,Value)

#define IWebBrowserApp_get_StatusBar(This,pBool)	\
    (This)->lpVtbl -> get_StatusBar(This,pBool)

#define IWebBrowserApp_put_StatusBar(This,Value)	\
    (This)->lpVtbl -> put_StatusBar(This,Value)

#define IWebBrowserApp_get_StatusText(This,StatusText)	\
    (This)->lpVtbl -> get_StatusText(This,StatusText)

#define IWebBrowserApp_put_StatusText(This,StatusText)	\
    (This)->lpVtbl -> put_StatusText(This,StatusText)

#define IWebBrowserApp_get_ToolBar(This,Value)	\
    (This)->lpVtbl -> get_ToolBar(This,Value)

#define IWebBrowserApp_put_ToolBar(This,Value)	\
    (This)->lpVtbl -> put_ToolBar(This,Value)

#define IWebBrowserApp_get_MenuBar(This,Value)	\
    (This)->lpVtbl -> get_MenuBar(This,Value)

#define IWebBrowserApp_put_MenuBar(This,Value)	\
    (This)->lpVtbl -> put_MenuBar(This,Value)

#define IWebBrowserApp_get_FullScreen(This,pbFullScreen)	\
    (This)->lpVtbl -> get_FullScreen(This,pbFullScreen)

#define IWebBrowserApp_put_FullScreen(This,bFullScreen)	\
    (This)->lpVtbl -> put_FullScreen(This,bFullScreen)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebBrowserApp_Quit_Proxy( 
    IWebBrowserApp __RPC_FAR * This);


void __RPC_STUB IWebBrowserApp_Quit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebBrowserApp_ClientToWindow_Proxy( 
    IWebBrowserApp __RPC_FAR * This,
    /* [out][in] */ int __RPC_FAR *pcx,
    /* [out][in] */ int __RPC_FAR *pcy);


void __RPC_STUB IWebBrowserApp_ClientToWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebBrowserApp_PutProperty_Proxy( 
    IWebBrowserApp __RPC_FAR * This,
    /* [in] */ BSTR Property,
    /* [in] */ VARIANT vtValue);


void __RPC_STUB IWebBrowserApp_PutProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebBrowserApp_GetProperty_Proxy( 
    IWebBrowserApp __RPC_FAR * This,
    /* [in] */ BSTR Property,
    /* [retval][out] */ VARIANT __RPC_FAR *pvtValue);


void __RPC_STUB IWebBrowserApp_GetProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowserApp_get_Name_Proxy( 
    IWebBrowserApp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Name);


void __RPC_STUB IWebBrowserApp_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowserApp_get_HWND_Proxy( 
    IWebBrowserApp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pHWND);


void __RPC_STUB IWebBrowserApp_get_HWND_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowserApp_get_FullName_Proxy( 
    IWebBrowserApp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *FullName);


void __RPC_STUB IWebBrowserApp_get_FullName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowserApp_get_Path_Proxy( 
    IWebBrowserApp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *Path);


void __RPC_STUB IWebBrowserApp_get_Path_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowserApp_get_Visible_Proxy( 
    IWebBrowserApp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBool);


void __RPC_STUB IWebBrowserApp_get_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IWebBrowserApp_put_Visible_Proxy( 
    IWebBrowserApp __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Value);


void __RPC_STUB IWebBrowserApp_put_Visible_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowserApp_get_StatusBar_Proxy( 
    IWebBrowserApp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBool);


void __RPC_STUB IWebBrowserApp_get_StatusBar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IWebBrowserApp_put_StatusBar_Proxy( 
    IWebBrowserApp __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Value);


void __RPC_STUB IWebBrowserApp_put_StatusBar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowserApp_get_StatusText_Proxy( 
    IWebBrowserApp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *StatusText);


void __RPC_STUB IWebBrowserApp_get_StatusText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IWebBrowserApp_put_StatusText_Proxy( 
    IWebBrowserApp __RPC_FAR * This,
    /* [in] */ BSTR StatusText);


void __RPC_STUB IWebBrowserApp_put_StatusText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowserApp_get_ToolBar_Proxy( 
    IWebBrowserApp __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *Value);


void __RPC_STUB IWebBrowserApp_get_ToolBar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IWebBrowserApp_put_ToolBar_Proxy( 
    IWebBrowserApp __RPC_FAR * This,
    /* [in] */ int Value);


void __RPC_STUB IWebBrowserApp_put_ToolBar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowserApp_get_MenuBar_Proxy( 
    IWebBrowserApp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Value);


void __RPC_STUB IWebBrowserApp_get_MenuBar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IWebBrowserApp_put_MenuBar_Proxy( 
    IWebBrowserApp __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Value);


void __RPC_STUB IWebBrowserApp_put_MenuBar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowserApp_get_FullScreen_Proxy( 
    IWebBrowserApp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbFullScreen);


void __RPC_STUB IWebBrowserApp_get_FullScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IWebBrowserApp_put_FullScreen_Proxy( 
    IWebBrowserApp __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bFullScreen);


void __RPC_STUB IWebBrowserApp_put_FullScreen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebBrowserApp_INTERFACE_DEFINED__ */


#ifndef __IWebBrowser2_INTERFACE_DEFINED__
#define __IWebBrowser2_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IWebBrowser2
 * at Mon Nov 17 12:05:03 1997
 * using MIDL 3.02.88
 ****************************************/
/* [object][dual][oleautomation][hidden][helpcontext][helpstring][uuid] */ 



EXTERN_C const IID IID_IWebBrowser2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("D30C1661-CDAF-11d0-8A3E-00C04FC9E26E")
    IWebBrowser2 : public IWebBrowserApp
    {
    public:
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Navigate2( 
            /* [in] */ VARIANT __RPC_FAR *URL,
            /* [optional][in] */ VARIANT __RPC_FAR *Flags,
            /* [optional][in] */ VARIANT __RPC_FAR *TargetFrameName,
            /* [optional][in] */ VARIANT __RPC_FAR *PostData,
            /* [optional][in] */ VARIANT __RPC_FAR *Headers) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE QueryStatusWB( 
            /* [in] */ OLECMDID cmdID,
            /* [retval][out] */ OLECMDF __RPC_FAR *pcmdf) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ExecWB( 
            /* [in] */ OLECMDID cmdID,
            /* [in] */ OLECMDEXECOPT cmdexecopt,
            /* [optional][in] */ VARIANT __RPC_FAR *pvaIn,
            /* [optional][in][out] */ VARIANT __RPC_FAR *pvaOut) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowBrowserBar( 
            /* [in] */ VARIANT __RPC_FAR *pvaClsid,
            /* [optional][in] */ VARIANT __RPC_FAR *pvarShow,
            /* [optional][in] */ VARIANT __RPC_FAR *pvarSize) = 0;
        
        virtual /* [bindable][propget][id] */ HRESULT STDMETHODCALLTYPE get_ReadyState( 
            /* [out][retval] */ READYSTATE __RPC_FAR *plReadyState) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Offline( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbOffline) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Offline( 
            /* [in] */ VARIANT_BOOL bOffline) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Silent( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbSilent) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Silent( 
            /* [in] */ VARIANT_BOOL bSilent) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_RegisterAsBrowser( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRegister) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_RegisterAsBrowser( 
            /* [in] */ VARIANT_BOOL bRegister) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_RegisterAsDropTarget( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRegister) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_RegisterAsDropTarget( 
            /* [in] */ VARIANT_BOOL bRegister) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_TheaterMode( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRegister) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_TheaterMode( 
            /* [in] */ VARIANT_BOOL bRegister) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_AddressBar( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Value) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_AddressBar( 
            /* [in] */ VARIANT_BOOL Value) = 0;
        
        virtual /* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Resizable( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Value) = 0;
        
        virtual /* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Resizable( 
            /* [in] */ VARIANT_BOOL Value) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWebBrowser2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWebBrowser2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWebBrowser2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GoBack )( 
            IWebBrowser2 __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GoForward )( 
            IWebBrowser2 __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GoHome )( 
            IWebBrowser2 __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GoSearch )( 
            IWebBrowser2 __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Navigate )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ BSTR URL,
            /* [optional][in] */ VARIANT __RPC_FAR *Flags,
            /* [optional][in] */ VARIANT __RPC_FAR *TargetFrameName,
            /* [optional][in] */ VARIANT __RPC_FAR *PostData,
            /* [optional][in] */ VARIANT __RPC_FAR *Headers);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IWebBrowser2 __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh2 )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [optional][in] */ VARIANT __RPC_FAR *Level);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IWebBrowser2 __RPC_FAR * This);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Container )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Document )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TopLevelContainer )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBool);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Type);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Left )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pl);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Left )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ long Left);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Top )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pl);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Top )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ long Top);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Width )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pl);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Width )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ long Width);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Height )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pl);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Height )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ long Height);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocationName )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *LocationName);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocationURL )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *LocationURL);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Busy )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBool);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Quit )( 
            IWebBrowser2 __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClientToWindow )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [out][in] */ int __RPC_FAR *pcx,
            /* [out][in] */ int __RPC_FAR *pcy);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutProperty )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ BSTR Property,
            /* [in] */ VARIANT vtValue);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProperty )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ BSTR Property,
            /* [retval][out] */ VARIANT __RPC_FAR *pvtValue);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Name);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HWND )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pHWND);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullName )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *FullName);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Path )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *Path);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Visible )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBool);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Visible )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Value);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusBar )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBool);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StatusBar )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Value);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StatusText )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *StatusText);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StatusText )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ BSTR StatusText);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ToolBar )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *Value);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ToolBar )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ int Value);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MenuBar )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Value);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MenuBar )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Value);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FullScreen )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbFullScreen);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FullScreen )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bFullScreen);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Navigate2 )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *URL,
            /* [optional][in] */ VARIANT __RPC_FAR *Flags,
            /* [optional][in] */ VARIANT __RPC_FAR *TargetFrameName,
            /* [optional][in] */ VARIANT __RPC_FAR *PostData,
            /* [optional][in] */ VARIANT __RPC_FAR *Headers);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryStatusWB )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ OLECMDID cmdID,
            /* [retval][out] */ OLECMDF __RPC_FAR *pcmdf);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExecWB )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ OLECMDID cmdID,
            /* [in] */ OLECMDEXECOPT cmdexecopt,
            /* [optional][in] */ VARIANT __RPC_FAR *pvaIn,
            /* [optional][in][out] */ VARIANT __RPC_FAR *pvaOut);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowBrowserBar )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *pvaClsid,
            /* [optional][in] */ VARIANT __RPC_FAR *pvarShow,
            /* [optional][in] */ VARIANT __RPC_FAR *pvarSize);
        
        /* [bindable][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReadyState )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [out][retval] */ READYSTATE __RPC_FAR *plReadyState);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Offline )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbOffline);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Offline )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bOffline);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Silent )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbSilent);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Silent )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bSilent);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RegisterAsBrowser )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRegister);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RegisterAsBrowser )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bRegister);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RegisterAsDropTarget )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRegister);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RegisterAsDropTarget )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bRegister);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TheaterMode )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRegister);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TheaterMode )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL bRegister);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AddressBar )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Value);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AddressBar )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Value);
        
        /* [helpcontext][helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Resizable )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Value);
        
        /* [helpcontext][helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Resizable )( 
            IWebBrowser2 __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL Value);
        
        END_INTERFACE
    } IWebBrowser2Vtbl;

    interface IWebBrowser2
    {
        CONST_VTBL struct IWebBrowser2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWebBrowser2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWebBrowser2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWebBrowser2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWebBrowser2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWebBrowser2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWebBrowser2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWebBrowser2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWebBrowser2_GoBack(This)	\
    (This)->lpVtbl -> GoBack(This)

#define IWebBrowser2_GoForward(This)	\
    (This)->lpVtbl -> GoForward(This)

#define IWebBrowser2_GoHome(This)	\
    (This)->lpVtbl -> GoHome(This)

#define IWebBrowser2_GoSearch(This)	\
    (This)->lpVtbl -> GoSearch(This)

#define IWebBrowser2_Navigate(This,URL,Flags,TargetFrameName,PostData,Headers)	\
    (This)->lpVtbl -> Navigate(This,URL,Flags,TargetFrameName,PostData,Headers)

#define IWebBrowser2_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IWebBrowser2_Refresh2(This,Level)	\
    (This)->lpVtbl -> Refresh2(This,Level)

#define IWebBrowser2_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IWebBrowser2_get_Application(This,ppDisp)	\
    (This)->lpVtbl -> get_Application(This,ppDisp)

#define IWebBrowser2_get_Parent(This,ppDisp)	\
    (This)->lpVtbl -> get_Parent(This,ppDisp)

#define IWebBrowser2_get_Container(This,ppDisp)	\
    (This)->lpVtbl -> get_Container(This,ppDisp)

#define IWebBrowser2_get_Document(This,ppDisp)	\
    (This)->lpVtbl -> get_Document(This,ppDisp)

#define IWebBrowser2_get_TopLevelContainer(This,pBool)	\
    (This)->lpVtbl -> get_TopLevelContainer(This,pBool)

#define IWebBrowser2_get_Type(This,Type)	\
    (This)->lpVtbl -> get_Type(This,Type)

#define IWebBrowser2_get_Left(This,pl)	\
    (This)->lpVtbl -> get_Left(This,pl)

#define IWebBrowser2_put_Left(This,Left)	\
    (This)->lpVtbl -> put_Left(This,Left)

#define IWebBrowser2_get_Top(This,pl)	\
    (This)->lpVtbl -> get_Top(This,pl)

#define IWebBrowser2_put_Top(This,Top)	\
    (This)->lpVtbl -> put_Top(This,Top)

#define IWebBrowser2_get_Width(This,pl)	\
    (This)->lpVtbl -> get_Width(This,pl)

#define IWebBrowser2_put_Width(This,Width)	\
    (This)->lpVtbl -> put_Width(This,Width)

#define IWebBrowser2_get_Height(This,pl)	\
    (This)->lpVtbl -> get_Height(This,pl)

#define IWebBrowser2_put_Height(This,Height)	\
    (This)->lpVtbl -> put_Height(This,Height)

#define IWebBrowser2_get_LocationName(This,LocationName)	\
    (This)->lpVtbl -> get_LocationName(This,LocationName)

#define IWebBrowser2_get_LocationURL(This,LocationURL)	\
    (This)->lpVtbl -> get_LocationURL(This,LocationURL)

#define IWebBrowser2_get_Busy(This,pBool)	\
    (This)->lpVtbl -> get_Busy(This,pBool)


#define IWebBrowser2_Quit(This)	\
    (This)->lpVtbl -> Quit(This)

#define IWebBrowser2_ClientToWindow(This,pcx,pcy)	\
    (This)->lpVtbl -> ClientToWindow(This,pcx,pcy)

#define IWebBrowser2_PutProperty(This,Property,vtValue)	\
    (This)->lpVtbl -> PutProperty(This,Property,vtValue)

#define IWebBrowser2_GetProperty(This,Property,pvtValue)	\
    (This)->lpVtbl -> GetProperty(This,Property,pvtValue)

#define IWebBrowser2_get_Name(This,Name)	\
    (This)->lpVtbl -> get_Name(This,Name)

#define IWebBrowser2_get_HWND(This,pHWND)	\
    (This)->lpVtbl -> get_HWND(This,pHWND)

#define IWebBrowser2_get_FullName(This,FullName)	\
    (This)->lpVtbl -> get_FullName(This,FullName)

#define IWebBrowser2_get_Path(This,Path)	\
    (This)->lpVtbl -> get_Path(This,Path)

#define IWebBrowser2_get_Visible(This,pBool)	\
    (This)->lpVtbl -> get_Visible(This,pBool)

#define IWebBrowser2_put_Visible(This,Value)	\
    (This)->lpVtbl -> put_Visible(This,Value)

#define IWebBrowser2_get_StatusBar(This,pBool)	\
    (This)->lpVtbl -> get_StatusBar(This,pBool)

#define IWebBrowser2_put_StatusBar(This,Value)	\
    (This)->lpVtbl -> put_StatusBar(This,Value)

#define IWebBrowser2_get_StatusText(This,StatusText)	\
    (This)->lpVtbl -> get_StatusText(This,StatusText)

#define IWebBrowser2_put_StatusText(This,StatusText)	\
    (This)->lpVtbl -> put_StatusText(This,StatusText)

#define IWebBrowser2_get_ToolBar(This,Value)	\
    (This)->lpVtbl -> get_ToolBar(This,Value)

#define IWebBrowser2_put_ToolBar(This,Value)	\
    (This)->lpVtbl -> put_ToolBar(This,Value)

#define IWebBrowser2_get_MenuBar(This,Value)	\
    (This)->lpVtbl -> get_MenuBar(This,Value)

#define IWebBrowser2_put_MenuBar(This,Value)	\
    (This)->lpVtbl -> put_MenuBar(This,Value)

#define IWebBrowser2_get_FullScreen(This,pbFullScreen)	\
    (This)->lpVtbl -> get_FullScreen(This,pbFullScreen)

#define IWebBrowser2_put_FullScreen(This,bFullScreen)	\
    (This)->lpVtbl -> put_FullScreen(This,bFullScreen)


#define IWebBrowser2_Navigate2(This,URL,Flags,TargetFrameName,PostData,Headers)	\
    (This)->lpVtbl -> Navigate2(This,URL,Flags,TargetFrameName,PostData,Headers)

#define IWebBrowser2_QueryStatusWB(This,cmdID,pcmdf)	\
    (This)->lpVtbl -> QueryStatusWB(This,cmdID,pcmdf)

#define IWebBrowser2_ExecWB(This,cmdID,cmdexecopt,pvaIn,pvaOut)	\
    (This)->lpVtbl -> ExecWB(This,cmdID,cmdexecopt,pvaIn,pvaOut)

#define IWebBrowser2_ShowBrowserBar(This,pvaClsid,pvarShow,pvarSize)	\
    (This)->lpVtbl -> ShowBrowserBar(This,pvaClsid,pvarShow,pvarSize)

#define IWebBrowser2_get_ReadyState(This,plReadyState)	\
    (This)->lpVtbl -> get_ReadyState(This,plReadyState)

#define IWebBrowser2_get_Offline(This,pbOffline)	\
    (This)->lpVtbl -> get_Offline(This,pbOffline)

#define IWebBrowser2_put_Offline(This,bOffline)	\
    (This)->lpVtbl -> put_Offline(This,bOffline)

#define IWebBrowser2_get_Silent(This,pbSilent)	\
    (This)->lpVtbl -> get_Silent(This,pbSilent)

#define IWebBrowser2_put_Silent(This,bSilent)	\
    (This)->lpVtbl -> put_Silent(This,bSilent)

#define IWebBrowser2_get_RegisterAsBrowser(This,pbRegister)	\
    (This)->lpVtbl -> get_RegisterAsBrowser(This,pbRegister)

#define IWebBrowser2_put_RegisterAsBrowser(This,bRegister)	\
    (This)->lpVtbl -> put_RegisterAsBrowser(This,bRegister)

#define IWebBrowser2_get_RegisterAsDropTarget(This,pbRegister)	\
    (This)->lpVtbl -> get_RegisterAsDropTarget(This,pbRegister)

#define IWebBrowser2_put_RegisterAsDropTarget(This,bRegister)	\
    (This)->lpVtbl -> put_RegisterAsDropTarget(This,bRegister)

#define IWebBrowser2_get_TheaterMode(This,pbRegister)	\
    (This)->lpVtbl -> get_TheaterMode(This,pbRegister)

#define IWebBrowser2_put_TheaterMode(This,bRegister)	\
    (This)->lpVtbl -> put_TheaterMode(This,bRegister)

#define IWebBrowser2_get_AddressBar(This,Value)	\
    (This)->lpVtbl -> get_AddressBar(This,Value)

#define IWebBrowser2_put_AddressBar(This,Value)	\
    (This)->lpVtbl -> put_AddressBar(This,Value)

#define IWebBrowser2_get_Resizable(This,Value)	\
    (This)->lpVtbl -> get_Resizable(This,Value)

#define IWebBrowser2_put_Resizable(This,Value)	\
    (This)->lpVtbl -> put_Resizable(This,Value)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser2_Navigate2_Proxy( 
    IWebBrowser2 __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *URL,
    /* [optional][in] */ VARIANT __RPC_FAR *Flags,
    /* [optional][in] */ VARIANT __RPC_FAR *TargetFrameName,
    /* [optional][in] */ VARIANT __RPC_FAR *PostData,
    /* [optional][in] */ VARIANT __RPC_FAR *Headers);


void __RPC_STUB IWebBrowser2_Navigate2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser2_QueryStatusWB_Proxy( 
    IWebBrowser2 __RPC_FAR * This,
    /* [in] */ OLECMDID cmdID,
    /* [retval][out] */ OLECMDF __RPC_FAR *pcmdf);


void __RPC_STUB IWebBrowser2_QueryStatusWB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser2_ExecWB_Proxy( 
    IWebBrowser2 __RPC_FAR * This,
    /* [in] */ OLECMDID cmdID,
    /* [in] */ OLECMDEXECOPT cmdexecopt,
    /* [optional][in] */ VARIANT __RPC_FAR *pvaIn,
    /* [optional][in][out] */ VARIANT __RPC_FAR *pvaOut);


void __RPC_STUB IWebBrowser2_ExecWB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser2_ShowBrowserBar_Proxy( 
    IWebBrowser2 __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *pvaClsid,
    /* [optional][in] */ VARIANT __RPC_FAR *pvarShow,
    /* [optional][in] */ VARIANT __RPC_FAR *pvarSize);


void __RPC_STUB IWebBrowser2_ShowBrowserBar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [bindable][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser2_get_ReadyState_Proxy( 
    IWebBrowser2 __RPC_FAR * This,
    /* [out][retval] */ READYSTATE __RPC_FAR *plReadyState);


void __RPC_STUB IWebBrowser2_get_ReadyState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser2_get_Offline_Proxy( 
    IWebBrowser2 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbOffline);


void __RPC_STUB IWebBrowser2_get_Offline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser2_put_Offline_Proxy( 
    IWebBrowser2 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bOffline);


void __RPC_STUB IWebBrowser2_put_Offline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser2_get_Silent_Proxy( 
    IWebBrowser2 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbSilent);


void __RPC_STUB IWebBrowser2_get_Silent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser2_put_Silent_Proxy( 
    IWebBrowser2 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bSilent);


void __RPC_STUB IWebBrowser2_put_Silent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser2_get_RegisterAsBrowser_Proxy( 
    IWebBrowser2 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRegister);


void __RPC_STUB IWebBrowser2_get_RegisterAsBrowser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser2_put_RegisterAsBrowser_Proxy( 
    IWebBrowser2 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bRegister);


void __RPC_STUB IWebBrowser2_put_RegisterAsBrowser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser2_get_RegisterAsDropTarget_Proxy( 
    IWebBrowser2 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRegister);


void __RPC_STUB IWebBrowser2_get_RegisterAsDropTarget_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser2_put_RegisterAsDropTarget_Proxy( 
    IWebBrowser2 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bRegister);


void __RPC_STUB IWebBrowser2_put_RegisterAsDropTarget_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser2_get_TheaterMode_Proxy( 
    IWebBrowser2 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pbRegister);


void __RPC_STUB IWebBrowser2_get_TheaterMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser2_put_TheaterMode_Proxy( 
    IWebBrowser2 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL bRegister);


void __RPC_STUB IWebBrowser2_put_TheaterMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser2_get_AddressBar_Proxy( 
    IWebBrowser2 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Value);


void __RPC_STUB IWebBrowser2_get_AddressBar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser2_put_AddressBar_Proxy( 
    IWebBrowser2 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Value);


void __RPC_STUB IWebBrowser2_put_AddressBar_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser2_get_Resizable_Proxy( 
    IWebBrowser2 __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *Value);


void __RPC_STUB IWebBrowser2_get_Resizable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE IWebBrowser2_put_Resizable_Proxy( 
    IWebBrowser2 __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL Value);


void __RPC_STUB IWebBrowser2_put_Resizable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWebBrowser2_INTERFACE_DEFINED__ */


#ifndef __DWebBrowserEvents2_DISPINTERFACE_DEFINED__
#define __DWebBrowserEvents2_DISPINTERFACE_DEFINED__

/****************************************
 * Generated header for dispinterface: DWebBrowserEvents2
 * at Mon Nov 17 12:05:03 1997
 * using MIDL 3.02.88
 ****************************************/
/* [hidden][helpstring][uuid] */ 



EXTERN_C const IID DIID_DWebBrowserEvents2;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface DECLSPEC_UUID("34A715A0-6587-11D0-924A-0020AFC7AC4D")
    DWebBrowserEvents2 : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct DWebBrowserEvents2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DWebBrowserEvents2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DWebBrowserEvents2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DWebBrowserEvents2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            DWebBrowserEvents2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            DWebBrowserEvents2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            DWebBrowserEvents2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            DWebBrowserEvents2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } DWebBrowserEvents2Vtbl;

    interface DWebBrowserEvents2
    {
        CONST_VTBL struct DWebBrowserEvents2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DWebBrowserEvents2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DWebBrowserEvents2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DWebBrowserEvents2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DWebBrowserEvents2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define DWebBrowserEvents2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define DWebBrowserEvents2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define DWebBrowserEvents2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __DWebBrowserEvents2_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WebBrowser_V1;

#ifdef __cplusplus

class DECLSPEC_UUID("EAB22AC3-30C1-11CF-A7EB-0000C05BAE0B")
WebBrowser_V1;
#endif

EXTERN_C const CLSID CLSID_WebBrowser;

#ifdef __cplusplus

class DECLSPEC_UUID("8856F961-340A-11D0-A96B-00C04FD705A2")
WebBrowser;
#endif

EXTERN_C const CLSID CLSID_InternetExplorer;

#ifdef __cplusplus

class DECLSPEC_UUID("0002DF01-0000-0000-C000-000000000046")
InternetExplorer;
#endif

#ifndef __IFolderViewOC_INTERFACE_DEFINED__
#define __IFolderViewOC_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IFolderViewOC
 * at Mon Nov 17 12:05:03 1997
 * using MIDL 3.02.88
 ****************************************/
/* [object][dual][oleautomation][hidden][helpcontext][helpstring][uuid] */ 



EXTERN_C const IID IID_IFolderViewOC;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("9BA05970-F6A8-11CF-A442-00A0C90A8F39")
    IFolderViewOC : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE SetFolderView( 
            /* [in] */ IDispatch __RPC_FAR *pdisp) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IFolderViewOCVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFolderViewOC __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFolderViewOC __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFolderViewOC __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IFolderViewOC __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IFolderViewOC __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IFolderViewOC __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IFolderViewOC __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFolderView )( 
            IFolderViewOC __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pdisp);
        
        END_INTERFACE
    } IFolderViewOCVtbl;

    interface IFolderViewOC
    {
        CONST_VTBL struct IFolderViewOCVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFolderViewOC_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFolderViewOC_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFolderViewOC_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFolderViewOC_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IFolderViewOC_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IFolderViewOC_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IFolderViewOC_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IFolderViewOC_SetFolderView(This,pdisp)	\
    (This)->lpVtbl -> SetFolderView(This,pdisp)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring] */ HRESULT STDMETHODCALLTYPE IFolderViewOC_SetFolderView_Proxy( 
    IFolderViewOC __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pdisp);


void __RPC_STUB IFolderViewOC_SetFolderView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFolderViewOC_INTERFACE_DEFINED__ */


#ifndef __DShellFolderViewEvents_DISPINTERFACE_DEFINED__
#define __DShellFolderViewEvents_DISPINTERFACE_DEFINED__

/****************************************
 * Generated header for dispinterface: DShellFolderViewEvents
 * at Mon Nov 17 12:05:03 1997
 * using MIDL 3.02.88
 ****************************************/
/* [helpstring][uuid] */ 



EXTERN_C const IID DIID_DShellFolderViewEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface DECLSPEC_UUID("62112AA2-EBE4-11cf-A5FB-0020AFE7292D")
    DShellFolderViewEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct DShellFolderViewEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DShellFolderViewEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DShellFolderViewEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DShellFolderViewEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            DShellFolderViewEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            DShellFolderViewEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            DShellFolderViewEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            DShellFolderViewEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } DShellFolderViewEventsVtbl;

    interface DShellFolderViewEvents
    {
        CONST_VTBL struct DShellFolderViewEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DShellFolderViewEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DShellFolderViewEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DShellFolderViewEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DShellFolderViewEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define DShellFolderViewEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define DShellFolderViewEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define DShellFolderViewEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __DShellFolderViewEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ShellFolderViewOC;

#ifdef __cplusplus

class DECLSPEC_UUID("9BA05971-F6A8-11CF-A442-00A0C90A8F39")
ShellFolderViewOC;
#endif

#ifndef __DShellWindowsEvents_DISPINTERFACE_DEFINED__
#define __DShellWindowsEvents_DISPINTERFACE_DEFINED__

/****************************************
 * Generated header for dispinterface: DShellWindowsEvents
 * at Mon Nov 17 12:05:03 1997
 * using MIDL 3.02.88
 ****************************************/
/* [helpstring][uuid] */ 



EXTERN_C const IID DIID_DShellWindowsEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    interface DECLSPEC_UUID("fe4106e0-399a-11d0-a48c-00a0c90a8f39")
    DShellWindowsEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct DShellWindowsEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            DShellWindowsEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            DShellWindowsEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            DShellWindowsEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            DShellWindowsEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            DShellWindowsEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            DShellWindowsEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            DShellWindowsEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } DShellWindowsEventsVtbl;

    interface DShellWindowsEvents
    {
        CONST_VTBL struct DShellWindowsEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define DShellWindowsEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define DShellWindowsEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define DShellWindowsEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define DShellWindowsEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define DShellWindowsEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define DShellWindowsEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define DShellWindowsEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __DShellWindowsEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IShellWindows_INTERFACE_DEFINED__
#define __IShellWindows_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IShellWindows
 * at Mon Nov 17 12:05:03 1997
 * using MIDL 3.02.88
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



EXTERN_C const IID IID_IShellWindows;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("85CB6900-4D95-11CF-960C-0080C7F4EE85")
    IShellWindows : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [optional][in] */ VARIANT index,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Folder) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE _NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk) = 0;
        
        virtual /* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE Register( 
            /* [in] */ IDispatch __RPC_FAR *pid,
            /* [in] */ long hwnd,
            /* [in] */ int swClass,
            /* [out] */ long __RPC_FAR *plCookie) = 0;
        
        virtual /* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE RegisterPending( 
            /* [in] */ long lThreadId,
            /* [in] */ VARIANT __RPC_FAR *pvarloc,
            /* [in] */ VARIANT __RPC_FAR *pvarlocRoot,
            /* [in] */ int swClass,
            /* [out] */ long __RPC_FAR *plCookie) = 0;
        
        virtual /* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE Revoke( 
            /* [in] */ long lCookie) = 0;
        
        virtual /* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE OnNavigate( 
            /* [in] */ long lCookie,
            /* [in] */ VARIANT __RPC_FAR *pvarLoc) = 0;
        
        virtual /* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE OnActivated( 
            /* [in] */ long lCookie,
            /* [in] */ VARIANT_BOOL fActive) = 0;
        
        virtual /* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE FindWindow( 
            /* [in] */ VARIANT __RPC_FAR *pvarLoc,
            /* [in] */ VARIANT __RPC_FAR *pvarLocRoot,
            /* [in] */ int swClass,
            /* [out] */ long __RPC_FAR *phwnd,
            /* [in] */ int swfwOptions,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispOut) = 0;
        
        virtual /* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE OnCreated( 
            /* [in] */ long lCookie,
            /* [in] */ IUnknown __RPC_FAR *punk) = 0;
        
        virtual /* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE ProcessAttachDetach( 
            /* [in] */ VARIANT_BOOL fAttach) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellWindowsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IShellWindows __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IShellWindows __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IShellWindows __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IShellWindows __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IShellWindows __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IShellWindows __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IShellWindows __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IShellWindows __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IShellWindows __RPC_FAR * This,
            /* [optional][in] */ VARIANT index,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Folder);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_NewEnum )( 
            IShellWindows __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        /* [hidden][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Register )( 
            IShellWindows __RPC_FAR * This,
            /* [in] */ IDispatch __RPC_FAR *pid,
            /* [in] */ long hwnd,
            /* [in] */ int swClass,
            /* [out] */ long __RPC_FAR *plCookie);
        
        /* [hidden][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterPending )( 
            IShellWindows __RPC_FAR * This,
            /* [in] */ long lThreadId,
            /* [in] */ VARIANT __RPC_FAR *pvarloc,
            /* [in] */ VARIANT __RPC_FAR *pvarlocRoot,
            /* [in] */ int swClass,
            /* [out] */ long __RPC_FAR *plCookie);
        
        /* [hidden][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Revoke )( 
            IShellWindows __RPC_FAR * This,
            /* [in] */ long lCookie);
        
        /* [hidden][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnNavigate )( 
            IShellWindows __RPC_FAR * This,
            /* [in] */ long lCookie,
            /* [in] */ VARIANT __RPC_FAR *pvarLoc);
        
        /* [hidden][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnActivated )( 
            IShellWindows __RPC_FAR * This,
            /* [in] */ long lCookie,
            /* [in] */ VARIANT_BOOL fActive);
        
        /* [hidden][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindWindow )( 
            IShellWindows __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *pvarLoc,
            /* [in] */ VARIANT __RPC_FAR *pvarLocRoot,
            /* [in] */ int swClass,
            /* [out] */ long __RPC_FAR *phwnd,
            /* [in] */ int swfwOptions,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispOut);
        
        /* [hidden][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnCreated )( 
            IShellWindows __RPC_FAR * This,
            /* [in] */ long lCookie,
            /* [in] */ IUnknown __RPC_FAR *punk);
        
        /* [hidden][helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ProcessAttachDetach )( 
            IShellWindows __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL fAttach);
        
        END_INTERFACE
    } IShellWindowsVtbl;

    interface IShellWindows
    {
        CONST_VTBL struct IShellWindowsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellWindows_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IShellWindows_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IShellWindows_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IShellWindows_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IShellWindows_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IShellWindows_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IShellWindows_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IShellWindows_get_Count(This,Count)	\
    (This)->lpVtbl -> get_Count(This,Count)

#define IShellWindows_Item(This,index,Folder)	\
    (This)->lpVtbl -> Item(This,index,Folder)

#define IShellWindows__NewEnum(This,ppunk)	\
    (This)->lpVtbl -> _NewEnum(This,ppunk)

#define IShellWindows_Register(This,pid,hwnd,swClass,plCookie)	\
    (This)->lpVtbl -> Register(This,pid,hwnd,swClass,plCookie)

#define IShellWindows_RegisterPending(This,lThreadId,pvarloc,pvarlocRoot,swClass,plCookie)	\
    (This)->lpVtbl -> RegisterPending(This,lThreadId,pvarloc,pvarlocRoot,swClass,plCookie)

#define IShellWindows_Revoke(This,lCookie)	\
    (This)->lpVtbl -> Revoke(This,lCookie)

#define IShellWindows_OnNavigate(This,lCookie,pvarLoc)	\
    (This)->lpVtbl -> OnNavigate(This,lCookie,pvarLoc)

#define IShellWindows_OnActivated(This,lCookie,fActive)	\
    (This)->lpVtbl -> OnActivated(This,lCookie,fActive)

#define IShellWindows_FindWindow(This,pvarLoc,pvarLocRoot,swClass,phwnd,swfwOptions,ppdispOut)	\
    (This)->lpVtbl -> FindWindow(This,pvarLoc,pvarLocRoot,swClass,phwnd,swfwOptions,ppdispOut)

#define IShellWindows_OnCreated(This,lCookie,punk)	\
    (This)->lpVtbl -> OnCreated(This,lCookie,punk)

#define IShellWindows_ProcessAttachDetach(This,fAttach)	\
    (This)->lpVtbl -> ProcessAttachDetach(This,fAttach)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IShellWindows_get_Count_Proxy( 
    IShellWindows __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB IShellWindows_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IShellWindows_Item_Proxy( 
    IShellWindows __RPC_FAR * This,
    /* [optional][in] */ VARIANT index,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *Folder);


void __RPC_STUB IShellWindows_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IShellWindows__NewEnum_Proxy( 
    IShellWindows __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);


void __RPC_STUB IShellWindows__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE IShellWindows_Register_Proxy( 
    IShellWindows __RPC_FAR * This,
    /* [in] */ IDispatch __RPC_FAR *pid,
    /* [in] */ long hwnd,
    /* [in] */ int swClass,
    /* [out] */ long __RPC_FAR *plCookie);


void __RPC_STUB IShellWindows_Register_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE IShellWindows_RegisterPending_Proxy( 
    IShellWindows __RPC_FAR * This,
    /* [in] */ long lThreadId,
    /* [in] */ VARIANT __RPC_FAR *pvarloc,
    /* [in] */ VARIANT __RPC_FAR *pvarlocRoot,
    /* [in] */ int swClass,
    /* [out] */ long __RPC_FAR *plCookie);


void __RPC_STUB IShellWindows_RegisterPending_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE IShellWindows_Revoke_Proxy( 
    IShellWindows __RPC_FAR * This,
    /* [in] */ long lCookie);


void __RPC_STUB IShellWindows_Revoke_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE IShellWindows_OnNavigate_Proxy( 
    IShellWindows __RPC_FAR * This,
    /* [in] */ long lCookie,
    /* [in] */ VARIANT __RPC_FAR *pvarLoc);


void __RPC_STUB IShellWindows_OnNavigate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE IShellWindows_OnActivated_Proxy( 
    IShellWindows __RPC_FAR * This,
    /* [in] */ long lCookie,
    /* [in] */ VARIANT_BOOL fActive);


void __RPC_STUB IShellWindows_OnActivated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE IShellWindows_FindWindow_Proxy( 
    IShellWindows __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *pvarLoc,
    /* [in] */ VARIANT __RPC_FAR *pvarLocRoot,
    /* [in] */ int swClass,
    /* [out] */ long __RPC_FAR *phwnd,
    /* [in] */ int swfwOptions,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppdispOut);


void __RPC_STUB IShellWindows_FindWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE IShellWindows_OnCreated_Proxy( 
    IShellWindows __RPC_FAR * This,
    /* [in] */ long lCookie,
    /* [in] */ IUnknown __RPC_FAR *punk);


void __RPC_STUB IShellWindows_OnCreated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring] */ HRESULT STDMETHODCALLTYPE IShellWindows_ProcessAttachDetach_Proxy( 
    IShellWindows __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL fAttach);


void __RPC_STUB IShellWindows_ProcessAttachDetach_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellWindows_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ShellWindows;

#ifdef __cplusplus

class DECLSPEC_UUID("9BA05972-F6A8-11CF-A442-00A0C90A8F39")
ShellWindows;
#endif

#ifndef __IShellLinkDual_INTERFACE_DEFINED__
#define __IShellLinkDual_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IShellLinkDual
 * at Mon Nov 17 12:05:03 1997
 * using MIDL 3.02.88
 ****************************************/
/* [object][hidden][dual][oleautomation][helpstring][uuid] */ 



EXTERN_C const IID IID_IShellLinkDual;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("88A05C00-F000-11CE-8350-444553540000")
    IShellLinkDual : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Path( 
            /* [retval][out] */ BSTR __RPC_FAR *pbs) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Path( 
            /* [in] */ BSTR bs) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *pbs) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR bs) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_WorkingDirectory( 
            /* [retval][out] */ BSTR __RPC_FAR *pbs) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_WorkingDirectory( 
            /* [in] */ BSTR bs) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Arguments( 
            /* [retval][out] */ BSTR __RPC_FAR *pbs) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Arguments( 
            /* [in] */ BSTR bs) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Hotkey( 
            /* [retval][out] */ int __RPC_FAR *piHK) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Hotkey( 
            /* [in] */ int iHK) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ShowCommand( 
            /* [retval][out] */ int __RPC_FAR *piShowCommand) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ShowCommand( 
            /* [in] */ int iShowCommand) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Resolve( 
            /* [in] */ int fFlags) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetIconLocation( 
            /* [out] */ BSTR __RPC_FAR *pbs,
            /* [retval][out] */ int __RPC_FAR *piIcon) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetIconLocation( 
            /* [in] */ BSTR bs,
            /* [in] */ int iIcon) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [optional][in] */ VARIANT vWhere) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellLinkDualVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IShellLinkDual __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IShellLinkDual __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IShellLinkDual __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IShellLinkDual __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IShellLinkDual __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IShellLinkDual __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IShellLinkDual __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Path )( 
            IShellLinkDual __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbs);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Path )( 
            IShellLinkDual __RPC_FAR * This,
            /* [in] */ BSTR bs);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            IShellLinkDual __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbs);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Description )( 
            IShellLinkDual __RPC_FAR * This,
            /* [in] */ BSTR bs);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WorkingDirectory )( 
            IShellLinkDual __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbs);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WorkingDirectory )( 
            IShellLinkDual __RPC_FAR * This,
            /* [in] */ BSTR bs);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Arguments )( 
            IShellLinkDual __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbs);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Arguments )( 
            IShellLinkDual __RPC_FAR * This,
            /* [in] */ BSTR bs);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Hotkey )( 
            IShellLinkDual __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piHK);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Hotkey )( 
            IShellLinkDual __RPC_FAR * This,
            /* [in] */ int iHK);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ShowCommand )( 
            IShellLinkDual __RPC_FAR * This,
            /* [retval][out] */ int __RPC_FAR *piShowCommand);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ShowCommand )( 
            IShellLinkDual __RPC_FAR * This,
            /* [in] */ int iShowCommand);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Resolve )( 
            IShellLinkDual __RPC_FAR * This,
            /* [in] */ int fFlags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIconLocation )( 
            IShellLinkDual __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbs,
            /* [retval][out] */ int __RPC_FAR *piIcon);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetIconLocation )( 
            IShellLinkDual __RPC_FAR * This,
            /* [in] */ BSTR bs,
            /* [in] */ int iIcon);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Save )( 
            IShellLinkDual __RPC_FAR * This,
            /* [optional][in] */ VARIANT vWhere);
        
        END_INTERFACE
    } IShellLinkDualVtbl;

    interface IShellLinkDual
    {
        CONST_VTBL struct IShellLinkDualVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellLinkDual_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IShellLinkDual_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IShellLinkDual_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IShellLinkDual_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IShellLinkDual_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IShellLinkDual_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IShellLinkDual_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IShellLinkDual_get_Path(This,pbs)	\
    (This)->lpVtbl -> get_Path(This,pbs)

#define IShellLinkDual_put_Path(This,bs)	\
    (This)->lpVtbl -> put_Path(This,bs)

#define IShellLinkDual_get_Description(This,pbs)	\
    (This)->lpVtbl -> get_Description(This,pbs)

#define IShellLinkDual_put_Description(This,bs)	\
    (This)->lpVtbl -> put_Description(This,bs)

#define IShellLinkDual_get_WorkingDirectory(This,pbs)	\
    (This)->lpVtbl -> get_WorkingDirectory(This,pbs)

#define IShellLinkDual_put_WorkingDirectory(This,bs)	\
    (This)->lpVtbl -> put_WorkingDirectory(This,bs)

#define IShellLinkDual_get_Arguments(This,pbs)	\
    (This)->lpVtbl -> get_Arguments(This,pbs)

#define IShellLinkDual_put_Arguments(This,bs)	\
    (This)->lpVtbl -> put_Arguments(This,bs)

#define IShellLinkDual_get_Hotkey(This,piHK)	\
    (This)->lpVtbl -> get_Hotkey(This,piHK)

#define IShellLinkDual_put_Hotkey(This,iHK)	\
    (This)->lpVtbl -> put_Hotkey(This,iHK)

#define IShellLinkDual_get_ShowCommand(This,piShowCommand)	\
    (This)->lpVtbl -> get_ShowCommand(This,piShowCommand)

#define IShellLinkDual_put_ShowCommand(This,iShowCommand)	\
    (This)->lpVtbl -> put_ShowCommand(This,iShowCommand)

#define IShellLinkDual_Resolve(This,fFlags)	\
    (This)->lpVtbl -> Resolve(This,fFlags)

#define IShellLinkDual_GetIconLocation(This,pbs,piIcon)	\
    (This)->lpVtbl -> GetIconLocation(This,pbs,piIcon)

#define IShellLinkDual_SetIconLocation(This,bs,iIcon)	\
    (This)->lpVtbl -> SetIconLocation(This,bs,iIcon)

#define IShellLinkDual_Save(This,vWhere)	\
    (This)->lpVtbl -> Save(This,vWhere)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IShellLinkDual_get_Path_Proxy( 
    IShellLinkDual __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbs);


void __RPC_STUB IShellLinkDual_get_Path_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IShellLinkDual_put_Path_Proxy( 
    IShellLinkDual __RPC_FAR * This,
    /* [in] */ BSTR bs);


void __RPC_STUB IShellLinkDual_put_Path_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IShellLinkDual_get_Description_Proxy( 
    IShellLinkDual __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbs);


void __RPC_STUB IShellLinkDual_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IShellLinkDual_put_Description_Proxy( 
    IShellLinkDual __RPC_FAR * This,
    /* [in] */ BSTR bs);


void __RPC_STUB IShellLinkDual_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IShellLinkDual_get_WorkingDirectory_Proxy( 
    IShellLinkDual __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbs);


void __RPC_STUB IShellLinkDual_get_WorkingDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IShellLinkDual_put_WorkingDirectory_Proxy( 
    IShellLinkDual __RPC_FAR * This,
    /* [in] */ BSTR bs);


void __RPC_STUB IShellLinkDual_put_WorkingDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IShellLinkDual_get_Arguments_Proxy( 
    IShellLinkDual __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbs);


void __RPC_STUB IShellLinkDual_get_Arguments_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IShellLinkDual_put_Arguments_Proxy( 
    IShellLinkDual __RPC_FAR * This,
    /* [in] */ BSTR bs);


void __RPC_STUB IShellLinkDual_put_Arguments_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IShellLinkDual_get_Hotkey_Proxy( 
    IShellLinkDual __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *piHK);


void __RPC_STUB IShellLinkDual_get_Hotkey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IShellLinkDual_put_Hotkey_Proxy( 
    IShellLinkDual __RPC_FAR * This,
    /* [in] */ int iHK);


void __RPC_STUB IShellLinkDual_put_Hotkey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IShellLinkDual_get_ShowCommand_Proxy( 
    IShellLinkDual __RPC_FAR * This,
    /* [retval][out] */ int __RPC_FAR *piShowCommand);


void __RPC_STUB IShellLinkDual_get_ShowCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IShellLinkDual_put_ShowCommand_Proxy( 
    IShellLinkDual __RPC_FAR * This,
    /* [in] */ int iShowCommand);


void __RPC_STUB IShellLinkDual_put_ShowCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellLinkDual_Resolve_Proxy( 
    IShellLinkDual __RPC_FAR * This,
    /* [in] */ int fFlags);


void __RPC_STUB IShellLinkDual_Resolve_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellLinkDual_GetIconLocation_Proxy( 
    IShellLinkDual __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbs,
    /* [retval][out] */ int __RPC_FAR *piIcon);


void __RPC_STUB IShellLinkDual_GetIconLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellLinkDual_SetIconLocation_Proxy( 
    IShellLinkDual __RPC_FAR * This,
    /* [in] */ BSTR bs,
    /* [in] */ int iIcon);


void __RPC_STUB IShellLinkDual_SetIconLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellLinkDual_Save_Proxy( 
    IShellLinkDual __RPC_FAR * This,
    /* [optional][in] */ VARIANT vWhere);


void __RPC_STUB IShellLinkDual_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellLinkDual_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ShellLinkObject;

#ifdef __cplusplus

class DECLSPEC_UUID("11219420-1768-11d1-95BE-00609797EA4F")
ShellLinkObject;
#endif

#ifndef __FolderItemVerb_INTERFACE_DEFINED__
#define __FolderItemVerb_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: FolderItemVerb
 * at Mon Nov 17 12:05:03 1997
 * using MIDL 3.02.88
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



EXTERN_C const IID IID_FolderItemVerb;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("08EC3E00-50B0-11CF-960C-0080C7F4EE85")
    FolderItemVerb : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbs) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DoIt( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct FolderItemVerbVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            FolderItemVerb __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            FolderItemVerb __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            FolderItemVerb __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            FolderItemVerb __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            FolderItemVerb __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            FolderItemVerb __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            FolderItemVerb __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            FolderItemVerb __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            FolderItemVerb __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            FolderItemVerb __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbs);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DoIt )( 
            FolderItemVerb __RPC_FAR * This);
        
        END_INTERFACE
    } FolderItemVerbVtbl;

    interface FolderItemVerb
    {
        CONST_VTBL struct FolderItemVerbVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define FolderItemVerb_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define FolderItemVerb_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define FolderItemVerb_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define FolderItemVerb_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define FolderItemVerb_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define FolderItemVerb_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define FolderItemVerb_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define FolderItemVerb_get_Application(This,ppid)	\
    (This)->lpVtbl -> get_Application(This,ppid)

#define FolderItemVerb_get_Parent(This,ppid)	\
    (This)->lpVtbl -> get_Parent(This,ppid)

#define FolderItemVerb_get_Name(This,pbs)	\
    (This)->lpVtbl -> get_Name(This,pbs)

#define FolderItemVerb_DoIt(This)	\
    (This)->lpVtbl -> DoIt(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE FolderItemVerb_get_Application_Proxy( 
    FolderItemVerb __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB FolderItemVerb_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE FolderItemVerb_get_Parent_Proxy( 
    FolderItemVerb __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB FolderItemVerb_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE FolderItemVerb_get_Name_Proxy( 
    FolderItemVerb __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbs);


void __RPC_STUB FolderItemVerb_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE FolderItemVerb_DoIt_Proxy( 
    FolderItemVerb __RPC_FAR * This);


void __RPC_STUB FolderItemVerb_DoIt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __FolderItemVerb_INTERFACE_DEFINED__ */


#ifndef __FolderItemVerbs_INTERFACE_DEFINED__
#define __FolderItemVerbs_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: FolderItemVerbs
 * at Mon Nov 17 12:05:03 1997
 * using MIDL 3.02.88
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



EXTERN_C const IID IID_FolderItemVerbs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("1F8352C0-50B0-11CF-960C-0080C7F4EE85")
    FolderItemVerbs : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [optional][in] */ VARIANT index,
            /* [retval][out] */ FolderItemVerb __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE _NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct FolderItemVerbsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            FolderItemVerbs __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            FolderItemVerbs __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            FolderItemVerbs __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            FolderItemVerbs __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            FolderItemVerbs __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            FolderItemVerbs __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            FolderItemVerbs __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            FolderItemVerbs __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            FolderItemVerbs __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            FolderItemVerbs __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            FolderItemVerbs __RPC_FAR * This,
            /* [optional][in] */ VARIANT index,
            /* [retval][out] */ FolderItemVerb __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_NewEnum )( 
            FolderItemVerbs __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        END_INTERFACE
    } FolderItemVerbsVtbl;

    interface FolderItemVerbs
    {
        CONST_VTBL struct FolderItemVerbsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define FolderItemVerbs_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define FolderItemVerbs_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define FolderItemVerbs_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define FolderItemVerbs_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define FolderItemVerbs_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define FolderItemVerbs_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define FolderItemVerbs_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define FolderItemVerbs_get_Count(This,plCount)	\
    (This)->lpVtbl -> get_Count(This,plCount)

#define FolderItemVerbs_get_Application(This,ppid)	\
    (This)->lpVtbl -> get_Application(This,ppid)

#define FolderItemVerbs_get_Parent(This,ppid)	\
    (This)->lpVtbl -> get_Parent(This,ppid)

#define FolderItemVerbs_Item(This,index,ppid)	\
    (This)->lpVtbl -> Item(This,index,ppid)

#define FolderItemVerbs__NewEnum(This,ppunk)	\
    (This)->lpVtbl -> _NewEnum(This,ppunk)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE FolderItemVerbs_get_Count_Proxy( 
    FolderItemVerbs __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB FolderItemVerbs_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE FolderItemVerbs_get_Application_Proxy( 
    FolderItemVerbs __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB FolderItemVerbs_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE FolderItemVerbs_get_Parent_Proxy( 
    FolderItemVerbs __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB FolderItemVerbs_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE FolderItemVerbs_Item_Proxy( 
    FolderItemVerbs __RPC_FAR * This,
    /* [optional][in] */ VARIANT index,
    /* [retval][out] */ FolderItemVerb __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB FolderItemVerbs_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FolderItemVerbs__NewEnum_Proxy( 
    FolderItemVerbs __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);


void __RPC_STUB FolderItemVerbs__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __FolderItemVerbs_INTERFACE_DEFINED__ */


#ifndef __Folder_INTERFACE_DEFINED__
#define __Folder_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: Folder
 * at Mon Nov 17 12:05:03 1997
 * using MIDL 3.02.88
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



EXTERN_C const IID IID_Folder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("BBCBDE60-C3FF-11CE-8350-444553540000")
    Folder : public IDispatch
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Title( 
            /* [retval][out] */ BSTR __RPC_FAR *pbs) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ParentFolder( 
            /* [retval][out] */ Folder __RPC_FAR *__RPC_FAR *ppsf) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Items( 
            /* [retval][out] */ FolderItems __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ParseName( 
            /* [in] */ BSTR bName,
            /* [retval][out] */ FolderItem __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NewFolder( 
            /* [in] */ BSTR bName,
            /* [optional][in] */ VARIANT vOptions) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MoveHere( 
            /* [in] */ VARIANT vItem,
            /* [optional][in] */ VARIANT vOptions) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CopyHere( 
            /* [in] */ VARIANT vItem,
            /* [optional][in] */ VARIANT vOptions) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDetailsOf( 
            /* [in] */ VARIANT vItem,
            /* [in] */ int iColumn,
            /* [retval][out] */ BSTR __RPC_FAR *pbs) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct FolderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            Folder __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            Folder __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            Folder __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            Folder __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            Folder __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            Folder __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            Folder __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Title )( 
            Folder __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbs);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            Folder __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            Folder __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ParentFolder )( 
            Folder __RPC_FAR * This,
            /* [retval][out] */ Folder __RPC_FAR *__RPC_FAR *ppsf);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Items )( 
            Folder __RPC_FAR * This,
            /* [retval][out] */ FolderItems __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ParseName )( 
            Folder __RPC_FAR * This,
            /* [in] */ BSTR bName,
            /* [retval][out] */ FolderItem __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NewFolder )( 
            Folder __RPC_FAR * This,
            /* [in] */ BSTR bName,
            /* [optional][in] */ VARIANT vOptions);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveHere )( 
            Folder __RPC_FAR * This,
            /* [in] */ VARIANT vItem,
            /* [optional][in] */ VARIANT vOptions);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CopyHere )( 
            Folder __RPC_FAR * This,
            /* [in] */ VARIANT vItem,
            /* [optional][in] */ VARIANT vOptions);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDetailsOf )( 
            Folder __RPC_FAR * This,
            /* [in] */ VARIANT vItem,
            /* [in] */ int iColumn,
            /* [retval][out] */ BSTR __RPC_FAR *pbs);
        
        END_INTERFACE
    } FolderVtbl;

    interface Folder
    {
        CONST_VTBL struct FolderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Folder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define Folder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define Folder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define Folder_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define Folder_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define Folder_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define Folder_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define Folder_get_Title(This,pbs)	\
    (This)->lpVtbl -> get_Title(This,pbs)

#define Folder_get_Application(This,ppid)	\
    (This)->lpVtbl -> get_Application(This,ppid)

#define Folder_get_Parent(This,ppid)	\
    (This)->lpVtbl -> get_Parent(This,ppid)

#define Folder_get_ParentFolder(This,ppsf)	\
    (This)->lpVtbl -> get_ParentFolder(This,ppsf)

#define Folder_Items(This,ppid)	\
    (This)->lpVtbl -> Items(This,ppid)

#define Folder_ParseName(This,bName,ppid)	\
    (This)->lpVtbl -> ParseName(This,bName,ppid)

#define Folder_NewFolder(This,bName,vOptions)	\
    (This)->lpVtbl -> NewFolder(This,bName,vOptions)

#define Folder_MoveHere(This,vItem,vOptions)	\
    (This)->lpVtbl -> MoveHere(This,vItem,vOptions)

#define Folder_CopyHere(This,vItem,vOptions)	\
    (This)->lpVtbl -> CopyHere(This,vItem,vOptions)

#define Folder_GetDetailsOf(This,vItem,iColumn,pbs)	\
    (This)->lpVtbl -> GetDetailsOf(This,vItem,iColumn,pbs)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE Folder_get_Title_Proxy( 
    Folder __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbs);


void __RPC_STUB Folder_get_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE Folder_get_Application_Proxy( 
    Folder __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB Folder_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE Folder_get_Parent_Proxy( 
    Folder __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB Folder_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE Folder_get_ParentFolder_Proxy( 
    Folder __RPC_FAR * This,
    /* [retval][out] */ Folder __RPC_FAR *__RPC_FAR *ppsf);


void __RPC_STUB Folder_get_ParentFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE Folder_Items_Proxy( 
    Folder __RPC_FAR * This,
    /* [retval][out] */ FolderItems __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB Folder_Items_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE Folder_ParseName_Proxy( 
    Folder __RPC_FAR * This,
    /* [in] */ BSTR bName,
    /* [retval][out] */ FolderItem __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB Folder_ParseName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE Folder_NewFolder_Proxy( 
    Folder __RPC_FAR * This,
    /* [in] */ BSTR bName,
    /* [optional][in] */ VARIANT vOptions);


void __RPC_STUB Folder_NewFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE Folder_MoveHere_Proxy( 
    Folder __RPC_FAR * This,
    /* [in] */ VARIANT vItem,
    /* [optional][in] */ VARIANT vOptions);


void __RPC_STUB Folder_MoveHere_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE Folder_CopyHere_Proxy( 
    Folder __RPC_FAR * This,
    /* [in] */ VARIANT vItem,
    /* [optional][in] */ VARIANT vOptions);


void __RPC_STUB Folder_CopyHere_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE Folder_GetDetailsOf_Proxy( 
    Folder __RPC_FAR * This,
    /* [in] */ VARIANT vItem,
    /* [in] */ int iColumn,
    /* [retval][out] */ BSTR __RPC_FAR *pbs);


void __RPC_STUB Folder_GetDetailsOf_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __Folder_INTERFACE_DEFINED__ */


#ifndef __FolderItem_INTERFACE_DEFINED__
#define __FolderItem_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: FolderItem
 * at Mon Nov 17 12:05:03 1997
 * using MIDL 3.02.88
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



EXTERN_C const IID IID_FolderItem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("FAC32C80-CBE4-11CE-8350-444553540000")
    FolderItem : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pbs) = 0;
        
        virtual /* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR bs) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Path( 
            /* [retval][out] */ BSTR __RPC_FAR *pbs) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GetLink( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_GetFolder( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsLink( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pb) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsFolder( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pb) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsFileSystem( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pb) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_IsBrowsable( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pb) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ModifyDate( 
            /* [retval][out] */ DATE __RPC_FAR *pdt) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ModifyDate( 
            /* [in] */ DATE dt) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ LONG __RPC_FAR *pul) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ BSTR __RPC_FAR *pbs) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Verbs( 
            /* [retval][out] */ FolderItemVerbs __RPC_FAR *__RPC_FAR *ppfic) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InvokeVerb( 
            /* [optional][in] */ VARIANT vVerb) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct FolderItemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            FolderItem __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            FolderItem __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            FolderItem __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            FolderItem __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            FolderItem __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            FolderItem __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            FolderItem __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            FolderItem __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            FolderItem __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            FolderItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbs);
        
        /* [helpstring][propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            FolderItem __RPC_FAR * This,
            /* [in] */ BSTR bs);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Path )( 
            FolderItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbs);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GetLink )( 
            FolderItem __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GetFolder )( 
            FolderItem __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsLink )( 
            FolderItem __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pb);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsFolder )( 
            FolderItem __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pb);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsFileSystem )( 
            FolderItem __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pb);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsBrowsable )( 
            FolderItem __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pb);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ModifyDate )( 
            FolderItem __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *pdt);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ModifyDate )( 
            FolderItem __RPC_FAR * This,
            /* [in] */ DATE dt);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Size )( 
            FolderItem __RPC_FAR * This,
            /* [retval][out] */ LONG __RPC_FAR *pul);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            FolderItem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbs);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Verbs )( 
            FolderItem __RPC_FAR * This,
            /* [retval][out] */ FolderItemVerbs __RPC_FAR *__RPC_FAR *ppfic);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InvokeVerb )( 
            FolderItem __RPC_FAR * This,
            /* [optional][in] */ VARIANT vVerb);
        
        END_INTERFACE
    } FolderItemVtbl;

    interface FolderItem
    {
        CONST_VTBL struct FolderItemVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define FolderItem_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define FolderItem_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define FolderItem_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define FolderItem_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define FolderItem_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define FolderItem_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define FolderItem_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define FolderItem_get_Application(This,ppid)	\
    (This)->lpVtbl -> get_Application(This,ppid)

#define FolderItem_get_Parent(This,ppid)	\
    (This)->lpVtbl -> get_Parent(This,ppid)

#define FolderItem_get_Name(This,pbs)	\
    (This)->lpVtbl -> get_Name(This,pbs)

#define FolderItem_put_Name(This,bs)	\
    (This)->lpVtbl -> put_Name(This,bs)

#define FolderItem_get_Path(This,pbs)	\
    (This)->lpVtbl -> get_Path(This,pbs)

#define FolderItem_get_GetLink(This,ppid)	\
    (This)->lpVtbl -> get_GetLink(This,ppid)

#define FolderItem_get_GetFolder(This,ppid)	\
    (This)->lpVtbl -> get_GetFolder(This,ppid)

#define FolderItem_get_IsLink(This,pb)	\
    (This)->lpVtbl -> get_IsLink(This,pb)

#define FolderItem_get_IsFolder(This,pb)	\
    (This)->lpVtbl -> get_IsFolder(This,pb)

#define FolderItem_get_IsFileSystem(This,pb)	\
    (This)->lpVtbl -> get_IsFileSystem(This,pb)

#define FolderItem_get_IsBrowsable(This,pb)	\
    (This)->lpVtbl -> get_IsBrowsable(This,pb)

#define FolderItem_get_ModifyDate(This,pdt)	\
    (This)->lpVtbl -> get_ModifyDate(This,pdt)

#define FolderItem_put_ModifyDate(This,dt)	\
    (This)->lpVtbl -> put_ModifyDate(This,dt)

#define FolderItem_get_Size(This,pul)	\
    (This)->lpVtbl -> get_Size(This,pul)

#define FolderItem_get_Type(This,pbs)	\
    (This)->lpVtbl -> get_Type(This,pbs)

#define FolderItem_Verbs(This,ppfic)	\
    (This)->lpVtbl -> Verbs(This,ppfic)

#define FolderItem_InvokeVerb(This,vVerb)	\
    (This)->lpVtbl -> InvokeVerb(This,vVerb)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE FolderItem_get_Application_Proxy( 
    FolderItem __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB FolderItem_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE FolderItem_get_Parent_Proxy( 
    FolderItem __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB FolderItem_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE FolderItem_get_Name_Proxy( 
    FolderItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbs);


void __RPC_STUB FolderItem_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput][id] */ HRESULT STDMETHODCALLTYPE FolderItem_put_Name_Proxy( 
    FolderItem __RPC_FAR * This,
    /* [in] */ BSTR bs);


void __RPC_STUB FolderItem_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE FolderItem_get_Path_Proxy( 
    FolderItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbs);


void __RPC_STUB FolderItem_get_Path_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE FolderItem_get_GetLink_Proxy( 
    FolderItem __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB FolderItem_get_GetLink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE FolderItem_get_GetFolder_Proxy( 
    FolderItem __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB FolderItem_get_GetFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE FolderItem_get_IsLink_Proxy( 
    FolderItem __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pb);


void __RPC_STUB FolderItem_get_IsLink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE FolderItem_get_IsFolder_Proxy( 
    FolderItem __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pb);


void __RPC_STUB FolderItem_get_IsFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE FolderItem_get_IsFileSystem_Proxy( 
    FolderItem __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pb);


void __RPC_STUB FolderItem_get_IsFileSystem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE FolderItem_get_IsBrowsable_Proxy( 
    FolderItem __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pb);


void __RPC_STUB FolderItem_get_IsBrowsable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE FolderItem_get_ModifyDate_Proxy( 
    FolderItem __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *pdt);


void __RPC_STUB FolderItem_get_ModifyDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE FolderItem_put_ModifyDate_Proxy( 
    FolderItem __RPC_FAR * This,
    /* [in] */ DATE dt);


void __RPC_STUB FolderItem_put_ModifyDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE FolderItem_get_Size_Proxy( 
    FolderItem __RPC_FAR * This,
    /* [retval][out] */ LONG __RPC_FAR *pul);


void __RPC_STUB FolderItem_get_Size_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE FolderItem_get_Type_Proxy( 
    FolderItem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbs);


void __RPC_STUB FolderItem_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE FolderItem_Verbs_Proxy( 
    FolderItem __RPC_FAR * This,
    /* [retval][out] */ FolderItemVerbs __RPC_FAR *__RPC_FAR *ppfic);


void __RPC_STUB FolderItem_Verbs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE FolderItem_InvokeVerb_Proxy( 
    FolderItem __RPC_FAR * This,
    /* [optional][in] */ VARIANT vVerb);


void __RPC_STUB FolderItem_InvokeVerb_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __FolderItem_INTERFACE_DEFINED__ */


#ifndef __FolderItems_INTERFACE_DEFINED__
#define __FolderItems_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: FolderItems
 * at Mon Nov 17 12:05:03 1997
 * using MIDL 3.02.88
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



EXTERN_C const IID IID_FolderItems;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("744129E0-CBE5-11CE-8350-444553540000")
    FolderItems : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *plCount) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [optional][in] */ VARIANT index,
            /* [retval][out] */ FolderItem __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE _NewEnum( 
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct FolderItemsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            FolderItems __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            FolderItems __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            FolderItems __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            FolderItems __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            FolderItems __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            FolderItems __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            FolderItems __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            FolderItems __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plCount);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            FolderItems __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            FolderItems __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            FolderItems __RPC_FAR * This,
            /* [optional][in] */ VARIANT index,
            /* [retval][out] */ FolderItem __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *_NewEnum )( 
            FolderItems __RPC_FAR * This,
            /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);
        
        END_INTERFACE
    } FolderItemsVtbl;

    interface FolderItems
    {
        CONST_VTBL struct FolderItemsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define FolderItems_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define FolderItems_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define FolderItems_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define FolderItems_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define FolderItems_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define FolderItems_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define FolderItems_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define FolderItems_get_Count(This,plCount)	\
    (This)->lpVtbl -> get_Count(This,plCount)

#define FolderItems_get_Application(This,ppid)	\
    (This)->lpVtbl -> get_Application(This,ppid)

#define FolderItems_get_Parent(This,ppid)	\
    (This)->lpVtbl -> get_Parent(This,ppid)

#define FolderItems_Item(This,index,ppid)	\
    (This)->lpVtbl -> Item(This,index,ppid)

#define FolderItems__NewEnum(This,ppunk)	\
    (This)->lpVtbl -> _NewEnum(This,ppunk)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE FolderItems_get_Count_Proxy( 
    FolderItems __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plCount);


void __RPC_STUB FolderItems_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE FolderItems_get_Application_Proxy( 
    FolderItems __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB FolderItems_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE FolderItems_get_Parent_Proxy( 
    FolderItems __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB FolderItems_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE FolderItems_Item_Proxy( 
    FolderItems __RPC_FAR * This,
    /* [optional][in] */ VARIANT index,
    /* [retval][out] */ FolderItem __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB FolderItems_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FolderItems__NewEnum_Proxy( 
    FolderItems __RPC_FAR * This,
    /* [retval][out] */ IUnknown __RPC_FAR *__RPC_FAR *ppunk);


void __RPC_STUB FolderItems__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __FolderItems_INTERFACE_DEFINED__ */


#ifndef __IShellFolderViewDual_INTERFACE_DEFINED__
#define __IShellFolderViewDual_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IShellFolderViewDual
 * at Mon Nov 17 12:05:03 1997
 * using MIDL 3.02.88
 ****************************************/
/* [object][dual][hidden][oleautomation][helpstring][uuid] */ 



EXTERN_C const IID IID_IShellFolderViewDual;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("E7A1AF80-4D96-11CF-960C-0080C7F4EE85")
    IShellFolderViewDual : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Folder( 
            /* [retval][out] */ Folder __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SelectedItems( 
            /* [retval][out] */ FolderItems __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_FocusedItem( 
            /* [retval][out] */ FolderItem __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SelectItem( 
            /* [in] */ VARIANT __RPC_FAR *pvfi,
            /* [in] */ int dwFlags) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE PopupItemMenu( 
            /* [in] */ FolderItem __RPC_FAR *pfi,
            /* [optional][in] */ VARIANT vx,
            /* [optional][in] */ VARIANT vy,
            /* [retval][out] */ BSTR __RPC_FAR *pbs) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Script( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp) = 0;
        
        virtual /* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ViewOptions( 
            /* [retval][out] */ long __RPC_FAR *plViewOptions) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellFolderViewDualVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IShellFolderViewDual __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IShellFolderViewDual __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IShellFolderViewDual __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IShellFolderViewDual __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IShellFolderViewDual __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IShellFolderViewDual __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IShellFolderViewDual __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            IShellFolderViewDual __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IShellFolderViewDual __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Folder )( 
            IShellFolderViewDual __RPC_FAR * This,
            /* [retval][out] */ Folder __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SelectedItems )( 
            IShellFolderViewDual __RPC_FAR * This,
            /* [retval][out] */ FolderItems __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FocusedItem )( 
            IShellFolderViewDual __RPC_FAR * This,
            /* [retval][out] */ FolderItem __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SelectItem )( 
            IShellFolderViewDual __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *pvfi,
            /* [in] */ int dwFlags);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PopupItemMenu )( 
            IShellFolderViewDual __RPC_FAR * This,
            /* [in] */ FolderItem __RPC_FAR *pfi,
            /* [optional][in] */ VARIANT vx,
            /* [optional][in] */ VARIANT vy,
            /* [retval][out] */ BSTR __RPC_FAR *pbs);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Script )( 
            IShellFolderViewDual __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);
        
        /* [helpcontext][helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ViewOptions )( 
            IShellFolderViewDual __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plViewOptions);
        
        END_INTERFACE
    } IShellFolderViewDualVtbl;

    interface IShellFolderViewDual
    {
        CONST_VTBL struct IShellFolderViewDualVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellFolderViewDual_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IShellFolderViewDual_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IShellFolderViewDual_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IShellFolderViewDual_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IShellFolderViewDual_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IShellFolderViewDual_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IShellFolderViewDual_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IShellFolderViewDual_get_Application(This,ppid)	\
    (This)->lpVtbl -> get_Application(This,ppid)

#define IShellFolderViewDual_get_Parent(This,ppid)	\
    (This)->lpVtbl -> get_Parent(This,ppid)

#define IShellFolderViewDual_get_Folder(This,ppid)	\
    (This)->lpVtbl -> get_Folder(This,ppid)

#define IShellFolderViewDual_SelectedItems(This,ppid)	\
    (This)->lpVtbl -> SelectedItems(This,ppid)

#define IShellFolderViewDual_get_FocusedItem(This,ppid)	\
    (This)->lpVtbl -> get_FocusedItem(This,ppid)

#define IShellFolderViewDual_SelectItem(This,pvfi,dwFlags)	\
    (This)->lpVtbl -> SelectItem(This,pvfi,dwFlags)

#define IShellFolderViewDual_PopupItemMenu(This,pfi,vx,vy,pbs)	\
    (This)->lpVtbl -> PopupItemMenu(This,pfi,vx,vy,pbs)

#define IShellFolderViewDual_get_Script(This,ppDisp)	\
    (This)->lpVtbl -> get_Script(This,ppDisp)

#define IShellFolderViewDual_get_ViewOptions(This,plViewOptions)	\
    (This)->lpVtbl -> get_ViewOptions(This,plViewOptions)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IShellFolderViewDual_get_Application_Proxy( 
    IShellFolderViewDual __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB IShellFolderViewDual_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IShellFolderViewDual_get_Parent_Proxy( 
    IShellFolderViewDual __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB IShellFolderViewDual_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IShellFolderViewDual_get_Folder_Proxy( 
    IShellFolderViewDual __RPC_FAR * This,
    /* [retval][out] */ Folder __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB IShellFolderViewDual_get_Folder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellFolderViewDual_SelectedItems_Proxy( 
    IShellFolderViewDual __RPC_FAR * This,
    /* [retval][out] */ FolderItems __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB IShellFolderViewDual_SelectedItems_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IShellFolderViewDual_get_FocusedItem_Proxy( 
    IShellFolderViewDual __RPC_FAR * This,
    /* [retval][out] */ FolderItem __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB IShellFolderViewDual_get_FocusedItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellFolderViewDual_SelectItem_Proxy( 
    IShellFolderViewDual __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *pvfi,
    /* [in] */ int dwFlags);


void __RPC_STUB IShellFolderViewDual_SelectItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellFolderViewDual_PopupItemMenu_Proxy( 
    IShellFolderViewDual __RPC_FAR * This,
    /* [in] */ FolderItem __RPC_FAR *pfi,
    /* [optional][in] */ VARIANT vx,
    /* [optional][in] */ VARIANT vy,
    /* [retval][out] */ BSTR __RPC_FAR *pbs);


void __RPC_STUB IShellFolderViewDual_PopupItemMenu_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IShellFolderViewDual_get_Script_Proxy( 
    IShellFolderViewDual __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);


void __RPC_STUB IShellFolderViewDual_get_Script_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][propget] */ HRESULT STDMETHODCALLTYPE IShellFolderViewDual_get_ViewOptions_Proxy( 
    IShellFolderViewDual __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plViewOptions);


void __RPC_STUB IShellFolderViewDual_get_ViewOptions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellFolderViewDual_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ShellFolderView;

#ifdef __cplusplus

class DECLSPEC_UUID("62112AA1-EBE4-11cf-A5FB-0020AFE7292D")
ShellFolderView;
#endif

#ifndef __IShellDispatch_INTERFACE_DEFINED__
#define __IShellDispatch_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IShellDispatch
 * at Mon Nov 17 12:05:03 1997
 * using MIDL 3.02.88
 ****************************************/
/* [object][dual][hidden][oleautomation][helpstring][uuid] */ 



EXTERN_C const IID IID_IShellDispatch;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("D8F015C0-C278-11CE-A49E-444553540000")
    IShellDispatch : public IDispatch
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Application( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Parent( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NameSpace( 
            /* [in] */ VARIANT vDir,
            /* [retval][out] */ Folder __RPC_FAR *__RPC_FAR *ppsdf) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE BrowseForFolder( 
            /* [in] */ long Hwnd,
            /* [in] */ BSTR Title,
            /* [in] */ long Options,
            /* [optional][in] */ VARIANT RootFolder,
            /* [retval][out] */ Folder __RPC_FAR *__RPC_FAR *ppsdf) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Windows( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ VARIANT vDir) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Explore( 
            /* [in] */ VARIANT vDir) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MinimizeAll( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UndoMinimizeALL( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FileRun( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CascadeWindows( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TileVertically( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TileHorizontally( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ShutdownWindows( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Suspend( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EjectPC( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetTime( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TrayProperties( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Help( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FindFiles( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FindComputer( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RefreshMenu( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ControlPanelItem( 
            /* [in] */ BSTR szDir) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellDispatchVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IShellDispatch __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IShellDispatch __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IShellDispatch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IShellDispatch __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IShellDispatch __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IShellDispatch __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IShellDispatch __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Application )( 
            IShellDispatch __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Parent )( 
            IShellDispatch __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NameSpace )( 
            IShellDispatch __RPC_FAR * This,
            /* [in] */ VARIANT vDir,
            /* [retval][out] */ Folder __RPC_FAR *__RPC_FAR *ppsdf);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BrowseForFolder )( 
            IShellDispatch __RPC_FAR * This,
            /* [in] */ long Hwnd,
            /* [in] */ BSTR Title,
            /* [in] */ long Options,
            /* [optional][in] */ VARIANT RootFolder,
            /* [retval][out] */ Folder __RPC_FAR *__RPC_FAR *ppsdf);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Windows )( 
            IShellDispatch __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Open )( 
            IShellDispatch __RPC_FAR * This,
            /* [in] */ VARIANT vDir);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Explore )( 
            IShellDispatch __RPC_FAR * This,
            /* [in] */ VARIANT vDir);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MinimizeAll )( 
            IShellDispatch __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UndoMinimizeALL )( 
            IShellDispatch __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FileRun )( 
            IShellDispatch __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CascadeWindows )( 
            IShellDispatch __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TileVertically )( 
            IShellDispatch __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TileHorizontally )( 
            IShellDispatch __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShutdownWindows )( 
            IShellDispatch __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Suspend )( 
            IShellDispatch __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EjectPC )( 
            IShellDispatch __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTime )( 
            IShellDispatch __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TrayProperties )( 
            IShellDispatch __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Help )( 
            IShellDispatch __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindFiles )( 
            IShellDispatch __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindComputer )( 
            IShellDispatch __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RefreshMenu )( 
            IShellDispatch __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ControlPanelItem )( 
            IShellDispatch __RPC_FAR * This,
            /* [in] */ BSTR szDir);
        
        END_INTERFACE
    } IShellDispatchVtbl;

    interface IShellDispatch
    {
        CONST_VTBL struct IShellDispatchVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellDispatch_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IShellDispatch_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IShellDispatch_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IShellDispatch_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IShellDispatch_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IShellDispatch_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IShellDispatch_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IShellDispatch_get_Application(This,ppid)	\
    (This)->lpVtbl -> get_Application(This,ppid)

#define IShellDispatch_get_Parent(This,ppid)	\
    (This)->lpVtbl -> get_Parent(This,ppid)

#define IShellDispatch_NameSpace(This,vDir,ppsdf)	\
    (This)->lpVtbl -> NameSpace(This,vDir,ppsdf)

#define IShellDispatch_BrowseForFolder(This,Hwnd,Title,Options,RootFolder,ppsdf)	\
    (This)->lpVtbl -> BrowseForFolder(This,Hwnd,Title,Options,RootFolder,ppsdf)

#define IShellDispatch_Windows(This,ppid)	\
    (This)->lpVtbl -> Windows(This,ppid)

#define IShellDispatch_Open(This,vDir)	\
    (This)->lpVtbl -> Open(This,vDir)

#define IShellDispatch_Explore(This,vDir)	\
    (This)->lpVtbl -> Explore(This,vDir)

#define IShellDispatch_MinimizeAll(This)	\
    (This)->lpVtbl -> MinimizeAll(This)

#define IShellDispatch_UndoMinimizeALL(This)	\
    (This)->lpVtbl -> UndoMinimizeALL(This)

#define IShellDispatch_FileRun(This)	\
    (This)->lpVtbl -> FileRun(This)

#define IShellDispatch_CascadeWindows(This)	\
    (This)->lpVtbl -> CascadeWindows(This)

#define IShellDispatch_TileVertically(This)	\
    (This)->lpVtbl -> TileVertically(This)

#define IShellDispatch_TileHorizontally(This)	\
    (This)->lpVtbl -> TileHorizontally(This)

#define IShellDispatch_ShutdownWindows(This)	\
    (This)->lpVtbl -> ShutdownWindows(This)

#define IShellDispatch_Suspend(This)	\
    (This)->lpVtbl -> Suspend(This)

#define IShellDispatch_EjectPC(This)	\
    (This)->lpVtbl -> EjectPC(This)

#define IShellDispatch_SetTime(This)	\
    (This)->lpVtbl -> SetTime(This)

#define IShellDispatch_TrayProperties(This)	\
    (This)->lpVtbl -> TrayProperties(This)

#define IShellDispatch_Help(This)	\
    (This)->lpVtbl -> Help(This)

#define IShellDispatch_FindFiles(This)	\
    (This)->lpVtbl -> FindFiles(This)

#define IShellDispatch_FindComputer(This)	\
    (This)->lpVtbl -> FindComputer(This)

#define IShellDispatch_RefreshMenu(This)	\
    (This)->lpVtbl -> RefreshMenu(This)

#define IShellDispatch_ControlPanelItem(This,szDir)	\
    (This)->lpVtbl -> ControlPanelItem(This,szDir)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IShellDispatch_get_Application_Proxy( 
    IShellDispatch __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB IShellDispatch_get_Application_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IShellDispatch_get_Parent_Proxy( 
    IShellDispatch __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB IShellDispatch_get_Parent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellDispatch_NameSpace_Proxy( 
    IShellDispatch __RPC_FAR * This,
    /* [in] */ VARIANT vDir,
    /* [retval][out] */ Folder __RPC_FAR *__RPC_FAR *ppsdf);


void __RPC_STUB IShellDispatch_NameSpace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellDispatch_BrowseForFolder_Proxy( 
    IShellDispatch __RPC_FAR * This,
    /* [in] */ long Hwnd,
    /* [in] */ BSTR Title,
    /* [in] */ long Options,
    /* [optional][in] */ VARIANT RootFolder,
    /* [retval][out] */ Folder __RPC_FAR *__RPC_FAR *ppsdf);


void __RPC_STUB IShellDispatch_BrowseForFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellDispatch_Windows_Proxy( 
    IShellDispatch __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *ppid);


void __RPC_STUB IShellDispatch_Windows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellDispatch_Open_Proxy( 
    IShellDispatch __RPC_FAR * This,
    /* [in] */ VARIANT vDir);


void __RPC_STUB IShellDispatch_Open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellDispatch_Explore_Proxy( 
    IShellDispatch __RPC_FAR * This,
    /* [in] */ VARIANT vDir);


void __RPC_STUB IShellDispatch_Explore_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellDispatch_MinimizeAll_Proxy( 
    IShellDispatch __RPC_FAR * This);


void __RPC_STUB IShellDispatch_MinimizeAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellDispatch_UndoMinimizeALL_Proxy( 
    IShellDispatch __RPC_FAR * This);


void __RPC_STUB IShellDispatch_UndoMinimizeALL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellDispatch_FileRun_Proxy( 
    IShellDispatch __RPC_FAR * This);


void __RPC_STUB IShellDispatch_FileRun_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellDispatch_CascadeWindows_Proxy( 
    IShellDispatch __RPC_FAR * This);


void __RPC_STUB IShellDispatch_CascadeWindows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellDispatch_TileVertically_Proxy( 
    IShellDispatch __RPC_FAR * This);


void __RPC_STUB IShellDispatch_TileVertically_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellDispatch_TileHorizontally_Proxy( 
    IShellDispatch __RPC_FAR * This);


void __RPC_STUB IShellDispatch_TileHorizontally_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellDispatch_ShutdownWindows_Proxy( 
    IShellDispatch __RPC_FAR * This);


void __RPC_STUB IShellDispatch_ShutdownWindows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellDispatch_Suspend_Proxy( 
    IShellDispatch __RPC_FAR * This);


void __RPC_STUB IShellDispatch_Suspend_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellDispatch_EjectPC_Proxy( 
    IShellDispatch __RPC_FAR * This);


void __RPC_STUB IShellDispatch_EjectPC_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellDispatch_SetTime_Proxy( 
    IShellDispatch __RPC_FAR * This);


void __RPC_STUB IShellDispatch_SetTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellDispatch_TrayProperties_Proxy( 
    IShellDispatch __RPC_FAR * This);


void __RPC_STUB IShellDispatch_TrayProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellDispatch_Help_Proxy( 
    IShellDispatch __RPC_FAR * This);


void __RPC_STUB IShellDispatch_Help_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellDispatch_FindFiles_Proxy( 
    IShellDispatch __RPC_FAR * This);


void __RPC_STUB IShellDispatch_FindFiles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellDispatch_FindComputer_Proxy( 
    IShellDispatch __RPC_FAR * This);


void __RPC_STUB IShellDispatch_FindComputer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellDispatch_RefreshMenu_Proxy( 
    IShellDispatch __RPC_FAR * This);


void __RPC_STUB IShellDispatch_RefreshMenu_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IShellDispatch_ControlPanelItem_Proxy( 
    IShellDispatch __RPC_FAR * This,
    /* [in] */ BSTR szDir);


void __RPC_STUB IShellDispatch_ControlPanelItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellDispatch_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Shell;

#ifdef __cplusplus

class DECLSPEC_UUID("13709620-C279-11CE-A49E-444553540000")
Shell;
#endif

EXTERN_C const CLSID CLSID_ShellDispatchInproc;

#ifdef __cplusplus

class DECLSPEC_UUID("0A89A860-D7B1-11CE-8350-444553540000")
ShellDispatchInproc;
#endif

EXTERN_C const CLSID CLSID_WebViewFolderContents;

#ifdef __cplusplus

class DECLSPEC_UUID("1820FED0-473E-11D0-A96C-00C04FD705A2")
WebViewFolderContents;
#endif

#ifndef __IShellUIHelper_INTERFACE_DEFINED__
#define __IShellUIHelper_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IShellUIHelper
 * at Mon Nov 17 12:05:03 1997
 * using MIDL 3.02.88
 ****************************************/
/* [object][dual][oleautomation][helpstring][uuid] */ 



EXTERN_C const IID IID_IShellUIHelper;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("729FE2F8-1EA8-11d1-8F85-00C04FC2FBE1")
    IShellUIHelper : public IDispatch
    {
    public:
        virtual /* [id][hidden] */ HRESULT STDMETHODCALLTYPE ResetFirstBootMode( void) = 0;
        
        virtual /* [id][hidden] */ HRESULT STDMETHODCALLTYPE ResetSafeMode( void) = 0;
        
        virtual /* [id][hidden] */ HRESULT STDMETHODCALLTYPE RefreshOfflineDesktop( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AddFavorite( 
            /* [in] */ BSTR URL,
            /* [in][optional] */ VARIANT __RPC_FAR *Title) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AddChannel( 
            /* [in] */ BSTR URL) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AddDesktopComponent( 
            /* [in] */ BSTR URL,
            /* [in] */ BSTR Type,
            /* [in][optional] */ VARIANT __RPC_FAR *Left,
            /* [in][optional] */ VARIANT __RPC_FAR *Top,
            /* [in][optional] */ VARIANT __RPC_FAR *Width,
            /* [in][optional] */ VARIANT __RPC_FAR *Height) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE IsSubscribed( 
            /* [in] */ BSTR URL,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBool) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IShellUIHelperVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IShellUIHelper __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IShellUIHelper __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IShellUIHelper __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IShellUIHelper __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IShellUIHelper __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IShellUIHelper __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IShellUIHelper __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetFirstBootMode )( 
            IShellUIHelper __RPC_FAR * This);
        
        /* [id][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetSafeMode )( 
            IShellUIHelper __RPC_FAR * This);
        
        /* [id][hidden] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RefreshOfflineDesktop )( 
            IShellUIHelper __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddFavorite )( 
            IShellUIHelper __RPC_FAR * This,
            /* [in] */ BSTR URL,
            /* [in][optional] */ VARIANT __RPC_FAR *Title);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddChannel )( 
            IShellUIHelper __RPC_FAR * This,
            /* [in] */ BSTR URL);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddDesktopComponent )( 
            IShellUIHelper __RPC_FAR * This,
            /* [in] */ BSTR URL,
            /* [in] */ BSTR Type,
            /* [in][optional] */ VARIANT __RPC_FAR *Left,
            /* [in][optional] */ VARIANT __RPC_FAR *Top,
            /* [in][optional] */ VARIANT __RPC_FAR *Width,
            /* [in][optional] */ VARIANT __RPC_FAR *Height);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsSubscribed )( 
            IShellUIHelper __RPC_FAR * This,
            /* [in] */ BSTR URL,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBool);
        
        END_INTERFACE
    } IShellUIHelperVtbl;

    interface IShellUIHelper
    {
        CONST_VTBL struct IShellUIHelperVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IShellUIHelper_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IShellUIHelper_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IShellUIHelper_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IShellUIHelper_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IShellUIHelper_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IShellUIHelper_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IShellUIHelper_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IShellUIHelper_ResetFirstBootMode(This)	\
    (This)->lpVtbl -> ResetFirstBootMode(This)

#define IShellUIHelper_ResetSafeMode(This)	\
    (This)->lpVtbl -> ResetSafeMode(This)

#define IShellUIHelper_RefreshOfflineDesktop(This)	\
    (This)->lpVtbl -> RefreshOfflineDesktop(This)

#define IShellUIHelper_AddFavorite(This,URL,Title)	\
    (This)->lpVtbl -> AddFavorite(This,URL,Title)

#define IShellUIHelper_AddChannel(This,URL)	\
    (This)->lpVtbl -> AddChannel(This,URL)

#define IShellUIHelper_AddDesktopComponent(This,URL,Type,Left,Top,Width,Height)	\
    (This)->lpVtbl -> AddDesktopComponent(This,URL,Type,Left,Top,Width,Height)

#define IShellUIHelper_IsSubscribed(This,URL,pBool)	\
    (This)->lpVtbl -> IsSubscribed(This,URL,pBool)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][hidden] */ HRESULT STDMETHODCALLTYPE IShellUIHelper_ResetFirstBootMode_Proxy( 
    IShellUIHelper __RPC_FAR * This);


void __RPC_STUB IShellUIHelper_ResetFirstBootMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][hidden] */ HRESULT STDMETHODCALLTYPE IShellUIHelper_ResetSafeMode_Proxy( 
    IShellUIHelper __RPC_FAR * This);


void __RPC_STUB IShellUIHelper_ResetSafeMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][hidden] */ HRESULT STDMETHODCALLTYPE IShellUIHelper_RefreshOfflineDesktop_Proxy( 
    IShellUIHelper __RPC_FAR * This);


void __RPC_STUB IShellUIHelper_RefreshOfflineDesktop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShellUIHelper_AddFavorite_Proxy( 
    IShellUIHelper __RPC_FAR * This,
    /* [in] */ BSTR URL,
    /* [in][optional] */ VARIANT __RPC_FAR *Title);


void __RPC_STUB IShellUIHelper_AddFavorite_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShellUIHelper_AddChannel_Proxy( 
    IShellUIHelper __RPC_FAR * This,
    /* [in] */ BSTR URL);


void __RPC_STUB IShellUIHelper_AddChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShellUIHelper_AddDesktopComponent_Proxy( 
    IShellUIHelper __RPC_FAR * This,
    /* [in] */ BSTR URL,
    /* [in] */ BSTR Type,
    /* [in][optional] */ VARIANT __RPC_FAR *Left,
    /* [in][optional] */ VARIANT __RPC_FAR *Top,
    /* [in][optional] */ VARIANT __RPC_FAR *Width,
    /* [in][optional] */ VARIANT __RPC_FAR *Height);


void __RPC_STUB IShellUIHelper_AddDesktopComponent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE IShellUIHelper_IsSubscribed_Proxy( 
    IShellUIHelper __RPC_FAR * This,
    /* [in] */ BSTR URL,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pBool);


void __RPC_STUB IShellUIHelper_IsSubscribed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IShellUIHelper_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ShellUIHelper;

#ifdef __cplusplus

class DECLSPEC_UUID("64AB4BB7-111E-11d1-8F79-00C04FC2FBE1")
ShellUIHelper;
#endif
#endif /* __SHDocVw_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
