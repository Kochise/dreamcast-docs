/* --------------------------------------------------------------------------

Basic Forms example of a custom sendable form.  It is an EXE server
rather than a DLL.  It implements the minimum form interface required
to launch and send a form.

Copyright (C) 1995 Microsoft Corporation

-------------------------------------------------------------------------- */

#define WINDOWS

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include <malloc.h>
#include <memory.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <search.h>

#ifdef _WIN32
#include <winver.h>
#else
#include <ver.h>
#endif

//$FORM

//---[ Form specific includes ]--------------------------------------------

#include <ole2.h>
#include <mapiform.h>
#include <mapix.h>
#include <mapiutil.h>

//$FORM

//---[ Various platform defines ]------------------------------------------

#ifndef APIENTRY                // Windows NT defines APIENTRY,
#define APIENTRY far pascal             // but 3.x doesn't.
#endif

#ifndef _WIN32                   // Windows 3.x uses a FARPROC
#define DLGPROC FARPROC                 // for dialogs
#endif

unsigned int _charmax;

#ifdef _WIN32
#define MoveTo(_1, _2, _3) MoveToEx(_1,_2,_3,NULL)
#endif

//---[ Define Debug Trace Tags ]-------------------------------------------

#include "dbugit.h"

#ifdef DEBUG
ASSERTDATA
#endif

//---[ Local header dependencies ]-----------------------------------------

#include "check.h"
#include "dlg.h"
#include "wcheck.h"
#include "checkdta.h"
#include "movelist.h"
#include "form.h" //$FORM

//---[ Globally Accessible Config Info ]-----------------------------------

struct  rCheckConfigRec rConfig;                // Config struct
struct  rGameStateRec rGameState;               // Game state
class   CMoveList CMoves;                               // Move list
SQUARE  b[SQRS_MAX];                                    // Board structure

static  POINT       pntStart;                   // For buttonup/down processing.

char szAppName[] = APP_NAME;                    // The name of this application

#ifdef DEBUG
char szTitle[]   = "Checkers (debug)";
#else
#ifdef TEST
char szTitle[]   = "Checkers (test)";
#else
char szTitle[]   = "Checkers";
#endif
#endif

//---[ Globally Accessible Handles ]---------------------------------------

HINSTANCE       hInst;          // current instance handle

HWND    hMainWnd        = NULL;         // Main window handle
HWND    hClientWnd      = NULL;         // Client window handle
HBRUSH  hbrBlack;                       
HBRUSH  hbrWhite;                       
HBRUSH  hbrRed;                         
HBRUSH  hbrBckgrnd;                     
HBRUSH  hbrBlue;                        
HBRUSH  hbrHuman;                       
HBRUSH  hbrComputer;            
HBRUSH  hbrDkgrey;                      
HPEN    hpenDkgrey;                     
HBITMAP hBtmaps;                        // Piece bitmaps

HCURSOR curNormal;                      // Standard cursor
HCURSOR curThink;                       // Computer is thinking cursor
HCURSOR curPiece;                       // Piece cursor (move in progress)
HCURSOR curResize;                      // Resize cursor

#define SQR_XSIZE       rConfig.iSquareSize
#define SQR_YSIZE       rConfig.iSquareSize

#define OFST_INCREMENT      rConfig.iSquareSize         // OFFSET into bitmap
#define OFST_BLANK          (0*OFST_INCREMENT)          // OFFSET into bitmap
#define OFST_BLANK_RED      (1*OFST_INCREMENT)          // OFFSET into bitmap
#define OFST_COMPUTER       (2*OFST_INCREMENT)          // OFFSET into bitmap
#define OFST_COMPUTER_KING  (3*OFST_INCREMENT)          // OFFSET into bitmap
#define OFST_HUMAN_KING     (4*OFST_INCREMENT)          // OFFSET into bitmap
#define OFST_HUMAN          (5*OFST_INCREMENT)          // OFFSET into bitmap

FRM *pfrm; //$FORM

//---[ Inline code includes ]----------------------------------------------

/****************************************************************************
*****************************************************************************
*****************************************************************************
****************************************************************************/
CMoveList::CMoveList()
{
    m_iNumBoards = 0;
    m_fClassInitialized = FALSE;
    m_prFirstBoard = NULL;
    m_prCurrentBoard = m_prFirstBoard;
    m_prCurrentSearchBoard = m_prFirstBoard;
}

CMoveList::~CMoveList()
{
    m_prCurrentBoard = m_prFirstBoard;
    PurgeBoards();
}

BOARD CMoveList::GetFirstBoard(BOARD b, int *piPlayerTurn)
{
    AssertSz(m_fClassInitialized, "MoveList class not initialized in GetFirstBoard()");

    m_prCurrentSearchBoard = m_prFirstBoard;
    if (NULL == m_prCurrentSearchBoard)
    return NULL;
    else
    {
    AssertSz((BLACK == m_prCurrentSearchBoard->iPlayerTurn) ||
             (RED == m_prCurrentSearchBoard->iPlayerTurn), 
             "EBr rocks!");
    
        *piPlayerTurn = m_prCurrentSearchBoard->iPlayerTurn;
    CopyBoard(m_prCurrentSearchBoard->b, b);
        
    m_prCurrentSearchBoard = m_prCurrentSearchBoard->prNextBoard;
    return b;
    }
}

BOARD CMoveList::GetNextBoard(BOARD b, int *piPlayerTurn)
{
    AssertSz(m_fClassInitialized, "MoveList class not initialized in GetNextBoard()");

    if (NULL == m_prCurrentSearchBoard)
    {
    return NULL;
    }
    else
    {
    AssertSz((BLACK == m_prCurrentSearchBoard->iPlayerTurn) ||
             (RED == m_prCurrentSearchBoard->iPlayerTurn), 
             "Kt C abayn  04/07/94");
    
        *piPlayerTurn = m_prCurrentSearchBoard->iPlayerTurn;        
    CopyBoard(m_prCurrentSearchBoard->b, b);
    m_prCurrentSearchBoard = m_prCurrentSearchBoard->prNextBoard;
    return b;
    }
}

BOOL CMoveList::Init()
{
    AssertSz(!m_fClassInitialized, "Class already initialized");

    m_fClassInitialized = TRUE;
    return TRUE;
}

BOOL CMoveList::BackMove(BOARD b, int *piPlayerTurn)
{
    AssertSz(m_fClassInitialized, "MoveList class not initialized in BackMove()");

    if (NULL == m_prFirstBoard)
    return FALSE;

    AssertSz(m_prCurrentBoard, "Current Board hosed");

    if (m_prCurrentBoard == m_prFirstBoard)
    {
    return FALSE;
    }
    else
    {
    m_prCurrentBoard = m_prCurrentBoard->prPrevBoard;
    
    AssertSz((BLACK == m_prCurrentBoard->iPlayerTurn) ||
             (RED == m_prCurrentBoard->iPlayerTurn), 
             "Meatloaf");

        *piPlayerTurn = m_prCurrentBoard->iPlayerTurn;
    CopyBoard(m_prCurrentBoard->b, b);
    return TRUE;
    }
}

BOOL CMoveList::ForwardMove(BOARD b, int *piPlayerTurn)
{
    AssertSz(m_fClassInitialized, "MoveList class not initialized in ForwardMove()");

    if (NULL == m_prCurrentBoard)
    return FALSE;

    if (NULL == m_prCurrentBoard->prNextBoard)
    return FALSE;
    else
    {
    m_prCurrentBoard = m_prCurrentBoard->prNextBoard;

    AssertSz((BLACK == m_prCurrentBoard->iPlayerTurn) ||
             (RED == m_prCurrentBoard->iPlayerTurn), 
             "Just say no to yes.");

        *piPlayerTurn = m_prCurrentBoard->iPlayerTurn;
    CopyBoard(m_prCurrentBoard->b, b);
    return TRUE;
    }
}

BOOL CMoveList::NewMove(BOARD b, int iPlayerTurn)
{
    struct rBoardNode *prNewBoard = NULL;

    AssertSz(m_fClassInitialized, "MoveList class not initialized in NewMove()");

    // Remove any old boards that would get overwritten.

    if (NULL != m_prCurrentBoard)
    {
    PurgeBoards();
    }
    
    prNewBoard = (struct rBoardNode *)malloc(sizeof(struct rBoardNode));
    if (!prNewBoard)
    {
    MessageBox(NULL, "Out of memory.", "Checkers", MB_ICONEXCLAMATION | MB_OK);
    return FALSE;
    }
    else
    {
    m_iNumBoards++;

    prNewBoard->prNextBoard = NULL;
    prNewBoard->prPrevBoard = NULL;
    CopyBoard(b, prNewBoard->b);

    if (NULL == m_prFirstBoard)
    {
        m_prFirstBoard = prNewBoard;
    }
    else
    {
        m_prCurrentBoard->prNextBoard = prNewBoard;
    }

    prNewBoard->prPrevBoard = m_prCurrentBoard;
    prNewBoard->iPlayerTurn = iPlayerTurn;
    m_prCurrentBoard = prNewBoard;
    return TRUE;
    }
}

BOOL CMoveList::ClearBoards()
{
    m_prCurrentBoard = m_prFirstBoard;
    return (PurgeBoards());
}

BOOL CMoveList::PurgeBoards()
{
    struct rBoardNode *prDeleteBoard;
    
    if (NULL == m_prCurrentBoard || 0 == m_fClassInitialized)
    return TRUE;
    else
    {
    prDeleteBoard = m_prCurrentBoard->prNextBoard;
    while (prDeleteBoard != NULL)
    {
        m_prCurrentBoard->prNextBoard = prDeleteBoard->prNextBoard;
        free (prDeleteBoard);
        m_iNumBoards--;
        prDeleteBoard = m_prCurrentBoard->prNextBoard;
    }
    return TRUE;
    }
}

/****************************************************************************
*****************************************************************************
*****************************************************************************
****************************************************************************/

BOOL WritePrivateProfileLong(LPCSTR lpszSection, LPCSTR lpszEntry, long lTheLong, LPCSTR lpszFilename);
BOOL WritePrivateProfileInt(LPCSTR lpszSection, LPCSTR lpszEntry, int iTheInt, LPCSTR lpszFilename);
long GetDlgItemLong(HWND hDlg, WORD id);
int  GetDlgItemInt(HWND hDlg, WORD id);
void SetDlgItemInt(HWND hDlg, WORD id, int iValue);
void SetDlgItemLong(HWND hDlg, WORD id, long lValue);
BOOL ValidateNumeric(char *pszText);
LONG GetPrivateProfileLong(LPCSTR lpszSection, LPCSTR lpszEntry, long lDefault, LPCSTR lpszFileName);

BOOL WritePrivateProfileInt(LPCSTR lpszSection, LPCSTR lpszEntry, int iTheInt, LPCSTR lpszFilename)
{
    char szINIString[32];

    AssertSz(lpszSection, "lpszSection == NULL");
    AssertSz(lpszEntry, "lpszEntry == NULL");
    AssertSz(lpszFilename, "lpszFilename == NULL");

    _itoa(iTheInt, szINIString, 10);   // Convert the int to a string. Base10
     return WritePrivateProfileString(lpszSection, lpszEntry, (LPSTR)szINIString, lpszFilename);
}

long GetDlgItemLong(HWND hDlg, WORD id)
{
    char szTemp[20];    // Can't imagine a number longer than this.
    long lTemp;

    GetDlgItemText (hDlg, id, (LPSTR) szTemp, sizeof(szTemp));
    lTemp = atol(szTemp);

    return lTemp;
}

int GetDlgItemInt(HWND hDlg, WORD id)
{
    char szTemp[20];    // Can't imagine a number longer than this.
    int iTemp;

    GetDlgItemText (hDlg, id, (LPSTR) szTemp, sizeof(szTemp));
    iTemp = atoi(szTemp);

    return iTemp;
}

void SetDlgItemInt(HWND hDlg, WORD id, int iValue)
{
    char szTemp[20];     // Can't imagine a number longer than this.
    
    _itoa(iValue, szTemp, 10);
    SetDlgItemText (hDlg, id, szTemp);
}

void SetDlgItemLong(HWND hDlg, WORD id, long lValue)
{
    char szTemp[20];     // Can't imagine a number longer than this.
    
    _ltoa(lValue, szTemp, 10);
    SetDlgItemText (hDlg, id, szTemp);
}

LONG GetPrivateProfileLong(LPCSTR lpszSection, LPCSTR lpszEntry, long lDefault, LPCSTR lpszFileName)
{
    LONG l;
    char szTemp[20];

    GetPrivateProfileString(lpszSection, lpszEntry, "~~", szTemp, 20, lpszFileName);
    if (lstrcmp(szTemp, "~~") == 0)
    l = lDefault;
    else
    l = atol(szTemp);
    return l;
}

BOOL WritePrivateProfileLong(LPCSTR lpszSection, LPCSTR lpszEntry, long lTheLong, LPCSTR lpszFilename)
{
    char szINIString[32];

    AssertSz(lpszSection, "lpszSection == NULL");
    AssertSz(lpszEntry, "lpszEntry == NULL");
    AssertSz(lpszFilename, "lpszFilename == NULL");

    _ltoa(lTheLong, szINIString, 10);   // Convert the int to a string. Base10
     return WritePrivateProfileString(lpszSection, lpszEntry, (LPSTR)szINIString, lpszFilename);
}

/****************************************************************************
*****************************************************************************
*****************************************************************************
****************************************************************************/
int OpenCheckers(HINSTANCE hInstance, int nCmdShow)
{
    MSG msg;
    HACCEL hAccelTable = NULL;          // Accelerator table handle.

    // Perform initializations that apply to a specific instance

    if (!InitInstance(hInstance, nCmdShow)) 
    {
    AssertSz(0,"InitInst failed");
        return (FALSE);
    }

    hAccelTable = LoadAccelerators (hInstance, (LPSTR)"WCheck");
    AssertSz(hAccelTable,"no accelerators");

    // Acquire and dispatch messages until a WM_QUIT message is received.

    while (GetMessage(&msg,         // message structure
        NULL,                                   // handle of window receiving the message
        0,                                      // lowest message to examine
        0))                                     // highest message to examine
    {
        if (!TranslateAccelerator (msg.hwnd, hAccelTable, &msg)) 
        {
            TranslateMessage(&msg); // Translates virtual key codes
            DispatchMessage(&msg);  // Dispatches message to window
        }
    }

    return 0;

} /* end open checkers */

/****************************************************************************

    FUNCTION: WinMain(HINSTANCE, HINSTANCE, LPSTR, int)

    PURPOSE: calls initialization function, processes message loop

    COMMENTS:

        Windows recognizes this function by name as the initial entry point
        for the program.  This function calls the application initialization
        routine, if no other instance of the program is running, and always
        calls the instance initialization routine.  It then executes a message
        retrieval and dispatch loop that is the top-level control structure
        for the remainder of execution.  The loop is terminated when a WM_QUIT
        message is received, at which time this function exits the application
        instance by returning the value passed by PostQuitMessage().

        If this function must abort before entering the message loop, it
        returns the conventional value NULL.

****************************************************************************/
int APIENTRY WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{

    AssertSz(((RED == PLAYER1) && (BLACK == PLAYER2)) || 
         ((BLACK == PLAYER1) && (RED == PLAYER2)), "Players are schizoid");

    hInst = hInstance;                              // Set global Instance handle

    if (!hPrevInstance)                                             
    {
        if (!InitApplication(hInstance))        
        {
            return (FALSE);     
        }
    }

    // Check for the -Embedding switch

    if (lpCmdLine && (lpCmdLine[0] == '/' || lpCmdLine[0] == '-'))
    {

        // Attempt to be a form

    if (NOERROR == HrStartOleAndRegisterClassFactory())
        {
        rGameState.fPlayAsForm = TRUE; // we are acting as a form

        #ifdef DEBUG
        nCmdShow = SW_SHOWMINIMIZED;
        #else
        nCmdShow = SW_HIDE;
        #endif

        // Open the checkers form window .. but do not show until we're DoVerb'd

        OpenCheckers(hInstance, nCmdShow);

        // Call this function if ..StartForms succeeded

        HrStopForms();

        return 0;
        }

        if (IDYES == MessageBox(GetFocus(), "Unable to initialize messaging subsystem.\nWould you like to play against the computer?", "Checkers", MB_YESNO ))
        {
        OpenCheckers(hInstance, nCmdShow);
        return 0;
        }

    }

    OpenCheckers(hInstance, nCmdShow);
    return 0;
}

VOID ReadPlayerInfo(int iPlayerNum, char *pszPlayerName)
{
    AssertSz((iPlayerNum == BLACK) || (iPlayerNum == RED), "Invalid Player Num");
    AssertSz(pszPlayerName, "Playername can't be NULL");

    if (rGameState.fPlayAsForm)
    {
    rConfig.rPlayer[iPlayerNum].iPlayerType = HUMAN_PLAYER;
    if (22871 == GetPrivateProfileInt ("Computer", "Config", HUMAN_PLAYER, INI_NAME))
        {
        rConfig.rPlayer[iPlayerNum].iPlayerType = COMPUTER_PLAYER;
        }
    }
    else
    {
    if (PLAYER1 == iPlayerNum)
        rConfig.rPlayer[iPlayerNum].iPlayerType = HUMAN_PLAYER;
    else
        rConfig.rPlayer[iPlayerNum].iPlayerType = COMPUTER_PLAYER;
    }
       
    // Get computer config options.

    rConfig.rPlayer[iPlayerNum].iMemPositions = GetPrivateProfileInt (pszPlayerName, "MemPositions", 0, INI_NAME);
    rConfig.rPlayer[iPlayerNum].iUseMoveTheory = GetPrivateProfileInt (pszPlayerName, "UseMoveTheory", 1, INI_NAME);
    rConfig.rPlayer[iPlayerNum].iUseMoveShuffling = GetPrivateProfileInt (pszPlayerName, "UseMoveShuffling", 1, INI_NAME);
    rConfig.rPlayer[iPlayerNum].iUseEqualMoveSkipping = GetPrivateProfileInt (pszPlayerName, "UseEqualMoveSkipping", 1, INI_NAME);
    rConfig.rPlayer[iPlayerNum].iUseOpeningBook = GetPrivateProfileInt (pszPlayerName, "UseOpeningBook", 1, INI_NAME);
    rConfig.rPlayer[iPlayerNum].lUseGoodMoveSkipping = GetPrivateProfileLong (pszPlayerName, "UseGoodMoveSkipping", 0, INI_NAME);
    rConfig.rPlayer[iPlayerNum].iMaxRecursionDepth = GetPrivateProfileInt (pszPlayerName, "MaxRecursionDepth", 5, INI_NAME);
    rConfig.rPlayer[iPlayerNum].iUseAlphaBetaPruning = GetPrivateProfileInt (pszPlayerName, "UseAlphaBetaPruning", 1, INI_NAME);
    rConfig.rPlayer[iPlayerNum].lAlphaPruningOriginalDepth = GetPrivateProfileLong (pszPlayerName, "AlphaPruningOriginalDepth", 2, INI_NAME);
    rConfig.rPlayer[iPlayerNum].lAlphaPruningWidth = GetPrivateProfileLong (pszPlayerName, "AlphaPruningWidth", 35, INI_NAME);

}

VOID    ReadINI ()
{
    TraceTag(tagUI,"ReadINI()");

    // Read general config info

    rConfig.iGameType = GetPrivateProfileInt ("Config", "GameType", GAME_CHECKERS, INI_NAME);
    rConfig.iMustJump = GetPrivateProfileInt ("Config", "MustJump", 1, INI_NAME);
    rConfig.iBoardFlipped = 1;
    rConfig.iSquareSize = GetPrivateProfileInt ("Config", "SquareSize", 30, INI_NAME);
    rConfig.iMaxMoves = GetPrivateProfileInt ("Config", "MaxMoves", 200, INI_NAME);

    // Read specific player config for both (potential) computer players.

    ReadPlayerInfo(PLAYER1, "Player1");
    ReadPlayerInfo(PLAYER2, "Player2");
}

VOID WritePlayerInfo(int iPlayerNum, char *pszPlayerName)
{
    AssertSz((iPlayerNum == RED) || (iPlayerNum == BLACK), "Invalid Player Num");
    AssertSz(pszPlayerName, "Playername can't be NULL");

    // Player specific config items

    WritePrivateProfileInt (pszPlayerName, "PlayerType", rConfig.rPlayer[iPlayerNum].iPlayerType, INI_NAME);
    WritePrivateProfileInt (pszPlayerName, "MemPositions", rConfig.rPlayer[iPlayerNum].iMemPositions, INI_NAME);
    WritePrivateProfileInt (pszPlayerName, "UseMoveTheory", rConfig.rPlayer[iPlayerNum].iUseMoveTheory, INI_NAME);
    WritePrivateProfileInt (pszPlayerName, "UseMoveShuffling", rConfig.rPlayer[iPlayerNum].iUseMoveShuffling, INI_NAME);
    WritePrivateProfileInt (pszPlayerName, "UseEqualMoveSkipping", rConfig.rPlayer[iPlayerNum].iUseEqualMoveSkipping, INI_NAME);
    WritePrivateProfileInt (pszPlayerName, "UseOpeningBook", rConfig.rPlayer[iPlayerNum].iUseOpeningBook, INI_NAME);
    WritePrivateProfileLong(pszPlayerName, "UseGoodMoveSkipping", rConfig.rPlayer[iPlayerNum].lUseGoodMoveSkipping, INI_NAME);
    WritePrivateProfileInt (pszPlayerName, "MaxRecursionDepth", rConfig.rPlayer[iPlayerNum].iMaxRecursionDepth, INI_NAME);
    WritePrivateProfileInt (pszPlayerName, "UseAlphaBetaPruning", rConfig.rPlayer[iPlayerNum].iUseAlphaBetaPruning, INI_NAME);
    WritePrivateProfileLong(pszPlayerName, "AlphaPruningOriginalDepth", rConfig.rPlayer[iPlayerNum].lAlphaPruningOriginalDepth, INI_NAME);
    WritePrivateProfileLong(pszPlayerName, "AlphaPruningWidth", rConfig.rPlayer[iPlayerNum].lAlphaPruningWidth, INI_NAME);

}

VOID    WriteINI ()
{
    RECT    rect;
    char    szTempStr[10];                       // For rect.value translation

    TraceTag(tagUI,"WriteINI()");

    // Store state of config radio buttons

    WritePrivateProfileInt ("Config", "GameType", rConfig.iGameType, INI_NAME);
    WritePrivateProfileInt ("Config", "MustJump", rConfig.iMustJump, INI_NAME);
    WritePrivateProfileInt ("Config", "SquareSize", rConfig.iSquareSize, INI_NAME);
    WritePrivateProfileInt ("Config", "MaxMoves", rConfig.iMaxMoves, INI_NAME);

    // Write player info

    WritePlayerInfo(PLAYER1, "Player1");
    WritePlayerInfo(PLAYER2, "Player2");

    // Store state of Window

    GetWindowRect (hMainWnd, &rect);
    if (!IsIconic(hMainWnd))
    {
    wsprintf (szTempStr, "%d", rect.left);
    WritePrivateProfileString ("Window", "Left", szTempStr, INI_NAME);
    wsprintf (szTempStr, "%d", rect.top);
    WritePrivateProfileString ("Window", "Top", szTempStr, INI_NAME);
    wsprintf (szTempStr, "%d", rect.right - rect.left);
    WritePrivateProfileString ("Window", "Width", szTempStr, INI_NAME);
    wsprintf (szTempStr, "%d", rect.bottom - rect.top);
    WritePrivateProfileString ("Window", "Height", szTempStr, INI_NAME);
    }

}

BOOL InitApplication(HINSTANCE hInstance)
{
    WNDCLASS        wc;

    // Fill in window class structure with parameters that describe the
    // main window.

    wc.style         = CS_HREDRAW | CS_VREDRAW;             // Class style(s).
    wc.lpfnWndProc   = (WNDPROC)CheckersWndProc;    // Window Procedure
    wc.cbClsExtra    = 0;                                   // No per-class extra data.
    wc.cbWndExtra    = 0;                                   // No per-window extra data.
    wc.hInstance     = hInstance;                           // Owner of this class
    wc.hIcon         = LoadIcon (hInstance, "WCheckIcon");  // Icon name from .RC
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);                 // Cursor
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);                    // Default color
    wc.lpszMenuName  = (LPSTR)"WCheck_NORMAL";              // Menu name from .RC
    wc.lpszClassName = szAppName;                                           // Name to register as

    // Register the window class and return success/failure code.
    return (RegisterClass(&wc));
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND    hWnd; // Main window handle.
    HDC hdc = NULL;

    // Save the instance handle in static variable, which will be used in
    // many subsequence calls from this application to Windows.

    // need to set this here because we may get call from somewhere besides winmain
    hInst = hInstance; // Store instance handle in our global variable

    hbrWhite = (HBRUSH)GetStockObject(WHITE_BRUSH);
    hbrBlack = (HBRUSH)GetStockObject(BLACK_BRUSH);

    hbrRed        = CreateSolidBrush(RGB(0xFF,0,0));
    hbrBckgrnd    = CreateSolidBrush(GetNearestColor(hdc, RGB(0xAA,0xAA,0xAA)));
    hbrBlue       = CreateSolidBrush(RGB(0,0,0xFF));
    hpenDkgrey    = CreatePen( PS_SOLID, 1, RGB( 0x55, 0x55, 0x55 ) );

    #ifdef _WIN32
        hbrDkgrey     = CreateSolidBrush(RGB(0x55,0x55,0x55));
    #else
        hbrDkgrey     = CreateSolidBrush(GetNearestColor(hdc, RGB(0x55,0x55,0x55)));
    #endif

    // Fail initialization if we can't create brushs/pens/etc..

    if (!hbrRed || 
        !hbrBckgrnd || 
        !hbrBlue ||
        !hbrWhite || 
        !hbrBlack || 
        !hpenDkgrey || 
        !hbrDkgrey)
    return(FALSE);

    curNormal   = LoadCursor(NULL, IDC_ARROW);
    curThink    = LoadCursor(NULL, IDC_WAIT);
    curResize       = LoadCursor(NULL, IDC_SIZENWSE);

    if (!curNormal || !curThink || !curResize)
    return(FALSE);

    // Create a main window for this application instance.
    hWnd = CreateWindow(
        szAppName,           // See RegisterClass() call.
        szTitle,             // Text for window title bar.
        WS_OVERLAPPEDWINDOW, // Window style.
    GetPrivateProfileInt ("Window", "Left",  13  /* CW_USEDEFAULT */, INI_NAME),
    GetPrivateProfileInt ("Window", "Top",   8   /* CW_USEDEFAULT */, INI_NAME),
    GetPrivateProfileInt ("Window", "Width", 356 /* CW_USEDEFAULT */, INI_NAME),
    GetPrivateProfileInt ("Window", "Height",306 /* CW_USEDEFAULT */, INI_NAME),
        NULL,                // Overlapped windows have no parent.
        NULL,                // Use the window class menu.
        hInstance,           // This instance owns this window.
        NULL                 // We don't use any data in our WM_CREATE
    );

    // If window could not be created, return "failure"
    if (!hWnd) {
        return (FALSE);
    }

    while (!SetTimer (hWnd, ID_TIMER, TIMER_GRANULARITY, NULL))
    {
    if (IDCANCEL == MessageBox (hWnd, "Too many clocks or timers!", szAppName,
        MB_ICONEXCLAMATION | MB_RETRYCANCEL))
        {
        return FALSE;
        }
    }

    // Make the window visible; update its client area; and return "success"

    ShowWindow(hWnd, nCmdShow); // Show the window // SW_SHOWNORMAL // SW_HIDE
    UpdateWindow(hWnd);         // Sends WM_PAINT message

    SendMessage(hWnd, WM_OTHERINIT, 0, 0L);

    return (TRUE);              // We succeeded...

}

/****************************************************************************
*****************************************************************************
*****************************************************************************
****************************************************************************/

// FillBoard() puts the pieces on the board (draws them).

void NEAR PASCAL FillBoard(BOARD b, HDC hDC)

{
    int         i                       = 0;            // Loop (for pieces) variable
    HDC         hTmpDC          = NULL;         // Temp work DC
    HBITMAP hOldbm              = NULL;         // Store old Bitmap handle
    int         yBm             = 0;            // Bitmap to use (depending on piece)
    int         iOffset         = 0;            // Squares alternate starting postion..
    int         iX                      = 0;            // Location (x) to place square
    int             iY                      = 0;            // Location (y) to place square
    int     iLocation       = 0;            // For figuring real location after swap..

    hTmpDC = CreateCompatibleDC( hDC );
    hOldbm = (HBITMAP)SelectObject( hTmpDC, hBtmaps );

    for (i=1; i <= 32; i++)
    {
        if (rConfig.iBoardFlipped)
            iLocation = 33-i;
        else
            iLocation = i;
            
    AssertSz(iLocation > 0, "Bee-Gees r a bit");
    AssertSz(iLocation <= SQRS_MAX, "Jello: The environmentally safe defoliant");

    switch(b[iLocation])
    {
        case 0:
        yBm = 0;
        break;
        case (RED | KING):
        yBm = OFST_COMPUTER_KING;
        break;
        case RED:
        yBm = OFST_COMPUTER;
        break;
        case (BLACK | KING):
        yBm = OFST_HUMAN_KING;
        break;
        case BLACK:
        yBm = OFST_HUMAN;
        break;
        default:
        {
        AssertSz(FALSE, "Piece value invalid");
        TraceTag(tagUI, "Invalid piece value of piece %d is: %d", i, b[i]);
        }
        break;
    }

        // Calculate location of square on board. (offset?)

        iY = (i-1) / 4;
        iX = (i-1) % 4;
    if ((iY % 2) == 1)
            iOffset = 0;
        else
            iOffset = 1;

        // Place the square on the board

        BitBlt( hDC, BOARD_LEFT + (rConfig.iSquareSize*(2*iX+iOffset)), BOARD_TOP + (rConfig.iSquareSize*iY),
        rConfig.iSquareSize, rConfig.iSquareSize, hTmpDC, 0, yBm, SRCCOPY );

        // All squares have an accompanying blank square. Depending on the 
        // offset, it can be on either side of the filled square.

        if (iOffset == 1)
            BitBlt( hDC, BOARD_LEFT + (rConfig.iSquareSize*(2*iX)), BOARD_TOP + (rConfig.iSquareSize*iY),
                rConfig.iSquareSize, rConfig.iSquareSize, hTmpDC, 0, OFST_BLANK_RED, SRCCOPY);
        else
            BitBlt( hDC, BOARD_LEFT + (rConfig.iSquareSize*(2*iX+1)), BOARD_TOP + (rConfig.iSquareSize*iY),
                rConfig.iSquareSize, rConfig.iSquareSize, hTmpDC, 0, OFST_BLANK_RED, SRCCOPY);

    }

    // Draw setup rack if the user is in setup mode.

    if (rGameState.fSetupMode)
    {

        BitBlt( hDC, BOARD_LEFT + (rConfig.iSquareSize * RACK_LEFT), 
            BOARD_TOP + (rConfig.iSquareSize * (RACK_TOP)), 
            rConfig.iSquareSize, rConfig.iSquareSize, 
            hTmpDC, 0, OFST_COMPUTER, SRCCOPY);

        BitBlt( hDC, BOARD_LEFT + (rConfig.iSquareSize * RACK_LEFT), 
            BOARD_TOP + (rConfig.iSquareSize * (RACK_TOP + 1)), 
            rConfig.iSquareSize, rConfig.iSquareSize, 
            hTmpDC, 0, OFST_HUMAN, SRCCOPY);

        BitBlt( hDC, BOARD_LEFT + (rConfig.iSquareSize * RACK_LEFT), 
            BOARD_TOP + (rConfig.iSquareSize * (RACK_TOP + 2)), 
            rConfig.iSquareSize, rConfig.iSquareSize, 
            hTmpDC, 0, OFST_COMPUTER_KING, SRCCOPY);

        BitBlt( hDC, BOARD_LEFT + (rConfig.iSquareSize * RACK_LEFT), 
            BOARD_TOP + (rConfig.iSquareSize * (RACK_TOP + 3)), 
            rConfig.iSquareSize, rConfig.iSquareSize, 
            hTmpDC, 0, OFST_HUMAN_KING, SRCCOPY);

        BitBlt( hDC, BOARD_LEFT + (rConfig.iSquareSize * RACK_LEFT), 
            BOARD_TOP + (rConfig.iSquareSize * (RACK_TOP + 4)), 
            rConfig.iSquareSize, rConfig.iSquareSize, 
            hTmpDC, 0, OFST_BLANK, SRCCOPY);
    }

    SelectObject( hTmpDC, hOldbm );
    DeleteDC( hTmpDC );
}

// Removes the piece that's moving, and replaces with a blank square.

void vClearMovingPiece(HDC hDC, int iX, int iY)
{
    HDC   hTmpDC;
    HBITMAP hOldbm;
    int   yBm;

    hTmpDC = CreateCompatibleDC( hDC );
    hOldbm = (HBITMAP)SelectObject( hTmpDC, hBtmaps );

    yBm = 0;

    BitBlt( hDC, BOARD_LEFT + (rConfig.iSquareSize*iX), BOARD_TOP + (rConfig.iSquareSize*iY),
    rConfig.iSquareSize, rConfig.iSquareSize, hTmpDC, 0, yBm, SRCCOPY );

    SelectObject( hTmpDC, hOldbm );
    DeleteDC( hTmpDC );
}

// Reset the board to starting positions.
void ClearBoard(BOARD b)
{
    Assert(b);

    b[0]  = 0;          b[1]  = BLACK;  b[2]  = BLACK;  b[3] = BLACK;
    b[4]  = BLACK;  b[5]  = BLACK;  b[6]  = BLACK;      b[7] = BLACK;
    b[8]  = BLACK;  b[9]  = BLACK;  b[10] = BLACK;      b[11] = BLACK;
    b[12] = BLACK;  b[13] = EMPTY;      b[14] = EMPTY;  b[15] = EMPTY;
    b[16] = EMPTY;  b[17] = EMPTY;      b[18] = EMPTY;  b[19] = EMPTY;
    b[20] = EMPTY;  b[21] = RED;        b[22] = RED;    b[23] = RED;
    b[24] = RED;        b[25] = RED;    b[26] = RED;    b[27] = RED;
    b[28] = RED;        b[29] = RED;    b[30] = RED;    b[31] = RED;
    b[32] = RED;
}

void DrawBoard(BOARD b)
{
    HDC hDC = GetDC(hMainWnd);
    
    Assert(b);

    FillBoard(b, hDC);
    ReleaseDC(hMainWnd, hDC);

}

/****************************************************************************
*****************************************************************************
*****************************************************************************
****************************************************************************/

void DisplayGameOver(HWND hWnd, int iPlayerTurn)
{
    int iWinner = BLACK;

    AssertSz(hWnd, "hWnd hosed, homey.");
    AssertSz((rGameState.iPlayerTurn == BLACK) || 
             (rGameState.iPlayerTurn == RED), "Very low sodium");

    // NOTE: Caller is passing in the losing player. The turn has already
    // switched before this gets called. This makes iPlayerTurn 
    // equivalent to the winner in a give-away game. If the game type is 
    // standard checkers, I want to invert winner.

    iWinner = iPlayerTurn;
    if (rConfig.iGameType == GAME_CHECKERS)
    iWinner = next(iWinner);
    
    if (RED == iWinner)
        MessageBox(hWnd, "Game over. Red wins!", "Checkers", MB_OK );
    else
        MessageBox(hWnd, "Game over. Black wins!", "Checkers", MB_OK );

}

void DisplayGameDrawn(HWND hWnd, int iPlayerTurn)
{
    AssertSz(hWnd, "hWnd hosed (in DisplayGameDrawn), homey.");
    AssertSz((rGameState.iPlayerTurn == BLACK) || 
             (rGameState.iPlayerTurn == RED), "Vl bites");

    MessageBox(hWnd, "Game drawn. (Game over)", "Checkers", MB_OK );
}


/****************************************************************************
*****************************************************************************
*****************************************************************************
****************************************************************************/

void NEAR PASCAL CheckGenPieces(HDC hDC)
{
    HDC     hTmpDC  = NULL;
    HBITMAP hOldbm  = NULL;
    HBRUSH  hOldbr  = NULL;
    int     i               = 0;

    AssertSz(hDC, "Null hDC in CheckGenPieces");

    if( hBtmaps != NULL )
        DeleteObject( hBtmaps );

    // We have 6 different pieces (including the blank). So we just fill
    // a region big enough for 6 squares.
    hBtmaps = CreateCompatibleBitmap( hDC, SQR_XSIZE, 6*SQR_YSIZE );

    /* allocate an off-screen DC, so we can paint the ellipses now */
    hTmpDC = CreateCompatibleDC( hDC );
    hOldbm = (HBITMAP)SelectObject( hTmpDC, hBtmaps );

    /* blank out the off-screen bitmap, ie: paint the background into it */
    hOldbr = (HBRUSH)SelectObject( hTmpDC, GetStockObject( LTGRAY_BRUSH ));
    PatBlt( hTmpDC, 0, 0, SQR_XSIZE, SQR_YSIZE, PATCOPY );
    SetBkMode( hTmpDC, TRANSPARENT );

    /* draw the square's "grooved" borders */
    SelectObject( hTmpDC, hpenDkgrey );
    MoveTo( hTmpDC, 2, SQR_YSIZE-2 );
    LineTo( hTmpDC, SQR_XSIZE-2, SQR_YSIZE-2 );
    LineTo( hTmpDC, SQR_XSIZE-2, 1 );
    SelectObject( hTmpDC, GetStockObject( WHITE_PEN ) );
    LineTo( hTmpDC, 1, 1 );
    LineTo( hTmpDC, 1, SQR_YSIZE );
    SelectObject( hTmpDC, GetStockObject( BLACK_PEN ) );
    MoveTo( hTmpDC, 2, SQR_YSIZE-1 );
    LineTo( hTmpDC, SQR_XSIZE-1, SQR_YSIZE-1 );
    LineTo( hTmpDC, SQR_XSIZE-1, 0 );

    /* copy the borders to the other bitmaps */
    for( i=OFST_INCREMENT; i <= OFST_HUMAN; i+=OFST_INCREMENT )
    BitBlt(hTmpDC, 0, i, SQR_XSIZE, SQR_YSIZE, hTmpDC, 0, 0, SRCCOPY);

    /* Attempt at RED SQUARE*/
    SelectObject( hTmpDC, hbrDkgrey );
    hOldbr = (HBRUSH)SelectObject( hTmpDC, GetStockObject( LTGRAY_BRUSH ));
    SelectObject( hTmpDC, hbrRed);
    PatBlt( hTmpDC, 0+2, OFST_BLANK_RED+2, SQR_XSIZE-4, SQR_YSIZE-4, PATCOPY );

    /* first piece: computer */
    SelectObject(hTmpDC, GetStockObject( WHITE_PEN ) );
    SelectObject(hTmpDC, GetStockObject( WHITE_BRUSH ) );
    Ellipse( hTmpDC, 3, OFST_COMPUTER+3, SQR_XSIZE-6, OFST_COMPUTER+SQR_YSIZE-6 );
    SelectObject(hTmpDC, hpenDkgrey );
    SelectObject(hTmpDC, hbrDkgrey );
    Ellipse( hTmpDC, 6, OFST_COMPUTER+6, SQR_XSIZE-3, OFST_COMPUTER+SQR_YSIZE-3 );
    SelectObject(hTmpDC, GetStockObject( BLACK_PEN ) );
    SelectObject(hTmpDC, hbrRed);
    Ellipse( hTmpDC, 4, OFST_COMPUTER+4, SQR_XSIZE-5, OFST_COMPUTER+SQR_YSIZE-5 );

    /* computer king */
    BitBlt( hTmpDC, 0, OFST_COMPUTER_KING, SQR_XSIZE, OFST_COMPUTER_KING+SQR_YSIZE, hTmpDC,
        0, OFST_COMPUTER, SRCCOPY );
    SelectObject( hTmpDC, GetStockObject( WHITE_PEN ) );
    MoveTo(hTmpDC, (SQR_XSIZE / 2 - 4), OFST_COMPUTER_KING + (SQR_YSIZE / 2));
    LineTo(hTmpDC, (SQR_XSIZE / 2 + 4), OFST_COMPUTER_KING + (SQR_YSIZE / 2));
    MoveTo(hTmpDC, (SQR_XSIZE / 2 - 4), OFST_COMPUTER_KING + (SQR_YSIZE / 2) + 1);
    LineTo(hTmpDC, (SQR_XSIZE / 2 + 4), OFST_COMPUTER_KING + (SQR_YSIZE / 2) + 1);
    MoveTo(hTmpDC, (SQR_XSIZE / 2 - 2), OFST_COMPUTER_KING + (SQR_YSIZE / 2) - 1);
    LineTo(hTmpDC, (SQR_XSIZE / 2 + 2), OFST_COMPUTER_KING + (SQR_YSIZE / 2) - 1);

    MoveTo(hTmpDC, (SQR_XSIZE / 2 - 4), OFST_COMPUTER_KING + (SQR_YSIZE / 2) - 1);
    LineTo(hTmpDC, (SQR_XSIZE / 2 - 6), OFST_COMPUTER_KING + (SQR_YSIZE / 2) - 3);
    MoveTo(hTmpDC, (SQR_XSIZE / 2 + 3), OFST_COMPUTER_KING + (SQR_YSIZE / 2) - 1);
    LineTo(hTmpDC, (SQR_XSIZE / 2 + 5), OFST_COMPUTER_KING + (SQR_YSIZE / 2) - 3);
    MoveTo(hTmpDC, (SQR_XSIZE / 2 - 2), OFST_COMPUTER_KING + (SQR_YSIZE / 2) - 2);
    LineTo(hTmpDC, (SQR_XSIZE / 2 - 3), OFST_COMPUTER_KING + (SQR_YSIZE / 2) - 4);
    MoveTo(hTmpDC, (SQR_XSIZE / 2 + 1), OFST_COMPUTER_KING + (SQR_YSIZE / 2) - 2);
    LineTo(hTmpDC, (SQR_XSIZE / 2 + 3), OFST_COMPUTER_KING + (SQR_YSIZE / 2) - 4);

    /* human king */
    BitBlt( hTmpDC, 0, OFST_HUMAN_KING, SQR_XSIZE, OFST_HUMAN_KING+SQR_YSIZE, hTmpDC,
    0, OFST_COMPUTER, SRCCOPY );
    SelectObject(hTmpDC, hbrBlack);
    SelectObject(hTmpDC, GetStockObject( BLACK_PEN ) );
    Ellipse( hTmpDC, 4, OFST_HUMAN_KING+4, SQR_XSIZE-5, OFST_HUMAN_KING+SQR_YSIZE-5 );
    SelectObject( hTmpDC, GetStockObject( WHITE_PEN ) );
    SelectObject( hTmpDC, GetStockObject( WHITE_PEN ) );
    MoveTo(hTmpDC, (SQR_XSIZE / 2 - 4), OFST_HUMAN_KING + (SQR_YSIZE / 2));
    LineTo(hTmpDC, (SQR_XSIZE / 2 + 4), OFST_HUMAN_KING + (SQR_YSIZE / 2));
    MoveTo(hTmpDC, (SQR_XSIZE / 2 - 4), OFST_HUMAN_KING + (SQR_YSIZE / 2) + 1);
    LineTo(hTmpDC, (SQR_XSIZE / 2 + 4), OFST_HUMAN_KING + (SQR_YSIZE / 2) + 1);
    MoveTo(hTmpDC, (SQR_XSIZE / 2 - 2), OFST_HUMAN_KING + (SQR_YSIZE / 2) - 1);
    LineTo(hTmpDC, (SQR_XSIZE / 2 + 2), OFST_HUMAN_KING + (SQR_YSIZE / 2) - 1);

    MoveTo(hTmpDC, (SQR_XSIZE / 2 - 4), OFST_HUMAN_KING + (SQR_YSIZE / 2) - 1);
    LineTo(hTmpDC, (SQR_XSIZE / 2 - 6), OFST_HUMAN_KING + (SQR_YSIZE / 2) - 3);
    MoveTo(hTmpDC, (SQR_XSIZE / 2 + 3), OFST_HUMAN_KING + (SQR_YSIZE / 2) - 1);
    LineTo(hTmpDC, (SQR_XSIZE / 2 + 5), OFST_HUMAN_KING + (SQR_YSIZE / 2) - 3);
    MoveTo(hTmpDC, (SQR_XSIZE / 2 - 2), OFST_HUMAN_KING + (SQR_YSIZE / 2) - 2);
    LineTo(hTmpDC, (SQR_XSIZE / 2 - 3), OFST_HUMAN_KING + (SQR_YSIZE / 2) - 4);
    MoveTo(hTmpDC, (SQR_XSIZE / 2 + 1), OFST_HUMAN_KING + (SQR_YSIZE / 2) - 2);
    LineTo(hTmpDC, (SQR_XSIZE / 2 + 3), OFST_HUMAN_KING + (SQR_YSIZE / 2) - 4);
    
    /* human */
    BitBlt( hTmpDC, 0, OFST_HUMAN, SQR_XSIZE, SQR_YSIZE, hTmpDC,
    0, OFST_COMPUTER, SRCCOPY );
    SelectObject(hTmpDC, GetStockObject( BLACK_PEN ) );
    SelectObject(hTmpDC, hbrBlack);
    Ellipse( hTmpDC, 4, OFST_HUMAN+4, SQR_XSIZE-5, OFST_HUMAN+SQR_YSIZE-5 );

    SelectObject( hTmpDC, hOldbr );
    SelectObject( hTmpDC, hOldbm );
    DeleteDC( hTmpDC );
}

/****************************************************************************
*****************************************************************************
*****************************************************************************
****************************************************************************/

void NEAR PASCAL CheckCreate()

{
    HDC  hDC;
    TEXTMETRIC    charsize;           /* characteristics of the characters */
    int COLOR = 1;

    hDC = GetDC(hMainWnd);
    GetTextMetrics(hDC, (LPTEXTMETRIC)&charsize);

    ReleaseDC(hMainWnd, hDC);

    COLOR = GetDeviceCaps(hDC, NUMCOLORS) > 2;

    if (COLOR == TRUE)
    {
    hbrComputer = hbrBlue;
    hbrHuman = hbrRed;
    }
    else
    {
    hbrComputer = hbrBlack;
    hbrHuman = hbrWhite;
    }
}

/****************************************************************************
*****************************************************************************
*****************************************************************************
****************************************************************************/

/* Called on WM_PAINT messages. */

void NEAR PASCAL CheckPaint(BOARD b, HDC hDC)

{
    CheckGenPieces(hDC);
    SetBkMode(hDC, OPAQUE);

    DrawBoard(b);
}

/****************************************************************************
*****************************************************************************
*****************************************************************************
****************************************************************************/

void inline vTranslateCurPosToSquare(POINT pntCur, int *pix, int *piy)
{
    Assert(pix);
    Assert(piy);
    Assert(rConfig.iSquareSize != 0);

    *pix = (pntCur.x - BOARD_LEFT) / rConfig.iSquareSize;
    *piy = (pntCur.y - BOARD_TOP) / rConfig.iSquareSize;

    if ((*pix < 0) || (*pix > 7) || (*piy < 0) || (*piy > 7))
    {
        if ((!rGameState.fSetupMode) || (*pix != 10) || (*piy < 2) || (*piy > 6))
        {
            *pix = -1;              // Return invalid x/y locations
            *piy = -1;              // Return invalid x/y locations
        }
    }
}

void inline vTranslateUIToEngineSquare(int *piEngine, int iX, int iY)
{
    AssertSz(piEngine, "piEngine == NULL");

    if (((iY + iX) % 2 == 0) ||
    (iY < 0) || (iY > 7) || (iX < 0) || (iX > 7))
    {
    *piEngine = -1;         // Return invalid engine ID
        return;
    }
    else
    {
    *piEngine = iY * 4 + (iX / 2) + 1;
    }

    if (rConfig.iBoardFlipped)
        *piEngine = (33 - *piEngine);
}

void inline vTranslateEngineToUISquare(int iEngine, int *piX, int *piY)
{
    Assert(iEngine > 0);
    Assert(piX);
    Assert(piY);

    if (rConfig.iBoardFlipped)
        iEngine = (33 - iEngine);
    
    *piY = (iEngine - 1) / 4;
    *piX = ((iEngine - 1) % 4) * 2 + ((*piY + 1) % 2);
}                           

/****************************************************************************
*****************************************************************************
*****************************************************************************
****************************************************************************/

BOOL fValidSetupPiece(BOARD b, int ix, int iy)
{
    int iEngine = -1;
    int iPiece  = -1;
    BOOL fRackPiece = FALSE;

    AssertSz(b, "Where's the board");

    if ((ix < 0) || (ix > 7) || (iy < 0) || (iy > 7))
    {
        // Check for Setup Rack pieces

        if ((ix != 10) || (iy < 2) || (iy > 6))
            return FALSE;
        else
            fRackPiece = TRUE;
    }
    
    vTranslateUIToEngineSquare(&iEngine, ix, iy);

    AssertSz((iEngine == -1) || 
         ((iEngine > 0) && (iEngine <= SQRS_MAX)), 
             "iEngine needs counseling");
    
    if (iEngine != -1)
    {
        iPiece = (int) b[iEngine];

        if ((iPiece & RED) || (iPiece & BLACK) || (iPiece == EMPTY))
            return TRUE;
        else
            return FALSE;
    }
    else
    {
        if (!fRackPiece)
            return FALSE;
        else
            return TRUE;
    }

}

BOOL fValidPlayerPiece(BOARD b, int ix, int iy)
{
    int iEngine = 0;
    int iPiece = 0;

    AssertSz(b, "Where's the board?");
    AssertSz(((rGameState.iPlayerTurn == RED) || 
          (rGameState.iPlayerTurn == BLACK)), "Harrison");
    
    if ((ix < 0) || (ix > 7) || (iy < 0) || (iy > 7))
    return FALSE;

    vTranslateUIToEngineSquare(&iEngine, ix, iy);

    // Assert that the engine return is either a "normal" invalid, or
    // a normal engine square. Should NOT be 0.

    AssertSz((iEngine == -1) || 
         ((iEngine > 0) && (iEngine <= SQRS_MAX)), 
             "Abort, Retry, Fail?");
    
    if (iEngine != -1)
    iPiece = (int) b[iEngine];
    else
        return FALSE;

    if (RED == rGameState.iPlayerTurn)
    {
    if (iPiece & RED)
        return TRUE;
    else
        return FALSE;
    }
    else 
    {
        if (BLACK == rGameState.iPlayerTurn)
    {
        if (iPiece & BLACK)
        return TRUE;
        else
        return FALSE;
        }
    else
        {
        AssertSz(FALSE, "rGameState.iPlayerTurn invalid!");
        return FALSE;
    }
    }
}


/****************************************************************************
*****************************************************************************
*****************************************************************************
****************************************************************************/

void OnGamePlayableAfterMove(void)
{
    if (pfrm)
    {
    AssertSz(pfrm->pMessage,"no message to send");

    // ----- Update our forms information based on user interaction
    pfrm->SetCheckersData(b,rGameState.iPlayerTurn,0,QualityOfBoard(b,rGameState.iPlayerTurn));

    // ----- Send this baby, and shut her down
    SetWindowText(hMainWnd,"Sending ...");
    pfrm->SendForm();
    pfrm->ShutdownForm(OLECLOSE_NOSAVE);
    }
}

/****************************************************************************
*****************************************************************************
*****************************************************************************
****************************************************************************/
// Handle WM_INITMENU message.

VOID vHandle_WM_INITMENU(HWND hWnd, HMENU hMenu)
{
    hMenu = GetMenu(hWnd);
    if (rGameState.fThinking)
    {
    EnableMenuItem(hMenu, 0, MF_DISABLED | MF_BYPOSITION);
    EnableMenuItem(hMenu, 1, MF_DISABLED | MF_BYPOSITION);
    }
    else
    {
    EnableMenuItem(hMenu, 0, MF_ENABLED | MF_BYPOSITION);
    EnableMenuItem(hMenu, 1, MF_ENABLED | MF_BYPOSITION);
    }
}

BOOL fHandle_WM_CREATE(HWND hWnd, CREATESTRUCT FAR* lpCreateStruct)
{
    HDC         hDC     = NULL;
    HMENU       hm              = NULL;

    hMainWnd = hWnd;
    ReadINI();

    // Set game state variables.

    rGameState.fSetupMode = FALSE;          // Game in setup mode? Need for button processing
    rGameState.fThinking = FALSE;           // Is the computer thinking?
    rGameState.fPaused = FALSE;             // Is the game paused?
    rGameState.fGameInProgress = FALSE;     // Did the game start? How to react to "File:New"
    rGameState.fLMouseButtonDown = FALSE;   // Is the left mouse-button currently down?
    rGameState.fRMouseButtonDown = FALSE;   // Is the left mouse-button currently down?
    rGameState.fMoveInProgress = FALSE;     // Is the user in the middle of a move?
    rGameState.fComputerBusy = FALSE;               // Is the computer thinking?
    rGameState.fGameOver = FALSE;                   // Is the game over?
    rGameState.fInitDone = FALSE;                   // Is initialization done?
    rGameState.iPlayerTurn = BLACK;
    rGameState.iCursorState = NORMAL_CURSOR;        // What state is the cursor in?
    rGameState.fMouseResizeInProgress = FALSE;      // Is the user resizing right now?
    rConfig.iSetupPurgeBoards = TRUE;               // Purge boards when exit setup?
    
    CMoves.Init();
    CheckCreate();
    hDC = GetDC(hWnd);
    ClearBoard(b);
    CMoves.NewMove(b, rGameState.iPlayerTurn);
    FillBoard(b, hDC);

    hm = GetMenu(hWnd);
    if (!rConfig.iBoardFlipped)
    {
        CheckMenuItem(hm, IDM_FLIP, MF_CHECKED);
    }

    CheckMenuItem(hm, IDM_BASE_LEVEL + rConfig.rPlayer[RED].iMaxRecursionDepth, MF_CHECKED);

    switch(rConfig.iGameType)
    {
    case GAME_CHECKERS:
        CheckMenuItem(hm, IDM_GAME_CHECKERS, MF_CHECKED);
        CheckMenuItem(hm, IDM_GAME_GIVEAWAY, MF_UNCHECKED);
        break;
    case GAME_GIVEAWAY:
        CheckMenuItem(hm, IDM_GAME_GIVEAWAY, MF_CHECKED);
        CheckMenuItem(hm, IDM_GAME_CHECKERS, MF_UNCHECKED);
        break;
    default:
        // Set to checkers, assert if debug
        CheckMenuItem(hm, IDM_GAME_CHECKERS, MF_CHECKED);
        CheckMenuItem(hm, IDM_GAME_GIVEAWAY, MF_UNCHECKED);
        MessageBox(hWnd, "Game type invalid. Setting to checkers", "Checkers", MB_OK);
        rConfig.iGameType = GAME_CHECKERS;
        break;
    }

    // Load "Piece" cursor.

    curPiece   = LoadCursor(hInst, "PieceCur");
    if (curPiece)
    TraceTag(tagUI, "Cur Piece is valid");
    else
    TraceTag(tagUI, "Cur Piece is invalid");

    return TRUE;

}

VOID vHandle_WM_DESTROY(HWND hWnd)
{
    WriteINI();

    if (pfrm)
    {
        FRM *pfrml; //$FORM
        pfrml = pfrm;
        pfrm = NULL;
        pfrml->ShutdownForm(OLECLOSE_NOSAVE);
        pfrml->Release();
    }

    DeleteObject(hbrBckgrnd);
    DeleteObject(hbrRed);
    DeleteObject(hbrBlue);
    DeleteObject(hbrDkgrey);
    DeleteObject(hpenDkgrey);
    DeleteObject(hBtmaps);

    // WinHelp(hWnd, (LPSTR)szHelpFile, HELP_QUIT, 0L);

    PostQuitMessage(0);
}

VOID vHandle_WM_TIMER(HWND hWnd, UINT id)
{
    #ifdef DEBUG
    static int x=0;
    if (0==x)
    {
    if (!((BLACK == rGameState.iPlayerTurn) ||
      (RED == rGameState.iPlayerTurn))) x++;
    AssertSz(((BLACK == rGameState.iPlayerTurn) || 
          (RED == rGameState.iPlayerTurn)), 
          "Caffeine-Free? What's the point?");
    }
    #endif
    
    if ((rConfig.rPlayer[rGameState.iPlayerTurn].iPlayerType == COMPUTER_PLAYER) &&
        (rGameState.fInitDone) && 
        (!rGameState.fPaused) && 
        (!rGameState.fComputerBusy) &&
        (!rGameState.fGameOver))
    {
    ComputerMove();
    }
}

VOID vHandle_WM_RBUTTONDOWN(HWND hWnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
    AssertSz(!rGameState.fRMouseButtonDown, "David Copperfield with a mouse");
    TraceTag(tagMouse, "in vHandle_WM_RBUTTONDOWN");
    TraceTag(tagMouse, "rGameState.fRMouseButtonDown: %d", rGameState.fRMouseButtonDown);

    if (!rGameState.fLMouseButtonDown)
    {
        SetCapture(hWnd);

        if (rGameState.fSetupMode)
            SetupRButtonDown(hWnd, keyFlags, x, y);
        else
        {
        // No-op.
        }    
    }
    else
    {
    // No-op.
    }
    

}

VOID vHandle_WM_LBUTTONDOWN(HWND hWnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
    AssertSz(!rGameState.fLMouseButtonDown, "How'd you do that?");

    TraceTag(tagMouse, "in vHandle_WM_LBUTTONDOWN");
    TraceTag(tagMouse, "rGameState.fLMouseButtonDown: %d", rGameState.fLMouseButtonDown);
    TraceTag(tagMouse, "rGameState.fRMouseButtonDown: %d", rGameState.fRMouseButtonDown);

    SetCapture(hWnd);

    switch (rGameState.iCursorState)
    {
        case NORMAL_CURSOR:
            TraceTag(tagMouse, "Move LButtonDown");
            if (!rGameState.fRMouseButtonDown)
            {
                SetCapture(hWnd);

                if (rGameState.fSetupMode)
                SetupLButtonDown(hWnd, keyFlags, x, y);
                else
                {
                    AssertSz(((BLACK == rGameState.iPlayerTurn) || 
                        (RED == rGameState.iPlayerTurn)), 
                        "Just how often am I going to check this?");

                    if ((!rGameState.fGameOver) &&
                    (HUMAN_PLAYER == rConfig.rPlayer[rGameState.iPlayerTurn].iPlayerType))
                    NormalLButtonDown(hWnd, keyFlags, x, y);
                }    
            }
            else
            {
                // NO-OP if other button already down
            }
            break;

        case RESIZE_CURSOR:
        {
            TraceTag(tagMouse, "Resize LButtonDown");
            rGameState.fMouseResizeInProgress = TRUE;
        }
    }               // end switch
        
}


VOID vHandle_WM_LBUTTONUP(HWND hWnd, int x, int y, UINT keyFlags)
{
    TraceTag(tagMouse, "in vHandle_WM_LBUTTONUP");

    TraceTag(tagMouse, "rGameState.fLMouseButtonDown: %d", rGameState.fLMouseButtonDown);
    TraceTag(tagMouse, "rGameState.fRMouseButtonDown: %d", rGameState.fRMouseButtonDown);

    ReleaseCapture();
    
    if (rGameState.fMouseResizeInProgress)
    {
        rGameState.fMouseResizeInProgress = FALSE;
    }
    else
    {
        if (rGameState.fSetupMode)
            SetupLButtonUp(hWnd, keyFlags, x, y);
        else
            if (!rGameState.fGameOver)
            NormalLButtonUp(hWnd, keyFlags, x, y);
    }
}

VOID vHandle_WM_RBUTTONUP(HWND hWnd, int x, int y, UINT keyFlags)
{

    TraceTag(tagMouse, "in vHandle_WM_RBUTTONUP");

    TraceTag(tagMouse, "rGameState.fLMouseButtonDown: %d", rGameState.fLMouseButtonDown);
    TraceTag(tagMouse, "rGameState.fRMouseButtonDown: %d", rGameState.fRMouseButtonDown);

    ReleaseCapture();
    if (rGameState.fSetupMode)
    SetupRButtonUp(hWnd, keyFlags, x, y);
    else
    {
    // NO-OP
    }
}

VOID vHandle_WM_MOUSEMOVE(HWND hWnd, int x, int y, UINT keyFlags)
{

    TraceTag(tagMouse, "in vHandle_WM_MOUSEMOVE. Mouse position: x:%d  y:%d", x, y);

    if (rGameState.fRMouseButtonDown)
    {
        // NO-OP
    }
    else
    {
        if (rGameState.fLMouseButtonDown)
        {
            // NO-OP: Should be the actual mouse resize code.
        }
        else
        {
            if (rGameState.fMouseResizeInProgress)
            {
                int iNewBoardSize = 0;
                int iNewSquareSize = 0;
                HDC hDC = 0;
                RECT rectInvalidate;

                TraceTag(tagMouse, "End of mouse resize");
        
                iNewBoardSize = ((x - BOARD_LEFT) + (y - BOARD_TOP)) / 2;
                TraceTag(tagMouse, "iNewBoardSize: %d", iNewBoardSize);

                iNewSquareSize = iNewBoardSize / 8;

                AssertSz(MAX_SQUARE_SIZE >= MIN_SQUARE_SIZE, "Max < Min. Duh.");
        
                if (iNewSquareSize < MIN_SQUARE_SIZE)
                    iNewSquareSize = MIN_SQUARE_SIZE;

                if (iNewSquareSize > MAX_SQUARE_SIZE)
                    iNewSquareSize = MAX_SQUARE_SIZE;

                if (iNewSquareSize != rConfig.iSquareSize)
                {
                    rectInvalidate.left             = BOARD_LEFT;
                    rectInvalidate.right    = BOARD_LEFT + rConfig.iSquareSize*13;
                    rectInvalidate.top              = BOARD_TOP;
                    rectInvalidate.bottom   = BOARD_TOP + rConfig.iSquareSize*8;

                    InvalidateRect(hWnd, &rectInvalidate, TRUE);
                    hDC = GetDC(hWnd);
                    rConfig.iSquareSize = iNewSquareSize;
                CheckGenPieces(hDC);
                    UpdateWindow(hWnd);
                DrawBoard(b);    
                }
                
                SetCursor(curResize);
                TraceTag(tagMouse, "Resize now: x: %d, y: %d", x, y);
            }
            else
            {
                // User is in normal play/setup mode. No mouse down. We want to 
                // change the cursor based on whether we're scanning over pieces
                // or over the "resize" area.

                switch(rGameState.iCursorState)
                {
                    case NORMAL_CURSOR:
                        if ((x > BOARD_LEFT + rConfig.iSquareSize*8 - RESIZE_RANGE) && 
                        (x < BOARD_LEFT + rConfig.iSquareSize*8 + RESIZE_RANGE) &&
                            (y > BOARD_TOP + rConfig.iSquareSize*8 - RESIZE_RANGE) &&
                            (y < BOARD_TOP + rConfig.iSquareSize*8 + RESIZE_RANGE))
                        {
                            TraceTag(tagMouse, "Setting RESIZE_CURSOR");
                            SetCursor(curResize);
                            rGameState.iCursorState = RESIZE_CURSOR;
                        }
                        else
                        {
                            SetCursor(curNormal);
                        }
                        break;
    
                    case RESIZE_CURSOR:
                        if ((x < BOARD_LEFT + rConfig.iSquareSize*8 - RESIZE_RANGE) ||
                        (x > BOARD_LEFT + rConfig.iSquareSize*8 + RESIZE_RANGE) ||
                            (y < BOARD_TOP + rConfig.iSquareSize*8 - RESIZE_RANGE) ||
                            (y > BOARD_TOP + rConfig.iSquareSize*8 + RESIZE_RANGE))
                        {
                            TraceTag(tagMouse, "Setting NORMAL_CURSOR");
                            SetCursor(curNormal);
                            rGameState.iCursorState = NORMAL_CURSOR;
                        }
                        else
                        {
                            SetCursor(curResize);
                        }
                        break;
                    default:
                        AssertSz(FALSE, "Forest AND the trees");
                        break;
                }                                                       // end switch
            }                                                               // end else fMouseResizeInProgress
        }                                                                       // end else fLMouseButtonDown
    }                                                                               // end else fRMouseButtonDown
}

VOID vHandle_WM_PAINT(HWND hWnd)
{
    PAINTSTRUCT ps;

    BeginPaint(hWnd, (LPPAINTSTRUCT)&ps);
    CheckPaint(b, ps.hdc);
    EndPaint(hWnd, (LPPAINTSTRUCT)&ps);
}

VOID vHandle_WM_VSCROLL(HWND hWnd, HWND hWndCtl, UINT code, int pos)
{
    AssertSz(FALSE, "When did I start getting VSCROLL messages?");
}

VOID vHandle_WM_HSCROLL(HWND hWnd, HWND hWndCtl, UINT code, int pos)
{
    AssertSz(FALSE, "When did I start getting HSCROLL messages?");
}

VOID vHandle_WM_GETMINMAXINFO(HWND hWnd, MINMAXINFO FAR * lpMinMaxInfo)
{
    // NO-OP
}

VOID vHandle_WM_COMMAND(HWND hWnd, int wmId, HWND hwndCtl, UINT wmEvent)
{
    // Used by various commands

    FARPROC lpProcDialog = NULL;
    int iDialogBoxResult = -1;
    RECT rectInvalidate;
    HDC hDC = NULL;
    HMENU hm = NULL;

    switch (wmId)
    {
    #ifdef NEVER
    case IDM_FILENEW:
    {
        int iResponse;

        iResponse = MessageBox(hWnd, "You have asked to start " \
        "a new game. Note, this will end your current game. " \
        "Would you like to save your game first?", "New Game?",
        MB_YESNOCANCEL | MB_DEFBUTTON2 | MB_ICONQUESTION);

        switch (iResponse)
        {
        case IDYES:
            SaveAsBoard(b);
            // We mean to fall through to the IDNO case below

        case IDNO:
            ClearBoard(b);
            CMoves.ClearBoards();
                    rGameState.fGameOver = FALSE;
                    rGameState.iPlayerTurn = BLACK;
                    CMoves.NewMove(b, rGameState.iPlayerTurn);
            DrawBoard(b);
            break;

        case IDCANCEL:
                    DrawBoard(b);
            break;
        }
        break;
    }
    #endif //never

    case IDM_SAVE:
        NYI("IDM_SAVE");
        break;

    case IDM_GAME_CHECKERS:
        if (rConfig.iGameType != GAME_CHECKERS)
        {
        hm = GetMenu(hWnd);
        CheckMenuItem(hm, IDM_GAME_CHECKERS, MF_CHECKED);
        CheckMenuItem(hm, IDM_GAME_GIVEAWAY, MF_UNCHECKED);
        rConfig.iGameType = GAME_CHECKERS;
        }
        break;

    case IDM_GAME_GIVEAWAY:
        if (rConfig.iGameType != GAME_GIVEAWAY)
        {
        hm = GetMenu(hWnd);
        CheckMenuItem(hm,IDM_GAME_CHECKERS,MF_UNCHECKED);
        CheckMenuItem(hm,IDM_GAME_GIVEAWAY,MF_CHECKED);
        rConfig.iGameType = GAME_GIVEAWAY;
        }
        break;

    case IDM_SETUP_BOARD:

        SetMenu(hWnd, LoadMenu(hInst, "WCheck_SETUP"));
        rGameState.fSetupMode = TRUE;

            rectInvalidate.left= BOARD_LEFT + rConfig.iSquareSize*10;
            rectInvalidate.right = rectInvalidate.left + rConfig.iSquareSize;
            rectInvalidate.top = BOARD_TOP + rConfig.iSquareSize*2;
            rectInvalidate.bottom = BOARD_TOP + rConfig.iSquareSize*7;
            InvalidateRect(hMainWnd, &rectInvalidate, TRUE);
        
            //$$ () game over state
            break;

    case IDM_SETUP_EXIT:

        lpProcDialog = MakeProcInstance ((FARPROC) PlayerTurnDialogProc, hInst);
        iDialogBoxResult = DialogBox(hInst, "PLAYER_TURN", 
        hWnd, (DLGPROC) lpProcDialog);
        if (iDialogBoxResult != -1)        
            {

            AssertSz((BLACK == iDialogBoxResult) ||
                     (RED == iDialogBoxResult), 
                     "Darn tootin!");
        
        SetMenu(hWnd, LoadMenu(hInst, "WCheck_NORMAL"));
                rGameState.iPlayerTurn = iDialogBoxResult;
        rGameState.fSetupMode = FALSE;
                rectInvalidate.left= BOARD_LEFT + rConfig.iSquareSize*10;
                rectInvalidate.right = rectInvalidate.left + rConfig.iSquareSize;
                rectInvalidate.top = BOARD_TOP + rConfig.iSquareSize*2;
                rectInvalidate.bottom = BOARD_TOP + rConfig.iSquareSize*7;
                InvalidateRect(hMainWnd, &rectInvalidate, TRUE);
                if (rConfig.iSetupPurgeBoards)
                    CMoves.ClearBoards();
                else
                    CMoves.PurgeBoards();
                CMoves.NewMove(b, rGameState.iPlayerTurn);
        }
        break;

    case IDM_PLAYERS:
        lpProcDialog = MakeProcInstance ((FARPROC) PlayersDialogProc, hInst);
        DialogBox (hInst, "PLAYERS", hWnd, (DLGPROC) lpProcDialog);
        FreeProcInstance (lpProcDialog);
        break;

    case IDM_BACK:
        {
        // Change menu to say "Continue"
        rGameState.fPaused = TRUE;
                rGameState.fGameOver = FALSE;

                // $$ () game over state

        TraceTag(tagUI, "Calling CMoves.BackMove(b)");
        if (FALSE == CMoves.BackMove(b, &rGameState.iPlayerTurn))
                {
                    TraceTag(tagUI, "BEEP: Can't back up.");
            MessageBeep(MB_OK);
                }
        else
            DrawBoard(b);
        }
        break;

    case IDM_FORWARD:
    {
        // Change menu to say "Continue"
        rGameState.fPaused = TRUE;

            // $$ () game over state
        TraceTag(tagUI, "Calling CMoves.ForwardMove(b)");
        if (FALSE == CMoves.ForwardMove(b, &rGameState.iPlayerTurn))
            {
                TraceTag(tagUI, "BEEP: Can't go forward.");
                MessageBeep(MB_OK);
            }
        else
        DrawBoard(b);
    }
    break;

        case IDM_FLIP:
            hm = GetMenu(hWnd);
            if (FALSE == rConfig.iBoardFlipped)
            {
                rConfig.iBoardFlipped = TRUE;
                CheckMenuItem(hm, IDM_FLIP, MF_UNCHECKED);
            }
            else
            {
                rConfig.iBoardFlipped = FALSE;
                CheckMenuItem(hm, IDM_FLIP, MF_CHECKED);
            }

            DrawBoard(b);
            break;

        case IDM_CONTINUE:

        rGameState.fPaused = FALSE;
        CMoves.PurgeBoards();

            // $$ () game over state

        AssertSz(((BLACK == rGameState.iPlayerTurn) || 
                (RED == rGameState.iPlayerTurn)), 
                "Who flicked that?");

        if (COMPUTER_PLAYER == rConfig.rPlayer[rGameState.iPlayerTurn].iPlayerType)
        {
        ComputerMove();
        }
        break;

        case IDM_SETDRAWMOVES:
        lpProcDialog = MakeProcInstance ((FARPROC) DebugConfigDialogProc, hInst);
        DialogBox (hInst, "DEBUG_CONFIG", hWnd, (DLGPROC) lpProcDialog);
        FreeProcInstance (lpProcDialog);
            break;


    case IDM_BASE_LEVEL:
    case IDM_BASE_LEVEL + 1:
    case IDM_BASE_LEVEL + 2:
    case IDM_BASE_LEVEL + 3:
    case IDM_BASE_LEVEL + 4:
    case IDM_BASE_LEVEL + 5:
    case IDM_BASE_LEVEL + 6:
    case IDM_BASE_LEVEL + 7:
    case IDM_BASE_LEVEL + 8:
    case IDM_BASE_LEVEL + 9:
    case IDM_BASE_LEVEL + 10:
    case IDM_BASE_LEVEL + 11:
    case IDM_BASE_LEVEL + 12:
    case IDM_BASE_LEVEL + 13:
    case IDM_BASE_LEVEL + 14:
    case IDM_BASE_LEVEL + 15:
    case IDM_BASE_LEVEL + 16:
    case IDM_BASE_LEVEL + 17:
    case IDM_BASE_LEVEL + 18:
    case IDM_BASE_LEVEL + 19:
    case IDM_BASE_LEVEL + 20:
        HMENU hm;
        int i;

        hm = GetMenu(hWnd);
        i=20;
        for (;i;i--)
            CheckMenuItem(hm, IDM_BASE_LEVEL + i, MF_UNCHECKED);
        CheckMenuItem(hm, wmId, MF_CHECKED);
        rConfig.rPlayer[BLACK].iMaxRecursionDepth =
            rConfig.rPlayer[RED].iMaxRecursionDepth = wmId - IDM_BASE_LEVEL;
        break;

    case IDM_HINT:
        {
        SQUARE      db[SQRS_MAX];
        int i;

        SetCursor(curThink);
        CopyBoard(b,db);
        PlayBestMove(db, rGameState.iPlayerTurn, 0, 0,
            (int)rConfig.rPlayer[rGameState.iPlayerTurn].lAlphaPruningOriginalDepth,    /* prune depth */
            (int)rConfig.rPlayer[rGameState.iPlayerTurn].lAlphaPruningWidth,    /* prune size */
            (int)rConfig.rPlayer[rGameState.iPlayerTurn].iMaxRecursionDepth   /* max depth */
            );
        SetCursor(curNormal);
        for (i=0; i<3; ++i)
        {
        #define WAIT_TICKS 250
        #ifndef _WIN32
        DWORD startTick;
        #endif
        DrawBoard(db);
        #ifdef _WIN32
        Sleep(WAIT_TICKS);
        #else
        startTick = GetTickCount() + WAIT_TICKS;
        while (GetTickCount() < startTick) /* do nothing */;
        #endif
        DrawBoard(b);
        #ifdef _WIN32
        Sleep(WAIT_TICKS);
        #else
        startTick = GetTickCount() + WAIT_TICKS;
        while (GetTickCount() < startTick) /* do nothing */;
        #endif
        }

        
        }
        break;

    case IDM_ADDRESS:
        if (pfrm) // $ FORM
        pfrm->AddressForm(hWnd,(BOOL) wmEvent);
        else
        MessageBeep(MB_OK);
        break;

        case IDM_ABOUT:
            
            lpProcDialog = MakeProcInstance((FARPROC)About, hInst);

            DialogBox(hInst,           // current instance
                "AboutBox",            // dlg resource to use
                hWnd,                  // parent handle
                (DLGPROC)lpProcDialog); // About() instance address

            FreeProcInstance(lpProcDialog);
            break;

        case IDM_EXIT:
            DestroyWindow (hWnd);
            break;
    }
}

/****************************************************************************
*****************************************************************************
*****************************************************************************
****************************************************************************/

LRESULT CALLBACK CheckersWndProc(
        HWND hWnd,         // window handle
        UINT message,      // type of message
        WPARAM wParam,     // additional information
        LPARAM lParam)     // additional information

{
    switch (message)
    {
    HANDLE_MSG(hWnd, WM_CREATE, fHandle_WM_CREATE);
        HANDLE_MSG(hWnd, WM_INITMENU, vHandle_WM_INITMENU);
        HANDLE_MSG(hWnd, WM_DESTROY, vHandle_WM_DESTROY);
        HANDLE_MSG(hWnd, WM_TIMER, vHandle_WM_TIMER);
        HANDLE_MSG(hWnd, WM_LBUTTONDOWN, vHandle_WM_LBUTTONDOWN);
        HANDLE_MSG(hWnd, WM_LBUTTONUP, vHandle_WM_LBUTTONUP);
        HANDLE_MSG(hWnd, WM_RBUTTONDOWN, vHandle_WM_RBUTTONDOWN);
        HANDLE_MSG(hWnd, WM_RBUTTONUP, vHandle_WM_RBUTTONUP);
        HANDLE_MSG(hWnd, WM_MOUSEMOVE, vHandle_WM_MOUSEMOVE);
        HANDLE_MSG(hWnd, WM_PAINT, vHandle_WM_PAINT);
        HANDLE_MSG(hWnd, WM_VSCROLL, vHandle_WM_VSCROLL);
        HANDLE_MSG(hWnd, WM_HSCROLL, vHandle_WM_HSCROLL);
        HANDLE_MSG(hWnd, WM_GETMINMAXINFO, vHandle_WM_GETMINMAXINFO);
        HANDLE_MSG(hWnd, WM_COMMAND, vHandle_WM_COMMAND);

        case EM_GIVEFORMTOHWND:

        ShowWindow(hWnd, SW_SHOWNORMAL);

        // ----- params valid
        AssertSz(NULL == pfrm,"two forms?");
        AssertSz(lParam,"no forms?");
        pfrm = (FRM*) lParam;
        TraceTag(tagForm,"wcheck pfrm->AddRef");
        pfrm->AddRef();
        Assert(pfrm->pMessage);

        pfrm->GetCheckersData(b,&rGameState.iPlayerTurn,NULL,NULL);
        AssertSz(rGameState.iPlayerTurn == RED || rGameState.iPlayerTurn == BLACK,"cool: neither red or blacks turn according to mapi");
        rConfig.iBoardFlipped = 1;
        if (RED == rGameState.iPlayerTurn)
        rConfig.iBoardFlipped = 0;
        rGameState.fPaused = FALSE;


        DrawBoard(b);

        break;

        case WM_OTHERINIT:

        if (!rGameState.fPlayAsForm)
        {
        if (COMPUTER_PLAYER == rConfig.rPlayer[PLAYER1].iPlayerType)
            {
            MessageBox(hWnd, "Computer is configured to move first. The " \
            "game will start out paused. Select 'Continue' from the " \
            "main menu to start.", "Checkers", MB_OK);
            rGameState.fPaused = TRUE;
            }
        }
        else
        {
        rGameState.fPaused = TRUE;
        }
            rGameState.fInitDone = TRUE;
        break;

    case WM_CLOSE:
        if (pfrm)
        {
        FRM *pfrml; //$FORM
        pfrml = pfrm;
        pfrm = NULL;
        pfrml->ShutdownForm(OLECLOSE_NOSAVE);
        pfrml->Release();
        }
        return(DefWindowProc(hWnd, message, wParam, lParam));

        default:          // Passes it on if unproccessed
            return (DefWindowProc(hWnd, message, wParam, lParam));
    }
    return (0);
}

/****************************************************************************
*****************************************************************************
*****************************************************************************
****************************************************************************/

long WINAPI ComputerMove()
{
    int iGameState = GAME_PLAYABLE;
    
    rGameState.fComputerBusy = TRUE;
    rGameState.fGameInProgress = TRUE;

    TraceTag(tagUI, "Calling PlayBestMove()");
    SetCursor(curThink);

    AssertSz(((BLACK == rGameState.iPlayerTurn) || 
              (RED == rGameState.iPlayerTurn)), 
              "This one says x!");

        PlayBestMove(b, rGameState.iPlayerTurn, 0, 0,
        (int)rConfig.rPlayer[rGameState.iPlayerTurn].lAlphaPruningOriginalDepth,    /* prune depth */
        (int)rConfig.rPlayer[rGameState.iPlayerTurn].lAlphaPruningWidth,    /* prune size */
        (int)rConfig.rPlayer[rGameState.iPlayerTurn].iMaxRecursionDepth   /* max depth */
        );
        
    SetCursor(curNormal);
    TraceTag(tagUI, "Done with PlayBestMove()");
    DrawBoard(b);

    if (rGameState.iPlayerTurn == BLACK)
    rGameState.iPlayerTurn = RED;
    else
    rGameState.iPlayerTurn = BLACK;

    CMoves.NewMove(b, rGameState.iPlayerTurn);

    iGameState = GameOver(b, rGameState.iPlayerTurn);
    switch (iGameState)
    {
    case GAME_WON:
            rGameState.fGameOver = TRUE;
            DisplayGameOver(hMainWnd, rGameState.iPlayerTurn);
        break;
        case GAME_DRAWN:
        rGameState.fGameOver = TRUE;
        DisplayGameDrawn(hMainWnd, rGameState.iPlayerTurn);
            break;            
        case GAME_PLAYABLE:
        OnGamePlayableAfterMove();
            break;         
        default:
            AssertSz(FALSE, "STILL dead");                     
    }

    rGameState.fComputerBusy = FALSE;
    
    return(0);
    
}

/****************************************************************************
*****************************************************************************
*****************************************************************************
****************************************************************************/

void inline SetupLButtonDown(HWND hWnd, UINT keyFlags, int x, int y)
{
    int iSX = 0;
    int iSY = 0;

    (pntStart).x = x;
    (pntStart).y = y;

    vTranslateCurPosToSquare(pntStart, &iSX, &iSY);

    if (fValidSetupPiece(b, iSX, iSY))
    {
    HDC hDC;

    SetCursor(curPiece);
    hDC = GetDC(hWnd);
    AssertSz((iSX >= 0) && ((iSX <= 7) || (iSX == 10)), "iSX out of range on ButtonDown");
    AssertSz((iSY >= 0) && (iSY <= 7), "iSY out of range on ButtonDown");
        if ((iSX != 10) && (!(GetKeyState(VK_CONTROL) & 0x8000)))
            vClearMovingPiece(hDC, iSX, iSY);
    rGameState.fMoveInProgress = TRUE;
    }
    else
    {
        TraceTag(tagUI, "BEEP: Not a valid setup piece");
    MessageBeep(MB_OK);
    rGameState.fMoveInProgress = FALSE;
    }
    rGameState.fLMouseButtonDown = TRUE;
    TraceTag(tagMouse, "rGameState.fLMouseButtonDown: %d", rGameState.fLMouseButtonDown);
    
}

void inline SetupRButtonDown(HWND hWnd, UINT keyFlags, int x, int y)
{
    int iSX = 0;
    int iSY = 0;

    TraceTag(tagMouse, "in SetupRButtonDown()");

    (pntStart).x = x;
    (pntStart).y = y;

    vTranslateCurPosToSquare(pntStart, &iSX, &iSY);

    if (fValidSetupPiece(b, iSX, iSY))
    {
    HDC hDC;

    SetCursor(curPiece);
    hDC = GetDC(hWnd);
    AssertSz((iSX >= 0) && ((iSX <= 7) || (iSX == 10)), "iSX out of range on ButtonDown");
    AssertSz((iSY >= 0) && (iSY <= 7), "iSY out of range on ButtonDown");
        vClearMovingPiece(hDC, iSX, iSY);
    rGameState.fMoveInProgress = TRUE;
    }
    else
    {
        TraceTag(tagUI, "BEEP: Not a valid setup piece (in RButtonDown)");
    MessageBeep(MB_OK);
    rGameState.fMoveInProgress = FALSE;
    }
    rGameState.fRMouseButtonDown = TRUE;
    TraceTag(tagMouse, "rGameState.fRMouseButtonDown: %d", rGameState.fRMouseButtonDown);
    
}

void inline NormalLButtonDown(HWND hWnd, UINT keyFlags, int x, int y)
{
    int iSX = 0;
    int iSY = 0;

    AssertSz((rGameState.iPlayerTurn == RED) ||
       (rGameState.iPlayerTurn == BLACK), "Player turn is bogus.");

    TraceTag(tagMouse, "in NormalLButtonDown()");

    if ((HUMAN_PLAYER == rConfig.rPlayer[rGameState.iPlayerTurn].iPlayerType) && 
    (!rGameState.fPaused))
    {
    TraceTag(tagUI, "Button down at x:%d - y:%d", x, y);
    (pntStart).x = x;
    (pntStart).y = y;

    vTranslateCurPosToSquare(pntStart, &iSX, &iSY);
    if (fValidPlayerPiece(b, iSX, iSY))
    {
        HDC hDC;

        SetCursor(curPiece);
        hDC = GetDC(hWnd);
        AssertSz((iSX >= 0) && (iSX <= 7), "iSX out of range on ButtonDown");
        AssertSz((iSY >= 0) && (iSY <= 7), "iSY out of range on ButtonDown");
        vClearMovingPiece(hDC, iSX, iSY);
        rGameState.fMoveInProgress = TRUE;
    }
    else
    {
            TraceTag(tagUI, "BEEP: Not a valid piece in LButtonDown");
        MessageBeep(MB_OK);
        rGameState.fMoveInProgress = FALSE;
    }
    }
    else
    {
        TraceTag(tagUI, "BEEP: Wrong player in LButtonDown");
    MessageBeep(MB_OK);
    }

    rGameState.fLMouseButtonDown = TRUE;
    TraceTag(tagMouse, "rGameState.fLMouseButtonDown: %d", rGameState.fLMouseButtonDown);
    
}

void inline SetupLButtonUp(HWND hWnd, WPARAM uParam, int x, int y)
{

    TraceTag(tagMouse, "in SetupLButtonUp()");

    if (rGameState.fMoveInProgress)
    {
    int     iEngineStart=0;
    int     iEngineEnd=0;
    int     iSX = 0;
    int     iSY = 0;
    int     iEX = 0;
    int     iEY = 0;
    BOOL    fRackSelect = FALSE;
        POINT   pntEnd;

    SetCursor(curNormal);

    rGameState.fLMouseButtonDown = FALSE;
    pntEnd.x = x;
    pntEnd.y = y;
    
    vTranslateCurPosToSquare(pntStart, &iSX, &iSY);
        if ((iSX == 10) && (iSY >=2) && (iSY <= 6))
            fRackSelect = TRUE;
        else
        {
            fRackSelect = FALSE;
            vTranslateUIToEngineSquare(&iEngineStart, iSX, iSY);
        }

    vTranslateCurPosToSquare(pntEnd, &iEX, &iEY);
    vTranslateUIToEngineSquare(&iEngineEnd, iEX, iEY);

    TraceTag(tagUI, "Button up at x:%d - y:%d", pntEnd.x, pntEnd.y);

        if (iEngineStart != iEngineEnd)
        {
        if ((iEngineEnd != -1) && (iEngineStart != -1) && (!fRackSelect))
        {
            TraceTag(tagUI, "St: %d * End: %d", iEngineStart, iEngineEnd);

            AssertSz(!fRackSelect, "Trains, Planes, and Automobiles");
            AssertSz(iEngineEnd < SQRS_MAX,"what could be a train");
            AssertSz(iEngineEnd > 0,"what could be trains");
            AssertSz(iEngineStart < SQRS_MAX,"two what could be a train");
            AssertSz(iEngineStart > 0,"two what could be trains");

                b[iEngineEnd] = b[iEngineStart];

            // If high-order bit is set, the control key is down, and I should
            // do a copy (not remove the source piece).

            if (!(GetKeyState(VK_CONTROL) & 0x8000))
                b[iEngineStart] = EMPTY;

            
        }
            else
            {
            AssertSz(iEngineEnd < SQRS_MAX,"while (TRUE) fork();");
            AssertSz((iEngineEnd > 0) || (-1 == iEngineEnd),"while (TRUE) spoon();");
            
                if ((iEngineEnd != -1) && (fRackSelect))
                {
                    switch(iSY)
                    {
                        case 2:
                            b[iEngineEnd] = RED;
                            break;
                        case 3:
                            b[iEngineEnd] = BLACK;
                            break;
                        case 4:
                            b[iEngineEnd] = RED | KING;
                            break;
                        case 5:
                            b[iEngineEnd] = BLACK | KING;
                            break;
                        case 6:
                            b[iEngineEnd] = EMPTY;
                            break;
                        default:
                            AssertSz(FALSE, "Phenylketonurics: Contains Phenylalanine");
                            break;
                    }
                }
        }
    }
    else
    {
        // This is what happens if we picked up a piece and dropped it on
        // the same square. Right now this is a no-op.
    }
                                                          
    DrawBoard(b);
    }

    rGameState.fLMouseButtonDown = FALSE;
    TraceTag(tagMouse, "rGameState.fLMouseButtonDown: %d", rGameState.fLMouseButtonDown);
    
}

void inline SetupRButtonUp(HWND hWnd, WPARAM uParam, int x, int y)
{

    TraceTag(tagMouse, "in SetupRButtonUp()");

    if (rGameState.fMoveInProgress)
    {
    int     iEngineStart=0;
    int     iEngineEnd=0;  
    int     iSX = 0;
    int     iSY = 0;
    int     iEX = 0;
    int     iEY = 0;
    BOOL    fRackSelect = FALSE;
        POINT   pntEnd;

    SetCursor(curNormal);

    rGameState.fRMouseButtonDown = FALSE;
    pntEnd.x = x;
    pntEnd.y = y;
    
    vTranslateCurPosToSquare(pntStart, &iSX, &iSY);
        if ((iSX == 10) && (iSY >=2) && (iSY <= 6))
            fRackSelect = TRUE;
        else
        {
            fRackSelect = FALSE;
            vTranslateUIToEngineSquare(&iEngineStart, iSX, iSY);
        }

    vTranslateCurPosToSquare(pntEnd, &iEX, &iEY);
    vTranslateUIToEngineSquare(&iEngineEnd, iEX, iEY);

    TraceTag(tagUI, "Button up at x:%d - y:%d", pntEnd.x, pntEnd.y);

        if (iEngineStart == iEngineEnd)
        {
        if ((iEngineStart != -1) && (!fRackSelect))
        {
            TraceTag(tagUI, "St: %d * End: %d", iEngineStart, iEngineEnd);

            AssertSz(!fRackSelect, "Trains, Planes, and Automobiles");
            AssertSz(iEngineEnd < SQRS_MAX,"what could be a train");
            AssertSz(iEngineEnd > 0,"what could be trains");
            AssertSz(iEngineStart < SQRS_MAX,"two what could be a train");
            AssertSz(iEngineStart > 0,"two what could be trains");

                b[iEngineStart] = EMPTY;
        }
    }
    else
    {
        // This is what happens if we clicked on a piece but moved off of the
        // original square.. Right now this is a no-op.
    }
                                                          
    DrawBoard(b);
    }
    
    rGameState.fRMouseButtonDown = FALSE;
    TraceTag(tagMouse, "rGameState.fRMouseButtonDown: %d", rGameState.fRMouseButtonDown);

}


void inline NormalLButtonUp(HWND hWnd, WPARAM uParam, int x, int y)
{
    int iGameState = GAME_PLAYABLE;

    TraceTag(tagMouse, "in NormalLButtonUp()");

    if (rGameState.fMoveInProgress)
    {
    int     iEngineStart;                      
    int     iEngineEnd;
    int     iValid = 0;    // Valid move
    int     iSX = 0;
    int     iSY = 0;
    int     iEX = 0;
    int     iEY = 0;
    POINT   pntEnd;

    SetCursor(curNormal);

    rGameState.fLMouseButtonDown = FALSE;
    pntEnd.x = x;
    pntEnd.y = y;
    
    vTranslateCurPosToSquare(pntStart, &iSX, &iSY);
    vTranslateUIToEngineSquare(&iEngineStart, iSX, iSY);
    vTranslateCurPosToSquare(pntEnd, &iEX, &iEY);
    vTranslateUIToEngineSquare(&iEngineEnd, iEX, iEY);

    TraceTag(tagUI, "Button up at x:%d - y:%d", pntEnd.x, pntEnd.y);

    if ((iEngineEnd != -1) && (iEngineStart != -1))
    {
        TraceTag(tagUI, "St: %d * End: %d", iEngineStart, iEngineEnd);

        AssertSz(((BLACK == rGameState.iPlayerTurn) || 
              (RED == rGameState.iPlayerTurn)), "Fronk, lots!");
              
        if (HUMAN_PLAYER == rConfig.rPlayer[rGameState.iPlayerTurn].iPlayerType)
        {
        AssertSz(iEngineEnd < SQRS_MAX,"ugly players what could be a train");
        AssertSz(iEngineEnd >= 0,"ugly players what could be trains");
        AssertSz(iEngineStart < SQRS_MAX,"ugly players two what could be a train");
        AssertSz(iEngineStart >= 0,"ugly players two what could be trains");
        iValid = MoveValid(b, iEngineStart, iEngineEnd, rGameState.iPlayerTurn);
        }
    }
    else
        iValid = -1;

    DrawBoard(b);

        if (iValid == 1)
        {
        if (rGameState.iPlayerTurn == BLACK)
            rGameState.iPlayerTurn = RED;
        else
            rGameState.iPlayerTurn = BLACK;
    
        CMoves.NewMove(b, rGameState.iPlayerTurn);
            iGameState = GameOver(b, rGameState.iPlayerTurn);
            switch (iGameState)
            {
            case GAME_WON:
                    rGameState.fGameOver = TRUE;
                    DisplayGameOver(hMainWnd, rGameState.iPlayerTurn);
                break;
                case GAME_DRAWN:
                rGameState.fGameOver = TRUE;
                DisplayGameDrawn(hMainWnd, rGameState.iPlayerTurn);
                    break;            
                case GAME_PLAYABLE:
            OnGamePlayableAfterMove();
                    break;         
                default:
                    AssertSz(FALSE, "very dead");                      
            }
        }
    }
    rGameState.fMoveInProgress = FALSE;
    rGameState.fLMouseButtonDown = FALSE;
    TraceTag(tagMouse, "rGameState.fLMouseButtonDown: %d", rGameState.fLMouseButtonDown);
    
}

/****************************************************************************
*****************************************************************************
*****************************************************************************
****************************************************************************/

BOOL CenterWindow (HWND hwndChild, HWND hwndParent)
{
    RECT    rChild, rParent;
    int     wChild, hChild, wParent, hParent;
    int     wScreen, hScreen, xNew, yNew;
    HDC     hdc;

    // Get the Height and Width of the child window
    GetWindowRect (hwndChild, &rChild);
    wChild = rChild.right - rChild.left;
    hChild = rChild.bottom - rChild.top;

    // Get the Height and Width of the parent window
    GetWindowRect (hwndParent, &rParent);
    wParent = rParent.right - rParent.left;
    hParent = rParent.bottom - rParent.top;

    // Get the display limits
    hdc = GetDC (hwndChild);
    wScreen = GetDeviceCaps (hdc, HORZRES);
    hScreen = GetDeviceCaps (hdc, VERTRES);
    ReleaseDC (hwndChild, hdc);

    // Calculate new X position, then adjust for screen
    xNew = rParent.left + ((wParent - wChild) /2);
    if (xNew < 0) {
        xNew = 0;
    } else if ((xNew+wChild) > wScreen) {
        xNew = wScreen - wChild;
    }

    // Calculate new Y position, then adjust for screen
    yNew = rParent.top  + ((hParent - hChild) /2);
    if (yNew < 0) {
        yNew = 0;
    } else if ((yNew+hChild) > hScreen) {
        yNew = hScreen - hChild;
    }

    // Set it, and return
    return SetWindowPos (hwndChild, NULL,
        xNew, yNew, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

/****************************************************************************
*****************************************************************************
*****************************************************************************
****************************************************************************/

BOOL FAR PASCAL ComputerSettingsDialogProc (HWND hDlg,
                    WORD wMsgID,
                    WPARAM wParam,
                    LPARAM lParam)
{
    static struct rPlayerRec *prPlayer;

    switch (wMsgID)

    {
    case WM_INITDIALOG:
        prPlayer = (struct rPlayerRec FAR *) lParam;
        Assert(prPlayer);
        SendDlgItemMessage(hDlg, IDCB_USE_OPENING_BOOK, BM_SETCHECK, prPlayer->iUseOpeningBook, 0L);
        SendDlgItemMessage(hDlg, IDCB_USE_MEM_POSITIONS, BM_SETCHECK, prPlayer->iMemPositions, 0L);
        SendDlgItemMessage(hDlg, IDCB_USE_MOVE_THEORY, BM_SETCHECK, prPlayer->iUseMoveTheory, 0L);
        SendDlgItemMessage(hDlg, IDCB_MOVE_SHUFFLING, BM_SETCHECK, prPlayer->iUseMoveShuffling, 0L);
        SendDlgItemMessage(hDlg, IDCB_GOOD_MOVE_SKIPPING, BM_SETCHECK, (int)prPlayer->lUseGoodMoveSkipping, 0L);
        SendDlgItemMessage(hDlg, IDCB_EQUAL_MOVE_SKIPPING, BM_SETCHECK, prPlayer->iUseEqualMoveSkipping, 0L);
        SendDlgItemMessage(hDlg, IDCB_ALPHA_BETA_PRUNING, BM_SETCHECK, prPlayer->iUseAlphaBetaPruning, 0L);

        // Set other edit controls

        SetDlgItemLong(hDlg, IDEC_RECURSION_DEPTH, prPlayer->iMaxRecursionDepth);
            SetDlgItemLong(hDlg, IDEC_PRUNING_DEPTH, prPlayer->lAlphaPruningOriginalDepth);
            SetDlgItemLong(hDlg, IDEC_PRUNING_WIDTH, prPlayer->lAlphaPruningWidth);
        return TRUE;

    case WM_COMMAND:
        switch (wParam)
        {
        case IDOK:
            EndDialog (hDlg, TRUE);
            
            // Get Checkbox values
            prPlayer->iUseOpeningBook = (int)SendDlgItemMessage(hDlg, IDCB_USE_OPENING_BOOK, BM_GETCHECK, 0, 0L);
            prPlayer->iMemPositions = (int)SendDlgItemMessage(hDlg, IDCB_USE_MEM_POSITIONS, BM_GETCHECK, 0, 0L);
            prPlayer->iUseMoveTheory = (int)SendDlgItemMessage(hDlg, IDCB_USE_MOVE_THEORY, BM_GETCHECK, 0, 0L);
            prPlayer->iUseMoveShuffling = (int)SendDlgItemMessage(hDlg, IDCB_MOVE_SHUFFLING, BM_GETCHECK, 0, 0L);
            prPlayer->lUseGoodMoveSkipping = (int)SendDlgItemMessage(hDlg, IDCB_GOOD_MOVE_SKIPPING, BM_GETCHECK, 0, 0L);
            prPlayer->iUseEqualMoveSkipping = (int)SendDlgItemMessage(hDlg, IDCB_EQUAL_MOVE_SKIPPING, BM_GETCHECK, 0, 0L);
            prPlayer->iUseAlphaBetaPruning = (int)SendDlgItemMessage(hDlg, IDCB_ALPHA_BETA_PRUNING, BM_GETCHECK, 0, 0L);
            prPlayer->iMemPositions = (int)SendDlgItemMessage(hDlg, IDCB_USE_MEM_POSITIONS, BM_GETCHECK, 0, 0L);

            // Get Edit Control Values

            prPlayer->iMaxRecursionDepth         = GetDlgItemInt(hDlg, IDEC_RECURSION_DEPTH);
                    prPlayer->lAlphaPruningOriginalDepth = GetDlgItemLong(hDlg, IDEC_PRUNING_DEPTH);
                    prPlayer->lAlphaPruningWidth         = GetDlgItemLong(hDlg, IDEC_PRUNING_WIDTH);

            return TRUE;

        case IDCANCEL:
            EndDialog (hDlg, TRUE);
            return TRUE;
        }                                    // end switch
        break;
    }
    return FALSE;
}

BOOL FAR PASCAL PlayersDialogProc (HWND hDlg,
                    WORD wMsgID,
                    WPARAM wParam,
                    LPARAM lParam)
{
    switch (wMsgID)

    {
    case WM_INITDIALOG:
        switch(rConfig.rPlayer[PLAYER1].iPlayerType)
        {
        case HUMAN_PLAYER:
            SendDlgItemMessage(hDlg, IDRB_P1_HUMAN, BM_SETCHECK, 1, 0L);
            break;
        case COMPUTER_PLAYER:
            SendDlgItemMessage(hDlg, IDRB_P1_COMPUTER, BM_SETCHECK, 1, 0L);
            break;
        case NETWORK_PLAYER:
            SendDlgItemMessage(hDlg, IDRB_P1_NETWORK, BM_SETCHECK, 1, 0L);
            break;
        default:
            AssertSz(FALSE, "rConfig.rPlayer[PLAYER1].iPlayerType not valid");
            break;
        }
        
        switch(rConfig.rPlayer[PLAYER2].iPlayerType)
        {
        case HUMAN_PLAYER:
            SendDlgItemMessage(hDlg, IDRB_P2_HUMAN, BM_SETCHECK, 1, 0L);
            break;
        case COMPUTER_PLAYER:
            SendDlgItemMessage(hDlg, IDRB_P2_COMPUTER, BM_SETCHECK, 1, 0L);
            break;
        case NETWORK_PLAYER:
            SendDlgItemMessage(hDlg, IDRB_P2_NETWORK, BM_SETCHECK, 1, 0L);
            break;
        default:
            AssertSz(FALSE, "rConfig.rPlayer[PLAYER2].iPlayerType not valid");
            break;
        }

        return TRUE;

    case WM_COMMAND:
        switch (wParam)
        {
        case IDB_P1_COMPUTER_SETUP:

            DialogBoxParam (hInst,       // current instance
                    "COMPUTER_SETUP_MASTER", // dlg resource to use
                    hDlg,        // parent handle
                    (DLGPROC)ComputerSettingsDialogProc, // Config() instance address
                    (LPARAM) (struct rPlayerRec *) (&(rConfig.rPlayer[PLAYER1])));
            break;

        case IDB_P2_COMPUTER_SETUP:

            DialogBoxParam (hInst,       // current instance
                    "COMPUTER_SETUP_MASTER", // dlg resource to use
                    hDlg,        // parent handle
                    (DLGPROC)ComputerSettingsDialogProc, // Config() instance address
                    (LPARAM) (struct rPlayerRec *) (&(rConfig.rPlayer[PLAYER2])));
            break;
        
        case IDB_P1_NETWORK_SETUP:
        case IDB_P2_NETWORK_SETUP:
            NYI("Player Network Setup");
            break;

        case IDOK:
            EndDialog (hDlg, TRUE);
            if (SendDlgItemMessage(hDlg, IDRB_P1_HUMAN, BM_GETCHECK, 0, 0L))
            rConfig.rPlayer[PLAYER1].iPlayerType = HUMAN_PLAYER;
            if (SendDlgItemMessage(hDlg, IDRB_P1_COMPUTER, BM_GETCHECK, 0, 0L))
            rConfig.rPlayer[PLAYER1].iPlayerType = COMPUTER_PLAYER;
            if (SendDlgItemMessage(hDlg, IDRB_P1_NETWORK, BM_GETCHECK, 0, 0L))
            rConfig.rPlayer[PLAYER1].iPlayerType = NETWORK_PLAYER;
            if (SendDlgItemMessage(hDlg, IDRB_P2_HUMAN, BM_GETCHECK, 0, 0L))
            rConfig.rPlayer[PLAYER2].iPlayerType = HUMAN_PLAYER;
            if (SendDlgItemMessage(hDlg, IDRB_P2_COMPUTER, BM_GETCHECK, 0, 0L))
            rConfig.rPlayer[PLAYER2].iPlayerType = COMPUTER_PLAYER;
            if (SendDlgItemMessage(hDlg, IDRB_P2_NETWORK, BM_GETCHECK, 0, 0L))
            rConfig.rPlayer[PLAYER2].iPlayerType = NETWORK_PLAYER;
            return TRUE;

        case IDCANCEL:
            EndDialog (hDlg, TRUE);
            return TRUE;
        }                                    // end switch
        break;
    }
    return FALSE;
}


BOOL FAR PASCAL DebugConfigDialogProc (HWND hDlg,
                    WORD wMsgID,
                    WPARAM wParam,
                    LPARAM lParam)
{
    switch (wMsgID)

    {
    case WM_INITDIALOG:
        SetDlgItemInt(hDlg, IDEC_MAX_MOVES, rConfig.iMaxMoves);
        return TRUE;

    case WM_COMMAND:
        switch (wParam)
        {
        case IDOK:
            EndDialog (hDlg, TRUE);
            rConfig.iMaxMoves = GetDlgItemInt(hDlg, IDEC_MAX_MOVES);
            return TRUE;

        case IDCANCEL:
            EndDialog (hDlg, TRUE);
            return TRUE;
        }                                    // end switch
        break;
    }
    return FALSE;
}


int FAR PASCAL PlayerTurnDialogProc (HWND hDlg,
                    WORD wMsgID,
                    WPARAM wParam,
                    LPARAM lParam)
{
    switch (wMsgID)

    {
    case WM_INITDIALOG:
            CenterWindow (hDlg, GetWindow (hDlg, GW_OWNER));
        return TRUE;

    case WM_COMMAND:
        switch (wParam)
        {
        case IDB_PLAYER1:
            EndDialog (hDlg, PLAYER1);
            return TRUE;

        case IDB_PLAYER2:
            EndDialog (hDlg, PLAYER2);
            return TRUE;
        
        case IDCANCEL:
            // Return -1 so the calling function will know that the result
            // from the dialog call isn't equal to a player ID.
            
            EndDialog (hDlg, -1);
            break;    
        }                                    // end switch
        break;
    }
    return FALSE;
}


LRESULT CALLBACK About(
        HWND hDlg,           // window handle of the dialog box
        UINT message,        // type of message
        WPARAM wParam,       // message-specific information
        LPARAM lParam)
{
    static  HFONT hfontDlg;
    static  LPSTR   lpVersion;
    static  DWORD   dwVerInfoSize;
    static  DWORD   dwVerHnd;
    static  UINT    uVersionLen;
    static  WORD    wRootLen;
    BOOL    bRetCode;
    static  int     i;
    static  char    szFullPath[256];
    static  char    szResult[256];
    static  char    szGetName[256];

    switch (message) {
        case WM_INITDIALOG:  // message: initialize dialog box
            // Create a font to use
            hfontDlg = CreateFont(14, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0,
                VARIABLE_PITCH | FF_SWISS, "");

            // Center the dialog over the application window
            CenterWindow (hDlg, GetWindow (hDlg, GW_OWNER));

            // Get version information from the application
            GetModuleFileName (hInst, szFullPath, sizeof(szFullPath));
            dwVerInfoSize = GetFileVersionInfoSize(szFullPath, &dwVerHnd);
            if (dwVerInfoSize) {
                // If we were able to get the information, process it:
                LPSTR   lpstrVffInfo;
                HANDLE  hMem;
                hMem = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
                lpstrVffInfo  = (char *)GlobalLock(hMem);
                GetFileVersionInfo(szFullPath, dwVerHnd, dwVerInfoSize, lpstrVffInfo);
                lstrcpy(szGetName, "\\StringFileInfo\\040904E4\\");
                wRootLen = lstrlen(szGetName);

                // Walk through the dialog items that we want to replace:
                for (i = DLG_VERFIRST; i <= DLG_VERLAST; i++) {
                    GetDlgItemText(hDlg, i, szResult, sizeof(szResult));
                    szGetName[wRootLen] = (char)0;
                    lstrcat (szGetName, szResult);
                    uVersionLen   = 0;
                    lpVersion     = NULL;
                      bRetCode      =  VerQueryValue((LPVOID)lpstrVffInfo,
                          (LPSTR)szGetName,
                          (LPVOID *)&lpVersion,
#if defined (_WIN32)
                          (PUINT)&uVersionLen); // For MIPS strictness
#else
                          (UINT FAR *)&uVersionLen);
#endif

                      if ( bRetCode && uVersionLen && lpVersion) {
                          // Replace dialog item text with version info
                          lstrcpy(szResult, lpVersion);
                          SetDlgItemText(hDlg, i, szResult);
                          SendMessage (GetDlgItem (hDlg, i), WM_SETFONT, (UINT)hfontDlg, TRUE);
                      }
                } // for (i = DLG_VERFIRST; i <= DLG_VERLAST; i++)

                GlobalUnlock(hMem);
                GlobalFree(hMem);
            } // if (dwVerInfoSize)

            return (TRUE);

        case WM_COMMAND:                      // message: received a command
            if (LOWORD(wParam) == IDOK        // "OK" box selected?
            || LOWORD(wParam) == IDCANCEL) {  // System menu close command?
                EndDialog(hDlg, TRUE);        // Exit the dialog
                DeleteObject (hfontDlg);
                return (TRUE);
            }
            break;
    }
    return (FALSE); // Didn't process the message

    lParam; // This will prevent 'unused formal parameter' warnings
}

