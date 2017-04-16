/****************************************************************************
*
*
*    PROGRAM: Sizebox.c
*
*    PURPOSE: Sizebox for testing
*
****************************************************************************/

#include <windows.h>    // includes basic windows functionality
#include <string.h>
#include "sizebox.h"

HINSTANCE hInst;

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
    int nCmdShow
    )
{

   MSG msg;                       

  	if (!InitApplication(hInstance))
	    return (FALSE);     

   /* Perform initializations that apply to a specific instance */
   if (!InitInstance(hInstance, nCmdShow))
	   return (FALSE);

   /* Acquire and dispatch messages until a WM_QUIT message is received. */
   while (GetMessage(&msg,
	    NULL,              
	    0,                 
	    0))                
	{
	   TranslateMessage(&msg);
	   DispatchMessage(&msg); 
   }
   return (msg.wParam);  
                                                 
}


/****************************************************************************
*
*    FUNCTION: InitApplication(HANDLE)
*
*    PURPOSE: Initializes window data and registers window class
*
****************************************************************************/

BOOL InitApplication(HANDLE hInstance)       /* current instance             */
{
   WNDCLASS  wcSizebox;
    
   /* Fill in window class structure with parameters that describe the       */
   /* main window.                                                           */

   wcSizebox.style = 0;                     
   wcSizebox.lpfnWndProc = (WNDPROC)MainWndProc; 
   wcSizebox.cbClsExtra = 0;              
   wcSizebox.cbWndExtra = 0;              
   wcSizebox.hInstance = hInstance;       
   wcSizebox.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(SIZEBOX_ICON));
   wcSizebox.hCursor = LoadCursor(NULL, IDC_ARROW);
   wcSizebox.hbrBackground = GetStockObject(WHITE_BRUSH); 
   wcSizebox.lpszMenuName =  "SizeboxMenu";  
   wcSizebox.lpszClassName = "SizeboxWClass";

   return (RegisterClass(&wcSizebox));

}


/****************************************************************************
*
*    FUNCTION:  InitInstance(HANDLE, int)
*
*    PURPOSE:  Saves instance handle and creates main window
*
****************************************************************************/

BOOL InitInstance(
   HANDLE          hInstance,
   int             nCmdShow) 
{
   HWND            hWnd;

   hInst = hInstance;

   hWnd = CreateWindow(
   	"SizeboxWClass",           
	   "Sizebox Sample", 
   	WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, CW_USEDEFAULT, 300, 150,
	   NULL,               
   	NULL,               
	   hInstance,          
   	NULL);

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
****************************************************************************/

LONG APIENTRY MainWndProc(
	HWND hWnd,                /* window handle                   */
	UINT message,             /* type of message                 */
	UINT wParam,              /* additional information          */
	LONG lParam)              /* additional information          */
{
   HWND hWndChild;
   HDC hdc;
   PAINTSTRUCT ps;

   switch (message) 
   {

      case WM_CREATE:
         hWndChild = CreateWindow(
         	"Scrollbar", 
         	"",
         	WS_CHILD | WS_VISIBLE | SBS_SIZEBOX | SBS_SIZEBOXTOPLEFTALIGN,
         	0,0,0,0,
         	hWnd,         
         	(HMENU)10,         
            hInst,
            NULL);
         break;

      case WM_PAINT:
      {

         hdc = BeginPaint(hWnd, &ps);
         TextOut(hdc, 20, 10, instruct1, strlen(instruct1));      
         TextOut(hdc, 20, 30, instruct2, strlen(instruct2));      
         TextOut(hdc, 20, 50, instruct3, strlen(instruct3));      
         
         EndPaint(hWnd, &ps);
      }
      break;
         

   	case WM_COMMAND:

	      switch( LOWORD( wParam ))
	      {
		      case IDM_EXIT:
		         PostQuitMessage(0);
   		      break;

	      	case IDM_ABOUT:
		         DialogBox(hInst, "AboutBox", hWnd, (DLGPROC)About);
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


