//+---------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1992 - 1993.
//
//  File:       popfile.c
//
//  Contents:
//
//  Classes:
//
//  Functions:
//
//  History:    1-06-95   RichardW   Created
//
//----------------------------------------------------------------------------

#include <pop3srvp.h>
#pragma hdrstop

#define POP3_LOCKFILE       TEXT("poplock")
#define POP3_LOCKFILE_NAME  TEXT("\\") POP3_LOCKFILE
#define POP3_SEARCH         TEXT("\\*.*")


WCHAR   BaseDirectory[MAX_PATH];

//+---------------------------------------------------------------------------
//
//  Function:   LockMailDirectory
//
//  Synopsis:   Attempts to lock the mail directory
//
//  Arguments:  [hUserToken] -- Token of user
//              [pszPath]    -- path to the mail directory
//
//  Returns:    Handle of lock file on success, or NULL
//
//  History:    1-06-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
HANDLE
LockMailDirectory(
    HANDLE          hUserToken,
    PCHAR           pszPath)
{

    WCHAR   PathToOpen[MAX_PATH];
    WCHAR   WidePath[64];
    HANDLE  hLockFile;

    //
    // Build lock file name
    //
    MultiByteToWideChar(
        CP_ACP, MB_PRECOMPOSED,
        pszPath, -1,
        WidePath, sizeof(WidePath) / sizeof(WCHAR) );

    wcscpy(PathToOpen, BaseDirectory);
    wcscat(PathToOpen, WidePath);
    wcscat(PathToOpen, POP3_LOCKFILE_NAME);

    //
    // Impersonate the client
    //
#ifdef SECURE_BUILD

    ImpersonateLoggedOnUser(hUserToken);

#endif

    //
    // Attempt to create the file.  This will fail if it already exists,
    // which would indicate that another thread/client is accessing this
    // mailbox.
    //
    DebugLog((DEB_TRACE, "Opening lock file as %ws\n", PathToOpen));

    hLockFile = CreateFile( PathToOpen,
                            GENERIC_READ | GENERIC_WRITE,
                            0,
                            NULL,
                            CREATE_NEW,
                            FILE_ATTRIBUTE_NORMAL |
                            FILE_FLAG_DELETE_ON_CLOSE,
                            NULL);

    //
    // Done being the client.  Back to server security
    //
    RevertToSelf();

    //
    // Return a handle, or NULL if failed
    //
    return(hLockFile != INVALID_HANDLE_VALUE ? hLockFile : NULL);

}

//+---------------------------------------------------------------------------
//
//  Function:   OpenMailMessage
//
//  Synopsis:   Opens the specified mail message as the user
//
//  Arguments:  [MessageId]  --
//              [pDir]       --
//              [hUserToken] --
//
//  History:    1-08-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
HANDLE
OpenMailMessage(
    DWORD               MessageId,
    PPopMailDirectory   pDir,
    HANDLE              hUserToken)
{
    HANDLE  hMailFile;
    WCHAR   Path[MAX_PATH];

    //
    // Impersonate the client
    //
#ifdef SECURE_BUILD

    ImpersonateLoggedOnUser(hUserToken);

#endif

    //
    // Attempt to create the file.  This will fail if it already exists,
    // which would indicate that another thread/client is accessing this
    // mailbox.
    //
    wcscpy(Path, pDir->pBaseDir);
    wcscat(Path, TEXT("\\"));
    wcscat(Path, pDir->Messages[MessageId].pszFileName);

    hMailFile = CreateFile( Path,
                            GENERIC_READ | GENERIC_WRITE,
                            0,
                            NULL,
                            OPEN_EXISTING,
                            FILE_ATTRIBUTE_HIDDEN,
                            NULL);

    //
    // Done being the client.  Back to server security
    //
    RevertToSelf();

    //
    // Return a handle, or NULL if failed
    //
    return(hMailFile != INVALID_HANDLE_VALUE ? hMailFile : NULL);
}


//+---------------------------------------------------------------------------
//
//  Function:   UnlockMailDirectory
//
//  Synopsis:   Unlocks the mail directory
//
//  Arguments:  [hLockFile] -- Handle of lock file to close
//
//  Returns:    TRUE if success, FALSE if failure
//
//  History:    1-06-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
BOOL
UnlockMailDirectory(
    HANDLE      hLockFile)
{
    //
    // Since the lock file was opened with DELETE_ON_CLOSE semantics, it will
    // softly and silently vanish away when we close this, the one handle to
    // it.
    //

    return(CloseHandle(hLockFile));
}



//+---------------------------------------------------------------------------
//
//  Function:   ReadMailDirectory
//
//  Synopsis:   Reads in a list of all the files in the directory
//
//  Arguments:  [hUserToken] --
//              [pszPath]    --
//
//  Returns:
//
//  History:    1-08-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
PPopMailDirectory
ReadMailDirectory(
    HANDLE          hUserToken,
    PCHAR           pszPath)
{
    WIN32_FIND_DATA     FindData;
    PPopMailDirectory   pDir;
    WCHAR               MailDir[MAX_PATH];
    WCHAR               WidePath[64];
    HANDLE              hSearch;
    PPopMessageHeader   pExtraHeaders;
    PPopMessageHeader   pHeader;
    DWORD               RemainingHeaders;

    MultiByteToWideChar(
        CP_ACP, MB_PRECOMPOSED,
        pszPath, -1,
        WidePath, sizeof(WidePath) / sizeof(WCHAR) );
    wcscpy(MailDir, BaseDirectory);
    wcscat(MailDir, WidePath);

    pDir = LocalAlloc(LMEM_FIXED | LMEM_ZEROINIT, sizeof(PopMailDirectory));
    pDir->pBaseDir = LocalAlloc(LMEM_FIXED, (wcslen(MailDir) + 1) * sizeof(WCHAR));
    wcscpy(pDir->pBaseDir, MailDir);

    wcscat(MailDir, POP3_SEARCH);

#ifdef SECURE_BUILD

    ImpersonateLoggedOnUser(hUserToken);

#endif

    hSearch = FindFirstFile(MailDir, &FindData);

    if (hSearch == INVALID_HANDLE_VALUE)
    {
        DebugLog((DEB_TRACE, "FindFirst FAILED!, %d\n", GetLastError()));
        RevertToSelf();

        return(NULL);
    }

    pExtraHeaders = LocalAlloc(LMEM_FIXED, sizeof(PopMessageHeader) * 10);
    RemainingHeaders = 10;
    pHeader = pExtraHeaders;

    do
    {
        if (FindData.dwFileAttributes & (FILE_ATTRIBUTE_DIRECTORY |
                                        FILE_ATTRIBUTE_SYSTEM |
                                        FILE_ATTRIBUTE_HIDDEN) )
        {
            continue;   // Skip non-normal files
        }
        if (wcsicmp(FindData.cFileName,POP3_LOCKFILE) == 0)
        {
            continue;   // Skip our lock file
        }
        DebugLog((DEB_TRACE, "ReadDir:  Message %ws, size %d\n",
                FindData.cFileName, FindData.nFileSizeLow));

        pHeader->Flags = 0;
        pDir->TotalSize += FindData.nFileSizeLow;
        pHeader->Size = FindData.nFileSizeLow;

        pHeader->pszFileName = LocalAlloc(LMEM_FIXED,
                            (wcslen(FindData.cFileName) + 1) * sizeof(WCHAR) );

        wcscpy(pHeader->pszFileName, FindData.cFileName);
        pHeader++;
        RemainingHeaders--;



        if (RemainingHeaders == 0)
        {
            PPopMessageHeader   pTemp;


            pTemp = LocalAlloc(LMEM_FIXED, sizeof(PopMessageHeader) * (pDir->cMessages + 20));

            CopyMemory(pTemp, pExtraHeaders, sizeof(PopMessageHeader) * (pDir->cMessages + 10));

            LocalFree(pExtraHeaders);

            pExtraHeaders = pTemp;

            RemainingHeaders = 10;

            pDir->cMessages += 10;
        }

    } while (FindNextFile(hSearch, &FindData));

    pDir->cMessages += (10 - RemainingHeaders);
    pDir->Messages = pExtraHeaders;

    FindClose(hSearch);

    pDir->cAvailMessages = pDir->cMessages;
    pDir->AvailSize = pDir->TotalSize;

    RevertToSelf();

    return(pDir);
}

BOOL
CommitMailDirectory(
    PPopMailDirectory   pDir,
    HANDLE              hUserToken)
{
    DWORD   i;
    WCHAR   Path[MAX_PATH];
    PWSTR   pszPath;

    wcscpy(Path, pDir->pBaseDir);
    wcscat(Path, TEXT("\\"));
    pszPath = Path + wcslen(Path);


#ifdef SECURE_BUILD

    ImpersonateLoggedOnUser(hUserToken);

#endif

    for (i = 0; i < pDir->cMessages ; i++)
    {
        if (pDir->Messages[i].Flags & POP3_MESSAGE_DELETE)
        {
            wcscpy(pszPath, pDir->Messages[i].pszFileName);
            DeleteFile(Path);
        }
    }

    RevertToSelf();

    return(TRUE);
}

void
FreeMailDirectory(
    PPopMailDirectory   pDir)
{
    DWORD   i;

    for (i = 0 ; i < pDir->cMessages ; i++ )
    {
        LocalFree(pDir->Messages[i].pszFileName);
    }

    LocalFree(pDir->Messages);
    LocalFree(pDir);

}
