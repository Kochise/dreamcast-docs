/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          OIPAObj.cpp
   
   Description:   COleInPlaceActiveObject implementation.

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "OIPAObj.h"

/**************************************************************************

   COleInPlaceActiveObject::COleInPlaceActiveObject()
   
**************************************************************************/

COleInPlaceActiveObject::COleInPlaceActiveObject(COleDocument *pOleDoc)
{
OutputDebugString(TEXT("COleInPlaceActiveObject's constructor\n"));

m_pOleDoc = pOleDoc;

m_fEnableModeless = FALSE;
}

/**************************************************************************

   COleInPlaceActiveObject::~COleInPlaceActiveObject()
   
**************************************************************************/

COleInPlaceActiveObject::~COleInPlaceActiveObject()
{
OutputDebugString(TEXT("COleInPlaceActiveObject's destructor\n"));
}

/**************************************************************************

   COleInPlaceActiveObject::QueryInterface()
   
**************************************************************************/

STDMETHODIMP COleInPlaceActiveObject::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
OutputDebugString(TEXT("COleInPlaceActiveObject::QueryInterface\n"));

return m_pOleDoc->QueryInterface(riid, ppReturn);
}

/**************************************************************************

   COleInPlaceActiveObject::AddRef()
   
**************************************************************************/

STDMETHODIMP_(ULONG) COleInPlaceActiveObject::AddRef()
{
OutputDebugString(TEXT("COleInPlaceActiveObject::AddRef\n"));

return m_pOleDoc->AddRef();
}

/**************************************************************************

   COleInPlaceActiveObject::Release()
   
**************************************************************************/

STDMETHODIMP_(ULONG) COleInPlaceActiveObject::Release()
{
OutputDebugString(TEXT("COleInPlaceActiveObject::Release\n"));

return m_pOleDoc->Release();
}

/**************************************************************************

   COleInPlaceActiveObject::OnDocWindowActivate()
   
**************************************************************************/

STDMETHODIMP COleInPlaceActiveObject::OnDocWindowActivate(BOOL fActivate)
{
OutputDebugString(TEXT("COleInPlaceActiveObject::OnDocWindowActivate\n"));

//If we are getting activated, merge our menus.
if(fActivate)
   {
   if(m_pOleDoc->m_pOleDocView)
      {
      m_pOleDoc->m_pOleDocView->MergeMenus();
      }
   }

return S_OK;
}

/**************************************************************************

   COleInPlaceActiveObject::OnFrameWindowActivate()
   
**************************************************************************/

STDMETHODIMP COleInPlaceActiveObject::OnFrameWindowActivate(BOOL fActivate)
{
OutputDebugString(TEXT("COleInPlaceActiveObject::OnFrameWindowActivate\n"));

return S_OK;
}

/**************************************************************************

   COleInPlaceActiveObject::GetWindow()
   
**************************************************************************/

STDMETHODIMP COleInPlaceActiveObject::GetWindow(HWND *phwnd)
{
OutputDebugString(TEXT("COleInPlaceActiveObject::GetWindow\n"));

return m_pOleDoc->GetWindow(phwnd);
}

/**************************************************************************

   COleInPlaceActiveObject::ContextSensitiveHelp()
   
**************************************************************************/

STDMETHODIMP COleInPlaceActiveObject::ContextSensitiveHelp(BOOL fEnterMode)
{
OutputDebugString(TEXT("COleInPlaceActiveObject::ContextSensitiveHelp\n"));

return E_NOTIMPL;
}

/**************************************************************************

   COleInPlaceActiveObject::TranslateAccelerator()
   
**************************************************************************/

STDMETHODIMP COleInPlaceActiveObject::TranslateAccelerator(LPMSG lpmsg)
{
OutputDebugString(TEXT("COleInPlaceActiveObject::TranslateAccelerator\n"));

// no accelerator table, return FALSE
return S_FALSE;
}

/**************************************************************************

   COleInPlaceActiveObject::ResizeBorder()
   
**************************************************************************/

STDMETHODIMP COleInPlaceActiveObject::ResizeBorder(   LPCRECT lprectBorder,
                                                      LPOLEINPLACEUIWINDOW lpUIWindow,
                                                      BOOL fFrameWindow)
{
OutputDebugString(TEXT("COleInPlaceActiveObject::ResizeBorder\n"));

return S_OK;
}

/**************************************************************************

   COleInPlaceActiveObject::EnableModeless()
   
**************************************************************************/

STDMETHODIMP COleInPlaceActiveObject::EnableModeless(BOOL fEnable)
{
OutputDebugString(TEXT("COleInPlaceActiveObject::EnableModeless\n"));

m_fEnableModeless = fEnable;

return S_OK;
}
