/*
    PROGRAM: QURYDEMO
    ========

    PURPOSE:
    ========
    demonstrates a simple MDI application that allows a user to
    simultaneously connect to multiple hetrogeneous databases
    and perform SQL queries to get results.

    FUNCTIONS:
    ==========
    WinMain() - main routine
    MainWndProc() - processes Main Application Window messages
    MDIChildProc() - processes MDI child window messages
    ToolbarProc() - processes tool bar messages
    StatusbarProc() - processes Status bar messages
    ConnectDlgProc() - processes Connection Dialog box messages
    DisconnectDlgProc() - processes Disconnect Dialog box messages
    AboutDlgProc() - processes messages for About dialog box
    MDIChildDlgProc() - processes messages for dummy child dialog box
            in MDI child window
    DrawBitmap() - draws bitmaps for toolbuttons

    COMMENTS:
    =========
    Created by Microsoft Corporation.
*/

#include <stdio.h>
#include <string.h>
#include <time.h>

#include <windows.h>
#ifdef WIN32
#include <windowsx.h>
#else
#include "w16macro.h"
#endif
#include "qurydemo.h"

CONSTSTR(szKeyWord,			 "query demo, features");


/*
    FUNCTION: WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
    COMMENTS: Application Entry Routine.
          Register Classes. Create Main Window and MDI Child Window.
          Process Main Message Loop.
*/

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
   MSG     msg;            //msg structure
   WNDCLASS    wc;         //class structure
   HICON       hMainIcon;      //App Icon
   HICON       hMDIChildIcon;      //MDI Child Icon
   HWND        hWndMDIChild;       //temp MDI Child Window Handle
   char        szBuffer[MAXBUFLEN+1];  //temp string buffer to check class name
   BOOL        bDialogMessage = FALSE; //temp boolean to check dilogbox msgs
   HACCEL      hAccel;         //accelerator table handle

   hAppInstance = hInstance;

   // check if application is already running, if
   // so make it active and bring it in focus

   if (hWndFrame = FindWindow(ODBCFRAMECLASS, NULL)) {
      hWndFrame = GetLastActivePopup(hWndFrame);
      if (IsIconic(hWndFrame))
         OpenIcon(hWndFrame);
      else
         BringWindowToTop(hWndFrame);
      ACTIVATEWINDOW(hWndFrame);
      return (FALSE);
   }

   // initialize ODBC Driver Manager Interface

   if (!InitSQLEnvironment()) {
      MessageBox(hWndFrame, INITERROR, EXECERROR, MB_OK|MB_ICONHAND);
      return (FALSE);
   }

   // register window classes for the application - Main Window Class

   wc.style = 0;
   wc.lpfnWndProc = MainWndProc;
   wc.cbClsExtra = 0;
   wc.cbWndExtra = 0;
   wc.hInstance = hAppInstance;
   wc.hIcon = hMainIcon = LoadIcon(hAppInstance, APPICON);
   wc.hCursor = LoadCursor((HINSTANCE)NULL, IDC_ARROW);
   wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE+1);
   wc.lpszMenuName =  QURYDEMOMENU;
   wc.lpszClassName = ODBCFRAMECLASS;

   if (!RegisterClass(&wc)) {
      MessageBox(hWndFrame, CLASSERROR, EXECERROR, MB_OK|MB_ICONHAND|MB_TASKMODAL);
      return (FALSE);
   }

   // register Toolbar Class

   wc.hIcon = (HICON)NULL;
   wc.lpszMenuName =  NULL;
   wc.lpfnWndProc = ToolbarProc;
   wc.lpszClassName = ODBCTOOLCLASS;

   if (!RegisterClass(&wc)) {
      MessageBox(hWndFrame, CLASSERROR, EXECERROR, MB_OK|MB_ICONHAND|MB_TASKMODAL);
      return (FALSE);
   }

   // register Statusbar Class

   wc.lpfnWndProc = StatusbarProc;
   wc.lpszClassName = ODBCSTATUSCLASS;

   if (!RegisterClass(&wc)) {
      MessageBox(hWndFrame, CLASSERROR, EXECERROR, MB_OK|MB_ICONHAND|MB_TASKMODAL);
      return (FALSE);
   }

   // register MDI Child Window Class

   wc.hIcon = hMDIChildIcon = LoadIcon(hAppInstance, QUERYWINDOWICON);
   wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
   wc.cbWndExtra = CBWNDEXTRA;
   wc.lpszClassName = ODBCMDICLASS;
   wc.lpfnWndProc = MDIChildProc;

   if (!RegisterClass(&wc)) {
      MessageBox(hWndFrame, CLASSERROR, EXECERROR, MB_OK|MB_ICONHAND|MB_TASKMODAL);
      return (FALSE);
   }

   // create Main window and the MDI Client window

   if (!(hWndFrame = CreateWindow(ODBCFRAMECLASS, APPTITLE, WS_OVERLAPPEDWINDOW,
                                  CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                  (HWND)NULL, (HMENU)NULL, hAppInstance, NULL))) {
      MessageBox(hWndFrame, CREATEMAINERR, EXECERROR, MB_OK|MB_ICONHAND|MB_TASKMODAL);
      return (FALSE);
   }

   ShowWindow(hWndFrame, nCmdShow);
   UpdateWindow(hWndFrame);

   // load accelerators

   hAccel = LoadAccelerators(hAppInstance, APPACCELERATOR);

   // acquire and dispatch messages until a WM_QUIT message is received

   while (GetMessage(&msg, (HWND)NULL, 0, 0)) {

      // check for App accelerators

      if (TranslateAccelerator(hWndFrame, hAccel, &msg))
         continue;

      // check for MDI accelerators

      if (TranslateMDISysAccel(hWndMDIClient, &msg))
         continue;

      // each MDI Child has a modeless dialog in its client area
      // to provide tab controls. Check for Modeless Dialog msgs.

      for (hWndMDIChild = GetWindow(hWndMDIClient, GW_CHILD); hWndMDIChild; hWndMDIChild = GetWindow(hWndMDIChild, GW_HWNDNEXT)) {
         GetClassName(hWndMDIChild, szBuffer, MAXBUFLEN);
         if (strcmp(szBuffer, ODBCMDICLASS))
            continue;
         if (IsDialogMessage((HWND)GetWindowLong(hWndMDIChild, GWLAPP_HDLG), &msg)) {
            bDialogMessage = TRUE;
            break;
         }
      }

      if (bDialogMessage) {
         bDialogMessage = FALSE;
         continue;
      }

      // if the message does not need special processing, dispatch it

      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }

   // free memory used by ODBC Driver Manager interface

   FreeSQLEnvironment();


   // free Icon resources

   if (hMainIcon)
      DestroyIcon(hMainIcon);

   if (hMDIChildIcon)
      DestroyIcon(hMDIChildIcon);

   return (msg.wParam);
}

/*
    FUNCTION: MainWndProc(HWND hWnd, UINT   message, WPARAM wParam, LPARAM lParam)
    COMMENTS: Windows Callback procedure to handle Window messages.
              Menu Commands and System Command messages are handled by
              this main window.
*/

long CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message) {
      static int  iToolY;         //remember Toolbar height for resize
      static int  iStatusY;       //remember Statusbar height for resize

     case WM_CREATE:
      {
         CLIENTCREATESTRUCT  ccs;        //MDIclient window structure
         HDC         hDC;        //Device Context handle
         SIZE            sizeBar;    //Size of a text bar
         RECT            rectCombo;      //Size of combo box

         // Create child windows
         //1. combobox to display connections - DSN, SQLHDBC
         //2. combobox to display SQLHSTMT on current SQLHDBC
         //3. Toolbar to put toolbuttons
         //4. Statusbat to display current action, date and time
         //5. MDI Client Window to process MDI children

         hWndCrsrList = CreateWindow(COMBOBOXCLASS, NULL,
                                     WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS |
                                     WS_VSCROLL | CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL,
                                     5, 2, 180, 150, hWnd,
                                     (HMENU)IDW_CRSRLIST, hAppInstance, NULL);

         hWndStmtList = CreateWindow(COMBOBOXCLASS, NULL,
                                     WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS |
                                     WS_VSCROLL | CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL,
                                     190, 2, 150, 150, hWnd,
                                     (HMENU)IDW_STMTLIST, hAppInstance, NULL);

         hWndToolbar = CreateWindow(ODBCTOOLCLASS, NULL,
                                    WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
                                    0, 0, 0, 0, hWnd, (HMENU)IDW_TOOLBAR, hAppInstance, NULL);

         hWndStatusbar = CreateWindow(ODBCSTATUSCLASS, NULL,
                                      WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS,
                                      0, 0, 0, 0, hWnd, (HMENU)IDW_STATUSBAR, hAppInstance, NULL);

         ccs.hWindowMenu = GetSubMenu(GetMenu(hWnd), WINDOWMENUPLACE);
         ccs.idFirstChild = IDM_MDICHILD;

         hWndMDIClient = CreateWindow(MDICLIENTCLASS, NULL,
                                      WS_CHILD | WS_CLIPSIBLINGS |
                                      WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL | WS_VISIBLE,
                                      0, 0, 0, 0, hWnd,
                                      (HMENU)IDW_MDICLIENT, hAppInstance, (LPSTR)&ccs);

         // check to see if any of the above window creation failed

         if (!hWndCrsrList || !hWndStmtList || !hWndToolbar || !hWndStatusbar || !hWndMDIClient) {
            MessageBox(hWnd, CREATEMAINERR, EXECERROR, MB_OK|MB_ICONHAND|MB_TASKMODAL);
            PostMessage(hWnd, WM_CLOSE, 0, 0);
            break;
         }
         // calculate proper text height for tool and status bars

         GetWindowRect(hWndStmtList, &rectCombo);
         iToolY = rectCombo.bottom - rectCombo.top + TOOLBARMARGINY;

         if (hDC = GetDC(hWndStatusbar)) {
            GetTextExtentPoint(hDC, ALPHABETS, strlen(ALPHABETS), &sizeBar);
            ReleaseDC(hWndStatusbar, hDC);
            iStatusY = sizeBar.cy + STATUSBARMARGINY;
         }
         else {
            iStatusY = 0;
            DestroyWindow(hWndStatusbar);
         }

         break;
      }

     case WM_GETMINMAXINFO:

      // limit minimum size of the main window

      ((MINMAXINFO FAR*)lParam)->ptMinTrackSize.x =
         max(MINWIDTH, rectStatusText.right-rectStatusText.left+iTimex+iDatex+14);
      ((MINMAXINFO FAR*)lParam)->ptMinTrackSize.y = MINHEIGHT;
      break;

     case WM_SIZE: // resize children
      {
         WORD    wWidth = LOWORD(lParam);    //width of rectangle
         WORD    wHeight = HIWORD(lParam);   //height of rectangle

         MoveWindow(hWndToolbar, 0, 0, wWidth, iToolY, TRUE);
         MoveWindow(hWndStatusbar, 0, wHeight-iStatusY, wWidth, iStatusY, TRUE);
         InvalidateRect(hWndStatusbar, NULL, TRUE);
         MoveWindow(hWndMDIClient, 0, iToolY, wWidth, wHeight-iStatusY-iToolY, TRUE);
         break;
      }

     case WM_SYSCOLORCHANGE: // inform 3D controls of color change

      //      Ctl3dColorChange();
      break;

     case WM_SYSCOMMAND: // close comboboxes if dropped down

      SendMessage(hWndCrsrList, CB_SHOWDROPDOWN, (WPARAM)FALSE, 0);
      SendMessage(hWndStmtList, CB_SHOWDROPDOWN, (WPARAM)FALSE, 0);
      return (DefFrameProc(hWnd, hWndMDIClient, message, wParam, lParam));

     case WM_INITMENUPOPUP: // initialize popup menus
      {
         int iMenuId;    //Menu ID being processed
         int nItems;         //# of menu items
         int nPos;           //Menu Position

         //ignore the msg if it is for a system menu

         if (HIWORD(lParam))
            break;

         // Go through the menu items for current popup menu
         // and enable/disable menu item, if required

         nItems = GetMenuItemCount((HMENU)wParam);
         for (nPos = 0; nPos < nItems; nPos++)
            switch (iMenuId = GetMenuItemID((HMENU)wParam, nPos)) {
              case IDM_DISCONNECT:
              case IDM_NEW:

               EnableMenuItem((HMENU)wParam, iMenuId, MF_BYCOMMAND|
                              ((SendMessage(hWndCrsrList, CB_GETCOUNT, 0, 0) > 0)
                               ? MF_ENABLED
                               : MF_GRAYED));
               break;

              case IDM_QUERY:
              case IDM_TILE:
              case IDM_CASCADE:
              case IDM_ICONS:
              case IDM_CLOSEALL:

               EnableMenuItem((HMENU)wParam, iMenuId, MF_BYCOMMAND|
                              (GetWindow(hWndMDIClient, GW_CHILD)
                               ? MF_ENABLED
                               : MF_GRAYED));
               break;

              default:

               break;
            }
         break;
      }

     case WM_MENUSELECT: // update status bar to reflect menu selection
      {
         int iMenuFlag;      //Check menu type
         HMENU   hMenu;              //Menu Handle
         char    szMenuName[MAXBUFLEN+1];//Menu Name

         // store Menuitem ID as a state value for text display

         wStatusText = GET_WM_MENUSELECT_CMD(wParam, lParam);

         // process popup menus ie non menuitem selections

         iMenuFlag = GET_WM_MENUSELECT_FLAGS(wParam, lParam);

         // if the selected menu is a system popup menu

         if (wStatusText && (iMenuFlag & MF_SYSMENU) && (iMenuFlag & MF_POPUP))
            wStatusText = IDM_POPUPAPPSYS;

         // else if the selected menu is a popup menu check menu names
         // OR check if it is a control popup menu of maximized MDI Child window

         else if (wStatusText && (iMenuFlag & MF_POPUP)) {
            hMenu = (HMENU)wStatusText;
            GetMenuString(hMenu, 0, szMenuName, MAXBUFLEN, MF_BYPOSITION);
            if (!strcmp(szMenuName, MENUITEMCONNECT))
               wStatusText = IDM_POPUPLOGIN;
            else if (!strcmp(szMenuName, MENUITEMQUERY))
               wStatusText = IDM_POPUPQUERY;
            else if (!strcmp(szMenuName, MENUITEMTILE))
               wStatusText = IDM_POPUPWINDOW;
            else if (!strcmp(szMenuName, MENUITEMAPPHELP))
               wStatusText = IDM_POPUPHELP;
            else if (GetMenuString(hMenu, SC_NEXTWINDOW, szMenuName, MAXBUFLEN, MF_BYCOMMAND)>0)
               wStatusText = IDM_POPUPMDISYS;
            else
               wStatusText = 0;
         }

         // invalidate status bar for repaint

         InvalidateRect(hWndStatusbar, &rectStatusText, TRUE);
         break;
      }

     case WM_COMMAND: // process menu commands

      switch (GET_WM_COMMAND_ID(wParam, lParam)) {

        case IDM_CONNECT: // bring up connect dialog & do connect processing

         DialogBox(hAppInstance, CONNECTDIALOG, hWnd,ConnectDlgProc);
         break;

        case IDM_DRIVERCONNECT: // let the driver do the dialogs

         DriverConnectDatabase(hWnd);
         break;

        case IDM_DISCONNECT: // bringup disconnect dlg and do disconnects

         DialogBox(hAppInstance, DISCONNECTDIALOG, hWnd,DisconnectDlgProc);
         break;

        case IDM_QUERY: // process execute query request

         ExecuteQuery();
         break;

        case IDM_EXIT: // process exit request

         SendMessage(hWndFrame, WM_CLOSE, 0, 0);
         break;

        case IDM_NEW: // create a new query window on current connect

         NewQueryWindow();
         break;

        case IDM_TILE: // let MDI Client tile the MDI children

         SendMessage(hWndMDIClient, WM_MDITILE, 0, 0);
         break;

        case IDM_CASCADE: // let MDI Client cascade MDI children

         SendMessage(hWndMDIClient, WM_MDICASCADE, 0, 0);
         break;

        case IDM_ICONS: // let MDI Client arrange iconic MDI children

         SendMessage(hWndMDIClient, WM_MDIICONARRANGE, 0, 0);
         break;

        case IDM_CLOSEALL: // Close all open windows and free hstmts
         {
            HWND    hWndTemp;   //temp window handle

            // hide MDI Client Windows to avoid repaints

            ShowWindow(hWndMDIClient,SW_HIDE);
            while (hWndTemp = GetWindow(hWndMDIClient, GW_CHILD))
               SendMessage(hWndMDIClient, WM_MDIDESTROY, (WPARAM)hWndTemp, 0);
            ShowWindow(hWndMDIClient, SW_SHOW);
            break;
         }

        case IDM_APPHELP: // bring up Samples Help file

         WinHelp(hWnd, SAMPLESHELPFILE, HELP_KEY,(DWORD)(LPTSTR)szKeyWord);
			break;

        case IDM_ABOUT: // bringup About dialog

         DialogBox(hAppInstance, ABOUTDIALOG, hWnd, AboutDlgProc);
         break;

        case IDW_CRSRLIST: // change current cursor ?

         if (GET_WM_COMMAND_CMD(wParam, lParam) == CBN_SELCHANGE)
            ChangeCurrentCursor(GET_WM_COMMAND_HWND(wParam, lParam));
         else if (GET_WM_COMMAND_CMD(wParam, lParam) == CBN_KILLFOCUS)
            PostMessage(GET_WM_COMMAND_HWND(wParam, lParam), CB_SHOWDROPDOWN,
                        (WPARAM)FALSE, 0);
         else
            DefFrameProc(hWnd, hWndMDIClient, WM_COMMAND, wParam, lParam);
         break;

        case IDW_STMTLIST: // change current hstmt?

         if (GET_WM_COMMAND_CMD(wParam, lParam) == CBN_SELCHANGE)
            ChangeCurrentQuery(GET_WM_COMMAND_HWND(wParam, lParam));
         else if (GET_WM_COMMAND_CMD(wParam, lParam) == CBN_KILLFOCUS)
            PostMessage(GET_WM_COMMAND_HWND(wParam, lParam), CB_SHOWDROPDOWN,
                        (WPARAM)FALSE, 0);
         else
            DefFrameProc(hWnd, hWndMDIClient, WM_COMMAND, wParam, lParam);
         break;

        default:

         DefFrameProc(hWnd, hWndMDIClient, WM_COMMAND, wParam, lParam);
         break;
      }
      break;

     case WM_CLOSE: //close all MDI windows, hdbcs & hstmts, else fail

      return (CloseDatabases()
              ? DefFrameProc(hWnd, hWndMDIClient, message, wParam, lParam)
              : FALSE);

     case WM_DESTROY:

      // Close Help File if open

      WinHelp(hWnd, SAMPLESHELPFILE, HELP_QUIT, 0);
      PostQuitMessage(0);
      break;

     default:

      return (DefFrameProc(hWnd, hWndMDIClient, message, wParam, lParam));
   }
   return (0);
}

/*
    FUNCTION: MDIChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    COMMENTS: Window Procedure for MDI Child windows
*/

long CALLBACK MDIChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message) {
      HWND    hWndTemp;   //temporary window handle
      DLGPROC lpDlgProc;  //procedure address for modeless dialog

     case WM_CREATE:

      // create child windows
      // 1. Modeless Dialog box in the background to process tabs
      // 2. Static Text to display prompt
      // 3. Edit Control to type SQL text
      // 4. List Box to display results
      // store dialog handle for future reference
      // set focus to edit control

      // if create failed due to low system resources

      if (!hWnd)
         break;

      hWndActiveChild = hWnd;
      hWndTemp = CreateDialog(hAppInstance, MDICHILDDIALOG, hWndActiveChild, MDIChildDlgProc);

      // check to see if the dialog was created?, if not destroy this window

      if (!hWndTemp) {
         return (-1);
      }

      SetWindowLong(hWnd, GWLAPP_HDLG, (LONG)hWndTemp);
      SetFocus(GetDlgItem(hWndTemp, IDTEXT_SQL));
      break;

     case WM_SIZE: {
        WORD    wWidth;         //New Width of MDI Child
        WORD    wHeight;        //New Height of MDI Child
        HDC     hDC;            //Device Context
        char    szBuffer[MAXBUFLEN+1];  //Static Control Text
        int nStrLen;        //Buffer Length
        SIZE    size;           //Screen size for text display

        // call default procedure first, to let MDI position the child & then move its children

        DefMDIChildProc(hWnd, message, wParam, lParam);

        // move child windows with proper screen size for text display

        wWidth = LOWORD(lParam);
        wHeight = HIWORD(lParam);
        hWndTemp = (HWND)GetWindowLong(hWnd, GWLAPP_HDLG);

        nStrLen = GetWindowText(GetDlgItem(hWndTemp, IDTEXT_PRMPT), szBuffer, MAXBUFLEN);
        hDC = GetDC(hWnd);
        GetTextExtentPoint(hDC, szBuffer, nStrLen, &size);
        ReleaseDC(hWnd, hDC);

        MoveWindow(hWndTemp, 0, 0, wWidth, wHeight, TRUE);
        MoveWindow(GetDlgItem(hWndTemp, IDTEXT_PRMPT), 0, 0, size.cx+2, size.cy+2, TRUE);
        MoveWindow(GetDlgItem(hWndTemp, IDTEXT_SQL), size.cx+3, 0, wWidth - (size.cx+2), size.cy+2, TRUE);
        MoveWindow(GetDlgItem(hWndTemp, IDLIST_RSLT), 0, size.cy+3, wWidth, wHeight - (size.cy+2), TRUE);
        break;
     }

     case WM_MENUSELECT: // update status bar to reflect menu selection
      {
         int iMenuFlag;      //Check menu type

         // store the Menu Item Id as a state value for text display

         wStatusText = GET_WM_MENUSELECT_CMD(wParam, lParam);

         // if none of the menuitems was selected, check if
         // the control popup menu is selected.

         iMenuFlag = GET_WM_MENUSELECT_FLAGS(wParam, lParam);

         // if the selected menu is a system popup menu

         if (wStatusText && (iMenuFlag & MF_SYSMENU) && (iMenuFlag & MF_POPUP))
            wStatusText = IDM_POPUPMDISYS;

         // invalidate status bar for repaint

         InvalidateRect(hWndStatusbar, &rectStatusText, TRUE);
         break;
      }

     case WM_MDIACTIVATE:

      // check if the display of comboboxes require a change

      if (GET_WM_MDIACTIVATE_FACTIVATE(hWnd, wParam, lParam) &&
          (hWndActiveChild) && (hWndActiveChild != hWnd)) {
         hWndActiveChild = hWnd;
         DisplayNewCrsrAndStmt();
      }
      break;

     case WM_MOUSEACTIVATE:

      // current window has changed, update comboboxes.

      hWndActiveChild = hWnd;
      DisplayNewCrsrAndStmt();
      break;

     case WM_SETFOCUS:

      // pass on the focus to the edit box for user to type in SQL

      SetFocus(GetDlgItem((HWND)GetWindowLong(hWnd, GWLAPP_HDLG), IDTEXT_SQL));
      break;

     case WM_DESTROY:

      // check if the window was being destroyed while creation failed

      if (!hWnd)
         break;

      // close the window and free instance thunk for modeless dialog

      CloseQueryWindow(hWnd);
      lpDlgProc = (DLGPROC)GetWindowLong((HWND)GetWindowLong(hWnd, GWLAPP_HDLG), DWL_DLGPROC);
      DestroyWindow((HWND)GetWindowLong(hWnd, GWLAPP_HDLG));
      FreeProcInstance(lpDlgProc);
      if (hWnd == hWndActiveChild)
         hWndActiveChild = (HWND)NULL;
      break;

     default:

      return (DefMDIChildProc(hWnd, message, wParam, lParam));
   }
   return (0);
}

/*
    FUNCTION: ToolbarProc(HWND hWnd, UINT   message, WPARAM wParam, LPARAM lParam)
    COMMENTS: callback window procedure for toolbar window.
          Handle pain and mouse messages to paint the toolbar and
          provide default button behaviour for toolbar buttons.
*/

long CALLBACK ToolbarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message) {
      static HBITMAP  hbmpNewQuery;           //btn1 bitmap handle
      static HBITMAP  hbmpRunQuery;           //btn2 bitmap handle
      static RECT stNewQuery;         //btn1 rectangle
      static RECT stRunQuery;                     //btn2 rectangle
      POINT       stMousePosition;        //current mouse pos
      BOOL        bButtonPosition;        //mouse pos flag
      static BOOL bNewQueryBtnDown = FALSE;   //was btn1 down before?
      static BOOL bRunQueryBtnDown = FALSE;   //was btn2 down before?
      static int  nLastButtonDown = 0;        //Which btn was down before?

     case WM_CREATE:

      // load bitmaps for buttons
      // initialize static rectangles for button positions on toolbar
      // initialize state variable for status text display

      hbmpNewQuery = LoadBitmap(hAppInstance, BMP_NEWQUERY);
      hbmpRunQuery = LoadBitmap(hAppInstance, BMP_RUNQUERY);

      stNewQuery.left   = BTTNX;
      stNewQuery.right  = BTTNX+BTTNWIDTH+1;
      stNewQuery.top    = BTTNY;
      stNewQuery.bottom = BTTNY+BTTNHEIGHT+1;

      stRunQuery.left   = BTTNX+BTTNWIDTH+BTTNMARGIN;
      stRunQuery.right  = BTTNX+BTTNWIDTH+BTTNMARGIN+BTTNWIDTH+1;
      stRunQuery.top    = BTTNY;
      stRunQuery.bottom = BTTNY+BTTNHEIGHT+1;

      wStatusText = 0;
      break;

     case WM_DESTROY:

      // delete bitmap handles

      if (hbmpNewQuery)
         DeleteObject(hbmpNewQuery);
      if (hbmpRunQuery)
         DeleteObject(hbmpRunQuery);
      break;

     case WM_LBUTTONDOWN:

      // Check if the mouse key lies on any one of the buttons
      // if so, set state variable to reflect that button and
      // invalidate proper regions on tool & status bars for update.
      // set capture on mouse movements till the mouse key is
      // released.

      stMousePosition.x = LOWORD(lParam);
      stMousePosition.y = HIWORD(lParam);

      if (PtInRect(&stNewQuery, stMousePosition)) {
         bNewQueryBtnDown = TRUE;
         wStatusText = nLastButtonDown = IDM_NEW;
         SetCapture(hWnd);
         InvalidateRect(hWnd, &stNewQuery, TRUE);
         InvalidateRect(hWndStatusbar, &rectStatusText, TRUE);
      }
      else if (PtInRect(&stRunQuery, stMousePosition)) {
         bRunQueryBtnDown = TRUE;
         wStatusText = nLastButtonDown = IDM_QUERY;
         SetCapture(hWnd);
         InvalidateRect(hWnd, &stRunQuery, TRUE);
         InvalidateRect(hWndStatusbar, &rectStatusText, TRUE);
      }
      break;

     case WM_LBUTTONUP:

      // check if the mouse movements from key down movements
      // were captured, if so process the key release state.
      // if the key was released in the same button where it
      // was pressed, it is equivalent to a button click.

      if (hWnd != GetCapture())
         break;

      stMousePosition.x = LOWORD(lParam);
      stMousePosition.y = HIWORD(lParam);

      if (bNewQueryBtnDown && PtInRect(&stNewQuery, stMousePosition)) {
         bNewQueryBtnDown = FALSE;
         nLastButtonDown = 0;
         InvalidateRect(hWnd, &stNewQuery, TRUE);
         PostMessage(hWndFrame, WM_COMMAND, GET_WM_COMMAND_MPS(IDM_NEW, 0, 0));
         SendMessage(hWndCrsrList, CB_SHOWDROPDOWN, (WPARAM)FALSE, 0);
         SendMessage(hWndStmtList, CB_SHOWDROPDOWN, (WPARAM)FALSE, 0);
      }
      else if (bRunQueryBtnDown && PtInRect(&stRunQuery, stMousePosition)) {
         bRunQueryBtnDown = FALSE;
         nLastButtonDown = 0;
         InvalidateRect(hWnd, &stRunQuery, TRUE);
         PostMessage(hWndFrame, WM_COMMAND, GET_WM_COMMAND_MPS(IDM_QUERY, 0, 0));
         SendMessage(hWndCrsrList, CB_SHOWDROPDOWN, (WPARAM)FALSE, 0);
         SendMessage(hWndStmtList, CB_SHOWDROPDOWN, (WPARAM)FALSE, 0);
      }

      ReleaseCapture();
      wStatusText = 0;
      InvalidateRect(hWndStatusbar, &rectStatusText, TRUE);
      break;

     case WM_MOUSEMOVE:

      // process mouse movement only if the mouse key was pressed
      // down and its movements were being captured. If the mouse
      // moves outside of the currently depressed button, it needs
      // to be drawn again with normal state.

      if (hWnd != GetCapture())
         break;

      stMousePosition.x = LOWORD(lParam);
      stMousePosition.y = HIWORD(lParam);

      if (nLastButtonDown == IDM_NEW) {
         bButtonPosition = PtInRect(&stNewQuery, stMousePosition);
         if (bNewQueryBtnDown != bButtonPosition) {
            bNewQueryBtnDown = bButtonPosition;
            InvalidateRect(hWnd, &stNewQuery, TRUE);
         }
      }
      else if (nLastButtonDown == IDM_QUERY) {
         bButtonPosition = PtInRect(&stRunQuery, stMousePosition);
         if (bRunQueryBtnDown != bButtonPosition) {
            bRunQueryBtnDown = bButtonPosition;
            InvalidateRect(hWnd, &stRunQuery, TRUE);
         }
      }
      break;

     case WM_PAINT:
      {
         PAINTSTRUCT ps;     //paint structure
         RECT        rect;       //rectangle for tool bar
         HDC     hDC;        //device context handle
         int     iWidth;     //tool bar width
         int     iHeight;    //tool bar height
         HPEN        hLtGrayPen; //buttonface color pen
         HPEN        hGrayPen;   //buttonshadow color pen
         int     btnx;       //button x coordinate position

         if (!(hDC = BeginPaint(hWnd, &ps)))
            break;

         GetClientRect(hWnd, &rect);
         iWidth = rect.right;
         iHeight = rect.bottom;

         hLtGrayPen = CreatePen(PS_SOLID, 0, GetSysColor(COLOR_BTNFACE));
         hGrayPen = CreatePen(PS_SOLID, 0, GetSysColor(COLOR_BTNSHADOW));

         // draw background and border

         SelectObject(hDC, GetStockObject(LTGRAY_BRUSH));
         SelectObject(hDC, hLtGrayPen);
         Rectangle(hDC, 0, 0, iWidth, iHeight);

         SelectObject(hDC, GetStockObject(BLACK_PEN));
         MoveToEx(hDC, 0, iHeight-1, NULL);
         LineTo(hDC, iWidth, iHeight-1);

         SelectObject(hDC, GetStockObject(WHITE_PEN));
         MoveToEx(hDC, 0, 0, NULL);
         LineTo(hDC, iWidth, 0);

         // draw tool bar buttons (new query, run query)
         // check state variables to draw proper button state

         btnx = BTTNX;
         SelectObject(hDC, GetStockObject(BLACK_PEN));
         DRAWBTTNRECT(hDC, btnx, BTTNY, BTTNWIDTH, BTTNHEIGHT);
         DrawBitmap(hDC, (bNewQueryBtnDown?btnx+3:btnx+2), (bNewQueryBtnDown?BTTNY+3:BTTNY+2), hbmpNewQuery);
         SelectObject(hDC, (bNewQueryBtnDown ? hGrayPen : GetStockObject(WHITE_PEN)));
         DRAWBTTNLIFT1(hDC, btnx, BTTNY, BTTNWIDTH, BTTNHEIGHT);
         SelectObject(hDC, (bNewQueryBtnDown ? hLtGrayPen : hGrayPen));
         DRAWBTTNLIFT2(hDC, btnx, BTTNY, BTTNWIDTH, BTTNHEIGHT);

         btnx += BTTNWIDTH+BTTNMARGIN;
         SelectObject(hDC, GetStockObject(BLACK_PEN));
         DRAWBTTNRECT(hDC, btnx, BTTNY, BTTNWIDTH, BTTNHEIGHT);
         DrawBitmap(hDC, (bRunQueryBtnDown?btnx+3:btnx+2), (bRunQueryBtnDown?BTTNY+3:BTTNY+2), hbmpRunQuery);
         SelectObject(hDC, (bRunQueryBtnDown ? hGrayPen : GetStockObject(WHITE_PEN)));
         DRAWBTTNLIFT1(hDC, btnx, BTTNY, BTTNWIDTH, BTTNHEIGHT);
         SelectObject(hDC, (bRunQueryBtnDown ? hLtGrayPen : hGrayPen));
         DRAWBTTNLIFT2(hDC, btnx, BTTNY, BTTNWIDTH, BTTNHEIGHT);

         SelectObject(hDC, GetStockObject(WHITE_PEN));
         EndPaint(hWnd, &ps);

         // delete create objects

         if (hLtGrayPen)
            DeleteObject(hLtGrayPen);
         if (hGrayPen)
            DeleteObject(hGrayPen);
         break;
      }

     default:

      return (DefWindowProc(hWnd, message, wParam, lParam));
   }
   return (0);
}

/*
    FUNCTION: StatusbarProc(HWND hWnd, UINT   message, WPARAM wParam, LPARAM lParam)
    COMMENTS: callback window procedure for status bar.
          process paint messages and timer messages to update current
          state, date and time
*/

long CALLBACK StatusbarProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message) {
      static RECT DateTimeRect; // remember for frequent updates

     case WM_CREATE:
      {
         HDC hDC;        // device context
         SIZE    sizeText;       // size of status text box
         SIZE    sizeTime;       // size of time display box
         SIZE    sizeDate;       // size of date display box

         // start a timer for periodic updates to date and time display
         // find out width of status text, date and time display boxes

         SetTimer(hWnd,  (UINT)IDT_STATUSTIMER, (UINT)TIMERDELAY, NULL);

         iTimex = iDatex = 0;
         rectStatusText.left = 2;
         rectStatusText.top = 3;

         if (hDC = GetDC(hWnd)) {
            GetTextExtentPoint(hDC, STATUSNEW, strlen(STATUSNEW), &sizeText);
            GetTextExtentPoint(hDC, TIMETEXT, strlen(TIMETEXT), &sizeTime);
            GetTextExtentPoint(hDC, DATETEXT, strlen(DATETEXT), &sizeDate);
            ReleaseDC(hWnd, hDC);
            rectStatusText.right = sizeText.cx + rectStatusText.left;
            iTimex = sizeTime.cx;
            iDatex = sizeDate.cx;
         }
         break;
      }

     case WM_TIMER:

      // invalidate only the date&time area for update

      InvalidateRect(hWnd, &DateTimeRect, TRUE);
      break;

     case WM_PAINT:
      {
         HDC     hDC;            //device context
         PAINTSTRUCT ps;         //paint structure
         RECT        rect;                   //status bar rect
         int     iWidth;                 //status bar width
         int     iHeight;                //status bar height
         HPEN        hLtGrayPen;             //btnface color pen
         HPEN        hGrayPen;               //btnshadow color pen
         char        szText[MAXBUFLEN];      //text buffer for display
         time_t      tCurrentTime;           //current date&time
         struct tm   stTime;                 //date&time structure

         if (!(hDC = BeginPaint(hWnd, &ps)))
            break;

         GetClientRect(hWnd, &rect);
         iWidth = rect.right;
         iHeight = rect.bottom;
         rectStatusText.bottom = iHeight-2;

         hLtGrayPen = CreatePen(PS_SOLID, 0, GetSysColor(COLOR_BTNFACE));
         hGrayPen = CreatePen(PS_SOLID, 0, GetSysColor(COLOR_BTNSHADOW));

         // paint background and border

         SelectObject(hDC, GetStockObject(LTGRAY_BRUSH));
         SelectObject(hDC, hLtGrayPen);
         Rectangle(hDC, 0, 0, iWidth, iHeight);

         SelectObject(hDC, GetStockObject(BLACK_PEN));
         MoveToEx(hDC, 0, 0, NULL);
         LineTo(hDC, iWidth, 0);
         SelectObject(hDC, GetStockObject(WHITE_PEN));
         MoveToEx(hDC, 0, 1, NULL);
         LineTo(hDC, iWidth, 1);

         // draw text boxes for status, time and date display

         SelectObject(hDC, hGrayPen);
         MoveToEx(hDC, rectStatusText.left, rectStatusText.bottom, NULL);
         LineTo(hDC, rectStatusText.left, rectStatusText.top);
         LineTo(hDC, rectStatusText.right, rectStatusText.top);
         SelectObject(hDC, GetStockObject(WHITE_PEN));
         LineTo(hDC, rectStatusText.right, rectStatusText.bottom);
         LineTo(hDC, rectStatusText.left, rectStatusText.bottom);

         SelectObject(hDC, hGrayPen);
         MoveToEx(hDC, iWidth-2, 3, NULL);
         LineTo(hDC, iWidth-iDatex-2, 3);
         LineTo(hDC, iWidth-iDatex-2, iHeight-2);
         SelectObject(hDC, GetStockObject(WHITE_PEN));
         LineTo(hDC, iWidth-2, iHeight-2);
         LineTo(hDC, iWidth-2, 3);

         SelectObject(hDC, hGrayPen);
         MoveToEx(hDC, iWidth-iDatex-6, 3, NULL);
         LineTo(hDC, iWidth-iTimex-iDatex-6, 3);
         LineTo(hDC, iWidth-iTimex-iDatex-6, iHeight-2);
         SelectObject(hDC, GetStockObject(WHITE_PEN));
         LineTo(hDC, iWidth-iDatex-6, iHeight-2);
         LineTo(hDC, iWidth-iDatex-6, 3);

         // draw status text in the display box based on current
         // value of wStatusText global flag

         SetBkMode(hDC, TRANSPARENT);
         SetTextColor(hDC, GetSysColor(COLOR_BTNTEXT));

         switch (wStatusText) {
           case IDM_POPUPAPPSYS:

            strcpy(szText, STATUSPOPUPAPPSYS);
            break;

           case IDM_POPUPMDISYS:

            strcpy(szText, STATUSPOPUPMDISYS);
            break;

           case SC_RESTORE:

            strcpy(szText, STATUSRESTORE);
            break;

           case SC_MOVE:

            strcpy(szText, STATUSMOVE);
            break;

           case SC_SIZE:

            strcpy(szText, STATUSSIZE);
            break;

           case SC_MINIMIZE:

            strcpy(szText, STATUSMINIMIZE);
            break;

           case SC_MAXIMIZE:

            strcpy(szText, STATUSMAXIMIZE);
            break;

           case SC_CLOSE:

            strcpy(szText, STATUSCLOSE);
            break;

           case SC_NEXTWINDOW:

            strcpy(szText, STATUSNEXTWINDOW);
            break;

           case SC_PREVWINDOW:

            strcpy(szText, STATUSPREVWINDOW);
            break;

           case SC_TASKLIST:

            strcpy(szText, STATUSTASKLIST);
            break;

           case IDM_POPUPLOGIN:

            strcpy(szText, STATUSPOPUPLOGIN);
            break;

           case IDM_CONNECT:

            strcpy(szText, STATUSCONNECT);
            break;

           case IDM_DRIVERCONNECT:

            strcpy(szText, STATUSDRIVERCONNECT);
            break;

           case IDM_DISCONNECT:

            strcpy(szText, STATUSDISCONNECT);
            break;

           case IDM_EXIT:

            strcpy(szText, STATUSEXIT);
            break;

           case IDM_POPUPQUERY:

            strcpy(szText, STATUSPOPUPQUERY);
            break;

           case IDM_QUERY:

            strcpy(szText, STATUSQUERY);
            break;

           case IDM_NEW:

            strcpy(szText, STATUSNEW);
            break;

           case IDM_POPUPWINDOW:

            strcpy(szText, STATUSPOPUPWINDOW);
            break;

           case IDM_TILE:

            strcpy(szText, STATUSTILE);
            break;

           case IDM_CASCADE:

            strcpy(szText, STATUSCASCADE);
            break;

           case IDM_ICONS:

            strcpy(szText, STATUSICONS);
            break;

           case IDM_CLOSEALL:

            strcpy(szText, STATUSCLOSEALL);
            break;

           case IDM_POPUPHELP:

            strcpy(szText, STATUSPOPUPHELP);
            break;

           case IDM_APPHELP:

            strcpy(szText, STATUSAPPHELP);
            break;

           case IDM_ABOUT:

            strcpy(szText, STATUSABOUT);
            break;

           default:

            if (wStatusText >= IDM_MDICHILD)
               sprintf(szText, STATUSMDICHILD, wStatusText-IDM_MDICHILD+1);
            else
               strcpy(szText, STATUSDEFAULT);
            break;
         }

         DrawText(hDC, szText, strlen(szText), &rectStatusText, DT_LEFT);

         // get current date and time and display time in time box

         time(&tCurrentTime);
         stTime = *localtime(&tCurrentTime);
         strftime(szText, MAXBUFLEN, TIMEFORMAT, &stTime);
         rect.top = rectStatusText.top;
         rect.bottom = rectStatusText.bottom;
         rect.left  = iWidth-iTimex-iDatex-6;
         rect.right = iWidth-iDatex-6;
         DrawText(hDC, szText, strlen(szText), &rect, DT_LEFT);

         // display date in date box

         strftime(szText, MAXBUFLEN, DATEFORMAT, &stTime);
         rect.left  = iWidth-iDatex-2;
         rect.right = iWidth-2;
         DrawText(hDC, szText, strlen(szText), &rect, DT_LEFT);

         // remember the date&time rectangle to minimize painting

         DateTimeRect.left   = iWidth-iTimex-iDatex-6;
         DateTimeRect.right  = iWidth-2;
         DateTimeRect.top    = rect.top;
         DateTimeRect.bottom = rect.bottom;

         EndPaint(hWnd, &ps);

         // delete created objects

         if (hLtGrayPen)
            DeleteObject(hLtGrayPen);
         if (hGrayPen)
            DeleteObject(hGrayPen);
         break;
      }

     default:

      return (DefWindowProc(hWnd, message, wParam, lParam));
      break;
   }
   return (0);
}

/*
    FUNCTION: ConnectDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    COMMENTS: Callback dialog box procedure for connect menu command
          displays a list of available data sources, asks for user
          name and password to pass default connection parameters
          for a data source connection
*/

BOOL CALLBACK ConnectDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message) {
      HCURSOR hOldCursor; // Default Cursor Shape

     case WM_INITDIALOG:

      // display list of available data sources

      hOldCursor = SetCursor(LoadCursor((HINSTANCE)NULL, IDC_WAIT));
      DisplayDatabases(GetDlgItem(hWnd, IDCOMBO_DATASOURCE));
      SetCursor(hOldCursor);
      break;

     case WM_COMMAND:

      switch (GET_WM_COMMAND_ID(wParam, lParam)) {
        case IDOK: // make a connection using the supplied values

         hOldCursor = SetCursor(LoadCursor((HINSTANCE)NULL, IDC_WAIT));

         // check if a DSN was provided for connection

         if (SendDlgItemMessage(hWnd, IDCOMBO_DATASOURCE, WM_GETTEXTLENGTH, 0, 0))
            EndDialog(hWnd, ConnectDatabase(hWnd));
         else
            MessageBox(hWnd, NODSNERR, MOREINFO, MB_OK|MB_ICONHAND);

         SetCursor(hOldCursor);
         break;

        case IDCANCEL:

         EndDialog(hWnd, FALSE);
         break;

        default:

         return (FALSE);
         break;
      }
      break;

     default:

      return (FALSE);
      break;
   }
   return (TRUE);
}

/*
    FUNCTION: DisconnectDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    COMMENTS: Callback dialog box procedure for disconnect dialog.
          provides a list of available SQLHDBCs and a list of SQLHSTMTs
          for currently selected SQLHDBC. Allows closure of all SQLHDBCs
          and SQLHSTMTs one by one or in groups.
*/

BOOL CALLBACK DisconnectDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   switch (message) {
      static HWND hListhdbc;  //listbox that displays hdbc(s)
      static HWND hListstmt;      //listbox that displays hstmt(s)
      static HWND hPushOk;        //pushbutton to free hdbc
      static HWND hPushClose;     //pushbutton to free hstmt
      static HWND hPushCancel;    //pushbutton to close dialog

     case WM_INITDIALOG:

      // store handles for future reference

      hListhdbc = GetDlgItem(hWnd, IDLIST_HDBC);
      hListstmt = GetDlgItem(hWnd, IDLIST_STMT);
      hPushOk = GetDlgItem(hWnd, IDDISCONNECT);
      hPushCancel = GetDlgItem(hWnd, IDCANCEL);
      hPushClose = GetDlgItem(hWnd, IDCLOSE_ACTVTY);

      // display connected database handles and statements

      DisplayConnections(hListhdbc);
      DisplayQueries(hListstmt, hListhdbc, 0);

      // enable or disable pushbuttons & listboxes to match available hdbc & hstmt

      if (SendMessage(hListhdbc, LB_GETCOUNT, 0, 0)>0) {
         EnableWindow(hPushOk, TRUE);
         if (SendMessage(hListstmt, LB_GETCOUNT, 0, 0)>0) {
            EnableWindow(hPushClose, TRUE);
            SetFocus(hPushClose);
            SendMessage(hPushClose, BM_SETSTYLE, (WPARAM)BS_DEFPUSHBUTTON, TRUE);
         }
         else {
            EnableWindow(hListstmt, FALSE);
            EnableWindow(hPushClose, FALSE);
            SetFocus(hPushOk);
            SendMessage(hPushOk, BM_SETSTYLE, (WPARAM)BS_DEFPUSHBUTTON, TRUE);
         }
      }
      else {
         EnableWindow(hListhdbc, FALSE);
         EnableWindow(hListstmt, FALSE);
         EnableWindow(hPushOk, FALSE);
         SetFocus(hPushCancel);
         SendMessage(hPushCancel, BM_SETSTYLE, (WPARAM)BS_DEFPUSHBUTTON, TRUE);
      }

      // return FALSE to prevent default focus.

      return (FALSE);

     case WM_COMMAND:

      switch (GET_WM_COMMAND_ID(wParam, lParam)) {
        case IDDISCONNECT:

         // Free current hdbc, display available hdbc(s)

         FreeConnect(hListhdbc);
         SendMessage(hListstmt, LB_RESETCONTENT, 0, 0);
         DisplayConnections(hListhdbc);

         // update displayed hstmt(s) for current hdbc
         // enable or disable pushbuttons to match available
         // hdbc(s) and hstmt(s) for closure

         if (SendMessage(hListhdbc, LB_GETCOUNT, 0, 0) > 0) {
            SendMessage(hListhdbc, LB_SETCURSEL, 0, 0);
            EnableWindow(hListstmt, TRUE);
            DisplayQueries(hListstmt, hListhdbc, 0);
            if (SendMessage(hListstmt, LB_GETCOUNT, 0, 0)>0) {
               EnableWindow(hPushClose, TRUE);
               SetFocus(hPushClose);
               SendMessage(hPushClose, BM_SETSTYLE, (WPARAM)BS_DEFPUSHBUTTON, TRUE);
            }
            else {
               EnableWindow(hListstmt, FALSE);
               EnableWindow(hPushClose, FALSE);
               SetFocus(hPushOk);
               SendMessage(hPushOk, BM_SETSTYLE, (WPARAM)BS_DEFPUSHBUTTON, TRUE);
            }
         }
         else {
            EnableWindow(hListhdbc, FALSE);
            EnableWindow(hPushOk, FALSE);
            EnableWindow(hPushClose, FALSE);
            SetFocus(hPushCancel);
            SendMessage(hPushCancel, BM_SETSTYLE, (WPARAM)BS_DEFPUSHBUTTON, TRUE);
         }
         break;

        case IDCANCEL:

         // close dialog

         EndDialog(hWnd, FALSE);
         break;

        case IDCLOSE_ACTVTY:
         {
            int nIndex; // counter to search for selected hstmt(s)

            // go through all displayed hstmt(s) and free all highlighted ones

            for (nIndex = (int)SendMessage(hListstmt, LB_GETCOUNT, 0, 0)-1;
                 nIndex >= 0; nIndex--)
               if (SendMessage(hListstmt, LB_GETSEL, nIndex, 0))
                  FreeQuery(hListstmt, hListhdbc, nIndex);

            // reset both hdbc(s) and hstmt(s) display

            nIndex = (int)SendMessage(hListhdbc, LB_GETCURSEL, 0, 0);
            DisplayConnections(hListhdbc);
            SendMessage(hListhdbc, LB_SETCURSEL, nIndex, 0);
            DisplayQueries(hListstmt, hListhdbc, nIndex);

            // enable or disable pushbuttons to match available
            // hdbc(s) and hstmt(s) for closure

            if (SendMessage(hListstmt, LB_GETCOUNT, 0, 0)>0) {
               EnableWindow(hPushClose, TRUE);
               SetFocus(hPushClose);
               SendMessage(hPushClose, BM_SETSTYLE, (WPARAM)BS_DEFPUSHBUTTON, TRUE);
            }
            else {
               EnableWindow(hListstmt, FALSE);
               EnableWindow(hPushClose, FALSE);
               SetFocus(hPushOk);
               SendMessage(hPushOk, BM_SETSTYLE, (WPARAM)BS_DEFPUSHBUTTON, TRUE);
            }
            break;
         }

        case IDLIST_HDBC:

         // If the current selection in hdbc(s) has changed
         // update the list of hstmt(s) to match the new hdbc

         if (GET_WM_COMMAND_CMD(wParam, lParam) == LBN_SELCHANGE)
            DisplayQueries(hListstmt, hListhdbc,
                           (UINT)SendMessage(GET_WM_COMMAND_HWND(wParam, lParam), LB_GETCURSEL, 0, 0));

         // Enable or disable hstmt listbox and close pushbutton accordingly

         EnableWindow(hListstmt, (SendMessage(hListstmt, LB_GETCOUNT, 0, 0)>0));
         EnableWindow(hPushClose, (SendMessage(hListstmt, LB_GETCOUNT, 0, 0)>0));
         break;

        default:

         return (FALSE);
      }
      break;

     default:

      return (FALSE);
   }

   return (TRUE);
}

/*
    FUNCTION: AboutDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    COMMENTS: Callback dialog box procedure for About dialog box
          displays the about information and closes upon selection of
          ok button
*/

BOOL CALLBACK AboutDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   if (message == WM_COMMAND) {
      EndDialog(hWnd, TRUE);
      return (TRUE);
   }
   else
      return (FALSE);
}

/*
    FUNCTION: MDIChildDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    COMMENTS: Callback dialog box procedure for modeless child dialog box
          in each MDI Child Window. This dialog box simply processes
          the tab messages (by default) to allow switching from edit
          control (SQL Text) to list box control (Query results).
*/

BOOL CALLBACK MDIChildDlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   return (FALSE);
}

/*
    FUNCTION: DrawBitmap(HDC hDC, int iLeft, int iTop, HBITMAP hBitmap
    COMMENTS: Draws a bitmap on given Device context with given bitmap
          handle at given location
*/

VOID FAR PASCAL DrawBitmap(HDC hDC, int iLeft, int iTop, HBITMAP hBitmap)
{
   HDC hMemDC;     // Device Context in Memory
   POINT   stPoint;        // point structure for conversion from device to logical units
   BITMAP  stBitmap;
   HGDIOBJ hObject;

   // create a compatible device context in memory and select the bitmap
   // in to it.

   if (!(hMemDC = CreateCompatibleDC(hDC))) return;

   hObject = SelectObject(hMemDC, hBitmap);
   SetMapMode(hMemDC, GetMapMode(hDC));

   // Get bitmap size and convert it to logical units from device units.

   GetObject(hBitmap, sizeof(BITMAP), &stBitmap);
   stPoint.x = stBitmap.bmWidth;
   stPoint.y = stBitmap.bmHeight;
   DPtoLP(hDC, &stPoint, 1);

   // bit block transfer the bitmap from memory device context to given
   // device context at specified location

   BitBlt(hDC, iLeft, iTop, stPoint.x, stPoint.y, hMemDC, 0, 0, SRCCOPY);

   // select original object in the memory device context and destroy it

   SelectObject(hMemDC, hObject);
   DeleteDC(hMemDC);
}

/********************************************* END OF FILE **************************************************/
