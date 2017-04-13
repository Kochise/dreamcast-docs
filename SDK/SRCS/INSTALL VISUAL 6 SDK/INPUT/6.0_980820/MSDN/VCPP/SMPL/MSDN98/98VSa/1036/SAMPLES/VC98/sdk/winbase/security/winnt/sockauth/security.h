/*++

Copyright 1996-1997 Microsoft Corporation

Module Name:

    security.h

Abstract:

    Functions to handle communication with the security package

Revision History:

--*/

BOOL InitPackage (DWORD *pcbMaxMessage);
BOOL TermPackage ();
BOOL InitSession (DWORD dwKey);
BOOL TermSession (DWORD dwKey);
BOOL GenClientContext (
			DWORD dwKey,
			BYTE *pIn,
			DWORD cbIn,
			BYTE *pOut,
			DWORD *pcbOut,
			BOOL *pfDone
			);
BOOL GenServerContext (
			DWORD dwKey,
			BYTE *pIn,
			DWORD cbIn,
			BYTE *pOut,
			DWORD *pcbOut,
			BOOL *pfDone
			);
BOOL ImpersonateContext (DWORD dwKey);
BOOL RevertContext (DWORD dwKey);

