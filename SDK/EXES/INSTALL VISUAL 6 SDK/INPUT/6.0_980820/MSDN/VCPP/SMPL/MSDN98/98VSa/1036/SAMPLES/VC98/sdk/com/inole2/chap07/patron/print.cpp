/*
 * PRINT.CPP
 * Patron Chapter 7
 *
 * Implementation of printing functions for both CPatronDoc
 * and CPages classes.  These functions are here to keep clutter
 * down in document.cpp and pages.cpp.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */

#include "patron.h"

static HWND g_hDlgPrint=NULL;
static BOOL g_fCancelPrint=FALSE;


/*
 * CPatronDoc::Print
 *
 * Purpose:
 *  Prints the current document.
 *
 * Parameters:
 *  hWndFrame       HWND of the frame to use for dialog parents.
 *
 * Return Value:
 *  BOOL            TRUE if printing happened, FALSE if it didn't
 *                  start or didn't complete.
 */

BOOL CPatronDoc::Print(HWND hWndFrame)
    {
    PRINTDLG        pd;
    BOOL            fSuccess;

    memset(&pd, 0, sizeof(PRINTDLG));
    pd.lStructSize=sizeof(PRINTDLG);
    pd.hwndOwner  =hWndFrame;
    pd.nCopies    =1;
    pd.nFromPage  =(USHORT)-1;
    pd.nToPage    =(USHORT)-1;
    pd.nMinPage   =1;
    pd.nMaxPage   =m_pPG->NumPagesGet();

    pd.lpfnPrintHook=PrintDlgHook;

    //Get the current document printer settings
    pd.hDevMode=m_pPG->DevModeGet();

    pd.Flags=PD_RETURNDC | PD_ALLPAGES | PD_COLLATE
        | PD_HIDEPRINTTOFILE | PD_NOSELECTION | PD_ENABLEPRINTHOOK;

    if (!PrintDlg(&pd))
        return FALSE;

    if (NULL!=pd.hDevMode)
        GlobalFree(pd.hDevMode);

    if (NULL!=pd.hDevNames)
        GlobalFree(pd.hDevNames);

    //Go do the actual printing.
    fSuccess=m_pPG->Print(pd.hDC, PSZ(IDS_DOCUMENTNAME), pd.Flags
        , pd.nFromPage, pd.nToPage, pd.nCopies);

    if (!fSuccess)
        {
        MessageBox(m_hWnd, PSZ(IDS_PRINTERROR)
            , PSZ(IDS_DOCUMENTCAPTION), MB_OK);
        }

    return fSuccess;
    }






/*
 * CPatronDoc::PrinterSetup
 *
 * Purpose:
 *  Selects a new printer and options for this document.
 *
 * Parameters:
 *  hWndFrame       HWND of the frame to use for dialog parents.
 *  fDefault        BOOL to avoid any dialog and just use the
 *                  default.
 *
 * Return Value:
 *  UINT            Undefined
 */

UINT CPatronDoc::PrinterSetup(HWND hWndFrame, BOOL fDefault)
    {
    PRINTDLG        pd;

    //Attempt to get printer metrics for the default printer.
    memset(&pd, 0, sizeof(PRINTDLG));
    pd.lStructSize=sizeof(PRINTDLG);

    if (fDefault)
        pd.Flags=PD_RETURNDEFAULT;
    else
        {
        pd.hwndOwner=hWndFrame;
        pd.Flags=PD_PRINTSETUP;

        //Get the current document printer settings
        pd.hDevMode=m_pPG->DevModeGet();
        }

    if (!PrintDlg(&pd))
        return FALSE;

    if (!m_pPG->DevModeSet(pd.hDevMode, pd.hDevNames))
        {
        GlobalFree(pd.hDevNames);
        GlobalFree(pd.hDevMode);
        return FALSE;
        }

    FDirtySet(TRUE);
    return 1;
    }



/*
 * PrintDlgHook
 *
 * Purpose:
 *  Callback hook for the Print Dialog so we can hide the Setup
 *  button.  Patron only allows Setup before anything exists on
 *  the page, and is not written to handle setup at Print time.
 */

UINT CALLBACK PrintDlgHook(HWND hDlg, UINT iMsg, WPARAM wParam
    , LPARAM lParam)
    {
    if (WM_INITDIALOG==iMsg)
        {
        HWND        hWnd;

        hWnd=GetDlgItem(hDlg, psh1);
        ShowWindow(hWnd, SW_HIDE);
        return TRUE;
        }

    return FALSE;
    }








/*
 * CPages::DevModeSet
 *
 * Purpose:
 *  Provides the Pages with the current printer information.
 *
 * Parameters:
 *  hDevMode        HGLOBAL to the memory containing the DEVMODE.
 *                  This function assumes responsibility for this
 *                  handle.
 *  hDevNames       HGLOBAL providing the driver name and device
 *                  name from which we can create a DC for
 *                  information.
 *
 * Return Value:
 *  BOOL            TRUE if we could accept this configuration,
 *                  FALSE otherwise.  If we return TRUE we also
 *                  delete the old memory we hold.
 */

BOOL CPages::DevModeSet(HGLOBAL hDevMode, HGLOBAL hDevNames)
    {
    LPDEVNAMES      pdn;
    LPTSTR          psz;
    //CHAPTER7MOD
    HGLOBAL         hMem;
    PDEVICECONFIG   pdc;
    LPDEVMODE       pdm;
    LPSTREAM        pIStream;
    HRESULT         hr;
    ULONG           cbDevMode, cbWrite;
    BOOL            fRet=FALSE;

    if (NULL==hDevMode || NULL==hDevNames)
        return FALSE;

    hr=m_pIStorage->OpenStream(SZSTREAMDEVICECONFIG, 0, STGM_DIRECT
        | STGM_WRITE | STGM_SHARE_EXCLUSIVE, 0, &pIStream);

    if (FAILED(hr))
        return FALSE;

    /*
     * DEVMODE is variable length--total length in hDevMode, so the
     * amount to write is that plus string space.  We subtract
     * sizeof(DEVMODE) as that is already included from GlobalSize.
     */
    cbDevMode=GlobalSize(hDevMode);
    cbWrite=cbDevMode+sizeof(DEVICECONFIG)-sizeof(DEVMODE);

    hMem=GlobalAlloc(GHND, cbWrite);

    if (NULL==hMem)
        {
        pIStream->Release();
        return FALSE;
        }

    pdc=(PDEVICECONFIG)GlobalLock(hMem);    //This always works
    pdm=(LPDEVMODE)GlobalLock(hDevMode);    //This might not

    if (NULL!=pdm)
        {
        pdc->cb=cbWrite;
        pdc->cbDevMode=cbDevMode;
        memcpy(&pdc->dm, pdm, (int)cbDevMode);
        GlobalUnlock(hDevMode);

        psz=(LPTSTR)GlobalLock(hDevNames);

        if (NULL!=psz)
            {
            pdn=(LPDEVNAMES)psz;
            lstrcpy(pdc->szDriver, psz+pdn->wDriverOffset);
            lstrcpy(pdc->szDevice, psz+pdn->wDeviceOffset);
            lstrcpy(pdc->szPort,   psz+pdn->wOutputOffset);

            pIStream->Write(pdc, cbWrite, &cbWrite);
            GlobalUnlock(hDevNames);
            fRet=TRUE;
            }
        }

    GlobalUnlock(hMem);
    GlobalFree(hMem);

    pIStream->Release();

    if (!fRet)
        return FALSE;

    GlobalFree(hDevNames);
    GlobalFree(hDevMode);

    //End CHAPTER7MOD
    return ConfigureForDevice();
    }




/*
 * CPages::DevModeGet
 *
 * Purpose:
 *  Retrieves a copy of the current DEVMODE structure for this
 *  Pages window.  The caller is responsible for this memory.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HGLOBAL         Handle to the memory containing the DEVMODE
 *                  structure.
 */

HGLOBAL CPages::DevModeGet(void)
    {
    //CHAPTER7MOD
    HGLOBAL         hMem;
    LPVOID          pv;
    ULONG           cbDevMode, cbRead;
    LARGE_INTEGER   li;
    LPSTREAM        pIStream;
    HRESULT         hr;

    hr=m_pIStorage->OpenStream(SZSTREAMDEVICECONFIG, 0, STGM_DIRECT
        | STGM_READ | STGM_SHARE_EXCLUSIVE, 0, &pIStream);

    if (FAILED(hr))
        return FALSE;

    //Read how much to allocate for the DEVMODE structure
    LISet32(li, CBSEEKOFFSETCBDEVMODE);
    pIStream->Seek(li, STREAM_SEEK_SET, NULL);
    pIStream->Read(&cbDevMode, sizeof(ULONG), &cbRead);

    hMem=GlobalAlloc(GHND, cbDevMode);

    if (NULL!=hMem)
        {
        pv=(LPVOID)GlobalLock(hMem);
        pIStream->Read(pv, cbDevMode, &cbRead);
        GlobalUnlock(hMem);
        }

    pIStream->Release();
    //End CHAPTER7MOD
    return hMem;
    }







/*
 * CPages::ConfigureForDevice
 *
 * Purpose:
 *  Recalculates our drawing configuration based on the contents of
 *  an hDC.  If no HDC is given we use the contents of our DevMode
 *  stream.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CPages::ConfigureForDevice(void)
    {
    POINT           ptOffset, ptPaper;
    RECT            rc;
    HDC             hDC;
    CHourglass      hg;
    //CHAPTER7MOD
    HGLOBAL         hMem;
    PDEVICECONFIG   pdc;
    HRESULT         hr;
    LARGE_INTEGER   li;
    LPSTREAM        pIStream;
    ULONG           cb, cbRead;

    //Read the DEVMODE and driver names from the header stream.
    hr=m_pIStorage->OpenStream(SZSTREAMDEVICECONFIG, 0, STGM_DIRECT
        | STGM_READ | STGM_SHARE_EXCLUSIVE, 0, &pIStream);

    if (FAILED(hr))
        return FALSE;

    //Read size of structure including variable portion of DEVMODE
    pIStream->Read(&cb, sizeof(DWORD), &cbRead);

    hMem=GlobalAlloc(GHND, cb);

    if (NULL==hMem)
        {
        pIStream->Release();
        return FALSE;
        }

    //Now get the real information.
    pdc=(PDEVICECONFIG)GlobalLock(hMem);
    LISet32(li, 0);
    pIStream->Seek(li, STREAM_SEEK_SET, NULL);
    pIStream->Read(pdc, cb, &cbRead);
    pIStream->Release();

    //Get the DC then configure
    hDC=CreateIC(pdc->szDriver, pdc->szDevice, pdc->szPort, &pdc->dm);

    //Got what we want, clean up the memory.
    GlobalUnlock(hMem);
    GlobalFree(hMem);
    //End CHAPTER7MOD

    if (NULL==hDC)
        return FALSE;

    //Get usable page dimensions:  already sensitive to orientation
    m_cx=GetDeviceCaps(hDC, HORZSIZE)*10-16; //*10: mm to LOMETRIC
    m_cy=GetDeviceCaps(hDC, VERTSIZE)*10-16; //-16: for driver bugs.

    //Calculate the printer-limited margins on sides in LOMETRIC.
    Escape(hDC, GETPRINTINGOFFSET, NULL, NULL, &ptOffset);
    Escape(hDC, GETPHYSPAGESIZE,   NULL, NULL, &ptPaper);

    SetRect(&rc, ptOffset.x, ptOffset.y, ptPaper.x, ptPaper.y);
    SetMapMode(hDC, MM_LOMETRIC);
    RectConvertMappings(&rc, hDC, FALSE);

    //Left and top margins are the printing offset.
    m_xMarginLeft= rc.left+8;   //+8 to match -16 above
    m_yMarginTop =-rc.top+8;    //LOMETRIC makes this negative.

    //Right is (paper width)-(usable width)-(left margin)
    m_xMarginRight =rc.right-m_cx-m_xMarginLeft;

    //Bottom is (paper height)-(usable height)-(top margin)+1
    m_yMarginBottom=-rc.bottom-m_cy-m_yMarginTop+1;

    UpdateScrollRanges();

    DeleteDC(hDC);
    return TRUE;
    }




/*
 * CPages::Print
 *
 * Purpose:
 *  Prints a specified range of pages to a given hDC.  Repeats for
 *  a given number of copies.
 *
 * Parameters:
 *  hDC             HDC to which we print.
 *  pszDoc          LPTSTR providing the document name.
 *  dwFlags         DWORD flags from PrintDlg
 *  iPageStart      UINT starting page index (one based)
 *  iPageEnd        UINT ending page index (one based).  Includes
 *                  this page.
 *  cCopies         UINT number of copies to print.  If PD_COLLATE
 *                  in dwFlags is set, we print multiple copies of
 *                  each page as we cycle through.  Otherwise we
 *                  cycle multiple times.
 *
 * Return Value:
 *  None
 */

BOOL CPages::Print(HDC hDC, LPTSTR pszDoc, DWORD dwFlags
    , UINT iPageStart, UINT iPageEnd, UINT cCopies)
    {
    BOOL        fError=FALSE;
    int         iPage, iPageInc;
    int         iUserPage, cPages;
    UINT        iRepeat, cRepeat;
    UINT        iCycle, cCycles;
    UINT        iPageHold=m_iPageCur;
    HWND        hWndT, hWndTop=NULL;
    DOCINFO     di;
    PCDocument  pDoc;

    //Validate hDC and page ranges
    if (NULL==hDC)
        return FALSE;

    if ((PD_PAGENUMS & dwFlags))
        {
        if (-1==iPageStart)
            iPageStart=0;
        else
            iPageStart--;   //Switch to zero offset.

        if (-1==iPageEnd)
            iPageEnd=m_cPages-1;
        else
            iPageEnd--;     //Switch to zero offset.
        }
    else //Can't test PD_ALLPAGES with & since it's defined as 0L
        {
        iPageStart=0;
        iPageEnd=m_cPages-1;
        }

    //Arrange cycles and repeats depending on cCopies and collating
    if (PD_COLLATE & dwFlags)
        {
        cCycles=cCopies;
        cRepeat=1;
        }
    else
        {
        cCycles=1;
        cRepeat=cCopies;
        }

    //Disable the frame window to prevent reentrancy while printing.
    hWndT=GetParent(m_hWnd);
    pDoc=(PCDocument)SendMessage(hWndT, DOCM_PDOCUMENT, 0, 0L);

    if (NULL!=pDoc)
        {
        PCFrame pFR;

        pFR=pDoc->FrameGet();
        hWndTop=pFR->Window();
        EnableWindow(hWndTop, FALSE);
        }

    SetAbortProc(hDC, AbortProc);
    g_fCancelPrint=FALSE;

    //If these don't work then we'll just live without a dialog.
    g_hDlgPrint=CreateDialog(m_hInst, MAKEINTRESOURCE(IDD_PRINTING)
        , hWndTop, PrintDlgProc);

    //Increment for either direction.
    iPageInc=(iPageStart > iPageEnd) ? -1 : 1;

    //Initial entries in dialog box.
    cPages=1+((int)(iPageEnd-iPageStart)*iPageInc);

    SendMessage(g_hDlgPrint, PRINTM_PAGEUPDATE, 1, (LPARAM)cPages);
    SendMessage(g_hDlgPrint, PRINTM_COPYUPDATE, 1, (LPARAM)cRepeat);

    di.cbSize=sizeof(DOCINFO);
    di.lpszDocName=pszDoc;
    di.lpszOutput=NULL;

    if (StartDoc(hDC, &di) > 0)
        {
        /*
         * Iterate over the pages, repeating each page depending on
         * the copies we want and if we have collate enabled.
         */

        for (iCycle=1; iCycle <= cCycles; iCycle++)
            {
            if (PD_COLLATE & dwFlags)
                {
                SendMessage(g_hDlgPrint, PRINTM_COPYUPDATE, iCycle
                    , (LPARAM)cCycles);
                }

            //iPageInc controls direction
            for (iPage=iPageStart; ; iPage+=iPageInc)
                {
                iUserPage=1+((iPage-(int)iPageStart)*iPageInc);

                SendMessage(g_hDlgPrint, PRINTM_PAGEUPDATE
                    , iUserPage, (LPARAM)cPages);

                m_iPageCur=iPage;   //We restore this later.

                for (iRepeat=1; iRepeat <= cRepeat; iRepeat++)
                    {
                    if (!(PD_COLLATE & dwFlags))
                        {
                        SendMessage(g_hDlgPrint, PRINTM_COPYUPDATE
                            , iRepeat, (LPARAM)cRepeat);
                        }

                    StartPage(hDC);
                    Draw(hDC, TRUE, TRUE);

                    if (EndPage(hDC) < 0)
                        fError=TRUE;

                    if (fError || g_fCancelPrint)
                        break;
                    }

                if (fError || g_fCancelPrint)
                    break;

                //If we just printed the last page, time to quit.
                if (iPage==(int)iPageEnd)
                    break;
                }

            if (fError || g_fCancelPrint)
                break;
            }

        if (!fError)
            EndDoc(hDC);
        else
            AbortDoc(hDC);
        }
    else
        fError=TRUE;

    //Set the page back to what it was before all this started.
    m_iPageCur=iPageHold;

    EnableWindow(hWndTop, TRUE);
    SetFocus(hWndTop);
    DestroyWindow(g_hDlgPrint);
    DeleteDC(hDC);
    return !fError;
    }






/*
 * AbortProc
 *
 * Purpose:
 *  Abort procedure for printing the pages.
 *
 * Parameters:
 *  hDC             HDC on which printing is happening.
 *  iErr            int error code.
 *
 * Return Value:
 *  BOOL            TRUE to continue the print job, FALSE otherwise.
 */

BOOL APIENTRY AbortProc(HDC hDC, int iErr)
    {
    MSG     msg;

    while (!g_fCancelPrint
        && PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
        if (NULL==g_hDlgPrint
            || !IsDialogMessage(g_hDlgPrint, &msg))
            {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            }
        }

    return !g_fCancelPrint;
    }




/*
 * PrintDlgProc
 *
 * Purpose:
 *  Modeless dialog procedure for the dialog displayed while Patron
 *  is printing pages.
 */

BOOL APIENTRY PrintDlgProc(HWND hDlg, UINT iMsg, WPARAM wParam
    , LPARAM lParam)
    {
    TCHAR           szFormat[40];
    TCHAR           szOutput[80];

    switch (iMsg)
        {
        case WM_INITDIALOG:
            EnableMenuItem(GetSystemMenu(hDlg, FALSE), SC_CLOSE
                , MF_GRAYED);
            return TRUE;

        case WM_COMMAND:
            //Cancel button was pressed.
            g_fCancelPrint=TRUE;
            ShowWindow(hDlg, SW_HIDE);
            return TRUE;

        case PRINTM_PAGEUPDATE:
            GetDlgItemText(hDlg, ID_PAGESTRING, szFormat
                , sizeof(szFormat));
            wsprintf(szOutput, szFormat, wParam, (UINT)lParam);
            SetDlgItemText(hDlg, ID_CURRENTPAGE, szOutput);
            return TRUE;

        case PRINTM_COPYUPDATE:
            GetDlgItemText(hDlg, ID_COPYSTRING, szFormat
                , sizeof(szFormat));
            wsprintf(szOutput, szFormat, wParam, (UINT)lParam);
            SetDlgItemText(hDlg, ID_CURRENTCOPY, szOutput);
            return TRUE;
        }

    return FALSE;
    }
