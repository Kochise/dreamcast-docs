/****************************************************************************
*
*    PROGRAM: scroll32.c
*
*    PURPOSE: Scroll bar exercise sample
*
****************************************************************************/

#include <windows.h>    // includes basic windows functionality
#include <stdio.h>      // includes standard file i/o functionality
#include <string.h>     // includes string functions
#include "scroll32.h" 

HINSTANCE hInst;
UINT uVertPos;
UINT uHorzPos;
UINT uVertMax;
UINT uHorzMax;
BOOL fVertSet;
BOOL fHorzSet;

/****************************************************************************
*
*    FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)
*
*    PURPOSE: calls initialization function, processes message loop
*
****************************************************************************/

int APIENTRY WinMain(
   HINSTANCE hInstance,
   HINSTANCE hPrevInstance,
   LPSTR lpCmdLine,
   int nCmdShow )
{

   MSG msg;   

   if (!InitApplication(hInstance))
	      return (FALSE);

   /* Perform initializations that apply to a specific instance */
   if (!InitInstance(hInstance, nCmdShow))
	   return (FALSE);

   /* Acquire and dispatch messages until a WM_QUIT message is received. */
   while (GetMessage(&msg, NULL, 0, 0))
	{
   	TranslateMessage(&msg);
	   DispatchMessage(&msg);
   }
   return (msg.wParam);           /* Returns the value from PostQuitMessage */
}


/****************************************************************************
*
*    FUNCTION: InitApplication(HANDLE)
*
*    PURPOSE: Initializes window data and registers window class
*
*    COMMENTS:
*
*        In this function, we initialize a window class by filling out a data
*        structure of type WNDCLASS and calling the Windows RegisterClass()
*        function.
*
****************************************************************************/

BOOL InitApplication(HANDLE hInstance)
{
   WNDCLASS  wc;

   /* Fill in window class structure with parameters that describe the       */
   /* main window.                                                           */
   wc.style = 0;                       /* Class style(s).                    */
   wc.lpfnWndProc = (WNDPROC)MainWndProc;
   wc.cbClsExtra = 0;                  /* No per-class extra data.           */
   wc.cbWndExtra = 0;                  /* No per-window extra data.          */
   wc.hInstance = hInstance;           /* Application that owns the class.   */
   wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(SCROLL32_ICON));
   wc.hCursor = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground = GetStockObject(WHITE_BRUSH); 
   wc.lpszMenuName =  "ScrollMenu";    /* Name of menu resource in .RC file. */
   wc.lpszClassName = "ScrollClass";   /* Name used in call to CreateWindow. */

   /* Register the window class and return success/failure code. */
   return (RegisterClass(&wc));
}

/****************************************************************************
*
*    FUNCTION:  InitInstance(HANDLE, int)
*
*    PURPOSE:  Saves instance handle and creates main window
*
****************************************************************************/

BOOL InitInstance(
   HANDLE          hInstance,          /* Current instance identifier.       */
   int             nCmdShow)           /* Param for first ShowWindow() call. */
{
   HWND            hWnd;               /* Main window handle.                */

   /* Save the instance handle */
   hInst = hInstance;

   /* Create a main window for this application instance.  */
   hWnd = CreateWindow(
	   "ScrollClass",       
   	"Scrollbar Exerciser",  /* Text for window title bar.         */
	   WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
	   CW_USEDEFAULT,          /* Default horizontal position.       */
   	CW_USEDEFAULT,          /* Default vertical position.         */
   	CW_USEDEFAULT,          /* Default width.                     */
   	CW_USEDEFAULT,          /* Default height.                    */
   	NULL,                   /* Overlapped windows have no parent. */
   	NULL,                   /* Use the window class menu.         */
   	hInstance,              /* This instance owns this window.    */
   	NULL );

   /* If window could not be created, return "failure" */
   if (!hWnd)
   	return (FALSE);

   /* Make the window visible; update its client area; and return "success" */
   ShowWindow(hWnd, nCmdShow); 
   UpdateWindow(hWnd);         
   return (TRUE);              
}

/****************************************************************************
*
*    FUNCTION: MainWndProc(HWND, unsigned, WORD, LONG)
*
*    PURPOSE:  Processes messages
*
*    COMMENTS:
*
*        This function processes all messags sent to the window.  When the
*        user choses one of the options from one of the menus, the command
*        is processed here and passed onto the function for that command.
*
****************************************************************************/

LONG APIENTRY MainWndProc(
   HWND hWnd,                /* window handle                   */
	UINT message,             /* type of message                 */
	UINT wParam,              /* additional information          */
	LONG lParam)              /* additional information          */
{                                  

   HDC hdc;
   PAINTSTRUCT ps;
   static HWND hWndHorzScroll, hWndVertScroll;
   static UINT uHorzPage, uVertPage, uHorzLine, uVertLine;
   WORD wScrollNotify;
   UINT uMess;
   static RECT RclHorz, RclVert;
   POINT Pt;

   switch (message)
   {

      case WM_CREATE:
      {
         RECT rcl;

         GetClientRect(hWnd, &rcl);
            
         // create a scrollbar to put in the window
         hWndHorzScroll = CreateWindow(
         	"Scrollbar", 
         	"",
         	WS_CHILD | WS_VISIBLE | SBS_HORZ | SBS_TOPALIGN,
         	SM_CXVSCROLL,0,rcl.right - SM_CXVSCROLL,0,
         	hWnd,         
         	(HMENU)10,         
            hInst, 
            NULL);

         SetScrollRange( hWndHorzScroll, SB_CTL, 0, MAX_RANGE, FALSE);
         GetClientRect( hWndHorzScroll, &RclHorz);

         hWndVertScroll = CreateWindow(
         	"Scrollbar", 
         	"",
         	WS_CHILD | WS_VISIBLE | SBS_VERT | SBS_LEFTALIGN,
         	0,0,0,rcl.bottom,
         	hWnd,         
         	(HMENU)20,         
            hInst, 
            NULL);

         SetScrollRange( hWndVertScroll, SB_CTL, 0, MAX_RANGE, FALSE);
         GetClientRect( hWndVertScroll, &RclVert);

         SetScrollPos(hWndHorzScroll, SB_CTL, 0, TRUE);
         SetScrollPos(hWndVertScroll, SB_CTL, 0, TRUE);

         uVertPos = uHorzPos = 0;
         uVertMax = uHorzMax = MAX_RANGE;
         fVertSet = fHorzSet = TRUE;
         uHorzPage = uHorzMax / 5;
         uVertPage = uVertMax / 5;
         uHorzLine = uHorzMax / 10;
         uVertLine = uVertMax / 10;
      }
      break;

      case WM_PAINT:
      {
         char buffer[128];
         RECT rcl;

         hdc = BeginPaint(hWnd, &ps);
         GetClientRect(hWnd, &rcl);

         sprintf(buffer, "Horizontal Thumb position = %d", uHorzPos);
         TextOut(hdc, rcl.left + 20, rcl.bottom - 90, buffer, strlen(buffer));
         sprintf(buffer, "Maximum Horizontal position = %d", uHorzMax);
         TextOut(hdc, rcl.left + 20, rcl.bottom - 70, buffer, strlen(buffer));
         
         sprintf(buffer, "Vertical Thumb position = %d", uVertPos);
         TextOut(hdc, rcl.left + 20, rcl.bottom - 50, buffer, strlen(buffer));
         sprintf(buffer, "Maximum Vertical position = %d", uVertMax);
         TextOut(hdc, rcl.left + 20, rcl.bottom - 30, buffer, strlen(buffer));

         EndPaint(hWnd, &ps);
      }                 
      break;

      case WM_HSCROLL: 
      {
         UINT xNewPos;    /* new position */

         switch (LOWORD(wParam)) 
         {
            /* User clicked the shaft left of the scroll box. */
            case SB_PAGEUP:
                xNewPos = uHorzPos - uHorzPage;
                break;

            /* User clicked the shaft right of the scroll box. */
            case SB_PAGEDOWN:
                xNewPos = uHorzPos + uHorzPage;
                break;

            /* User clicked the left arrow. */
            case SB_LINEUP:
                xNewPos = uHorzPos - uHorzLine;
                break;

            /* User clicked the right arrow. */
            case SB_LINEDOWN:
                xNewPos = uHorzPos + uHorzLine;
                break;

            case SB_TOP:
               xNewPos = uHorzMax;
               break;

            case SB_BOTTOM:
               xNewPos = 0;
               break;
                  
            /* User dragged the scroll box. */
            case SB_THUMBPOSITION:
            case SB_THUMBTRACK:
               /* if range is greater than 16 bits, then convert */
               if (uHorzMax > 65535) 
               {
                  double d1;

                  //get the current cursor position
                  GetCursorPos(&Pt);
                  // map it to the scroll window
                  ScreenToClient(hWndHorzScroll, &Pt);
                  // multiply by the maximum horizontal position
                  // and store in a double to keep from overflowing
                  d1 = (double)Pt.x * (double)uHorzMax;
                  // divide by the right side of the scroll window
                  xNewPos = (UINT)(d1 / (double)RclHorz.right);      
               }
               /* else just take the 16-bit value passed in HIWORD(wParam) */
               else
                  xNewPos = HIWORD(wParam);
               break;

            default:
               xNewPos = uHorzPos;
         }

         /* New position must be between 0 and the screen width. */
         xNewPos = max(0, xNewPos);
         xNewPos = min(uHorzMax, xNewPos);

         /* Reset the current scroll position. */
         uHorzPos = xNewPos;

         /* Reset the scroll bar. */
         if ((LOWORD(wParam) != SB_THUMBTRACK) && (LOWORD(wParam) != SB_THUMBPOSITION))
            SetScrollPos(hWndHorzScroll, SB_CTL, uHorzPos, TRUE);

         InvalidateRect(hWnd, NULL, TRUE);
      }
      break;

      case WM_VSCROLL: 
      {
         int yNewPos;    /* new position */

         switch (LOWORD(wParam)) 
         {
            /* User clicked the shaft above the scroll box. */
            case SB_PAGEUP:
                yNewPos = uVertPos - uVertPage;
                break;

            /* User clicked the shaft below the scroll box. */
            case SB_PAGEDOWN:
                yNewPos = uVertPos + uVertPage;
                break;

            /* User clicked the top arrow. */
            case SB_LINEUP:
                yNewPos = uVertPos - uVertLine;
                break;

            /* User clicked the bottom arrow. */
            case SB_LINEDOWN:
                yNewPos = uVertPos + uVertLine;
                break;

            case SB_TOP:
               yNewPos = uVertMax;
               break;

            case SB_BOTTOM:
               yNewPos = 0;
               break;

            /* User dragged the scroll box. */
            case SB_THUMBTRACK:
            case SB_THUMBPOSITION:
               /* if range is greater than 16 bits, then convert */
               if (uVertMax > 65535) 
               {
                  double d1;

                  //get the current cursor position
                  GetCursorPos(&Pt);
                  // map it to the scroll window
                  ScreenToClient(hWndVertScroll, &Pt);
                  // multiply by the maximum horizontal position
                  // and store in a double to keep from overflowing
                  d1 = (double)Pt.y * (double)uVertMax;
                  // divide by the right side of the scroll window
                  yNewPos = (UINT)(d1 / (double)RclVert.bottom);      
               }
               /* else just take the 16-bit value passed in HIWORD(wParam) */
               else
                  yNewPos = HIWORD(wParam);                  
               break;

            default:
               yNewPos = uVertPos;
         }
         /* New position must be between 0 and the max height. */
         yNewPos = max(0, yNewPos);
         yNewPos = min((int)uVertMax, yNewPos);

         /* If the current position does not change, do not scroll.*/
         if (yNewPos == (int)uVertPos)
            break;

         /* Reset the current scroll position. */
         uVertPos = yNewPos;

         /* Reset the scroll bar. */
         SetScrollPos(hWndVertScroll, SB_CTL, uVertPos, TRUE);

         InvalidateRect(hWnd, NULL, TRUE);

      }
      break;

      case WM_KEYDOWN:
         switch (wParam) 
         {
            case VK_UP:
               wScrollNotify = SB_LINEUP;
               uMess = WM_VSCROLL;
               break;

            case VK_PRIOR:    //PAGEUP key
               wScrollNotify = SB_PAGEUP;
               uMess = WM_VSCROLL;
               break;

            case VK_NEXT:     // PAGEDOWN key
               wScrollNotify = SB_PAGEDOWN;
               uMess = WM_VSCROLL;
               break;

            case VK_DOWN:
               wScrollNotify = SB_LINEDOWN;
               uMess = WM_VSCROLL;
               break;

            case VK_HOME:
               wScrollNotify = SB_BOTTOM;
               uMess = WM_HSCROLL;
               break;

            case VK_END:
               wScrollNotify = SB_TOP;
               uMess = WM_HSCROLL;
               break;

            case VK_RIGHT:
               wScrollNotify = SB_LINEDOWN;
               uMess = WM_HSCROLL;
               break;

            case VK_LEFT:
               wScrollNotify = SB_LINEUP;
               uMess = WM_HSCROLL;
               break;

            default:
               wScrollNotify = 0xFFFF;
               break;
         }
         if (wScrollNotify != -1)
            SendMessage(hWnd, uMess,
               MAKELONG(wScrollNotify, 0), 0L);

         break;

	   case WM_COMMAND: 
         switch( LOWORD( wParam ))
	      {

            case IDM_SETPOS:
               if (DialogBox(hInst, "SetPos", hWnd, (DLGPROC)SetPos) == TRUE)
               {
                  if (fHorzSet == TRUE)
                  {
                     SetScrollPos(hWndHorzScroll, SB_CTL, uHorzPos, TRUE);
                     fHorzSet = FALSE;
                  }
            
                  if (fVertSet == TRUE)
                  {
                     SetScrollPos(hWndVertScroll, SB_CTL, uVertPos, TRUE);
                     fVertSet = FALSE;
                  }
                               
                  InvalidateRect(hWnd, NULL, TRUE);
               }
               break;

            case IDM_SETRANGE:
               if (DialogBox(hInst, "SetRange", hWnd, (DLGPROC)SetRange) == TRUE)
               {
                  if (fHorzSet == TRUE)
                  {
                     SetScrollRange( hWndHorzScroll, SB_CTL, 0, uHorzMax, TRUE);
                     if (uHorzPos > uHorzMax)
                        uHorzPos = uHorzMax;
                     uHorzPage = uHorzMax / 5;
                     uHorzLine = uHorzMax / 10;
                     fHorzSet = FALSE;
                  }   

                  if (fVertSet == TRUE)
                  {
                     SetScrollRange( hWndVertScroll, SB_CTL, 0, uVertMax, TRUE);
                     if (uVertPos > uVertMax)
                        uVertPos = uVertMax;
                     uVertPage = uVertMax / 5;
                     uVertLine = uVertMax / 10;
                     fVertSet = TRUE;
                  }

                  InvalidateRect(hWnd, NULL, TRUE);

               }
               break;

		      case IDM_ABOUT: 
		         DialogBox(hInst, "AboutBox", hWnd, (DLGPROC)About);
		         break;

		      case IDM_EXIT:
		         PostQuitMessage(0);
		         break;

		      default:
		         return (DefWindowProc(hWnd, message, wParam, lParam));

	      }
	      break;

	   case WM_DESTROY:                  /* message: window being destroyed */
	      PostQuitMessage(0);
	      break;

   	default:
	      return (DefWindowProc(hWnd, message, wParam, lParam));
   }
   return (0);
}


/****************************************************************************
*
*    FUNCTION: SetPos(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages to set the scroll bar position.
*
****************************************************************************/

BOOL APIENTRY SetPos(
   HWND hDlg,              
	UINT message,           
	UINT wParam,            
	LONG lParam)
{
   UINT uRet;
   BOOL lpTranslated;
   char buffer[128];

   switch (message)
   {
	   case WM_INITDIALOG:
         SetDlgItemInt(hDlg, IDE_HORZPOS, uHorzPos, FALSE);
         SetDlgItemInt(hDlg, IDE_VERTPOS, uVertPos, FALSE);
	      return (TRUE);

   	case WM_COMMAND:      
	      if (LOWORD(wParam) == IDOK)
         {
            // see if horizontal was checked
            if (IsDlgButtonChecked(hDlg, IDC_HORIZONTAL) == 1)
            {
               // get position entered
               uRet = GetDlgItemInt(hDlg, IDE_HORZPOS, &lpTranslated, FALSE);
               if (((uRet >= 0) && (uRet <= uHorzMax)) && ((INT)lpTranslated != 0))
               {
                  uHorzPos = uRet;
                  fHorzSet = TRUE;
               }
               else
               {
                  sprintf(buffer, "Value must be between 0 and %x", uHorzMax);
                  if (MessageBox(hDlg, buffer, "Out of Range!", MB_OKCANCEL ) == IDOK)
                     break;
                  else  
                  {
                     EndDialog(hDlg, FALSE);
                     return(FALSE);
                  }
               }
            }
            // see if vertical was checked
            if (IsDlgButtonChecked(hDlg, IDC_VERTICAL) == 1)
            {
               // get position entered
               uRet = GetDlgItemInt(hDlg, IDE_VERTPOS, &lpTranslated, FALSE);
               if (((uRet >= 0) && (uRet <= uVertMax)) && ((INT)lpTranslated != 0))
               {
                  uVertPos = uRet;
                  fVertSet = TRUE;
               }
               else
               {
                  sprintf(buffer, "Value must be between 0 and %x", uVertMax);
                  if (MessageBox(hDlg, buffer, "Out of Range!", MB_OKCANCEL ) == IDOK)
                     break;
                  else  
                  {
                     EndDialog(hDlg, FALSE);
                     return(FALSE);
                  }
               }
            }

		      EndDialog(hDlg, TRUE);
      		return (TRUE);
	      }
         else if (LOWORD(wParam) == IDCANCEL)
         {
            EndDialog(hDlg, FALSE);
            return (FALSE);
         }
	      break;
    }
    return (FALSE);
}

/****************************************************************************
*
*    FUNCTION: SetRange(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages to set the scroll bar range.
*
****************************************************************************/

BOOL APIENTRY SetRange(
   HWND hDlg,              
	UINT message,           
	UINT wParam,            
	LONG lParam)
{
   UINT uRet;
   BOOL lpTranslated;

   switch (message)
   {
	   case WM_INITDIALOG:
         SetDlgItemInt(hDlg, IDE_HORZPOS, uHorzMax, FALSE);
         SetDlgItemInt(hDlg, IDE_VERTPOS, uVertMax, FALSE);
	      return (TRUE);


   	case WM_COMMAND:      
	      if (LOWORD(wParam) == IDOK)
         {
            // see if horizontal was checked
            if (IsDlgButtonChecked(hDlg, IDC_HORIZONTAL) == 1)
            {
               // get maximum position entered
               uRet = GetDlgItemInt(hDlg, IDE_HORZPOS, &lpTranslated, FALSE);
               if (((uRet > 0) && (uRet <= MAX_RANGE)) && ((INT)lpTranslated != 0))
               {
                  uHorzMax = uRet;
                  fHorzSet = TRUE;
               }
               else
               {
                  if (MessageBox(hDlg, "Value must be between 0 and 0x7fffffff", "Out of Range!", MB_OKCANCEL ) == IDOK)
                     break;
                  else  
                  {
                     EndDialog(hDlg, FALSE);
                     return(FALSE);
                  }
               }
            }
            // see if vertical was checked
            if (IsDlgButtonChecked(hDlg, IDC_VERTICAL) == 1)
            {
               // get maximum position entered
               uRet = GetDlgItemInt(hDlg, IDE_VERTPOS, &lpTranslated, FALSE);
               if (((uRet > 0) && (uRet <= MAX_RANGE)) && ((INT)lpTranslated != 0))
               {
                  uVertMax = uRet;
                  fVertSet = TRUE;
               }
               else
               {
                  if (MessageBox(hDlg, "Value must be between 0 and 0x7fffffff", "Out of Range!", MB_OKCANCEL ) == IDOK)
                     break;
                  else  
                  {
                     EndDialog(hDlg, FALSE);
                     return(FALSE);
                  }
               }
            }

		      EndDialog(hDlg, TRUE);
      		return (TRUE);
	      }
         else if (LOWORD(wParam) == IDCANCEL)
         {
            EndDialog(hDlg, FALSE);
            return (FALSE);
         }
	      break;
    }
    return (FALSE);
}

/****************************************************************************
*
*    FUNCTION: About(HWND, UINT, UINT, LONG)
*
*    PURPOSE:  Processes messages for "About" dialog box
*
****************************************************************************/

BOOL APIENTRY About(
   HWND hDlg,              
	UINT message,           
	UINT wParam,            
	LONG lParam)
{
   switch (message)
   {
	   case WM_INITDIALOG:
	      return (TRUE);

   	case WM_COMMAND:      
	      if (LOWORD(wParam) == IDOK)
         {
		      EndDialog(hDlg, TRUE);
      		return (TRUE);
	      }
	      break;
    }
    return (FALSE);
}

