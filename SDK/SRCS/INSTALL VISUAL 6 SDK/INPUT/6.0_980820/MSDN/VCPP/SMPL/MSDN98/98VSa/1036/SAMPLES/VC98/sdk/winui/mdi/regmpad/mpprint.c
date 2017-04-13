/***************************************************************************
 *                                                                         *
 *  MODULE      : MpPrint()                                                *
 *                                                                         *
 *  PURPOSE     : Printing code for MultiPad.                              *
 *                                                                         *
 *  FUNCTIONS   : GetPrinterDC ()          -  Creates a printer DC for the *
 *                                            default device.              *
 *                                                                         *
 *                AbortProc ()             -  Export proc. for GDI to check*
 *                                            print abort.                 *
 *                                                                         *
 *                PrintDlgProc ()          -  Dialog function for the print*
 *                                            cancel dialog.               *
 *                                                                         *
 *                PrintFile ()             -  Prints the contents of the   *
 *                                            edit control.                *
 *                                                                         *
 *                GetInitializationData () -  Gets DC initialisation data  *
 *                                            from a DC supporting         *
 *                                            ExtDeviceMode().                   *
 *                                                                         *
 ***************************************************************************/
#include "multipad.h"

BOOL fAbort;            /* TRUE if the user has aborted the print job    */
HWND hwndPDlg;          /* Handle to the cancel print dialog             */
CHAR szDevice[160];     /* Contains the device, the driver, and the port */
PSTR szDriver;          /* Pointer to the driver name                    */
PSTR szPort;            /* Port, ie, LPT1                                */
PSTR szTitle;           /* Global pointer to job title                   */
INT iPrinter = 0;       /* level of available printer support.           */
                        /* 0 - no printer available                      */
                        /* 1 - printer available                         */
                        /* 2 - driver supports 3.0 device initialization */
HANDLE hInitData=NULL;  /* handle to initialization data                 */

CHAR szExtDeviceMode[] = "EXTDEVICEMODE";

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : GetPrinterDC ()                                            *
 *                                                                          *
 *  PURPOSE    : Creates a printer display context for the default device.  *
 *               As a side effect, it sets the szDevice and szPort variables*
 *               It also sets iPrinter to the supported level of printing.  *
 *                                                                          *
 *  RETURNS    : HDC   - A handle to printer DC.                            *
 *                                                                          *
 ****************************************************************************/
HDC APIENTRY GetPrinterDC(BOOL bInformation)
{
    HDC      hdc;
    LPDEVMODE  lpdevmode = NULL;

    iPrinter = 0;

    /* Get the printer information from win.ini into a buffer and
     * null terminate it.
     */
    GetProfileString ( "windows", "device", "" ,szDevice, sizeof(szDevice));
    for (szDriver = szDevice; *szDriver && *szDriver != ','; szDriver++)
        ;
    if (*szDriver)
        *szDriver++ = 0;

    /* From the current position in the buffer, null teminate the
     * list of ports
     */
    for (szPort = szDriver; *szPort && *szPort != ','; szPort++)
        ;
    if (*szPort)
        *szPort++ = 0;

    /* if the device, driver and port buffers all contain meaningful data,
     * proceed.
     */
    if (!*szDevice || !*szDriver || !*szPort){
        *szDevice = 0;
        return NULL;
    }

    /* Create the printer display context */
    if (hInitData){
        /* Get a pointer to the initialization data */
        lpdevmode = (LPDEVMODE) LocalLock (hInitData);

        if (lstrcmp (szDevice, (LPSTR)lpdevmode)){
            /* User has changed the device... cancel this setup, as it is
             * invalid (although if we worked harder we could retain some
             * of it).
             */
            lpdevmode = NULL;
            LocalUnlock (hInitData);
            LocalFree (hInitData);
            hInitData = NULL;
        }
    }

    if (bInformation)
      hdc = CreateIC (szDriver, szDevice, szPort, lpdevmode);
   else
      hdc = CreateDC (szDriver, szDevice, szPort, lpdevmode);

    /* Unlock initialization data */
    if (hInitData)
        LocalUnlock (hInitData);

    if (!hdc)
        return NULL;


    iPrinter = 1;

    /* Find out if ExtDeviceMode() is supported and set flag appropriately */
    if (GetProcAddress (LoadLibrary(szDriver), szExtDeviceMode))
        iPrinter = 2;

    return hdc;

}

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : AbortProc()                                                *
 *                                                                          *
 *  PURPOSE    : To be called by GDI print code to check for user abort.    *
 *                                                                          *
 ****************************************************************************/
INT APIENTRY AbortProc (
        HDC hdc,
        WORD reserved)
{
    MSG msg;

    /* Allow other apps to run, or get abort messages */
    while (!fAbort && PeekMessage (&msg, NULL, 0, 0, TRUE))
        if (!hwndPDlg || !IsDialogMessage (hwndPDlg, &msg)){
            TranslateMessage (&msg);
            DispatchMessage  (&msg);
        }
    return !fAbort;

        UNREFERENCED_PARAMETER(hdc);
        UNREFERENCED_PARAMETER(reserved);
}

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : PrintDlgProc ()                                            *
 *                                                                          *
 *  PURPOSE    : Dialog function for the print cancel dialog box.           *
 *                                                                          *
 *  RETURNS    : TRUE  - OK to abort/ not OK to abort                       *
 *               FALSE - otherwise.                                         *
 *                                                                          *
 ****************************************************************************/
BOOL APIENTRY PrintDlgProc(HWND hwnd, UINT msg, WORD wParam, LONG lParam)
{
    switch (msg){
        case WM_INITDIALOG:
            /* Set up information in dialog box */
            SetDlgItemText (hwnd, IDD_PRINTDEVICE, (LPSTR)szDevice);
            SetDlgItemText (hwnd, IDD_PRINTPORT, (LPSTR)szPort);
            SetDlgItemText (hwnd, IDD_PRINTTITLE, (LPSTR)szTitle);
            break;

        case WM_COMMAND:
            /* abort printing if the only button gets hit */
            fAbort = TRUE;
            break;

        default:
            return FALSE;
    }
    return TRUE;
        UNREFERENCED_PARAMETER(wParam);
        UNREFERENCED_PARAMETER(lParam);
}

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : PrintFile ()                                               *
 *                                                                          *
 *  PURPOSE    : Prints the contents of the edit control.                   *
 *                                                                          *
 ****************************************************************************/

VOID APIENTRY PrintFile(HWND hwnd)
{
    HDC     hdc;
    INT     yExtPage;
    CHAR    sz[32];
    int     cch;
    WORD    ich;
    PSTR    pch;
    WORD    iLine;
    WORD    nLinesEc;
    WORD    i;
    HANDLE  hT;
    HWND    hwndPDlg;
    DWORD   dy;
    INT     yExtSoFar;
    WORD    fError = TRUE;
    HWND    hwndEdit;

    hwndEdit = (HWND)GetWindowLong(hwnd,GWL_HWNDEDIT);

    /* Create the job title by loading the title string from STRINGTABLE */
    cch = LoadString (hInst, IDS_PRINTJOB, sz, sizeof(sz));
    szTitle = sz + cch;
    cch += GetWindowText (hwnd, sz + cch, 32 - cch);
    sz[31] = 0;

    /* Initialize the printer */
    hdc = GetPrinterDC(FALSE);
    if (!hdc)
        goto getout5;

    /* Disable the main application window and create the Cancel dialog */
    EnableWindow (hwndFrame, FALSE);

    hwndPDlg = CreateDialog (hInst, IDD_PRINT, hwnd, (DLGPROC) PrintDlgProc);

    if (!hwndPDlg)
        goto getout3;
    ShowWindow (hwndPDlg, SW_SHOW);
    UpdateWindow (hwndPDlg);

    /* Allow the app. to inform GDI of the escape function to call */
    if (Escape(hdc, SETABORTPROC, 0, (LPSTR)AbortProc, NULL) < 0)
        goto getout1;

    /* Initialize the document */
    if (Escape(hdc, STARTDOC, cch, (LPSTR)sz, NULL) < 0)
        goto getout1;

    /* Get the height of one line and the height of a page */
    {
    SIZE tmp;
    GetTextExtentPoint(hdc, "CC", 2, &tmp );
    dy = tmp.cy;
    }

    yExtPage = GetDeviceCaps(hdc, VERTRES);

    /* Get the lines in document and and a handle to the text buffer */
    iLine     = 0;
    yExtSoFar = 0;
    nLinesEc  = (WORD)SendMessage (hwndEdit, EM_GETLINECOUNT, 0, 0L);
    hT        = (HANDLE)SendMessage (hwndEdit, EM_GETHANDLE, 0, 0L);

    /* While more lines print out the text */
    while (iLine < nLinesEc){
        if (yExtSoFar + (int) dy > yExtPage){
            /* Reached the end of a page. Tell the device driver to eject a
             * page
             */
            if (Escape(hdc, NEWFRAME, 0, NULL, NULL) < 0 || fAbort)
                goto getout2;
            yExtSoFar = 0;
        }

        /* Get the length and position of the line in the buffer
         * and lock from that offset into the buffer */
        ich = (WORD)SendMessage (hwndEdit, EM_LINEINDEX, iLine, 0L);
        cch = (WORD)SendMessage (hwndEdit, EM_LINELENGTH, ich, 0L);
        pch = (PSTR)LocalLock(hT) + ich;

        /* Print the line and unlock the text handle */
        TextOut (hdc, 0, yExtSoFar, (LPSTR)pch, cch);
        LocalUnlock (hT);

        /* Test and see if the Abort flag has been set. If yes, exit. */
        if (fAbort)
            goto getout2;

        /* Move down the page */
        yExtSoFar += dy;
        iLine++;
    }

    /* Eject the last page. */
    if (Escape(hdc, NEWFRAME, 0, NULL, NULL) < 0)
        goto getout2;

    /* Complete the document. */
    if (Escape(hdc, ENDDOC, 0, NULL, NULL) < 0){
getout2:
        /* Ran into a problem before NEWFRAME? Abort the document */
        Escape( hdc, ABORTDOC, 0, NULL, NULL);
    }
    else
        fError=FALSE;

getout3:
    /* Close the cancel dialog and re-enable main app. window */
    EnableWindow (hwndFrame, TRUE);
    DestroyWindow (hwndPDlg);

getout1:
    DeleteDC(hdc);

getout5:
#ifdef WIN16
    /* Get rid of dialog procedure instances */
    FreeProcInstance (lpfnPDlg);
#endif

#ifdef WIN16
getout4:
    FreeProcInstance (lpfnAbort);
getout:
#endif

    /* Error? make sure the user knows... */
    if (fError)
        MPError (hwnd, MB_OK | MB_ICONEXCLAMATION, IDS_PRINTERROR, (LPSTR)szTitle);

    return;
        UNREFERENCED_PARAMETER(i);
}

/****************************************************************************
 *                                                                          *
 *  FUNCTION   : GetInitializationData()                                    *
 *                                                                          *
 *  PURPOSE    : Gets DC initialization data from a printer driver          *
 *               supporting ExtDeviceMode(). Called in response to the      *
 *               File/Printer setup menu selection.                         *
 *                                                                          *
 *               This function allows the user to change the printer        *
 *               settings FOR MULTIPAD ONLY.  This allows Multipad to print *
 *               in a variety of settings without messing up any other      *
 *               applications. In a more sophisticated application, this    *
 *               setup could even be saved on a document-by-document basis. *
 *                                                                          *
 ****************************************************************************/
BOOL APIENTRY GetInitializationData( HWND hwnd )
{
    LPSTR     lpOld;
    LPSTR     lpNew;
    FARPROC   lpfn;
    HANDLE    hT,hDrv;
    CHAR      sz[32];
    int           cb;
    INT       flag;

    /* Pop up dialog for user and retain data in app buffer */
    flag = DM_PROMPT | DM_COPY;

    /* Load the device driver and find the ExtDeviceMode() function */
    wsprintf (sz, "%s.drv", (LPSTR)szDriver);
    if ((int)(hDrv = LoadLibrary (sz)) < 32)
        return FALSE;
    if (!(lpfn = GetProcAddress (hDrv, szExtDeviceMode)))
        return FALSE;

    if (hInitData){
        /* We have some old data... we want to modify the previously specified
         * setup rather than starting with the default setup.
         */
        lpOld = (LPSTR)LocalLock(hInitData);
        flag |= DM_MODIFY;
    }
    else
        lpOld = NULL;

    /* Get the number of bytes needed for the init data */
    cb = (*lpfn) (hwnd,
                  hDrv,
                  (LPDEVMODE)NULL,
                  (LPSTR)szDevice,
                  (LPSTR)szPort,
                  (LPDEVMODE)NULL,
                  (LPSTR)NULL,
                  0);

    /* Grab some memory for the new data and lock it. */
    hT    = LocalAlloc (LHND,cb);
    if(!hT){
        MessageBox(hwnd, "<GetInitializationData> Not enough memory.", NULL, MB_OK | MB_ICONHAND);
            LocalUnlock(hInitData);
            LocalFree(hInitData);
        FreeLibrary(hDrv);
        return(FALSE);
    }

    lpNew = (LPSTR)LocalLock (hT);

    /* Post the device mode dialog. 0 flag iff user hits OK button */
    if ((*lpfn) (hwnd,
                 hDrv,
                 (LPDEVMODE)lpNew,
                 (LPSTR)szDevice,
                 (LPSTR)szPort,
                 (LPDEVMODE)lpOld,
                 (LPSTR)NULL,
                 flag)==IDOK)
        flag = 0;

    /* Unlock the input structures */
    LocalUnlock (hT);

    if (hInitData)
        LocalUnlock (hInitData);

    /* If the user hit OK and everything worked, free the original init.
     * data and retain the new one.  Otherwise, toss the new buffer.
     */
    if (flag)
        LocalFree (hT);
    else{
        if (hInitData)
            LocalFree (hInitData);
        hInitData = hT;
    }

    FreeLibrary(hDrv);
    return (!flag);
}
