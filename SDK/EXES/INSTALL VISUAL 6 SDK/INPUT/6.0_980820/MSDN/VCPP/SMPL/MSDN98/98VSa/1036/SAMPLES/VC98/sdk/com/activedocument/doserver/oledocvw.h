/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/******************************************************************************

   File:          OleDoctVw.h
   
   Description:   COleDocumentView definitions.

******************************************************************************/

#ifndef OLEDOCUMENTVIEW_H
#define OLEDOCUMENTVIEW_H

#include "DOServer.h"

#define VIEW_CLASS_NAME TEXT("DocObject_View_Class")

/**************************************************************************

   COleDocumentView class definition

**************************************************************************/

class COleDocument;

class COleDocumentView : public IOleDocumentView
{
friend class COleDocument;
friend class COleInPlaceActiveObject;

private:
	BOOL                       m_fInPlaceActive;
	RECT                       m_Rect;
   COleDocument               *m_pOleDoc;
	LPOLEINPLACESITE           m_pInPlaceSite;
   HWND                       m_hwndView;
   LPOLEINPLACEFRAME          m_pInPlaceFrame;
   LPOLEINPLACEUIWINDOW       m_pInPlaceUIWindow;
   OLEINPLACEFRAMEINFO        m_FrameInfo;
   HMENU                      m_hSharedMenu;
   HOLEMENU                   m_hOleMenu;
   OLEMENUGROUPWIDTHS         m_mgw;
   BOOL                       m_fUIActive;
   
public:
   COleDocumentView(COleDocument*);
   ~COleDocumentView();
   
   //IUnknown methods
   STDMETHODIMP QueryInterface(REFIID, LPVOID*);
   STDMETHODIMP_(DWORD) AddRef();
   STDMETHODIMP_(DWORD) Release();

   //IOleDocumentView methods
   STDMETHODIMP SetInPlaceSite(IOleInPlaceSite*);
   STDMETHODIMP GetInPlaceSite(IOleInPlaceSite**);
   STDMETHODIMP GetDocument(IUnknown**);
   STDMETHODIMP SetRect(LPRECT);
   STDMETHODIMP GetRect(LPRECT);
   STDMETHODIMP SetRectComplex(LPRECT, LPRECT, LPRECT, LPRECT);
   STDMETHODIMP Show(BOOL);
   STDMETHODIMP UIActivate(BOOL);
   STDMETHODIMP Open(void);
   STDMETHODIMP CloseView(DWORD);
   STDMETHODIMP SaveViewState(IStream*);
   STDMETHODIMP ApplyViewState(IStream*);
   STDMETHODIMP Clone(IOleInPlaceSite*, IOleDocumentView**);

private:
   STDMETHODIMP ActivateInPlace();
   STDMETHODIMP DeactivateInPlace();
   STDMETHODIMP ActivateUI();
   STDMETHODIMP DeactivateUI();
   STDMETHODIMP CreateViewWindow();
   static LRESULT CALLBACK ViewWndProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT OnPaint(void);
	LRESULT OnCommand(UINT, UINT, HWND);
	LRESULT OnCreate(void);
   BOOL MergeMenus(void);
   BOOL RemoveMenus(void);
   BOOL UpdateMenu(HMENU);
};

#endif   //OLEDOCUMENTVIEW_H
