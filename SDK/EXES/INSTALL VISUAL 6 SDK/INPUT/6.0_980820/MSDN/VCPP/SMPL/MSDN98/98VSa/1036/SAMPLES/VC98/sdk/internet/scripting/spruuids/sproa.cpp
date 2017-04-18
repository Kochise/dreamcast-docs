//---------------------------------------------------------------------------
// SprOA.cpp
//---------------------------------------------------------------------------
// Sprite handler, OLE Automation support
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
#include "DispIDs.h"
#include <math.h>


//---------------------------------------------------------------------------
// DEBUG info
//---------------------------------------------------------------------------
SZTHISFILE


//***************************************************************************
//***************************************************************************
//**
//**  SpriteClass Class
//**
//***************************************************************************
//***************************************************************************


//***************************************************************************
// Fire ISpriteClassEvents Events
//***************************************************************************

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
void CSpriteClass::FireInit
(
  CSprite *pspr,
  VARIANT *pvarUser
)
{
  IDispatch **ppdisp = m_cp.m_rgpdisp;
  VARIANTARG  var[2];

  VariantInit(&var[1]);
  var[1].vt = VT_DISPATCH;
  var[1].pdispVal = pspr->GetDispatch();
  pspr->AddRef();
  VariantInit(&var[0]);
  VariantCopy(&var[0], pvarUser);

  for (; ppdisp < &m_cp.m_rgpdisp[SC_cADVISE]; ppdisp++)
    if (*ppdisp)
      InvokeEvent(*ppdisp, DISPID_SpriteClassEvents_Init, var, 2);

  pspr->Release();    // For var[1].pdispVal
  VariantClear(&var[0]);
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
void CSpriteClass::FireTick
(
  CSprite *pspr
)
{
  IDispatch **ppdisp = m_cp.m_rgpdisp;
  VARIANTARG  var[1];

  VariantInit(&var[0]);
  var[0].vt = VT_DISPATCH;
  var[0].pdispVal = pspr->GetDispatch();
  pspr->AddRef();

  for (; ppdisp < &m_cp.m_rgpdisp[SC_cADVISE]; ppdisp++)
    if (*ppdisp)
      InvokeEvent(*ppdisp, DISPID_SpriteClassEvents_Tick, var, 1);

  pspr->Release();    // For var[0].pdispVal
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
void CSpriteClass::FireBorder
(
  CSprite *pspr,
  BRD      brd
)
{
  IDispatch **ppdisp = m_cp.m_rgpdisp;
  VARIANTARG  var[2];

  VariantInit(&var[1]);
  var[1].vt = VT_DISPATCH;
  var[1].pdispVal = pspr->GetDispatch();
  pspr->AddRef();
  VariantInit(&var[0]);
  var[0].vt = VT_I4;
  var[0].lVal = brd;

  for (; ppdisp < &m_cp.m_rgpdisp[SC_cADVISE]; ppdisp++)
    if (*ppdisp)
      {
      BOOL f;
      HRESULT hr = InvokeEvent(*ppdisp, DISPID_SpriteClassEvents_Border, var, 2);
      if (hr)
        f = TRUE;
      }

  pspr->Release();    // For var[1].pdispVal
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
void CSpriteClass::FireTerm
(
  CSprite *pspr
)
{
  IDispatch **ppdisp = m_cp.m_rgpdisp;
  VARIANTARG  var[1];

  VariantInit(&var[0]);
  var[0].vt = VT_DISPATCH;
  var[0].pdispVal = pspr->GetDispatch();
  pspr->AddRef();

  for (; ppdisp < &m_cp.m_rgpdisp[SC_cADVISE]; ppdisp++)
    if (*ppdisp)
      InvokeEvent(*ppdisp, DISPID_SpriteClassEvents_Term, var, 1);

  pspr->Release();    // For var[0].pdispVal
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
void CSpriteClass::FireLastTerm
(
  void
)
{
  IDispatch **ppdisp = m_cp.m_rgpdisp;

  for (; ppdisp < &m_cp.m_rgpdisp[SC_cADVISE]; ppdisp++)
    if (*ppdisp)
      InvokeEvent(*ppdisp, DISPID_SpriteClassEvents_LastTerm, NULL, 0);
}


//***************************************************************************
// ISpriteClass Interface
//***************************************************************************

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::get_Application
(
  ISpruuidsApp** ppRet
)
{
  if (!ppRet)
    return E_INVALIDARG;
  return g_punkApplicationNA->QueryInterface(IID_ISpruuidsApp, (void **)ppRet);
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::get_Parent
(
  IGame** ppRet
)
{
  if (!ppRet)
    return E_INVALIDARG;
  return m_pdisp->m_punkParent->QueryInterface(IID_IGame, (void **)ppRet);
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::CreateSprite
(
  int       x,
  int       y,
  VARIANT   arg,
  ISprite **ppRet
)
{
  CSprite *pspr = new CSprite(this, x, y, NULL, &arg);
  if (!pspr)
    return E_OUTOFMEMORY;
  *ppRet = pspr;
  (*ppRet)->AddRef();
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::get_Tag
(
  VARIANT* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;
  VariantInit(pRet);
  return VariantCopy(pRet, &m_varTag);
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::put_Tag
(
  VARIANT val
)
{
  return VariantCopy(&m_varTag, &val);
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::get_Image
(
  int* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;
  *pRet = m_iimg;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::put_Image
(
  int val
)
{
  if (val > 0 && val < m_pdisp->m_cimg)
    m_iimg = val;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::get_Border
(
  int* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;
  *pRet = m_brd;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::put_Border
(
  int val
)
{
  m_brd = val;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::get_Collide
(
  int* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;
  *pRet = m_maskCollide;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::put_Collide
(
  int val
)
{
  m_maskCollide = val;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::get_MaximumVelocity
(
  FLOAT* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;

  *pRet = FLOATOFFULL(m_vFullMax);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::put_MaximumVelocity
(
  FLOAT val
)
{
  m_vFullMax = FULLOFFLOAT(val);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::get_Friction
(
  FLOAT* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;
  *pRet = m_friction;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::put_Friction
(
  FLOAT val
)
{
  m_friction = val;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::get_MaximumAcceleration
(
  FLOAT* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;

  *pRet = FLOATOFFULL(m_aFullMax);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::put_MaximumAcceleration
(
  FLOAT val
)
{
  m_aFullMax = FULLOFFLOAT(val);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::get_AccelerationFriction
(
  FLOAT* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;
  *pRet = m_frictionAccel;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::put_AccelerationFriction
(
  FLOAT val
)
{
  m_frictionAccel = val;
  m_fFrictionAccel = (val != (FLOAT)1.0);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSpriteClass::get_SpriteCount
(
  int* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;
  *pRet = m_cspr;
  return S_OK;
}



//***************************************************************************
//***************************************************************************
//**
//**  Sprite Class
//**
//***************************************************************************
//***************************************************************************


//***************************************************************************
// ISprite Interface
//***************************************************************************

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::get_Application
(
  ISpruuidsApp** ppRet
)
{
  if (!ppRet)
    return E_INVALIDARG;
  return g_punkApplicationNA->QueryInterface(IID_ISpruuidsApp, (void **)ppRet);
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::get_Parent
(
  ISpriteClass** ppRet
)
{
  if (!ppRet)
    return E_INVALIDARG;
  return m_psc->QueryInterface(IID_ISpriteClass, (void **)ppRet);
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::MoveTo
(
  FLOAT x,
  FLOAT y
)
{
  this->MoveToFull(FULLOFFLOAT(x), FULLOFFLOAT(y), TRUE);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::MoveBy
(
  FLOAT dx,
  FLOAT dy
)
{
  this->MoveByFull(FULLOFFLOAT(dx), FULLOFFLOAT(dy), TRUE);
  return S_OK;
}



//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::MoveAtSprite
(
  ISprite* sprite,
  float    dMax,
  float    scale,
  long     flags
)
{
  if (!sprite)
    return E_INVALIDARG;

  // Store parameters & do every tickMove ticks if MAS_REMEMBER set.
  if (flags & MAS_REMEMBER)
    {
    if (m_psprAt)
      {
      m_psprAt->Release();
      m_psprAt = NULL;
      }
    m_psprAt = (CSprite *)(void *)sprite;
    if (!m_psprAt)
      return S_OK;
    m_psprAt->AddRef();
    m_dMaxAt = dMax;
    m_scaleAt = scale;
    m_flagsAt = flags;
    return S_OK;
    }

  // Otherwise, do this right now.
  this->DoMoveAt((CSprite *)(void *)sprite, dMax, scale, flags, FALSE);
  return S_OK;
}



//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::Remove
(
  void 
)
{
  this->MarkFree();
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::Refresh
(
  void 
)
{
  this->_FDraw(FALSE);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::IgnoreMove
(
  void 
)
{
  m_fIgnoreMove = TRUE;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::get_Left
(
  FLOAT* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;

  *pRet = FLOATOFFULL(m_xFull);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::put_Left
(
  FLOAT val
)
{
  m_xFull = FULLOFFLOAT(val);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::get_Top
(
  FLOAT* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;

  *pRet = FLOATOFFULL(m_yFull);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::put_Top
(
  FLOAT val
)
{
  m_yFull = FULLOFFLOAT(val);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::get_Vx
(
  FLOAT* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;

  *pRet = FLOATOFFULL(m_vxFull);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::put_Vx
(
  FLOAT val
)
{
  m_vxFull = FULLOFFLOAT(val);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::get_Vy
(
  FLOAT* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;

  *pRet = FLOATOFFULL(m_vyFull);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::put_Vy
(
  FLOAT val
)
{
  m_vyFull = FULLOFFLOAT(val);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::get_Ax
(
  FLOAT* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;

  *pRet = FLOATOFFULL(m_axFull);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::put_Ax
(
  FLOAT val
)
{
  m_axFull = FULLOFFLOAT(val);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::get_Ay
(
  FLOAT* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;

  *pRet = FLOATOFFULL(m_ayFull);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::put_Ay
(
  FLOAT val
)
{
  m_ayFull = FULLOFFLOAT(val);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::get_FrictionX
(
  FLOAT* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;

  *pRet = m_fx;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::put_FrictionX
(
  FLOAT val
)
{
  m_fx = val;
  m_fFriction = (m_fx != 1.0) || (m_fy != 1.0);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::get_FrictionY
(
  FLOAT* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;

  *pRet = m_fy;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::put_FrictionY
(
  FLOAT val
)
{
  m_fy = val;
  m_fFriction = (m_fx != 1.0) || (m_fy != 1.0);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::get_Width
(
  int* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;
  *pRet = m_pimg->cx;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::get_Height
(
  int* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;
  *pRet = m_pimg->cy;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::get_Image
(
  int* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;
  *pRet = m_iimg;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::put_Image
(
  int val
)
{
  if (val >= 0 && val < m_pdisp->m_cimg)
    {
    PIMG pimgCur = m_pimg;

    if (!m_fHidden)
      this->_Erase();
    m_iimg = val;
    m_pimg = &(m_pdisp->m_prgimg[m_iimg]);
    // Keep image centered, if Visible
    if (!m_fHidden)
      {
      m_x += (pimgCur->cx - m_pimg->cx) >> 1;
      m_y += (pimgCur->cy - m_pimg->cy) >> 1;
      this->_FDraw(FALSE);
      }
    }
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::get_TickMove
(
  int* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;
  *pRet = m_tickMoveMax;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::put_TickMove
(
  int val
)
{
  m_tickMoveMax = val;
  if (m_tickMove > m_tickMoveMax)
    m_tickMove = m_tickMoveMax;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::get_TickEvent
(
  int* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;
  *pRet = m_tickEvtMax;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::put_TickEvent
(
  int val
)
{
  m_tickEvtMax = val;
  if (m_tickEvt > m_tickEvtMax)
    m_tickEvt = m_tickEvtMax;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::get_Visible
(
  VARIANT_BOOL* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;
  *pRet = m_fHidden ? 0 : -1;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::put_Visible
(
  VARIANT_BOOL val
)
{
  if (m_fLinked)
    {
    m_fHidden = !val;
    if (!m_fHidden)
      this->_Erase();
    else
      this->_FDraw(FALSE);
    }
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::get_Tag
(
  VARIANT* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;
  VariantInit(pRet);
  return VariantCopy(pRet, &m_varTag);
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CSprite::put_Tag
(
  VARIANT val
)
{
  return VariantCopy(&m_varTag, &val);
}

//--- EOF -------------------------------------------------------------------
