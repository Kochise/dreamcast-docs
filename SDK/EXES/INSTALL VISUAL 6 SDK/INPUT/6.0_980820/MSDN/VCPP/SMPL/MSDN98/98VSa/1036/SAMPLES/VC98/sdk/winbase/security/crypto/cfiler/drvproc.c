
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright 1996-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

// DRVPROC.C

#include "cfiler.h"

extern HANDLE   			ghModule;
extern HANDLE				ghwndMain;
extern HFONT    			ghFont;
extern HANDLE   			ghDrvThread;
extern HANDLE   			ghMenu;
extern HWND	 		    	ghwndDrives;
extern HWND 	 	 		ghwndDrv;
extern HWND     			ghFocusWnd;
extern LPDINFO  			glpDrives;
extern CRITICAL_SECTION    	gDrvCS;   

/**********************************************************************\
* DrawItem()
*
* in parmeters
* lpdis - Information the owner window must have to determine how 
* to paint the owner-draw listbox
*
* Calls DrawText to output a string with the right color in the
* rectangle contained in lpdis
\**********************************************************************/

VOID APIENTRY DrawItem(LPDRAWITEMSTRUCT lpdis) {
		COLORREF crOldColor;
		TCHAR	szFile[256];
		INT	 i, nLen;
		TCHAR szBuf[275];
		TEXTMETRIC tm;
		RECT rc;

		if (!lpdis) {
			ErrorMsg(TEXT("DrawEntireItem: lpdis is NULL."));
			return;
		}
		
		GetTextMetrics(lpdis->hDC, &tm);
		
	  	// Filenames such as Q&A.DOC should look correct.
	  	
	  	ReplaceEscapeCharacters((LPTSTR)lpdis->itemData, szBuf);
				
		nLen = lstrlen(szBuf);
		
		if (nLen > HEADER_SIZE) {
			ErrorMsg(TEXT("fnKey has been Destroyed!"));
			crOldColor = SetTextColor(lpdis->hDC, RGB(140, 140, 140));
			CopyRect(&rc, &lpdis->rcItem);
       		rc.left += 1;
       		lstrcpy(szFile, TEXT("RecoverMe"));
       		DrawText(lpdis->hDC, szFile, lstrlen(szFile), (LPRECT)&rc, DT_LEFT);
          	SetTextColor(lpdis->hDC, crOldColor);
			return;
		}
		
		if (szBuf[0] == TEXT('|')) {
			
			// This is an encrypted file. Select gray as the color.
			
			crOldColor = SetTextColor(lpdis->hDC, RGB(140, 140, 140));
			
			for (i = 0; i < nLen - 1; i++)
				szFile[i] = szBuf[i + 1];

			szFile[i] = TEXT('\0');
		}
		else if (szBuf[0] == TEXT('>')) {
			
			// This is an encrypted and signed file.
			
			crOldColor = SetTextColor(lpdis->hDC, RGB(255, 140, 140));
			
			for (i = 0; i < nLen - 1; i++)
				szFile[i] = szBuf[i + 1];

			szFile[i] = TEXT('\0');
		}
		else if (szBuf[0] == TEXT(';')) {
			
			// This is a signed only file.
			
			crOldColor = SetTextColor(lpdis->hDC, RGB(255, 0, 0));
			
			for (i = 0; i < nLen - 1; i++)
				szFile[i] = szBuf[i + 1];

			szFile[i] = TEXT('\0');
		}
		else 
			lstrcpy(szFile, szBuf);
              	
       	CopyRect(&rc, &lpdis->rcItem);
       	
       	rc.left += 1;
       	
       	DrawText(lpdis->hDC, szFile, lstrlen(szFile), (LPRECT)&rc, DT_LEFT);
     	
		if (szBuf[0] == TEXT('|') || szBuf[0] == TEXT('>') || szBuf[0] == TEXT(';'))
	       	SetTextColor(lpdis->hDC, crOldColor);
		
       	return;
}

/**********************************************************************\
* HandleSelectionState()
*
* in parmeters
* lpdis - Information the owner window must have to determine how 
* to paint the owner-draw listbox
*
* purpose:
* Handles a change in an item selection state. This function must
* check the current background color for the rectangle contained
* in the DRAWITEMSTRUCT pointer, lpdis. The background color and
* text color must be changed appropriately.
\**********************************************************************/

VOID APIENTRY HandleSelectionState(LPDRAWITEMSTRUCT lpdis)
{
     if (!lpdis) {
     	ErrorMsg(TEXT("HandleSelectionState: lpdis is NULL."));
     	return;
     }
     
     if (lpdis->itemState & ODS_SELECTED) {
	 	if (GetBkColor(lpdis->hDC) == GetSysColor(COLOR_HIGHLIGHT)) {
			return;
		}
		else {
			SetTextColor(lpdis->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
			SetBkColor(lpdis->hDC, GetSysColor(COLOR_HIGHLIGHT));
			DrawItem(lpdis);
			return;
		}
	}
	else {
		if (GetBkColor(lpdis->hDC) != GetSysColor(COLOR_WINDOW)) {
			return;
		}
		else {
			SetTextColor(lpdis->hDC, GetSysColor(COLOR_WINDOWTEXT));
			SetBkColor(lpdis->hDC, GetSysColor(COLOR_WINDOW));
			DrawItem(lpdis);
			return;
		}
	}
}

/**********************************************************************\
* DrawEntireItem()
*
* in parmeters
* lpdis - Information the owner window must have to determine how 
* to paint the owner-draw listbox
*
* Sets the background color and the text color and calls DrawItem()
\**********************************************************************/

VOID APIENTRY DrawEntireItem(LPDRAWITEMSTRUCT lpdis)
{
        if (!lpdis) {
        	ErrorMsg(TEXT("DrawEntireItem: lpdis is NULL."));
        	return;
        }
        
        SetBkColor(lpdis->hDC, GetSysColor(COLOR_WINDOW));
        SetTextColor(lpdis->hDC, GetSysColor(COLOR_WINDOWTEXT));

        DrawItem(lpdis);
         
	    __try {
        	if (!lpdis) {
        		ErrorMsg(TEXT("DrawEntireItem: lpdis is NULL."));
        		return;
        	}
        	
        	if (!lpdis->itemData) {
        		ErrorMsg(TEXT("DrawEntireItem: lpdis->itemData is NULL."));
        		return;
        	}
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
        	ErrorMsg(TEXT("DrawEntireItem: lpdis is BOGUS."));
        	return;
        }
        
        /* Draw or erase appropriate frames */
        __try {
        	HandleSelectionState(lpdis);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			ErrorMsg(TEXT("DrawEntireItem: Attempt to call HandleSelectionState raised an exception."));
			return;
		}
}

LRESULT  WINAPI DrvWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    LPDRAWITEMSTRUCT lpdis;
    LPMEASUREITEMSTRUCT lpmis;
    LPCOMPAREITEMSTRUCT lpcis;
    
    DWORD dwDirStyle = WS_BORDER | WS_CHILD | WS_VISIBLE |
                              LBS_NOINTEGRALHEIGHT | LBS_NOTIFY |
                              LBS_HASSTRINGS | LBS_WANTKEYBOARDINPUT |
                              LBS_DISABLENOSCROLL | WS_HSCROLL |
                              WS_VSCROLL |LBS_USETABSTOPS;

    DWORD dwFileStyle = WS_BORDER | WS_CHILD | WS_VISIBLE |
                              LBS_NOINTEGRALHEIGHT | LBS_NOTIFY |
                           	  LBS_OWNERDRAWFIXED | LBS_WANTKEYBOARDINPUT |
                              LBS_DISABLENOSCROLL | WS_HSCROLL |
                              LBS_EXTENDEDSEL | LBS_MULTIPLESEL |
                              LBS_MULTICOLUMN | LBS_SORT;

    switch (message){

        //
        // Creates the text and listbox windows for this Drv child and
        //  saves its handle in the per Drv child DRVCHILDINFO data structure.
        //
        case WM_CREATE: {
            LPCINFO lpCInfo;

            DWORD   dwLoop;

            LPDINFO lpWalk;

            LONG    lTabs = LISTBOX_TAB_SIZE;
			
            //
            // Initialize DRVCHILDINFO structure
            //
            lpCInfo = (LPCINFO) ((LPCREATESTRUCT) lParam)->lpCreateParams;

            if (!lpCInfo) {
            	ErrorMsg(TEXT("DrvWndProc: lpCInfo is NULL."));
            	return 0;
         	}
         	
         	lpCInfo->hwnd = hwnd;

            // Create text window
            lpCInfo->hTextWnd = CreateWindow(TEXT("TextClass"), NULL,
                                   	SS_LEFT | WS_CHILD | WS_VISIBLE | WS_BORDER,
                                    0, 0, 0, 0,
                                    lpCInfo->hwnd,
                                    (HMENU) TEXT_WINDOW_ID,
                                    ghModule,
                                    NULL);

            if (!lpCInfo->hTextWnd) {
            	ErrorMsg(TEXT("DrvWndProc: WM_CREATE: CreateWindow failed."));
            	return 0;
            }
            
            // Create Directory and File List boxes
            lpCInfo->hDirLB = CreateWindow(TEXT("LISTBOX"), NULL,
                                    dwDirStyle,
                                    0, 0, 0, 0,
                                    lpCInfo->hwnd,
                                    (HMENU) LISTDIR_ID,
                                    ghModule,
                                    NULL);

            if (!lpCInfo->hDirLB) {
            	ErrorMsg(TEXT("DrvWndProc: WM_CREATE: CreateWindow failed."));
            	return 0;
            }
            
            // Create directory listbox string table.
            
            lpCInfo->DirTable = TableNew();

			if (!lpCInfo->DirTable) {
				ErrorMsg(TEXT("WM_CREATE: TableNew failed."));
				return 0;
			}
            
            lpCInfo->hFileLB = CreateWindow(TEXT("LISTBOX"), NULL,
                                    dwFileStyle,
                                    0, 0, 0, 0,
                                    lpCInfo->hwnd,
                                    (HMENU) LISTFILE_ID,
                                    ghModule,
                                    NULL);
            
            if (!lpCInfo->hFileLB) {
            	ErrorMsg(TEXT("DrvWndProc: WM_CREATE: CreateWindow failed."));
            	return 0;
            }
            
            lpCInfo->FileTable = TableNew();
            
            if (!lpCInfo->FileTable) {
            	ErrorMsg(TEXT("WM_CREATE: TableNew failed."));
            	return 0;
            }
            
	        if (!Logon(hwnd)) {
				MessageBox(hwnd, TEXT("DrvWndProc: WM_CREATE: Logon failed. Terminating application."), NULL, MB_OK);
				exit(1);
				return 0;
			}
		
			//
            // fDirLeft indicates whether the Directory ListBox defaults to
            //  the left side of each of the two drive windows.
            // fDirExpand indicates whether the Directory Listbox defaults
            //  to full expansion.
            //
            lpCInfo->fDirLeft = TRUE;
            lpCInfo->fDirExpand = FALSE;
            lpCInfo->fSuicide = FALSE;

            //
            // Create Mutex associated with each list box
            //
            lpCInfo->hDirMutex = CreateMutex(NULL, FALSE, NULL);
            lpCInfo->hFileMutex = CreateMutex(NULL, FALSE, NULL);

            //
            // Associate window with the current directory LPDINFO structure
            //   from the Drives linked list
            //
                            
            dwLoop = GetCurrentDirectory( DIRECTORY_STRING_SIZE,
                                          lpCInfo->CaptionBarText);
            
            CharUpper(lpCInfo->CaptionBarText);

            WaitForSingleObject(ghDrvThread, INFINITE);
            EnterCriticalSection(&gDrvCS);

            lpWalk = glpDrives;

            if(dwLoop && dwLoop <= DIRECTORY_STRING_SIZE) {
            	while(lpWalk && tolower(lpWalk->DriveName[0]) 
            					!= tolower((lpCInfo->CaptionBarText)[0]))
                    lpWalk = lpWalk->next;

                if( !lpWalk ){
                    ErrorMsg(TEXT("Drive Child Create: Drive list failure."));
                    LeaveCriticalSection(&gDrvCS);
                    return(-1);
                }
            }
            else{
                ErrorMsg(TEXT("Drive Child Create: GetCurrentDir failure."));
                LeaveCriticalSection(&gDrvCS);
                return(-1);
            }

            LeaveCriticalSection(&gDrvCS);

            lpCInfo->lpDriveInfo = lpWalk;

            //
            // Save the handle to DRVCHILDINFO in our window structure
            //
            SetWindowLong(hwnd, GWL_USERDATA, (LONG) lpCInfo);

            //
            // Initialize child windows
            //
            if( !SendMessage(lpCInfo->hDirLB, LB_SETTABSTOPS, (WPARAM)1,
                            (LPARAM)&lTabs) )
                ErrorMsg(TEXT("Drv window Create: Set tab stop failure."));


            //
            // Set default font.
            //
            SendMessage(lpCInfo->hDirLB, WM_SETFONT, (WPARAM)ghFont, (LPARAM)FALSE);
            SendMessage(lpCInfo->hFileLB, WM_SETFONT, (WPARAM)ghFont, (LPARAM)FALSE);

            SendMessage(hwnd, WM_COMMAND, (WPARAM)MM_REFRESH, (LPARAM)NULL);

            return 1;
        }

        case WM_COMMAND: {
          static LPCINFO     lpCInfo;
          static SELECTINFO  Select;

          //
          // Retrieving this child window's DRVCHILDINFO data for displaying
          //    messages in the text window
          //
          lpCInfo = (LPCINFO) GetWindowLong(hwnd, GWL_USERDATA);

          if (!lpCInfo) {
          	ErrorMsg(TEXT("DrvWndProc: WM_COMMAND: lpCInfo is NULL."));
          	return FALSE;
          }
          
          switch (LOWORD(wParam)){

            //
            //  Clears the selection in the active window.
            //  Sent when user hits escape key.
            //
            case MM_ESCAPE:{
                //
                // If there is a directory expand in process, kill the
                //  thread, and leave the listbox in a semi-expanded state.
                //  Else, clear file selection, and switch to command window.
                //
                if( WaitForSingleObject( lpCInfo->hDirMutex, MUTEX_TIMEOUT)
                        == WAIT_TIMEOUT ){
                    lpCInfo->fSuicide = TRUE;
                    lpCInfo->fEscape = TRUE;
                }
                else
                    ReleaseMutex( lpCInfo->hDirMutex );

                SendMessage(lpCInfo->hFileLB, LB_SETCURSEL, (WPARAM)-1,
                               (LPARAM)0);

                return 1;
            }

            case MM_ENCRYPT_DECRYPT: {
                if( ghFocusWnd == lpCInfo->hFileLB ) {
			    RunListBoxItem(lpCInfo, ENCRYPT_DECRYPT);
                }
                else
                    if( ghFocusWnd == lpCInfo->hDirLB ){
                        if( !PostMessage(hwnd, WM_COMMAND, MM_FILLDIR,
                                         (LPARAM)0) ){
                            ErrorMsg(TEXT("MM_ENCRYPT_DECRYPT: Filldir failure."));
                            return 0;
                        }
                    }
    
                    return 1;
            }

			case MM_SIGN: {
				if( ghFocusWnd == lpCInfo->hFileLB ) {
			    RunListBoxItem(lpCInfo, SIGN);
                }
                else
                    if( ghFocusWnd == lpCInfo->hDirLB ){
                        if( !PostMessage(hwnd, WM_COMMAND, MM_FILLDIR,
                                         (LPARAM)0) ){
                            ErrorMsg(TEXT("MM_SIGN: Filldir failure."));
                            return 0;
                        }
                    }
             
                return 1;
            }
		
			case MM_VERIFY: {
				if( ghFocusWnd == lpCInfo->hFileLB ) {
			    RunListBoxItem(lpCInfo, VERIFY);
                }
                else
                    if( ghFocusWnd == lpCInfo->hDirLB ){
                        if( !PostMessage(hwnd, WM_COMMAND, MM_FILLDIR,
                                         (LPARAM)0) ){
                            ErrorMsg(TEXT("MM_VERIFY: Filldir failure."));
                            return 0;
                        }
                    }

                return 1;
            }
   
            case MM_EXPAND:{

                lpCInfo->fDirExpand = !lpCInfo->fDirExpand;

                if( lpCInfo->fDirExpand )
                    CheckMenuItem( ghMenu, MM_EXPAND,
                                    MF_BYCOMMAND | MF_CHECKED);
                else
                    CheckMenuItem( ghMenu, MM_EXPAND,
                                MF_BYCOMMAND | MF_UNCHECKED);

                if( !SendMessage( (HWND)lpCInfo->hwnd, WM_COMMAND,
                                 (WPARAM)MM_REFRESH, (LPARAM)0 ) ){
                    ErrorMsg(TEXT("MM_EXPAND:  MM_REFRESH failure."));
                    return 0;
                }
                return 1;
            }

            //
            // refreshes contents of directory and file ListBoxes.
            //
            case MM_REFRESH:{

                DWORD   dwThreadID;
                INT i, N;

                if( WaitForSingleObject( lpCInfo->hDirMutex, MUTEX_TIMEOUT)
                        == WAIT_TIMEOUT )
                    //
                    // If the full directory expand has been cancled, kill the
                    //  existing thread.
                    //
                    if( !lpCInfo->fDirExpand && !lpCInfo->fSuicide){
                        lpCInfo->fSuicide = TRUE;
                        return 1;
                    }
                    else{
                        return 0;
                    }

                // if set, clear the expand dir. user abort (escape key) flag.
                if( lpCInfo->fEscape ){
                    lpCInfo->fEscape = FALSE;
                    ReleaseMutex( lpCInfo->hDirMutex );
                    return 1;
                }

                // At this point, the Dir LB mutex has been grabbed.

                // Clear directory LB.  If expand flag is set, expand all
                //  directories.  Refill File LB.
                //
                        
                N = GetSize(lpCInfo->DirTable);
                                	   	
			   	for (i = 0; i < N; i++)
			   		TableRemove(lpCInfo->DirTable, 0);
			   	
			   	if( SendMessage( lpCInfo->hDirLB, LB_RESETCONTENT,
                                 (WPARAM)0, (LPARAM)0 ) < 0 ){
                    ErrorMsg(TEXT("Refresh Drv window: Reset Dir LB content failure."));
                    ReleaseMutex( lpCInfo->hDirMutex );
                    return 0;
                }

     			//
                // This call puts the default root entry back into the empty
                //  LB.  Set suicide flag to false to ensure it will complete.
                //
                lpCInfo->fSuicide = FALSE;
                ExpDir( lpCInfo );

                //
                // All the Dir LB work is done.  Release Dir LB Mutex.
                //
                ReleaseMutex( lpCInfo->hDirMutex );

                if( lpCInfo->fDirExpand ){

                    CloseHandle( lpCInfo->hDirThread );

                    lpCInfo->hDirThread = CreateThread( NULL, 0,
                                  (LPTHREAD_START_ROUTINE)FullExpand,
                                  (LPVOID)lpCInfo, 0, &dwThreadID);

                    if( !lpCInfo->hDirThread ){
                        ErrorMsg(TEXT("MM_REFRESH: FullExpand CreateThread failure."));
                        return 0;
                    }
                }
                else
                    ExpDir( lpCInfo );

                if( !PostMessage(hwnd, WM_COMMAND, MM_FILLFILE,
                                 (LPARAM)0) ){
                    ErrorMsg(TEXT("Refresh Drv window: Fillfile failure."));
                    return 0;
                }

                return 1;
            }

            //
            //  Fill listbox in lParam with directory from Drv child's drive.
            //  Sent by MM_REFRESH.
            //
            //  lParam == 0
            //
            case MM_FILLDIR:{

                DWORD   dwThreadID;

                lpCInfo->fSuicide = FALSE;

                CloseHandle( lpCInfo->hDirThread );

                lpCInfo->hDirThread = CreateThread( NULL, 0,
                              (LPTHREAD_START_ROUTINE)ExpDir,
                              (LPVOID)lpCInfo, 0, &dwThreadID);

                if( !(lpCInfo->hDirThread) ){
                    ErrorMsg(TEXT("MM_FILLDIR: ExpDir CreateThread failure."));
                    return 0;
                }

                return 1;
            }

            //
            //  Fill listbox in lParam with files from current directory.
            //  Sent by MM_REFRESH & LBN_DBLCLK in DrvWndProc.
            //
            //  lParam == 0
            //
            case MM_FILLFILE:
                ghFocusWnd = lpCInfo->hFileLB;
                return FillFile(lpCInfo, hwnd);
				break;

            //
            // The following WM_COMMAND messages are sent by the listboxes
            //
            // HIWORD(wParam) = LB notification message
            // lParam = LB window handle
            //
            case LISTFILE_ID:{
              switch( HIWORD(wParam) ){
                //
                // In case of double click on a directory, expand the file
                // Listbox. if on a file name, run or edit file.
                //
                case LBN_DBLCLK:{
                    RunListBoxItem(lpCInfo, ENCRYPT_DECRYPT);
                    return 1;
                }
                break;

                case LBN_SETFOCUS:{
                    ghFocusWnd = lpCInfo->hFileLB;
                }
                break;

                default:
                    return 1;
              }
            } // LISTFILE_ID
            break;

            //
            // Notification from the Directory ListBox
            //
            case LISTDIR_ID:{
              switch( HIWORD(wParam) ){

                case LBN_SETFOCUS:{
                    ghFocusWnd = lpCInfo->hDirLB;
                }
                break;

                //
                // Expand subdirectories in dir listbox
                //
                case LBN_DBLCLK:{

                    if( !PostMessage(hwnd, WM_COMMAND, MM_FILLDIR,
                                     (LPARAM)0) ){
                        ErrorMsg(TEXT("Dir ListBox Notify: Filldir failure."));
                        return 0;
                    }
                    return 1;
                }
                break;

                case LBN_SELCHANGE:{
                    //
                    // for the Directory LB, fill the
                    // corresp. File LB with items in the newly selected dir.
                    //
                    LONG lIndex;

                    if( WaitForSingleObject( lpCInfo->hDirMutex, MUTEX_TIMEOUT)
                            == WAIT_TIMEOUT ){
                        ErrorMsg(TEXT("Dir LB Notify: Dir LB Mutex Timeout."));
                        return 0;
                    }

                    //
                    // Retrieve selected (careted) item.
                    //
                    lIndex = SendMessage( (HWND)lParam, LB_GETCARETINDEX,
                                        (WPARAM)NULL, (LPARAM)NULL );

                    if( !ConstructDirName(lpCInfo, lIndex,
                                          lpCInfo->CaptionBarText) ){
                        ErrorMsg(TEXT("Dir LB Notify:  ConstructDirName failure."));
                        ReleaseMutex( lpCInfo->hDirMutex );
                        return 0;
                    }

                    ReleaseMutex( lpCInfo->hDirMutex );

                    if( !PostMessage(hwnd, WM_COMMAND, MM_FILLFILE,
                                     (LPARAM)0) ){
                        ErrorMsg(TEXT("Dir ListBox Notify: Fillfile failure."));
                        return 0;
                    }
                } // LBN_SELCHANGE
                break;

                default:
                    return 1;
              }
            } //  LISTDIR_ID
            break;

            default:
               return 1;
          }
        }
        break;

        //
        // Whenever the Drv child window is resized, its children has to be
        //  resized accordingly.  The GetWindowLong GWL_USERDATA values
        //  contain the height of the windows queried, set in their respective
        //  WM_CREATE cases.
        //
        case WM_SIZE: {
            LPCINFO     lpCInfo;

            int         nListHeight,
                        nListWidth;

            HWND        hLeftLB,
                        hRightLB;

            //
            // First, get the text window's handle from the per Drv child
            //  DRVCHILDINFO data structure
            //
            lpCInfo = (LPCINFO)GetWindowLong(hwnd, GWL_USERDATA);

            if (!lpCInfo) {
            	ErrorMsg(TEXT("DrvWndProc: WM_SIZE: lpCInfo is NULL."));
            	return 0;
            }
            
            nListHeight = HIWORD(lParam) -
                          GetWindowLong(lpCInfo->hTextWnd, GWL_USERDATA)
                          - LIST_BORDER * 2;

            nListWidth = (LOWORD(lParam) - LIST_BORDER) / 2 - LIST_BORDER;

            //
            // Always, put the text window at the top of the Drv window.
            // Increasing sides and bottom extents by 1 to overlap border
            //   with Drv child border
            //
            MoveWindow(lpCInfo->hTextWnd,
                       -1,
                       0,
                       LOWORD(lParam) + 2,
                       GetWindowLong(lpCInfo->hTextWnd, GWL_USERDATA) + 1,
                       TRUE);

            if( lpCInfo->fDirLeft ){
                hLeftLB = lpCInfo->hDirLB;
                hRightLB = lpCInfo->hFileLB;
            }
            else{
                hLeftLB = lpCInfo->hFileLB;
                hRightLB = lpCInfo->hDirLB;
            }

            MoveWindow(hLeftLB,
                       LIST_BORDER,
                       GetWindowLong(lpCInfo->hTextWnd, GWL_USERDATA) + 1
                         + LIST_BORDER,
                       nListWidth,
                       nListHeight,
                       TRUE);

            MoveWindow(hRightLB,
                       (LOWORD(lParam) + LIST_BORDER) / 2,
                       GetWindowLong(lpCInfo->hTextWnd, GWL_USERDATA) + 1
                         + LIST_BORDER,
                       nListWidth,
                       nListHeight,
                       TRUE);

        break;
        }

        case WM_PARENTNOTIFY:{
            LPCINFO lpCInfo;

            if(wParam == WM_LBUTTONDOWN){
                lpCInfo = (LPCINFO) GetWindowLong(hwnd, GWL_USERDATA);
                if(lpCInfo == NULL){
                    ErrorMsg(TEXT("Drv child: Parent notify failure."));
                    return 1;
                }
                if(HIWORD(wParam) == LISTDIR_ID)
                    SetFocus(lpCInfo->hDirLB);
                else
                    if(HIWORD(wParam) == LISTFILE_ID)
                        SetFocus(lpCInfo->hFileLB);
                    else
                        if(HIWORD(wParam) == TEXT_WINDOW_ID)
                            SetFocus(lpCInfo->hTextWnd);
            }

            break;
        }

        //
        // Same as MainWndProc's MM_ACTIVEDRV case.  The initial PostMessage
        //   is so the currently active Drv child will not process the message
        //   until it is no longer in focus.
        //
        case WM_MOUSEACTIVATE:{
            LPCINFO lpCInfo;

            PostMessage(ghwndDrv, WM_COMMAND, (WPARAM)MM_TOGGLE,
                        (LPARAM)NULL);
            ghwndDrv = hwnd;
            SendMessage(ghwndDrv, WM_COMMAND, (WPARAM)MM_TOGGLE,
                        (LPARAM)NULL);

            lpCInfo = (LPCINFO) GetWindowLong(hwnd, GWL_USERDATA);
            
            if (!lpCInfo) {
            	ErrorMsg(TEXT("DrvWndProc: lpCInfo is NULL."));
            	return FALSE;
            }
            
            SendMessage(ghwndDrives, WM_COMMAND, MM_ACTIVEDRV,
                        (LPARAM)lpCInfo->lpDriveInfo);

            break;
        }

        //
        // Free the DRVCHILDINFO data that associates with this window
        //  also, reset the menu.
        //
        case WM_CLOSE: {
            LPCINFO lpCInfo;
			
            lpCInfo = (LPCINFO)GetWindowLong(hwnd, GWL_USERDATA);
			
            if (!lpCInfo) {
            	ErrorMsg(TEXT("DrvWndProc: WM_CLOSE: lpCInfo is NULL."));
            	return 0;
            }
            
            CloseHandle(lpCInfo->hDirThread);
            CloseHandle(lpCInfo->hDirMutex );
            CloseHandle(lpCInfo->hFileMutex );
			TableFree(lpCInfo->DirTable);
			TableFree(lpCInfo->FileTable);
			
			break;
        }

                //   case WM_DELETEITEM:
            case WM_DRAWITEM: {
            
	            // Get pointer to the DRAWITEMSTRUCT 
	            lpdis = (LPDRAWITEMSTRUCT)lParam;

	            switch (lpdis->itemAction)
	            {
	            	case ODA_DRAWENTIRE:
	            		DrawEntireItem(lpdis);
	            		break;

	            	case ODA_SELECT:
	            		HandleSelectionState(lpdis);
	            		break;
	            	
	            }
 
	              // Return TRUE meaning that we processed this message. 
	            return 1;
			}

	        case WM_MEASUREITEM:{
	           
	            lpmis = (LPMEASUREITEMSTRUCT)lParam;
			

	            // All the items are the same height since the list box style is
	            // LBS_OWNERDRAWFIXED
	            //
	            lpmis->itemHeight = 15;
	            return 1;
			}        
            
            case WM_COMPAREITEM: {
				INT cv;
				
				lpcis = (LPCOMPAREITEMSTRUCT)lParam;

				if (!lpcis->itemData1)
					ErrorMsg(TEXT("WM_COMPAREITEM: lpcis->itemData1 is NULL."));
				
				if (!lpcis->itemData2)
					ErrorMsg(TEXT("WM_COMPAREITEM: lpcis->itemData2 is NULL."));
				
				cv = CFilerlstrcmp((LPTSTR)(lpcis->itemData1), (LPTSTR)(lpcis->itemData2));
								
				if (cv < 0)
					return -1;
				else if (cv == 0)
            		return 0;
				else if (cv > 0)
            		return 1;
            
			}
            
            default:
            return DefWindowProc(hwnd, message, wParam, lParam);

    } //switch
    return DefWindowProc(hwnd, message, wParam, lParam);
}

/*************************************************************************************\
* TextWndProc()
*
* Text Window procedure for displaying miscellaneous messages to user.
\*************************************************************************************/

LRESULT WINAPI TextWndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        {
        HDC        hDC;
        HGDIOBJ    hOldFont;
        TEXTMETRIC tm;
        LONG       lHeight;

        hDC = GetDC(hwnd);

        hOldFont = SelectObject(hDC, ghFont);
        GetTextMetrics(hDC, &tm);

        //
        // base the height of the window on size of text
        //
        lHeight = tm.tmHeight + GetSystemMetrics(SM_CYBORDER) + 6;

        //
        // saved the height for later reference
        //
        SetWindowLong(hwnd, GWL_USERDATA, lHeight);

            if(hOldFont)
                SelectObject(hDC, hOldFont);

            ReleaseDC(hwnd, hDC);
            break;
        }

    case WM_SETTEXT:
            DefWindowProc(hwnd, message, wParam, lParam);
            if( !InvalidateRect(hwnd, NULL, TRUE) ){
                ErrorMsg(TEXT("Textwindow: Set text failure."));
                return 1;
            }
            UpdateWindow(hwnd);
            return 1;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            RECT        rc;
            TCHAR       ach[BUF_SIZE];
            int         len, nxBorder, nyBorder;
            HFONT       hOldFont = NULL;
            HBRUSH      hBrush;

            BeginPaint(hwnd, &ps);

            GetClientRect(hwnd,&rc);

            len = GetWindowText(hwnd, ach, BUF_SIZE);

            SetBkMode(ps.hdc, TRANSPARENT);

            if( GetParent(hwnd) == ghwndDrv ){
                hBrush = CreateSolidBrush( GetSysColor(COLOR_ACTIVECAPTION) );
                SetTextColor( ps.hdc, GetSysColor(COLOR_CAPTIONTEXT) );
            }
            else{
                hBrush = CreateSolidBrush( GetSysColor(COLOR_INACTIVECAPTION) );
                SetTextColor( ps.hdc, GetSysColor(COLOR_INACTIVECAPTIONTEXT) );
            }

            hOldFont = SelectObject(ps.hdc, ghFont);

            FillRect(ps.hdc, &rc, hBrush);

            nxBorder = GetSystemMetrics(SM_CXBORDER);
            rc.left  += 9*nxBorder;
            rc.right -= 9*nxBorder;

            nyBorder = GetSystemMetrics(SM_CYBORDER);
            rc.top    += 3*nyBorder;
            rc.bottom -= 3*nyBorder;

            ExtTextOut(ps.hdc, rc.left+2*nxBorder, rc.top, ETO_CLIPPED,
                    &rc, ach, len, NULL);

            SetBkMode(ps.hdc, OPAQUE);

            if (hOldFont)
                SelectObject(ps.hdc, hOldFont);

            DeleteObject(hBrush);

            EndPaint(hwnd, &ps);
            return 1;
        }
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
