/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 - 1998 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          DeskBand.h
   
   Description:   CDeskBand definitions.

**************************************************************************/

#include <windows.h>
#include <shlobj.h>

#include "Globals.h"

#ifndef DESKBAND_H
#define DESKBAND_H

#define DB_CLASS_NAME (TEXT("DeskBandSampleClass"))

#define MIN_SIZE_X   10
#define MIN_SIZE_Y   10

#define IDM_COMMAND  0

/**************************************************************************

   CDeskBand class definition

**************************************************************************/

class CDeskBand : public IDeskBand, 
                  public IInputObject, 
                  public IObjectWithSite,
                  public IPersistStream,
                  public IContextMenu
{
protected:
   DWORD m_ObjRefCount;

public:
   CDeskBand();
   ~CDeskBand();

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

   //IDeskBand methods
   STDMETHOD (GetBandInfo) (DWORD, DWORD, DESKBANDINFO*);

   //IInputObject methods
   STDMETHOD (UIActivateIO) (BOOL, LPMSG);
   STDMETHOD (HasFocusIO) (void);
   STDMETHOD (TranslateAcceleratorIO) (LPMSG);

   //IObjectWithSite methods
   STDMETHOD (SetSite) (IUnknown*);
   STDMETHOD (GetSite) (REFIID, LPVOID*);

   //IPersistStream methods
   STDMETHOD (GetClassID) (LPCLSID);
   STDMETHOD (IsDirty) (void);
   STDMETHOD (Load) (LPSTREAM);
   STDMETHOD (Save) (LPSTREAM, BOOL);
   STDMETHOD (GetSizeMax) (ULARGE_INTEGER*);

   //IContextMenu methods
   STDMETHOD (QueryContextMenu)(HMENU, UINT, UINT, UINT, UINT);
   STDMETHOD (InvokeCommand)(LPCMINVOKECOMMANDINFO);
   STDMETHOD (GetCommandString)(UINT, UINT, LPUINT, LPSTR, UINT);

private:
	BOOL m_bFocus;
	HWND m_hwndParent;
	HWND m_hWnd;
	DWORD m_dwViewMode;
   DWORD m_dwBandID;
   IInputObjectSite *m_pSite;

private:
	void FocusChange(BOOL);
   LRESULT OnKillFocus(void);
	LRESULT OnSetFocus(void);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	LRESULT OnPaint(void);
	LRESULT OnCommand(WPARAM wParam, LPARAM lParam);
   BOOL RegisterAndCreateWindow(void);
};

#endif   //DESKBAND_H

