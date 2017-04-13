//---------------------------------------------------------------------------
// Score.cpp
//---------------------------------------------------------------------------
// Score object to track score, # lives, level.
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
#include "Score.h"
#include "Spr.h"
#include "Game.h"
extern CGame *g_pgame;


//---------------------------------------------------------------------------
// DEBUG info
//---------------------------------------------------------------------------
SZTHISFILE


//---------------------------------------------------------------------------
// Initialize score stuff
//---------------------------------------------------------------------------
HRESULT CScore::s_hr = E_FAIL;

HRESULT CScore::CreateScore
(
  HINSTANCE hinst,          // Needed to load bitmaps
  HWND      hwnd,           // hwnd on which to draw the Score, Level, # Lives
  HWND      hwndPS,         // hwnd of PlaySurface
  HWND      hwndStat,       // hwnd of Status Bar
  long      scoreFirst1Up,  // Score to first new life
  long      scoreSecond1Up, // Score to 2nd new life
  long      dscoreNext1Up,  // Score to next new life
  int       cship,          // Number lives to start
  IDBMP     idbmpShip,      // Bitmap for display of # lives
  IDBMP     idbmpPlus,      // Bitmap for "+" when out of room for # lives
  CScore  **ppscoreOut      // Return value: new score object
)
{
  // Initialize output parameters
  *ppscoreOut = NULL;

  // Validate required args, etc.
  if (!idbmpShip || !hwnd)
    return E_INVALIDARG;

  *ppscoreOut = new CScore(hinst, hwnd, hwndPS, hwndStat, scoreFirst1Up, scoreSecond1Up, dscoreNext1Up, cship, idbmpShip, idbmpPlus);
  if (!ppscoreOut)
    return E_OUTOFMEMORY;
  if (s_hr)
    {
    delete *ppscoreOut;
    return s_hr;
    }

  return S_OK;
}


//---------------------------------------------------------------------------
// Initialize score stuff
//---------------------------------------------------------------------------
CScore::CScore
(
  HINSTANCE hinst,          // Needed to load bitmaps
  HWND      hwnd,           // hwnd on which to draw the Score, Level, # Lives
  HWND      hwndPS,         // hwnd of PlaySurface
  HWND      hwndStat,       // hwnd of Status Bar
  long      scoreFirst1Up,  // Score to first new life
  long      scoreSecond1Up, // Score to 2nd new life
  long      dscoreNext1Up,  // Score to next new life
  int       cshipStart,     // Number lives to start
  IDBMP     idbmpShip,      // Bitmap for display of # lives
  IDBMP     idbmpPlus       // Bitmap for "+" when out of room for # lives
)
{
  BITMAP bmp;
  RECT   rectStat;

  INIT_SIGNATURE(SIG_Score);

  // Assume success
  s_hr = S_OK;

  // Assume reasonable default values, if not supplied
  m_hinst          = hinst;
  m_hwnd           = hwnd;
  m_hwndStat       = hwndStat;
  m_hwndPS         = hwndPS;
  m_scoreFirst1Up  = scoreFirst1Up  ? scoreFirst1Up : 0x7fffffff;
  m_scoreSecond1Up = scoreSecond1Up ? scoreFirst1Up : 0x7fffffff;
  m_dscoreNext1Up  = dscoreNext1Up  ? dscoreNext1Up : 0x7fffffff;
  m_cshipStart     = cshipStart;

  // Init rest of class
  m_hbmpShip  = NULL;
  m_hbmpPlus  = NULL;
  m_cyMax     = 0;
  m_cxShip    = 0;
  m_cyShip    = 0;
  m_cxPlus    = 0;
  m_cyPlus    = 0;
  // m_scoreNext1Up = m_scoreFirst1Up;    // Handled by NewGame()
  // m_score        = 0;                  // Handled by NewGame()
  // m_cship        = m_cshipStart;       // Handled by NewGame()
  // m_lvl          = 0;                  // Handled by NewGame()
  // m_rectScore    = 0;                  // Handled below
  // m_rectShip     = 0;                  // Handled below
  // m_rectLvl      = 0;                  // Handled below

  // Finish initing the score object
  this->NewGame();
  ASSERT(m_scoreNext1Up == m_scoreFirst1Up, "NewGame() not initing all");
  ASSERT(!m_score, "NewGame() not initing all");
  ASSERT(m_cship == cshipStart, "NewGame() not initing all");
  ASSERT(!m_lvl, "NewGame() not initing all");

  // Load the bmp for the display of lives
  m_hbmpShip = LoadBitmap(hinst, MAKEINTRESOURCE(idbmpShip));
  if (!m_hbmpShip)
    {
    s_hr = E_FAIL;
    return;
    }
  GetObject(m_hbmpShip, sizeof(bmp), (HGDIOBJ)&bmp);
  m_cxPlus = m_cxShip = bmp.bmWidth;
  m_cyPlus = m_cyShip = m_cyMax = bmp.bmHeight;

  // Load the bmp of the "+" for the display of lives
  if (idbmpPlus)
    {
    m_hbmpPlus = LoadBitmap(hinst, MAKEINTRESOURCE(idbmpPlus));
    if (!m_hbmpPlus)
      {
      s_hr = E_FAIL;
      return;
      }
    GetObject(m_hbmpPlus, sizeof(bmp), (HGDIOBJ)&bmp);
    m_cxPlus = bmp.bmWidth;
    m_cyPlus = bmp.bmHeight;
    if (m_cyPlus > m_cyMax)
      m_cyMax = m_cyPlus;
    }

  // Calc height of Text.
  // HACK: Cheat and use DrawText() with a "|" instead of getting TextMetrics...
  rectStat.top = 0;
  DrawText(GetDC(hwnd), "|", 1, &rectStat, DT_NOCLIP|DT_NOPREFIX|DT_SINGLELINE|DT_CALCRECT);
  m_cyStat = rectStat.bottom;
  if (rectStat.bottom > m_cyMax)
    m_cyMax = rectStat.bottom;

  // Place PlaySurface correctly
  this->Size(372, 282);
}


//---------------------------------------------------------------------------
// Given the size of the PlaySurface, calculate the size of the Dlg & other
// components.
//---------------------------------------------------------------------------
void CScore::Size
(
  int cx,
  int cy
)
{
  RECT rect, rectCli;

#define cBRD  (6)
  GetWindowRect(m_hwnd, &rect);
  GetClientRect(m_hwnd, &rectCli);
  ClientToScreen(m_hwnd, (LPPOINT)&rectCli);
  ClientToScreen(m_hwnd, (LPPOINT)&rectCli.right);
  MoveWindow(m_hwnd,     rect.left,
                         rect.top,
                         cx + (2 * cBRD) + (rect.right - rect.left) - (rectCli.right - rectCli.left),
                         cy + (3 * cBRD + m_cyMax + m_cyStat) + (rect.bottom - rect.top) - (rectCli.bottom - rectCli.top),
                         TRUE);
  GetClientRect(m_hwnd, &rect);
  MoveWindow(m_hwndStat, cBRD,
                         rect.bottom - (m_cyStat + cBRD),
                         rect.right  - (2 * cBRD),
                         m_cyStat, TRUE);
  MoveWindow(m_hwndPS,   cBRD,
                         cBRD + m_cyMax,
                         rect.right  - (2 * cBRD),
                         rect.bottom - (3 * cBRD + m_cyMax + m_cyStat), TRUE);
  GetWindowRect(m_hwndPS, &rect);
  ScreenToClient(m_hwnd, (LPPOINT)&rect);
  ScreenToClient(m_hwnd, (LPPOINT)&rect.right);
  rect.top    = 1;
  rect.bottom = m_cyMax + 4;
  m_rectScore = rect;
  m_rectShip  = rect;
  m_rectLvl   = rect;
  m_rectShip.right = m_rectLvl.left   = rect.left +  (rect.right - rect.left) / 3;
  m_rectLvl.right  = m_rectScore.left = rect.left + ((rect.right - rect.left) / 3 * 2);
  GetClientRect(m_hwndPS, &rect);
  g_pgame->m_pdisp->m_cx = rect.right  - rect.left;
  g_pgame->m_pdisp->m_cy = rect.bottom - rect.top;
  InvalidateRect(m_hwnd,   NULL, TRUE);
  InvalidateRect(m_hwndPS, NULL, TRUE);
}


//---------------------------------------------------------------------------
// Terminate score stuff
//---------------------------------------------------------------------------
CScore::~CScore
(
  void
)
{
  CHECK_SIGNATURE(SIG_Score);

  if (m_hbmpShip)
    DeleteObject((HGDIOBJ)m_hbmpShip);
  if (m_hbmpPlus)
    DeleteObject((HGDIOBJ)m_hbmpPlus);

  DESTROY_SIGNATURE(SIG_Score);
}


//---------------------------------------------------------------------------
// Re-initialize score stuff for new game
//---------------------------------------------------------------------------
void CScore::NewGame
(
  void
)
{
  m_scoreNext1Up = m_scoreFirst1Up;
  m_score        = 0;
  m_cship        = m_cshipStart;
  m_lvl          = 0;

  InvalidateRect(m_hwnd, NULL, TRUE);
}


//---------------------------------------------------------------------------
// Paint score stuff: # 1Ups, current level, score
//---------------------------------------------------------------------------
void CScore::Paint
(
  HDC hdc
)
{
  char	 rgch[100];
  int	 x, y;
  int	 i;
  extern HDC     g_hdcMem;
  extern HBITMAP g_hbmpStock;

  SelectObject(g_hdcMem, m_hbmpShip);
  x = m_rectShip.left;
  y = m_rectShip.top + ((m_rectShip.bottom - m_rectShip.top - m_cyShip) >> 1);

  // Draw the 1Ups w/a "+", if necessary
  for (i=1; i<m_cship; i++)
    {
    BitBlt(hdc, x, y, m_cxShip, m_cyShip, g_hdcMem, 0, 0, SRCCOPY);
    x += m_cxShip + (m_cxShip >> 2);

    // If we only have more 1Ups, but only room for the "+", draw the "+"
    if (x + m_cxShip + m_cxPlus > m_rectShip.right && m_hbmpPlus && i+1<m_cship)
      {
      y = m_rectShip.top + ((m_rectShip.bottom - m_rectShip.top - m_cyPlus) >> 1);
      SelectObject(g_hdcMem, m_hbmpPlus);
      BitBlt(hdc, x, y, m_cxPlus, m_cyPlus, g_hdcMem, 0, 0, SRCCOPY);
      break;
      }
    }
  SelectObject(g_hdcMem, g_hbmpStock);

  SetBkMode(hdc, TRANSPARENT);
  wsprintf(rgch, "%ld", m_score);
  DrawText(hdc, rgch, -1, &m_rectScore, DT_RIGHT|DT_NOCLIP|DT_NOPREFIX|DT_SINGLELINE|DT_VCENTER);

  wsprintf(rgch, "%d", m_lvl);
  DrawText(hdc, rgch, -1, &m_rectLvl,   DT_CENTER|DT_NOCLIP|DT_NOPREFIX|DT_SINGLELINE|DT_VCENTER);
}


//---------------------------------------------------------------------------
// Change the score by the delta d.
//---------------------------------------------------------------------------
void CScore::Add
(
  long d      // Change the score by this amount (signed)
)
{
  m_score += d;
  if (m_score < 0)
    m_score = 0;
  if (m_score >= m_scoreNext1Up)
    {
    if (m_score > m_scoreSecond1Up)
      m_scoreNext1Up += m_dscoreNext1Up;
    else
      m_scoreNext1Up = m_scoreSecond1Up;
    m_cship++;
    InvalidateRect(m_hwnd, &m_rectShip, TRUE);
    g_pgame->m_pgameoa->FireNewShip();
    }

  InvalidateRect(m_hwnd, &m_rectScore, TRUE);
}


//---------------------------------------------------------------------------
// Called when pausing or unpausing
//---------------------------------------------------------------------------
void CScore::SetStatusText
(
  const char *pszText
)
{
  SetWindowText(m_hwndStat, pszText);
}

//--- EOF -------------------------------------------------------------------
