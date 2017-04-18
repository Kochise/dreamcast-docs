/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.02.88 */
/* at Tue Jun 15 19:55:09 1999
 */
/* Compiler settings for .\ieceui.idl:
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

#include <Commdlg.h> // for PAGESETUPDIALOG
#include <urlmon.h> // for BINDINFO structure

#ifndef __ieceui_h__
#define __ieceui_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __Iieui_FWD_DEFINED__
#define __Iieui_FWD_DEFINED__
typedef interface Iieui Iieui;
#endif 	/* __Iieui_FWD_DEFINED__ */


#ifndef __ieui_FWD_DEFINED__
#define __ieui_FWD_DEFINED__

#ifdef __cplusplus
typedef class ieui ieui;
#else
typedef struct ieui ieui;
#endif /* __cplusplus */

#endif 	/* __ieui_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __Iieui_INTERFACE_DEFINED__
#define __Iieui_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: Iieui
 * at Tue Jun 15 19:55:09 1999
 * using MIDL 3.02.88
 ****************************************/
/* [unique][helpstring][local][uuid][object] */ 


#define STD_CTL_SCODE(n) MAKE_SCODE(SEVERITY_ERROR, FACILITY_CONTROL, n)

#define CTL_E_METHODNOTAPPLICABLE  STD_CTL_SCODE(444)
#define CTL_E_CANTMOVEFOCUSTOCTRL  STD_CTL_SCODE(2110)
#define CTL_E_CONTROLNEEDSFOCUS    STD_CTL_SCODE(2185)
#define CTL_E_INVALIDPICTURETYPE   STD_CTL_SCODE(485)
#define CTL_E_INVALIDPASTETARGET   CUSTOM_CTL_SCODE( CTL_E_CUSTOM_FIRST + 0 )
#define CTL_E_INVALIDPASTESOURCE   CUSTOM_CTL_SCODE( CTL_E_CUSTOM_FIRST + 1 )


/*******************************************************************/
/* 8-31-1999 t-kirkb
/*
/* PAGESETUPOPT
/*
/* Need extended page setup options structure for capturing print
/* job flags on page setup.  Replaceable UI should write option
/* values to customize the current print job.  Options are turned
/* on by masking the option true.
/*
/* For example, to turn on active frame printing:
/*
/*    dwOptionValues |= PSOPT_PRINTACTIVEFRAMEON;
/*    dwOptionValues |= PSOPT_PRINTACTIVEFRAME;
/*
/* and, to turn off active frame printing:
/*
/*    dwOptionValues |= PSOPT_PRINTACTIVEFRAMEON;
/*    dwOptionValues &= ~PSOPT_PRINTACTIVEFRAME;
/*
/*******************************************************************/
typedef struct
{
	DWORD dwOptionValues; // Custom option values
}	PAGESETUPOPT, *LPPAGESETUPOPT;

#define PSOPT_PRINTACTIVEFRAMEON 0x00000004
#define PSOPT_PRINTACTIVEFRAME   0x00000002


EXTERN_C const IID IID_Iieui;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("B048FC80-122D-11D3-9590-00C04FAEA6D4")
    Iieui : public IUnknown
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowScriptErrorDialog( 
            /* [in] */ HWND hwndParent,
            /* [in] */ IDispatch __RPC_FAR *pDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowFindDialog( 
            /* [in] */ HWND hwndParent,
            /* [in] */ IDispatch __RPC_FAR *pDisp) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowPromptDialog( 
            /* [in] */ HWND hwndParent,
            /* [in] */ BSTR message,
            /* [in] */ BSTR defstr,
            /* [out] */ LPTSTR __RPC_FAR *strEditResult) = 0;

		virtual STDMETHODIMP_(int) ShowAlertConfirm(
			HWND hWnd,
			LPCTSTR lpText,
			UINT uType) = 0;

       	virtual /* [helpstring][id] */ STDMETHODIMP_(int) ShowMessageBox(
			HWND hWnd,
			LPCTSTR lpText,
			LPCTSTR lpCaption,
			UINT uType,
			...) = 0;

		virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowPrintCancelDialog( 
			/* [in] */ HWND hwndParent,
			/* [out] */ HWND* phPrintCancelDlg,
			/* [in] */ BOOL* pfAbortPrintJob) = 0;

		virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowPageSetupDialog( 
        	/* [in, out] */ PAGESETUPDLG *ppage_setup_dlg,
        	/* [in, out] */ PAGESETUPOPT *ppage_setup_opt,
        	BOOL *pfResult) = 0;

	virtual /* [helpstring][id] */ STDMETHODIMP_(BOOL) ShowGetSaveFileName(OPENFILENAME *pofn) = 0;
	virtual /* [helpstring][id] */ STDMETHODIMP_(BOOL) ShowGetOpenFileName(OPENFILENAME *pofn) = 0;


        virtual /* [helpstring][id] */ STDMETHODIMP_(int) ShowBindingErrorMessageBox( 
            /* [in] */ HWND hwnd,
            /* [in] */ HRESULT hrError,
            /* [in] */ DWORD dwResource,
            /* [in] */ LPCTSTR pszUrlParam,
            /* [in] */ UINT fuFlags) = 0;
        

	virtual STDMETHODIMP_(void) ShowCDownLoad_UI(
		IMoniker* pmk,
		IBindCtx *pbc,
		BOOL fSync,
		BOOL fSaveAs,
		BOOL fSafe,
		LPWSTR pwzHeaders,
		DWORD dwVerb,
		DWORD grfBINDF,
		BINDINFO* pbinfo,
		LPCTSTR pszRedir,
		HANDLE hSig,
		LONG* pcModelessDlg,
		HWND* phDlgActive,
		CRITICAL_SECTION *pcs) = 0;


	virtual STDMETHODIMP ShowCDownLoad_UIURL(
		LPCWSTR pwszURL,
		IBindCtx *pbc,
		LPWSTR pwzHeaders, 
		BOOL fSync,
		BOOL fSaveAs,
		BOOL fSafe,
		DWORD dwVerb,
		DWORD grfBINDF,
		BINDINFO* pbinfo,
		LPCTSTR pszRedir,
		HANDLE hSig,
		LONG* pcModelessDlg,
		HWND* phDlgActive,
		CRITICAL_SECTION *pcs) = 0;

	virtual STDMETHODIMP ShowLastErrorInfo(
		int idsDefault,
		HWND hWnd) = 0;

	virtual STDMETHODIMP ShowLoadError(
		HRESULT hrDisplay,
		HWND hWnd,
		LPCTSTR pszUrl) = 0;

	virtual STDMETHODIMP GetErrorText(
		HRESULT hrError,
		LPTSTR pstr,
		int cch) = 0;

	virtual STDMETHODIMP GetSolutionText(
		HRESULT hrError,
		LPTSTR pstr,
		int cch) = 0;

	virtual STDMETHODIMP_(int) MessageBoxW(
		HWND hwndParent, 
		LPCWSTR lpText, 
		LPCWSTR lpCaption, 
		UINT uType) = 0;

	virtual STDMETHODIMP_(BOOL) RenderFullTVFocusRect(
		HDC hdc, 
		LPRECT lprc, 
		UINT wFlags) = 0;

	virtual STDMETHODIMP_(BOOL) DrawTVFocusRect(
		HDC hdc, 
		LPCRECT lprc, 
		UINT wFlags) = 0;
    };
    
#else 	/* C style interface */

#error Please use C++ to include this file

#endif 	/* C style interface */

#endif 	/* __Iieui_INTERFACE_DEFINED__ */



#ifndef __IECEUILib_LIBRARY_DEFINED__
#define __IECEUILib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: IECEUILib
 * at Tue Jun 15 19:55:09 1999
 * using MIDL 3.02.88
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_IECEUILib;

EXTERN_C const CLSID CLSID_ieui;

#ifdef __cplusplus

class DECLSPEC_UUID("B048FC81-122D-11D3-9590-00C04FAEA6D4")
ieui;
#endif
#endif /* __IECEUILib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
