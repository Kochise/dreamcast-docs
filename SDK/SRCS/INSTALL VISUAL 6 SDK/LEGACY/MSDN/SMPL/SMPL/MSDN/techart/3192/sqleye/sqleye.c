//***************************** Module Header ********************************
// Module Name: sqleye.c
//
//
// Author PeterWil 1994, Microsoft Ltd.
//****************************************************************************
#define VERSION "SQLEYE Version 1.0"
#define LICENSE "For full details of the licenses relating to the DLLs needed to run SQLEYE please read your Microsoft SQL Server and Microsoft Open Data Services license agreements."

#define DBNTWIN32

// Standard compiler/sql server supplied header files
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <windows.h>
#include <sqlfront.h>
#include <sqldb.h>
#include <srv.h>

// Application specific header files
#include "sqleye.h"
#include "initserv.h"
#include "sqlcbs.h"
#include "dialogs.h"
#include "mngeserv.h"
#include "sendmsg.h"

// Could make these user configurable
#define MAX_CONNECTIONS "255"
#define MAX_CONNECTION 255

// define the dblogin timeout period (seconds)
#define LOGIN_TIME_OUT 15

// define the name of the log file
#define LOG_FILE "sqleye.log"

// Globals
HANDLE ghModule;
HWND   ghwndMain = NULL;
HWND   hwndClient;
HICON  hiAwake, hiAsleep, hiIn, hiOut, hiWaiting, hiRPC, hiGhost, hiStats, hiConnect;

HMENU      hMenu, hMenuWindow;
char       szSvr[MAXSVR+1], szRegKey[MAXRKEY+1] = "Server";

// Declare the structures that ODS needs to get started
SRV_CONFIG *config;
SRV_SERVER *server;

// The thread for the ODS part of SQLEYE to run on
DWORD      lSrvThreadId;   

// Declare the handle to protect the linked list of remote structures
HANDLE    LinkedList_SEM;

// A lot of other routines make use of the log to control what is logged
LOG        Log;

// defined in sqlcbs
extern     BOOL bAutoScroll;
extern     BOOL bAutoTile;
extern     BOOL bStartMin;
extern     BOOL bGhosts;

// Flag to start up straight away without a chance to change the config values
BOOL bAutoStart = FALSE;

// The style for the main window
// Done this way so we can modify it on the fly depending on startup options
DWORD MainStyle = WS_OVERLAPPED | WS_CAPTION | WS_BORDER | WS_THICKFRAME |
                    WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_CLIPCHILDREN |
                    WS_VISIBLE | WS_SYSMENU | MDIS_ALLCHILDSTYLES;

// Forward declarations for local routines
int WINAPI   MainWndProc(HWND, UINT, DWORD, LONG);
int WINAPI   About(HWND, UINT, DWORD, LONG);
int WINAPI   InitEyeDlgProc(HWND, UINT, DWORD,LONG);
int WINAPI   StartSrv(void);
BOOL         InitializeApp(void);
BOOL         InitializeODSServer(void);

//*************************** Function Header ********************************
// Function Name: Main
//
// Description :
//****************************************************************************
int WINAPI WinMain(
    HANDLE  hInstance,
    HANDLE  hPrevInstance,
    LPSTR   lpCmdLine,
    int     nShowCmd)
{
    MSG msg;
    LPSTR lpCommandLine;

    // Create the semaphore to protect the linked list right at the start
    LinkedList_SEM  = CreateSemaphore(NULL, 1, 1, NULL);
    
    // Set up as high priority process
    SetPriorityClass(hInstance,HIGH_PRIORITY_CLASS);

    ghModule = GetModuleHandle(NULL);

    // Set the MDI flag
    Log.MDI             = TRUE;
    // Set Default Logging Options
    // Screen options
    Log.MDI_Query       = TRUE;
    Log.MDI_Result      = TRUE;
    Log.MDI_Attention   = TRUE;
    Log.MDI_Message     = TRUE;
    Log.MDI_Error       = TRUE;
    Log.MDI_Timing      = FALSE;
    Log.MDI_RowCount    = TRUE;

    // log file options
    Log.FILE_Query      = FALSE;
    Log.FILE_Result     = FALSE;
    Log.FILE_Attention  = FALSE;
    Log.FILE_Message    = FALSE;
    Log.FILE_Error      = FALSE;
    Log.FILE_Timing     = FALSE;
    Log.FILE_RowCount   = FALSE;
    Log.FILE_Connections= FALSE;

    // and for the statistics
    Log.Statistics_IO   = FALSE;
    Log.Statistics_Time = FALSE;
    // and for the scripts
    Log.Build_Scripts   = FALSE;


    // process the command line
    while ( lpCommandLine = strtok(lpCmdLine," \0") )
    {
        // set lpCmdLine to null so the while loop strtok carries on from where it left off
        lpCmdLine = NULL;

        if ( !strcmp(lpCommandLine,"/R") || !strcmp(lpCommandLine,"/r") )
            {
            // set the registry key name
            lpCommandLine = strtok(NULL," \0");
            strncpy(szRegKey,lpCommandLine,MAXRKEY);
            strcat(szRegKey,"\0");
            }
                
        if ( !strcmp(lpCommandLine,"/S") || !strcmp(lpCommandLine,"/s") )
            {
            // set the server name
            lpCommandLine = strtok(NULL," \0");
            strncpy(szSvr,lpCommandLine,MAXSVR);
            strcat(szSvr,"\0");
            }
                
        if ( !strcmp(lpCommandLine,"/A") || !strcmp(lpCommandLine,"/a") )
            {
            // Autostart (no chance to change the config value)
            bAutoStart = TRUE;
            }

        if ( !strcmp(lpCommandLine,"/L") || !strcmp(lpCommandLine,"/l") )
            {
            // Log only. No MDI windows
            Log.MDI = FALSE;
            }

        if ( !strcmp(lpCommandLine,"/M") || !strcmp(lpCommandLine,"/m") )
            {
            // Start SQLEYE mimimised
            // Only effective if started from a command line
            // File manager and program manager can over-ride this setting
            MainStyle = MainStyle | WS_MINIMIZE;
            }
    }

    // Initialise SQLEYE (e.g. set up the classes etc..)
    // If this fails then exit SQLEYE
    if (!InitializeApp()) {
        ERRBOX("SQLEYE: InitializeApp failure!");
        return 0;
    }

    // Main message processing loop 
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // THE END
    return 1;
}

//*************************** Function Header ********************************
// Function Name: InitializeApp
//
// Description : Load Icons, register classes, initialize variables
//****************************************************************************
BOOL InitializeApp(void)
{
    WNDCLASS wc;
    char *dbver;

    // Load the standard Icons that we'll use
    hiAwake   = LoadIcon(ghModule,MAKEINTRESOURCE(IDI_OPEN));
    hiAsleep  = LoadIcon(ghModule,MAKEINTRESOURCE(IDI_SLEEP)); 
    hiIn      = LoadIcon(ghModule,MAKEINTRESOURCE(IDI_IN));
    hiOut     = LoadIcon(ghModule,MAKEINTRESOURCE(IDI_OUT)); 
    hiWaiting = LoadIcon(ghModule,MAKEINTRESOURCE(IDI_WAITING)); 
    hiRPC     = LoadIcon(ghModule,MAKEINTRESOURCE(IDI_RPC)); 
    hiGhost   = LoadIcon(ghModule,MAKEINTRESOURCE(IDI_GHOST)); 
    hiStats   = LoadIcon(ghModule,MAKEINTRESOURCE(IDI_STATS)); 
    hiConnect = LoadIcon(ghModule,MAKEINTRESOURCE(IDI_CONNECT)); 

    // Set up the class information for the main window class
    wc.style            = CS_OWNDC;
    wc.lpfnWndProc      = (WNDPROC)MainWndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = ghModule;
    wc.hIcon            = hiAsleep;
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName     = "MainMenu";
    wc.lpszClassName    = "sqleyeClass";

    // register the main window class, otherwise exit
    if (!RegisterClass(&wc))
        return FALSE;

    // Set up the class information for the child window class
    wc.style            = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc      = (WNDPROC)ClientWndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = sizeof(HANDLE); // to hold the CLIENTINFO handle for the MDI
    wc.hInstance        = ghModule;
    wc.hIcon            = NULL;
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = "sqleyeClientClass";

    // register the child window class, otherwise exit
    if (!RegisterClass(&wc))
        return FALSE;

    // Load the main menu
    if ( (hMenu = LoadMenu(ghModule, "MainMenu")) == NULL)
        return FALSE;

    // Set up the menu item under which to place the child windows
    if ( (hMenuWindow = GetSubMenu(hMenu, WINDOWMENU)) == NULL)
        return FALSE;

    // Create the main window
    ghwndMain = CreateWindowEx(
        0L,
        (LPSTR)"sqleyeClass", 
        (LPSTR)"SQLEYE",
        MainStyle,   
        0, 
        0, 
        500, 
        400, // Arbitrary values
        NULL,       
        hMenu,
        ghModule,
        NULL);

    // if we couldn't create the main window then exit
    if (ghwndMain == NULL)
        return FALSE;

    // If we can't load dblib there's no point going any further
    if ( (dbver = dbinit()) == NULL)
    {
        ERRBOX("Couldn't initialise DBLIB");
        return FALSE;
    }
    // Could display the version of DBLIB
    // else MSGBOX(dbver);


    // If we can't change the max number of dbprocs the default value is always 25
    if (dbsetmaxprocs(MAX_CONNECTION) != SUCCEED)
        ERRBOX("Couldn't change the maximum number of dbprocs\nDefault setting now being used (25 dbprocs)");

    // If we can't change the login timeout to what we want the default one is 60secs
    if (dbsetlogintime(LOGIN_TIME_OUT)!=SUCCEED)
        ERRBOX("Couldn't change the dblib login timeout\nDefault setting is now being used (60 seconds)");

    // set up the dblib error and message handlers
    dberrhandle(RemoteErr);
    dbmsghandle(RemoteMsgs);

    // Set the focus on the main window
    SetFocus(ghwndMain);

    // Now we're up and running we can start the gateway if we want to
    // Are we going to autostart
    if (bAutoStart)
        // If so initialise the ODS Server
        InitializeODSServer();
    else
        // Call the routine that allows the user to initialise the ODS server
        PostMessage(ghwndMain,WM_COMMAND,IDM_INIT_ODS,0L);

    // All finished here
    return TRUE;
}


//*************************** Function Header ********************************
// Function Name: MainWndProc
//
// Description : Window handler for the main window
//****************************************************************************
int WINAPI MainWndProc(
    HWND hwnd,
    UINT message,
    DWORD wParam,
    LONG lParam)
{
    static int         iCount=1;
    CLIENTCREATESTRUCT clientcreate;

    switch (message)
    {
        case WM_CREATE:
            clientcreate.hWindowMenu  = hMenuWindow;
            clientcreate.idFirstChild = 1;

            // Initially no processes in the list
            SetWindowLong(hwnd, GWL_USERDATA, (LONG)NULL);

            hwndClient = CreateWindow("MDICLIENT",
                NULL,
                WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,
                0,0,0,0,
                hwnd,
                NULL,
                ghModule,
                (LPVOID)&clientcreate);
        return 0L;

        case WM_CLOSE:
            if (server != NULL)
            {
                if (MessageBox(hwnd,
                    "Exiting SQLEYE in this way will drop all connections without alerting users.\nDo you wish to proceed ?\n\n(the recommended way to shut down SQLEYE is to log on to SQLEYE as 'sa' and issue the 'shutdown sqleye' command).",
                    "Shutdown",
                    MB_OKCANCEL | MB_ICONEXCLAMATION | MB_TASKMODAL)  == IDOK)
                {
                    PostMessage(hwnd,WM_COMMAND,IDM_PAUSE_SERVER,0L);
                    if (MessageBox(hwnd,
                        "SQLEYE has been paused (No new connections).\n\nSelect OK to complete shutdown.\n\n(Cancel will leave SQLEYE in a paused state).",
                        "Shutdown",
                        MB_OKCANCEL | MB_ICONEXCLAMATION | MB_TASKMODAL) == IDOK)
                        SendMessage(ghwndMain, WM_DESTROY, 0L, 0L);
                }
            } else SendMessage(ghwndMain, WM_DESTROY, 0L, 0L);
            return 0L;

        case WM_DESTROY:
            // End of the app so tidy up dblib
            dbexit();
            // We can now kill the GUI
            PostQuitMessage(0);
        return 0L;

        case WM_SIZE:   
            // when the main window changes size then tile if necessary
            if (bAutoTile) PostMessage(hwnd,WM_COMMAND,IDM_TILE,0L);
            // Need to pass this on to the client
        return DefFrameProc(hwnd,  hwndClient, message, wParam, lParam);

        case WM_COMMAND:
        switch (LOWORD(wParam))
            {
            // License information
            case IDM_LICENSE:
                MessageBox(hwnd,
                    LICENSE,
                    "License Restrictions",
                    MB_OK);
            return 0L;

            // Clear all child windows
            case IDM_CLEAR_BUFFER:
                EnumChildWindows(hwndClient,EnumClearBuffers,0L);
            return 0L;

            // Tile the child windows
            case IDM_TILE:
                SendMessage(hwndClient, WM_MDITILE, 0L, 0L);
            return 0L;

            // Cascade the child windows                                        
            case IDM_CASCADE:
                SendMessage(hwndClient, WM_MDICASCADE, 0L, 0L);
            return 0L;

            // Arrange the child Icons
            case IDM_ARRANGE:
                SendMessage(hwndClient, WM_MDIICONARRANGE, 0L, 0L);
            return 0L;
            
            // Close all ghost windows
            case IDM_CLOSE_GHOSTS:
                EnumChildWindows(hwndClient,EnumCloseGhosts,0L);
            return 0L;

            // Initialise the ODS part
            case IDM_INIT_ODS:
                DialogBox(ghModule,MAKEINTRESOURCE(IDD_INITBOX), ghwndMain, (WNDPROC)InitEyeDlgProc);
            return 0L;

            // No new connections
            case IDM_PAUSE_SERVER:
                // Modify the menu
                ModifyMenu(hMenu,IDM_PAUSE_SERVER  ,MF_GRAYED ,IDM_PAUSE_SERVER,
                    (LPSTR)"THE GATEWAY IS PAUSED (No new connections)");
                ModifyMenu(hMenu,IDM_RESTART_SERVER,MF_ENABLED,IDM_RESTART_SERVER,
                    (LPSTR)"&Restart the gateway (Allow new connections)");
                // Pause the server
                ServerSleep(NULL);
            return 0L;

            // Allow new connections
            case IDM_RESTART_SERVER:
                // Modify the menu
                ModifyMenu(hMenu,IDM_RESTART_SERVER,MF_GRAYED ,IDM_RESTART_SERVER,
                    (LPSTR)"&Restart the gateway (Allow new connections)");
                ModifyMenu(hMenu,IDM_PAUSE_SERVER  ,MF_ENABLED,IDM_PAUSE_SERVER,
                    (LPSTR)"&Pause the gateway (No new connections)");
                // Restart the server
                ServerRestart(NULL);
            return 0L;

            // Exit the application
            case IDM_EXIT:
                SendMessage(ghwndMain, WM_CLOSE, 0L, 0L);
            return 0L;

            // Display the about box
            case IDM_ABOUT:
                if (DialogBox(ghModule, "AboutBox", ghwndMain, (WNDPROC)About) == -1)
                    MessageBox(ghwndMain, "SQLEYE: About Dialog Creation Error!", "Error", MB_OK | MB_ICONHAND);
            return 0L;

            // Display the about box
            case IDM_SEND_ALL:
                if (DialogBox(ghModule, MAKEINTRESOURCE(IDD_SENDALL), ghwndMain, (WNDPROC)SendAll) == -1)
                    MessageBox(ghwndMain, "SQLEYE: Send message Dialog Creation Error!", "Error", MB_OK | MB_ICONHAND);
            return 0L;

            // Toggle the Auto-scrolling of the child windows
            case IDM_AUTOSCROLL:
            if (bAutoScroll)
            {
                CheckMenuItem(hMenu,IDM_AUTOSCROLL,MF_UNCHECKED);
                bAutoScroll = FALSE;
            } else {
                CheckMenuItem(hMenu,IDM_AUTOSCROLL,MF_CHECKED);
                bAutoScroll =TRUE;
            }
            return 0L;
            
            // Toggle the Auto-Tiling of the child windows
            case IDM_AUTOTILE:
            if (bAutoTile) 
            {
                bAutoTile = FALSE;
                CheckMenuItem(hMenu,IDM_AUTOTILE,MF_UNCHECKED);
                EnableMenuItem(hMenu,IDM_CASCADE ,MF_ENABLED);
            } else {
                bAutoTile =TRUE;
                CheckMenuItem(hMenu,IDM_AUTOTILE,MF_CHECKED);
                EnableMenuItem(hMenu,IDM_CASCADE ,MF_GRAYED);
                // Tile the windows
                PostMessage(hwnd,WM_COMMAND,IDM_TILE,0L);
            }
            return 0L;

            // Toggle the start mimized for the child windows
            case IDM_STARTMIN:
            if (bStartMin)
            {
                CheckMenuItem(hMenu,IDM_STARTMIN,MF_UNCHECKED);
                bStartMin = FALSE;
            } else {
                CheckMenuItem(hMenu,IDM_STARTMIN,MF_CHECKED);
                bStartMin = TRUE;
            }
            return 0L;

            // Toggle the ghosts
            case IDM_GHOSTS:
            if (bGhosts)
            {
                CheckMenuItem(hMenu,IDM_GHOSTS,MF_UNCHECKED);
                bGhosts = FALSE;
            } else {
                CheckMenuItem(hMenu,IDM_GHOSTS,MF_CHECKED);
                bGhosts = TRUE;
            }
            return 0L;

            // Toggle the build scripts
            case IDM_BUILD_SCRIPTS:
            if (Log.Build_Scripts)
            {
                CheckMenuItem(hMenu,IDM_BUILD_SCRIPTS, MF_UNCHECKED);
                Log.Build_Scripts = FALSE;
            } else {
                CheckMenuItem(hMenu,IDM_BUILD_SCRIPTS, MF_CHECKED);
                Log.Build_Scripts = TRUE;
            }
            return 0L;

            // Toggle the timings
            case IDM_FILE_Timing:
            if (Log.FILE_Timing)
            {
                CheckMenuItem(hMenu,IDM_FILE_Timing, MF_UNCHECKED);
                Log.FILE_Timing = FALSE;
            } else {
                CheckMenuItem(hMenu,IDM_FILE_Timing, MF_CHECKED);
                Log.FILE_Timing = TRUE;
            }
            return 0L;
            case IDM_MDI_Timing:
            if (Log.MDI_Timing)
            {
                CheckMenuItem(hMenu,IDM_MDI_Timing, MF_UNCHECKED);
                Log.MDI_Timing = FALSE;
            } else {
                CheckMenuItem(hMenu,IDM_MDI_Timing, MF_CHECKED);
                Log.MDI_Timing = TRUE;
            }
            return 0L;

            // Toggle the queries
            case IDM_FILE_Query:
            if (Log.FILE_Query)
            {
                CheckMenuItem(hMenu,IDM_FILE_Query, MF_UNCHECKED);
                Log.FILE_Query = FALSE;
            } else {
                CheckMenuItem(hMenu,IDM_FILE_Query, MF_CHECKED);
                Log.FILE_Query = TRUE;
            }
            return 0L;
            case IDM_MDI_Query:
            if (Log.MDI_Query)
            {
                CheckMenuItem(hMenu,IDM_MDI_Query, MF_UNCHECKED);
                Log.MDI_Query = FALSE;
            } else {
                CheckMenuItem(hMenu,IDM_MDI_Query, MF_CHECKED);
                Log.MDI_Query = TRUE;
            }
            return 0L;

            // Toggle the results
            case IDM_FILE_Result:
            if (Log.FILE_Result)
            {
                CheckMenuItem(hMenu,IDM_FILE_Result, MF_UNCHECKED);
                Log.FILE_Result = FALSE;
            } else {
                CheckMenuItem(hMenu,IDM_FILE_Result, MF_CHECKED);
                Log.FILE_Result = TRUE;
            }
            return 0L;
            case IDM_MDI_Result:
            if (Log.MDI_Result)
            {
                CheckMenuItem(hMenu,IDM_MDI_Result, MF_UNCHECKED);
                Log.MDI_Result = FALSE;
            } else {
                CheckMenuItem(hMenu,IDM_MDI_Result, MF_CHECKED);
                Log.MDI_Result = TRUE;
            }
            return 0L;

            // Toggle the Attention
            case IDM_FILE_Attention:
            if (Log.FILE_Attention)
            {
                CheckMenuItem(hMenu,IDM_FILE_Attention, MF_UNCHECKED);
                Log.FILE_Attention = FALSE;
            } else {
                CheckMenuItem(hMenu,IDM_FILE_Attention, MF_CHECKED);
                Log.FILE_Attention = TRUE;
            }
            return 0L;
            case IDM_MDI_Attention:
            if (Log.MDI_Attention)
            {
                CheckMenuItem(hMenu,IDM_MDI_Attention, MF_UNCHECKED);
                Log.MDI_Attention = FALSE;
            } else {
                CheckMenuItem(hMenu,IDM_MDI_Attention, MF_CHECKED);
                Log.MDI_Attention = TRUE;
            }
            return 0L;

            // Toggle the Message
            case IDM_FILE_Message:
            if (Log.FILE_Message)
            {
                CheckMenuItem(hMenu,IDM_FILE_Message, MF_UNCHECKED);
                Log.FILE_Message = FALSE;
            } else {
                CheckMenuItem(hMenu,IDM_FILE_Message, MF_CHECKED);
                Log.FILE_Message = TRUE;
            }
            return 0L;
            case IDM_MDI_Message:
            if (Log.MDI_Message)
            {
                CheckMenuItem(hMenu,IDM_MDI_Message, MF_UNCHECKED);
                Log.MDI_Message = FALSE;
            } else {
                CheckMenuItem(hMenu,IDM_MDI_Message, MF_CHECKED);
                Log.MDI_Message = TRUE;
            }
            return 0L;

            // Toggle the Error
            case IDM_FILE_Error:
            if (Log.FILE_Error)
            {
                CheckMenuItem(hMenu,IDM_FILE_Error, MF_UNCHECKED);
                Log.FILE_Error = FALSE;
            } else {
                CheckMenuItem(hMenu,IDM_FILE_Error, MF_CHECKED);
                Log.FILE_Error = TRUE;
            }
            return 0L;
            case IDM_MDI_Error:
            if (Log.MDI_Error)
            {
                CheckMenuItem(hMenu,IDM_MDI_Error, MF_UNCHECKED);
                Log.MDI_Error = FALSE;
            } else {
                CheckMenuItem(hMenu,IDM_MDI_Error, MF_CHECKED);
                Log.MDI_Error = TRUE;
            }
            return 0L;

            // Toggle the rowcount
            case IDM_FILE_Rowcount:
            if (Log.FILE_RowCount)
            {
                CheckMenuItem(hMenu,IDM_FILE_Rowcount, MF_UNCHECKED);
                Log.FILE_RowCount = FALSE;
            } else {
                CheckMenuItem(hMenu,IDM_FILE_Rowcount, MF_CHECKED);
                Log.FILE_RowCount = TRUE;
            }
            return 0L;
            case IDM_MDI_Rowcount:
            if (Log.MDI_RowCount)
            {
                CheckMenuItem(hMenu,IDM_MDI_Rowcount, MF_UNCHECKED);
                Log.MDI_RowCount = FALSE;
            } else {
                CheckMenuItem(hMenu,IDM_MDI_Rowcount, MF_CHECKED);
                Log.MDI_RowCount = TRUE;
            }
            return 0L;

            // Toggle the Connections
            case IDM_FILE_Connections:
            if (Log.FILE_Connections)
            {
                CheckMenuItem(hMenu,IDM_FILE_Connections, MF_UNCHECKED);
                Log.FILE_Connections = FALSE;
            } else {
                CheckMenuItem(hMenu,IDM_FILE_Connections, MF_CHECKED);
                Log.FILE_Connections = TRUE;
            }
            return 0L;

            // Toggle the IO STATS
            case IDM_STATS_IO:
            if (Log.Statistics_IO)
            {
                CheckMenuItem(hMenu,IDM_STATS_IO, MF_UNCHECKED);
                Log.Statistics_IO = FALSE;
            } else {
                CheckMenuItem(hMenu,IDM_STATS_IO, MF_CHECKED);
                Log.Statistics_IO = TRUE;
            }
            return 0L;

            // Toggle the Time STATS
            case IDM_STATS_TIME:
            if (Log.Statistics_Time)
            {
                CheckMenuItem(hMenu,IDM_STATS_TIME, MF_UNCHECKED);
                Log.Statistics_Time = FALSE;
            } else {
                CheckMenuItem(hMenu,IDM_STATS_TIME, MF_CHECKED);
                Log.Statistics_Time = TRUE;
            }
            return 0L;

            default:
            return DefFrameProc(hwnd,  hwndClient, message, wParam, lParam);
            }

        default:
        return DefFrameProc(hwnd,  hwndClient, message, wParam, lParam);
    }
}


//****************************** Function Header ******************************
//
// Function : About
//
// Description: Handles the about dialog box
//
//*****************************************************************************
int WINAPI About(HWND hDlg,UINT message,DWORD wParam,LONG lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
            // Display the version string
            SendDlgItemMessage(hDlg,IDD_VERSION,  WM_SETTEXT,(DWORD)0,(LONG)VERSION);
            return TRUE;

        case WM_COMMAND:
            if ( LOWORD(wParam == IDOK) || LOWORD(wParam == IDCANCEL) )
                EndDialog(hDlg, wParam);
            break;
    }

    return FALSE;
}  

//****************************** Function Header ******************************
//
// Function : InitEyeDlgProc
//
// Description: Handles the initialisation dialog box
//
//*****************************************************************************

int WINAPI InitEyeDlgProc(HWND hDlg,UINT message,DWORD wParam,LONG lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
            // Display the license info
            SendDlgItemMessage(hDlg,IDD_LICENSE,WM_SETTEXT,(DWORD)0,(LONG)LICENSE);
            // Set the server and regkey values
            SendDlgItemMessage(hDlg,IDD_PIPE,  EM_REPLACESEL,(DWORD)0,(LONG)szRegKey);
            SendDlgItemMessage(hDlg,IDD_SERVER,EM_REPLACESEL,(DWORD)0,(LONG)szSvr);
            // Set Check box with current value
            SendDlgItemMessage(hDlg, IDD_MDI, BM_SETCHECK, Log.MDI, (LONG) 0);
            return TRUE;

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDOK:
                    // Retrieve server name
                    strcpy(szSvr, "");
                    GetDlgItemText(hDlg, IDD_SERVER, szSvr, MAXSVR);
                    strcat(szSvr, "\0");

                    // Retrieve key name
                    strcpy(szRegKey, "");
                    GetDlgItemText(hDlg, IDD_PIPE, szRegKey, MAXRKEY);
                    strcat(szRegKey, "\0");

                    // Retrieve logging options
                    Log.MDI = SendDlgItemMessage(hDlg,IDD_MDI, BM_GETCHECK, (DWORD) 0, (LONG) 0);

                    // Initilaise the ODS server
                    if ( !InitializeODSServer() )
                        return -1;

                    // End the dialog
                    EndDialog(hDlg, wParam);
                    return 0L;

                case IDCANCEL:
                    EndDialog(hDlg, wParam);
                    return 0L;
            }
    }
    return FALSE;
}


//****************************** Function Header ******************************
//
// Function : InitialiseODSServer
//
// Description: Initialises the ODS Server
//
//*****************************************************************************
BOOL InitializeODSServer(void)
{
    char * pszTmp;
    HANDLE hThread;

    // Send the server name to the gateway's DLL module
    SetRemoteServerName(szSvr);

    // Allocate a configuration structure that is used to
    // initialize the Open Data Services application
    config = srv_config_alloc();

    if (config == NULL)
    {
        ERRBOX("Unable to allocate config structure.");
        return FALSE;
    }

    // Allow MAX_CONNECTIONS  connections at a time.
    srv_config(config, (DBINT)SRV_CONNECTIONS, MAX_CONNECTIONS, SRV_NULLTERM);
                    
    // Set the log file.
    srv_config(config, (DBINT)SRV_LOGFILE, LOG_FILE, SRV_NULLTERM);

    // Install the Open Data Services error handler.
    srv_errhandle(ChkErr);

    // Initialize the gateway and save the server handle
    // so it can be used in later functions.
    server = srv_init(config, szRegKey, SRV_NULLTERM);

    // Release the config structure
    srv_free(config);

    if (server == NULL)
    {
        ERRBOX("Unable to initialize Gateway.  Check log file");
        return FALSE;
    }

    // When starting the gateway, initialize the remote server 
    // structure. This is done in the InitServer() function.
    // All the other event handlers are also defined in the
    // InitServer() function.
    srv_handle(server, (DBINT)SRV_START, InitServer);

    // Now everything's ready to go with our gateway, so we
    // start it and keep it going until we get a stop request.
    srv_log(server, TRUE, "SQLEYE Starting", SRV_NULLTERM);

    // Start the Gateway on a separate thread
    if ( (hThread = CreateThread(NULL, 0,
        (LPTHREAD_START_ROUTINE)StartSrv,
        server,
        (DWORD)NULL,
        &lSrvThreadId)) == NULL)
    {
        ERRBOX("Unable to create server thread.");
        return FALSE;
    }
            
    // modify the control menu options
    EnableMenuItem(hMenu,IDM_INIT_ODS      ,MF_GRAYED );
    EnableMenuItem(hMenu,IDM_PAUSE_SERVER  ,MF_ENABLED);
    EnableMenuItem(hMenu,IDM_RESTART_SERVER,MF_GRAYED );

    // Modify the View menu if necessary and set values
    if (!Log.MDI) 
        {
        EnableMenuItem(hMenu,VIEWMENU,MF_BYPOSITION | MF_GRAYED);
        DrawMenuBar( ghwndMain );
        Log.MDI_Query       = FALSE;
        Log.MDI_Result      = FALSE;
        Log.MDI_Attention   = FALSE;
        Log.MDI_Message     = FALSE;
        Log.MDI_Error       = FALSE;
        Log.MDI_Timing      = FALSE;
        Log.MDI_RowCount    = FALSE;
        }

    // Change the main title to match the settings
    pszTmp = (char *)malloc(
        sizeof(" -> SQLEYE -> ") +
        sizeof(server->connect_name) +
        sizeof(szSvr) +
        sizeof("(local)") + 1
        );
    sprintf(pszTmp,"%s -> SQLEYE -> %s",server->connect_name,szSvr);
    if (strcmp(szSvr,"")==0) strcat(pszTmp,"(local)");

    if (SetWindowText(ghwndMain,pszTmp)==FALSE)
        ERRBOX("SQLEYE: Unable to change main title !");
    free(pszTmp);

    return TRUE;
}

//****************************** Function Header ******************************
//
// Function : StartSrv
//
// Description: Starts the Server
//
//*****************************************************************************
int WINAPI StartSrv(void)
{
    if (srv_run(server) == FAIL)
        MessageBox(ghwndMain,
            "Unable to start the gateway",
            "ODS Error",
            MB_OK | MB_ICONHAND);
    else
    {
        MessageBox(ghwndMain,
            "Gateway has been shut down in response to a remote request.",
            "ODS Message",
            MB_OK | MB_ICONINFORMATION);
    }

    // destroy the window
    PostMessage(ghwndMain,WM_DESTROY,0L,0L);

    return 1;
}

