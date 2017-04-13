
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright 1996-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

// CFILER.C
#include "cfiler.h"
#include "time.h"

HANDLE		  		ghModule;                                    
HANDLE  			ghDrvThread = NULL;
HWND    			ghwndMain = NULL;                      
HWND    			ghwndDrives;              
HWND    			ghwndDrv;
HWND    			ghFocusWnd;                   
HFONT   			ghFont;
HMENU				ghMenu;                        
BOOL                gfDrvWndOrient = SIDE_BY_SIDE,
                    gfKeepCommandWin = FALSE;
DRVCHILDINFO        gDrvChildInfo;
LPDINFO             glpDrives = (LPDINFO)0;    		
CRITICAL_SECTION    gDrvCS;              		     		
                                             
extern LPTSTR 		lpDriveStrings;
extern ALG_ID		AlgidEncrypt;
extern ALG_ID		AlgidSign;
extern CHAR			sPass[BUF_SIZE];
extern TCHAR		szPassName[BUF_SIZE];

int WINAPI WinMain(HINSTANCE hInstance, 
				   HINSTANCE hPrevInstance, 
				   LPSTR lpCmdLine, 
				   INT nCmdShow) {
    MSG    msg;
    HANDLE hAccel;

    ghModule = hInstance;

    if (!InitializeApp()) {
        ErrorMsg(TEXT("WinMain: InitializeApp failed."));
        return 0;
    }

    ShowWindow(ghwndMain, nCmdShow);

    if (!(hAccel = LoadAccelerators (ghModule, MAKEINTRESOURCE(ACCEL_ID))))
        ErrorMsg(TEXT("WinMain: LoadAccelerators failed."));

    while (GetMessage(&msg, NULL, 0, 0)) {
        if( !TranslateAccelerator(ghwndMain, hAccel, &msg) ) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 1;

    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(hPrevInstance);
}

BOOL InitializeApp(void)
{
    WNDCLASS wc;
	HWND FirsthWnd, FirstChildhWnd;

	if (FirsthWnd = FindWindow("CRYPTFILERClass", NULL))
	{
	   // Found another running application with the same class name.
	   // Therefore, one instance is already running.

	   FirstChildhWnd = GetLastActivePopup(FirsthWnd);
	   BringWindowToTop(FirsthWnd);         // bring main window to top

	   if (FirsthWnd != FirstChildhWnd)
	      BringWindowToTop(FirstChildhWnd); // a pop-up window is active
	                                        // bring it to the top too

	   return FALSE;                        // do not run second instance
	}

    srand(time(0));
       
    lstrcpy(szPassName, TEXT("\0"));
    
    wc.style            = 0;
    wc.lpfnWndProc      = (WNDPROC)MainWndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra   	= 0;
    wc.hInstance        = ghModule;
    wc.hIcon            = LoadIcon(ghModule, MAKEINTRESOURCE(UI_CRYPTFILERICON));
    wc.hCursor          = 0;
    wc.hbrBackground    = (HBRUSH)(COLOR_APPWORKSPACE);
    wc.lpszMenuName     = TEXT("CRYPTFILERMenu");
    wc.lpszClassName    = TEXT("CRYPTFILERClass");

    if (!RegisterClass(&wc)) {
		ErrorMsg(TEXT("InitializeApp: RegisterClass failed."));
    	return FALSE;
	}

    wc.lpfnWndProc  = DrvWndProc;
    wc.hIcon        = NULL;
    wc.lpszMenuName = NULL;
    wc.lpszClassName    = TEXT("DrvClass");

    if (!RegisterClass(&wc)) {
        ErrorMsg(TEXT("InitializeApp: RegisterClass failed."));
        return FALSE;
    }
    
    wc.style        = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc  = DriveBarProc;
    wc.hbrBackground    = (HBRUSH)(COLOR_BTNSHADOW);
    wc.lpszClassName    = TEXT("DriveBarClass");

    if (!RegisterClass(&wc)) {
        ErrorMsg(TEXT("InitializeApp: RegisterClass failed."));
        return FALSE;
	}

    wc.style        = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc  = TextWndProc;
    wc.hbrBackground    = (HBRUSH)(COLOR_INACTIVECAPTION);
    wc.lpszClassName    = TEXT("TextClass");

    if (!RegisterClass(&wc)) {
        ErrorMsg(TEXT("InitializeApp: RegisterClass failed."));
        return FALSE;
	}

    ghMenu = LoadMenu(ghModule, TEXT("CRYPTFILERMenu"));

    if (!ghMenu)
		return FALSE;    
    
    AlgidEncrypt = CALG_RC2;
	AlgidSign = CALG_MD4;
	
	ghwndMain = CreateWindow(TEXT("CRYPTFILERClass"),
                             TEXT("CRYPTFILER"),
                             WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT,
                             CW_USEDEFAULT,
                             MAIN_WIDTH,
                             MAIN_HEIGHT,
                             HWND_DESKTOP,
                             ghMenu,
                             ghModule,
                             NULL);

    if (!ghwndMain) {
		ErrorMsg(TEXT("InitializeApp: CreateWindow failed."));
		return FALSE;
	}

	if (!MakeHashDirectory()) {
		ErrorMsg(TEXT("InitializeApp: MakeHashDirectory failed."));
		return FALSE;
	}

	return TRUE;
}

LRESULT WINAPI MainWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    INT bRet;
    
    switch (message) {
    	case WM_CREATE: { 
        LOGFONT    lf;
        HDC        hDC;
        HGDIOBJ    hOldFont;
		HGDIOBJ	   hFont;
        TEXTMETRIC tm;
        DWORD dwThreadID;
		DWORD dwLastError = GetLastError();
        LPCINFO lpCInfo;
        	
        //
        // Initialize drive list and Set Directory critical sections.
        //
        InitializeCriticalSection(&gDrvCS);
       
        ghDrvThread = CreateThread(NULL, 0,
                                   (LPTHREAD_START_ROUTINE)EnumDrives,
                                   (LPVOID)&glpDrives,
                                   0, &dwThreadID);
		
		if (!ghDrvThread) {
			ErrorMsg(TEXT("MainWndProc: CreateThread failed."));
			return 0;
		}       
        
        //
        // Compute default application font by creating a bold version
        //   of the system default icon font.
        //
        if (!SystemParametersInfo(SPI_GETICONTITLELOGFONT, 
        						  sizeof(lf), 
        						  (PVOID) &lf, 
        						  FALSE)) {
			
			ErrorMsg(TEXT("MainWndProc: SystemParametersInfo failed."));
			return 0;
		}

        hDC = GetDC(hwnd);

        if (!hDC) {
			ErrorMsg(TEXT("MainWndProc: GetDC failed."));
			return 0;
		}
        
        //
        // this is the height for 8 point size font in pixels.
        //  (1 point = 1/72 in.)
        //
        lf.lfHeight = 8 * GetDeviceCaps(hDC, LOGPIXELSY) / 72;
        lf.lfWeight = BOLD_FONT;

        ghFont = CreateFontIndirect(&lf);
		if (!ghFont) {
			ErrorMsg(TEXT("MainWndProc: CreateFontIndirect failed."));
			return 0;
		}

        hOldFont = SelectObject(hDC, ghFont);

        if (!hOldFont || (HGDIOBJ)hOldFont == (HGDIOBJ)GDI_ERROR) {
			ErrorMsg(TEXT("MainWndProc: SelectObject failed."));
			return 0;
		}

        if (!GetTextMetrics(hDC, &tm)) {
			ErrorMsg(TEXT("MainWndProc: GetTextMetrics failed."));
			return 0;
		}

        if (hOldFont) {
			hFont = SelectObject(hDC, hOldFont);
 			if (!hFont || (HGDIOBJ)hFont == (HGDIOBJ)GDI_ERROR) {
 				ErrorMsg(TEXT("MainWndProc: SelectObject failed."));
 				return 0;
 			}
 		} 
        
        if (!ReleaseDC(hwnd, hDC)) {
			ErrorMsg(TEXT("MainWndProc: ReleaseDC failed.\r\n"));
			return 0;
		}

        //
        // Create Drive windows
        //
        gDrvChildInfo.hParent = hwnd;
      
  		ghwndDrv = CreateWindow(TEXT("DrvClass"), NULL,
                                 WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
                                 0, 0, 0, 0,
                                 hwnd, (HMENU) 1, ghModule,
                                 (LPVOID)&gDrvChildInfo);

		if (!ghwndDrv) {
			ErrorMsg(TEXT("MainWndProc: CreateWindow failed."));
			dwLastError = GetLastError();
			return 0;
		}

        ghwndDrv = ghwndDrv;

        //
        // Set initial focus to Drive Child 1's Directory listbox.
        //
        lpCInfo = (LPCINFO)GetWindowLong(ghwndDrv, GWL_USERDATA);

        if (!lpCInfo) {
        	ErrorMsg(TEXT("MainWndProc: WM_CREATE: lpCInfo is NULL."));
        	return 0;
        }
        
        ghFocusWnd = lpCInfo->hDirLB;

        if (!ghFocusWnd) {
        	ErrorMsg(TEXT("MainWndProc: GetWindowLong failed."));
			return 0;
		}
        	
        // Create DriveBar, FunctionBar and Command windows
        
        ghwndDrives = CreateWindow(TEXT("DriveBarClass"), NULL,
                                    WS_CHILD | WS_VISIBLE | WS_BORDER,
                                   0, 0, 0, 0,
                                   hwnd, (HMENU) 3, ghModule,
                                   (LPVOID)NULL);

        if (!ghwndDrives) {
        	ErrorMsg(TEXT("MainWndProc: CreateWindow failed."));
        	return 0;
        }

        UpdateDrivesMenu(ghMenu, ghDrvThread);
      	      	
      	return 1;
      }

      case WM_COMMAND:{

        //
        // The menu Identifiers for the drives are (potentially)
        // MM_DRIVE_NUM + 0 thru MM_DRIVE_NUM + 25. They all go to the
        // same case, so we will put the Menu ID in lParam, and
        // MM_DRIVE_NUM in LOWORD(wParam).
        //
        if( (LOWORD(wParam) - MM_DRIVE_NUM) <= 25 &&
            (LOWORD(wParam) - MM_DRIVE_NUM) >= 0 ){
            lParam = LOWORD(wParam);
            wParam = MM_DRIVE_NUM;
        }

        switch (LOWORD(wParam)) {
            //
            // If a drive is selected from the Drives menu, or clicked
            //  on the drives toolbar, the currently active child will
            //  switch to this drive. Message 'unconverted' (see top of
            //  WM_COMMAND case), and sent to DriveBarProc
            //
            case MM_DRIVE_NUM:{

                SendMessage(ghwndDrives, WM_COMMAND,
                            (WPARAM)lParam, (LPARAM)NULL);
                return 1;
            }

            //
            // Passes these WM_COMMAND messages to the appropriate active child
            //  window proc for processing
            //
            case MM_TAB:
            case MM_ESCAPE:
            case MM_ENCRYPT_DECRYPT:
			case MM_SIGN:
			case MM_VERIFY:
            case MM_EXPAND:{

                SendMessage(ghwndDrv, WM_COMMAND, wParam, lParam);
                return 1;
            }

            case MM_EXIT:{
                SendMessage(ghwndMain, WM_CLOSE, wParam, lParam);
                return 1;
            }

            //
            // Creates the drive enumeration thread to re-enumerate the
            //   available drives in the main menu.  Also sends a refresh
            //   to the active drive child, and repaints the window.
            //
            case MM_REFRESH: {
                DWORD   dwThreadID;

                //
                // Initialize/Refresh Drives linked list
                //

                if( WaitForSingleObject(ghDrvThread, 0) != WAIT_TIMEOUT ){

                    //
                    // Close previous Drive Thread handle before creating new handle.
                    //
                    CloseHandle( ghDrvThread );

                    ghDrvThread = CreateThread(NULL, 0,
                                           (LPTHREAD_START_ROUTINE)EnumDrives,
                                           (LPVOID)&glpDrives,
                                           0, &dwThreadID);

                    //
                    // Refresh active child, drive toolbar, and drives menu
                    //
                    SendMessage(ghwndDrv, WM_COMMAND, wParam, lParam);
                    SendMessage(ghwndDrives, WM_COMMAND, wParam, lParam);
                    UpdateDrivesMenu(ghMenu, ghDrvThread);

                    //
                    // Mark all for repaint
                    //
                    InvalidateRect(hwnd,NULL,TRUE);

                }
                else
                    MessageBeep(MB_ICONASTERISK);

                return 1;
            }

            //
            // Swaps the directory and file list boxes of the active drv child.
            //
            case MM_SWAP:{
                LPCINFO lpCInfo;
                RECT    rect;

                lpCInfo = (LPCINFO)GetWindowLong(ghwndDrv, GWL_USERDATA);

                if (!lpCInfo) {
                	ErrorMsg(TEXT("MainWndProc: MM_SWAP: lpCInfo is NULL."));
                	return FALSE;
                }
                
                //
                // Switch the flag which indicates which side the Directory
                //  LB is on.  This is used by the WM_SIZE case of DrvWndProc.
                //
                lpCInfo->fDirLeft = !lpCInfo->fDirLeft;

                //
                // Send size message with current size to active child,
                //   in order to redraw the listboxes.
                //
                if( !GetClientRect( ghwndDrv, &rect ) )
                    return 0;

                SendMessage( ghwndDrv, WM_SIZE, SIZENORMAL,
                             MAKELONG( rect.right - rect.left,
                                       rect.bottom - rect.top) );
                return 1;
            }

            case MM_KEEPCMD:{

                gfKeepCommandWin = !gfKeepCommandWin;

                if( gfKeepCommandWin )
                    CheckMenuItem( ghMenu, MM_KEEPCMD,
                                    MF_BYCOMMAND | MF_CHECKED);
                else
                    CheckMenuItem( ghMenu, MM_KEEPCMD,
                                MF_BYCOMMAND | MF_UNCHECKED);
            }
            break;

            //
            // Toggles the relative Drive Child orientaion between
            // Over/under and side/side.  gfDrvWndOrient is a flag checked
            // by WM_SIZE to size Drv children
            //
            case MM_ORIENT:{
                RECT    rect;

                if( gfDrvWndOrient == OVER_UNDER )
                    gfDrvWndOrient = SIDE_BY_SIDE;
                else
                    gfDrvWndOrient = OVER_UNDER;

                //
                // Send size message with current size to self (main window),
                //   in order to redraw the Drv children.
                //
                if( !GetClientRect( hwnd, &rect ) )
                    return 0;

                SendMessage( hwnd, WM_SIZE, SIZENORMAL,
                             MAKELONG( rect.right - rect.left,
                                       rect.bottom - rect.top) );

                InvalidateRect(ghwndDrv,NULL,TRUE);
           
                return 1;
            }

            //
            // Launches the About DialogBox.
            //
            case MM_ABOUT:{
                if (DialogBox(ghModule, 
                			  TEXT("AboutBox"), 
                			  ghwndMain, 
                			  (DLGPROC)AboutProc) == -1)
                        
                	ErrorMsg(TEXT("Main: About Dialog Creation Error!"));
                return 1;
            }

            case ID_HELP:
        		if (!WinHelp(hwnd, TEXT("cf.hlp"), HELP_CONTENTS, 0L)) {
					ErrorMsg(TEXT("MainWndProc: WinHelp failed."));
					return 0;
				}
			
        		return 1;

			case ID_ENCRYPTION_ALGORITHM:
				bRet = DialogBox(ghModule, 
							     TEXT("ENCRYPTION_ALGORITHM"), 
							     ghwndMain, 
							     EncryptDlgProc);
				if (bRet == TRUE)
					InvalidateRect(ghwndMain, NULL, TRUE);
				else if (bRet == FALSE)
					return FALSE;
				return 1; 

			case ID_SIGNATURE_ALGORITHM:
				bRet = DialogBox(ghModule, TEXT("HASH_ALGORITHM"), ghwndMain, HashDlgProc);
				if (bRet == TRUE)
					InvalidateRect(ghwndMain, NULL, TRUE);
				else if (bRet == FALSE)
					return FALSE;
				return 1;
		
			case MM_PASS:
				AlgidEncrypt = 0;
				if (!GetPass(ghwndMain) || strlen(sPass) == 0) {
					AlgidEncrypt = CALG_RC2;
					return FALSE;
				}
				return 1;
					
			case ID_HIDE: {
				DWORD cm;
				
				cm = CheckMenuItem(ghMenu, ID_HIDE, MF_CHECKED);

				if (cm == MF_CHECKED) {
					if (ShowSignatures())
						CheckMenuItem(ghMenu, ID_HIDE, MF_UNCHECKED);
				}
				else if (cm == MF_UNCHECKED) {
					if (HideSignatures())
						CheckMenuItem(ghMenu, ID_HIDE, MF_CHECKED);
				}
				else {
					ErrorMsg(TEXT("ID_HIDE: CheckMenuItem failed."));
					return 0;
				}

				return 1;
			}
			
			default:
                return(DefWindowProc(hwnd, message, wParam, lParam));
        }
        return 1;
      }
      //
      // Whenever the window is resized, its children have to be
      //  resized accordingly.  The GetWindowLong values are the height
      //  of the windows queried by this function, and are set in the
      //  WM_CREATE cases of their respective WNDPROCs.
      //
      case WM_SIZE:{
        int DrvWndHeight;

        //
        // Always put the drives toolbar at the top of the frame window
        //
        MoveWindow(ghwndDrives,
           0,
           0,
           LOWORD(lParam),
           GetWindowLong(ghwndDrives, GWL_USERDATA),
           TRUE);

        //
        // Always size the Drive Children between the Drives and Command
        // windows. The width is set so that borders overlap.
        //

        if( gfDrvWndOrient == OVER_UNDER ){

            DrvWndHeight = ( HIWORD(lParam) -
                           GetWindowLong(ghwndDrives, GWL_USERDATA));

            MoveWindow(ghwndDrv,
                       -1,
                       GetWindowLong(ghwndDrives, GWL_USERDATA),
                       (LOWORD(lParam) + 2),
                       DrvWndHeight,
                       TRUE);
        }
        else{

            DrvWndHeight = HIWORD(lParam) -
                           GetWindowLong(ghwndDrives, GWL_USERDATA);

            MoveWindow(ghwndDrv,
                        -1,
                        GetWindowLong(ghwndDrives, GWL_USERDATA),
                        (LOWORD(lParam)/2 + 1)*2,
                        DrvWndHeight,
                        TRUE);
        }

        return 1;
      }

      case WM_DESTROY: {
        Logoff(hwnd);
       
	   	DeleteHashDirectory();

        free(lpDriveStrings);
		
		DestroyMenu(ghMenu);
        
        SendMessage(ghwndDrv, WM_CLOSE, 0, 0);
        
        //
        // Close last drive thread handle,
        //  the created font, and the Drive list critical section.
        //
        CloseHandle( ghDrvThread );

        DeleteObject(ghFont);

        DeleteCriticalSection(&gDrvCS);

        PostQuitMessage(0);
	
	    return 1;
      }

      default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
}

LRESULT WINAPI AboutProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
      case WM_INITDIALOG:{
        return TRUE;
      }

      case WM_COMMAND:{
        if (wParam == IDOK)
            EndDialog(hDlg, wParam);
        break;
      }
    }

    return FALSE;

    UNREFERENCED_PARAMETER(lParam);
    UNREFERENCED_PARAMETER(hDlg);
}

/************************************************************************\
* DriveBarProc()														
*																				
* Drive Toolbar procedure for displaying available drive Icons.			
*  A bitmap button is displayed corresponding to the drive type of the	
*  given drive, with the drive letter alongside.						
*  ghwndDrives is the global handle assoc. w/ this window procedure.	
\***********************************************************************/

LRESULT WINAPI DriveBarProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HBITMAP  hDrvBmp[NUM_BITMAPS];
    static HBRUSH   hBrush;         // background brush
    static int      nDrvEntryWidth; // width of button/letter entry
    static int      yVal;           // y value in toolbar for top left of bmp
    static LPBINFO  lpDrvButtonRoot;
    static int      nActiveDrvIndex;

    switch (message)
    {
        case WM_CREATE:{
            HDC        hDC;
            HGDIOBJ    hOldFont;
            TEXTMETRIC tm;
            LONG       lHeight;


            lpDrvButtonRoot = NULL;

            //
            // Load drive button bitmaps.
            //
            for(yVal = 0; yVal < NUM_BITMAPS; yVal++)
                hDrvBmp[yVal] = LoadBitmap( ghModule,
                                      MAKEINTRESOURCE(UB_BMP_MARKER + yVal) );

            //
            // Sets background color of Toolbar non-modal dialog children.
            //
            hBrush = CreateSolidBrush(GetSysColor(COLOR_MENU));

            hDC = GetDC(hwnd);

            hOldFont = SelectObject(hDC, ghFont);
            GetTextMetrics(hDC, &tm);

            //
            // base the height of the window on size of text
            //
            lHeight = tm.tmHeight + GetSystemMetrics(SM_CYBORDER) + 6;

            //
            // saved the window height, drive button entry width
            //   and button y starting value for later reference
            //
            SetWindowLong(hwnd, GWL_USERDATA, lHeight);

            //
            // Width of one button entry = spacing, button, sm. space,
            //   drive letter, spacing.
            //
            nDrvEntryWidth = DRIVE_BITMAP_SPACING + DRIVE_BITMAP_WIDTH +
                             DRIVE_LETTER_SPACING + tm.tmAveCharWidth +
                             DRIVE_BITMAP_SPACING;

            //
            // Center bitmaps (by height) in drive toolbar.
            //
            yVal = (lHeight - DRIVE_BITMAP_HEIGHT)/2;

            SelectObject(hDC, hOldFont);
            ReleaseDC(hwnd, hDC);

            SendMessage(hwnd, WM_COMMAND, (WPARAM)MM_REFRESH, (LPARAM)NULL);

            break;
        }

        case WM_COMMAND:{
            //
            // The button Identifiers for the drives are (potentially)
            // MM_DRIVE_NUM + 0 thru MM_DRIVE_NUM + 25. They all go to the
            // same case, so we will put the Menu ID in lParam, and
            // MM_DRIVE_NUM in LOWORD(wParam).
            //
            if( (LOWORD(wParam) - MM_DRIVE_NUM) <= 25 &&
                (LOWORD(wParam) - MM_DRIVE_NUM) >= 0 ){
                lParam = LOWORD(wParam);
                wParam = MM_DRIVE_NUM;
            }

            switch( LOWORD(wParam) ){
              case MM_REFRESH:{

                LPDINFO lpWalk;
                LPBINFO lpBWalk, lpBHold;
                LPCINFO lpCInfo;
                int     xVal = 0;
				int		nCount = MM_DRIVE_NUM;
				               
                lpCInfo = (LPCINFO)GetWindowLong(ghwndDrv, GWL_USERDATA);

                if (!lpCInfo) {
                	ErrorMsg(TEXT("DriveBarProc: MM_REFRESH: lpCInfo is NULL."));
                	return FALSE;
                }
                
                //
                // Wait for Drive Thread to complete, if necessary.
                //
                WaitForSingleObject(ghDrvThread, INFINITE);
                EnterCriticalSection(&gDrvCS);

                //
                // Traverse DRVINFO linked list, creating drive buttons and
                //   allocating corresp. structures as necessary.
                //
                lpWalk = glpDrives;
                lpBWalk = lpDrvButtonRoot;

                while( lpWalk != NULL ){
                	if( lpBWalk == NULL ){ //If at the end of the button list

                        // Allocate a LPBINFO (button) structure
						
                        lpBWalk = (LPBINFO)malloc((DWORD)sizeof(BINFO));
                        
                        if (!lpBWalk) {
							ErrorMsg(TEXT("DriveBarProc: MM_REFRESH: malloc failed."));
							return 0;
						}
						
                        lpBWalk->next = NULL;

                        // Create a button window
                        lpBWalk->hButton = (HANDLE)CreateWindow(TEXT("BUTTON"),
                                                 lpWalk->DriveName,
                                                 WS_CHILD | WS_VISIBLE |
                                                 BS_OWNERDRAW ,
                                                 xVal + DRIVE_BITMAP_SPACING,
                                                 yVal,
                                                 DRIVE_BITMAP_WIDTH,
                                                 DRIVE_BITMAP_HEIGHT,
                                                 hwnd,
                                                 (HMENU)nCount,
                                                 ghModule,
                                                 NULL);
						
                        // Insert structure into list
                        if( lpDrvButtonRoot == NULL)
                            lpDrvButtonRoot = lpBHold = lpBWalk;
                        else{
                            lpBHold->next = lpBWalk;
                            lpBWalk->next = NULL;
                        }

                    }

                    // An LPBINFO (button) structure exists: now initialize

                    // Set Title of Button (Drive Letter)

                    SetWindowText(lpBWalk->hButton, lpWalk->DriveName);

                    // Set Child Window ID for Button
                    // SetMenu(lpBWalk->hButton, (HMENU)nCount);

                    // Determine button up/down status
                    if( lpCInfo->lpDriveInfo == lpWalk ){
                        nActiveDrvIndex = nCount;
                        lpBWalk->fButtonDown = TRUE;
                    }
                    else
                        lpBWalk->fButtonDown = FALSE;

                    // Set a pointer to the corresponding drive in Drive list
                    lpBWalk->lpDrive = lpWalk;

                    nCount++;
                    xVal += nDrvEntryWidth;
                    lpBHold = lpBWalk;
                    lpBWalk = lpBWalk->next;

                    lpWalk = lpWalk->next;
                
                }

                LeaveCriticalSection(&gDrvCS);

                //
                // Free any remaining button windows.
                //
                while( lpBWalk != NULL ){
                    // NULL out new end of list
                    lpBHold->next = NULL;

                    // Assign pointer to doomed node
                    lpBHold = lpBWalk;
                    lpBWalk = lpBWalk->next;

                    // Free doomed node resources
                    if( !DestroyWindow(lpBHold->hButton) )
                        ErrorMsg(TEXT("DriveBarProc: Drive Button Destroy Error"));

                    free(lpBHold);
                }

                SendMessage(hwnd, WM_PAINT, (WPARAM)NULL, (LPARAM)NULL);
                				
				break;
              }


              //
              // switches the drive button to the newly active drv child's
              //   current drive.  Called by WM_MOUSEACTIVATE in DrvWndProc,
              //   as well as ChangeDrive.
              //   lParam contains the drive linked list pointer of the active
              //   drv child's LPCINFO struct.
              //
              case MM_ACTIVEDRV:{
                LPBINFO lpBWalk = lpDrvButtonRoot;
                int     nCount = 0;

                //
                // 'unpush' old active button
                //
                for( nCount = MM_DRIVE_NUM; nCount < nActiveDrvIndex; nCount++)
                    lpBWalk = lpBWalk->next;
                lpBWalk->fButtonDown = FALSE;

                InvalidateRect(lpBWalk->hButton, NULL, FALSE);

                //
                // change active drive to new before redrawing old.
                //  'push' new active button
                //
                lpBWalk = lpDrvButtonRoot;
                nCount = MM_DRIVE_NUM;
                while( lpBWalk->lpDrive != (LPDINFO)lParam){
                    lpBWalk = lpBWalk->next;
                    nCount++;
                }

                nActiveDrvIndex = nCount;

                lpBWalk->fButtonDown = TRUE;

                InvalidateRect(lpBWalk->hButton, NULL, FALSE);

                break;
              }

              //
              // Changes drive of active child.  ButtonID in lParam.
              //
              case MM_DRIVE_NUM:{

                LPBINFO lpBWalk = lpDrvButtonRoot;
                int     nCount = 0;
                TCHAR    szDrvBuff[DIRECTORY_STRING_SIZE];

                //
                // if drive chosen is already current drive, leave.
                //
                if( nActiveDrvIndex == (int)lParam )
                    break;

                //
                // unpush' old active button
                //
                for( nCount = MM_DRIVE_NUM; nCount < nActiveDrvIndex; nCount++)
                    lpBWalk = lpBWalk->next;
                lpBWalk->fButtonDown = FALSE;

                //
                // change active drive to new before redrawing old.
                //
                nActiveDrvIndex = (int)lParam;

                InvalidateRect(lpBWalk->hButton, NULL, FALSE);

                //
                // 'push' new active button
                //
                lpBWalk = lpDrvButtonRoot;

                for( nCount = MM_DRIVE_NUM; nCount < nActiveDrvIndex; nCount++)
                    lpBWalk = lpBWalk->next;
                lpBWalk->fButtonDown = TRUE;

                InvalidateRect(lpBWalk->hButton, NULL, FALSE);

                GetWindowText(lpBWalk->hButton, szDrvBuff,
                              DIRECTORY_STRING_SIZE);

                if( !ChangeDrive(szDrvBuff, (DWORD)nActiveDrvIndex) ){
                    ErrorMsg(TEXT("Error changing Drives.\r\n"));
                    return 0;
                }

                break;
              }
            }
            return 1;
        }

        //
        // Sent by all created buttons for initialization purposes.
        //
        case WM_MEASUREITEM:{
            LPMEASUREITEMSTRUCT lpMIS;

            lpMIS = (LPMEASUREITEMSTRUCT)lParam;

            lpMIS->CtlType = ODT_BUTTON;
            lpMIS->CtlID = (UINT)wParam;
            lpMIS->itemWidth = DRIVE_BITMAP_WIDTH;
            lpMIS->itemHeight = DRIVE_BITMAP_HEIGHT;

            return 1;
        }

        //
        // Sent by owner draw drive buttons when needing redrawing.
        //
        case WM_DRAWITEM:{
            LPBINFO lpBWalk = lpDrvButtonRoot;
            int     nCount;
            int     nBmpIndex;
            HDC     hDC;
            HDC     hCompatDC;
            HGDIOBJ hOldBitmap;
            TCHAR    szDrvBuff[DIRECTORY_STRING_SIZE];
            LPDRAWITEMSTRUCT    lpDIS;

            lpDIS = (LPDRAWITEMSTRUCT)lParam;

            for( nCount = MM_DRIVE_NUM; nCount < (int)wParam; nCount++)
                lpBWalk = lpBWalk->next;

            //
            // If not the current selected button, handle button stuff.
            //
            if( (int)wParam != nActiveDrvIndex ){
                //
                // mousebutton is down...
                //
                if( lpDIS->itemAction & ODA_SELECT ){
                    //
                    // left button region, 'unpush' button
                    //
                    if( lpDIS->itemState == (UINT)ODS_FOCUS )
                        lpBWalk->fButtonDown = FALSE;
                    //
                    // clicked on a button, draw 'pushed' button
                    //
                    if( lpDIS->itemState == (UINT)(ODS_SELECTED | ODS_FOCUS))
                        lpBWalk->fButtonDown = TRUE;
                }
            }

            //
            // draw current state of button.
            //
            GetWindowText(lpDIS->hwndItem, szDrvBuff,
                          DIRECTORY_STRING_SIZE);

            szDrvBuff[1] = TEXT('\0');

            hCompatDC = CreateCompatibleDC(lpDIS->hDC);
            hOldBitmap = CreateCompatibleBitmap(hCompatDC,
                                                DRIVE_BITMAP_WIDTH,
                                                DRIVE_BITMAP_HEIGHT);

            nBmpIndex = GetDriveBitmap(lpBWalk);

            SelectObject( hCompatDC, hDrvBmp[nBmpIndex] );

            if( !hOldBitmap )
                ErrorMsg(TEXT("WM_DRAWITEM: SelectObject failure."));

            if( !BitBlt(lpDIS->hDC, lpDIS->rcItem.left, lpDIS->rcItem.top,
                   DRIVE_BITMAP_WIDTH,
                   DRIVE_BITMAP_HEIGHT,
                   hCompatDC, 0, 0, SRCCOPY) )
                ErrorMsg(TEXT("WM_DRAWITEM: BitBlt failure."));


            SelectObject( hCompatDC, hOldBitmap);
            DeleteDC(hCompatDC);

            hDC = GetDC(hwnd);
            SetBkMode(hDC, OPAQUE);
            SetTextColor(hDC, GetSysColor(COLOR_MENUTEXT) );
            SetBkColor(hDC, GetSysColor(COLOR_MENU) );

            TextOut(hDC,
                    ((int)(wParam - MM_DRIVE_NUM) * nDrvEntryWidth) +
                        DRIVE_BITMAP_SPACING + DRIVE_BITMAP_WIDTH +
                        DRIVE_LETTER_SPACING,
                    (GetSystemMetrics(SM_CYBORDER) + 6)/2,
                    szDrvBuff, 1);

            SetBkMode(hDC, OPAQUE);

            ReleaseDC(hwnd, hDC);
			
			DeleteObject(hOldBitmap);

            break;
        }


        case WM_PAINT:{
            HDC     hCompatDC;
            RECT     rc;
            PAINTSTRUCT ps;

            //
            // Paint btnshadow background.
            //
            GetClientRect(hwnd, &rc);

            BeginPaint(hwnd, &ps);

            hCompatDC = CreateCompatibleDC(ps.hdc);
            FillRect(ps.hdc, &rc, hBrush);

            EndPaint(hwnd, &ps);

            DeleteDC(hCompatDC);
            
            return(TRUE);
        }

        case WM_DESTROY:{
            LPBINFO p, q;
            LPDINFO p1, q1;

            DeleteObject(hBrush);

            for (p = lpDrvButtonRoot; p; p = q) {
				q = p->next;
				free(p);
			}
            
            for (p1 = glpDrives; p1; p1 = q1) {
            	q1 = p1->next;
            	free(p1);
            	p1 = NULL;
            }
            
            for(yVal = 0; yVal < NUM_BITMAPS; yVal++)
                DeleteObject(hDrvBmp[yVal]);

            break;
        }
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

/************************************************************************\
* GetDriveBitmap()														
*																		
* Determines the appropriate index into the drive button bitmap array	
* (hDrvBmp[]), given a pointer to a drive info structure (LPDINFO)	
*																		
* lpWalk          -   pointer to LPDINFO structure.					
* lpCurrentDrv    -   pointer to current drive of active child.		
\***********************************************************************/

int GetDriveBitmap(LPBINFO lpBWalk)
{
    int nBmpIndex;

    EnterCriticalSection(&gDrvCS);

    switch( lpBWalk->lpDrive->DriveType ){
        case DRIVE_REMOVABLE:{
          nBmpIndex = UB_FLOPPY1 - UB_BMP_MARKER;
          break;
        }

        case DRIVE_REMOTE:{
          nBmpIndex = UB_REMOTE1 - UB_BMP_MARKER;
            break;
        }

        case DRIVE_CDROM:{
          nBmpIndex = UB_CD1 - UB_BMP_MARKER;
            break;
        }

        case DRIVE_FIXED:
        default:{
          nBmpIndex = UB_FIXED1 - UB_BMP_MARKER;
            break;
        }
    }

    LeaveCriticalSection(&gDrvCS);

    if( lpBWalk->fButtonDown == TRUE )
        nBmpIndex++;

    return(nBmpIndex);
}

/********************************************************************************\
* ChangeDrive()
*
*   Changes the current drive of the child.  Called by the MM_DRIVE_NUM
*   cases in MainWndProc and DriveBarProc.  This is caused by choosing a
*   Drive menu item or selecting a drive button from the drive toolbar.
*
*   lpszDriveName -   points to a buffer containing the name of the drive
*   DriveID       -   points to the ID of the Menu item or button, which
*                         corresponds to the index into the drives linked list
*                         of the new drive.
\********************************************************************************/

BOOL ChangeDrive(LPTSTR lpszDriveName, DWORD DriveIndex)
{
    LPCINFO     lpCInfo;
    LPDINFO     lpWalk;
    DWORD       dwLoop;
    UINT        nDriveType;

    //
    // Retrieve active child handle.
    //
    if( (ghwndDrv != ghwndDrv) ){
        ErrorMsg(TEXT("A Drive Window Must be Active."));
        return 0;
    }

    //
    // Retrieving the child window's DRVCHILDINFO data
    //
    lpCInfo = (LPCINFO)GetWindowLong(ghwndDrv, GWL_USERDATA);

    if (!lpCInfo) {
    	ErrorMsg(TEXT("ChangeDrive: lpCInfo is NULL."));
    	return FALSE;
    }
    
    //
    // Enter Drive list critical section
    //
    EnterCriticalSection(&gDrvCS);

    //
    // if removable drive, check for existing media.
    //
    nDriveType = GetDriveType(lpszDriveName);
    if( nDriveType == DRIVE_REMOVABLE ||
        nDriveType == DRIVE_CDROM ){
        dwLoop = (DWORD)IDOK;

        while( !CheckRM(lpszDriveName) && (dwLoop == (DWORD)IDOK) ){

           dwLoop = (DWORD)MessageBox(ghwndMain,
                           TEXT("CRYPTFILER: Insert some media in drive"),
                           lpszDriveName, MB_OKCANCEL);
        }

        if( dwLoop == (DWORD)IDCANCEL ){
            SendMessage(ghwndDrives, WM_COMMAND, MM_ACTIVEDRV,
                        (LPARAM)lpCInfo->lpDriveInfo);
        LeaveCriticalSection(&gDrvCS);
            return 0;
        }
    }

    //
    // set lpDriveInfo member to associated drive struct.
    //
    lpWalk = glpDrives;
    for( dwLoop = 0; dwLoop < DriveIndex - MM_DRIVE_NUM;
         dwLoop++)
         lpWalk = lpWalk->next;

    lpCInfo->lpDriveInfo = lpWalk;

    lstrcpy(lpCInfo->CaptionBarText, lpWalk->DriveName);

    LeaveCriticalSection(&gDrvCS);

    //
    // This will terminate any currently running drive thread.
    //
    SendMessage(ghwndDrv, WM_COMMAND, MM_ESCAPE, (LPARAM)0);
    lpCInfo->fEscape = FALSE;

    //
    // enact the drive change.
    //
    PostMessage(ghwndDrv, WM_COMMAND, MM_REFRESH, (LPARAM)0);

    return 1;
}

/********************************************************************************\
* UpdateDrivesMenu()
*
* Adds current drives from the glpDrives linked list to the TEXT('Drives') menu
*
* Input: hDrivesMenu - handle to TEXT('Drives') Menu
*        hThread    - used to wait for drives thread to terminate
\********************************************************************************/

BOOL UpdateDrivesMenu(HMENU hMenu, HANDLE hThread)
{
    HMENU   hDrivesMenu;
    int     NumMenuItems;
    DWORD   dwLoop;
    LPDINFO lpWalk;

    //
    // Remove list of drive menu items from Drive menu, if any.
    //
    hDrivesMenu = GetSubMenu( hMenu, DRIVE_MENU_NUM);
    if(!hDrivesMenu){
        ErrorMsg(TEXT("UpdateDrivesMenu: GetSubMenu error."));
        return FALSE;
    }

    if((NumMenuItems = GetMenuItemCount(hDrivesMenu)) == -1) {
        ErrorMsg(TEXT("Main Refresh: Menu Item Count Error."));
		return FALSE;
	}

    //
    // Delete previous menu items.
    //
    for( dwLoop = 0; dwLoop < (DWORD)NumMenuItems; dwLoop++)
        if(!DeleteMenu(hDrivesMenu, 0, MF_BYPOSITION)){
            ErrorMsg(TEXT("Main Refresh: Menu Item Delete Error."));
            return FALSE;
        }

    //
    // Wait for Enumdrv Thread to terminate, and
    //   enter drive list critical section
    //
    if (WaitForSingleObject(hThread, INFINITE) == WAIT_FAILED) {
		ErrorMsg(TEXT("UpdateDrivesMenu: WaitForSingleObject failed."));
		return FALSE;
	}

    EnterCriticalSection(&gDrvCS);

    //
    // Fill drive menu from glpDrives linked list
    //
    NumMenuItems = 0;
    lpWalk = glpDrives;

    while(lpWalk != NULL){
        if(!InsertMenu(hDrivesMenu, NumMenuItems, MF_STRING | MF_BYPOSITION 
        			| MF_ENABLED, MM_DRIVE_NUM + NumMenuItems, lpWalk->DriveName)) {
            ErrorMsg(TEXT("Main Refresh: Menu Item Insert Error."));
			return FALSE;
		}
        NumMenuItems++;
        lpWalk = lpWalk->next;
    }

    LeaveCriticalSection(&gDrvCS);

    return TRUE;
}

/***************************************************************\
* ErrorMsg()
*
*   Displays a Message Box with a given error message.
*
\***************************************************************/

void ErrorMsg(LPTSTR szMsg)
{
    TCHAR szHold[DIRECTORY_STRING_SIZE + 1];

    lstrcpy( szHold, szMsg );
    lstrcat( szHold, TEXT("\n") );

   	OutputDebugString(szHold);
}
