/*-----------------------------------------------------------------------------
    This is a part of the Microsoft Source Code Samples. 
    Copyright (C) 1995 Microsoft Corporation.
    All rights reserved. 
    This source code is only intended as a supplement to 
    Microsoft Development Tools and/or WinHelp documentation.
    See these sources for detailed information regarding the 
    Microsoft samples programs.

    MODULE: Transfer.c

    PURPOSE: Transfer a file (receive or send).

    FUNCTIONS:
        TransferRepeatCreate   - Preps program for a repeated send
        TransferRepeatDestroy  - Completes a repeated send
        TransferRepeatDo       - Sends the data to the writer thread
        TransferFileTextStart  - Preps program for a text file send
        TransferFileTextEnd    - Completes a file transfer
        TransferThreadProc     - Thread procedure to do actual transfer
        TransferFileText       - Preps program for a text file send
        ReceiveFileText        - Preps program for a text file capture
        OpenTheFile            - Opens a file
        CreateTheFile          - Creates a file
        GetTransferSizes       - Determines transfer metrics from file and buffer sizes
        ShowTransferStatistics - Displays transfer stats
        CheckForMessges        - Peek message check to keep things flowing
                                 during a transfer
        SendFile               - Send a file
        CaptureFile            - Sets the receive state for file capture
       
-----------------------------------------------------------------------------*/

#include <windows.h>
#include <commctrl.h>
#include "mttty.h"

//
// Globals used in this file only
//
HANDLE hFile;
HANDLE hTransferAbortEvent;
HANDLE hTransferThread;
UINT   uTimerId;
MMRESULT mmTimer = (MMRESULT)NULL;
char * lpBuf;
//
// Prototypes for functions called only within this file
//
DWORD WINAPI TransferThreadProc(LPVOID);
HANDLE OpenTheFile( LPCTSTR );
HANDLE CreateTheFile( LPCTSTR );
void CaptureFile( HANDLE, HWND );
UINT CheckForMessages( void );
BOOL GetTransferSizes( HANDLE, DWORD *, DWORD *, DWORD *);


/*-----------------------------------------------------------------------------

FUNCTION: TransferRepeatCreate(LPCTSTR, DWORD)

PURPOSE: Prepares program for a repeated text file transfer (send)

PARAMETERS:
    lpstrFileName - name of file selected to send
    dwFrequency   - frequency of timer

COMMENTS: This function sets up a window timer to fire off
          every so often.  When it fires, TransferRepeatDo is
          called with the same name as above.  This causes the file transfer
          to actuall take place.
          TransferRepeatDestroy is called to kill the timer.
          This function disables certain menu items that should not be
          available for the duration of a repeated send even if the actual
          Tx is not taking place.

HISTORY:   Date:      Author:     Comment:
            1/29/96   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void TransferRepeatCreate(LPCTSTR lpszFileName, DWORD dwFrequency)
{
    HMENU hMenu;
    UINT  MenuFlags ;
    DWORD dwFileSize;
    DWORD dwMaxPackets;
    DWORD dwPacketSize;
    DWORD dwRead;

    //
    // open the file
    //
    hFile = OpenTheFile(lpszFileName);
    if (hFile == INVALID_HANDLE_VALUE)
        return;

    //
    // modify transfer menu
    //
    hMenu = GetMenu(ghwndMain);
    MenuFlags = MF_DISABLED | MF_GRAYED;
    EnableMenuItem(hMenu, ID_TRANSFER_SENDFILETEXT, MenuFlags);
    EnableMenuItem(hMenu, ID_TRANSFER_SENDREPEATEDLY, MenuFlags);
    EnableMenuItem(hMenu, ID_TRANSFER_ABORTREPEATEDSENDING, MF_ENABLED);
    EnableMenuItem(hMenu, ID_TRANSFER_RECEIVEFILETEXT, MenuFlags);

    //
    // enable abort button and progress bar
    //
    SetWindowText(GetDlgItem(ghWndStatusDlg, IDC_ABORTBTN), "Abort Tx");
    ShowWindow(GetDlgItem(ghWndStatusDlg, IDC_ABORTBTN), SW_SHOW);

    if (!GetTransferSizes(hFile, &dwPacketSize, &dwMaxPackets, &dwFileSize)) {
        TransferRepeatDestroy();
        return;
    }

    // Allocate a buffer
    lpBuf = HeapAlloc(ghWriterHeap, 0, dwFileSize);
    if (lpBuf == NULL) {
        ErrorReporter("HeapAlloc (data block from writer heap).\r\nFile is too large");
        TransferRepeatDestroy();
        return;
    }

    // fill the buffer
    if (!ReadFile(hFile, lpBuf, dwFileSize, &dwRead, NULL)) {
        ErrorReporter("Can't read from file\n");
        TransferRepeatDestroy();
    }

    if (dwRead != dwFileSize)
        ErrorReporter("Didn't read entire file\n");
        
    mmTimer = timeSetEvent((UINT) dwFrequency, 10, TransferRepeatDo, dwRead, TIME_PERIODIC);
    if (mmTimer == (MMRESULT) NULL) {
        ErrorReporter("Could not create mm timer");
        TransferRepeatDestroy();
    }
    else {
        REPEATING(TTYInfo) = TRUE;
        OutputDebugString("Timer setup.\n");
    }

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: TransferRepeatDestroy( void )

PURPOSE: Stops a repeated text file transfer (send)

COMMENTS: Kills the repeated-send timer.

HISTORY:   Date:      Author:     Comment:
            1/29/96   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void TransferRepeatDestroy()
{
    HMENU hMenu;
    DWORD MenuFlags;
    MMRESULT mmRes;

    if (mmTimer != (MMRESULT) NULL) {
        mmRes = timeKillEvent(mmTimer);
        if (mmRes != TIMERR_NOERROR)
            ErrorReporter("Can't kill mm timer");
        mmTimer = (MMRESULT) NULL;
    }

    // close the file
    CloseHandle(hFile);

    // inform writer to abort all pending write requests
    if (!WriterAddFirstNodeTimeout(WRITE_ABORT, 0, 0, NULL, NULL, NULL, 500))
        ErrorReporter("Couldn't inform writer to abort sending.");

    // free the buffer
    if (!HeapFree(ghWriterHeap, 0, lpBuf))
        ErrorReporter("HeapFree (data block from writer heap)");
    
    REPEATING(TTYInfo) = FALSE;
    OutputDebugString("Repeated transfer destroyed.\r\n");

    //
    // enable transfer menu
    //
    hMenu = GetMenu(ghwndMain);
    MenuFlags = MF_ENABLED;
    EnableMenuItem(hMenu, ID_TRANSFER_ABORTREPEATEDSENDING, MF_DISABLED | MF_GRAYED);
    EnableMenuItem(hMenu, ID_TRANSFER_SENDFILETEXT, MenuFlags);
    EnableMenuItem(hMenu, ID_TRANSFER_SENDREPEATEDLY, MenuFlags);
    EnableMenuItem(hMenu, ID_TRANSFER_RECEIVEFILETEXT, MenuFlags);

    ShowWindow(GetDlgItem(ghWndStatusDlg, IDC_ABORTBTN), SW_HIDE);
    
    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: TransferRepeatDo( void )

PURPOSE: Performs a single text file transfer (send)

COMMENTS: Allocates a block to hold the file.
          Prepares the writer packet.

HISTORY:   Date:      Author:     Comment:
            1/29/96   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void CALLBACK TransferRepeatDo( UINT uTimerId, 
                                        UINT uRes, 
                                        DWORD dwFileSize, 
                                        DWORD dwRes1, 
                                        DWORD dwRes2)
{
    if (CONNECTED(TTYInfo)
        if (!WriterAddNewNodeTimeout(WRITE_BLOCK, dwFileSize, 0, lpBuf, 0, 0, 10))
            PostMessage(ghwndMain, WM_COMMAND, ID_TRANSFER_ABORTSENDING, MAKELPARAM(IDC_ABORTBTN, 0) );
    
    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: TransferFileTextStart(LPCTSTR)

PURPOSE: Prepares program for a text file transfer (send)

PARAMETERS:
    lpstrFileName - name of file selected to send

COMMENTS: Modifies menus and dialog control, then restores them

HISTORY:   Date:      Author:     Comment:
            1/26/96   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void TransferFileTextStart(LPCTSTR lpstrFileName)
{
    DWORD dwThreadId;
    HMENU hMenu;
    UINT  MenuFlags ;

    //
    // open the file
    //
    hFile = OpenTheFile(lpstrFileName);
    if (hFile == INVALID_HANDLE_VALUE)
        return;

    //
    // modify transfer menu
    //
    hMenu = GetMenu(ghwndMain);
    MenuFlags = MF_DISABLED | MF_GRAYED;
    EnableMenuItem(hMenu, ID_TRANSFER_SENDFILETEXT, MenuFlags);
    EnableMenuItem(hMenu, ID_TRANSFER_SENDREPEATEDLY, MenuFlags);
    EnableMenuItem(hMenu, ID_TRANSFER_ABORTSENDING, MF_ENABLED);
    EnableMenuItem(hMenu, ID_TRANSFER_RECEIVEFILETEXT, MenuFlags);
    
    //
    // enable abort button and progress bar
    //
    gfAbortTransfer = FALSE;
    SetWindowText(GetDlgItem(ghWndStatusDlg, IDC_ABORTBTN), "Abort Tx");
    ShowWindow(GetDlgItem(ghWndStatusDlg, IDC_ABORTBTN), SW_SHOW);
    ShowWindow(GetDlgItem(ghWndStatusDlg, IDC_TRANSFERPROGRESS), SW_SHOW);

    // start the transfer thread
    hTransferAbortEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (hTransferAbortEvent == NULL)
        ErrorReporter("CreateEvent(Transfer Abort Event)");

    hTransferThread = CreateThread(NULL, 0, 
                                TransferThreadProc, 
                                (LPVOID) hFile, 0, &dwThreadId);

    if (hTransferThread == NULL) {
        ErrorReporter("CreateThread (Transfer Thread)");
        TransferFileTextEnd();
    }
    else
        TRANSFERRING(TTYInfo) = TRUE;

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: TransferFileTextEnd()

PURPOSE: Stops a text file transfer (send)

COMMENTS: Modifies menus and dialog control, then restores them

HISTORY:   Date:      Author:     Comment:
           1/26/96   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void TransferFileTextEnd()
{
    HMENU hMenu;
    UINT MenuFlags ;

    // stop the transfer thread
    SetEvent(hTransferAbortEvent);

    OutputDebugString("Waiting for transfer thread...\n");

    if (WaitForSingleObject(hTransferThread, 3000) != WAIT_OBJECT_0) {
        ErrorReporter("TransferThread didn't stop.");
        TerminateThread(hTransferThread, 0);
    }
    else
        OutputDebugString("Transfer thread exited\n");

    CloseHandle(hTransferAbortEvent);
    CloseHandle(hTransferThread);

    TRANSFERRING(TTYInfo) = FALSE;

    //
    // enable transfer menu
    //
    hMenu = GetMenu(ghwndMain);
    MenuFlags = MF_ENABLED;
    EnableMenuItem(hMenu, ID_TRANSFER_SENDFILETEXT, MenuFlags);
    EnableMenuItem(hMenu, ID_TRANSFER_SENDREPEATEDLY, MenuFlags);
    EnableMenuItem(hMenu, ID_TRANSFER_RECEIVEFILETEXT, MenuFlags);
    EnableMenuItem(hMenu, ID_TRANSFER_ABORTSENDING, MF_DISABLED | MF_GRAYED);
    
    //
    // disable abort button and progress bar
    //
    ShowWindow(GetDlgItem(ghWndStatusDlg, IDC_ABORTBTN), SW_HIDE);
    ShowWindow(GetDlgItem(ghWndStatusDlg, IDC_TRANSFERPROGRESS), SW_HIDE);

    //
    // close the file
    //
    CloseHandle(hFile);
}


/*-----------------------------------------------------------------------------

FUNCTION: ReceiveFileText(LPCTSTR)

PURPOSE: Prepares program for a text file transfer (receive)

PARAMETERS:
    lpstrFileName - name of file selected for receiving 

COMMENTS: Modifies menus and control, then restores them

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void ReceiveFileText(LPCTSTR lpstrFileName)
{
    HMENU hMenu;
    UINT MenuFlags ;

    //
    // create the file
    //
    ghFileCapture = CreateTheFile(lpstrFileName);
    if (ghFileCapture == INVALID_HANDLE_VALUE)
        return;

    /*
        setup transfer
        disable file menu
    */
    hMenu = GetMenu(ghwndMain);
    MenuFlags = MF_DISABLED | MF_GRAYED;
    EnableMenuItem(hMenu, ID_FILE_CONNECT, MenuFlags);
    EnableMenuItem(hMenu, ID_FILE_DISCONNECT, MenuFlags);
    
    //
    // disable transfer menu
    //
    EnableMenuItem(hMenu, ID_TRANSFER_SENDFILETEXT, MenuFlags);
    EnableMenuItem(hMenu, ID_TRANSFER_RECEIVEFILETEXT, MenuFlags);
    EnableMenuItem(hMenu, ID_TRANSFER_SENDREPEATEDLY, MenuFlags);
    
    //
    // enable abort button and progress bar
    //
    gfAbortTransfer = FALSE;
    SetWindowText(GetDlgItem(ghWndStatusDlg, IDC_ABORTBTN), "Close Capture");
    ShowWindow(GetDlgItem(ghWndStatusDlg, IDC_ABORTBTN), SW_SHOW);
    ShowWindow(GetDlgItem(ghWndStatusDlg, IDC_TRANSFERPROGRESS), SW_SHOW);

    //
    // send file until done or abort
    //
    CaptureFile(ghFileCapture, GetDlgItem(ghWndStatusDlg, IDC_TRANSFERPROGRESS));

    //
    // enable menu
    //
    hMenu = GetMenu(ghwndMain);
    MenuFlags = MF_ENABLED;
    ChangeConnection(ghwndMain, CONNECTED(TTYInfo));
    
    //
    // enable transfer menu
    //
    EnableMenuItem(hMenu, ID_TRANSFER_SENDFILETEXT, MenuFlags);
    EnableMenuItem(hMenu, ID_TRANSFER_RECEIVEFILETEXT, MenuFlags);
    EnableMenuItem(hMenu, ID_TRANSFER_SENDREPEATEDLY, MenuFlags);

    //
    // hide abort button and progress bar
    //
    ShowWindow(GetDlgItem(ghWndStatusDlg, IDC_ABORTBTN), SW_HIDE);
    ShowWindow(GetDlgItem(ghWndStatusDlg, IDC_TRANSFERPROGRESS), SW_HIDE);
    
    gfAbortTransfer = FALSE;

    CloseHandle(ghFileCapture);

    return; // returns when file transfer is complete or aborted
}

/*-----------------------------------------------------------------------------

FUNCTION: OpenTheFile(LPCTSTR)

PURPOSE: Open a file and return the file handle

PARAMETERS:
    lpFName - name of file to open

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
HANDLE OpenTheFile(LPCTSTR lpFName)
{
    HANDLE hTemp;

    hTemp = CreateFile(lpFName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0,NULL);

    if (hTemp == INVALID_HANDLE_VALUE)
        ErrorReporter("CreateFile");

    return hTemp;
}

/*-----------------------------------------------------------------------------

FUNCTION: CreateTheFile(LPCTSTR)

PURPOSE: Creates a file and returns the file handle

PARAMETERS:
    lpFName - name of file to create

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
HANDLE CreateTheFile(LPCTSTR lpFName)
{
    HANDLE hTemp;

    hTemp = CreateFile(lpFName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0,NULL);

    if (hTemp == INVALID_HANDLE_VALUE)
        ErrorReporter("CreateFile");

    return hTemp;
}

/*-----------------------------------------------------------------------------

FUNCTION: GetTransferSizes(HANDLE, DWORD *, DWORD *, DWORD *)

PURPOSE: Examines file and determines packet size, number of packets,
         and file size.

PARAMETERS:
    hFile - handle of file to get size information from
    pdwDataPacketSize - size of an individual data packet
    pdwNumPackets     - total number of packets
    pdwFileSize       - size of file

RETURN:
    TRUE  - all metrics could be determined
    FALSE - something wrong with the file metrics, can't transfer

COMMENTS:
    This module can't handle files that are extremely large, so
    it may return FALSE if a large file is specified.

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
BOOL GetTransferSizes(HANDLE hFile, DWORD * pdwDataPacketSize, DWORD * pdwNumPackets, DWORD * pdwFileSize)
{
    BY_HANDLE_FILE_INFORMATION fi;

    if (!GetFileInformationByHandle(hFile, &fi)) {
        ErrorReporter("GetFileInformationByHandle");
        return FALSE;
    }
    else {
        if (fi.nFileSizeHigh) {
            MessageBox(ghwndMain, "File is too large to transfer.", "File Transfer Error", MB_OK);
            return FALSE;
        }

        //
        // setup packet size, file size and compute the number of packets
        //
        *pdwDataPacketSize = MAX_WRITE_BUFFER;
        *pdwFileSize = fi.nFileSizeLow;
        *pdwNumPackets = *pdwFileSize / *pdwDataPacketSize;

        if (*pdwNumPackets > 65534) {
            MessageBox(ghwndMain, "File is too large for buffer size.", "File Transfer Error", MB_OK);
            return FALSE;
        }
    }
    return TRUE;
}

/*-----------------------------------------------------------------------------

FUNCTION: ShowTransferStatistics(DWORD, DWORD, DWORD)

PURPOSE: Displays bytes transferred and bytes per second

PARAMETERS:
    dwEnd              - ending time in milliseconds
    dwStart            - starting time
    dwBytesTransferred - bytes sent

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void ShowTransferStatistics(DWORD dwEnd, DWORD dwStart, DWORD dwBytesTransferred)
{
    char szTemp[100];
    DWORD dwSecs;

    dwSecs = (dwEnd - dwStart) / 1000;

    //
    // display only if dwSecs != 0; if dwSecs == 0, then divide by zero occurs.
    //
    if (dwSecs != 0) {
        wsprintf(szTemp, "Bytes transferred: %d\r\nBytes/Second: %d\r\n", dwBytesTransferred, dwBytesTransferred / dwSecs);
        UpdateStatus(szTemp);
    }

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: CheckForMessages

PURPOSE: Check for a message and dispatch it.

RETURN:
    If the WM_CLOSE message or the WM_SYSCOMMAND (SC_CLOSE) is 
    retrieved, WM_CLOSE is posted, and WM_CLOSEQUIT is 
    returned by the function.  This allows the caller
    to detect this as an abort condition and exit properly.  When
    the caller exits, the main message loop in the WinMain function
    should be entered again and the WM_CLOSE message will be 
    handled properly.
           
    If there is a message other than those above, it is dispatched 
    and TRUE is returned indicating that a message was dispatched.
            
    If no message is found, FALSE is returned.

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
UINT CheckForMessages()
{
    MSG msg;

    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_CLOSE) {
            PostMessage(ghwndMain, WM_CLOSE, 0, 0);
            return WM_CLOSE;
        }

        if (msg.message == WM_SYSCOMMAND && msg.wParam == SC_CLOSE) {            
            PostMessage(ghwndMain, WM_CLOSE, 0, 0);
            return WM_CLOSE;
        }

        if (!TranslateAccelerator( ghwndMain, ghAccel, &msg )) {
            TranslateMessage( &msg ) ;
            DispatchMessage( &msg ) ;
        }

        return TRUE ;
    }
    
    return FALSE ;
}

/*-----------------------------------------------------------------------------

FUNCTION: CaptureFile(HANDLE, HWND)

PURPOSE: Receives a file

PARAMETERS:
    hFile - handle of file to receive the data being captured (not used)
    hWndProgress - window handle of progress bar (not used)

COMMENTS: Sets the receive state and waits for capture to end

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void CaptureFile(HANDLE hFile, HWND hWndProgress)
{
    UINT uMsgResult;
    gdwReceiveState = RECEIVE_CAPTURED;

    while ( !gfAbortTransfer ) {

        uMsgResult = CheckForMessages();

        //
        // If WM_CLOSE is retrieved, then exit.
        // If no message is retrieved, then sleep a little.
        // If any other message is retrieved, check for another one.
        //
        switch(uMsgResult)
        {
            case WM_CLOSE:  gfAbortTransfer = TRUE; break;
            case FALSE:     Sleep(200);             break;
            case TRUE:                              break;
        }
    }

    gdwReceiveState = RECEIVE_TTY;

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: TransferThreadProc(LPVOID)

PURPOSE: Worker thread does all the file transfer work

PARAMETERS:
    lpV - actually a HANDLE for the file

COMMENTS: Function allows the hTransferAbortEvent to 
          signal an abort condition.
          If the thread finishes OK, then the thread
          calls the TransferFileTextEnd function itself.

HISTORY:   Date:      Author:     Comment:
           1/26/96   AllenD      Wrote it

-----------------------------------------------------------------------------*/
DWORD WINAPI TransferThreadProc(LPVOID lpV)
{
    DWORD  dwPacketSize, dwMaxPackets, dwFileSize;
    DWORD  dwStartTime;
    HWND   hWndProgress;
    HANDLE hFileHandle;
    HANDLE hDataHeap;
    BOOL fStarted = TRUE;
    BOOL fAborting = FALSE;

    hFileHandle = (HANDLE) lpV;
    hWndProgress = GetDlgItem(ghWndStatusDlg, IDC_TRANSFERPROGRESS);

    // set up transfer metrics
    if (!GetTransferSizes(hFileHandle, &dwPacketSize, &dwMaxPackets, &dwFileSize))
        fAborting = TRUE;
    else {
        SendMessage(hWndProgress, PBM_SETRANGE, 0, MAKELPARAM(0, dwMaxPackets+1));
        SendMessage(hWndProgress, PBM_SETSTEP, (WPARAM) 1, 0);
        SendMessage(hWndProgress, PBM_SETPOS, 0, 0);
    }

    // set up transfer heaps
    if (!fAborting) {
        SYSTEM_INFO sysInfo;
        GetSystemInfo(&sysInfo);
        hDataHeap = HeapCreate(0, sysInfo.dwPageSize * 2, sysInfo.dwPageSize * 10);
        if (hDataHeap == NULL) {
            ErrorReporter("HeapCreate (Data Heap)");
            fAborting = TRUE;
        }
    }

    // inform writer thread that a file is about to be transferred
    if (!fAborting) {
        if (!WriterAddNewNode(WRITE_FILESTART, dwFileSize, 0, NULL, NULL, NULL))
            fAborting = TRUE;
    }

    OutputDebugString("Xfer: About to start sending data\n");

    // Get Transfer Start Time
    dwStartTime = GetTickCount();

    if (WaitForSingleObject(hTransferAbortEvent, 0) == WAIT_OBJECT_0)
        fAborting = TRUE;

    while (!fAborting) {
        char * lpDataBuf;
        PWRITEREQUEST pWrite;

        // transfer file, loop until all blocks of file have been read
        lpDataBuf = HeapAlloc(hDataHeap, 0, dwPacketSize);
        pWrite = HeapAlloc(ghWriterHeap, 0, sizeof(WRITEREQUEST));
        if ((lpDataBuf != NULL) && (pWrite != NULL)) {

            DWORD dwRead;

            // read from file into new buffer
            if (ReadFile(hFileHandle, lpDataBuf, dwPacketSize, &dwRead, NULL)) {
                WriterAddExistingNode(pWrite, WRITE_FILE, dwRead, 0, lpDataBuf, hDataHeap, hWndProgress);

                if (dwRead != dwPacketSize) // eof
                    break;
            }
        }
        else {
            BOOL fRes;
            /*
                Either the data heap is full, or the writer heap is full.
                Free any allocated block, wait a little and try again.

                Waiting lets the writer thread send some blocks and free
                the data blocks from the data heap and the control
                blocks from the writer heap.
            */
            if (lpDataBuf) {
                EnterCriticalSection(&gcsDataHeap);
                fRes = HeapFree(hDataHeap, 0, lpDataBuf);
                LeaveCriticalSection(&gcsDataHeap);
                if (!fRes)
                    ErrorReporter("HeapFree (Data block)");
            }

            if (pWrite) {
                EnterCriticalSection(&gcsWriterHeap);
                fRes = HeapFree(ghWriterHeap, 0, pWrite);
                LeaveCriticalSection(&gcsWriterHeap);
                if (!fRes)
                    ErrorReporter("HeapFree (Writer block)");
            }

            OutputDebugString("Xfer: A heap is full.  Waiting...\n");

            // wait a little
            // check for abort during the wait
            if (WaitForSingleObject(hTransferAbortEvent, 200) == WAIT_OBJECT_0)
                fAborting = TRUE;
        }

        // has the user aborted?
        if (WaitForSingleObject(hTransferAbortEvent, 0) == WAIT_OBJECT_0)
            fAborting = TRUE;
    }

    OutputDebugString("Xfer: Done sending packets.\n");

    if (fAborting) {
        // inform writer that transfer is aborting

        OutputDebugString("Xfer: Sending Abort Packet to writer\n");
        WriterAddFirstNodeTimeout(WRITE_ABORT, dwFileSize, 0, NULL, NULL, NULL, 500);
    }
    else
        WriterAddNewNodeTimeout(WRITE_FILEEND, dwFileSize, 0, NULL, NULL, NULL, 500);
        
    {
        // wait til writer thread finishes with all blocks
        HANDLE hEvents[2];
        DWORD dwRes;
        BOOL  fTransferComplete = FALSE;
        
        hEvents[0] = ghTransferCompleteEvent;
        hEvents[1] = hTransferAbortEvent;

        OutputDebugString("Xfer: Waiting for transfer complete signal from writer\n");
        do {
            ResetEvent(hTransferAbortEvent);

            dwRes = WaitForMultipleObjects(2, hEvents, FALSE, INFINITE);
            switch(dwRes) {
            case WAIT_OBJECT_0:      
                fTransferComplete = TRUE;   
                OutputDebugString("Transfer complete signal rec'd\n");
                break;
            case WAIT_OBJECT_0 + 1:  
                fAborting = TRUE;           
                OutputDebugString("Transfer abort signal rec'd\n");
                OutputDebugString("Xfer: Sending Abort Packet to writer\n");
                if (!WriterAddFirstNodeTimeout(WRITE_ABORT, dwFileSize, 0, NULL, NULL, NULL, 500))
                    ErrorReporter("Can't add abort packet\n");
                break;
            case WAIT_TIMEOUT:                                   break;
            default:
                ErrorReporter("WaitForMultipleObjects(Transfer Complete Event and Transfer Abort Event)");
                fTransferComplete = TRUE;
                break;
            }
        } while (!fTransferComplete);
    }

    OutputDebugString("Xfer: transfer complete\n");

    // report statistics
    if (!fAborting)
        ShowTransferStatistics(GetTickCount(), dwStartTime, dwFileSize);

    // break down metrics
    PostMessage(hWndProgress, PBM_SETPOS, 0, 0);

    // break down heaps
    if (hDataHeap != NULL) {
        if (!HeapDestroy(hDataHeap))
            ErrorReporter("HeapDestroy (data heap)");
    }

    // If I am done without user intervention, then post the
    // "abort" message myself.  This will cause the main thread to
    // clean up after the file transfer.
    if (!fAborting)
        PostMessage(ghwndMain, WM_COMMAND, ID_TRANSFER_ABORTSENDING, 0);

    // exit thread

    return 0;
}

