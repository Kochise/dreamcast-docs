/*
    Header File for QURYDEMO application
    Created by Microsoft Corporation.
*/
#ifdef WIN32
#define CONSTSTR(name, str) const char name[]=str
#else
#define CONSTSTR(name, str) const char FAR * name=str
#endif


#ifdef RC_INVOKED
#define ID(id) id
#else
#define ID(id) MAKEINTRESOURCE(id)
#endif

/* Resource Identifiers */

#define BMP_NEWQUERY        ID(10)  // new window button bitmap
#define BMP_RUNQUERY        ID(20)  // exec query button bitmap
#define APPICON             ID(30)  // application icon
#define QUERYWINDOWICON     ID(40)  // MDI Child window icon
#define QURYDEMOMENU        ID(50)  // Application menu
#define CONNECTDIALOG       ID(60)  // connect modal dialog box
#define DISCONNECTDIALOG    ID(70)  // disconnect modal dialog box
#define ABOUTDIALOG         ID(80)  // about modal dialog box
#define MDICHILDDIALOG      ID(90)  // MDI Child modeless dialog box
#define APPACCELERATOR      ID(100) // Accelerator table for the app

/* Menu Identifiers */

#define IDM_POPUPAPPSYS     10  // Placeholder, used by status bar
#define IDM_POPUPMDISYS     20  // Placeholder, used by status bar
#define IDM_POPUPLOGIN      100 // Placeholder, used by status bar
#define IDM_CONNECT         110
#define IDM_DRIVERCONNECT   120
#define IDM_DISCONNECT      130 
#define IDM_EXIT            140
#define IDM_POPUPQUERY      150 // Placeholder, used by status bar
#define IDM_QUERY           160
#define IDM_NEW             170
#define IDM_POPUPWINDOW     180     // Placeholder, used by status bar
#define IDM_TILE            190
#define IDM_CASCADE         200
#define IDM_ICONS           210
#define IDM_CLOSEALL        220
#define IDM_POPUPHELP       230 // Placeholder, used by status bar
#define IDM_APPHELP         240
#define IDM_ABOUT           250

#define IDM_MDICHILD        260

/* child window ids */

#define IDW_TOOLBAR         10
#define IDW_STATUSBAR       20
#define IDW_MDICLIENT       30

#define IDW_CRSRLIST        10  // toolbar comboboxes
#define IDW_STMTLIST        20

#define IDCOMBO_DATASOURCE  10  // connect dialog box controls
#define IDTEXT_USERNAME     20
#define IDTEXT_PASSWORD     30

#define IDLIST_HDBC         10  // disconnect dialog box controls
#define IDLIST_STMT         20
#define IDCLOSE_ACTVTY      30
#define IDDISCONNECT        40
#define IDICON_WARN         50

#define IDTEXT_PRMPT        10  // MDI child's modeless dialog controls
#define IDTEXT_SQL          20
#define IDLIST_RSLT         30

/* MDI Child Window Offsets */

#define CBWNDEXTRA          4   // storage in MDI Child Window
#define GWLAPP_HDLG         0   // child dialog handle

/* Help File */

#define SAMPLESHELPFILE     "..\\doc\\odbcsmpl.hlp"
#define HLP_QURYDEMO        30

/* Other Constants */

#define MAXCHILDWNDS        10          //maximum child windows allowed
#define MAXBUFLEN           256         //display buffer size
#define MAX_COL             15          //maximum column in result set
#define MAX_ROW             100         //maximum number of rows
#define MAXDATALEN          25          //maximum data length per column
#define MAXDISPLAYSIZE      MAX_COL*(MAXDATALEN+1)
#define MINWIDTH            415         //minimum width of app window
#define MINHEIGHT           350         //minimum height of app window
#define LISTTABSTOP         100         //tabstop in the display listbox
#define LISTHORZSCROLL      (LISTTABSTOP*2)     //horizontal scroll for the listbox
#define LISTHORZEXT         0           //horizontal extent inthe list box
#define WINDOWMENUPLACE     2           //Window menu place for adding MDI child windows
#define IDT_STATUSTIMER     1           //timer id
#define TIMERDELAY          60000           //timer duration
#define BTTNX               345         //first toolbar button location
#define BTTNY               2           //button y position
#define BTTNWIDTH           25                      //button width
#define BTTNHEIGHT          23                      //button height
#define BTTNMARGIN          5           //distance between toolbar buttons
#define TOOLBARMARGINY      5           //fixed margin w/o combobox height
#define STATUSBARMARGINY    8           //fixed margin w/o textbox height

/* String Constants */

#define POPUPLOGIN          "&Login"
#define MENUITEMCONNECT     "&Connect... \aCtrl+C"
#define MENUITEMDRIVERCONNECT   "D&river Connect... \aCtrl+R"
#define MENUITEMDISCONNECT  "&Disconnect... \aCtrl+D"
#define MENUITEMEXIT        "E&xit"
#define POPUPQUERY          "&Query"
#define MENUITEMQUERY       "&Execute SQL \aCtrl+E"
#define MENUITEMNEW         "&New Query \aCtrl+N"
#define POPUPWINDOW         "&Window"
#define MENUITEMTILE        "&Tile"
#define MENUITEMCASCADE     "&Cascade"
#define MENUITEMICONS       "Arrange &Icons"
#define MENUITEMCLOSEALL    "Close &All"
#define POPUPHELP           "&Help"
#define MENUITEMAPPHELP     "&Help on Qurydemo"
#define MENUITEMABOUT       "&About Qurydemo..."

#ifdef WIN32
#define ODBCFRAMECLASS      "QDEMO32MAIN"
#else
#define ODBCFRAMECLASS      "QDEMOMAIN"
#endif

#define ODBCTOOLCLASS       "QDEMOTool"
#define ODBCSTATUSCLASS     "QDEMOStatus"
#define ODBCMDICLASS        "QDEMOMDI"
#define COMBOBOXCLASS       "COMBOBOX"
#define MDICLIENTCLASS      "MDICLIENT"
#define UNTITLED            "Untitled"
#define APPTITLE            "ODBC Sample Program"
#define EXECERROR           "Execution Error"
#define INITERROR           "Failed to initialize ODBC interface"
#define CLASSERROR          "Failed to register application class"
#define CREATEMAINERR       "Failed to create application main window"
#define CREATECHILDERR      "Failed to create a new window"
#define ALPHABETS           "abcdefghijklmnopqrstuvwxyz"
#define TIMETEXT            "MM:MM MM"
#define DATETEXT            "MMM-MM"
#define TIMEFORMAT          " %I:%M %p"
#define DATEFORMAT          " %b-%d"
#define NODSNERR            "Please provide a Data Source"
#define MOREINFO            "Incomplete Information"
#define STATUSPOPUPAPPSYS   " Control menu for the application "
#define STATUSPOPUPMDISYS   " Control menu for the window "
#define STATUSRESTORE       " Restore window to normal "
#define STATUSMOVE          " Move window "
#define STATUSSIZE          " Size window "
#define STATUSMINIMIZE      " Minimize window "
#define STATUSMAXIMIZE      " Maximize window "
#define STATUSCLOSE         " Close window "
#define STATUSNEXTWINDOW    " Switch to next window "
#define STATUSPREVWINDOW    " Switch to previous window "
#define STATUSTASKLIST      " Bring up task list "
#define STATUSPOPUPLOGIN    " Login and logout commands "
#define STATUSCONNECT       " Connect with default parameters... "
#define STATUSDRIVERCONNECT " Connect with driver dialogs... "
#define STATUSDISCONNECT    " Close open connections... "
#define STATUSEXIT          " Exit application "
#define STATUSPOPUPQUERY    " Query commands "
#define STATUSQUERY         " Execute SQL statement... "
#define STATUSNEW           " New window on current connection... "
#define STATUSPOPUPWINDOW   " Window management commands "
#define STATUSTILE          " Tile all normal child windows "
#define STATUSCASCADE       " Cascade all normal child windows "
#define STATUSICONS         " Arrange iconic child windows "
#define STATUSCLOSEALL      " Close all child windows "
#define STATUSMDICHILD      " Activate the window marked as %d"
#define STATUSPOPUPHELP     " Help commands "
#define STATUSAPPHELP       " Display help on application "
#define STATUSABOUT         " About application "
#define STATUSDEFAULT       " Ready "

#define DEFDBNAME               "?"
#define DSN_HDBC_FORMAT         "%s!%lX"
#define DSN_HDBC_HSTMT_FORMAT   "DSN=%s!HDBC=%lX!HSTMT=%lX"
#define SCANDSNHDBC_FORMAT      "%[^!]!%lX"
#define SCANHDBC_FORMAT         "%*[^!]!%lX"
#define SCANHDBC_TITLEFORMAT    "DSN=%*[^!]!HDBC=%lX"
#define SCANHDBCHSTMT_FORMAT    "DSN=%*[^!]!HDBC=%lX!HSTMT=%lX"
#define SCANHSTMT_TITLEFORMAT   "DSN=%*[^!]!HDBC=%*lX!HSTMT=%lX"
#define SCAN_HDBC_FORMAT			"%*c%lX"
#define SCAN_HDBC_TITLEFORMAT		"DSN=%*cHDBC=%lX"


#define CUR_MARK            "<-"
#define CURQUERY_STRING     "Query!%lX<-"
#define QUERY_STRING        "Query!%lX"
#define MAKECONNECT         "Please connect to a data source using Login menu."
#define OPENWINDOW          "Please open a window from Query menu."
#define NOHDBCERROR         "No Connection Available"
#define NOHSTMTERROR        "No Query Window Available"
#define MAXCHILDEXCEEDED    "Please close a child window and try again."
#define MAXCHLDERR          "Error - Too many Child Windows"
#define COLTRUNC_WARNG      "Number of columns in display truncated to %u"
#define ROWTRUNC_WARNG      "Number of rows in display truncated to %u"
#define TRUNCERR            "Data Truncation"
#define CLOSEALLHDBC        "All open connections have been closed."
#define LOGOUTINFO          "Log Out Information"
#define SQLERR_FORMAT       "SQL Error State:%s, Native Error Code: %lX, ODBC Error: %s"
#define SQLERRMSGTITLE      "SQL_ERROR results"
#define SQLERRCNTDTITLE     "SQL_ERROR results continued"
#define SQLWRNMSGTITLE      "SQL_SUCCESS_WITH_INFO results"
#define SQLWRNCNTDTITLE     "SQL_SUCCESS_WITH_INFO results continued"
#define NULLDATASTRING      "SQL_NULL_DATA"



/* Globals */

HWND        hWndFrame;      // Main Frame Window handle
HWND        hWndToolbar;    // Toolbar window handle
HWND        hWndCrsrList;   // hdbc(s) combobox on the tool bar
HWND        hWndStmtList;   // hstmt(s) combobox on the tool bar
HWND        hWndStatusbar;  // status bar handle
HWND        hWndMDIClient;  // MDI Client window handle
HWND        hWndActiveChild;// Current active MDI Child window
HINSTANCE   hAppInstance;   // Application instance
WORD        wStatusText;    // Status text state
int         iTimex;         // Time box (on the status bar) width
int         iDatex;         // Date box (on the status bar) width
RECT        rectStatusText; // Text box on the status bar




#ifdef __SQL    // internal to query.c

int         nChildCount;            // Number of child windows currently open
SQLHENV     henv;                   // Environment Handle
char        szDispBuffer[MAXDISPLAYSIZE+1]; // Display Buffer
UCHAR       rgbData[MAX_COL][MAXDATALEN];   // Results Data Array
SDWORD      dwDataLen[MAX_COL];     // Results Data Length Array

#endif

/* Macros and Function Prototypes */

#ifdef WIN32
#define     ACTIVATEWINDOW(h)   SetForegroundWindow(h)
#else
#define     ACTIVATEWINDOW(h)   SetFocus(h)
#endif

#define DRAWBTTNRECT(h,x,y,cx,cy)   MoveToEx(h,x+1,y,NULL);\
                    LineTo(h,x+cx,y);\
                    MoveToEx(h,x+cx,y+1,NULL);\
                    LineTo(h,x+cx,y+cy);\
                    MoveToEx(h,x+cx-1,y+cy,NULL);\
                    LineTo(h,x,y+cy);\
                    MoveToEx(h,x,y+cy-1,NULL);\
                    LineTo(h,x,y);

#define DRAWBTTNLIFT1(h,x,y,cx,cy)  MoveToEx(h,x+1,y+cy-1,NULL);\
                    LineTo(h,x+1,y+1);\
                    LineTo(h,x+cx-1,y+1);

#define DRAWBTTNLIFT2(h,x,y,cx,cy)  MoveToEx(h,x+1,y+cy-1,NULL);\
                    LineTo(h,x+cx-1,y+cy-1);\
                    LineTo(h,x+cx-1,y);\
                    MoveToEx(h,x+2,y+cy-2,NULL);\
                    LineTo(h,x+cx-2,y+cy-2);\
                    LineTo(h,x+cx-2,y+1);

int PASCAL      WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
long    CALLBACK    MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
long    CALLBACK    ToolbarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
long    CALLBACK    StatusbarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
long    CALLBACK    MDIChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL    CALLBACK    ConnectDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL    CALLBACK    DisconnectDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL    CALLBACK    AboutDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL    CALLBACK    MDIChildDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
VOID    FAR PASCAL  DrawBitmap(HDC hDC, int iLeft, int iTop, HBITMAP hBitmap);

BOOL    FAR PASCAL  InitSQLEnvironment();
void    FAR PASCAL  DisplayDatabases(HWND hWnd);
BOOL    FAR PASCAL  ConnectDatabase(HWND hWnd);
BOOL    FAR PASCAL  DriverConnectDatabase(HWND hWnd);
void    FAR PASCAL  DisplayConnections(HWND hWndhdbc);
void    FAR PASCAL  DisplayQueries(HWND hWndhstmt, HWND hWndhdbc, int nCrsrIndex);
void    FAR PASCAL  NewQueryWindow();
void    FAR PASCAL  ChangeCurrentQuery(HWND hWndStmtList);
void    FAR PASCAL  ChangeCurrentCursor(HWND hWndCrsrList);
void    FAR PASCAL  DisplayNewCrsrAndStmt();
void    FAR PASCAL  FreeConnect(HWND hWndhdbc);
void    FAR PASCAL  FreeQuery(HWND hWndhstmt, HWND hWndhdbc, int nIndex);
void    FAR PASCAL  CloseQueryWindow(HWND hWnd);
BOOL    FAR PASCAL  FreeSQLEnvironment();
void    FAR PASCAL  ExecuteQuery();
BOOL    FAR PASCAL  CloseDatabases();

#ifdef __SQL    // internal to query.c

void    FAR PASCAL  DisplayError(SQLRETURN nResult, HWND hWnd, SWORD fHandleType, SQLHANDLE handle);

#endif
/******************************* End of File ********************************/
