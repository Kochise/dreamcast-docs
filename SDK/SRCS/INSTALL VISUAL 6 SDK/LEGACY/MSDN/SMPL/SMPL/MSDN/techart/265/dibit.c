/**************************************************************************** 
    PROGRAM: dibit.c

    PURPOSE: dibit template for Windows applications

    FUNCTIONS:

	WinMain() - calls initialization function, processes message loop
	InitApplication() - initializes window data and registers window
	InitInstance() - saves instance handle and creates main window
	MainWndProc() - processes messages
	About() - processes messages for "About" dialog box

    COMMENTS:

        Windows can have several copies of your application running at the
        same time.  The variable hInst keeps track of which instance this
        application is so that processing will be to the correct window.

****************************************************************************/

#include "windows.h"		    /* required for all Windows applications */
#include "dibit.h"		    /* specific to this program		     */
#include "commdlg.h"

HANDLE hInst;			    /* current instance			     */

char achFileName[128];
char str[255];

WORD wOperation = IDM_SETDIB;	/* default to SetDIBits() */
BOOL bDIBLoaded = FALSE;	/* initially no DIB is loaded */
WORD offBits;			/* offset to the bits */
HANDLE hDIBInfo = NULL;		/* the DIB header */
HBITMAP hDDBitmap = NULL;	/* a device dependent copy of the DIB */
HBITMAP hOldBitmap;
HDC hMemDC;

WORD wPalOp = 0;		/* default to no palette stuff */
HPALETTE hPalette = NULL;	/* palette used for display */
HANDLE hPalHeader = NULL;	/* DIB header with indices for color table */

void PASCAL NEAR PaintDIB(HWND);
DWORD PASCAL lread (int, VOID far *, DWORD);
HPALETTE PASCAL NEAR MakeDIBPalette(LPBITMAPINFOHEADER);
HANDLE PASCAL NEAR MakeIndexHeader(LPBITMAPINFOHEADER);
int InitDIB(HWND);

/****************************************************************************

    FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)

    PURPOSE: calls initialization function, processes message loop

    COMMENTS:

        Windows recognizes this function by name as the initial entry point 
        for the program.  This function calls the application initialization 
        routine, if no other instance of the program is running, and always 
        calls the instance initialization routine.  It then executes a message 
        retrieval and dispatch loop that is the top-level control structure 
        for the remainder of execution.  The loop is terminated when a WM_QUIT 
        message is received, at which time this function exits the application 
        instance by returning the value passed by PostQuitMessage(). 

        If this function must abort before entering the message loop, it 
        returns the conventional value NULL.  

****************************************************************************/

int PASCAL WinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow)
HANDLE hInstance;			     /* current instance	     */
HANDLE hPrevInstance;			     /* previous instance	     */
LPSTR lpCmdLine;			     /* command line		     */
int nCmdShow;				     /* show-window type (open/icon) */
{
    MSG msg;				     /* message			     */

    if (!hPrevInstance)			 /* Other instances of app running? */
	if (!InitApplication(hInstance)) /* Initialize shared things */
	    return (FALSE);		 /* Exits if unable to initialize     */

    /* Perform initializations that apply to a specific instance */

    if (!InitInstance(hInstance, nCmdShow))
        return (FALSE);

    /* Acquire and dispatch messages until a WM_QUIT message is received. */

    while (GetMessage(&msg,	   /* message structure			     */
	    NULL,		   /* handle of window receiving the message */
	    NULL,		   /* lowest message to examine		     */
	    NULL))		   /* highest message to examine	     */
	{
	TranslateMessage(&msg);	   /* Translates virtual key codes	     */
	DispatchMessage(&msg);	   /* Dispatches message to window	     */
    }
    return (msg.wParam);	   /* Returns the value from PostQuitMessage */
}


/****************************************************************************

    FUNCTION: InitApplication(HANDLE)

    PURPOSE: Initializes window data and registers window class

    COMMENTS:

        This function is called at initialization time only if no other 
        instances of the application are running.  This function performs 
        initialization tasks that can be done once for any number of running 
        instances.  

        In this case, we initialize a window class by filling out a data 
        structure of type WNDCLASS and calling the Windows RegisterClass() 
        function.  Since all instances of this application use the same window 
        class, we only need to do this when the first instance is initialized.  


****************************************************************************/

BOOL InitApplication(hInstance)
HANDLE hInstance;			       /* current instance	     */
{
    WNDCLASS  wc;

    /* Fill in window class structure with parameters that describe the       */
    /* main window.                                                           */

    wc.style = NULL;                    /* Class style(s).                    */
    wc.lpfnWndProc = MainWndProc;       /* Function to retrieve messages for  */
                                        /* windows of this class.             */
    wc.cbClsExtra = 0;                  /* No per-class extra data.           */
    wc.cbWndExtra = 0;                  /* No per-window extra data.          */
    wc.hInstance = hInstance;           /* Application that owns the class.   */
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = COLOR_WINDOW+1;
    wc.lpszMenuName =  "dibitMenu";   /* Name of menu resource in .RC file. */
    wc.lpszClassName = "dibitWClass"; /* Name used in call to CreateWindow. */

    /* Register the window class and return success/failure code. */

    return (RegisterClass(&wc));
}


/****************************************************************************

    FUNCTION:  InitInstance(HANDLE, int)

    PURPOSE:  Saves instance handle and creates main window

    COMMENTS:

        This function is called at initialization time for every instance of 
        this application.  This function performs initialization tasks that 
        cannot be shared by multiple instances.  

        In this case, we save the instance handle in a static variable and 
        create and display the main program window.  
        
****************************************************************************/

BOOL InitInstance(hInstance, nCmdShow)
    HANDLE          hInstance;          /* Current instance identifier.       */
    int             nCmdShow;           /* Param for first ShowWindow() call. */
{
    HWND            hWnd;               /* Main window handle.                */

    /* Save the instance handle in static variable, which will be used in  */
    /* many subsequence calls from this application to Windows.            */

    hInst = hInstance;

    /* Create a main window for this application instance.  */

    hWnd = CreateWindow(
        "dibitWClass",                /* See RegisterClass() call.          */
        "dibit Sample Application",   /* Text for window title bar.         */
        WS_OVERLAPPEDWINDOW,            /* Window style.                      */
        CW_USEDEFAULT,                  /* Default horizontal position.       */
        CW_USEDEFAULT,                  /* Default vertical position.         */
        CW_USEDEFAULT,                  /* Default width.                     */
        CW_USEDEFAULT,                  /* Default height.                    */
        NULL,                           /* Overlapped windows have no parent. */
        NULL,                           /* Use the window class menu.         */
        hInstance,                      /* This instance owns this window.    */
        NULL                            /* Pointer not needed.                */
    );

    /* If window could not be created, return "failure" */

    if (!hWnd)
        return (FALSE);

    /* Make the window visible; update its client area; and return "success" */

    ShowWindow(hWnd, nCmdShow);  /* Show the window                        */
    UpdateWindow(hWnd);          /* Sends WM_PAINT message                 */
    return (TRUE);               /* Returns the value from PostQuitMessage */

}

/****************************************************************************

    FUNCTION: MainWndProc(HWND, UINT, WPARAM, LPARAM)

    PURPOSE:  Processes messages

    MESSAGES:

	WM_COMMAND    - application menu (About dialog box)
	WM_DESTROY    - destroy window

    COMMENTS:

	To process the IDM_ABOUT message, call MakeProcInstance() to get the
	current instance address of the About() function.  Then call Dialog
	box which will create the box according to the information in your
	dibit.rc file and turn control over to the About() function.	When
	it returns, free the intance address.

****************************************************************************/

long FAR PASCAL __export MainWndProc(hWnd, message, wParam, lParam)
HWND hWnd;				  /* window handle		     */
UINT message;			      /* type of message		 */
WPARAM wParam;				    /* additional information	       */
LPARAM lParam;				    /* additional information	       */
{
    FARPROC lpProcAbout;
    OPENFILENAME    ofn;

    switch (message) {
	case WM_CREATE:
	    hDIBInfo = GlobalAlloc(GMEM_MOVEABLE, 
	    		(DWORD)(sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD)));
	    break;

	case WM_INITMENU:
	    CheckMenuItem(wParam, wOperation, MF_CHECKED);
	    break;

	case WM_COMMAND:	   /* message: command from application menu */
	    switch(wParam) {
		case IDM_ABOUT:
		    lpProcAbout = MakeProcInstance(About, hInst);

		    DialogBox(hInst,		 /* current instance	     */
		        "AboutBox",			 /* resource to use	     */
		        hWnd,			 /* parent handle	     */
		        lpProcAbout);		 /* About() instance address */

		    FreeProcInstance(lpProcAbout);
		    break;

		case IDM_SETDIB:
		case IDM_TODEV:
		case IDM_STRETCH:
		    CheckMenuItem(GetMenu(hWnd), wOperation, MF_UNCHECKED);
		    wOperation = wParam;
		    CheckMenuItem(GetMenu(hWnd), wOperation, MF_CHECKED);
		    InvalidateRect(hWnd, NULL, TRUE);
		    break;

		case IDM_PALRGB:
		case IDM_PALIND:
		    if (wPalOp == wParam)	/* turning off palette use */
		    {
			CheckMenuItem(GetMenu(hWnd), wPalOp, MF_UNCHECKED);
			wPalOp = 0;

			/* since palette use is being turned off, 
			** any device-dependent bitmap we have created
			** is no longer valid for use.  free it up
			*/
			if (hDDBitmap)
			{
			    SelectObject(hMemDC, hOldBitmap);
			    DeleteDC(hMemDC);
			    DeleteObject(hDDBitmap);
			    hDDBitmap = NULL;
			}
		    }
		    else	/* changing palette use options */
		    {
			if (wPalOp)
			    CheckMenuItem(GetMenu(hWnd), wPalOp, MF_UNCHECKED);

			/* turning on palette use for the first time.
			** if we had a device-dependent bitmap, get rid
			** of it so that it will be rebuilt with palette.
			*/
			else if (hDDBitmap)
			{
			    SelectObject(hMemDC, hOldBitmap);
			    DeleteDC(hMemDC);
			    DeleteObject(hDDBitmap);
			    hDDBitmap = NULL;
			}
			wPalOp = wParam;
			CheckMenuItem(GetMenu(hWnd), wPalOp, MF_CHECKED);
		    }
		    InvalidateRect(hWnd, NULL, TRUE);
		    break;

                case IDM_OPEN:
		    ofn.lStructSize = sizeof(OPENFILENAME);
		    ofn.hwndOwner = hWnd;
		    ofn.lpstrFilter = NULL;
                    ofn.lpstrFilter = "Bitmaps (*.BMP)\0*.BMP\0";
		    ofn.lpstrCustomFilter = NULL;
		    ofn.nFilterIndex = 1;
		    achFileName[0] = 0;		/* pass in NULL */
		    ofn.lpstrFile = (LPSTR)achFileName;
		    ofn.nMaxFile = 128;
		    ofn.lpstrInitialDir = NULL;
		    ofn.lpstrTitle = NULL;
		    ofn.lpstrFileTitle = NULL;
            ofn.lpstrDefExt = NULL;
                    ofn.Flags = 0;

                    if (GetOpenFileName((LPOPENFILENAME)&ofn))
			if (InitDIB (hWnd))
			    InvalidateRect (hWnd, NULL, FALSE);
                    break;

		default:
		    return (DefWindowProc(hWnd, message, wParam, lParam));
	    }
	    break;

	/* if system palette change caused by someone else, force repaint */
	case WM_PALETTECHANGED:
	    if (wParam != hWnd && bDIBLoaded)
		InvalidateRect(hWnd, NULL, TRUE);
	    break;

	/* if doing stretching, resize the image */
	case WM_SIZE:
	    if (wOperation == IDM_STRETCH && bDIBLoaded)
		InvalidateRect(hWnd, NULL, TRUE);
	    break;

	case WM_PAINT:
	    if (!bDIBLoaded)		/* if no DIB loaded, nothing to draw */
		return (DefWindowProc(hWnd, message, wParam, lParam));
	    else
		PaintDIB(hWnd);
	    break;

	case WM_DESTROY:		  /* message: window being destroyed */
	    PostQuitMessage(0);
	    break;

	default:			  /* Passes it on if unproccessed    */
	    return (DefWindowProc(hWnd, message, wParam, lParam));
    }
    return (NULL);
}

/****************************************************************************
 *									    *
 *  FUNCTION   : MakeIndexHeader(lpInfo)				    *
 *									    *
 *  PURPOSE    : Given a BITMAPINFOHEADER, create a new info header 
 *		 using the DIB_PAL_COLORS format.
 *									    *
 *  RETURNS    : non-zero - global handle of a new header
 *		 zero - unable to create new header
 *									    *
 ****************************************************************************/
HANDLE PASCAL NEAR MakeIndexHeader(LPBITMAPINFOHEADER lpInfo)
{
    HANDLE hPalInfo;
    LPBITMAPINFOHEADER lpPalInfo;
    WORD FAR *lpTable;
    WORD i;

    if (lpInfo->biClrUsed)
    {
	hPalInfo = GlobalAlloc(GMEM_MOVEABLE, lpInfo->biSize +
					lpInfo->biClrUsed * sizeof(WORD));
	if (!hPalInfo)
	    return(NULL);
	lpPalInfo = (LPBITMAPINFOHEADER)GlobalLock(hPalInfo);

	*lpPalInfo = *lpInfo;
	lpTable = (WORD FAR *)((LPSTR)lpPalInfo + lpPalInfo->biSize);

        for (i = 0; i < (WORD)lpInfo->biClrUsed; i++)
	    *lpTable++ = i;

	GlobalUnlock(hPalInfo);
	return(hPalInfo);
    }
    else
	return(NULL);
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
        for (i = 0; i < (WORD)lpInfo->biClrUsed; i++, lpRGB++)
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

/****************************************************************************
 *									    *
 *  FUNCTION   : PaintDIB(hWnd)						    *
 *									    *
 *  PURPOSE    : Paint the currently loaded DIB using the options chosen
 *		 by the user.
 *									    *
 *  RETURNS    : None.
 *									    *
 ****************************************************************************/
void PASCAL NEAR PaintDIB(HWND hWnd)
{
    PAINTSTRUCT ps;
    HDC hDC;
    RECT Rectangle;
    LPBITMAPINFOHEADER lpInfo;
    LPBITMAPINFOHEADER lpHeader;
    HPALETTE hOldPal;
    WORD wDIBUse;

    hDC = BeginPaint(hWnd, &ps);
    lpInfo = (LPBITMAPINFOHEADER) GlobalLock(hDIBInfo);

    /* if using a palette for drawing and there is actually 
    ** a color table, then get a palette and realize it.
    */
    if (wPalOp && lpInfo->biClrUsed)
    {
	if (!hPalette)
	    hPalette = MakeDIBPalette(lpInfo);
	if (!hPalette)
	{
	    MessageBox(hWnd, "Can't create palette", "Error", MB_ICONSTOP | MB_OK);
	    goto ExitTime;
	}
	hOldPal = SelectPalette(hDC, hPalette, FALSE);
	RealizePalette(hDC);

	/* if using DIB_PAL_COLORS and the bitmap is not 24-bit,
	** then use a header with a color table of indices.
	*/
	if (wPalOp == IDM_PALIND && (lpInfo->biBitCount != 24))
	{
	    if (!hPalHeader)
	    {
		hPalHeader = MakeIndexHeader(lpInfo);
	    }
	    if (!hPalHeader)
	    {
		MessageBox(hWnd, "Can't create Indexed color table", "Error", MB_ICONSTOP | MB_OK);
		goto ExitTime;
	    }
	    lpHeader = (LPBITMAPINFOHEADER) GlobalLock(hPalHeader);
	    wDIBUse = DIB_PAL_COLORS;
	}
	else
	{
	    lpHeader = lpInfo;
	    wDIBUse = DIB_RGB_COLORS;
	}
    }
    else
    {
	lpHeader = lpInfo;
	wDIBUse = DIB_RGB_COLORS;
    }

    switch (wOperation)
    {
	case IDM_SETDIB:
		//error message if can't create
			
	    if (!hDDBitmap)
	    {
		hMemDC = CreateCompatibleDC(hDC);
		hDDBitmap = CreateCompatibleBitmap(hDC, 
				(WORD)lpInfo->biWidth, (WORD)lpInfo->biHeight);
		SetDIBits(hDC, hDDBitmap, 0, (WORD)lpInfo->biHeight, 
					(LPSTR)lpInfo + offBits, 
					(LPBITMAPINFO)lpHeader, wDIBUse);
		hOldBitmap = SelectObject(hMemDC, hDDBitmap);
	    }
	    BitBlt(hDC, 0, 0, (WORD)lpInfo->biWidth, (WORD)lpInfo->biHeight,
	    		hMemDC, 0, 0, SRCCOPY);
	    break;
	case IDM_TODEV:
	    SetDIBitsToDevice(hDC, 0, 0, (WORD)lpInfo->biWidth, (WORD)lpInfo->biHeight,
	    		0, 0, 0, (WORD)lpInfo->biHeight, 
			(LPSTR)lpInfo + offBits, (LPBITMAPINFO)lpHeader, wDIBUse);
	    break;
	case IDM_STRETCH:
	/* get dimensions of window and stretch to fit */
	    GetClientRect(hWnd, (LPRECT)&Rectangle);
	    StretchDIBits(hDC, 0, 0, Rectangle.right, Rectangle.bottom,
				0, 0, (WORD)lpInfo->biWidth, (WORD)lpInfo->biHeight,
				(LPSTR)lpInfo + offBits, 
				(LPBITMAPINFO)lpHeader, wDIBUse, SRCCOPY);

	/* NOTE: because driver does not do the StretchDIB
	**       itself, this is not a fast operation.
	**       internally it converts to CreateDIBitmap
	**       followed by a StretchBlt
	*/
	    break;
    }

    /* clean up any palette work */
    if (wPalOp)
    {
	SelectPalette(hDC, hOldPal, FALSE);
	if (wPalOp == IDM_PALIND)
	    GlobalUnlock(hPalHeader);
    }

ExitTime:
    GlobalUnlock(hDIBInfo);
    EndPaint(hWnd, &ps);
}


/****************************************************************************
 *									    *
 *  FUNCTION   : ReadDIB(hWnd)						    *
 *									    *
 *  PURPOSE    : Reads a DIB from a file, obtains a handle to it's          *
 *		 BITMAPINFO struct. and loads the DIB.                      *
 *									    *
 *  RETURNS    : TRUE  - DIB loads ok					    *
 *		 FALSE - otherwise					    *
 *									    *
 ****************************************************************************/
int ReadDIB(HWND hWnd)
{
    unsigned	       fh;
    LPBITMAPINFOHEADER lpbi;
    OFSTRUCT	       of;
    BITMAPFILEHEADER   bf;
    WORD		nNumColors;
    WORD		result = FALSE;		/* assume failure */

    /* Open the file and get a handle to it's BITMAPINFO */

    fh = OpenFile (achFileName, &of, OF_READ);
    if (fh == -1) {
        wsprintf(str,"Can't open file '%ls'", (LPSTR)achFileName);
	MessageBox(hWnd, str, "Error", MB_ICONSTOP | MB_OK);
	return (FALSE);
    }

    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIBInfo);

    /* read the BITMAPFILEHEADER */
    if (sizeof (bf) != _lread (fh, (LPSTR)&bf, sizeof (bf)))
	goto ErrExit;

    if (bf.bfType != 0x4d42)	/* 'BM' */
	goto ErrExit;

    if (sizeof(BITMAPINFOHEADER) != _lread (fh, (LPSTR)lpbi, sizeof(BITMAPINFOHEADER)))
	goto ErrExit;

    /* !!!!! for now, don't even deal with CORE headers */
    if (lpbi->biSize == sizeof(BITMAPCOREHEADER))
	goto ErrExit;

    if (!(nNumColors = (WORD)lpbi->biClrUsed))
    {
	/* no color table for 24-bit, default size otherwise */
	if (lpbi->biBitCount != 24)
	    nNumColors = 1 << lpbi->biBitCount;	/* standard size table */
    }

    /*	fill in some default values if they are zero */
    if (lpbi->biClrUsed == 0)
        lpbi->biClrUsed = (DWORD)nNumColors;

    if (lpbi->biSizeImage == 0)
    {
	lpbi->biSizeImage = ((((lpbi->biWidth * (DWORD)lpbi->biBitCount) + 31) & ~31) >> 3)
			 * lpbi->biHeight;
    }

    /* get a proper-sized buffer for header, color table and bits */ 
    GlobalUnlock(hDIBInfo);
    hDIBInfo = GlobalReAlloc(hDIBInfo, lpbi->biSize +
    					nNumColors * sizeof(RGBQUAD) +
					lpbi->biSizeImage, 0);
    if (!hDIBInfo)	/* can't resize buffer for loading */
	goto ErrExit2;

    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIBInfo);

    /* read the color table */
    _lread (fh, (LPSTR)(lpbi) + lpbi->biSize, nNumColors * sizeof(RGBQUAD));

    /* offset to the bits from start of DIB header */
    offBits = (WORD)lpbi->biSize + nNumColors * sizeof(RGBQUAD);

    if (bf.bfOffBits != 0L)
    {
        _llseek(fh,bf.bfOffBits,SEEK_SET);
    }
    if (lpbi->biSizeImage == lread(fh, (LPSTR)lpbi + offBits, lpbi->biSizeImage))
	result = TRUE;

ErrExit:
    _lclose(fh);
    GlobalUnlock(hDIBInfo);
ErrExit2:
    return(result);
}

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
 *									    *
 *  FUNCTION   : InitDIB(hWnd)						    *
 *									    *
 *  PURPOSE    : cleans up old DIB info, reads new DIB from file,
 *		 resizes window for new DIB		 
 *									    *
 *  RETURNS    : TRUE  - DIB loads ok					    *
 *		 FALSE - otherwise					    *
 *									    *
 ****************************************************************************/
int InitDIB(HWND hWnd)
{
    LPBITMAPINFOHEADER lpbi;
    RECT		Rectangle;

    /* if there was an old DIB, free it up */
    if (bDIBLoaded)
    {
	if (hDDBitmap)
	{
	    SelectObject(hMemDC, hOldBitmap);
	    DeleteDC(hMemDC);
	    DeleteObject(hDDBitmap);
	    hDDBitmap = NULL;
	}
	bDIBLoaded = FALSE;
	if (hPalette)
	{
	    DeleteObject(hPalette);
	    hPalette = 0;
	}
	if (hPalHeader)
	{
	    GlobalFree(hPalHeader);
	    hPalHeader = NULL;
	}
    }


    /* load the DIB from the file */
    if (!ReadDIB(hWnd))
    {
	MessageBox(hWnd, "Error attempting to read DIB", "Error", MB_ICONSTOP | MB_OK);
	return(FALSE);
    }

    bDIBLoaded = TRUE;		/* there is a DIB loaded now */

    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIBInfo);
    SetWindowText(hWnd, achFileName);
    Rectangle.left	 = 0;
    Rectangle.top	 = 0;
    Rectangle.right  = (WORD)lpbi->biWidth;
    Rectangle.bottom = (WORD)lpbi->biHeight;
    GlobalUnlock(hDIBInfo);

    /* Compute the size of the window rectangle based on the given
     * client rectangle size and the window style, then size the
     * window.  Do not deal with possibility of more than one menu line.
     */
    AdjustWindowRect (&Rectangle, WS_OVERLAPPEDWINDOW, TRUE);
    SetWindowPos (hWnd, (HWND)NULL, 0, 0,
		      Rectangle.right  - Rectangle.left,
		      Rectangle.bottom - Rectangle.top + 1,
		      SWP_NOMOVE | SWP_NOZORDER);

    GetClientRect(hWnd, &Rectangle);

    return(TRUE);
}

/****************************************************************************

    FUNCTION: About(HWND, unsigned, WORD, LONG)

    PURPOSE:  Processes messages for "About" dialog box

    MESSAGES:

	WM_INITDIALOG - initialize dialog box
	WM_COMMAND    - Input received

    COMMENTS:

	No initialization is needed for this particular dialog box, but TRUE
	must be returned to Windows.

	Wait for user to click on "Ok" button, then close the dialog box.

****************************************************************************/

BOOL FAR PASCAL __export About(hDlg, message, wParam, lParam)
HWND hDlg;                                /* window handle of the dialog box */
unsigned message;                         /* type of message                 */
WORD wParam;                              /* message-specific information    */
LONG lParam;
{
    switch (message) {
	case WM_INITDIALOG:		   /* message: initialize dialog box */
	    return (TRUE);

	case WM_COMMAND:		      /* message: received a command */
	    if (wParam == IDOK                /* "OK" box selected?	     */
                || wParam == IDCANCEL) {      /* System menu close command? */
		EndDialog(hDlg, TRUE);	      /* Exits the dialog box	     */
		return (TRUE);
	    }
	    break;
    }
    return (FALSE);			      /* Didn't process a message    */
}
