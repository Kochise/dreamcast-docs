// Copyright 1991 Microsoft Corporation. All rights reserved.

#include "windows.h"

#define WINDOWMENU  1  /* position of window menu     */

#define CBWNDEXTRA  6
#define WD_HDIB		0
#define WD_HBITMAP	2
#define WD_HPALETTE	4

#ifdef RC_INVOKED
#define ID(id) id
#else
#define ID(id) MAKEINTRESOURCE(id)
#endif

/* resource ID's */
#define IDBLANDFRAME  ID(1)
#define IDBLANDCHILD  ID(2)
#define IDBLANDMENU   ID(3)

/* menu ID's */
#define IDM_FILENEW        1001
#define IDM_OPEN           1002
#define IDM_FILEEXIT       1006
#define IDM_WINDOWTILE     4001
#define IDM_WINDOWCASCADE  4002
#define IDM_WINDOWCLOSEALL 4003
#define IDM_WINDOWICONS    4004
#define IDM_WINDOWCHILD    4100

/* string constants */
#define IDS_CLIENTTITLE    16
#define IDS_UNTITLED       17
#define IDS_APPNAME        18

/* private messages */
#define WMMINE_MDIACTIVATE	WM_USER+1

#define MAXREAD  32768		       /* Number of bytes to be read during */
				       /* each read operation.		    */

typedef struct {
    HANDLE hDIB;
    HANDLE hBitmap;
    HANDLE hPalette;
    } DIBINIT;


/* External variable declarations */
extern HANDLE hInst;       /* application instance handle  */
extern HWND hwndFrame;     /* main window handle           */
extern HWND hwndMDIClient; /* handle of MDI Client window  */
extern LONG styleDefault;  /* default child creation state */
extern char szChild[];     /* class of child               */

/* External functions */
extern BOOL FAR PASCAL InitializeApplication(VOID);
extern BOOL FAR PASCAL InitializeInstance   (LPSTR,WORD);
extern HWND FAR PASCAL MakeNewChild         (char *);
extern LONG FAR PASCAL BlandFrameWndProc    (HWND,UINT,WPARAM,LPARAM);
extern LONG FAR PASCAL multipalChildWndProc (HWND,UINT,WPARAM,LPARAM);

BOOL NEAR PASCAL MakeBitmapAndPalette(HDC,HANDLE,HPALETTE *,HBITMAP *);
HPALETTE PASCAL NEAR MakeDIBPalette(LPBITMAPINFOHEADER);
