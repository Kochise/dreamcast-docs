/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// WndTabs.h : main header file for the WNDTABS DLL
//

#if !defined(AFX_WNDTABS_H__6A06C12C_4748_11D1_BC91_0000010016A6__INCLUDED_)
#define AFX_WNDTABS_H__6A06C12C_4748_11D1_BC91_0000010016A6__INCLUDED_

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include <ObjModel\addguid.h>
#include <ObjModel\appguid.h>
#include <ObjModel\bldguid.h>
#include <ObjModel\textguid.h>
#include <ObjModel\dbgguid.h>


#include "Logger.h"

class WWhizInterface;

class CWTManageState
{
public:
    CWTManageState(AFX_MODULE_STATE* pModuleState);
    ~CWTManageState();

    static long m_cRef;    

protected:    
    AFX_MAINTAIN_STATE2 m_state;

};

#define WT_MANAGE_STATE() CWTManageState _ctlState(AfxGetStaticModuleState())

class CLanguageDLL
{
public:
    HMODULE     m_hDLL;
    CString     m_sDLLName;
    CString     m_sDLLPath;

    CString     m_sAuthor;

    CString     m_sLanguageNameEnglish;
    CString     m_sLanguageNameNative;
    CString     m_sFont;
    int         m_iFontPoint;

    CLanguageDLL() { m_hDLL = NULL; }
    ~CLanguageDLL() { Release(); }

    bool Apply();
    void Release();
};

/////////////////////////////////////////////////////////////////////////////
// CWndTabsApp

class CWndTabsApp : public CWinApp, public CBCGWorkspace 
{
protected:
    int     m_iFocusCount;
    
    WWhizInterface *m_pWWhizInterface;

public:
    CWndTabsApp();
    ~CWndTabsApp();

	// Override from CBCGWorkspace
	virtual void PreLoadState();
    virtual BOOL ShowPopupMenu(UINT uiMenuResId, const CPoint& point, 
        CWnd* pWnd);

    class CMainFrame *m_pMainFrame;

    bool m_bDoDeleteVS6KeyBindings;

    bool Focus();
    void UnFocus();
    bool IsFocused() { return m_iFocusCount > 0; }

    int AddUserImageUnique(HBITMAP hBMP);

    WWhizInterface *GetWWhizInterface(bool bCreate = true);
    void ReportWWhizInterfaceException();
    bool m_bAllowWWhizInterface;

    CArray<CLanguageDLL, CLanguageDLL&> m_LangDLLs;
    CLanguageDLL *GetLanguageDLL(LPCTSTR lpszDLLName);

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CWndTabsApp)
	public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
	//}}AFX_VIRTUAL

    //{{AFX_MSG(CWndTabsApp)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

protected:
    void LoadLangDLLs();
    void LoadLangDLL(HMODULE hDLL);
};

extern CWndTabsApp theApp;

#define DS5_USER_KEY    "Software\\Microsoft\\Devstudio\\5.0"
#define DS6_USER_KEY    "Software\\Microsoft\\Devstudio\\6.0"
#define DS5_ADDIN_KEY   DS5_USER_KEY "\\AddIns"
#define DS6_ADDIN_KEY   DS6_USER_KEY "\\AddIns"
#define DS6_AUT_KEY     DS6_USER_KEY "\\Keyboard\\Aut"

#define EVC3_USER_KEY   "Software\\Microsoft\\CEStudio\\3.0\\evc"
#define EVC4_USER_KEY   "Software\\Microsoft\\CEStudio\\4.0\\evc"
#define EVC3_ADDIN_KEY  EVC3_USER_KEY "\\AddIns"
#define EVC4_ADDIN_KEY  EVC4_USER_KEY "\\AddIns"

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WNDTABS_H__6A06C12C_4748_11D1_BC91_0000010016A6__INCLUDED)
