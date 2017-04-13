/*++

Copyright (c) 1995-1997 Microsoft Corporation

Module Name:

    proto.h

Abstract:

    prototypes

Environment:

    Internet

Revision History:

    dd-mmm-yyy <email>

--*/

BOOL
HttpGetSocket(
    char * Verb,
    char * Server,
    char * URL,
    BOOL   DisplayHeaders,
    DWORD  ClientDataSize,
    PSTR   pszUserName,
    PSTR   pszPassword,
    PSTR   pszStore,
    PSTR   pszPref );
