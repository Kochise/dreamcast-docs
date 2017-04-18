//---------------------------------------------------------------------------
// GameOA.cpp
//---------------------------------------------------------------------------
// Sample spr program, OLE Automation implementation
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
#include "Game.h"
#include "App.h"
#include "Spr.h"
#include "Score.h"
#include "DispIDs.h"
#include <math.h>


//---------------------------------------------------------------------------
// DEBUG info
//---------------------------------------------------------------------------
SZTHISFILE


//---------------------------------------------------------------------------
// Various Globals
//---------------------------------------------------------------------------
extern CGame *g_pgame;
ITypeInfo *g_ptinfoClsGameOA = NULL;
ITypeInfo *g_ptinfoIntGameOA = NULL;



//***************************************************************************
// Constructor / Destructor
//***************************************************************************

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
CGameOA::CGameOA
(
  CGame *pgame
)
{
  m_pgame           = pgame;
  m_pdispBaseObject = NULL;
}



//***************************************************************************
// Fire IGameEvents Events
//***************************************************************************

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void CGameOA::FireNewGame
(
  void
)
{
  IDispatch **ppdisp = m_cp.m_rgpdisp;

  for (; ppdisp < &m_cp.m_rgpdisp[GAME_cADVISE]; ppdisp++)
    if (*ppdisp)
      InvokeEvent(*ppdisp, DISPID_GameEvents_NewGame, NULL, 0);
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void CGameOA::FireNewLevel
(
  void
)
{
  IDispatch **ppdisp = m_cp.m_rgpdisp;

  for (; ppdisp < &m_cp.m_rgpdisp[GAME_cADVISE]; ppdisp++)
    if (*ppdisp)
      InvokeEvent(*ppdisp, DISPID_GameEvents_NewLevel, NULL, 0);
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void CGameOA::FireNewShip
(
  void
)
{
  IDispatch **ppdisp = m_cp.m_rgpdisp;

  for (; ppdisp < &m_cp.m_rgpdisp[GAME_cADVISE]; ppdisp++)
    if (*ppdisp)
      InvokeEvent(*ppdisp, DISPID_GameEvents_NewShip, NULL, 0);
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void CGameOA::FireCollide
(
  CSprite *psprLowId,
  CSprite *psprHighId,
  int      maskCollide
)
{
  IDispatch **ppdisp = g_pgame->m_pgameoa->m_cp.m_rgpdisp;
  VARIANTARG  var[3];

  VariantInit(&var[2]);
  var[2].vt = VT_DISPATCH;
  var[2].pdispVal = psprLowId->GetDispatch();
  psprLowId->AddRef();
  VariantInit(&var[1]);
  var[1].vt = VT_DISPATCH;
  var[1].pdispVal = psprHighId->GetDispatch();
  psprHighId->AddRef();
  VariantInit(&var[0]);
  var[0].vt = VT_I4;
  var[0].lVal = maskCollide;

  for (; ppdisp < &g_pgame->m_pgameoa->m_cp.m_rgpdisp[GAME_cADVISE]; ppdisp++)
    if (*ppdisp)
      InvokeEvent(*ppdisp, DISPID_GameEvents_Collide, var, 3);

  psprLowId->Release();     // For var[2].pdispVal
  psprHighId->Release();    // For var[1].pdispVal
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void CGameOA::FireTick
(
  void
)
{
  IDispatch **ppdisp = m_cp.m_rgpdisp;

  for (; ppdisp < &m_cp.m_rgpdisp[GAME_cADVISE]; ppdisp++)
    if (*ppdisp)
      InvokeEvent(*ppdisp, DISPID_GameEvents_Tick, NULL, 0);
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void CGameOA::FireKeyDown
(
  int vk
)
{
  IDispatch **ppdisp = m_cp.m_rgpdisp;
  VARIANTARG  var[2];

  VariantInit(&var[0]);
  var[0].vt   = VT_I4;
  var[0].lVal = vk;

  for (; ppdisp < &m_cp.m_rgpdisp[GAME_cADVISE]; ppdisp++)
    if (*ppdisp)
      InvokeEvent(*ppdisp, DISPID_GameEvents_KeyDown, var, 1);
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void CGameOA::FireKeyPress
(
  int ascii
)
{
  IDispatch **ppdisp = m_cp.m_rgpdisp;
  VARIANTARG  var[1];

  VariantInit(&var[0]);
  var[0].vt   = VT_I4;
  var[0].lVal = ascii;

  for (; ppdisp < &m_cp.m_rgpdisp[GAME_cADVISE]; ppdisp++)
    if (*ppdisp)
      InvokeEvent(*ppdisp, DISPID_GameEvents_KeyPress, var, 1);
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void CGameOA::FireKeyUp
(
  int vk
)
{
  IDispatch **ppdisp = m_cp.m_rgpdisp;
  VARIANTARG  var[2];

  VariantInit(&var[0]);
  var[0].vt   = VT_I4;
  var[0].lVal = vk;

  for (; ppdisp < &m_cp.m_rgpdisp[GAME_cADVISE]; ppdisp++)
    if (*ppdisp)
      InvokeEvent(*ppdisp, DISPID_GameEvents_KeyUp, var, 1);
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void CGameOA::FireMouseMove
(
  int  x,
  int  y,
  long mk
)
{
  IDispatch **ppdisp = m_cp.m_rgpdisp;
  VARIANTARG  var[4];

  VariantInit(&var[3]);
  var[3].vt = VT_I4;
  var[3].lVal = (mk & MK_SHIFT   ? 1 : 0) |
                (mk & MK_CONTROL ? 2 : 0);
  VariantInit(&var[2]);
  var[2].vt = VT_I4;
  var[2].lVal = (mk & MK_LBUTTON ? 1 : 0) |
                (mk & MK_RBUTTON ? 2 : 0) |
                (mk & MK_MBUTTON ? 4 : 0);
  VariantInit(&var[1]);
  var[1].vt = VT_I4;
  var[1].lVal = x;
  VariantInit(&var[0]);
  var[0].vt = VT_I4;
  var[0].lVal = y;

  for (; ppdisp < &m_cp.m_rgpdisp[GAME_cADVISE]; ppdisp++)
    if (*ppdisp)
      InvokeEvent(*ppdisp, DISPID_GameEvents_MouseMove, var, 4);
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void CGameOA::FireMouseDown
(
  int  x,
  int  y,
  long mk,
  long button
)
{
  IDispatch **ppdisp = m_cp.m_rgpdisp;
  VARIANTARG  var[4];

  VariantInit(&var[3]);
  var[3].vt = VT_I4;
  var[3].lVal = (mk & MK_SHIFT   ? 1 : 0) |
                (mk & MK_CONTROL ? 2 : 0);
  VariantInit(&var[2]);
  var[2].vt = VT_I4;
  var[2].lVal = (button & MK_LBUTTON ? 1 : 0) |
                (button & MK_RBUTTON ? 2 : 0) |
                (button & MK_MBUTTON ? 4 : 0);
  VariantInit(&var[1]);
  var[1].vt = VT_I4;
  var[1].lVal = x;
  VariantInit(&var[0]);
  var[0].vt = VT_I4;
  var[0].lVal = y;

  for (; ppdisp < &m_cp.m_rgpdisp[GAME_cADVISE]; ppdisp++)
    if (*ppdisp)
      InvokeEvent(*ppdisp, DISPID_GameEvents_MouseDown, var, 4);
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void CGameOA::FireMouseUp
(
  int  x,
  int  y,
  long mk,
  long button
)
{
  IDispatch **ppdisp = m_cp.m_rgpdisp;
  VARIANTARG  var[4];

  VariantInit(&var[3]);
  var[3].vt = VT_I4;
  var[3].lVal = (mk & MK_SHIFT   ? 1 : 0) |
                (mk & MK_CONTROL ? 2 : 0);
  VariantInit(&var[2]);
  var[2].vt = VT_I4;
  var[2].lVal = (button & MK_LBUTTON ? 1 : 0) |
                (button & MK_RBUTTON ? 2 : 0) |
                (button & MK_MBUTTON ? 4 : 0);
  VariantInit(&var[1]);
  var[1].vt = VT_I4;
  var[1].lVal = x;
  VariantInit(&var[0]);
  var[0].vt = VT_I4;
  var[0].lVal = y;

  for (; ppdisp < &m_cp.m_rgpdisp[GAME_cADVISE]; ppdisp++)
    if (*ppdisp)
      InvokeEvent(*ppdisp, DISPID_GameEvents_MouseUp, var, 4);
}


//***************************************************************************
// IGame Interface
//***************************************************************************

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::get_Caption
(
  BSTR* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;
  UINT cch = GetWindowTextLength(m_pgame->m_hwndDlg);
  char *pszT = new char[cch+1];
  if (!pszT)
    return E_OUTOFMEMORY;
  *pRet = SysAllocStringLen(NULL, cch);
  if (!*pRet)
    {
    delete [] pszT;
    return E_OUTOFMEMORY;
    }
  GetWindowText(m_pgame->m_hwndDlg, pszT, cch+1);
  MultiByteToWideChar(CP_ACP, 0, pszT, -1, *pRet, cch+1);
  delete [] pszT;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::put_Caption
(
  BSTR bstr
)
{
  WCHAR *pwsz = bstr ? bstr : L"";
  MAKE_ANSIPTR_FROMWIDE(pszT, pwsz);
  SetWindowText(m_pgame->m_hwndDlg, pszT);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::get_StatusText
(
  BSTR* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;
  UINT cch = GetWindowTextLength(m_pgame->m_hwndStat);
  char *pszT = new char[cch+1];
  if (!pszT)
    return E_OUTOFMEMORY;
  *pRet = SysAllocStringLen(NULL, cch);
  if (!*pRet)
    {
    delete [] pszT;
    return E_OUTOFMEMORY;
    }
  GetWindowText(m_pgame->m_hwndStat, pszT, cch+1);
  MultiByteToWideChar(CP_ACP, 0, pszT, -1, *pRet, cch+1);
  delete [] pszT;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::put_StatusText
(
  BSTR bstr
)
{
  WCHAR *pwsz = bstr ? bstr : L"";
  MAKE_ANSIPTR_FROMWIDE(pszT, pwsz);
  m_pgame->m_pscore->SetStatusText(pszT);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::get_Application
(
  ISpruuidsApp** lppaReturn
)
{
  return g_papp->QueryInterface(IID_ISpruuidsApp, (void **)lppaReturn);
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::get_Parent
(
  ISpruuidsApp** lppaReturn
)
{
  return g_papp->QueryInterface(IID_ISpruuidsApp, (void **)lppaReturn);
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::StartGame
(
  void 
)
{
  m_pgame->NewGame();
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::EndGame
(
  void 
)
{
  m_pgame->GameOver();
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::RemoveAllSprites
(
  void 
)
{
  m_pgame->m_pdisp->DestroyAll();
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::NextLevel
(
  void 
)
{
  m_pgame->NewLevel();
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::Refresh
(
  void 
)
{
  m_pgame->m_pdisp->Refresh();
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::AddScore
(
  int val
)
{
  m_pgame->m_pscore->Add(val);
  return S_OK;
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::StdBorderBounce
(
  ISprite *psprite,
  int      brd
)
{
  CSprite *pspr = SPRITEOFI(psprite);

  if ((brd & SPR_brdTOP) && pspr->m_vyFull < 0)
    {
    pspr->m_vyFull = -pspr->m_vyFull;
    pspr->IgnoreMove();
    }
  if ((brd & SPR_brdLEFT) && pspr->m_vxFull < 0)
    {
    pspr->m_vxFull = -pspr->m_vxFull;
    pspr->IgnoreMove();
    }
  if ((brd & SPR_brdBOTTOM) && pspr->m_vyFull > 0)
    {
    pspr->m_vyFull = -pspr->m_vyFull;
    pspr->IgnoreMove();
    }
  if ((brd & SPR_brdRIGHT) && pspr->m_vxFull > 0)
    {
    pspr->m_vxFull = -pspr->m_vxFull;
    pspr->IgnoreMove();
    }
  return S_OK;
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::StdBorderWrap
(
  ISprite *psprite,
  int      brd
)
{
  CSprite *pspr = SPRITEOFI(psprite);

  if ((brd & SPR_brdTOP) && pspr->m_vyFull < 0)
    pspr->m_y = pspr->m_pdisp->m_cy;
  if ((brd & SPR_brdLEFT) && pspr->m_vxFull < 0)
    pspr->m_x = pspr->m_pdisp->m_cx;
  if ((brd & SPR_brdBOTTOM) && pspr->m_vyFull > 0)
    pspr->m_y = -pspr->m_pimg->cy;
  if ((brd & SPR_brdRIGHT) && pspr->m_vxFull > 0)
    pspr->m_x = -pspr->m_pimg->cx;
  return S_OK;
}


//---------------------------------------------------------------------------
// Generate a random number between 0 and n.
//---------------------------------------------------------------------------
int MyRand
(
  int n
)
{
  int t, u;
  static nLast=0, tLast=0;

  if (n <= 1)
    return 0;

  n &= RAND_MAX;
  if (n == nLast)
    t = tLast;
  else
    {
    nLast = n;
    for (t=2; t<n; t<<=1)
      ;
    t--;
    tLast = t;
    }

  do
    {
    u = t & rand();
    } while (u >= n);
  return u;
}


//---------------------------------------------------------------------------
// Init to random position which doesn't cause a collision event.
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::StdInitRand
(
  ISprite *psprite,
  VARIANT  varUser
)
{
  CSprite *pspr = SPRITEOFI(psprite);
  CSprite *psprT;
  LONG     x, y, dx, dy;
  int      cx, cy;
  int      lUser = (varUser.vt == VT_I4) ? varUser.lVal : 0;
  LONG     dist = 8128;

  cx = pspr->m_pimg->cx;
  cy = pspr->m_pimg->cy;
  do
    {
Loop:
    x = MyRand(pspr->m_pdisp->m_cx - cx);
    y = MyRand(pspr->m_pdisp->m_cy - cy);
    for (psprT=pspr->m_pdisp->m_psprFirst; psprT; psprT=psprT->m_psprNext)
      {
      if (!(psprT->m_psc->m_maskCollide & pspr->m_psc->m_maskCollide) && // if potential collision doesn't matter
          x <= psprT->m_x+psprT->m_pimg->cx && x+cx >= psprT->m_x &&  // and we collide
          y <= psprT->m_y+psprT->m_pimg->cy && y+cy >= psprT->m_y)
	goto Loop;                              // then try another location
      }
    dx = (x - (pspr->m_pdisp->m_cx>>1));
    dy = (y - (pspr->m_pdisp->m_cy>>1));
    } while (dx*dx + dy*dy < dist);
  pspr->m_x = (int)x;
  pspr->m_y = (int)y;
  return S_OK;
}


//---------------------------------------------------------------------------
// Init to random position along edge of disp.
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::StdInitEdge
(
  ISprite *psprite,
  VARIANT  varUser
)
{
  CSprite *pspr = SPRITEOFI(psprite);

  if (rand() & 1)
    {
    pspr->m_x = MyRand(pspr->m_pdisp->m_cx - pspr->m_pimg->cx);
    if (rand() & 1)
      pspr->m_y = pspr->m_pdisp->m_cy - pspr->m_pimg->cy;
    }
  else
    {
    pspr->m_y = MyRand(pspr->m_pdisp->m_cy - pspr->m_pimg->cy);
    if (rand() & 1)
      pspr->m_x = pspr->m_pdisp->m_cx - pspr->m_pimg->cx;
    }
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::get_Paused
(
  VARIANT_BOOL* pRet
)
{
  *pRet = m_pgame->m_fPaused;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::put_Paused
(
  VARIANT_BOOL val
)
{
  m_pgame->Pause(!!val);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::get_Width
(
  int* pRet
)
{
  *pRet = m_pgame->m_pdisp->m_cx;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::put_Width
(
  int val
)
{
  if (val < 20 || val > 1024)
    return E_FAIL;
  m_pgame->m_pscore->Size(val, m_pgame->m_pdisp->m_cy);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::get_Height
(
  int* pRet
)
{
  *pRet = m_pgame->m_pdisp->m_cy;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::put_Height
(
  int val
)
{
  if (val < 20 || val > 1024)
    return E_FAIL;
  m_pgame->m_pscore->Size(m_pgame->m_pdisp->m_cx, val);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::get_BackColor
(
  long* pRet
)
{
  *pRet = m_pgame->m_pdisp->m_colorBack;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::put_BackColor
(
  long val
)
{
  if (val & 0xff000000)
    return E_FAIL;
  m_pgame->m_pdisp->SetBackColor(val);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::get_Score
(
  int* pRet
)
{
  *pRet = m_pgame->m_pscore->GetScore();
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::put_Score
(
  int val
)
{
  m_pgame->m_pscore->SetScore(val);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::get_Level
(
  int* pRet
)
{
  *pRet = m_pgame->m_pscore->GetLevel();
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::put_Level
(
  int val
)
{
  m_pgame->m_pscore->SetLevel(val);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::get_ShipCount
(
  int* pRet
)
{
  *pRet = m_pgame->m_pscore->GetCShip();
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::put_ShipCount
(
  int val
)
{
  m_pgame->m_pscore->SetCShip(val);
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::get_ScoreFirst1Up
(
  int* pRet
)
{
  *pRet = m_pgame->m_pscore->m_scoreFirst1Up;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::put_ScoreFirst1Up
(
  int val
)
{
  if (val < 0)
    return E_FAIL;
  m_pgame->m_pscore->m_scoreFirst1Up = val;
  if (m_pgame->m_pscore->m_scoreSecond1Up < val)
    m_pgame->m_pscore->m_scoreSecond1Up = val;
  if (m_pgame->m_pscore->GetScore() < m_pgame->m_pscore->m_scoreFirst1Up)
    m_pgame->m_pscore->m_scoreNext1Up = val;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::get_ScoreSecond1Up
(
  int* pRet
)
{
  *pRet = m_pgame->m_pscore->m_scoreSecond1Up;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::put_ScoreSecond1Up
(
  int val
)
{
  if (val < 0)
    return E_FAIL;
  m_pgame->m_pscore->m_scoreSecond1Up = val;
  if (val < m_pgame->m_pscore->m_scoreFirst1Up)
    m_pgame->m_pscore->m_scoreFirst1Up = val;
  if (m_pgame->m_pscore->GetScore() > m_pgame->m_pscore->m_scoreFirst1Up  &&
      m_pgame->m_pscore->GetScore() < m_pgame->m_pscore->m_scoreSecond1Up)
    m_pgame->m_pscore->m_scoreNext1Up = val;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::get_DScoreNext1Up
(
  int* pRet
)
{
  *pRet = m_pgame->m_pscore->m_dscoreNext1Up;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::put_DScoreNext1Up
(
  int val
)
{
  if (val < 0)
    return E_FAIL;
  m_pgame->m_pscore->m_dscoreNext1Up = val;
  if (m_pgame->m_pscore->GetScore() > m_pgame->m_pscore->m_scoreFirst1Up && m_pgame->m_pscore->GetScore() > 0)
    {
    m_pgame->m_pscore->m_scoreNext1Up = m_pgame->m_pscore->m_scoreFirst1Up;
    while (m_pgame->m_pscore->m_scoreNext1Up < m_pgame->m_pscore->GetScore())
      m_pgame->m_pscore->m_scoreNext1Up += m_pgame->m_pscore->m_dscoreNext1Up;
    }
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::get_ShipsStart
(
  int* pRet
)
{
  *pRet = m_pgame->m_pscore->m_cshipStart;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::put_ShipsStart
(
  int val
)
{
  if (val < 0)
    return E_FAIL;
  m_pgame->m_pscore->m_cshipStart = val;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::get_Tag
(
  VARIANT* pRet
)
{
  if (!pRet)
    return E_INVALIDARG;
  VariantInit(pRet);
  return VariantCopy(pRet, &m_pgame->m_varTag);
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::put_Tag
(
  VARIANT val
)
{
  return VariantCopy(&m_pgame->m_varTag, &val);
}



//***************************************************************************
// IDispatch Interface
//***************************************************************************

//---------------------------------------------------------------------------
// Method needed by COleAuto, so it can implement IDispatch for us.
//---------------------------------------------------------------------------
HRESULT CGameOA::GetTypeLibInfo
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
  *ppclsidOut = &CLSID_Game;
  *ppiidOut   = &IID_IGame;
  *ppptlOut   = &g_ptlMain;
  return S_OK;
}



//***************************************************************************
// IProvideClassInfo Interfaces
//***************************************************************************

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::GetClassInfo
(
  ITypeInfo** pptinfoOut
)
{
  HRESULT hr = ((COleAuto *)this)->CheckTypeInfo(0, 0x0409);
  if (hr)
    return hr;
  *pptinfoOut = g_ptinfoClsGameOA;
  (*pptinfoOut)->AddRef();
  return S_OK;
}




//***************************************************************************
// IConnectionPointContainer Interface
//***************************************************************************

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::EnumConnectionPoints
(
  LPENUMCONNECTIONPOINTS* ppEnum
)
{
  return E_NOTIMPL;   // UNDONE: Implement this method
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::FindConnectionPoint
(
  REFIID             iid,
  LPCONNECTIONPOINT* ppCpOut
)
{
  if (!ppCpOut)
    return E_INVALIDARG;

  if (iid == DIID_IGameEvents || iid == IID_IDispatch)
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
CGameOA::XCP::XCP
(
  void
)
{
  m_cref = 1;
  for (int i=0; i<GAME_cADVISE; i++)
    m_rgpdisp[i] = NULL;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
void CGameOA::XCP::Close
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
STDMETHODIMP CGameOA::XCP::QueryInterface
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
STDMETHODIMP_(ULONG) CGameOA::XCP::AddRef
(
  void 
)
{
  return ++m_cref;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CGameOA::XCP::Release
(
  void 
)
{
  CGame *pgame = this->PGAMEOA()->m_pgame;
  ASSERT(m_cref, "bad m_cref");
  m_cref--;
  if (!m_cref && !pgame->m_cref)
    {
    delete pgame;
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
STDMETHODIMP CGameOA::XCP::GetConnectionInterface
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
STDMETHODIMP CGameOA::XCP::GetConnectionPointContainer
(
  IConnectionPointContainer** ppCPC
)
{
  if (!ppCPC)
    return E_INVALIDARG;

  *ppCPC = this->PGAMEOA();
  (*ppCPC)->AddRef();
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::XCP::Advise
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
  for (ppdisp=m_rgpdisp; *ppdisp && ppdisp<&m_rgpdisp[GAME_cADVISE]; ppdisp++)
    ;
  // Did we find one?
  if (ppdisp >= &m_rgpdisp[GAME_cADVISE])
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
STDMETHODIMP CGameOA::XCP::Unadvise
(
  DWORD dwCookie
)
{
  if (!dwCookie || dwCookie > GAME_cADVISE)
    return E_INVALIDARG;

  m_rgpdisp[dwCookie-1]->Release();
  m_rgpdisp[dwCookie-1] = NULL;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGameOA::XCP::EnumConnections
(
  LPENUMCONNECTIONS* ppEnum
)
{
  return E_NOTIMPL;   // UNDONE: Implement this method
}


//--- EOF -------------------------------------------------------------------
