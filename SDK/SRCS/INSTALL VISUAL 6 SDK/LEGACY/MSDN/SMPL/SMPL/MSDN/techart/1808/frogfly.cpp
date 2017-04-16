
/****************************************************************************

        PROGRAM: frogfly.c

        PURPOSE: Sample application to demonstrate "life" C++ objects.
                 Accompains an MSDN CD article.


        Author: Ruediger R. Asche

****************************************************************************/

#include <windows.h>   
#include "classes.hpp"


/****************************************************************************

        FUNCTION: WinMain(HINSTANCE, HINSTANCE, LPSTR, int)


****************************************************************************/
int APIENTRY WinMain(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow)
{

        MSG msg;

/* Under Windows 3.x, hPrevInstance could be != 0 which the application
   had to catch. hPrevInstance is always 0 under Windows NT, so we do not
   need to check explicitly. */

        if (!InitApplication(hInstance))
                return (FALSE);
        if (!InitInstance(hInstance, nCmdShow))
                return (FALSE);

        while (GetMessage(&msg,NULL,0,0))     
        {
          TranslateMessage(&msg);
          DispatchMessage(&msg); 
        }
        return (msg.wParam); 
        lpCmdLine; // This will prevent 'unused formal parameter' warnings
}


/****************************************************************************

        FUNCTION: InitApplication(HINSTANCE)

        PURPOSE: Initializes window data and registers window class


****************************************************************************/

BOOL InitApplication(HINSTANCE hInstance)
{
        WNDCLASS  wc;

        wc.style         = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc   = (WNDPROC)WndProc;       
        wc.cbClsExtra    = 0;                      
        wc.cbWndExtra    = 0;                      
        wc.hInstance     = hInstance;              
        wc.hIcon         = LoadIcon (hInstance, szAppName); 
        wc.hCursor       = LoadCursor(hInstance, "burger");
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
        wc.lpszMenuName  = szAppName;              
        wc.lpszClassName = szAppName;              
        return (RegisterClass(&wc));
}


/****************************************************************************

        FUNCTION:  InitInstance(HINSTANCE, int)

****************************************************************************/

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
        HWND hWnd; 
        hWnd = CreateWindow(
                szAppName,           
                szTitle,             
                WS_OVERLAPPEDWINDOW,
                CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, 
                NULL,                
                NULL,                
                hInstance,           
                NULL                 
        );

        if (!hWnd) return (FALSE);
        ShowWindow(hWnd, nCmdShow); 
        UpdateWindow(hWnd);         
        return (TRUE);              
}

/****************************************************************************

        FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)


****************************************************************************/

LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM uParam,LPARAM lParam)     
{       static HPEN hPenKetchup;
        static HINSTANCE hInst;          
        switch (message) 
        {
          case WM_SIZE:
                the_pond->iPondWidth=LOWORD(lParam);
                the_pond->iPondHeight=HIWORD(lParam);
                return(0);
                break;
          case WM_CREATE:
                hInst = (HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE);
                the_pond = new pond(hWnd, hInst);
                hPenKetchup = CreatePen(PS_SOLID,3,KETCHUP_COLOR);
                InitializeCriticalSection(&csSerializeDraw);
                break;
          case WM_LBUTTONDOWN:
		        { HDC hDC;
                  HPEN hDefaultPen;
                  EnterCriticalSection(&csSerializeDraw);
                  hDC=GetDC(hWnd);
                  hDefaultPen = SelectObject(hDC,hPenKetchup);
                  Rectangle(hDC,LOWORD(lParam),HIWORD(lParam),LOWORD(lParam)+4,HIWORD(lParam)+4);
                  SelectObject(hDC,hDefaultPen);
                  ReleaseDC(hWnd,hDC);
                  LeaveCriticalSection(&csSerializeDraw);
                };
                break;
          case WM_TIMER:
                { char szBuf[60];
                  wsprintf(szBuf,"Remaining Frog Calories: %d, Flies: %d",the_pond->RetrieveFrogCalories(),the_pond->ReturnObjectCount(FLY_TYPE));
                  SetWindowText(hWnd,szBuf);
                };
                break;
          case WM_OBJECT_DIED:
                the_pond->Remove((int)uParam);
                if (!the_pond->ReturnObjectCount(FROG_TYPE))
                   PostMessage(hWnd,WM_COMMAND,IDM_STOPSIM,NULL);
                break;
          case WM_KEYDOWN:
                { int iNewXVel,iNewYVel;
                  switch (uParam)
                      { case VK_LEFT:
                           iNewXVel=-FROGMOVEMENT;
                           iNewYVel=0;
                           break;
                        case VK_RIGHT:
                           iNewXVel=FROGMOVEMENT;
                           iNewYVel=0;
                           break;
                        case VK_UP:
                           iNewXVel=0;
                           iNewYVel=-FROGMOVEMENT;
                           break;
                        case VK_DOWN:
                           iNewXVel=0;
                           iNewYVel=FROGMOVEMENT;
                           break;
                        default:
                           iNewXVel = iNewYVel = 0;
                      };
                  the_pond->SetFrogVelocity(iNewXVel,iNewYVel);
                };
                break;
          case WM_COMMAND:
                switch(uParam)
		            { case IDM_STARTSIM:
                      if (!the_pond->CreateObject(FROG_TYPE))
                         { MessageBox(hWnd,"Could not create frog!","",MB_OK);
                           break;
                         };
                      SetTimer(hWnd,1,1000,NULL);
                      break;
                      case IDM_STOPSIM:
                        KillTimer(hWnd,1);
                        the_pond->KillFrog();
                        SetWindowText(hWnd,"No simulation in progress");
                      break;
                      case IDM_ADDFLY: /*here create a new fly object*/
                        the_pond->CreateObject(FLY_TYPE);
                      break;
                    };
                    break;
          case WM_DESTROY:
                DeleteCriticalSection(&csSerializeDraw);
                DeleteObject(hPenKetchup);
                delete the_pond;
                PostQuitMessage(0);
                break;
          default:
                return (DefWindowProc(hWnd, message, uParam, lParam));
        }
        return (0);
}


