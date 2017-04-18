//---------------------------------------------------------------------------
// Spr.cpp
//---------------------------------------------------------------------------
// Sprite handler
//---------------------------------------------------------------------------
// (C) Copyright 1992-1997 by Microsoft Corporation.  All rights reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//---------------------------------------------------------------------------

#include "Main.h"
#pragma hdrstop
#include "Spr.h"
#include <math.h>


//---------------------------------------------------------------------------
// DEBUG info
//---------------------------------------------------------------------------
SZTHISFILE


//---------------------------------------------------------------------------
// Global Variables
//---------------------------------------------------------------------------
ITypeInfo *g_ptinfoClsSpriteClass = NULL;
ITypeInfo *g_ptinfoIntSpriteClass = NULL;
ITypeInfo *g_ptinfoClsSprite      = NULL;
ITypeInfo *g_ptinfoIntSprite      = NULL;
HBITMAP    g_hbmpStock            = NULL;
HBRUSH     g_hbrushStock          = NULL;
HDC        g_hdcMem               = NULL;


//***************************************************************************
//***************************************************************************
//**
//**  Display Class
//**
//***************************************************************************
//***************************************************************************

//---------------------------------------------------------------------------
// Initialize display surface for sprites
//---------------------------------------------------------------------------
CDisplay::CDisplay
(
  HINSTANCE  hinst,
  HWND       hwnd,
  HDC        hdc,
  IUnknown  *punkParent,
  PFNCOLLIDE pfnCollide,
  int        cimg,
  PIMG       prgimg,
  UINT       idbmp
)
{
  RECT rect;

  INIT_SIGNATURE(SIG_Display);

  // Create an HDC and get the stock bitmap
  if (!g_hdcMem)
    {
    HBITMAP hbmp;

    g_hdcMem = CreateCompatibleDC(NULL);
    hbmp = CreateCompatibleBitmap(g_hdcMem, 1, 1);
    g_hbmpStock = (HBITMAP)SelectObject(g_hdcMem, hbmp);
    SelectObject(g_hdcMem, g_hbmpStock);
    DeleteObject(hbmp);
    g_hbrushStock = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    }

  // Stash away values & init member variables
  m_hinst      = hinst;
  m_hdc        = hdc;
  GetClientRect(hwnd, &rect);
  m_cx         = rect.right;
  m_cy         = rect.bottom;
  m_pfnCollide = pfnCollide;
  m_csc        = 0;
  m_cimg       = cimg;
  m_prgimg     = prgimg;
  m_idbmp      = idbmp;
  m_psprFirst  = NULL;
  m_psprLast   = NULL;
  m_punkParent = punkParent;
  m_hbmp       = NULL;
  m_hbrushBack = NULL;
  this->SetBackColor(0x00c0c0c0);
  m_hwnd       = hwnd;

  // Compute animated images
  for (int i=0; i<cimg; i++)
    if (prgimg[i].iimgNext != iimgNONE &&
        prgimg[i].iimgNext != iimgREMOVE)
      prgimg[i].pimgNext = &prgimg[prgimg[i].iimgNext];

  // Load in all hbmp
  m_hbmp = LoadBitmap(m_hinst, MAKEINTRESOURCE(m_idbmp));
}


//---------------------------------------------------------------------------
// Terminate Sprite Sytem
//---------------------------------------------------------------------------
CDisplay::~CDisplay
(
  void
)
{
  CHECK_SIGNATURE(SIG_Display);

  if (m_hbrushBack)
    {
    SelectObject(g_hdcMem, g_hbrushStock);
    DeleteObject(m_hbrushBack);
    m_hbrushBack = NULL;
    }

  if (g_hdcMem)
    {
    SelectObject(g_hdcMem, g_hbmpStock);
    DeleteDC(g_hdcMem);
    g_hdcMem = NULL;
    }

  if (m_hbmp)
    {
    // Delete all loaded bitmaps:
    DeleteObject((HGDIOBJ)m_hbmp);
    m_hbmp = (HBITMAP)NULL;
    }

  DESTROY_SIGNATURE(SIG_Display);
}


//---------------------------------------------------------------------------
// Free all sprites on Display.
//---------------------------------------------------------------------------
void CDisplay::DestroyAll
(
  void
)
{
  CSprite *pspr;

  while (m_psprFirst)
    {
    pspr = m_psprFirst;
    pspr->_Unlink(FALSE);
    pspr->Release();
    }
}


//---------------------------------------------------------------------------
// Move all sprites on Display.
//---------------------------------------------------------------------------
void CDisplay::Timer
(
  void
)
{
  CSprite *pspr;
  CSprite *psprPrev;

  for (pspr=m_psprLast; pspr; pspr=psprPrev)
    {
    psprPrev = pspr->m_psprPrev;

    // Fire Tick event, if sprite exists
    if (!pspr->m_fFree)
      {
      if (--pspr->m_tickEvt <= 0)
        {
        pspr->m_psc->FireTick(pspr);
        pspr->m_tickEvt = pspr->m_tickEvtMax;
        }
      }

    // Move sprite, if it still exits (FireTick might have killed it.)
    if (!pspr->m_fFree)
      {
      if (--pspr->m_tickMove <= 0)
        {
        long xOldFull;
        long yOldFull;

        pspr->m_tickMove = pspr->m_tickMoveMax;

        // Does this sprite have a "MoveAt" sprite attached?
        if (pspr->m_psprAt)
          pspr->DoMoveAt(pspr->m_psprAt, pspr->m_dMaxAt, pspr->m_scaleAt, pspr->m_flagsAt, TRUE);

        xOldFull = pspr->m_xFull;
        yOldFull = pspr->m_yFull;
        if (HIWORD(xOldFull + pspr->m_vxFull) == HIWORD(xOldFull) &&
            HIWORD(yOldFull + pspr->m_vyFull) == HIWORD(yOldFull))
          {
          // Movement was only fractional, so don't need to redraw sprite.
          pspr->m_xFull += pspr->m_vxFull;
          pspr->m_yFull += pspr->m_vyFull;
          }
        else
          {
          pspr->_Erase();
          pspr->m_xFull += pspr->m_vxFull;
          pspr->m_yFull += pspr->m_vyFull;
          if (pspr->m_pimg->iimgNext == iimgREMOVE)
            pspr->Remove();
          else if (pspr->m_pimg->iimgNext != iimgNONE)
            {
            pspr->m_iimg = pspr->m_pimg->iimgNext;
            pspr->m_pimg = pspr->m_pimg->pimgNext;
            }
          if (!pspr->_FDraw(TRUE))
            {
            pspr->m_xFull = xOldFull;
            pspr->m_yFull = yOldFull;
            pspr->_FDraw(FALSE);
            }
          }

        // Calculate Friction
        if (pspr->m_fFriction)
          {
          pspr->m_vxFull = (long)((FLOAT)pspr->m_vxFull * pspr->m_fx);
          pspr->m_vyFull = (long)((FLOAT)pspr->m_vyFull * pspr->m_fy);
          }

        // Calculate AccelerationFriction
        if (pspr->m_psc->m_fFrictionAccel)
          {
          pspr->m_axFull = (long)((FLOAT)pspr->m_axFull * pspr->m_psc->m_frictionAccel);
          pspr->m_ayFull = (long)((FLOAT)pspr->m_ayFull * pspr->m_psc->m_frictionAccel);
          }

        // Calculate Acceleration
        pspr->m_vxFull += pspr->m_axFull;
        pspr->m_vyFull += pspr->m_ayFull;

        // Ensure Vel is not over max allowed for SpriteClass
        if (pspr->m_vxFull > pspr->m_psc->m_vFullMax)
          pspr->m_vxFull = pspr->m_psc->m_vFullMax;
        else if (pspr->m_vxFull < -pspr->m_psc->m_vFullMax)
          pspr->m_vxFull = -pspr->m_psc->m_vFullMax;
        if (pspr->m_vyFull > pspr->m_psc->m_vFullMax)
          pspr->m_vyFull = pspr->m_psc->m_vFullMax;
        else if (pspr->m_vyFull < -pspr->m_psc->m_vFullMax)
          pspr->m_vyFull = -pspr->m_psc->m_vFullMax;
        }
      }

    if (pspr->m_fFree)
      {
      pspr->_Unlink(TRUE);
      pspr->Release();
      }
    }
}


//---------------------------------------------------------------------------
// Paint all sprites.
//---------------------------------------------------------------------------
void CDisplay::Paint
(
  HDC hdc
)
{
  CSprite *pspr;

  if (hdc == NULL)
    hdc = m_hdc;

  for (pspr=m_psprLast; pspr; pspr=pspr->m_psprPrev)
    {
    if (!pspr->m_fFree && !pspr->m_fHidden)
      {
      SelectObject(g_hdcMem, m_hbmp);
      BitBlt(hdc, pspr->m_x, pspr->m_y, pspr->m_pimg->cx, pspr->m_pimg->cy, g_hdcMem, pspr->m_pimg->x, pspr->m_pimg->y, SRCCOPY);
      }
    }
  SelectObject(g_hdcMem, g_hbmpStock);
}


//---------------------------------------------------------------------------
// Paint any sprites with fNeedRefresh set.
//---------------------------------------------------------------------------
void CDisplay::Refresh
(
  void
)
{
  CSprite *pspr;
  HDC	   hdc = m_hdc;

  for (pspr=m_psprLast; pspr; pspr=pspr->m_psprPrev)
    {
    if (pspr->m_fNeedRefresh && !pspr->m_fHidden)
      {
      pspr->m_fNeedRefresh = FALSE;
      SelectObject(g_hdcMem, m_hbmp);
      BitBlt(hdc, pspr->m_x, pspr->m_y, pspr->m_pimg->cx, pspr->m_pimg->cy, g_hdcMem, pspr->m_pimg->x, pspr->m_pimg->y, SRCCOPY);
      }
    }
  SelectObject(g_hdcMem, g_hbmpStock);
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void CDisplay::SetBackColor
(
  COLORREF c
)
{
  static LOGBRUSH lb = {BS_SOLID, 0x00c0c0c0, 0};

  if (m_colorBack == c)
    return;
  m_colorBack = c;
  lb.lbColor = c;
  if (m_hbrushBack)
    DeleteObject(m_hbrushBack);
  m_hbrushBack = CreateBrushIndirect(&lb);
}


//---------------------------------------------------------------------------
// Send Collide event back to the fn passed into the constructor.
//---------------------------------------------------------------------------
void CDisplay::FireCollide
(
  CSprite *psprLowId,
  CSprite *psprHighId,
  int      maskCollide
)
{
  (*m_pfnCollide)(psprLowId, psprHighId, maskCollide);
}


//***************************************************************************
//***************************************************************************
//**
//**  SpriteClass Class
//**
//***************************************************************************
//***************************************************************************

HRESULT s_hr = S_OK;


//---------------------------------------------------------------------------
// Create function for SpriteClass.  Use instead of "new CSpriteClass".
//---------------------------------------------------------------------------
HRESULT CSpriteClass::Create
(
  CDisplay      *pdisp,
  CSpriteClass **ppscOut
)
{
  if (!ppscOut)
    return E_INVALIDARG;

  *ppscOut = new CSpriteClass(pdisp);
  if (!*ppscOut)
    return E_OUTOFMEMORY;

  return S_OK;
}


//---------------------------------------------------------------------------
// Constructor for SpriteClass
//---------------------------------------------------------------------------
CSpriteClass::CSpriteClass
(
  CDisplay *pdisp
)
{
  INIT_SIGNATURE(SIG_SpriteClass);

  m_id              = ++(pdisp->m_csc);
  m_pdisp           = pdisp;
  m_brd             = SPR_brdALL;
  m_maskCollide     = 0;
  m_iimg            = 0;
  m_cspr            = 0;
  m_cref            = 1;
  m_pdispBaseObject = NULL;
  VariantInit(&m_varTag);
  m_friction        = (FLOAT)1.0;
  m_frictionAccel   = (FLOAT)1.0;
  m_fFrictionAccel  = FALSE;
  m_vFullMax    = 0x000a0000;
  m_aFullMax    = 0x00010000;
}


//---------------------------------------------------------------------------
// Destructor for Sprite
//---------------------------------------------------------------------------
void CSpriteClass::Close
(
  void
)
{
  CHECK_SIGNATURE(SIG_SpriteClass);

  CSprite *pspr;
  CSprite *psprPrev;

  // Destroy all sprites of this SpriteClass
  for (pspr=m_pdisp->m_psprLast; pspr; pspr=psprPrev)
    {
    psprPrev = pspr->m_psprPrev;

    if (pspr->m_psc == this)
      {
      pspr->_Unlink(FALSE);
      pspr->m_psc = NULL;
      pspr->Release();
      }
    }

  // Unadvise all event sinks
  m_cp.Close();

  // Clear incase this is an object
  VariantClear(&m_varTag);
}


//---------------------------------------------------------------------------
// Destructor for Sprite
//---------------------------------------------------------------------------
CSpriteClass::~CSpriteClass
(
  void
)
{
  CHECK_SIGNATURE(SIG_SpriteClass);
  this->Close();
  DESTROY_SIGNATURE(SIG_SpriteClass);
}


//***************************************************************************
// IUnknown Interface
//***************************************************************************

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::QueryInterface
(
  REFIID  iid,
  LPVOID* ppvObjOut
)
{
  if (!ppvObjOut)
    return E_INVALIDARG;

  *ppvObjOut = NULL;

  if (iid == IID_IUnknown)
    *ppvObjOut = this->GetUnknown();
  else if (iid == IID_IDispatch)
    *ppvObjOut = this->GetDispatch();
  else if (iid == IID_ISpriteClass)
    *ppvObjOut = (ISpriteClass *)this;
  else if (iid == IID_IConnectionPointContainer)
    *ppvObjOut = (IConnectionPointContainer *)this;
  else if (iid == IID_IProvideClassInfo)
    *ppvObjOut = (IProvideClassInfo *)this;

  if (*ppvObjOut)
    {
    this->AddRef();
    return S_OK;
    }

  return E_NOINTERFACE;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CSpriteClass::AddRef
(
  void 
)
{
  return ++m_cref;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CSpriteClass::Release
(
  void 
)
{
  ASSERT(m_cref, "bad m_cref");
  m_cref--;
  if (!m_cref)
    {
    this->Close();
    if (!m_cref && !m_cp.m_cref)
      {
      delete this;
      return 0;
      }
    }
  return m_cref;
}


//***************************************************************************
// IDispatch Interface
//***************************************************************************

//---------------------------------------------------------------------------
// Method needed by COleAuto, so it can implement IDispatch for us.
//---------------------------------------------------------------------------
HRESULT CSpriteClass::GetTypeLibInfo
(
  HINSTANCE    *phinstOut,
  const GUID  **pplibidOut, 
  SHORT        *pwMajLib, 
  SHORT        *pwMinLib,
  const CLSID **ppclsidOut, 
  const IID   **ppiidOut, 
  ITypeLib   ***ppptlOut
)
{
  *phinstOut  = g_hinst;
  *pplibidOut = &LIBID_SPRUUIDS;
  *pwMajLib   = 1;
  *pwMinLib   = 0;
  *ppclsidOut = &CLSID_SpriteClass;
  *ppiidOut   = &IID_ISpriteClass;
  *ppptlOut   = &g_ptlMain;
  return S_OK;
}


//***************************************************************************
// IProvideClassInfo Interface
//***************************************************************************

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::GetClassInfo
(
  ITypeInfo** pptinfoOut
)
{
  HRESULT hr = ((COleAuto *)this)->CheckTypeInfo(0, 0x0409);
  if (hr)
    return hr;
  *pptinfoOut = g_ptinfoClsSpriteClass;
  (*pptinfoOut)->AddRef();
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::GetGUID
(
  DWORD dwGuidKind,
  GUID* pGUID
)
{
  if (pGUID)
    return E_INVALIDARG;

  if (dwGuidKind != GUIDKIND_DEFAULT_SOURCE_DISP_IID)
    return E_INVALIDARG;

  *pGUID = DIID_ISpriteClassEvents;
  return S_OK;
}


//***************************************************************************
// IConnectionPointContainer Interface
//***************************************************************************

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::EnumConnectionPoints
(
  LPENUMCONNECTIONPOINTS* ppEnum
)
{
  return E_NOTIMPL;   // UNDONE: Implement this method
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::FindConnectionPoint
(
  REFIID             iid,
  LPCONNECTIONPOINT* ppCpOut
)
{
  if (!ppCpOut)
    return E_INVALIDARG;

  if (iid == DIID_ISpriteClassEvents || iid == IID_IDispatch)
    {
    *ppCpOut = &m_cp;
    (*ppCpOut)->AddRef();
    return S_OK;
    }
    
  return E_NOINTERFACE;
}


//***************************************************************************
// Embedded IConnectionPoint Class
//***************************************************************************

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
CSpriteClass::XCP::XCP
(
  void
)
{
  m_cref = 1;
  for (int i=0; i<SC_cADVISE; i++)
    m_rgpdisp[i] = NULL;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
void CSpriteClass::XCP::Close
(
  void
)
{
  for (int i=0; i<SC_cADVISE; i++)
    if (m_rgpdisp[i])
      {
      m_rgpdisp[i]->Release();
      m_rgpdisp[i] = NULL;
      }
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::XCP::QueryInterface
(
  REFIID  iid,
  LPVOID* ppvObjOut
)
{
  if (!ppvObjOut)
    return E_INVALIDARG;

  *ppvObjOut = NULL;

  if (iid == IID_IUnknown)
    *ppvObjOut = this->GetUnknown();
  else if (iid == IID_IConnectionPoint)
    *ppvObjOut = (IConnectionPoint *)this;

  if (*ppvObjOut)
    {
    this->AddRef();
    return S_OK;
    }

  return E_NOINTERFACE;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CSpriteClass::XCP::AddRef
(
  void 
)
{
  return ++m_cref;
}


#define SCOFCP(pcp)  ((CSpriteClass *)((char *)pcp - (char *)&(((CSpriteClass *)0)->m_cp)))
//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CSpriteClass::XCP::Release
(
  void 
)
{
  CSpriteClass *psc = SCOFCP(this);

  ASSERT(m_cref, "bad m_cref");
  m_cref--;
  if (!m_cref && !psc->m_cref)
    {
    delete psc;
    return 0;
    }
  return m_cref;
}


//***************************************************************************
// IConnectionPoint Interface
//***************************************************************************

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::XCP::GetConnectionInterface
(
  IID* piid
)
{
  if (!piid)
    return E_INVALIDARG;

  memcpy(piid, &DIID_ISpriteClassEvents, sizeof(IID));
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::XCP::GetConnectionPointContainer
(
  IConnectionPointContainer** ppCpcOut
)
{
  if (!ppCpcOut)
    return E_INVALIDARG;

  *ppCpcOut = SCOFCP(this);
  (*ppCpcOut)->AddRef();
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::XCP::Advise
(
  IUnknown* punkSink,
  DWORD*    pdwCookie
)
{
  IDispatch  *psce = NULL;
  IDispatch **ppdisp;
  HRESULT     hr;

  if (!punkSink || !pdwCookie)
    return E_INVALIDARG;
  *pdwCookie = 0;

  // Look for empty slot
  for (ppdisp=m_rgpdisp; *ppdisp && ppdisp<&m_rgpdisp[SC_cADVISE]; ppdisp++)
    ;
  // Did we find one?
  if (ppdisp >= &m_rgpdisp[SC_cADVISE])
    return E_FAIL;          // UNDONE: Error?

  // Now see if sink supports correct interface
  hr = punkSink->QueryInterface(DIID_ISpriteClassEvents, (void **)&psce);
  if (hr == E_NOINTERFACE)
    {
    hr = punkSink->QueryInterface(IID_IDispatch, (void **)&psce);
    if (hr)
      return hr;
    }
  ASSERT(psce, "QI but no ptr");

  // Finish advise by stashing punkSink QI'd to our interface
  *ppdisp = psce;       // AddRef'd from QI
  *pdwCookie = (ppdisp - m_rgpdisp) + 1;

  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::XCP::Unadvise
(
  DWORD dwCookie
)
{
  if (!dwCookie || dwCookie > SC_cADVISE)
    return E_INVALIDARG;

  m_rgpdisp[dwCookie-1]->Release();
  m_rgpdisp[dwCookie-1] = NULL;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::XCP::EnumConnections
(
  LPENUMCONNECTIONS* ppEnum
)
{
  return E_NOTIMPL;   // UNDONE: Implement this method
}



//***************************************************************************
//***************************************************************************
//**
//**  Sprite Class
//**
//***************************************************************************
//***************************************************************************

//---------------------------------------------------------------------------
// Constructor for Sprite
//---------------------------------------------------------------------------
CSprite::CSprite
(
  CSpriteClass *psc,
  int           x,
  int           y,
  CSprite      *psprPrev,	  // NULL==1st, -1==Last
  VARIANT      *pvarUser
)
{
  INIT_SIGNATURE(SIG_Sprite);

  m_pdisp        = psc->m_pdisp;
  m_psprNext     = NULL;
  m_psprPrev     = psprPrev;
  m_xFull        = 0;
  m_x            = x;
  m_yFull        = 0;
  m_y            = y;
  m_vxFull       = 0;
  m_vyFull       = 0;
  m_axFull       = 0;
  m_ayFull       = 0;
  m_fx           = psc->m_friction;
  m_fy           = psc->m_friction;
  m_fFriction    = (psc->m_friction != 1.0);
  m_tickEvt      = 0x7fffffff;
  m_tickEvtMax   = 0x7fffffff;
  m_tickMove     = 1;
  m_tickMoveMax  = 1;
  m_iimg         = psc->m_iimg;
  m_pimg         = &m_pdisp->m_prgimg[m_iimg];
  m_psc          = psc;
  m_fNeedRefresh = TRUE;
  m_fFree        = FALSE;
  m_fIgnoreMove  = FALSE;
  m_fLinked      = FALSE;
  m_fHidden      = 2;     // Set to 2 instead of TRUE to detect if user explicitly hides it during _Init event
  m_cref         = 1;
  m_psprAt       = NULL;
  m_pdispBaseObject = NULL;
  VariantInit(&m_varTag);
  this->_Link();

  m_psc->FireInit(this, pvarUser);
  if (m_fHidden == 2) 
    m_fHidden = FALSE;    // If not explicitly hidden in event, show it
}


//---------------------------------------------------------------------------
// Destructor for Sprite
//---------------------------------------------------------------------------
CSprite::~CSprite
(
  void
)
{
  CHECK_SIGNATURE(SIG_Sprite);
  VariantClear(&m_varTag);
  if (m_psprAt)
    {
    m_psprAt->Release();
    m_psprAt = NULL;
    }
  this->_Unlink(TRUE);
  DESTROY_SIGNATURE(SIG_Sprite);
}


//---------------------------------------------------------------------------
// Change the class of an existing pspr
//---------------------------------------------------------------------------
CSprite *CSprite::PsprMutate
(
  CSpriteClass *psc,
  VARIANT      *pvarUser
)
{
  m_x          += m_pimg->cx >> 1;
  m_y          += m_pimg->cy >> 1;
  m_iimg        = psc->m_iimg;
  m_pimg        = &m_pdisp->m_prgimg[m_iimg];
  m_x          -= m_pimg->cx >> 1;
  m_y          -= m_pimg->cy >> 1;
  m_psc->m_cspr--;
  m_psc         = psc;
  m_psc->m_cspr++;
  m_tickEvt     = 0x7fffffff;
  m_tickEvtMax  = 0x7fffffff;
  m_tickMove    = 0;
  m_tickMoveMax = 1;
  m_fHidden     = 2;     // Set to 2 instead of TRUE to detect if user explicitly hides it during _Init event
  
  m_psc->FireInit(this, pvarUser);
  if (m_fHidden == 2) 
    m_fHidden = FALSE;    // If not explicitly hidden in event, show it
  return this;
}


//---------------------------------------------------------------------------
// Free a SPR structure
//---------------------------------------------------------------------------
void CSprite::MarkFree
(
  void
)
{
  if (m_psprAt)
    {
    m_psprAt->Release();
    m_psprAt = NULL;
    }
  m_psc->FireTerm(this);
  m_fFree = TRUE;
}


//---------------------------------------------------------------------------
// Link a sprite into the display list
//---------------------------------------------------------------------------
void CSprite::_Link
(
  void
)
{
  if (!m_psprPrev)
    {
    m_psprNext = m_pdisp->m_psprFirst;
    m_pdisp->m_psprFirst = this;
    if (m_psprNext)
      m_psprNext->m_psprPrev = this;
    if (!m_pdisp->m_psprLast)
      m_pdisp->m_psprLast = this;
    }
  else if (m_psprPrev == (CSprite *)-1)
    {
    m_psprNext = NULL;
    m_psprPrev = m_pdisp->m_psprLast;
    if (m_pdisp->m_psprLast)
      m_pdisp->m_psprLast->m_psprNext = this;
    else
      m_pdisp->m_psprFirst = this;
    m_pdisp->m_psprLast = this;
    }
  else
    {
    // UNDONE: Fix this up.
    m_psprNext = m_pdisp->m_psprLast->m_psprNext;
    m_pdisp->m_psprLast->m_psprNext = this;
    m_psprNext->m_psprPrev = this;
    if (m_pdisp->m_psprLast == m_pdisp->m_psprLast)
      m_pdisp->m_psprLast = this;
    }

  m_fLinked = TRUE;
  m_psc->m_cspr++;
  //this->_FDraw(FALSE);      // Require "s.Refresh" to avoid spurious paint before img set
}


//---------------------------------------------------------------------------
// Unlink a sprite into the display list
//---------------------------------------------------------------------------
void CSprite::_Unlink
(
  BOOL fFireEvt
)
{
  if (!m_fLinked)
    return;

  this->_Erase();

  if (m_pdisp->m_psprFirst == this)
    m_pdisp->m_psprFirst = m_psprNext;
  if (m_pdisp->m_psprLast  == this)
    m_pdisp->m_psprLast  = m_psprPrev;

  if (m_psprPrev)
    m_psprPrev->m_psprNext = m_psprNext;
  if (m_psprNext)
    m_psprNext->m_psprPrev = m_psprPrev;

  m_fLinked = FALSE;
  m_fHidden = TRUE;

  // Track # of sprites of this kind.  If there are no more, then
  // fire the _LastTerm event.
  m_psc->m_cspr--;
  if (fFireEvt && !m_psc->m_cspr)
    m_psc->FireLastTerm();

  if (m_psprAt)
    {
    m_psprAt->Release();
    m_psprAt = NULL;
    }
}


//---------------------------------------------------------------------------
// Draw the given sprite
//---------------------------------------------------------------------------
BOOL CSprite::_FDraw
(
  BOOL	fCollide
)
{
  CSprite *psprT;
  CSprite *psprNext;
  int x   = m_x;
  int y   = m_y;
  int cx  = m_pimg->cx;
  int cy  = m_pimg->cy;
  HDC hdc = m_pdisp->m_hdc;

  if (fCollide && !m_fFree)
    {
    int maskCollide = m_psc->m_maskCollide;

    if (m_fHidden)
      goto DoneWithColl;

    for (psprT=m_pdisp->m_psprFirst; psprT; psprT=psprNext)
      {
      psprNext = psprT->m_psprNext;
      if (psprT != this &&                                    // Never collide w/self
          ((psprT->m_psc != m_psc) || (maskCollide & 1)) &&   // Coll w/like kind only if bit 1 set
          (maskCollide & psprT->m_psc->m_maskCollide & ~1) && // Coll w/other kinds only if masks overlap
          x <= psprT->m_x+psprT->m_pimg->cx && x+cx >= psprT->m_x && // Coll only if actually touch
          y <= psprT->m_y+psprT->m_pimg->cy && y+cy >= psprT->m_y)
        {
        m_fIgnoreMove = FALSE;
        if (m_psc->m_id <= psprT->m_psc->m_id)
          m_pdisp->FireCollide(this, psprT, maskCollide & psprT->m_psc->m_maskCollide);
        else
          m_pdisp->FireCollide(psprT, this, maskCollide & psprT->m_psc->m_maskCollide);
        if (m_fFree)
          return TRUE;
        if (m_fIgnoreMove)
          return FALSE;
        if (psprT->m_fFree)
          goto DoneWithColl;
        }
      }
DoneWithColl:;
    if ((m_psc->m_brd & SPR_brdALL))
      {
      BRD brd = 0;
      if (m_psc->m_brd & SPR_brdIN)
        {
        if (x < 0) brd	= SPR_brdINLEFT;
        if (y < 0) brd |= SPR_brdINTOP;
        if (x+cx > m_pdisp->m_cx) brd |= SPR_brdINRIGHT;
        if (y+cy > m_pdisp->m_cy) brd |= SPR_brdINBOTTOM;
        }
      if (m_psc->m_brd & SPR_brdOUT)
        {
        if (x+cx < 0) brd  = SPR_brdOUTLEFT;
        if (y+cy < 0) brd |= SPR_brdOUTTOP;
        if (x > m_pdisp->m_cx) brd |= SPR_brdOUTRIGHT;
        if (y > m_pdisp->m_cy) brd |= SPR_brdOUTBOTTOM;
        }
      if (brd)
        {
        m_fIgnoreMove = FALSE;
        m_psc->FireBorder(this, brd);

        if (m_fFree)
          return TRUE;
        if (m_fIgnoreMove)
          return FALSE;
        }
      }
    }

  // Don't draw if not visible
  if (m_fHidden)
    return TRUE;

  SelectObject(g_hdcMem, m_pdisp->m_hbmp);
  BitBlt(hdc, m_x, m_y, cx, cy, g_hdcMem, m_pimg->x, m_pimg->y, SRCCOPY);
  m_fNeedRefresh = FALSE;
  for (psprT=m_psprPrev; psprT; psprT=psprT->m_psprPrev)
    {
    if (!psprT->m_fNeedRefresh &&
        x <= psprT->m_x+psprT->m_pimg->cx && x+cx >= psprT->m_x &&
        y <= psprT->m_y+psprT->m_pimg->cy && y+cy >= psprT->m_y)
      {
      psprT->m_fNeedRefresh = TRUE;
      }
    }
  SelectObject(g_hdcMem, g_hbmpStock);
  return TRUE;
}


//---------------------------------------------------------------------------
// Erase the given sprite
//---------------------------------------------------------------------------
void CSprite::_Erase
(
  void
)
{
  int      x   = m_x;
  int      y   = m_y;
  int      cx  = m_pimg->cx;
  int      cy  = m_pimg->cy;
  HDC      hdc = m_pdisp->m_hdc;
  CSprite *psprT;

  SelectObject(hdc, (HGDIOBJ)(m_pdisp->m_hbrushBack ? m_pdisp->m_hbrushBack : g_hbrushStock));
  PatBlt(hdc, m_x, m_y, cx, cy, PATCOPY);
  for (psprT=m_pdisp->m_psprLast; psprT; psprT=psprT->m_psprPrev)
    {
    if (psprT != this && !psprT->m_fNeedRefresh &&
        x <= psprT->m_x+psprT->m_pimg->cx && x+cx >= psprT->m_x &&
        y <= psprT->m_y+psprT->m_pimg->cy && y+cy >= psprT->m_y)
      psprT->m_fNeedRefresh = TRUE;
    }
  SelectObject(g_hdcMem, g_hbrushStock);
}


//---------------------------------------------------------------------------
// Move the given sprite to new location
//---------------------------------------------------------------------------
BOOL CSprite::MoveToFull
(
  long	xFull,
  long	yFull,
  BOOL	fCollide
)
{
  long xOldFull = m_xFull;
  long yOldFull = m_yFull;

  this->_Erase();
  m_xFull = xFull;
  m_yFull = yFull;
  if (m_pimg->iimgNext == iimgREMOVE)
    this->Remove();
  else if (m_pimg->iimgNext != iimgNONE)
    {
    m_iimg = m_pimg->iimgNext;
    m_pimg = m_pimg->pimgNext;
    }
  if (!this->_FDraw(fCollide))
    {
    m_xFull = xOldFull;
    m_yFull = yOldFull;
    this->_FDraw(FALSE);
    return FALSE;
    }
  return TRUE;
}


//---------------------------------------------------------------------------
// Move the given sprite to new location
//---------------------------------------------------------------------------
BOOL CSprite::MoveByFull
(
  long	dxFull,
  long	dyFull,
  BOOL	fCollide
)
{
  long xOldFull = m_xFull;
  long yOldFull = m_yFull;

  if (HIWORD(xOldFull + dxFull) == HIWORD(xOldFull) &&
      HIWORD(yOldFull + dyFull) == HIWORD(yOldFull))
    {
    m_xFull += dxFull;
    m_yFull += dyFull;
    return TRUE;
    }

  this->_Erase();
  m_xFull += dxFull;
  m_yFull += dyFull;
  if (m_pimg->iimgNext == iimgREMOVE)
    this->Remove();
  else if (m_pimg->iimgNext != iimgNONE)
    {
    m_iimg = m_pimg->iimgNext;
    m_pimg = m_pimg->pimgNext;
    }

  if (!this->_FDraw(fCollide))
    {
    m_xFull = xOldFull;
    m_yFull = yOldFull;
    this->_FDraw(FALSE);
    return FALSE;
    }
  return TRUE;
}


//---------------------------------------------------------------------------
// flags: 1=X, 2=Y;
//        4=Pos, 8=Vel, 16=Accel;
//        32=Less With Distance (default=More);
//        128=Remember
//---------------------------------------------------------------------------
BOOL CSprite::DoMoveAt
(
  CSprite *psprAt,
  float    scale,
  float    dMax,
  long     flags,
  BOOL     fCollide
)
  {
  long dx = psprAt->m_xFull - m_xFull;
  long dy = psprAt->m_yFull - m_yFull;

  if (flags & MAS_RECIPDIST)
    {
    dx = FULLOFFLOAT((FLOAT)1.0 / FLOATOFFULL(dx | 0xffff));
    dy = FULLOFFLOAT((FLOAT)1.0 / FLOATOFFULL(dy | 0xffff));
    }

  float d = FLOATOFFULL(dx) * scale;
  if (d > dMax)
    d = dMax;
  else if (d < -dMax)
    d = -dMax;
  dx = FULLOFFLOAT(d);
  d = FLOATOFFULL(dy) * scale;
  if (d > dMax)
    d = dMax;
  else if (d < -dMax)
    d = -dMax;
  dy = FULLOFFLOAT(d);

  if (flags & MAS_X)
    {
    if (flags & MAS_VEL)
      {
      m_vxFull += dx;
      if (m_vxFull > m_psc->m_vFullMax)
        m_vxFull = m_psc->m_vFullMax;
      else if (m_vxFull < -m_psc->m_vFullMax)
        m_vxFull = -m_psc->m_vFullMax;
      }
    if (flags & MAS_ACCEL)
      {
      m_axFull += dx;
      if (m_axFull > m_psc->m_aFullMax)
        m_axFull = m_psc->m_aFullMax;
      else if (m_axFull < -m_psc->m_aFullMax)
        m_axFull = -m_psc->m_aFullMax;
      }
    if (!(flags & MAS_POS))
      dx = 0;
    }
  else 
    dx = 0;

  if (flags & MAS_Y)
    {
    if (flags & MAS_VEL)
      {
      m_vyFull += dy;
      if (m_vyFull > m_psc->m_vFullMax)
        m_vyFull = m_psc->m_vFullMax;
      else if (m_vyFull < -m_psc->m_vFullMax)
        m_vyFull = -m_psc->m_vFullMax;
      }
    if (flags & MAS_ACCEL)
      {
      m_ayFull += dy;
      if (m_ayFull > m_psc->m_aFullMax)
        m_ayFull = m_psc->m_aFullMax;
      else if (m_ayFull < -m_psc->m_aFullMax)
        m_ayFull = -m_psc->m_aFullMax;
      }
    if (!(flags & MAS_POS))
      dy = 0;
    }
  else 
    dy = 0;

  if (dx || dy)
    return this->MoveByFull(dx, dy, fCollide);

  return TRUE;
  }


//***************************************************************************
// IUnknown Interface
//***************************************************************************

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::QueryInterface
(
  REFIID  iid,
  LPVOID* ppvObjOut
)
{
  if (!ppvObjOut)
    return E_INVALIDARG;

  *ppvObjOut = NULL;

  if (iid == IID_IUnknown)
    *ppvObjOut = this->GetUnknown();
  else if (iid == IID_IDispatch)
    *ppvObjOut = this->GetDispatch();
  else if (iid == IID_ISprite)
    *ppvObjOut = (ISprite *)this;

  if (*ppvObjOut)
    {
    this->AddRef();
    return S_OK;
    }

  return E_NOINTERFACE;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CSprite::AddRef
(
  void 
)
{
  return ++m_cref;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CSprite::Release
(
  void 
)
{
  ASSERT(m_cref, "bad m_cref");
  m_cref--;
  if (!m_cref)
    {
    delete this;
    return 0;
    }
  return m_cref;
}


//***************************************************************************
// IDispatch Interface
//***************************************************************************

//---------------------------------------------------------------------------
// Method needed by COleAuto, so it can implement IDispatch for us.
//---------------------------------------------------------------------------
HRESULT CSprite::GetTypeLibInfo
(
  HINSTANCE    *phinstOut,
  const GUID  **pplibidOut, 
  SHORT        *pwMajLib, 
  SHORT        *pwMinLib,
  const CLSID **ppclsidOut, 
  const IID   **ppiidOut, 
  ITypeLib   ***ppptlOut
)
{
  *phinstOut  = g_hinst;
  *pplibidOut = &LIBID_SPRUUIDS;
  *pwMajLib   = 1;
  *pwMinLib   = 0;
  *ppclsidOut = &CLSID_Sprite;
  *ppiidOut   = &IID_ISprite;
  *ppptlOut   = &g_ptlMain;
  return S_OK;
}

//--- EOF -------------------------------------------------------------------


