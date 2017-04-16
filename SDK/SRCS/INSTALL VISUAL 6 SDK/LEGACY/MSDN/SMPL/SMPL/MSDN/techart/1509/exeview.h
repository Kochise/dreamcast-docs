#include <windows.h>


#define IDR_MAINICON		     20
#define IDR_EXEVIEWMENU 	     30

#define IDS_EXEVIEWCLASS	     1000
#define IDS_MEMVIEWCLASS	     1001
#define IDS_MEMVIEWTITLE	     1002
#define IDS_CAPTION		     1003
#define IDS_ERROR		     1005
#define IDS_CANTOPENFILE	     1006
#define IDS_CANTMAPVIEW 	     1007
#define IDS_CANTCREATEMAPPING	     1008
#define IDS_EXEFILEEXT		     1009
#define IDS_FILEOPENTITLE	     1010
#define IDS_NTFILESIGNATURE	     1020
#define IDS_OS2FILESIGNATURE	     1021
#define IDS_OS2FILESIGNATURELE	     1022
#define IDS_DOSFILESIGNATURE	     1023
#define IDS_UNKNOWNFILESIGNATURE     1024


#define IDM_OPEN		     2001
#define IDM_CLOSE		     2002
#define IDM_EXIT		     2010

#define VIEWWXB 		     8
#define WXB_LPMEMVIEW		     0
#define WXB_LPOLDMEMVIEW	     4


/* struct for memory view window */
typedef struct tagMemView
    {
    HANDLE    hFile;
    HANDLE    hMMFile;
    LPVOID    lpMem;
    int       nBase;
    int       nSize;
    int       xWin, yWin;
    int       PosV, RangeV;
    long      nLines;
    int       nExtraBytes;
} MEMVIEW, * LPMEMVIEW;



/* prototypes for functions in exeview.c */
LONG   WINAPI ExeViewWndProc (HWND, UINT, WPARAM, LPARAM);
int    WINAPI NotifyUser (HWND, int, int, char *, UINT);
void   WINAPI ReportError (int);

/* prototypes for functions in pview.c */
void   WINAPI ViewExe (HWND, char *);
LONG   WINAPI MemWndProc (HWND, UINT, WPARAM, LPARAM);

/* prototypes for functions in viewio.c */
BOOL   WINAPI GetFileName (HWND, char *, char *);
void   WINAPI GetFileFromPath (char *, char *);
BOOL   WINAPI GetCmdLine (char *, char *, BOOL *);
BOOL   WINAPI IsValidFile (char *);
