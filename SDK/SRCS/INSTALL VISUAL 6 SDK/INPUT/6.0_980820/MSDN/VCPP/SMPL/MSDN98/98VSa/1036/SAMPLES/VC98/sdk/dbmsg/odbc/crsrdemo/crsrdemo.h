/*--------------------------------------------------------------------------
  Cursors.h -- General constants, types, prototypes and variables

  This code is furnished on an as-is basis as part of the ODBC SDK and is
  intended for example purposes only.

--------------------------------------------------------------------------*/

#ifndef __CURSORS_H
#define __CURSORS_H


#ifdef	_M_ALPHA
#define  Print(x,y,z) wsprintf(x,y,z)
#else
#define Print(x,y,z)  wvsprintf(x,y,z)
#endif


#ifdef INCL_GLOBAL
#define GLOBAL
#define INITHAND(name, type)    type name = NULL
#ifdef WIN32
#define CONSTSTR(name, str) const char name[]=str
#else
#define CONSTSTR(name, str) const char FAR * name=str
#endif
#else
#define GLOBAL  extern
#define INITHAND(name, type)    extern type name
#ifdef WIN32
#define CONSTSTR(name, str) extern const char name[]
#else
#define CONSTSTR(name, str) extern const char FAR * name
#endif
#endif


// Constants ---------------------------------------------------------------
#ifdef WIN32
#define EXPFUNC __stdcall
#define INTFUNC __stdcall
#else
#define EXPFUNC __export __far __pascal
#define INTFUNC __pascal
#endif


#define INLINE __inline

// Miscellaneous
#define cbMAXSQL    512                    // Maximum SQL string length
#define cbSTRLEN    256                    // Maximum string length
#define cbINTLEN    16                     // maximum length of an decimal
                                           // integer in text format
#define cbBUFSIZE   4096                   // Working buffer size
#define cPOINTS 10                         // Font point size
#define cxBORDER    6                      // Painting border
#define cyBORDER    2                      // Painting border
#define MAX_MAXBIND 200                    // maximum length of any column
#define DEF_MAXBIND 50                     // default maximum length

// Miscellaneous strings
CONSTSTR(szMDICLIENT,   "MDICLIENT");
CONSTSTR(szCHILDCLASS,  "CursorsChild");
CONSTSTR(szFRAMECLASS,  "CursorsFrame");
CONSTSTR(szSTATICCLASS, "STATIC");
CONSTSTR(szEDITCLASS,   "EDIT");
CONSTSTR(szSCROLLCLASS, "SCROLLBAR");
CONSTSTR(szDSNKEY,      "DSN=");
CONSTSTR(szDATATRUNC,   "01004");
CONSTSTR(szTITLEFMT,    "%s (CURSOR%04d)");
CONSTSTR(szCURSORNAME,  "CURSOR%04d");
CONSTSTR(szFONT,        "MS Sans Serif");
CONSTSTR(szRECORD,      "Record:");
CONSTSTR(szRECNUM,      "%6d");
CONSTSTR(szHELPFILE,    "..\\doc\\odbcsmpl.hlp");  // Samples help file
CONSTSTR(szKeyword,		"cursor demo features");

#define HLP_CRSRDEMO 40     // magic from help file

// Macros
#define AllocPtr(x) GlobalAllocPtr(GHND, (x))
#define FreePtr(x)      if ((x)) GlobalFreePtr((x))
#define DBCError(hwnd,x)    ODBCError(hwnd,SQL_HANDLE_DBC, g_hdbc, (x))
#define ENVError(hwnd,x)    ODBCError(hwnd,SQL_HANDLE_ENV, g_henv,  (x))

#define SUCCESS(x)  (((x)==SQL_SUCCESS) || ((x)==SQL_SUCCESS_WITH_INFO))

#define ISBLANK(x)      ((x) == ' ')
#define ISCOMMA(x)      ((x) == ',')
#define ISNUM(x)        (((x) >= '0') && ((x) <= '9'))
#define ISLPAREN(x)     ((x) == '(')
#define ISRPAREN(x)     ((x) == ')')
#define ISPERIOD(x)     ((x) == '.')
#define ISRETURN(x)     (((x) == '\n') || ((x) == '\r'))
#define ISTAB(x)        ((x) == '\t')
#define ISWHITE(x)      (ISBLANK(x) || ISTAB(x) || ISRETURN(x))

#define ROW_BINDING(x)  (x->fBindByRow ==   IDC_RADIO_BINDROW)
#define IS_ALLWFETCH(x) (x->dwGuiFlags & GUIF_ALWAYSFETCH)
#define UNREF_PARAM(x)  (x)

#define MAXNAME     100


// Types -------------------------------------------------------------------
typedef UWORD  FAR  *LPUWORD;
typedef SDWORD FAR  *LPSDWORD;

typedef struct tagBIGCOL {                 // Big column structure
    char        szName[cbSTRLEN];          //   Column name
    LPSTR       lpsz;                      //   Pointer to column data
    SDWORD      cb;                        //   Length of data
} BIGCOL, FAR *LPBIGCOL;

typedef struct tagCOL {                    // Column structure
    char        szName[cbSTRLEN];          //   Column name
    SDWORD      cb;                        //   Column width (transfer width)
    SDWORD      cbc;                       //   Column width (display  width)
    SWORD       fCType;                    //   C type
    SWORD       fSqlType;                  //   ODBC Sql type
    LPSDWORD    lpcb;                      //   Pointer to returned width
    LPBYTE      lpb;                       //   Pointer to returned data
} COL, FAR *LPCOL;

typedef struct tagCHILD {                  // Child window variables
    HWND        hwnd;                      //   Current window handle
    BOOL        fInSetScroll;              //   In SetScroll function flag
    BOOL        fIsMinimized;              //   Window minimized flag
    BOOL        fHaveMouse;                //   Mouse captured flag
    int         iMouseRow;                 //   Mouse down row

    int         ccols;                     //   Number of characters per line
    int         crowwin;                   //   Rows per window
    int         ccolwin;                   //   Character columns per window
    HWND        hwndVScroll;               //   Vertical scroll bar
    HWND        hwndHScroll;               //   Horizontal scroll bar
    BOOL        fVScroll;                  //   Vertical scroll active flag
    BOOL        fHScroll;                  //   Horizontal scroll active flag

    LPINT       lpnTabs;                   //   Array of tab values
    char        szFmt[cbSTRLEN];           //   Format string
    char *     rglpv;                     //   wvsprintf data array

    HRGN        hrgn;                      //   Clip region
    LPSTR       lpsz;                      //   Working buffer

    SQLHSTMT    hstmt;                     //   ODBC statement handle
    SQLHSTMT    hstmtTmp;                  //   Temp ODBC statement handle
    LPSTR       sql;                       //   SQL statement

    SWORD       ccol;                      //   Number of result columns
    LPCOL       lpcol;                     //   Column information array
    BOOL        fResultSetExists;          //   Result set exists flag
    BOOL        fDataFetched;              //   Data has been fetched flag
    LPUWORD     lpfStatus;                 //   Row status array

    BOOL        fBindByRow;                //   Row-wise binding flag
    LPBYTE      lpb;                       //   Row-wise binding buffer
    SDWORD      cbrow;                     //   Row-wise binding step quantity

    UWORD       fConcurrency;              //   Scroll concurrency
    SDWORD      crowKeyset;                //   Keyset option
    UWORD       crowRowset;                //   Rowset option
    BOOL        fRowset;                   //   crowRowset has been modified
    char        szRowset[cbINTLEN];        //   text format buffer of inputed
                                           //   crowRowset

    BOOL        fAsync;                    //   Async enabled flag
    BOOL        fCanceled;                 //   Request canceled flag
    UWORD       irowPos;                   //   Positioned row (via SQLSetPos)
    SDWORD      irow;                      //   First row in row set (absolute)
    UWORD       cBind;                     //   Number of bound columns
    BOOL        fBind;                     //   cBind's been modified 
    char        szBind[cbINTLEN];          //   a buffer to store the
                                           // text format of inputed cBind
    BOOL        fBindAll;                  //   Bind all columns flag
    UWORD       ccolRetrieved;             //   Number of retrieved columns

    SDWORD      arow;                      //   Fetch absolute value
    SDWORD      rrow;                      //   Fetch relative value
    UCHAR       szQualifier[MAXNAME];      //   qualifier name
    UCHAR       szTable[MAXNAME];          //   table name
    UCHAR       szUser[MAXNAME];           //   user name
    UCHAR       szType[MAXNAME];           //   table type (for SQLtables)
    UCHAR       szColName[MAXNAME];        //   column name (for SQLColumns)
    UWORD       dwOperation;               //   operation to perform  (mistype)
    DWORD       dwGuiFlags;                //   flags and state to the gui
    SDWORD      crowMaxBind;               //   max length to bind col to
    BOOL        fMaxBind;                  //   crowMaxBind has been modified
    char        szMaxBind[cbINTLEN];       //   the text format buffer of the 
                                           //   inputed crowMaxBind
    DWORD       crowCurrent;               //   current actual size of rowset
    BOOL        fNoConcurrency;            //   driver doesn't support concur
    BOOL        fNoCursorType;             //   no cursor type
    UWORD       dwRadioButton;             //   What radio button in info dlg?
    UWORD       FetchOP;
#ifdef THREAD
    CRITICAL_SECTION ThreadCreation;
    HANDLE hThread;
#endif
} CHILD, FAR *LPCHILD;

#define     OPER_SELECT     1
#define     OPER_TABLES     2
#define     OPER_PRIVS      3
#define     OPER_STATS      4
#define     OPER_PROCS      5
#define     OPER_COLUMN     6
#define     OPER_TYPES      7


#define     GUIF_TABLES_RADIO   0x00001     // 'tables' radio button set
#define     GUIF_ALWAYSFETCH    0x00002     // always fetch first

#define SetDlgText(hdlg,id,text)  Edit_SetText(GetDlgItem(hdlg,id), text)

// dialog pair -- dialog and id

typedef struct tagDialogPair{
    LPSTR   szDlgPairTitle;
    int     iDlgPairDlgId;
} DIALOG_PAIR;




// Prototypes --------------------------------------------------------------
// General routines
void INTFUNC AdjustMenus(void);
int  INTFUNC DoDialog(HWND, int, DLGPROC);
void INTFUNC DoMessage(HWND, UINT);
void INTFUNC GetCurrentValue(LPSTR, LPCOL, LPCHILD);
BOOL INTFUNC IsUpdateable(SDWORD);
void INTFUNC MakeTable(void);
BOOL INTFUNC ODBCError(HWND, SWORD, SQLHANDLE, SQLRETURN);
BOOL INTFUNC SetCurrentValue(LPSTR, LPCOL, LPCHILD);
SQLRETURN INTFUNC PrepareStmt(LPCHILD lpchild);
BOOL INTFUNC ProcessResults(LPCHILD lpchild);

// Window/Dialog procedures
BOOL CALLBACK InitControlCallback( HWND , LPARAM);

INLINE  BOOL    SetOrGetCheck( HWND,  int   , BOOL);
INLINE  VOID    SetOrGetEditArray( HWND, UCHAR FAR *, int);

VOID    INTFUNC  InitializeDialogControls( HWND hDlg, LPCHILD   lpChild);
VOID    INTFUNC  ControlValue ( LPCHILD, HWND, HWND , int   , int );
BOOL    INTFUNC  InitializeListBox( HWND, int, const DIALOG_PAIR FAR * , int, int);
BOOL    INTFUNC  SetHiddenFields( HWND  hDlg, int       iAct);
BOOL    INTFUNC  AlignToControl( HWND   hWnd, HWND  hDlg, int       iCtlId);
BOOL    CALLBACK OptionsDlgProc(HWND hdlg,UINT msg,WPARAM wparam,LPARAM lparam);
VOID    INTFUNC  ClassOnCommand(HWND hWnd, int iId, HWND hWndCtl, UINT uNotify);
BOOL    CALLBACK ChildOptDlgProc(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL    CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK AbsDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK DataDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK FindDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK MakeTableDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK OptDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK RelDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK StmtDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK TableDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK UpdateDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK SQLTablesDlgProc(HWND,UINT,WPARAM,LPARAM);

LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK FrameProc(HWND, UINT, WPARAM, LPARAM);


// Variables ---------------------------------------------------------------
GLOBAL  HWND        g_hwnd;                // Main window handle
GLOBAL  HWND        g_hwndClient;          // MDI client window handle
GLOBAL  HWND        g_hwndChildDialog;     // child dialog if active
GLOBAL  HINSTANCE   g_hinst;               // Instance handle
GLOBAL  HACCEL      g_haccel;              // Accelerators

GLOBAL  HMENU       g_hmenuInit;           // Pre-connection menu
GLOBAL  HMENU       g_hmenuInitWindow;     //   Windows menu (for MDI)
GLOBAL  HMENU       g_hmenuFrame;          // Connection made menu
GLOBAL  HMENU       g_hmenuFrameWindow;    //   Windows menu (for MDI)
GLOBAL  HMENU       g_hmenuChild;          // Child window menu
GLOBAL  HMENU       g_hmenuChildWindow;    //   Windows menu (for MDI)

GLOBAL  int         g_cxVScroll;           // Width  of vertical scroll bar
GLOBAL  int         g_cyHScroll;           // Height of horizontal scroll bar

GLOBAL  int         g_cx;                  // Width  of a character
GLOBAL  int         g_cy;                  // Height of a character

GLOBAL  int         g_cxRecord;            // Width of record count area
GLOBAL  int         g_cxRecnum;            // Width of record number

GLOBAL  HFONT       g_hfontName;           // Column name font
GLOBAL  HFONT       g_hfontData;           // Data font

GLOBAL  HBRUSH      g_hbrWin;              // Window background brush
GLOBAL  HBRUSH      g_hbrBtn;              // Button face brush
GLOBAL  HBRUSH      g_hbrScroll;           // Scroll bar brush

GLOBAL  SQLHENV     g_henv;                // ODBC environment handle
GLOBAL  SQLHDBC     g_hdbc;                // ODBC connection handle

GLOBAL  SWORD       g_cbName;              // Maximum column name width
GLOBAL  char        g_szQuoteChar[2];      // Identifier quote char
GLOBAL  BOOL        g_fConnected;          // Connected flag
GLOBAL  BOOL        g_fAsyncSupported;     // Driver supports async flag
GLOBAL  char        g_szDSN[SQL_MAX_DSN_LENGTH+1];  // Data source name
GLOBAL  int         g_cChild;              // Number of child windows
GLOBAL  int         g_cCursor;             // Current cursor number

GLOBAL  char        g_szTable[cbSTRLEN];   // Make table name
GLOBAL  SDWORD      g_mrows;               // Make table row count

GLOBAL  char        g_szTITLE[cbSTRLEN];   // App title
GLOBAL  char        g_szNoRow[cbSTRLEN];   // No row string
GLOBAL  char        g_szRowError[cbSTRLEN];// No row string
GLOBAL  char        g_szNull[cbSTRLEN];    // Null column string
GLOBAL  char        g_szRowDeleted[cbSTRLEN]; // Row deleted string
GLOBAL  char        g_szUnknown[cbSTRLEN]; // Unknown string



// Constants ---------------------------------------------------------------
#define WMU_INIT            (WM_USER+1)
#define WMU_DROPTABLE       (WM_USER+2)
#define WMU_INSERTREC       (WM_USER+4)
#define WMU_CLEANUP         (WM_USER+5)
#define WMU_CANCEL          (WM_USER+6)
#define WMU_NEWOPTION       (WM_USER+7)         // new options child menu
#define WMU_SETSUBTEXT      (WM_USER+8)         // set subtext (options group)

#define ACT_INIT            1                   // initialize control
#define ACT_TRIGGER         2                   // control has been set

#endif // __CURSORS_H
