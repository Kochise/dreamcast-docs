
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1993-96 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/

#include "PortTool.h"

HWND	hCancelDlg = 0;
PRINTDLG	pdPrint;


/* get default printer configuration and save in hWnd extra bytes for use later */
BOOL WINAPI GetPrinterConfig (
    HWND    hWnd)
{
    pdPrint.lStructSize = sizeof (PRINTDLG);
	pdPrint.Flags		= PD_RETURNDEFAULT;
	pdPrint.hwndOwner	= hWnd;
	pdPrint.hDevMode	= NULL;
	pdPrint.hDevNames	= NULL;
	pdPrint.hDC 		= NULL;

	PrintDlg (&pdPrint);

	SetWindowLong (hWnd, WL_HPTRDEVNAMES, (LONG) pdPrint.hDevNames);

	return TRUE;
}



/* abort proc called by gdi during print download process */
int WINAPI AbortProc (
    HDC     hdc,
    int     nErr)
{
    BOOL    fContinue = TRUE;
    MSG     msg;

    /* process messages for cancel dialog and other apps */
    while (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
	{
	if (msg.message == UM_CANCELPRINT)
	    {
	    fContinue = FALSE;
	    break;
	    }

	else if (!hCancelDlg || !IsDialogMessage (hCancelDlg, &msg))
	    {
	    TranslateMessage (&msg);
	    DispatchMessage  (&msg);
	    }
	}

    return fContinue;
}




BOOL WINAPI CancelDlgProc (
    HWND    hWnd,
    UINT    uMsg,
    UINT    uParam,
    LONG    lParam)
{

    switch (uMsg)
	{
	case WM_INITDIALOG:
	    {
	    char    *lpdn;
	    char    lpszTitle[MAX_PATH];
        HWND    hWndOwner = GetWindow(hWnd, GW_OWNER);

	    /* initialize dialog control information */
	    lpdn = LocalLock (pdPrint.hDevNames);

	    SetDlgItemText (hWnd,
			    IDC_PRINTDEVICE,
			    lpdn + sizeof (DEVNAMES) +
				((DEVNAMES *)lpdn)->wDeviceOffset);
	    SetDlgItemText (hWnd,
			    IDC_PRINTPORT,
			    lpdn + sizeof (DEVNAMES) +
				((DEVNAMES *)lpdn)->wOutputOffset);
	    LocalUnlock (pdPrint.hDevNames);
	    GetWindowText (hWndOwner, lpszTitle, sizeof (lpszTitle));
	    SetDlgItemText (hWnd, IDC_PRINTTITLE, lpszTitle);
	    }
	    break;

	case WM_COMMAND:
	    /* if cancel button selected, post message to cancel print job */
	    if (LOWORD (uParam) == IDCANCEL)
		{
		PostMessage (GetParent (hWnd), UM_CANCELPRINT, 0, 0);
		DestroyWindow (hWnd);
		}
	    break;

	default:
	    return FALSE;
    }
    return TRUE;
}



/* put up the print common dialog, and print */
int WINAPI PrintFile (
    HWND    hWnd)
{
    char	*lpEditData;
    HANDLE	hEditData;
    SIZE	sLine;
    int 	yLineExt;
    int 	yExt;
    int 	yPageExt;
    UINT	uLine;
    UINT	uNumLines;
    UINT	uOffset;
    UINT	uLineLen;
    UINT	uTitleLen;
    HWND	hWndEdit;
	// PRINTDLG	pdPrint;
    DOCINFO	diPrint;
    char	lpszJobName[MAX_PATH];
    HFONT	hFont;
    HFONT	hFontPrt = NULL;
    int		nPageCnt = 1;


    /* call common print dialog to get initialized printer DC */
    pdPrint.hwndOwner = hWnd;
    pdPrint.hDC = NULL;
    pdPrint.Flags = PD_RETURNDC ;


    /* call common print dialog */
    if (!PrintDlg (&pdPrint))
	return IDS_PTRCOMMDLGFAILED;

    /* start cancel dialog box */
    hCancelDlg = CreateDialog ((HANDLE)GetModuleHandle (NULL),
			       IDD_CANCELDLG,
			       hWnd,
			       CancelDlgProc);


    if (!hCancelDlg)
	return IDS_CANCELDLGFAILED;

    ShowWindow (hCancelDlg, SW_SHOW);
    UpdateWindow (hCancelDlg);

    /* set AbortProc callback */
    if (SetAbortProc (pdPrint.hDC, (PROC)AbortProc) < 0)
	{
	/* on error, clean up and go away */
	DestroyWindow (hCancelDlg);
	DeleteDC (pdPrint.hDC);
	return IDS_SETABORTPROCFAILED;
	}

    hWndEdit = (HWND)GetWindowLong (hWnd, WL_HWNDEDIT);
    if (NULL == (hFont = (HFONT)SendMessage(hWndEdit, WM_GETFONT, 0, 0L))) {
        hFont = GetStockObject(SYSTEM_FONT);
    } else {
        HDC     hdcScreen;
        LOGFONT lf;

        if (NULL != (hdcScreen = GetDC(hWnd))) {
            if(GetObject(hFont, sizeof(LOGFONT), &lf)) {
                lf.lfWidth = 0;
                lf.lfHeight = lf.lfHeight
                            * GetDeviceCaps(pdPrint.hDC, LOGPIXELSX)
                            / GetDeviceCaps(hdcScreen, LOGPIXELSX);
                if (NULL != (hFontPrt = CreateFontIndirect(&lf))) {
                    hFont = hFontPrt;
                }
            }
            ReleaseDC(hWnd, hdcScreen);
        }
    }
    hFont = SelectObject(pdPrint.hDC, hFont);

    /* initialize printer for job */
    GetWindowText (hWnd, lpszJobName, sizeof (lpszJobName));
    diPrint.cbSize = sizeof (DOCINFO);
    diPrint.lpszDocName = lpszJobName;
    diPrint.lpszOutput = NULL;
    if (StartDoc (pdPrint.hDC, &diPrint) == SP_ERROR ||  StartPage (pdPrint.hDC) < 0)
	{
	/* on error, clean up and go away */
	DestroyWindow (hCancelDlg);
	SelectObject(pdPrint.hDC, hFont);
        if (hFontPrt) {
	    DeleteObject(hFontPrt);
        }
	DeleteDC (pdPrint.hDC);
	return IDS_STARTDOCFAILED;
	}

    /* job started, so display cancel dialog */
    ShowWindow (hCancelDlg, SW_SHOW);
    UpdateWindow (hCancelDlg);

    /* retrieve dimensions for printing and init loop variables */
    /* 'hWndEdit' has already been got. */
    hWndEdit = (HWND)GetWindowLong(hWnd, WL_HWNDEDIT);
    hEditData = (HANDLE)SendMessage (hWndEdit, EM_GETHANDLE, 0, 0L);
    uNumLines = (WORD)SendMessage (hWndEdit, EM_GETLINECOUNT, 0, 0L);
    GetTextExtentPoint (pdPrint.hDC, "CC", 2, &sLine);
    yLineExt = sLine.cy;
    yPageExt = GetDeviceCaps (pdPrint.hDC, VERTRES);
    yExt = 0;
    uLine = 0;
    if (pdPrint.Flags & PD_PAGENUMS) {
	uLine = (pdPrint.nFromPage - 1) * (yPageExt / yLineExt);
    }

    /* print text line by line from top to bottom */
    while (uLine < uNumLines)
	{
	if ((pdPrint.Flags & PD_PAGENUMS) &&
	    (uLine >= (UINT)(pdPrint.nToPage * (yPageExt / yLineExt)))) {
	    break;
	}
	/* if at end of page, start a new page */
	if ((yExt + yLineExt) > yPageExt)
	    {
	    if (!EndPage (pdPrint.hDC) || StartPage (pdPrint.hDC) < 0)
		{
		DestroyWindow (hCancelDlg);
		SelectObject(pdPrint.hDC, hFont);
                if (hFontPrt) {
                    DeleteObject(hFontPrt);
                }
		DeleteDC (pdPrint.hDC);
		return IDS_PRINTABORTED;
		}
	    yExt = 0;
	    }

	/* determine buffer offset for current line and line length */
	uOffset = SendMessage (hWndEdit, EM_LINEINDEX, uLine, 0);
	uLineLen = SendMessage (hWndEdit, EM_LINELENGTH, uOffset, 0);

#if defined (WIN32)
    uTitleLen=GetWindowTextLength(hWndEdit);
    hEditData=LocalAlloc(LHND,uTitleLen+1); 
    lpEditData=LocalLock(hEditData); 
    GetWindowText(hWndEdit, lpEditData, uTitleLen+1);
#else
    hEditData = (HANDLE)SendMessage (hWndEdit, EM_GETHANDLE, 0, 0L);
	lpEditData = LocalLock (hEditData);
#endif

	/* print current the line and unlock the text handle */
    TextOut (pdPrint.hDC, 0, yExt, (char *)lpEditData+uOffset, uLineLen);
	LocalUnlock (hEditData);

	/* increment page position */
	yExt += yLineExt;
	uLine++;
	}

    /* end the last page and document */
    EndPage (pdPrint.hDC);
    EndDoc (pdPrint.hDC);

    SelectObject(pdPrint.hDC, hFont);
    if (hFontPrt) {
        DeleteObject(hFontPrt);
    }
    /* end cancel dialog box, clean up and exit */
    DestroyWindow (hCancelDlg);
    DeleteDC(pdPrint.hDC);
    return TRUE;
}



/* printer setup common dialog */
int WINAPI PrinterSetup (
    HWND    hWnd)
{
	// PRINTDLG	pdPrint;

	pdPrint.Flags		= PD_PRINTSETUP;
	pdPrint.hwndOwner	= hWnd;

    /* call common print dialog */
	if (!PrintDlg (&pdPrint) && CommDlgExtendedError ())
		return IDS_PTRCOMMDLGFAILED;
	else
		return 0;
}
