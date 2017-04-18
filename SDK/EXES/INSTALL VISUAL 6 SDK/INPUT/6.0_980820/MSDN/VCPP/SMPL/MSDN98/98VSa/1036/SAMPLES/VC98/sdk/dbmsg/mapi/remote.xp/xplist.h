///////////////////////////////////////////////////////////////////////////////
//
//  File Name
//      XPLIST.H 
//
//  Description
//      Data structures, class definitions, and prototypes for downloading
//      messages. Here define CList and CMsgQueue.
//      CList holds a pointer to two messages queues: Messages to download
//      and downloaded messages that are pending processing from the spooler.
//
//  Author
//      Les Thaler
//
//  Revision: 1.7
//
// Written for Microsoft Windows Developer Support
// Copyright (c) 1995-1996 Microsoft Corporation. All rights reserved.
//
#ifndef _XPLIST_H_
#define _XPLIST_H_

long WINAPI FileCopy (HANDLE hTemp, HANDLE hPipe, DWORD dwMsgLen);
MID WINAPI PropToMID (long lProp);

class CList;
class CXPLogon;

// node in queue of downloaded/to-be-downloaded messages
typedef struct _LIST_NODE
{
    struct _LIST_NODE *     pNext;
    HANDLE                  hFile;
    TCHAR                   szFileName[_MAX_PATH];
    MSG_HDR                 Hdr;
    MID                     OpStat;
    BOOL                    fRetry;
} LIST_NODE, *PLIST_NODE;

    
// FIFO queue of downloaded/to-be-downloaded messages
class CMsgQueue
{   
friend CList;
///////////////////////////////////////////////////////////////////////////////
// Member functions specific to this class
//
public:
    void WINAPI Insert
                    (PLIST_NODE             pNode);
    PLIST_NODE WINAPI Delete
                    ();
    inline BOOL WINAPI Empty
                    () { return m_ulItems == 0;};

///////////////////////////////////////////////////////////////////////////////
// Constructors and destructors
//
    CMsgQueue();
    ~CMsgQueue();        

///////////////////////////////////////////////////////////////////////////////
// Data members
//
private :
    PLIST_NODE      m_pHead;
    PLIST_NODE      m_pTail;
public:
    ULONG           m_ulItems;
};

// Object for manipulating downloaded/to-be-downloaded queues
// including managing data transfer with remote server
class CList
{
///////////////////////////////////////////////////////////////////////////////
// Member functions specific to this class
//
public :
    BOOL WINAPI Init
                    ();
    STDMETHODIMP DownLoadMsgs
                    (LPMAPITABLE                pTable,
                     ULONG                      ulRowCount,
                     HANDLE                     hPipe);
    BOOL WINAPI UpdateTableRow
                    (LPBYTE                     pEID,
                     MID                        midAction);
    inline void WINAPI SetLogon
                    (CXPLogon *                 pLogon)
                    { m_pLogon = pLogon; }
    inline PLIST_NODE WINAPI GetDownloadNode
                    () { if (m_pDownloaded)
                         { return m_pDownloaded->Delete(); }
                         return NULL; }
    inline BOOL WINAPI AreTherePendingDownloads
                    () { if (m_pDownloaded)
                         { return (!m_pDownloaded->Empty()); }
                         return FALSE; }
    inline BOOL WINAPI QueuePendingMsgFile
                    (LPTSTR                     pstrFileName)
                    { PLIST_NODE pNode = new LIST_NODE;
                      if (pNode)
                      { ZeroMemory (pNode, sizeof(LIST_NODE));
                        lstrcpy (pNode->szFileName, pstrFileName);
                        m_pDownloaded->Insert (pNode);
                        return TRUE;
                      }
                      TraceMessage ("CLisg::QueuePendingMsgFile: Failed to allocate new node");
                      return FALSE; }
    void WINAPI UpdateProgress
                    ();
    inline void WINAPI ReQueueNode
                    (PLIST_NODE                 pNode)
                    { m_pToDownload->Insert (pNode); }

private :
    void WINAPI DownLoadNow
                    (HANDLE                     hPipe);
///////////////////////////////////////////////////////////////////////////////
// Constructors and destructors
//
public :
    CList();
    ~CList();

///////////////////////////////////////////////////////////////////////////////
// Data members
//
private :
    ULONG               m_ulMsgCount;
    ULONG               m_ulMsgLeft;
    CXPLogon *          m_pLogon;           // We need access to his stuff
    CMsgQueue *         m_pToDownload;      // 'TO DO' queue
    CMsgQueue *         m_pDownloaded;      // 'DONE' queue
};

#endif // _XPLIST_H_

// End of file for XPLIST.H
