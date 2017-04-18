/****************************************************************************

    PROGRAM: transblt.c

    PURPOSE: transblt template for Windows applications

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

#include "windows.h"		    /* required for all Windows applications */
#include "mmsystem.h"		// needed for CAPS1 definitions
#include "transblt.h"		    /* specific to this program		     */

#define rgbWhite RGB(255,255,255)
#define rgbBlack RGB(0,0,0)
#define rgbTransparent HouseColor[wTransColor - IDM_BLACK]

HANDLE hInst;			    /* current instance			     */

HBITMAP hbmHouse;
HBITMAP hbmFade;
HBITMAP hbmDefault;
HBITMAP	hbmBinoculars;
HBITMAP hbmTransMask;
HDC hdcMem, hdcMem2;
BOOL bTransMaskBuilt = FALSE;

WORD wMaskType = IDM_MASK1;	// mask being demoed.
WORD wTransColor = IDM_BLACK;	// transparent color

DWORD HouseColor[5] = {RGB(0,0,0), RGB(255,0,0), RGB(128,0,0), RGB(0,255,0),
			RGB(0,255,255)};

void PASCAL NEAR BuildBitmaps(void);
void PASCAL NEAR DestroyBitmaps(void);
void PASCAL NEAR PaintIt(HWND);
void PASCAL NEAR ShowStatus(HDC, HDC, HDC);

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
    wc.lpfnWndProc = (WNDPROC) MainWndProc;
                                        /* windows of this class.             */
    wc.cbClsExtra = 0;                  /* No per-class extra data.           */
    wc.cbWndExtra = 0;                  /* No per-window extra data.          */
    wc.hInstance = hInstance;           /* Application that owns the class.   */
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(WHITE_BRUSH); 
    wc.lpszMenuName =  "transbltMenu";   /* Name of menu resource in .RC file. */
    wc.lpszClassName = "transbltWClass"; /* Name used in call to CreateWindow. */

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
        "transbltWClass",                /* See RegisterClass() call.          */
        "transblt Sample Application",   /* Text for window title bar.         */
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

    FUNCTION: MainWndProc(HWND, unsigned, WORD, LONG)

    PURPOSE:  Processes messages

    MESSAGES:

	WM_COMMAND    - application menu (About dialog box)
	WM_DESTROY    - destroy window

    COMMENTS:

	To process the IDM_ABOUT message, call MakeProcInstance() to get the
	current instance address of the About() function.  Then call Dialog
	box which will create the box according to the information in your
	transblt.rc file and turn control over to the About() function.	When
	it returns, free the intance address.

****************************************************************************/

long FAR PASCAL MainWndProc(hWnd, message, wParam, lParam)
HWND hWnd;				  /* window handle		     */
unsigned message;			  /* type of message		     */
WORD wParam;				  /* additional information	     */
LONG lParam;				  /* additional information	     */
{
    FARPROC lpProcAbout;		  /* pointer to the "About" function */

    switch (message) {
	case WM_CREATE:
	    BuildBitmaps();
	    break;

	case WM_INITMENU:
	    CheckMenuItem(wParam, wMaskType, MF_CHECKED);
	    CheckMenuItem(wParam, wTransColor, MF_CHECKED);
	    break;

	case WM_COMMAND:	   /* message: command from application menu */
	    switch (wParam)
	    {
		case IDM_ABOUT:
		{
		    lpProcAbout = MakeProcInstance(About, hInst);

		    DialogBox(hInst,		 /* current instance	     */
		    "AboutBox",			 /* resource to use	     */
		    hWnd,			 /* parent handle	     */
		    lpProcAbout);		 /* About() instance address */

		    FreeProcInstance(lpProcAbout);
		    break;
		}

		case IDM_MASK1:
		case IDM_MASK2:
		case IDM_MASK3:
		    if (wParam != wMaskType)
		    {
			CheckMenuItem(GetMenu(hWnd), wMaskType, MF_UNCHECKED);
			wMaskType = wParam;
			CheckMenuItem(GetMenu(hWnd), wMaskType, MF_CHECKED);
			InvalidateRect(hWnd, NULL, TRUE);
		    }
		    break;

		case IDM_BLACK:
		case IDM_RED:
		case IDM_DRED:
		case IDM_GREEN:
		case IDM_CYAN:
		    if (wParam != wTransColor)
		    {
			CheckMenuItem(GetMenu(hWnd), wTransColor, MF_UNCHECKED);
			wTransColor = wParam;
			CheckMenuItem(GetMenu(hWnd), wTransColor, MF_UNCHECKED);

			bTransMaskBuilt = FALSE;
			InvalidateRect(hWnd, NULL, TRUE);
		    }
		    break;

		default: /* Lets Windows process it	     */
		    return (DefWindowProc(hWnd, message, wParam, lParam));
	    }
	    break;

	case WM_PAINT:
	    PaintIt(hWnd);
	    break;

	case WM_DESTROY:		  /* message: window being destroyed */
	    DestroyBitmaps();
	    PostQuitMessage(0);
	    break;

	default:			  /* Passes it on if unproccessed    */
	    return (DefWindowProc(hWnd, message, wParam, lParam));
    }
    return (NULL);
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

BOOL FAR PASCAL About(hDlg, message, wParam, lParam)
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

/****************************************************************************
 *
 *  FUNCTION   : PaintIt(hWnd)
 *
 *  PURPOSE    : 
 *
 *  RETURNS    : None.
 *
 ****************************************************************************/
void PASCAL NEAR PaintIt(HWND hWnd)
{
    PAINTSTRUCT ps;
    HDC hdcScreen;
    WORD x=320, y=20, i;
    WORD oldMode;
    DWORD rgbOld;

    hdcScreen = BeginPaint(hWnd, &ps);

    // fill in destination space.
    SelectObject(hdcMem, hbmFade);
    BitBlt(hdcScreen, 300, 0, 100, 100, hdcMem, 0, 0, SRCCOPY);

    SetBkColor(hdcScreen, rgbWhite);
    SetTextColor(hdcScreen, rgbBlack);

    switch (wMaskType)
    {
	case (IDM_MASK1):
	    SelectObject(hdcMem, hbmHouse);
	    SelectObject(hdcMem2, hbmBinoculars);

	    ShowStatus(hdcScreen, hdcMem, hdcMem2);

	    BitBlt(hdcScreen, x, y, 50, 50, hdcMem, 0, 0, SRCINVERT);
	    BitBlt(hdcScreen, x, y, 50, 50, hdcMem2, 0, 0, SRCAND);
	    BitBlt(hdcScreen, x, y, 50, 50, hdcMem, 0, 0, SRCINVERT);
	    break;

	case (IDM_MASK2):
	case (IDM_MASK3):
	    SelectObject(hdcMem, hbmHouse);
	    SelectObject(hdcMem2, hbmTransMask);

	    // if the device supports transparency, let it do the work.
	    if (GetDeviceCaps(hdcScreen, CAPS1) & C1_TRANSPARENT)
	    {
		oldMode = SetBkMode(hdcScreen, NEWTRANSPARENT);
		rgbOld = SetBkColor(hdcScreen, rgbTransparent);
		BitBlt(hdcScreen, x, y, 50, 50, hdcMem, 0, 0, SRCCOPY);
		SetBkColor(hdcScreen, rgbOld);
		SetBkMode(hdcScreen, oldMode);
		break;
	    }

	    // build mask based on transparent color.
	    if (!bTransMaskBuilt)
	    {
		bTransMaskBuilt = TRUE;

		SetBkColor(hdcMem, rgbTransparent);
		BitBlt(hdcMem2, 0, 0, 50, 50, hdcMem, 0, 0, SRCCOPY);
	    }

	    ShowStatus(hdcScreen, hdcMem, hdcMem2);

	    // using a true mask.
	    if (wMaskType == IDM_MASK2)
	    {
		BitBlt(hdcScreen, x, y, 50, 50, hdcMem, 0, 0, SRCINVERT);
		BitBlt(hdcScreen, x, y, 50, 50, hdcMem2, 0, 0, SRCAND);
		BitBlt(hdcScreen, x, y, 50, 50, hdcMem, 0, 0, SRCINVERT);
	    }

	    // using the black-source method.
	    else
	    {
		// if transparent color is black, the house bitmap is
		// ready for use.  Otherwise, put black in the right
		// place for masking.
		if (wTransColor != IDM_BLACK)
		{
		    SetBkColor(hdcMem, rgbBlack);
		    SetTextColor(hdcMem, rgbWhite);
		    BitBlt(hdcMem, 0, 0, 50, 50, hdcMem2, 0, 0, SRCAND);

		    // show the modified bitmap
		    BitBlt(hdcScreen, 120, 150, 50, 50, hdcMem, 0, 0, SRCCOPY);
		    TextOut(hdcScreen, 100, 220, "(Modified Source)", 17);
		}

		BitBlt(hdcScreen, x, y, 50, 50, hdcMem2, 0, 0, SRCAND);
		BitBlt(hdcScreen, x, y, 50, 50, hdcMem, 0, 0, SRCPAINT);

		// undo work on house bitmap.
		if (wTransColor != IDM_BLACK)
		{
		    SetBkColor(hdcMem, rgbTransparent);
		    SetTextColor(hdcMem, rgbBlack);
		    BitBlt(hdcMem, 0, 0, 50, 50, hdcMem2, 0, 0, SRCPAINT);
		}
	    }
	    break;
    }

    SelectObject(hdcMem, hbmDefault);
    SelectObject(hdcMem2, hbmDefault);
    EndPaint(hWnd, &ps);
}

void PASCAL NEAR ShowStatus(HDC hdcDst, HDC hdcSrc, HDC hdcMask)
{
    HBITMAP hbm;

    hbm = SelectObject(hdcSrc, hbmFade);
    BitBlt(hdcDst, 0, 0, 100, 100, hdcSrc, 0, 0, SRCCOPY);
    SelectObject(hdcSrc, hbm);
    TextOut(hdcDst, 0, 110, "Destination", 11);

    BitBlt(hdcDst, 120, 20, 50, 50, hdcSrc, 0, 0, SRCCOPY);
    TextOut(hdcDst, 100, 110, "+ Source", 8);

    if (hdcMask)
    {
	BitBlt(hdcDst, 220, 20, 50, 50, hdcMask, 0, 0, SRCCOPY);
	TextOut(hdcDst, 200, 110, "+ Mask", 6);
    }

    TextOut(hdcDst, 300, 110, "= Transparency", 14);
}

void PASCAL NEAR BuildBitmaps(void)
{
    HDC hdcScreen;
    HBRUSH hbr;
    POINT poly[3];
    WORD i;

    hdcScreen = GetDC(NULL);

    hbmHouse = CreateCompatibleBitmap(hdcScreen, 50, 50);
    hbmFade = CreateCompatibleBitmap(hdcScreen, 100, 100);
    hbmBinoculars = CreateBitmap(50, 50, 1, 1, NULL);
    hbmTransMask = CreateBitmap(50, 50, 1, 1, NULL);
    hdcMem = CreateCompatibleDC(hdcScreen);
    hdcMem2 = CreateCompatibleDC(hdcScreen);

    ReleaseDC(NULL, hdcScreen);

    // Draw the house bitmap.  This will be the basic source bitmap.

    SelectObject(hdcMem, GetStockObject(NULL_PEN));
    hbmDefault = SelectObject(hdcMem, hbmHouse);
    
    // sky.
    hbr = CreateSolidBrush(RGB(0, 255, 255));
    hbr = SelectObject(hdcMem, hbr);
    PatBlt(hdcMem, 0, 0, 50, 30, PATCOPY);
    hbr = SelectObject(hdcMem, hbr);
    DeleteObject(hbr);

    // horizon.
    PatBlt(hdcMem, 0, 30, 50, 31, BLACKNESS);

    // lawn
    hbr = CreateSolidBrush(RGB(0, 255, 0));
    hbr = SelectObject(hdcMem, hbr);
    PatBlt(hdcMem, 0, 31, 50, 20, PATCOPY);
    hbr = SelectObject(hdcMem, hbr);
    DeleteObject(hbr);

    // house body
    hbr = CreateSolidBrush(RGB(255, 0, 0));
    hbr = SelectObject(hdcMem, hbr);
    PatBlt(hdcMem, 5, 20, 40, 20, PATCOPY);
    hbr = SelectObject(hdcMem, hbr);
    DeleteObject(hbr);

    // house roof
    hbr = CreateSolidBrush(RGB(128, 0, 0));
    hbr = SelectObject(hdcMem, hbr);
    poly[0].x = 2;
    poly[0].y = 20;
    poly[1].x = 47;
    poly[1].y = 20;
    poly[2].x = 25;
    poly[2].y = 5;
    Polygon(hdcMem, poly, 3);
    hbr = SelectObject(hdcMem, hbr);
    DeleteObject(hbr);

    // windows
    hbr = SelectObject(hdcMem, GetStockObject(BLACK_BRUSH));
    PatBlt(hdcMem, 10, 22, 12, 13, BLACKNESS);
    PatBlt(hdcMem, 28, 22, 12, 13, BLACKNESS);


    // build the fade background bitmap.
    SelectObject(hdcMem, hbmFade);
    for (i=56; i<256; i+=2)
    {
	hbr = CreateSolidBrush(RGB(i, 0, i));
	hbr = SelectObject(hdcMem, hbr);
	PatBlt(hdcMem, 0, (i - 56)/2, 100, 3, PATCOPY);
	hbr = SelectObject(hdcMem, hbr);
	DeleteObject(hbr);
    }

    // build the binoculars true mask.
    SelectObject(hdcMem, hbmBinoculars);
    PatBlt(hdcMem, 0, 0, 50, 50, WHITENESS);
    SelectObject(hdcMem, GetStockObject(BLACK_BRUSH));
    Ellipse(hdcMem, 7, 7, 24, 43);
    Ellipse(hdcMem, 26, 7, 43, 43);

    SelectObject(hdcMem, hbmDefault);
}

void PASCAL NEAR DestroyBitmaps(void)
{
    DeleteObject(hbmHouse);
    DeleteObject(hbmFade);
    DeleteObject(hbmBinoculars);
    DeleteObject(hbmTransMask);
    DeleteDC(hdcMem);
    DeleteDC(hdcMem2);
}
