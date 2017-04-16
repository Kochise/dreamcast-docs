/*-----------------------------------------------------------------------------
    This is a part of the Microsoft Source Code Samples. 
    Copyright (C) 1995 Microsoft Corporation.
    All rights reserved. 
    This source code is only intended as a supplement to 
    Microsoft Development Tools and/or WinHelp documentation.
    See these sources for detailed information regarding the 
    Microsoft samples programs.

    MODULE: Writer.c

    PURPOSE: Handles all port writing and write request linked list

    FUNCTIONS:
        WriterProc - Thread procedure handles all writing
        HandleWriteRequests - calls writing procedures based on write request type
        WriterTerminate     - sets the transfer complete event
        WriterFile          - Writes a file transfer packet out the port
        WriterFileStart     - initializes a file transfer
        WriterChar          - Writes a char out the port
        WriterGeneric       - Actual writing funciton handles all i/o operations
        WriterAddNewNode    - Adds new write request packet to linked list
        WriterAddNewNodeTimeout - Adds new node, but can timeout.
        WriterAddExistingNode - Modifies an existing packet and 
                                links it to the linked list
        AddToLinkedList     - Adds the node to the list
        RemoveFromLinkedList - Removes a node
        
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------

    Write request packets are put into the writer request linked list
    and processed by the functions in this module.

    The members of the WRITEREQUEST structure are described as follows:
              
          DWORD     dwWriteType;       // dictates the type of request
          DWORD     dwSize;            // size of data to write
          char      ch;                // character to send
          char *    lpBuf;             // address of data buffer
          HANDLE    hHeap;             // heap containing data buffer
          HWND      hWndProgress;      // hwnd for progress indicator


    dwWriteType can be one of the following values:
                
        WRITE_CHAR       0x01    // indicates the request is for sending a single character

            WriteRequest.ch contains the character to send
                             

        WRITE_FILE       0x02    // indicates the request is for a file transfer

            WriteRequest.dwSize       : contains the size of the buffer
            WriteReqeust.lpBuf        : points to the buffer containing the data to send
            WriteRequest.hHeap        : contains the handle of the heap containing the data buffer
            WriteReqeust.hWndProgress : contains the hwnd of the file transfer progress indicator


        WRITE_FILESTART  0x03    // indicates the a file transfer is starting

            WriteRequest.dwSize : indicates the total size of the file


        WRITE_FILEEND    0x04    // indicates the last block in a file transfer
      

        WRITE_ABORT      0x05    // indicates the file transfer is aborted

        WRITE_BLOCK      0x06    // indicates the request is for sending
                                 // a block of data
             WriteRequest.dwSize : containst the size of the buffer
             WriteRequest.lpBuf  : points to the buffer containing the data to send


-----------------------------------------------------------------------------*/

#include <windows.h>
#include <commctrl.h>

#include "MTTTY.h"

//
// Prototypes for function called only within this file
//
PWRITEREQUEST RemoveFromLinkedList( PWRITEREQUEST );
BOOL WriterAddExistingNode( PWRITEREQUEST, DWORD, DWORD, char, char *, HANDLE, HWND );
BOOL WriterAddNewNode( DWORD, DWORD, char, char *, HANDLE, HWND );
void HandleWriteRequests( void );
void WriterFileStart( DWORD );
void WriterComplete( void );
void WriterAbort( PWRITEREQUEST );
void AddToLinkedList( PWRITEREQUEST );
void AddToFrontOfLinkedList( PWRITEREQUEST );
void WriterGeneric( char *, DWORD );
void WriterFile( PWRITEREQUEST );
void WriterChar( PWRITEREQUEST );
void WriterBlock( PWRITEREQUEST );


/*-----------------------------------------------------------------------------

FUNCTION: WriterProc(LPVOID)

PURPOSE: Thread function controls console input and comm port writing

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
DWORD WINAPI WriterProc(LPVOID lpV)
{
    SYSTEM_INFO sysInfo;
    HANDLE hArray[2];
    DWORD dwRes;
    DWORD dwSize;
    BOOL fDone = FALSE;

    //
    // create a heap for WRITE_REQUEST packets
    //
    GetSystemInfo(&sysInfo);
    ghWriterHeap = HeapCreate(0, sysInfo.dwPageSize*2, sysInfo.dwPageSize*4);
    if (ghWriterHeap == NULL)
        ErrorInComm("HeapCreate (write request heap)");

    //
    // create synchronization events for write requests and file transfers
    //
    ghWriterEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (ghWriterEvent == NULL)
        ErrorInComm("CreateEvent(writ request event)");

    ghTransferCompleteEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (ghTransferCompleteEvent == NULL)
        ErrorInComm("CreateEvent(transfer complete event)");

    //
    // initialize write request linked list
    //
    dwSize = sizeof(WRITEREQUEST);
    gpWriterHead = HeapAlloc(ghWriterHeap, HEAP_ZERO_MEMORY, dwSize);
    gpWriterTail = HeapAlloc(ghWriterHeap, HEAP_ZERO_MEMORY, dwSize);
    gpWriterHead->pNext = gpWriterTail;
    gpWriterTail->pPrev = gpWriterHead;

    hArray[0] = ghWriterEvent;
    hArray[1] = ghThreadExitEvent;
   
    while ( !fDone ) {
        dwRes = WaitForMultipleObjects(2, hArray, FALSE, WRITE_CHECK_TIMEOUT);
        switch(dwRes)
        {
            case WAIT_TIMEOUT:
                    break;

            case WAIT_FAILED:
                    ErrorReporter("WaitForMultipleObjects( writer proc )");
                    break;

            //
            // write request event
            //
            case WAIT_OBJECT_0:
                    HandleWriteRequests();
                    break;
            //
            // thread exit event
            //
            case WAIT_OBJECT_0 + 1:
                    fDone = TRUE;
                    break;
        }
    }

    CloseHandle(ghTransferCompleteEvent);
    CloseHandle(ghWriterEvent);

    //
    // Destroy WRITE_REQUEST heap
    //
    HeapDestroy(ghWriterHeap);
    return 1;
}

/*-----------------------------------------------------------------------------

FUNCTION: HandleWriteRequests

PURPOSE: Retrieves write request and calls the proper function
         depending on the write request type.

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

            5/25/96   AllenD      Modified to include

-----------------------------------------------------------------------------*/
void HandleWriteRequests()
{
    PWRITEREQUEST pWrite;
    BOOL fRes;
    
    pWrite = gpWriterHead->pNext;
    
    while(pWrite != gpWriterTail) {
        switch(pWrite->dwWriteType)
        {
            case WRITE_CHAR:          WriterChar(pWrite);                break;

            case WRITE_FILESTART:     WriterFileStart(pWrite->dwSize);   break;

            case WRITE_FILE:          WriterFile(pWrite);
                                      //
                                      // free data block
                                      //
                                      EnterCriticalSection(&gcsDataHeap);
                                      fRes = HeapFree(pWrite->hHeap, 0, pWrite->lpBuf);
                                      LeaveCriticalSection(&gcsDataHeap);
                                      if (!fRes)
                                          ErrorReporter("HeapFree(file transfer buffer)");
                                      break;

            case WRITE_FILEEND:       WriterComplete();                 break;

            case WRITE_ABORT:         WriterAbort(pWrite);              break;

            case WRITE_BLOCK:         WriterBlock(pWrite);              break;

            default:                  ErrorReporter("Bad write request"); 
                                      break;
        }

        //
        // remove current node and get next node
        //
        pWrite = RemoveFromLinkedList(pWrite);
        pWrite = gpWriterHead->pNext;
    }

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: WriterComplete

PURPOSE: Handle an transfer completion

HISTORY:   Date:      Author:     Comment:
            1/26/96   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void WriterComplete()
{
    if (!SetEvent(ghTransferCompleteEvent))
        ErrorReporter("SetEvent (transfer complete event)");

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: WriterAbort

PURPOSE: Handle an transfer abort.  Delete all writer packets.
         Data packets get deleted with the entire data heap in the transfer
         thread.

HISTORY:   Date:      Author:     Comment:
            1/26/96   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void WriterAbort(PWRITEREQUEST pAbortNode)
{
    PWRITEREQUEST pCurrent;
    PWRITEREQUEST pNextNode;
    BOOL fRes;
    int i = 0;
    char szMessage[30];

    EnterCriticalSection(&gcsWriterHeap);
    // remove all nodes after me
    pCurrent = pAbortNode->pNext;

    while (pCurrent != gpWriterTail) {
        pNextNode = pCurrent->pNext;
        fRes = HeapFree(ghWriterHeap, 0, pCurrent);
        if (!fRes)
            break;
        i++;
        pCurrent = pNextNode;
    }

    pAbortNode->pNext = gpWriterTail;
    gpWriterTail->pPrev = pAbortNode;
    LeaveCriticalSection(&gcsWriterHeap);

    wsprintf(szMessage, "%d packets ignored.\n", i);
    OutputDebugString(szMessage);

    if (!fRes)
        ErrorReporter("HeapFree (Writer heap)");

    if (!SetEvent(ghTransferCompleteEvent))
        ErrorReporter("SetEvent (transfer complete event)");

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: WriterFile(PWRITEREQUEST)

PURPOSE: Handles a file transfer request

PARAMETERS:
    pWrite - pointer to write request packet

COMMENTS: WRITEREQUEST packet contains the following:
            lpBuf       : Address of data buffer
            dwSize      : size of data buffer
            hWndProgress: hwnd of progress indicator
            hHeap       : handle to heap which contains the data buffer

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void WriterFile(PWRITEREQUEST pWrite)
{
    WriterGeneric(pWrite->lpBuf, pWrite->dwSize);

    //
    // update progress indicator (even if aborting)
    //
    if (!PostMessage(pWrite->hWndProgress, PBM_STEPIT, 0, 0))
        ErrorReporter("PostMessage (file transfer status)");

    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: WriterBlock(PWRITEREQUEST)

PURPOSE: Sends a block of characters

PARAMETERS:
    pWrite - pointer to write request packet

COMMENTS: WRITEREQUEST packet contains the following:
            lpBuf       : Address of data buffer
            dwSize      : size of data buffer

HISTORY:   Date:      Author:     Comment:
            1/29/96   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void WriterBlock(PWRITEREQUEST pWrite)
{   

    WriterGeneric(pWrite->lpBuf, pWrite->dwSize);
    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: WriterFileStart(DWORD)

PURPOSE: Initializes a file transfer (send)

PARAMETER:
    dwFileSize - not used

COMMENTS: Provided to do any special initializations for transfer

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it
           11/20/95   AllenD      Took out all test code

-----------------------------------------------------------------------------*/
void WriterFileStart(DWORD dwFileSize)
{
    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: WriterChar(PWRITEREQUEST)

PURPOSE: Handles sending characters

PARAMETER:
    pWrite - pointer to write request packet

COMMENTS: WRITEREQUEST packet contains the following:
            ch : character to send

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void WriterChar(PWRITEREQUEST pWrite)
{
    WriterGeneric(&(pWrite->ch), 1);
    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: WriterGeneric(char *, DWORD)

PURPOSE: Handles sending all types of data

PARAMETER:
    lpBuf     - pointer to data buffer
    dwToWrite - size of buffer

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void WriterGeneric(char * lpBuf, DWORD dwToWrite)
{
    OVERLAPPED osWrite = {0};
    HANDLE hArray[2];
    DWORD dwWritten;
    DWORD dwRes;

    //
    // If no writing is allowed, then just return
    //
    if (NOWRITING(TTYInfo))
        return ;

    //
    // create this writes overlapped structure hEvent
    //
    osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (osWrite.hEvent == NULL)
        ErrorInComm("CreateEvent (overlapped write hEvent)");

    hArray[0] = osWrite.hEvent;
    hArray[1] = ghThreadExitEvent;
    
    //
    // issue write
    //
    if (!WriteFile(COMDEV(TTYInfo), lpBuf, dwToWrite, &dwWritten, &osWrite)) {
        if (GetLastError() == ERROR_IO_PENDING) { 
            //
            // write is delayed
            //
            dwRes = WaitForMultipleObjects(2, hArray, FALSE, INFINITE);
            switch(dwRes)
            {
                //
                // write event set
                //
                case WAIT_OBJECT_0:
                            SetLastError(ERROR_SUCCESS);
                            if (!GetOverlappedResult(COMDEV(TTYInfo), &osWrite, &dwWritten, FALSE)) {
                                if (GetLastError() == ERROR_OPERATION_ABORTED)
                                    UpdateStatus("Write aborted\r\n");
                                else
                                    ErrorInComm("GetOverlappedResult(in Writer)");
                            }
                            
                            if (dwWritten != dwToWrite) {
                                if ((GetLastError() == ERROR_SUCCESS) && SHOWTIMEOUTS(TTYInfo))
                                    UpdateStatus("Write timed out. (overlapped)\r\n");
                                else
                                    ErrorReporter("Error writing data to port (overlapped)");
                            }
                            break;

                //
                // thread exit event set
                //
                case WAIT_OBJECT_0 + 1:
                            break;

                //                
                // wait timed out
                //
                case WAIT_TIMEOUT:
                            UpdateStatus("Wait Timeout in WriterGeneric.\r\n");
                            break;

                case WAIT_FAILED:
                default:    ErrorInComm("WaitForMultipleObjects (WriterGeneric)");
                            break;
            }
        }
        else    
            //
            // writefile failed, but it isn't delayed
            //
            ErrorInComm("WriteFile (in Writer)");
    }
    else {
        //
        // writefile returned immediately
        //
        if (dwWritten != dwToWrite)
            UpdateStatus("Write timed out. (immediate)\r\n");
    }

    CloseHandle(osWrite.hEvent);
    
    return;
}

/*-----------------------------------------------------------------------------

FUNCTION: WriterAddNewNode(DWORD, DWORD, char, char *, HANDLE, HWND)

PURPOSE: Adds a new write request packet

PARAMETERS:
    dwRequestType - write request packet request type
    dwSize        - size of write request
    ch            - character to write
    lpBuf         - address of buffer to write
    hHeap         - heap handle of data buffer
    hProgress     - hwnd of transfer progress bar

RETURN:
    TRUE if node is added to linked list
    FALSE if node can't be allocated.

COMMENTS: Allocates a new packet and fills it based on the
          parameters passed in.

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
BOOL WriterAddNewNode(  DWORD dwRequestType, 
                        DWORD dwSize, 
                        char ch, 
                        char * lpBuf, 
                        HANDLE hHeap, 
                        HWND hProgress)
{
    PWRITEREQUEST pWrite;

    //
    // allocate new packet
    //
    pWrite = HeapAlloc(ghWriterHeap, 0, sizeof(WRITEREQUEST));
    if (pWrite == NULL) {
        ErrorReporter("HeapAlloc (writer packet)");
        return FALSE;
    }

    //
    // assign packet info
    //
    pWrite->dwWriteType  = dwRequestType;
    pWrite->dwSize       = dwSize;
    pWrite->ch           = ch;
    pWrite->lpBuf        = lpBuf;
    pWrite->hHeap        = hHeap;
    pWrite->hWndProgress = hProgress;

    AddToLinkedList(pWrite);
    
    return TRUE;
}

/*-----------------------------------------------------------------------------

FUNCTION: WriterAddNewNodeTimeout(DWORD, DWORD, char, char *, 
                                    HANDLE, HWND, DWORD)

PURPOSE: Adds a new write request packet, timesout if can't allocate packet.

PARAMETERS:
    dwRequestType - write request packet request type
    dwSize        - size of write request
    ch            - character to write
    lpBuf         - address of buffer to write
    hHeap         - heap handle of data buffer
    hProgress     - hwnd of transfer progress bar
    dwTimeout     - timeout value for waiting

RETURN:
    TRUE if node is added to linked list
    FALSE if node can't be allocated.

COMMENTS: Allocates a new packet and fills it based on the
          parameters passed in.  If the first attemp to allocate packet
          fails, then the function sleeps and tries again when it resumes.

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
BOOL WriterAddNewNodeTimeout(   DWORD dwRequestType, 
                                DWORD dwSize, 
                                char ch, 
                                char * lpBuf, 
                                HANDLE hHeap, 
                                HWND hProgress,
                                DWORD dwTimeout  )
{
    PWRITEREQUEST pWrite;

    //
    // attempt first allocation
    //
    pWrite = HeapAlloc(ghWriterHeap, 0, sizeof(WRITEREQUEST));
    if (pWrite == NULL) {
        Sleep(dwTimeout);
        //
        // attempt second allocation
        //
        pWrite = HeapAlloc(ghWriterHeap, 0, sizeof(WRITEREQUEST));
        if (pWrite == NULL) {
            ErrorReporter("HeapAlloc (writer packet)");
            return FALSE;
        }
    }

    //
    // assign packet info
    //
    pWrite->dwWriteType  = dwRequestType;
    pWrite->dwSize       = dwSize;
    pWrite->ch           = ch;
    pWrite->lpBuf        = lpBuf;
    pWrite->hHeap        = hHeap;
    pWrite->hWndProgress = hProgress;

    AddToLinkedList(pWrite);
    
    return TRUE;
}

/*-----------------------------------------------------------------------------

FUNCTION: WriterAddFirstNodeTimeout(DWORD, DWORD, char, char *, 
                                    HANDLE, HWND, DWORD)

PURPOSE: Adds a new write request packet and places it at the front of the 
         list, timesout if can't allocate packet.

PARAMETERS:
    dwRequestType - write request packet request type
    dwSize        - size of write request
    ch            - character to write
    lpBuf         - address of buffer to write
    hHeap         - heap handle of data buffer
    hProgress     - hwnd of transfer progress bar
    dwTimeout     - timeout value for waiting

RETURN:
    TRUE if node is added to linked list
    FALSE if node can't be allocated.

COMMENTS: This function differs from WriterAddNewNodeTimeout only in that
          it places the node at the front of the list.

HISTORY:   Date:      Author:     Comment:
            1/26/96   AllenD      Wrote it

-----------------------------------------------------------------------------*/
BOOL WriterAddFirstNodeTimeout(   DWORD dwRequestType, 
                                DWORD dwSize, 
                                char ch, 
                                char * lpBuf, 
                                HANDLE hHeap, 
                                HWND hProgress,
                                DWORD dwTimeout  )
{
    PWRITEREQUEST pWrite;

    //
    // attempt first allocation
    //
    pWrite = HeapAlloc(ghWriterHeap, 0, sizeof(WRITEREQUEST));
    if (pWrite == NULL) {
        Sleep(dwTimeout);
        //
        // attempt second allocation
        //
        pWrite = HeapAlloc(ghWriterHeap, 0, sizeof(WRITEREQUEST));
        if (pWrite == NULL) {
            ErrorReporter("HeapAlloc (writer packet)");
            return FALSE;
        }
    }

    //
    // assign packet info
    //
    pWrite->dwWriteType  = dwRequestType;
    pWrite->dwSize       = dwSize;
    pWrite->ch           = ch;
    pWrite->lpBuf        = lpBuf;
    pWrite->hHeap        = hHeap;
    pWrite->hWndProgress = hProgress;

    AddToFrontOfLinkedList(pWrite);
    
    return TRUE;
}

/*-----------------------------------------------------------------------------

FUNCTION: WriterAddExistingNode

PURPOSE: Adds a write request packet

PARAMETERS:
    dwRequestType - write request packet request type
    dwSize        - size of write request
    ch            - character to write
    lpBuf         - address of buffer to write
    hHeap         - heap handle of data buffer
    hProgress     - hwnd of transfer progress bar

RETURN: always TRUE

COMMENTS: Similar to WriterAddNewNode, except that the
          memory has already been allocated.

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
BOOL WriterAddExistingNode( PWRITEREQUEST pNode, 
                            DWORD dwRequestType, 
                            DWORD dwSize, 
                            char ch, 
                            char * lpBuf, 
                            HANDLE hHeap, 
                            HWND hProgress)
{
    //
    // assign packet info
    //
    pNode->dwWriteType  = dwRequestType;
    pNode->dwSize       = dwSize;
    pNode->ch           = ch;
    pNode->lpBuf        = lpBuf;
    pNode->hHeap        = hHeap;
    pNode->hWndProgress = hProgress;

    AddToLinkedList(pNode);
 
    return TRUE;
}

/*-----------------------------------------------------------------------------

FUNCTION: AddToLinkedList(PWRITEREQUEST)

PURPOSE: Adds a node to the write request linked list

PARAMETERS:
    pNode - pointer to write request packet to add to linked list

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void AddToLinkedList(PWRITEREQUEST pNode)
{
    PWRITEREQUEST pOldLast;
    //
    // add node to linked list
    //
    EnterCriticalSection(&gcsWriterHeap);

    pOldLast = gpWriterTail->pPrev;

    pNode->pNext = gpWriterTail;
    pNode->pPrev = pOldLast;

    pOldLast->pNext = pNode;
    gpWriterTail->pPrev = pNode;

    LeaveCriticalSection(&gcsWriterHeap);

    //
    // notify writer thread that a node has been added
    // 
    if (!SetEvent(ghWriterEvent))
        ErrorReporter("SetEvent( writer packet )");
    
    return;    
}

/*-----------------------------------------------------------------------------

FUNCTION: AddToFrontOfLinkedList(PWRITEREQUEST)

PURPOSE: Adds a node to the front of the write request linked list

PARAMETERS:
    pNode - pointer to write request packet to add to linked list

HISTORY:   Date:      Author:     Comment:
            1/26/96   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void AddToFrontOfLinkedList(PWRITEREQUEST pNode)
{
    PWRITEREQUEST pNextNode;
    //
    // add node to linked list
    //
    EnterCriticalSection(&gcsWriterHeap);

    pNextNode = gpWriterHead->pNext;
    
    pNextNode->pPrev = pNode;
    gpWriterHead->pNext = pNode;
    
    pNode->pNext = pNextNode;
    pNode->pPrev = gpWriterHead;

    LeaveCriticalSection(&gcsWriterHeap);

    //
    // notify writer thread that a node has been added
    // 
    if (!SetEvent(ghWriterEvent))
        ErrorReporter("SetEvent( writer packet )");
    
    return;    
}

/*-----------------------------------------------------------------------------

FUNCTION: RemoveFromLinkedList(PWRITEREQUEST)

PURPOSE: Deallocates the head node and makes the passed in node 
         the new head node.
         Sets the head node point to node just after the passed in node.
         Returns the node pointed to by the head node.

PARAMETERS:
    pNode - pointer to node to make the new head

RETURN:
    Pointer to next node.  This will be NULL if there are no
    more nodes in the list.

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
PWRITEREQUEST RemoveFromLinkedList(PWRITEREQUEST pNode)
{
    PWRITEREQUEST pNextNode;
    PWRITEREQUEST pPrevNode;
    BOOL bRes;

    EnterCriticalSection(&gcsWriterHeap);
    
    pNextNode = pNode->pNext;
    pPrevNode = pNode->pPrev;    
    
    bRes = HeapFree(ghWriterHeap, 0, pNode);
    
    pPrevNode->pNext = pNextNode;
    pNextNode->pPrev = pPrevNode;

    LeaveCriticalSection(&gcsWriterHeap);

    if (!bRes)
        ErrorReporter("HeapFree(write request)");

    return pNextNode;     // return the freed node's pNext (maybe the tail)
}

