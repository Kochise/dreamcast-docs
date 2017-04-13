
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/


BOOL DisconnectFromProgman(VOID);
BOOL ConnectToProgmanW(VOID);
BOOL ConnectToProgmanA(VOID);
BOOL ProgmanExecuteStringW(LPWSTR pszExec);
BOOL ProgmanExecuteStringA(LPSTR pszExec);

#ifdef UNICODE
#define ConnectToProgman ConnectToProgmanW
#define ProgmanExecuteString ProgmanExecuteStringW
#else
#define ConnectToProgman ConnectToProgmanA
#define ProgmanExecuteString ProgmanExecuteStringA
#endif
