//---------------------------------------------------------------------------
// MsgLoop.cpp
//---------------------------------------------------------------------------
// Implementation of message loop for application.  Includes implementation
// of IOleComponentManager.
//---------------------------------------------------------------------------
// (C) Copyright 1995-1997 by Microsoft Corporation.  All rights reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//---------------------------------------------------------------------------

#include "Main.h"
#pragma hdrstop
#include "MsgLoop.h"


//---------------------------------------------------------------------------
// DEBUG info
//---------------------------------------------------------------------------
SZTHISFILE


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
CMsgLoop::CMsgLoop
(
  HWND hwnd
)
  {
  INIT_SIGNATURE(SIG_MsgLoop);

  for (int i=0; i<cCOMP; i++)
    m_rgcomp[i].pcomp = NULL;

  m_icompActive  = icompNIL;
  m_fInState     = FALSE;
  m_icompState   = icompNIL;
  m_uStateID     = 0;
  m_fScrptReset  = FALSE;
  m_fQuitting    = FALSE;
  m_hwnd         = hwnd;
  m_haccel       = NULL;     // Load accel table here
  m_icompMsgLoop =icompNIL;

  m_cref        = 1;
  m_cMsgLoop    = 0;
  }


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
CMsgLoop::~CMsgLoop
(
  void
)
  {
  CHECK_SIGNATURE(SIG_MsgLoop);

  for (int i=0; i<cCOMP; i++)
    if (m_rgcomp[i].pcomp)
      {
      m_rgcomp[i].pcomp->Terminate();
      RELEASEPTR(m_rgcomp[i].pcomp);
      }

  DESTROY_SIGNATURE(SIG_MsgLoop);
  }


//***************************************************************************
// IUnknown methods
//***************************************************************************

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP CMsgLoop::QueryInterface
(
  REFIID   riid, 
  void   **ppvObj
)
  {
  *ppvObj = NULL;

  if (riid == IID_IUnknown)
    *ppvObj = (LPVOID)(IUnknown *)(IOleComponentManager *)this;
  else if (riid == IID_IOleComponentManager)
    *ppvObj = (LPVOID)(IOleComponentManager *)this; 

  if (*ppvObj) 
    {
    this->AddRef();
    return S_OK;
    }
  
  return E_NOINTERFACE;
  }


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CMsgLoop::AddRef
(
  void
)
  {
  CHECK_SIGNATURE(SIG_MsgLoop);
  return ++m_cref;
  }


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CMsgLoop::Release
(
  void
)
  {
  CHECK_SIGNATURE(SIG_MsgLoop);
  if (--m_cref)
    return m_cref;

  delete this;
  return 0;
  }



//***************************************************************************
// IOleComponentManager Methods
//***************************************************************************

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP CMsgLoop::QueryService
(
  REFGUID guidService, 
  REFIID  iid, 
  void  **ppvObjOut
) 
  {
  *ppvObjOut = NULL;
  return E_NOINTERFACE;
  }


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(BOOL) CMsgLoop::FRegisterComponent
(
  IOleComponent   *piComponent, 
  const CMGRRINFO *pcrinfo, 
  DWORD           *pdwCompIDOut
)
  {
  for (int i=0; i<cCOMP; i++)
    if (!m_rgcomp[i].pcomp)
      {
      piComponent->AddRef();
      m_rgcomp[i].pcomp = piComponent;
      *pdwCompIDOut = i;
      return TRUE;
      }

  FAIL("Out of room!");
  return FALSE;
  }


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(BOOL) CMsgLoop::FRevokeComponent
(
  DWORD icomp
)
  {
  ASSERT(m_rgcomp[icomp].pcomp, "Bogus icomp");
  RELEASEPTR(m_rgcomp[icomp].pcomp);
  if (m_icompActive == icomp)
    m_icompActive = icompNIL;
  if (m_icompMsgLoop == icomp)
    m_icompMsgLoop = icompNIL;
  return TRUE;
  }


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(BOOL) CMsgLoop::FUpdateComponentRegistration
( 
  DWORD            dwComponentID, 
  const CMGRRINFO *pcrinfo
)
  {
  // Don't track info anyway, so pretend it worked:
  return TRUE;
  }


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(void) CMsgLoop::OnComponentActivate
(
  DWORD icomp
)
  {
  ASSERT(m_rgcomp[icomp].pcomp, "Bad icomp");
  m_icompActive = icomp;
  return;
  }


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(BOOL) CMsgLoop::FSetTrackingComponent
(
  DWORD dwComponentID, 
  BOOL  fTrack
)
  {
  // UNDONE: Need to support
  return FALSE;
  }


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(void) CMsgLoop::OnComponentEnterState
(
  DWORD icomp,
  ULONG uStateID, 
  ULONG uContext, 
  ULONG cpicmExclude,
  IOleComponentManager **rgpicmExclude,
  DWORD dwReserved
)
  {
  ASSERT(m_rgcomp[icomp].pcomp, "Bad icomp");
  ASSERT(uStateID==cmgrstateModal,  "Not modal state");
  ASSERT(!m_fInState, "Nested modal states");

  m_icompState = icomp;
  m_fInState   = TRUE;
  m_uStateID   = uStateID;
  if (uStateID == cmgrstateModal)
    EnableWindow(m_hwnd, FALSE);
  }


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(BOOL) CMsgLoop::FOnComponentExitState
(
  DWORD icomp,
  ULONG uStateID,
  ULONG uContext,
  ULONG cpicmExclude,
  IOleComponentManager **rgpicmExclude
)
  {
  ASSERT(m_rgcomp[icomp].pcomp, "Bad icomp");
  ASSERT(icomp==(DWORD)m_icompState, "icomp didn't own state");
  ASSERT(uStateID==cmgrstateModal,  "Not modal state");
  ASSERT(uStateID==m_uStateID, "non-matching modal states on pop");
  ASSERT(m_fInState, "underflow of modal state");

  m_fInState   = FALSE;
  m_icompState = icompNIL;
  if (uStateID == cmgrstateModal)
    EnableWindow(m_hwnd, TRUE);
  return TRUE;
  }


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(BOOL) CMsgLoop::FInState
(
  ULONG uStateID,
  void *pvoid
)
  {
  return m_fInState && uStateID==m_uStateID;
  }


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(BOOL) CMsgLoop::FContinueIdle
(
  void
)
  {
  return FALSE;
  }


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(BOOL) CMsgLoop::FPushMessageLoop
(
  DWORD icomp, 
  ULONG uReason, 
  void *pvLoopData
)
  {
  MessageLoop(icomp, uReason, pvLoopData);
  return TRUE;
  }


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(BOOL) CMsgLoop::FCreateSubComponentManager
(
  IUnknown *piunkOuter, 
  IUnknown *piunkServProv,
  REFIID    riid, 
  void    **ppvObj
)
  {
  ASSERT(!piunkOuter, "Don't support aggre. SubCompMgr");
  HRESULT hr = this->QueryInterface(riid, ppvObj);
  return !FAILED(hr);
  }


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(BOOL) CMsgLoop::FGetParentComponentManager
(
  IOleComponentManager **ppicm
)
  {
  // UNDONE: Need to implement
  return FALSE;
  }


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(BOOL) CMsgLoop::FGetActiveComponent
(
  DWORD           dwReserved,
  IOleComponent **ppcompOut
)
  {
  // Do we have an active component?
  if (m_icompActive == icompNIL)
    {
    *ppcompOut = NULL;
    return FALSE;
    }

  // Yes, return it
  *ppcompOut = m_rgcomp[m_icompActive].pcomp;
  (*ppcompOut)->AddRef();       // for *ppcompOut
  return TRUE;
  }



//***************************************************************************
// Message Loop Implementation
//***************************************************************************

//---------------------------------------------------------------------------
// This pushes a new message loop.
//---------------------------------------------------------------------------
void CMsgLoop::MessageLoop
(
  DWORD icomp,
  ULONG uReason, 
  void *pvLoopData
)
  {
  BOOL  fExitLoop = FALSE;

  m_cMsgLoop++;

  while (!fExitLoop) 
    fExitLoop = PumpMessage(icomp, uReason, pvLoopData);

  m_cMsgLoop--;

  if (!m_cMsgLoop)
    m_fScrptReset = FALSE;
  }


//---------------------------------------------------------------------------
// This processes one message.
// Returns TRUE if it is time to exit the current message loop.
//---------------------------------------------------------------------------
BOOL CMsgLoop::PumpMessage
(
  DWORD icomp,
  ULONG uReason, 
  void *pvLoopData
)
  {
  BOOL fExitLoop = FALSE;
  BOOL fMsg;
  MSG  msg;

  fMsg = PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE);
  if (fMsg) 
    {
    if (msg.message == WM_QUIT)
      {
      // Since we're not really an app, re-post the WM_QUIT message, until
      // we can pop any msgloops we've pushed.
      if (m_cMsgLoop)
       	PostQuitMessage(msg.wParam);
      return TRUE;
      }
    else
      ProcessMessage(&msg);
    }

  if (m_fScrptReset)
    return TRUE;

  // A Component told us to push this message loop, and so we
  // ask them whether it's time yet to exit the loop
  fExitLoop = !m_rgcomp[icomp].pcomp->FContinueMessageLoop(uReason, pvLoopData);

  if (!fMsg && !fExitLoop) 
    {
    // There weren't any messages and we don't need to exit this message
    // loop yet.  Therefore, now is the right time to do idle processing
    DoIdleProcessing();
    WaitMessage();
    }

  return fExitLoop;
  }


//---------------------------------------------------------------------------
// This processes one message.
//---------------------------------------------------------------------------
void CMsgLoop::ProcessMessage
(
  MSG  *pmsg
)
  {    						
  // When a component is active give it a chance to translate
  // its accelerators.
  if (m_icompActive != icompNIL)
    {
    if (!m_rgcomp[m_icompActive].pcomp->FPreTranslateMessage(pmsg))
      {
      TranslateMessage(pmsg);	    // Translates virtual key codes  
      DispatchMessage(pmsg);	    // Dispatches message to window 
      }
    } 
  else 
    {
    if (!TranslateAccelerator(m_hwnd, m_haccel, pmsg))
      {
      TranslateMessage(pmsg); // Translates virtual key codes  
      DispatchMessage(pmsg);  // Dispatches message to window 
      }
    }
  }


//---------------------------------------------------------------------------
// This is called at idle time.
//---------------------------------------------------------------------------
void CMsgLoop::DoIdleProcessing
(
  void
)
  {
  MSG  msg;
  BOOL fContinue = TRUE;

  while (fContinue && !PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    {
    fContinue = DoIdle();
    }
  }


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
BOOL CMsgLoop::DoIdle
(
  void
)
  {
  int  i;
  BOOL fDidWork = FALSE;

  // if we have periodic idle tasks that to be done, 
  // do them and return TRUE.
  for (i=0; i<cCOMP; i++)
    {
    if (m_rgcomp[i].pcomp)
      if (m_rgcomp[i].pcomp->FDoIdle(cmgridlefPeriodic))
        fDidWork = TRUE;
    if (fDidWork)
      return TRUE;
    }
	
  // if any high priority idle tasks need to be done,
  // do it, and return TRUE.
  for (i=0; i<cCOMP; i++)
    {
    if (m_rgcomp[i].pcomp)
      if (m_rgcomp[i].pcomp->FDoIdle(cmgridlefPriority))
        fDidWork = TRUE;
    if (fDidWork)
      return TRUE;
    }

  // if any lower priority idle tasks need to be done,
  // do it, and return TRUE.
  for (i=0; i<cCOMP; i++)
    {
    if (m_rgcomp[i].pcomp)
      if (m_rgcomp[i].pcomp->FDoIdle(cmgridlefNonPeriodic))
        fDidWork = TRUE;
    if (fDidWork)
      return TRUE;
    }

  return FALSE;
  }

//--- EOF -------------------------------------------------------------------
