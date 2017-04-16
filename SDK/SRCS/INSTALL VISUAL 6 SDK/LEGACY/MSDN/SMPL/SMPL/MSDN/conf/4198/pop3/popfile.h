//+---------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1992 - 1993.
//
//  File:       popfile.h
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

#ifndef __POPFILE_H__
#define __POPFILE_H__





HANDLE
LockMailDirectory(
    HANDLE          hUserToken,         // Token of user
    PCHAR           pszPath);           // Path to mail directory

BOOL
UnlockMailDirectory(
    HANDLE          hLockFile);

PPopMailDirectory
ReadMailDirectory(
    HANDLE          hUserToken,
    PCHAR           pszPath);

BOOL
CommitMailDirectory(
    PPopMailDirectory   pDir,
    HANDLE              hUserToken);

void
FreeMailDirectory(
    PPopMailDirectory   pDir);


HANDLE
OpenMailMessage(
    DWORD               MessageId,
    PPopMailDirectory   pDir,
    HANDLE              hUserToken);

#endif
