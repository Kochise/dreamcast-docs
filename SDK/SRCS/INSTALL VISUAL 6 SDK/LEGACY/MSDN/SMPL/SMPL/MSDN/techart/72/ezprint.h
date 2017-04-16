/* Constants */
#define 	XEXT	        1000
#define  	YEXT	        1000
#define    	NUMCHAR 256
#define    	IDS_SAP_FAILED 					1000
#define    	IDS_SD_FAILED					1001	
#define    	IDS_PRTMGR_DOCNAME 	1002	
#define   	IDS_ERRORMSG					1003	

#define 	PRTJOBNAME						32

/* Color macros */
#define BLACK RGB(0x00, 0x00, 0x00)

/* Printing structure  that defines the object and it's characteristics */
typedef struct tagPRINTSTRUCT
  {
    int  nPrintObject;
    UINT uiTextFlags;
    UINT uiFillFlags;
    UINT uiPenFlags;
    int  nXOrg;
    int  nYOrg;   
    int  nXExt;
    int  nYExt;
    int  nPointSize;
    char szText[NUMCHAR];
  } PRINTSTRUCT;
  
typedef PRINTSTRUCT FAR * LPPRINTSTRUCT;

/* Print Objects */
#define PO_TEXT 	    0
#define PO_RECT 	    1
#define PO_LINE 	    2
#define PO_CHART    3
#define PO_NEWPAGE	    4
#define PO_GRID 	   5

/* Object Flags */
#define TEXT_NORMAL	    0x0000
#define TEXT_BOLD	    0x0001
#define TEXT_ITALIC	    0x0002
#define TEXT_UNDERLINED     0x0004
#define TEXT_STRIKEOUT	    0x0008
#define TEXT_RECT	    0x0010
#define TEXT_LEFT	    0x0020
#define TEXT_RIGHT	    0x0040
#define TEXT_CENTER	    0x0080
#define TEXT_EXPANDTABS     0x0100
#define TEXT_SINGLELINE     0x0200
#define TEXT_NOCLIP	    0x0400

#define FILL_NONE	    0x0000
#define FILL_GRAY	    0x0001
#define FILL_LTGRAY	    0x0002
#define FILL_DKGRAY	    0x0004
#define FILL_BLACK	    0x0008

#define PEN_SOLID	    0x0000
#define PEN_DOT		    0x0001
#define PEN_DASH	    0x0002
#define PEN_THIN	    0x0004
#define PEN_THICK	    0x0008
#define PEN_DASHDOT	    0x0010
#define PEN_DASHDOTDOT	    0x0020

typedef struct tagPAGESTRUCT
  {
    UINT   VOx;
    UINT   VOy;
    UINT   VEx;
    UINT   VEy;
    UINT   WOx;
    UINT   WOy;
    UINT   WEx;
    UINT   WEy;
    POINT  LogPels;
    POINT  LogPage;
  } PAGESTRUCT;

typedef PAGESTRUCT FAR * LPPAGESTRUCT;

/* Function prototypes */
int  FAR PASCAL LibMain(HANDLE, WORD, WORD, LPSTR);
int  FAR PASCAL WEP (int);
int  FAR PASCAL PrintAbortDlg (HWND hDlg, unsigned msg, WORD wParam, LONG lParam);
BOOL FAR PASCAL StartDocument(HWND, BOOL);
BOOL FAR PASCAL EndDocument(HWND);
BOOL FAR PASCAL PrintAbortProc (HDC hDC, short code);
int  FAR PASCAL PrintObject(LPPRINTSTRUCT);
int PrintObjectIndirect(LPPRINTSTRUCT);

/* Global Variables */
#if defined  MAIN
HANDLE	hInst;
PRINTDLG	pd;
BOOL	bPDInit	= FALSE;
LPPRINTSTRUCT	lpPStruct = NULL;
int		uiLineSpacing;
BOOL	bAbort;
HWND	hDlgAbort;
PAGESTRUCT	Page;
#else                                                      
extern HANDLE	      hInst;
extern PRINTDLG       pd;
extern BOOL	      bPDInit;
extern LPPRINTSTRUCT  lpPStruct;
extern int	      uiLineSpacing;
extern BOOL	      bAbort;
extern HWND	      hDlgAbort;
extern PAGESTRUCT     Page;
#endif
