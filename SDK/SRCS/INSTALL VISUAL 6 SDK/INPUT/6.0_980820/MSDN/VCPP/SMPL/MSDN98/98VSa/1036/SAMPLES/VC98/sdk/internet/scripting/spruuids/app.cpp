//---------------------------------------------------------------------------
// App.cpp
//---------------------------------------------------------------------------
// Shell for sample spr program
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
#include "App.h"
#include "MsgLoop.h"
#include "Game.h"
#include <stdio.h>


//---------------------------------------------------------------------------
// DEBUG info
//---------------------------------------------------------------------------
SZTHISFILE


//---------------------------------------------------------------------------
// Prototypes
//---------------------------------------------------------------------------
BOOL CALLBACK AppDlgProc(  HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);
LONG CALLBACK PSWndProc(   HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);


//---------------------------------------------------------------------------
// Global Variables
//---------------------------------------------------------------------------
HINSTANCE g_hinst             = NULL;
ITypeLib *g_ptlMain           = NULL;   // Cache of TypeLib
CApp     *g_papp              = NULL;
IUnknown *g_punkApplicationNA = NULL;   // Not AddRef()'d
char     *g_pszCodeFile       = NULL;
char     *g_pszRecFile        = NULL;
FILE     *g_pfileRec          = NULL;
int       g_mode              = MODE_NORMAL;
CMGRRINFO App_crinfo =
  {
  sizeof(CMGRRINFO),      // size of CMGRRINFO structure in bytes.
  0,                      // Don't need idle time
  cmgrrfPreTranslateAll,  // Need pretranslate
  cmgradvfModal           // Need modal notifications
  };
HRESULT CApp::s_hr = E_FAIL;


//---------------------------------------------------------------------------
// Helpers for little vs. bit endian
//---------------------------------------------------------------------------

#undef BIGENDIAN // change for big-endian systems

typedef union
  {
  DWORD i4;
  struct
    {
    char b1;
    char b2;
    char b3;
    char b4;
    };
  } I4_SW;

#ifndef BIGENDIAN
  #define NORMALIZE_I4(i4)  (i4)
#else
  #define NORMALIZE_I4(i4) \
    {                      \
    I4_SW l=i4;            \
    (i4).b1 = l.b4;        \
    (i4).b2 = l.b3;        \
    (i4).b3 = l.b2;        \
    (i4).b4 = l.b1;        \
    }
#endif

typedef struct
  {
  char   win;
  char   msg;
  I4_SW  wp;
  I4_SW  lp;
  } REC;


//---------------------------------------------------------------------------
// Write out one message.
//---------------------------------------------------------------------------
#define RECORD(win, msg, wp, lp)    {if (g_mode == MODE_RECORD) Record(win,msg,wp,lp);}
#define WIN_DLG   ((char)0xdd)  // Dlg
#define WIN_PS    ((char)0xee)  // playsurfacE
#define WIN_ABOUT ((char)0xaa)  // About
  
void Record
(
  char   win,
  UINT   msg,
  WPARAM wp,
  LPARAM lp
)
{
  REC rec;

  if (!g_pfileRec)
    {
    g_pfileRec = fopen(g_pszRecFile, "wb");
    if (!g_pfileRec)
      {
      MessageBox(NULL, "Could not open record file", "Spruuids", MB_OK | MB_ICONEXCLAMATION);
      exit(1);
      }
    }

  switch (msg)
    {
    default:
      return;

    case WM_COMMAND:
      msg = 1;
      break;
    case WM_SYSCOMMAND:
      msg = 2;
      break;
    case WM_TIMER:
      msg = 3;
      break;
    case WM_CHAR:
      msg = 4;
      break;
    case WM_KEYDOWN:
      msg = 5;
      break;
    case WM_KEYUP:
      msg = 6;
      break;
    case WM_MOUSEMOVE:
      msg = 7;
      break;
    case WM_LBUTTONUP:
      msg = 8;
      break;
    case WM_RBUTTONUP:
      msg = 9;
      break;
    case WM_MBUTTONUP:
      msg = 10;
      break;
    case WM_LBUTTONDOWN:
      msg = 11;
      break;
    case WM_RBUTTONDOWN:
      msg = 12;
      break;
    case WM_MBUTTONDOWN:
      msg = 13;
      break;
    }

  rec.win = win;
  rec.msg = (char)msg;
  rec.wp.i4 = wp;
  NORMALIZE_I4(rec.wp);    // Handle byte-swapping for little vs. big endian.
  rec.lp.i4 = lp;
  NORMALIZE_I4(rec.lp);    // Handle byte-swapping for little vs. big endian.
  fwrite(&rec, sizeof(rec), 1, g_pfileRec);
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
HRESULT CApp::Playback
(
  void
)
{
  REC    rec;
  HWND   hwnd;
  UINT   msg;

  if (!g_pfileRec)
    {
    g_pfileRec = fopen(g_pszRecFile, "rb");
    if (!g_pfileRec)
      {
      MessageBox(NULL, "Could not open playback file", "Spruuids", MB_OK | MB_ICONEXCLAMATION);
      return E_FAIL;
      }
    }

  while (TRUE)
    {
    size_t cch = fread(&rec, sizeof(rec), 1, g_pfileRec);
    if (cch != 1)
      {
      if (feof(g_pfileRec))
        {
        fclose(g_pfileRec);
        g_pfileRec = NULL;
        g_mode = MODE_NORMAL;
        m_fQuit = TRUE;
        return S_OK;
        }
      MessageBox(NULL, "Unexpected read error in playback file", "Spruuids", MB_OK | MB_ICONEXCLAMATION);
      return E_FAIL;
      }

    switch (rec.win)
      {
      case WIN_DLG:
        hwnd = m_hwndDlg;
        break;

      case WIN_PS:
        hwnd = m_hwndPS;
        break;

      case WIN_ABOUT:
        hwnd = m_hwndAbout;
        break;
      }

    UINT mpimsg[] = {0, WM_COMMAND, WM_SYSCOMMAND, WM_TIMER, WM_CHAR, WM_KEYDOWN, WM_KEYUP,
                        WM_MOUSEMOVE, WM_LBUTTONUP, WM_RBUTTONUP, WM_MBUTTONUP, WM_LBUTTONDOWN,
                        WM_RBUTTONDOWN, WM_MBUTTONDOWN};
    if (rec.msg <= 0 || rec.msg >= sizeof(mpimsg)/sizeof(mpimsg[0]))
      {
      MessageBox(NULL, "Bad msg # in playback file", "Spruuids", MB_OK | MB_ICONEXCLAMATION);
      return E_FAIL;
      }
    msg = mpimsg[rec.msg];
    NORMALIZE_I4(rec.wp);    // Handle byte-swapping for little vs. big endian.
    NORMALIZE_I4(rec.lp);    // Handle byte-swapping for little vs. big endian.

    SendMessage(hwnd, msg, (WPARAM)rec.wp.i4, (LPARAM)rec.lp.i4);
    if (!m_pmsgloop->FPushMessageLoop(g_papp->m_idcomp, cmgrloopDoEvents, NULL))
      return E_FAIL;
    }

  return S_OK;
}


//---------------------------------------------------------------------------
// Helper to parse command-line parameters
//---------------------------------------------------------------------------
HRESULT ParseCmdLine
(
  char *pszCmdLine
)
{
  if (!pszCmdLine)
    goto DoError;

  if (pszCmdLine[0] == '/')
    {
    if (pszCmdLine[1] == 'P')
      {
      g_mode = MODE_PLAYBACK;
      goto GetFile;
      }
    else if (pszCmdLine[1] == 'R')
      {
      g_mode = MODE_RECORD;
GetFile:
      if (pszCmdLine[2] <= ' ')
        goto DoError;
      pszCmdLine += 2;
      g_pszRecFile = pszCmdLine;
      while (*pszCmdLine > ' ')   // Skip non-white space
        pszCmdLine++;
      if (!*pszCmdLine)   // End Of String
        goto DoError;     // Needed <fileCode>
      *pszCmdLine = 0;
      pszCmdLine++;
      srand(1);           // Seed random # generator
      }
    else
      goto DoError;
    }

  // Skip white space
  while (*pszCmdLine && *pszCmdLine <= ' ')
    pszCmdLine++;
  if (!*pszCmdLine)
    {
DoError:
    MessageBox(NULL, "Usage: Spruuids [/P<filePlay> | /R<fileRec>] <fileCode>, where <fileCode> is a VB Script", "Spruuids", MB_OK | MB_ICONEXCLAMATION);
    return E_FAIL;
    }

  // Rest of Cmd Line should be source file
  g_pszCodeFile = pszCmdLine;
  return S_OK;
}


//---------------------------------------------------------------------------
// Main program
//---------------------------------------------------------------------------
int WINAPI WinMain
(
  HINSTANCE hinst,        // Instance handle of current instance
  HINSTANCE hinstPrev,    // Instance handle of previous instance
  LPSTR     lpszCmdLine,  // Null-terminated command line
  int	    iCmdShow      // How window should be initially displayed
)
{
  int     ret   = 1;      // Assume non-normal exit
  BOOL    fInit = FALSE;
  HRESULT hr;

  // Stuff hinst in global for all to see
  g_hinst      = hinst;
  hr = ParseCmdLine(lpszCmdLine);
  if (hr)
    goto CleanUp;

  // Initialize OLE
  hr = CoInitialize(NULL);
  if (hr)
    goto CleanUp;
  fInit = TRUE;

  // Create the CApp object, since it runs the show, note it inits g_papp
  hr = CApp::CreateApp(hinst);
  if (hr)
    goto CleanUp;
  ASSERT(g_papp, "!hr but g_papp==NULL");

  // Start a new game
  g_papp->CausePause(0);
  AppEvt_NewGame();

  // Either Playback or push the main msg loop
  if (g_mode == MODE_PLAYBACK)
    hr = g_papp->Playback();
  else
    hr = g_papp->MainMsgLoop();
  if (hr)
    goto CleanUp;

  // Normal exit
  ret = 0;

  // Cleanup, if we haven't already done so
CleanUp:
  if (g_pfileRec)
    {
    fclose(g_pfileRec);
    g_pfileRec = NULL;
    }
  if (g_papp)
    delete g_papp;
  if (fInit)
    CoUninitialize();
  return ret;
}


//***************************************************************************
// Constructor and Destructor support for CApp
//***************************************************************************

//---------------------------------------------------------------------------
// Creates an instance of CApp.  Use this instead of "new", as this returns
// errors, etc.
//---------------------------------------------------------------------------
HRESULT CApp::CreateApp
(
  HINSTANCE hinst
)
{
  if (g_papp)
    return E_UNEXPECTED;

  CApp *papp = new CApp(hinst);
  if (!papp)
    return E_OUTOFMEMORY;
  if (papp->s_hr)
    return papp->s_hr;

  return S_OK;
}


//---------------------------------------------------------------------------
// Constructor
//---------------------------------------------------------------------------
CApp::CApp
(
  HINSTANCE hinst
)
{
  WNDCLASS cls;
  RECT     rect;
  int      cx, cy;

  INIT_SIGNATURE(SIG_App);

  // Init globals
  g_papp              = this;
  g_punkApplicationNA = this->GetUnknown(); // GetUnknown() doesn't AddRef, but we don't want to anyway.
  s_hr                = E_FAIL;             // Assume failure

  // Init members
  m_pmsgloop        = NULL;
  m_pgame           = NULL;
  m_hwndDlg         = NULL;
  m_hwndPS          = NULL;
  m_hwndStat        = NULL;
  m_hwndAbout       = NULL;
  m_hinst           = hinst;
  m_idcomp          = 0xffffffff;
  m_fRegisteredComp = FALSE;
  m_cmodal          = 0;
  m_fQuit           = FALSE;
  m_cref            = 1;
  m_ptinfoCls       = NULL;
  m_ptinfoInt       = NULL;
  m_pdispBaseObject = NULL;

  // Add new class for dialog which is our application:
  cls.style         = 0;
  cls.lpfnWndProc   = DefDlgProc;
  cls.cbClsExtra    = 0;
  cls.cbWndExtra    = 0;
  cls.hInstance     = hinst;
  cls.hIcon         = LoadIcon(hinst, MAKEINTRESOURCE(ID_ICO_APP));
  cls.hCursor       = NULL;
  cls.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
  cls.lpszMenuName  = NULL;
  cls.lpszClassName = "DlgClass";
  if (!RegisterClass(&cls))
    return;

  // Add new class for play surface:
  cls.style         = CS_OWNDC;
  cls.lpfnWndProc   = PSWndProc;
  cls.cbClsExtra    = 0;
  cls.cbWndExtra    = 0;
  cls.hInstance     = hinst;
  cls.hIcon         = NULL;
  cls.hCursor       = LoadCursor(hinst, MAKEINTRESOURCE(ID_CUR_PLAYSURF));
  cls.hbrBackground = NULL;
  cls.lpszMenuName  = NULL;
  cls.lpszClassName = "PlaySurface";
  if (!RegisterClass(&cls))
    return;

  // Now that we've registerd the window classes, create the main window
  m_hwndDlg = CreateDialog(hinst, MAKEINTRESOURCE(ID_DLG_APP), NULL, AppDlgProc);
  if (!m_hwndDlg)
    {
    s_hr = E_OUTOFMEMORY;
    return;
    }

  // Center Dialog:
  GetWindowRect(m_hwndDlg, &rect);
  rect.right  -= rect.left;
  rect.bottom -= rect.top;
  cx = GetSystemMetrics(SM_CXSCREEN);
  cy = GetSystemMetrics(SM_CYSCREEN);
  MoveWindow(m_hwndDlg, (cx - rect.right) >> 1, (cy - rect.bottom) >> 1, rect.right, rect.bottom, TRUE);

  // Create the Component Manager
  m_pmsgloop = new CMsgLoop(m_hwndDlg);
  if (!m_pmsgloop)
    {
    s_hr = E_OUTOFMEMORY;
    return;
    }

  m_fRegisteredComp = m_pmsgloop->FRegisterComponent(this, &App_crinfo, &m_idcomp);
  if (!m_fRegisteredComp)
    return;

  HRESULT hr = this->LoadGame();
  if (hr)
    {
    s_hr = hr;
    return;
    }

  // Success
  s_hr = S_OK;
  ShowWindow(m_hwndDlg, SW_NORMAL);
  return;
}


//---------------------------------------------------------------------------
// Destructor
//---------------------------------------------------------------------------
CApp::~CApp
(
  void
)
{
  CHECK_SIGNATURE(SIG_App);

  g_papp = NULL;
  g_punkApplicationNA = NULL;   // Wasn't AddRef()'d, so don't Release().

  if (m_hwndDlg)
    {
    ShowWindow(m_hwndDlg, SW_HIDE);
    ReleaseCapture();
    DestroyWindow(m_hwndDlg);
    m_hwndDlg = NULL;
    }

  if (m_pgame)
    {
    delete m_pgame;
    m_pgame = NULL;
    }

  if (m_fRegisteredComp)
    {
    ASSERT(m_pmsgloop, "m_idcomp, but !m_pmsgloop");
    BOOL f = m_pmsgloop->FRevokeComponent(m_idcomp);
    ASSERT(!f, "!f");
    m_fRegisteredComp = FALSE;
    }

  if (m_pmsgloop)
    {
    m_pmsgloop->Release();
    m_pmsgloop = NULL;
    }

  // Free dynamically created TypeInfo / TypeLib stuff
  if (g_ptinfoClsGame)
    g_ptinfoClsGame->Release();
  if (g_ptinfoIntGame)
    g_ptinfoIntGame->Release();

  if (g_ptlGameSubObj)
    g_ptlGameSubObj->Release();

  // Free TypeInfo / TypeLib loaded from our resources
  if (g_ptinfoClsGameOA)
    g_ptinfoClsGameOA->Release();
  if (g_ptinfoIntGameOA)
    g_ptinfoIntGameOA->Release();

  if (g_ptinfoClsSpriteClass)
    g_ptinfoClsSpriteClass->Release();
  if (g_ptinfoIntSpriteClass)
    g_ptinfoIntSpriteClass->Release();

  if (g_ptinfoClsSprite)
    g_ptinfoClsSprite->Release();
  if (g_ptinfoIntSprite)
    g_ptinfoIntSprite->Release();

  if (m_ptinfoCls)
    m_ptinfoCls->Release();
  if (m_ptinfoInt)
    m_ptinfoInt->Release();

  if (g_ptlMain)
    g_ptlMain->Release();

  DESTROY_SIGNATURE(SIG_App);
}


//***************************************************************************
// General methods
//***************************************************************************

//---------------------------------------------------------------------------
// Enter main message loop for application
//---------------------------------------------------------------------------
HRESULT CApp::MainMsgLoop
(
  void
)
{
  if (!m_pmsgloop->FPushMessageLoop(g_papp->m_idcomp, cmgrloopDoEvents, NULL))
    return E_FAIL;

  return S_OK;
}


//---------------------------------------------------------------------------
// Load a game from the given file.
//---------------------------------------------------------------------------
HRESULT CApp::LoadGame
(
  void
)
{
  if (m_pgame)
    return E_UNEXPECTED;

  return CGame::CreateGame(g_hinst, m_hwndDlg, m_hwndPS, m_hwndStat, m_pmsgloop, &m_pgame);
}

  
//---------------------------------------------------------------------------
// Get rid of an existing game, if present.
//---------------------------------------------------------------------------
void CApp::CloseGame
(
  void
)
{
  if (m_pgame)
    {
    m_pgame->Close();
    m_pgame->Release();
    m_pgame = NULL;
    }
}

  
//---------------------------------------------------------------------------
// Called when pausing or unpausing
//---------------------------------------------------------------------------
void CApp::CausePause
(
  int p   // -1=Toggle, 0=UnPause, 1=Pause
)
{
  // Invoke game.cpp's Pause event.  Returns whether or not app is paused
  p = AppEvt_Pause(p);
}


//***************************************************************************
// DlgProcs, WndProcs
//***************************************************************************

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
BOOL CALLBACK AppDlgProc
(
  HWND   hwnd,
  UINT   msg,
  WPARAM wp,
  LPARAM lp
)
{
  switch (msg)
    {
    case WM_INITDIALOG:
      {
      g_papp->m_hwndDlg  = hwnd;
      g_papp->m_hwndPS   = GetDlgItem(hwnd, ID_CTL_PLAYSURF);
      g_papp->m_hwndStat = GetDlgItem(hwnd, ID_CTL_STATUS);
      break;
      }

    case WM_ACTIVATE:
      if (LOWORD(wp) != WA_INACTIVE)
        {
        g_papp->m_pmsgloop->OnComponentActivate(g_papp->m_idcomp);
        SetFocus(g_papp->m_hwndPS);
        return TRUE;
        }
      break;

    case WM_SETFOCUS:
      SetFocus(g_papp->m_hwndPS);
      return TRUE;

    case WM_QUERYDRAGICON:
      return (BOOL)LoadIcon(g_papp->m_hinst, MAKEINTRESOURCE(ID_ICO_APP));

    case WM_PAINT:
      {
      HDC hdc;
      PAINTSTRUCT ps;

      if (!IsIconic(hwnd))
        return FALSE;
      hdc = wp ? (HDC)wp : BeginPaint(hwnd, &ps);
      DrawIcon(hdc, 0, 0, LoadIcon(g_papp->m_hinst, MAKEINTRESOURCE(ID_ICO_APP)));
      if (!wp)
        EndPaint(hwnd, &ps);
      return TRUE;
      }

    case WM_ERASEBKGND:
      {
      if (IsIconic(hwnd))
        {
        DefWindowProc(hwnd, msg, wp, lp);
        return TRUE;
        }

      // Draw fancy boarders
      RECT rect;

      GetClientRect(hwnd, &rect);
      DrawEdge((HDC)wp, &rect, 0, BF_RECT | BF_MIDDLE);

      GetWindowRect(g_papp->m_hwndPS, &rect);
      ScreenToClient(hwnd, (LPPOINT)&rect);
      ScreenToClient(hwnd, (LPPOINT)&rect.right);
      InflateRect(&rect, 2, 2);
      DrawEdge((HDC)wp, &rect, EDGE_SUNKEN, BF_RECT);

      GetWindowRect(g_papp->m_hwndStat, &rect);
      InflateRect(&rect, 2, 2);
      ScreenToClient(hwnd, (LPPOINT)&rect);
      ScreenToClient(hwnd, (LPPOINT)&rect.right);
      DrawEdge((HDC)wp, &rect, BDR_SUNKENOUTER, BF_RECT);
      break;
      }

    case WM_SYSCOMMAND:
      RECORD(WIN_DLG, msg, wp, lp);
      switch (wp & 0xfff0)
        {
        case SC_CLOSE:
          if (g_papp->FQueryTerminate(TRUE))
            g_papp->m_fQuit = TRUE;
          break;
        }
      return FALSE;

    case WM_SIZE:
      if (IsIconic(hwnd))
        g_papp->CausePause(TRUE);
      break;

    case WM_COMMAND:
      RECORD(WIN_DLG, msg, wp, lp);
      if (!LOWORD(lp) || HIWORD(lp) == 1)
        switch (wp)
          {
          case ID_MENU_NEWGAME:
            g_papp->CausePause(1);
            if (!g_papp->m_pgame->m_fGameOver && g_mode != MODE_PLAYBACK)
              {
              int ret;
              g_papp->m_pmsgloop->OnComponentEnterState(g_papp->m_idcomp, cmgrstateModal, cmgrcontextAll, 0, NULL, NULL);
              ret = MessageBox(g_papp->m_hwndDlg, "Do you really want to start a new game?", "Spruuids", MB_YESNO | MB_ICONQUESTION);
              g_papp->m_pmsgloop->FOnComponentExitState(g_papp->m_idcomp, cmgrstateModal, cmgrcontextAll, 0, NULL);
              SetFocus(g_papp->m_hwndPS);
              if (ret == IDYES)
                goto NewGame;
              }
            else
              {
NewGame:      g_papp->CausePause(0);
              AppEvt_NewGame();
              }
            return TRUE;

          case ID_MENU_EDIT:
            {
            char sz[255];
            // Shell notepad to edit file we loaded.
            g_papp->CausePause(1);
            wsprintf(sz, "Notepad.exe %s", g_pszCodeFile);
            WinExec(sz, SW_SHOWNORMAL);
            return TRUE;
            }

          case ID_MENU_RELOAD:
            g_papp->CausePause(1);
            if (g_papp->m_pgame && !g_papp->m_pgame->m_fGameOver)
              {
              int ret;
              g_papp->m_pmsgloop->OnComponentEnterState(g_papp->m_idcomp, cmgrstateModal, cmgrcontextAll, 0, NULL, NULL);
              ret = MessageBox(g_papp->m_hwndDlg, "Do you really want to start a new game?", "Spruuids", MB_YESNO | MB_ICONQUESTION);
              g_papp->m_pmsgloop->FOnComponentExitState(g_papp->m_idcomp, cmgrstateModal, cmgrcontextAll, 0, NULL);
              SetFocus(g_papp->m_hwndPS);
              if (ret == IDYES)
                goto OpenGame;
              }
            else
              {
OpenGame:     g_papp->CloseGame();
              g_papp->LoadGame();
              g_papp->CausePause(0);
              AppEvt_NewGame();    // Start a new game
              }
            return TRUE;

          case ID_MENU_EXIT:
            if (g_papp->FQueryTerminate(TRUE))
              g_papp->m_fQuit = TRUE;
            return TRUE;

          case ID_MENU_PAUSE:
            g_papp->CausePause(-1);
            break;

          case ID_MENU_ABOUT:
            g_papp->CausePause(1);
            g_papp->m_pmsgloop->OnComponentEnterState(g_papp->m_idcomp, cmgrstateModal, cmgrcontextAll, 0, NULL, NULL);
            DialogBox(g_papp->m_hinst, MAKEINTRESOURCE(ID_DLG_ABOUT), g_papp->m_hwndDlg, AboutDlgProc);
            g_papp->m_pmsgloop->FOnComponentExitState(g_papp->m_idcomp, cmgrstateModal, cmgrcontextAll, 0, NULL);
            SetFocus(g_papp->m_hwndPS);
            return TRUE;

          case ID_MENU_HIGHSCORES:
          case ID_MENU_HELPINDEX:
          case ID_MENU_HELPPLAY:
          case ID_MENU_HELPCOMMANDS:
          case ID_MENU_HELPHELP:
            return TRUE;
          }
      break;
    }

  return AppEvt_DlgProc(hwnd, msg, wp, lp);
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
BOOL CALLBACK AboutDlgProc
(
  HWND   hwnd,
  UINT   msg,
  WPARAM wp,
  LPARAM lp
)
{
  switch (msg)
    {
    case WM_INITDIALOG:
      {
      RECT rect;
      RECT rect2;

      g_papp->m_hwndAbout = hwnd;
      GetWindowRect(g_papp->m_hwndDlg, &rect);
      GetWindowRect(hwnd, &rect2);
      MoveWindow(hwnd, (rect.right+rect.left)/2-(rect2.right-rect2.left)/2,
                       (rect.bottom+rect.top)/2-(rect2.bottom-rect2.top)/2,
                       rect2.right-rect2.left,
                       rect2.bottom-rect2.top,
                       TRUE);
      return TRUE;
      }

    case WM_COMMAND:
      RECORD(WIN_ABOUT, msg, wp, lp);
      g_papp->m_hwndAbout = NULL;
      EndDialog(hwnd, TRUE);
      return TRUE;
    }
  return FALSE;
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
LRESULT CALLBACK PSWndProc
(
  HWND   hwnd,
  UINT   msg,
  WPARAM wp,
  LPARAM lp
)
{
  switch (msg)
    {
    case WM_TIMER:
    case WM_CHAR:
    case WM_KEYUP:
    case WM_MOUSEMOVE:
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
      RECORD(WIN_PS, msg, wp, lp);
      break;


    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
      RECORD(WIN_PS, msg, wp, lp);
      SetFocus(hwnd);
      break;

    case WM_GETDLGCODE:
      return DLGC_WANTALLKEYS | DLGC_WANTARROWS | DLGC_WANTCHARS | DLGC_WANTMESSAGE | DLGC_WANTTAB;

    case WM_KEYDOWN:
      RECORD(WIN_PS, msg, wp, lp);
      switch (wp)
        {
        case VK_ESCAPE:
          ShowWindow(g_papp->m_hwndDlg, SW_MINIMIZE);
          break;

        case VK_F1:
          SendMessage(g_papp->m_hwndDlg, WM_COMMAND, ID_MENU_HELPINDEX, 0L);
          break;

        case VK_F2:
          SendMessage(g_papp->m_hwndDlg, WM_COMMAND, ID_MENU_NEWGAME, 0L);
          break;

        case VK_PAUSE:
        case VK_F3:
          SendMessage(g_papp->m_hwndDlg, WM_COMMAND, ID_MENU_PAUSE, 0L);
          break;

        case VK_F5:
          SendMessage(g_papp->m_hwndDlg, WM_COMMAND, ID_MENU_RELOAD, 0L);
          break;

        case VK_F9:
          SendMessage(g_papp->m_hwndDlg, WM_COMMAND, ID_MENU_EDIT, 0L);
          break;
        }
      break;
    }

  return AppEvt_PSWndProc(hwnd, msg, wp, lp);
}


//***************************************************************************
// IUnknown Interface
//***************************************************************************

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP CApp::QueryInterface
(
  REFIID iid,
  void **ppvObjOut
)
{
  if (!ppvObjOut)
    return E_INVALIDARG;

  *ppvObjOut = NULL;

  if (iid == IID_IUnknown)
    *ppvObjOut = this->GetUnknown();
  else if (iid == IID_IDispatch)
    *ppvObjOut = this->GetDispatch();
  else if (iid == IID_ISpruuidsApp)
    *ppvObjOut = (ISpruuidsApp *)this;
  else if (iid == IID_IOleComponent)
    *ppvObjOut = (IOleComponent *)this;

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
STDMETHODIMP_(ULONG) CApp::AddRef
(
  void
)
{
  ASSERT(m_cref, "bad m_cref");
  return ++m_cref;
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CApp::Release
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
// IOleComponent Interface
//***************************************************************************

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(BOOL) CApp::FPreTranslateMessage
(
  MSG *pmsg
)
{
  return IsDialogMessage(m_hwndDlg, pmsg);
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(void) CApp::OnEnterState
(
  ULONG state,
  BOOL  fEnter
)
{
  // TODO: We only care about Modal notifications.  You application will likely
  // TODO: need to support some of the others.

  if (state == cmgrstateModal)
    {
    if (fEnter)
      {
      if (!m_cmodal)
        {
        this->CausePause(1);              // Pause for the user, since we're modal
        EnableWindow(m_hwndDlg, FALSE);   // Entering modal state, so disable window
        }
      m_cmodal++;
      }
    else if (m_cmodal)    // Don't decrement if zero!
      {
      m_cmodal--;
      if (!m_cmodal)
        EnableWindow(m_hwndDlg, TRUE);   // Leaving modal state, so re-enable window
      }
    }
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(void) CApp::OnAppActivate
(
  BOOL  fActive,
  DWORD dwOtherThreadID
)
{
  // TODO: If you have floating palettes, etc., show them here.
  SetFocus(m_hwndPS);
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(void) CApp::OnLoseActivation
(
  void
)
{
  // TODO: If you have floating palettes, etc., hide them here.
  this->CausePause(1);
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(BOOL) CApp::FDoIdle
(
  DWORD grfidlef
)
{
  // TODO: If you have need idle-time processing, do so here
  return FALSE;
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(BOOL) CApp::FContinueMessageLoop
(
  ULONG uReason,
  void *pvLoopData
)
{
  MSG msg;

  // If we're playing back a recording, return from msg loop once there are
  // no more msgs.
  if (g_mode == MODE_PLAYBACK && !PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE))
    return FALSE;

  // Since the only time we push a message loop is for the Main message loop,
  // we don't want that one popped until we decide to exit the application.
  return !m_fQuit;
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(BOOL) CApp::FQueryTerminate
(
  BOOL fPromptUser
)
{
  // Disallow termination if modal dlg is up
  if (m_cmodal)
    {
    if (fPromptUser)
      MessageBox(NULL, "Please terminate Dlg before exiting", "Spruuids",
                 MB_TASKMODAL | MB_ICONEXCLAMATION | MB_OK);
    return FALSE;
    }

  return AppEvt_FQueryTerminate(fPromptUser);
}


//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
STDMETHODIMP_(void) CApp::Terminate
(
  void
)
{
  // Unregister component & release all refs on Component Manager
  if (m_fRegisteredComp)
    {
    ASSERT(m_pmsgloop, "m_idcomp, but !m_pmsgloop");
    BOOL f = m_pmsgloop->FRevokeComponent(m_idcomp);
    ASSERT(!f, "!f");
    m_fRegisteredComp = FALSE;
    }

  if (m_pmsgloop)
    {
    m_pmsgloop->Release();
    m_pmsgloop = NULL;
    }

  m_fQuit = TRUE;
}


//***************************************************************************
// IDispatch Interface
//***************************************************************************

//---------------------------------------------------------------------------
// Method needed by COleAuto, so it can implement IDispatch for us.
//---------------------------------------------------------------------------
HRESULT CApp::GetTypeLibInfo
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
  *ppclsidOut = &CLSID_SpruuidsApp;
  *ppiidOut   = &IID_ISpruuidsApp;
  *ppptlOut   = &g_ptlMain;
  return S_OK;
}


//***************************************************************************
// SpruuidsApp Interface
//***************************************************************************

//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CApp::get_Application
(
  ISpruuidsApp** lppaReturn
)
{
  return this->QueryInterface(IID_ISpruuidsApp, (void **)lppaReturn);
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CApp::get_Parent
(
  ISpruuidsApp** lppaReturn
)
{
  return this->QueryInterface(IID_ISpruuidsApp, (void **)lppaReturn);
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CApp::Quit
(
  void 
)
{
  m_fQuit = TRUE;

  return S_OK;
}


//---------------------------------------------------------------------------
// 
//---------------------------------------------------------------------------
STDMETHODIMP CApp::get_Game
(
  IGame** lppaReturn
)
{
  return m_pgame->QueryInterface(IID_IGame, (void **)lppaReturn);
}

  
//--- EOF -------------------------------------------------------------------
