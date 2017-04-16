/*-----------------------------------------------------------------------------
    This is a part of the Microsoft Source Code Samples. 
    Copyright (C) 1995 Microsoft Corporation.
    All rights reserved. 
    This source code is only intended as a supplement to 
    Microsoft Development Tools and/or WinHelp documentation.
    See these sources for detailed information regarding the 
    Microsoft samples programs.

    MODULE:   Status.c

    PURPOSE:  Controls the status dialog at bottom of screen

    Functions:
        OpenStatusToolBar    - Creates the status dialog
        CreateStatusEditFont - Creates the status edit control font
        StatusDlgProc        - Status dialog procedure
        InitStatusMessage    - Initializes the status message mechanism
        StatusMessage        - Updates status edit control
        UpdateStatus         - Creates a status message node (entry point
                               for other threads
        ReportModemStatus    - Updates modem status controls
        CheckModemStatus     - Calls GetCommModemStatus and ReportModemStatus
        ReportComStat        - Updates comm status controls based on
                               COMSTAT structure (from ClearCommError)
        ReportCommError      - Reports comm errors when they occur
        ReportStatusEvent    - Reports comm events when they occur

-----------------------------------------------------------------------------*/

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "MTTTY.h"

#define MAX_STATUS_LENGTH       100

//
// Prototypes for functions called only within this file
//
void ReportStatusEvent( DWORD );
void ReportCommError( void );
void ReportModemStatus( DWORD );
BOOL CALLBACK StatusDlgProc( HWND, UINT, WPARAM, LPARAM );
void InitStatusMessage( void );


/*-----------------------------------------------------------------------------

FUNCTION: OpenStatusToolbar(HWND)

PURPOSE: Opens the modeless status dialog

PARAMETERS:
    hWnd - Handle of window which owns the dialog

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

/*-----------------------------------------------------------------------------*/
void OpenStatusToolbar(HWND hWnd)
{
    ghWndStatusDlg = CreateDialog(ghInst, MAKEINTRESOURCE(IDD_STATUSDIALOG), hWnd, StatusDlgProc);

    if (ghWndStatusDlg == NULL)
        ErrorReporter("CreateDialog (Status Dialog)");

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: CreateStatusEditFont

PURPOSE: Creates the font for the status edit control

RETURN: HFONT of new font created

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
HFONT CreateStatusEditFont()
{
    LOGFONT lf = {0};
    HFONT   hFont;

    lf.lfHeight         = 14 ;
    lf.lfCharSet        = ANSI_CHARSET ;
    lf.lfOutPrecision   = OUT_DEFAULT_PRECIS ;
    lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS ;
    lf.lfQuality        = DEFAULT_QUALITY ;
    lf.lfPitchAndFamily = VARIABLE_PITCH | FF_SWISS ;

    hFont = CreateFontIndirect(&lf);
    return hFont;
}

/*-----------------------------------------------------------------------------

FUNCTION: StatusDlgProc(HWND, UINT, WPARAM, LPARAM)

PURPOSE: Provides the dialog procedure for the status dialog

PARAMETERS:
    hWndDlg - Dialog window handle
    uMsg    - Window message
    wParam  - message parameter (depends on message)
    lParam  - message parameter (depends on message)

RETURN:
    TRUE if message is handled
    FALSE if message is not handled
    Exception is WM_INITDIALOG: returns FALSE since focus is not set

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
BOOL CALLBACK StatusDlgProc(HWND hWndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BOOL  fRet = FALSE;

    switch(uMsg)
    {
        case WM_INITDIALOG:     // setup dialog with defaults
            SendMessage(GetDlgItem(hWndDlg, IDC_STATUSEDIT), WM_SETFONT, (WPARAM)ghFontStatus, 0);
            InitStatusMessage();
            break;

        case WM_COMMAND: 
            {
                switch(LOWORD(wParam))
                {
                    case IDC_ABORTBTN:
                        SendMessage(ghwndMain, WM_COMMAND, ID_TRANSFER_ABORTSENDING, MAKELPARAM(IDC_ABORTBTN,0) );
                        fRet = TRUE;
                        break;

                    case IDC_STATCTS:
                    case IDC_STATDSR:
                    case IDC_STATRING:
                    case IDC_STATRLSD:
                        CheckModemStatus(TRUE);
                        fRet = TRUE;
                        break;

                    case IDC_CTSHOLDCHK:
                    case IDC_DSRHOLDCHK:
                    case IDC_RLSDHOLDCHK:
                    case IDC_XOFFHOLDCHK:
                    case IDC_XOFFSENTCHK:
                    case IDC_EOFSENTCHK:
                    case IDC_TXIMCHK:
                        CheckComStat(TRUE);
                        fRet = TRUE;
                        break;

                    default:
                        break;
                }
            }
            break;

        default:
            break;
    }    

    return fRet;
}

/*-----------------------------------------------------------------------------

FUNCTION: InitStatusMessage

PURPOSE: Initializes status message heap and linked list

HISTORY:   Date:      Author:     Comment:
           11/21/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void InitStatusMessage()
{
    SYSTEM_INFO SysInfo;

    GetSystemInfo(&SysInfo);
    ghStatusMessageHeap = HeapCreate(0, SysInfo.dwPageSize, 0);
    if (ghStatusMessageHeap == NULL)
        ErrorReporter("HeapCreate (Status message)");

    glpStatusMessageHead = HeapAlloc(ghStatusMessageHeap, HEAP_ZERO_MEMORY, sizeof(STATUS_MESSAGE));
    glpStatusMessageTail = glpStatusMessageHead;

    gnStatusIndex = 0;

    /*
        Queue the initial status message.
        This won't show up until the ReaderAndStatusProc function
        is called when the threads are created after the port is connected.
    */
    UpdateStatus("Status message go here:\r\n");

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: StatusMessage

PURPOSE: Retrieves status message from status message linked list
         and updates status edit control.

COMMENTS: Called from ReaderAndStatusProc when the status event
          has been set.  Clears edit control when number of characters
          exceeds MAX_STATUS_BUFFER.

HISTORY:   Date:      Author:     Comment:
           11/21/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void StatusMessage()
{
    STATUS_MESSAGE * lpStatusMessage;
    DWORD dwRes;
    HWND hEdit;
    BOOL bRes;

    hEdit = GetDlgItem (ghWndStatusDlg, IDC_STATUSEDIT);

    /*
        If status control has a lot of characters in it,
        then wipe them out and start over
    */
    if (gnStatusIndex > MAX_STATUS_BUFFER) {
        SendMessageTimeout( hEdit, EM_SETSEL, 
                            (WPARAM) (INT) 0, (LPARAM) (INT) -1,
                            SMTO_NORMAL | SMTO_ABORTIFHUNG, 
                            500, &dwRes);
        SendMessageTimeout( hEdit, EM_REPLACESEL, 
                            0, (LPARAM) "",
                            SMTO_NORMAL | SMTO_ABORTIFHUNG, 
                            500, &dwRes);
        gnStatusIndex = 0;
    }

    //
    // Loop through each node in the status message linked list.
    //
    for ( lpStatusMessage = glpStatusMessageHead->lpNext ; lpStatusMessage ; )
    {
        //
        // if global quit event is set, then just exit this loop
        //
        if (WaitForSingleObject(ghThreadExitEvent, 0) == WAIT_OBJECT_0)
            break;

        // 
        // Place each status message into the status control.
        //
        SendMessageTimeout( hEdit, EM_SETSEL, 
                            gnStatusIndex, gnStatusIndex, 
                            SMTO_NORMAL | SMTO_ABORTIFHUNG, 
                            500, &dwRes);
        SendMessageTimeout( hEdit, EM_REPLACESEL, 
                            0, (LPARAM) ((LPSTR) &(lpStatusMessage->chMessageStart)),
                            SMTO_NORMAL | SMTO_ABORTIFHUNG, 
                            500, &dwRes);
        gnStatusIndex += strlen(&(lpStatusMessage->chMessageStart));

        //
        // Update status message linked list
        //
        EnterCriticalSection(&gStatusCritical);

        bRes = HeapFree(ghStatusMessageHeap, 0, glpStatusMessageHead);
        
        glpStatusMessageHead = lpStatusMessage;
        lpStatusMessage = lpStatusMessage->lpNext;

        LeaveCriticalSection(&gStatusCritical);

        if (!bRes)
            ErrorReporter("HeapFree (status message)");
    }

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: UpdateStatus(char *)

PURPOSE: Places the passed in string into the status message linked 
         list and sets the event to make the message display.

PARAMETERS:
    szText - message to be placed in the status control

COMMENTS: Synchronization needed in order to ensure that only
          one thread at a time places a string in the list

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it
           11/21/95   AllenD      Modified to use a status message heap

-----------------------------------------------------------------------------*/
void UpdateStatus(char * szText)
{
    char * szNewMsg;
    DWORD dwSize;
    STATUS_MESSAGE * lpStatusMessage;
    static dwMessageCounter = 0;

    dwMessageCounter++;

    dwSize = strlen(szText) + 30;    // include NULL terminator and space for counter

    EnterCriticalSection(&gStatusCritical);

    szNewMsg = HeapAlloc(ghStatusMessageHeap, 0, dwSize+30);
    if (szNewMsg == NULL) {
        LeaveCriticalSection(&gStatusCritical);
        ErrorReporter("HeapAlloc (status message)");
        return;
    }
    else {
        wsprintf(szNewMsg, "%d:%s", dwMessageCounter, szText);
        if (strlen(szNewMsg) > dwSize) {
            LeaveCriticalSection(&gStatusCritical);
            ErrorInComm("Heap Corruption in UpdateStatus\n");
        }
    }

    lpStatusMessage = HeapAlloc(ghStatusMessageHeap, 0, sizeof(LPSTR) + dwSize );
    if (lpStatusMessage == NULL) {
        LeaveCriticalSection(&gStatusCritical);
        ErrorReporter("HeapAlloc (status message)");
        return ;
    }
      
    lpStatusMessage->lpNext = NULL;
    glpStatusMessageTail->lpNext = lpStatusMessage;
    glpStatusMessageTail = lpStatusMessage;
    CopyMemory(&(lpStatusMessage->chMessageStart), szNewMsg, dwSize);
    LeaveCriticalSection(&gStatusCritical);

    SetEvent(ghStatusMessageEvent);

    return ;
}

/*-----------------------------------------------------------------------------

FUNCTION: ReportModemStatus(DWORD)

PURPOSE: Reports modem status line states

PARAMETERS:
    dwModemStatus - current modem status flag

COMMENTS: Checks each button according to the state

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void ReportModemStatus(DWORD dwModemStatus)
{
    BOOL fCTS, fDSR, fRING, fRLSD;
    BOOL fStat[4];
    int  i;

    fCTS = fStat[0] = MS_CTS_ON & dwModemStatus;
    fDSR = fStat[1] = MS_DSR_ON & dwModemStatus;
    fRING = fStat[2] = MS_RING_ON & dwModemStatus;
    fRLSD = fStat[3] = MS_RLSD_ON & dwModemStatus;

    for (i = IDC_STATCTS; i <= IDC_STATRLSD; i++)
        CheckDlgButton(ghWndStatusDlg, i, fStat[i-IDC_STATCTS] ? 1 : 0);

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: CheckModemStatus(BOOL)

PURPOSE: Check new status and possibly report it

PARAMETERS:
    bUpdateNow - if TRUE, update should be done
                 if FALSE, update is done only if status is different

COMMENTS: Reports status if bUpdateNow is true or
          new status is different from old status

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void CheckModemStatus( BOOL bUpdateNow )
{
    //
    // dwOldStatus needs to be static so that it is maintained 
    // between function calls by the same thread.
    // It also needs to be __declspec(thread) so that it is 
    // initialized when a new thread is created.
    //

    __declspec(thread) static DWORD dwOldStatus = 0;

    DWORD dwNewModemStatus;

    if (!GetCommModemStatus(COMDEV(TTYInfo), &dwNewModemStatus))
        ErrorReporter("GetCommModemStatus");

    //
    // Report status if bUpdateNow is true or status has changed
    //
    if (bUpdateNow || (dwNewModemStatus != dwOldStatus)) {
        ReportModemStatus(dwNewModemStatus);
        dwOldStatus = dwNewModemStatus;
    }

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: ReportComStat( COMSTAT )

PURPOSE: Update status dialog controls based on the COMSTAT structure

PARAMETERS:
    ComStat - comstat structure used to update comm stat controls.  

HISTORY:   Date:      Author:     Comment:
           12/01/95   AllenD      Wrote it
           12/18/95   AllenD      Modified it

-----------------------------------------------------------------------------*/
void ReportComStat(COMSTAT ComStat)
{
    CheckDlgButton(ghWndStatusDlg, IDC_CTSHOLDCHK, ComStat.fCtsHold);
    CheckDlgButton(ghWndStatusDlg, IDC_DSRHOLDCHK, ComStat.fDsrHold);
    CheckDlgButton(ghWndStatusDlg, IDC_RLSDHOLDCHK, ComStat.fRlsdHold);
    CheckDlgButton(ghWndStatusDlg, IDC_XOFFHOLDCHK, ComStat.fXoffHold);
    CheckDlgButton(ghWndStatusDlg, IDC_XOFFSENTCHK, ComStat.fXoffSent);
    CheckDlgButton(ghWndStatusDlg, IDC_EOFSENTCHK, ComStat.fEof);
    CheckDlgButton(ghWndStatusDlg, IDC_TXIMCHK, ComStat.fTxim);

    SetDlgItemInt(ghWndStatusDlg, IDC_TXCHAREDIT, ComStat.cbOutQue, FALSE);
    SetDlgItemInt(ghWndStatusDlg, IDC_RXCHAREDIT, ComStat.cbInQue, FALSE);

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: CheckComStat(BOOL)

PURPOSE: Calls ClearCommError and reports the results.

PARAMETERS:
    bUpdateNow - If TRUE, then ReportComStat is called with new results.
                 if FALSE, then ReportComStat is called only if
                 new results differ from old.

COMMENTS: Called when the ReaderAndStatusProc times out after waiting on
          its event handles.  Also called from ReportStatusEvent.

HISTORY:   Date:      Author:     Comment:
           12/18/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void CheckComStat(BOOL bUpdateNow)
{
    COMSTAT ComStatNew;
    DWORD dwErrors;

    __declspec(thread) static COMSTAT ComStatOld = {0};
    __declspec(thread) static DWORD dwErrorsOld = 0;

    BOOL bReport = bUpdateNow;

    if (!ClearCommError(COMDEV(TTYInfo), &dwErrors, &ComStatNew))
        ErrorReporter("ClearCommError");

    if (dwErrors != dwErrorsOld) {
        bReport = TRUE;
        dwErrorsOld = dwErrors;
    }

    if (memcmp(&ComStatOld, &ComStatNew, sizeof(COMSTAT))) {
        bReport = TRUE;
        ComStatOld = ComStatNew;
    }
    
    if (bReport)
        ReportComStat(ComStatNew);

    ComStatOld = ComStatNew;

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: ReportCommError

PURPOSE: Calls ClearCommError and reports the results

COMMENTS: This function is called if EV_ERR occurs and is called
          when the ReaderAndStatusProc times out after waiting on
          its event handles.

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void ReportCommError()
{
    COMSTAT comStat;
    DWORD   dwErrors;
    BOOL    fOOP, fOVERRUN, fPTO, fRXOVER, fRXPARITY, fTXFULL;
    BOOL    fBREAK, fDNS, fFRAME, fIOE, fMODE;
    char    szMessage[100];

    //
    // Get and clear current errors on the port
    //
    if (!ClearCommError(COMDEV(TTYInfo), &dwErrors, &comStat))
        ErrorReporter("ClearCommError");

    //
    // get error flags
    //
    fDNS = dwErrors & CE_DNS;
    fIOE = dwErrors & CE_IOE;
    fOOP = dwErrors & CE_OOP;
    fPTO = dwErrors & CE_PTO;
    fMODE = dwErrors & CE_MODE;
    fBREAK = dwErrors & CE_BREAK;
    fFRAME = dwErrors & CE_FRAME;
    fRXOVER = dwErrors & CE_RXOVER;
    fTXFULL = dwErrors & CE_TXFULL;
    fOVERRUN = dwErrors & CE_OVERRUN;
    fRXPARITY = dwErrors & CE_RXPARITY;

    //
    // create error string
    //
    strcpy(szMessage, "ERROR: ");
    strcat(szMessage, fDNS ? "DNS " : "");
    strcat(szMessage, fIOE ? "IOE " : "");
    strcat(szMessage, fOOP ? "OOP " : "");
    strcat(szMessage, fPTO ? "PTO " : "");
    strcat(szMessage, fMODE ? "MODE " : "");
    strcat(szMessage, fBREAK ? "BREAK " : "");
    strcat(szMessage, fFRAME ? "FRAME " : "");
    strcat(szMessage, fRXOVER ? "RXOVER " : "");
    strcat(szMessage, fTXFULL ? "TXFULL " : "");
    strcat(szMessage, fOVERRUN ? "OVERRUN " : "");
    strcat(szMessage, fRXPARITY ? "RXPARITY " : "");

    strcat(szMessage, "\r\n");

    //
    // if there really were errors, then report them
    //
    if (dwErrors)
        UpdateStatus(szMessage);
    
    //
    // Report info from the COMSTAT structure
    //
    ReportComStat(comStat);

    //
    // Show COMSTAT structure with the error indicator
    //
    if (comStat.fCtsHold)
        UpdateStatus("Tx waiting for CTS signal.\r\n");

    if (comStat.fDsrHold)
        UpdateStatus("Tx waiting for DSR signal.\r\n");

    if (comStat.fRlsdHold)
        UpdateStatus("Tx waiting for RLSD signal.\r\n");

    if (comStat.fXoffHold)
        UpdateStatus("Tx waiting, XOFF char rec'd.\r\n");

    if (comStat.fXoffSent)
        UpdateStatus("Tx waiting, XOFF char sent.\r\n");
    
    if (comStat.fEof)
        UpdateStatus("EOF character received.\r\n");
    
    if (comStat.fTxim)
        UpdateStatus("Character waiting for Tx.\r\n");

    if (comStat.cbInQue) {
        wsprintf(szMessage, "%d bytes in input buffer.\r\n", comStat.cbInQue);
        UpdateStatus(szMessage);
    }

    if (comStat.cbOutQue) {
        wsprintf(szMessage, "%d bytes in output buffer.\r\n", comStat.cbOutQue);
        UpdateStatus(szMessage);
    }

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: ReportStatusEvent(DWORD)

PURPOSE: Report a comm status event

PARAMETERS:
    dwStatus - status event flag from WaitCommEvent

COMMENTS: This is different than line status (aka Modem Status).

NOTE: EV_RING isn't detected on Windows 95.  This is a known problem.
      A workaround to the problem is to rely on GetCommModemStatus, or
      set the modem to send a "RING" and have the app detect it.

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

/*-----------------------------------------------------------------------------*/
void ReportStatusEvent(DWORD dwStatus)
{
    BOOL fRING, fRLSD, fRXCHAR, fRXFLAG, fTXEMPTY;
    BOOL fBREAK, fCTS, fDSR, fERR;
    char szMessage[70];

    //
    // Get status event flags.
    //
    fCTS = EV_CTS & dwStatus;
    fDSR = EV_DSR & dwStatus;
    fERR = EV_ERR & dwStatus;
    fRING = EV_RING & dwStatus;
    fRLSD = EV_RLSD & dwStatus;
    fBREAK = EV_BREAK & dwStatus;
    fRXCHAR = EV_RXCHAR & dwStatus;
    fRXFLAG = EV_RXFLAG & dwStatus;
    fTXEMPTY = EV_TXEMPTY & dwStatus;

    /*
        Construct status message indicating the 
        status event flags that are set.
    */
    strcpy(szMessage, "EVENT: ");
    strcat(szMessage, fCTS ? "CTS " : "");
    strcat(szMessage, fDSR ? "DSR " : "");
    strcat(szMessage, fERR ? "ERR " : "");
    strcat(szMessage, fRING ? "RING " : "");
    strcat(szMessage, fRLSD ? "RLSD " : "");
    strcat(szMessage, fBREAK ? "BREAK " : "");
    strcat(szMessage, fRXFLAG ? "RXFLAG " : "");
    strcat(szMessage, fRXCHAR ? "RXCHAR " : "");
    strcat(szMessage, fTXEMPTY ? "TXEMPTY " : "");

    /*
        If dwStatus == NULL, then no status event flags are set.
        This happens when the event flag is changed with SetCommMask.
    */
    if (dwStatus == 0x0000)
        strcat(szMessage, "NULL");

    strcat(szMessage, "\r\n");

    //
    // Queue the status message for the status control
    // 
    UpdateStatus(szMessage);

    /*
        If an error flag is set in the event flag, then
        report the error with the status message
        If not, then just report the comm status.
    */
    if (fERR)
        ReportCommError();
    
    /*
        Might as well check the modem status and comm status now since
        the event may have been caused by a change in line status.
        Line status is indicated by the CheckModemStatus function.
    */
    CheckModemStatus( FALSE );

    /*
        Since line status can affect sending/receiving when 
        hardware flow-control is used, ReportComStat should 
        be called to show comm status.  This is called only if no error
        was reported in the event flag.  If an error was reported, then
        ReportCommError was called above and CheckComStat was already called
        in that function.
    */
    if (!fERR)
        CheckComStat( FALSE );

    return;
}
