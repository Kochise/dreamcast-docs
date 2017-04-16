//***************************** Module Header ******************************
// Module Name: sqleye.h
//
// SQLEYE's header file
//
// Author PeterWil 1994, Microsoft Ltd.
//***************************************************************************

//
// Resource defines
//
#define WINDOWMENU  5
#define VIEWMENU    1
#define MAXSVR      32
#define MAXUSR      30
#define MAXPWD      30
#define MAXRKEY     50
#define MAXAPPNAME  30
#define MAXLANGUAGE 30
#define MAXPASSWORD 30
#define MAXHOSTNAME 30
#define MAXFILENAME 256

#ifdef RC_INVOKED
#define ID(id) id
#else
#define ID(id) MAKEINTRESOURCE(id)
#endif

#define IDI_SLEEP       101
#define IDI_OPEN        102
#define IDI_IN          103
#define IDI_OUT         104
#define IDI_WAITING     105
#define IDI_RPC         106
#define IDI_GHOST       107
#define IDI_STATS       108
#define IDI_CONNECT     109

//
// Menu ID's
//
#define IDM_INIT_ODS    21
#define IDM_ABOUT       22
#define IDM_EXIT        23

#define IDM_AUTOSCROLL  30
#define IDM_AUTOTILE    31
#define IDM_STARTMIN    32

#define IDM_ACTIVE_ICON     40
#define IDM_INACTIVE_ICON   41
#define IDM_IN_ICON         42
#define IDM_OUT_ICON        43
#define IDM_RPC_ICON        44
#define IDM_INIT_MDI        45
#define IDM_GHOST_ICON      46
#define IDM_CONNECT_ICON    47

#define IDM_STATS_IO        50
#define IDM_STATS_TIME      51

#define IDM_CASCADE      60
#define IDM_TILE         61
#define IDM_ARRANGE      62
#define IDM_CLOSE_GHOSTS 63

#define IDM_SEND_ALL    70

#define IDM_PAUSE_SERVER    80
#define IDM_RESTART_SERVER  81

#define IDM_GHOSTS          82
#define IDM_BUILD_SCRIPTS   83
#define IDM_CLEAR_BUFFER    84

#define IDM_MDI_Query       90
#define IDM_MDI_Result      91
#define IDM_MDI_Attention   92
#define IDM_MDI_Message     93
#define IDM_MDI_Error       94
#define IDM_MDI_Timing      95
#define IDM_MDI_Rowcount    96

#define IDM_FILE_Query       10
#define IDM_FILE_Result      11
#define IDM_FILE_Attention   12
#define IDM_FILE_Message     13
#define IDM_FILE_Error       14
#define IDM_FILE_Timing      15
#define IDM_FILE_Rowcount    16
#define IDM_FILE_Connections 17
#define IDM_LICENSE          18

typedef struct _LogInfo
{
    // Are we displaying on the screen ?
    BOOL MDI;
    // If so what are we displaying on the screen
    BOOL MDI_Query;
    BOOL MDI_Result;
    BOOL MDI_Attention;
    BOOL MDI_Message;
    BOOL MDI_Error;
    BOOL MDI_Timing;
    BOOL MDI_RowCount;
    // What we are logging in the log file
    BOOL FILE_Query;
    BOOL FILE_Result;
    BOOL FILE_Attention;
    BOOL FILE_Message;
    BOOL FILE_Error;
    BOOL FILE_Timing;
    BOOL FILE_RowCount;
    BOOL FILE_Connections;
    // These tell us what other files SQLEYE is generating
    BOOL Statistics_IO;
    BOOL Statistics_Time;
    BOOL Build_Scripts;
} LOG;

// Define some message codes.
#define SRV_MAXERROR    20000
#define RPC_UNKNOWN     SRV_MAXERROR + 1
#define COMPUTE_ROW     SRV_MAXERROR + 2
#define REMOTE_MSG      SRV_MAXERROR + 3
#define SEND_FAILED     SRV_MAXERROR + 4
#define BULK_CMD        "insert bulk"

// Could make this user configurable
#define MAX_ROWS    512

// Declare the structure to use for our private data area.
// It will be passed to the event handlers in the SRV_PROC structure.
// Used for RPC only
#define MAXPARAMS   255

// The following error value must be sent back to the client in the event
// of a failure to login to the target database.  It is used in the
// init_remote() function.
#define REMOTE_FAIL 4002

// Structure to hold the information an MDI window needs
typedef struct _ClientInfo
{
    HWND       hwnd;
    int        iCurrentRow;
    // This next buffer holds the pointers to the data rows for the connection.
    // Although a ring buffer would be better in terms of always keeping the 
    // the maximum history. This way has a couple of advantages :
    // - We get to clear out the data in large chunks making us only scroll the window 
    //   once. In a ring buffer if the user was looking at the first row then we would
    //   need to scroll the window every time we added a new row (and hence deleted an 
    //   old one). This means that when we switch off Autoscrolling to save processor
    //   time we will still end up scrolling.
    //   (If we didn't scroll then we coudn't repaint the screen in responce to a
    //   WM_PAINT message)
    // - With the routine that adds rows in a different thread to the routine that
    //   draws the rows, we'd have to implement critical sections around the linked 
    //   list. 
    // - It's much easier and quicker to draw the rows.
    char      *pszRow[MAX_ROWS];
    COLORREF   color[MAX_ROWS];
    HICON      hAppIcon;  
    int
               cxClient,
               cyClient,
               iMaxVScrollPos,
               iMaxHScrollPos,
               iMaxHorRow, 
               iVScrollPos,
               iHScrollPos,
               iDisplayedVRows,
               iDisplayedHRows,
               cyChar,
               cxChar,
               cxCaps,
               iIconType;
    RECT       ExtraRect;
    BOOL       bClearBuf;
} CLIENTINFO, *PCLIENTINFO;

// Structure to hold the info for a remote connection
typedef struct remote_dbms
{
    // Linked list of structures
    // We will also use this list for sending messages and other later features.
    void       *Next;
    // DBLIB
    LOGINREC   *login;
    DBPROCESS  *dbproc;
    BOOL        bulk_mode;
    // These tell us what stats the client wants back
    BOOL        bStatisticsIO;
    BOOL        bStatisticsTime;
    // We know from the Log stucture above what stats SQLEYE wants.
    // All we need to know now is what state the connection is in and
    // we can then make intelligent decisions on when to switch stats
    // at the SQL Server on and off
    BOOL        bStatisticsIO_On;
    BOOL        bStatisticsTime_On;
    // for RPC parameters
    int         retparams[MAXPARAMS]; 
    // MDI client info
    HANDLE      hMDI; 
    // The server process
    SRV_PROC   *srvproc;
} REMOTE_DBMS;

// the colours used to display info on the screen
#define  colorRed   (COLORREF)0x000000FF
#define  colorBlue  (COLORREF)0x00FF0000
#define  colorGreen (COLORREF)0x00009600
#define  colorBlack (COLORREF)0x00000000

// a few simple message boxes
#define MSGBOX(a) MessageBox(NULL,a,"SQLEYE Message",MB_OK | MB_ICONINFORMATION)
#define ERRBOX(a) MessageBox(NULL,a,"SQLEYE Error",MB_OK | MB_ICONSTOP)
