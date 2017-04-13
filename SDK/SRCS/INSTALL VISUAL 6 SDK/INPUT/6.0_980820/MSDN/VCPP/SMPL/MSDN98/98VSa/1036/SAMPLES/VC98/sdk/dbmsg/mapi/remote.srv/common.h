///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      COMMON.H
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
#include "WDSADM.H"

extern "C"
{
    void WINAPI InsertNewDLMNodeA
                        (DLM_INFO_A                 Info,
                         DLM_XMIT_LIST_A *          pList);
    void WINAPI InsertNewDLMNodeW
                        (DLM_INFO_W                 Info,
                         DLM_XMIT_LIST_W *          pList);

    void __RPC_USER DLM_XMIT_LIST_A_free_inst
                        (DLM_XMIT_LIST_A __RPC_FAR * pList);
    void __RPC_USER DLM_XMIT_LIST_W_free_inst
                        (DLM_XMIT_LIST_W __RPC_FAR * pList);
    
    int WINAPI PrivateMessageBox
                        (UINT                       ids,
                         HWND                       hOwnerWnd,
                         UINT                       uFlags);
    void WINAPI CenterDialogBox
                        (HWND                       hDlg);
};

#ifdef UNICODE
#define InsertNewDLMNode        InsertNewDLMNodeW
#define FreeDLMList(a)          DLM_XMIT_LIST_W_free_inst((DLM_XMIT_LIST_W *)a)
#define DLM_XMIT_LIST           DLM_XMIT_LIST_W
#else
#define InsertNewDLMNode        InsertNewDLMNodeA
#define FreeDLMList(a)          DLM_XMIT_LIST_A_free_inst((DLM_XMIT_LIST_A *)a)
#define DLM_XMIT_LIST           DLM_XMIT_LIST_A
#endif // UNICODE

// End of file for COMMON.H
