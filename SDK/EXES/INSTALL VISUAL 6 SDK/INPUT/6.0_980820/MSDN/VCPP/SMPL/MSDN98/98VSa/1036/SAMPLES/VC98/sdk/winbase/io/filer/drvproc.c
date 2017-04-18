
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/

/******************************Module*Header*******************************\
* Module Name:  drvproc.c
*
* Filer : SDK sample
*   +   Simple File Management program with GUI front end.
*       Demonstrates Win32 File I/O API and various User algorithms.
*
* DRVPROC.C : Contains procedures relating to child window management.
*               In this sample, the Drive children handle the directory
*               and file enumeration, as well as the file I/O operations.
*
\**************************************************************************/

#define  STRICT
#include <windows.h>
#include <string.h>
#define _MBCS
#include <mbstring.h>
#include "globals.h"
#include "filer.h"
#include "expdir.h"
#include "drvproc.h"

extern HANDLE   ghModule;
extern HANDLE   ghHeap;
extern HFONT    ghFont;
extern HANDLE   ghDrvThread;
extern HANDLE   ghMenu;

extern HWND     ghwndCommand;
extern HWND     ghwndDrives;
extern HWND     ghActiveChild;
extern HWND     ghwndDrv1;
extern HWND     ghwndDrv2;
extern HWND     ghFocusWnd;

extern LPDINFO  glpDrives;

extern CRITICAL_SECTION    gHeapCS;  // Global heap critical section var.
extern CRITICAL_SECTION    gDrvCS;   // Drive list critical section var.

extern TCHAR    gszEditor[DIRECTORY_STRING_SIZE];
extern TCHAR    gszCommandLine[DIRECTORY_STRING_SIZE * 2];

extern TCHAR    gszExtensions[NUM_EXTENSION_STRINGS][EXTENSION_LENGTH];

extern VKINFO   gVKArray[NUM_VERSION_INFO_KEYS];  // .EXE version info array.


/***************************************************************************\
* DrvWndProc()
*
* History:
* 05-1-92  Created
\***************************************************************************/

LRESULT  WINAPI DrvWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    TCHAR lpBuffer[128];
	DWORD dwDirStyle = WS_BORDER | WS_CHILD | WS_VISIBLE |
                              LBS_NOINTEGRALHEIGHT | LBS_NOTIFY |
                              LBS_HASSTRINGS | LBS_WANTKEYBOARDINPUT |
                              LBS_DISABLENOSCROLL | WS_HSCROLL |
                              WS_VSCROLL |LBS_USETABSTOPS;

    DWORD dwFileStyle = WS_BORDER | WS_CHILD | WS_VISIBLE |
                               LBS_NOINTEGRALHEIGHT | LBS_NOTIFY |
                               LBS_HASSTRINGS | LBS_WANTKEYBOARDINPUT |
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

            lpCInfo->hwnd = hwnd;

            // Create text window
            lpCInfo->hTextWnd = CreateWindow(TEXT("TextClass"), NULL,
                                    SS_LEFT | WS_CHILD | WS_VISIBLE | WS_BORDER,
                                    0, 0, 0, 0,
                                    lpCInfo->hwnd,
                                    (HMENU) TEXT_WINDOW_ID,
                                    ghModule,
                                    NULL);

            // Create Directory and File List boxes
            lpCInfo->hDirLB = CreateWindow(TEXT("LISTBOX"), NULL,
                                    dwDirStyle,
                                    0, 0, 0, 0,
                                    lpCInfo->hwnd,
                                    (HMENU) LISTDIR_ID,
                                    ghModule,
                                    NULL);

            lpCInfo->hFileLB = CreateWindow(TEXT("LISTBOX"), NULL,
                                    dwFileStyle,
                                    0, 0, 0, 0,
                                    lpCInfo->hwnd,
                                    (HMENU) LISTFILE_ID,
                                    ghModule,
                                    NULL);

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
                                          lpCInfo->CaptionBarText );
            CharUpper(lpCInfo->CaptionBarText);

            WaitForSingleObject(ghDrvThread, INFINITE);
            EnterCriticalSection(&gDrvCS);

            lpWalk = glpDrives;

            if( dwLoop && dwLoop <= DIRECTORY_STRING_SIZE ){
                while( lpWalk && lpWalk->DriveName[0] !=
                       (lpCInfo->CaptionBarText)[0] )
                    lpWalk = lpWalk->next;
                if( !lpWalk ){
					LoadString(ghModule, IDS_DCCDRVLST, lpBuffer, sizeof(lpBuffer)); 
                    ErrorMsg(lpBuffer);
                    LeaveCriticalSection(&gDrvCS);
                    return(-1);
                }
            }
            else{
				LoadString(ghModule, IDS_DCCCURDIR, lpBuffer, sizeof(lpBuffer)); 
                ErrorMsg(lpBuffer);
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
                            (LPARAM)&lTabs) ) {
				LoadString(ghModule, IDS_DCCTABSTP, lpBuffer, sizeof(lpBuffer)); 
                ErrorMsg(lpBuffer);
            }

            //
            // Set default font.
            //
            SendMessage(lpCInfo->hDirLB, WM_SETFONT, (WPARAM)ghFont, (LPARAM)FALSE);
            SendMessage(lpCInfo->hFileLB, WM_SETFONT, (WPARAM)ghFont, (LPARAM)FALSE);

            SendMessage(hwnd, WM_COMMAND, (WPARAM)MM_REFRESH, (LPARAM)NULL);

            return(1);
        }

        case WM_COMMAND: {
          static LPCINFO     lpCInfo;
          static SELECTINFO  Select;

          //
          // Retrieving this child window's DRVCHILDINFO data for displaying
          //    messages in the text window
          //
          lpCInfo = (LPCINFO) GetWindowLong(hwnd, GWL_USERDATA);

          switch (LOWORD(wParam)){

            case MM_TAB:{
                HWND    hFocus;

                hFocus = GetFocus();

                if( hFocus == lpCInfo->hDirLB )
                    ghFocusWnd = lpCInfo->hFileLB;
                else
                    if( hFocus == lpCInfo->hFileLB )
                        ghFocusWnd = ghwndCommand;
                    else
                        if( hFocus == ghwndCommand)
                            ghFocusWnd = lpCInfo->hDirLB;

                SetFocus( ghFocusWnd );
                return(1);
            }

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

                SetFocus( ghwndCommand );
                ghFocusWnd = ghwndCommand;
                SendMessage(ghwndCommand, LB_SETCURSEL, (WPARAM)0,
                               (LPARAM)-1);
                return(1);
            }

            case MM_OPEN:{
                if( ghFocusWnd == lpCInfo->hFileLB )
                    OpenListBoxItem(lpCInfo);
                else
                    if( ghFocusWnd == lpCInfo->hDirLB ){
                        if( !PostMessage(hwnd, WM_COMMAND, MM_FILLDIR,
                                         (LPARAM)0) ){
            				LoadString(ghModule, IDS_MMOPENERR, lpBuffer, sizeof(lpBuffer)); 
                            ErrorMsg(lpBuffer);
                            return(0);
                        }
                    }
                    else
                        RunCommandItem(lpCInfo);

                return(1);
            }

            case MM_COPY:{

                Select.hwnd = hwnd;
                Select.dwAction = MM_COPY;
                LoadString(ghModule, IDS_COPYING, lpBuffer, sizeof(lpBuffer)); 
                Select.szAction = lpBuffer;
                LoadString(ghModule, IDS_COPYINGTO, lpBuffer, sizeof(lpBuffer));
                Select.szToFrom = lpBuffer;

                ExecuteFileAction(&Select);

                return(1);
            }

            case MM_DELETE:{

                Select.hwnd = hwnd;
                Select.dwAction = MM_DELETE;
                LoadString(ghModule, IDS_DELETING, lpBuffer, sizeof(lpBuffer));
                Select.szAction = lpBuffer;
                LoadString(ghModule, IDS_DELETINGFRM, lpBuffer, sizeof(lpBuffer));
                Select.szToFrom = lpBuffer;

                ExecuteFileAction(&Select);

                return(1);
            }

            case MM_MOVE:{

                Select.hwnd = hwnd;
                Select.dwAction = MM_MOVE;
                LoadString(ghModule, IDS_MOVING, lpBuffer, sizeof(lpBuffer));
                Select.szAction = lpBuffer;
                LoadString(ghModule, IDS_COPYINGTO, lpBuffer, sizeof(lpBuffer));
                Select.szToFrom = lpBuffer;

                ExecuteFileAction(&Select);

                return(1);
            }

            case MM_RENAME:{

                if( DialogBoxParam(ghModule, TEXT("RenameDlg"), hwnd,
                              (DLGPROC)RenameProc, (LPARAM)lpCInfo) == -1 ){
                    LoadString(ghModule, IDS_RENAMEERR, lpBuffer, sizeof(lpBuffer));
                    ErrorMsg(lpBuffer);
                    return(0);
                }

                return(1);
            }

            case MM_MKDIR:{

                if( DialogBoxParam(ghModule, TEXT("MkDirDlg"), hwnd,
                              (DLGPROC)MkDirProc, (LPARAM)lpCInfo) == -1 ){
                    LoadString(ghModule, IDS_MKDIRERR, lpBuffer, sizeof(lpBuffer));
                    ErrorMsg(lpBuffer);
                    return(0);
                }

                return(1);
            }

            case MM_VERSION:{

                if( DialogBoxParam(ghModule, TEXT("VersionInfoDlg"), hwnd,
                              (DLGPROC)VersionProc, (LPARAM)lpCInfo) == -1 ){
                    LoadString(ghModule, IDS_VERDLGERR, lpBuffer, sizeof(lpBuffer));
                    ErrorMsg(lpBuffer);
                    return(0);
                }

                return(1);
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
                    LoadString(ghModule, IDS_MMEXPAND, lpBuffer, sizeof(lpBuffer));
                    ErrorMsg(lpBuffer);
                    return(0);
                }
                return(1);
            }

            //
            // refreshes contents of directory and file ListBoxes.
            //
            case MM_REFRESH:{

                DWORD   dwThreadID;

                if( WaitForSingleObject( lpCInfo->hDirMutex, MUTEX_TIMEOUT)
                        == WAIT_TIMEOUT )
                    //
                    // If the full directory expand has been cancled, kill the
                    //  existing thread.
                    //
                    if( !lpCInfo->fDirExpand && !lpCInfo->fSuicide){
                        lpCInfo->fSuicide = TRUE;
                        return(1);
                    }
                    else{
                        return(0);
                    }

                // if set, clear the expand dir. user abort (escape key) flag.
                if( lpCInfo->fEscape ){
                    lpCInfo->fEscape = FALSE;
                    ReleaseMutex( lpCInfo->hDirMutex );
                    return(1);
                }

                // At this point, the Dir LB mutex has been grabbed.

                // Clear directory LB.  If expand flag is set, expand all
                //  directories.  Refill File LB.
                //
                if( SendMessage( lpCInfo->hDirLB, LB_RESETCONTENT,
                                 (WPARAM)0, (LPARAM)0 ) < 0 ){
                    LoadString(ghModule, IDS_REFRESH1, lpBuffer, sizeof(lpBuffer));
                    ErrorMsg(lpBuffer);
                    ReleaseMutex( lpCInfo->hDirMutex );
                    return(0);
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
                        LoadString(ghModule, IDS_REFRESH2, lpBuffer, sizeof(lpBuffer));
                        ErrorMsg(lpBuffer);
                        return(0);
                    }
                }
                else
                    ExpDir( lpCInfo );

                if( !PostMessage(hwnd, WM_COMMAND, MM_FILLFILE,
                                 (LPARAM)0) ){
                    LoadString(ghModule, IDS_REFRESH3, lpBuffer, sizeof(lpBuffer));
                    ErrorMsg(lpBuffer);
                    return(0);
                }

                return(1);
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
                    LoadString(ghModule, IDS_FILDIRERR, lpBuffer, sizeof(lpBuffer));
                    ErrorMsg(lpBuffer);
                    return(0);
                }

                return(1);
            }

            //
            //  Fill listbox in lParam with files from current directory.
            //  Sent by MM_REFRESH & LBN_DBLCLK in DrvWndProc, as well as
            //  DoFileIO. and HandleIOError().
            //
            //  lParam == 0
            //
            case MM_FILLFILE:{
                TCHAR               szFiles[DIRECTORY_STRING_SIZE + 20];
                LPTSTR              lpHold;

                if( WaitForSingleObject( lpCInfo->hFileMutex, MUTEX_TIMEOUT)
                        == WAIT_TIMEOUT ){
                    LoadString(ghModule, IDS_FILDIRERR2, lpBuffer, sizeof(lpBuffer));
                    ErrorMsg(lpBuffer);
                    return(0);
                }


                //
                // Not checking for errors here, as LB_RESETCONTENT always
                //  returns true, and LB_DIR returns an error if the directory
                //  is empty.
                //
                SendMessage(lpCInfo->hFileLB, LB_RESETCONTENT, (WPARAM)NULL, (LPARAM)NULL);

                lstrcpy( szFiles, lpCInfo->CaptionBarText );
                lpHold = TStrChr(szFiles, TEXT('\0'));
                lpHold--;
                if( *lpHold != TEXT('\\') ){
                    lpHold++;
                    *lpHold = TEXT('\\');
                }

                lpHold++;
                lstrcpy( lpHold, TEXT("*.*"));

                if( SendMessage( lpCInfo->hFileLB, LB_DIR, (WPARAM)0x10,
                                 (LPARAM)szFiles ) == LB_ERR ){
                    LoadString(ghModule, IDS_FILDIRERR3, lpBuffer, sizeof(lpBuffer));
                    ErrorMsg(lpBuffer);
                    ReleaseMutex( lpCInfo->hFileMutex );
                    return(0);
                }

                //
                //  Set selection to first file.
                //
                if( SendMessage( lpCInfo->hFileLB, LB_SETSEL, (WPARAM)TRUE,
                                 (LPARAM)0 ) == LB_ERR ){
                    LoadString(ghModule, IDS_FILDIRERR4, lpBuffer, sizeof(lpBuffer));
                    ErrorMsg(lpBuffer);
                    ReleaseMutex( lpCInfo->hFileMutex );
                    return(0);
                }

                SetWindowText(lpCInfo->hTextWnd, lpCInfo->CaptionBarText);

                ReleaseMutex( lpCInfo->hFileMutex );

                return(1);
            }

            //
            //  Toggle active status of drive child.
            //
            case MM_TOGGLE:{

                SetWindowText(lpCInfo->hTextWnd, lpCInfo->CaptionBarText);
                return(1);
            }

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
                    OpenListBoxItem(lpCInfo);
                    return(1);
                }
                break;

                case LBN_SETFOCUS:{
                    ghFocusWnd = lpCInfo->hFileLB;
                }
                break;

                default:
                    return(1);
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
                        LoadString(ghModule, IDS_DBLCLKERR, lpBuffer, sizeof(lpBuffer));
                        ErrorMsg(lpBuffer);
                        return(0);
                    }
                    return(1);
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
                        LoadString(ghModule, IDS_SELCNGERR, lpBuffer, sizeof(lpBuffer));
                        ErrorMsg(lpBuffer);
                        return(0);
                    }

                    //
                    // Retrieve selected (careted) item.
                    //
                    lIndex = SendMessage( (HWND)lParam, LB_GETCARETINDEX,
                                        (WPARAM)NULL, (LPARAM)NULL );

                    if( !ConstructDirName(lpCInfo, lIndex,
                                          lpCInfo->CaptionBarText) ){
                        LoadString(ghModule, IDS_CONDIRERR, lpBuffer, sizeof(lpBuffer));
                        ErrorMsg(lpBuffer);
                        ReleaseMutex( lpCInfo->hDirMutex );
                        return(0);
                    }

                    ReleaseMutex( lpCInfo->hDirMutex );

                    if( !PostMessage(hwnd, WM_COMMAND, MM_FILLFILE,
                                     (LPARAM)0) ){
                        LoadString(ghModule, IDS_LBNOTFYERR, lpBuffer, sizeof(lpBuffer));
                        ErrorMsg(lpBuffer);
                        return(0);
                    }
                } // LBN_SELCHANGE
                break;

                default:
                    return(1);
              }
            } //  LISTDIR_ID
            break;

            default:
               return(1);
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
                    LoadString(ghModule, IDS_PARNTFYERR, lpBuffer, sizeof(lpBuffer));
                    ErrorMsg(lpBuffer);
                    return(1);
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

            PostMessage(ghActiveChild, WM_COMMAND, (WPARAM)MM_TOGGLE,
                        (LPARAM)NULL);
            ghActiveChild = hwnd;
            SendMessage(ghActiveChild, WM_COMMAND, (WPARAM)MM_TOGGLE,
                        (LPARAM)NULL);

            lpCInfo = (LPCINFO) GetWindowLong(hwnd, GWL_USERDATA);
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

            CloseHandle(lpCInfo->hDirMutex );
            CloseHandle(lpCInfo->hFileMutex );

            EnterCriticalSection(&gHeapCS);
            HeapFree(ghHeap, 0, (LPVOID)lpCInfo);
            LeaveCriticalSection(&gHeapCS);

            break;
        }

        default:
            return DefWindowProc(hwnd, message, wParam, lParam);

    } //switch
    return DefWindowProc(hwnd, message, wParam, lParam);
}


/***************************************************************************\
*
* GetLBText()
*
* Gets the text of the currently selected (careted) item in the given
*   listbox.
*
* Returns:  Index of selected item if successful, -1 on failure
*
* History:
* 4/26/93
*   Created.
*
\***************************************************************************/
LONG GetLBText(HWND hActiveLB, PTCHAR szItemBuff)
{
    LONG    lIndex;
    TCHAR   lpBuffer[128];

    //
    // Retrieve selected (careted) item.
    //
    lIndex = SendMessage( hActiveLB, LB_GETCARETINDEX,
                          (WPARAM)NULL, (LPARAM)NULL );

    if( SendMessage( hActiveLB, LB_GETTEXT, (WPARAM)lIndex,
                     (LPARAM)szItemBuff) == LB_ERR ){
        LoadString(ghModule, IDS_GETLBTXTERR, lpBuffer, sizeof(lpBuffer));
        ErrorMsg(lpBuffer);
        return(-1);
    }

    return( lIndex );
}


/***************************************************************************\
*
* UpdateFileLB()
*
* Updates the file listbox of the drive child given by sending an MM_FILLFILE
*   message to it.
*
*  input:   hwnd    -   Handle of drive child to update file listbox of.
*
* History:
* 6/3/92
*   Created.
*
\***************************************************************************/
void UpdateFileLB(HWND hwnd)
{
    LPCINFO lpCInfo;

    lpCInfo = (LPCINFO)GetWindowLong(hwnd, GWL_USERDATA);

    SendMessage(hwnd, WM_COMMAND, (WPARAM)MM_FILLFILE,
                (LPARAM)0);
}


/***************************************************************************\
*
* OpenListBoxItem()
*
* Attempts to expand a selected File list box directory entry into an available
*  file listbox, or spawn a selected list box file.
*
*  input:   lpCInfo   -   pointer to Drv child's LPCINFO structure
*
* History:
* 5/27/92
*   Created.
*
\***************************************************************************/
BOOL OpenListBoxItem(LPCINFO lpCInfo)
{
    TCHAR   szItemBuff[DIRECTORY_STRING_SIZE];
    TCHAR   lpBuffer[128];

    //
    // Retrieve selected (careted) item.
    //
    GetLBText(lpCInfo->hFileLB, szItemBuff);

    //
    // Determine whether the item is a directory or a file.
    //   If file, Run if possible.
    //
    if( !IsDirectory(lpCInfo->CaptionBarText, szItemBuff) ){
        RunListBoxItem(lpCInfo);
        return(1);
        }

    //
    // It is a directory.  Set the new caption text, and expand files.
    //
    lstrcpy( lpCInfo->CaptionBarText, szItemBuff);

    if( !PostMessage(lpCInfo->hwnd, WM_COMMAND, MM_FILLFILE,
                        (LPARAM)0) ){
        LoadString(ghModule, IDS_OPENLBERR, lpBuffer, sizeof(lpBuffer));
        ErrorMsg(lpBuffer);
        return(0);
    }

    return(1);
}

/***************************************************************************\
*
* RunListBoxItem()
*
* Attempts to spawn the selected list box file. If the file is not executable,
*   attempts to spawn an editor to edit the file.
*
*  input:   lpCInfo   -   pointer to Drv child's LPCINFO structure
*
* History:
* 5/27/92
*   Created.
*
* 5/12/93
*   Modified.
*
\***************************************************************************/
BOOL RunListBoxItem(LPCINFO lpCInfo)
{
    LONG        lIndex;
    TCHAR       szFileBuff[DIRECTORY_STRING_SIZE];
    TCHAR       szCmdLine[DIRECTORY_STRING_SIZE * 2];
    LPTSTR      szHold;
    TCHAR       lpBuffer[128];

    STARTUPINFO si;
    PROCESS_INFORMATION pi;


    lstrcpy(szCmdLine, lpCInfo->CaptionBarText);

    lstrcat(szCmdLine, TEXT("\\"));

    //
    // Get file that was opened, and attempt to spawn. If fails, attempt to
    // edit it.
    //

    //
    // Retrieve selected (careted) item.
    //
    lIndex = GetLBText(lpCInfo->hFileLB, szFileBuff);
    if( lIndex == LB_ERR)
        return(0);

    //
    // Don't assume the file has an extension. if no '.', insert one at end
    //  of file, so spawned editor will not assume any default extension.
    //  (i.e. Notepad assumes a .TXT if no extension is given.)
    //
    szHold = TStrChr(szFileBuff, TEXT('.'));
    if( !szHold ){
        szHold = TStrChr(szFileBuff, TEXT('\0'));
        *szHold = TEXT('.');
        *(szHold + sizeof(TCHAR)) = TEXT('\0');
    }

    si.cb = sizeof(STARTUPINFO);
    si.lpReserved = NULL;
    si.lpDesktop = NULL;
    si.lpTitle = NULL;
    si.dwFlags = 0;
    si.cbReserved2 = 0;
    si.lpReserved2 = NULL;

    //
    // Convert file to uppercase for extension comparison.  Raise the
    //   priority of this thread for the duration of the create process code.
    //   This is so the CreateProcess will not be held up by the directory
    //   fill threads.
    //   If an executable extension, spawn, else edit.
    //
    CharUpper(szFileBuff);

    SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_HIGHEST);

    for(lIndex = 0; lIndex < NUM_EXTENSION_STRINGS; lIndex++)
        if( !lstrcmp(szHold, &gszExtensions[lIndex][0]) ){

            lstrcat(szCmdLine, szFileBuff);

            if( !CreateProcess(NULL, (LPTSTR)szCmdLine, NULL, NULL, FALSE,
                               CREATE_NEW_CONSOLE | NORMAL_PRIORITY_CLASS,
                               NULL, lpCInfo->CaptionBarText, &si, &pi) ){
                LoadString(ghModule, IDS_CANTSPAWN, lpBuffer, sizeof(lpBuffer));
                ErrorMsg(lpBuffer);
                return(0);
            }

            CloseHandle( pi.hProcess );
            CloseHandle( pi.hThread );

            return(1);
        }

    LoadString(ghModule, STR_DEF_EDITOR, szCmdLine,
               DIRECTORY_STRING_SIZE * 2);
    lstrcat(szCmdLine, TEXT(" "));
    lstrcat(szCmdLine, szFileBuff);

    if( !CreateProcess(NULL, szCmdLine, NULL, NULL, FALSE,
                       CREATE_NEW_CONSOLE | NORMAL_PRIORITY_CLASS,
                       NULL, lpCInfo->CaptionBarText, &si, &pi) ){
        LoadString(ghModule, IDS_CANTEDIT, lpBuffer, sizeof(lpBuffer));
        ErrorMsg(lpBuffer);
        return(0);
    }

    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );

    SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_NORMAL);

    return(1);
}


/***************************************************************************\
*
* FilerGetVersion()
*
*  Given an item from a File ListBox, GetVersion retrieves the version
*    information from the specified file.
*
*  input:   lpszFileName   -   the name of the file.
*           dwBuffSize     -   > 0 size of buffer to hold version info
*           szBuff         -   buffer to hold version info
*
*  returns: TRUE if successful, FALSE otherwise.
*
*  comments:  gVKArray would need a critical section if this function were
*             to be called by more than one thread.
*
* History:
* 2/23/93
*   Created.
*
\***************************************************************************/
BOOL FilerGetVersion(LPTSTR lpszFileName, DWORD dwBuffSize, LPTSTR szBuff)
{
    //
    // NUM_VERSION_INFO_KEYS in GLOBALS.H should be set to the number of entries in
    //   VersionKeys[].
    //
    CONST static TCHAR   *VersionKeys[] = {
            TEXT("ProductName"),
            TEXT("ProductVersion"),
            TEXT("OriginalFilename"),
            TEXT("FileDescription"),
            TEXT("FileVersion"),
            TEXT("CompanyName"),
            TEXT("LegalCopyright"),
            TEXT("LegalTrademarks"),
            TEXT("InternalName"),
            TEXT("PrivateBuild"),
            TEXT("SpecialBuild"),
            TEXT("Comments")
    };

    static TCHAR szNull[1] = TEXT("");
    LPVOID  lpInfo;
    DWORD   cch;
    UINT    i;
    TCHAR   key[80];
    TCHAR   lpBuffer[10];

    GetFileVersionInfo(lpszFileName, 0, dwBuffSize, (LPVOID)szBuff );
    wsprintf(lpBuffer, "%04X", GetUserDefaultLangID());
	strcat(lpBuffer,TEXT("04B0"));
    for (i = 0; i < NUM_VERSION_INFO_KEYS; i++) {
        lstrcpy(key, VERSION_INFO_KEY_ROOT);
        lstrcat(key, lpBuffer);
        lstrcat(key, "\\");
        lstrcat(key, VersionKeys[i]);
        gVKArray[i].szKey = VersionKeys[i];

        //
        // If version info exists, and the key query is successful, add
        //  the value.  Otherwise, the value for the key is NULL.
        //
        if( dwBuffSize && VerQueryValue(szBuff, key, &lpInfo, &cch) )
            gVKArray[i].szValue = lpInfo;
        else
            gVKArray[i].szValue = szNull;
    }

    return TRUE;
}


/***************************************************************************\
* VersionProc()
*
* .EXE Version Info Dialog Box
*
* History:
* 2/24/93  2am
*   Created.
\***************************************************************************/
LRESULT WINAPI VersionProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static LPTSTR   lpszBuff;
    TCHAR   lpBuffer[128];

    switch (message){
      case WM_INITDIALOG:{

        LPCINFO lpCInfo;
        DWORD   dwLength;
        DWORD   dwCount;
        DWORD   dwHandle;
        TCHAR   szFile[DIRECTORY_STRING_SIZE];
        TCHAR   szDir[DIRECTORY_STRING_SIZE];
        TCHAR   szFullName[DIRECTORY_STRING_SIZE];
        LPTSTR  lpszHold;
        TCHAR   lpBuffer[128];


        lpCInfo = (LPCINFO)lParam;
        LoadString(ghModule, IDS_FILE, lpBuffer, sizeof(lpBuffer));
        strcpy(szFile, lpBuffer);
        LoadString(ghModule, IDS_DIR, lpBuffer, sizeof(lpBuffer));
        strcpy(szDir, lpBuffer);

        //
        // Concatenate path to szDir text-control string.
        //
        lstrcat(szDir, lpCInfo->CaptionBarText);
        SendDlgItemMessage( hDlg, SB_DEST, WM_SETTEXT,
                            (WPARAM)0, (LPARAM)szDir);

        //
        // Concatenate File name to szFile text-control string.
        //
        dwLength = lstrlen(szFile);

        //
        // Get selected (careted) ListBox item
        //
        GetLBText(lpCInfo->hFileLB, (PTCHAR)&szFile[dwLength]);

        SendDlgItemMessage( hDlg, SB_SOURCE, WM_SETTEXT,
                            (WPARAM)0, (LPARAM)szFile);

        //
        // Fill Version Key and Value edit boxes.
        //
        lstrcpy( szFullName, lpCInfo->CaptionBarText );

        //
        // a file under some file systems may have [] characters.
        //   Prepend path, adding a delimiting backslash unless we're in the root.
        //   If the attribute check is successful, it's a file, so leave.
        //
        lpszHold = TStrChr(szFullName, TEXT('\0'));

        lpszHold--;
        if( *lpszHold != TEXT('\\') ){
            lpszHold++;
            *lpszHold = TEXT('\\');
        }
        lpszHold++;

        lstrcpy(lpszHold, &szFile[dwLength]); // File name past 'File:' prefix

        dwLength = GetFileVersionInfoSize( szFullName, &dwHandle);
        if( !dwLength ){
            LoadString(ghModule, IDS_GETVERERR, lpBuffer, sizeof(lpBuffer));
            ErrorMsg(lpBuffer);
            return(1);
        }

        // Allocate Version Info buffer
        EnterCriticalSection(&gHeapCS);
        lpszBuff = (LPTSTR)HeapAlloc( ghHeap, HEAP_ZERO_MEMORY, dwLength * sizeof(TCHAR) );
        LeaveCriticalSection(&gHeapCS);

        FilerGetVersion( szFullName, dwLength, lpszBuff );

        for( dwCount = 0; dwCount < NUM_VERSION_INFO_KEYS; dwCount++){
            if( SendDlgItemMessage( hDlg, SB_KEY, LB_ADDSTRING, 0,
                                    (LPARAM)gVKArray[dwCount].szKey)
                                    == LB_ERR ){
                LoadString(ghModule, IDS_GETVERERR2, lpBuffer, sizeof(lpBuffer));
                ErrorMsg(lpBuffer);
                return(0);
            }
            if( SendDlgItemMessage( hDlg, SB_VALUE, LB_ADDSTRING, 0,
                                    (LPARAM)gVKArray[dwCount].szValue)
                                    == LB_ERR ){
                LoadString(ghModule, IDS_GETVERERR3, lpBuffer, sizeof(lpBuffer));
                ErrorMsg(lpBuffer);
                return(0);
            }
        }

        //  Set selection in listboxes to first item.
        if( SendDlgItemMessage( hDlg, SB_KEY, LB_SETCURSEL,
                               (WPARAM)0,
                               (LPARAM)0 )
                               == LB_ERR ){
            LoadString(ghModule, IDS_GETVERERR4, lpBuffer, sizeof(lpBuffer));
            ErrorMsg(lpBuffer);
            return(0);
        }
        if( SendDlgItemMessage( hDlg, SB_VALUE, LB_SETCURSEL,
                               (WPARAM)0,
                               (LPARAM)0 )
                               == LB_ERR ){
            LoadString(ghModule, IDS_GETVERERR5, lpBuffer, sizeof(lpBuffer));
            ErrorMsg(lpBuffer);
            return(0);
        }

        //  Initialize Scroll Bar
        //  Check to see if a scroll bar is needed. See GLOBALS.H and FILER.DLG
        if( NUM_VERSION_INFO_KEYS - VERSION_DLG_LB_HEIGHT > 0 )
            SendDlgItemMessage( hDlg, SB_SCROLL, SBM_SETRANGE,
                               (WPARAM)0,
                               (LPARAM)NUM_VERSION_INFO_KEYS -1);
        SendDlgItemMessage( hDlg, SB_SCROLL, SBM_SETPOS,
                           (WPARAM)0,
                           (LPARAM)TRUE );

        return(1);
      }

      case WM_VSCROLL:{
        int nPos;

        nPos = SendDlgItemMessage( hDlg, SB_SCROLL, SBM_GETPOS,
                                  (WPARAM)0,
                                  (LPARAM)0 );

        switch( LOWORD(wParam) ){

            case SB_PAGEDOWN:{
                nPos += VERSION_DLG_LB_HEIGHT;
                if( nPos > NUM_VERSION_INFO_KEYS )
                    nPos = NUM_VERSION_INFO_KEYS;
                break;
            }
            case SB_LINEDOWN:{
                nPos++;
                if( nPos > NUM_VERSION_INFO_KEYS )
                    nPos = NUM_VERSION_INFO_KEYS;
                break;
            }
            case SB_PAGEUP:{
                nPos -= VERSION_DLG_LB_HEIGHT;
                if( nPos < 0 )
                    nPos = 0;
                break;
            }
            case SB_LINEUP:{
                nPos--;
                if( nPos < 0 )
                    nPos = 0;
                break;
            }
            default:
                return(1);
        }

        //  Set Scroll Bar position
        SendDlgItemMessage( hDlg, SB_SCROLL, SBM_SETPOS,
                            (WPARAM)nPos,
                            (LPARAM)TRUE );
        //  Set selection in listboxes
        if( SendDlgItemMessage( hDlg, SB_KEY, LB_SETCURSEL,
                                (WPARAM)nPos,
                                (LPARAM)0 )
                                == LB_ERR ){
            LoadString(ghModule, IDS_GETVERERR6, lpBuffer, sizeof(lpBuffer));
            ErrorMsg(lpBuffer);
            return(0);
        }
        if( SendDlgItemMessage( hDlg, SB_VALUE, LB_SETCURSEL,
                                (WPARAM)nPos,
                                (LPARAM)0 )
                                == LB_ERR ){
            LoadString(ghModule, IDS_GETVERERR6, lpBuffer, sizeof(lpBuffer));
            ErrorMsg(lpBuffer);
            return(0);
        }

        return(0);
      }

      case WM_CLOSE:
          // Free allocated buffer
          EnterCriticalSection(&gHeapCS);
          HeapFree( ghHeap, 0, lpszBuff);
          LeaveCriticalSection(&gHeapCS);

          EndDialog(hDlg, wParam);
          return(1);

      case WM_COMMAND:{
            int nLBid = 0;  // holds ID of listbox other than one sending LBN msg.

        switch( LOWORD(wParam) ){
            case SB_OK:
            case SB_CANCEL:{
                // Free allocated buffer
                EnterCriticalSection(&gHeapCS);
                HeapFree( ghHeap, 0, lpszBuff);
                LeaveCriticalSection(&gHeapCS);

                EndDialog(hDlg, wParam);
                return(1);
            }

            // SB_VALUE and SB_KEY are the ListBox IDs. Below are LB notifications.
            case SB_VALUE:
                nLBid = SB_KEY;
                // we slip through to the SB_KEY case on purpose!!
            case SB_KEY:{
                int nSelect;    // Holds selected item

                if( HIWORD(wParam) == LBN_SELCHANGE ){

                    if( !nLBid )    // If nLBid wasn't set by the SB_VALUE case above...
                        nLBid = SB_VALUE;

                    //  Get current listbox selection.
                    nSelect = SendDlgItemMessage( hDlg, LOWORD(wParam), LB_GETCURSEL,
                                        (WPARAM)0,
                                        (LPARAM)0 );
                    if( nSelect == LB_ERR ){
                        LoadString(ghModule, IDS_GETVERERR7, lpBuffer, sizeof(lpBuffer));
                        ErrorMsg(lpBuffer);
                        return(0);
                    }

                    //  Set similar selection in corresponding listbox.
                    if( SendDlgItemMessage( hDlg, nLBid, LB_SETCURSEL,
                                            (WPARAM)nSelect,
                                            (LPARAM)0 )
                                            == LB_ERR ){
                        LoadString(ghModule, IDS_GETVERERR8, lpBuffer, sizeof(lpBuffer));
                        ErrorMsg(lpBuffer);
                        return(0);
                    }


                    //  Set Scroll Bar position
                    SendDlgItemMessage( hDlg, SB_SCROLL, SBM_SETPOS,
                                        (WPARAM)nSelect,
                                        (LPARAM)TRUE );
                }
            }
        }
        return(1);
      }
    }

    return(0);
}


/***************************************************************************\
*
* IsDirectory()
*
*  Given an item from a ListBox filled from an LB_DIR call, IsDirectory
*    verifies whether or not the item is a directory, and if so, returns
*    true, and places the full directory path in lpszFile.
*
*  input:   lpszDir     -   Holds current directory
*           lpszFile    -   Holds item of dubious directoryness.
*
* History:
* 5/30/92
*   Created.
*
\***************************************************************************/
BOOL IsDirectory(LPTSTR lpszDir, LPTSTR lpszFile)
{
    DWORD   dwAttrib;
    LPTSTR  lpszHold;
    TCHAR   szItem[DIRECTORY_STRING_SIZE * 2];
    TCHAR   lpBuffer[128];


    //
    // if it's '..', go up one directory
    //
    if( !lstrcmp(lpszFile, TEXT("[..]")) ){
        lstrcpy(lpszFile, lpszDir);
        lpszHold = TStrChr(lpszFile, TEXT('\0'));
        while( lpszHold > lpszFile ){
            if(*lpszHold == TEXT('\\')){
                break;
            }
            lpszHold = CharPrev(lpszFile, lpszHold);
        }
        if(lpszHold <= lpszFile){
            LoadString(ghModule, IDS_ISDIRERR, lpBuffer, sizeof(lpBuffer));
            ErrorMsg(lpBuffer);
            return(0);
        }
        else{
            if( TStrChr(lpszFile, TEXT('\\')) == lpszHold )
                lpszHold++;
            *lpszHold = TEXT('\0');
            return(1);
        }
    }

    //
    // A directory will have [] around it in the listbox. Check for it.
    //
    if( *lpszFile != TEXT('[') )
        return(0);

    //
    // A file under some file systems may have [] characters.
    //   Prepend path, adding a delimiting backslash unless we're in the root.
    //   If the attribute check is successful, it's a file, so leave.
    //
    // NOTE:  This is a hack.  If there is a file called '[foo]' and a
    //   Directory called 'foo', they will appear identical in the listbox.
    //   Rather than check for this rare case, if it happens, Filer will
    //   assume it is a file first, as the directory may be changed from
    //   the Directory Listbox.
    //
    lstrcpy(szItem, lpszDir);
    lpszHold = TStrChr(szItem, TEXT('\0'));

    lpszHold--;
    if( *lpszHold != TEXT('\\') ){
        lpszHold++;
        *lpszHold = TEXT('\\');
    }
    lpszHold++;

    lstrcpy(lpszHold, lpszFile);

    dwAttrib = GetFileAttributes(szItem);

    if( dwAttrib != 0xFFFFFFFF )             // there really is a file called
        return(0);                           //  '[foo]'.  Exit.

    //
    // remove the [], and check if valid directory.
    //   if it fails, or it's not a directory, leave.
    //
    lstrcpy(lpszHold, &lpszFile[1]);
    lpszHold = TStrChr(lpszHold, TEXT('\0'));

    lpszHold--;
    if( *lpszHold != TEXT(']') )
        return(0);
    *lpszHold = TEXT('\0');

    dwAttrib = GetFileAttributes(szItem);

    if( (dwAttrib == 0xFFFFFFFF) || !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY) )
        return(0);

    //
    // OK, it's a directory, and szItem now holds the fully qualified path.
    // copy this to the filename buffer sent in, and return true.
    //
    CharUpper(szItem);
    lstrcpy(lpszFile, szItem);
    return(1);
}


/***************************************************************************\
*
* ExecuteFileAction()
*
* Creates a dialog box verifying a file action, and carries out the action.
*
*  input:   hwnd    -   handle to Drv child.
*           lpSelect    -   pointer to SELECTINFO structure, containing
*                           info on the file i/o action to be performed.
*
* History:
* 5/28/92
*   Created.
*
\***************************************************************************/
BOOL ExecuteFileAction(LPSINFO lpSelect)
{
    TCHAR   lpBuffer[128];

    if( DialogBoxParam(ghModule, TEXT("SelectDlg"), lpSelect->hwnd,
                  (DLGPROC)SelectProc, (LPARAM)lpSelect) == -1 ){
        LoadString(ghModule, IDS_EXEFILEERR, lpBuffer, sizeof(lpBuffer));
        ErrorMsg(lpBuffer);
        return(0);
    }
    return(1);
}


/***************************************************************************\
* SelectProc()
*
* File I/O selection dialog proc.
*
* History:
* 5/28/92
*   Created.
\***************************************************************************/
LRESULT WINAPI SelectProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static LPSINFO lpSelect;
    TCHAR   lpBuffer[128];

    switch (message) {
      case WM_INITDIALOG:{

        lpSelect = (LPSINFO)lParam;

        //
        // Fill source and destination fields of Select dialog.
        //
        if( !FillSelectDlg(hDlg, lpSelect) ){
            EndDialog(hDlg, wParam);
            return(1);
        }

        //
        // Set the TEXT('action') text (i.e. TEXT("COPYING:"), TEXT("MOVING:"), etc.)
        //
        if( !SetDlgItemText(hDlg, SB_ACTION, lpSelect->szAction) ){
            LoadString(ghModule, IDS_SELPROCERR, lpBuffer, sizeof(lpBuffer));
            ErrorMsg(lpBuffer);
            EndDialog(hDlg, wParam);
            return(1);
        }

        //
        // Set the TEXT("TO:") or TEXT("FROM:") text.
        //
        if( !SetDlgItemText(hDlg, SB_TOFROM, lpSelect->szToFrom) ){
            LoadString(ghModule, IDS_SELPROCERR, lpBuffer, sizeof(lpBuffer));
            ErrorMsg(lpBuffer);
            EndDialog(hDlg, wParam);
            return(1);
        }

        break;
      }
      case WM_CLOSE:
        EndDialog(hDlg, wParam);
        return(1);
      
      case WM_COMMAND:{
        switch(LOWORD(wParam)){
            case SB_OK:{
                DoFileIO(hDlg, lpSelect);
                EndDialog(hDlg, wParam);
                return(1);
            }
            case SB_CANCEL:{
                EndDialog(hDlg, wParam);
                return(1);
            }
        }
        return(1);
      }
    }

    return(0);
}


/***************************************************************************\
*
* FillSelectDlg()
*
* Fills the Select Dialog box with the files selected in the active Drv Child
*  for a file i/o action.  Destination defaults to directory selection in
*  inactive Drv Child.
*
*  input:   hDlg    -   handle to Select dialog box.
*           hwnd    -   handle to Drv child.
*
* History:
* 5/28/92
*   Created.
*
\***************************************************************************/
BOOL FillSelectDlg(HWND hDlg, LPSINFO lpSelect)
{
    LONG    lCount;         // Number of items selected in ListBox
    LONG    lSize;          // Holds size of a string
    LONG    lLargest = 0;   // Holds largest string encountered.
    UINT    *lpnIndex;      // ptr to array of selected ListBox items' indeces
    int     i;              // counter
    TCHAR   lpBuffer[128];  // Buffer for string retrieved from resources

    LPCINFO lpCInfo;
    HWND    hDest;          // dir of files if delete, else inactive Drv dir.

    HDC     hDC;
    TEXTMETRIC  Metrics;

    LPTSTR  lpszHold;       // marks end of directory path in szName.
    TCHAR   szName[DIRECTORY_STRING_SIZE * 2];  // holds ListBox strings.


    lpCInfo = (LPCINFO)GetWindowLong(lpSelect->hwnd, GWL_USERDATA);

    lCount = SendMessage( lpCInfo->hFileLB, LB_GETSELCOUNT,
                          (WPARAM)NULL, (LPARAM)NULL );

    //
    // if no items selected, leave.
    //
    if( !lCount )
        return(0);

    //
    // Allocate array of lCount listbox indexes, and fill it.
    //
    EnterCriticalSection(&gHeapCS);
    lpnIndex = (UINT*)HeapAlloc( ghHeap, HEAP_ZERO_MEMORY, lCount * sizeof(UINT) );
    LeaveCriticalSection(&gHeapCS);
    if( !lpnIndex ){
        LoadString(ghModule, IDS_SELDLGERR, lpBuffer, sizeof(lpBuffer));
        ErrorMsg(lpBuffer);
        return(0);
    }

    if( SendMessage( lpCInfo->hFileLB, LB_GETSELITEMS, (WPARAM)lCount,
                     (LPARAM)lpnIndex) != lCount ){
        LoadString(ghModule, IDS_SELDLGERR2, lpBuffer, sizeof(lpBuffer));
        ErrorMsg(lpBuffer);
        return(0);
    }

    //
    // Check if each selected entry is a valid file.
    //
    // Check to see if there is a terminating backslash, by decrementing
    //  pointer, checking, adding a '\' if necessary, then re-incrementing
    //  the pointer.
    //
    lstrcpy(szName, lpCInfo->CaptionBarText);

    lpszHold = TStrChr(szName, TEXT('\0'));

    lpszHold--;
    if( *lpszHold != TEXT('\\') ){
        lpszHold++;
        *lpszHold = TEXT('\\');
    }
    lpszHold++;

    //
    // Fill Dlg ListBox with selected strings from Drv child's ListBox,
    //   noting size of largest entry.
    //
    for( i = 0; i < lCount; i++){
        if( SendMessage( lpCInfo->hFileLB, LB_GETTEXT, (WPARAM)lpnIndex[i],
                        (LPARAM)lpszHold) == LB_ERR ){
            LoadString(ghModule, IDS_SELDLGERR3, lpBuffer, sizeof(lpBuffer));
            ErrorMsg(lpBuffer);
            return(0);
        }

        if( GetFileAttributes(szName) == 0xFFFFFFFF ){    //Error
            LoadString(ghModule, IDS_SELDLGERR4, lpBuffer, sizeof(lpBuffer));
            lstrcat(lpszHold, lpBuffer);
            ErrorMsg(lpszHold);
        }
        else{
            lSize = lstrlen(lpszHold);
            if( lSize > lLargest )
                lLargest = lSize;

            if( SendDlgItemMessage( hDlg, SB_SOURCE, LB_ADDSTRING, 0,
                                    (LPARAM)lpszHold) == LB_ERR ){
                LoadString(ghModule, IDS_SELDLGERR5, lpBuffer, sizeof(lpBuffer));
                ErrorMsg(lpBuffer);
                return(0);
            }
        }
    }

    //
    // Get the average char width of current font,
    // We then set the dialog listbox column width to
    // (longest string + arbitrary column spacing) * ave width.
    //
    hDC = GetDC(lpSelect->hwnd);
    if( !GetTextMetrics(hDC, &Metrics) ){
        LoadString(ghModule, IDS_SELDLGERR6, lpBuffer, sizeof(lpBuffer));
        ErrorMsg(lpBuffer);
        return(0);
    }

    ReleaseDC(lpSelect->hwnd, hDC);

    SendDlgItemMessage( hDlg, SB_SOURCE, LB_SETCOLUMNWIDTH,
                        (WPARAM)((lLargest + 8) * Metrics.tmAveCharWidth),
                        (LPARAM)NULL );

    EnterCriticalSection(&gHeapCS);
    HeapFree( ghHeap, 0, (LPVOID)lpnIndex);
    LeaveCriticalSection(&gHeapCS);


    //
    // Fill SB_DEST with directory.
    // If deleteing, default to the directory of the files.
    //
    if( lpSelect->dwAction != MM_DELETE ){
        //
        // Not Deleting.  Default to selected directory (titlebar)
        //   of the inactive Drive child.
        //
        if( lpSelect->hwnd == ghwndDrv1 )
            hDest = ghwndDrv2;
        else
            hDest = ghwndDrv1;

        lpCInfo = (LPCINFO)GetWindowLong(hDest, GWL_USERDATA);
    }

   SendDlgItemMessage( hDlg, SB_DEST, EM_LIMITTEXT,
                            (WPARAM)DIRECTORY_STRING_SIZE, (LPARAM)0);

   if( SendDlgItemMessage( hDlg, SB_DEST, WM_SETTEXT, 0,
                            (LPARAM)lpCInfo->CaptionBarText) == CB_ERR ){
        LoadString(ghModule, IDS_SELDLGERR7, lpBuffer, sizeof(lpBuffer));
        ErrorMsg(lpBuffer);
        return(0);
    }

    return(1);
}


/***************************************************************************\
*
* DoFileIO()
*
* Called by SelectProc.  Carries out the chosed file operations verified
*   in the Select Dialog Box.
*
*  input:   hDlg    -   handle to Select dialog box.
*           lpSelect    -   ptr to SELECTINFO structure.
*
*  returns: 1 if successful
*           0 if unsuccessful
* History:
* 6/3/92
*   Created.
*
\***************************************************************************/
BOOL DoFileIO( HWND hDlg, LPSINFO lpSelect)
{
    LONG    lCount;
    LONG    lFile;
    LPCINFO lpCInfo;
    LPTSTR  lpEndDest;
    LPTSTR  lpEndSource;
    BOOL    fError = FALSE;
    TCHAR   lpBuffer[128];

    TCHAR   szSource[DIRECTORY_STRING_SIZE];
    TCHAR   szDest[DIRECTORY_STRING_SIZE * 2];


    //
    // Find number of files to copy
    //
    lCount = SendDlgItemMessage( hDlg, SB_SOURCE, LB_GETCOUNT, (WPARAM)NULL,
                                 (LPARAM)NULL);

    if( (lCount == LB_ERR) || (lCount == 0) ){
        LoadString(ghModule, IDS_FILEIOERR, lpBuffer, sizeof(lpBuffer));
        ErrorMsg(lpBuffer);
        return(0);
    }

    //
    // Get source directory path. Add a \ to the end, set pointer to end.
    //
    lpCInfo = (LPCINFO)GetWindowLong( lpSelect->hwnd, GWL_USERDATA);

    lstrcpy(szSource, lpCInfo->CaptionBarText);

    lpEndSource = TStrChr(szSource, TEXT('\0'));
    *lpEndSource++ = TEXT('\\');

    //
    // Get destination directory path. Add a \ to the end, set pointer to end.
    //
    if( SendDlgItemMessage( hDlg, SB_DEST, WM_GETTEXT,
            (WPARAM)DIRECTORY_STRING_SIZE * 2, (LPARAM)szDest) == CB_ERR ){
        LoadString(ghModule, IDS_FILEIOERR2, lpBuffer, sizeof(lpBuffer));
        ErrorMsg(lpBuffer);
        return(0);
    }

    lpEndDest = TStrChr(szDest, TEXT('\0'));
    *lpEndDest++ = TEXT('\\');

    //
    // for each file, do appropriate I/O.
    //
    while( lCount ){

        lCount--;

        lFile = SendDlgItemMessage( hDlg, SB_SOURCE, LB_GETTEXT,
                                    (WPARAM)0, (LPARAM)lpEndSource);
        if( lFile == LB_ERR){
            LoadString(ghModule, IDS_FILEIOERR3, lpBuffer, sizeof(lpBuffer));
            ErrorMsg(lpBuffer);
            fError = TRUE;
        }

        SendDlgItemMessage( hDlg, SB_SOURCE, LB_DELETESTRING,
                            (WPARAM)0, (LPARAM)NULL);

        switch( lpSelect->dwAction ){
          case MM_COPY:{

            lstrcpy(lpEndDest, lpEndSource);

            if( !CopyFile( szSource, szDest, TRUE) )
                if( !HandleIOError(lpSelect->hwnd, lpSelect->dwAction,
                                   szSource, szDest) )
                    fError = TRUE;
            break;
          }

          case MM_MOVE:{

            lstrcpy(lpEndDest, lpEndSource);

            if( !MoveFileEx( szSource, szDest,
                            MOVEFILE_REPLACE_EXISTING|MOVEFILE_COPY_ALLOWED) )
                if( !HandleIOError(lpSelect->hwnd, lpSelect->dwAction,
                                   szSource, szDest) )
                    fError = TRUE;
            break;
          }
          case MM_DELETE:{

            if(GetFileAttributes(szSource) & FILE_ATTRIBUTE_DIRECTORY) {
                if(!RemoveDirectory(szSource))
                    if( !HandleIOError(lpSelect->hwnd, lpSelect->dwAction,
                                   szSource, szDest) )
                        fError = TRUE;
            }
            else {
                if( !DeleteFile(szSource) )
                    if( !HandleIOError(lpSelect->hwnd, lpSelect->dwAction,
                                   szSource, szDest) )
                        fError = TRUE;
            }
          }
          break;  
        }
        if( fError )
            break;
    }

    //
    //  Update file listboxes.
    //
    if( fError )
        return(0);
    else{
        UpdateFileLB(ghwndDrv1);
        UpdateFileLB(ghwndDrv2);
    }

    return(1);
}


/***************************************************************************\
*
* HandleIOError()
*
* Called by DoFileIO. Handles errors arising from File IO operations
*
*  input:   hwnd        -   handle to Drv child window
*           dwAction    -   File I/O Action.  Window message.
*           szSource    -   ptr to Source string
*           szDest      -   ptr to Destination string
*
*  returns: 1 if successful
*           0 if unsuccessful
*
* History:
* 6/3/92
*   Created.
*
\***************************************************************************/
BOOL HandleIOError(HWND hwnd, DWORD dwAction, LPTSTR szSource, LPTSTR szDest)
{
    DWORD   dwError;
    int     nReply;
    LPCINFO lpCInfo;
    TCHAR   buff[50];
    TCHAR   lpBuffer[128];

    dwError = GetLastError();

    CharUpper(szDest);

    switch( dwError ){
        case ERROR_ALREADY_EXISTS:
        case ERROR_FILE_EXISTS:{
          //
          // MoveFile file already exists. We can CopyFile & DeleteFile source.
          //
          LoadString(ghModule, IDS_HNDIOMSG, lpBuffer, sizeof(lpBuffer));
          nReply = MessageBox(hwnd,
                              lpBuffer,
                              szDest, MB_YESNOCANCEL);
          switch( nReply ){
            case IDYES:{

              lpCInfo = (LPCINFO)GetWindowLong(hwnd, GWL_USERDATA);

              if( !CopyFile( szSource, szDest, FALSE) )
                  if( HandleIOError(hwnd, dwAction, szSource, szDest) )
                      return(1);
                  else
                      return(0);
              if( dwAction == MM_MOVE )
                  if( !DeleteFile( szSource) )
                      if( HandleIOError(hwnd, dwAction, szSource, szDest) )
                          return(1);
                      else
                          return(0);

              UpdateFileLB(ghwndDrv1);
              UpdateFileLB(ghwndDrv2);

              return(1);
            }
            case IDNO:{
              return(1);
            }
            case IDCANCEL:{
              return(0);
            }
          }
          break;
        }

        case ERROR_ACCESS_DENIED:
        case ERROR_FILE_NOT_FOUND:
        case ERROR_INVALID_PARAMETER:{
            LoadString(ghModule, IDS_HNDIOMSG2, lpBuffer, sizeof(lpBuffer));
            wsprintf(buff,
                     lpBuffer,
                     dwError);
            MessageBox( hwnd, buff, szDest, MB_OK);

            return(1);
        }

        case ERROR_DISK_FULL:{
            LoadString(ghModule, IDS_HNDIOMSG3, lpBuffer, sizeof(lpBuffer));
            MessageBox( hwnd,
            lpBuffer,
            szDest, MB_OK);
            return(0);
        }

        case ERROR_INVALID_NAME:
        case ERROR_DIRECTORY:
        case ERROR_PATH_NOT_FOUND:{
            LoadString(ghModule, IDS_HNDIOMSG4, lpBuffer, sizeof(lpBuffer));
            MessageBox( hwnd,
            lpBuffer,
            szDest, MB_OK);
            return(0);
        }

        default:{
            LoadString(ghModule, IDS_HNDIOMSG5, lpBuffer, sizeof(lpBuffer));
            wsprintf(buff, lpBuffer, dwError);
            ErrorMsg(buff);
            return(1);
        }
    }

    return(1);
}


/***************************************************************************\
* RenameProc()
*
* File I/O rename Dialog Box
*
* History:
* 6/5/92  2am
*   Created.
\***************************************************************************/
LRESULT WINAPI RenameProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static TCHAR   szName[DIRECTORY_STRING_SIZE];
    static LPTSTR  lpszHold;
    static LPCINFO lpCInfo;
    TCHAR   lpBuffer[128];
    TCHAR   lpBuffer2[128];

    switch (message){
      case WM_INITDIALOG:{

        LONG    lIndex;

        lpCInfo = (LPCINFO)lParam;

        //
        // Check to see if there is a terminating backslash, by decrementing
        //  pointer, checking, adding a '\' if necessary, then re-incrementing
        //  the pointer.
        //
        lstrcpy(szName, lpCInfo->CaptionBarText);
        lpszHold = TStrChr(szName, TEXT('\0'));

        lpszHold--;
        if( *lpszHold != TEXT('\\') ){
            lpszHold++;
            *lpszHold = TEXT('\\');
        }
        lpszHold++;

        lIndex = GetLBText(lpCInfo->hFileLB, lpszHold);
        if( lIndex == LB_ERR )
            return(1);

        //
        // if not a valid file (i.e. listbox directory entry in []s), fail.
        //
        if( GetFileAttributes(szName) == 0xFFFFFFFF ){    //Error
            LoadString(ghModule, IDS_SELDLGERR4, lpBuffer, sizeof(lpBuffer));
            lstrcat(lpszHold, lpBuffer);
            ErrorMsg(lpszHold);
            return(1);
        }

        //
        // Place name in both source and destination edit controls.
        //
        CharUpper(szName);

        SendDlgItemMessage( hDlg, SB_SOURCE, EM_LIMITTEXT,
                            (WPARAM)DIRECTORY_STRING_SIZE, (LPARAM)0);

        SendDlgItemMessage( hDlg, SB_DEST, EM_LIMITTEXT,
                            (WPARAM)DIRECTORY_STRING_SIZE, (LPARAM)0);

        if( SendDlgItemMessage( hDlg, SB_SOURCE, WM_SETTEXT, 0,
                                (LPARAM)lpszHold) == LB_ERR ){
            LoadString(ghModule, IDS_RENMEMSG, lpBuffer, sizeof(lpBuffer));
            ErrorMsg(lpBuffer);
            return(1);
        }
        if( SendDlgItemMessage( hDlg, SB_DEST, WM_SETTEXT, 0,
                                (LPARAM)lpszHold) == LB_ERR ){
            LoadString(ghModule, IDS_RENMEMSG2, lpBuffer, sizeof(lpBuffer));
            ErrorMsg(lpBuffer);
            return(1);
        }
        return(1);
      }
      case WM_COMMAND:{
        switch(LOWORD(wParam)){
            case SB_OK:{
                TCHAR   szDest[DIRECTORY_STRING_SIZE];
                LPTSTR  lpszCheck;

                //
                // the entire source dir\file is still in static szName.
                // static lpszHold points to the end of the dir
                //
                *lpszHold = TEXT('\0');

                lstrcpy(szDest, szName);

                if( SendDlgItemMessage( hDlg, SB_SOURCE, WM_GETTEXT,
                                        DIRECTORY_STRING_SIZE,
                                        (LPARAM)lpszHold) == LB_ERR ){
                    LoadString(ghModule, IDS_RENMEMSG3, lpBuffer, sizeof(lpBuffer));
                    ErrorMsg(lpBuffer);
                    EndDialog(hDlg, wParam);
                    return(1);
                }

                //
                // If there are any \s in the new filename, fail.
                //
                lpszCheck = TStrChr(lpszHold, TEXT('\\'));

                if( lpszCheck ){
                    LoadString(ghModule, IDS_RENMEMSG4, lpBuffer, sizeof(lpBuffer));
                    LoadString(ghModule, IDS_RENMEMSG5, lpBuffer2, sizeof(lpBuffer2));
                    MessageBox(lpCInfo->hwnd,
                               lpBuffer,
                               lpBuffer2, MB_OK );
                    return(1);
                }

                lpszHold = TStrChr(szDest, TEXT('\0'));

                if( SendDlgItemMessage( hDlg, SB_DEST, WM_GETTEXT,
                                        DIRECTORY_STRING_SIZE,
                                        (LPARAM)lpszHold) == LB_ERR ){
                    LoadString(ghModule, IDS_RENMEMSG6, lpBuffer, sizeof(lpBuffer));
                    ErrorMsg(lpBuffer);
                    EndDialog(hDlg, wParam);
                    return(1);
                }

                //
                // If there are any \s in the destination filename, fail.
                //
                lpszCheck = TStrChr(lpszHold, TEXT('\\'));

                if( lpszCheck ){
                    LoadString(ghModule, IDS_RENMEMSG4, lpBuffer, sizeof(lpBuffer));
                    LoadString(ghModule, IDS_RENMEMSG5, lpBuffer2, sizeof(lpBuffer2));
                    MessageBox(lpCInfo->hwnd,
                               lpBuffer,
                               lpBuffer2, MB_OK );
                    return(1);
                }

                //
                // if strings are identical, leave.
                //
                if( !lstrcmpi(szName, szDest) ){
                    EndDialog(hDlg, wParam);
                    return(1);
                }

                if( !MoveFile( szName, szDest) )
                    if( !HandleIOError(lpCInfo->hwnd,
                                       (DWORD)MM_RENAME, szName, szDest) ){
                        EndDialog(hDlg, wParam);
                        return(1);
                    }

                if( !PostMessage(lpCInfo->hwnd, WM_COMMAND, MM_FILLFILE,
                                 (LPARAM)0) ) {
                    LoadString(ghModule, IDS_RENMEMSG7, lpBuffer, sizeof(lpBuffer));
                    ErrorMsg(lpBuffer);
                }
                EndDialog(hDlg, wParam);
                return(1);
            }
            case SB_CANCEL:{
                EndDialog(hDlg, wParam);
                return(1);
            }
        }
        return(1);
      } // WM_COMMAND
    }

    return(0);
}


/***************************************************************************\
* MkDirProc()
*
* File I/O Make Directory Dialog Box
*
* History:
* 6/5/92  2am
*   Created.
\***************************************************************************/
LRESULT WINAPI MkDirProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    TCHAR   lpBuffer[128];

    switch (message){
      case WM_INITDIALOG:{
        LPCINFO lpCInfo;
        TCHAR   szDest[DIRECTORY_STRING_SIZE];
        LPTSTR  lpszHold;


        lpCInfo = (LPCINFO)lParam;

        //
        // Check to see if there is a terminating backslash, by decrementing
        //  pointer, checking, adding a '\' if necessary.
        //
        lstrcpy(szDest, lpCInfo->CaptionBarText);
        lpszHold = TStrChr(szDest, TEXT('\0'));

        lpszHold--;
        if( *lpszHold != TEXT('\\') ){
            lpszHold++;
            *lpszHold = TEXT('\\');
            lpszHold++;
            *lpszHold = TEXT('\0');
        }

        SendDlgItemMessage( hDlg, SB_DEST, EM_LIMITTEXT,
                            (WPARAM)DIRECTORY_STRING_SIZE, (LPARAM)0);

        //
        // Place name in directory name edit control.
        //
        if( SendDlgItemMessage( hDlg, SB_DEST, WM_SETTEXT, 0,
                                (LPARAM)szDest) == LB_ERR ){
            LoadString(ghModule, IDS_MKDIRMSG, lpBuffer, sizeof(lpBuffer));
            ErrorMsg(lpBuffer);
            return(1);
        }

        SendDlgItemMessage( hDlg, SB_DEST, EM_SETSEL, (WPARAM)-1, (LPARAM)0);

        return(1);
      }
      case WM_COMMAND:{
        switch(wParam){
            case SB_OK:{
                TCHAR    szDest[DIRECTORY_STRING_SIZE];

                if( SendDlgItemMessage( hDlg, SB_DEST, WM_GETTEXT,
                                        DIRECTORY_STRING_SIZE,
                                        (LPARAM)szDest) == LB_ERR ){
                    LoadString(ghModule, IDS_MKDIRMSG2, lpBuffer, sizeof(lpBuffer));
                    ErrorMsg(lpBuffer);
                    EndDialog(hDlg, wParam);
                    return(1);
                }

                //
                // If loacation of subdir is invalid, leave.
                //
                if( !CreateDirectory(szDest, NULL) ){
                    LoadString(ghModule, IDS_MKDIRMSG3, lpBuffer, sizeof(lpBuffer));
                    ErrorMsg(lpBuffer);
                    EndDialog(hDlg, wParam);
                    return(1);
                }

                SendMessage( ghwndDrv1, WM_COMMAND, MM_REFRESH, (LPARAM)0);
                SendMessage( ghwndDrv2, WM_COMMAND, MM_REFRESH, (LPARAM)0);
            }
            case SB_CANCEL:{
                EndDialog(hDlg, wParam);
                return(1);
            }
        }
        return(1);
      }
    }

    return(0);
}


/***************************************************************************\
*
* TextWndProc()
*
* Text Window procedure for displaying miscellaneous messages to user.
*
* History:
* 5/25/92
*   Created.
*
\***************************************************************************/

LRESULT WINAPI TextWndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    TCHAR   lpBuffer[128];
    
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
                LoadString(ghModule, IDS_TXTMSG, lpBuffer, sizeof(lpBuffer));
                ErrorMsg(lpBuffer);
                return(1);
            }
            UpdateWindow(hwnd);
            return(1);

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            RECT        rc;
            TCHAR       ach[128];
            int         len, nxBorder, nyBorder;
            HFONT       hOldFont = NULL;
            HBRUSH      hBrush;

            BeginPaint(hwnd, &ps);

            GetClientRect(hwnd,&rc);

            len = GetWindowText(hwnd, ach, sizeof(ach));

            SetBkMode(ps.hdc, TRANSPARENT);

            if( GetParent(hwnd) == ghActiveChild ){
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
            return(1);
        }
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

/***************************************************************************\
*
* TStrChr()
*
* A strchr() function which is ASCII or UNICODE.
*
* History:
* 2/25/93
*   Created.
*
\***************************************************************************/
PTCHAR TStrChr(const PTCHAR string, UINT c)
{
#ifdef UNICODE
    return wcschr((wchar_t*)string, (wchar_t)c);
#else
    PTCHAR  psz;
    for (psz = string; *psz; psz = CharNext(psz)) {
        if (*psz == (TCHAR)c) {
            break;
        }
    }
    return psz;
#endif
}
