////////////////////////////////////////////////////////////////
// Implementation for CDynViewDocTemplate, a document template that
// supports multiple views per doc.
//
// Copyright 1996 Microsoft Systems Journal. If this code works, 
// it was written by Paul DiLascia. If not, I don't know who wrote it.
//
#include "stdafx.h"
#include "resource.h"
#include "dyntempl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CDynViewDocTemplate, CMultiDocTemplate)

//////////////////
// NOTE: You must #define ID_VIEW_AS_BEGIN and ID_VIEW_AS_END in your 
// resource.h file. CDynViewDocTemplate uses RANGE handlers to handle 
// the "View As" commands and command update, in the given range.
//
BEGIN_MESSAGE_MAP(CDynViewDocTemplate, CDocTemplate)
   //{{AFX_MSG_MAP(CDynViewDocTemplate)
   ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_AS_BEGIN,ID_VIEW_AS_END,OnUpdateViewAs)
   ON_COMMAND_EX_RANGE(ID_VIEW_AS_BEGIN, ID_VIEW_AS_END, OnViewAs)
   //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//////////////////
// Constructor is like CMultiDocTemplate, but takes an array of 
// DYNAMICVIEWINFO's instead of a single runtime class for the view.
//
CDynViewDocTemplate::CDynViewDocTemplate(UINT nIDResource, 
   CRuntimeClass* pDocClass, 
   CRuntimeClass* pFrameClass, 
   const DYNAMICVIEWINFO* pViewInfo)
   : CMultiDocTemplate(nIDResource, pDocClass, pFrameClass, NULL)
{
   ASSERT(pViewInfo);
   m_pViewInfo = pViewInfo;
   m_pViewClass = pViewInfo[0].rtc;

#ifdef _DEBUG
   // Check that # of entries in table matches begin/end command IDs
   for (int n=0; pViewInfo[n].name; n++)
      ;
   if (n!=ID_VIEW_AS_END-ID_VIEW_AS_BEGIN+1) {
      TRACE0("Number of view classes in table does not match command ID\n");
      TRACE0("range ID_VIEW_AS_BEGIN to ID_VIEW_AS_END!\n");
      ASSERT(FALSE);
   }
#endif
}

CDynViewDocTemplate::~CDynViewDocTemplate()
{
}

//////////////////
// Get the 0-based view class ID given a ptr to a view.
//
int CDynViewDocTemplate::GetViewID(CView* pView)
{
   for (int i=0; m_pViewInfo[i].name; i++) {
      if (m_pViewInfo[i].rtc == pView->GetRuntimeClass())
         return i;
   }
   return -1; // (invalid)
}

//////////////////
// Get class info about a view.
//
const DYNAMICVIEWINFO* CDynViewDocTemplate::GetViewInfo(CView* pView)
{
   ASSERT_VALID(pView);
   int iViewID = GetViewID(pView);
   return iViewID >=0 ? &m_pViewInfo[iViewID] : NULL;
}

//////////////////
// Override to change the view class when a document is opened,
// to use whichever view class was saved with the doc.
//
void CDynViewDocTemplate::InitialUpdateFrame(CFrameWnd* pFrame, 
   CDocument* pDoc, BOOL bMakeVisible)
{
   CMultiDocTemplate::InitialUpdateFrame(pFrame, pDoc, bMakeVisible);
   ReplaceView(pFrame, GetViewID(pDoc), bMakeVisible);
}

//////////////////
// Handle "View As Xxx" command to change view class. Both this and
// InitialUpdateFrame call a common helper, ReplaceView.
//
BOOL CDynViewDocTemplate::OnViewAs(UINT nCmdID) 
{
   CFrameWnd* pFrame = (CFrameWnd*)AfxGetMainWnd();
   ASSERT_VALID(pFrame);
   ASSERT(pFrame->IsFrameWnd());
   pFrame = pFrame->GetActiveFrame();
   ReplaceView(pFrame, nCmdID-ID_VIEW_AS_BEGIN, TRUE);
   return FALSE;
}

///////////////////
// Replace the current view with a one of a different class
//
CView* CDynViewDocTemplate::ReplaceView(CFrameWnd* pFrame, 
   int iNewViewType, BOOL bMakeVisible)
{
   ASSERT(ID_VIEW_AS_BEGIN<=iNewViewType+ID_VIEW_AS_BEGIN && 
      iNewViewType+ID_VIEW_AS_BEGIN<=ID_VIEW_AS_END);

   CView* pView = pFrame->GetActiveView();
   ASSERT_VALID(pView);

   CRuntimeClass* pViewClass = m_pViewInfo[iNewViewType].rtc;
   if (!pView->IsKindOf(pViewClass)) {

      // Tell MFC not to delete the doc when the view is destroyed
      CDocument* pDoc = pView->GetDocument();
      BOOL bSaveAutoDelete = pDoc->m_bAutoDelete;
      pDoc->m_bAutoDelete = FALSE;
      pFrame->SetActiveView(NULL);  // it's safer

#ifndef DONT_RECYCLE_HWND
      // This implementation reuses the actual (Windows) window
      //
      HWND hwnd = pView->Detach();  // remove window from view
      delete pView;                 // destroy C++ obj & remove from doc too
      pView = (CView*)pViewClass->CreateObject();  // create new view
      ASSERT(pView);
      ASSERT_KINDOF(CView, pView);
      pView->Attach(hwnd);          // reuse the same HWND !
      pDoc->AddView(pView);         // add view to doc
      pFrame->SetActiveView(pView); // make it the active view
#else
      // This implementation create a whole new (Windows) window
      //
      CRect rcView;
      pView->GetWindowRect(&rcView);// save original view window size
      pView->DestroyWindow();       // destroy old view

      // Create new view using CFrameWnd::CreateView, 
      // which requires a "CCreateContext"
      CCreateContext context;
      context.m_pNewViewClass = pViewClass;
      context.m_pCurrentDoc   = pDoc;
      pView = (CView*)pFrame->CreateView(&context);
      ASSERT(pView);
      ASSERT_VALID(pView);

      // Set view window size to same as old view
      pFrame->ScreenToClient(&rcView);
      pView->MoveWindow(&rcView, FALSE);
#endif

      pDoc->m_bAutoDelete = bSaveAutoDelete;

      // This will do good stuff, like update the title 
      // and send WM_INITIALUPDATE to the view.
      //
      pFrame->InitialUpdateFrame(pDoc, bMakeVisible);
   }
   return pView;
}

//////////////////
// Update "View As Xxx" command: set radio button for whichever kind
// of view is currently active.
//
void CDynViewDocTemplate::OnUpdateViewAs(CCmdUI* pCmdUI) 
{
   ASSERT(ID_VIEW_AS_BEGIN<=pCmdUI->m_nID && pCmdUI->m_nID<=ID_VIEW_AS_END);

   CFrameWnd* pFrame = (CFrameWnd*)AfxGetMainWnd();
   ASSERT_VALID(pFrame);
   ASSERT(pFrame->IsFrameWnd());
   CView* pView = pFrame->GetActiveFrame()->GetActiveView();
   pCmdUI->SetRadio(pView && 
      pView->IsKindOf(m_pViewInfo[pCmdUI->m_nID-ID_VIEW_AS_BEGIN].rtc));
}
