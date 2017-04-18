/*+----------------------------------------------------------------------------

Microsoft Windows Sample Program
Copyright (C) 1994 - 1997 Microsoft Corporation.  All rights reserved.

FILE:       error.cxx

PURPOSE:    Demonstrates how to get the message text for an error code from
            the system resources.

FUNCTIONS:  PrintErrorMessage - Prints the message text for an error code.

-----------------------------------------------------------------------------*/
#include <windows.h>
#include <stdio.h>

//+---------------------------------------------------------------------------
//
//  Function:   PrintErrorMessage
//
//  Synopsis:   Prints the message text for the specified error code.
//
//  Notes:      PrintErrorMessage uses FormatMessage to get the message
//              text from the system resources.
//
//----------------------------------------------------------------------------
void PrintErrorMessage(HRESULT hr)
{
  DWORD cMsgLen;
  char *pszErrorMessage = 0; /* buffer for message text from system */

  /* get the text description for that error number from the system */
  cMsgLen = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, 
                          0, 
                          (DWORD) hr,
                          MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
                          (LPTSTR) &pszErrorMessage, 
                          512,
                          0);

    if(cMsgLen > 0)
    {
        printf("Error %x: %s\n", hr, pszErrorMessage);
        LocalFree((HLOCAL) pszErrorMessage);
    }
    else
    {
        printf("Error %x\n", hr);
    }
}
