/****************************************************************************

        PROGRAM: w32pen.c

        PURPOSE: 
        
        FUNCTIONS:

        WinMain() - calls initialization function, processes message loop
        InitApplication() - initializes window data and registers window
        InitInstance() - saves instance handle and creates main window
        WndProc() - processes messages
        CenterWindow() - used to center the "About" box over application window
        About() - processes messages for "About" dialog box

        COMMENTS:

****************************************************************************/
#define MAIN

#include <windows.h>
#include <commdlg.h>
#include <colordlg.h>
#include <stdlib.h>
#include <time.h>
#include "resource.h"
#include "w32pen.h"

#define BTN_WIDTH (8 * dwXChar)
#define BTN_HEIGHT (2 * dwYChar)
#define BTN_XSPACER (4 * dwXChar)
   
HFONT CreateLogFont(HDC hdc, LPSTR szFace, int PointSize);

char szFile[MAXFILTERLEN];
char szFileTitle[MAXFILTERLEN];

/****************************************************************************

        FUNCTION: WinMain(HINSTANCE, HINSTANCE, LPSTR, int)

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
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{

        MSG msg;
        HANDLE hAccelTable;

        if (!hPrevInstance) 
        {       // Other instances of app running?
                        if (!InitApplication(hInstance)) 
                          return (FALSE);     // Exits if unable to initialize
        }

        /* Perform initializations that apply to a specific instance */

        if (!InitInstance(hInstance, nCmdShow)) 
                return (FALSE);

        hAccelTable = LoadAccelerators (hInstance, szAppName);

        while (GetMessage(&msg, 
           NULL,   
           0,   
           0))     
        {
                if (!TranslateAccelerator (msg.hwnd, hAccelTable, &msg)) 
                {
                        TranslateMessage(&msg);// Translates virtual key codes
                        DispatchMessage(&msg); // Dispatches message to window
                }
        }


        return (msg.wParam); // Returns the value from PostQuitMessage

        lpCmdLine; // This will prevent 'unused formal parameter' warnings
}


/****************************************************************************

        FUNCTION: InitApplication(HINSTANCE)

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

BOOL InitApplication(HINSTANCE hInstance)
{
        WNDCLASS  wc;
		BOOL      bRet = TRUE;

        // Fill in window class structure with parameters that describe the
        // main window.

        wc.style         = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc   = (WNDPROC)WndProc;       
        wc.cbClsExtra    = 0;                      
        wc.cbWndExtra    = 0;                      
        wc.hInstance     = hInstance;              
        wc.hIcon         = LoadIcon (hInstance, szAppName); 
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = GetStockObject(GRAY_BRUSH);
        wc.lpszMenuName  = szAppName;              
        wc.lpszClassName = szAppName;              

		if (!RegisterClass(&wc))
		  bRet = FALSE;
		  		
		return (bRet);
}

/****************************************************************************

        FUNCTION:  InitInstance(HINSTANCE, int)

        PURPOSE:  Saves instance handle and creates main window

        COMMENTS:

                This function is called at initialization time for every instance of
                this application.  This function performs initialization tasks that
                cannot be shared by multiple instances.

                In this case, we save the instance handle in a static variable and
                create and display the main program window.

****************************************************************************/

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
        HWND hWnd;

        // Save the instance handle in static variable, which will be used in
        // many subsequence calls from this application to Windows.

        hInst = hInstance; // Store instance handle in our global variable

        // Create a main window for this application instance.

        hWnd = CreateWindow(
                szAppName,           
                szTitle,             
                WS_OVERLAPPEDWINDOW,0,0,
                CW_USEDEFAULT, CW_USEDEFAULT, 
                NULL,                
                NULL,                
                hInstance,           
                NULL                 
        );

        // If window could not be created, return "failure"
        if (!hWnd) 
          return (FALSE);

		hwndMain = hWnd;
        ShowWindow(hwndMain, nCmdShow);
        UpdateWindow(hwndMain);

        return (TRUE);              

}

/****************************************************************************

        FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)

        PURPOSE:  Processes messages

        MESSAGES:

        WM_COMMAND    - application menu (About dialog box)
        WM_DESTROY    - destroy window

        COMMENTS:

        To process the IDM_ABOUT message, call MakeProcInstance() to get the
        current instance address of the About() function.  Then call Dialog
        box which will create the box according to the information in your
        w32pen.rc file and turn control over to the About() function.  When
        it returns, free the intance address.

****************************************************************************/

LRESULT CALLBACK WndProc(HWND hWnd,UINT message, WPARAM uParam,LPARAM lParam)
{
	static HWND hwndFirst,
				hwndLast,
				hwndPrev,
				hwndNext;
	static LONG	dwXChar,
				dwYChar;
  	PAINTSTRUCT ps;
  	WORD 		xPos, 
  				yPos, 
  				mmxPos, 
  				mmyPos;
  	DWORD 		dwCommDlgError;
  	RECT 		rc;
  	int 		i,
  				iXCenter;
  	PPENRECORD 	pTempPRNode;
  	HDC 		hDC;
	TEXTMETRIC	tmWindow;

  switch (message) 
  {
    case WM_CREATE:
		//
		// button height and width attributes
		//
		hDC = GetDC(hwndMain);
		GetTextMetrics(hDC, &tmWindow);
		ReleaseDC(hwndMain, hDC);

		dwXChar = tmWindow.tmAveCharWidth;
		dwYChar = tmWindow.tmHeight;

      	hCur = LoadCursor(hInst, MAKEINTRESOURCE(IDC_PENCUR));
	  	hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	  	hPatBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP4));
	  	
		//Create buttons
	  	hwndFirst = CreateWindow("button", "First", WS_CHILD | 
	  	        WS_VISIBLE | BS_PUSHBUTTON,0,0, BTN_WIDTH,
	  			BTN_HEIGHT, hWnd, (HMENU)IDC_FIRST,hInst, NULL);
	  	hwndLast = CreateWindow("button", "Last", WS_CHILD | 
	  			WS_VISIBLE | BS_PUSHBUTTON, 0, 0, BTN_WIDTH,
	  			BTN_HEIGHT, hWnd, (HMENU)IDC_LAST, hInst, NULL);
	  	hwndPrev = CreateWindow("button", "Prev", WS_CHILD | 
	  			WS_VISIBLE | BS_PUSHBUTTON, 0, 0, BTN_WIDTH,
	  			BTN_HEIGHT, hWnd, (HMENU)IDC_PREV, hInst,  NULL);
	  	hwndNext = CreateWindow("button", "Next", WS_CHILD | 
	  			WS_VISIBLE | BS_PUSHBUTTON, 0, 0, BTN_WIDTH,
	  			BTN_HEIGHT, hWnd, (HMENU)IDC_NEXT, hInst, NULL);
	  	break;

    case WM_PAINT:
	  	BeginPaint(hWnd, &ps);
	  	DrawWorkSpace(hWnd, ps.hdc);
	  	if (pPenList)
	  	{
	    	//
			// Traverse the list and draw all of the pen lines in the
			// list up to the pPenCurrent node.  Once we reach the end
			// of the pen list, we must be sure to draw the last pen 
			// line...hence, the second DrawRndLine() call below.
			//
	    	for (pTempPRNode = pPenList; pTempPRNode != pPenCurrent; 
	    							pTempPRNode = pTempPRNode->next)
          		DrawRndLine(ps.hdc, pTempPRNode);
            
            // draw the pPenCurrent node
			DrawRndLine(ps.hdc, pTempPRNode);
			DrawJoinCap(ps.hdc, pTempPRNode);
	  	}

	  	EndPaint(hWnd, &ps);
	  	break;
	
	case WM_MOUSEMOVE:
		mmxPos = LOWORD(lParam);  
      	mmyPos = HIWORD(lParam);
      	if (mmxPos >= grWorkRect.left && mmxPos <= grWorkRect.right &&
          	mmyPos >= grWorkRect.top  && mmyPos <= grWorkRect.bottom)
	    	
	    	bInHitArea = TRUE;
      	else
	    	bInHitArea = FALSE;
	  	break;

	case WM_SETCURSOR:
	  	if (bInHitArea)
	  	{
	    	SetCursor(hCur);
			return (TRUE);
	  	}
      	else 
      		return (DefWindowProc(hWnd, message, uParam, lParam));
	  	break;

	case WM_LBUTTONUP:
      	xPos = LOWORD(lParam);  
      	yPos = HIWORD(lParam);  
      	if (xPos >= grWorkRect.left && xPos <= grWorkRect.right &&
          	yPos >= grWorkRect.top  && yPos <= grWorkRect.bottom)
	  	{
        	cc.lStructSize = sizeof(CHOOSECOLOR);
        	cc.hwndOwner = hWnd;
        	cc.hInstance = (HWND)hInst;
        	cc.rgbResult = clr;
        	cc.lpCustColors = aclrCust;

        	cc.Flags =  CC_ENABLEHOOK | CC_ENABLETEMPLATE;
        	cc.lpfnHook = (LPCCHOOKPROC)SetPenAttr;
        	cc.lpTemplateName = "PENATTR";

        	if (ChooseColor(&cc))
			{
		  		// this section has been changed from the denniscr original
		  		// by a-jasons (10-14-93)
		  
		  		//
		  		// allocate a new node...but check to see if the list exists yet
		  		//
	      		if (pPenList) {
		    		pTempPRNode = (PPENRECORD)HeapAlloc(hPenHeap, 
		    				HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 
		    				sizeof(PENRECORD));
		    		//
		    		// insert the new node at the end of the list
		    		//
		    		pPenList->prev->next = pTempPRNode;
		    		pTempPRNode->prev = pPenList->prev;
		    		pTempPRNode->next = pPenList;
		    		pPenList->prev = pTempPRNode;
		  		}
		  		else {
		    		//
		    		// neither the heap or the list exist, so create both
		    		//
		    		hPenHeap = HeapCreate(0, 0, 0);
		    		pPenList = (PPENRECORD)HeapAlloc(hPenHeap, 
		    				HEAP_NO_SERIALIZE | HEAP_ZERO_MEMORY, 
		    				sizeof(PENRECORD)); 
				
					pTempPRNode = pPenList;
					pPenList->next = pPenList;
					pPenList->prev = pPenList;
		  		}
          
          		// update the pPenCurrent pointer
          		pPenCurrent = pTempPRNode;
		  		//
		  		//make assignments to new node
		  		//
		  		pTempPRNode->dwPenType = PenRecord.dwPenType;
  		  		pTempPRNode->dwPenStyle = PenRecord.dwPenStyle;
		  		pTempPRNode->dwJoinStyle = PenRecord.dwJoinStyle;
		  		pTempPRNode->dwEndCapStyle = PenRecord.dwEndCapStyle;
		  		pTempPRNode->dwWidth = PenRecord.dwWidth;
		  		pTempPRNode->lb.lbStyle = PenRecord.lb.lbStyle;
          		memcpy(&pTempPRNode->xf, &PenRecord.xf, sizeof(XFORM));
		  		PenRecord.nPickPriority = uiNumPenRecs;
		  		pTempPRNode->lb.lbColor = cc.rgbResult;
		  		if (PenRecord.lb.lbStyle == BS_HATCHED)
		  	  		pTempPRNode->lb.lbHatch = HS_CROSS;
		  		else
		    		pTempPRNode->lb.lbHatch = 0;

		  		if (PenRecord.lb.lbStyle == BS_PATTERN)
		    		pTempPRNode->lb.lbHatch = (LONG)hPatBitmap;

          		GetClientRect(hWnd, &rc);
   	      		//
	      		//seed the random number generator and draw the lines
	      		//
          		srand((unsigned)time(NULL));
		  
          		for (i = 0; i < 10; i++)
	      		{
	        		pTempPRNode->PtsToDraw[i].x = rand() % rc.right;
	         		pTempPRNode->PtsToDraw[i].y = rand() % rc.bottom;
	      		}
                
                //
                // Invalidate the client region of the main window
                // so that it includes the new pen.
                //
				UnionRect(&rc, &grJoinCapRect, &grWorkRect);
	    		InvalidateRect(hwndMain, &rc, TRUE);
 		  		
 		  		//
		  		//remove the grayed Save As and Clear menu item if necessary
		  		//
		  		if ( MF_GRAYED == GetMenuState(GetSubMenu(GetMenu(hWnd), 0), 
		  											IDM_SAVEAS, MF_BYCOMMAND) )
		    	
		    		EnableMenuItem(GetSubMenu(GetMenu(hWnd), 0), IDM_SAVEAS, MF_ENABLED);
		  		if ( MF_GRAYED == GetMenuState(GetSubMenu(GetMenu(hWnd), 0), 
		  											IDM_CLEAR, MF_BYCOMMAND) )
		    	
		    		EnableMenuItem(GetSubMenu(GetMenu(hWnd), 0), IDM_CLEAR, MF_ENABLED);
			}
	    	else
	      		dwCommDlgError = CommDlgExtendedError();
        }
	 	break;
    
    case WM_SIZE:
    	if (GetClientRect(hWnd, &rc)) {
    		grButtonRect.right  = rc.right - BTN_XSPACER;
    		grButtonRect.left   = grButtonRect.right - BTN_WIDTH;
    		grButtonRect.top    = rc.top + HIWORD(lParam)/8;
    		grButtonRect.bottom = rc.bottom - HIWORD(lParam)/8;
    		
    		iXCenter = (grButtonRect.left - rc.left)/2;
    		
    		//
    		// Create work area rect
    		//
    		grWorkRect.left   = iXCenter - iXCenter / 2;
    		grWorkRect.right  = grButtonRect.left - BTN_XSPACER;
    		grWorkRect.top    = grButtonRect.top;
    		grWorkRect.bottom = grButtonRect.bottom;
    		
    		iXCenter = (grWorkRect.left - rc.left) / 2;
    		
    		//
    		// Create join and endcap rect
    		//
			grJoinCapRect.left   = iXCenter - iXCenter / 2;
			grJoinCapRect.right  = iXCenter + iXCenter / 2;
			grJoinCapRect.top    = grButtonRect.top;
			grJoinCapRect.bottom = grButtonRect.bottom;

			//
			// Reposition the buttons in their rectangle area
			//
			grButtonRect.bottom = grButtonRect.bottom - BTN_HEIGHT;

			MoveWindow(hwndFirst, grButtonRect.left, grButtonRect.top,
						BTN_WIDTH, BTN_HEIGHT, TRUE);
			MoveWindow(hwndPrev, grButtonRect.left,
						(grButtonRect.top * 2 + grButtonRect.bottom) / 3,
						BTN_WIDTH, BTN_HEIGHT, TRUE);
			MoveWindow(hwndNext, grButtonRect.left,
						(grButtonRect.top + 2 * grButtonRect.bottom) / 3,
						BTN_WIDTH, BTN_HEIGHT, TRUE);
			MoveWindow(hwndLast, grButtonRect.left, grButtonRect.bottom,
						BTN_WIDTH, BTN_HEIGHT, TRUE);

		}
		break;
		
    case WM_COMMAND:
    	if (HIWORD(uParam) == BN_CLICKED && lParam && pPenList) {
    		switch (LOWORD(uParam)) {
    			case IDC_FIRST: // Go to start of list
    				pPenCurrent = pPenList;
    				break;
    			case IDC_LAST: // Go to end of list
    				pPenCurrent = pPenList->prev;
    				break;
    			case IDC_PREV: // Go to next node
    				pPenCurrent = pPenCurrent->prev;
    				break;
    			case IDC_NEXT: // Go to next node
    				pPenCurrent = pPenCurrent->next;
    				break;
    		}
    		
    		//
    		// Invalidate the work area so that it gets redrawn.
    		//
			UnionRect(&rc, &grJoinCapRect, &grWorkRect);
    		InvalidateRect(hwndMain, &rc, TRUE);
    		
    	} 
      	else {
      		switch (LOWORD(uParam)) {
	     		case IDM_CLEAR:
	       			if (pPenList)
		     			HeapDestroy(hPenHeap);
		   			pPenList = NULL;
		   			ClearWorkAreas(hWnd, &grWorkRect, &grJoinCapRect);
		   			break;

	     		case IDM_SAVEAS:
   	       			if (pPenList)
	       			{
			 			RECT rcBound;
		     			HDC hmetadc;
		     			HDC hdcRef = GetDC(hWnd);
             			int iWidthMM = GetDeviceCaps(hdcRef, HORZSIZE);
             			int iHeightMM = GetDeviceCaps(hdcRef, VERTSIZE);
             			int iWidthPels = GetDeviceCaps(hdcRef, HORZRES);
             			int iHeightPels = GetDeviceCaps(hdcRef, VERTRES);
             			int iMMPerPelX = (iWidthMM * 100)/iWidthPels;
             			int iMMPerPelY = (iHeightMM * 100)/iHeightPels;

		     			if (SaveAs(hWnd))
			 			{
			 		  		memcpy(&rcBound, &grWorkRect, sizeof(RECT));
	           				InflateRect(&rcBound, -4, -4);
	           				rcBound.right --;
	           				rcBound.bottom--;
			   				//
               				//Convert client coordinates to .01-mm units. 
			   				//
               				rcBound.left = rcBound.left * iMMPerPelX;
               				rcBound.top = rcBound.top * iMMPerPelY;
               				rcBound.right = rcBound.right * iMMPerPelX;
               				rcBound.bottom = rcBound.bottom * iMMPerPelY;

			   				hmetadc = CreateEnhMetaFile(hdcRef, szFile, 
			   										&rcBound, NULL);
		       
			   				//
			   				// Traverse the Pen List, drawing each line as 
			   				// we go.  Note that the for loop will only plot 
			   				// n-1 lines (n being the number of pens).  Thus, 
			   				// we need to include a mechanism to plot the 
			   				// last line in the list (i.e. simply 
			   				// DrawRndLine() again after the loop).
			   				//
	           				for (pTempPRNode = pPenList; 
	           								pTempPRNode->next != pPenList; 
	           								pTempPRNode = pTempPRNode->next)
                 				DrawRndLine(hmetadc, pTempPRNode);
			   
			   				DrawRndLine(hmetadc, pTempPRNode);
			   				DrawJoinCap(hmetadc, pTempPRNode);

			   				DeleteEnhMetaFile(CloseEnhMetaFile(hmetadc));
			 			}
			 			if (hdcRef)
			   				ReleaseDC(hWnd, hdcRef);
	       			}
		   			break;

         		case IDM_EXIT:
           			DestroyWindow (hWnd);
           			break;

         		case IDM_ABOUT:
           			DialogBox(hInst, "AboutBox", hWnd, (DLGPROC)About); 
           			break;

         		default:
           			return (DefWindowProc(hWnd, message, uParam, lParam));
      		}
      	}
    	break;

    case WM_DESTROY:  // message: window being destroyed
	  DeleteObject(hBitmap);
	  DeleteObject(hPatBitmap);

	  if (pPenList)
		HeapDestroy(hPenHeap);

      PostQuitMessage(0);
      break;

    default:          // Passes it on if unproccessed
      return (DefWindowProc(hWnd, message, uParam, lParam));
  }
  return (0);
}

/******************************************************************

  FUNCTION : DrawWorkSpace

  PURPOSE  : draw the rectangles that define the drawing area in 
             the client area
   
  COMMENTS : 

  HISTORY  : created - denniscr - 8/9/93

*******************************************************************/

BOOL DrawWorkSpace(HWND hwnd, HDC hdc)
{
  RECT rc;
  RECT rcTitles;
  HPEN hOldPen, hPen;
  HFONT hFont, hOldFont;
  BOOL bRet = TRUE;
  TEXTMETRIC tm;

  if (GetClientRect(hwnd, &rc))
  {

    DWORD dwPenStyle = PS_GEOMETRIC | PS_INSIDEFRAME | PS_ENDCAP_SQUARE | PS_JOIN_BEVEL;	
    DWORD dwWidth = 8;	
    LOGBRUSH lb;	
    DWORD dwStyleCount = 0;	

    lb.lbStyle = BS_PATTERN;
	lb.lbColor = 0;
	lb.lbHatch = (LONG)hBitmap;

	hPen = ExtCreatePen(dwPenStyle, dwWidth, &lb, dwStyleCount, NULL);

	if (hPen)
	  hOldPen = SelectObject(hdc, hPen);

    Rectangle(hdc, grWorkRect.left, grWorkRect.top, grWorkRect.right, grWorkRect.bottom);

	//
	//smaller rectangle on left for showing join and endcap
	//
	Rectangle(hdc, grJoinCapRect.left, grJoinCapRect.top, grJoinCapRect.right, grJoinCapRect.bottom);

	//
	//draw the titles above and below the left rectangle
	//
	hFont = CreateLogFont(hdc, "ARIAL", 8);
	hOldFont = SelectObject(hdc, hFont);
	GetTextMetrics(hdc, &tm);

	SetBkMode(hdc, TRANSPARENT);
	rcTitles.left = grJoinCapRect.left;
	rcTitles.top = grJoinCapRect.top - 2 * tm.tmHeight;
	rcTitles.right = grJoinCapRect.right;
	rcTitles.bottom = rcTitles.top;
	rcTitles.bottom = rcTitles.top = (rcTitles.top < 0) ? 0 : rcTitles.top;

	DrawText(hdc, (LPSTR)"End Cap", 7, &rcTitles, DT_SINGLELINE | DT_NOCLIP | DT_CENTER);

	rcTitles.top = grJoinCapRect.bottom + tm.tmHeight;
	rcTitles.bottom = rcTitles.top;
	rcTitles.bottom = rcTitles.top = (rcTitles.top > rc.bottom - tm.tmHeight) ? 
	                                  rc.bottom - tm.tmHeight : rcTitles.top;

	DrawText(hdc, (LPSTR)"Join", 4, &rcTitles, DT_SINGLELINE | DT_NOCLIP | DT_CENTER);

	DeleteObject(SelectObject(hdc, hOldFont));

    if (hOldPen)
	  DeleteObject(SelectObject(hdc, hOldPen));
  }
  else
    bRet = FALSE;

  return (bRet);               
  
}


/****************************************************************************

        FUNCTION: CenterWindow (HWND, HWND)

        PURPOSE:  Center one window over another

        COMMENTS:

        Dialog boxes take on the screen position that they were designed at,
        which is not always appropriate. Centering the dialog over a particular
        window usually results in a better position.

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

/****************************************************************************
*
*    FUNCTION: SaveAs(HWND)
*
*    PURPOSE:  Invokes the common dialog function to save the current
*              buffer to a file.
*    COMMENTS:
*
*        This function initializes the OPENFILENAME structure for any
*        mode selected by the user: standard, using a hook or using a
*        customized template.  It then calls the GetSaveFileName()
*        common dialog function.
*
*    RETURN VALUES:
*        TRUE - The file was saved successfully.
*        FALSE - The buffer was not saved to a file.
*
****************************************************************************/
BOOL SaveAs(HWND hWnd)
{
  
   strcpy( szFile, "");
   strcpy( szFileTitle, "");

   OpenFileName.lStructSize       = sizeof(OPENFILENAME);
   OpenFileName.hwndOwner         = hWnd;
   OpenFileName.hInstance         = (HANDLE) hInst;
   OpenFileName.lpstrFilter       = "Enhanced MetaFile(*.EMF)\0*.EMF\0\0";
   OpenFileName.lpstrCustomFilter = (LPSTR) NULL;
   OpenFileName.nMaxCustFilter    = 0L;
   OpenFileName.nFilterIndex      = 1L;
   OpenFileName.lpstrFile         = szFile;
   OpenFileName.nMaxFile          = sizeof(szFile);
   OpenFileName.lpstrFileTitle    = szFileTitle;
   OpenFileName.nMaxFileTitle     = sizeof(szFileTitle);
   OpenFileName.lpstrInitialDir   = NULL;
   OpenFileName.lpstrTitle        = "Save File As";
   OpenFileName.nFileOffset       = 0;
   OpenFileName.nFileExtension    = 0;
   OpenFileName.lpstrDefExt       = "emf";
   OpenFileName.lCustData         = 0;

   OpenFileName.Flags = OFN_OVERWRITEPROMPT;
   OpenFileName.lpfnHook = (LPOFNHOOKPROC)(FARPROC)NULL;
   OpenFileName.lpTemplateName = (LPSTR)NULL;
   
   if ( GetSaveFileName( &OpenFileName ))
        return(TRUE);
   else
        return FALSE;
}

/***********************************************************************

  FUNCTION   : CreateLogFont

  PARAMETERS : HDC hdc
               LPSTR szFace
			   int PointSize

  PURPOSE    : Obtain a handle to a bold font created using the 
               face name and point size

  CALLS      : GetDeviceCaps
               memset
			   lstrcpy
			   CreateFontIndirect
			   MulDiv

  MESSAGES   : none

  RETURNS    : void

  COMMENTS   :

  HISTORY    : 9/20/93 - created - denniscr

************************************************************************/

HFONT CreateLogFont(HDC hdc, LPSTR szFace, int PointSize)
{
	LOGFONT lf;

	memset(&lf, 0, sizeof(LOGFONT));

	lf.lfWeight = FW_BOLD;
    lf.lfHeight = -MulDiv(PointSize,
        GetDeviceCaps(hdc, LOGPIXELSY), 72);

    lstrcpy((LPSTR)lf.lfFaceName, szFace);

    return (CreateFontIndirect(&lf));
}

#undef MAIN
