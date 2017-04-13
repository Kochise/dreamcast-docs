///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      XPLIST.CPP
//
//  Description
//      This file implements the classe CMsgQueue and CList used in this
//      transport to process remote messages. The two classes help us process
//      the list of messages selected in the Remote Viewer of a mail client.
//
//  Authors
//      Les Thaler
//      Irving De la Cruz
//
//  Revision: 1.7
//  
// Written for Microsoft Windows Developer Support
// Copyright (c) 1995-1996 Microsoft Corporation. All rights reserved.
//
#include "XPWDSR.H"

enum
{
    STAT,
    EID,
    NUM_PROPS
};
static const SizedSPropTagArray (NUM_PROPS, sptProps) =
{
    NUM_PROPS,
    {
        PR_MSG_STATUS,
        PR_ENTRYID
    }
};

///////////////////////////////////////////////////////////////////////////////
//    CMsgQueue::CMsgQueue()
//
//    Parameters                        
//      None.
//
//    Purpose
//      CMsgQueue class constructor. 
//
//    Return Value
//      None.
//
CMsgQueue::CMsgQueue()
{
    m_ulItems  = 0;
    m_pHead = NULL;
    m_pTail = NULL;
}

///////////////////////////////////////////////////////////////////////////////
//    CMsgQueue::~MsgQueue()
//
//    Parameters                        
//      None. 
//
//    Purpose
//      CMsgQueue class destructor, walks the queue freeing each node
//      and the node's members.
//
//    Return Value
//      None
//
CMsgQueue::~CMsgQueue()
{
    if (!Empty())
    {
        PLIST_NODE pNode;
        do     
        {
            pNode = m_pHead->pNext;
            delete m_pHead;
            m_pHead = pNode;
        } while (pNode);
    }
}

///////////////////////////////////////////////////////////////////////////////
//    CMsgQueue::Insert()
//
//    Parameters                        
//      pNode       Pointer to the node to queue
//
//    Purpose
//      Queues a node into the message queue
//
//    Return Value
//      None.
//
void WINAPI CMsgQueue::Insert (PLIST_NODE pNode)
{
    pNode->pNext = NULL;
    if (Empty())
    {
        m_pHead = m_pTail = pNode;
    }
    else
    {
        m_pTail->pNext = pNode;
        m_pTail = m_pTail->pNext;           
    }
    m_ulItems++;
}

///////////////////////////////////////////////////////////////////////////////
//    CMsgQueue::Delete()
//
//    Parameters                        
//      None.
//
//    Purpose
//      Dequeues a node from the message queue. The caller is responsible for
//      freeing the node after use.
//
//    Return Value
//      The pointer to the dequeued node on success, NULL otherwise
//
PLIST_NODE WINAPI CMsgQueue::Delete()
{   
    if (!m_ulItems)
    {
        return NULL;
    }
    PLIST_NODE pNode = m_pHead;
    if (m_pHead->pNext == NULL)
    {
        m_pHead = m_pTail = NULL;
    }
    else
    {
        m_pHead = m_pHead->pNext;
    }
    m_ulItems--;
    pNode->pNext = NULL;
    return pNode;
}

///////////////////////////////////////////////////////////////////////////////
//    CList::CList()
//
//    Parameters                        
//      None
//
//    Purpose
//      Class constructor for the CList class, the list of downloaded
//      messages. Encapsulates the message queue and methods for manipulating
//      in the context of the CXPLogon object.
//
//    Return Value
//      None.
//
CList::CList()
{
    m_pToDownload = NULL;
    m_pDownloaded = NULL;
    m_pLogon      = NULL;
}
 
///////////////////////////////////////////////////////////////////////////////
//    CList::~CList()
//
//    Parameters                        
//      None.
//
//    Purpose
//      CList class destructor. Frees the TO DO and DONE queues
//
//    Return Value
//      None.
//
CList::~CList()
{
    // free the msg queues
    delete m_pToDownload;
    m_pToDownload = NULL;
    delete m_pDownloaded;
    m_pDownloaded = NULL;
}

///////////////////////////////////////////////////////////////////////////////
//    PropToMID()
//
//    Parameters                        
//      lProp       the MAPI MSGSTATUS_REMOTExx flag
//
//    Purpose
//      Translate the MAPI MSGSTATUS_REMOTExx flag bimask into an internal
//      message ID. This utility function is useful for walking the contents
//      table and checking which messages have been marked for downloading,
//      moving, etc.
//
//    Return Value
//      The message ID if lProp indicates the message was marked for a remote
//      operation, UNMARKED otherwise.
//
MID WINAPI PropToMID (long lProp)
{
    if (lProp & MSGSTATUS_REMOTE_DOWNLOAD)
    {
        if (lProp & MSGSTATUS_REMOTE_DELETE)
        {
            return MSG_MOVE;
        }
        else
        {
            return MSG_DOWNLOAD;
        }
    }
    else
    {
        if (lProp & MSGSTATUS_REMOTE_DELETE)
        {
            return MSG_DELETE;
        }
    }
    return UNMARKED;        
}

///////////////////////////////////////////////////////////////////////////////
//    CList::UpdateTableRow()
//
//    Parameters                        
//      pEID        Pointer to a message entry ID
//      midAction   Action taken on a row of the remote folder contents table
//
//    Purpose
//      Update a message's row in the contents table. Call this
//      method after a remote DOWNLOAD, MOVE or DELETE to synch the local
//      header contents table with what's really on the server.
//
//    Return Value
//      TRUE on success, FALSE otherwise
//
BOOL WINAPI CList::UpdateTableRow (LPBYTE pEID, MID midAction)
{
    SPropValue spvEID = { 0 };
    spvEID.ulPropTag = PR_ENTRYID;
    spvEID.Value.bin.cb = TRANSPORT_MESSAGE_EID_SIZE;
    spvEID.Value.bin.lpb = pEID;
    LPTABLEDATA pTableData = m_pLogon->GetRemoteFolderTableData();
    HRESULT hResult;
    if (midAction == MSG_DOWNLOAD)
    {
        LPSRow pRow;
        ULONG i;
        long lOldFlags;
        hResult = pTableData->HrQueryRow (&spvEID, &pRow, NULL);
        TraceResult ("CList::UpdateTableRow: Failed to query the table row", hResult);
        if (!hResult)
        {
            for (i=0; i<pRow->cValues; i++)
            {
                if (PR_MESSAGE_FLAGS == pRow->lpProps[i].ulPropTag)
                {
                    lOldFlags = pRow->lpProps[i].Value.l;
                    pRow->lpProps[i].Value.l |= MSGFLAG_READ;
                    if (pRow->lpProps[i].Value.l != lOldFlags)
                    {
                        hResult = pTableData->HrModifyRow (pRow);
                    }
                    break; // Out of the FOR() loop
                }
            }
            gpfnFreeBuffer (pRow);
        }
    }
    else
    {
        hResult = pTableData->HrDeleteRow (&spvEID);
    }
    TraceResult ("CList::UpdateTableRow: Failed to update the table row", hResult);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CList::Init()
//
//    Parameters                        
//      none.
//
//    Purpose
//      Initializes the CList object. Creates the 'TO DO' and "DONE'
//      message queues.
//
//    Return Value
//      TRUE on success, FALSE otherwise
//
BOOL WINAPI CList::Init()
{
    if (m_pToDownload)
    {
        delete m_pToDownload;
    }
    m_pToDownload = new CMsgQueue;
    if (m_pDownloaded)
    {
        delete m_pDownloaded;
    }
    m_pDownloaded = new CMsgQueue;

    if (!m_pToDownload || !m_pDownloaded)
    {
        delete m_pToDownload;
        delete m_pDownloaded;
        TraceMessage ("CList::Init: Failed to create download queues");
        return FALSE;
    }
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//    CList::DownLoadMsgs()
//
//    Parameters                        
//      pTable          Pointer to the header contents table
//      ulRowCount      Count of entries in the contents table
//      hPipe           Handle to the named pipe opened to the server
//                      where the messages in being downloaded through.
//
//    Purpose
//      Walks through the contents table and checks the PR_MSG_STATUS of each
//      entry. Messages marked for download, move, or delete are allocated a
//      node for queuing the "TO DO' queue. Messages marked for download or
//      move additionally have a temporary filename created for them to hold
//      the downloaded message. 
//
//      If the resulting 'TO DO' queue is non-empty, the download worker
//      thread is started and the CList object passed to it. This starts the
//      background processing of messages in the 'TO DO' queue.
//
//    Return Value
//      An HRESULT
//
HRESULT WINAPI CList::DownLoadMsgs (LPMAPITABLE pTable, ULONG ulRowCount, HANDLE hPipe)
{
    HRESULT hResult = pTable->SetColumns ((LPSPropTagArray)&sptProps, 0);
    if (hResult)
    {
        TraceResult ("CList::DownLoadMsgs: Failed to set the columns", hResult);
        return hResult;
    }

    LPSRowSet pRows;
    hResult = pTable->QueryRows (ulRowCount, 0, &pRows);
    if (hResult)
    {
        TraceResult ("CList::DownLoadMsgs: Failed to get the rows", hResult);
        return hResult;
    }

    // construct the list of msgs to download/delete/move
    ASSERT (pRows->cRows);
    MID midMsgAction;
    for (ULONG i=0; i<pRows->cRows; i++)
    {
        ASSERT (PR_MSG_STATUS == pRows->aRow[i].lpProps[STAT].ulPropTag);
        ASSERT (PR_ENTRYID == pRows->aRow[i].lpProps[EID].ulPropTag);
        if (pRows->aRow[i].lpProps[STAT].ulPropTag == PR_MSG_STATUS &&
            pRows->aRow[i].lpProps[EID].ulPropTag  == PR_ENTRYID)
        {
            midMsgAction= PropToMID (pRows->aRow[i].lpProps[STAT].Value.l);
            // Queue message only if marked for remote processing
            if (UNMARKED != midMsgAction)
            {
                PLIST_NODE pNode= new LIST_NODE;
                if (NULL == pNode)
                {
                    TraceMessage ("CList::DownLoadMsgs: Failed to allocate new node");
                    hResult = E_OUTOFMEMORY;
                    break;
                }
                ZeroMemory (pNode, sizeof(LIST_NODE));
                pNode->fRetry = FALSE;

                // Only downloaded/moved msgs need the tempfile
                if (midMsgAction == MSG_DOWNLOAD || midMsgAction == MSG_MOVE)                
                {
                    m_pLogon->GetMsgTempFileName (pNode->szFileName);
                }
                ASSERT (TRANSPORT_MESSAGE_EID_SIZE == pRows->aRow[i].lpProps[EID].Value.bin.cb);
                CopyMemory (pNode->Hdr.Info.EID, pRows->aRow[i].lpProps[EID].Value.bin.lpb, TRANSPORT_MESSAGE_EID_SIZE);
                pNode->Hdr.ulMID = pNode->OpStat = midMsgAction;
                // insert in 'TO DO' queue
                m_pToDownload->Insert (pNode);
            }
        }
    }
    FreeProws(pRows);
    if (!hResult)
    {
        ASSERT (!m_pToDownload->Empty());
        DownLoadNow (hPipe);
    }
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CList::DownLoadNow()
//
//    Parameters                        
//      hPipe           Handle to the named pipe opened to the server
//                      where the messages in being downloaded through.
//
//    Purpose
//      For each message in the 'TO DO' queue, check its requested
//      operation and format a control command to send over the pipe to
//      the server. 
//
//      The control command will contain the requested operation code and
//      the remote entry ID of the message. The server will ACK the control
//      command if the operation can be performed on the server side. The 
//      ACK message sent back by the server contains the size in bytes of
//      the data stream that the server will next write to the pipe.
//
//      If the server can't perform the requested operation (e.g. the message
//      can't be opened), it sends back an OP_FAILED command (NAK) and the 
//      dequeued TO DO message is discarded. This is considered a non-fatal error.
//      and the rest of the queue is processed.
//   
//      Downloaded and moved messages have a temporary file created for them before
//      the data transfer to the message store is started. A failure creating the
//      file is also non-fatal, the current message is discarded but processing
//      continues. After the temp file is created, data transfer is started on
//      the pipe. The stream is copied from the pipe into the temp file.
//
//      If the MOVE/DOWNLOAD operation succeeds, the 'TO DO' message is inserted
//      into the 'DONE' queue which is then passed to StartMessage for processing
//      in the spooler Poll() loop.
//
//      On exit, we send the server a 'HANG UP' command.
//
//    Return Value
//      None
//
void WINAPI CList::DownLoadNow (HANDLE hPipe)
{
    PLIST_NODE pNode;
    MSG_HDR CtrlMsg, InMsg;
    DWORD dwBytes;
    m_ulMsgCount = m_pToDownload->m_ulItems;
    for (ULONG i=0; i<m_ulMsgCount; i++)
    {
        pNode = m_pToDownload->Delete();
        if (NULL == pNode)
        {
            TraceMessage ("CList::DownLoadNow: Failed to get node from internal queue");
            continue; // The FOR() loop
        }
        CtrlMsg = pNode->Hdr;
        switch (pNode->Hdr.ulMID)
        {
            case MSG_MOVE :
            case MSG_DOWNLOAD :
                // We need a temp file where we download the server message temporeraly
                // until it gets picked up in IXPLogon::StartMessage()
                pNode->hFile = CreateFile (pNode->szFileName,
                                           GENERIC_READ | GENERIC_WRITE,
                                           FILE_SHARE_READ,
                                           NULL,
                                           CREATE_ALWAYS,
                                           FILE_ATTRIBUTE_TEMPORARY,
                                           NULL);
                if (INVALID_HANDLE_VALUE == pNode->hFile)
                {
                    pNode->OpStat = OP_FAILED;
                    TraceResult ("CList::DownLoadNow: Failed to create local file", GetLastError());
                    goto ProcessNextMessage;
                }
                // The node has a header structure with the command action to instruct
                // the server on what we need to do on this message
                if (!WriteFile (hPipe, &CtrlMsg, sizeof(MSG_HDR), &dwBytes, NULL))
                {
                    TraceResult ("CList::DownLoadNow: (MOVE/COPY) Failed to send control message to host", GetLastError());
                    goto ProcessNextMessage;
                }
                // Upon receiving the control header, the remote host sent a response
                if (!ReadFile (hPipe, &InMsg, sizeof(MSG_HDR), &dwBytes, NULL))
                {
                    TraceResult ("CList::DownLoadNow: (MOVE/COPY) Failed to receive message to data", GetLastError());
                    goto ProcessNextMessage;
                }
                // Check the result of the host and if successful, copy the message to a local file
                if (OP_FAILED == InMsg.ulMID ||
                    NO_ERROR != FileCopy (pNode->hFile, hPipe, InMsg.Info.ulMsgLen))
                {
                    goto ProcessNextMessage;
                }
                // If the message was moved from the remote server, we must remote the
                // row in the remote folder viewer.
                UpdateTableRow (pNode->Hdr.Info.EID, pNode->Hdr.ulMID);
                m_pDownloaded->Insert (pNode);
                pNode = NULL;
                break;

            case MSG_DELETE :
                if (!WriteFile (hPipe, &CtrlMsg, sizeof(MSG_HDR), &dwBytes, NULL))
                {
                    TraceResult ("CList::DownLoadNow: (DELETE) Failed to send control message to host", GetLastError());
                    goto ProcessNextMessage;
                }
                if (!ReadFile (hPipe, &InMsg, sizeof(MSG_HDR), &dwBytes, NULL))
                {
                    TraceResult ("CList::DownLoadNow: (DELETE) Failed to receive message to data", GetLastError());
                    goto ProcessNextMessage;
                }
                if (InMsg.ulMID != OP_FAILED)
                {
                    UpdateTableRow (pNode->Hdr.Info.EID, MSG_DELETE);
                }
                break;
            default :
                TraceMessage ("CList::DownLoadNow: Unknown action on this node");
                break;
        }
ProcessNextMessage:
        m_pLogon->UpdateProgress ((((i + 1) * 100) / m_ulMsgCount), REMOTE_ACTION_DOWNLOADING_MSGS);
        if (pNode)
        {
            if (pNode->hFile)
            {
                CloseHandle (pNode->hFile);
                DeleteFile (pNode->szFileName);
            }
            delete pNode;
        }
    }
    CtrlMsg.ulMID = GOODBYE;
    WriteFile (hPipe, &CtrlMsg, sizeof(MSG_HDR), &dwBytes, NULL);
    m_ulMsgLeft = m_ulMsgCount; 
}

///////////////////////////////////////////////////////////////////////////////
//    CList::UpdateProgress()
//
//    Parameters
//      None
//
//    Purpose
//      Update the progress percentage in the status row after a message is
//      processed in IXPLogon::StartMessage()
//
//    Return Value
//      None
//
void WINAPI CList::UpdateProgress()
{
    if (m_ulMsgCount)
    {
        m_ulMsgLeft--;
        m_pLogon->UpdateProgress ((((m_ulMsgCount - m_ulMsgLeft) * 100) / m_ulMsgCount),
                                    REMOTE_ACTION_PROCESSING_MSGS);
    }
}

///////////////////////////////////////////////////////////////////////////////
//    FileCopy()
//
//    Parameters                        
//      hDest       Handle of stream object receiving the data
//      hSrc        Handle of stream object whence data
//      dwMsgLen    Number of bytes to transfer
//
//    Purpose
//      Transfers dwMsgLen bytes from hSrc to hDest. The objects can be
//      open file handles, pipes, or any stream oriented object that uses
//      the Read/WriteFile semantics.      
//
//    Return Value
//      NO_ERROR on success, ERROR_READ/WRITE_FAULT otherwise
//
long WINAPI FileCopy (HANDLE hDest, HANDLE hSrc, DWORD dwMsgLen)
{
    BYTE abBuffer[IO_BUFFERSIZE]; 
    DWORD dwRead, dwRemaining = dwMsgLen;
    BOOL bSuccess;
    long lResult = NO_ERROR;
    for (DWORD dwWritten=0 ; dwRemaining>0; dwRemaining -= dwWritten)
    {
        bSuccess = ReadFile (hSrc, abBuffer, min(dwRemaining, IO_BUFFERSIZE), &dwRead, NULL);
        if (!dwRead || !bSuccess)
        {
            lResult = ERROR_READ_FAULT;
            break;
        }
        bSuccess = WriteFile (hDest, abBuffer, dwRead, &dwWritten, NULL);
        if (!dwWritten || !bSuccess)
        {
            lResult = ERROR_WRITE_FAULT;
            break;
        }
    }
    if (lResult)
    {
        TraceResult ("CList::FileCopy: IO operation failed", GetLastError());
    }
    else
    {
        FlushFileBuffers (hDest);
        SetFilePointer (hDest, 0, NULL, FILE_BEGIN);
    }
    return lResult;
}

// End of file for XPLIST.CPP
