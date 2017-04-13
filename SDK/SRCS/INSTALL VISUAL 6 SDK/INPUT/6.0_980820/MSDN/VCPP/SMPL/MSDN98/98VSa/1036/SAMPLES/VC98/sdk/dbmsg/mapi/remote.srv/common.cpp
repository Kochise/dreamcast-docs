///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      COMMON.CPP
//
//  Description
//
//  Author
//      Irving De la Cruz
//
//  Revision: 1.7
//
// Written for Microsoft Windows Developer Support
// Copyright (c) 1995-1996 Microsoft Corporation. All rights reserved.
//
#include <WINDOWS.H>
#include "TRACES.H"
#include "WINDSGBL.H"
#include "WDSADM.H"
#include "COMMON.H"

// Remark this line to turn verbose tracing OFF
//#define DO_INFO_TRACES
#ifdef DO_INFO_TRACES
#define InfoTrace(a)        TraceInfoMessage(a)
#else
#define InfoTrace(a)        0
#endif // DO_INFO_TRACES


extern "C"
{
    extern HINSTANCE ghInstance;
    extern TCHAR g_szAppTitle[];
}

///////////////////////////////////////////////////////////////////////////////
//    InsertNewDLMNodeA()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
void WINAPI InsertNewDLMNodeA (DLM_INFO_A Info, DLM_XMIT_LIST_A * pList)
{
    DLM_LIST_A * pNewNode = (DLM_LIST_A *)midl_user_allocate (sizeof (DLM_LIST_A));
    if (NULL == pNewNode)
    {
        TraceMessage ("InsertNewDLMNodeA: Failed to allocate new node");
        return;
    }
    pNewNode->Info = Info;
    pNewNode->pNext = NULL;
    
    DLM_XMIT_LIST_A * pCurrent = pList;
    while (pCurrent->pNext)
    {
        pCurrent = pCurrent->pNext;
    }
    pCurrent->pNext = pNewNode;
}

///////////////////////////////////////////////////////////////////////////////
//    DLM_XMIT_LIST_A_to_xmit()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
void __RPC_USER DLM_XMIT_LIST_A_to_xmit (DLM_XMIT_LIST_A __RPC_FAR * pList,
                                         DLM_ARRAY_A __RPC_FAR * __RPC_FAR * ppArray)
{
    InfoTrace ("DLM_XMIT_LIST_A_to_xmit: Function invoked");

    DLM_XMIT_LIST_A * pHead = pList;  // save pointer to start
    DLM_ARRAY_A * pArray;

    // Count the number of member in the list
    ULONG ulCount = 0;
    for (; pList != NULL; pList = pList->pNext)
    {
        ulCount++;
    }

    *ppArray = NULL;

    // Allocate the memory for the array using the MIDL memory allocator (which we implement)
    pArray = (DLM_ARRAY_A *)midl_user_allocate (sizeof(DLM_ARRAY_A) + (ulCount * sizeof(DLM_INFO_A)));
    if (NULL == pArray)
    {
        TraceMessage ("DLM_XMIT_LIST_A_to_xmit: Failed to allocate XMIT array");
        return;
    }
    pArray->dwCount = ulCount;

    // Copy the linked list of members into the allocated array.
    for (ulCount = 0, pList = pHead; pList != NULL; pList = pList->pNext)
    {
        pArray->pMembers[ulCount++] = pList->Info;
    }

    // Return the array allocated to the RPC stubs
    *ppArray = pArray;
}

///////////////////////////////////////////////////////////////////////////////
//    DLM_XMIT_LIST_A_from_xmit()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
void __RPC_USER DLM_XMIT_LIST_A_from_xmit (DLM_ARRAY_A __RPC_FAR * pArray,
                                           DLM_XMIT_LIST_A __RPC_FAR * pList)
{
    InfoTrace ("DLM_XMIT_LIST_A_from_xmit: Function invoked");
    
    if (pArray->dwCount <= 0)
    {
        pList = NULL;
        return;
    }

    if (pList == NULL)
    {
        InsertNewDLMNodeA (pArray->pMembers[0], pList);
    }
    else
    {
        DLM_XMIT_LIST_A_free_inst (pList);
        pList->Info = pArray->pMembers[0];
        pList->pNext = NULL;
    }

    for (UINT i=1; i<pArray->dwCount; i++)
    {
        InsertNewDLMNodeA (pArray->pMembers[i], pList);
    }
}

///////////////////////////////////////////////////////////////////////////////
//    DLM_XMIT_LIST_A_free_inst()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
void __RPC_USER DLM_XMIT_LIST_A_free_inst (DLM_XMIT_LIST_A __RPC_FAR * pList)
{
    InfoTrace ("DLM_XMIT_LIST_A_free_inst: Function invoked");
    // Don't delete the first node.
    DLM_XMIT_LIST_A * pNextNode, *pNode = pList->pNext;
    ZeroMemory (pList, sizeof(DLM_XMIT_LIST_A));

    while (pNode)
    {
        pNextNode = pNode->pNext;
        midl_user_free (pNode);
        pNode = pNextNode;
    }
}

///////////////////////////////////////////////////////////////////////////////
//    DLM_XMIT_LIST_A_free_xmit()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
void __RPC_USER DLM_XMIT_LIST_A_free_xmit (DLM_ARRAY_A __RPC_FAR * pArray)
{
    InfoTrace ("DLM_XMIT_LIST_A_free_xmit: Function invoked");
    midl_user_free (pArray);
}

///////////////////////////////////////////////////////////////////////////////
//    InsertNewDLMNodeW()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
void WINAPI InsertNewDLMNodeW (DLM_INFO_W Info, DLM_XMIT_LIST_W * pList)
{
    DLM_LIST_W * pNewNode = (DLM_LIST_W *)midl_user_allocate (sizeof (DLM_LIST_W));
    if (NULL == pNewNode)
    {
        TraceMessage ("InsertNewDLMNodeW: Failed to allocate new node");
        return;
    }
    pNewNode->Info = Info;
    pNewNode->pNext = NULL;
    
    DLM_XMIT_LIST_W * pCurrent = pList;
    while (pCurrent->pNext)
    {
        pCurrent = pCurrent->pNext;
    }
    pCurrent->pNext = pNewNode;
}

///////////////////////////////////////////////////////////////////////////////
//    DLM_XMIT_LIST_W_to_xmit()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
void __RPC_USER DLM_XMIT_LIST_W_to_xmit (DLM_XMIT_LIST_W __RPC_FAR * pList,
                                         DLM_ARRAY_W __RPC_FAR * __RPC_FAR * ppArray)
{
    InfoTrace ("DLM_XMIT_LIST_W_to_xmit: Function invoked");

    DLM_XMIT_LIST_W * pHead = pList;  // save pointer to start
    DLM_ARRAY_W * pArray;

    // Count the number of member in the list
    ULONG ulCount = 0;
    for (; pList != NULL; pList = pList->pNext)
    {
        ulCount++;
    }

    *ppArray = NULL;

    // Allocate the memory for the array using the MIDL memory allocator (which we implement)
    pArray = (DLM_ARRAY_W *)midl_user_allocate (sizeof(DLM_ARRAY_W) + (ulCount * sizeof(DLM_INFO_W)));
    if (NULL == pArray)
    {
        TraceMessage ("DLM_XMIT_LIST_W_to_xmit: Failed to allocate XMIT array");
        return;
    }
    pArray->dwCount = ulCount;

    // Copy the linked list of members into the allocated array.
    for (ulCount = 0, pList = pHead; pList != NULL; pList = pList->pNext)
    {
        pArray->pMembers[ulCount++] = pList->Info;
    }

    // Return the array allocated to the RPC stubs
    *ppArray = pArray;
}

///////////////////////////////////////////////////////////////////////////////
//    DLM_XMIT_LIST_W_from_xmit()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
void __RPC_USER DLM_XMIT_LIST_W_from_xmit (DLM_ARRAY_W __RPC_FAR * pArray,
                                           DLM_XMIT_LIST_W __RPC_FAR * pList)
{
    InfoTrace ("DLM_XMIT_LIST_W_from_xmit: Function invoked");
    
    if (pArray->dwCount <= 0)
    {
        pList = NULL;
        return;
    }

    if (pList == NULL)
    {
        InsertNewDLMNodeW (pArray->pMembers[0], pList);
    }
    else
    {
        DLM_XMIT_LIST_W_free_inst (pList);
        pList->Info = pArray->pMembers[0];
        pList->pNext = NULL;
    }

    for (UINT i=1; i<pArray->dwCount; i++)
    {
        InsertNewDLMNodeW (pArray->pMembers[i], pList);
    }
}

///////////////////////////////////////////////////////////////////////////////
//    DLM_XMIT_LIST_W_free_inst()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
void __RPC_USER DLM_XMIT_LIST_W_free_inst (DLM_XMIT_LIST_W __RPC_FAR * pList)
{
    InfoTrace ("DLM_XMIT_LIST_W_free_inst: Function invoked");
    // Don't delete the first node.
    DLM_XMIT_LIST_W * pNextNode, * pNode = pList->pNext;
    ZeroMemory (pList, sizeof(DLM_XMIT_LIST_W));

    while (pNode)
    {
        pNextNode = pNode->pNext;
        midl_user_free (pNode);
        pNode = pNextNode;
    }
}

///////////////////////////////////////////////////////////////////////////////
//    DLM_XMIT_LIST_W_free_xmit()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
void __RPC_USER DLM_XMIT_LIST_W_free_xmit (DLM_ARRAY_W __RPC_FAR * pArray)
{
    InfoTrace ("DLM_XMIT_LIST_W_free_xmit: Function invoked");
    midl_user_free (pArray);
}

///////////////////////////////////////////////////////////////////////////////
//    PrivateMessageBox()
//
//    Parameters
//      ids             String ID of a string in the resource string table
//      hOwnerWnd       Window who will own the Message Box
//      uFlags          Flags (options) for the message box
//      
//    Purpose
//      This function display a message box with a string loaded from the
//      string table of this app. The ID of the string is passed in the ids
//      parameter. The dialog box is modal with respect to the window
//      identified in hOwnerWnd. The options to display the dialog box are
//      passed in uFlags
//      
//    Return Value
//      ID of the button pressed in the message box dialog box
//      
int WINAPI PrivateMessageBox (UINT ids, HWND hOwnerWnd, UINT uFlags)
{
    // Default response
    int nResponse = -1;
    // Get the string from the string table. The size of the buffer is the
    // maximum number of character allowed in the character buffer, without
    // the accounting for the NULL terminator
    TCHAR szBuffer[256];
    // Set the cursor to an arrow, in case it wasn't.
    HCURSOR hPrevCursor = SetCursor (LoadCursor (NULL, MAKEINTRESOURCE(IDC_ARROW)));
    if (LoadString (ghInstance, ids, szBuffer, 255))
    {
        if (0 == uFlags)
        {
            uFlags = MB_OK | MB_ICONSTOP;
        }
        uFlags |= MB_SETFOREGROUND;
        nResponse = MessageBox (hOwnerWnd, szBuffer, g_szAppTitle, uFlags);
    }
    // Before returning, reset the cursor to the previous state
    SetCursor (hPrevCursor);
    return nResponse;
}

///////////////////////////////////////////////////////////////////////////////
//    CenterDialogBox()
//
//    Parameters
//      hDlg    Handle to the dialog (or window) that we want to center.
//      
//    Purpose
//      This function centers a window, vertically and horizontally,
//      with respect to the desktop (or screen)
//      
//    Return Value
//      None.
//      
void WINAPI CenterDialogBox (HWND hDlg)
{
    POINT   pt;
    RECT    r1, r2;
    int    iWidth, iHeight;
    GetWindowRect (GetDesktopWindow(), &r1);
    GetWindowRect (hDlg, &r2);
    iWidth = r2.right - r2.left;
    iHeight = r2.bottom - r2.top;
    pt.x = (r1.right - r1.left) / 2;
    pt.y = (r1.bottom - r1.top) / 2;
    pt.x = pt.x - (iWidth / 2);
    pt.y = pt.y - (iHeight / 2);
    MoveWindow (hDlg, pt.x, pt.y, iWidth, iHeight, FALSE);
}

///////////////////////////////////////////////////////////////////////////////
//    midl_user_allocate()
//
//    Parameters
//      len     Size (in bytes) of the memory block to allocate for the
//              RPC object
//
//    Purpose
//      Allocates memory as needed by the RPC runtime library.
//      The stubs or runtime libraries may need to allocate memory.
//      By convention, they call a user-specified function named
//      midl_user_allocate.
//
//    Return Value
//      Pointer to a block of memory of len byte in size
//
void __RPC_FAR * __RPC_API midl_user_allocate (size_t len)
{
    LPVOID pVoid = HeapAlloc (GetProcessHeap(), HEAP_ZERO_MEMORY, (DWORD)len);
    if (NULL == pVoid)
    {
        TraceMessage ("midl_user_allocate: Failed to allocated RPC memory block");
    }
    return pVoid;
}

///////////////////////////////////////////////////////////////////////////////
//    midl_user_free()
//
//    Parameters
//      ptr     Pointer to memory block to release
//
//    Purpose
//      Free memory as needed by the RPC runtime library.
//      The stubs or runtime libraries may need to free memory.
//      By convention, they call a user-specified function named
//      midl_user_free.
//
//    Return Value
//      None
//
void __RPC_API midl_user_free (void __RPC_FAR * ptr)
{
    HeapFree (GetProcessHeap(), 0, ptr);
}

// End of file for COMMON.CPP
