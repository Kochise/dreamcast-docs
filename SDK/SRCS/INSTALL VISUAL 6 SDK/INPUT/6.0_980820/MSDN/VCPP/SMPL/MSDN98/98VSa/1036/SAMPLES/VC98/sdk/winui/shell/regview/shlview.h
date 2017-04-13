/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          ShlView.h
   
   Description:   CShellView definitions.

**************************************************************************/

#ifndef SHELLVIEW_H
#define SHELLVIEW_H

#include <windows.h>
#include <windowsx.h>
#include <objbase.h>
#include <shlobj.h>
#include <ServProv.h>
#include <DocObj.h>
#include "ShlFldr.h"
#include "PidlMgr.h"
#include "DockWndw.h"

/**************************************************************************

   global variables

**************************************************************************/

extern HINSTANCE  g_hInst;
extern UINT       g_DllRefCount;
extern HIMAGELIST g_himlLarge;
extern HIMAGELIST g_himlSmall;

/**************************************************************************

   global IDs

**************************************************************************/

#define NS_CLASS_NAME   (TEXT("RegViewNSClass"))

//menu items
#define IDM_VIEW_KEYS   (FCIDM_SHVIEWFIRST + 0x500)
#define IDM_VIEW_IDW    (FCIDM_SHVIEWFIRST + 0x501)
#define IDM_MYFILEITEM  (FCIDM_SHVIEWFIRST + 0x502)

//control IDs
#define ID_LISTVIEW     2000

/**************************************************************************

   CShellView class definition

**************************************************************************/

class CShellView : public IShellView, public IOleCommandTarget
{
friend CDockingWindow;

protected:
   DWORD m_ObjRefCount;
   
public:
   CShellView(CShellFolder*, LPCITEMIDLIST);
   ~CShellView();
   
   //IUnknown methods
   STDMETHOD (QueryInterface)(REFIID, LPVOID*);
   STDMETHOD_ (DWORD, AddRef)();
   STDMETHOD_ (DWORD, Release)();
   
   //IOleWindow methods
   STDMETHOD (GetWindow) (HWND*);
   STDMETHOD (ContextSensitiveHelp) (BOOL);

   //IShellView methods
   STDMETHOD (TranslateAccelerator) (LPMSG);
   STDMETHOD (EnableModeless) (BOOL);
   STDMETHOD (UIActivate) (UINT);
   STDMETHOD (Refresh) (void);
   STDMETHOD (CreateViewWindow) (LPSHELLVIEW, LPCFOLDERSETTINGS, LPSHELLBROWSER, LPRECT, HWND*);
   STDMETHOD (DestroyViewWindow) (void);
   STDMETHOD (GetCurrentInfo) (LPFOLDERSETTINGS);
   STDMETHOD (AddPropertySheetPages) (DWORD, LPFNADDPROPSHEETPAGE, LPARAM);
   STDMETHOD (SaveViewState) (void);
   STDMETHOD (SelectItem) (LPCITEMIDLIST, UINT);
   STDMETHOD (GetItemObject) (UINT, REFIID, LPVOID*);

   //IOleCommandTarget methods
   STDMETHOD (QueryStatus) (const GUID *pguidCmdGroup, ULONG cCmds, OLECMD prgCmds[], OLECMDTEXT *pCmdText);
   STDMETHOD (Exec) (const GUID *pguidCmdGroup, DWORD nCmdID, DWORD nCmdExecOpt, VARIANTARG *pvaIn, VARIANTARG *pvaOut);

private:
	//private member variables
   UINT m_uState;
	HKEY m_hKeyRoot;
	LPITEMIDLIST m_pidl;
	FOLDERSETTINGS m_FolderSettings;
	LPSHELLBROWSER m_pShellBrowser;
	HWND m_hwndParent;
	HWND m_hWnd;
	HWND m_hwndList;
	HMENU m_hMenu;
   CShellFolder *m_pSFParent;
	LPMALLOC m_pMalloc;
   LPPIDLMGR m_pPidlMgr;
	CDockingWindow* m_pDockingWindow;

	//private member functions
   static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	LRESULT UpdateMenu(HMENU hMenu);
	HMENU BuildRegistryMenu(void);
	void MergeFileMenu(HMENU);
	void MergeViewMenu(HMENU);
	LRESULT OnCommand(DWORD, DWORD, HWND);
	LRESULT OnActivate(UINT);
	void OnDeactivate(void);
	LRESULT OnSetFocus(void);
	LRESULT OnKillFocus(void);
	LRESULT OnNotify(UINT, LPNMHDR);
	LRESULT OnSize(WORD, WORD);
	LRESULT OnCreate(void);
	BOOL CreateList(void);
	BOOL InitList(void);
	void FillList(void);
	BOOL CanDoIDockingWindow(void);
	BOOL AddRemoveDockingWindow(BOOL);
	LRESULT OnSettingChange(LPCTSTR);
   void UpdateShellSettings(void);

};

#endif   //SHELLVIEW_H
