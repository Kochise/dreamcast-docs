/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    MiscCE.cpp

Abstract:

    Misc functions for Windows CE.

-------------------------------------------------------------------*/

#include "DC.h"

extern HWND AppHWnd; // In InitPC.cpp

// Displays an error message in a message box.
// Accepts a formated string.
void DisplayErrorMessage(int MessageId,...)
{
    TCHAR szTitle[50];
    TCHAR szFormat[1024];
    TCHAR Buffer[2048];
    va_list  va;

    LoadString(gHInstance, IDS_ERROR_TITLE, szTitle, 50);
    LoadString(gHInstance, MessageId, szFormat, 1024);
    va_start(va, MessageId);
	wsprintf(Buffer, szFormat, va);
    va_end(va);

	OutputDebugString(Buffer);
}
