/*
 *
 *  PROGRAM  : multipal.c
 *
 *  PURPOSE  : Show example of a minimal MDI application
 *
 *  FUNCTIONS:
 *
 *      WinMain() - Calls the initialization function
 *                  and processes message loop
 *
 *      BlandFrameWndProc() - Window function for the "frame"
 *                  window, which controls the menu
 *                  and contains the MDI client window
 *
 *      multipalChildWndProc()- Window function for the individual
 *                  child windows
 *
 *      CommandHandler() - Processes the "frame" window's
 *                  WM_COMMAND messages.
 *
 * Copyright 1991 Microsoft Corporation. All rights reserved.
 */
// COPYRIGHT:
//
//   (C) Copyright Microsoft Corp. 1993.  All rights reserved.
//
//   You have a royalty-free right to use, modify, reproduce and
//   distribute the Sample Files (and/or any modified version) in
//   any way you find useful, provided that you agree that
//   Microsoft has no warranty obligations or liability for any
//   Sample Application Files which are modified.
//


/*--------------------  #includes  -------------------------------*/

#include "multipal.h"
#include "commdlg.h"

/*--------------------  global variables  -------------------------*/

HANDLE hInst;                   // Program instance handle
HWND hwndFrame     = NULL;      // Handle to main window
HWND hwndMDIClient = NULL;      // Handle to MDI client
char szFrame[] = "multipal frame";   // Class name for "frame" window
char szChild[] = "multipal child";   // Class name for MDI window
HDC hMemDC = NULL;		// Global handle to memory DC so it
				// is only created once.  Destroyed
				// when at WM_DESTROY time.

/*---------------------  function prototypes  -----------------------*/

// Forward declarations of helper functions in this module

VOID NEAR PASCAL CommandHandler  (HWND,WORD);

BOOL ReadDIB(LPSTR, DIBINIT *);
void PASCAL NEAR PaintDIB(HWND);
VOID NEAR PASCAL SendMessageToKids (WORD,WPARAM,LPARAM);

/*---------------  BlandFrameWndProc()  -------------------------------*/
/*
 *
 *  FUNCTION   : BlandFrameWndProc (hwnd, msg, wParam, lParam )
 *
 *  PURPOSE    : The window function for the "frame" window, which controls
 *               the menu and encompasses all the MDI child windows. Does
 *               the major part of the message processing. Specifically, in
 *               response to:
 *
 *               WM_CREATE : Creates and displays the "frame".
 *
 *               WM_COMMAND: Passes control to a command-handling function.
 *
 *               WM_CLOSE  : Quits the app. 
 *
 *               WM_DESTROY: Destroys frame window and quits app.
 *
 *  NOTE: If cases are added for WM_MENUCHAR, WM_NEXTMENU, WM_SETFOCUS,
 *        and WM_SIZE, note that these messages should be passed on
 *        to DefFrameProc even if we handle them.  See the SDK Reference
 *        entry for DefFrameProc
 */

LONG FAR PASCAL BlandFrameWndProc ( hwnd, msg, wParam, lParam )

register HWND hwnd;
UINT	      msg;
register WPARAM wParam;
LPARAM		lParam;

{
    HDC hDC;
    WORD i;
    LPARAM temp;

    switch (msg)
        {
        case WM_CREATE:
            {
            CLIENTCREATESTRUCT ccs;

            // Find window menu where children will be listed 
            ccs.hWindowMenu  = GetSubMenu (GetMenu(hwnd),WINDOWMENU);
            ccs.idFirstChild = IDM_WINDOWCHILD;

            // Create the MDI client 
            hwndMDIClient = CreateWindow ("mdiclient",
                NULL,
                WS_CHILD | WS_CLIPCHILDREN,
                0,
                0,
                0,
                0,
                hwnd,
                0,
                hInst,
                (LPSTR)&ccs);
            ShowWindow (hwndMDIClient,SW_SHOW);

	    // Create long-lasting memory DC.
	    hDC = GetDC(NULL);
	    hMemDC = CreateCompatibleDC(hDC);
	    ReleaseDC(NULL,hDC);
            break;
            }

	case WM_QUERYNEWPALETTE:
	    // Get the currently active document.
	    temp = SendMessage(hwndMDIClient,WM_MDIGETACTIVE, NULL, NULL); 

	    // Tell the active document to realize in foreground.
	    i = (WORD)SendMessage(LOWORD(temp), WM_QUERYNEWPALETTE, NULL, NULL);

	    // If mapping is unchanged, other documents could still change,
	    // so give them a change to realize.
	    if (!i)
		SendMessageToKids(WM_PALETTECHANGED, LOWORD(temp), NULL);
	    return(i);
	    break;

	// System palette has changed, so pass it on to the children.
	case WM_PALETTECHANGED:
	    SendMessageToKids(WM_PALETTECHANGED, wParam, lParam);
	    break;

        case WM_COMMAND:
            // Direct all menu selection or accelerator commands to 
            // the CommandHandler function
            CommandHandler (hwnd,wParam);
            break;

        case WM_CLOSE:
            DestroyWindow (hwnd);
            break;

        case WM_DESTROY:
	    // Get rid of globally maintained memory DC.
	    DeleteDC(hMemDC);
            PostQuitMessage (0);
            break;

        default:
            // use DefFrameProc() instead of DefWindowProc(), since there
            // are things that have to be handled differently because of MDI
            
            return DefFrameProc (hwnd,hwndMDIClient,msg,wParam,lParam);
        }
    return 0;
}


/*--------------------multipalChildWndProc  ----------------------*/
/*
 *
 *  FUNCTION: multipalChildWndProc ( hwnd, msg, wParam, lParam )  
 *
 *  NOTE: If cases are added for WM_CHILDACTIVATE, WM_GETMINMAXINFO,
 *        WM_MENUCHAR, WM_MOVE, WM_NEXTMENU, WM_SETFOCUS, WM_SIZE,
 *        or WM_SYSCOMMAND, these messages should be passed on
 *        to DefMDIChildProc even if we handle them. See the SDK
 *        Reference entry for DefMDIChildProc
 *
 */


LONG FAR PASCAL multipalChildWndProc ( hWnd, msg, wParam, lParam )

register HWND hWnd;
UINT	      msg;
register WPARAM wParam;
LPARAM		lParam;

{
    HPALETTE hOldPal;
    HDC hDC;
    WORD i;
    DIBINIT FAR * lpdiInit;

    switch (msg) {
        case WM_PAINT:
	    PaintDIB(hWnd);
	    break;

	case WM_CREATE:
	    // Get the window's image defining information.
	    lpdiInit = (DIBINIT FAR *)((MDICREATESTRUCT FAR *) 
	    	((CREATESTRUCT FAR *)lParam)->lpCreateParams)->lParam;
	    SetWindowWord(hWnd, WD_HDIB, lpdiInit->hDIB);
	    SetWindowWord(hWnd, WD_HBITMAP, lpdiInit->hBitmap);
	    SetWindowWord(hWnd, WD_HPALETTE, lpdiInit->hPalette);
	    break;

// Respond to palette messages by realizing the window's palette.
// If the realization indicates a change in the system mapping, then
// invalidate the window to force a repaint.
//
// To handle multiple palettes, the palette is selected in the 
// background in response to WM_PALETTECHANGED and in the foreground
// in response to the WM_QUERYNEWPALETTE message.  Only the current
// active MDI child gets the WM_QUERYNEWPALETTE message.  The other
// MDI children only receive the WM_PALETTECHANGED message.

	case WM_PALETTECHANGED:
	    if (hWnd == wParam)
		break;
	case WM_QUERYNEWPALETTE:
	    hDC = GetDC(hWnd);
	    hOldPal = SelectPalette(hDC, GetWindowWord(hWnd, WD_HPALETTE), 
	    			(msg == WM_QUERYNEWPALETTE) ? FALSE : TRUE);
	    i = RealizePalette(hDC);
	    SelectPalette(hDC, hOldPal, TRUE);
	    RealizePalette(hDC);
	    ReleaseDC(hWnd, hDC);
	    if (i)
		InvalidateRect(hWnd, NULL, TRUE);
	    return(i);
	    break;

// MDI child is becoming active.  For palettes, this is pretty much 
// the same as the whole application being activated, so get the 
// WM_QUERYNEWPALETTE (foreground activation) messaging under way.

	case WMMINE_MDIACTIVATE:
	case WM_MDIACTIVATE:
	    if (wParam)
		SendMessage(hwndFrame, WM_QUERYNEWPALETTE, NULL, NULL);
	    break;

	case WM_DESTROY:
	    GlobalFree(GetWindowWord(hWnd, WD_HDIB));
	    DeleteObject(GetWindowWord(hWnd, WD_HPALETTE));
	    DeleteObject(GetWindowWord(hWnd, WD_HBITMAP));
	    break;

	default:
	    return DefMDIChildProc (hWnd, msg, wParam, lParam);
	}
}


/*-----------------  CommandHandler  -------------------------------*/
/*
 *
 *  FUNCTION   : CommandHandler ()
 *                    
 *  PURPOSE    : Processes all "frame" WM_COMMAND messages.       
 *                     
 */

VOID NEAR PASCAL CommandHandler ( hwnd, wParam )
register HWND hwnd;
register WORD wParam;

{
    OPENFILENAME    ofn;
    char szName[128];
    HWND hwndTemp;

    switch (wParam)
        {
	case IDM_OPEN:
	    ofn.lStructSize = sizeof(OPENFILENAME);
	    ofn.hwndOwner = hwnd;
	    ofn.lpstrFilter = NULL;
            ofn.lpstrFilter = "Bitmaps (*.BMP)\0*.BMP\0";
	    ofn.lpstrCustomFilter = NULL;
	    ofn.nFilterIndex = 1;
	    szName[0] = 0;		/* pass in NULL */
	    ofn.lpstrFile = (LPSTR)szName;
	    ofn.nMaxFile = 128;
	    ofn.lpstrInitialDir = NULL;
	    ofn.lpstrTitle = NULL;
	    ofn.lpstrFileTitle = NULL;
	    ofn.lpstrDefExt = NULL;
            ofn.Flags = 0;

            if (GetOpenFileName((LPOPENFILENAME)&ofn))
	    {
	        if (hwndTemp = MakeNewChild((PSTR)szName));
		  // Special activation stuff for the first time document.
		  SendMessage(hwndTemp, WMMINE_MDIACTIVATE, TRUE, 
		  				MAKELONG(hwndTemp, NULL));
	    }
	    break;

        case IDM_FILEEXIT:
            // Close application 
            SendMessage (hwnd, WM_CLOSE, 0, 0L);
            break;

        case IDM_WINDOWTILE:
            // Tile MDI windows 
            SendMessage (hwndMDIClient, WM_MDITILE, 0, 0L);
            break;

        case IDM_WINDOWCASCADE:
            // Cascade MDI windows 
            SendMessage (hwndMDIClient, WM_MDICASCADE, 0, 0L);
            break;

        case IDM_WINDOWICONS:
            // Auto - arrange MDI icons 
            SendMessage (hwndMDIClient, WM_MDIICONARRANGE, 0, 0L);
            break;

        default:
            // This is essential, since there are frame WM_COMMANDS generated
            // by the MDI system for activating child windows via the
            // window menu.
            DefFrameProc(hwnd, hwndMDIClient, WM_COMMAND, wParam, 0L);
        }
}

/*-----------------------  WinMain  ----------------------------------*/
/*
 *
 *  FUNCTION   : WinMain(HANDLE, HANDLE, LPSTR, int) 
 *                     
 *  PURPOSE    : Creates the "frame" window, does some initialization and  
 *     enters the message loop.         
 *              
 */


int NEAR PASCAL WinMain(hInstance, hPrevInstance, lpszCmdLine, nCmdShow)

HANDLE hInstance;
HANDLE hPrevInstance;
LPSTR  lpszCmdLine;
int    nCmdShow;
{
    MSG msg;

    hInst = hInstance;

    // If this is the first instance of the app. register window classes 
    if (!hPrevInstance)
       if (!InitializeApplication ())
         return 0;

    // Create the frame and do other initialization
    if (!InitializeInstance (lpszCmdLine, nCmdShow))
       return 0;

    // Enter main message loop 
    while (GetMessage (&msg, NULL, 0, 0))
        // If a keyboard message is for the MDI, let the MDI client
        // take care of it.  Otherwise, just handle the message as usual
        if ( !TranslateMDISysAccel (hwndMDIClient, &msg))
            {
            TranslateMessage (&msg);
            DispatchMessage (&msg);
            }
    return 0;
}

/*--------------------- InitializeApplication  -------------------------*/
/*
 *
 *  FUNCTION   : InitializeApplication ()
 *
 *  PURPOSE    : Sets up the class data structures and does a one-time
 *               initialization of the app by registering the window classes
 *
 *  RETURNS    : TRUE  - If RegisterClass() was successful for both classes.
 *               FALSE - otherwise.
 *
 */

BOOL FAR PASCAL InitializeApplication()
{
    WNDCLASS  wc;

    // Register the frame class 
    wc.style         = 0;
    wc.lpfnWndProc   = BlandFrameWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInst;
    wc.hIcon         = LoadIcon(hInst, IDBLANDFRAME);
    wc.hCursor       = LoadCursor(NULL,IDC_ARROW);
    wc.hbrBackground = COLOR_APPWORKSPACE+1;
    wc.lpszMenuName  = IDBLANDMENU;
    wc.lpszClassName = szFrame;

    if (RegisterClass (&wc))
      {
      // Register the MDI child class 
      wc.lpfnWndProc   = multipalChildWndProc;
      wc.hIcon         = LoadIcon(hInst,IDBLANDCHILD);
      wc.lpszMenuName  = NULL;
      wc.cbWndExtra    = CBWNDEXTRA;
      wc.lpszClassName = szChild;

      if (RegisterClass(&wc))
        return TRUE;
      }

    return FALSE;
}
/*----------------------  InitializeInstance  --------------------------*/
/*
 *
 *  FUNCTION   : InitializeInstance ()
 *
 *  PURPOSE    : Performs a per-instance initialization of multipal. It
 *               also creates the frame and one MDI child window.
 *
 *  RETURNS    : TRUE  - If initialization was successful.
 *               FALSE - otherwise.
 *
 */

BOOL FAR PASCAL InitializeInstance(LPSTR lpCmdLine, WORD nCmdShow)
{
    extern HWND   hwndMDIClient;
	   char   sz[80] = "MultiPal";

    // Create the frame 
    // MDI Client window is created in frame's WM_CREATE case
    hwndFrame = CreateWindow (szFrame,
            sz,
            WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
            CW_USEDEFAULT,
            0,
            CW_USEDEFAULT,
            0,
            NULL,
            NULL,
            hInst,
            NULL);

    if (hwndFrame && hwndMDIClient)
        {
        // Display the frame window 
        ShowWindow (hwndFrame, nCmdShow);
        UpdateWindow (hwndFrame);

        return TRUE;
        }

    return FALSE;
}

/****************************************************************************
 *
 *  FUNCTION   : SendMessageToKids
 *
 *  PURPOSE    : Send the given message with the given parameters to all
 *               of the MDI child windows.
 *
 *  RETURNS    : None.
 *
 ****************************************************************************/

VOID NEAR PASCAL SendMessageToKids (WORD msg, WPARAM wParam, LPARAM lParam)
{
    register HWND hwndT;

    hwndT = GetWindow (hwndMDIClient, GW_CHILD);
    while (hwndT)
    {
	SendMessage (hwndT, msg, wParam, lParam);
	hwndT = GetWindow(hwndT, GW_HWNDNEXT);
    }
}

/*----------------   MakeNewChild  -----------------------------*/
/*
 *
 *  FUNCTION   : MakeNewChild (lpName)
 *
 *  PURPOSE    : Creates a new MDI child window after loading the
 *               DIB to be displayed by the window.
 *
 *  RETURNS    : HWND  - A handle to the new window.
 *
 */

HWND FAR PASCAL MakeNewChild(char *pName)
{
    HWND            hwnd = NULL;
    MDICREATESTRUCT mcs;
    DIBINIT diInfo;

    // Read the DIB.  If there are problems, don't create the window.
    if (ReadDIB (pName, &diInfo))
    {
        mcs.szTitle = (LPSTR)pName; /* Fully qualified pathname*/

	mcs.szClass    = szChild;
	mcs.hOwner     = hInst;
	mcs.x = mcs.cx = CW_USEDEFAULT;  // Use the default size for the window
	mcs.y = mcs.cy = CW_USEDEFAULT;
	mcs.style      = 0;
	mcs.lParam     = (long)((DIBINIT FAR *)&diInfo);

	// tell the MDI Client to create the child 
	hwnd = (WORD)SendMessage (hwndMDIClient,
                              WM_MDICREATE,
                              0,
                              (LONG)(LPMDICREATESTRUCT)&mcs);

	ShowWindow(hwnd, SW_SHOW);
    }
    return hwnd;
}


// Height of the palette strip.
#define PALHEIGHT 15

/****************************************************************************
 *
 *  FUNCTION   : PaintDIB(hWnd)
 *
 *  PURPOSE    : Paints the window's DIB using BitBlt and the device-
 *               dependent form of the image.  Also, as a bonus, paints
 *               a small strip containing all the colors of the palette
 *               that is being used.
 *
 *  RETURNS    : None.
 *
 ****************************************************************************/
void PASCAL NEAR PaintDIB(HWND hWnd)
{
    PAINTSTRUCT ps;
    HDC hDC;
    RECT Rect;
    HPALETTE hOldPal;
    HBITMAP hOldBit;
    WORD i;
    HBRUSH hbr;
    WORD palNumEntries;

    hDC = BeginPaint(hWnd, &ps);

    GetClientRect(hWnd, &Rect);

// Get the bitmap ready for blting.
// The palette is selected and realized.

// Note that the palette is forced into the background.  This is
// entirely sufficient because its realization into the system palette
// is already accomplished when responding the palette messages.

    hOldBit = SelectObject(hMemDC, GetWindowWord(hWnd, WD_HBITMAP));
    SelectPalette(hMemDC, GetWindowWord(hWnd, WD_HPALETTE), TRUE);
    hOldPal = SelectPalette(hDC, GetWindowWord(hWnd, WD_HPALETTE), TRUE);
    RealizePalette(hDC);

    // Blt image just below the palette strip.
    BitBlt(hDC, 0, PALHEIGHT, Rect.right-Rect.left, Rect.bottom - Rect.top,
    		hMemDC, 0, 0, SRCCOPY);


    // For fluff, draw the image's palette in the top rows of the
    // the window.  A magenta line separates the palette from the
    // bitmap itself.
    // PALETTEINDEX is used to access colors from the palette.
    GetObject(GetWindowWord(hWnd, WD_HPALETTE), sizeof(WORD), &palNumEntries);
    for (i = 0; i < palNumEntries; i++)
    {
	// A palette-relative brush is used for drawing.
	if (hbr = CreateSolidBrush(PALETTEINDEX(i)))
	{
	    hbr = SelectObject(hDC, hbr);
	    PatBlt(hDC, i*2, 0, 2, PALHEIGHT, PATCOPY);
	    hbr = SelectObject(hDC, hbr);
	    DeleteObject(hbr);
	}
    }
    if (hbr = CreateSolidBrush(RGB(255, 0, 255)))
    {
	hbr = SelectObject(hDC, hbr);
	PatBlt(hDC, 0, PALHEIGHT-1, Rect.right - Rect.left, 2, PATCOPY);
	hbr = SelectObject(hDC, hbr);
	DeleteObject(hbr);
    }

    SelectPalette(hMemDC, hOldPal, TRUE);
    SelectPalette(hDC, hOldPal, TRUE);
    RealizePalette(hDC);
    SelectObject(hMemDC, hOldBit);

    EndPaint(hWnd, &ps);
}


//-------------------------------------------------------------------
// The routines below are used for reading the DIB file and setting
// up the device dependent version of the image.
//-------------------------------------------------------------------

/**************** PRIVATE ROUTINE TO READ MORE THAN 64K *********************/
/****************************************************************************
 *									    *
 *  FUNCTION   : lread(int fh, VOID FAR *pv, DWORD ul)			    *
 *									    *
 *  PURPOSE    : Reads data in steps of 32k till all the data has been read.*
 *									    *
 *  RETURNS    : 0 - If read did not proceed correctly. 		    *
 *		 number of bytes read otherwise.			    *
 *									    *
 ****************************************************************************/
DWORD PASCAL lread (int fh, VOID far *pv, DWORD ul)
{
    DWORD     ulT = ul;
    BYTE huge *hp = pv;

    while (ul > (DWORD)MAXREAD) {
	if (_lread(fh, (LPSTR)hp, (WORD)MAXREAD) != MAXREAD)
		return 0;
	ul -= MAXREAD;
	hp += MAXREAD;
    }
    if (_lread(fh, (LPSTR)hp, (WORD)ul) != (WORD)ul)
	return 0;
    return ulT;
}
/**************** PRIVATE ROUTINE TO READ MORE THAN 64K *********************/

/****************************************************************************
 *
 *  FUNCTION   : ReadDIB(hWnd)
 *
 *  PURPOSE    : Reads a DIB from a file, obtains a handle to its
 *		 BITMAPINFO struct. and loads the DIB.  Once the DIB
 *               is loaded, the function also creates a bitmap and
 *               palette out of the DIB for a device-dependent form.
 *
 *  RETURNS    : TRUE  - DIB loaded and bitmap/palette created 
 *                       The DIBINIT structure pointed to by pInfo is
 *                       filled with the appropriate handles.
 *		 FALSE - otherwise
 *
 ****************************************************************************/
BOOL ReadDIB(LPSTR lpFileName, DIBINIT * pInfo)
{
    unsigned	       fh;
    LPBITMAPINFOHEADER lpbi;
    OFSTRUCT	       of;
    BITMAPFILEHEADER   bf;
    WORD		nNumColors;
    BOOL result = FALSE;
    char str[128];
    WORD offBits;
    HDC hDC;
    BOOL bCoreHead = FALSE;

    /* Open the file and get a handle to it's BITMAPINFO */

    fh = OpenFile (lpFileName, &of, OF_READ);
    if (fh == -1) {
	wsprintf(str,"Can't open file '%ls'", (LPSTR)lpFileName);
	MessageBox(hwndFrame, str, "Error", MB_ICONSTOP | MB_OK);
	return (NULL);
    }

    pInfo->hDIB = GlobalAlloc(GHND, (DWORD)(sizeof(BITMAPINFOHEADER) + 
    					256 * sizeof(RGBQUAD)));
    if (!pInfo->hDIB)
	return(NULL);

    lpbi = (LPBITMAPINFOHEADER)GlobalLock(pInfo->hDIB);

    /* read the BITMAPFILEHEADER */
    if (sizeof (bf) != _lread (fh, (LPSTR)&bf, sizeof (bf)))
	goto ErrExit;

    if (bf.bfType != 0x4d42)	/* 'BM' */
	goto ErrExit;

    if (sizeof(BITMAPCOREHEADER) != _lread (fh, (LPSTR)lpbi, sizeof(BITMAPCOREHEADER)))
	goto ErrExit;

    if (lpbi->biSize == sizeof(BITMAPCOREHEADER))
    {
	lpbi->biSize = sizeof(BITMAPINFOHEADER);
	lpbi->biBitCount = ((LPBITMAPCOREHEADER)lpbi)->bcBitCount;
	lpbi->biPlanes = ((LPBITMAPCOREHEADER)lpbi)->bcPlanes;
	lpbi->biHeight = ((LPBITMAPCOREHEADER)lpbi)->bcHeight;
	lpbi->biWidth = ((LPBITMAPCOREHEADER)lpbi)->bcWidth;
	bCoreHead = TRUE;
    }
    else
    {
    	// get to the start of the header and read INFOHEADER
        _llseek(fh,sizeof(BITMAPFILEHEADER),SEEK_SET);
	if (sizeof(BITMAPINFOHEADER) != _lread (fh, (LPSTR)lpbi, sizeof(BITMAPINFOHEADER)))
	    goto ErrExit;
    }

    if (!(nNumColors = (WORD)lpbi->biClrUsed))
    {
	/* no color table for 24-bit, default size otherwise */
	if (lpbi->biBitCount != 24)
	    nNumColors = 1 << lpbi->biBitCount;	/* standard size table */
    }

    /*	fill in some default values if they are zero */
    if (lpbi->biClrUsed == 0)
	lpbi->biClrUsed = nNumColors;

    if (lpbi->biSizeImage == 0)
    {
	lpbi->biSizeImage = ((((lpbi->biWidth * (DWORD)lpbi->biBitCount) + 31) & ~31) >> 3)
			 * lpbi->biHeight;
    }

    /* get a proper-sized buffer for header, color table and bits */ 
    GlobalUnlock(pInfo->hDIB);
    pInfo->hDIB = GlobalReAlloc(pInfo->hDIB, lpbi->biSize +
    					nNumColors * sizeof(RGBQUAD) +
					lpbi->biSizeImage, 0);
    if (!pInfo->hDIB)	/* can't resize buffer for loading */
	goto ErrExit2;

    lpbi = (LPBITMAPINFOHEADER)GlobalLock(pInfo->hDIB);

    /* read the color table */
    if (!bCoreHead)
	_lread(fh, (LPSTR)(lpbi) + lpbi->biSize, nNumColors * sizeof(RGBQUAD));
    else
    {
	signed int i;
	RGBQUAD FAR *pQuad;
	RGBTRIPLE FAR *pTriple;

	_lread(fh, (LPSTR)(lpbi) + lpbi->biSize, nNumColors * sizeof(RGBTRIPLE));

	pQuad = (RGBQUAD FAR *)((LPSTR)lpbi + lpbi->biSize);
	pTriple = (RGBTRIPLE FAR *) pQuad;
	for (i = nNumColors - 1; i >= 0; i--)
	{
	    pQuad[i].rgbRed = pTriple[i].rgbtRed;
	    pQuad[i].rgbBlue = pTriple[i].rgbtBlue;
	    pQuad[i].rgbGreen = pTriple[i].rgbtGreen;
	    pQuad[i].rgbReserved = 0;
	}
    }

    /* offset to the bits from start of DIB header */
    offBits = (WORD)lpbi->biSize + nNumColors * sizeof(RGBQUAD);

    if (bf.bfOffBits != 0L)
    {
        _llseek(fh,bf.bfOffBits,SEEK_SET);
    }

    if (lpbi->biSizeImage == lread(fh, (LPSTR)lpbi + offBits, lpbi->biSizeImage))
    {
	GlobalUnlock(pInfo->hDIB);

	hDC = GetDC(NULL);
	if (!MakeBitmapAndPalette(hDC, pInfo->hDIB, &(pInfo->hPalette),
					&(pInfo->hBitmap)))
	{
	    ReleaseDC(NULL,hDC);
	    goto ErrExit2;
	}
	else
	{
	    ReleaseDC(NULL,hDC);
	    result = TRUE;
	}
    }
    else
    {
ErrExit:
	GlobalUnlock(pInfo->hDIB);
ErrExit2:
	GlobalFree(pInfo->hDIB);
    }

    _lclose(fh);
    return(result);
}

/****************************************************************************
 *
 *  FUNCTION   : MakeBitmapAndPalette
 *
 *  PURPOSE    : Given a DIB, creates a bitmap and corresponding palette
 *               to be used for a device-dependent representation of
 *               of the image.
 *
 *  RETURNS    : TRUE  --> success. phPal and phBitmap are filled with 
 *                         appropriate handles.  Caller is responsible
 *                         for freeing objects.
 *               FALSE --> unable to create objects.  both pointer are
 *                         not valid
 *
 ****************************************************************************/
BOOL NEAR PASCAL MakeBitmapAndPalette(HDC hDC, HANDLE hDIB, 
			HPALETTE * phPal, HBITMAP * phBitmap)
{
    LPBITMAPINFOHEADER lpInfo;
    BOOL result = FALSE;
    HBITMAP hBitmap;
    HPALETTE hPalette, hOldPal;
    LPSTR lpBits;

    lpInfo = (LPBITMAPINFOHEADER) GlobalLock(hDIB);
    if (hPalette = MakeDIBPalette(lpInfo))
    {
	// Need to realize palette for converting DIB to bitmap.
	hOldPal = SelectPalette(hDC, hPalette, TRUE);
	RealizePalette(hDC);

	lpBits = (LPSTR)lpInfo + (WORD)lpInfo->biSize + 
		(WORD)lpInfo->biClrUsed * sizeof(RGBQUAD);
	hBitmap = CreateDIBitmap(hDC, lpInfo, CBM_INIT, lpBits, 
				(LPBITMAPINFO)lpInfo, DIB_RGB_COLORS);

	SelectPalette(hDC, hOldPal, TRUE);
	RealizePalette(hDC);

	if (!hBitmap)
	    DeleteObject(hPalette);
	else
	{
	    *phBitmap = hBitmap;
	    *phPal = hPalette;
	    result = TRUE;
	}
    }
    return(result);
}

/****************************************************************************
 *									    *
 *  FUNCTION   : MakeDIBPalette(lpInfo)					    *
 *									    *
 *  PURPOSE    : Given a BITMAPINFOHEADER, create a palette based on 
 *		 the color table.
 *		 
 *									    *
 *  RETURNS    : non-zero - handle of a corresponding palette 
 *		 zero - unable to create palette
 *									    *
 ****************************************************************************/
HPALETTE PASCAL NEAR MakeDIBPalette(LPBITMAPINFOHEADER lpInfo)
{
    NPLOGPALETTE npPal;
    RGBQUAD far *lpRGB;
    HPALETTE hLogPal; 
    WORD i;

    /* since biClrUsed field was filled during the loading of the DIB,
    ** we know it contains the number of colors in the color table.
    */
    if (lpInfo->biClrUsed)
    {
	npPal = (NPLOGPALETTE)LocalAlloc(LMEM_FIXED, sizeof(LOGPALETTE) + 
				(WORD)lpInfo->biClrUsed * sizeof(PALETTEENTRY));
	if (!npPal)
	    return(FALSE);

	npPal->palVersion = 0x300;
	npPal->palNumEntries = (WORD)lpInfo->biClrUsed;

	/* get pointer to the color table */
	lpRGB = (RGBQUAD FAR *)((LPSTR)lpInfo + lpInfo->biSize);

	/* copy colors from the color table to the LogPalette structure */
	for (i = 0; i < lpInfo->biClrUsed; i++, lpRGB++)
	{
	    npPal->palPalEntry[i].peRed = lpRGB->rgbRed;
	    npPal->palPalEntry[i].peGreen = lpRGB->rgbGreen;
	    npPal->palPalEntry[i].peBlue = lpRGB->rgbBlue;
	    npPal->palPalEntry[i].peFlags = 0;
	}

	hLogPal = CreatePalette((LPLOGPALETTE)npPal);
	LocalFree((HANDLE)npPal);
	return(hLogPal);
    }

    /* 24-bit DIB with no color table.  return default palette.  Another
    ** option would be to create a 256 color "rainbow" palette to provide
    ** some good color choices.
    */
    else
	return(GetStockObject(DEFAULT_PALETTE));
}
