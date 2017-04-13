/*
 * SELFREG.CPP
 * Server Self-Registrtation Utility, Chapter 5
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "selfreg.h"


/*
 * WinMain
 *
 * Purpose:
 *  Main entry point of application.
 */

int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hInstPrev
    , LPSTR pszCmdLine, int nCmdShow)
    {
    BOOL        fEXE=FALSE;
    BOOL        fUnreg=FALSE;
    LPSTR       psz;
    char        ch;

    /*
     * Walk down the command line looking for /u and /e in
     * any order.  The first non-whitespace character after
     * whitespace that is not a "/" is assumed to be the
     * beginning of the server filename.  This is all done
     * in ANSI because pszCmdLine is in ANSI.
     */

    psz=pszCmdLine;

    while (ch=*psz)
        {
        BOOL    fStop=FALSE;

        switch (ch)
            {
            case '\t':
            case '\n':
            case '\r':
            case ' ':
                //Scan for next non-whitespace and continue
                psz=PszWhiteSpaceScan(psz, TRUE);
                continue;

            case '/':
                /*
                 * Check what flag this is, then skip to next
                 * whitespace.
                 */
                ch=*(++psz);
                if ('u'==ch)
                    fUnreg=TRUE;

                if ('e'==ch)
                    fEXE=TRUE;

                psz=PszWhiteSpaceScan(psz, FALSE);
                continue;

            default:
                fStop=TRUE;
                break;
            }

        if (fStop)
            break;

        psz++;
        }


    if (0==ch)
        return 0;   //Nothing to do


    /*
     * Now launch and EXE or load a DLL and tell them to do
     * their registration or unregistartion.
     */
    if (fEXE)
        {
        char    szEXE[512];

        wsprintfA(szEXE, "%s %s", psz
            , fUnreg ? "/UNREGSERVER" : "/REGSERVER");
        WinExec(szEXE, SW_HIDE);

        MessageBoxA(NULL, fUnreg
            ? "EXE unregistration started"
            : "EXE registration started.", "SelfReg", MB_OK);
        }
    else
        {
        HINSTANCE       hMod;

        //Do this for the sake of DLLs.
        if (FAILED(CoInitialize(NULL)))
            return 0;

        hMod=LoadLibraryA(psz);

        if (hMod > (HINSTANCE)HINSTANCE_ERROR)
            {
            HRESULT (STDAPICALLTYPE *pfn)(void);
            BOOL    fRes=FALSE;

            if (fUnreg)
                {
                (FARPROC&)pfn=GetProcAddress(hMod
                    , "DllUnregisterServer");

                if (NULL!=pfn)
                    fRes=SUCCEEDED((*pfn)());

                MessageBoxA(NULL, fRes
                    ? "DLL unregistration succeeded."
                    : "DLL unregistration failed.", "SelfReg", MB_OK);
                }
            else
                {
                (FARPROC&)pfn=GetProcAddress(hMod
                    , "DllRegisterServer");

                if (NULL!=pfn)
                    fRes=SUCCEEDED((*pfn)());

                MessageBoxA(NULL , fRes
                    ? "DLL registration succeeded."
                    : "DLL registration failed.", "SelfReg", MB_OK);
                }

            CoFreeLibrary(hMod);
            CoUninitialize();
            }
        else
            {
            MessageBoxA(NULL, "LoadLibrary failed.", "SelfReg"
                , MB_OK);
            }
        }

    return 1;
    }




LPSTR PszWhiteSpaceScan(LPSTR psz, BOOL fSkip)
    {
    char        ch;
    BOOL        fWhite;

    while (ch=*psz)
        {
        fWhite=('\n'==ch || '\r'==ch
            || '\t'==ch || ' '==ch);

        //Too bad C doesn't have a logical XOR (^^) operator.
        if ((fSkip && !fWhite) || (!fSkip && fWhite))
            break;

        psz++;
        }

    return psz;
    }
