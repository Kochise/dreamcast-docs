#ifndef __EXTERNAL_H            // guard against multiple inclusion
#define __EXTERNAL_H

/********************************************************************
 * external.h
 *
 * Description
 *    Defines, data structures, and prototypes for functions in IE 
 *    components
 ********************************************************************/

/********************************************************************
 * Defines - HTML Dialog callback (see HTML control documentation)
 ********************************************************************/
#define HTMLDIALOGCALLBACK_CREATE       0
#define HTMLDIALOGCALLBACK_DESTROY      1
#define HTMLDIALOGCALLBACK_MSGLOOP      2

/********************************************************************
 * Typedefs - HTML Dialog and VMI Mime type callback functions
 ********************************************************************/
typedef HRESULT (CALLBACK *PFNHTMLDIALOGCALLBACK)(UINT uiType, HWND hwnd, IHTMLDocument2 *pHTMLDocument2, ULONG ulData);
typedef HRESULT (CALLBACK *PFNSHOWVMUMESSAGECALLBACK)(HRESULT hr, BOOL bLeave);
typedef HRESULT (CALLBACK *PFNGETVMUDEVICECALLBACK)(DWORD dwType, HANDLE hEvent, BYTE *pnPort, BYTE *pnDevice);

/********************************************************************
 * Public functions - Create/Destroy
 ********************************************************************/
HRESULT LoadDLLs(void);
HRESULT FreeDLLs(void);

/********************************************************************
 * Public functions - from MSHTML.DLL
 ********************************************************************/
HRESULT RegisterHTMLDialogCallback(PFNHTMLDIALOGCALLBACK pfnHTMLDialogCallback, ULONG ulData, ULONG *pulCookie);
HRESULT UnRegisterHTMLDialogCallback(ULONG ulCookie);
HRESULT GetCurrentFocusElement(IHTMLDocument2 *pHTMLDocument2, IHTMLElement **ppHTMLElement);
HRESULT ShowHTMLDialog(HWND hwndParent, IMoniker *pMoniker, VARIANT *pvarArgIn, TCHAR *pchOptions, VARIANT *pvarArgOut);

/********************************************************************
 * Public functions - from URLMON.DLL
 ********************************************************************/
HRESULT CreateURLMoniker(IMoniker *pmkContext, LPWSTR pszURL, IMoniker **ppMoniker);

/********************************************************************
 * Public functions - from VMIMIME.DLL
 ********************************************************************/
HRESULT SetShowVMUMessageCallback(PFNSHOWVMUMESSAGECALLBACK pShowVMUMessage);
HRESULT SetGetVMUDeviceCallback(PFNGETVMUDEVICECALLBACK pGetVMUDevice);

#endif // __EXTERNAL_H
