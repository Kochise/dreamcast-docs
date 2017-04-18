///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      RASHOST.CPP
//
//  Description
//      This file contains the initialization functions for the DLL library
//      and for the Security Host protocol. The NT RAS manager will call into
//      our DLL when a dialing user needs to be validated.
//
//  Author
//      Irving De la Cruz
//
//  Revision: 1.1
//
// Written for Microsoft Developer Support
// Copyright (c) 1995-1997 Microsoft Corporation. All rights reserved.
//
#include "RASHOST.H"

HINSTANCE                       ghLibHandle = NULL;
RASSECURITYDIALOGSENDPROC       gpfnSendProc = NULL;
RASSECURITYDIALOGRECEIVEPROC    gpfnReceiveProc = NULL;

///////////////////////////////////////////////////////////////////////////////
//    LibMain()
//
//    Parameters
//      { Refer to the Win32 SDK documentation for DLL entry points }
//
//    Purpose
//      Entry point of this DLL
//
//    Return Value
//      TRUE if the DLL should proceed with the dwReason case, FALSE otherwise.
//
BOOL APIENTRY LibMain (HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
{
    if (DLL_PROCESS_DETACH == dwReason && ghLibHandle)
    {
        FreeLibrary (ghLibHandle);
    }
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//    RasSecurityDialogBegin()
//
//    Parameters
//      hPort       Handle to the COM port where the user is logging in
//                  (A RAS handle, not a standard handle)
//      pSendBuf    Pointer to a buffer where we can copy stuff to be sent
//                  over the wire
//      SendBufSize Size of the outgoing buffer
//      pRecvBuf    Pointer a buffer where stuff is received from the
//                  remote client machine
//      RecvBufSize Size of the incoming buffer
//      RasSecurityDialogComplete   Pointer to a callback function we must
//                  call after we have completed our validation, indicating
//                  the RAS manager weather or not we granted access to the
//                  caller.
//
//    Purpose
//      This is the entry point for our security DLL. When the RAS manager
//      receives a call from a user, after it does its user validation, it
//      will call into us at this entry point to allow us to do extra
//      validation.
//      NOTE: It is very important that this function does not BLOCK. If
//            it does, the RAS manager will be block and no other calls
//            will be accepted. That is why we copy the incoming
//            parameters into a private structure and then spawn a thread
//            to do the actual validation work.
//            The passed parameters will be valid until we call the
//            ending function.
//
//    Return Value
//      ERROR_SUCCESS is we were able to start the validation. Otherwise
//      return and error from WINERROR.H or RASERROR.H
//
DWORD WINAPI RasSecurityDialogBegin (HPORT hPort,
                                     PBYTE pSendBuf,
                                     DWORD SendBufSize,
                                     PBYTE pRecvBuf,
                                     DWORD RecvBufSize,
                                     VOID  (WINAPI *RasSecurityDialogComplete)(SECURITY_MESSAGE*))
{
    // Initialize the global pointer to the entry points in the RAS manager
    // DLL. I use these entry points to send and receive data to the remote
    // client machine. These functions will send and receive RAW buffers of
    // data to the other machine just before PPP-framing starts.
    // These functions have not been exported in any publish import library
    // so we must do a dynamic binding to them.
    if (NULL == ghLibHandle)
    {
        ghLibHandle = LoadLibrary ("RASMAN.DLL");
        if (NULL == ghLibHandle)
        {
            return ERROR_DLL_NOT_FOUND;
        }
    }
    // Obtain the send and received entry points from the RAS manager DLL.
    if (NULL == gpfnSendProc)
    {
        gpfnSendProc = (RASSECURITYDIALOGSENDPROC)GetProcAddress (ghLibHandle, TEXT("RasSecurityDialogSend"));
        if (NULL == gpfnSendProc)
        {
            return ERROR_PROC_NOT_FOUND;
        }
    }
    if (NULL == gpfnReceiveProc)
    {
        gpfnReceiveProc = (RASSECURITYDIALOGRECEIVEPROC)GetProcAddress (ghLibHandle, TEXT("RasSecurityDialogReceive"));
        if (NULL == gpfnReceiveProc)
        {
            return ERROR_PROC_NOT_FOUND;
        }
    }
    
    // Save the parameters passed and give them to the working thread
    // that will handle the authentication of the caller. The thread
    // should release this memory.
    // The parameters passed to use should be valid until we call the
    // dialog end function or until we get call in the termination
    // dialog entry point by the RAS system supervisor (the RAS manager)
    PWORK_THREAD_DATA pCallData = (PWORK_THREAD_DATA)HeapAlloc (GetProcessHeap(),
                                                                HEAP_ZERO_MEMORY,
                                                                sizeof(WORK_THREAD_DATA));
    if (NULL == pCallData)
    {
        return ERROR_OUTOFMEMORY;
    }
    // Initialize the members.
    pCallData->hPort = hPort;
    pCallData->pSendBuf = pSendBuf;
    pCallData->SendBufSize = SendBufSize;
    pCallData->pRecvBuf = pRecvBuf;
    pCallData->RecvBufSize = RecvBufSize;
    pCallData->pfnSecurityDialogEnd = RasSecurityDialogComplete;

    // For each call, spawn a working thread that will make the neccesary
    // authentication of the dial-up caller. We should never block the call
    // to RasSecurityDialogBegin(). If we do so, RAS will also block and no
    // more call would be accepted.
    DWORD dwThreadID;
    HANDLE hThread = CreateThread (NULL,
                                   0,
                                   (LPTHREAD_START_ROUTINE)CallWorkerThread,
                                   (LPVOID)pCallData,
                                   0,
                                   &dwThreadID);
    if (NULL == hThread)
    {
        // Call GetLastError() before calling HeapFree().
        DWORD dwError = GetLastError();
        HeapFree (GetProcessHeap(), 0, pCallData);
        return dwError;
    }
    return ERROR_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
//    RasSecurityDialogEnd()
//
//    Parameters
//      hPort   Handle to the COM port (A RAS handle, not a standard handle)
//
//    Purpose
//      Stub function. Need to export this by the security DLL even if
//      not needed. We need to return non-zero to indicate RAS we are no
//      longer responsible for the port connection. It will take care
//      of the rest.
//
//    Return Value
//      ERROR_PORT_DISCONNECTED always
//
DWORD WINAPI RasSecurityDialogEnd (HPORT hPort)
{
    return ERROR_PORT_DISCONNECTED;
}

///////////////////////////////////////////////////////////////////////////////
//    CallWorkerThread()
//
//    Parameters
//      pCallData   Pointer to the data structure with the data for the
//                  instance we are handling.
//
//    Purpose
//      This is the function for the thread that interacts with a dialing RAS
//      user. Here we query the user for its identity and based on it we
//      compute a challenge to for it. Once the response from the client
//      is received, we validate it and decide wether or not we allow access.
//
//    Return Value
//      None
//
void WINAPI CallWorkerThread (PWORK_THREAD_DATA pCallData)
{
    // Initialize the appropiate structures
    SECURITY_MESSAGE smResult = { 0 };
    smResult.hPort = pCallData->hPort;
    lstrcpy (smResult.UserName, TEXT("(RASHOST - Unknown)"));

    DWORD dwBytes = pCallData->RecvBufSize;
    ZeroMemory (pCallData->pRecvBuf, dwBytes);
    dwBytes = sizeof(RASHOST_DATA);

    // Initialize the structure that we'll send to the caller
    RASHOST_DATA HostData = { 0 };
    HostData.dwSize = sizeof(RASHOST_DATA);
    
    // Create an event to wait for client responses
    HANDLE hEvent = CreateEvent (NULL, FALSE, FALSE, NULL);

    // We must copy the data from the structure to the buffer RAS
    // manager uses to transmit the information. This buffer
    // cannot be larger than 1500 bytes
    CopyMemory (pCallData->pSendBuf, &HostData, sizeof(RASHOST_DATA));
    DWORD dwError = 0;

    gpfnSendProc (pCallData->hPort,
                  pCallData->pSendBuf,
                  (WORD)sizeof(RASHOST_DATA));

    // Wait for an answer from the client responder
    gpfnReceiveProc (pCallData->hPort,
                     pCallData->pRecvBuf,
                     (WORD *)&dwBytes,
                     0,
                     hEvent);
    DWORD dwWait;
    dwWait = WaitForSingleObject (hEvent, CLIENT_RESPONSE_TIMEOUT);
    if (WAIT_OBJECT_0 != dwWait)
    {
        dwError = ERROR_SMM_TIMEOUT;
        goto ErrorExit;
    }

    // Copy the client data from the incoming buffer to the data structure
    CopyMemory (&HostData, pCallData->pRecvBuf, sizeof(RASHOST_DATA));
    
    // Save this information for RAS authentication with the NT RAS manager.
    // The user name must be the same as the one in the NT account database
    // on the domain where the user is granted access.
    lstrcpy (smResult.UserName, HostData.szUserName);
    lstrcpy (smResult.Domain, HostData.szUserDomain);

    //lstrcpy (smResult.UserName, "IrvingD");

    BOOL fAccessGranted; // Weather or not access was granted
    // With the received client response, validate the access for the client
    dwError = ValidateCallingUser (&HostData, &fAccessGranted);
    if (dwError)
    {
        goto ErrorExit;
    }
    
    if (fAccessGranted)
    {
        // Access has been granted
        smResult.dwMsgId = SECURITYMSG_SUCCESS;
    }
    else
    {
        // The caller did not respond correctly
        smResult.dwMsgId = SECURITYMSG_FAILURE;
    }

ErrorExit:
    if (dwError)
    {
        // There was an error, deny access.
        if (ERROR_SMM_TIMEOUT == dwError)
        {
            smResult.dwMsgId = SECURITYMSG_FAILURE;
        }
        else
        {
            smResult.dwMsgId = SECURITYMSG_ERROR;
            smResult.dwError = dwError;
        }
    }
    // Release the synchronization objects
    CloseHandle (hEvent);
    // Tell the RAS manager we are finished by calling the END dialog funcition.
    pCallData->pfnSecurityDialogEnd (&smResult);
    // Free the memory of this call instance before exiting the thread
    HeapFree (GetProcessHeap(), 0, pCallData);
}

///////////////////////////////////////////////////////////////////////////////
//    ValidateCallingUser()
//
//    Parameters
//      pData               Pointer to the host data structure
//      pfAccessGranted     We return TRUE here is access is granted.
//                          FALSE otherwise.
//
//    Purpose
//      Here we validate the answer to the challenge sent to the client.
//
//    Return Value
//      ERROR_SUCCESS if successful. Otherwiser an error code from WINERROR.H
//      or RASERROR.H
//
DWORD WINAPI ValidateCallingUser (PRASHOST_DATA       pData,
                                  BOOL *              pfAccessGranted)
{
    DWORD dwResult = ERROR_SUCCESS;
    *pfAccessGranted = FALSE;
    
    // Do stuff here

    return dwResult;
}

// End of file for RASHOST.CPP
