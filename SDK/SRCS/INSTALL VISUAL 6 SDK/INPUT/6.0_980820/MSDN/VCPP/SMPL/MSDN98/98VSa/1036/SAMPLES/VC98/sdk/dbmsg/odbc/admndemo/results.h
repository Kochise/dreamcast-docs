//*---------------------------------------------------------------------------------
//|  ODBC System Administrator
//|
//|  This code is furnished on an as-is basis as part of the ODBC SDK and is
//|  intended for example purposes only.
//|
//|   Title:   RESULTS.H
//|      This file contains the prototypes and defines for anyone using RESULTS.H.
//*---------------------------------------------------------------------------------
#ifndef results_DEFS
#define results_DEFS

#include <windows.h>
#include "sql.h"
#include "sqlext.h"

//------------------------------------------------------------------------
//  Defines
//------------------------------------------------------------------------
#define SQL_TYPE                 1
#define C_TYPE                   2
#define TYPENAME                 35

#define MAXBYTES                 255


#define RDATA_WHITE              RGB(255,255,255)
#define RDATA_GRAY               RGB(190, 190, 190)
#define RDATA_BLACK              RGB(0, 0, 0)
#define RDATA_RED                RGB(255,0,0)
#define RDATA_GREEN              RGB(0,255,0)
#define RDATA_BLUE               RGB(0,0,255)
#define RDATA_LTBLUE             RGB(0,255,255)
#define RDATA_DEFAULT_TEXT             GetSysColor(COLOR_WINDOWTEXT)
#define RDATA_DEFAULT_BKGRND           GetSysColor(COLOR_WINDOW)
#define RDATA_DEFAULT_SELECT_TEXT      GetSysColor(COLOR_HIGHLIGHTTEXT)
#define RDATA_DEFAULT_SELECT           GetSysColor(COLOR_HIGHLIGHT)


//------------------------------------------------------------------------
//  Declare global variables
//------------------------------------------------------------------------



//*--------------------------------------------------------------------
//|  METADATA:
//|   This structure contains the meta data about each column in the
//|      results set.  This information can be easily retrieved using
//|      SQLColAttribute or SQLDescribeCol.
//*--------------------------------------------------------------------
typedef struct tagMETADATA {
   LPSTR       szColumnName;           // Name of the column
   char        szTypeName[TYPENAME];   // ODBC type name
   SDWORD      fSqlType;               // Numeric SQL type
   UDWORD      precision;              // Precision of the data type
   SWORD       scale;                  // Scale of the data type
   int         cbDisplaySize;          // How many bytes to display
   UINT        fAlign;                 // What alignment to take
   int         xCol;                   // x offset from 0 for column
   UINT        cColWidth;              // Width of column in pixels
   UINT        cbOffset;               // Byte offset in row storage
   } METADATA;


//*--------------------------------------------------------------------
//|  This structure is created when the user creates a results set.
//|   It must be used for all major function calls.
//*--------------------------------------------------------------------
typedef struct tagRESULTSSET {
   char        szTitle[MAXBUFF];       // Title for the window
   int         cbColumns;              // How many columns in results?
   HINSTANCE   hInst;                  // Instance handle for this dll
   HWND        hwndResults;            // Window handle for the MDI client window
   HWND        hwndClient;             // Window handle of the client window
   HWND        hwndTitle;              // Column names
   HWND        hwndList;               // Window handle for list box
   HWND        hwndHScroll;            // Window handle for horizontal scroll bar
   HWND        hwndVScroll;            // Window handle for vertical scroll bar
   HFONT       hFont;                  // Logical font for window
   int         cx;                     // Width of the average character
   int         cy;                     // Height of the average character
   int         cTitleHeight;           // Height of the title bar
   int         yTitleLoc;              // What y value to use when drawing title text
   int         cRowWidth;              // Overall width if completely shown
   METADATA    FAR * md;               // Structure with meta data
   } RESULTSSET, FAR * lpRESULTSSET;


//------------------------------------------------------------------------
//  Following structure is used to keep track of data for each column
//------------------------------------------------------------------------
typedef struct tagCOLUMNDATA {
   LPSTR    szCols;                             // Column data
   } COLUMNDATA, FAR * lpCOLUMNDATA;

//------------------------------------------------------------------------
//  Following structure should be allocated for each row
//------------------------------------------------------------------------
typedef struct tagRowData {
   COLUMNDATA FAR *     cd;                     // Pointer to column information
   LPSTR                data;                   // Buffer for all column data
   COLORREF             textColor;              // Color of text
   COLORREF             bkgrnd;                 // Color of background
   } ROWDATA, FAR * lpROWDATA;



//------------------------------------------------------------------------
//  Declare function prototypes
//------------------------------------------------------------------------
BOOL EXTFUN CreateResultsSet(RESULTSSET FAR * rs, HWND hwndClient, HINSTANCE hInst,
                           int count, LPSTR szTitle);
BOOL EXTFUN SetMetaDataColumn(RESULTSSET FAR * rs, int iCol, LPSTR szCol,
                           LPSTR szTypeName, SDWORD fSqlType, UDWORD precision, SWORD scale,
                           int cbDisplay, UINT fAlign);
ROWDATA FAR * AllocateRowData(RESULTSSET FAR * rs, COLORREF cColor, COLORREF cBkg);
BOOL EXTFUN SetColumnData(int icol, ROWDATA FAR * rd, LPSTR str);
void EXTFUN FreeRowData(RESULTSSET FAR * rs, ROWDATA FAR * rd);
void EXTFUN FreeResultsSet(RESULTSSET FAR * rs);
int  FindRightCol(RESULTSSET FAR * rs, int xLeftCol, int cWidth);
void CreateResultsFont(RESULTSSET FAR * rs, HWND hwnd, LOGFONT FAR * lf);
void DrawRowData(RESULTSSET FAR * rs, DRAWITEMSTRUCT FAR * dwitem,
                           int xLeftCol, int xRightCol);
void INTFUN DrawColumnTitles(HDC hdc, RESULTSSET FAR * rs,
                           RECT FAR * crect, int xLeftCol, int xRightCol);
void  HandleHScroll(WPARAM wParam, RESULTSSET FAR * rs,
                           HWND hwnd, HWND hwndHScroll, int FAR * xLeftCol, int FAR * xRightCol,
                           HWND hwndList, int cbColumns, int cbClient, RECT FAR * tRect);
void HandleVirtualHScroll(WPARAM wParam, HWND hwndList, HWND hwndOwner);
int   AddRowData(RESULTSSET FAR * rs, ROWDATA FAR * rd);
SWORD GetNumResultsCols(HSTMT hstmt);
LPSTR GetTypeName(int type, int fType);
void  ConvertSqlTypeToChar(RESULTSSET FAR * rs, int col, LPSTR inbuff,
                           LPSTR outbuff, SDWORD rtnd);
void  BinToChar(LPSTR outstr, LPSTR instr, SDWORD count);


#endif
