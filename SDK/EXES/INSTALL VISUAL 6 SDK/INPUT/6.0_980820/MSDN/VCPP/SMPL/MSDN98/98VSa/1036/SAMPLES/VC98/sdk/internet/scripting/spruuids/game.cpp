//---------------------------------------------------------------------------
// Game.cpp
//---------------------------------------------------------------------------
// Sample spr program
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
#include "SpruuidP.h"
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>


//---------------------------------------------------------------------------
// DEBUG info
//---------------------------------------------------------------------------
SZTHISFILE


//---------------------------------------------------------------------------
// Forward Declares
//---------------------------------------------------------------------------
int DisplayScriptError(HINSTANCE hinst, HWND hwndParent, LPCSTR pszError, int ichError);


//---------------------------------------------------------------------------
// Image data
//---------------------------------------------------------------------------
#define ADDPIX(    id,idNext,x,y,cx,cy) {iimg##idNext, x, y, cx, cy},
#define ADDPIXLAST(id,idNext,x,y,cx,cy) {iimg##idNext, x, y, cx, cy}
#define ADDPIXIMG
IMG Game_img[] = {
#include "SpruuidP.pix"
};
#undef ADDPIX
#undef ADDPIXLAST
#undef ADDPIXIMG


//---------------------------------------------------------------------------
// Various Globals
//---------------------------------------------------------------------------
CGame     *g_pgame            = NULL;
ITypeLib  *g_ptlGameSubObj    = NULL;
ITypeInfo *g_ptinfoClsGame    = NULL;
ITypeInfo *g_ptinfoIntGame    = NULL;
char      *CGame::s_pszError  = NULL;
ULONG      g_clineOffset;


//---------------------------------------------------------------------------
// Cover for contstructor.  Use instead of new CGame!
//---------------------------------------------------------------------------
HRESULT CGame::s_hr = E_FAIL;

HRESULT CGame::CreateGame
(
  HINSTANCE hinst,
  HWND      hwndDlg,
  HWND      hwndPS,
  HWND      hwndStat,
  IOleComponentManager *pcm,
  CGame   **ppgameOut
)
{
  CGame  *pgame;
  HRESULT hr;

  *ppgameOut = NULL;
  pgame = new CGame(hinst, hwndDlg, hwndPS, hwndStat, pcm);
  if (!pgame)
    return E_OUTOFMEMORY;
  else if (pgame->s_hr)
    {
    delete pgame;
    return s_hr;
    }

// ##### BEGIN ACTIVEX SCRIPTING SUPPORT #####
// Add the Game as a Named Item & load its code
  g_clineOffset = 0;
  hr = pgame->ParseFile(g_pszCodeFile, L"Game");
  if (hr)
    {
    MessageBox(g_papp->m_hwndDlg, s_pszError ? s_pszError : "Unspecified Error", "Spruuids", MB_OK | MB_ICONEXCLAMATION);
    return hr;
    }
// #####  END  ACTIVEX SCRIPTING SUPPORT #####

  // Create sprite classes based upon $OBJECT lines in file
  for (int i=0; i<pgame->m_csubobj; i++)
    {
    CHECK(CSpriteClass::Create(pgame->m_pdisp, &pgame->m_rgpsc[i]));
    pgame->m_rgpdispSubObjs[i] = pgame->m_rgpsc[i]->GetDispatch();
    pgame->m_rgpdispSubObjs[i]->AddRef();
    }

  if (hr)
    {
CleanUp:
    delete pgame;
    return hr;
    }

// ##### BEGIN ACTIVEX SCRIPTING SUPPORT #####
  // Start the script running...
  hr = pgame->m_ps->SetScriptState(SCRIPTSTATE_CONNECTED);
  if (hr)
    {
    delete pgame;
    return hr;
    }
// #####  END  ACTIVEX SCRIPTING SUPPORT #####

  // Success
  *ppgameOut = pgame;
  return S_OK;
}


//---------------------------------------------------------------------------
// Constructor
//---------------------------------------------------------------------------
CGame::CGame
(
  HINSTANCE hinst,
  HWND      hwndDlg,
  HWND      hwndPS,
  HWND      hwndStat,
  IOleComponentManager *pcm
)
{
  INIT_SIGNATURE(SIG_Game);

  // Setup globals
  g_pgame       = this;
  s_hr          = S_OK;

  // Init members
  m_hinst        = hinst;
  m_hwndDlg      = hwndDlg;
  m_hwndPS       = hwndPS;
  m_hwndStat     = hwndStat;
  m_cref         = 1;
  m_fPaused      = FALSE;
  m_fShipDead    = FALSE;
  m_fShipRestart = FALSE;
  m_fGameOver    = TRUE;
  m_pcm          = pcm;
  m_ps           = NULL;
  m_psp          = NULL;
  VariantInit(&m_varTag);
  m_pscore       = NULL;
  m_pdisp        = NULL;
  m_pdispBaseObject = NULL;
  m_pgameoa      = NULL;
  m_csubobj      = 0;

  CoCreateGuid(&m_libidSubObj);
  CoCreateGuid(&m_clsidSubObj);
  CoCreateGuid(&m_iidSubObj);

  m_pgameoa = new CGameOA(this);
  if (!m_pgameoa)
    {
    s_hr = E_OUTOFMEMORY;
    return;
    }
  this->SetBaseObject(m_pgameoa->GetDispatch());

  m_pdisp = new CDisplay(hinst, hwndPS, GetDC(hwndPS),
                         this->GetUnknown(), CGameOA::FireCollide,
                         sizeof(Game_img)/sizeof(IMG), Game_img, ID_BMP_SPRITES);
  if (!m_pdisp)
    {
    s_hr = E_OUTOFMEMORY;
    return;
    }

  s_hr = CScore::CreateScore(
                      m_hinst,       // hinst to load resources from
                      m_hwndDlg,     // hwnd on which to draw score
                      m_hwndPS,      // hwnd of PlaySurface
                      m_hwndStat,    // hwnd of Status bar
                      2500,          // scoreFirst1Up
                      5000,          // scoreSecond1Up
                      2500,          // dscoreNext1Up
                      3,             // cshipStart;
                      ID_BMP_SHIP,   // idbmpShip;
                      ID_BMP_PLUS,   // idbmpPlus;
                      &m_pscore);
  if (s_hr)
    return;
  ASSERT(m_pscore, "Good hr, but m_pscore==NULL");

  // Default to VBScript
  extern const CLSID CLSID_VBScript;
  m_clsidEngine = CLSID_VBScript;

  // Success
  s_hr = S_OK;
}


//---------------------------------------------------------------------------
// Clean up allocated resources
//---------------------------------------------------------------------------
CGame::~CGame
(
  void
)
{
  CHECK_SIGNATURE(SIG_Game);
  this->Close();
  if (m_pgameoa)
    delete m_pgameoa;
  DESTROY_SIGNATURE(SIG_Game);
}


//---------------------------------------------------------------------------
// Clean up allocated resources
//---------------------------------------------------------------------------
void CGame::Close
(
  void
)
{
  CHECK_SIGNATURE(SIG_Game);

  if (g_mode != MODE_PLAYBACK)
    KillTimer(m_hwndPS, 0);

  g_pgame = NULL;

  // Clear this, since it may be an object
  VariantClear(&m_varTag);

// ##### BEGIN ACTIVEX SCRIPTING SUPPORT #####
  // Release the language engine, since it may hold on to us
  if (m_psp)
    m_psp->Release();
  if (m_ps)
    {
    m_ps->Close();
    m_ps->Release();
    }
// #####  END  ACTIVEX SCRIPTING SUPPORT #####

  // Drop all sink's that have Advise()'d us, since they might keep us alive
  m_pgameoa->m_cp.Close();

  // Release all existing sprites
  if (m_pdisp)
    m_pdisp->DestroyAll();

  // Close & Release the SpriteClass Sub Objects
  for (int i=0; i<m_csubobj; i++)
    {
    delete [] m_rgpwszSubObjs[i];
    if (m_rgpdispSubObjs[i])
      {
      m_rgpdispSubObjs[i]->Release();
      m_rgpdispSubObjs[i] = NULL;
      }
    if (m_rgpsc[i])
      {
      m_rgpsc[i]->Close();
      m_rgpsc[i]->Release();
      m_rgpsc[i] = NULL;
      }
    }

  // Now destroy the Score & Display objects
  if (m_pscore)
    {
    delete m_pscore;
    m_pscore = NULL;
    }
  if (m_pdisp)
    {
    delete m_pdisp;
    m_pdisp = NULL;
    }
}


//***************************************************************************
// IUnknown Interface
//***************************************************************************

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGame::QueryInterface
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
  else if (iid == IID_IGameSubObjects)
    *ppvObjOut = this->GetDispatch();
  else if (iid == IID_IActiveScriptSite)
    *ppvObjOut = (IActiveScriptSite *)this;
  else if (iid == IID_IActiveScriptSiteWindow)
    *ppvObjOut = (IActiveScriptSiteWindow *)this;
  else if (iid == IID_IProvideClassInfo)
    *ppvObjOut = (IProvideClassInfo *)this;
  else if (iid == IID_IProvideMultipleClassInfo)
    *ppvObjOut = (IProvideMultipleClassInfo *)this;
  else if (iid == IID_IGame)
    *ppvObjOut = (IGame *)(this->m_pgameoa);
  else if (iid == IID_IConnectionPointContainer)
    *ppvObjOut = (IConnectionPointContainer *)(this->m_pgameoa);

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
STDMETHODIMP_(ULONG) CGame::AddRef
(
  void 
)
{
  return ++m_cref;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CGame::Release
(
  void 
)
{
  ASSERT(m_cref, "bad m_cref");
  m_cref--;
  if (!m_cref)
    {
    m_pgameoa->m_cp.Close();     // Make sure nobody's holding on to us because we're holding their sink
    if (!m_cref && !m_pgameoa->m_cp.m_cref)
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
// Re-implement COleAuto's GetIDsOfNames(), so we can implement the dynamic
// properties we added for the $OBJECT=SpriteClassName lines.
//---------------------------------------------------------------------------
STDMETHODIMP CGame::GetIDsOfNames
(
  REFIID    iid,
  OLECHAR** rgszNames,
  UINT      cNames,
  LCID      lcid,
  DISPID*   prgdispid
)
{
  // Validate Args
  if (iid != IID_NULL)
      return E_INVALIDARG;

  // See if a sub-object matches the name passed in.
  for (int i=0; i<m_csubobj; i++)
    if (!wcscmp(*rgszNames, m_rgpwszSubObjs[i]))
      {
      if (cNames != 1)
        return DISP_E_NONAMEDARGS;
      *prgdispid = 0x80010000 | i;
      return S_OK;
      }

  return COleAuto::GetIDsOfNames(iid, rgszNames, cNames, lcid, prgdispid);
}


//---------------------------------------------------------------------------
// Re-implement COleAuto's Invoke(), so we can implement the dynamic
// properties we added for the $OBJECT=SpriteClassName lines.
//---------------------------------------------------------------------------
STDMETHODIMP CGame::Invoke
(
  DISPID      dispid,
  REFIID      riid,
  LCID        lcid,
  WORD        wFlags,
  DISPPARAMS* pdispparams,
  VARIANT*    pvarResult,
  EXCEPINFO*  pexcepinfo, 
  UINT*       puArgErr)
{
  IDispatch *pdisp = NULL;

  // Validate Args
  if (pvarResult)
    VariantInit(pvarResult);
  if (puArgErr)
    *puArgErr = 0;
  SetErrorInfo(0L, NULL);

  // If dispid isn't a dynamic property, call COleAuto's dispatch,
  // and it will forward the request on to m_pdispBaseObject.
  if ((dispid & 0x80010000) != 0x80010000)
    return COleAuto::Invoke(dispid, riid, lcid, wFlags, pdispparams, pvarResult, pexcepinfo, puArgErr);
  // It's for one of our property objects...

  // Make sure we have either a PropGet or a Method
  if (!(wFlags & (DISPATCH_METHOD | DISPATCH_PROPERTYGET)))
    return DISP_E_MEMBERNOTFOUND;

  dispid &= 0xffff;
  if (dispid >= m_csubobj)
    return DISP_E_MEMBERNOTFOUND;

  if (pdispparams->cArgs)
    return DISP_E_BADPARAMCOUNT;

  if (pdispparams->cNamedArgs)
    return DISP_E_NONAMEDARGS;

  // Get an addref'd IDispatch to the property object
  pdisp = m_rgpdispSubObjs[dispid];
  ASSERT(pdisp, "NULL m_rgpdispSubObjs[]");

  if (pvarResult)	
    {
    pvarResult->vt = VT_DISPATCH;
    pvarResult->pdispVal = pdisp;
    pdisp->AddRef();		// We're returning this disp ptr
    }

  return S_OK;
}


//---------------------------------------------------------------------------
// Method needed by COleAuto, so it can implement IDispatch for us.
//---------------------------------------------------------------------------
HRESULT CGame::GetTypeLibInfo
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
  HRESULT hr = this->BuildTypeInfo();
  if (hr)
    return hr;
  *phinstOut  = NULL;
  *pplibidOut = &m_libidSubObj;
  *pwMajLib   = 1;
  *pwMinLib   = 0;
  *ppclsidOut = &m_clsidSubObj;
  *ppiidOut   = &m_iidSubObj;
  *ppptlOut   = &g_ptlGameSubObj;
  return S_OK;
}


//***************************************************************************
// IProvideClassInfo Interfaces
//***************************************************************************

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGame::GetClassInfo
(
  ITypeInfo** pptinfoOut
)
{
  HRESULT hr = ((COleAuto *)this)->CheckTypeInfo(0, 0x0409);
  if (hr)
    return hr;
  *pptinfoOut = g_ptinfoClsGame;
  (*pptinfoOut)->AddRef();
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGame::GetGUID
(
  DWORD dwGuidKind,
  GUID* pGUID
)
{
  if (pGUID)
    return E_INVALIDARG;

  if (dwGuidKind != GUIDKIND_DEFAULT_SOURCE_DISP_IID)
    return E_INVALIDARG;

  *pGUID = DIID_IGameEvents;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGame::GetMultiTypeInfoCount
(
  ULONG *pcti
)
{
  if (!pcti)
    return E_INVALIDARG;

  *pcti = 2;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGame::GetInfoOfIndex
(
  ULONG       iti,
  DWORD       dwFlags,
  ITypeInfo** pptiCoClass,
  DWORD*      pdwTIFlags,
  ULONG*      pcdispidReserved,
  IID*        piidPrimary,
  IID*        piidSource
)
{
  HRESULT    hr        = S_OK;
  ITypeInfo *ptinfoOut = NULL;

  if (iti > 1)
    hr = E_FAIL;

//  if (dwFlags & ~MULTICLASSINFO_ALL)
//    hr = E_INVALIDARG;

  if (dwFlags & MULTICLASSINFO_GETTYPEINFO)
    {
    if (!pptiCoClass || !pdwTIFlags)
      hr = E_INVALIDARG;
    else
      {
      *pdwTIFlags  = 0L;
      *pptiCoClass = NULL;
      if (iti == 0)
        {
        hr = ((COleAuto *)this)->CheckTypeInfo(0, 0x0409);
        if (hr)
          return hr;
        ptinfoOut = g_ptinfoClsGame;
        }
      else
        {
        hr = ((COleAuto *)m_pgameoa)->CheckTypeInfo(0, 0x0409);
        if (hr)
          return hr;
        ptinfoOut = g_ptinfoClsGameOA;
        }
      }
    }

  if (dwFlags & MULTICLASSINFO_GETNUMRESERVEDDISPIDS)
    {
    if (!pcdispidReserved)
      hr = E_INVALIDARG;
    else
      *pcdispidReserved = 256;
    }

  if (dwFlags & MULTICLASSINFO_GETIIDPRIMARY)
    {
    if (!piidPrimary)
      hr = E_INVALIDARG;
    else if (iti == 0)
      *piidPrimary = IID_IGameSubObjects;
    else
      *piidPrimary = IID_IGame;
    }

  if (dwFlags & MULTICLASSINFO_GETIIDSOURCE)
    {
    if (!piidSource)
      hr = E_INVALIDARG;
    else if (iti == 0)
      *piidSource = IID_NULL;
    else
      *piidSource = DIID_IGameEvents;
    }

  // Fill in ptinfo out param
  if (hr)
    {
    if (pptiCoClass)
      *pptiCoClass = NULL;
    }
  else if (pptiCoClass)
    {
    *pptiCoClass = ptinfoOut;
    (*pptiCoClass)->AddRef();
    }

  return hr;
}



// ##### BEGIN ACTIVEX SCRIPTING SUPPORT #####
//***************************************************************************
// IActiveScriptSite Interface
//***************************************************************************

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGame::GetLCID
(
  LCID *plcid
)
{
  return E_NOTIMPL;     // Use system settings
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGame::GetItemInfo
(
  LPCOLESTR   pstrName,
  DWORD       dwReturnMask,
  IUnknown**  ppunkItemOut,
  ITypeInfo** pptinfoOut
)
{
  HRESULT hr;

  if (dwReturnMask & SCRIPTINFO_ITYPEINFO)
    {
    if (!pptinfoOut)
      return E_INVALIDARG;
    *pptinfoOut = NULL;
    }

  if (dwReturnMask & SCRIPTINFO_IUNKNOWN)
    {
    if (!ppunkItemOut)
      return E_INVALIDARG;
    *ppunkItemOut = NULL;
    }

  if (!_wcsicmp(L"game", pstrName))
    {
    if (dwReturnMask & SCRIPTINFO_ITYPEINFO)
      {
      hr = ((COleAuto *)this)->CheckTypeInfo(0, 0x0409);
      if (hr)
        return hr;
      *pptinfoOut = g_ptinfoClsGame;
      (*pptinfoOut)->AddRef();      // because returning
      }
    if (dwReturnMask & SCRIPTINFO_IUNKNOWN)
      {
      *ppunkItemOut = this->GetUnknown();
      (*ppunkItemOut)->AddRef();    // because returning
      }
    return S_OK;
    }

  return TYPE_E_ELEMENTNOTFOUND;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGame::GetDocVersionString
(
  BSTR *pbstrVersion
)
{
  return E_NOTIMPL;   // UNDONE: Implement this method
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGame::RequestItems
(
  void 
)
{
  return m_ps->AddNamedItem(L"Game", SCRIPTITEM_ISVISIBLE | SCRIPTITEM_ISSOURCE);
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGame::RequestTypeLibs
(
  void 
)
{
  return m_ps->AddTypeLib(LIBID_SPRUUIDS, 1, 0, 0);
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGame::OnScriptTerminate
(
  const VARIANT   *pvarResult,
  const EXCEPINFO *pexcepinfo
)
{
  // UNDONE: Put up error dlg here
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGame::OnStateChange
(
  SCRIPTSTATE ssScriptState
)
{
  // Don't care about notification
  return S_OK;
}


//---------------------------------------------------------------------------
// Display the error
//---------------------------------------------------------------------------
STDMETHODIMP CGame::OnScriptError
(
  IActiveScriptError *pse
)
{
  char      szError[1024];
  char     *pszArrow = NULL;
  BOOL      fAlloc = FALSE;
  EXCEPINFO ei;
  DWORD     dwSrcContext;
  ULONG     ulLine;
  LONG      ichError;
  BSTR      bstrLine = NULL;
  HRESULT   hr;

  CHECK(pse->GetExceptionInfo(&ei));
  CHECK(pse->GetSourcePosition(&dwSrcContext, &ulLine, &ichError));
  ulLine += g_clineOffset;    // Adjust for $ENGINE/$OBJECT/etc. lines
  hr = pse->GetSourceLineText(&bstrLine);
  if (hr)
    hr = S_OK;  // Ignore this error, there may not be source available
  
  if (!hr)
    {
    MAKE_ANSIPTR_FROMWIDE(pszSrc,  ei.bstrSource);
    MAKE_ANSIPTR_FROMWIDE(pszDesc, ei.bstrDescription);
    MAKE_ANSIPTR_FROMWIDE(pszLine, bstrLine);
    if (ichError > 0 && ichError < 255)
      {
      pszArrow = new char[ichError+1];
      memset(pszArrow, '-', ichError);
      pszArrow[ichError-1] = 'v';
      pszArrow[ichError]   = 0;
      fAlloc = TRUE;
      }
    else
      pszArrow = "";

    wsprintf(szError, "Source:'%s'\nFile:'%s'  Line:%d  Char:%d\nError:%d  '%s'\n%s\n%s",
                      pszSrc, g_pszCodeFile, ulLine, ichError,
                      (int)ei.wCode, pszDesc, pszArrow, pszLine);
    DisplayScriptError(g_hinst, m_hwndDlg, szError, ichError);
    }

CleanUp:
  if (fAlloc)
    delete [] pszArrow;
  if (bstrLine)
    SysFreeString(bstrLine);

  return hr;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGame::OnEnterScript
(
  void 
)
{
  // No need to do anything
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGame::OnLeaveScript
(
  void 
)
{
  // No need to do anything
  return S_OK;
}



//***************************************************************************
// IActiveScriptSiteWindow Interface
//***************************************************************************

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGame::GetWindow
(
  HWND *phwndOut
)
{
  if (!phwndOut)
    return E_INVALIDARG;
  *phwndOut = m_hwndDlg;
  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CGame::EnableModeless
(
  BOOL fEnable
)
{
  if (fEnable)
    m_pcm->FOnComponentExitState(g_papp->m_idcomp, cmgrstateModal, cmgrcontextAll, 0, NULL);
  else
    m_pcm->OnComponentEnterState(g_papp->m_idcomp, cmgrstateModal, cmgrcontextAll, 0, NULL, NULL);
  return S_OK;
}
// #####  END  ACTIVEX SCRIPTING SUPPORT #####


//***************************************************************************
// Misc WndProc-related Methods
//***************************************************************************

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
BOOL AppEvt_DlgProc
(
  HWND   hwnd,
  UINT   msg,
  WPARAM wp,
  LPARAM lp
)
{
  if (!g_pgame)
    return FALSE;

  return g_pgame->DlgProc(hwnd, msg, wp, lp);
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
BOOL CGame::DlgProc
(
  HWND   hwnd,
  UINT   msg,
  WPARAM wp,
  LPARAM lp
)
{
  switch (msg)
    {
    case WM_ERASEBKGND:
      if (m_pscore)
        {
        m_pscore->Paint((HDC)wp);
        return TRUE;
        }
      break;
    }
  return FALSE;
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
LRESULT AppEvt_PSWndProc
(
  HWND   hwnd,
  UINT   msg,
  WPARAM wp,
  LPARAM lp
)
{
  if (!g_pgame)
    return DefWindowProc(hwnd, msg, wp, lp);

  return g_pgame->PSWndProc(hwnd, msg, wp, lp);
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
LRESULT CGame::PSWndProc
(
  HWND   hwnd,
  UINT   msg,
  WPARAM wp,
  LPARAM lp
)
{
  switch (msg)
    {
    case WM_PAINT:
      if (m_pdisp)
        {
        if (wp)
          m_pdisp->Paint((HDC)wp);
        else
          {
          PAINTSTRUCT ps;

          BeginPaint(hwnd, &ps);
          m_pdisp->Paint(ps.hdc);
          EndPaint(hwnd, &ps);
          }
        return 1L;
        }
      break;

    case WM_ERASEBKGND:
      SelectObject((HDC)wp, (HGDIOBJ)(m_pdisp->m_hbrushBack ? (HBRUSH)(m_pdisp->m_hbrushBack) : (HBRUSH)g_hbrushStock));
      PatBlt((HDC)wp, 0, 0, 32000, 32000, PATCOPY);
      SelectObject((HDC)wp, g_hbrushStock);
      return TRUE;

    case WM_SIZE:
      {
      RECT rect;

      GetClientRect(hwnd, &rect);
      m_pdisp->m_cx = rect.right;
      m_pdisp->m_cy = rect.bottom;
      break;
      }

    case WM_TIMER:
      {
      if (m_fGameOver)
        break;

      m_pdisp->Timer();

      if (m_fPaused)
        break;

      if (m_fShipRestart)
        {
        m_pdisp->Refresh();
        break;
        }

      if (!m_fShipDead)
        {
        static cRefresh = 0;

        m_pgameoa->FireTick();
        if (++cRefresh > 5)	      // What's a reasonable number?
          {
          m_pdisp->Refresh();
          cRefresh = 0;
          }
        }
      else
        {
        m_pscore->ShipKilled();
        InvalidateRect(m_hwndDlg, NULL, TRUE);
        if (m_pscore->GetCShip() <= 0)
          {
          this->GameOver();
          break;
          }

        m_fShipDead = FALSE;
        m_fShipRestart = TRUE;
        InvalidateRect(hwnd, NULL, TRUE);
        }
      break;
      }

    case WM_KEYDOWN:
      m_pgameoa->FireKeyDown(wp);
      break;

    case WM_CHAR:
      m_pgameoa->FireKeyPress(wp);
      break;

    case WM_KEYUP:
      m_pgameoa->FireKeyUp(wp);
      break;

    case WM_MOUSEMOVE:
      m_pgameoa->FireMouseMove(LOWORD(lp), HIWORD(lp), wp);
      break;

    case WM_LBUTTONDOWN:
      m_pgameoa->FireMouseDown(LOWORD(lp), HIWORD(lp), wp, MK_LBUTTON);
      break;

    case WM_RBUTTONDOWN:
      m_pgameoa->FireMouseDown(LOWORD(lp), HIWORD(lp), wp, MK_RBUTTON);
      break;

    case WM_MBUTTONDOWN:
      m_pgameoa->FireMouseDown(LOWORD(lp), HIWORD(lp), wp, MK_MBUTTON);
      break;

    case WM_LBUTTONUP:
      m_pgameoa->FireMouseUp(LOWORD(lp), HIWORD(lp), wp, MK_LBUTTON);
      break;

    case WM_RBUTTONUP:
      m_pgameoa->FireMouseUp(LOWORD(lp), HIWORD(lp), wp, MK_RBUTTON);
      break;

    case WM_MBUTTONUP:
      m_pgameoa->FireMouseUp(LOWORD(lp), HIWORD(lp), wp, MK_MBUTTON);
      break;
    }

  return DefWindowProc(hwnd, msg, wp, lp);
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
LRESULT CALLBACK ScriptErrorDialog
(
  HWND   hwnd,
  UINT   msg,
  WPARAM wp,
  LPARAM lp
)
{
  LPCSTR pszError;

  switch (msg) 
    {
    case WM_INITDIALOG:
      pszError = (LPCSTR)lp;
      ShowWindow(hwnd, SW_HIDE);
      SendDlgItemMessage(hwnd, ID_CTL_ERROR, WM_SETFONT,
                         (WPARAM)GetStockObject(ANSI_FIXED_FONT), MAKELPARAM(FALSE,0));
      SendDlgItemMessage(hwnd, ID_CTL_ERROR, WM_SETTEXT, 0, (LPARAM)pszError);
      ShowWindow(hwnd, SW_SHOW);
      return (TRUE);

     case WM_COMMAND:
       switch(LOWORD(wp))
         {
         case IDOK:
         case IDCANCEL:
           goto Destroy;
         }
       break;
    }
  return FALSE;

Destroy:
  EndDialog(hwnd, 0);
  return TRUE;
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
int DisplayScriptError
(
  HINSTANCE hinst,
  HWND      hwndParent,
  LPCSTR    pszError,
  int       ichError
)
{
  int   result;
  UINT  len = lstrlen(pszError);
  UINT  newlen;
  UINT  newindex;
  UINT  i;
  LPSTR pszNewError;

  // Figure out how long the real string will be
  newlen = 0;
  for (i=0; i<len; i++)
    {
    CHAR c = pszError[i];

    if (c == '\n')
      newlen +=1;               // Convert \n to \r\n
    else if (c == '\r')
      {
      if (pszError[i+1] == '\n')
        {
        newlen++;               // Leave \r\n alone
        i++;
        }
      else
        newlen++;               // Convert \r to \r\n
      }
    newlen++;
    }

  // Create the real string:
  pszNewError = new char[newlen+1];
  if (!pszNewError)
    return -1;

  newindex = 0;
  for (i=0; i<len; i++)
    {
    CHAR c = pszError[i];

    if (c == '\n')
      pszNewError[newindex++] = '\r';             // Convert \n to \r\n
    else if (c == '\r')
      {
      if (pszError[i+1] == '\n')
        {
        pszNewError[newindex++] = pszError[i++];  // Leave \r\n alone
        i++;
        }
      else
        {
        pszNewError[newindex++] = c;              // Convert \r to \r\n
        c = '\n';
        }
      }
    pszNewError[newindex++] = c;
    }
  pszNewError[newindex] = '\0';

  // Create the dialog box
  g_pgame->m_pcm->OnComponentEnterState(g_papp->m_idcomp, cmgrstateModal, cmgrcontextAll, 0, NULL, NULL);
  g_pgame->Pause(1);
  result = DialogBoxParam(
	  hinst,                         // Handle to application instance
	  MAKEINTRESOURCE(ID_DLG_ERROR), // Identifies dialog box template name  
	  hwndParent,                    // Handle to owner window
	  (DLGPROC)ScriptErrorDialog,    // Pointer to dialog box procedure
	  (DWORD)pszNewError);           // Context
  g_pgame->m_pcm->FOnComponentExitState(g_papp->m_idcomp, cmgrstateModal, cmgrcontextAll, 0, NULL);
  SetFocus(g_pgame->m_hwndPS);

  delete[] pszNewError;

  return result;
}


//***************************************************************************
// Misc General Methods
//***************************************************************************

//---------------------------------------------------------------------------
// New level
//---------------------------------------------------------------------------
void CGame::NewLevel
(
  void
)
{
  g_pgame->m_pdisp->DestroyAll();
  m_pscore->NextLevel();
  m_fShipRestart = TRUE;
  InvalidateRect(m_hwndPS,  NULL, TRUE);
  InvalidateRect(m_hwndDlg, NULL, TRUE);
  m_pgameoa->FireNewLevel();
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void AppEvt_NewGame
(
  void
)
{
  g_pgame->NewGame();
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void CGame::NewGame
(
  void
)
{
  m_pdisp->DestroyAll();
  m_pscore->NewGame();
  m_fGameOver    = FALSE;
  m_fShipRestart = TRUE;
  m_pgameoa->FireNewGame();
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
BOOL AppEvt_Pause
(
  int pause
)
{
  return g_pgame->Pause(pause);
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
BOOL CGame::Pause
(
  int pause
)
{
  if (pause == -1)            // Toggle
    pause = !m_fPaused;

  switch (pause)
    {
    case 1:                   // Pause
      if (m_fGameOver)
        goto UnPause;
      if (g_mode != MODE_PLAYBACK)
        KillTimer(m_hwndPS, 0);
      m_fPaused = TRUE;
      break;

    case 0:                   // UnPause
UnPause:
      if (g_mode != MODE_PLAYBACK)
        SetTimer(m_hwndPS, 0, 40, NULL);
      m_fPaused = FALSE;
      break;
    }

  if (m_fPaused)
    m_pscore->SetStatusText("Game Paused.  Press F3 to Continue.");
  else
    m_pscore->SetStatusText("");

  return m_fPaused;
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
BOOL AppEvt_FQueryTerminate
(
  BOOL fPromptUser
)
{
  return g_pgame->FQueryTerminate(fPromptUser);
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
BOOL CGame::FQueryTerminate
(
  BOOL fPromptUser
)
{
  // UNDONE
  return TRUE;
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
void CGame::GameOver
(
  void
)
{
  m_fGameOver = TRUE;
  InvalidateRect(m_hwndPS, NULL, TRUE);
  m_pscore->SetStatusText("Game Over.  Press F2 to Play a New Game.");
}


// ##### BEGIN ACTIVEX SCRIPTING SUPPORT #####
//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
HRESULT CGame::CreateScriptEngine
(
  LPCOLESTR pstrItemName
)
{
  HRESULT hr;

  if (m_ps)
    return S_FALSE;   // Already created it

  // Create the ActiveX Scripting Engine
  hr = CoCreateInstance(m_clsidEngine, NULL, CLSCTX_INPROC_SERVER, IID_IActiveScript, (void **)&m_ps);
  if (hr)
    {
    s_pszError = "Creating the ActiveX Scripting engine failed.  Scripting engine is probably not correctly registered or CLSID incorrect.";
    return E_FAIL;
    }
  // Script Engine must support IActiveScriptParse for us to use it
  hr = m_ps->QueryInterface(IID_IActiveScriptParse, (void **)&m_psp);
  if (hr)
    {
    s_pszError = "ActiveX Scripting engine does not support IActiveScriptParse";
    return hr;
    }
  hr = m_ps->SetScriptSite(this);
  if (hr)
    return hr;
  // InitNew the object:
  hr = m_psp->InitNew();
  if (hr)
    return hr;
  hr = m_ps->AddNamedItem(L"Game", SCRIPTITEM_ISVISIBLE | SCRIPTITEM_ISSOURCE);
  return hr;
}
// #####  END  ACTIVEX SCRIPTING SUPPORT #####



//***************************************************************************
// Parsing support
//***************************************************************************

//---------------------------------------------------------------------------
// Skip white space, counting lines.  Treat \r & \n as white space only if
// fSkipNewLines is TRUE.
//---------------------------------------------------------------------------
void SkipWhite
(
  char **ppsz,
  BOOL   fSkipNewLines
)
{
  // Skip white space
  while (**ppsz && **ppsz<=' ')
    {
    if (**ppsz == '\r' || **ppsz == '\n')
      {
      if (!fSkipNewLines)
        return;
      if (**ppsz == '\r' && (*ppsz)[1] == '\n')
        ++*ppsz;
      g_clineOffset++;
      }
    ++*ppsz;
    }
}


//---------------------------------------------------------------------------
// Finds $OBJECT, $ENGINE, $INCLUDE, etc, parses past '=' to argument.  NULL
// terminates the argument, then returns a ptr to begining of arg & to beg
// of next line.
//---------------------------------------------------------------------------
struct
  {
  int   cch;
  char *psz;
  } g_rgtoken[] = 
    {
      {7, "$ENGINE"},
      {7, "$OBJECT"},
      {8, "$INCLUDE"},
      {0, ""},
    };

int FindToken
(
  char    *pszCur,
  char   **ppszBeginArg,
  char   **ppszNextLine,
  HRESULT *phr,
  char   **ppszError
)
{
  char chQuote = 0;
  char ch;

  *phr = S_OK;
  SkipWhite(&pszCur, TRUE);
  if (*pszCur != '$')
    {
    *ppszNextLine = pszCur;
    return 0;   // No token found
    }

  for (int i=0; g_rgtoken[i].cch; i++)
    {
    if (!strncmp(pszCur, g_rgtoken[i].psz, g_rgtoken[i].cch))
      {
      pszCur += g_rgtoken[i].cch;
      SkipWhite(&pszCur, FALSE);
      if (*pszCur != '=')
        {
        *ppszError = "Missing '=' on $ENGINE, $OBJECT, or $INCLUDE line";
        *phr = E_FAIL;
        return 0;
        }
      pszCur++;
      SkipWhite(&pszCur, FALSE);
      if (*pszCur <= ' ')
        {
        *ppszError = "Missing argument on $ENGINE, $OBJECT, or $INCLUDE line";
        *phr = E_FAIL;
        return 0;
        }
      if (*pszCur=='"' || *pszCur=='\'' || *pszCur=='<')
        {
        chQuote = *pszCur;
        if (chQuote == '<')
          chQuote = '>';
        pszCur++;
        }
      *ppszBeginArg = pszCur;
      if (chQuote)
        {
        // Look for End of String, EOL, or End of Quote
        while (*pszCur && *pszCur!='\n' && *pszCur!='\r' && *pszCur!=chQuote)
          pszCur++;
        }
      else
        {
        // Skip non-white space
        while (*pszCur > ' ')
          pszCur++;
        }
      ch = *pszCur;
      *pszCur = 0;
NextChar:
      switch (ch)
        {
        default:
          // Look for EOL
          pszCur++;
          ch = *pszCur;
          goto NextChar;

        case '\r':
          // Skip the cr we're at
          g_clineOffset++;
          pszCur++;
          if (*pszCur == '\n')
            pszCur++;
          break;

        case '\n':
          // Skip the newline we're at
          g_clineOffset++;
          pszCur++;
          break;

        case 0:
           break;
        }

      *ppszNextLine = pszCur;
      return i+1;
      }
    }

  *ppszError = "unrecognized token; must be $ENGINE, $OBJECT, or $INCLUDE";
  *phr = E_FAIL;
  return 0;
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
HRESULT CGame::ParseFile
(
  char     *pszFileName,
  LPCOLESTR pstrItemName
)
{
  struct _stat stat;
  size_t       cch;
  EXCEPINFO    ei;
  char        *pszT;
  char        *pszAlloc;
  FILE        *pfile;
  HRESULT      hr = S_OK;
  int          tk = 0;
  char        *pszArg;

  // Find the length of the file
  if (_stat(pszFileName, &stat))
    return E_FAIL;
  cch = stat.st_size;

  // Allocate a buffer to read the file
  pszAlloc = new char[cch+1];
  if (!pszAlloc)
    return E_OUTOFMEMORY;
  memset(pszAlloc, 0, cch);   // HACK: Since cch may be too large, zero-fill string

  // Open & read the file
  pfile = fopen(pszFileName, "rb");
  if (!pfile)
    {
    s_pszError = "Bad file name";
    hr = E_FAIL;
    goto Error;
    }
  fread(pszAlloc, cch, 1, pfile);
  fclose(pfile);

  // Parse lines begining w/$
  pszAlloc[cch] = 0;
  pszT = pszAlloc;
  while (tk=FindToken(pszT, &pszArg, &pszT, &hr, &s_pszError))
    {
    switch (tk)
      {
      case 1:   // $ENGINE
        {
        MAKE_WIDEPTR_FROMANSI(pwszCLSID, pszArg);
        hr = CLSIDFromString(pwszCLSID, &m_clsidEngine);
        if (hr)
          {
          s_pszError = "Bad $ENGINE={xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx} syntax";
          goto Error;
          }
        hr = this->CreateScriptEngine(pstrItemName);
        if (hr == S_FALSE)
          {
          s_pszError = "$ENGINE must be first line; Script Engine already created.";
          goto Error;
          }
        else if (hr)
          goto Error;
        break;
        }

      case 2:  // $OBJECT
        if (m_csubobj >= csubobjMAX)
          {
          s_pszError = "Too many $OBJECT lines";
          goto Error;
          }

        m_rgpwszSubObjs[m_csubobj] = new WCHAR [strlen(pszArg)+1];
        if (!m_rgpwszSubObjs[m_csubobj])
          {
          s_pszError = "Out Of Memory";
          goto Error;
          }
        UNICODE_FROM_ANSI(m_rgpwszSubObjs[m_csubobj], pszArg, 2*strlen(pszArg));
        m_rgpdispSubObjs[m_csubobj] = NULL;
        m_rgpsc[m_csubobj] = NULL;
        m_csubobj++;
        break;

      case 3:   // $INCLUDE
        hr = this->ParseFile(pszArg, pstrItemName);
        if (hr)
          goto Error;
        break;
      }
    }

  // If there's anything left, assume it's code
  if (*pszT)
    {
// ##### BEGIN ACTIVEX SCRIPTING SUPPORT #####
    // Make sure we've created the scripting engine
    if (!m_ps)
      {
      hr = this->CreateScriptEngine(pstrItemName);
      if (hr)
        goto Error;
      }

    // Hand it the code
    MAKE_WIDEPTR_FROMANSI(pwszCode, pszT);
    hr = m_psp->ParseScriptText(pwszCode, pstrItemName, NULL, NULL, 0, 0, 0L, NULL, &ei);
    hr = S_OK;    // Ignore parse errors, so user can press F9 to view source...
// #####  END  ACTIVEX SCRIPTING SUPPORT #####
    }

Error:
  delete [] pszAlloc;
  return hr;
}



//***************************************************************************
// Dynamic object model support
//***************************************************************************

//---------------------------------------------------------------------------
// Builds the typeinfo for the container object from the list of property 
// objects.
//---------------------------------------------------------------------------
HRESULT CGame::BuildTypeInfo
(
  void
)
{
  static GUID guidStdOle = {0x00020430,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46};
  ITypeLib*        ptlStdOle   = NULL;
  ITypeInfo*       ptinfoIDisp = NULL;
  ICreateTypeLib * pcreatetl   = NULL;
  ICreateTypeInfo* pctiCoClass = NULL;		// For creating the CoClass
  ICreateTypeInfo* pctiProps   = NULL;		// For creating the Primary (Property) Dispinterface
  FUNCDESC         funcdesc    = {0};
  TYPEDESC         tdescUser   = {0};
  ELEMDESC         edArg       = {0};
  HREFTYPE         hreftype;
  int              index;
  int              i;
  HRESULT          hr;

  if (g_ptinfoIntGame && g_ptinfoClsGame)
    return S_OK;

  // Create TypeLib
  CHECKSZ(CreateTypeLib(SYS_WIN32, L"c:\\SprdSubO.tlb" /* szFile */, &pcreatetl), "CreateTypeLib FAILED");

  // Misc. global props of the TypeLib
  CHECKSZ(pcreatetl->SetGuid(m_libidSubObj), "TL SetGuid FAILED");
  CHECKSZ(pcreatetl->SetVersion(1, 0), "TL SetVersion FAILED");
  CHECKSZ(pcreatetl->SetName(L"Sprds"), "TL SetName FAILED");
  CHECKSZ(pcreatetl->SetLcid(LOCALE_SYSTEM_DEFAULT), "TL SetLcid FAILED");

  // Get Information on IDispatch
  CHECKSZ(LoadRegTypeLib(guidStdOle, STDOLE_MAJORVERNUM, STDOLE_MINORVERNUM, STDOLE_LCID, &ptlStdOle), "LoadRegTypeLib FAILED");
  CHECKSZ(ptlStdOle->GetTypeInfoOfGuid(IID_IDispatch, &ptinfoIDisp), "GetTypeInfoOfGuid (IID_IDispatch) FAILED");

  // Create TypeInfo
  CHECKSZ(pcreatetl->CreateTypeInfo(L"GameSubObjs", TKIND_DISPATCH, &pctiProps), "Create TI FAILED");
  CHECKSZ(pctiProps->SetGuid(m_iidSubObj), "cti SetGuid FAILED");
  CHECKSZ(pctiProps->SetVersion(1, 0), "cti SetVersion FAILED");
  CHECKSZ(pctiProps->AddRefTypeInfo(ptinfoIDisp, &hreftype), "cti AddRefTypeInfoo FAILED"); 	// Reference StdOLE
  CHECKSZ(pctiProps->AddImplType(0, hreftype), "cti AddImplType FAILED");

  funcdesc.funckind = FUNC_DISPATCH;
  funcdesc.invkind  = INVOKE_PROPERTYGET;
  funcdesc.callconv = CC_STDCALL;
  funcdesc.cScodes  = -1;
  funcdesc.elemdescFunc.tdesc.vt = VT_PTR;
  funcdesc.elemdescFunc.tdesc.lptdesc = &tdescUser;
  tdescUser.vt = VT_USERDEFINED;

  // Loop through all of the SpriteClasses ($OBJECTs) in this game, adding a
  // property to pctiProps which corresponds to the control.
  index = 0;
  for (i=0; i<m_csubobj; i++)
    {
    // Need to make sure this starts out cleared
    if (!g_ptinfoClsSpriteClass)
      {
      CHECKCL(LoadTypeInfo(g_hinst, 0, 1, 0, 0x0409,
                           LIBID_SPRUUIDS, CLSID_SpriteClass, IID_ISpriteClass, FALSE,
                           &g_ptlMain, &g_ptinfoClsSpriteClass, &g_ptinfoIntSpriteClass));
      }
    CHECKCL(pctiProps->AddRefTypeInfo(g_ptinfoClsSpriteClass, &tdescUser.hreftype));
    funcdesc.memid = 0x80010000 | i;
    funcdesc.wFuncFlags = FUNCFLAG_FSOURCE;

    CHECKCL(pctiProps->AddFuncDesc(index, &funcdesc));
    CHECKCL(pctiProps->SetFuncAndParamNames(index, &m_rgpwszSubObjs[i], 1));

    index++;
    continue;

CheckLoop:
    // Do any clean up here

    CHECKSZ(hr,"BuildTypeInfo FAILED");
    break;
    }

  // Finish off the TI for the Props
  CHECKSZ(pctiProps->LayOut(), "BuildTypeInfo FAILED");
  CHECKSZ(pctiProps->QueryInterface(IID_ITypeInfo, (void **)&g_ptinfoIntGame), "BuildTypeInfo FAILED");

  // Now we have to create a coclass for the interface
  CHECKSZ(pcreatetl->CreateTypeInfo(L"Game", TKIND_COCLASS, &pctiCoClass), "BuildTypeInfo FAILED");
  CHECKSZ(pctiCoClass->SetGuid(m_clsidSubObj), "BuildTypeInfo FAILED");
  CHECKSZ(pctiCoClass->SetVersion(1, 0), "BuildTypeInfo FAILED");

  // Add the Page Property dispinterface to coclass
  CHECKSZ(pctiCoClass->AddRefTypeInfo(g_ptinfoIntGame, &hreftype), "BuildTypeInfo FAILED");
  CHECKSZ(pctiCoClass->AddImplType(0, hreftype), "BuildTypeInfo FAILED");
  CHECKSZ(pctiCoClass->SetImplTypeFlags(0, IMPLTYPEFLAG_FDEFAULT), "BuildTypeInfo FAILED");

  // Finish off the CoClass
  CHECKSZ(pctiCoClass->LayOut(), "BuildTypeInfo FAILED");
  CHECKSZ(pctiCoClass->QueryInterface(IID_ITypeInfo, (void **)&g_ptinfoClsGame), "BuildTypeInfo FAILED");

  // Finish off the Library
  CHECKSZ(pcreatetl->QueryInterface(IID_ITypeLib, (void **)&g_ptlGameSubObj), "BuildTypeLib FAILED");

CleanUp:
  // Code to release refs aquired during page build.
  if (pctiCoClass)
    pctiCoClass->Release();
  if (pctiProps)
    pctiProps->Release();
  if (ptinfoIDisp)
    ptinfoIDisp->Release();
  if (ptlStdOle)
    ptlStdOle->Release();
  if (pcreatetl)
    pcreatetl->Release();

  return hr;
};

//--- EOF -------------------------------------------------------------------
