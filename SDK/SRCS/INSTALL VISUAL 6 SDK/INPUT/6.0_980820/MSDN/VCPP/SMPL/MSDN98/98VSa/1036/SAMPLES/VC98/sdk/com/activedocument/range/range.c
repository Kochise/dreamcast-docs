// ===========================================================================
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright 1996 Microsoft Corporation.  All Rights Reserved.
// ===========================================================================
#include <windows.h>
#include <urlmon.h>
#include <stdio.h>
#include <stdlib.h>
#include "range.h"

DWORD g_dwThread;

//==============================================================================
void DumpBytes (PBYTE pBuf, DWORD cbBuf)
{
    DWORD i;
    for (i=0; i<cbBuf; i++)
    {
        switch(pBuf[i])
        {
            case 10:  printf("[LF]"); break;
            case 13:  printf("[CR]"); break;
            default:  printf("%c", pBuf[i]); break;
        }
    }
}

//==============================================================================
void PrintResultCode (HRESULT hr)
{
#define CASEMSG(hr) case hr: printf(#hr); break;

	printf ("Done with result ");
	switch (hr)
	{
		CASEMSG(S_OK)
		CASEMSG(S_FALSE)
		CASEMSG(E_FAIL)

        CASEMSG(INET_E_INVALID_URL)
		CASEMSG(INET_E_NO_SESSION)
		CASEMSG(INET_E_CANNOT_CONNECT)
		CASEMSG(INET_E_RESOURCE_NOT_FOUND)
		CASEMSG(INET_E_OBJECT_NOT_FOUND)
		CASEMSG(INET_E_DATA_NOT_AVAILABLE)
		CASEMSG(INET_E_DOWNLOAD_FAILURE)
		CASEMSG(INET_E_AUTHENTICATION_REQUIRED)
		CASEMSG(INET_E_NO_VALID_MEDIA)  
		CASEMSG(INET_E_CONNECTION_TIMEOUT)
		CASEMSG(INET_E_INVALID_REQUEST)
		CASEMSG(INET_E_UNKNOWN_PROTOCOL)
		CASEMSG(INET_E_SECURITY_PROBLEM)
		CASEMSG(INET_E_CANNOT_LOAD_DATA)
		CASEMSG(INET_E_CANNOT_INSTANTIATE_OBJECT)
		
		default:
		    printf ("0x%x", hr);
	}
	printf ("\n");
}

//==============================================================================
BOOL RequestCallback (PHTTP_REQUESTCB_PARAM pCBParam)
{
    printf ("RequestCallback[%d] ", pCBParam->dwRequestCtx);

    switch (pCBParam->CallbackType)
    {
        case REQUESTCB_STARTED:
            printf ("Started\n");
            printf ("  Status: %d\n", pCBParam->dwResponseCode);
            printf ("  Content-Length: %d\n", pCBParam->dwContentLength);
            if (pCBParam->fdwRequestFlags & HTTP_REQUEST_ACCEPT_RANGES)
                printf ("  Accept-Ranges: bytes\n");
            if (pCBParam->fdwRequestFlags & HTTP_REQUEST_FROM_CACHE)
                printf ("  From Cache\n");
            return TRUE;

        case REQUESTCB_DATA:

		    // Dump some bytes so we can verify them.
		    printf ("offset=%5d got %4d bytes:",
		        pCBParam->dwDataOffset, pCBParam->cbDataLength);
		    DumpBytes ((PBYTE) pCBParam->lpDataBuffer, min(pCBParam->cbDataLength, 15));
		    printf ("\n");
		    return TRUE;

        case REQUESTCB_DONE:
            PrintResultCode (pCBParam->hrRequest);
            // Let the console app thread exit the message loop.
            PostThreadMessage (g_dwThread, WM_QUIT, 0, 0);
            return TRUE;
	}
}

//==============================================================================
int __cdecl main (int argc, char *argv[])
{
    MSG msg;
    HTTP_REQUEST_PARAM Param;

    SYSTEMTIME st;
    PSTR pszUrl;
    HTTP_REQUEST_RANGE ranges[10];
    DWORD cRanges;

    // Check usage.
    if (argc<2 || argc%2 || argc>(2*(sizeof(ranges))/sizeof(ranges[0])))
    {
        fprintf (stderr, "Usage:   range <http-url> [<offset1> <size1>]  [<offset2> <size2>]  [<offset3> <size3>]  ...\n");
        fprintf (stderr, "Example: range http://www.microsoft.com 2 5 10 52 20 4\n");
        exit (1);
    }

    // Get URL and ranges from command line.
    pszUrl = argv[1];
    cRanges = 0;
    while (argc -= 2)
    {
		if (argc <= 0)
			break;

    	ranges[cRanges].dwOffset = atoi(argv[2 * cRanges + 2]);
    	ranges[cRanges].dwSize   = atoi(argv[2 * cRanges + 3]);
        cRanges++;
    }

    // Pass current time as unless-modified-since time.
    GetSystemTime (&st);
    
    // Save the thread ID so the we can post ourselves
    // WM_QUIT from the callback without creating a window.
    g_dwThread = GetCurrentThreadId();

    // Read range depends on URL monikers which depend on COM.
    if (FAILED(CoInitialize(NULL)))
        exit (1);
    
    // Initiate the read range request.
    ZeroMemory (&Param, sizeof(Param));
    Param.cbStruct     = sizeof(Param);
    Param.pszUrl       = pszUrl;
    Param.pfnRequestCB = RequestCallback;
    Param.dwRequestCtx = 15;
    Param.pRanges      = &ranges[0];
    Param.cRanges      = cRanges;
    Param.pstUnlessModifiedSince = &st;
      
    if (HttpReadRequest (&Param))
    {
        // Must enter a message loop for the binding to progress.
        while (GetMessage (&msg, NULL, 0, 0))
        {
            TranslateMessage (&msg);
            DispatchMessage (&msg);
        }
    }

    CoUninitialize();
    return 1;
}

