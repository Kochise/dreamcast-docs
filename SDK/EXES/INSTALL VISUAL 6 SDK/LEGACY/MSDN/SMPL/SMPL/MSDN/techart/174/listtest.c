#include "listtest.h"   

HINSTANCE    hVlbLib;

int PASCAL WinMain(HANDLE hInstance, HANDLE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
 MSG        msg;           /* MSG structure to store your messages        */
 int        nRc;           /* return value from Register Classes          */

 strcpy(szAppName, "LISTTEST");
 hInst = hInstance;

 if(!hPrevInstance)
   {
    /* register window classes if first instance of application         */
    if ((nRc = nCwRegisterClasses()) == -1)
      {
       /* registering one of the windows failed                         */
       LoadString(hInst, IDS_ERR_REGISTER_CLASS, szString, sizeof(szString));
       MessageBox(NULL, szString, NULL, MB_ICONEXCLAMATION);
       return nRc;
      }
   }

/* create application's Main window                                    */
 hWndMain = CreateWindow(
                szAppName,               /* Window class name           */
                NULL,                   /* no title                     */
                WS_CAPTION      |        /* Title and Min/Max           */
                WS_SYSMENU      |        /* Add system menu box         */
                WS_MINIMIZEBOX  |        /* Add minimize box            */
                WS_MAXIMIZEBOX  |        /* Add maximize box            */
                WS_THICKFRAME   |        /* thick sizeable frame        */
                WS_CLIPCHILDREN |         /* don't draw in child windows areas */
                WS_OVERLAPPED,
                CW_USEDEFAULT, 0,        /* Use default X, Y            */
                CW_USEDEFAULT, 0,        /* Use default X, Y            */
                NULL,                    /* Parent window's handle      */
                NULL,                    /* Default to Class Menu       */
                hInst,                   /* Instance of window          */
                NULL);                   /* Create struct for WM_CREATE */


 if(hWndMain == NULL)
   {
    LoadString(hInst, IDS_ERR_CREATE_WINDOW, szString, sizeof(szString));
    MessageBox(NULL, szString, NULL, MB_ICONEXCLAMATION);
    return IDS_ERR_CREATE_WINDOW;
   }

 ShowWindow(hWndMain, nCmdShow);            /* display main window      */

 while(GetMessage(&msg, NULL, 0, 0))        /* Until WM_QUIT message    */
   {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
   }

 /* Do clean up before exiting from the application                     */
 CwUnRegisterClasses();
 return msg.wParam;
}


LONG FAR PASCAL WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
 HMENU      hMenu=0;            /* handle for the menu                 */
 int        nRc=0;              /* return code                         */

 switch (Message)
   {
    case WM_COMMAND:
#ifdef WIN32
         switch (LOWORD(wParam))
#else
         switch (wParam)
#endif
           {
            case IDM_DIALOG:
                 /* Place User Code to respond to the                   */
                 /* Menu Item Named "Dialog" here.                      */


                 {
                  FARPROC lpfnDIALOGSMsgProc;

                  lpfnDIALOGSMsgProc = MakeProcInstance((FARPROC)DIALOGSMsgProc, hInst);
                  nRc = DialogBox(hInst, MAKEINTRESOURCE(100), hWnd, lpfnDIALOGSMsgProc);
                  FreeProcInstance(lpfnDIALOGSMsgProc);
                 }
                 break;

            default:
                return DefWindowProc(hWnd, Message, wParam, lParam);
           }
         break;        /* End of WM_COMMAND                             */

    case WM_CREATE:
#ifdef WIN32
             hVlbLib = LoadLibrary("vlist32.dll");
#else
             hVlbLib = LoadLibrary("vlist.dll");
#endif
         break;       /*  End of WM_CREATE                              */

    case WM_DESTROY:
             FreeLibrary(hVlbLib);
         break;

    case WM_CLOSE:  /* close the window                                 */
         /* Destroy child windows, modeless dialogs, then, this window  */
         DestroyWindow(hWnd);
         if (hWnd == hWndMain)
           PostQuitMessage(0);  /* Quit the application                 */
        break;

    default:
         return DefWindowProc(hWnd, Message, wParam, lParam);
   }
 return 0L;
}


BOOL FAR PASCAL DIALOGSMsgProc(HWND hWndDlg, UINT Message, WPARAM wParam, LPARAM lParam)
{
 HWND                   hwndList;
 static char            szText[128];
 LPVLBSTRUCT            lpvlbInStruct;

 switch(Message)
   {
    case WM_INITDIALOG:
         cwCenter(hWndDlg, 0);
         /* initialize working variables                                */
		 hwndList = GetDlgItem(hWndDlg, 101);
		 {
			int Tabs[3] = { 50, 100, 150 };
			SendMessage(hwndList, VLB_SETTABSTOPS, 3, (LPARAM)((int FAR *)Tabs) );
		 }
         SendMessage(hwndList, VLB_INITIALIZE, 0, 0L);
         SendMessage(hwndList, VLB_SETHORIZONTALEXTENT, 700, 0L);
         break; /* End of WM_INITDIALOG                                 */

    case WM_CLOSE:
         {
           VLBSTRUCT  vlbOutStruct;
           hwndList = GetDlgItem(hWndDlg, 101);
           vlbOutStruct.lIndex = SendMessage(hwndList, VLB_GETCURSEL, 0, 0L);
           vlbOutStruct.lpTextPointer = szText;
           SendMessage(hwndList, VLB_GETTEXT, 0, (LPARAM)(LPVLBSTRUCT)&vlbOutStruct);
           MessageBox(NULL, szText, "Current Item" , MB_OK);
           EndDialog(hWndDlg, FALSE);
         }
         break; /* End of WM_CLOSE                                      */

    case WM_COMMAND:
#ifdef WIN32
         switch (LOWORD(wParam))
#else
         switch (wParam)
#endif
           {
            case IDOK:
               {
                 VLBSTRUCT  vlbOutStruct;
                 hwndList = GetDlgItem(hWndDlg, 101);
                 vlbOutStruct.lIndex = SendMessage(hwndList, VLB_GETCURSEL, 0, 0L);
                 vlbOutStruct.lpTextPointer = szText;
                 SendMessage(hwndList, VLB_GETTEXT, 0, (LPARAM)(LPVLBSTRUCT)&vlbOutStruct);
                 MessageBox(NULL, szText, "Current Item" , MB_OK);
                 EndDialog(hWndDlg, FALSE);
               }
                 break;
           }
         break;    /* End of WM_COMMAND                                 */          
         
    case VLB_PREV:
         lpvlbInStruct = (LPVLBSTRUCT)lParam;

         if ( lpvlbInStruct->lIndex > 0 ) {
            lpvlbInStruct->nStatus = VLB_OK;
            lpvlbInStruct->lIndex--;
            lpvlbInStruct->lData = lpvlbInStruct->lIndex;
			sprintf(szText,"Item\t%ld\tSome Text to Scroll\tMMMMMMMMMMMMMMMMMMMMM",lpvlbInStruct->lIndex);
            lpvlbInStruct->lpTextPointer = szText;
            return TRUE;
         }
         else {
            lpvlbInStruct->nStatus = VLB_ENDOFFILE;
            return TRUE;
         }
         break;

    case VLB_FINDPOS:
         lpvlbInStruct = (LPVLBSTRUCT)lParam;

         if ( lpvlbInStruct->lIndex == 0L ) {
            goto First;
         }
         else if ( lpvlbInStruct->lIndex == 100L ) {
            goto Last;
         }
         else {
            lpvlbInStruct->lIndex = lpvlbInStruct->lData*1000L;
            lpvlbInStruct->nStatus = VLB_OK;
			sprintf(szText,"Item\t%ld\tSome Text to Scroll\tMMMMMMMMMMMMMMMMMMMMM",lpvlbInStruct->lIndex);
            lpvlbInStruct->lpTextPointer = szText;
            return TRUE;
         }
       break;

    case VLB_FINDITEM:
         lpvlbInStruct = (LPVLBSTRUCT)lParam;

         lpvlbInStruct->lIndex = lpvlbInStruct->lData;
         lpvlbInStruct->nStatus = VLB_OK;
		 sprintf(szText,"Item\t%ld\tSome Text to Scroll\tMMMMMMMMMMMMMMMMMMMMM",lpvlbInStruct->lIndex);
         lpvlbInStruct->lpTextPointer = szText;

         return TRUE;

       break;

    case VLB_FINDSTRING:
    case VLB_FINDSTRINGEXACT:
    case VLB_SELECTSTRING:
    case VLBR_FINDSTRING:
    case VLBR_FINDSTRINGEXACT:
    case VLBR_SELECTSTRING:
       {
         lpvlbInStruct = (LPVLBSTRUCT)lParam;

         _fstrcpy(szText,lpvlbInStruct->lpFindString);
         lpvlbInStruct->lIndex = atol(szText);
		 sprintf(szText,"Item\t%ld\tSome Text to Scroll\tMMMMMMMMMMMMMMMMMMMMM",lpvlbInStruct->lIndex);
         lpvlbInStruct->lpTextPointer = szText;
         lpvlbInStruct->lData = lpvlbInStruct->lIndex;
         lpvlbInStruct->nStatus = VLB_OK;
         return TRUE;
       }
       break;

    case VLB_RANGE:
         lpvlbInStruct = (LPVLBSTRUCT)lParam;

         lpvlbInStruct->lIndex = 100000L;
         lpvlbInStruct->nStatus = VLB_OK;
         return TRUE;

       break;

    case VLB_NEXT:
         lpvlbInStruct = (LPVLBSTRUCT)lParam;

         if ( lpvlbInStruct->lIndex < 99999L ) {
            lpvlbInStruct->nStatus = VLB_OK;
            lpvlbInStruct->lIndex++;
            lpvlbInStruct->lData = lpvlbInStruct->lIndex;
			sprintf(szText,"Item\t%ld\tSome Text to Scroll\tMMMMMMMMMMMMMMMMMMMMM",lpvlbInStruct->lIndex);
            lpvlbInStruct->lpTextPointer = szText;
            return TRUE;
         }
         else {
            lpvlbInStruct->nStatus = VLB_ENDOFFILE;
            return TRUE;
         }
       break;

    case VLB_FIRST:
First:
         lpvlbInStruct = (LPVLBSTRUCT)lParam;

         lpvlbInStruct->nStatus = VLB_OK;
         lpvlbInStruct->lIndex = 0L;
		 sprintf(szText,"Item\t%ld\tSome Text to Scroll\tMMMMMMMMMMMMMMMMMMMMM",lpvlbInStruct->lIndex);
         lpvlbInStruct->lpTextPointer = szText;
         lpvlbInStruct->lData = lpvlbInStruct->lIndex;
         return TRUE;

    case VLB_LAST:
Last:
         lpvlbInStruct = (LPVLBSTRUCT)lParam;

         lpvlbInStruct->nStatus = VLB_OK;
         lpvlbInStruct->lIndex = 99999L;
		 sprintf(szText,"Item\t%ld\tSome Text to Scroll\tMMMMMMMMMMMMMMMMMMMMM",lpvlbInStruct->lIndex);
         lpvlbInStruct->lpTextPointer = szText;
         lpvlbInStruct->lData = lpvlbInStruct->lIndex;
         return TRUE;

       break;

    case VLB_GETITEMDATA:
    case VLBR_GETITEMDATA:
         lpvlbInStruct = (LPVLBSTRUCT)lParam;

         lpvlbInStruct->nStatus = VLB_OK;
         lpvlbInStruct->lData = lpvlbInStruct->lIndex;
         return TRUE;
       break;

    case VLB_GETTEXT:
    case VLBR_GETTEXT:
         lpvlbInStruct = (LPVLBSTRUCT)lParam;

         lpvlbInStruct->nStatus = VLB_OK;
         lpvlbInStruct->lData = lpvlbInStruct->lIndex;
		 sprintf(szText,"Item\t%ld\tSome Text to Scroll\tMMMMMMMMMMMMMMMMMMMMM",lpvlbInStruct->lIndex);
         lpvlbInStruct->lpTextPointer = szText;
         return TRUE;
       break;

    default:
        return FALSE;
   }
 return TRUE;
}


int nCwRegisterClasses(void)
{
 WNDCLASS   wndclass;    /* struct to define a window class             */
 memset(&wndclass, 0x00, sizeof(WNDCLASS));


 /* load WNDCLASS with window's characteristics                         */
 wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_BYTEALIGNWINDOW;
 wndclass.lpfnWndProc = WndProc;
 /* Extra storage for Class and Window objects                          */
 wndclass.cbClsExtra = 0;
 wndclass.cbWndExtra = 0;
 wndclass.hInstance = hInst;
 wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
 wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
 /* Create brush for erasing background                                 */
 wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
 wndclass.lpszMenuName = szAppName;   /* Menu Name is App Name */
 wndclass.lpszClassName = szAppName; /* Class Name is App Name */
 if(!RegisterClass(&wndclass))
   return -1;


 return(0);
}

void cwCenter(hWnd, top)
HWND hWnd;
int top;
{
 POINT      pt;
 RECT       swp;
 RECT       rParent;
 int        iwidth;
 int        iheight;

 /* get the rectangles for the parent and the child                     */
 GetWindowRect(hWnd, &swp);
 GetClientRect(hWndMain, &rParent);

 /* calculate the height and width for MoveWindow                       */
 iwidth = swp.right - swp.left;
 iheight = swp.bottom - swp.top;

 /* find the center point and convert to screen coordinates             */
 pt.x = (rParent.right - rParent.left) / 2;
 pt.y = (rParent.bottom - rParent.top) / 2;
 ClientToScreen(hWndMain, &pt);

 /* calculate the new x, y starting point                               */
 pt.x = pt.x - (iwidth / 2);
 pt.y = pt.y - (iheight / 2);

 /* top will adjust the window position, up or down                     */
 if(top)
   pt.y = pt.y + top;

 /* move the window                                                     */
 MoveWindow(hWnd, pt.x, pt.y, iwidth, iheight, FALSE);
}

void CwUnRegisterClasses(void)
{
 WNDCLASS   wndclass;    /* struct to define a window class             */
 memset(&wndclass, 0x00, sizeof(WNDCLASS));

 UnregisterClass(szAppName, hInst);
}
