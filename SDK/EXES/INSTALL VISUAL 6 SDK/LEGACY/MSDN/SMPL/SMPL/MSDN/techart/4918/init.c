/*-----------------------------------------------------------------------------

    This is a part of the Microsoft Source Code Samples. 
    Copyright (C) 1995 Microsoft Corporation.
    All rights reserved. 
    This source code is only intended as a supplement to 
    Microsoft Development Tools and/or WinHelp documentation.
    See these sources for detailed information regarding the 
    Microsoft samples programs.

    MODULE: Init.c

    PURPOSE: Intializes global data and comm port connects.
                Closes comm ports and cleans up global data.

    FUNCTIONS:
        GlobalInitialize  - Init global variables and system objects
        GlobalCleanup     - cleanup global variables and system objects
        ClearTTYContents  - Clears the tty buffer
        InitNewFont       - Creates a new font for the TTY child window
        CreateTTYInfo     - Creates the dynamic tty info structure controlling
                            behavior of tty
        DestroyTTYInfo    - deallocates tty info structure
        StartThreads      - Starts worker threads when a port is opened
        SetupCommPort     - Opens the port for the first time
        WaitForThreads    - Sets the thread exit event and wait for worker
                            threads to exit
        BreakDownCommPort - Closes a connection to the comm port
        DisconnectOK      - Asks user if it is ok to disconnect

-----------------------------------------------------------------------------*/

#include <windows.h>
#include <commctrl.h>
#include "mttty.h"

/*
    Prototypes for functions called only within this file
*/
void StartThreads( void );
DWORD WaitForThreads( DWORD );

/*
    TimeoutsDefault
        We need ReadIntervalTimeout here to cause the read operations
        that we do to actually timeout and become overlapped.
        Specifying 1 here causes ReadFile to return very quickly
        so that our reader thread will continue execution.
*/
COMMTIMEOUTS gTimeoutsDefault = { 0x01, 0, 0, 0, 0 };


/*-----------------------------------------------------------------------------

FUNCTION: GlobalInitialize

PURPOSE: Intializes global variables before any windows are created

COMMENTS: Partner to GlobalCleanup

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void GlobalInitialize()
{
    int cyMenuHeight, cyCaptionHeight, cyFrameHeight;

    //
    // critical sections in status reporting & node management
    //
    InitializeCriticalSection(&gStatusCritical);
    InitializeCriticalSection(&gcsWriterHeap);
    InitializeCriticalSection(&gcsDataHeap);

    //
    // status message event
    //
    ghStatusMessageEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (ghStatusMessageEvent == NULL)
        ErrorReporter("CreateEvent (Status message event)");

    //
    // thread exit event
    //
    ghThreadExitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (ghThreadExitEvent == NULL)
        ErrorReporter("CreateEvent (Thread exit event)");        

    //
    // used in file transfer status bar
    //
    InitCommonControls();

    //
    // font for status reporting control
    //
    ghFontStatus = CreateStatusEditFont();

    //
    // the following are used for sizing the tty window and dialog windows
    //
    gwBaseY = HIWORD(GetDialogBaseUnits());
    cyMenuHeight = GetSystemMetrics(SM_CYMENU);
    cyCaptionHeight = GetSystemMetrics(SM_CYCAPTION);
    cyFrameHeight = GetSystemMetrics(SM_CYFRAME);
    gcyMinimumWindowHeight = cyMenuHeight + \
                            4 * cyCaptionHeight + \
                            2 * cyFrameHeight +
                            (SETTINGSFACTOR + STATUSFACTOR) * gwBaseY ;
    return ;
}


/*-----------------------------------------------------------------------------

FUNCTION: GlobalCleanup

PURPOSE: Cleans up any global variables

COMMENTS: Partner to GlobalInitialize

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void GlobalCleanup()
{
    DeleteCriticalSection(&gStatusCritical);
    DeleteCriticalSection(&gcsWriterHeap);
    DeleteCriticalSection(&gcsDataHeap);
    DeleteObject(ghFontStatus);
    CloseHandle(ghStatusMessageEvent);
    CloseHandle(ghThreadExitEvent);
    HeapDestroy(ghStatusMessageHeap);
    return;
}


/*-----------------------------------------------------------------------------

FUNCTION: ClearTTYContents

PURPOSE: Clears the tty buffer

RETURN: always TRUE

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
BOOL ClearTTYContents()
{
    FillMemory(SCREEN(TTYInfo), MAXCOLS*MAXROWS, ' ');
    return TRUE;
}


/*-----------------------------------------------------------------------------

FUNCTION: InitNewFont(LOGFONT, COLORREF)

PURPOSE: Prepares a font for use in the TTY screen

PARAMETERS:
    LogFont  - New logical font for tty screen
    rgbColor - New color for TTY painting

COMMENTS: Called when a new connection is made, or the TTY font
          is changed by the user.

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void InitNewFont(LOGFONT LogFont, COLORREF rgbColor)
{
    TEXTMETRIC tm;
    HDC        hDC;

    //
    // if old one exists, then I should delete it
    //
    if (HTTYFONT(TTYInfo))
        DeleteObject(HTTYFONT(TTYInfo));

    LFTTYFONT(TTYInfo) = LogFont;
    HTTYFONT(TTYInfo) = CreateFontIndirect(&(LFTTYFONT(TTYInfo)));
    FGCOLOR(TTYInfo) = rgbColor;

    hDC = GetDC( ghwndMain ) ;
    SelectObject( hDC, HTTYFONT( TTYInfo ) ) ;
    GetTextMetrics( hDC, &tm ) ;
    ReleaseDC( ghwndMain, hDC ) ;

    //
    // character width and height
    //
    XCHAR( TTYInfo ) = tm.tmAveCharWidth  ;
    YCHAR( TTYInfo ) = tm.tmHeight + tm.tmExternalLeading ;

    XOFFSET( TTYInfo ) = 0 ;
    YOFFSET( TTYInfo ) = YCHAR(TTYInfo) * ROW(TTYInfo);
}

/*-----------------------------------------------------------------------------

FUNCTION: InitTTYInfo

PURPOSE: Initializes TTY structure

COMMENTS: This structure is a collection of TTY attributes
          used by all parts of this program

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it
            2/14/96   AllenD      Removed npTTYInfo

-----------------------------------------------------------------------------*/
BOOL InitTTYInfo()
{
    //
    // initialize generial TTY info
    //
    COMDEV( TTYInfo )        = NULL ;
    CONNECTED( TTYInfo )     = FALSE ;
    LOCALECHO( TTYInfo )     = FALSE ;
    CURSORSTATE( TTYInfo )   = CS_HIDE ;
    PORT( TTYInfo )          = 1 ;
    BAUDRATE( TTYInfo )      = CBR_9600 ;
    BYTESIZE( TTYInfo )      = 8 ;
    PARITY( TTYInfo )        = NOPARITY ;
    STOPBITS( TTYInfo )      = ONESTOPBIT ;
    AUTOWRAP( TTYInfo )      = TRUE;
    NEWLINE( TTYInfo )       = FALSE;
    XSIZE( TTYInfo )         = 0 ;
    YSIZE( TTYInfo )         = 0 ;
    XSCROLL( TTYInfo )       = 0 ;
    YSCROLL( TTYInfo )       = 0 ;
    COLUMN( TTYInfo )        = 0 ;
    ROW( TTYInfo )           = MAXROWS - 1 ;
    DISPLAYERRORS( TTYInfo ) = TRUE ;

    //
    // timeouts
    //
    TIMEOUTSNEW( TTYInfo )   = gTimeoutsDefault;

    //
    // read state and status events
    //
    gdwReceiveState            = RECEIVE_TTY;
    EVENTFLAGS( TTYInfo )    = EVENTFLAGS_DEFAULT;
    FLAGCHAR( TTYInfo )      = FLAGCHAR_DEFAULT;

    //
    // Flow Control Settings
    //
    DTRCONTROL( TTYInfo )    = DTR_CONTROL_ENABLE;
    RTSCONTROL( TTYInfo )    = RTS_CONTROL_ENABLE;
    XONCHAR( TTYInfo )       = ASCII_XON;
    XOFFCHAR( TTYInfo )      = ASCII_XOFF;
    XONLIMIT( TTYInfo )      = 0;
    XOFFLIMIT( TTYInfo )     = 0;
    CTSOUTFLOW( TTYInfo )    = FALSE;
    DSROUTFLOW( TTYInfo )    = FALSE;
    DSRINFLOW( TTYInfo )     = FALSE;
    XONXOFFOUTFLOW(TTYInfo)  = FALSE;
    XONXOFFINFLOW(TTYInfo)   = FALSE;
    TXAFTERXOFFSENT(TTYInfo) = FALSE;

    NOREADING(TTYInfo)       = FALSE;
    NOWRITING(TTYInfo)       = FALSE;
    NOEVENTS(TTYInfo)        = FALSE;
    NOSTATUS(TTYInfo)        = FALSE;
    SHOWTIMEOUTS(TTYInfo)    = FALSE;

    //
    // setup default font information
    // 
    LFTTYFONT( TTYInfo ).lfHeight =         12 ;
    LFTTYFONT( TTYInfo ).lfWidth =          0 ;
    LFTTYFONT( TTYInfo ).lfEscapement =     0 ;
    LFTTYFONT( TTYInfo ).lfOrientation =    0 ;
    LFTTYFONT( TTYInfo ).lfWeight =         0 ;
    LFTTYFONT( TTYInfo ).lfItalic =         0 ;
    LFTTYFONT( TTYInfo ).lfUnderline =      0 ;
    LFTTYFONT( TTYInfo ).lfStrikeOut =      0 ;
    LFTTYFONT( TTYInfo ).lfCharSet =        OEM_CHARSET ;
    LFTTYFONT( TTYInfo ).lfOutPrecision =   OUT_DEFAULT_PRECIS ;
    LFTTYFONT( TTYInfo ).lfClipPrecision =  CLIP_DEFAULT_PRECIS ;
    LFTTYFONT( TTYInfo ).lfQuality =        DEFAULT_QUALITY ;
    LFTTYFONT( TTYInfo ).lfPitchAndFamily = FIXED_PITCH | FF_MODERN ;
    strcpy( LFTTYFONT( TTYInfo ).lfFaceName, "FixedSys" ) ;

    InitNewFont( LFTTYFONT(TTYInfo), RGB(0,0,0));

    ClearTTYContents();

    return ( TRUE ) ;
}

/*-----------------------------------------------------------------------------

FUNCTION: DestroyTTYInfo

PURPOSE: Frees objects associated with the TTYInfo structure

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it
            2/14/96   AllenD      Removed npTTYInfo

-----------------------------------------------------------------------------*/
void DestroyTTYInfo()
{
    DeleteObject(HTTYFONT(TTYInfo));
}

/*-----------------------------------------------------------------------------

FUNCTION: StartThreads

PURPOSE: Creates the Reader/Status and Writer threads

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void StartThreads(void)
{
    DWORD dwReadStatId;
    DWORD dwWriterId;

    READSTATTHREAD(TTYInfo) = 
            CreateThread( NULL, 
                          0,
                          (LPTHREAD_START_ROUTINE) ReaderAndStatusProc,
                          (LPVOID) ghWndTTY, 
                          0, 
                          &dwReadStatId);

    if (READSTATTHREAD(TTYInfo) == NULL)
        ErrorInComm("CreateThread(Reader/Status)");

    WRITERTHREAD(TTYInfo) = 
            CreateThread( NULL, 
                          0, 
                          (LPTHREAD_START_ROUTINE) WriterProc, 
                          (LPVOID) NULL, 
                          0, 
                          &dwWriterId );
                   
    if (WRITERTHREAD(TTYInfo) == NULL)
        ErrorInComm("CreateThread (Writer)");

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: SetupCommPort( void )

PURPOSE: Setup Communication Port with our settings

RETURN: 
    Handle of comm port is successful
    NULL is error occurs

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
HANDLE SetupCommPort()
{
    //
    // get tty settings from settings dialog
    //
    UpdateTTYInfo();

    //
    // open communication port handle
    //
    COMDEV( TTYInfo ) = CreateFile( gszPort,  
                                      GENERIC_READ | GENERIC_WRITE, 
                                      0, 
                                      0, 
                                      OPEN_EXISTING,
                                      FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
                                      0);

    if (COMDEV(TTYInfo) == INVALID_HANDLE_VALUE) {   
        ErrorReporter("CreateFile");
        return NULL;
    }

    //
    // Save original comm timeouts and set new ones
    //
    if (!GetCommTimeouts( COMDEV(TTYInfo), &(TIMEOUTSORIG(TTYInfo))))
        ErrorReporter("GetCommTimeouts");

    //
    // Set port state
    //
    UpdateConnection();

    //
    // set comm buffer sizes
    //
    SetupComm(COMDEV(TTYInfo), MAX_READ_BUFFER, MAX_WRITE_BUFFER);

    //
    // raise DTR
    //
    if (!EscapeCommFunction(COMDEV(TTYInfo), SETDTR))
        ErrorReporter("EscapeCommFunction (SETDTR)");

    //
    // start threads and set initial thread state to not done
    //
    StartThreads();

    //
    // set overall connect flag
    //
    CONNECTED( TTYInfo ) = TRUE ;

    return COMDEV(TTYInfo);
}

/*-----------------------------------------------------------------------------

FUNCTION: WaitForThreads(DWORD)

PURPOSE: Waits a specified time for the worker threads to exit

PARAMETERS:
    dwTimeout - milliseconds to wait until timeout

RETURN:
    WAIT_OBJECT_0 - successful wait, threads are not running
    WAIT_TIMEOUT  - at least one thread is still running
    WAIT_FAILED   - failure in WaitForMultipleObjects

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

----------------------------------------------------------------------------*/
DWORD WaitForThreads(DWORD dwTimeout)
{	
    HANDLE hThreads[2];
    DWORD  dwRes;

    hThreads[0] = READSTATTHREAD(TTYInfo);
    hThreads[1] = WRITERTHREAD(TTYInfo);

    //
    // set thread exit event here
    //
    SetEvent(ghThreadExitEvent);

    dwRes = WaitForMultipleObjects(2, hThreads, TRUE, dwTimeout);
    switch(dwRes)
    {
        case WAIT_OBJECT_0:
        case WAIT_OBJECT_0 + 1: 
            dwRes = WAIT_OBJECT_0;
            break;

        case WAIT_TIMEOUT:
            
            if (WaitForSingleObject(READSTATTHREAD(TTYInfo), 0) == WAIT_TIMEOUT)
                OutputDebugString("Reader/Status Thread didn't exit.\n\r");

            if (WaitForSingleObject(WRITERTHREAD(TTYInfo), 0) == WAIT_TIMEOUT)
                OutputDebugString("Writer Thread didn't exit.\n\r");

            break;

        default:
            ErrorReporter("WaitForMultipleObjects");
            break;
    }

    //
    // reset thread exit event here
    //
    ResetEvent(ghThreadExitEvent);

    return dwRes;
}

/*-----------------------------------------------------------------------------

FUNCTION: BreakDownCommPort

PURPOSE: Closes a connection to a comm port

RETURN:
    TRUE  - successful breakdown of port
    FALSE - port isn't connected

COMMENTS: Waits for threads to exit,
          clears DTR, restores comm port timeouts, purges any i/o
          and closes all pertinent handles

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
BOOL BreakDownCommPort()
{
    if (!CONNECTED(TTYInfo))
        return FALSE;

    CONNECTED( TTYInfo ) = FALSE;

    //
    // wait for the threads for a small period
    //
    if (WaitForThreads(20000) != WAIT_OBJECT_0)
        /*
            if threads haven't exited, then they will
            interfere with a new connection.  I must abort
            the entire program.
        */
        ErrorHandler("Error closing port.");

    //
    // lower DTR
    //
    if (!EscapeCommFunction(COMDEV(TTYInfo), CLRDTR))
        ErrorReporter("EscapeCommFunction(CLRDTR)");

    //
    // restore original comm timeouts
    //
    if (!SetCommTimeouts(COMDEV(TTYInfo),  &(TIMEOUTSORIG(TTYInfo))))
        ErrorReporter("SetCommTimeouts (Restoration to original)");

    //
    // Purge reads/writes, input buffer and output buffer
    //
    if (!PurgeComm(COMDEV(TTYInfo), PURGE_FLAGS))
        ErrorReporter("PurgeComm");

    CloseHandle(COMDEV(TTYInfo));
    CloseHandle(READSTATTHREAD(TTYInfo));
    CloseHandle(WRITERTHREAD(TTYInfo));

    return TRUE;
}
 
/*-----------------------------------------------------------------------------

FUNCTION: DisconnectOK

PURPOSE: Asks user if it is OK to disconnect

RETURN:
    TRUE  - OK to disconnect
    FALSE - Disconnect not OK

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
BOOL DisconnectOK()
{
    if (!CONNECTED(TTYInfo))
        return TRUE;
    
    return ((MessageBox(ghwndMain, "OK to Disconnect?", gszPort, MB_YESNO)) == IDYES);
}
