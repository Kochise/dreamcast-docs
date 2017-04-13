/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          DockWndw.h
   
   Description:   CDockingWindow definitions.

**************************************************************************/

#include <windows.h>
#include <shlobj.h>

#if (_WIN32_IE < 0x0400)
#define CDockingWindow  IUnknown

#else //(_WIN32_IE >= 0x0400)

#include "ShlView.h"

#ifndef DOCKINGWINDOW_H
#define DOCKINGWINDOW_H

#define SHTB_CLASS_NAME (TEXT("RegViewToolbarClass"))

/**************************************************************************
   global variables
**************************************************************************/

extern HINSTANCE  g_hInst;
extern UINT       g_DllRefCount;

#define TOOLBAR_HEIGHT  50

/**************************************************************************

   CDockingWindow class definition

**************************************************************************/

class CDockingWindow : public IDockingWindow, public IInputObject, public IObjectWithSite
{
protected:
   DWORD m_ObjRefCount;

public:
   CDockingWindow(CShellView*, HWND);
   ~CDockingWindow();

   //IUnknown methods
   STDMETHODIMP QueryInterface(REFIID, LPVOID*);
   STDMETHODIMP_(DWORD) AddRef();
   STDMETHODIMP_(DWORD) Release();

   //IOleWindow methods
   STDMETHOD (GetWindow) (HWND*);
   STDMETHOD (ContextSensitiveHelp) (BOOL);

   //IDockingWindow methods
   STDMETHOD (ShowDW) (BOOL fShow);
   STDMETHOD (CloseDW) (DWORD dwReserved);
   STDMETHOD (ResizeBorderDW) (LPCRECT prcBorder, IUnknown* punkToolbarSite, BOOL fReserved);

   //IInputObject methods
   STDMETHOD (UIActivateIO) (BOOL, LPMSG);
   STDMETHOD (HasFocusIO) (void);
   STDMETHOD (TranslateAcceleratorIO) (LPMSG);

   //IObjectWithSite methods
   STDMETHOD (SetSite) (IUnknown*);
   STDMETHOD (GetSite) (REFIID, LPVOID*);

private:
	BOOL NegotiateBorderSpace(IDockingWindowSite*, LPCRECT prcBorder = NULL);
	RECT m_rcDisplay;
	BOOL m_bFocus;
	HWND m_hwndParent;
	HWND m_hWnd;
	HWND m_hwndCommand;
   CShellView *m_pView;
   IDockingWindowSite *m_pSite;

private:
	void FocusChange(BOOL);
   LRESULT OnKillFocus(void);
	LRESULT OnSetFocus(void);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	LRESULT OnPaint(void);
	LRESULT OnCommand(WPARAM wParam, LPARAM lParam);
};

#endif   //DOCKINGWINDOW_H

#endif   //(_WIN32_IE >= 0x0400)
