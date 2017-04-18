///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      SUPPORT.CPP
//
//  Description
//      Support functions for remote admin program.
//
//  Author
//      Irving De la Cruz
//      
//  Revision: 1.7
//
// Written for Microsoft Windows Developer Support
// Copyright (c) 1995-1996 Microsoft Corporation. All rights reserved.
//
#include "_WINDS.H"

///////////////////////////////////////////////////////////////////////////////
//    ReleaseSyncObj()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
void WINAPI ReleaseSyncObj()
{
    DeleteCriticalSection (&g_csIOInfo);
    DeleteCriticalSection (&g_csPipeID);
    DeleteCriticalSection (&g_csNotifLinks);
    DeleteCriticalSection (&g_csServiceState);
    CloseHandle (g_IOInfo.hResumeEvent);
}

///////////////////////////////////////////////////////////////////////////////
//    LoadSettingsFromRegistry()
//
//    Parameters
//      None
//
//    Purpose
//      This function is used to load the application setting structure values
//      from the registry under a subkey for our application. The entire data
//      structure is read from a single sub entry as an array of binary data,
//      unreadable to humans.
//      
//    Return Value
//      None
//      
void WINAPI LoadSettingsFromRegistry()
{
    HKEY hAppKey;
    // Try to open the key in the registry, open it with READ rights,
    // and read the data into our strcture
    if (ERROR_SUCCESS == RegOpenKeyEx (HKEY_LOCAL_MACHINE,
                                       WINDS_SERVICE_REGISTRY_KEY,
                                       0,
                                       KEY_READ,
                                       &hAppKey))
    {
        ULONG cbSize = MAX_PATH*sizeof(TCHAR);
        DWORD dwError = RegQueryValueEx (hAppKey,
                                         DATA_FILE_SUB_KEY,
                                         NULL,
                                         NULL,
                                         (LPBYTE)g_szDataFile,
                                         &cbSize);
        RegCloseKey (hAppKey);
        // If we failed to get the data from the registry we can't return
        // yet, we will proceed to initialize the options with default
        // values
        if (ERROR_SUCCESS == dwError)
        {
            return;
        }
    }
    // If we couldn't read the file name, then initialize to default values
    lstrcpy (g_szDataFile, TEXT(".\\WINDS.DAT"));
}

///////////////////////////////////////////////////////////////////////////////
//    SaveSettingsToRegistry()
//
//    Parameters
//      None
//
//    Purpose
//      This function is used to save the settings structure values to the
//      registry under a subkey for our application. The key where we write
//      the values is created if it doesn't exist. The entire structure data
//      is written to a single sub entry as an array of binary data,
//      unreadable to humans.
//      
//    Return Value
//      None
//      
void WINAPI SaveSettingsToRegistry()
{
    HKEY hAppKey;
    DWORD dwDisposition = MAX_PATH*sizeof(TCHAR);
    // Try to open the key in the registry, open it with READ/WRITE rights
    if (ERROR_SUCCESS != RegCreateKeyEx (HKEY_LOCAL_MACHINE,
                                         WINDS_SERVICE_REGISTRY_KEY,
                                         0,
                                         NULL,
                                         REG_OPTION_NON_VOLATILE,
                                         KEY_WRITE,
                                         NULL,
                                         &hAppKey,
                                         &dwDisposition))
    {
        // If we fail to access the registry, we need to get out, we don't
        // have a key opened where to write
        TraceResult ("SaveSettingsToRegistry: Failed to open app key", HRESULT_FROM_WIN32(GetLastError()));
    }
    else
    {
        // With the opened key handle, create a sub entry where we save our
        // structure values. For this sample we just write the entire
        // structure as a big blob of data, which we read the save way.
        if (ERROR_SUCCESS != RegSetValueEx (hAppKey,
                                            DATA_FILE_SUB_KEY,
                                            0,
                                            REG_SZ,
                                            (LPBYTE)g_szDataFile,
                                            (lstrlen (g_szDataFile)+1)*sizeof(TCHAR)))
        {
            TraceResult ("SaveSettingsToRegistry: Failed to save registry values", HRESULT_FROM_WIN32(GetLastError()));
        }
        // Close the handle we have open and return the appropiate flag
        RegCloseKey (hAppKey);
    }
}

///////////////////////////////////////////////////////////////////////////////
//    GetLocalTempFileName()
//
//    Parameters
//      pszFileName     Pointer to a buffer allocated by the caller where the
//                      function returns a fully qualified patha and file for
//                      a uniquely named temporary file name.
//
//    Purpose
//      This function creates a temporary file name. The file name will be
//      returned in the pszFileName buffer which must have been allocated by
//      the caller. The file will have a fully qualified path to its location.
//      The location of the file is on the TEMP directory as set in the system.
//
//    Return Value
//      0 if the function is successful at creating a temporary
//      unique file name. A system error code otherwise.
//
HRESULT WINAPI GetLocalTempFileName(LPTSTR pszFileName)
{
    HRESULT hResult = S_OK;
    TCHAR szTmpPath[_MAX_PATH];

    // Ask the system for the TEMP directory
    if (!GetTempPath (_MAX_PATH, szTmpPath))
    {
        hResult = HRESULT_FROM_WIN32(GetLastError());
        TraceResult ("GetLocalTempFileName: Failed to get temp path", hResult);
        return hResult;
    }

    if (!GetTempFileName (szTmpPath,        // Call the Win32 API
                          TEXT("WDS"),      // Our fixed prefix for temp files
                          0,                // Use a pseudo-unique number
                          pszFileName))     // Destination buffer
    {
        hResult = HRESULT_FROM_WIN32(GetLastError());
        TraceResult ("GetLocalTempFileName: Failed to get temp file name", hResult);
    }
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    FileCopy()
//
//    Parameters                        
//      hDest           handle to destination file/stream
//      hSrc            handle to source file/stream
//      dwMsgLen        number of bytes to copy
//
//    Purpose
//      Copies bytes from one open file or stream object to another file
//      stream object.
//      
//    Return Value
//      NO_ERROR on success, ERROR_READ/WRITE_FAULT otherwise
//      
long WINAPI FileCopy(HANDLE hDest, HANDLE hSrc, DWORD dwMsgLen)
{
    BYTE  buf[IO_BUFFERSIZE]; 
    DWORD nRead, nRemaining = dwMsgLen;
    BOOL  bRes;
    for (DWORD nWritten=0; nRemaining>0; nRemaining -= nWritten)
    {
        bRes = ReadFile (hSrc, buf, min(nRemaining, (DWORD)IO_BUFFERSIZE), &nRead, NULL);
        if (!nRead || !bRes)
        {
            return HRESULT_FROM_WIN32(ERROR_READ_FAULT);
        }
        bRes = WriteFile(hDest, buf, nRead, &nWritten, NULL);
        if (!nWritten || !bRes)
        {
            return HRESULT_FROM_WIN32(ERROR_WRITE_FAULT);
        }
    }
    return NO_ERROR;
}

///////////////////////////////////////////////////////////////////////////////
//    WaitForClientConnection()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
long WINAPI WaitForClientConnection (HANDLE hPipe, DWORD dwTimeOut)
{
    dwTimeOut *= 1000; // The timeout value comes is seconds so we must convert them to milliseconds.

    long lResult = 0;
    BOOL bResult;
    OVERLAPPED ovWait = { 0 };
    ovWait.hEvent = CreateEvent (NULL, FALSE, FALSE, NULL);
    if (NULL == ovWait.hEvent)
    {
        lResult = HRESULT_FROM_WIN32(GetLastError());
        TraceResult ("WaitForClientConnection: Failed to create wait event", lResult);
    }
    else
    {
        bResult = ConnectNamedPipe (hPipe, &ovWait);
        if (FALSE == bResult)
        {
            lResult = HRESULT_FROM_WIN32(GetLastError());
            if (HRESULT_FROM_WIN32(lResult) == HRESULT_FROM_WIN32(ERROR_IO_PENDING) ||
                HRESULT_FROM_WIN32(lResult) == HRESULT_FROM_WIN32(ERROR_PIPE_CONNECTED))
            {
                lResult = S_OK;
            }
        }
        if (!lResult)
        {
            lResult = WaitForSingleObject (ovWait.hEvent, dwTimeOut);
            if (WAIT_OBJECT_0 == lResult)
            {
                lResult = 0; // No error;
            }
            else
            {
                TraceMessage ("WaitForClientConnection: Client did not connect. Timeout");
                lResult = HRESULT_FROM_WIN32(ERROR_PIPE_NOT_CONNECTED);
            }
        }
        else
        {
            lResult = HRESULT_FROM_WIN32(GetLastError());
            TraceResult ("WaitForClientConnection: Failed to wait for connection", lResult);
        }
        CloseHandle (ovWait.hEvent);
    }
    return lResult;
}

///////////////////////////////////////////////////////////////////////////////
//    AnsiToUnicode()
//
//    Parameters
//      
//    Purpose
//
//    Return Value
//      None.
//
HRESULT WINAPI AnsiToUnicode (LPSTR   szStr,
                              LPWSTR  wcStr,
                              ULONG   cchUnicode)
{
    HRESULT hResult = S_OK;
    // Do we have a string to duplicate?
    if (!szStr || !wcStr)
    {
        TraceMessage ("AnsiToUnicode: NULL string pointers");
        return E_INVALIDARG;
    }
    int iChars = MultiByteToWideChar (CP_ACP,
                                      MB_PRECOMPOSED,
                                      szStr,
                                      -1,
                                      wcStr,
                                      cchUnicode);
    if (0 == iChars)
    {
        hResult = HRESULT_FROM_WIN32(GetLastError());
        TraceResult ("AnsiToUnicode: Failed tp convert to UNICODE", hResult);
    }
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    UnicodeToAnsi()
//
//    Parameters
//      
//    Purpose
//
//    Return Value
//      None.
//
HRESULT WINAPI UnicodeToAnsi (LPWSTR  wcStr,
                              LPSTR   szStr,
                              ULONG   cchAnsi)
{
    HRESULT hResult = S_OK;
    // Do we have a string to duplicate?
    if (!szStr || !wcStr)
    {
        TraceMessage ("UnicodeToAnsi: NULL string pointers");
        return E_INVALIDARG;
    }
    int iChars = WideCharToMultiByte (CP_ACP,
                                      0,
                                      wcStr,
                                      -1,
                                      szStr,
                                      cchAnsi,
                                      NULL,
                                      NULL);
    if (0 == iChars)
    {
        hResult = HRESULT_FROM_WIN32(GetLastError());
        TraceResult ("UnicodeToAnsi: Failed tp convert to UNICODE", hResult);
    }
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    GetNextPipeID()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
DWORD WINAPI GetNextPipeID()
{
    DWORD dwPipeID;
    EnterCriticalSection (&g_csPipeID);
    if (g_dwNextPipeID > MAX_PIPE_NUMBER)
    {
        g_dwNextPipeID = MIN_PIPE_NUMBER;
    }
    dwPipeID = g_dwNextPipeID;
    g_dwNextPipeID++;
    LeaveCriticalSection (&g_csPipeID);
    return dwPipeID;
}

///////////////////////////////////////////////////////////////////////////////
//    CObjectList::CObjectList()
//
//    Parameters
//      
//    Purpose
//
//    Return Value
//      None.
//
CObjectList::CObjectList()
{
    TraceMessage ("CObjectList: Constructor called");
    m_hHeap = GetProcessHeap();
    m_pHead = NULL;
    InitializeCriticalSection (&m_csObj);
}

///////////////////////////////////////////////////////////////////////////////
//    CObjectList::~CObjectList()
//
//    Parameters
//      
//    Purpose
//
//    Return Value
//      None.
//
CObjectList::~CObjectList()
{
    TraceMessage ("CObjectList: Destructor called");
    // Free the entire list
    POBJLIST_NODE pNode = m_pHead;
    while (m_pHead)
    {
        pNode = m_pHead->pNext;
        HeapFree (m_hHeap, 0, m_pHead);
        m_pHead = pNode;
    }
    DeleteCriticalSection (&m_csObj);
}

///////////////////////////////////////////////////////////////////////////////
//    CObjectList::Insert()
//
//    Parameters
//      
//    Purpose
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CObjectList::Insert (DWORD             dwObjID,
                                  LPTSTR            pObjName,
                                  WINDS_AB_OBJTYPE  ObjType)
{
    // Allocate a new node
    POBJLIST_NODE pNode, pNewNode = (POBJLIST_NODE)HeapAlloc (m_hHeap,
                                                              HEAP_ZERO_MEMORY,
                                                              sizeof(OBJLIST_NODE));
    if (NULL == pNewNode)
    {
        TraceResult ("CObjectList::Insert: Failed to allocate new node", E_OUTOFMEMORY);
        return E_OUTOFMEMORY;
    }
    // Copy the data of the node
    // pNewNode->pNext = NULL; <- implied in the allocation
    pNewNode->dwObjID = dwObjID;
    pNewNode->ObjType = ObjType;
    lstrcpy (pNewNode->szObjAlias, pObjName);
    
    EnterCriticalSection (&m_csObj);
    // Insert the node at the end of the list
    if (m_pHead)
    {
        pNode = m_pHead;
        while (m_pHead)
        {
            if (NULL == pNode->pNext)
            {
                pNode->pNext = pNewNode;
                break; // Out of the WHILE() loop
            }
            pNode = pNode->pNext;
        }
    }
    else
    {
        m_pHead = pNewNode;
    }
    LeaveCriticalSection (&m_csObj);
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//    CObjectList::Delete()
//
//    Parameters
//      
//    Purpose
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CObjectList::Delete (DWORD dwObjID)
{
    HRESULT hResult = HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
    EnterCriticalSection (&m_csObj);
    POBJLIST_NODE pNext, pPrev = NULL, pNode = m_pHead;
    while (pNode)
    {
        if (pNode->dwObjID == dwObjID)
        {
            // If the node is the head of the list, make the head point to the next node
            if (m_pHead == pNode)
            {
                m_pHead = m_pHead->pNext;
            }
            // Save the next pointer so that we may delete the current node
            pNext = pNode->pNext;
            HeapFree (m_hHeap, 0, pNode);
            if (pPrev)
            {
                pPrev->pNext = pNext;
            }
            hResult = S_OK;
            break; // Out of the WHILE() loop
        }
        else
        {
            pPrev = pNode;
            pNode = pNode->pNext;
        }
    }
    LeaveCriticalSection (&m_csObj);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CObjectList::FindObjFromID()
//
//    Parameters
//      
//    Purpose
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CObjectList::FindObjFromID (DWORD              dwObjID,
                                         LPTSTR             pObjName,
                                         WINDS_AB_OBJTYPE * pObjType)
{
    HRESULT hResult = HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
    EnterCriticalSection (&m_csObj);
    POBJLIST_NODE pNode = m_pHead;
    while (pNode)
    {
        if (pNode->dwObjID == dwObjID)
        {
            *pObjType = pNode->ObjType;
            lstrcpy (pObjName, pNode->szObjAlias);
            hResult = S_OK; 
            break; // Out of the WHILE() loop
        }
        pNode = pNode->pNext;
    }
    LeaveCriticalSection (&m_csObj);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CObjectList::FindObjFromName()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CObjectList::FindObjFromName (WINDS_AB_OBJTYPE     ObjType,
                                           LPTSTR               pObjName,
                                           DWORD *              pdwObjID)
{
    HRESULT hResult = HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
    EnterCriticalSection (&m_csObj);
    POBJLIST_NODE pNode = m_pHead;
    while (pNode)
    {
        if (pNode->ObjType == ObjType && 0 == lstrcmpi (pNode->szObjAlias, pObjName))
        {
            *pdwObjID = pNode->dwObjID;
            hResult = S_OK;
            break; // Out of the WHILE() loop
        }
        pNode = pNode->pNext;
    }
    LeaveCriticalSection (&m_csObj);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CObjectList::FindObjAndTypeFromName()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//      An HRESULT
//
STDMETHODIMP CObjectList::FindObjAndTypeFromName (LPTSTR               pObjName,
                                                  WINDS_AB_OBJTYPE *   pObjType,
                                                  DWORD *              pdwObjID)
{
    HRESULT hResult = HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
    EnterCriticalSection (&m_csObj);
    POBJLIST_NODE pNode = m_pHead;
    while (pNode)
    {
        if (0 == lstrcmpi (pNode->szObjAlias, pObjName))
        {
            *pObjType = pNode->ObjType;
            *pdwObjID = pNode->dwObjID;
            hResult = S_OK;
            break; // Out of the WHILE() loop
        }
        pNode = pNode->pNext;
    }
    LeaveCriticalSection (&m_csObj);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CObjectList::IsAliasNameAvailable()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//      An HRESULT
//
BOOL WINAPI CObjectList::IsAliasNameAvailable (LPTSTR pObjName)
{
    BOOL bResult = TRUE;
    EnterCriticalSection (&m_csObj);
    POBJLIST_NODE pNode = m_pHead;
    while (pNode)
    {
        if (0 == lstrcmpi (pNode->szObjAlias, pObjName))
        {
            bResult = FALSE;
            break; // Out of the WHILE() loop
        }
        pNode = pNode->pNext;
    }
    LeaveCriticalSection (&m_csObj);
    return bResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CreateDLsDirectory()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
HRESULT WINAPI CreateDLsDirectory (LPSTORAGE pStorage)
{
    LPSTORAGE pPFStg;
    HRESULT hResult = pStorage->CreateStorage (DISTRIBUTION_LISTS, CREATE_FLAGS, 0, 0, &pPFStg);
    if (!hResult)
    {
        pPFStg->Release();
    }
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CreatePublicFoldersDirectory()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
HRESULT WINAPI CreatePublicFoldersDirectory (LPSTORAGE pStorage)
{
    LPSTORAGE pPFStg;
    HRESULT hResult = pStorage->CreateStorage (PUBLIC_FOLDERS_ROOT, CREATE_FLAGS, 0, 0, &pPFStg);
    if (!hResult)
    {
        pPFStg->Release();
    }
    return hResult;
}

// End of file for SUPPORT.CPP
