/********************************************************************
 * Copyright (c) 1999 Microsoft Corporation
 *
 * IEUI.h
 *
 * Description
 *   Definition for the CIEUI class to handle replaceable UI 
 *   components in the HTML control.
 ********************************************************************/

#ifndef __IEUI_H        // Prevent multiple inclusions
#define __IEUI_H

/********************************************************************
 * Includes
 ********************************************************************/
#include <ieceui.h>     // Iieui interface definition

/********************************************************************
 * Message box defines
 ********************************************************************/

#define MB_OK                           0x00000000L
#define MB_OKCANCEL                     0x00000001L
#define MB_YESNOCANCEL                  0x00000003L
#define MB_YESNO                        0x00000004L
#define MB_ICONQUESTION                 0x00000020L
#define MB_ICONEXCLAMATION              0x00000030L

/********************************************************************
 * Focus rect defines
 ********************************************************************/

#define FF_TOPLEFT                      0x0000
#define FF_TOPRIGHT                     0x0001
#define FF_BOTTOMLEFT                   0x0002
#define FF_BOTTOMRIGHT                  0x0004
#define FF_TOP                          0x0008
#define FF_LEFT                         0x000F
#define FF_BOTTOM                       0x0010
#define FF_RIGHT                        0x0020

#define FF_YELLOW                       0x0100
#define FF_RED                          0x0200
#define FF_BLUE                         0x0400
#define FF_GREEN                        0x0800

#define YELLOW_FOCUSRECT_X_OFFSET	0
#define YELLOW_FOCUSRECT_Y_OFFSET	1
#define RED_FOCUSRECT_X_OFFSET		14
#define RED_FOCUSRECT_Y_OFFSET		1
#define BLUE_FOCUSRECT_X_OFFSET		28
#define BLUE_FOCUSRECT_Y_OFFSET		1
#define GREEN_FOCUSRECT_X_OFFSET	42
#define GREEN_FOCUSRECT_Y_OFFSET	1

#define FOCUSRECT_LEFT			0
#define FOCUSRECT_TOP			0
#define FOCUSRECT_BOTTOM		9
#define FOCUSRECT_RIGHT			8
#define FOCUSRECT_EDGE_LENGTH	        2
#define FOCUSRECT_THICKNESS             5

class CIEUI : public IClassFactory,     // Class Factory interface (class 
                                        // factory and main object are same)
              public Iieui              // Replaceable UI interface
{
    public:
        // Constructor/Destructor
                           CIEUI(void);
                  virtual ~CIEUI(void);

        // IUnknown
        STDMETHOD(         QueryInterface)(REFIID riid, LPVOID *ppvObj);
        STDMETHOD_(ULONG,  AddRef)(void);
        STDMETHOD_(ULONG,  Release)(void);

        // IClassFactory
        STDMETHOD(         CreateInstance)(IUnknown *pUnkOuter, REFIID riid, LPVOID *ppvObj);
        STDMETHOD(         LockServer)(BOOL bLock);

        // Iieui
        STDMETHOD(         ShowScriptErrorDialog)(HWND hwndParent, IDispatch *pDispatch);
        STDMETHOD(         ShowFindDialog)(HWND hwndParent, IDispatch *pDispatch);
        STDMETHOD(         ShowPromptDialog)(HWND hwndParent, BSTR bstrMessage, BSTR bstrDefault, LPTSTR *szEditResult);
        STDMETHOD_(int,    ShowAlertConfirm)(HWND hwndParent, LPCTSTR szText, UINT uType);
        STDMETHOD_(int,    ShowMessageBox)(HWND hwndParent, LPCTSTR szText, LPCTSTR szCaption, UINT uType, ...);
        STDMETHOD(         ShowPrintCancelDialog)(HWND hwndParent, HWND *phwndPrintCancelDlg, BOOL *pfAbortPrintJob);
        STDMETHOD(         ShowPageSetupDialog)(PAGESETUPDLG *pdlgPageSetup, PAGESETUPOPT *poptPageSetup, BOOL *pfResult);
        STDMETHOD_(BOOL,   ShowGetSaveFileName)(OPENFILENAME *pofn);
        STDMETHOD_(BOOL,   ShowGetOpenFileName)(OPENFILENAME *pofn);        	
        STDMETHOD_(int,    ShowBindingErrorMessageBox)(HWND hwndParent, HRESULT hrError, DWORD dwResource, LPCTSTR szUrlParam, UINT fuFlags);
        STDMETHOD_(void,   ShowCDownLoad_UI)(IMoniker *pMoniker, IBindCtx *pBindCtx, BOOL fSync, BOOL fSaveAs, BOOL fSafe, LPWSTR szHeaders, DWORD dwVerb, DWORD grfBINDF, BINDINFO *pBindInfo, LPCTSTR szRedir, HANDLE hSig, LONG *pcModelessDlg, HWND *phwndDlgActive, CRITICAL_SECTION *pcs);
        STDMETHOD(         ShowCDownLoad_UIURL)(LPCWSTR szURL, IBindCtx *pBindCtx, LPWSTR szHeaders, BOOL fSync, BOOL fSaveAs, BOOL fSafe, DWORD dwVerb, DWORD grfBINDF, BINDINFO *pBindInfo, LPCTSTR szRedir, HANDLE hSig, LONG *pcModelessDlg, HWND *phwmdDlgActive, CRITICAL_SECTION *pcs);
        STDMETHOD(         ShowLastErrorInfo)(int idsDefault, HWND hwndParent);
        STDMETHOD(         ShowLoadError)(HRESULT hrDisplay, HWND hwndParent, LPCTSTR szUrl);
        STDMETHOD(         GetErrorText)(HRESULT hrError, LPTSTR pstr, int cch);
        STDMETHOD(         GetSolutionText)(HRESULT hrError, LPTSTR pstr, int cch);
        STDMETHOD_(int,    MessageBoxW)(HWND hwndParent, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType);
        STDMETHOD_(BOOL,   RenderFullTVFocusRect)(HDC hdc, LPRECT lprc, UINT wFlags);
        STDMETHOD_(BOOL,   DrawTVFocusRect)(HDC hdc, LPCRECT lprc, UINT wFlags);

    private:
        // Helper functions
        int                ShowMessageBoxInternal(BOOL bFormat, HWND hwndParent, LPCTSTR szText, LPCTSTR szCaption, UINT uType, ...);
        BOOL               InitResources(void);

        // Member Data
        ULONG              _ulRefCount;   // Reference count for object
        HDC                _hdcBitmap;    // Focus rect bitmap in a DC
        HBITMAP            _hbmBitmap;    // Focus rect bitmap
};

#endif // __IEUI_H
