
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1992-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

//+---------------------------------------------------------------------------
//
//  File:       pop3.c
//
//  Contents:   This file contains the code to handle each pop command
//
//----------------------------------------------------------------------------

#include "pop3srvp.h"
#pragma hdrstop

char *  PopCommands[] = {   POP3_HELO,
                            POP3_USER,
                            POP3_PASS,
                            POP3_QUIT,
                            POP3_STAT,
                            POP3_LIST,
                            POP3_RETR,
                            POP3_DELE,
                            POP3_LAST,
                            POP3_RSET };

Pop3DispatchFn  Pop3DispatchTable[] = {
                            HeloDispatch,
                            UserDispatch,
                            PassDispatch,
                            QuitDispatch,
                            StatDispatch,
                            ListDispatch,
                            RetrDispatch,
                            DeleDispatch,
                            LastDispatch,
                            RsetDispatch };

#define POP3_STAT_RESPONSE  POP3_GOOD_RESPONSE " %d %d\r\n"
#define POP3_GOOD_RESPLINE  POP3_GOOD_RESPONSE "\r\n"
#define POP3_LIST_RESPLINE  "%d %d\r\n"
#define POP3_TERMINATOR     ".\r\n"
#define POP3_RETR_RESPONSE  POP3_GOOD_RESPONSE " %d octets\r\n"
#define POP3_LAST_RESPONSE  POP3_GOOD_RESPONSE " %d\r\n"

#define BANNER_STRING   POP3_GOOD_RESPONSE " POP3 Example Server Ready\r\n"
#define ERROR_POP3_INVALID_STATE     POP3_BAD_RESPONSE " Command not valid in this state\r\n"
#define ERROR_INVALID_USERNAME  POP3_BAD_RESPONSE " Username not valid\r\n"
#define ERROR_AUTH_FAILED       POP3_BAD_RESPONSE " Unable to log on\r\n"
#define ERROR_LOCK_FAILED_S     POP3_BAD_RESPONSE " Unable to lock directory\r\n"
#define ERROR_UNKNOWN_MESSAGE   POP3_BAD_RESPONSE " Unknown message\r\n"
#define ERROR_READ_FAILED_S     POP3_BAD_RESPONSE " Unable to read directory\r\n"
#define ERROR_SERVER_FAILURE    POP3_BAD_RESPONSE " General failure on server\r\n"


//+---------------------------------------------------------------------------
//
//  Function:   Pop3CrackCommand
//
//  Synopsis:   Takes an input buffer as received from a client, and cracks
//              it to determine the command to execute
//
//  Arguments:  [Request]    -- Input buffer
//              [RequestLen] -- Input buffer length
//
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
int
Pop3CrackCommand(
    PUCHAR      Request,
    DWORD       RequestLen)
{
    int i;

    if (RequestLen < 4)
    {
        return(-1);
    }

    for (i = 0; i < MAX_POP3_COMMAND ; i++ )
    {
        if (_strnicmp((PCHAR) Request, PopCommands[i], 4) == 0 )
        {
            return(i);
        }
    }

    return(-1);
}

//+---------------------------------------------------------------------------
//
//  Function:   CreatePop3Context
//
//  Synopsis:   Creates a client context to keep associated with the socket
//
//  Arguments:  (none)
//
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
PVOID
CreatePop3Context(void)
{
    PPopContext pContext;

    pContext = LocalAlloc(LMEM_FIXED | LMEM_ZEROINIT, sizeof(PopContext));
    if (pContext)
    {
        pContext->State = PopAuthorization;
        ReportServiceEvent(
            EVENTLOG_INFORMATION_TYPE,
            POP3EVENT_USER_CONNECT,
            0, NULL, 0);
    }
    return(pContext);
}

//+---------------------------------------------------------------------------
//
//  Function:   DeletePop3Context
//
//  Synopsis:   Gets rid of the context when the socket closes
//
//  Arguments:  [pvContext] --
//
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
VOID
DeletePop3Context(PVOID pvContext)
{
    PPopContext pContext;

    pContext = (PPopContext) pvContext;

    if (pContext->pDirectory)
    {
        FreeMailDirectory(pContext->pDirectory);
        UnlockMailDirectory(pContext->hDirectoryLock);
        CloseHandle(pContext->hUserToken);
    }

    LocalFree(pContext);

}


//+---------------------------------------------------------------------------
//
//  Function:   AllocAndCopyString
//
//  Synopsis:   Copies a string into local alloc memory, so that socket code
//              can send it off, then free it.
//
//  Arguments:  [pszString] -- string to copy
//              [pcbString] -- returned length of string
//
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
PUCHAR
AllocAndCopyString(
    PCHAR   pszString,
    PDWORD  pcbString)
{
    PCHAR   pszNewString;

    *pcbString = strlen(pszString);
    pszNewString = LocalAlloc(LMEM_FIXED, *pcbString + 1);
    if (pszNewString)
    {
        strcpy(pszNewString, pszString);
    }
    return((PUCHAR) pszNewString);
}

//+---------------------------------------------------------------------------
//
//  Function:   HeloDispatch
//
//  Synopsis:   Handles the HELO command, which, perversely, never gets sent
//              by most clients.
//
//  Arguments:  [pContext]        --
//              [InputBuffer]     --
//              [InputBufferLen]  --
//              [SendHandle]      --
//              [OutputBuffer]    --
//              [OutputBufferLen] --
//
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
Pop3Disposition
HeloDispatch(
    PPopContext pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen)
{
    DebugLog((DEB_TRACE_PROT, "Received HELO\n"));

    //
    // Verify context, and that the context says we can receive this command
    //

    if (!pContext)
    {
        return(Pop3_Discard);
    }

    if ((pContext->State == PopTransact) ||
        (pContext->State == PopUpdate) )
    {
        *OutputBuffer = ERROR_POP3_INVALID_STATE;
        *OutputBufferLen = sizeof(ERROR_POP3_INVALID_STATE);
        return(Pop3_SendError);
    }

    //
    // Put us into Authorization state
    //
    pContext->State = PopAuthorization;

    //
    // No file, but copy the banner string and return it.
    //
    *SendHandle = NULL;
    *OutputBuffer = AllocAndCopyString(BANNER_STRING, OutputBufferLen);

    return(Pop3_SendBuffer);

}

//+---------------------------------------------------------------------------
//
//  Function:   UserDispatch
//
//  Synopsis:   Handles the USER command
//
//  Arguments:  [pContext]        --
//              [InputBuffer]     --
//              [InputBufferLen]  --
//              [SendHandle]      --
//              [OutputBuffer]    --
//              [OutputBufferLen] --
//
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
Pop3Disposition
UserDispatch(
    PPopContext pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen)
{
    char * Src;
    char * Dst;

    DebugLog((DEB_TRACE_PROT, "Received USER\n"));


    //
    // Verify context, and that the context says we can receive this command
    //
    if (!pContext)
    {
        return(Pop3_Discard);
    }

    if (pContext->State != PopAuthorization)
    {
        *OutputBuffer = ERROR_POP3_INVALID_STATE;
        *OutputBufferLen = sizeof(ERROR_POP3_INVALID_STATE);
        return(Pop3_SendError);
    }

    if (InputBufferLen - POP3_COMMAND_LENGTH > USERNAME_LENGTH)
    {
        *OutputBuffer = ERROR_INVALID_USERNAME;
        *OutputBufferLen = sizeof(ERROR_INVALID_USERNAME);
        return(Pop3_SendError);
    }

    //
    // Copy in the user name without trailing \r or \n.
    //

    Src = InputBuffer + POP3_COMMAND_LENGTH;
    Dst = pContext->UserName;
    while (*Src && (*Src != '\r') && (*Src != '\n'))
    {
        *Dst++ = *Src++;
    }
    *Dst = '\0';

    //
    // Set the state so that we are expecting the password
    //
    pContext->State = PopAuthorization2;

    *SendHandle = NULL;
    *OutputBuffer = AllocAndCopyString(POP3_GOOD_RESPLINE, OutputBufferLen);

    return(Pop3_SendBuffer);

}


//+---------------------------------------------------------------------------
//
//  Function:   PassDispatch
//
//  Synopsis:   Handles the PASS command
//
//  Arguments:  [pContext]        --
//              [InputBuffer]     --
//              [InputBufferLen]  --
//              [SendHandle]      --
//              [OutputBuffer]    --
//              [OutputBufferLen] --
//
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
Pop3Disposition
PassDispatch(
    PPopContext pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen)
{
    CHAR    pass[MAX_PATH];
    char *  Dst;
    char *  Src;


    DebugLog((DEB_TRACE_PROT, "Received PASS\n"));


    //
    // Verify context, and that the context says we can receive this command
    //

    if (!pContext)
    {
        return(Pop3_Discard);
    }

    if (pContext->State != PopAuthorization2)
    {
        *OutputBuffer = ERROR_POP3_INVALID_STATE;
        *OutputBufferLen = sizeof(ERROR_POP3_INVALID_STATE);
        return(Pop3_SendError);
    }

    //
    // Copy in the password without trailing \r or \n.
    //

    Src = InputBuffer + POP3_COMMAND_LENGTH;
    Dst = pass;
    while (*Src && (*Src != '\r') && (*Src != '\n'))
    {
        *Dst++ = *Src++;
    }
    *Dst = '\0';


#ifdef SECURE_BUILD

    //
    // Attempt to log the user on, meaning verify the name and password
    // provided, and get a token back.  The "." we're passing in means
    // use the domain if this machine is part of a domain, or use the local
    // accounts domain.
    //
    if (!LogonUserA(    pContext->UserName,
                        ".",
                        pass,
                        LOGON32_LOGON_INTERACTIVE,
                        LOGON32_PROVIDER_DEFAULT,
                        &pContext->hUserToken) )
    {
        pContext->State = PopAuthorization;
        ReportServiceEvent(
            EVENTLOG_WARNING_TYPE,
            POP3EVENT_LOGON_FAILURE,
            0, NULL,
            0);

        *OutputBuffer = ERROR_AUTH_FAILED;
        *OutputBufferLen = sizeof(ERROR_AUTH_FAILED);
        return(Pop3_SendError);
    }

#endif

    //
    // Now, open and read the mail drop directory
    //

    pContext->hDirectoryLock = LockMailDirectory(pContext->hUserToken,
                                                 pContext->UserName);

    if (!pContext->hDirectoryLock)
    {
        //
        // Could not lock directory.  Basically, we shut down this connection,
        // and let it go.
        //

        DebugLog((DEB_ERROR, "Unable to lock directory, %d\n", GetLastError()));

        pContext->State = PopAuthorization;

        //
        // Close the token.  This logs the user off.
        //
        CloseHandle(pContext->hUserToken);
        pContext->hUserToken = NULL;

        *OutputBuffer = ERROR_LOCK_FAILED_S;
        *OutputBufferLen = sizeof(ERROR_LOCK_FAILED_S);
        return(Pop3_SendError);
    }

    pContext->pDirectory = ReadMailDirectory(pContext->hUserToken,
                                             pContext->UserName);

    if (!pContext->pDirectory)
    {
        //
        // Couldn't read the directory.  So, we panic and
        // throw it all away.
        //

        DebugLog((DEB_ERROR, "Unable to read directory!\n"));

        pContext->State = PopAuthorization;
        UnlockMailDirectory(pContext->hDirectoryLock);
        pContext->hDirectoryLock = NULL;
        CloseHandle(pContext->hUserToken);

        *OutputBuffer = ERROR_READ_FAILED_S;
        *OutputBufferLen = sizeof(ERROR_LOCK_FAILED_S);
        return(Pop3_SendError);
    }

    pContext->State = PopTransact;
    *OutputBuffer = AllocAndCopyString(POP3_GOOD_RESPLINE, OutputBufferLen);
    return(Pop3_SendBuffer);

}

//+---------------------------------------------------------------------------
//
//  Function:   QuitDispatch
//
//  Synopsis:   Handles the QUIT command
//
//  Arguments:  [pContext]        --
//              [InputBuffer]     --
//              [InputBufferLen]  --
//              [SendHandle]      --
//              [OutputBuffer]    --
//              [OutputBufferLen] --
//
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
Pop3Disposition
QuitDispatch(
    PPopContext pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen)
{

    DebugLog((DEB_TRACE_PROT, "Received QUIT\n"));

    //
    // Verify context, and that the context says we can receive this command
    //

    if (!pContext)
    {
        return(Pop3_Discard);
    }

    if (pContext->State == PopTransact)
    {
        pContext->State = PopUpdate;

        CommitMailDirectory(pContext->pDirectory, pContext->hUserToken);
        FreeMailDirectory(pContext->pDirectory);
        UnlockMailDirectory(pContext->hDirectoryLock);
        CloseHandle(pContext->hUserToken);
    }

    pContext->State = PopShutdown;

    *OutputBuffer = AllocAndCopyString(POP3_GOOD_RESPLINE, OutputBufferLen);

    return(Pop3_SendBuffer);

}


//+---------------------------------------------------------------------------
//
//  Function:   StatDispatch
//
//  Synopsis:   Handles the STAT command
//
//  Arguments:  [pContext]        --
//              [InputBuffer]     --
//              [InputBufferLen]  --
//              [SendHandle]      --
//              [OutputBuffer]    --
//              [OutputBufferLen] --
//
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
Pop3Disposition
StatDispatch(
    PPopContext pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen)
{

    char    StatResp[80];

    DebugLog((DEB_TRACE_PROT, "Received STAT\n"));

    //
    // Verify context, and that the context says we can receive this command
    //

    if (!pContext)
    {
        return(Pop3_Discard);
    }

    if (pContext->State != PopTransact)
    {
        *OutputBuffer = ERROR_POP3_INVALID_STATE;
        *OutputBufferLen = sizeof(ERROR_POP3_INVALID_STATE);
        return(Pop3_SendError);
    }

    //
    // Print the response into the buffer, then copy it and return it.
    //

    sprintf(StatResp, POP3_STAT_RESPONSE, pContext->pDirectory->cAvailMessages,
                        pContext->pDirectory->AvailSize);

    *OutputBuffer = AllocAndCopyString(StatResp, OutputBufferLen);
    *SendHandle = NULL;

    DebugLog((DEB_TRACE_PROT, "STAT: Sending %s\n", StatResp));

    return(Pop3_SendBuffer);

}


//+---------------------------------------------------------------------------
//
//  Function:   ListDispatch
//
//  Synopsis:   Handles the LIST command
//
//  Arguments:  [pContext]        --
//              [InputBuffer]     --
//              [InputBufferLen]  --
//              [SendHandle]      --
//              [OutputBuffer]    --
//              [OutputBufferLen] --
//
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
Pop3Disposition
ListDispatch(
    PPopContext pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen)
{
    PCHAR       pszBuffer;
    PCHAR       pszWalk;
    DWORD       TotalAlloc;
    DWORD       UsedAlloc;
    DWORD       CharCount;
    DWORD       SingleMessage;
    DWORD       i;
    char        SingleLine[80];


    DebugLog((DEB_TRACE_PROT, "Received LIST\n"));

    //
    // Verify context, and that the context says we can receive this command
    //

    if (!pContext)
    {
        return(Pop3_Discard);
    }

    if (pContext->State != PopTransact)
    {
        *OutputBuffer = ERROR_POP3_INVALID_STATE;
        *OutputBufferLen = sizeof(ERROR_POP3_INVALID_STATE);
        return(Pop3_SendError);
    }

    //
    // If there is a parameter, process it so we can find out what specific
    // message they want
    //

    if (InputBufferLen > POP3_COMMAND_LENGTH)
    {
        SingleMessage = (DWORD) -1;
        sscanf(&InputBuffer[POP3_COMMAND_LENGTH], " %d", &SingleMessage);

        //
        // Pop is 1-based, we're 0-based
        //
        SingleMessage--;

        if ((SingleMessage > pContext->pDirectory->cMessages) ||
            (pContext->pDirectory->Messages[SingleMessage].Flags & POP3_MESSAGE_DELETE))
        {
            *OutputBuffer = ERROR_UNKNOWN_MESSAGE;
            *OutputBufferLen = sizeof(ERROR_UNKNOWN_MESSAGE);
            return(Pop3_SendError);
        }

        sprintf(SingleLine, POP3_STAT_RESPONSE, SingleMessage + 1,
                    pContext->pDirectory->Messages[SingleMessage].Size);

        *OutputBuffer = AllocAndCopyString(SingleLine, OutputBufferLen);
        DebugLog((DEB_TRACE_PROT, "LIST: Sending %s", SingleLine));
        return(Pop3_SendBuffer);
    }

    //
    // If they want the whole list, send the whole list
    //
    TotalAlloc = pContext->pDirectory->cAvailMessages * 16 + 24;
    pszBuffer = LocalAlloc(LMEM_FIXED | LMEM_ZEROINIT, TotalAlloc);
    if (!pszBuffer)
    {
        *OutputBuffer = ERROR_SERVER_FAILURE;
        *OutputBufferLen = sizeof(ERROR_SERVER_FAILURE);
        return(Pop3_SendError);
        
    }
    pszWalk = pszBuffer;
    UsedAlloc = 0;

    //
    // Copy the header
    //
    CharCount = sprintf(pszWalk, POP3_STAT_RESPONSE,
                        pContext->pDirectory->cAvailMessages,
                        pContext->pDirectory->AvailSize);

    pszWalk += CharCount;
    UsedAlloc += CharCount;
    for (i = 0; i < pContext->pDirectory->cMessages ; i++ )
    {
        //
        // For every message not marked deleted, copy it in
        //
        if ((pContext->pDirectory->Messages[i].Flags & POP3_MESSAGE_DELETE) == 0)
        {
            CharCount = sprintf(pszWalk, POP3_LIST_RESPLINE,
                                i+1, pContext->pDirectory->Messages[i].Size);
            pszWalk += CharCount;
            UsedAlloc += CharCount;
        }
    }

    strcpy(pszWalk, POP3_TERMINATOR);
    UsedAlloc += 3;

    *OutputBuffer = pszBuffer;
    *OutputBufferLen = UsedAlloc;

    DebugLog((DEB_TRACE_PROT, "LIST: Sending %s\n", pszBuffer));

    return(Pop3_SendBuffer);

}

//+---------------------------------------------------------------------------
//
//  Function:   RetrDispatch
//
//  Synopsis:   Handles the RETR command
//
//  Arguments:  [pContext]        --
//              [InputBuffer]     --
//              [InputBufferLen]  --
//              [SendHandle]      --
//              [OutputBuffer]    --
//              [OutputBufferLen] --
//
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
Pop3Disposition
RetrDispatch(
    PPopContext pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen)
{
    DWORD   MessageId;
    char    Line[40];


    DebugLog((DEB_TRACE_PROT, "Received RETR\n"));

    //
    // Verify context, and that the context says we can receive this command
    //

    if (!pContext)
    {
        return(Pop3_Discard);
    }

    if (pContext->State != PopTransact)
    {
        *OutputBuffer = ERROR_POP3_INVALID_STATE;
        *OutputBufferLen = sizeof(ERROR_POP3_INVALID_STATE);
        return(Pop3_SendError);
    }

    MessageId = (DWORD) -1;

    if (InputBufferLen > POP3_COMMAND_LENGTH)
    {
        sscanf(&InputBuffer[POP3_COMMAND_LENGTH], "%d", &MessageId);
    }

    //
    // Pop is 1-based, we're 0-based
    //
    MessageId--;

    if ((MessageId > pContext->pDirectory->cMessages) ||
        (pContext->pDirectory->Messages[MessageId].Flags & POP3_MESSAGE_DELETE))
    {
        *OutputBuffer = ERROR_UNKNOWN_MESSAGE;
        *OutputBufferLen = sizeof(ERROR_UNKNOWN_MESSAGE);
        return(Pop3_SendError);
    }


    //
    // Open the mail message.  We pass in the user's token, so that
    // we can impersonate when we do the open.
    //

    *SendHandle = OpenMailMessage(  MessageId,
                                    pContext->pDirectory,
                                    pContext->hUserToken);

    if (*SendHandle)
    {
        sprintf(Line, POP3_RETR_RESPONSE,
                pContext->pDirectory->Messages[MessageId].Size);
        *OutputBuffer = AllocAndCopyString(Line, OutputBufferLen);
        if (pContext->pDirectory->NextMessage < MessageId)
        {
            pContext->pDirectory->NextMessage = MessageId;
        }

        return(Pop3_SendBufferThenFile);

    }

    *OutputBuffer = ERROR_SERVER_FAILURE;
    *OutputBufferLen = sizeof(ERROR_SERVER_FAILURE);
    return(Pop3_SendError);
}


//+---------------------------------------------------------------------------
//
//  Function:   DeleDispatch
//
//  Synopsis:   Handles the DELE command
//
//  Arguments:  [pContext]        --
//              [InputBuffer]     --
//              [InputBufferLen]  --
//              [SendHandle]      --
//              [OutputBuffer]    --
//              [OutputBufferLen] --
//
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
Pop3Disposition
DeleDispatch(
    PPopContext pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen)
{
    DWORD   MessageId;


    DebugLog((DEB_TRACE_PROT, "Received DELE\n"));

    //
    // Verify context, and that the context says we can receive this command
    //

    if (!pContext)
    {
        return(Pop3_Discard);
    }

    if (pContext->State != PopTransact)
    {
        *OutputBuffer = ERROR_POP3_INVALID_STATE;
        *OutputBufferLen = sizeof(ERROR_POP3_INVALID_STATE);
        return(Pop3_SendError);
    }

    MessageId = (DWORD) -1;

    if (InputBufferLen > POP3_COMMAND_LENGTH)
    {
        sscanf(&InputBuffer[POP3_COMMAND_LENGTH], "%d", &MessageId);
    }

    //
    // Pop is 1-based, we're 0-based
    //
    MessageId--;

    if (MessageId > pContext->pDirectory->cMessages ||
        (pContext->pDirectory->Messages[MessageId].Flags & POP3_MESSAGE_DELETE))
    {
        *OutputBuffer = ERROR_UNKNOWN_MESSAGE;
        *OutputBufferLen = sizeof(ERROR_UNKNOWN_MESSAGE);
        return(Pop3_SendError);
    }

    //
    // Update directory with "deleted" file
    //
    pContext->pDirectory->Messages[MessageId].Flags |= POP3_MESSAGE_DELETE;
    pContext->pDirectory->cAvailMessages--;
    pContext->pDirectory->AvailSize -= pContext->pDirectory->Messages[MessageId].Size;

    *OutputBuffer = AllocAndCopyString(POP3_GOOD_RESPLINE, OutputBufferLen);
    return(Pop3_SendBuffer);
}

//+---------------------------------------------------------------------------
//
//  Function:   NoopDispatch
//
//  Synopsis:   Handles the NOOP command
//
//  Arguments:  [pContext]        --
//              [InputBuffer]     --
//              [InputBufferLen]  --
//              [SendHandle]      --
//              [OutputBuffer]    --
//              [OutputBufferLen] --
//
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
Pop3Disposition
NoopDispatch(
    PPopContext pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen)
{

    DebugLog((DEB_TRACE_PROT, "Received NOOP\n"));

    //
    // Verify context, and that the context says we can receive this command
    //

    if (!pContext)
    {
        return(Pop3_Discard);
    }

    if (pContext->State != PopTransact)
    {
        *OutputBuffer = ERROR_POP3_INVALID_STATE;
        *OutputBufferLen = sizeof(ERROR_POP3_INVALID_STATE);
        return(Pop3_SendError);
    }

    *OutputBuffer = AllocAndCopyString(POP3_GOOD_RESPLINE, OutputBufferLen);
    return(Pop3_SendBuffer);
}


//+---------------------------------------------------------------------------
//
//  Function:   LastDispatch
//
//  Synopsis:   Handles the LAST command
//
//  Arguments:  [pContext]        --
//              [InputBuffer]     --
//              [InputBufferLen]  --
//              [SendHandle]      --
//              [OutputBuffer]    --
//              [OutputBufferLen] --
//
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
Pop3Disposition
LastDispatch(
    PPopContext pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen)
{
    char    Line[40];

    DebugLog((DEB_TRACE_PROT, "Received LAST\n"));

    if (!pContext)
    {
        return(Pop3_Discard);
    }

    if (pContext->State != PopTransact)
    {
        *OutputBuffer = ERROR_POP3_INVALID_STATE;
        *OutputBufferLen = sizeof(ERROR_POP3_INVALID_STATE);
        return(Pop3_SendError);
    }

    sprintf(Line, POP3_LAST_RESPONSE, pContext->pDirectory->NextMessage+1);
    *OutputBuffer = AllocAndCopyString(Line, OutputBufferLen);

    return(Pop3_SendBuffer);
}


//+---------------------------------------------------------------------------
//
//  Function:   RsetDispatch
//
//  Synopsis:   Handles the RSET command
//
//  Arguments:  [pContext]        --
//              [InputBuffer]     --
//              [InputBufferLen]  --
//              [SendHandle]      --
//              [OutputBuffer]    --
//              [OutputBufferLen] --
//
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
Pop3Disposition
RsetDispatch(
    PPopContext pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen)
{
    DWORD   i;

    DebugLog((DEB_TRACE_PROT, "Received LAST\n"));

    if (!pContext)
    {
        return(Pop3_Discard);
    }

    if (pContext->State != PopTransact)
    {
        *OutputBuffer = ERROR_POP3_INVALID_STATE;
        *OutputBufferLen = sizeof(ERROR_POP3_INVALID_STATE);
        return(Pop3_SendError);
    }

    for (i = 0; i < pContext->pDirectory->cMessages ; i++ )
    {
        pContext->pDirectory->Messages[i].Flags = 0;
    }

    pContext->pDirectory->NextMessage = 0;
    pContext->pDirectory->cAvailMessages = pContext->pDirectory->cMessages;
    pContext->pDirectory->AvailSize = pContext->pDirectory->TotalSize;

    *OutputBuffer = AllocAndCopyString(POP3_GOOD_RESPLINE, OutputBufferLen);
    return(Pop3_SendBuffer);
}



//+---------------------------------------------------------------------------
//
//  Function:   Pop3Dispatch
//
//  Synopsis:   Dispatch the command
//
//  Arguments:  [pContext]        --    Context for client connection
//              [InputBuffer]     --    Input Buffer (stuff from client)
//              [InputBufferLen]  --    How much stuff
//              [SendHandle]      --    Handle to Transmit, if so required
//              [OutputBuffer]    --    (returned) pointer of stuff to send
//              [OutputBufferLen] --    (returned) size of stuff to send
//
//  Returns:    a Pop3Disposition, which indicates what the socket code
//              should do with this stuff.  See pop3ctx.h for the dispositions
//
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
Pop3Disposition
Pop3Dispatch(
    PVOID       pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen
    )

{
    PPopContext pPopContext;
    int     Command;

    pPopContext = (PPopContext) pContext;

    //
    // Null terminate, so string functions won't get confused later.
    //

    InputBuffer[InputBufferLen] = L'\0';

    //
    // Figure the command out
    //

    Command = Pop3CrackCommand(InputBuffer, InputBufferLen);

    //
    // If it didn't parse, throw it away
    //
    if (Command == -1)
    {
        return(Pop3_Discard);
    }

    //
    // Let the command handlers do their thing
    //
    return(Pop3DispatchTable[Command](  pPopContext,
                                        InputBuffer,
                                        InputBufferLen,
                                        SendHandle,
                                        OutputBuffer,
                                        OutputBufferLen) );


}

#if DBG

//
// Interactive debug testing
//
void TestLoop(void)
{
    char    InputBuffer[256];
    DWORD   InputBufferLen;
    char *  OutputBuffer;
    DWORD   OutputBufferLen;
    HANDLE  hTest;
    PVOID   pContext;
    Pop3Disposition Disposition;
    extern WCHAR BaseDirectory[];

    printf("-------------------\n");
    printf("Interactive Test Mode\n");

    pContext = CreatePop3Context();
    do
    {
        gets(InputBuffer);
        InputBufferLen = strlen(InputBuffer);
        if (InputBufferLen)
        {
            Disposition = Pop3Dispatch( pContext,
                                        InputBuffer,
                                        InputBufferLen,
                                        &hTest,
                                        &OutputBuffer,
                                        &OutputBufferLen);

            switch (Disposition)
            {
                case Pop3_Discard:
                    printf("[Discard message]\n");
                    break;

                case Pop3_SendError:
                    printf("%s", OutputBuffer);
                    break;

                case Pop3_SendBuffer:
                    printf("%s", OutputBuffer);
                    LocalFree(OutputBuffer);
                    break;

                case Pop3_SendFile:
                    printf("Transmit file %x\n", hTest);
                    printf(".\r\n");
                    CloseHandle(hTest);
                    break;

                case Pop3_SendBufferThenFile:
                    printf("%s", OutputBuffer);
                    printf("Transmit file %x\n", hTest);
                    printf(".\r\n");
                    CloseHandle(hTest);
                    LocalFree(OutputBuffer);
                    break;

                case Pop3_SendFileThenBuffer:
                    printf("Transmit file %x\n", hTest);
                    printf("%s", OutputBuffer);
                    CloseHandle(hTest);
                    LocalFree(OutputBuffer);
                    break;

            }

        }

    } while (InputBufferLen);

}
#endif
