///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      ADMNOTIF.CPP
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
#include "ADMIN.H"

// Remark this line to turn verbose tracing OFF
//#define DO_INFO_TRACES
#ifdef DO_INFO_TRACES
#define InfoTrace(a)        TraceInfoMessage(a)
#else
#define InfoTrace(a)        0
#endif // DO_INFO_TRACES

///////////////////////////////////////////////////////////////////////////////
//    BindToServer()
//
//    Parameters
//      [IN]    szServer   Name of the remote server to which we will bind
//                         for RPC calls. If this pointer is NULL, we
//                         unbind from that server.
//
//    Purpose
//      This function makes the necessary calls to the RPC runtime library
//      to bind to the remote server so that we can start RPC function calls.
//
//    Return Value
//      An HRESULT
//
HRESULT WINAPI BindToServer (LPTSTR szServer)
{
    static TCHAR szLastServer[64] = { 0 };
    static TCHAR * szStringBinding = NULL;
    
    // If a server name was given, we compare to the current server that we are
    // already bounded to. If we are connected return the call.
    if (szServer)
    {
        if (0 == lstrcmpi (szLastServer, szServer))
        {
            if (szStringBinding)
            {
                return 0;
            }
        }
        else
        {
            // Save the name of the server in the static buffer
            lstrcpy (szLastServer, szServer);
        }
    }

    RPC_STATUS status = 0;
    if (szStringBinding) // Unbind only if bound
    {
        status = RpcStringFree ((WINDS_RPC_STRING*)&szStringBinding);
        if (!status)
        {
            szStringBinding = NULL;
            status = RpcBindingFree (&hWINDSADM);  // hWINDSADM is defined in WDSADM.H and WDSADM.ACF
        }
        if (status)
        {
            status = MAKE_HRESULT(1, FACILITY_RPC, status);
            TraceResult ("BindToServer: Failed to free the binding", status);
        }
    }
    // If this is NULL, then we don't need to bind to anything.
    if (!szServer)
    {
        szLastServer[0] = 0;
        return S_OK;
    }
    if (!status)
    {
        status = RpcStringBindingCompose (NULL,
                                          (WINDS_RPC_STRING)WINDS_RPC_PROTOCOL,
                                          (WINDS_RPC_STRING)szServer,
                                          (WINDS_RPC_STRING)WINDS_ADMIN_RPC_ENDPOINT,
                                          NULL,
                                          (WINDS_RPC_STRING*)&szStringBinding);
        if (!status)
        {
            status = RpcBindingFromStringBinding ((WINDS_RPC_STRING)szStringBinding, &hWINDSADM); // hWINDSADM is defined in WDSADM.H and WDSADM.ACF
        }
    }
    if (status)
    {
        szLastServer[0] = 0;
        status = MAKE_HRESULT(1, FACILITY_RPC, status);
        TraceResult ("BindToServer: Failed to create remote server binding handle", status);
    }
    return status;
}

///////////////////////////////////////////////////////////////////////////////
//    CNotifLink::CNotifLink()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
CNotifLink::CNotifLink()
{
    m_hMailSlot = NULL;
    m_ulConnectionID = 0;
    ZeroMemory (m_szComputerName, sizeof(m_szComputerName));
    DWORD dwNameSize = MAX_COMPUTERNAME_LENGTH + 1;
    GetComputerName (m_szComputerName, &dwNameSize);
}

///////////////////////////////////////////////////////////////////////////////
//    CNotifLink::~CNotifLink()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
CNotifLink::~CNotifLink()
{
    EndNotifications();
}

///////////////////////////////////////////////////////////////////////////////
//    CNotifLink::EndNotifications()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
STDMETHODIMP CNotifLink::EndNotifications()
{
    if (0 == m_ulConnectionID)
    {
        ASSERT (NULL == m_hMailSlot);
        return S_OK;
    }
    CloseHandle (m_hMailSlot);
    m_hMailSlot = NULL;
    HRESULT hResult;
    RpcTryExcept
    {
        hResult = RemoteAdmTerminateNotif ((WINDS_RPC_STRING)m_szComputerName, m_ulConnectionID);
    }
    RpcExcept(1)
    {
        hResult = RpcExceptionCode();
        if (RPC_S_SERVER_UNAVAILABLE == hResult)
        {
            hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
        }
        else
        {
            hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
        }
    }
    RpcEndExcept
    m_ulConnectionID = 0;
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CNotifLink::StartNotification()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
STDMETHODIMP CNotifLink::StartNotification()
{
    if (0 != m_ulConnectionID)
    {
        return S_OK;
    }
    DWORD dwThreadID, dwFlags = WINDS_ADMINISTRATOR |
                                WINDS_NOTIF_ON_USER |
                                WINDS_NOTIF_ON_AB |
                                WINDS_NOTIF_ON_MS;
#ifdef UNICODE
    dwFlags |= WINDS_UNICODE;
#endif // UNICODE

    HANDLE hThread;
    TCHAR szMailslotName[64];
    HRESULT hResult = S_OK;
    RpcTryExcept
    {
        hResult = RemoteAdmValidateNotif ((WINDS_RPC_STRING)m_szComputerName,
                                          dwFlags,
                                          &m_ulConnectionID);
    }
    RpcExcept(1)
    {
        hResult = RpcExceptionCode();
        if (RPC_S_SERVER_UNAVAILABLE == hResult)
        {
            hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
        }
        else
        {
            hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
        }
    }
    RpcEndExcept
    if (!hResult)
    {
        wsprintf (szMailslotName,
                  CLIENT_MAILSLOT_SINK_NAME_FORMAT,
                  ADMIN_WINDS_NOTIFICATION_MAILSLOT,
                  m_ulConnectionID);
        m_hMailSlot = CreateMailslot (szMailslotName, 0, MAILSLOT_WAIT_FOREVER, NULL);
        if (INVALID_HANDLE_VALUE == m_hMailSlot)
        {
            hResult = HRESULT_FROM_WIN32(GetLastError());
        }
        else
        {
            hThread = CreateThread (NULL,
                                    0,
                                    (LPTHREAD_START_ROUTINE)MailslotListenThreadProc,
                                    (LPVOID)this,
                                    CREATE_SUSPENDED,
                                    &dwThreadID);
            if (hThread)
            {
                SetThreadPriority (hThread, THREAD_PRIORITY_LOWEST);
                ResumeThread (hThread);
                CloseHandle (hThread);
            }
            else
            {
                hResult = HRESULT_FROM_WIN32(GetLastError());
                CloseHandle (m_hMailSlot);
            }
        }
        if (hResult)
        {
            EndNotifications();
        }
    }
    TraceResult ("CNotifLink::StartNotification", hResult);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    MailslotListenThreadProc()
//
//    Parameters
//
//    Purpose
//      This is function runs in a separate low priority thread listening for
//      notification that a WINDS server sends.. When a
//      notification of interest is received, an appropiate action is taken.
//      The notification arrive on a mailslot created by the logon object.
//
//    Return Value
//      S_OK always.
//
DWORD WINAPI MailslotListenThreadProc (CNotifLink * pLink)
{
    TCHAR szBuffer[256] = { 0 };
    LV_FINDINFO lfi = { 0 };
    LV_ITEM lvi = { 0 };
    
    HANDLE hMailslot = pLink->GetListenMailslot();
    DWORD dwRead;
    FILETIME ftLastNotifTime = { 0 };
    WINDS_NOTIF_EVENT LastEvent;
    WINDS_NOTIFICATION Notif;
    HRESULT hReadError;
    while (TRUE)
    {
        if (!ReadFile (hMailslot, &Notif, sizeof(WINDS_NOTIFICATION), &dwRead, NULL)) 
        { 
            hReadError = HRESULT_FROM_WIN32 (GetLastError());
            if (HRESULT_FROM_WIN32(ERROR_INVALID_HANDLE) == hReadError ||
                HRESULT_FROM_WIN32(ERROR_HANDLE_EOF) == hReadError)
            {
                break; // out of the WHILE() loop and terminate the thread
            }
            TraceResult ("MailslotListenThreadProc: ReadFile", HRESULT_FROM_WIN32(GetLastError()));
            continue;
        }
        // Mailslot are received in each network protocol stack installed on the system.
        // Check the time stamp and event of the last notification received. If it
        // is the same, drop it and continue listen for new and different incoming
        // data on the mailslot.
        if (ftLastNotifTime.dwLowDateTime  == Notif.ftEventTime.dwLowDateTime &&
            ftLastNotifTime.dwHighDateTime == Notif.ftEventTime.dwHighDateTime &&
            LastEvent                      == Notif.Event)
        {
            continue;
        }
        // Save the last event information
        ftLastNotifTime = Notif.ftEventTime;
        LastEvent = Notif.Event;

        #ifdef DO_INFO_TRACES
        switch (Notif.Event)
        {
            case AB_USER_ADDED :
                InfoTrace ("AB_USER_ADDED notification received from the WINDS server");
                break;
            case AB_USER_MODIFIED :
                InfoTrace ("AB_USER_MODIFIED notification received from the WINDS server");
                break;
            case AB_USER_DELETED :
                InfoTrace ("AB_USER_DELETED notification received from the WINDS server");
                break;
            case AB_DL_ADDED :
                InfoTrace ("AB_DL_ADDED notification received from the WINDS server");
                break;
            case AB_DL_MODIFIED :
                InfoTrace ("AB_DL_MODIFIED notification received from the WINDS server");
                break;
            case AB_DL_DELETED :
                InfoTrace ("AB_DL_DELETED notification received from the WINDS server");
                break;
            case MS_MESSAGE_ADDED :
            case MS_MESSAGE_MODIFIED :
            case MS_MESSAGE_DELETED :
            case MS_FOLDER_ADDED :
            case MS_FOLDER_MODIFIED :
            case MS_FOLDER_DELETED :
                break;
            case SERVER_IS_SHUTTING_DOWN :
                InfoTrace ("SERVER_IS_SHUTTING_DOWN notification received from the WINDS server");
                break;
            case RESET_LINKS_WITH_SERVER :
                InfoTrace ("RESET_LINKS_WITH_SERVER notification received from the WINDS server");
                break;
            case SERVER_HAS_RESTARTED :
                InfoTrace ("SERVER_HAS_RESTARTED notification received from the WINDS server");
                break;
            case AB_GET_LOCAL_ABDATA_NOW :
                InfoTrace ("AB_GET_LOCAL_ABDATA_NOW notification received from the WINDS server");
                break;
            default :
                InfoTrace ("UNKNOWN notification received from the WINDS server");
                break;
        }
        #endif // DO_INFO_TRACES

        switch (Notif.Event)
        {
            case AB_USER_ADDED :
            case AB_DL_ADDED :
                {
                    if (AB_USER_ADDED == Notif.Event)
                    {
                        if (ITEM_SERVER_USER_MAILBOXES != g_LVItemsType)
                        {
                            break;
                        }
                    }
                    else
                    {
                        if (ITEM_SERVER_DIST_LISTS != g_LVItemsType)
                        {
                            break;
                        }
                    }

                    int iNewItem = ListView_GetItemCount (ghListView);
                    lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
                    lvi.iItem = iNewItem;
                    lvi.iSubItem = 0;
                    if (AB_USER_ADDED == Notif.Event)
                    {
                        
                        lvi.pszText = Notif.Info.MB.szMailboxName;
                        lvi.lParam = Notif.Info.MB.dwObjID;
                        lvi.iImage = IMG_USER_MAILBOX;
                    }
                    else
                    {
                        lvi.pszText = Notif.Info.DL.szDLAlias;
                        lvi.lParam = Notif.Info.DL.dwObjID;
                        lvi.iImage = IMG_DIST_LIST;
                    }
                    lvi.iItem = ListView_InsertItem (ghListView, &lvi);
                    if (AB_USER_ADDED == Notif.Event)
                    {
                        ListView_SetItemText (ghListView, lvi.iItem, 1, Notif.Info.MB.szFullName);
                        ListView_SetItemText (ghListView, lvi.iItem, 2, Notif.Info.MB.szJobTitle);
                        ListView_SetItemText (ghListView, lvi.iItem, 3, Notif.Info.MB.szOffice);
                        ListView_SetItemText (ghListView, lvi.iItem, 4, Notif.Info.MB.szPhone);
                        ListView_SetItemText (ghListView, lvi.iItem, 5, Notif.Info.MB.szAltPhone);
                        ListView_SetItemText (ghListView, lvi.iItem, 6, Notif.Info.MB.szFax);
                    }
                    else
                    {
                        ListView_SetItemText (ghListView, lvi.iItem, 1, Notif.Info.DL.szDLFullName);
                    }
                }
                break;

            case AB_USER_DELETED :
            case AB_USER_MODIFIED :
            case AB_DL_DELETED :
            case AB_DL_MODIFIED :
                if (AB_USER_DELETED == Notif.Event || AB_USER_MODIFIED == Notif.Event)
                {
                    if (ITEM_SERVER_USER_MAILBOXES != g_LVItemsType)
                    {
                        break;
                    }
                }
                else
                {
                    if (ITEM_SERVER_DIST_LISTS != g_LVItemsType)
                    {
                        break;
                    }
                }
                lfi.flags = LVFI_STRING;
                if (AB_USER_MODIFIED == Notif.Event || AB_USER_DELETED == Notif.Event)
                {
                    lfi.psz = Notif.Info.MB.szMailboxName;
                }
                else
                {
                    lfi.psz = Notif.Info.DL.szDLAlias;
                }
                lvi.iItem = ListView_FindItem (ghListView, -1, &lfi);
                if (-1 == lvi.iItem)
                {
                    break;
                }
                if (AB_DL_DELETED == Notif.Event || AB_USER_DELETED == Notif.Event)
                {
                    ListView_DeleteItem (ghListView, lvi.iItem);
                }
                else
                {
                    lvi.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;
                    lvi.iSubItem = 0;
                    if (AB_USER_MODIFIED == Notif.Event)
                    {
                        lvi.pszText = Notif.Info.MB.szMailboxName;
                        lvi.lParam = Notif.Info.MB.dwObjID;
                        lvi.iImage = IMG_USER_MAILBOX;
                        ListView_SetItem (ghListView, &lvi);
                        ListView_SetItemText (ghListView, lvi.iItem, 1, Notif.Info.MB.szFullName);
                        ListView_SetItemText (ghListView, lvi.iItem, 2, Notif.Info.MB.szJobTitle);
                        ListView_SetItemText (ghListView, lvi.iItem, 3, Notif.Info.MB.szOffice);
                        ListView_SetItemText (ghListView, lvi.iItem, 4, Notif.Info.MB.szPhone);
                        ListView_SetItemText (ghListView, lvi.iItem, 5, Notif.Info.MB.szAltPhone);
                        ListView_SetItemText (ghListView, lvi.iItem, 6, Notif.Info.MB.szFax);
                    }
                    else
                    {
                        lvi.pszText = Notif.Info.DL.szDLAlias;
                        lvi.lParam = Notif.Info.DL.dwObjID;
                        lvi.iImage = IMG_DIST_LIST;
                        ListView_SetItem (ghListView, &lvi);
                        ListView_SetItemText (ghListView, lvi.iItem, 1, Notif.Info.DL.szDLFullName);
                    }
                }
                break;
            case RESET_LINKS_WITH_SERVER :
                PostMessage (ghWnd, WM_WINDS_RESET_NOTIF_LINK, 0, 0);
                break;
        }
    } 
    return S_OK;
}

// End of file for ADMNOTIF.CPP
