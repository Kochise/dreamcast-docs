/*****************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1992-1997 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\*****************************************************************************/
/*****************************************************************************
 *																			 *
 *   PROGRAM: TextFX.c														 *
 *																			 *
 *   PURPOSE: TextFX template for Windows applications						 *
 *																			 *
 *   FUNCTIONS:																 *
 *																			 *
 *   GetLastErrorBox() - Report GetLastError() values as text                *
 *   WinMain() - calls initialization function, processes message loop		 *
 *   InitApplication() - initializes window data and registers window		 *
 *   InitInstance() - saves instance handle and creates main window			 *
 *   WndProc() - processes messages											 *
 *   CenterWindow() - used to center the "About" box over application window *
 *   About() - processes messages for "About" dialog box					 *
 *																			 *
 *   COMMENTS:																 *
 *****************************************************************************/

#include <windows.h>   // required for all Windows applications
#include "resource.h"  // specific to this program
#include <time.h>
#include "textfx.h"    // specific to this program
#include "guide.h"
#include "fx.h"

#define QUICKTESTPOINTS 2      // Number of points to use for Quick Test

HINSTANCE hInst;       // current instance

char szAppName[] = "TextFX";   // The name of this application
char szTitle[]   = "TextFX Test Application"; // The title bar text

// Random number stuff for generating random points for "Quick Test" option
#define randfloat() ((float)rand() / (float)RAND_MAX)
#define random(i) ((short)(randfloat() * (float)(i)))

/**********************************************************************
 *                                                                    *
 * FUNCTION:  GetLastErrorBox(HWND, LPSTR)                            *  
 *																	  *
 * PURPOSE:   Gets the error status and, if an error is indicated,    *
 *            converts the error number into text and displays it     *
 *            in a MessageBox.                                        *
 *                                                                    *
 *********************************************************************/
DWORD GetLastErrorBox(HWND hWnd, LPSTR lpTitle)
{
   LPVOID lpv;
   DWORD  dwRv;

   if (GetLastError() == 0) return 0;
   
   dwRv = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                        FORMAT_MESSAGE_FROM_SYSTEM,
                        NULL,
                        GetLastError(),
                        MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
                        (LPVOID)&lpv,
                        0,
                        NULL);
   
   MessageBox(hWnd, lpv, lpTitle, MB_OK);
   
   if(dwRv)
      LocalFree(lpv);
   
   SetLastError(0);
   return dwRv;
}

/*****************************************************************************
 *																			 *
 * FUNCTION: WinMain(HINSTANCE, HINSTANCE, LPSTR, int)						 *
 *																			 *
 * PURPOSE: calls initialization function, processes message loop			 *
 *																			 *
 * COMMENTS:																 *
 *																			 *
 *    Windows recognizes this function by name as the initial entry point	 *
 *    for the program.  This function calls the application initialization	 *
 *    routine, if no other instance of the program is running, and always	 *
 *    calls the instance initialization routine.  It then executes a message *
 *    retrieval and dispatch loop that is the top-level control structure	 *
 *    for the remainder of execution.  The loop is terminated when a WM_QUIT *
 *    message is received, at which time this function exits the application *
 *    instance by returning the value passed by PostQuitMessage().			 *
 *																			 *
 *    If this function must abort before entering the message loop, it		 *
 *    returns the conventional value NULL.									 *
 *																			 *
 ****************************************************************************/
int APIENTRY WinMain(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow)
{		
    MSG msg;
    HANDLE hAccelTable;
	LONG lTime;

	// Just for fun, lets seed the random number generator
	time(&lTime);
    srand(lTime);


    if (!hPrevInstance) {       // Other instances of app running?
            if (!InitApplication(hInstance)) { // Initialize shared things
            return (FALSE);     // Exits if unable to initialize
        }
    }

    /* Perform initializations that apply to a specific instance */

    if (!InitInstance(hInstance, nCmdShow)) {
            return (FALSE);
    }

    hAccelTable = LoadAccelerators (hInstance, "TEXTFXACCEL");

    /* Acquire and dispatch messages until a WM_QUIT message is received. */

    while (GetMessage(&msg, // message structure
       NULL,   // handle of window receiving the message
       0,      // lowest message to examine
       0))     // highest message to examine
    {
        if (!TranslateAccelerator (msg.hwnd, hAccelTable, &msg)) {
            TranslateMessage(&msg);// Translates virtual key codes
            DispatchMessage(&msg); // Dispatches message to window
        }
    }

    return (msg.wParam); // Returns the value from PostQuitMessage

    UNREFERENCED_PARAMETER(lpCmdLine); // This will prevent 'unused formal parameter' warnings
}


/*****************************************************************************
 *																			 *
 *  FUNCTION: InitApplication(HINSTANCE)									 *
 *																			 *
 *  PURPOSE: Initializes window data and registers window class				 *
 *																			 *
 *  COMMENTS:																 *
 *																			 *
 *    This function is called at initialization time only if no other		 *
 *    instances of the application are running.  This function performs	     *
 *    initialization tasks that can be done once for any number of running	 *
 *    instances.															 *
 *																			 *
 *    In this case, we initialize a window class by filling out a data		 *
 *    structure of type WNDCLASS and calling the Windows RegisterClass()	 *
 *    function.  Since all instances of this application use the same window *
 *    class, we only need to do this when the first instance is initialized. *
 *																			 *
 *****************************************************************************/
BOOL InitApplication(HINSTANCE hInstance)
{
    WNDCLASS  wc;

    // Fill in window class structure with parameters that describe the
    // main window.

    wc.style         = CS_OWNDC;               // Class style(s).
    wc.lpfnWndProc   = (WNDPROC)WndProc;       // Window Procedure
    wc.cbClsExtra    = 0;                      // No per-class extra data.
    wc.cbWndExtra    = 0;                      // No per-window extra data.
    wc.hInstance     = hInstance;              // Owner of this class
    wc.hIcon         = LoadIcon (hInstance, szAppName); // Icon name from .RC
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);// Cursor
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);// Default color
    wc.lpszMenuName  = "TEXTFXMENU";           // Menu name from .RC
    wc.lpszClassName = szAppName;              // Name to register as

    // Register the window class and return success/failure code.
    return (RegisterClass(&wc));
}


/*****************************************************************************
 *																			 *
 *   FUNCTION:  InitInstance(HINSTANCE, int)								 *
 *																			 *
 *   PURPOSE:  Saves instance handle and creates main window				 *
 *																			 *
 *   COMMENTS:																 *
 *																			 *
 *      This function is called at initialization time for every instance of *
 *      this application.  This function performs initialization tasks that	 *
 *      cannot be shared by multiple instances.								 *
 *																			 *
 *      In this case, we save the instance handle in a static variable and	 *
 *      create and display the main program window.							 *
 *																			 *
 ****************************************************************************/
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND            hWnd; // Main window handle.

    // Save the instance handle in static variable, which will be used in
    // many subsequence calls from this application to Windows.

    hInst = hInstance; // Store instance handle in our global variable

    // Create a main window for this application instance.

    hWnd = CreateWindow(
            szAppName,           // See RegisterClass() call.
            szTitle,             // Text for window title bar.
            WS_OVERLAPPEDWINDOW,// Window style.
            CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, // Use default positioning
            NULL,                // Overlapped windows have no parent.
            NULL,                // Use the window class menu.
            hInstance,           // This instance owns this window.
            NULL                 // We don't use any data in our WM_CREATE
    );

    // If window could not be created, return "failure"
    if (!hWnd) {
            return (FALSE);
    }

    // Make the window visible; update its client area; and return "success"
    ShowWindow(hWnd, nCmdShow); // Show the window
    UpdateWindow(hWnd);         // Sends WM_PAINT message

    return (TRUE);              // We succeeded...

}
									  

/*****************************************************************************
 *																			 *
 *   FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)							 *
 *																			 *
 *   PURPOSE:  Processes messages											 *
 *																			 *
 *   MESSAGES:																 *
 *																			 *
 *   WM_COMMAND    - application menu (About dialog box)					 *
 *   WM_DESTROY    - destroy window											 *
 *																			 *
 *   COMMENTS:																 *
 *																			 *
 *   To process the IDM_ABOUT message, call MakeProcInstance() to get the	 *
 *   current instance address of the About() function.  Then call Dialog	 *
 *   box which will create the box according to the information in your		 *
 *   TextFX.rc file and turn control over to the About() function.  When	 *
 *   it returns, free the intance address.									 *
 *																			 *
 ****************************************************************************/
LRESULT CALLBACK WndProc(
                HWND hWnd,         // window handle
                UINT message,      // type of message
                WPARAM uParam,     // additional information
                LPARAM lParam)     // additional information
{
	int wmId, wmEvent;
    static BOOL bOn = TRUE;  // Which guide line (top = TRUE) are we on?
    static LPPOINT lpTop = NULL;
	static LPPOINT lpBot = NULL;
    static DWORD dwTop = 0;
	static DWORD dwBot = 0;
	static BOOL bOutlineOnly = FALSE;
	static BOOL bShowGuides  = FALSE;
    static HPEN hpenBlue, hpenRed;
	
	SetLastError(0); // Set error flag to "no errors"

	switch (message) {	 
	    case WM_CREATE:  // Select an big Arial font into our DC 
		    {
			    HDC hDC = GetDC(hWnd);
                LOGFONT lf;
				HFONT hf;

			    memset(&lf, 0, sizeof(LOGFONT));
			    lf.lfHeight = -72;		// Big fonts scale better
		        strcpy((LPSTR)&(lf.lfFaceName), "arial");
	          
			    // Create and select the font
			    hf = CreateFontIndirect(&lf); 
			    SelectObject(hDC, hf);

				hpenBlue = CreatePen(PS_SOLID, 1, RGB(0,0,255));
				hpenRed  = CreatePen(PS_SOLID, 1, RGB(255,0,0));
			}
			
			GetLastErrorBox(hWnd, "Error in WM_CREATE");
			break;

		case WM_PAINT: 
            {
			   PAINTSTRUCT ps;
			   HDC hDC = BeginPaint(hWnd, &ps);
               RECT rect;
               			   
			   // Clear the client area 
               GetClientRect(hWnd, &rect);
       	       PatBlt(hDC, 0, 0, rect.right, rect.bottom, WHITENESS);
		           
   			   
   			   // If we have something to show...
   			   if (dwTop && dwBot) {

    			   // Show the top guide line if we have one and the user wants to
    			   if (dwTop && bShowGuides) {
                     SelectObject(hDC, hpenBlue);
                     ShowGuide(hDC, lpTop, dwTop);
                     SelectObject(hDC, GetStockObject(BLACK_PEN));
                   }
			   
    			   // If we have a bottom guide line
    			   if (dwBot) {                     
		       
    		       	   // ...then show it if the use wants to
            		   if (bShowGuides) {
            		     SelectObject(hDC, hpenRed);
                         ShowGuide(hDC, lpBot, dwBot);
            			 SelectObject(hDC, GetStockObject(BLACK_PEN));
                       }					     
		  
            		   // Do the mapping and show the text
            		   TextEffect(hDC, lpTop, lpBot, dwTop, dwBot, "This is a test", bOutlineOnly); 
                   }
               }

               EndPaint(hWnd, &ps);
			}
            break;

		case WM_LBUTTONDOWN: // Read a guide line from the user
            {
               HDC hDC = GetDC(hWnd);                   
               RECT rect;    
               
               if (bOn) {
                   GetClientRect(hWnd, &rect);
                   
                   // Clear the screen
                   PatBlt(hDC, 0, 0, rect.right, rect.bottom, WHITENESS);
                   
                   // Get rid of the previous guide lines
                   if (lpTop) 
                     GlobalFree(lpTop);
                   if (lpBot) 
                     GlobalFree(lpBot);
			       dwBot = 0;

				   SelectObject(hDC, hpenBlue);  // Top guide line is blue
                   GetGuideLine(hWnd, &lpTop, &dwTop);
               }
               else {
                   SelectObject(hDC, hpenRed);	// Bottom guide line is red
                   GetGuideLine(hWnd, &lpBot, &dwBot);
               }
               
               // Black as night, black as coal, I want to see the sun blotted out from the sky...
               SelectObject(hDC, GetStockObject(BLACK_PEN));
               bOn = !bOn;

			   if (bOn) {  

                  // Expand the line segment into points 
       		      FillOut(&lpTop, &dwTop);
                  FillOut(&lpBot, &dwBot);

                  InvalidateRect(hWnd, NULL, FALSE);  // Draw the text via WM_PAINT
               }
            }		  
			
			GetLastErrorBox(hWnd, "Error in WM_LBUTTONDOWN");
            break;
        
        case WM_COMMAND:
            wmId    = LOWORD(uParam);
            wmEvent = HIWORD(uParam);

            switch (wmId) {
				case IDM_QUICKTEST:  // Randomly generate guide lines
				    {
					  RECT rect;
					  int i;
					  
					  bOn = TRUE;  // Reset to top guide line

					  GetClientRect(hWnd, &rect);
					  if (dwTop)
					    GlobalFree(lpTop);
					  if (dwBot)
					    GlobalFree(lpBot);
					  
					  // Allocate top guide line
					  lpTop = (LPPOINT)GlobalAlloc(GPTR, sizeof(POINT) * QUICKTESTPOINTS);
					  if (!lpTop) break;
					  
					  // Allocate bottom guide line
					  lpBot = (LPPOINT)GlobalAlloc(GPTR, sizeof(POINT) * QUICKTESTPOINTS);
					  if (!lpBot) {
					    GlobalFree(lpTop);
						break;
					  }
					  
					  // Generate points
					  for (i=0; i<QUICKTESTPOINTS; i++) {
					    lpTop[i].x = random(rect.right);
                        lpTop[i].y = random(rect.bottom);
						lpBot[i].x = random(rect.right);
                        lpBot[i].y = random(rect.bottom);
					  }		 
					  
					  // Set number of points for top and bottom lines
					  dwTop = QUICKTESTPOINTS;
					  dwBot = QUICKTESTPOINTS;
					  
					  // Expand the line segment into points 
        		      FillOut(&lpTop, &dwTop);
                      FillOut(&lpBot, &dwBot);
		  
			          InvalidateRect(hWnd, NULL, FALSE);  // Draw the text via WM_PAINT
					}
			
					GetLastErrorBox(hWnd, "Error in IDM_QUICKTEST");  
					break;

	            case IDM_CHOOSEFONT: // Let the user pick a font
					{
					   HDC hDC = GetDC(hWnd);
                       HFONT hf;
					   LOGFONT lf;
					   CHOOSEFONT cf;
                           
				       ZeroMemory(&cf, sizeof(cf));  
					   ZeroMemory(&lf, sizeof(lf));  
														   
					   cf.lStructSize = sizeof(CHOOSEFONT);
					   cf.lpLogFont = &lf;
                       cf.Flags = CF_SCREENFONTS | CF_TTONLY;
					   
					   if (ChooseFont(&cf)) {
                           lf.lfHeight = -72;    // Bigger fonts look better
    					   hf = CreateFontIndirect(&lf); 
                       	   DeleteObject(SelectObject(hDC, hf));	 
					   }
			        }

			        // If we have text to show then re-render it
					if (dwTop && dwBot) 
					  InvalidateRect(hWnd, NULL, FALSE);  // Draw the text via WM_PAINT
					
					GetLastErrorBox(hWnd, "Error in IDM_CHOOSEFONT");
			        break;
                    
				case IDM_SHOWGUIDES:  // User toggled guide display
                    bShowGuides = !bShowGuides;
                    CheckMenuItem(GetMenu(hWnd), IDM_SHOWGUIDES, bShowGuides ? MF_CHECKED : MF_UNCHECKED);
					
					// If we have text to show then re-render it
					if (dwTop && dwBot) 
					  InvalidateRect(hWnd, NULL, FALSE);  // Draw the text via WM_PAINT
					
					GetLastErrorBox(hWnd, "Error in IDM_SHOWGUIDES");
                    break;
									  
				case IDM_OUTLINE:	  // User toggled display of text as outline
                    bOutlineOnly = !bOutlineOnly;
                    CheckMenuItem(GetMenu(hWnd), IDM_OUTLINE, bOutlineOnly ? MF_CHECKED : MF_UNCHECKED);
					
					// If we have text to show then re-render it
					if (dwTop && dwBot) 
					  InvalidateRect(hWnd, NULL, FALSE);  // Draw the text via WM_PAINT
					
					GetLastErrorBox(hWnd, "Error in IDM_OUTLINE");
                    break;

                case IDM_ABOUT:
                    DialogBox(hInst,          // current instance
                             "ABOUTBOX",      // dlg resource to use
                             hWnd,            // parent handle
                             (DLGPROC)About); // About() instance address

                    break;

                
                case IDM_EXIT:
                    DestroyWindow (hWnd);
                    break;

                default:
                    return (DefWindowProc(hWnd, message, uParam, lParam));
            }
            break;

        case WM_DESTROY:  // message: window being destroyed
                PostQuitMessage(0);
                break;
    
        default:          // Passes it on if unproccessed
                return (DefWindowProc(hWnd, message, uParam, lParam));
	}
	return (0);
}

/*****************************************************************************
 *																			 *
 *   FUNCTION: CenterWindow (HWND, HWND)									 *
 *																			 *
 *   PURPOSE:  Center one window over another								 *
 *																			 *
 *   COMMENTS:																 *
 *																			 *
 *   Dialog boxes take on the screen position that they were designed at,	 *
 *   which is not always appropriate. Centering the dialog over a particular *
 *   window usually results in a better position.							 *
 *																			 *
 ****************************************************************************/

BOOL CenterWindow (HWND hwndChild, HWND hwndParent)
{
        RECT    rChild, rParent;
        int     wChild, hChild, wParent, hParent;
        int     wScreen, hScreen, xNew, yNew;
        HDC     hdc;

        // Get the Height and Width of the child window
        GetWindowRect (hwndChild, &rChild);
        wChild = rChild.right - rChild.left;
        hChild = rChild.bottom - rChild.top;

        // Get the Height and Width of the parent window
        GetWindowRect (hwndParent, &rParent);
        wParent = rParent.right - rParent.left;
        hParent = rParent.bottom - rParent.top;

        // Get the display limits
        hdc = GetDC (hwndChild);
        wScreen = GetDeviceCaps (hdc, HORZRES);
        hScreen = GetDeviceCaps (hdc, VERTRES);
        ReleaseDC (hwndChild, hdc);

        // Calculate new X position, then adjust for screen
        xNew = rParent.left + ((wParent - wChild) /2);
        if (xNew < 0) {
                xNew = 0;
        } else if ((xNew+wChild) > wScreen) {
                xNew = wScreen - wChild;
        }

        // Calculate new Y position, then adjust for screen
        yNew = rParent.top  + ((hParent - hChild) /2);
        if (yNew < 0) {
                yNew = 0;
        } else if ((yNew+hChild) > hScreen) {
                yNew = hScreen - hChild;
        }

        // Set it, and return
        return SetWindowPos (hwndChild, NULL,
                xNew, yNew, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}


/*****************************************************************************
 *																			 *
 *   FUNCTION: About(HWND, UINT, WPARAM, LPARAM)							 *
 *																			 *
 *   PURPOSE:  Processes messages for "About" dialog box					 *
 *																			 *
 *   MESSAGES:																 *
 *																			 *
 *   WM_INITDIALOG - initialize dialog box									 *
 *   WM_COMMAND    - Input received											 *
 *																			 *
 *   COMMENTS:																 *
 *																			 *
 *   Display version information from the version section of the			 *
 *   application resource.													 *
 *																			 *
 *   Wait for user to click on "Ok" button, then close the dialog box.		 *
 *																			 *
 ****************************************************************************/

LRESULT CALLBACK About(
                HWND hDlg,           // window handle of the dialog box
                UINT message,        // type of message
                WPARAM uParam,       // message-specific information
                LPARAM lParam)
{
    switch (message) {
        case WM_INITDIALOG:  // message: initialize dialog box
            // Center the dialog over the application window
            CenterWindow (hDlg, GetWindow (hDlg, GW_OWNER));
            return (TRUE);

        case WM_COMMAND:                      // message: received a command
            if (LOWORD(uParam) == IDOK || LOWORD(uParam) == IDCANCEL) { 
                EndDialog(hDlg, TRUE);        // Exit the dialog
                return (TRUE);
            }
            break;
    }
    return (FALSE); // Didn't process the message

    UNREFERENCED_PARAMETER(lParam); // This will prevent 'unused formal parameter' warnings
}
