/*++

DCOM Permission Configuration Sample
Copyright (c) 1996, Microsoft Corporation. All rights reserved.

Module Name:

    dcomperm.cpp

Abstract:

    Main module for DCOM Permission Configuration Sample

Author:

    Michael Nelson

Environment:

    Windows NT

--*/

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include "ntsecapi.h"
#include "dcomperm.h"

void
ShowUsage (
    LPTSTR ErrorString
    )
{
    _tprintf (TEXT("%s\n"), ErrorString);
    _tprintf (TEXT("Syntax: dcomperm <option> [...]\n\n"));

    _tprintf (TEXT("Options:\n"));

    _tprintf (TEXT("   -da <\"set\" or \"remove\"> <Principal Name> [\"permit\" or \"deny\"]\n"));
    _tprintf (TEXT("   -da list\n"));
    _tprintf (TEXT("       Modify or list the default access permission list\n\n"));

    _tprintf (TEXT("   -dl <\"set\" or \"remove\"> <Principal Name> [\"permit\" or \"deny\"]\n"));
    _tprintf (TEXT("   -dl list\n"));
    _tprintf (TEXT("       Modify or list the default launch permission list\n\n"));

    _tprintf (TEXT("   -aa <AppID> <\"set\" or \"remove\"> <Principal Name> [\"permit\" or \"deny\"]\n"));
    _tprintf (TEXT("   -aa <AppID> default\n"));
    _tprintf (TEXT("   -aa <AppID> list\n"));
    _tprintf (TEXT("       Modify or list the access permission list for a specific AppID\n\n"));

    _tprintf (TEXT("   -al <AppID> <\"set\" or \"remove\"> <Principal Name> [\"permit\" or \"deny\"]\n"));
    _tprintf (TEXT("   -al <AppID> default\n"));
    _tprintf (TEXT("   -al <AppID> list\n"));
    _tprintf (TEXT("       Modify or list the launch permission list for a specific AppID\n\n"));

    _tprintf (TEXT("Press any key to continue. . ."));
    _getch();
    _tprintf (TEXT("\r                               \r"));

    _tprintf (TEXT("   -runas <AppID> <Principal Name> <Password>\n"));
    _tprintf (TEXT("   -runas <AppID> \"Interactive User\"\n"));
    _tprintf (TEXT("       Set the RunAs information for a specific AppID\n\n"));

    _tprintf (TEXT("Examples:\n"));
    _tprintf (TEXT("   dcomperm -da set redmond\\t-miken permit\n"));
    _tprintf (TEXT("   dcomperm -dl set redmond\\jdoe deny\n"));
    _tprintf (TEXT("   dcomperm -aa {12345678-1234-1234-1234-00aa00bbf7c7} list\n"));
    _tprintf (TEXT("   dcomperm -al {12345678-1234-1234-1234-00aa00bbf7c7} remove redmond\\t-miken\n"));
    _tprintf (TEXT("   dcomperm -runas {12345678-1234-1234-1234-00aa00bbf7c7} redmond\\jdoe password\n"));

    exit (0);
}

void
Error (
    LPTSTR ErrorMessage,
    DWORD ErrorCode
    )
{
    TCHAR messageBuffer [255];

    _tprintf (TEXT("%s\n%s"), ErrorMessage, SystemMessage (messageBuffer, ErrorCode));
    exit (0);
}

void
HandleDAOption (
    int argc,
    TCHAR **argv
    )
{
    DWORD returnValue;

    if (argc < 3)
        ShowUsage (TEXT("Invalid number of arguments."));

    if (_tcscmp (_tcsupr (argv [2]), TEXT("LIST")) == 0)
    {
        _tprintf (TEXT("Default access permission list:\n\n"));
        ListDefaultAccessACL();
        return;
    }

    if (argc < 4)
        ShowUsage (TEXT("Invalid number of arguments."));

    if (_tcscmp (_tcsupr (argv [2]), TEXT("SET")) == 0)
    {
        if (argc < 5)
            ShowUsage (TEXT("Invalid number of arguments."));

        if (_tcscmp (_tcsupr (argv [4]), TEXT("PERMIT")) == 0)
            returnValue = ChangeDefaultAccessACL (argv [3], TRUE, TRUE); else

        if (_tcscmp (_tcsupr (argv [4]), TEXT("DENY")) == 0)
            returnValue = ChangeDefaultAccessACL (argv [3], TRUE, FALSE); else
        {
            ShowUsage (TEXT("You can only set a user's permissions to \"permit\" or \"deny\".\n\n"));
        }

        if (returnValue != ERROR_SUCCESS)
            Error (TEXT("ERROR: Cannot add user to default access ACL."), returnValue);
    } else
    if (_tcscmp (_tcsupr (argv [2]), TEXT("REMOVE")) == 0)
    {
        returnValue = ChangeDefaultAccessACL (argv[3], FALSE, FALSE);

        if (returnValue != ERROR_SUCCESS)
            Error (TEXT("ERROR: Cannot remove user from default access ACL."), returnValue);
    } else
        ShowUsage (TEXT("You can only \"set\" or \"remove\" a user."));
}

void
HandleDLOption (
    int argc,
    TCHAR **argv
    )
{
    DWORD returnValue;

    if (argc < 3)
        ShowUsage (TEXT("Invalid number of arguments."));

    if (_tcscmp (_tcsupr (argv [2]), TEXT("LIST")) == 0)
    {
        _tprintf (TEXT("Default launch permission list:\n\n"));
        ListDefaultLaunchACL();
        return;
    }

    if (argc < 4)
        ShowUsage (TEXT("Invalid number of arguments."));

    if (_tcscmp (_tcsupr (argv [2]), TEXT("SET")) == 0)
    {
        if (argc < 5)
            ShowUsage (TEXT("Invalid number of arguments."));

        if (_tcscmp (_tcsupr (argv [4]), TEXT("PERMIT")) == 0)
            returnValue = ChangeDefaultLaunchACL (argv [3], TRUE, TRUE); else

        if (_tcscmp (_tcsupr (argv [4]), TEXT("DENY")) == 0)
            returnValue = ChangeDefaultLaunchACL (argv [3], TRUE, FALSE); else
        {
            ShowUsage (TEXT("You can only set a user's permissions to \"permit\" or \"deny\".\n\n"));
        }

        if (returnValue != ERROR_SUCCESS)
            Error (TEXT("ERROR: Cannot add user to default launch ACL."), returnValue);
    } else
    if (_tcscmp (_tcsupr (argv [3]), TEXT("REMOVE")) == 0)
    {
        returnValue = ChangeDefaultLaunchACL (argv[3], FALSE, FALSE);

        if (returnValue != ERROR_SUCCESS)
            Error (TEXT("ERROR: Cannot remove user from default launch ACL."), returnValue);
    } else
        ShowUsage (TEXT("You can only \"set\" or \"remove\" a user."));
}

void
HandleAAOption (
    int argc,
    TCHAR **argv
    )
{
    DWORD returnValue;
    HKEY  registryKey;
    TCHAR appid [256];
    TCHAR keyName [256];

    if (argc < 4)
        ShowUsage (TEXT("Invalid number of arguments."));

    if (_tcscmp (_tcsupr (argv[3]), TEXT("LIST")) == 0)
    {
        if (argc < 4)
            ShowUsage (TEXT("Invalid number of arguments."));

        _tprintf (TEXT("Access permission list for AppID %s:\n\n"), argv[2]);
        ListAppIDAccessACL (argv[2]);
        return;
    }

    if (_tcscmp (_tcsupr (argv[3]), TEXT("DEFAULT")) == 0)
    {
        if (argv [2][0] == '{')
            wsprintf (appid, TEXT("%s"), argv [2]); else
            wsprintf (appid, TEXT("{%s}"), argv [2]);

        wsprintf (keyName, TEXT("APPID\\%s"), appid);

        returnValue = RegOpenKeyEx (HKEY_CLASSES_ROOT, keyName, 0, KEY_ALL_ACCESS, &registryKey);
        if (returnValue != ERROR_SUCCESS && returnValue != ERROR_FILE_NOT_FOUND)
            Error (TEXT("ERROR: Cannot open AppID registry key."), returnValue);

        returnValue = RegDeleteValue (registryKey, TEXT("AccessPermission"));
        if (returnValue != ERROR_SUCCESS && returnValue != ERROR_FILE_NOT_FOUND)
            Error (TEXT("ERROR: Cannot delete AccessPermission value."), returnValue);

        RegCloseKey (registryKey);
        return;
    }

    if (argc < 5)
        ShowUsage (TEXT("Invalid number of arguments."));

    if (_tcscmp (_tcsupr (argv [3]), TEXT("SET")) == 0)
    {
        if (argc < 6)
            ShowUsage (TEXT("Invalid number of arguments."));

        if (_tcscmp (_tcsupr (argv [5]), TEXT("PERMIT")) == 0)
            returnValue = ChangeAppIDAccessACL (argv[2], argv [4], TRUE, TRUE); else

        if (_tcscmp (_tcsupr (argv [5]), TEXT("DENY")) == 0)
            returnValue = ChangeAppIDAccessACL (argv[2], argv [4], TRUE, FALSE); else
        {
            ShowUsage (TEXT("You can only set a user's permissions to \"permit\" or \"deny\".\n\n"));
        }

        if (returnValue != ERROR_SUCCESS)
            Error (TEXT("ERROR: Cannot add user to application access ACL."), returnValue);
    } else
    if (_tcscmp (_tcsupr (argv [3]), TEXT("REMOVE")) == 0)
    {
        returnValue = ChangeAppIDAccessACL (argv[2], argv[4], FALSE, FALSE);

        if (returnValue != ERROR_SUCCESS)
            Error (TEXT("ERROR: Cannot remove user from application access ACL."), returnValue);
    } else
        ShowUsage (TEXT("You can only \"set\" or \"remove\" a user."));
}

void
HandleALOption (
    int argc,
    TCHAR **argv
    )
{
    DWORD returnValue;
    HKEY  registryKey;
    TCHAR appid [256];
    TCHAR keyName [256];

    if (argc < 4)
        ShowUsage (TEXT("Invalid number of arguments."));

    if (_tcscmp (_tcsupr (argv[3]), TEXT("LIST")) == 0)
    {
        if (argc < 4)
            ShowUsage (TEXT("Invalid number of arguments.\n"));

        _tprintf (TEXT("Launch permission list for AppID %s:\n\n"), argv[2]);
        ListAppIDLaunchACL (argv[2]);
        return;
    }

    if (_tcscmp (_tcsupr (argv[3]), TEXT("DEFAULT")) == 0)
    {
        if (argv [2][0] == '{')
            wsprintf (appid, TEXT("%s"), argv [2]); else
            wsprintf (appid, TEXT("{%s}"), argv [2]);

        wsprintf (keyName, TEXT("APPID\\%s"), appid);

        returnValue = RegOpenKeyEx (HKEY_CLASSES_ROOT, keyName, 0, KEY_ALL_ACCESS, &registryKey);
        if (returnValue != ERROR_SUCCESS && returnValue != ERROR_FILE_NOT_FOUND)
            Error (TEXT("ERROR: Cannot open AppID registry key."), returnValue);

        returnValue = RegDeleteValue (registryKey, TEXT("LaunchPermission"));
        if (returnValue != ERROR_SUCCESS && returnValue != ERROR_FILE_NOT_FOUND)
            Error (TEXT("ERROR: Cannot delete LaunchPermission value."), returnValue);

        RegCloseKey (registryKey);
        return;
    }

    if (argc < 5)
        ShowUsage (TEXT("Invalid number of arguments."));

    if (_tcscmp (_tcsupr (argv [3]), TEXT("SET")) == 0)
    {
        if (argc < 6)
            ShowUsage (TEXT("Invalid number of arguments."));

        if (_tcscmp (_tcsupr (argv [5]), TEXT("PERMIT")) == 0)
            returnValue = ChangeAppIDLaunchACL (argv[2], argv [4], TRUE, TRUE); else

        if (_tcscmp (_tcsupr (argv [5]), TEXT("DENY")) == 0)
            returnValue = ChangeAppIDLaunchACL (argv[2], argv [4], TRUE, FALSE); else
        {
            ShowUsage (TEXT("You can only set a user's permissions to \"permit\" or \"deny\".\n\n"));
        }

        if (returnValue != ERROR_SUCCESS)
            Error (TEXT("ERROR: Cannot add user to application launch ACL."), returnValue);
    } else
    if (_tcscmp (_tcsupr (argv [3]), TEXT("REMOVE")) == 0)
    {
        returnValue = ChangeAppIDLaunchACL (argv[2], argv[4], FALSE, FALSE);

        if (returnValue != ERROR_SUCCESS)
            Error (TEXT("ERROR: Cannot remove user from application launch ACL."), returnValue);
    } else
        ShowUsage (TEXT("You can only \"set\" or \"remove\" a user."));
}

void
HandleRunAsOption (
    int argc,
    TCHAR **argv
    )
{
    DWORD returnValue;
    HKEY  registryKey;
    TCHAR appid [256];
    TCHAR keyName [256];

    if (argc < 4)
        ShowUsage (TEXT("Invalid number of arguments."));

    if (argv [2][0] == '{')
        wsprintf (appid, TEXT("%s"), argv [2]); else
        wsprintf (appid, TEXT("{%s}"), argv [2]);

    wsprintf (keyName, TEXT("APPID\\%s"), appid);

    returnValue = RegOpenKeyEx (HKEY_CLASSES_ROOT, keyName, 0, KEY_ALL_ACCESS, &registryKey);
    if (returnValue != ERROR_SUCCESS)
        Error (TEXT("ERROR: Cannot open AppID registry key."), returnValue);

    returnValue = RegSetValueEx (registryKey, TEXT("RunAs"), 0, REG_SZ, (LPBYTE) argv [3], _tcslen (argv[3]) * sizeof (TCHAR));
    if (returnValue != ERROR_SUCCESS)
        Error (TEXT("ERROR: Cannot set RunAs registry value."), returnValue);

    RegCloseKey (registryKey);

    if (_tcscmp (_tcsupr (argv[3]), TEXT("INTERACTIVE USER")) != 0)
    {
        if (argc < 5)
            ShowUsage (TEXT("Invalid number of arguments."));

        returnValue = SetRunAsPassword (argv[2], argv[3], argv[4]);
        if (returnValue != ERROR_SUCCESS)
            Error (TEXT("ERROR: Cannot set RunAs password."), returnValue);
    }
}

extern "C" void
_tmain (
    int argc,
    TCHAR **argv
    )
{
    if (argc < 2)
        ShowUsage (TEXT("No option specified."));

    if (_tcscmp (_tcsupr (argv [1]), TEXT("-DA")) == 0)
        HandleDAOption (argc, argv); else

    if (_tcscmp (_tcsupr (argv [1]), TEXT("-DL")) == 0)
        HandleDLOption (argc, argv); else

    if (_tcscmp (_tcsupr (argv [1]), TEXT("-AA")) == 0)
        HandleAAOption (argc, argv); else

    if (_tcscmp (_tcsupr (argv [1]), TEXT("-AL")) == 0)
        HandleALOption (argc, argv); else

    if (_tcscmp (_tcsupr (argv [1]), TEXT("-RUNAS")) == 0)
        HandleRunAsOption (argc, argv); else

    ShowUsage (TEXT("Invalid option specified."));
}
