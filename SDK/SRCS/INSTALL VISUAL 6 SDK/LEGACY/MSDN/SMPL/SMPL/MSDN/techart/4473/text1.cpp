

 //*****************************************
// Global variables.
//*****************************************

HANDLE g_hCommFile = NULL;

DWORD g_dwReadThreadID  = 0;
DWORD g_dwWriteThreadID = 0;
HANDLE g_hReadThread  = NULL;
HANDLE g_hWriteThread = NULL;

HANDLE g_hCloseEvent = NULL;

//*****************************************
// CommCode internal Function Prototypes
//*****************************************

void CloseReadThread();
void CloseWriteThread();

DWORD WINAPI StartReadThreadProc(LPVOID lpvParam);
DWORD WINAPI StartWriteThreadProc(LPVOID lpvParam);


BOOL HandleWriteData(LPOVERLAPPED lpOverlappedWrite,
        LPCSTR lpszStringToWrite, DWORD dwNumberOfBytesToWrite);


BOOL SetupReadEvent(LPOVERLAPPED lpOverlappedRead,
        LPSTR lpszInputBuffer, DWORD dwSizeofBuffer,
        LPDWORD lpnNumberOfBytesRead);
BOOL HandleReadEvent(LPOVERLAPPED lpOverlappedRead,
        LPSTR lpszInputBuffer, DWORD dwSizeofBuffer,
        LPDWORD lpnNumberOfBytesRead);
BOOL HandleReadData(LPCSTR lpszInputBuffer, DWORD dwSizeofBuffer);


BOOL HandleCommEvent(LPOVERLAPPED lpOverlappedCommEvent,
        LPDWORD lpfdwEvtMask, BOOL fRetrieveEvent);
BOOL SetupCommEvent(LPOVERLAPPED lpOverlappedCommEvent,
        LPDWORD lpfdwEvtMask);



//*****************************************
// Functions exported for use by other modules
//*****************************************



//
//  FUNCTION: StartComm(HANDLE)
//
//  PURPOSE: Starts communications over the comm port.
//
//  PARAMETERS:
//    hNewCommFile - This is the COMM File handle to communicate with.
//                   This handle is obtained from TAPI.
//
//  RETURN VALUE:
//    TRUE if able to setup the communications.
//
//  COMMENTS:
//
//    StartComm makes sure there isn't communication in progress already,
//    the hNewCommFile is valid, and all the threads can be created.  It
//    also configures the hNewCommFile for the appropriate COMM settings.
//
//    If StartComm fails for any reason, it's up to the calling application
//    to close the Comm file handle.
//
//

BOOL StartComm(HANDLE hNewCommFile)
{
    // Is this a valid comm handle?
    if (GetFileType(hNewCommFile) != FILE_TYPE_CHAR)
    {
        OutputDebugString("File handle is not a comm handle.\n");
        return FALSE;
    }

    // Are we already doing comm?
    if (g_hCommFile != NULL)
    {
        OutputDebugString("Already have a comm file open\n");
        return FALSE;
    }

    // Its ok to continue.

    g_hCommFile = hNewCommFile;

    // Setting and querying the comm port configurations.

    { // Configure the comm settings.
        COMMTIMEOUTS commtimeouts;
        DCB dcb;
        COMMPROP commprop;
        DWORD fdwEvtMask;

        // These are here just so you can set a breakpoint
        // and see what the comm settings are.  Most Comm settings
        // are already set through TAPI.
        GetCommState(hNewCommFile, &dcb);
        GetCommProperties(hNewCommFile, &commprop);
        GetCommMask(g_hCommFile, &fdwEvtMask);
        GetCommTimeouts(g_hCommFile, &commtimeouts);


        // The CommTimeout numbers will very likely change if you are
        // coding to meet some kind of specification where
        // you need to reply within a certain amount of time after
        // recieving the last byte.  However,  If 1/4th of a second
        // goes by between recieving two characters, its a good 
        // indication that the transmitting end has finished, even
        // assuming a 1200 baud modem.

        commtimeouts.ReadIntervalTimeout         = 250;
        commtimeouts.ReadTotalTimeoutMultiplier  = 0;
        commtimeouts.ReadTotalTimeoutConstant    = 0;
        commtimeouts.WriteTotalTimeoutMultiplier = 0;
        commtimeouts.WriteTotalTimeoutConstant   = 0;

        SetCommTimeouts(g_hCommFile, &commtimeouts);

        // fAbortOnError is the only DCB dependancy in TapiComm.
        // Can't guarentee that the SP will set this to what we expect.
        dcb.fAbortOnError = FALSE;
        SetCommState(hNewCommFile, &dcb);
    }

    // Create the event that will signal the threads to close.
    g_hCloseEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

    if (g_hCloseEvent == NULL)
    {
        OutputDebugLastError(GetLastError(), "Unable to CreateEvent: ");
        g_hCommFile = NULL;
        return FALSE;
    }

    // Create the Read thread.
    g_hReadThread =
        CreateThread(NULL, 0, StartReadThreadProc, 0, 0, &g_dwReadThreadID);
        
    if (g_hReadThread == NULL)
    {
        OutputDebugLastError(GetLastError(),"Unable to create Read thread");

        g_dwReadThreadID = 0;
        g_hCommFile = 0;
        return FALSE;
    }
    
    // Comm threads should to have a higher base priority than the UI thread.
    // If they don't, then any temporary priority boost the UI thread gains
    // could cause the COMM threads to loose data.
    SetThreadPriority(g_hReadThread, THREAD_PRIORITY_HIGHEST);

    // Create the Write thread.
    g_hWriteThread = 
        CreateThread(NULL, 0, StartWriteThreadProc, 0, 0, &g_dwWriteThreadID);
        
    if (g_hWriteThread == NULL)
    {
        OutputDebugLastError(GetLastError(),"Unable to create Write thread");

        CloseReadThread();
        g_dwWriteThreadID = 0;
        g_hCommFile = 0;
        return FALSE;
    }
    
    SetThreadPriority(g_hWriteThread, THREAD_PRIORITY_ABOVE_NORMAL);

    // Everything was created ok.  Ready to go!
    return TRUE;
}

//
//  FUNCTION: StopComm
//
//  PURPOSE: Stop and end all communication threads.
//
void StopComm()
{
    // No need to continue if we're not communicating.
    if (g_hCommFile == NULL)
        return;

    OutputDebugString("Stopping the Comm\n");

    // Close the threads.
    CloseReadThread();
    CloseWriteThread();

    // Not needed anymore.
    CloseHandle(g_hCloseEvent);

    // Now close the comm port handle.
    CloseHandle(g_hCommFile);
    g_hCommFile = NULL;
}


//
//  FUNCTION: WriteCommString(LPCSTR, DWORD)
//
//  PURPOSE: Send a String to the Write Thread to be written to the Comm.
//
BOOL WriteCommString(LPCSTR lpszStringToWrite, DWORD dwSizeofStringToWrite)
{
    if (g_hWriteThread)
    {
        if (PostThreadMessage(g_dwWriteThreadID, PWM_COMMWRITE, 
                (WPARAM) dwSizeofStringToWrite, (LPARAM) lpszStringToWrite))
        {
            return TRUE;
        }
        else
            OutputDebugString("Failed to Post to Write thread.\n");
    }
    else
        OutputDebugString("Write thread not created\n");

    return FALSE;
}


//*****************************************
// The rest of the functions are intended for use
// only within the CommCode module.
//*****************************************



//
//  FUNCTION: CloseReadThread
//
//  PURPOSE: Close the Read Thread.
//
//  PARAMETERS:
//    none
//
//  RETURN VALUE:
//    none
//
//  COMMENTS:
//
//    Closes the Read thread by signaling the CloseEvent.
//    Purges any outstanding reads on the comm port.
//
//    Note that terminating a thread leaks memory (read the docs).
//    Besides the normal leak incurred, there is an event object
//    that doesn't get closed.  This isn't worth worrying about 
//    since it shouldn't happen anyway.
//
//

void CloseReadThread()
{
    // If it exists...
    if (g_hReadThread)
    {
        OutputDebugString("Closing Read Thread\n");

        // Signal the event to close the worker threads.
        SetEvent(g_hCloseEvent);

        // Purge all outstanding reads
        PurgeComm(g_hCommFile, PURGE_RXABORT | PURGE_RXCLEAR);

        // Wait 10 seconds for it to exit.  Shouldn't happen.
        if (WaitForSingleObject(g_hReadThread, 10000) == WAIT_TIMEOUT)
        {
            OutputDebugString("Read thread not exiting.  Terminating it.\n");

            TerminateThread(g_hReadThread, 0);

            // The ReadThread cleans up these itself if it terminates
            // normally.
            CloseHandle(g_hReadThread);
            g_hReadThread = 0;
            g_dwReadThreadID = 0;
        }
    }
}


//
//  FUNCTION: CloseWriteThread
//
//  PURPOSE: Closes the Write Thread.
//
//  PARAMETERS:
//    none
//
//  RETURN VALUE:
//    none
//
//  COMMENTS:
//
//    Closes the write thread by signaling the CloseEvent.
//    Purges any outstanding writes on the comm port.
//
//    Note that terminating a thread leaks memory (read the docs).
//    Besides the normal leak incurred, there is an event object
//    that doesn't get closed.  This isn't worth worrying about 
//    since it shouldn't happen anyway.
//
//

void CloseWriteThread()
{
    // If it exists...
    if (g_hWriteThread)
    {
        OutputDebugString("Closing Write Thread\n");

        // Signal the event to close the worker threads.
        SetEvent(g_hCloseEvent);

        // Purge all outstanding writes.
        PurgeComm(g_hCommFile, PURGE_TXABORT | PURGE_TXCLEAR);

        // Wait 10 seconds for it to exit.  Shouldn't happen.
        if (WaitForSingleObject(g_hWriteThread, 10000) == WAIT_TIMEOUT)
        {
            OutputDebugString("Write thread not exiting.  Terminating it.\n");

            TerminateThread(g_hWriteThread, 0);

            // The WriteThread cleans up these itself if it terminates
            // normally.
            CloseHandle(g_hWriteThread);
            g_hWriteThread = 0;
            g_dwWriteThreadID = 0;

        }
    }
}


//
//  FUNCTION: StartWriteThreadProc(LPVOID)
//
//  PURPOSE: The starting point for the Write thread.
//
//  PARAMETERS:
//    lpvParam - unused.
//
//  RETURN VALUE:
//    DWORD - unused.
//
//  COMMENTS:
//
//    The Write thread uses a PeekMessage loop to wait for a string to write,
//    and when it gets one, it writes it to the Comm port.  If the CloseEvent
//    object is signaled, then it exits.  The use of messages to tell the
//    Write thread what to write provides a natural desynchronization between
//    the UI and the Write thread.
//
//

DWORD WINAPI StartWriteThreadProc(LPVOID lpvParam)
{
    MSG msg;
    DWORD dwHandleSignaled;

    // Needed for overlapped I/O.
    OVERLAPPED overlappedWrite = {0, 0, 0, 0, NULL};

    overlappedWrite.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
    if (overlappedWrite.hEvent == NULL)
    {
        OutputDebugLastError(GetLastError(), "Unable to CreateEvent: ");
        PostHangupCall();
        goto EndWriteThread;
    }

    // This is the main loop.  Loop until we break out.
    while (TRUE)
    {
        if (!PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // If there are no messages pending, wait for a message or 
            // the CloseEvent.
            dwHandleSignaled = 
                MsgWaitForMultipleObjects(1, &g_hCloseEvent, FALSE,
                    INFINITE, QS_ALLINPUT);

            switch(dwHandleSignaled)
            {
                case WAIT_OBJECT_0:     // CloseEvent signaled!
                {
                    // Time to exit.
                    goto EndWriteThread;
                }

                case WAIT_OBJECT_0 + 1: // New message was received.
                {
                    // Get the message that woke us up by looping again.
                    continue;
                }

                case WAIT_FAILED:       // Wait failed.  Shouldn't happen.
                {
                    OutputDebugLastError(GetLastError(),"Write WAIT_FAILED: ");
                    PostHangupCall();
                    goto EndWriteThread;
                }

                default:                // This case should never occur.
                {
                    OutputDebugPrintf("Unexpected Wait return value '%lx'",
                        dwHandleSignaled);
                    PostHangupCall();
                    goto EndWriteThread;
                }

            }
        }

        // Make sure the CloseEvent isn't signaled while retrieving messages.
        if (WAIT_TIMEOUT != WaitForSingleObject(g_hCloseEvent,0))
            goto EndWriteThread;

        // Process the message.

        // This could happen if a dialog is created on this thread.
        // This doesn't occur in this sample, but might if modified.
        if (msg.hwnd != NULL)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            continue;
        }

        // Handle the message.
        switch(msg.message)
        {
            case PWM_COMMWRITE:  // New string to write to Comm port.
            {
                OutputDebugString("Writing to comm port\n");

                // Write the string to the comm port.  HandleWriteData
                // does not return until the whole string has been written,
                // an error occurs or until the CloseEvent is signaled.
                if (!HandleWriteData(&overlappedWrite,
                        (LPSTR) msg.lParam, (DWORD) msg.wParam))
                {
                    // If it failed, either we got a signal to end or there
                    // really was a failure.

                    free((HLOCAL) msg.lParam); 
                    goto EndWriteThread;
                }

                // Data was sent in a LocalAlloc()d buffer.  Must free it.
                free((HLOCAL) msg.lParam); 
                break;
            }
    

            // What other messages could the thread get?
            default:
            {
                char Output[256];
    
                wsprintf(Output,
                    "Unexpected message posted to Write thread: %ui\n",
                    msg.message );
                    
                OutputDebugString(Output);
                break;
            }
        } // End of switch(message)

    } // End of main loop.

    // Thats the end.  Now clean up.
  EndWriteThread:

    OutputDebugString("Write thread shutting down\n");

    PurgeComm(g_hCommFile, PURGE_TXABORT | PURGE_TXCLEAR);

    CloseHandle(overlappedWrite.hEvent);

    g_dwWriteThreadID = 0;
    CloseHandle(g_hWriteThread);
    g_hWriteThread = 0;

    return 0;
}


//
//  FUNCTION: HandleWriteData(LPOVERLAPPED, LPCSTR, DWORD)
//
//  PURPOSE: Writes a given string to the comm file handle.
//
//  PARAMETERS:
//    lpOverlappedWrite      - Overlapped structure to use in WriteFile
//    lpszStringToWrite      - String to write.
//    dwNumberOfBytesToWrite - Length of String to write.
//
//  RETURN VALUE:
//    TRUE if all bytes were written.  False if there was a failure to
//    write the whole string.
//
//  COMMENTS:
//
//    This function is a helper function for the Write Thread.  It
//    is this call that actually writes a string to the comm file.
//    Note that this call blocks and waits for the Write to complete
//    or for the CloseEvent object to signal that the thread should end.
//    Another possible reason for returning FALSE is if the comm port
//    is closed by the service provider.
//
//

BOOL HandleWriteData(LPOVERLAPPED lpOverlappedWrite,
    LPCSTR lpszStringToWrite, DWORD dwNumberOfBytesToWrite)
{
    DWORD dwLastError;

    DWORD dwNumberOfBytesWritten = 0;
    DWORD dwWhereToStartWriting = 0; // Start at the beginning.

    DWORD dwHandleSignaled;
    HANDLE HandlesToWaitFor[2];

    HandlesToWaitFor[0] = g_hCloseEvent;
    HandlesToWaitFor[1] = lpOverlappedWrite -> hEvent;

    // Keep looping until all characters have been written.
    do
    {
        // Start the overlapped I/O.
        if (!WriteFile(g_hCommFile, 
                &lpszStringToWrite[ dwWhereToStartWriting ], 
                dwNumberOfBytesToWrite, &dwNumberOfBytesWritten,
                lpOverlappedWrite))
        {
            // WriteFile failed.  Expected; lets handle it.
            dwLastError = GetLastError();

            // Its possible for this error to occur if the 
            // service provider has closed the port.  Time to end.
            if (dwLastError == ERROR_INVALID_HANDLE)
            {
                OutputDebugString("ERROR_INVALID_HANDLE, "
                    "Likely that the Service Provider has closed the port.\n");
                return FALSE;
            }

            // Unexpected error.  No idea what.
            if (dwLastError != ERROR_IO_PENDING)
            {
                OutputDebugLastError(dwLastError,
                    "Error to writing to CommFile");
                
                OutputDebugString("Closing TAPI\n");
                PostHangupCall();
                return FALSE;
            }

            // This is the expected ERROR_IO_PENDING case.


            // Wait for either overlapped I/O completion,
            // or for the CloseEvent to get signaled.
            dwHandleSignaled = 
                WaitForMultipleObjects(2, HandlesToWaitFor, 
                    FALSE, INFINITE);

            switch(dwHandleSignaled)
            {
                case WAIT_OBJECT_0:     // CloseEvent signaled!
                {
                    // Time to exit.
                    return FALSE;
                }

                case WAIT_OBJECT_0 + 1: // Wait finished.
                {
                    // Time to get the results of the WriteFile
                    break;
                }

                case WAIT_FAILED: // Wait failed.  Shouldn't happen.
                {
                    OutputDebugLastError(GetLastError(), 
                        "Write WAIT_FAILED: ");
                    PostHangupCall();
                    return FALSE;
                }

                default: // This case should never occur.
                {
                    OutputDebugPrintf(
                        "Unexpected Wait return value '%lx'",
                        dwHandleSignaled);
                    PostHangupCall();
                    return FALSE;
                }
            }

            if (!GetOverlappedResult(g_hCommFile,
                     lpOverlappedWrite,
                     &dwNumberOfBytesWritten, TRUE))
            {
                dwLastError = GetLastError();

                // Its possible for this error to occur if the 
                // service provider has closed the port.
                if (dwLastError == ERROR_INVALID_HANDLE)
                {
                    OutputDebugString("ERROR_INVALID_HANDLE, "
                        "Likely that the Service Provider has closed the port.\n");
                    return FALSE;
                }

                // No idea what could cause another error.
                OutputDebugLastError(dwLastError,
                    "Error writing to CommFile while waiting");
                OutputDebugString("Closing TAPI\n");
                PostHangupCall();
                return FALSE;
            }
        }

        // Some data was written.  Make sure it all got written.

        dwNumberOfBytesToWrite -= dwNumberOfBytesWritten;
        dwWhereToStartWriting += dwNumberOfBytesWritten;
    }
    while(dwNumberOfBytesToWrite > 0);  // Write the whole thing!

    // Wrote the whole string.
    return TRUE;
}


//
//  FUNCTION: StartReadThreadProc(LPVOID)
//
//  PURPOSE: This is the starting point for the Read Thread.
//
//  PARAMETERS:
//    lpvParam - unused.
//
//  RETURN VALUE:
//    DWORD - unused.
//
//  COMMENTS:
//
//    The Read Thread uses overlapped ReadFile and sends any strings
//    read from the comm port to the UI to be printed.  This is
//    eventually done through a PostMessage so that the Read Thread
//    is never away from the comm port very long.  This also provides
//    natural desynchronization between the Read thread and the UI.
//
//    If the CloseEvent object is signaled, the Read Thread exits.
//
//    Note that there is absolutely *no* interpretation of the data,
//    which means no terminal emulation.  It basically means that this
//    sample is pretty useless as a TTY program.
//
//	  Separating the Read and Write threads is natural for a application
//    like this sample where there is no need for synchronization between
//    reading and writing.  However, if there is such a need (for example,
//    most file transfer algorithms synchronize the reading and writing),
//    then it would make a lot more sense to have a single thread to handle
//    both reading and writing.
//
//

DWORD WINAPI StartReadThreadProc(LPVOID lpvParam)
{
    char szInputBuffer[INPUTBUFFERSIZE];
    DWORD nNumberOfBytesRead;

    HANDLE HandlesToWaitFor[3];
    DWORD dwHandleSignaled;

    DWORD fdwEvtMask;

    // Needed for overlapped I/O (ReadFile)
    OVERLAPPED overlappedRead  = {0, 0, 0, 0, NULL};

    // Needed for overlapped Comm Event handling.
    OVERLAPPED overlappedCommEvent = {0, 0, 0, 0, NULL};

    // Lets put an event in the Read overlapped structure.
    overlappedRead.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
    if (overlappedRead.hEvent == NULL)
    {
        OutputDebugLastError(GetLastError(), "Unable to CreateEvent: ");
        PostHangupCall();
        goto EndReadThread;
    }

    // And an event for the CommEvent overlapped structure.
    overlappedCommEvent.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);
    if (overlappedCommEvent.hEvent == NULL)
    {
        OutputDebugLastError(GetLastError(), "Unable to CreateEvent: ");
        PostHangupCall();
        goto EndReadThread;
    }

    // We will be waiting on these objects.
    HandlesToWaitFor[0] = g_hCloseEvent;
    HandlesToWaitFor[1] = overlappedCommEvent.hEvent;
    HandlesToWaitFor[2] = overlappedRead.hEvent;


    // Setup CommEvent handling.

    // Set the comm mask so we receive error signals.
    if (!SetCommMask(g_hCommFile, EV_ERR))
    {
        OutputDebugLastError(GetLastError(),"Unable to SetCommMask: ");
        PostHangupCall();
        goto EndReadThread;
    }

    // Start waiting for CommEvents (Errors)
    if (!SetupCommEvent(&overlappedCommEvent, &fdwEvtMask))
    {
        PostHangupCall();
        goto EndReadThread;
    }

    // Start waiting for Read events.
    if (!SetupReadEvent(&overlappedRead,
                szInputBuffer, INPUTBUFFERSIZE,
                &nNumberOfBytesRead))
    {
        PostHangupCall();
        goto EndReadThread;
    }

    // Keep looping until we break out.
    while (TRUE)
    {
        // Wait until some event occurs (data to read; error; stopping).
        dwHandleSignaled = 
            WaitForMultipleObjects(3, HandlesToWaitFor,
                FALSE, INFINITE);

        // Which event occured?
        switch(dwHandleSignaled)
        {
            case WAIT_OBJECT_0:     // Signal to end the thread.
            {
                // Time to exit.
                goto EndReadThread;
            }

            case WAIT_OBJECT_0 + 1: // CommEvent signaled.
            {
                // Handle the CommEvent.
                if (!HandleCommEvent(&overlappedCommEvent, &fdwEvtMask, TRUE))
                {
                    PostHangupCall();
                    goto EndReadThread;
                }

                // Start waiting for the next CommEvent.
                if (!SetupCommEvent(&overlappedCommEvent, &fdwEvtMask))
                {
                    PostHangupCall();
                    goto EndReadThread;
                }
                break;
            }

            case WAIT_OBJECT_0 + 2: // Read Event signaled.
            {
                // Get the new data!
                if (!HandleReadEvent(&overlappedRead,
                            szInputBuffer, INPUTBUFFERSIZE,
                            &nNumberOfBytesRead))
                {
                    PostHangupCall();
                    goto EndReadThread;
                }

                // Wait for more new data.
                if (!SetupReadEvent(&overlappedRead,
                            szInputBuffer, INPUTBUFFERSIZE,
                            &nNumberOfBytesRead))
                {
                    PostHangupCall();
                    goto EndReadThread;
                }
                break;
            }

            case WAIT_FAILED:       // Wait failed.  Shouldn't happen.
            {
                OutputDebugLastError(GetLastError(),"Read WAIT_FAILED: ");
                PostHangupCall();
                goto EndReadThread;
            }

            default:    // This case should never occur.
            {
                OutputDebugPrintf("Unexpected Wait return value '%lx'",
                    dwHandleSignaled);
                PostHangupCall();
                goto EndReadThread;
            }
        } // End of switch(dwHandleSignaled).

    } // End of while(TRUE) loop.


    // Time to clean up Read Thread.
  EndReadThread:

    OutputDebugString("Read thread shutting down\n");
    PurgeComm(g_hCommFile, PURGE_RXABORT | PURGE_RXCLEAR);
    CloseHandle(overlappedRead.hEvent);
    CloseHandle(overlappedCommEvent.hEvent);
    g_dwReadThreadID = 0;
    CloseHandle(g_hReadThread);
    g_hReadThread = 0;
    return 0;
}

//
//  FUNCTION: SetupReadEvent(LPOVERLAPPED, LPSTR, DWORD, LPDWORD)
//
//  PURPOSE: Sets up an overlapped ReadFile
//
//  PARAMETERS:
//    lpOverlappedRead      - address of overlapped structure to use.
//    lpszInputBuffer       - Buffer to place incoming bytes.
//    dwSizeofBuffer        - size of lpszInputBuffer.
//    lpnNumberOfBytesRead  - address of DWORD to place the number of read bytes.
//
//  RETURN VALUE:
//    TRUE if able to successfully setup the ReadFile.  FALSE if there
//    was a failure setting up or if the CloseEvent object was signaled.
//
//  COMMENTS:
//
//    This function is a helper function for the Read Thread.  This
//    function sets up the overlapped ReadFile so that it can later
//    be waited on (or more appropriatly, so the event in the overlapped
//    structure can be waited upon).  If there is data waiting, it is
//    handled and the next ReadFile is initiated.
//    Another possible reason for returning FALSE is if the comm port
//    is closed by the service provider.
//    
//
//

BOOL SetupReadEvent(LPOVERLAPPED lpOverlappedRead,
    LPSTR lpszInputBuffer, DWORD dwSizeofBuffer,
    LPDWORD lpnNumberOfBytesRead)
{
    DWORD dwLastError;

  StartSetupReadEvent:

    // Make sure the CloseEvent hasn't been signaled yet.
    // Check is needed because this function is potentially recursive.
    if (WAIT_TIMEOUT != WaitForSingleObject(g_hCloseEvent,0))
        return FALSE;
    
    // Start the overlapped ReadFile.
    if (ReadFile(g_hCommFile, 
            lpszInputBuffer, dwSizeofBuffer,
            lpnNumberOfBytesRead, lpOverlappedRead))
    {
        // This would only happen if there was data waiting to be read.

        OutputDebugString("Data waiting for ReadFile.\n");
        
        // Handle the data.
        if (!HandleReadData(lpszInputBuffer, *lpnNumberOfBytesRead))
        {
            return FALSE;
        }

        // Start waiting for more data.
        goto StartSetupReadEvent;
    }

    // ReadFile failed.  Expected because of overlapped I/O.
    dwLastError = GetLastError();


    // LastError was ERROR_IO_PENDING, as expected.
    if (dwLastError == ERROR_IO_PENDING)
    {
        OutputDebugString("Waiting for data from comm connection.\n");
        return TRUE;
    }

    // Its possible for this error to occur if the 
    // service provider has closed the port.  Time to end.
    if (dwLastError == ERROR_INVALID_HANDLE)
    {
        OutputDebugString("ERROR_INVALID_HANDLE, "
            "Likely that the Service Provider has closed the port.\n");
        return FALSE;
    }

    // Unexpected error. No idea what could cause this to happen.
    OutputDebugLastError(dwLastError,"Unexpected ReadFile error: ");
    
    PostHangupCall();
    return FALSE;
}
 
 
//
//  FUNCTION: HandleReadEvent(LPOVERLAPPED, LPSTR, DWORD, LPDWORD)
//
//  PURPOSE: Retrieves and handles data when there is data ready.
//
//  PARAMETERS:
//    lpOverlappedRead      - address of overlapped structure to use.
//    lpszInputBuffer       - Buffer to place incoming bytes.
//    dwSizeofBuffer        - size of lpszInputBuffer.
//    lpnNumberOfBytesRead  - address of DWORD to place the number of read bytes.
//
//  RETURN VALUE:
//    TRUE if able to successfully retrieve and handle the available data.
//    FALSE if unable to retrieve or handle the data.
//
//  COMMENTS:
//
//    This function is another helper function for the Read Thread.  This
//    is the function that is called when there is data available after
//    an overlapped ReadFile has been setup.  It retrieves the data and
//    handles it.
//
//

BOOL HandleReadEvent(LPOVERLAPPED lpOverlappedRead,
    LPSTR lpszInputBuffer, DWORD dwSizeofBuffer,
    LPDWORD lpnNumberOfBytesRead)
{
    DWORD dwLastError;

    if (GetOverlappedResult(g_hCommFile,
            lpOverlappedRead, lpnNumberOfBytesRead, FALSE))
    {
        return HandleReadData(lpszInputBuffer, *lpnNumberOfBytesRead);
    }

    // Error in GetOverlappedResult; handle it.

    dwLastError = GetLastError();

    // Its possible for this error to occur if the 
    // service provider has closed the port.  Time to end.
    if (dwLastError == ERROR_INVALID_HANDLE)
    {
        OutputDebugString("ERROR_INVALID_HANDLE, "
            "Likely that the Service Provider has closed the port.\n");
        return FALSE;
    }

    OutputDebugLastError(dwLastError, 
        "Unexpected GetOverlappedResult Read Error: ");

    PostHangupCall();
    return FALSE;
}


//
//  FUNCTION: HandleReadData(LPCSTR, DWORD)
//
//  PURPOSE: Deals with data after its been read from the comm file.
//
//  PARAMETERS:
//    lpszInputBuffer  - Buffer to place incoming bytes.
//    dwSizeofBuffer   - size of lpszInputBuffer.
//
//  RETURN VALUE:
//    TRUE if able to successfully handle the data.
//    FALSE if unable to allocate memory or handle the data.
//
//  COMMENTS:
//
//    This function is yet another helper function for the Read Thread.
//    It LocalAlloc()s a buffer, copies the new data to this buffer and
//    calls PostWriteToDisplayCtl to let the EditCtls module deal with
//    the data.  Its assumed that PostWriteToDisplayCtl posts the message
//    rather than dealing with it right away so that the Read Thread
//    is free to get right back to waiting for data.  Its also assumed
//    that the EditCtls module is responsible for LocalFree()ing the
//    pointer that is passed on.
//
//

BOOL HandleReadData(LPCSTR lpszInputBuffer, DWORD dwSizeofBuffer)
{
    // If we got data and didn't just time out empty...
    if (dwSizeofBuffer)
    {
        LPSTR lpszPostedBytes;

        // Do something with the bytes read.
        OutputDebugString("Got something from Comm port!!!\n");

        lpszPostedBytes = LocalAlloc(LPTR,dwSizeofBuffer+1);
        if (lpszPostedBytes == NULL)
        {
            OutputDebugLastError(GetLastError(), "LocalAlloc: ");
            return FALSE;
        }

        memcpy(lpszPostedBytes, lpszInputBuffer, dwSizeofBuffer);
        lpszPostedBytes[dwSizeofBuffer] = '\0';

        return PostWriteToDisplayCtl(lpszPostedBytes, dwSizeofBuffer);
    }

}


//
//  FUNCTION: SetupCommEvent(LPOVERLAPPED, LPDWORD)
//
//  PURPOSE: Sets up the overlapped WaitCommEvent call.
//
//  PARAMETERS:
//    lpOverlappedCommEvent - Pointer to the overlapped structure to use.
//    lpfdwEvtMask          - Pointer to DWORD to received Event data.
//
//  RETURN VALUE:
//    TRUE if able to successfully setup the WaitCommEvent.
//    FALSE if unable to setup WaitCommEvent, unable to handle
//    an existing outstanding event or if the CloseEvent has been signaled.
//
//  COMMENTS:
//
//    This function is a helper function for the Read Thread that sets up
//    the WaitCommEvent so we can deal with comm events (like Comm errors)
//    if they occur.
//
//

BOOL SetupCommEvent(LPOVERLAPPED lpOverlappedCommEvent,
    LPDWORD lpfdwEvtMask)
{
    DWORD dwLastError;

  StartSetupCommEvent:

    // Make sure the CloseEvent hasn't been signaled yet.
    // Check is needed because this function is potentially recursive.
    if (WAIT_TIMEOUT != WaitForSingleObject(g_hCloseEvent,0))
        return FALSE;

    // Start waiting for Comm Errors.
    if (WaitCommEvent(g_hCommFile, lpfdwEvtMask, lpOverlappedCommEvent))
    {
        // This could happen if there was an error waiting on the
        // comm port.  Lets try and handle it.

        OutputDebugString("Event (Error) waiting before WaitCommEvent.\n");

        if (!HandleCommEvent(NULL, lpfdwEvtMask, FALSE))
            return FALSE;

        // What could cause infinite recursion at this point?
        goto StartSetupCommEvent;
    }

    // We expect ERROR_IO_PENDING returned from WaitCommEvent
    // because we are waiting with an overlapped structure.

    dwLastError = GetLastError();

    // LastError was ERROR_IO_PENDING, as expected.
    if (dwLastError == ERROR_IO_PENDING)
    {
        OutputDebugString("Waiting for a CommEvent (Error) to occur.\n");
        return TRUE;
    }

    // Its possible for this error to occur if the 
    // service provider has closed the port.  Time to end.
    if (dwLastError == ERROR_INVALID_HANDLE)
    {
        OutputDebugString("ERROR_INVALID_HANDLE, "
            "Likely that the Service Provider has closed the port.\n");
        return FALSE;
    }

    // Unexpected error. No idea what could cause this to happen.
    OutputDebugLastError(dwLastError, "Unexpected WaitCommEvent error: ");
    return FALSE;
}


//
//  FUNCTION: HandleCommEvent(LPOVERLAPPED, LPDWORD, BOOL)
//
//  PURPOSE: Handle an outstanding Comm Event.
//
//  PARAMETERS:
//    lpOverlappedCommEvent - Pointer to the overlapped structure to use.
//    lpfdwEvtMask          - Pointer to DWORD to received Event data.
//     fRetrieveEvent       - Flag to signal if the event needs to be
//                            retrieved, or has already been retrieved.
//
//  RETURN VALUE:
//    TRUE if able to handle a Comm Event.
//    FALSE if unable to setup WaitCommEvent, unable to handle
//    an existing outstanding event or if the CloseEvent has been signaled.
//
//  COMMENTS:
//
//    This function is a helper function for the Read Thread that (if
//    fRetrieveEvent == TRUE) retrieves an outstanding CommEvent and
//    deals with it.  The only event that should occur is an EV_ERR event,
//    signalling that there has been an error on the comm port.
//
//    Normally, comm errors would not be put into the normal data stream
//    as this sample is demonstrating.  Putting it in a status bar would
//    be more appropriate for a real application.
//
//

BOOL HandleCommEvent(LPOVERLAPPED lpOverlappedCommEvent, 
    LPDWORD lpfdwEvtMask, BOOL fRetrieveEvent)
{
    DWORD dwDummy;
    LPSTR lpszOutput;
    char szError[128] = "";
    DWORD dwErrors;
    DWORD nOutput;
    DWORD dwLastError;


    lpszOutput = LocalAlloc(LPTR,256);
    if (lpszOutput == NULL)
    {
        OutputDebugLastError(GetLastError(), "LocalAlloc: ");
        return FALSE;
    }

    // If this fails, it could be because the file was closed (and I/O is
    // finished) or because the overlapped I/O is still in progress.  In
    // either case (or any others) its a bug and return FALSE.
    if (fRetrieveEvent)
        if (!GetOverlappedResult(g_hCommFile, 
                lpOverlappedCommEvent, &dwDummy, FALSE))
        {
            dwLastError = GetLastError();

            // Its possible for this error to occur if the 
            // service provider has closed the port.  Time to end.
            if (dwLastError == ERROR_INVALID_HANDLE)
            {
                OutputDebugString("ERROR_INVALID_HANDLE, "
                    "Likely that the Service Provider has closed the port.\n");
                return FALSE;
            }

            OutputDebugLastError(dwLastError,
                "Unexpected GetOverlappedResult for WaitCommEvent: ");
            return FALSE;
        }

    // Was the event an error?
    if (*lpfdwEvtMask & EV_ERR)
    {
        // Which error was it?
        if (!ClearCommError(g_hCommFile, &dwErrors, NULL))
        {
            dwLastError = GetLastError();

            // Its possible for this error to occur if the 
            // service provider has closed the port.  Time to end.
            if (dwLastError == ERROR_INVALID_HANDLE)
            {
                OutputDebugString("ERROR_INVALID_HANDLE, "
                    "Likely that the Service Provider has closed the port.\n");
                return FALSE;
            }

            OutputDebugLastError(GetLastError(),"ClearCommError: ");
            return FALSE;
        }

        // Its possible that multiple errors occured and were handled
        // in the last ClearCommError.  Because all errors were signaled
        // individually, but cleared all at once, pending comm events 
        // can yield EV_ERR while dwErrors equals 0.  Ignore this event.
        if (dwErrors == 0)
        {
            strcat(szError, "NULL Error");
        }
       
        if (dwErrors & CE_FRAME)
        {
            if (szError[0])
                strcat(szError," and ");

            strcat(szError,"CE_FRAME");
        }

        if (dwErrors & CE_OVERRUN)
        {
            if (szError[0])
                strcat(szError," and ");

            strcat(szError,"CE_OVERRUN");
        }

        if (dwErrors & CE_RXPARITY)
        {
            if (szError[0])
                strcat(szError," and ");

            strcat(szError,"CE_RXPARITY");
        }

        if (dwErrors & ~ (CE_FRAME | CE_OVERRUN | CE_RXPARITY))
        {
            if (szError[0])
                strcat(szError," and ");

            strcat(szError,"EV_ERR Unknown EvtMask");
        }


        nOutput = wsprintf(lpszOutput,
            "Comm Event: '%s', EvtMask = '%lx'\n",
            szError, dwErrors);

        PostWriteToDisplayCtl(lpszOutput, nOutput);
        return TRUE;

    }

    // Should not have gotten here.  Only interested in ERR conditions.

    OutputDebugPrintf("Unexpected comm event %lx",*lpfdwEvtMask);
    return FALSE;
}

