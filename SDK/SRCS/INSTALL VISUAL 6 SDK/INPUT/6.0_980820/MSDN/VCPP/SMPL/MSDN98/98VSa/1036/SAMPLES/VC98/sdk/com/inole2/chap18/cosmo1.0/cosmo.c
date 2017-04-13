/*
 * COSMO.C
 *
 * Basic Windows application code, with only a few specifics for handling
 * blocking as far as OLE goes.  Most OLE interaction is directed through
 * other functions in other source files that actually make the OLE library
 * calls.
 *
 * Copyright(c) Microsoft Corp. 1992-1994 All Rights Reserved
 * Win32 version, January 1994
 */

#include <windows.h>
#include <ole.h>
#include "cosmo.h"
#include "oleglobl.h"





/*
 * Array of pointers to strings loaded from the resource file.
 * Pointers can be near since we'll use LocalAlloc for
 * the string space.
 */

char NEAR   *rgpsz[CSTRINGS];

//Global variable block.
GLOBALS     stGlobals;
LPGLOBALS   pGlob=&stGlobals;




/*
 * WinMain
 *
 * Purpose:
 *  Main entry point of application.   Should register the app class
 *  if a previous instance has not done so and do any other one-time
 *  initializations.
 *
 * Parameters:
 *  See Windows SDK Guide to Programming, page 2-3
 *
 * Return Value:
 *  Value to return to Windows--termination code.
 *
 */

int PASCAL WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance
    , LPSTR lpszCmdLine, int nCmdShow)
    {
    HACCEL      hAccel;
    HWND        hWnd;
    MSG         msg;


    pGlob->hInst=hInstance;
    pGlob->pszCmdLine=lpszCmdLine;
    pGlob->nCmdShow=nCmdShow;

    /*
     * Try to initialize; on failure, clean up anything that might have
     * been allocated.
     */
    if (!FApplicationInit(pGlob, hPrevInstance))
        {
        FApplicationExit(pGlob);
        return FALSE;
        }

    hWnd=CreateWindow(rgpsz[IDS_CLASSCOSMO], rgpsz[IDS_CAPTION]
        , WS_MINIMIZEBOX | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT
        , CW_USEDEFAULT, 400, 350, NULL, NULL, hInstance, NULL);

    if (NULL==hWnd)
        {
        FApplicationExit(pGlob);
        return FALSE;
        }

    //Prevent the WM_SIZE from ShowWindow from making us dirty.
    pGlob->fNoDirty=TRUE;
    ShowWindow(hWnd, pGlob->nCmdShow);
    pGlob->fNoDirty=FALSE;

    if (SW_HIDE != pGlob->nCmdShow)
        UpdateWindow(hWnd);

    hAccel=LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATORS));

    //Non-OLE message loop.
    while (GetMessage(&msg, NULL, 0,0 ))
        {
        if (!TranslateAccelerator(hWnd, hAccel, &msg))
            {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            }
        }

    FApplicationExit(pGlob);
    return msg.wParam;
    }





/*
 * CosmoWndProc
 *
 * Purpose:
 *  Window class procedure.  Standard callback.
 *
 * Parameters:
 *  The standard.
 *
 * Return Value:
 *  The standard.
 *
 */

LRESULT WINAPI CosmoWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
    {
    static BOOL fNoSizePoly;
    RECT        rc;
    BOOL        fOK;
    UINT        uTemp;
    DWORD       dwStyle;
    WORD        wID=LOWORD(wParam);

   #ifdef WIN32
    WORD        wCode=HIWORD(wParam);
    HWND        hWndMsg=(HWND)(UINT)lParam;
   #else
    WORD        wCode=HIWORD(lParam);
    HWND        hWndMsg=(HWND)(UINT)lParam;
   #endif

    switch (iMsg)
        {
        case WM_CREATE:
            //Set global variable defaults that pertain to this window.
            pGlob->hWnd=hWnd;
            pGlob->fOpenFile=FALSE;
            pGlob->fNoDirty=FALSE;

            FDirtySet(FALSE);

            //Create the secondary edit window.
            pGlob->hWndPolyline=HPolylineWindowCreate(hWnd, pGlob->hInst);

            //Set the initial window title.
            WindowTitleSet(pGlob->hWnd, rgpsz[IDS_UNTITLED]);

            if (!FFileInit(pGlob))
                PostMessage(hWnd, WM_CLOSE, 0, 0L);

            fNoSizePoly=FALSE;
            break;


        case WM_SIZE:
            /* If we are getting WM_SIZE in response to a Polyline
             * notification, then don't resize it again.
             */

            if (fNoSizePoly)
                break;

            //Resize the polyline editor window to fit the new client area.
            GetClientRect(hWnd, &rc);
            InflateRect(&rc, -8, -8);

            //Tell the Polyline window to resize without notifying us.
            SendMessage(pGlob->hWndPolyline, PLM_RECTSET, FALSE
                , (LONG)(LPSTR)&rc);

            /*
             * We consider sizing something that makes the file dirty, but
             * not until we've finished the create process, which is why
             * we set fDirty to FALSE after the ShowWindow above, because
             * ShowWindow sends a WM_SIZE when the window first appears.
             */
            FDirtySet(TRUE);
            break;

        case WM_GETMINMAXINFO:
            {
            //Limit the smallest tracking size allowable.
           #ifdef WIN32
            LPMINMAXINFO    pmmi=(LPMINMAXINFO)lParam;

            pmmi->ptMinTrackSize.x=158;
            pmmi->ptMinTrackSize.y=168;
           #else
            LPPOINT     ppt=(LPPOINT)lParam;

            ppt[3].x=158;
            ppt[3].y=168;
           #endif
            }
            break;

        case WM_CLOSE:
            if (!FFileExit(pGlob))
                break;

            DestroyWindow(hWnd);    //Same as DefWindowProc's action.
            break;


        case WM_DESTROY:
            PostQuitMessage(0);
            break;


        case WM_INITMENUPOPUP:
            /*
             * Check for Save possibility in File menu position 0.
             * In and OLE situation, this is always enabled.
             */
            if (!pGlob->fOLE && 0==LOWORD(lParam))
                {
                uTemp=(pGlob->fOpenFile) ? MF_ENABLED : (MF_DISABLED | MF_GRAYED);
                EnableMenuItem((HMENU)wParam, IDM_FILESAVE, uTemp | MF_BYCOMMAND);
                }

            //Check for possibility of Paste for edit menu position 1
            if (1==LOWORD(lParam))
                {
                fOK=IsClipboardFormatAvailable(pGlob->cfCosmo);
                uTemp=(fOK) ? MF_ENABLED : (MF_DISABLED | MF_GRAYED);
                EnableMenuItem((HMENU)wParam, IDM_EDITPASTE, uTemp | MF_BYCOMMAND);
                }

            break;


        case WM_COMMAND:
            switch (wID)
                {
                case ID_POLYLINE:
                    if (PLN_POINTCHANGE==wCode)
                        {
                        FDirtySet(TRUE);
                        break;
                        }

                    /*
                     * Polyline window is informing us that it changed size
                     * in response to setting it's data.  Therefore we
                     * have to size ourselves accordingly.
                     */
                    if (PLN_SIZECHANGE==wCode)
                        {
                        //Calculate new DIMENSIONS (we won't move)
                        GetWindowRect(pGlob->hWndPolyline, &rc);
                        InflateRect(&rc, 8, 8);

                        dwStyle=GetWindowLong(pGlob->hWnd, GWL_STYLE);
                        AdjustWindowRect(&rc, dwStyle, TRUE);

                        fNoSizePoly=TRUE;
                        SetWindowPos(pGlob->hWnd, NULL, 0, 0
                            , rc.right-rc.left, rc.bottom-rc.top
                            , SWP_NOMOVE | SWP_NOZORDER);

                        fNoSizePoly=FALSE;
                        FDirtySet(TRUE);
                        }
                    break;


                case IDM_FILENEW:
                    FFileNew(pGlob);
                    break;


                case IDM_FILEOPEN:
                    FFileOpen(pGlob, FALSE);
                    break;


                case IDM_FILESAVE:
                    FFileSave(pGlob);
                    break;


                case IDM_FILESAVEAS:
                    fOK=FFileSaveAs(pGlob);
                    return MAKELONG(fOK, 0);


                case IDM_FILEIMPORT:
                    FFileOpen(pGlob, TRUE);
                    break;


                case IDM_FILEEXIT:
                    PostMessage(hWnd, WM_CLOSE, 0, 0L);
                    break;


                case IDM_EDITUNDO:
                    SendMessage(pGlob->hWndPolyline, PLM_BACKUPUNDO, 0, 0L);
                    break;

                case IDM_EDITCUT:
                    FEditCut(pGlob);
                    break;

                case IDM_EDITCOPY:
                    FEditCopy(pGlob, FALSE);
                    break;

                case IDM_EDITPASTE:
                    FEditPaste(pGlob);
                    break;


                case IDM_HELPABOUT:
                   #ifdef WIN32
                    DialogBox(pGlob->hInst, MAKEINTRESOURCE(IDD_ABOUT)
                        , pGlob->hWnd, AboutProc);
                   #else
                    {
                    DLGPROC     lpfn;

                    lpfn=(DLGPROC)MakeProcInstance((FARPROC)AboutProc, pGlob->hInst);
                    DialogBox(pGlob->hInst, MAKEINTRESOURCE(IDD_ABOUT)
                        , pGlob->hWnd, lpfn);
                    FreeProcInstance((FARPROC)lpfn);
                    }
                   #endif

                    break;
                }
            break;

        default:
            return (DefWindowProc(hWnd, iMsg, wParam, lParam));
        }

    return 0L;
    }






/*
 * AboutProc
 *
 * Purpose:
 *  Dialog procedure for the omnipresent About box.
 *
 * Parameters:
 *  The standard.
 *
 * Return Value:
 *  The value to be returned through the DialogBox call that
 *  created the dialog.
 *
 */

BOOL WINAPI AboutProc(HWND hDlg, UINT iMsg, UINT wParam, LONG lParam)
    {
    switch (iMsg)
        {
        case WM_INITDIALOG:
            return TRUE;

        case WM_COMMAND:
            switch (LOWORD(wParam))
                {
                case IDOK:
                    EndDialog(hDlg, TRUE);
                }
            break;
        }
    return FALSE;
    }
