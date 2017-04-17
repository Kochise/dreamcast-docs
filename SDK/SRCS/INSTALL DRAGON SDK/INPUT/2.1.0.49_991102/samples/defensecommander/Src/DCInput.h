/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    DCInput.h

Abstract:

    Input related functions.

-------------------------------------------------------------------*/

BOOL InitInput(HWND AppHWnd);
void ShutdownInput(HWND AppHWnd);
void AcquireInput(void);
void UnacquireInput(void);
void KeyEvent(int Key, BOOL Down);
