/*++

Copyright 1996-1997 Microsoft Corporation

Module Name:

    collect.h

Abstract:

    Functions for a simple collection

Revision History:

--*/

BOOL GetEntry (DWORD dwKey, PVOID *ppData);
BOOL AddEntry (DWORD dwKey, PVOID pData);
BOOL DeleteEntry (DWORD dwKey, PVOID *ppData);

