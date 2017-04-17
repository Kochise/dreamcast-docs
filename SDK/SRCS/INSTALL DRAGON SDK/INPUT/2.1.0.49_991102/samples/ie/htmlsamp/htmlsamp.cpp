/********************************************************************
 * htmlsamp.cpp
 *
 * Description
 *    Main line of application. Handles initialization and cleaning up
 *    of windows, DLLs, call backs, etc.
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "headers.h"            // common headers
#include "htmldoc.h"            // CHTMLDoc
#include "htmldlg.h"            // CHTMLDialog
#include "titlebar.h"           // CTitleBar
#include "toolbar.h"            // CToolBar
#include "status.h"             // CStatusBar
#include "device.h"             // CVMUSelection
#include "sound.h"              // DSound wrappers
#include "statanim.h"           // CStatusAnimated
#include "alert.h"              // CAlertWindow
#include "external.h"           // external function wrappers
#ifdef GAME_SAMPLE
#include "gamefld.h"            // CGameField
#else  // GAME_SAMPLE
#endif // GAME_SAMPLE
#ifdef USE_FLASH
#include "flashapi.h"           // MM Flash
#endif // USE_FLASH

/********************************************************************
 * External Windows CE prototypes
 ********************************************************************/
extern "C"
{
BOOL WINAPI RegisterTaskBar(HWND);
BOOL WINAPI GetMessageWNoWait(PMSG pMsg, HWND hWnd, UINT wMsgFilterMin, 
                              UINT wMsgFilterMax);
};

/********************************************************************
 * Defines
 ********************************************************************/
#define SLEEP_SHUTDOWN  7000 // 2 seconds + 
                             // HKEY_LOCAL_MACHINE\Software\Microsoft\Ole\FreeTimeout 
                             // value

#ifdef USE_FLASH
#define DRAW_TIME       100   
#define INPUT_TIME      100   
#define CONNECT_TIME    1000 
#else  // USE_FLASH
#define DRAW_TIME       15   // 15 milliseconds 1/67 second
#define INPUT_TIME      30   // 30 milliseconds 1/33 second
#define CONNECT_TIME    1000 // 1000 milliseconds 1 second
#endif // USE_FLASH
 
#define X_ALERT         140  // position of alert windows
#define Y_ALERT         120
#define W_ALERT         360
#define H_ALERT         240

#define X_TOOLBAR       X_MARGIN        // position of tool bar
#define Y_TOOLBAR       Y_MARGIN
#ifdef GAME_SAMPLE
#define W_TOOLBAR       228
#else // GAME_SAMPLE
#define W_TOOLBAR       (W_SCREEN - 31)
#endif // GAME_SAMPLE
#define H_TOOLBAR       31

#define X_TITLEBAR      X_TOOLBAR       // position of title bar for HTML page
#define Y_TITLEBAR      (Y_TOOLBAR + H_TOOLBAR)
#ifdef GAME_SAMPLE
#define W_TITLEBAR      W_TOOLBAR
#else  // GAME_SAMPLE
#define W_TITLEBAR      W_SCREEN
#endif // GAME_SAMPLE
#define H_TITLEBAR      31

#define X_HTMLDOC       X_TOOLBAR       // position of HTML control
#define Y_HTMLDOC       (Y_TITLEBAR + H_TITLEBAR)
#define W_HTMLDOC       W_TITLEBAR
#define H_HTMLDOC       (H_SCREEN - Y_HTMLDOC + Y_MARGIN - 20)

#define X_HTMLSTAT      X_HTMLDOC       // position of status bar
#define Y_HTMLSTAT      (Y_HTMLDOC + H_HTMLDOC)
#ifdef GAME_SAMPLE
#define W_HTMLSTAT      W_HTMLDOC
#else
#define W_HTMLSTAT      (W_HTMLDOC - 20)
#endif
#define H_HTMLSTAT      (H_SCREEN - Y_HTMLSTAT + Y_MARGIN)

#ifdef GAME_SAMPLE
                                        // position of title bar for game
#define X_TITLE         (X_HTMLDOC + W_HTMLDOC + 26)
#define Y_TITLE         Y_MARGIN
#define W_TITLE         (W_SCREEN - X_GAMEFLD + X_MARGIN - 26)
#define H_TITLE         26

                                        // position of Battleship game field
#define X_GAMEFLD       (X_TITLE - H_TITLE)
#define Y_GAMEFLD       (Y_TITLE + H_TITLE)
#define W_GAMEFLD       (W_TITLE + H_TITLE)
#define H_GAMEFLD       (Y_HTMLDOC + H_HTMLDOC - Y_GAMEFLD)

                                        // position of status bar for Hit/Miss
#define X_GAMESTAT      X_GAMEFLD
#define Y_GAMESTAT      (Y_GAMEFLD + H_GAMEFLD)
#define W_GAMESTAT      (W_GAMEFLD / 2)
#define H_GAMESTAT      (H_SCREEN - Y_GAMESTAT + Y_MARGIN)

                                        // position of status for shot status
#define X_SHOTSTAT      (X_GAMESTAT + W_GAMESTAT)
#define Y_SHOTSTAT      Y_GAMESTAT
#define W_SHOTSTAT      W_GAMESTAT
#define H_SHOTSTAT      H_GAMESTAT

                                        // position of spinning icon
#define X_LOGO          X_GAMEFLD
#define Y_LOGO          Y_TITLE
#define W_LOGO          H_TITLE
#define H_LOGO          H_TITLE

#define W_LOGOICONS     (W_LOGO * 17)

                                        // position of wait screen
#define X_WAIT          195
#define Y_WAIT          178
#define W_WAIT          250
#define H_WAIT          124

#else  // GAME_SAMPLE

                                        // position of spinning icon
#define X_LOGO          (X_TOOLBAR + W_TOOLBAR)
#define Y_LOGO          Y_TOOLBAR
#define W_LOGO          H_TOOLBAR
#define H_LOGO          H_TOOLBAR

#define W_LOGOICONS     (W_LOGO * 9)

                                        // position of security icon
#define X_SECURITY      (X_HTMLSTAT + W_HTMLSTAT)
#define Y_SECURITY      Y_HTMLSTAT
#define W_SECURITY      (W_HTMLDOC - W_HTMLSTAT)
#define H_SECURITY      H_HTMLSTAT

#define W_SECURITYICONS (W_SECURITY * 2)

#endif // GAME_SAMPLE

#define W_BUTTONS       240             // tool bar buttons data
#define H_BUTTONS       25
#define NUM_BUTTONS     10

/********************************************************************
 * Global variables
 ********************************************************************/
HINSTANCE g_hInstance = NULL;                   // application instance
HWND      g_hwndGame  = NULL;                   // main app window
ULONG     g_ulHTMLDialogCallbackCookie = 0;     // HTML Dialog callback
ULONG     g_ulHTMLDialogCount          = 0;     // number of HTML Dialogs
LPDIRECTSOUNDBUFFER g_pSndBufferClick = NULL;   // button press click snd

/********************************************************************
 * Local prototypes
 ********************************************************************/
void SetPacificTimeZone(void);
void MessageLoopWork(BOOL bCheckConnection);
HWND InitializeGame(void);
HRESULT RegisterCallback(void);
HRESULT CALLBACK HTMLDialogCallback(UINT uiType, HWND hwnd, 
                                    IHTMLDocument2 *pHTMLDocument2, 
                                    ULONG ulData);
LRESULT CALLBACK DesktopWndProc(HWND hWnd, UINT message, WPARAM wParam, 
                                LPARAM lParam);
LRESULT CALLBACK GameWndProc(HWND hWnd, UINT message, WPARAM wParam, 
                             LPARAM lParam);

#ifdef GAME_SAMPLE
void ToggleHTMLWindows(HWND hwnd, BOOL bForceOn = FALSE, 
                       BOOL bForceOff = FALSE);
#endif // GAME_SAMPLE

/********************************************************************
 * WinMain
 *
 * Description
 *    Main line of application. Initializes the windows, call backs,
 *    and DLLs. Run the message pump. Cleans up the windows, call 
 *    backs, and DLLs.
 *
 * Parameters
 *    hinst        instance handle of application
 *    hInstPrev    instance handle of previously running application
 *                 (ignored)
 *    pszCmdLine   command line parameters (ignored)
 *    nCmdShow     how to show main window (ignored)
 * 
 * Returns
 *    0
 ********************************************************************/
int WINAPI WinMain(HINSTANCE hinst, HINSTANCE hInstPrev, LPWSTR pszCmdLine, 
                   int nCmdShow)
{
    g_hInstance = hinst;

    // set time zone. you may want to ask the user what time zone he
    // is in
    SetPacificTimeZone();

    // this library needs to be loaded early to register controls
    HINSTANCE hInstIECEUI = LoadLibrary(TEXT("ieceui.dll"));

    // initize COM
    if (SUCCEEDED(CoInitializeEx(NULL, COINIT_MULTITHREADED)))
    {
        // create main window
        g_hwndGame = InitializeGame();
        // create all the "windows"
        if (g_hwndGame)
        {
#ifdef GAME_SAMPLE
            CStatusBar      sbName(X_TITLE,    Y_TITLE,    W_TITLE,    H_TITLE,    RGB(0, 0, 255), MAKEINTRESOURCE(IDB_TITLE));
            CStatusBar      sbGame(X_GAMESTAT, Y_GAMESTAT, W_GAMESTAT, H_GAMESTAT, RGB(255, 0, 0), MAKEINTRESOURCE(IDB_GAMESTATUS));
            CStatusBar      sbShot(X_SHOTSTAT, Y_SHOTSTAT, W_SHOTSTAT, H_GAMESTAT, RGB(255, 0, 0), MAKEINTRESOURCE(IDB_GAMESTATUS));
            CGameField      gfGame(X_GAMEFLD,  Y_GAMEFLD,  W_GAMEFLD,  H_GAMEFLD,  &sbGame, &sbShot);
            CStatusAnimated sbLogo(X_LOGO,     Y_LOGO,     W_LOGO,     H_LOGO,     MAKEINTRESOURCE(IDB_LOGO), W_LOGOICONS);

            CStatusBar      *psbHTML = NULL;
            CTitleBar       *ptlHTML = NULL;
            CToolBar        *ptbHTML = NULL;
            CHTMLDoc        *pDoc    = NULL; 

            SetWindowLong(g_hwndGame,  0, (LPARAM)(&pDoc));
            SetWindowLong(g_hwndGame,  4, (LPARAM)(&psbHTML));
            SetWindowLong(g_hwndGame,  8, (LPARAM)(&ptlHTML));
            SetWindowLong(g_hwndGame, 12, (LPARAM)(&ptbHTML));
            SetWindowLong(g_hwndGame, 16, (LPARAM)(&sbLogo));

            // show HTML control and all its accessories
            ToggleHTMLWindows(g_hwndGame, TRUE);
#else  // GAME_SAMPLE
            TOOLBAR_BUTTON tbButtons[] = 
            {
                { ID_HOME,     2 },
                { ID_SEARCH,   6 },
                { ID_KEYBOARD, 3 },
                { ID_BACK,     0 },
                { ID_FORWARD,  1 },
                { ID_REFRESH,  4 },
                { ID_STOP,     5 },
                { ID_CONNECT,  8 },
                { ID_HELP,     7 },
                { ID_TB_END,   0 },
            };

            // load DLLs that will be used often
            LoadDLLs();

            // register call backs
            SetShowVMUMessageCallback(ShowVMUMessage);
            SetGetVMUDeviceCallback(GetVMUDevice);

            RegisterHTMLDialogCallback(HTMLDialogCallback, 0, 
                                       &g_ulHTMLDialogCallbackCookie);

            CWindow         dummy(0, 0, 0, 0, FALSE);
            CStatusBitmap   sbLock(X_SECURITY, Y_SECURITY, W_SECURITY, H_SECURITY, MAKEINTRESOURCE(IDB_SECURITY), W_SECURITYICONS);
            CStatusAnimated sbLogo(X_LOGO,     Y_LOGO,     W_LOGO,     H_LOGO,     MAKEINTRESOURCE(IDB_LOGO),     W_LOGOICONS);
            CStatusBar      sbHTML(X_HTMLSTAT, Y_HTMLSTAT, W_HTMLSTAT, H_HTMLSTAT, RGB(255, 0, 0), MAKEINTRESOURCE(IDB_HTMLSTATUS));
            CTitleBar       tlHTML(X_TITLEBAR, Y_TITLEBAR, W_TITLEBAR, H_TITLEBAR, RGB(0, 0, 255), MAKEINTRESOURCE(IDB_TITLEBAR));
            CToolBar        tbHTML(X_TOOLBAR,  Y_TOOLBAR,  W_TOOLBAR,  H_TOOLBAR,  MAKEINTRESOURCE(IDB_TOOLBAR), W_BUTTONS, H_BUTTONS, NUM_BUTTONS, MAKEINTRESOURCE(IDB_BUTTONS), tbButtons);
            CHTMLDoc *pDoc = new CHTMLDoc(g_hwndGame, X_HTMLDOC, Y_HTMLDOC, W_HTMLDOC, H_HTMLDOC, &sbHTML, &tlHTML, &tbHTML, &sbLock, &sbLogo);
            tlHTML.SetOwnerWindow(pDoc);
            tbHTML.SetOwnerWindow(pDoc);

            SetWindowLong(g_hwndGame,  0, (LPARAM)(&pDoc));
#endif // GAME_SAMPLE

            MSG  msg;

            // main message loop
            while (TRUE)
            {
                // use GetMessageWNoWait instead of PeekMessage
                // could also use GetMessage if doing drawing on a different thread
                if (GetMessageWNoWait(&msg, NULL, 0, 0))
                {
                    if (msg.message == WM_QUIT)
                    {
                        break;
                    }

                    // give control a chance to handle message
                    if (!pDoc || (S_FALSE == pDoc->PreTranslateMessage(&msg)))
                    {
                        TranslateMessage(&msg);
                        DispatchMessage(&msg);
                    }
                }

                // do drawing and input checking
                // this work could be done a different thread
                MessageLoopWork(TRUE);
            }

            // application ending
#ifdef GAME_SAMPLE
            // get rid of HTML control
            ToggleHTMLWindows(g_hwndGame, FALSE, TRUE);
#else  // GAME_SAMPLE
            // get rid of HTML control
            if (pDoc)
            {
                pDoc->ShutDown(TRUE);
                pDoc->Release();
                pDoc = NULL;
            }

            // reset callbacks
            SetShowVMUMessageCallback(NULL);
            SetGetVMUDeviceCallback(NULL);

            UnRegisterHTMLDialogCallback(g_ulHTMLDialogCallbackCookie);
            g_ulHTMLDialogCallbackCookie = 0;

            // no longer need DLLs
            FreeDLLs();
#endif // GAME_SAMPLE
        }

#ifdef USE_FLASH
            FlashSetDirectSound(NULL);
#endif // USE_FLASH

        // do this outside the above scope so local variables 
        // are destroyed before window is destroyed.
        if (g_hwndGame)
        {
            DestroyWindow(g_hwndGame);
        }

        OutputDebugString(TEXT("Exiting program. Please wait...\n"));
    
        // Give threads a chance to finish up.
        Sleep(SLEEP_SHUTDOWN);

        // uninitialize COM
        CoUninitialize();

        OutputDebugString(TEXT("Exited program.\n"));
    }

    // no longer need this library
    if (hInstIECEUI)
    {
        FreeLibrary(hInstIECEUI);
    }

    g_hInstance = NULL;

    return 0;
}

/********************************************************************
 * SetPacificTimeZone
 *
 * Description
 *    Sets the time zone to Pacific time. You may want to ask the user
 *    what his timezone is or determine this in some other way. This
 *    shows the Windows calls that need to be made to correctly set
 *    the time zone to make sure things like cookies work correctly.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    None
 ********************************************************************/
void SetPacificTimeZone(void)
{
    // set the timezone to be Pacific Time (-8 hrs, daylight savings 
    // first Sun in April to last Sunday in October)

    TIME_ZONE_INFORMATION tzi;
    memset(&tzi, 0, sizeof(tzi));

    _tcscpy(tzi.StandardName, TEXT("PST"));
    tzi.Bias = 480; // 8 hours
    tzi.StandardDate.wMonth = 10;
    tzi.StandardDate.wDay   = 5;
    tzi.StandardDate.wHour  = 2;

    _tcscpy(tzi.DaylightName, TEXT("PDT"));
    tzi.DaylightBias        = -60;
    tzi.DaylightDate.wMonth = 4;
    tzi.DaylightDate.wDay   = 1;
    tzi.DaylightDate.wHour  = 2;

    SetTimeZoneInformation(&tzi);

    // must also set the daylight saving flag during daylight savings time.

    // get the current date/time.
    SYSTEMTIME stNow;
    DATE       dtNow;
    GetLocalTime(&stNow);
    SystemTimeToVariantTime(&stNow, &dtNow);

    // find first Sunday of April (start of DST).
    SYSTEMTIME stDSTStart = { stNow.wYear, 4, 0, 1, 2, 0, 0, 0 };
    DATE       dtDSTStart;
    SystemTimeToVariantTime(&stDSTStart, &dtDSTStart);
    VariantTimeToSystemTime(dtDSTStart, &stDSTStart);
    if (stDSTStart.wDayOfWeek)
    {
        dtDSTStart += (7 - stDSTStart.wDayOfWeek);
    }

    // find last Sunday of October (end of DST).
    SYSTEMTIME stDSTEnd   = { stNow.wYear, 10, 0, 31, 2, 0, 0, 0 };
    DATE       dtDSTEnd;
    SystemTimeToVariantTime(&stDSTEnd, &dtDSTEnd);
    VariantTimeToSystemTime(dtDSTEnd, &stDSTEnd);
    if (stDSTEnd.wDayOfWeek)
    {
        dtDSTEnd -= stDSTEnd.wDayOfWeek;
    }

    // see if today is in between.    
    SetDaylightTime((dtNow >= dtDSTStart) && (dtNow <= dtDSTEnd));
}

/********************************************************************
 * Global variables
 ********************************************************************/
CHTMLDialog *g_pHTMLDialog[MAX_HTMLDIALOGS] = { 0 };

/********************************************************************
 * HTMLDialogCallback
 *
 * Description
 *    Call back function called when an event for an HTML Dialog 
 *    occurs.
 *
 * Parameters
 *    uiType           HTMLDIALOGCALLBACK flag
 *    hwnd             window handle of new HTML Dialog
 *    pHTMLDocument2   only valid on HTMLDIALOGCALLBACK_CREATE
 *                     HTML document of new HTML Dialog
 *    ulData           data specified by application when call back
 *                     was registered
 * 
 * Returns
 *    S_OK
 ********************************************************************/
HRESULT CALLBACK HTMLDialogCallback(UINT uiType, HWND hwnd, IHTMLDocument2 *pHTMLDocument2, ULONG ulData)
{
    switch (uiType)
    {
        // new HTML Dialog was created. Add it to the list and capture the 
        // cursor
        case HTMLDIALOGCALLBACK_CREATE:
        {
            if (pHTMLDocument2 && (g_ulHTMLDialogCount < (MAX_HTMLDIALOGS - 1)))
            {
                g_pHTMLDialog[g_ulHTMLDialogCount] = new CHTMLDialog(hwnd, pHTMLDocument2);
                if (g_pHTMLDialog[g_ulHTMLDialogCount])
                {
                    g_ulHTMLDialogCount++;
                    SetCursorCapture(g_pHTMLDialog[g_ulHTMLDialogCount - 1]);
                }
            }

            break;
        }

        // HTML Dialog was destroyed. Remove it from the list and pass along
        // cursor capture to previous HTML Dialog if necessary
        case HTMLDIALOGCALLBACK_DESTROY:
        {
            ULONG i;
            for (i = 0; i < g_ulHTMLDialogCount; i++)
            {
                if (g_pHTMLDialog[i]->GetHWND() == hwnd)
                {
                    delete g_pHTMLDialog[i];
                    g_pHTMLDialog[i] = NULL;
                    g_ulHTMLDialogCount--;
                    if (i != g_ulHTMLDialogCount)
                    {
                        memmove(g_pHTMLDialog + i, g_pHTMLDialog + i + 1, sizeof(CHTMLDialog *) * (g_ulHTMLDialogCount - i));
                    }
                    if (g_ulHTMLDialogCount)
                    {
                        SetCursorCapture(g_pHTMLDialog[g_ulHTMLDialogCount - 1]);
                    }
                }
            }

            break;
        }

        // called from inside message loop of modal HTML Dialog. This
        // may not be needed if you do drawing/input checking on a 
        // separate thread 
        case HTMLDIALOGCALLBACK_MSGLOOP:
        {
            MessageLoopWork(FALSE);
            break;
        }
    }

    return S_OK;
}

/********************************************************************
 * GetHTMLDialogForHWND
 *
 * Description
 *    Searches list of HTML Dialogs and returns CHTMLDialog object
 *    pointer for the object that owns the given HTML Dialog window
 *    handle.
 *
 * Parameters
 *    hwnd             handle of window for which to look up object
 * 
 * Returns
 *    CHTMLDialog *    pointer to object that owns the HWND
 ********************************************************************/
CHTMLDialog *GetHTMLDialogForHWND(HWND hwnd)
{
    ULONG i;
    for (i = 0; i < g_ulHTMLDialogCount; i++)
    {
        if (g_pHTMLDialog[i]->GetHWND() == hwnd)
        {
            return g_pHTMLDialog[i];
        }
    }

    return NULL;
}

/********************************************************************
 * Intialize game
 *
 * Description
 *    Creates the "desk top" window and the main application window.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    HWND      window handle of main application window
 *    NULL      failure
 ********************************************************************/
HWND InitializeGame(void)
{
    // register window class for desk top window
    WNDCLASS    wc;

    wc.style         = 0;
    wc.lpfnWndProc   = DesktopWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = g_hInstance;
    wc.hCursor       = NULL;
    wc.hIcon         = NULL;
    wc.hbrBackground = NULL;
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = TEXT("DesktopExplorerWindow");

    if (!RegisterClass (&wc)) 
    {
        return NULL;
    }

    // create desk top window (this window simulates the PC's desktop
    // window)
    HWND hwndDesk = CreateWindowEx(0, wc.lpszClassName, NULL, WS_VISIBLE,
                                   0, 0,
                                   GetSystemMetrics(SM_CXSCREEN),
                                   GetSystemMetrics(SM_CYSCREEN),
                                   NULL, NULL, g_hInstance, NULL);

    // register window class for application window
    wc.lpfnWndProc   = GameWndProc;
    wc.cbWndExtra    = sizeof(LPVOID) * 5;  // for htmldoc, title bar, 
                                            // tool bar, status bar, and 
                                            // spinning icon
    wc.lpszClassName = TEXT("GameWindow");

    if (!RegisterClass (&wc)) 
    {
        return NULL;
    }


    // create main application window    
    HWND hwndGame = CreateWindowEx(0, wc.lpszClassName, NULL, WS_VISIBLE, 
                                   0, 0,
                                   GetSystemMetrics(SM_CXSCREEN),
                                   GetSystemMetrics(SM_CYSCREEN),
                                   hwndDesk, NULL, g_hInstance, NULL);

    return hwndGame;
}

/********************************************************************
 * MessageLoopWork
 *
 * Description
 *    Draws the windows to the screen, checks for joystick input, and
 *    checks for time to disconnect RAS. This functionality may be
 *    written to be on a separate thread instead of in the message
 *    loop.
 *
 * Parameters
 *    bCheckConnection TRUE  if should check for disconnect time
 *                     FALSE if should not bother
 * 
 * Returns
 *    Non
 ********************************************************************/
void MessageLoopWork(BOOL bCheckConnection)
{
    static long lLastInput;
    static long lLastDraw;
    static long lLastConnect;

    long lNow = GetTickCount();

#ifdef USE_FLASH
    FlashIdle();
#endif // USE_FLASH

    // see if it's time to check DInput
    if ((lNow - lLastInput) > INPUT_TIME)
    {
        lLastInput = lNow;
        ReadDirectInputDevices();
    }

    // see if it's time to redraw screen
    if ((lNow - lLastDraw) >= DRAW_TIME)
    {
        lLastDraw = lNow;
        DrawCurrentScreen();
    }

    // see if it's time to check for disconnect
    if (bCheckConnection)
    {
        if ((lNow - lLastConnect) >= CONNECT_TIME)
        {
            lLastConnect = lNow;
            CHTMLDoc **ppDoc = (CHTMLDoc **)GetWindowLong(g_hwndGame, 0);
            if (ppDoc && *ppDoc)
            {
                // dont disconnect if dialog is up or screen is locked
                (*ppDoc)->CheckConnection(g_ulHTMLDialogCount || IsScreenLocked());
            }
        }
    }
}

/********************************************************************
 * DesktopWndProc
 *
 * Description
 *    Handles "desk top" window messages. When the window is created,
 *    it is registered as the main desk top window for CE.
 *
 * Parameters
 *    hwnd      window handle of window processing message
 *    uiMsg     message ID
 *    wParam    message data
 *    lParam    message data
 * 
 * Returns
 *    result of DefWindowProc
 ********************************************************************/
LRESULT CALLBACK DesktopWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) 
    {
        case WM_CREATE:
        {
            // let Windows CE know that it has a Desktop window
            RegisterTaskBar(hwnd);
            break;
        }

        case WM_DESTROY:
        {
            // let Windows CE know that it no longer has a Desktop window
            RegisterTaskBar(NULL);
            break;
        }

        case WM_SETFOCUS:
        {
            // pass focus message on to main application window
            if (g_hwndGame)
            {
                GameWndProc(g_hwndGame, message, wParam, lParam);
            }
        }
    }

    return DefWindowProc (hwnd, message, wParam, lParam);
} 

/********************************************************************
 * GameWndProc
 *
 * Description
 *    Handles the main application window messages.
 *
 * Parameters
 *    hwnd      window handle of window processing message
 *    uiMsg     message ID
 *    wParam    message data
 *    lParam    message data
 * 
 * Returns
 *    result of DefWindowProc
 ********************************************************************/
LRESULT CALLBACK GameWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static CAlertWindow *pWaitWindow;

    switch (message) 
    {
        case WM_CREATE:
        {
            // initialize DDraw, DInput, DSound and create the "click" sound
            CreateDirectDraw(hwnd);
            CreateDirectInput(g_hInstance, hwnd);
            CreateDirectSound(hwnd);
            g_pSndBufferClick = LoadSoundBuffer(MAKEINTRESOURCE(IDW_CLICK));
            break;
        }

        case WM_DESTROY:
        {
#ifdef USE_FLASH
            FlashSetDirectSound(NULL);
#endif // USE_FLASH

            // clean up DDraw, DInput, DSound and the click sound
            if (g_pSndBufferClick)
            {
                g_pSndBufferClick->Release();
                g_pSndBufferClick = NULL;
            }
            DestroyDirectSound();
            DestroyDirectInput();
            DestroyDirectDraw();
            break;
        }

        case WM_SETFOCUS:
        {
            // activate HTML control when window gets focus
            CHTMLDoc **ppDoc = (CHTMLDoc **)GetWindowLong(hwnd, 0);
            if (ppDoc && *ppDoc)
            {
                (*ppDoc)->DoActivation(LOWORD(wParam) != WA_INACTIVE);
            }
            return 0;
        }

        case WM_JOYSTICK:
        {
            // check for exit, then pass the message to the proper
            // "window"
            if (wParam && (*((LPDWORD)wParam) & JOYSTICK_X))
            {
                if (!g_ulHTMLDialogCount)
                {
                    PostQuitMessage(0);
                }
            }

            SendCurrentScreenJoystick(wParam, lParam);
            return 0;
        }

        case WM_GETDEVICE:
        {
            // display VMU device selection screen
            CVMUSelection *pVMUSelection = new CVMUSelection((HANDLE)wParam, (DWORD *)lParam);
            if (pVMUSelection)
            {
                if (FAILED(pVMUSelection->Start()))
                {
                    pVMUSelection->Stop();
                }
            }
            break;
        }
  
        case WM_SHOWMSG:
        {
            // display requested alert on status of VMU download
            BOOL    bLeaveUp = (BOOL)wParam;
            HRESULT hr       = (HRESULT)lParam;

            // wait alert stays up until another alert is requested
            if (pWaitWindow)
            {
                delete pWaitWindow;
                pWaitWindow = NULL;
            }
            switch (hr)
            {
                case E_PENDING:
                {
                    pWaitWindow = new CAlertWindow(X_ALERT, Y_ALERT, W_ALERT, H_ALERT, MAKEINTRESOURCE(IDB_DEVICEWAIT), FALSE);
                    break;
                }
                case S_OK:
                    {
                        new CAlertWindow(X_ALERT, Y_ALERT, W_ALERT, H_ALERT, MAKEINTRESOURCE(IDB_DEVICEOK));
                        // destroys itself when closed
                        break;
                    }
                default:
                    {
                        new CAlertWindow(X_ALERT, Y_ALERT, W_ALERT, H_ALERT, MAKEINTRESOURCE(IDB_DEVICEFAIL));
                        // destroys itself when closed
                        break;
                    }
           }

 
          break;
     }

#ifdef GAME_SAMPLE
        case WM_TOGGLEHTML:
        {
            // create or destroy HTML control and its accessories
            ToggleHTMLWindows(hwnd);
            break;
        }
#endif // GAME_SAMPLE

        default:
            break;
    }

    return DefWindowProc (hwnd, message, wParam, lParam);
} 

#ifdef GAME_SAMPLE

/********************************************************************
 * ToggleHTMLWindows
 *
 * Description
 *    Creates or destroys HTML control window and its accessory 
 *    windows depending on current state and requested state.
 *
 * Parameters
 *    hwnd         main application window (parent of HTML control)
 *    bForceOn     force the HTML control to be turned on regardless
 *                 of current state (i.e., application starting)
 *    bForceOff    force the HTML control be be turned off regardless
 *                 of current state (i.e., application exiting)
 * 
 * Returns
 *    None
 ********************************************************************/
void ToggleHTMLWindows(HWND hwnd, BOOL bForceOn, BOOL bForceOff)
{
    // validate internal data
    CHTMLDoc        **ppDoc    = (CHTMLDoc        **)GetWindowLong(hwnd,  0);
    CStatusBar      **ppsbHTML = (CStatusBar      **)GetWindowLong(hwnd,  4);
    CTitleBar       **pptlHTML = (CTitleBar       **)GetWindowLong(hwnd,  8);
    CToolBar        **pptbHTML = (CToolBar        **)GetWindowLong(hwnd, 12);
    CStatusAnimated  *psbLogo  = (CStatusAnimated  *)GetWindowLong(hwnd, 16);

    if (!ppDoc || !ppsbHTML || !pptlHTML || !pptbHTML)
    {
        return;
    }

    // show wait screen if application is not shutting down
    if (!bForceOff)
    {
        IDirectDrawSurface *pDDSBitmap = CreateBitmapSurface(MAKEINTRESOURCE(IDB_WAIT), W_WAIT, H_WAIT,  FALSE, 0);
        if (pDDSBitmap)
        {
            DrawWaitScreen(X_WAIT, Y_WAIT, W_WAIT, H_WAIT, pDDSBitmap);
            pDDSBitmap->Release();
        }
    }

    LockScreen();

    // toggle display of HTML control ON
    if (!*ppDoc && !bForceOff)
    {
        TOOLBAR_BUTTON tbButtons[] = 
        {
            { ID_HOME,     2 },
            { ID_SEARCH,   6 },
            { ID_KEYBOARD, 3 },
            { ID_BACK,     0 },
            { ID_FORWARD,  1 },
            { ID_REFRESH,  4 },
            { ID_STOP,     5 },
            { ID_CONNECT,  8 },
            { ID_HELP,     7 },
            { ID_TB_END,   0 },
        };

        // move game windows over to the right
        if (!bForceOn)
        {
            MoveAllWindows(W_HTMLDOC / 2, 0);
        }

        // load needed DLLs
        LoadDLLs();

        // register call backs
        SetShowVMUMessageCallback(ShowVMUMessage);
        SetGetVMUDeviceCallback(GetVMUDevice);

        RegisterHTMLDialogCallback(HTMLDialogCallback, 0, &g_ulHTMLDialogCallbackCookie);

        // create HTML control window and accessory windows
        *ppsbHTML = new CStatusBar     (X_HTMLSTAT, Y_HTMLSTAT, W_HTMLSTAT, H_HTMLSTAT, RGB(255, 0, 0), MAKEINTRESOURCE(IDB_HTMLSTATUS));
        *pptlHTML = new CTitleBar      (X_TITLEBAR, Y_TITLEBAR, W_TITLEBAR, H_TITLEBAR, RGB(0, 0, 255), MAKEINTRESOURCE(IDB_TITLEBAR));
        *pptbHTML = new CToolBar       (X_TOOLBAR,  Y_TOOLBAR,  W_TOOLBAR,  H_TOOLBAR,  MAKEINTRESOURCE(IDB_TOOLBAR), W_BUTTONS, H_BUTTONS, NUM_BUTTONS, MAKEINTRESOURCE(IDB_BUTTONS), tbButtons);
        *ppDoc    = new CHTMLDoc       (g_hwndGame, X_HTMLDOC,  Y_HTMLDOC,  W_HTMLDOC,  H_HTMLDOC, *ppsbHTML, *pptlHTML, *pptbHTML, NULL, psbLogo);

        // set up HTML control
        if (*ppsbHTML && *pptlHTML && *pptbHTML && *ppDoc)
        {
            (*pptlHTML)->SetOwnerWindow(*ppDoc);
            (*pptbHTML)->SetOwnerWindow(*ppDoc);
            if (!bForceOn)
            {
                SetActiveDisplay(X_MARGIN, Y_MARGIN, W_SCREEN, H_SCREEN);
                SetCursorPosition(X_LOGO + W_LOGO / 2, Y_LOGO + H_LOGO / 2);
            }

            UnlockScreen();
            return;
        }
    }

    // either shutting down or create did not succeed. 

    // center Battleship windows on screen
    if (!bForceOff)
    {
        MoveAllWindows(-(W_HTMLDOC / 2), 0);
    }

    // shutdown HTML control and its accessories
    if (*pptlHTML)
    {
        (*pptlHTML)->SetOwnerWindow(NULL);
    }

    if (*pptbHTML)
    {
        (*pptbHTML)->SetOwnerWindow(NULL);
    }

    if (*ppDoc)
    {
        (*ppDoc)->Hide();
        (*ppDoc)->ShutDown(bForceOff);
        (*ppDoc)->Release();
        *ppDoc = NULL;
    }

    if (*ppsbHTML)
    {
        delete (*ppsbHTML);
        *ppsbHTML = NULL;
    }

    if (*pptlHTML)
    {
        delete (*pptlHTML);
        *pptlHTML = NULL;
    }

    if (*pptbHTML)
    {
        delete (*pptbHTML);
        *pptbHTML = NULL;
    }

    // reset call backs
    SetShowVMUMessageCallback(NULL);
    SetGetVMUDeviceCallback(NULL);

    UnRegisterHTMLDialogCallback(g_ulHTMLDialogCallbackCookie);
    g_ulHTMLDialogCallbackCookie = 0;

    // unload unneeded DLLs
    FreeDLLs();

    // force COM to unload DLLs (see CoFreeUnusedLibraries doc)
    if (!bForceOff)
    {
        CoFreeUnusedLibraries();
        Sleep(SLEEP_SHUTDOWN);
        CoFreeUnusedLibraries();

        SetActiveDisplay(X_MARGIN + W_HTMLDOC / 2, Y_MARGIN, W_SCREEN - W_HTMLDOC, H_SCREEN);
        SetCursorPosition(X_LOGO - W_HTMLDOC / 2 + W_LOGO / 2, Y_LOGO + H_LOGO / 2);
    }

    UnlockScreen();
}

#endif // GAME_SAMPLE

